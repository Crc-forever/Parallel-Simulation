#include "ModelData.h"
#include "define.h"
#include "SimulationEngine.h"
#include <climits>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <direct.h>
#include <unordered_map>
#include <queue>

#include "xxhash.h"
#include <future>
#include <utility>
//#include "ModelInterface.h"
#include "ThreadPool.h"
#include "StateStore.h"
#include <filesystem>

#include "MemoryMappedFile.h"

namespace fs = std::filesystem;

using namespace std;

static std::mutex ioMutex; // IO线程池互斥锁
static ThreadPool ioThreadPool(64);

static std::unordered_set<int> passedWriteSliceIds; // 已经写入结果的切片Id集合,用于IO线程池避免无意义的写文件操作
static std::unordered_set<int> needWriteSliceIds; // 需要写入结果的切片Id集合,用于IO线程池避免无意义的写文件操作
static std::unordered_set<string> needWriteResultFileNames; // 需要写入结果的文件名集合,用于IO线程池避免无意义的写文件操作

static StateStore stateStore;

SimulationEngine::SimulationEngine() {
}

SimulationEngine::~SimulationEngine() {
}

const bool FLAG_PRINT = true;
const bool FLAG_WRITE_OUTPUT = true;

int Config_TOTAL_STEP = 100000000;
int Config_SLICE_STEP = 200000;
int Config_OUTBUFFER_COUNT = 20; //多缓冲区
int Config_OUTBUFFER_SIZE = 0; // Config_SLICE_STEP * MODEL_ONESTEP_OUTPUT_DATA_LEN;
int Config_STATE_SAMPLE_STEP = 1000;  // 每xx步采样一次状态
int Config_STATE_TOP_N = 5;           // 取前xx个状态
int Config_PARALLEL_SLICE_DELAY = 5;  // 并行执行的切片要在主线程的多少个切片之后
int Config_PARALLED_COUNT = 8;        // 与主线程并行的线程数
string Config_INPUT_FILE_PATH = "";  // 输入文件路径


MemoryMappedFile inputMMF;
unsigned long long inputDataFileSize = 0; // 输入文件大小

// vector<ifstream> inputFiles; // 为每个线程分别打开输入文件
vector<const char *> inputDataBufferPtrs; // 为主线程和其它线程分别创建输入数据缓冲区
// vector<vector<char>> startStateBuffers; // 为每个线程分别创建状态缓冲区
vector<vector<char>> stateBuffers; // 为每个线程分别创建状态缓冲区，
// 0段是startState，stateBuffers[threadid]前MODEL_STATE_DATA_LEN
// 1段是最终状态，stateBuffers[threadid]的之后MODEL_STATE_DATA_LEN
// 2段是TopNState，stateBuffers[threadid]的之后MODEL_STATE_DATA_LEN*Config_STATE_TOP_N
// 3段是当前临时状态，stateBuffers[threadid]的之后MODEL_STATE_DATA_LEN
vector<vector<vector<char>>> outputDataBuffers; // 为每个线程分别创建输出数据缓冲区  第一层是线程，第二层是多缓冲，第三层是数据    // **现在如果异步写输出数据的话，执行下以切片时，就会出现冲突，可以先动态申请内存出来，然后给异步线程去写**  解决方案：让它包含所有可能输出的数据，然后搞多重缓冲区
vector<int> outBufferWriteIndex; // 为每个线程分别创建输出数据缓冲区写入索引，缓冲区循环写入
vector<unordered_map<unsigned long long, int>> stateFreq; // 为每个线程分别创建状态频率表，key:状态哈希值，value:出现次数
vector<vector<SimulationEngine::TopNStateHashItem>> topNStateHash; // 为每个线程分别创建前Config_STATE_TOP_N个状态Hash

vector<unordered_map<unsigned long long, vector<char>>> hashStateMap; // 状态哈希值到状态的映射表

//定义宏定义，直接获取对应用途的stateBuffers的地址索引
#define START_STATE_BUFFER (stateBuffers[threadId].data())
#define FINAL_STATE_BUFFER (stateBuffers[threadId].data() + MODEL_STATE_DATA_LEN)
#define TOPN_STATE_BUFFER (stateBuffers[threadId].data() + MODEL_STATE_DATA_LEN * 2)
#define TEMP_STATE_BUFFER (stateBuffers[threadId].data() + MODEL_STATE_DATA_LEN * Config_STATE_TOP_N)



