#ifndef _DEFINE_H_
#define _DEFINE_H_
#include <string.h>
#include <string>
#include "Pacemaker_Correct.h"

// 常量定义
#define EXAMPLE_STEP 1000000
#define BUFFER_SIZE (EXAMPLE_STEP * 15 * sizeof(real_T))  // 15个输出，每个为real_T类型
#define DATA_DIR "DataOutPut"
#define FINAL_STATE_DIR "FinalState"

// 函数声明 - 数据管理模块
void create_data_dir();

// 双缓冲区相关函数
void init_buffers();
void free_buffers();
void write_disk(int buf_index);
void write_buffers(real_T data, size_t data_size);
void write_remain_data();

#endif