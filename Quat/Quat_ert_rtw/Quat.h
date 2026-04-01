#ifndef Quat_h_
#define Quat_h_
#ifndef Quat_COMMON_INCLUDES_
#define Quat_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "math.h"
#endif

#include <stddef.h>
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

typedef struct tag_RTM RT_MODEL;
struct tag_RTM {
  const char_T * volatile errorStatus;
};

extern void Quat_initialize(RT_MODEL *const rtM, int32_T rtU_Inport[8], int32_T
  rtU_Inport1[8], int32_T rtU_Inport2[8], int32_T rtU_Inport3[8], int32_T
  rtU_Inport4[8], int32_T rtU_Inport5[8], int32_T rtU_Inport6[8], int32_T
  rtU_Inport7[8], real32_T rtY_Outport[8], real32_T rtY_Outport1[8], real32_T
  rtY_Outport2[8], real32_T rtY_Outport3[8], real32_T rtY_Outport4[8]);
extern void Quat_step(RT_MODEL *const rtM, int32_T rtU_Inport[8], int32_T
                      rtU_Inport1[8], int32_T rtU_Inport2[8], int32_T
                      rtU_Inport3[8], int32_T rtU_Inport4[8], int32_T
                      rtU_Inport5[8], int32_T rtU_Inport6[8], int32_T
                      rtU_Inport7[8], real32_T rtY_Outport[8], real32_T
                      rtY_Outport1[8], real32_T rtY_Outport2[8], real32_T
                      rtY_Outport3[8], real32_T rtY_Outport4[8]);

#endif

