#include "Quat.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "math.h"

static void Difference_C1(const int32_T rtu_In1[8], const int32_T rtu_In2[8],
  const int32_T rtu_In3[8], const int32_T rtu_In4[8], int32_T rty_Out1[8],
  int32_T rty_Out2[8], int32_T rty_Out3[8], int32_T rty_Out4[8]);
static void Difference_C2(const int32_T rtu_In1[8], const int32_T rtu_In2[8],
  const int32_T rtu_In3[8], const int32_T rtu_In4[8], int32_T rty_Out1[8],
  int32_T rty_Out2[8], int32_T rty_Out3[8], int32_T rty_Out4[8]);
static void Quat_R1(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], real32_T rty_Out1[8]);
static void Quat_R2(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], const int32_T rtu_In8[8], real32_T rty_Out1[8]);
static void Quat_R3(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], const int32_T rtu_In8[8], real32_T rty_Out1[8]);
static void Quat_R4(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], const int32_T rtu_In8[8], real32_T rty_Out1[8]);
static void Quat_R5(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], const int32_T rtu_In8[8], real32_T rty_Out1[8]);
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

static void Difference_C1(const int32_T rtu_In1[8], const int32_T rtu_In2[8],
  const int32_T rtu_In3[8], const int32_T rtu_In4[8], int32_T rty_Out1[8],
  int32_T rty_Out2[8], int32_T rty_Out3[8], int32_T rty_Out4[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    int32_T rtu_In1_0;
    int32_T rtu_In2_0;
    int32_T rty_Out1_0;
    rtu_In1_0 = rtu_In1[i];
    rtu_In2_0 = rtu_In2[i];
    rty_Out1_0 = rtu_In1_0 - rtu_In2_0;
    if (rty_Out1_0 < 0) {
      rty_Out1[i] = -rty_Out1_0;
    } else {
      rty_Out1[i] = rty_Out1_0;
    }

    rty_Out1_0 = rtu_In3[i];
    rtu_In2_0 -= rty_Out1_0;
    if (rtu_In2_0 < 0) {
      rty_Out2[i] = -rtu_In2_0;
    } else {
      rty_Out2[i] = rtu_In2_0;
    }

    rtu_In2_0 = rtu_In4[i];
    rty_Out1_0 -= rtu_In2_0;
    if (rty_Out1_0 < 0) {
      rty_Out3[i] = -rty_Out1_0;
    } else {
      rty_Out3[i] = rty_Out1_0;
    }

    rtu_In1_0 = rtu_In2_0 - rtu_In1_0;
    if (rtu_In1_0 < 0) {
      rty_Out4[i] = -rtu_In1_0;
    } else {
      rty_Out4[i] = rtu_In1_0;
    }
  }
}

static void Difference_C2(const int32_T rtu_In1[8], const int32_T rtu_In2[8],
  const int32_T rtu_In3[8], const int32_T rtu_In4[8], int32_T rty_Out1[8],
  int32_T rty_Out2[8], int32_T rty_Out3[8], int32_T rty_Out4[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    int32_T rtu_In1_0;
    int32_T rtu_In2_0;
    int32_T rty_Out1_0;
    rtu_In1_0 = rtu_In1[i];
    rtu_In2_0 = rtu_In2[i];
    rty_Out1_0 = rtu_In1_0 - rtu_In2_0;
    if (rty_Out1_0 < 0) {
      rty_Out1[i] = -rty_Out1_0;
    } else {
      rty_Out1[i] = rty_Out1_0;
    }

    rty_Out1_0 = rtu_In3[i];
    rtu_In2_0 -= rty_Out1_0;
    if (rtu_In2_0 < 0) {
      rty_Out2[i] = -rtu_In2_0;
    } else {
      rty_Out2[i] = rtu_In2_0;
    }

    rtu_In2_0 = rtu_In4[i];
    rty_Out1_0 -= rtu_In2_0;
    if (rty_Out1_0 < 0) {
      rty_Out3[i] = -rty_Out1_0;
    } else {
      rty_Out3[i] = rty_Out1_0;
    }

    rtu_In1_0 = rtu_In2_0 - rtu_In1_0;
    if (rtu_In1_0 < 0) {
      rty_Out4[i] = -rtu_In1_0;
    } else {
      rty_Out4[i] = rtu_In1_0;
    }
  }
}

