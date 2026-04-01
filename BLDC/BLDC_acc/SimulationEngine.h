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
// extern const int Config_OUTBUFFER_COUNT = 20; //ֱ��ÿ����Ƭ���һ��������
extern int Config_OUTBUFFER_SIZE; //Config_SLICE_STEP * ONESTEP_INPUT_DATA_LEN;
extern int Config_STATE_SAMPLE_STEP;  // ÿxx������һ��״̬
extern int Config_STATE_TOP_N;           // ȡǰxx��״̬
extern int Config_PARALLEL_SLICE_DELAY;  // ����ִ�е���ƬҪ�����̵߳Ķ��ٸ���Ƭ֮��
extern int Config_PARALLED_COUNT;        // �����̲߳��е��߳���
extern string Config_INPUT_FILE_PATH;   // �����ļ�·��

class SimulationEngine {
public:
    SimulationEngine();
    ~SimulationEngine();
    

    // ��ʾ����ʱ��Ƭ���߳�Ҫִ�е����������
    struct TaskParam {
        int task_id;        // ������
        int slice_id;       // ��ƬId
        vector<char> state; // ִ�и���Ƭ�ĳ�ʼ״̬����
    };

    struct Worker {
        std::mutex m;                   // �����������й���״̬
        std::condition_variable cv;      // ���ڻ��Ѹ��߳�
        bool has_task = false;           // �Ƿ���������
        bool stop = false;               // �Ƿ���Ҫ�˳��߳�
        TaskParam param;                 // ��ǰʱ��Ƭ���������
    };

    struct TopNStateHashItem {
        unsigned long long hash;
        int count;
    };

    clock_t start_time = 0;
    Timer timer;  // ȫ�ּ�ʱ��

    int total_slice_count = 0;
    int current_slice_id = 0;

    int jumpCount = 0; // ��������Ƭ����

    std::vector<std::unique_ptr<Worker>> workers;
    std::vector<std::thread> threads;


    vector<pair<string, string>> copyTempSimulateResultList; // ����ִ�е��߳�Ҫ���Ƶ���ʱ����ļ���

    // IO�̳߳�д�ļ����߼��ǣ�
    // �����ƬId��passedWriteSliceIds��,������
    // ���Ҫд�����ƬId��needWriteSliceIds�����ļ�������needWriteResultFileNames��,������

    // ����������ر���
    int taskCount = 0; // �ѷ������������
    vector<unordered_map<unsigned long long, bool>> executedStateHashMap; // ��ͬ��Ƭ��ִ�й���״̬ͳ�� [i]��ʾ��Ƭi, ��¼״̬��ϣֵ�Ƿ���ֹ�

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
