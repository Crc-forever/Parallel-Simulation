#ifndef Fridge_Correct_h_
#define Fridge_Correct_h_
#ifndef Fridge_Correct_COMMON_INCLUDES_
#define Fridge_Correct_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif

#include "Fridge_Correct_types.h"
#include <string.h>
#include "rt_defines.h"
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

typedef struct {
  uint8_T is_active_c3_Fridge_Correct;
  uint8_T is_c3_Fridge_Correct;
  uint8_T temporalCounter_i1;
} DW_Fridge_Correct_T;

struct tag_RTM_Fridge_Correct_T {
  const char_T * volatile errorStatus;
  DW_Fridge_Correct_T *dwork;
};

extern void Fridge_Correct_initialize(RT_MODEL_Fridge_Correct_T *const
  Fridge_Correct_M, real_T *Fridge_Correct_U_DOOR_SENSOR, real_T
  *Fridge_Correct_U_TEMPERATURE, real_T *Fridge_Correct_U_REF, real_T
  *Fridge_Correct_Y_Out1, real_T *Fridge_Correct_Y_Out2, real_T
  *Fridge_Correct_Y_Out3);
extern void Fridge_Correct_step(RT_MODEL_Fridge_Correct_T *const
  Fridge_Correct_M, real_T Fridge_Correct_U_DOOR_SENSOR, real_T
  Fridge_Correct_U_TEMPERATURE, real_T Fridge_Correct_U_REF, real_T
  *Fridge_Correct_Y_Out1, real_T *Fridge_Correct_Y_Out2, real_T
  *Fridge_Correct_Y_Out3);
extern void Fridge_Correct_terminate(RT_MODEL_Fridge_Correct_T *const
  Fridge_Correct_M);

#endif

