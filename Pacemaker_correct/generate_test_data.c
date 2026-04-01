#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define TOTAL_STEPS 100000000  // 总步数
#define BLOCK_SIZE 1000000     // 每次写入的块大小（步）
#define PAIR_SIZE sizeof(real_T) * 2  // 每对数据的大小（16字节）
#define BUFFER_SIZE BLOCK_SIZE * PAIR_SIZE  // 缓冲区大小

typedef double real_T;
int main() {
    FILE *fp;
    real_T *buffer;
    size_t steps_written = 0;
    size_t bytes_written;
    clock_t start, end;
    double cpu_time_used;
    
    // 分配缓冲区
    buffer = (real_T *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        fprintf(stderr, "无法分配内存\n");
        return 1;
    }
    
    // 打开文件
    fp = fopen("test_data.bin", "wb");
    if (fp == NULL) {
        fprintf(stderr, "无法打开文件\n");
        free(buffer);
        return 1;
    }
    
    // 初始化随机数生成器
    srand(time(NULL));
    
    printf("开始生成测试数据...\n");
    start = clock();
    
    // 分块生成和写入数据
    while (steps_written < TOTAL_STEPS) {
        size_t current_block_size = (steps_written + BLOCK_SIZE <= TOTAL_STEPS) ? 
                                    BLOCK_SIZE : (TOTAL_STEPS - steps_written);
        
        // 填充缓冲区
        for (size_t i = 0; i < current_block_size * 2; i += 2) {
            // 生成第一个real_T数据（VENT_Amplitude）：范围0-5.0
            buffer[i] = (real_T)(rand() % 5000) / 1000.0;
            
            // 生成第二个real_T数据（Mode）：范围0, 1, 2, 3
            buffer[i + 1] = (real_T)(rand() % 4);
        }
        
        // 写入文件
        bytes_written = fwrite(buffer, PAIR_SIZE, current_block_size, fp);
        
        if (bytes_written != current_block_size) {
            fprintf(stderr, "写入文件失败\n");
            fclose(fp);
            free(buffer);
            return 1;
        }
        
        steps_written += current_block_size;
        printf("已生成 %.2f%%\r", (double)steps_written / TOTAL_STEPS * 100);
        fflush(stdout);
    }
    
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    // 关闭文件和释放内存
    fclose(fp);
    free(buffer);
    
    printf("\n测试数据生成完成！\n");
    printf("总步数: %zu\n", TOTAL_STEPS);
    printf("预计文件大小: %.2f MB\n", (double)(TOTAL_STEPS * PAIR_SIZE) / (1024 * 1024));
    printf("生成时间: %.2f 秒\n", cpu_time_used);
    
    return 0;
}