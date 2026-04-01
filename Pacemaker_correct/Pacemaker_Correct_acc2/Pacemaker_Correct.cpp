#include "Pacemaker_Correct.h"
#include "rtwtypes.h"
#include <math.h>
#include "Pacemaker_Correct_private.h"
#include <string.h>
#define Pacemaker_Co_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define Pacemaker_Corr_IN_AAI_Refactory ((uint8_T)2U)
#define Pacemaker_Corr_IN_VVI_Refactory ((uint8_T)10U)
#define Pacemaker_Correc_IN_AAI_Sensing ((uint8_T)3U)
#define Pacemaker_Correc_IN_VVI_Sensing ((uint8_T)11U)
#define Pacemaker_Correct_IN_AAI_Pacing ((uint8_T)1U)
#define Pacemaker_Correct_IN_AOO_Pacing ((uint8_T)5U)
#define Pacemaker_Correct_IN_MAIN      ((uint8_T)6U)
#define Pacemaker_Correct_IN_VOO_Pacing ((uint8_T)8U)
#define Pacemaker_Correct_IN_VVI_Pacing ((uint8_T)9U)
#define Pacemaker__IN_AOO_ChargingState ((uint8_T)4U)
#define Pacemaker__IN_VOO_ChargingState ((uint8_T)7U)

// Define the constant that was declared in the header file
const ConstB_Pacemaker_Correct_T Pacemaker_Correct_ConstB = {
  false,  // VENT_CMP_DETECT
  false   // ATR_CMP_DETECT
};

static void Pace_enter_atomic_VVI_Refactory(real_T
  Pacemaker_Correct_U_VENT_Amplitude, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out12, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15);
static void Pacemaker_Correct_VVI_Sensing(real_T
  Pacemaker_Correct_U_VENT_Amplitude, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out12, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15, DW_Pacemaker_Correct_T *Pacemaker_Correct_DW);
static void Pace_enter_atomic_AAI_Refactory(real_T *Pacemaker_Correct_Y_Out1,
  real_T *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out11, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15);
static void Pacemaker_Correct_AAI_Sensing(real_T *Pacemaker_Correct_Y_Out1,
  real_T *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out11, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15, DW_Pacemaker_Correct_T *Pacemaker_Correct_DW);
static void enter_atomic_AOO_ChargingState(real_T *Pacemaker_Correct_Y_Out1,
  real_T *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out14, real_T *Pacemaker_Correct_Y_Out15);
static void enter_atomic_VOO_ChargingState(real_T
  Pacemaker_Correct_U_VENT_Amplitude, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out14, real_T *Pacemaker_Correct_Y_Out15);
static void Pacemaker_Correct_MAIN(real_T Pacemaker_Correct_U_VENT_Amplitude,
  real_T *Pacemaker_Correct_Y_Out1, real_T *Pacemaker_Correct_Y_Out2, real_T
  *Pacemaker_Correct_Y_Out3, real_T *Pacemaker_Correct_Y_Out4, real_T
  *Pacemaker_Correct_Y_Out5, real_T *Pacemaker_Correct_Y_Out6, real_T
  *Pacemaker_Correct_Y_Out7, real_T *Pacemaker_Correct_Y_Out8, real_T
  *Pacemaker_Correct_Y_Out9, real_T *Pacemaker_Correct_Y_Out10, real_T
  *Pacemaker_Correct_Y_Out11, real_T *Pacemaker_Correct_Y_Out12, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15, B_Pacemaker_Correct_T *Pacemaker_Correct_B,
  DW_Pacemaker_Correct_T *Pacemaker_Correct_DW);
static void Pace_enter_atomic_VVI_Refactory(real_T
  Pacemaker_Correct_U_VENT_Amplitude, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out12, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15)
{
  *Pacemaker_Correct_Y_Out1 = 0.0;
  *Pacemaker_Correct_Y_Out2 = 0.0;
  *Pacemaker_Correct_Y_Out3 = Pacemaker_Correct_U_VENT_Amplitude / 5.0 * 100.0;
  *Pacemaker_Correct_Y_Out4 = 1.0;
  *Pacemaker_Correct_Y_Out5 = 1.0;
  *Pacemaker_Correct_Y_Out6 = 0.0;
  *Pacemaker_Correct_Y_Out7 = 0.0;
  *Pacemaker_Correct_Y_Out8 = 0.0;
  *Pacemaker_Correct_Y_Out9 = 1.0;
  *Pacemaker_Correct_Y_Out13 = 1.0;
  *Pacemaker_Correct_Y_Out12 = 70.0;
  *Pacemaker_Correct_Y_Out15 = 0.0;
  *Pacemaker_Correct_Y_Out14 = 1.0;
  *Pacemaker_Correct_Y_Out10 = 0.0;
}