void SimulationEngine::init(int argc, const char *argv[]) {


    // 解析所有参数到Config_*中
    if (!initParseArg(argc, argv)) {
        return;
    }

    timer.startSection("initCreateDirs_in_init");
    initCreateDirs();
    timer.endSection("initCreateDirs_in_init");
    
    Config_OUTBUFFER_SIZE = Config_SLICE_STEP * MODEL_ONESTEP_OUTPUT_DATA_LEN;
    total_slice_count = Config_TOTAL_STEP/Config_SLICE_STEP;
    if (Config_TOTAL_STEP % Config_SLICE_STEP != 0) {
        total_slice_count++;
    }

    timer.startSection("initBuffers_in_init");
    initBuffers();
    timer.endSection("initBuffers_in_init");

    executedStateHashMap.resize(total_slice_count);

    //// 获取输入文件大小
    //std::ifstream inputFile(Config_INPUT_FILE_PATH, std::ios::binary);
    //if (!inputFile.is_open()) {
    //    printf("Error: Failed to open input file %s\n", Config_INPUT_FILE_PATH.c_str());
    //    return;
    //}
    //inputFile.seekg(0, std::ios::end);
    //inputDataFileSize = inputFile.tellg();
    //inputFile.close();
    
}

bool SimulationEngine::initParseArg(int argc, const char *argv[]) {
    if (argc > 8) {
        Config_TOTAL_STEP = atoi(argv[1]);
        Config_SLICE_STEP = atoi(argv[2]);
        Config_OUTBUFFER_COUNT = atoi(argv[3]);
        Config_STATE_SAMPLE_STEP = atoi(argv[4]);
        Config_STATE_TOP_N = atoi(argv[5]);
        Config_PARALLEL_SLICE_DELAY = atoi(argv[6]);
        Config_PARALLED_COUNT = atoi(argv[7]);
        Config_INPUT_FILE_PATH = argv[8];
    } else {
        printf("Usage:\n");
        printf("  <Total Step>\n");
        printf("  <Slice Step>\n");
        printf("  <OutBuffer Count>\n");
        printf("  <State Sample Step>\n");
        printf("  <State Top N>\n");
        printf("  <Parallel Slice Delay>\n");
        printf("  <Paralled Count>\n");
        printf("  <Input File Path>\n");
        return false;
    }
    printf("Step: %d\n", Config_TOTAL_STEP);
    printf("Slice Step: %d\n", Config_SLICE_STEP);
    printf("OutBuffer Count: %d\n", Config_OUTBUFFER_COUNT);
    printf("State Sample Step: %d\n", Config_STATE_SAMPLE_STEP);
    printf("State Top N: %d\n", Config_STATE_TOP_N);
    printf("Parallel Slice Delay: %d\n", Config_PARALLEL_SLICE_DELAY);
    printf("Paralled Count: %d\n", Config_PARALLED_COUNT);
    printf("Input File Path: %s\n", Config_INPUT_FILE_PATH.c_str());
    return true;
}

void SimulationEngine::initCreateDirs()
{
    // 根输出目录
    fs::path simOutDir = "SimOut";
    fs::path outputDataDir = simOutDir / "OutputData";
    fs::path tempDir = simOutDir / "Temp";

    // 1. 确保 SimOut 存在
    fs::create_directories(simOutDir);

    // 2. 清空并创建 OutputData
    if (fs::exists(outputDataDir)) {
        for (const auto& entry : fs::directory_iterator(outputDataDir)) {
            fs::remove_all(entry);
        }
    } else {
        fs::create_directories(outputDataDir);
    }

    // 3. 清空并创建 Temp
    if (fs::exists(tempDir)) {
        for (const auto& entry : fs::directory_iterator(tempDir)) {
            fs::remove_all(entry);
        }
    } else {
        fs::create_directories(tempDir);
    }
}

