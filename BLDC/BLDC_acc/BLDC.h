#ifndef BLDC_h_
#define BLDC_h_
#ifndef BLDC_COMMON_INCLUDES_
#define BLDC_COMMON_INCLUDES_
#include "rtwtypes.h"
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

extern void BLDC_initialize(RT_MODEL *const rtM, int32_T rtU_U1[32], int32_T
  rtU_U2[32], int32_T rtU_U3[32], int32_T rtU_U4[32], int32_T rtU_KT[32],
  int32_T rtU_I[32], int32_T rtU_Kd[32], int32_T rtU_Kd_4[32], int32_T rtU_KT_I
  [32], int32_T rtU_Kd_3[32], int32_T rtY_u1[32], int32_T rtY_u2[32], int32_T
  rtY_u3[32], int32_T rtY_u4[32], real32_T rtY_omega_1[32], real32_T
  rtY_omega_2[32], real32_T rtY_omega_3[32], real32_T rtY_omega_4[32]);
extern void BLDC_step(RT_MODEL *const rtM, int32_T rtU_U1[32], int32_T rtU_U2[32],
                      int32_T rtU_U3[32], int32_T rtU_U4[32], int32_T rtU_KT[32],
                      int32_T rtU_I[32], int32_T rtU_Kd[32], int32_T rtU_Kd_4[32],
                      int32_T rtU_KT_I[32], int32_T rtU_Kd_3[32], int32_T
                      rtY_u1[32], int32_T rtY_u2[32], int32_T rtY_u3[32],
                      int32_T rtY_u4[32], real32_T rtY_omega_1[32], real32_T
                      rtY_omega_2[32], real32_T rtY_omega_3[32], real32_T
                      rtY_omega_4[32]);

#endif

