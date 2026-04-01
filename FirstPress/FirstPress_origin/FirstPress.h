#ifndef FirstPress_h_
#define FirstPress_h_
#ifndef FirstPress_COMMON_INCLUDES_
#define FirstPress_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif

#include "FirstPress_types.h"
#include "rt_defines.h"
#include <stddef.h>
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

struct tag_RTM_FirstPress_T {
  const char_T * volatile errorStatus;
};

extern void FirstPress_initialize(RT_MODEL_FirstPress_T *const FirstPress_M,
  int32_T FirstPress_U_FIRST_PASS[32], int16_T FirstPress_U_AUTO_MANUAL_SWITCH
  [32], boolean_T FirstPress_Y_INIT_JET_SELECT[32], boolean_T
  FirstPress_Y_INIT_STATE_ERROR[32], boolean_T FirstPress_Y_INIT_JET_SELECT1[32],
  boolean_T FirstPress_Y_INIT_STATE_ERROR1[32]);
extern void FirstPress_step(RT_MODEL_FirstPress_T *const FirstPress_M, int32_T
  FirstPress_U_FIRST_PASS[32], int16_T FirstPress_U_AUTO_MANUAL_SWITCH[32],
  boolean_T FirstPress_Y_INIT_JET_SELECT[32], boolean_T
  FirstPress_Y_INIT_STATE_ERROR[32], boolean_T FirstPress_Y_INIT_JET_SELECT1[32],
  boolean_T FirstPress_Y_INIT_STATE_ERROR1[32]);
extern void FirstPress_terminate(RT_MODEL_FirstPress_T *const FirstPress_M);

#endif