bool SimulationEngine::initBuffers() {
    // 为每个线程分别打开输入文件

    timer.startSection("initBuffers_openfile");
    //
    //inputFiles.resize(Config_PARALLED_COUNT + 1);
    //for (int i = 0; i < Config_PARALLED_COUNT + 1; i++) {
    //    inputFiles[i].open(Config_INPUT_FILE_PATH, std::ios::binary);
    //    if (!inputFiles[i]) {
    //        std::cerr << "Worker " << i
    //                  << " failed to open file " << Config_INPUT_FILE_PATH << "\n";
    //        return false;
    //    }
    //}
    
    
    inputMMF.open(Config_INPUT_FILE_PATH);
    // 判断是否成功打开文件
    if (!inputMMF.isOpen()) {
        std::cerr << "Failed to open file " << Config_INPUT_FILE_PATH << "\n";
        return false;
    }
    inputDataFileSize = inputMMF.size();

    timer.endSection("initBuffers_openfile");
    
    timer.startSection("initBuffers_createbuffer");
    // 为主线程和其它线程分别创建输入数据缓冲区
    inputDataBufferPtrs.resize(Config_PARALLED_COUNT + 1);
    stateBuffers.resize((Config_PARALLED_COUNT + 1));
    //startStateBuffers.resize(Config_PARALLED_COUNT + 1);
    outputDataBuffers.resize(Config_PARALLED_COUNT + 1);
    outBufferWriteIndex.resize(Config_PARALLED_COUNT + 1, 0);

    stateFreq.resize(Config_PARALLED_COUNT + 1);
    topNStateHash.resize(Config_PARALLED_COUNT + 1);
    hashStateMap.resize(Config_PARALLED_COUNT + 1);
    timer.endSection("initBuffers_createbuffer");

    timer.startSection("initBuffers_resizebuffer");
    for (int i = 0; i < Config_PARALLED_COUNT + 1; i++) {

        //inputDataBuffers[i].resize(Config_SLICE_STEP * MODEL_ONESTEP_INPUT_DATA_LEN);
        stateBuffers[i].resize(MODEL_STATE_DATA_LEN * (Config_STATE_TOP_N + 3));
        //startStateBuffers[i].resize(MODEL_STATE_DATA_LEN);
        outputDataBuffers[i].resize(Config_OUTBUFFER_COUNT);

        timer.startSection("initBuffers_resize_outputDataBuffers");
        for (int j = 0; j < Config_OUTBUFFER_COUNT; j++) {
            outputDataBuffers[i][j].resize(Config_SLICE_STEP * MODEL_ONESTEP_OUTPUT_DATA_LEN);
        }
        timer.endSection("initBuffers_resize_outputDataBuffers");

        topNStateHash[i].resize(Config_STATE_TOP_N);
    }
    timer.endSection("initBuffers_resizebuffer");

    return true;
}

