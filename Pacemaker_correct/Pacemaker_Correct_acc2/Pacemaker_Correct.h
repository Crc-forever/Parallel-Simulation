#ifndef Pacemaker_Correct_h_
#define Pacemaker_Correct_h_
#ifndef Pacemaker_Correct_COMMON_INCLUDES_
#define Pacemaker_Correct_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include "Pacemaker_Correct_types.h"
#include <string.h>
#include "rt_defines.h"
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

typedef struct {
  real_T Floor;
} B_Pacemaker_Correct_T;

typedef struct {
  real_T Flag;
  uint32_T temporalCounter_i1;
  uint8_T is_active_c3_Pacemaker_Correct;
  uint8_T is_c3_Pacemaker_Correct;
} DW_Pacemaker_Correct_T;

typedef struct {
  const boolean_T VENT_CMP_DETECT;
  const boolean_T ATR_CMP_DETECT;
} ConstB_Pacemaker_Correct_T;

struct tag_RTM_Pacemaker_Correct_T {
  const char_T * volatile errorStatus;
  B_Pacemaker_Correct_T *blockIO;
  DW_Pacemaker_Correct_T *dwork;
};

extern const ConstB_Pacemaker_Correct_T Pacemaker_Correct_ConstB;
extern void Pacemaker_Correct_initialize(RT_MODEL_Pacemaker_Correct_T *const
  Pacemaker_Correct_M, real_T *Pacemaker_Correct_U_VENT_Amplitude, real_T
  *Pacemaker_Correct_U_Mode, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out11, real_T
  *Pacemaker_Correct_Y_Out12, real_T *Pacemaker_Correct_Y_Out13, real_T
  *Pacemaker_Correct_Y_Out14, real_T *Pacemaker_Correct_Y_Out15);
extern void Pacemaker_Correct_step(RT_MODEL_Pacemaker_Correct_T *const
  Pacemaker_Correct_M, real_T Pacemaker_Correct_U_VENT_Amplitude, real_T
  Pacemaker_Correct_U_Mode, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out11, real_T
  *Pacemaker_Correct_Y_Out12, real_T *Pacemaker_Correct_Y_Out13, real_T
  *Pacemaker_Correct_Y_Out14, real_T *Pacemaker_Correct_Y_Out15);
extern void Pacemaker_Correct_terminate(RT_MODEL_Pacemaker_Correct_T *const
  Pacemaker_Correct_M);

#endif

