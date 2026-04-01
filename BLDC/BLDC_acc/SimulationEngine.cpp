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

static std::mutex ioMutex; // IO˜???˜˜˜˜˜
static ThreadPool ioThreadPool(64);

static std::unordered_set<int> passedWriteSliceIds; // ˜?˜?˜˜˜˜˜˜˜˜?Id˜˜˜˜,˜˜˜˜IO˜???˜˜˜˜˜˜˜˜˜˜?˜?˜˜˜˜˜
static std::unordered_set<int> needWriteSliceIds; // ˜˜??˜˜˜˜˜˜˜˜?Id˜˜˜˜,˜˜˜˜IO˜???˜˜˜˜˜˜˜˜˜˜?˜?˜˜˜˜˜
static std::unordered_set<string> needWriteResultFileNames; // ˜˜??˜˜˜˜˜˜˜?˜˜˜˜˜˜˜,˜˜˜˜IO˜???˜˜˜˜˜˜˜˜˜˜?˜?˜˜˜˜˜

static StateStore stateStore;

SimulationEngine::SimulationEngine() {
}

SimulationEngine::~SimulationEngine() {
}

const bool FLAG_PRINT = true;
const bool FLAG_WRITE_OUTPUT = true;

int Config_TOTAL_STEP = 100000000;
int Config_SLICE_STEP = 200000;
int Config_OUTBUFFER_COUNT = 20; //˜?˜˜˜˜
int Config_OUTBUFFER_SIZE = 0; // Config_SLICE_STEP * MODEL_ONESTEP_OUTPUT_DATA_LEN;
int Config_STATE_SAMPLE_STEP = 1000;  // ?xx˜˜˜˜˜˜?˜˜??
int Config_STATE_TOP_N = 5;           // ??xx˜˜??
int Config_PARALLEL_SLICE_DELAY = 5;  // ˜˜˜˜?˜?˜˜˜??˜˜˜˜˜???˜˜?˜˜˜??˜˜
int Config_PARALLED_COUNT = 8;        // ˜˜˜˜˜??˜˜?˜˜?˜˜˜
string Config_INPUT_FILE_PATH = "";  // ˜˜˜˜˜?˜·˜˜


MemoryMappedFile inputMMF;
unsigned long long inputDataFileSize = 0; // ˜˜˜˜˜?˜˜˜?

// vector<ifstream> inputFiles; // ??˜˜˜???˜˜˜˜˜˜˜?˜
vector<const char *> inputDataBufferPtrs; // ?˜˜˜??˜˜˜˜˜˜?????˜˜˜˜˜˜˜˜?˜˜˜˜˜
// vector<vector<char>> startStateBuffers; // ??˜˜˜?????˜??˜˜˜˜˜˜
vector<vector<char>> stateBuffers; // ??˜˜˜?????˜??˜˜˜˜˜˜˜˜
// 0˜˜˜˜startState˜˜stateBuffers[threadid]?MODEL_STATE_DATA_LEN
// 1˜˜˜˜˜˜˜˜??˜˜stateBuffers[threadid]˜˜?˜˜MODEL_STATE_DATA_LEN
// 2˜˜˜˜TopNState˜˜stateBuffers[threadid]˜˜?˜˜MODEL_STATE_DATA_LEN*Config_STATE_TOP_N
// 3˜˜˜?˜?˜˜???˜˜stateBuffers[threadid]˜˜?˜˜MODEL_STATE_DATA_LEN
vector<vector<vector<char>>> outputDataBuffers; // ??˜˜˜?????˜˜˜˜˜˜˜?˜˜˜˜˜  ˜˜?˜˜˜˜˜??˜˜?˜˜˜˜??˜?˜˜˜˜˜˜˜˜˜˜˜˜    // **˜˜˜˜˜˜˜˜??˜˜˜˜˜˜??˜˜˜?˜˜˜˜˜˜˜˜??˜˜˜?˜˜˜?˜?˜˜˜˜˜˜˜?˜?˜˜˜˜˜?˜˜˜˜˜˜?˜˜˜˜?˜?˜??**  ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜?˜˜˜˜˜˜˜˜˜˜˜?˜?˜˜˜˜˜?˜˜˜˜˜
vector<int> outBufferWriteIndex; // ??˜˜˜?????˜˜˜˜˜˜˜?˜˜˜˜˜?˜˜˜˜˜˜˜˜˜˜˜˜˜˜?˜˜?˜˜
vector<unordered_map<unsigned long long, int>> stateFreq; // ??˜˜˜?????˜???˜?˜˜˜key:??˜˜??˜˜value:˜˜˜?˜˜˜
vector<vector<SimulationEngine::TopNStateHashItem>> topNStateHash; // ??˜˜˜?????˜?Config_STATE_TOP_N˜˜??Hash