// 执行一个切片
// 主线程为0，其它线程为1~Config_PARALLED_COUNT
void SimulationEngine::simulataOneSlice(int slice_id, int threadId) {
    // 只为主线程计时
    if (threadId == 0) {
        timer.startSection("simulataOneSlice");
    }

    // 重置统计状态频次
    stateFreq[threadId].clear();

    if (threadId == 0) timer.startSection("simulataOneSlice_readinput");
    // 先从输入数据文件中读取一个切片的数据
    //auto &ifs = inputFiles[threadId];
    //const std::streamsize bytes = Config_SLICE_STEP * MODEL_ONESTEP_INPUT_DATA_LEN;
    //char* dst = inputDataBuffers[threadId].data();
    //
    //ifs.clear();
    //const uint64_t logicalOffset = static_cast<uint64_t>(slice_id) * bytes;
    //const std::streamoff fileOffset = static_cast<std::streamoff>(logicalOffset % inputDataFileSize);
    //const std::streamsize bytesToEnd = inputDataFileSize - fileOffset;

    const uint64_t bytesPerSlice = static_cast<uint64_t>(Config_SLICE_STEP) * MODEL_ONESTEP_INPUT_DATA_LEN;
    uint64_t fileOffset = (static_cast<uint64_t>(slice_id) * bytesPerSlice) % inputDataFileSize;

    const char* inputPtr = inputMMF.base() + fileOffset;
    inputDataBufferPtrs[threadId] = inputPtr;

    //if (bytesToEnd >= bytes) {
    //    // 情况 1：不跨文件尾
    //    ifs.seekg(fileOffset, std::ios::beg);
    //    ifs.read(dst, bytes);
    //} else {
    //    // 情况 2：跨文件尾
    //    // 先读到文件尾
    //    ifs.seekg(fileOffset, std::ios::beg);
    //    ifs.read(dst, bytesToEnd);
//
    //    // 再从文件头读剩余部分
    //    ifs.seekg(0, std::ios::beg);
    //    ifs.read(dst + bytesToEnd, bytes - bytesToEnd);
    //}

    if (threadId == 0) timer.endSection("simulataOneSlice_readinput");

    // 起始执行状态Hash
    if (threadId == 0) timer.startSection("calculateStateHash_in_simulataOneSlice");
    SE_Interface_GetState(START_STATE_BUFFER);
    unsigned long long startStateHash = calculateStateHash(START_STATE_BUFFER, MODEL_STATE_DATA_LEN); // XXH3_64bits(startStateBuffers[threadId].data(), MODEL_STATE_DATA_LEN);
    if (threadId == 0) timer.endSection("calculateStateHash_in_simulataOneSlice");
    

    if (threadId == 0) timer.startSection("simulataOneSlice_executeslice");
    // 执行一个切片
    for (int i = 0; i < Config_SLICE_STEP; i++) {
        SE_Interface_OneStep(
                             inputDataBufferPtrs[threadId] + i * MODEL_ONESTEP_INPUT_DATA_LEN,
                             outputDataBuffers[threadId][outBufferWriteIndex[threadId]].data() + i * MODEL_ONESTEP_OUTPUT_DATA_LEN);
        // 采用统计状态排名
        if (i % Config_STATE_SAMPLE_STEP == 0) {
            if (threadId == 0) timer.startSection("simulataOneSlice_executeslice_calculateStateHash");
            //if (i != 0) {
            SE_Interface_GetState(TEMP_STATE_BUFFER);
            //}
            unsigned long long curStateHash = calculateStateHash(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN); // XXH3_64bits(stateBuffers[threadId].data(), MODEL_STATE_DATA_LEN);
            stateFreq[threadId][curStateHash]++;
            
            // 取临时状态缓冲区的拷贝
            if(stateFreq[threadId][curStateHash] == 1) {
                hashStateMap[threadId][curStateHash] = vector<char>(TEMP_STATE_BUFFER, TEMP_STATE_BUFFER + MODEL_STATE_DATA_LEN);
            }
            if (threadId == 0) timer.endSection("simulataOneSlice_executeslice_calculateStateHash");
        }
    }
    if (threadId == 0) timer.endSection("simulataOneSlice_executeslice");

    if (threadId == 0) timer.startSection("getTopNStateHash_in_simulataOneSlice");
    // 获取前Config_STATE_TOP_N个状态的Hash
    getTopNStateHash(threadId);
    if (threadId == 0) timer.endSection("getTopNStateHash_in_simulataOneSlice");

    if (threadId == 0) timer.startSection("writeSimulateResult_in_simulataOneSlice");
    // 写入子线程的仿真结果
    writeSimulateResult(threadId, slice_id, startStateHash);
    if (threadId == 0) timer.endSection("writeSimulateResult_in_simulataOneSlice");
    
    // 只为主线程计时
    if (threadId == 0) {
        timer.endSection("simulataOneSlice");
    }
}

void SimulationEngine::getTopNStateHash(int threadId)
{
    auto cmp = [](const TopNStateHashItem& a, const TopNStateHashItem& b) {
        return a.count > b.count; // 小顶堆
    };

    // 统计前Config_STATE_TOP_N个状态
    std::priority_queue<TopNStateHashItem, std::vector<TopNStateHashItem>, decltype(cmp)> heap(cmp);
    for (const auto& pair : stateFreq[threadId]) {
        unsigned long long hash = pair.first;
        int cnt = pair.second;
        if ((int)heap.size() < Config_STATE_TOP_N) {
            heap.push({hash, cnt});
        } else if (cnt > heap.top().count) {
            heap.pop();
            heap.push({hash, cnt});
        }
    }
    
    int heapSize = heap.size();
    for (int i = heapSize - 1; i >= 0; i--) {
        if (!heap.empty()) {
            topNStateHash[threadId][i] = heap.top();
            heap.pop();
        }
        else {
            topNStateHash[threadId][i] = {0, 0};
        }
    }
}