static void Pacemaker_Correct_VVI_Sensing(real_T
  Pacemaker_Correct_U_VENT_Amplitude, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out12, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15, DW_Pacemaker_Correct_T *Pacemaker_Correct_DW)
{
  *Pacemaker_Correct_Y_Out15 = 0.0;
  *Pacemaker_Correct_Y_Out14 = 0.0;
  *Pacemaker_Correct_Y_Out10 = 1.0;
  if (Pacemaker_Correct_ConstB.VENT_CMP_DETECT) {
    Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
    Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
      Pacemaker_Corr_IN_VVI_Refactory;
    Pace_enter_atomic_VVI_Refactory(Pacemaker_Correct_U_VENT_Amplitude,
      Pacemaker_Correct_Y_Out1, Pacemaker_Correct_Y_Out2,
      Pacemaker_Correct_Y_Out3, Pacemaker_Correct_Y_Out4,
      Pacemaker_Correct_Y_Out5, Pacemaker_Correct_Y_Out6,
      Pacemaker_Correct_Y_Out7, Pacemaker_Correct_Y_Out8,
      Pacemaker_Correct_Y_Out9, Pacemaker_Correct_Y_Out10,
      Pacemaker_Correct_Y_Out12, Pacemaker_Correct_Y_Out13,
      Pacemaker_Correct_Y_Out14, Pacemaker_Correct_Y_Out15);
  } else if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000)
             >= 700U) {
    Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
    Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
      Pacemaker_Correct_IN_VVI_Pacing;
    *Pacemaker_Correct_Y_Out13 = 0.0;
    *Pacemaker_Correct_Y_Out4 = 0.0;
    *Pacemaker_Correct_Y_Out5 = 1.0;
    *Pacemaker_Correct_Y_Out8 = 0.0;
    *Pacemaker_Correct_Y_Out1 = 0.0;
    *Pacemaker_Correct_Y_Out6 = 0.0;
    *Pacemaker_Correct_Y_Out7 = 0.0;
    *Pacemaker_Correct_Y_Out2 = 1.0;
    *Pacemaker_Correct_Y_Out9 = 0.0;
    *Pacemaker_Correct_Y_Out3 = Pacemaker_Correct_U_VENT_Amplitude / 5.0 * 100.0;
    *Pacemaker_Correct_Y_Out15 = 1.0;
    *Pacemaker_Correct_Y_Out10 = 0.0;
    Pacemaker_Correct_DW->Flag = 1.0;
  }
}

static void Pace_enter_atomic_AAI_Refactory(real_T *Pacemaker_Correct_Y_Out1,
  real_T *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out11, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15)
{
  *Pacemaker_Correct_Y_Out1 = 0.0;
  *Pacemaker_Correct_Y_Out2 = 0.0;
  *Pacemaker_Correct_Y_Out3 = 60.0;
  *Pacemaker_Correct_Y_Out4 = 1.0;
  *Pacemaker_Correct_Y_Out5 = 1.0;
  *Pacemaker_Correct_Y_Out6 = 0.0;
  *Pacemaker_Correct_Y_Out7 = 0.0;
  *Pacemaker_Correct_Y_Out8 = 1.0;
  *Pacemaker_Correct_Y_Out9 = 0.0;
  *Pacemaker_Correct_Y_Out13 = 1.0;
  *Pacemaker_Correct_Y_Out11 = 70.0;
  *Pacemaker_Correct_Y_Out15 = 0.0;
  *Pacemaker_Correct_Y_Out14 = 1.0;
  *Pacemaker_Correct_Y_Out10 = 1.0;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static void Pacemaker_Correct_AAI_Sensing(real_T *Pacemaker_Correct_Y_Out1,
  real_T *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out11, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15, DW_Pacemaker_Correct_T *Pacemaker_Correct_DW)
{
  *Pacemaker_Correct_Y_Out15 = 0.0;
  *Pacemaker_Correct_Y_Out14 = 0.0;
  *Pacemaker_Correct_Y_Out10 = 1.0;
  if (Pacemaker_Correct_ConstB.ATR_CMP_DETECT) {
    Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
    Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
      Pacemaker_Corr_IN_AAI_Refactory;
    Pace_enter_atomic_AAI_Refactory(Pacemaker_Correct_Y_Out1,
      Pacemaker_Correct_Y_Out2, Pacemaker_Correct_Y_Out3,
      Pacemaker_Correct_Y_Out4, Pacemaker_Correct_Y_Out5,
      Pacemaker_Correct_Y_Out6, Pacemaker_Correct_Y_Out7,
      Pacemaker_Correct_Y_Out8, Pacemaker_Correct_Y_Out9,
      Pacemaker_Correct_Y_Out10, Pacemaker_Correct_Y_Out11,
      Pacemaker_Correct_Y_Out13, Pacemaker_Correct_Y_Out14,
      Pacemaker_Correct_Y_Out15);
  } else if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000)
             >= 700U) {
    Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
    Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
      Pacemaker_Correct_IN_AAI_Pacing;
    *Pacemaker_Correct_Y_Out13 = 0.0;
    *Pacemaker_Correct_Y_Out4 = 0.0;
    *Pacemaker_Correct_Y_Out5 = 1.0;
    *Pacemaker_Correct_Y_Out8 = 0.0;
    *Pacemaker_Correct_Y_Out1 = 1.0;
    *Pacemaker_Correct_Y_Out6 = 0.0;
    *Pacemaker_Correct_Y_Out7 = 0.0;
    *Pacemaker_Correct_Y_Out2 = 0.0;
    *Pacemaker_Correct_Y_Out9 = 0.0;
    *Pacemaker_Correct_Y_Out3 = 60.0;
    *Pacemaker_Correct_Y_Out15 = 1.0;
    *Pacemaker_Correct_Y_Out10 = 0.0;
    Pacemaker_Correct_DW->Flag = 1.0;
  }
}

