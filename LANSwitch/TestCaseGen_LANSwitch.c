#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef int32_t int32_T;

/* 测试向量结构 */
typedef struct {
    int32_T PortId;
    int32_T CMD;
    int32_T Arg1;
    int32_T Arg2;
    int32_T Arg3;
} TestVector;

/* CMD 定义 */
#define CMD_ADD     10001
#define CMD_COMM    10002
#define CMD_QUERY   10003
#define CMD_REMOVE  10004

#define TOTAL_STEPS 100000000
#define CHANGE_INTERVAL 500

int main(void)
{
    FILE *fp = fopen("test_data.bin", "wb");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    srand((unsigned int)time(NULL));

    int has10 = 0;
    int has20 = 0;

    for (int step = 1; step <= TOTAL_STEPS; step++) {
        TestVector tv = {0};

        /* 每 500 步：状态改变 */
        if (step % CHANGE_INTERVAL == 0) {
            /* 优先补齐端口，其次删除 */
            if (!has10) {
                tv.PortId = 10;
                tv.CMD = CMD_ADD;
                has10 = 1;
            } else if (!has20) {
                tv.PortId = 20;
                tv.CMD = CMD_ADD;
                has20 = 1;
            } else {
                /* 两个都有了，随机删一个 */
                if (rand() % 2 == 0) {
                    tv.PortId = 10;
                    has10 = 0;
                } else {
                    tv.PortId = 20;
                    has20 = 0;
                }
                tv.CMD = CMD_REMOVE;
            }

            tv.Arg1 = tv.Arg2 = tv.Arg3 = 0;
        }
        /* 其余步骤：查询或通信 */
        else {
            int both_exist = has10 && has20;
            int do_comm = rand() % 2;

            /* 随机选一个已存在或固定端口 */
            if (has10 && has20)
                tv.PortId = (rand() % 2) ? 10 : 20;
            else if (has10)
                tv.PortId = 10;
            else if (has20)
                tv.PortId = 20;
            else
                tv.PortId = 10;  /* 尚无端口，制造异常 */

            if (do_comm) {
                tv.CMD = CMD_COMM;

                if (both_exist && (rand() % 10 == 0)) {
                    /* 10% 通信失败 */
                    tv.Arg1 = 999;   /* 不存在的端口 */
                    tv.Arg2 = 0;
                    tv.Arg3 = 0;
                } else {
                    /* 正常通信 */
                    tv.Arg1 = (tv.PortId == 10) ? 20 : 10;
                    tv.Arg2 = rand() % 10;
                    tv.Arg3 = tv.Arg2 + (rand() % 3 + 1);
                }
            } else {
                tv.CMD = CMD_QUERY;
                tv.Arg1 = tv.Arg2 = tv.Arg3 = 0;
            }
        }

        fwrite(&tv, sizeof(TestVector), 1, fp);
    }

    fclose(fp);
    return 0;
}