// 写入子线程的仿真结果 *** 现在是同步写的 ***
void SimulationEngine::writeSimulateResult(int threadId, int slice_id, unsigned long long startStateHash)
{
    
    if (threadId == 0) {
        // 直接写出主线程的输出数据
        std::stringstream ss;
        ss << std::setw(9) << std::setfill('0') << slice_id;
        string sliceIdStr = ss.str();

        string fileName = "SimOut/OutputData/" + sliceIdStr + ".bin";
        int size = Config_SLICE_STEP * MODEL_ONESTEP_OUTPUT_DATA_LEN;
        char* data = outputDataBuffers[threadId][outBufferWriteIndex[threadId]].data();

        if (FLAG_WRITE_OUTPUT) {

            std::vector<char> snapshot(data, data + size);
            ioThreadPool.enqueue(0, [buf = std::move(snapshot), fileName]() {
                std::ofstream f(fileName, std::ios::binary);
                f.write(buf.data(), buf.size());
            });
        }

        //std::async(std::launch::async, [=]() {
        //    try {
        //        std::ofstream outFile("SimOut/OutputData/" + sliceIdStr + ".bin", std::ios::binary);
        //        outFile.write(outputDataBuffers[threadId][outBufferWriteIndex[threadId]].data(), Config_SLICE_STEP * MODEL_ONESTEP_OUTPUT_DATA_LEN);
        //        outFile.close();
        //    } catch (const std::exception& e) {
        //        std::cerr << "Error in writeSimulateResult threadId == 0: " << e.what() << std::endl;
        //    }
        //});
        
    }
    else {
        // 子线程将输出数据写入临时文件
        std::stringstream ss;
        ss << std::setw(9) << std::setfill('0') << slice_id;
        string sliceIdStr = ss.str();
        ss << "_" << std::hex << startStateHash;
        string file = ss.str();

        //memcpy(outputDataBuffers[threadId][outBufferWriteIndex[threadId]].data(), START_STATE_BUFFER, MODEL_STATE_DATA_LEN);
        //int offset = MODEL_STATE_DATA_LEN + Config_SLICE_STEP * MODEL_ONESTEP_OUTPUT_DATA_LEN;
        SE_Interface_GetState(FINAL_STATE_BUFFER);
        int offset = 0;
        for (const auto& item : topNStateHash[threadId]) {
            if (item.hash != 0) {
                memcpy(TOPN_STATE_BUFFER + offset, hashStateMap[threadId][item.hash].data(), MODEL_STATE_DATA_LEN);
                
            } else {
                memset(TOPN_STATE_BUFFER + offset, 0, MODEL_STATE_DATA_LEN);
            }
            offset += MODEL_STATE_DATA_LEN;
        }

        string fileName = "SimOut/Temp/" + file + "_State.bin";
        //int size = (Config_STATE_TOP_N + 2) * MODEL_STATE_DATA_LEN;
        //char* data = START_STATE_BUFFER;
        stateStore.put(fileName, vector<char>(stateBuffers[threadId]));

        // ioThreadPool.enqueue([data, size, fileName]() {
        //     std::ofstream f(fileName, std::ios::binary);
        //     f.write(data, size);
        //     f.close();
        // });

        if (FLAG_WRITE_OUTPUT) {
            fileName = "SimOut/Temp/" + file + "_Output.bin";
            int size = Config_OUTBUFFER_SIZE;
            char* data = outputDataBuffers[threadId][outBufferWriteIndex[threadId]].data();
            
            std::vector<char> snapshot(data, data + size);
            ioThreadPool.enqueue(2, [buf = std::move(snapshot), fileName, slice_id]() {

                {
                    std::lock_guard<std::mutex> lk(ioMutex);
                    if (passedWriteSliceIds.find(slice_id) != passedWriteSliceIds.end()) {
                        // cout << "No need to write slice " << slice_id << "\n";
                        return;
                    }
                    if (needWriteSliceIds.find(slice_id) != needWriteSliceIds.end() && 
                        needWriteResultFileNames.find(fileName) == needWriteResultFileNames.end()) {
                        // cout << "No need to write  output file" << fileName << "\n";
                        return;
                    }
                }



                std::ofstream f(fileName, std::ios::binary);
                f.write(buf.data(), buf.size());
            });
        }



        // std::async(std::launch::async, [=]() {
        //     try {
        //         int len = (Config_STATE_TOP_N + 2) * MODEL_STATE_DATA_LEN;
        //         std::ofstream stateFile("SimOut/Temp/" + fileName + "_State.bin", std::ios::binary);
        //         stateFile.write(START_STATE_BUFFER, len); // offset等于长度
        //         stateFile.close();
        //         if (!FLAG_DONOT_WRITE_OUTPUT) {
        //             std::ofstream outFile("SimOut/Temp/" + fileName + "_Output.bin", std::ios::binary);
        //             outFile.write(outputDataBuffers[threadId][outBufferWriteIndex[threadId]].data(), Config_OUTBUFFER_SIZE); // offset等于长度
        //             outFile.close();
        //         }
        //     } catch (const std::exception& e) {
        //         std::cerr << "Error in writeSimulateResult threadId == 0: " << e.what() << std::endl;
        //     }
        // });
        
    }
    outBufferWriteIndex[threadId] = (outBufferWriteIndex[threadId] + 1) % Config_OUTBUFFER_COUNT;
}