static void Quat_R1(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], real32_T rty_Out1[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    int64_T tmp;
    int64_T tmp_0;
    int32_T rtu_In1_0;
    rtu_In1_0 = rtu_In1[i];
    tmp = (int64_T)(rtu_In1_0 * rtu_In1_0) + rtu_In3[i] * rtu_In2[i];
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    tmp_0 = (int64_T)(rtu_In5[i] * rtu_In4[i]) + rtu_In7[i] * rtu_In6[i];
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    tmp += tmp_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    if (tmp > 0.0F) {
      rty_Out1[i] = 1.0F / sqrtf((real32_T)tmp);
    } else if (tmp == 0.0F) {
      rty_Out1[i] = (rtInfF);
    } else {
      rty_Out1[i] = (rtNaNF);
    }
  }
}

static void Quat_R2(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], const int32_T rtu_In8[8], real32_T rty_Out1[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    int64_T tmp;
    int64_T tmp_0;
    tmp = (int64_T)(rtu_In1[i] * rtu_In5[i]) + -(rtu_In2[i] * rtu_In6[i]);
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    tmp_0 = (int64_T)-(rtu_In3[i] * rtu_In7[i]) + -(rtu_In4[i] * rtu_In8[i]);
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    tmp += tmp_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    if (tmp > 0.0F) {
      rty_Out1[i] = 1.0F / sqrtf((real32_T)tmp);
    } else if (tmp == 0.0F) {
      rty_Out1[i] = (rtInfF);
    } else {
      rty_Out1[i] = (rtNaNF);
    }
  }
}

static void Quat_R3(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], const int32_T rtu_In8[8], real32_T rty_Out1[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    int64_T tmp;
    int64_T tmp_0;
    tmp = (int64_T)(rtu_In1[i] * rtu_In6[i]) + rtu_In2[i] * rtu_In5[i];
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    tmp_0 = (int64_T)(rtu_In3[i] * rtu_In8[i]) + -(rtu_In4[i] * rtu_In7[i]);
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    tmp += tmp_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    if (tmp > 0.0F) {
      rty_Out1[i] = 1.0F / sqrtf((real32_T)tmp);
    } else if (tmp == 0.0F) {
      rty_Out1[i] = (rtInfF);
    } else {
      rty_Out1[i] = (rtNaNF);
    }
  }
}

static void Quat_R4(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], const int32_T rtu_In8[8], real32_T rty_Out1[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    int64_T tmp;
    int64_T tmp_0;
    tmp = (int64_T)(rtu_In1[i] * rtu_In7[i]) + -(rtu_In2[i] * rtu_In8[i]);
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    tmp_0 = (int64_T)(rtu_In3[i] * rtu_In5[i]) + rtu_In4[i] * rtu_In6[i];
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    tmp += tmp_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    if (tmp > 0.0F) {
      rty_Out1[i] = 1.0F / sqrtf((real32_T)tmp);
    } else if (tmp == 0.0F) {
      rty_Out1[i] = (rtInfF);
    } else {
      rty_Out1[i] = (rtNaNF);
    }
  }
}

static void Quat_R5(const int32_T rtu_In1[8], const int32_T rtu_In2[8], const
                    int32_T rtu_In3[8], const int32_T rtu_In4[8], const int32_T
                    rtu_In5[8], const int32_T rtu_In6[8], const int32_T rtu_In7
                    [8], const int32_T rtu_In8[8], real32_T rty_Out1[8])
{
  int32_T i;
  for (i = 0; i < 8; i++) {
    int64_T tmp;
    int64_T tmp_0;
    tmp = (int64_T)(rtu_In1[i] * rtu_In8[i]) + rtu_In2[i] * rtu_In7[i];
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    tmp_0 = (int64_T)(rtu_In4[i] * rtu_In5[i]) + -(rtu_In3[i] * rtu_In6[i]);
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    tmp += tmp_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    if (tmp > 0.0F) {
      rty_Out1[i] = 1.0F / sqrtf((real32_T)tmp);
    } else if (tmp == 0.0F) {
      rty_Out1[i] = (rtInfF);
    } else {
      rty_Out1[i] = (rtNaNF);
    }
  }
}

