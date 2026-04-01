#include <stddef.h>
#include <stdio.h>
#include "FirstPress.h"
#include <time.h>
#include <windows.h>
#include "define.h"

static RT_MODEL_FirstPress_T FirstPress_M_;
static RT_MODEL_FirstPress_T *const FirstPress_MPtr = &FirstPress_M_;
static int32_T FirstPress_U_FIRST_PASS[32];
static int16_T FirstPress_U_AUTO_MANUAL_SWITCH[32];
static boolean_T FirstPress_Y_INIT_JET_SELECT[32];
static boolean_T FirstPress_Y_INIT_STATE_ERROR[32];
static boolean_T FirstPress_Y_INIT_JET_SELECT1[32];
static boolean_T FirstPress_Y_INIT_STATE_ERROR1[32];
void rt_OneStep(RT_MODEL_FirstPress_T *const FirstPress_M);
void rt_OneStep(RT_MODEL_FirstPress_T *const FirstPress_M)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    rtmSetErrorStatus(FirstPress_M, "Overrun");
    return;
  }

  OverrunFlag = true;
  FirstPress_step(FirstPress_M, FirstPress_U_FIRST_PASS,
                  FirstPress_U_AUTO_MANUAL_SWITCH, FirstPress_Y_INIT_JET_SELECT,
                  FirstPress_Y_INIT_STATE_ERROR, FirstPress_Y_INIT_JET_SELECT1,
                  FirstPress_Y_INIT_STATE_ERROR1);
  OverrunFlag = false;
}
int TOTAL_STEP = 500000;
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_FirstPress_T *const FirstPress_M = FirstPress_MPtr;

  FirstPress_initialize(FirstPress_M, FirstPress_U_FIRST_PASS,
                        FirstPress_U_AUTO_MANUAL_SWITCH,
                        FirstPress_Y_INIT_JET_SELECT,
                        FirstPress_Y_INIT_STATE_ERROR,
                        FirstPress_Y_INIT_JET_SELECT1,
                        FirstPress_Y_INIT_STATE_ERROR1);
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
    fread(FirstPress_U_FIRST_PASS, sizeof(int32_T), 32, file);
    fread(FirstPress_U_AUTO_MANUAL_SWITCH, sizeof(int16_T), 32, file);
    rt_OneStep(FirstPress_M);
    write_buffers(FirstPress_Y_INIT_JET_SELECT, sizeof(boolean_T)*32);
    write_buffers(FirstPress_Y_INIT_STATE_ERROR, sizeof(boolean_T)*32);
    write_buffers(FirstPress_Y_INIT_JET_SELECT1, sizeof(boolean_T)*32);
    write_buffers(FirstPress_Y_INIT_STATE_ERROR1, sizeof(boolean_T)*32);
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
  FirstPress_terminate(FirstPress_M);
  return 0;
}
