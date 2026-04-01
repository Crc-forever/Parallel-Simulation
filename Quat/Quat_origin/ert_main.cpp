#include <stddef.h>
#include <stdio.h>
#include "Quat.h"
#include <time.h>
#include <windows.h>
#include "define.h"

static RT_MODEL rtM_;
static RT_MODEL *const rtMPtr = &rtM_;
static int32_T rtU_Inport[8];
static int32_T rtU_Inport1[8];
static int32_T rtU_Inport2[8];
static int32_T rtU_Inport3[8];
static int32_T rtU_Inport4[8];
static int32_T rtU_Inport5[8];
static int32_T rtU_Inport6[8];
static int32_T rtU_Inport7[8];
static real32_T rtY_Outport[8];
static real32_T rtY_Outport1[8];
static real32_T rtY_Outport2[8];
static real32_T rtY_Outport3[8];
static real32_T rtY_Outport4[8];
void rt_OneStep(RT_MODEL *const rtM);
void rt_OneStep(RT_MODEL *const rtM)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }

  OverrunFlag = true;
  Quat_step(rtM, rtU_Inport, rtU_Inport1, rtU_Inport2, rtU_Inport3, rtU_Inport4,
            rtU_Inport5, rtU_Inport6, rtU_Inport7, rtY_Outport, rtY_Outport1,
            rtY_Outport2, rtY_Outport3, rtY_Outport4);
  OverrunFlag = false;
}

int TOTAL_STEP = 500000;
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL *const rtM = rtMPtr;

  Quat_initialize(rtM, rtU_Inport, rtU_Inport1, rtU_Inport2, rtU_Inport3,
                  rtU_Inport4, rtU_Inport5, rtU_Inport6, rtU_Inport7,
                  rtY_Outport, rtY_Outport1, rtY_Outport2, rtY_Outport3,
                  rtY_Outport4);
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
    fread(rtU_Inport, sizeof(int32_T), 8, file);
    fread(rtU_Inport1, sizeof(int32_T), 8, file);
    fread(rtU_Inport2, sizeof(int32_T), 8, file);
    fread(rtU_Inport3, sizeof(int32_T), 8, file);
    fread(rtU_Inport4, sizeof(int32_T), 8, file);
    fread(rtU_Inport5, sizeof(int32_T), 8, file);
    fread(rtU_Inport6, sizeof(int32_T), 8, file);
    fread(rtU_Inport7, sizeof(int32_T), 8, file);
    rt_OneStep(rtM);
    write_buffers(rtY_Outport, sizeof(real32_T)*8);
    write_buffers(rtY_Outport1, sizeof(real32_T)*8);
    write_buffers(rtY_Outport2, sizeof(real32_T)*8);
    write_buffers(rtY_Outport3, sizeof(real32_T)*8);
    write_buffers(rtY_Outport4, sizeof(real32_T)*8);
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