void Quat_step(RT_MODEL *const rtM, int32_T rtU_Inport[8], int32_T rtU_Inport1[8],
               int32_T rtU_Inport2[8], int32_T rtU_Inport3[8], int32_T
               rtU_Inport4[8], int32_T rtU_Inport5[8], int32_T rtU_Inport6[8],
               int32_T rtU_Inport7[8], real32_T rtY_Outport[8], real32_T
               rtY_Outport1[8], real32_T rtY_Outport2[8], real32_T rtY_Outport3
               [8], real32_T rtY_Outport4[8])
{
  int32_T rtb_Abs[8];
  int32_T rtb_Abs1[8];
  int32_T rtb_Abs2[8];
  int32_T rtb_Abs3[8];
  int32_T rtb_Abs4[8];
  int32_T rtb_Abs5[8];
  int32_T rtb_Abs6[8];
  int32_T rtb_Abs7[8];
  Difference_C1(rtU_Inport, rtU_Inport1, rtU_Inport2, rtU_Inport3, rtb_Abs,
                rtb_Abs1, rtb_Abs2, rtb_Abs3);
  Difference_C2(rtU_Inport4, rtU_Inport5, rtU_Inport6, rtU_Inport7, rtb_Abs4,
                rtb_Abs5, rtb_Abs6, rtb_Abs7);
  Quat_R2(rtb_Abs, rtb_Abs1, rtb_Abs2, rtb_Abs3, rtb_Abs4, rtb_Abs5, rtb_Abs6,
          rtb_Abs7, rtY_Outport1);
  Quat_R3(rtb_Abs, rtb_Abs1, rtb_Abs2, rtb_Abs3, rtb_Abs4, rtb_Abs5, rtb_Abs6,
          rtb_Abs7, rtY_Outport2);
  Quat_R4(rtb_Abs, rtb_Abs1, rtb_Abs2, rtb_Abs3, rtb_Abs4, rtb_Abs5, rtb_Abs6,
          rtb_Abs7, rtY_Outport3);
  Quat_R5(rtb_Abs, rtb_Abs1, rtb_Abs2, rtb_Abs3, rtb_Abs4, rtb_Abs5, rtb_Abs6,
          rtb_Abs7, rtY_Outport4);
  Quat_R1(rtb_Abs, rtb_Abs1, rtb_Abs1, rtb_Abs2, rtb_Abs2, rtb_Abs3, rtb_Abs3,
          rtY_Outport);
  UNUSED_PARAMETER(rtM);
}

void Quat_initialize(RT_MODEL *const rtM, int32_T rtU_Inport[8], int32_T
                     rtU_Inport1[8], int32_T rtU_Inport2[8], int32_T
                     rtU_Inport3[8], int32_T rtU_Inport4[8], int32_T
                     rtU_Inport5[8], int32_T rtU_Inport6[8], int32_T
                     rtU_Inport7[8], real32_T rtY_Outport[8], real32_T
                     rtY_Outport1[8], real32_T rtY_Outport2[8], real32_T
                     rtY_Outport3[8], real32_T rtY_Outport4[8])
{
  rtmSetErrorStatus(rtM, (NULL));
  (void)memset(&rtU_Inport[0], 0, sizeof(int32_T) << 3U);
  (void)memset(&rtU_Inport1[0], 0, sizeof(int32_T) << 3U);
  (void)memset(&rtU_Inport2[0], 0, sizeof(int32_T) << 3U);
  (void)memset(&rtU_Inport3[0], 0, sizeof(int32_T) << 3U);
  (void)memset(&rtU_Inport4[0], 0, sizeof(int32_T) << 3U);
  (void)memset(&rtU_Inport5[0], 0, sizeof(int32_T) << 3U);
  (void)memset(&rtU_Inport6[0], 0, sizeof(int32_T) << 3U);
  (void)memset(&rtU_Inport7[0], 0, sizeof(int32_T) << 3U);
  (void)memset(&rtY_Outport[0], 0, sizeof(real32_T) << 3U);
  (void)memset(&rtY_Outport1[0], 0, sizeof(real32_T) << 3U);
  (void)memset(&rtY_Outport2[0], 0, sizeof(real32_T) << 3U);
  (void)memset(&rtY_Outport3[0], 0, sizeof(real32_T) << 3U);
  (void)memset(&rtY_Outport4[0], 0, sizeof(real32_T) << 3U);
  UNUSED_PARAMETER(rtM);
}
