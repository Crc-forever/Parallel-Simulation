#include <stddef.h>
#include <stdio.h>
#include "BLDC.h"

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

int_T main(int_T argc, const char *argv[])
{
  RT_MODEL *const rtM = rtMPtr;
  (void)(argc);
  (void)(argv);
  BLDC_initialize(rtM, rtU_U1, rtU_U2, rtU_U3, rtU_U4, rtU_KT, rtU_I, rtU_Kd,
                  rtU_Kd_4, rtU_KT_I, rtU_Kd_3, rtY_u1, rtY_u2, rtY_u3, rtY_u4,
                  rtY_omega_1, rtY_omega_2, rtY_omega_3, rtY_omega_4);
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(rtM) == (NULL)) {
  }

  return 0;
}
