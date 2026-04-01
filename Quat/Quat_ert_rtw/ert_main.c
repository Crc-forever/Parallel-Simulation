#include <stddef.h>
#include <stdio.h>
#include "Quat.h"

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

int_T main(int_T argc, const char *argv[])
{
  RT_MODEL *const rtM = rtMPtr;
  (void)(argc);
  (void)(argv);
  Quat_initialize(rtM, rtU_Inport, rtU_Inport1, rtU_Inport2, rtU_Inport3,
                  rtU_Inport4, rtU_Inport5, rtU_Inport6, rtU_Inport7,
                  rtY_Outport, rtY_Outport1, rtY_Outport2, rtY_Outport3,
                  rtY_Outport4);
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(rtM) == (NULL)) {
  }

  return 0;
}