void worker_thread(
    int index,                          // 线程编号
    std::vector<std::unique_ptr<SimulationEngine::Worker>>* workers,   // 所有 Worker 数组
    SimulationEngine* se                // 指向主引擎的指针
) {
    // 初始化子线程的 SE 接口
    SE_Interface_Init();
    if (FLAG_PRINT) {
        cout << "Worker " << index << " initialized\n";
    }
    //// 如果文件打开失败，直接报错并退出线程
    //if (!inputFiles[index]) {
    //    std::cerr << "Worker " << index
    //              << " failed to open file " << Config_INPUT_FILE_PATH << "\n";
    //    return;
    //}

    // ===== 2. 进入“等待-执行”循环 =====
    while (true) {
        SimulationEngine::TaskParam local;  // 本地拷贝，避免执行期间持锁

        {
            // 加锁，准备检查状态
            std::unique_lock<std::mutex> lk((*workers)[index-1]->m);

            // 等待主线程发启动命令
            (*workers)[index-1]->cv.wait(lk, [&] {
                return (*workers)[index-1]->has_task ||
                       (*workers)[index-1]->stop;
            });

            // 如果主线程要求退出
            if ((*workers)[index-1]->stop) {
                break;
            }
            local = (*workers)[index-1]->param;
            // 拷贝本时间片参数
            local.slice_id = (*workers)[index-1]->param.slice_id;
            SE_Interface_SetState((*workers)[index-1]->param.state.data());

            // 清除任务标志，表示“已领取”
            (*workers)[index-1]->has_task = false;
        } // 立即释放锁

        unsigned long long localStateHash = se->calculateStateHash(local.state.data(), MODEL_STATE_DATA_LEN); // XXH3_64bits(local.state.data(), MODEL_STATE_DATA_LEN);
        // cout << "Worker " << index << " start slice " << local.slice_id << " with state hash " << std::hex << localStateHash << std::dec << endl;

        // ===== 3. 执行一个时间片的工作 =====

        //// 定位到指定文件偏移
        //const uint64_t bytesPerSlice = static_cast<uint64_t>(Config_SLICE_STEP) * MODEL_ONESTEP_INPUT_DATA_LEN;
        //uint64_t fileOffset = (static_cast<uint64_t>(local.slice_id) * bytesPerSlice) % inputDataFileSize;
        //const char* inputPtr = inputMMF.base() + fileOffset;
        //inputDataBufferPtrs[index] = inputPtr;
        
        //size_t offset = local.slice_id * Config_SLICE_STEP * MODEL_ONESTEP_INPUT_DATA_LEN;
        //inputFiles[index].seekg(offset, std::ios::beg);
        //
        //// 读取数据
        //inputFiles[index].read(inputDataBuffers[index].data(), Config_SLICE_STEP * MODEL_ONESTEP_INPUT_DATA_LEN);

        se->simulataOneSlice(local.slice_id, index);
    }

    //std::cout << "Worker " << index << " exiting\n";
}

void SimulationEngine::start() {

    int threadId = 0;

    timer.startSection("worker_thread");
    workers.clear();
    for (int i = 0; i < Config_PARALLED_COUNT; i++) {
        workers.emplace_back(std::unique_ptr<Worker>(new Worker()));

    }
    timer.endSection("worker_thread");

    timer.startSection("worker_thread_start");
    
    for (int i = 0; i < Config_PARALLED_COUNT; i++) {
        threads.emplace_back(worker_thread, i + 1, &workers, this);
    }
    timer.endSection("worker_thread_start");

    start_time = clock();

    SE_Interface_Init();

    for (int i = 0; i < 1; i++) {
        simulataOneSlice(i, 0);

        current_slice_id++;
    }

    for (int i = 0; i < total_slice_count - 1; i++) {
        
        timer.startSection("tryJumpNextSlice");
        bool res = tryJumpNextSlice();
        timer.endSection("tryJumpNextSlice");
        if (res) {
            continue;
        }

        timer.startSection("scheduleParallelTask");
        scheduleParallelTask();
        timer.endSection("scheduleParallelTask");
        
        timer.startSection("calculateStateHash");
        SE_Interface_GetState(TEMP_STATE_BUFFER);
        unsigned long long stateHash = calculateStateHash(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN); // XXH3_64bits(stateBuffers[0].data(), MODEL_STATE_DATA_LEN);
        timer.endSection("calculateStateHash");
        
        if (FLAG_PRINT) {
            cout << "Main thread start slice " << current_slice_id << " with state hash " << std::hex << stateHash << std::dec << endl;
        }
        {
            std::lock_guard<std::mutex> lk(ioMutex);
            passedWriteSliceIds.insert(current_slice_id);
        }
        simulataOneSlice(current_slice_id, 0);

        current_slice_id++;
    }

    
}