vector<unordered_map<unsigned long long, vector<char>>> hashStateMap; // ??˜˜??˜˜??˜˜?˜˜˜

//˜˜˜˜?˜??˜?˜?˜˜?˜˜?˜˜stateBuffers˜?˜?˜˜˜˜
#define START_STATE_BUFFER (stateBuffers[threadId].data())
#define FINAL_STATE_BUFFER (stateBuffers[threadId].data() + MODEL_STATE_DATA_LEN)
#define TOPN_STATE_BUFFER (stateBuffers[threadId].data() + MODEL_STATE_DATA_LEN * 2)
#define TEMP_STATE_BUFFER (stateBuffers[threadId].data() + MODEL_STATE_DATA_LEN * Config_STATE_TOP_N)



void SimulationEngine::init(int argc, const char *argv[]) {


    // ˜˜˜˜˜˜˜?˜˜˜˜˜Config_*˜˜
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

    //// ˜˜?˜˜˜˜˜?˜˜˜?
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
    // ˜˜˜˜˜??
    fs::path simOutDir = "SimOut";
    fs::path outputDataDir = simOutDir / "OutputData";
    fs::path tempDir = simOutDir / "Temp";

    // 1. ?˜˜ SimOut ˜˜˜˜
    fs::create_directories(simOutDir);

    // 2. ˜˜?˜˜˜˜˜ OutputData
    if (fs::exists(outputDataDir)) {
        for (const auto& entry : fs::directory_iterator(outputDataDir)) {
            fs::remove_all(entry);
        }
    } else {
        fs::create_directories(outputDataDir);
    }

    // 3. ˜˜?˜˜˜˜˜ Temp
    if (fs::exists(tempDir)) {
        for (const auto& entry : fs::directory_iterator(tempDir)) {
            fs::remove_all(entry);
        }
    } else {
        fs::create_directories(tempDir);
    }
}

