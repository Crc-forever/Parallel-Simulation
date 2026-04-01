#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <atomic>
#include "Timer.h"
#include <unordered_set>

#include "ModelData.h"



using namespace std;

extern const int MODEL_ONESTEP_INPUT_DATA_LEN;  // 3 * sizeof(real_T)
extern const int MODEL_STATE_DATA_LEN;  // 3 * sizeof(uint8_T)

extern int Config_TOTAL_STEP;
extern int Config_SLICE_STEP;
// extern const int Config_OUTBUFFER_COUNT = 20; //直接每个切片输出一个缓冲区
extern int Config_OUTBUFFER_SIZE; //Config_SLICE_STEP * ONESTEP_INPUT_DATA_LEN;
extern int Config_STATE_SAMPLE_STEP;  // 每xx步采样一次状态
extern int Config_STATE_TOP_N;           // 取前xx个状态
extern int Config_PARALLEL_SLICE_DELAY;  // 并行执行的切片要在主线程的多少个切片之后
extern int Config_PARALLED_COUNT;        // 与主线程并行的线程数
extern string Config_INPUT_FILE_PATH;   // 输入文件路径

class SimulationEngine {
public:
    SimulationEngine();
    ~SimulationEngine();
    

    // 表示“本时间片该线程要执行的任务参数”
    struct TaskParam {
        int task_id;        // 任务编号
        int slice_id;       // 切片Id
        vector<char> state; // 执行该切片的初始状态数据
    };

    struct Worker {
        std::mutex m;                   // 保护下面所有共享状态
        std::condition_variable cv;      // 用于唤醒该线程
        bool has_task = false;           // 是否有新任务
        bool stop = false;               // 是否需要退出线程
        TaskParam param;                 // 当前时间片的任务参数
    };

    struct TopNStateHashItem {
        unsigned long long hash;
        int count;
    };

    clock_t start_time = 0;
    Timer timer;  // 全局计时器

    int total_slice_count = 0;
    int current_slice_id = 0;

    int jumpCount = 0; // 跳过的切片数量

    std::vector<std::unique_ptr<Worker>> workers;
    std::vector<std::thread> threads;


    vector<pair<string, string>> copyTempSimulateResultList; // 并行执行的线程要复制的临时结果文件名

    // IO线程池写文件的逻辑是：
    // 如果切片Id在passedWriteSliceIds中,则跳过
    // 如果要写入的切片Id在needWriteSliceIds，且文件名不在needWriteResultFileNames中,则跳过

    // 并行任务相关变量
    int taskCount = 0; // 已分配的任务数量
    vector<unordered_map<unsigned long long, bool>> executedStateHashMap; // 不同切片上执行过的状态统计 [i]表示切片i, 记录状态哈希值是否出现过

    void init(int argc, const char *argv[]);
    bool initParseArg(int argc, const char *argv[]);
    void initCreateDirs();
    bool initBuffers();

    void start();

    void simulataOneSlice(int slice_id, int threadId);
    void getTopNStateHash(int threadId);
    void writeSimulateResult(int threadId, int slice_id, unsigned long long startStateHash);

    bool tryJumpNextSlice();

    void asyncMoveTempSimulateResult(string src, string dst);

    void scheduleParallelTask();

    void finish();

    unsigned long long calculateStateHash(char* state, int len);
};

void SE_Interface_Init();
void SE_Interface_OneStep(const char* input_buf, const char* output_buf);
unsigned long long SE_Interface_CalculateStateHash();
bool SE_Interface_CompareState(char* state);
void SE_Interface_GetState(char* state_buf);
void SE_Interface_SetState(char* state_buf);
