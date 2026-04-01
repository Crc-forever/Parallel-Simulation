#include <stddef.h>
#include <stdio.h>
#include "FirstPress.h"

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

int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_FirstPress_T *const FirstPress_M = FirstPress_MPtr;
  (void)(argc);
  (void)(argv);
  FirstPress_initialize(FirstPress_M, FirstPress_U_FIRST_PASS,
                        FirstPress_U_AUTO_MANUAL_SWITCH,
                        FirstPress_Y_INIT_JET_SELECT,
                        FirstPress_Y_INIT_STATE_ERROR,
                        FirstPress_Y_INIT_JET_SELECT1,
                        FirstPress_Y_INIT_STATE_ERROR1);
  printf("Warning: The simulation will run forever. "
         "Generated ERT main won't simulate model step behavior. "
         "To change this behavior select the 'MAT-file logging' option.\n");
  fflush((NULL));
  while (rtmGetErrorStatus(FirstPress_M) == (NULL)) {
  }

  FirstPress_terminate(FirstPress_M);
  return 0;
}
