#include <stddef.h>
#include <stdio.h>
#include "ABS.h"
#include <time.h>
#include <windows.h>
#include "define.h"

static RT_MODEL rtM_;
static RT_MODEL *const rtMPtr = &rtM_;
static int32_T rtU_Speed[32];
static int32_T rtU_FilterValue[32];
static int16_T rtU_Acc[32];
static int16_T rtU_P_i[32];
static int32_T rtU_Q[32];
static int32_T rtU_H[32];
static int32_T rtU_R[32];
static int32_T rtY_P_Update[32];
static int32_T rtY_Out1[32];
static int32_T rtY_Filter_Update[32];
static real32_T rtY_normalize_value[32];
void rt_OneStep(RT_MODEL *const rtM);
void rt_OneStep(RT_MODEL *const rtM)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }

  OverrunFlag = true;
  ABS_step(rtM, rtU_Speed, rtU_FilterValue, rtU_Acc, rtU_P_i, rtU_Q, rtU_H,
           rtU_R, rtY_P_Update, rtY_Out1, rtY_Filter_Update, rtY_normalize_value);
  OverrunFlag = false;
}

int TOTAL_STEP = 500000;
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL *const rtM = rtMPtr;
  
  ABS_initialize(rtM, rtU_Speed, rtU_FilterValue, rtU_Acc, rtU_P_i, rtU_Q, rtU_H,
                 rtU_R, rtY_P_Update, rtY_Out1, rtY_Filter_Update,
                 rtY_normalize_value);
  if (argc > 1) {
        TOTAL_STEP = atoi(argv[1]);
  }
  printf("Step: %d\n", TOTAL_STEP);
  clock_t start = clock();

  create_data_dir();
  init_buffers();

  FILE *file = fopen("../test_data.bin", "rb");
  if (file == NULL) {
      perror("we cannot open the test data file");
      return 1;
  }
  for(int i = 0; i < TOTAL_STEP; i++){
    fread(rtU_Speed, sizeof(int32_T), 32, file);
    fread(rtU_FilterValue, sizeof(int32_T), 32, file);
    fread(rtU_Acc, sizeof(int16_T), 32, file);
    fread(rtU_P_i, sizeof(int16_T), 32, file);
    fread(rtU_Q, sizeof(int32_T), 32, file);
    fread(rtU_H, sizeof(int32_T), 32, file);
    fread(rtU_R, sizeof(int32_T), 32, file);
    rt_OneStep(rtM);
    write_buffers(rtY_P_Update, sizeof(int32_T)*32);
    write_buffers(rtY_Out1, sizeof(int32_T)*32);
    write_buffers(rtY_Filter_Update, sizeof(int32_T)*32);
    write_buffers(rtY_normalize_value, sizeof(real32_T)*32);
  }
  write_remain_data();
  free_buffers();
  fclose(file);
  clock_t end = clock();
  double used_time = (double)(end -start) / CLOCKS_PER_SEC;
  FILE *result_file = fopen("result.txt", "w");
  if (result_file != NULL) {
        fprintf(result_file, "spent_time: %.3fsecond\n", used_time);
        fclose(result_file);
  }

  return 0;
}
