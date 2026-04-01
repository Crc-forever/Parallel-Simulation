#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_STEPS 100000000

//操作码定义 
#define OP_REGISTER 10001
#define OP_QUERY    10004
#define OP_UPGRADE  10016
#define OP_UPGRADE2 10032
#define OP_DELETE   10008

typedef struct {
    int32_t ArmId;
    int32_t Op;
    int32_t P1;
    int32_t P2;
    int32_t P3;
} TestVector;

//从 10  20 中选一个 
static int32_t pick_arm_id(void)
{
    return (rand() % 2) ? 10 : 20;
}

int main(void)
{
    FILE *fp;
    TestVector tv;
    int step;

    srand((unsigned int)time(NULL));

    fp = fopen("test_data.bin", "wb");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    for (step = 1; step <= TOTAL_STEPS; step++) {

        tv.ArmId = pick_arm_id();
        tv.P1 = 0;
        tv.P2 = 0;
        tv.P3 = 0;

        //每 1000 步：注册或删除 
        if (step % 1000 == 0) {
            if (rand() % 2) {
                tv.Op = OP_REGISTER;
            } else {
                tv.Op = OP_DELETE;
            }
        }
        //前 100 步允许升级，20% 概率 
        else if (step <= 100 && (rand() % 100) < 20) {
            if (rand() % 2) {
                tv.Op = OP_UPGRADE;
                tv.P1 = 3;    //对应 3  4  5 的升级路径 
            } else {
                tv.Op = OP_UPGRADE2;
                tv.P1 = 6;    //对应 6  7  8 的升级路径 
            }
        }
        //其余时间：查询 
        else {
            tv.Op = OP_QUERY;
        }

        fwrite(&tv, sizeof(TestVector), 1, fp);
    }

    fclose(fp);

    printf("Binary test data generated\n");
    printf("Total steps %d\n", TOTAL_STEPS);

    return 0;
}
