#include "ABS.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "math.h"

static void Accumulate(const int32_T rtu_H[32], const int32_T rtu_R[32], int32_T
  rty_Out1[32]);
static void Normalize(const int32_T rtu_In1[32], real32_T rty_Out1[32]);
static void PredictValue(const int32_T rtu_Speed[32], const int32_T rtu_Filter
  [32], int32_T rty_Value[32]);
static void SubtractPredict(const int32_T rtu_Predict_Value[32], const int32_T
  rtu_P_Update[32], const int32_T rtu_Accumulate[32], int32_T rty_Out1[32]);
static void UpdatePValue(const int16_T rtu_Acc[32], const int16_T rtu_P[32],
  const int32_T rtu_q[32], int32_T rty_P_Update[32]);
static void ABS_d(const int32_T rtu_Speed[32], const int32_T rtu_Filter[32],
                  const int16_T rtu_Acc[32], const int16_T rtu_P[32], const
                  int32_T rtu_q[32], const int32_T rtu_H[32], const int32_T
                  rtu_R[32], int32_T rty_Out1[32], int32_T rty_Out2[32], int32_T
                  rty_Out3[32], real32_T rty_Out4[32]);
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
real_T rtNaN = -(real_T)NAN;
real_T rtInf = (real_T)INFINITY;
real_T rtMinusInf = -(real_T)INFINITY;
real32_T rtNaNF = -(real32_T)NAN;
real32_T rtInfF = (real32_T)INFINITY;
real32_T rtMinusInfF = -(real32_T)INFINITY;

#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)
#else
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

static real_T rtGetInf(void)
{
  return rtInf;
}

static real32_T rtGetInfF(void)
{
  return rtInfF;
}

static real_T rtGetMinusInf(void)
{
  return rtMinusInf;
}

static real32_T rtGetMinusInfF(void)
{
  return rtMinusInfF;
}

static real_T rtGetNaN(void)
{
  return rtNaN;
}

static real32_T rtGetNaNF(void)
{
  return rtNaNF;
}

static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)isinf(value);
}

static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)isinf(value);
}

static boolean_T rtIsNaN(real_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

static boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(isnan(value) != 0);
}

static void Accumulate(const int32_T rtu_H[32], const int32_T rtu_R[32], int32_T
  rty_Out1[32])
{
  int32_T i;
  for (i = 0; i < 32; i++) {
    int64_T tmp;
    int32_T rtu_H_0;
    rtu_H_0 = rtu_H[i];
    tmp = (int64_T)(rtu_H_0 * rtu_R[i]) + rtu_H_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    rty_Out1[i] = (int32_T)tmp;
  }
}

static void Normalize(const int32_T rtu_In1[32], real32_T rty_Out1[32])
{
  int32_T i;
  for (i = 0; i < 32; i++) {
    int32_T u;
    u = rtu_In1[i];
    if (u > 0.0F) {
      rty_Out1[i] = 1.0F / sqrtf((real32_T)u);
    } else if (u == 0.0F) {
      rty_Out1[i] = (rtInfF);
    } else {
      rty_Out1[i] = (rtNaNF);
    }
  }
}

static void PredictValue(const int32_T rtu_Speed[32], const int32_T rtu_Filter
  [32], int32_T rty_Value[32])
{
  int32_T i;
  for (i = 0; i < 32; i++) {
    int32_T rty_Value_0;
    rty_Value_0 = rtu_Speed[i] - 3 * rtu_Filter[i];
    if (rty_Value_0 < 0) {
      rty_Value[i] = -rty_Value_0;
    } else {
      rty_Value[i] = rty_Value_0;
    }
  }
}

static void SubtractPredict(const int32_T rtu_Predict_Value[32], const int32_T
  rtu_P_Update[32], const int32_T rtu_Accumulate[32], int32_T rty_Out1[32])
{
  int32_T i;
  for (i = 0; i < 32; i++) {
    int64_T tmp;
    tmp = (int64_T)rtu_P_Update[i] - rtu_Accumulate[i];
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    tmp += rtu_Predict_Value[i];
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    rty_Out1[i] = (int32_T)tmp;
  }
}

static void UpdatePValue(const int16_T rtu_Acc[32], const int16_T rtu_P[32],
  const int32_T rtu_q[32], int32_T rty_P_Update[32])
{
  int32_T i;
  for (i = 0; i < 32; i++) {
    int64_T tmp;
    int32_T rty_P_Update_0;
    rty_P_Update_0 = rtu_Acc[i] * rtu_P[i];
    if (rty_P_Update_0 > 1073741823) {
      rty_P_Update_0 = MAX_int32_T;
    } else {
      rty_P_Update_0 <<= 1;
    }

    tmp = (int64_T)rtu_q[i] + rty_P_Update_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    rty_P_Update[i] = (int32_T)tmp;
  }
}

static void ABS_d(const int32_T rtu_Speed[32], const int32_T rtu_Filter[32],
                  const int16_T rtu_Acc[32], const int16_T rtu_P[32], const
                  int32_T rtu_q[32], const int32_T rtu_H[32], const int32_T
                  rtu_R[32], int32_T rty_Out1[32], int32_T rty_Out2[32], int32_T
                  rty_Out3[32], real32_T rty_Out4[32])
{
  int32_T rtb_Add1[32];
  int32_T i;
  Accumulate(rtu_H, rtu_R, rtb_Add1);
  PredictValue(rtu_Speed, rtu_Filter, rty_Out1);
  UpdatePValue(rtu_Acc, rtu_P, rtu_q, rty_Out2);
  SubtractPredict(rty_Out1, rty_Out2, rtb_Add1, rty_Out3);
  for (i = 0; i < 32; i++) {
    rty_Out1[i] = rty_Out3[i] >> 1;
  }

  Normalize(rtb_Add1, rty_Out4);
}

void ABS_step(RT_MODEL *const rtM, int32_T rtU_Speed[32], int32_T
              rtU_FilterValue[32], int16_T rtU_Acc[32], int16_T rtU_P_i[32],
              int32_T rtU_Q[32], int32_T rtU_H[32], int32_T rtU_R[32], int32_T
              rtY_P_Update[32], int32_T rtY_Out1[32], int32_T rtY_Filter_Update
              [32], real32_T rtY_normalize_value[32])
{
  ABS_d(rtU_Speed, rtU_FilterValue, rtU_Acc, rtU_P_i, rtU_Q, rtU_H, rtU_R,
        rtY_Out1, rtY_P_Update, rtY_Filter_Update, rtY_normalize_value);
  UNUSED_PARAMETER(rtM);
}

void ABS_initialize(RT_MODEL *const rtM, int32_T rtU_Speed[32], int32_T
                    rtU_FilterValue[32], int16_T rtU_Acc[32], int16_T rtU_P_i[32],
                    int32_T rtU_Q[32], int32_T rtU_H[32], int32_T rtU_R[32],
                    int32_T rtY_P_Update[32], int32_T rtY_Out1[32], int32_T
                    rtY_Filter_Update[32], real32_T rtY_normalize_value[32])
{
  rtmSetErrorStatus(rtM, (NULL));
  (void)memset(&rtU_Speed[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_FilterValue[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_Acc[0], 0, sizeof(int16_T) << 5U);
  (void)memset(&rtU_P_i[0], 0, sizeof(int16_T) << 5U);
  (void)memset(&rtU_Q[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_H[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_R[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtY_P_Update[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtY_Out1[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtY_Filter_Update[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtY_normalize_value[0], 0, sizeof(real32_T) << 5U);
  UNUSED_PARAMETER(rtM);
}