bool SimulationEngine::initBuffers() {
    // ??˜˜˜???˜˜˜˜˜˜˜?˜

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
    // ˜?˜˜?˜?˜˜˜˜?˜
    if (!inputMMF.isOpen()) {
        std::cerr << "Failed to open file " << Config_INPUT_FILE_PATH << "\n";
        return false;
    }
    inputDataFileSize = inputMMF.size();

    timer.endSection("initBuffers_openfile");
    
    timer.startSection("initBuffers_createbuffer");
    // ?˜˜˜??˜˜˜˜˜˜?????˜˜˜˜˜˜˜˜?˜˜˜˜˜
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

// ?˜˜?˜˜˜˜?
// ˜˜˜?˜?0˜˜˜˜˜˜˜?˜?1~Config_PARALLED_COUNT
void SimulationEngine::simulataOneSlice(int slice_id, int threadId) {
    // ??˜˜˜??˜?
    if (threadId == 0) {
        timer.startSection("simulataOneSlice");
    }

    // ˜˜˜˜?˜˜???˜˜
    stateFreq[threadId].clear();

    if (threadId == 0) timer.startSection("simulataOneSlice_readinput");
    // ˜?˜˜˜˜˜˜˜˜˜˜?˜˜?˜??˜˜˜˜?˜˜˜˜˜˜
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
    //    // ˜˜˜ 1˜˜˜˜˜˜˜?˜?
    //    ifs.seekg(fileOffset, std::ios::beg);
    //    ifs.read(dst, bytes);
    //} else {
    //    // ˜˜˜ 2˜˜˜˜˜?˜?
    //    // ˜?˜˜˜˜?˜?
    //    ifs.seekg(fileOffset, std::ios::beg);
    //    ifs.read(dst, bytesToEnd);
//
    //    // ˜?˜˜?˜?˜˜?˜?˜˜
    //    ifs.seekg(0, std::ios::beg);
    //    ifs.read(dst + bytesToEnd, bytes - bytesToEnd);
    //}

    if (threadId == 0) timer.endSection("simulataOneSlice_readinput");

    // ˜˜??˜˜??Hash
    if (threadId == 0) timer.startSection("calculateStateHash_in_simulataOneSlice");
    SE_Interface_GetState(START_STATE_BUFFER);
    unsigned long long startStateHash = calculateStateHash(START_STATE_BUFFER, MODEL_STATE_DATA_LEN); // XXH3_64bits(startStateBuffers[threadId].data(), MODEL_STATE_DATA_LEN);
    if (threadId == 0) timer.endSection("calculateStateHash_in_simulataOneSlice");
    

    if (threadId == 0) timer.startSection("simulataOneSlice_executeslice");
    // ?˜˜?˜˜˜˜?
    for (int i = 0; i < Config_SLICE_STEP; i++) {
        SE_Interface_OneStep(
                             inputDataBufferPtrs[threadId] + i * MODEL_ONESTEP_INPUT_DATA_LEN,
                             outputDataBuffers[threadId][outBufferWriteIndex[threadId]].data() + i * MODEL_ONESTEP_OUTPUT_DATA_LEN);
        // ˜˜˜˜?˜˜??˜˜˜˜
        if (i % Config_STATE_SAMPLE_STEP == 0) {
            if (threadId == 0) timer.startSection("simulataOneSlice_executeslice_calculateStateHash");
            //if (i != 0) {
            SE_Interface_GetState(TEMP_STATE_BUFFER);
            //}
            unsigned long long curStateHash = calculateStateHash(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN); // XXH3_64bits(stateBuffers[threadId].data(), MODEL_STATE_DATA_LEN);
            stateFreq[threadId][curStateHash]++;
            
            // ?˜˜???˜˜˜˜˜˜˜?˜˜˜
            if(stateFreq[threadId][curStateHash] == 1) {
                hashStateMap[threadId][curStateHash] = vector<char>(TEMP_STATE_BUFFER, TEMP_STATE_BUFFER + MODEL_STATE_DATA_LEN);
            }
            if (threadId == 0) timer.endSection("simulataOneSlice_executeslice_calculateStateHash");
        }
    }
    if (threadId == 0) timer.endSection("simulataOneSlice_executeslice");

    if (threadId == 0) timer.startSection("getTopNStateHash_in_simulataOneSlice");
    // ˜˜??Config_STATE_TOP_N˜˜??˜˜Hash
    getTopNStateHash(threadId);
    if (threadId == 0) timer.endSection("getTopNStateHash_in_simulataOneSlice");

    if (threadId == 0) timer.startSection("writeSimulateResult_in_simulataOneSlice");
    // ?˜˜˜˜˜???˜˜˜˜˜
    writeSimulateResult(threadId, slice_id, startStateHash);
    if (threadId == 0) timer.endSection("writeSimulateResult_in_simulataOneSlice");
    
    // ??˜˜˜??˜?
    if (threadId == 0) {
        timer.endSection("simulataOneSlice");
    }
}

void SimulationEngine::getTopNStateHash(int threadId)
{
    auto cmp = [](const TopNStateHashItem& a, const TopNStateHashItem& b) {
        return a.count > b.count; // ?˜˜˜˜
    };

    // ?˜˜?Config_STATE_TOP_N˜˜??
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

// ?˜˜˜˜˜???˜˜˜˜˜ *** ˜˜˜˜˜˜?˜˜?˜˜ ***
void SimulationEngine::writeSimulateResult(int threadId, int slice_id, unsigned long long startStateHash)
{
    
    if (threadId == 0) {
        // ?˜˜?˜˜˜˜˜??˜˜˜˜˜˜˜˜
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
        // ˜˜˜??˜˜˜˜˜˜˜˜?˜˜˜˜?˜?˜
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
        //         stateFile.write(START_STATE_BUFFER, len); // offset˜˜˜?˜˜˜
        //         stateFile.close();
        //         if (!FLAG_DONOT_WRITE_OUTPUT) {
        //             std::ofstream outFile("SimOut/Temp/" + fileName + "_Output.bin", std::ios::binary);
        //             outFile.write(outputDataBuffers[threadId][outBufferWriteIndex[threadId]].data(), Config_OUTBUFFER_SIZE); // offset˜˜˜?˜˜˜
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
    int index,                          // ˜??˜˜
    std::vector<std::unique_ptr<SimulationEngine::Worker>>* workers,   // ˜˜˜˜ Worker ˜˜˜˜
    SimulationEngine* se                // ?˜˜˜˜˜˜˜˜˜?˜˜
) {
    // ˜˜?˜˜˜˜˜??˜ SE ˜?˜
    SE_Interface_Init();
    if (FLAG_PRINT) {
        cout << "Worker " << index << " initialized\n";
    }
    //// ˜˜˜˜?˜˜˜?˜?˜?˜?˜˜˜˜˜˜?˜˜?˜
    //if (!inputFiles[index]) {
    //    std::cerr << "Worker " << index
    //              << " failed to open file " << Config_INPUT_FILE_PATH << "\n";
    //    return;
    //}

    // ===== 2. ˜˜˜?˜?˜-?˜?˜?˜˜ =====
    while (true) {
        SimulationEngine::TaskParam local;  // ˜˜˜?˜˜˜˜˜˜˜˜˜?˜˜˜?˜˜˜˜

        {
            // ˜˜˜˜˜˜?˜˜˜˜˜??
            std::unique_lock<std::mutex> lk((*workers)[index-1]->m);

            // ˜?˜˜˜˜??˜˜˜˜˜˜˜˜˜
            (*workers)[index-1]->cv.wait(lk, [&] {
                return (*workers)[index-1]->has_task ||
                       (*workers)[index-1]->stop;
            });

            // ˜˜˜˜˜˜?˜?˜˜˜?˜
            if ((*workers)[index-1]->stop) {
                break;
            }
            local = (*workers)[index-1]->param;
            // ˜˜˜˜˜˜?˜˜?˜˜˜˜
            local.slice_id = (*workers)[index-1]->param.slice_id;
            SE_Interface_SetState((*workers)[index-1]->param.state.data());

            // ˜˜˜˜˜˜˜˜?˜˜˜˜?˜˜˜˜˜˜?˜˜
            (*workers)[index-1]->has_task = false;
        } // ˜˜˜˜˜?˜˜˜

        unsigned long long localStateHash = se->calculateStateHash(local.state.data(), MODEL_STATE_DATA_LEN); // XXH3_64bits(local.state.data(), MODEL_STATE_DATA_LEN);
        // cout << "Worker " << index << " start slice " << local.slice_id << " with state hash " << std::hex << localStateHash << std::dec << endl;

        // ===== 3. ?˜˜?˜˜?˜˜?˜Å˜˜˜ =====

        //// ˜˜?˜˜?˜˜˜?˜?˜˜
        //const uint64_t bytesPerSlice = static_cast<uint64_t>(Config_SLICE_STEP) * MODEL_ONESTEP_INPUT_DATA_LEN;
        //uint64_t fileOffset = (static_cast<uint64_t>(local.slice_id) * bytesPerSlice) % inputDataFileSize;
        //const char* inputPtr = inputMMF.base() + fileOffset;
        //inputDataBufferPtrs[index] = inputPtr;
        
        //size_t offset = local.slice_id * Config_SLICE_STEP * MODEL_ONESTEP_INPUT_DATA_LEN;
        //inputFiles[index].seekg(offset, std::ios::beg);
        //
        //// ˜˜?˜˜˜˜
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

    // ˜?˜˜?˜˜˜˜?˜˜˜?˜?˜˜˜˜?˜˜?˜˜˜0000000XXX_State_OutputAndState.bin˜˜
    // ?˜˜˜˜?˜˜˜˜?˜˜˜˜?˜˜˜˜˜??˜˜0000000XXX_State(16˜˜˜?˜Hash?)_OutputAndState.bin˜˜˜˜XXX?˜˜?ID
    // ˜?˜˜˜?MODEL_STATE_DATA_LEN˜˜˜?˜???˜˜˜?˜
    // ?˜˜˜?˜??˜µ˜˜˜˜˜˜˜˜˜˜˜?˜˜˜˜˜˜˜??˜˜˜?Config_OUTBUFFER_SIZE = Config_SLICE_STEP * MODEL_ONESTEP_OUTPUT_DATA_LEN
    // ?˜˜?˜˜˜˜˜˜˜?˜˜˜??˜˜˜?˜??˜˜˜??˜˜˜?MODEL_STATE_DATA_LEN˜˜˜?˜
    // ˜˜?˜˜˜˜˜˜˜˜?N˜˜??˜˜?˜˜??˜˜˜??˜˜˜?MODEL_STATE_DATA_LEN˜˜˜??˜˜˜Config_STATE_TOP_N˜˜??˜˜˜˜

    SE_Interface_GetState(TEMP_STATE_BUFFER);
    unsigned long long stateHash = calculateStateHash(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN); // XXH3_64bits(stateBuffers[0].data(), MODEL_STATE_DATA_LEN);
    std::stringstream ss;

    // 16˜˜˜?˜stateHash
    ss << std::setw(9) << std::setfill('0') << current_slice_id;
    string sliceIdStr = ss.str();
    ss << "_" << std::hex << stateHash;
    string filename = ss.str();

    //// ˜??˜˜?˜˜???˜˜?˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜?˜˜?
    //std::ifstream file("SimOut/Temp/" + filename + "_State.bin", std::ios::binary);
    //if (!file) {
    //    return false;
    //}


    bool res = stateStore.take("SimOut/Temp/" + filename + "_State.bin", stateBuffers[threadId]);
    if (!res) {
        return false;
    }

    //// ˜˜˜??˜˜˜˜˜˜??N˜˜˜??˜˜?˜˜?˜˜˜˜˜?˜˜??
    //file.read(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN);
    bool isSame = SE_Interface_CompareState(START_STATE_BUFFER);
    if (!isSame) {
        //file.close();
        return false;
    }
    
    // ˜?˜˜˜˜˜˜˜?˜˜˜˜˜˜?˜˜˜˜??
    if (FLAG_WRITE_OUTPUT) {
        copyTempSimulateResultList.emplace_back(filename + "_Output.bin", sliceIdStr + ".bin");

        {
            std::lock_guard<std::mutex> lk(ioMutex);
            needWriteSliceIds.insert(current_slice_id);
            needWriteResultFileNames.insert("SimOut/Temp/" + filename + "_Output.bin");
        }
        //asyncCopyTempSimulateResult(filename + "_Output.bin", sliceIdStr + ".bin");
    }

    //// ˜˜˜˜˜˜MODEL_STATE_DATA_LEN˜˜˜??˜?˜˜Slice˜˜˜˜˜˜??˜˜˜˜˜˜˜?˜???
    //file.read(TEMP_STATE_BUFFER, MODEL_STATE_DATA_LEN);
    SE_Interface_SetState(FINAL_STATE_BUFFER);

    // ˜˜?˜?˜?˜˜TopN˜˜??
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
    
    // ?˜˜˜˜˜˜˜˜?˜˜?˜˜?˜˜˜˜?˜˜˜˜?
    if (FLAG_PRINT) {
        cout << "Jump to slice " << current_slice_id << " with state hash " << std::hex << stateHash << std::dec << endl;
    }
    
    current_slice_id++;
    jumpCount++;
    return true;
}


// ˜?˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜?˜˜˜˜??
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



    //// ?˜˜std::async˜??˜˜˜?˜˜˜˜˜˜˜˜˜
    //std::async(std::launch::async, [=]() {
    //    try {
    //        // ?src˜˜dst˜˜˜˜˜˜˜˜·˜˜
    //        string fullSrcPath = "SimOut/Temp/" + src;
    //        string fullDstPath = "SimOut/OutputData/" + dst;
    //        
    //        // ?˜?˜˜˜˜˜˜˜˜?˜˜˜˜˜˜ü˜˜?˜˜˜
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

            // ˜?˜parallelSliceId˜˜˜?˜?˜?˜TopNStateHash˜˜˜˜˜˜
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
                // ?˜˜˜˜˜˜˜˜˜
                std::lock_guard<std::mutex> lk(workers[taskScheduled]->m);
                workers[taskScheduled]->param = p;
                workers[taskScheduled]->has_task = true;
            }
            // ˜˜˜˜?˜˜˜?˜
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
    
    // ˜˜˜˜˜˜??˜˜˜simulataOneSlice˜˜?˜?˜˜
    timer.printStatistics();
    
    clock_t end_time = clock();
    double time_cost = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Simulation Time cost: " << time_cost << " seconds" << std::endl;

    std::cout << "Jump Count: " << jumpCount << " Total Slice Count: " << total_slice_count << " Jump Rate: " << (double)jumpCount / total_slice_count * 100 << "%" <<std::endl;
    
    inputMMF.close();
    // for (int i = 0; i < Config_PARALLED_COUNT + 1; ++i) {
    //     inputFiles[i].close();
    // }

    // ===== ??˜˜˜˜˜?˜˜?˜ =====
    for (int i = 0; i < Config_PARALLED_COUNT; ++i) {
        {
            std::lock_guard<std::mutex> lk(workers[i]->m);
            workers[i]->stop = true;
        }
        workers[i]->cv.notify_one();
    }

    // ===== ˜?˜˜˜˜˜˜??˜˜˜ =====
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
    //// ?˜˜˜˜state˜˜?˜˜˜˜˜?˜˜˜?hash?
    //unsigned long long hash = 0;
    //for (int i = 0; i < 3; ++i) {
    //    hash = hash * 256 + (unsigned char)state[i];
    //}
    unsigned long long hash = XXH3_64bits(state, len);
    return hash;
}