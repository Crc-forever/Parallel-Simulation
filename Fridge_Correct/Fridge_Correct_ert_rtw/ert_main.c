#include <stddef.h>
#include <stdio.h>
#include "Fridge_Correct.h"

static RT_MODEL_Fridge_Correct_T Fridge_Correct_M_;
static RT_MODEL_Fridge_Correct_T *const Fridge_Correct_MPtr = &Fridge_Correct_M_;
static DW_Fridge_Correct_T Fridge_Correct_DW;
static real_T Fridge_Correct_U_DOOR_SENSOR;
static real_T Fridge_Correct_U_TEMPERATURE;
static real_T Fridge_Correct_U_REF;
static real_T Fridge_Correct_Y_Out1;
static real_T Fridge_Correct_Y_Out2;
static real_T Fridge_Correct_Y_Out3;
void rt_OneStep(RT_MODEL_Fridge_Correct_T *const Fridge_Correct_M);
void rt_OneStep(RT_MODEL_Fridge_Correct_T *const Fridge_Correct_M)
{
  static boolean_T OverrunFlag = false;
  if (OverrunFlag) {
    rtmSetErrorStatus(Fridge_Correct_M, "Overrun");
    return;
  }

  OverrunFlag = true;
  Fridge_Correct_step(Fridge_Correct_M, Fridge_Correct_U_DOOR_SENSOR,
                      Fridge_Correct_U_TEMPERATURE, Fridge_Correct_U_REF,
                      &Fridge_Correct_Y_Out1, &Fridge_Correct_Y_Out2,
                      &Fridge_Correct_Y_Out3);
  OverrunFlag = false;
}

int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_Fridge_Correct_T *const Fridge_Correct_M = Fridge_Correct_MPtr;
  (void)(argc);
  (void)(argv);
  Fridge_Correct_M->dwork = &Fridge_Correct_DW;
  Fridge_Correct_initialize(Fridge_Correct_M, &Fridge_Correct_U_DOOR_SENSOR,
    &Fridge_Correct_U_TEMPERATURE, &Fridge_Correct_U_REF, &Fridge_Correct_Y_Out1,
    &Fridge_Correct_Y_Out2, &Fridge_Correct_Y_Out3);
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(Fridge_Correct_M) == (NULL)) {
  }

  Fridge_Correct_terminate(Fridge_Correct_M);
  return 0;
}
