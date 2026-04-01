#include <stddef.h>
#include <stdio.h>
#include "BLDC.h"
#include <time.h>
#include <windows.h>
#include "define.h"

static RT_MODEL rtM_;
static RT_MODEL *const rtMPtr = &rtM_;
static int32_T rtU_U1[32];
static int32_T rtU_U2[32];
static int32_T rtU_U3[32];
static int32_T rtU_U4[32];
static int32_T rtU_KT[32];
static int32_T rtU_I[32];
static int32_T rtU_Kd[32];
static int32_T rtU_Kd_4[32];
static int32_T rtU_KT_I[32];
static int32_T rtU_Kd_3[32];
static int32_T rtY_u1[32];
static int32_T rtY_u2[32];
static int32_T rtY_u3[32];
static int32_T rtY_u4[32];
static real32_T rtY_omega_1[32];
static real32_T rtY_omega_2[32];
static real32_T rtY_omega_3[32];
static real32_T rtY_omega_4[32];
void rt_OneStep(RT_MODEL *const rtM);
void rt_OneStep(RT_MODEL *const rtM)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }

  OverrunFlag = true;
  BLDC_step(rtM, rtU_U1, rtU_U2, rtU_U3, rtU_U4, rtU_KT, rtU_I, rtU_Kd, rtU_Kd_4,
            rtU_KT_I, rtU_Kd_3, rtY_u1, rtY_u2, rtY_u3, rtY_u4, rtY_omega_1,
            rtY_omega_2, rtY_omega_3, rtY_omega_4);
  OverrunFlag = false;
}
int TOTAL_STEP = 500000;
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL *const rtM = rtMPtr;

  BLDC_initialize(rtM, rtU_U1, rtU_U2, rtU_U3, rtU_U4, rtU_KT, rtU_I, rtU_Kd,
                  rtU_Kd_4, rtU_KT_I, rtU_Kd_3, rtY_u1, rtY_u2, rtY_u3, rtY_u4,
                  rtY_omega_1, rtY_omega_2, rtY_omega_3, rtY_omega_4);
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
    fread(rtU_U1, sizeof(int32_T), 32, file);
    fread(rtU_U2, sizeof(int32_T), 32, file);
    fread(rtU_U3, sizeof(int32_T), 32, file);
    fread(rtU_U4, sizeof(int32_T), 32, file);
    fread(rtU_KT, sizeof(int32_T), 32, file);
    fread(rtU_I, sizeof(int32_T), 32, file);
    fread(rtU_Kd, sizeof(int32_T), 32, file);
    fread(rtU_Kd_4, sizeof(int32_T), 32, file);
    fread(rtU_KT_I, sizeof(int32_T), 32, file);
    fread(rtU_Kd_3, sizeof(int32_T), 32, file);
    rt_OneStep(rtM);
    write_buffers(rtY_u1, sizeof(int32_T)*32);
    write_buffers(rtY_u2, sizeof(int32_T)*32);
    write_buffers(rtY_u3, sizeof(int32_T)*32);
    write_buffers(rtY_u4, sizeof(int32_T)*32);
    write_buffers(rtY_omega_1, sizeof(real32_T)*32);
    write_buffers(rtY_omega_2, sizeof(real32_T)*32);
    write_buffers(rtY_omega_3, sizeof(real32_T)*32);
    write_buffers(rtY_omega_4, sizeof(real32_T)*32);
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
