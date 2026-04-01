#ifndef Elevator_Correct_h_
#define Elevator_Correct_h_
#ifndef Elevator_Correct_COMMON_INCLUDES_
#define Elevator_Correct_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif

#include "Elevator_Correct_types.h"
#include <string.h>
#include "rt_defines.h"
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

typedef struct {
  real_T oraingoPisua;
  uint8_T is_active_c3_Elevator_Correct;
  uint8_T is_c3_Elevator_Correct;
  uint8_T temporalCounter_i1;
} DW_Elevator_Correct_T;

struct tag_RTM_Elevator_Correct_T {
  const char_T * volatile errorStatus;
  DW_Elevator_Correct_T *dwork;
};

extern void Elevator_Correct_initialize(RT_MODEL_Elevator_Correct_T *const
  Elevator_Correct_M, real_T *Elevator_Correct_U_pisua, real_T
  *Elevator_Correct_Y_Out1, real_T *Elevator_Correct_Y_Out2, real_T
  *Elevator_Correct_Y_Out3);
extern void Elevator_Correct_step(RT_MODEL_Elevator_Correct_T *const
  Elevator_Correct_M, real_T Elevator_Correct_U_pisua, real_T
  *Elevator_Correct_Y_Out1, real_T *Elevator_Correct_Y_Out2, real_T
  *Elevator_Correct_Y_Out3);
extern void Elevator_Correct_terminate(RT_MODEL_Elevator_Correct_T *const
  Elevator_Correct_M);

#endif

