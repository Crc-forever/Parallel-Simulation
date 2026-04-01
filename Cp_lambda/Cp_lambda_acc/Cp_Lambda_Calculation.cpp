/*
 * File: Cp_Lambda_Calculation.c
 *
 * Code generated for Simulink model 'Cp_Lambda_Calculation'.
 *
 * Model version                  : 23.1
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Fri Mar 13 17:07:06 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Cp_Lambda_Calculation.h"
#include <math.h>
#include "rtwtypes.h"
#include <stddef.h>
#define NumBitsPerChar                 8U

extern real_T rt_powd_snf(real_T u0, real_T u1);
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

#define NOT_USING_NONFINITE_LITERALS   1

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T tmp;
  real_T tmp_0;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void Cp_Lambda_Calculation_step(RT_MODEL *const rtM, real_T rtU_GeneratorSpeed,
  real_T rtU_Wind, real_T *rtY_Percentage, real_T *rtY_Out1, real_T *rtY_Out2,
  real_T *rtY_Out3, real_T *rtY_Out4, real_T *rtY_PercentagePowerDelivered)
{
  real_T rtb_Divide1;
  real_T rtb_Fcn1;
  real_T rtb_Fcn1_o;
  real_T rtb_lambda_nom;

  /* Gain: '<S1>/1//wind_base' incorporates:
   *  Inport: '<Root>/Wind'
   */
  rtb_lambda_nom = 0.083333333333333329 * rtU_Wind;

  /* Fcn: '<S1>/wind_speed^3' */
  rtb_Divide1 = rt_powd_snf(rtb_lambda_nom, 3.0);

  /* Saturate: '<S1>/Avoid division by zero ' */
  if (rtb_lambda_nom > 1.0E+6) {
    rtb_lambda_nom = 1.0E+6;
  } else if (rtb_lambda_nom < 1.0E-6) {
    rtb_lambda_nom = 1.0E-6;
  }

  /* Gain: '<S1>/lambda_nom' incorporates:
   *  Gain: '<S1>/1//speed_nom '
   *  Inport: '<Root>/Generator Speed'
   *  Product: '<S1>/Product'
   *  Saturate: '<S1>/Avoid division by zero '
   */
  rtb_lambda_nom = 1.0 / rtb_lambda_nom * (0.83333333333333337 *
    rtU_GeneratorSpeed) * 8.1;

  /* Saturate: '<S1>/Saturation1' */
  if (rtb_lambda_nom <= 1.0E-6) {
    rtb_Fcn1 = 1.0E-6;
  } else {
    rtb_Fcn1 = rtb_lambda_nom;
  }

  /* End of Saturate: '<S1>/Saturation1' */

  /* Fcn: '<S2>/Fcn' incorporates:
   *  Constant: '<S1>/Pitch_Angle'
   */
  rtb_Fcn1_o = 1.0 / (1.0 / rtb_Fcn1 - 0.035);

  /* Fcn: '<S2>/Fcn1' */
  rtb_Fcn1 = (116.0 / rtb_Fcn1_o - 5.0) * 0.5176 * exp(-21.0 / rtb_Fcn1_o) +
    0.0068 * rtb_Fcn1;

  /* Outport: '<Root>/Percentage' incorporates:
   *  Fcn: '<S1>/wind_speed^3'
   *  Gain: '<S1>/1//cp_nom'
   *  Product: '<S1>/Product '
   */
  *rtY_Percentage = 2.0833333333333335 * rtb_Fcn1 * rtb_Divide1;

  /* Product: '<S1>/Divide1' incorporates:
   *  Constant: '<S1>/K_del'
   *  Fcn: '<S1>/Fcn'
   *  Product: '<S1>/Divide'
   */
  rtb_Divide1 = 1.0 / (rtb_Fcn1 / rt_powd_snf(rtb_lambda_nom, 3.0)) * 0.9 *
    0.00081042783571606142;

  /* Fcn: '<S1>/Fcn1' */
  if (rtb_Divide1 < 0.0) {
    rtb_Divide1 = -rt_powd_snf(-rtb_Divide1, 0.33333333333333331);
  } else {
    rtb_Divide1 = rt_powd_snf(rtb_Divide1, 0.33333333333333331);
  }

  /* Outport: '<Root>/Out1' incorporates:
   *  Fcn: '<S1>/Fcn1'
   */
  *rtY_Out1 = rtb_Divide1;

  /* Outport: '<Root>/Out4' incorporates:
   *  Constant: '<S1>/rotor speed at MPPT'
   *  Fcn: '<S1>/Fcn1'
   *  Product: '<S1>/Product1'
   */
  *rtY_Out4 = 1.2 * rtb_Divide1;

  /* Outport: '<Root>/Out2' */
  *rtY_Out2 = rtb_Fcn1;

  /* Outport: '<Root>/Percentage Power Delivered' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Product: '<Root>/Divide'
   *  Product: '<Root>/Product'
   */
  *rtY_PercentagePowerDelivered = rtb_Fcn1 / 0.48 * 100.0;

  /* Outport: '<Root>/Out3' */
  *rtY_Out3 = rtb_lambda_nom;
  UNUSED_PARAMETER(rtM);
}

/* Model initialize function */
void Cp_Lambda_Calculation_initialize(RT_MODEL *const rtM, real_T
  *rtU_GeneratorSpeed, real_T *rtU_Wind, real_T *rtY_Percentage, real_T
  *rtY_Out1, real_T *rtY_Out2, real_T *rtY_Out3, real_T *rtY_Out4, real_T
  *rtY_PercentagePowerDelivered)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* external inputs */
  *rtU_GeneratorSpeed = 0.0;
  *rtU_Wind = 0.0;

  /* external outputs */
  *rtY_Percentage = 0.0;
  *rtY_Out1 = 0.0;
  *rtY_Out2 = 0.0;
  *rtY_Out3 = 0.0;
  *rtY_Out4 = 0.0;
  *rtY_PercentagePowerDelivered = 0.0;
  UNUSED_PARAMETER(rtM);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
