#include <stddef.h>
#include <stdio.h>
#include "CPUTask.h"
#include <time.h>
#include <windows.h>
#include "define.h"

static RT_MODEL_CPUTask_T CPUTask_M_;
static RT_MODEL_CPUTask_T *const CPUTask_MPtr = &CPUTask_M_;
static DW_CPUTask_T CPUTask_DW;
static int32_T CPUTask_U_op;
static int32_T CPUTask_U_taskId;
static int32_T CPUTask_U_para;
static int32_T CPUTask_Y_res;
static int32_T CPUTask_Y_out;
void rt_OneStep(RT_MODEL_CPUTask_T *const CPUTask_M);
void rt_OneStep(RT_MODEL_CPUTask_T *const CPUTask_M)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    return;
  }

  OverrunFlag = true;
  CPUTask_step(CPUTask_M, CPUTask_U_op, CPUTask_U_taskId, CPUTask_U_para,
               &CPUTask_Y_res, &CPUTask_Y_out);
  OverrunFlag = false;
}

int TOTAL_STEP = 50000000;
char *log_buf = (char *)malloc(10 * 1024 * 1024);
int log_buf_pos = 0; // 跟踪缓冲区当前位置
int32_T *input_buf = NULL; // 先初始化指针为NULL
int input_buf_pos = 0; // 跟踪缓冲区当前位置
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_CPUTask_T *const CPUTask_M = CPUTask_MPtr;
  (void)(argc);
  (void)(argv);
  CPUTask_M->dwork = &CPUTask_DW;
  CPUTask_initialize(CPUTask_M, &CPUTask_U_op, &CPUTask_U_taskId,
                     &CPUTask_U_para, &CPUTask_Y_res, &CPUTask_Y_out);
  
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

          fread(input_buf , sizeof(int32_T) , example_step*3 , file);
          input_buf_pos = 0; // 重置输入缓冲区位置
      }
      for(int i = 0; i < example_step; i++){
        CPUTask_U_op = input_buf[input_buf_pos++];
        CPUTask_U_taskId = input_buf[input_buf_pos++];
        CPUTask_U_para = input_buf[input_buf_pos++];
        rt_OneStep(CPUTask_M);
        write_buffers(CPUTask_Y_res, sizeof(int32_T));
        write_buffers(CPUTask_Y_out, sizeof(int32_T));
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

  CPUTask_terminate(CPUTask_M);
  return 0;
}