static void enter_atomic_AOO_ChargingState(real_T *Pacemaker_Correct_Y_Out1,
  real_T *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out14, real_T *Pacemaker_Correct_Y_Out15)
{
  *Pacemaker_Correct_Y_Out1 = 0.0;
  *Pacemaker_Correct_Y_Out2 = 0.0;
  *Pacemaker_Correct_Y_Out3 = 60.0;
  *Pacemaker_Correct_Y_Out4 = 1.0;
  *Pacemaker_Correct_Y_Out5 = 1.0;
  *Pacemaker_Correct_Y_Out6 = 0.0;
  *Pacemaker_Correct_Y_Out7 = 0.0;
  *Pacemaker_Correct_Y_Out8 = 1.0;
  *Pacemaker_Correct_Y_Out9 = 0.0;
  *Pacemaker_Correct_Y_Out15 = 0.0;
  *Pacemaker_Correct_Y_Out14 = 1.0;
}

static void enter_atomic_VOO_ChargingState(real_T
  Pacemaker_Correct_U_VENT_Amplitude, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out14, real_T *Pacemaker_Correct_Y_Out15)
{
  *Pacemaker_Correct_Y_Out1 = 0.0;
  *Pacemaker_Correct_Y_Out2 = 0.0;
  *Pacemaker_Correct_Y_Out3 = Pacemaker_Correct_U_VENT_Amplitude / 5.0 * 100.0;
  *Pacemaker_Correct_Y_Out4 = 1.0;
  *Pacemaker_Correct_Y_Out5 = 1.0;
  *Pacemaker_Correct_Y_Out6 = 0.0;
  *Pacemaker_Correct_Y_Out7 = 0.0;
  *Pacemaker_Correct_Y_Out8 = 0.0;
  *Pacemaker_Correct_Y_Out9 = 1.0;
  *Pacemaker_Correct_Y_Out15 = 0.0;
  *Pacemaker_Correct_Y_Out14 = 1.0;
}