bool SimulationEngine::tryJumpNextSlice() {
    
    int threadId = 0;

    // 判断是否存在一个已经写入完成的文件“0000000XXX_State_OutputAndState.bin”
    // 每个切片结果文件的文件名格式为“0000000XXX_State(16进制的Hash值)_OutputAndState.bin”，XXX为切片ID
    // 文件的前MODEL_STATE_DATA_LEN个字节为状态数据，
    // 之后是该状态下的所有输出数据，输出数据的长度为Config_OUTBUFFER_SIZE = Config_SLICE_STEP * MODEL_ONESTEP_OUTPUT_DATA_LEN
    // 之后执行完该切片后的状态数据，状态数据的长度为MODEL_STATE_DATA_LEN个字节
    // 再之后是排名前N的状态，每个状态数据的长度为MODEL_STATE_DATA_LEN个字节，共Config_STATE_TOP_N个状态数据

    SE_Interface_GetState(TEMP_STATE_BUFFER);
    unsigned long long stateHash = calculateStateHash(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN); // XXH3_64bits(stateBuffers[0].data(), MODEL_STATE_DATA_LEN);
    std::stringstream ss;

    // 16进制的stateHash
    ss << std::setw(9) << std::setfill('0') << current_slice_id;
    string sliceIdStr = ss.str();
    ss << "_" << std::hex << stateHash;
    string filename = ss.str();

    //// 判断该文件是否不存在，不存在则不能跳过当前切片
    //std::ifstream file("SimOut/Temp/" + filename + "_State.bin", std::ios::binary);
    //if (!file) {
    //    return false;
    //}


    bool res = stateStore.take("SimOut/Temp/" + filename + "_State.bin", stateBuffers[threadId]);
    if (!res) {
        return false;
    }

    //// 存在的话，则读取前N个字节，判断是否是正确的状态
    //file.read(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN);
    bool isSame = SE_Interface_CompareState(START_STATE_BUFFER);
    if (!isSame) {
        //file.close();
        return false;
    }
    
    // 异步拷贝该文件到主线程输出目录
    if (FLAG_WRITE_OUTPUT) {
        copyTempSimulateResultList.emplace_back(filename + "_Output.bin", sliceIdStr + ".bin");

        {
            std::lock_guard<std::mutex> lk(ioMutex);
            needWriteSliceIds.insert(current_slice_id);
            needWriteResultFileNames.insert("SimOut/Temp/" + filename + "_Output.bin");
        }
        //asyncCopyTempSimulateResult(filename + "_Output.bin", sliceIdStr + ".bin");
    }

    //// 继续读MODEL_STATE_DATA_LEN个字节获取该Slice的最终状态，并设置当前状态
    //file.read(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN);
    SE_Interface_SetState(FINAL_STATE_BUFFER);

    // 读取文件之后TopN个状态
    //file.seekg(-MODEL_STATE_DATA_LEN * Config_STATE_TOP_N, std::ios::end);
    for (int i = 0; i < Config_STATE_TOP_N; ++i) {
        // file.read(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN);
        topNStateHash[0][i].hash = calculateStateHash(TOPN_STATE_BUFFER + i * MODEL_STATE_DATA_LEN, MODEL_STATE_DATA_LEN); // (stateBuffers[0].data(), MODEL_STATE_DATA_LEN);
        topNStateHash[0][i].count = 0;
        if (topNStateHash[0][i].hash != 0) {
            hashStateMap[0][topNStateHash[0][i].hash] = vector<char>(TOPN_STATE_BUFFER + i * MODEL_STATE_DATA_LEN, TOPN_STATE_BUFFER + (i + 1) * MODEL_STATE_DATA_LEN);
        }
    }

    //file.close();
    
    // 直接跳过当前切片，执行下一个切片
    if (FLAG_PRINT) {
        cout << "Jump to slice " << current_slice_id << " with state hash " << std::hex << stateHash << std::dec << endl;
    }
    
    current_slice_id++;
    jumpCount++;
    return true;
}


