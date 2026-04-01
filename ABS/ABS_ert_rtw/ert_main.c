#include <stddef.h>
#include <stdio.h>
#include "ABS.h"

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

int_T main(int_T argc, const char *argv[])
{
  RT_MODEL *const rtM = rtMPtr;
  (void)(argc);
  (void)(argv);
  ABS_initialize(rtM, rtU_Speed, rtU_FilterValue, rtU_Acc, rtU_P_i, rtU_Q, rtU_H,
                 rtU_R, rtY_P_Update, rtY_Out1, rtY_Filter_Update,
                 rtY_normalize_value);
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(rtM) == (NULL)) {
  }

  return 0;
}