static void Pacemaker_Correct_MAIN(real_T Pacemaker_Correct_U_VENT_Amplitude,
  real_T *Pacemaker_Correct_Y_Out1, real_T *Pacemaker_Correct_Y_Out2, real_T
  *Pacemaker_Correct_Y_Out3, real_T *Pacemaker_Correct_Y_Out4, real_T
  *Pacemaker_Correct_Y_Out5, real_T *Pacemaker_Correct_Y_Out6, real_T
  *Pacemaker_Correct_Y_Out7, real_T *Pacemaker_Correct_Y_Out8, real_T
  *Pacemaker_Correct_Y_Out9, real_T *Pacemaker_Correct_Y_Out10, real_T
  *Pacemaker_Correct_Y_Out11, real_T *Pacemaker_Correct_Y_Out12, real_T
  *Pacemaker_Correct_Y_Out13, real_T *Pacemaker_Correct_Y_Out14, real_T
  *Pacemaker_Correct_Y_Out15, B_Pacemaker_Correct_T *Pacemaker_Correct_B,
  DW_Pacemaker_Correct_T *Pacemaker_Correct_DW)
{
  *Pacemaker_Correct_Y_Out4 = 0.0;
  *Pacemaker_Correct_Y_Out2 = 0.0;
  *Pacemaker_Correct_Y_Out1 = 0.0;
  *Pacemaker_Correct_Y_Out5 = 0.0;
  *Pacemaker_Correct_Y_Out8 = 0.0;
  *Pacemaker_Correct_Y_Out9 = 0.0;
  *Pacemaker_Correct_Y_Out6 = 0.0;
  *Pacemaker_Correct_Y_Out7 = 0.0;
  *Pacemaker_Correct_Y_Out13 = 0.0;
  *Pacemaker_Correct_Y_Out14 = 0.0;
  *Pacemaker_Correct_Y_Out15 = 0.0;
  if (Pacemaker_Correct_B->Floor == 0.0) {
    Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
    Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
      Pacemaker__IN_VOO_ChargingState;
    enter_atomic_VOO_ChargingState(Pacemaker_Correct_U_VENT_Amplitude,
      Pacemaker_Correct_Y_Out1, Pacemaker_Correct_Y_Out2,
      Pacemaker_Correct_Y_Out3, Pacemaker_Correct_Y_Out4,
      Pacemaker_Correct_Y_Out5, Pacemaker_Correct_Y_Out6,
      Pacemaker_Correct_Y_Out7, Pacemaker_Correct_Y_Out8,
      Pacemaker_Correct_Y_Out9, Pacemaker_Correct_Y_Out14,
      Pacemaker_Correct_Y_Out15);
  } else if (Pacemaker_Correct_B->Floor == 2.0) {
    Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
    Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
      Pacemaker_Corr_IN_VVI_Refactory;
    Pace_enter_atomic_VVI_Refactory(Pacemaker_Correct_U_VENT_Amplitude,
      Pacemaker_Correct_Y_Out1, Pacemaker_Correct_Y_Out2,
      Pacemaker_Correct_Y_Out3, Pacemaker_Correct_Y_Out4,
      Pacemaker_Correct_Y_Out5, Pacemaker_Correct_Y_Out6,
      Pacemaker_Correct_Y_Out7, Pacemaker_Correct_Y_Out8,
      Pacemaker_Correct_Y_Out9, Pacemaker_Correct_Y_Out10,
      Pacemaker_Correct_Y_Out12, Pacemaker_Correct_Y_Out13,
      Pacemaker_Correct_Y_Out14, Pacemaker_Correct_Y_Out15);
  } else if (Pacemaker_Correct_B->Floor == 3.0) {
    Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
    Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
      Pacemaker_Corr_IN_AAI_Refactory;
    Pace_enter_atomic_AAI_Refactory(Pacemaker_Correct_Y_Out1,
      Pacemaker_Correct_Y_Out2, Pacemaker_Correct_Y_Out3,
      Pacemaker_Correct_Y_Out4, Pacemaker_Correct_Y_Out5,
      Pacemaker_Correct_Y_Out6, Pacemaker_Correct_Y_Out7,
      Pacemaker_Correct_Y_Out8, Pacemaker_Correct_Y_Out9,
      Pacemaker_Correct_Y_Out10, Pacemaker_Correct_Y_Out11,
      Pacemaker_Correct_Y_Out13, Pacemaker_Correct_Y_Out14,
      Pacemaker_Correct_Y_Out15);
  } else if (Pacemaker_Correct_B->Floor == 1.0) {
    Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
    Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
      Pacemaker__IN_AOO_ChargingState;
    enter_atomic_AOO_ChargingState(Pacemaker_Correct_Y_Out1,
      Pacemaker_Correct_Y_Out2, Pacemaker_Correct_Y_Out3,
      Pacemaker_Correct_Y_Out4, Pacemaker_Correct_Y_Out5,
      Pacemaker_Correct_Y_Out6, Pacemaker_Correct_Y_Out7,
      Pacemaker_Correct_Y_Out8, Pacemaker_Correct_Y_Out9,
      Pacemaker_Correct_Y_Out14, Pacemaker_Correct_Y_Out15);
  }
}