// 异步拷贝仿真结果到主线程输出目录
void SimulationEngine::asyncMoveTempSimulateResult(string src, string dst) {

    string fullSrcPath = "SimOut/Temp/" + src;
    string fullDstPath = "SimOut/OutputData/" + dst;
    ioThreadPool.enqueue(1,[fullSrcPath, fullDstPath]() {
        try {
            fs::rename(fullSrcPath, fullDstPath);
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Move failed: " << e.what() << std::endl;
        }
    });



    //// 使用std::async异步执行文件拷贝操作
    //std::async(std::launch::async, [=]() {
    //    try {
    //        // 为src和dst添加完整路径
    //        string fullSrcPath = "SimOut/Temp/" + src;
    //        string fullDstPath = "SimOut/OutputData/" + dst;
    //        
    //        // 直接拷贝完整文件，采用简洁的代码
    //        std::ifstream infile(fullSrcPath, std::ios::binary);
    //        std::ofstream outfile(fullDstPath, std::ios::binary);
    //        if (!infile) {
    //            std::cerr << "Failed to open source or destination file: " << fullSrcPath << std::endl;
    //            return;
    //        }
    //        if (!outfile) {
    //            std::cerr << "Failed to open source or destination file: " << fullDstPath << std::endl;
    //            return;
    //        }
//
    //        outfile << infile.rdbuf();
//
    //        infile.close();
    //        outfile.close();
    //    } catch (const std::exception& e) {
    //        std::cerr << "Error in asyncCopyTempSimulateResult: " << e.what() << std::endl;
    //    }
    //});
}

void SimulationEngine::scheduleParallelTask()
{

    int parallelSliceId = current_slice_id + Config_PARALLEL_SLICE_DELAY;
    

    int taskScheduled = 0;
    while (true)
    {
        if (parallelSliceId >= total_slice_count) {
            break;
        }
        for (int i = 0; taskScheduled < Config_PARALLED_COUNT && i < Config_STATE_TOP_N; ++i) {

            // 判断parallelSliceId上是否执行过TopNStateHash的任务
            TopNStateHashItem& item = topNStateHash[0][i];
            if (executedStateHashMap[parallelSliceId].find(item.hash) != executedStateHashMap[parallelSliceId].end()) {
                continue;
            }

            executedStateHashMap[parallelSliceId][item.hash] = true;

            TaskParam p;
            p.task_id = taskScheduled;
            p.slice_id = parallelSliceId;
            p.state = hashStateMap[0][item.hash];

            {
                // 写入任务参数
                std::lock_guard<std::mutex> lk(workers[taskScheduled]->m);
                workers[taskScheduled]->param = p;
                workers[taskScheduled]->has_task = true;
            }
            // 唤醒指定线程
            workers[taskScheduled]->cv.notify_one();

            taskScheduled++;

            if (taskScheduled >= Config_PARALLED_COUNT) {
                break;
            }
        }
        
        if (taskScheduled >= Config_PARALLED_COUNT) {
            break;
        }
        parallelSliceId++;
    }
    
    if (taskScheduled == 0)
    {
        cout << "Schedule Finish" << endl;
    }
}

void SimulationEngine::finish()
{
    
    // 输出主线程函数simulataOneSlice的统计结果
    timer.printStatistics();
    
    clock_t end_time = clock();
    double time_cost = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Simulation Time cost: " << time_cost << " seconds" << std::endl;

    std::cout << "Jump Count: " << jumpCount << " Total Slice Count: " << total_slice_count << " Jump Rate: " << (double)jumpCount / total_slice_count * 100 << "%" <<std::endl;
    
    inputMMF.close();
    // for (int i = 0; i < Config_PARALLED_COUNT + 1; ++i) {
    //     inputFiles[i].close();
    // }

    // ===== 通知所有线程退出 =====
    for (int i = 0; i < Config_PARALLED_COUNT; ++i) {
        {
            std::lock_guard<std::mutex> lk(workers[i]->m);
            workers[i]->stop = true;
        }
        workers[i]->cv.notify_one();
    }

    // ===== 等待所有线程结束 =====
    for (auto& t : threads) {
        t.join();
    }

    ioThreadPool.waitIdle();

    
    for (auto& [src, dst] : copyTempSimulateResultList) {
        asyncMoveTempSimulateResult(src, dst);
    }
}

unsigned long long SimulationEngine::calculateStateHash(char* state, int len)
{
    //// 直接用state的前三个字节作为hash值
    //unsigned long long hash = 0;
    //for (int i = 0; i < 3; ++i) {
    //    hash = hash * 256 + (unsigned char)state[i];
    //}
    unsigned long long hash = XXH3_64bits(state, len);
    return hash;
}