#include "define.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <direct.h>
#include <string.h>
#include <thread>
#include <mutex>
using namespace std;
#define BUFFER_NUM 50
uint8_T *buffers[BUFFER_NUM];
int active_buf = 0; 
size_t buf_pos[BUFFER_NUM];
mutex buf_mutex[BUFFER_NUM];
int fileindex = 0;

void create_data_dir() {
    if (_mkdir(DATA_DIR) == -1) {
        DWORD error = GetLastError();
        if (error != ERROR_ALREADY_EXISTS) {
            printf("创建目录失败，错误码:%d\n", error);
            system("pause");
            exit(1);
        }
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
}

void free_buffers(){
    for(int i = 0; i< BUFFER_NUM; i++){
        if(buffers[i] != NULL)free(buffers[i]);
    }
}

// 将缓冲区数据写入磁盘（由工作线程执行）
void write_disk(int buf_index) {
    
    char filename[100];
    sprintf(filename, "%s\\%09d.bin", DATA_DIR, fileindex);
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("文件%s打开失败\n", filename);
        return;
    }
    {
        lock_guard<mutex> lock(buf_mutex[buf_index]);
        fwrite(buffers[buf_index], 1, buf_pos[buf_index], file);
        buf_pos[buf_index] = 0;
    }
    fclose(file);
    fileindex++;
}

// 写入数据到活动缓冲区，如果缓冲区满则切换并启动异步写入
void write_buffers(const void *data, size_t data_size) {
    if (data == NULL || data_size == 0) return;
    if (buf_pos[active_buf] + data_size > BUFFER_SIZE) {
        // 启动新线程将当前缓冲区写入磁盘
        //Sleep(100);
        thread myThread(write_disk, active_buf);
        if (myThread.joinable()) {
            myThread.detach();  // 分离线程，让其在后台自行完成
        }
        // 切换活动缓冲区
        active_buf = (active_buf + 1) % BUFFER_NUM;
    }
    // 将数据复制到当前活动缓冲区
    {
        lock_guard<mutex> lock(buf_mutex[active_buf]);
        memcpy(buffers[active_buf] + buf_pos[active_buf], data, data_size);
    }
    
    buf_pos[active_buf] += data_size;
}

// 写入剩余数据
void write_remain_data() {
    if (buf_pos[active_buf] > 0) {
        write_disk(active_buf);
    }
}