void Pacemaker_Correct_step(RT_MODEL_Pacemaker_Correct_T *const
  Pacemaker_Correct_M, real_T Pacemaker_Correct_U_VENT_Amplitude, real_T
  Pacemaker_Correct_U_Mode, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out11, real_T
  *Pacemaker_Correct_Y_Out12, real_T *Pacemaker_Correct_Y_Out13, real_T
  *Pacemaker_Correct_Y_Out14, real_T *Pacemaker_Correct_Y_Out15)
{
  B_Pacemaker_Correct_T *Pacemaker_Correct_B = Pacemaker_Correct_M->blockIO;
  DW_Pacemaker_Correct_T *Pacemaker_Correct_DW = Pacemaker_Correct_M->dwork;
  real_T tmp_0;
  uint16_T tmp;
  Pacemaker_Correct_B->Floor = floor(Pacemaker_Correct_U_Mode);
  if (Pacemaker_Correct_DW->temporalCounter_i1 < MAX_uint32_T) {
    Pacemaker_Correct_DW->temporalCounter_i1++;
  }

  if (Pacemaker_Correct_DW->is_active_c3_Pacemaker_Correct == 0) {
    Pacemaker_Correct_DW->is_active_c3_Pacemaker_Correct = 1U;
    Pacemaker_Correct_DW->is_c3_Pacemaker_Correct = Pacemaker_Correct_IN_MAIN;
    *Pacemaker_Correct_Y_Out4 = 0.0;
    *Pacemaker_Correct_Y_Out2 = 0.0;
    *Pacemaker_Correct_Y_Out1 = 0.0;
    *Pacemaker_Correct_Y_Out5 = 0.0;
    *Pacemaker_Correct_Y_Out8 = 0.0;
    *Pacemaker_Correct_Y_Out9 = 0.0;
    *Pacemaker_Correct_Y_Out6 = 0.0;
    *Pacemaker_Correct_Y_Out7 = 0.0;
    *Pacemaker_Correct_Y_Out13 = 0.0;
    *Pacemaker_Correct_Y_Out14 = 0.0;
    *Pacemaker_Correct_Y_Out15 = 0.0;
    Pacemaker_Correct_DW->Flag = 0.0;
  } else {
    switch (Pacemaker_Correct_DW->is_c3_Pacemaker_Correct) {
     case Pacemaker_Correct_IN_AAI_Pacing:
      *Pacemaker_Correct_Y_Out13 = 0.0;
      *Pacemaker_Correct_Y_Out4 = 0.0;
      *Pacemaker_Correct_Y_Out5 = 1.0;
      *Pacemaker_Correct_Y_Out8 = 0.0;
      *Pacemaker_Correct_Y_Out1 = 1.0;
      *Pacemaker_Correct_Y_Out6 = 0.0;
      *Pacemaker_Correct_Y_Out7 = 0.0;
      *Pacemaker_Correct_Y_Out2 = 0.0;
      *Pacemaker_Correct_Y_Out9 = 0.0;
      *Pacemaker_Correct_Y_Out15 = 1.0;
      *Pacemaker_Correct_Y_Out14 = 0.0;
      *Pacemaker_Correct_Y_Out10 = 0.0;
      if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000) >=
          1U) {
        Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
        Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
          Pacemaker_Corr_IN_AAI_Refactory;
        Pace_enter_atomic_AAI_Refactory(Pacemaker_Correct_Y_Out1,
          Pacemaker_Correct_Y_Out2, Pacemaker_Correct_Y_Out3,
          Pacemaker_Correct_Y_Out4, Pacemaker_Correct_Y_Out5,
          Pacemaker_Correct_Y_Out6, Pacemaker_Correct_Y_Out7,
          Pacemaker_Correct_Y_Out8, Pacemaker_Correct_Y_Out9,
          Pacemaker_Correct_Y_Out10, Pacemaker_Correct_Y_Out11,
          Pacemaker_Correct_Y_Out13, Pacemaker_Correct_Y_Out14,
          Pacemaker_Correct_Y_Out15);
      }
      break;

     case Pacemaker_Corr_IN_AAI_Refactory:
      *Pacemaker_Correct_Y_Out1 = 0.0;
      *Pacemaker_Correct_Y_Out2 = 0.0;
      *Pacemaker_Correct_Y_Out4 = 1.0;
      *Pacemaker_Correct_Y_Out5 = 1.0;
      *Pacemaker_Correct_Y_Out6 = 0.0;
      *Pacemaker_Correct_Y_Out7 = 0.0;
      *Pacemaker_Correct_Y_Out8 = 1.0;
      *Pacemaker_Correct_Y_Out9 = 0.0;
      *Pacemaker_Correct_Y_Out13 = 1.0;
      *Pacemaker_Correct_Y_Out15 = 0.0;
      *Pacemaker_Correct_Y_Out14 = 1.0;
      *Pacemaker_Correct_Y_Out10 = 1.0;
      tmp_0 = rt_roundd_snf(300.0 - Pacemaker_Correct_DW->Flag);
      if (tmp_0 < 65536.0) {
        if (tmp_0 >= 0.0) {
          tmp = (uint16_T)tmp_0;
        } else {
          tmp = 0U;
        }
      } else {
        tmp = MAX_uint16_T;
      }

      if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000) >=
          tmp) {
        Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
        Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
          Pacemaker_Correc_IN_AAI_Sensing;
        *Pacemaker_Correct_Y_Out14 = 0.0;
        Pacemaker_Correct_DW->Flag = 0.0;
      }
      break;

     case Pacemaker_Correc_IN_AAI_Sensing:
      Pacemaker_Correct_AAI_Sensing(Pacemaker_Correct_Y_Out1,
        Pacemaker_Correct_Y_Out2, Pacemaker_Correct_Y_Out3,
        Pacemaker_Correct_Y_Out4, Pacemaker_Correct_Y_Out5,
        Pacemaker_Correct_Y_Out6, Pacemaker_Correct_Y_Out7,
        Pacemaker_Correct_Y_Out8, Pacemaker_Correct_Y_Out9,
        Pacemaker_Correct_Y_Out10, Pacemaker_Correct_Y_Out11,
        Pacemaker_Correct_Y_Out13, Pacemaker_Correct_Y_Out14,
        Pacemaker_Correct_Y_Out15, Pacemaker_Correct_DW);
      break;

     case Pacemaker__IN_AOO_ChargingState:
      *Pacemaker_Correct_Y_Out1 = 0.0;
      *Pacemaker_Correct_Y_Out2 = 0.0;
      *Pacemaker_Correct_Y_Out4 = 1.0;
      *Pacemaker_Correct_Y_Out5 = 1.0;
      *Pacemaker_Correct_Y_Out6 = 0.0;
      *Pacemaker_Correct_Y_Out7 = 0.0;
      *Pacemaker_Correct_Y_Out8 = 1.0;
      *Pacemaker_Correct_Y_Out9 = 0.0;
      *Pacemaker_Correct_Y_Out15 = 0.0;
      *Pacemaker_Correct_Y_Out14 = 1.0;
      if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000) >=
          999U) {
        Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
        Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
          Pacemaker_Correct_IN_AOO_Pacing;
        *Pacemaker_Correct_Y_Out4 = 0.0;
        *Pacemaker_Correct_Y_Out8 = 0.0;
        *Pacemaker_Correct_Y_Out1 = 1.0;
        *Pacemaker_Correct_Y_Out3 = 60.0;
        *Pacemaker_Correct_Y_Out15 = 1.0;
        *Pacemaker_Correct_Y_Out14 = 0.0;
      }
      break;

     case Pacemaker_Correct_IN_AOO_Pacing:
      *Pacemaker_Correct_Y_Out4 = 0.0;
      *Pacemaker_Correct_Y_Out5 = 1.0;
      *Pacemaker_Correct_Y_Out8 = 0.0;
      *Pacemaker_Correct_Y_Out1 = 1.0;
      *Pacemaker_Correct_Y_Out6 = 0.0;
      *Pacemaker_Correct_Y_Out7 = 0.0;
      *Pacemaker_Correct_Y_Out2 = 0.0;
      *Pacemaker_Correct_Y_Out9 = 0.0;
      *Pacemaker_Correct_Y_Out15 = 1.0;
      *Pacemaker_Correct_Y_Out14 = 0.0;
      if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000) >=
          1U) {
        Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
        Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
          Pacemaker__IN_AOO_ChargingState;
        enter_atomic_AOO_ChargingState(Pacemaker_Correct_Y_Out1,
          Pacemaker_Correct_Y_Out2, Pacemaker_Correct_Y_Out3,
          Pacemaker_Correct_Y_Out4, Pacemaker_Correct_Y_Out5,
          Pacemaker_Correct_Y_Out6, Pacemaker_Correct_Y_Out7,
          Pacemaker_Correct_Y_Out8, Pacemaker_Correct_Y_Out9,
          Pacemaker_Correct_Y_Out14, Pacemaker_Correct_Y_Out15);
      }
      break;

     case Pacemaker_Correct_IN_MAIN:
      Pacemaker_Correct_MAIN(Pacemaker_Correct_U_VENT_Amplitude,
        Pacemaker_Correct_Y_Out1, Pacemaker_Correct_Y_Out2,
        Pacemaker_Correct_Y_Out3, Pacemaker_Correct_Y_Out4,
        Pacemaker_Correct_Y_Out5, Pacemaker_Correct_Y_Out6,
        Pacemaker_Correct_Y_Out7, Pacemaker_Correct_Y_Out8,
        Pacemaker_Correct_Y_Out9, Pacemaker_Correct_Y_Out10,
        Pacemaker_Correct_Y_Out11, Pacemaker_Correct_Y_Out12,
        Pacemaker_Correct_Y_Out13, Pacemaker_Correct_Y_Out14,
        Pacemaker_Correct_Y_Out15, Pacemaker_Correct_B, Pacemaker_Correct_DW);
      break;

     case Pacemaker__IN_VOO_ChargingState:
      *Pacemaker_Correct_Y_Out1 = 0.0;
      *Pacemaker_Correct_Y_Out2 = 0.0;
      *Pacemaker_Correct_Y_Out4 = 1.0;
      *Pacemaker_Correct_Y_Out5 = 1.0;
      *Pacemaker_Correct_Y_Out6 = 0.0;
      *Pacemaker_Correct_Y_Out7 = 0.0;
      *Pacemaker_Correct_Y_Out8 = 0.0;
      *Pacemaker_Correct_Y_Out9 = 1.0;
      *Pacemaker_Correct_Y_Out15 = 0.0;
      *Pacemaker_Correct_Y_Out14 = 1.0;
      if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000) >=
          998U) {
        Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
        Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
          Pacemaker_Correct_IN_VOO_Pacing;
        *Pacemaker_Correct_Y_Out4 = 0.0;
        *Pacemaker_Correct_Y_Out2 = 1.0;
        *Pacemaker_Correct_Y_Out9 = 0.0;
        *Pacemaker_Correct_Y_Out3 = Pacemaker_Correct_U_VENT_Amplitude / 5.0 *
          100.0;
        *Pacemaker_Correct_Y_Out15 = 1.0;
        *Pacemaker_Correct_Y_Out14 = 0.0;
      }
      break;

     case Pacemaker_Correct_IN_VOO_Pacing:
      *Pacemaker_Correct_Y_Out4 = 0.0;
      *Pacemaker_Correct_Y_Out5 = 1.0;
      *Pacemaker_Correct_Y_Out8 = 0.0;
      *Pacemaker_Correct_Y_Out1 = 0.0;
      *Pacemaker_Correct_Y_Out6 = 0.0;
      *Pacemaker_Correct_Y_Out7 = 0.0;
      *Pacemaker_Correct_Y_Out2 = 1.0;
      *Pacemaker_Correct_Y_Out9 = 0.0;
      *Pacemaker_Correct_Y_Out15 = 1.0;
      *Pacemaker_Correct_Y_Out14 = 0.0;
      if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000) >=
          2U) {
        Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
        Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
          Pacemaker__IN_VOO_ChargingState;
        enter_atomic_VOO_ChargingState(Pacemaker_Correct_U_VENT_Amplitude,
          Pacemaker_Correct_Y_Out1, Pacemaker_Correct_Y_Out2,
          Pacemaker_Correct_Y_Out3, Pacemaker_Correct_Y_Out4,
          Pacemaker_Correct_Y_Out5, Pacemaker_Correct_Y_Out6,
          Pacemaker_Correct_Y_Out7, Pacemaker_Correct_Y_Out8,
          Pacemaker_Correct_Y_Out9, Pacemaker_Correct_Y_Out14,
          Pacemaker_Correct_Y_Out15);
      }
      break;

     case Pacemaker_Correct_IN_VVI_Pacing:
      *Pacemaker_Correct_Y_Out13 = 0.0;
      *Pacemaker_Correct_Y_Out4 = 0.0;
      *Pacemaker_Correct_Y_Out5 = 1.0;
      *Pacemaker_Correct_Y_Out8 = 0.0;
      *Pacemaker_Correct_Y_Out1 = 0.0;
      *Pacemaker_Correct_Y_Out6 = 0.0;
      *Pacemaker_Correct_Y_Out7 = 0.0;
      *Pacemaker_Correct_Y_Out2 = 1.0;
      *Pacemaker_Correct_Y_Out9 = 0.0;
      *Pacemaker_Correct_Y_Out15 = 1.0;
      *Pacemaker_Correct_Y_Out14 = 0.0;
      *Pacemaker_Correct_Y_Out10 = 0.0;
      if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000) >=
          2U) {
        Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
        Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
          Pacemaker_Corr_IN_VVI_Refactory;
        Pace_enter_atomic_VVI_Refactory(Pacemaker_Correct_U_VENT_Amplitude,
          Pacemaker_Correct_Y_Out1, Pacemaker_Correct_Y_Out2,
          Pacemaker_Correct_Y_Out3, Pacemaker_Correct_Y_Out4,
          Pacemaker_Correct_Y_Out5, Pacemaker_Correct_Y_Out6,
          Pacemaker_Correct_Y_Out7, Pacemaker_Correct_Y_Out8,
          Pacemaker_Correct_Y_Out9, Pacemaker_Correct_Y_Out10,
          Pacemaker_Correct_Y_Out12, Pacemaker_Correct_Y_Out13,
          Pacemaker_Correct_Y_Out14, Pacemaker_Correct_Y_Out15);
      }
      break;

     case Pacemaker_Corr_IN_VVI_Refactory:
      *Pacemaker_Correct_Y_Out1 = 0.0;
      *Pacemaker_Correct_Y_Out2 = 0.0;
      *Pacemaker_Correct_Y_Out4 = 1.0;
      *Pacemaker_Correct_Y_Out5 = 1.0;
      *Pacemaker_Correct_Y_Out6 = 0.0;
      *Pacemaker_Correct_Y_Out7 = 0.0;
      *Pacemaker_Correct_Y_Out8 = 0.0;
      *Pacemaker_Correct_Y_Out9 = 1.0;
      *Pacemaker_Correct_Y_Out13 = 1.0;
      *Pacemaker_Correct_Y_Out15 = 0.0;
      *Pacemaker_Correct_Y_Out14 = 1.0;
      *Pacemaker_Correct_Y_Out10 = 0.0;
      if ((uint32_T)((int32_T)Pacemaker_Correct_DW->temporalCounter_i1 * 1000) >=
          (uint32_T)ceil(300.0 - 2.0 * Pacemaker_Correct_DW->Flag)) {
        Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
        Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
          Pacemaker_Correc_IN_VVI_Sensing;
        *Pacemaker_Correct_Y_Out14 = 0.0;
        *Pacemaker_Correct_Y_Out10 = 1.0;
        Pacemaker_Correct_DW->Flag = 0.0;
      }
      break;

     default:
      Pacemaker_Correct_VVI_Sensing(Pacemaker_Correct_U_VENT_Amplitude,
        Pacemaker_Correct_Y_Out1, Pacemaker_Correct_Y_Out2,
        Pacemaker_Correct_Y_Out3, Pacemaker_Correct_Y_Out4,
        Pacemaker_Correct_Y_Out5, Pacemaker_Correct_Y_Out6,
        Pacemaker_Correct_Y_Out7, Pacemaker_Correct_Y_Out8,
        Pacemaker_Correct_Y_Out9, Pacemaker_Correct_Y_Out10,
        Pacemaker_Correct_Y_Out12, Pacemaker_Correct_Y_Out13,
        Pacemaker_Correct_Y_Out14, Pacemaker_Correct_Y_Out15,
        Pacemaker_Correct_DW);
      break;
    }
  }
}

