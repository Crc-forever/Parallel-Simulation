#include "BLDC.h"
#include "rtwtypes.h"
#include <string.h>
#include <math.h>

extern real32_T rt_sqrt_Us32_Yf_If_f_pw_snf(int32_T u);
static void Normalize(const int32_T rtu_In1[32], const int32_T rtu_In2[32],
                      const int32_T rtu_In3[32], const int32_T rtu_In4[32],
                      real32_T rty_Out1[32], real32_T rty_Out2[32], real32_T
                      rty_Out3[32], real32_T rty_Out4[32]);
static void Omega_Sqr(const int32_T rtu_In1[32], const int32_T rtu_In2[32],
                      const int32_T rtu_In3[32], const int32_T rtu_In4[32],
                      const int32_T rtu_In5[32], const int32_T rtu_In6[32],
                      const int32_T rtu_In7[32], int32_T rty_Out1[32], int32_T
                      rty_Out2[32], int32_T rty_Out3[32], int32_T rty_Out4[32]);
static void BLDC_Sp_Calc(const int32_T rtu_In1[32], const int32_T rtu_In2[32],
  const int32_T rtu_In3[32], const int32_T rtu_In4[32], const int32_T rtu_In5[32],
  const int32_T rtu_In6[32], const int32_T rtu_In7[32], const int32_T rtu_In8[32],
  const int32_T rtu_In9[32], const int32_T rtu_In10[32], int32_T rty_u1[32],
  int32_T rty_u2[32], int32_T rty_u3[32], int32_T rty_u4[32], real32_T
  rty_omega_1[32], real32_T rty_omega_2[32], real32_T rty_omega_3[32], real32_T
  rty_omega_4[32]);

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

real32_T rt_sqrt_Us32_Yf_If_f_pw_snf(int32_T u)
{
  real32_T y;
  if (u == 0) {
    y = 0.0F;
  } else {
    y = (real32_T)sqrt((real32_T)u);
  }

  return y;
}

static void Normalize(const int32_T rtu_In1[32], const int32_T rtu_In2[32],
                      const int32_T rtu_In3[32], const int32_T rtu_In4[32],
                      real32_T rty_Out1[32], real32_T rty_Out2[32], real32_T
                      rty_Out3[32], real32_T rty_Out4[32])
{
  int32_T i;
  for (i = 0; i < 32; i++) {
    rty_Out1[i] = rt_sqrt_Us32_Yf_If_f_pw_snf(rtu_In1[i]);
    rty_Out2[i] = rt_sqrt_Us32_Yf_If_f_pw_snf(rtu_In2[i]);
    rty_Out3[i] = rt_sqrt_Us32_Yf_If_f_pw_snf(rtu_In3[i]);
    rty_Out4[i] = rt_sqrt_Us32_Yf_If_f_pw_snf(rtu_In4[i]);
  }
}

