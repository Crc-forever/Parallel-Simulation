#ifndef ABS_h_
#define ABS_h_
#ifndef ABS_COMMON_INCLUDES_
#define ABS_COMMON_INCLUDES_
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

extern void ABS_initialize(RT_MODEL *const rtM, int32_T rtU_Speed[32], int32_T
  rtU_FilterValue[32], int16_T rtU_Acc[32], int16_T rtU_P_i[32], int32_T rtU_Q
  [32], int32_T rtU_H[32], int32_T rtU_R[32], int32_T rtY_P_Update[32], int32_T
  rtY_Out1[32], int32_T rtY_Filter_Update[32], real32_T rtY_normalize_value[32]);
extern void ABS_step(RT_MODEL *const rtM, int32_T rtU_Speed[32], int32_T
                     rtU_FilterValue[32], int16_T rtU_Acc[32], int16_T rtU_P_i
                     [32], int32_T rtU_Q[32], int32_T rtU_H[32], int32_T rtU_R
                     [32], int32_T rtY_P_Update[32], int32_T rtY_Out1[32],
                     int32_T rtY_Filter_Update[32], real32_T
                     rtY_normalize_value[32]);

#endif

