#include <stddef.h>
#include <stdio.h>
#include "CPUTask.h"

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

int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_CPUTask_T *const CPUTask_M = CPUTask_MPtr;
  (void)(argc);
  (void)(argv);
  CPUTask_M->dwork = &CPUTask_DW;
  CPUTask_initialize(CPUTask_M, &CPUTask_U_op, &CPUTask_U_taskId,
                     &CPUTask_U_para, &CPUTask_Y_res, &CPUTask_Y_out);
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (1) {
  }

  CPUTask_terminate(CPUTask_M);
  return 0;
}