static void Omega_Sqr(const int32_T rtu_In1[32], const int32_T rtu_In2[32],
                      const int32_T rtu_In3[32], const int32_T rtu_In4[32],
                      const int32_T rtu_In5[32], const int32_T rtu_In6[32],
                      const int32_T rtu_In7[32], int32_T rty_Out1[32], int32_T
                      rty_Out2[32], int32_T rty_Out3[32], int32_T rty_Out4[32])
{
  int32_T i;
  for (i = 0; i < 32; i++) {
    int64_T tmp;
    int64_T tmp_0;
    int64_T tmp_1;
    int64_T tmp_2;
    int64_T tmp_3;
    int32_T rtu_In1_0;
    int32_T rtu_In2_0;
    tmp = rtu_In3[i];
    tmp_0 = rtu_In4[i];
    tmp_3 = tmp + tmp_0;
    if (tmp_3 > 2147483647LL) {
      tmp_3 = 2147483647LL;
    } else if (tmp_3 < -2147483648LL) {
      tmp_3 = -2147483648LL;
    }

    tmp_1 = rtu_In5[i];
    tmp_3 += tmp_1;
    if (tmp_3 > 2147483647LL) {
      tmp_3 = 2147483647LL;
    } else if (tmp_3 < -2147483648LL) {
      tmp_3 = -2147483648LL;
    }

    tmp_2 = rtu_In6[i];
    tmp_3 += tmp_2;
    if (tmp_3 > 2147483647LL) {
      tmp_3 = 2147483647LL;
    } else if (tmp_3 < -2147483648LL) {
      tmp_3 = -2147483648LL;
    }

    rtu_In2_0 = rtu_In2[i];
    rty_Out1[i] = rtu_In2_0 * (int32_T)tmp_3;
    tmp_3 = tmp_1 + tmp;
    if (tmp_3 > 2147483647LL) {
      tmp_3 = 2147483647LL;
    } else if (tmp_3 < -2147483648LL) {
      tmp_3 = -2147483648LL;
    }

    tmp_3 -= tmp_0;
    if (tmp_3 > 2147483647LL) {
      tmp_3 = 2147483647LL;
    } else if (tmp_3 < -2147483648LL) {
      tmp_3 = -2147483648LL;
    }

    tmp_3 -= tmp_2;
    if (tmp_3 > 2147483647LL) {
      tmp_3 = 2147483647LL;
    } else if (tmp_3 < -2147483648LL) {
      tmp_3 = -2147483648LL;
    }

    tmp_3 *= rtu_In7[i];
    if (tmp_3 > 2147483647LL) {
      tmp_3 = 2147483647LL;
    } else if (tmp_3 < -2147483648LL) {
      tmp_3 = -2147483648LL;
    }

    rty_Out4[i] = (int32_T)tmp_3;
    tmp_0 = tmp_2 - tmp_0;
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    rtu_In1_0 = rtu_In1[i];
    tmp_0 = (int64_T)(rtu_In2_0 * (int32_T)tmp_0) * rtu_In1_0;
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    rty_Out2[i] = (int32_T)tmp_0;
    tmp = tmp_1 - tmp;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    tmp = (int64_T)(rtu_In2_0 * (int32_T)tmp) * rtu_In1_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    rty_Out3[i] = (int32_T)tmp;
  }
}

static void BLDC_Sp_Calc(const int32_T rtu_In1[32], const int32_T rtu_In2[32],
  const int32_T rtu_In3[32], const int32_T rtu_In4[32], const int32_T rtu_In5[32],
  const int32_T rtu_In6[32], const int32_T rtu_In7[32], const int32_T rtu_In8[32],
  const int32_T rtu_In9[32], const int32_T rtu_In10[32], int32_T rty_u1[32],
  int32_T rty_u2[32], int32_T rty_u3[32], int32_T rty_u4[32], real32_T
  rty_omega_1[32], real32_T rty_omega_2[32], real32_T rty_omega_3[32], real32_T
  rty_omega_4[32])
{
  int64_T tmp;
  int64_T tmp_0;
  int32_T rtb_Add2[32];
  int32_T rtb_Add4[32];
  int32_T rtb_Add6[32];
  int32_T rtb_Add8[32];
  int32_T i;
  int32_T rtu_In4_0;
  int32_T rty_u3_0;
  int32_T rty_u4_0;
  for (i = 0; i < 32; i++) {
    rty_u3_0 = rtu_In9[i] * rtu_In5[i];
    rty_u3[i] = rty_u3_0;
    tmp = rtu_In6[i] * rtu_In3[i];
    tmp_0 = tmp + rty_u3_0;
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    rtu_In4_0 = rtu_In4[i];
    rty_u4_0 = rtu_In8[i] * rtu_In4_0;
    rty_u4[i] = rty_u4_0;
    tmp_0 -= rty_u4_0;
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    rtb_Add2[i] = (int32_T)tmp_0;
    rtu_In4_0 *= rtu_In7[i];
    rty_u2[i] = rtu_In4_0;
    tmp_0 = tmp - rtu_In4_0;
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    tmp_0 -= rty_u3_0;
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    rtb_Add4[i] = (int32_T)tmp_0;
    tmp_0 = tmp + rty_u4_0;
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    tmp_0 += rty_u3_0;
    if (tmp_0 > 2147483647LL) {
      tmp_0 = 2147483647LL;
    } else if (tmp_0 < -2147483648LL) {
      tmp_0 = -2147483648LL;
    }

    rtb_Add6[i] = (int32_T)tmp_0;
    tmp += rtu_In4_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    rty_u1[i] = (int32_T)tmp;
    tmp -= rty_u3_0;
    if (tmp > 2147483647LL) {
      tmp = 2147483647LL;
    } else if (tmp < -2147483648LL) {
      tmp = -2147483648LL;
    }

    rtb_Add8[i] = (int32_T)tmp;
  }

  Omega_Sqr(rtu_In1, rtu_In2, rtb_Add2, rtb_Add4, rtb_Add6, rtb_Add8, rtu_In10,
            rty_u1, rty_u2, rty_u3, rty_u4);
  Normalize(rtb_Add2, rtb_Add4, rtb_Add6, rtb_Add8, rty_omega_1, rty_omega_2,
            rty_omega_3, rty_omega_4);
}

