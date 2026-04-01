#ifndef _DEFINE_H_
#define _DEFINE_H_
#include <string.h>
#include <string>
#include "FirstPress.h"

// 常量定义
#define EXAMPLE_STEP 10000
#define BUFFER_SIZE (EXAMPLE_STEP * 32 * (sizeof(boolean_T)*4))  // 15个输出，每个为real32_T类型
#define DATA_DIR "DataOutPut"
#define FINAL_STATE_DIR "FinalState"

// 函数声明 - 数据管理模块
void create_data_dir();

// 双缓冲区相关函数
void init_buffers();
void free_buffers();
void write_disk(int buf_index);
void write_buffers(const void *data, size_t data_size);
void write_remain_data();

#endif
