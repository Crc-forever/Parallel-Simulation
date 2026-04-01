#include <stddef.h>
#include <stdio.h>
#include "LANSwitch.h"
#include <time.h>
#include <windows.h>
#include "define.h"

static RT_MODEL_LANSwitch_T LANSwitch_M_;
static RT_MODEL_LANSwitch_T *const LANSwitch_MPtr = &LANSwitch_M_;
static B_LANSwitch_T LANSwitch_B;
static DW_LANSwitch_T LANSwitch_DW;
static int32_T LANSwitch_U_PortId;
static int32_T LANSwitch_U_CMD;
static int32_T LANSwitch_U_Arg1;
static int32_T LANSwitch_U_Arg2;
static int32_T LANSwitch_U_Arg3;
static int32_T LANSwitch_Y_Result;
static int32_T LANSwitch_Y_MSG;
void rt_OneStep(RT_MODEL_LANSwitch_T *const LANSwitch_M);
void rt_OneStep(RT_MODEL_LANSwitch_T *const LANSwitch_M)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    rtmSetErrorStatus(LANSwitch_M, "Overrun");
    return;
  }

  OverrunFlag = true;
  LANSwitch_step(LANSwitch_M, LANSwitch_U_PortId, LANSwitch_U_CMD,
                 LANSwitch_U_Arg1, LANSwitch_U_Arg2, LANSwitch_U_Arg3,
                 &LANSwitch_Y_Result, &LANSwitch_Y_MSG);
  OverrunFlag = false;
}

int TOTAL_STEP = 50000000;
char *log_buf = (char *)malloc(10 * 1024 * 1024);
int log_buf_pos = 0; // 跟踪缓冲区当前位置
int32_T *input_buf = NULL; // 先初始化指针为NULL
int input_buf_pos = 0; // 跟踪缓冲区当前位置

int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_LANSwitch_T *const LANSwitch_M = LANSwitch_MPtr;
  (void)(argc);
  (void)(argv);
  LANSwitch_M->blockIO = &LANSwitch_B;
  LANSwitch_M->dwork = &LANSwitch_DW;
  LANSwitch_initialize(LANSwitch_M, &LANSwitch_U_PortId, &LANSwitch_U_CMD,
                       &LANSwitch_U_Arg1, &LANSwitch_U_Arg2, &LANSwitch_U_Arg3,
                       &LANSwitch_Y_Result, &LANSwitch_Y_MSG);
  if (argc > 1) {
        TOTAL_STEP = atoi(argv[1]);
  }
  printf("Step: %d\n", TOTAL_STEP);
  clock_t start = clock();

  create_data_dir();
  init_buffers();
  input_buf = (int32_T *)malloc(BUFFER_SIZE_INPUT);  
  FILE *file = fopen("../test_data.bin", "rb");
  if (file == NULL) {
      perror("we cannot open the test data file");
      return 1;
  }
  clock_t log_start = clock();
  int count = 0;
  while(count < TOTAL_STEP){
      if(count % example_step == 0){
          clock_t log_end = clock();
          double log_used_time = (double)(log_end - log_start) / CLOCKS_PER_SEC; 
          log_buf_pos += sprintf(log_buf + log_buf_pos , "第%d组耗时：%.3f秒\n" , count / example_step , log_used_time);
          log_start = log_end;

          fread(input_buf , sizeof(int32_T) , example_step*5 , file);
          input_buf_pos = 0; // 重置输入缓冲区位置
      }
      for(int i = 0; i < example_step; i++){
        LANSwitch_U_PortId = input_buf[input_buf_pos++];
        LANSwitch_U_CMD = input_buf[input_buf_pos++];
        LANSwitch_U_Arg1 = input_buf[input_buf_pos++];
        LANSwitch_U_Arg2 = input_buf[input_buf_pos++];
        LANSwitch_U_Arg3 = input_buf[input_buf_pos++];
        rt_OneStep(LANSwitch_M);
        write_buffers(LANSwitch_Y_Result, sizeof(int32_T));
        write_buffers(LANSwitch_Y_MSG, sizeof(int32_T));
        count++;
      }
  }
    
  write_remain_data();
  free_buffers();
  fclose(file);
  clock_t end = clock();
  double used_time = (double)(end -start) / CLOCKS_PER_SEC;
  FILE *result_file = fopen("result.txt", "w");
  if (result_file != NULL) {
        fprintf(result_file, "spent_time: %.3fsecond\n", used_time);
        fprintf(result_file , "%s" , log_buf);
        fclose(result_file);
  }
  free(log_buf);
  free(input_buf);
  LANSwitch_terminate(LANSwitch_M);
  return 0;
}