void BLDC_step(RT_MODEL *const rtM, int32_T rtU_U1[32], int32_T rtU_U2[32],
               int32_T rtU_U3[32], int32_T rtU_U4[32], int32_T rtU_KT[32],
               int32_T rtU_I[32], int32_T rtU_Kd[32], int32_T rtU_Kd_4[32],
               int32_T rtU_KT_I[32], int32_T rtU_Kd_3[32], int32_T rtY_u1[32],
               int32_T rtY_u2[32], int32_T rtY_u3[32], int32_T rtY_u4[32],
               real32_T rtY_omega_1[32], real32_T rtY_omega_2[32], real32_T
               rtY_omega_3[32], real32_T rtY_omega_4[32])
{
  BLDC_Sp_Calc(rtU_I, rtU_KT, rtU_Kd_3, rtU_KT_I, rtU_Kd_4, rtU_U1, rtU_U2,
               rtU_U3, rtU_U4, rtU_Kd, rtY_u1, rtY_u2, rtY_u3, rtY_u4,
               rtY_omega_1, rtY_omega_2, rtY_omega_3, rtY_omega_4);
  UNUSED_PARAMETER(rtM);
}

void BLDC_initialize(RT_MODEL *const rtM, int32_T rtU_U1[32], int32_T rtU_U2[32],
                     int32_T rtU_U3[32], int32_T rtU_U4[32], int32_T rtU_KT[32],
                     int32_T rtU_I[32], int32_T rtU_Kd[32], int32_T rtU_Kd_4[32],
                     int32_T rtU_KT_I[32], int32_T rtU_Kd_3[32], int32_T rtY_u1
                     [32], int32_T rtY_u2[32], int32_T rtY_u3[32], int32_T
                     rtY_u4[32], real32_T rtY_omega_1[32], real32_T rtY_omega_2
                     [32], real32_T rtY_omega_3[32], real32_T rtY_omega_4[32])
{
  rtmSetErrorStatus(rtM, (NULL));
  (void)memset(&rtU_U1[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_U2[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_U3[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_U4[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_KT[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_I[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_Kd[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_Kd_4[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_KT_I[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtU_Kd_3[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtY_u1[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtY_u2[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtY_u3[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtY_u4[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&rtY_omega_1[0], 0, sizeof(real32_T) << 5U);
  (void)memset(&rtY_omega_2[0], 0, sizeof(real32_T) << 5U);
  (void)memset(&rtY_omega_3[0], 0, sizeof(real32_T) << 5U);
  (void)memset(&rtY_omega_4[0], 0, sizeof(real32_T) << 5U);
  UNUSED_PARAMETER(rtM);
}
