#ifndef _DEFINE_H_
#define _DEFINE_H_
#include <string.h>
#include <string>
#include "CPUTask.h"

// 常量定义
#define example_step 1000000
#define BUFFER_SIZE (example_step * 2 * sizeof(int32_T))  // 2个输出，每个为int32_T类型
#define BUFFER_SIZE_INPUT (example_step * 3 * sizeof(int32_T))
#define DATA_DIR "DataOutPut"
#define FINAL_STATE_DIR "FinalState"

// 函数声明 - 数据管理模块
void create_data_dir();

// 双缓冲区相关函数
void init_buffers();
void free_buffers();
void write_disk(int buf_index);
void write_buffers(int32_T data, size_t data_size);
void write_remain_data();

#endif