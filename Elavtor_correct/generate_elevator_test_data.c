#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 使用与模型相同的数据类型定义
typedef double real_T;

#define TOTAL_STEPS 1000000000  // 1亿步
#define MAX_FLOOR 10         // 假设最大楼层为100
#define MIN_FLOOR 1           // 假设最小楼层为1

int main() {
    FILE *file = NULL;
    real_T *test_data = NULL;
    long i;
    
    printf("开始生成电梯模型测试用例...\n");
    printf("目标步数: %ld\n", TOTAL_STEPS);
    
    // 为了提高性能，先分配一块内存批量生成数据
    // 由于5000万步的数据量较大，一次分配可能会导致内存不足
    // 因此我们采用分批生成的方式
    
    // 每批处理的步数
    long batch_size = 1000000;  // 每批100万步
    long total_batches = TOTAL_STEPS / batch_size;
    long remaining_steps = TOTAL_STEPS % batch_size;
    
    // 分配批处理内存
    test_data = (real_T *)malloc(batch_size * sizeof(real_T));
    if (test_data == NULL) {
        printf("内存分配失败！\n");
        return 1;
    }
    
    // 以二进制写入模式打开文件
    file = fopen("test_data.bin", "wb");
    if (file == NULL) {
        printf("无法创建测试数据文件！\n");
        free(test_data);
        return 1;
    }
    
    // 初始化随机数生成器
    srand((unsigned int)time(NULL));
    
    // 分批生成并写入数据
    for (long batch = 0; batch < total_batches; batch++) {
        printf("生成批次 %ld/%ld...\n", batch + 1, total_batches + (remaining_steps > 0 ? 1 : 0));
        
        // 生成当前批次的随机楼层数据
        for (i = 0; i < batch_size; i++) {
            // 生成随机楼层 (MIN_FLOOR 到 MAX_FLOOR)
            test_data[i] = (real_T)(MIN_FLOOR + rand() % (MAX_FLOOR - MIN_FLOOR + 1));
        }
        
        // 将当前批次数据写入文件
        if (fwrite(test_data, sizeof(real_T), batch_size, file) != batch_size) {
            printf("写入数据失败！\n");
            fclose(file);
            free(test_data);
            return 1;
        }
    }
    
    // 处理剩余的步数
    if (remaining_steps > 0) {
        printf("生成最后一批数据...\n");
        
        // 生成剩余的随机楼层数据
        for (i = 0; i < remaining_steps; i++) {
            test_data[i] = (real_T)(MIN_FLOOR + rand() % (MAX_FLOOR - MIN_FLOOR + 1));
        }
        
        // 将剩余数据写入文件
        if (fwrite(test_data, sizeof(real_T), remaining_steps, file) != remaining_steps) {
            printf("写入剩余数据失败！\n");
            fclose(file);
            free(test_data);
            return 1;
        }
    }
    
    // 清理资源
    free(test_data);
    fclose(file);
    
    printf("测试用例生成完成！\n");
    printf("生成的文件: elevator_test_data.bin\n");
    printf("总步数: %ld\n", TOTAL_STEPS);
    printf("文件大小: %ld bytes\n", TOTAL_STEPS * sizeof(real_T));
    
    return 0;
}