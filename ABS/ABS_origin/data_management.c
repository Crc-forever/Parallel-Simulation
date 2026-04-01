#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <direct.h>
#include <errno.h>
#include <string.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <deque>
using namespace std;
#define BUFFER_NUM 100
uint8_T *buffers[BUFFER_NUM];
int active_buf = 0; 
size_t buf_pos[BUFFER_NUM];
mutex buf_mutex[BUFFER_NUM];
atomic<int> fileindex = 0;
mutex state_mutex;
condition_variable cv_pending;
condition_variable cv_free;
deque<int> pending_queue;
deque<int> free_queue;
thread writer_thread;
bool writer_running = false;
bool stop_writer = false;

void write_disk(int buf_index);

void create_data_dir() {
    if (_mkdir(DATA_DIR) == -1) {
        if (errno == EEXIST) {
            DWORD attrs = GetFileAttributesA(DATA_DIR);
            if (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY)) {
                return;
            }
        }
        printf("创建目录失败，errno:%d，winerr:%lu\n", errno, GetLastError());
        system("pause");
        exit(1);
    }
}


// 初始化双缓冲区
void init_buffers(){
    for(int i = 0; i< BUFFER_NUM; i++){
        buffers[i] = (uint8_T *)malloc(BUFFER_SIZE);
        if(buffers[i] == NULL){
            printf("缓冲区初始化失败\n");
            system("pause");
            exit(1);
        }
        memset(buffers[i] , 0 , BUFFER_SIZE);
        buf_pos[i] = 0;
    }
    {
        lock_guard<mutex> lock(state_mutex);
        pending_queue.clear();
        free_queue.clear();
        active_buf = 0;
        for (int i = 1; i < BUFFER_NUM; ++i) {
            free_queue.push_back(i);
        }
        stop_writer = false;
        writer_running = true;
    }
    writer_thread = thread([](){
        while (true) {
            int buf_index = -1;
            {
                unique_lock<mutex> lock(state_mutex);
                cv_pending.wait(lock, [] { return stop_writer || !pending_queue.empty(); });
                if (pending_queue.empty()) {
                    if (stop_writer) break;
                    continue;
                }
                buf_index = pending_queue.front();
                pending_queue.pop_front();
            }
            write_disk(buf_index);
            {
                lock_guard<mutex> lock(state_mutex);
                free_queue.push_back(buf_index);
            }
            cv_free.notify_one();
        }
    });
}

void free_buffers(){
    if (writer_thread.joinable()) {
        {
            lock_guard<mutex> lock(state_mutex);
            stop_writer = true;
        }
        cv_pending.notify_all();
        writer_thread.join();
    }
    {
        lock_guard<mutex> lock(state_mutex);
        writer_running = false;
        pending_queue.clear();
        free_queue.clear();
    }
    for(int i = 0; i< BUFFER_NUM; i++){
        if(buffers[i] != NULL)free(buffers[i]);
    }
}

// 将缓冲区数据写入磁盘（由工作线程执行）
void write_disk(int buf_index) {
    lock_guard<mutex> lock(buf_mutex[buf_index]);
    if (buf_pos[buf_index] == 0) return;
    int current_fileindex = fileindex.fetch_add(1);
    char filename[100];
    sprintf(filename, "%s\\%09d.bin", DATA_DIR, current_fileindex);
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("文件%s打开失败\n", filename);
        return;
    }
    fwrite(buffers[buf_index], 1, buf_pos[buf_index], file);
    buf_pos[buf_index] = 0;
    fclose(file);
}

// 写入数据到活动缓冲区，如果缓冲区满则切换并启动异步写入
void write_buffers(const void *data, size_t data_size) {
    if (data == NULL || data_size == 0) return;
    const uint8_T *src = (const uint8_T *)data;
    size_t remain = data_size;
    while (remain > 0) {
        unique_lock<mutex> state_lock(state_mutex);
        size_t space = BUFFER_SIZE - buf_pos[active_buf];
        if (space == 0) {
            int flush_buf = active_buf;
            pending_queue.push_back(flush_buf);
            cv_pending.notify_one();
            while (free_queue.empty()) {
                cv_free.wait(state_lock);
            }
            active_buf = free_queue.front();
            free_queue.pop_front();
            space = BUFFER_SIZE;
        }
        size_t chunk = (remain < space) ? remain : space;
        lock_guard<mutex> lock(buf_mutex[active_buf]);
        memcpy(buffers[active_buf] + buf_pos[active_buf], src, chunk);
        buf_pos[active_buf] += chunk;
        src += chunk;
        remain -= chunk;
    }
}

// 写入剩余数据
void write_remain_data() {
    {
        unique_lock<mutex> lock(state_mutex);
        if (buf_pos[active_buf] > 0) {
            pending_queue.push_back(active_buf);
            cv_pending.notify_one();
            while (free_queue.empty() && !pending_queue.empty()) {
                cv_free.wait(lock);
            }
        }
        stop_writer = true;
    }
    cv_pending.notify_all();
    if (writer_thread.joinable()) {
        writer_thread.join();
    }
    {
        lock_guard<mutex> lock(state_mutex);
        writer_running = false;
        pending_queue.clear();
        free_queue.clear();
    }
}