void Pacemaker_Correct_initialize(RT_MODEL_Pacemaker_Correct_T *const
  Pacemaker_Correct_M, real_T *Pacemaker_Correct_U_VENT_Amplitude, real_T
  *Pacemaker_Correct_U_Mode, real_T *Pacemaker_Correct_Y_Out1, real_T
  *Pacemaker_Correct_Y_Out2, real_T *Pacemaker_Correct_Y_Out3, real_T
  *Pacemaker_Correct_Y_Out4, real_T *Pacemaker_Correct_Y_Out5, real_T
  *Pacemaker_Correct_Y_Out6, real_T *Pacemaker_Correct_Y_Out7, real_T
  *Pacemaker_Correct_Y_Out8, real_T *Pacemaker_Correct_Y_Out9, real_T
  *Pacemaker_Correct_Y_Out10, real_T *Pacemaker_Correct_Y_Out11, real_T
  *Pacemaker_Correct_Y_Out12, real_T *Pacemaker_Correct_Y_Out13, real_T
  *Pacemaker_Correct_Y_Out14, real_T *Pacemaker_Correct_Y_Out15)
{
  DW_Pacemaker_Correct_T *Pacemaker_Correct_DW = Pacemaker_Correct_M->dwork;
  B_Pacemaker_Correct_T *Pacemaker_Correct_B = Pacemaker_Correct_M->blockIO;
  (void) memset(((void *) Pacemaker_Correct_B), 0,
                sizeof(B_Pacemaker_Correct_T));
  (void) memset((void *)Pacemaker_Correct_DW, 0,
                sizeof(DW_Pacemaker_Correct_T));
  *Pacemaker_Correct_U_VENT_Amplitude = 0.0;
  *Pacemaker_Correct_U_Mode = 0.0;
  *Pacemaker_Correct_Y_Out1 = 0.0;
  *Pacemaker_Correct_Y_Out2 = 0.0;
  *Pacemaker_Correct_Y_Out3 = 0.0;
  *Pacemaker_Correct_Y_Out4 = 0.0;
  *Pacemaker_Correct_Y_Out5 = 0.0;
  *Pacemaker_Correct_Y_Out6 = 0.0;
  *Pacemaker_Correct_Y_Out7 = 0.0;
  *Pacemaker_Correct_Y_Out8 = 0.0;
  *Pacemaker_Correct_Y_Out9 = 0.0;
  *Pacemaker_Correct_Y_Out10 = 0.0;
  *Pacemaker_Correct_Y_Out11 = 0.0;
  *Pacemaker_Correct_Y_Out12 = 0.0;
  *Pacemaker_Correct_Y_Out13 = 0.0;
  *Pacemaker_Correct_Y_Out14 = 0.0;
  *Pacemaker_Correct_Y_Out15 = 0.0;
  Pacemaker_Correct_DW->temporalCounter_i1 = 0U;
  *Pacemaker_Correct_Y_Out1 = 0.0;
  *Pacemaker_Correct_Y_Out2 = 0.0;
  *Pacemaker_Correct_Y_Out3 = 0.0;
  *Pacemaker_Correct_Y_Out4 = 0.0;
  *Pacemaker_Correct_Y_Out5 = 0.0;
  *Pacemaker_Correct_Y_Out6 = 0.0;
  *Pacemaker_Correct_Y_Out7 = 0.0;
  *Pacemaker_Correct_Y_Out8 = 0.0;
  *Pacemaker_Correct_Y_Out9 = 0.0;
  *Pacemaker_Correct_Y_Out13 = 0.0;
  *Pacemaker_Correct_Y_Out14 = 0.0;
  *Pacemaker_Correct_Y_Out15 = 0.0;
  *Pacemaker_Correct_Y_Out10 = 0.0;
  Pacemaker_Correct_DW->Flag = 0.0;
  *Pacemaker_Correct_Y_Out11 = 0.0;
  *Pacemaker_Correct_Y_Out12 = 0.0;
  Pacemaker_Correct_DW->is_active_c3_Pacemaker_Correct = 0U;
  Pacemaker_Correct_DW->is_c3_Pacemaker_Correct =
    Pacemaker_Co_IN_NO_ACTIVE_CHILD;
}

void Pacemaker_Correct_terminate(RT_MODEL_Pacemaker_Correct_T *const
  Pacemaker_Correct_M)
{
  UNUSED_PARAMETER(Pacemaker_Correct_M);
}
