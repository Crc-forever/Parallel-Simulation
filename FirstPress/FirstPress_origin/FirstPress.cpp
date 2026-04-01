#include "FirstPress.h"
#include "rtwtypes.h"
#include "FirstPress_private.h"
#include <string.h>

void FirstPress_First_Pass_Logic_P1(const int32_T rtu_FIRST_PASS[32], const
  int16_T rtu_AUTO_MANUAL_SWITCH[32], boolean_T rty_INIT_JET_SELECT[32],
  boolean_T rty_INIT_STATE_ERROR[32])
{
  int32_T i;
  for (i = 0; i < 32; i++) {
    int32_T q0;
    int32_T qY;
    int32_T rtu_FIRST_PASS_0;
    int16_T rtu_AUTO_MANUAL_SWITCH_0;
    rtu_AUTO_MANUAL_SWITCH_0 = rtu_AUTO_MANUAL_SWITCH[i];
    rtu_FIRST_PASS_0 = rtu_FIRST_PASS[i];
    if ((rtu_AUTO_MANUAL_SWITCH_0 >= 0) && (rtu_FIRST_PASS_0 <
         rtu_AUTO_MANUAL_SWITCH_0 - MAX_int32_T)) {
      qY = MAX_int32_T;
    } else if ((rtu_AUTO_MANUAL_SWITCH_0 < 0) && (rtu_FIRST_PASS_0 >
                rtu_AUTO_MANUAL_SWITCH_0 - MIN_int32_T)) {
      qY = MIN_int32_T;
    } else {
      qY = rtu_AUTO_MANUAL_SWITCH_0 - rtu_FIRST_PASS_0;
    }

    q0 = rtu_FIRST_PASS_0 * qY;
    if ((qY < 0) && (rtu_FIRST_PASS_0 < MIN_int32_T - qY)) {
      qY = MIN_int32_T;
    } else if ((qY > 0) && (rtu_FIRST_PASS_0 > MAX_int32_T - qY)) {
      qY = MAX_int32_T;
    } else {
      qY += rtu_FIRST_PASS_0;
    }

    if ((q0 < 0) && (qY < MIN_int32_T - q0)) {
      qY = MIN_int32_T;
    } else if ((q0 > 0) && (qY > MAX_int32_T - q0)) {
      qY = MAX_int32_T;
    } else {
      qY += q0;
    }

    rtu_FIRST_PASS_0 *= rtu_AUTO_MANUAL_SWITCH_0;
    if ((qY < 0) && (rtu_FIRST_PASS_0 < MIN_int32_T - qY)) {
      qY = MIN_int32_T;
    } else if ((qY > 0) && (rtu_FIRST_PASS_0 > MAX_int32_T - qY)) {
      qY = MAX_int32_T;
    } else {
      qY += rtu_FIRST_PASS_0;
    }

    if ((rtu_AUTO_MANUAL_SWITCH_0 < 0) && (qY < MIN_int32_T
         - rtu_AUTO_MANUAL_SWITCH_0)) {
      q0 = MIN_int32_T;
    } else if ((rtu_AUTO_MANUAL_SWITCH_0 > 0) && (qY > MAX_int32_T
                - rtu_AUTO_MANUAL_SWITCH_0)) {
      q0 = MAX_int32_T;
    } else {
      q0 = rtu_AUTO_MANUAL_SWITCH_0 + qY;
    }

    rtu_FIRST_PASS_0 = q0 * q0;
    if ((q0 < 0) && (rtu_FIRST_PASS_0 < MIN_int32_T - q0)) {
      rtu_FIRST_PASS_0 = MIN_int32_T;
    } else if ((q0 > 0) && (rtu_FIRST_PASS_0 > MAX_int32_T - q0)) {
      rtu_FIRST_PASS_0 = MAX_int32_T;
    } else {
      rtu_FIRST_PASS_0 += q0;
    }

    rty_INIT_JET_SELECT[i] = (rtu_FIRST_PASS_0 >= 100);
    qY = rtu_AUTO_MANUAL_SWITCH_0 - qY;
    rty_INIT_STATE_ERROR[i] = (rtu_AUTO_MANUAL_SWITCH_0 * qY * qY >= 30);
  }
}

void FirstPress_First_Prass_Logic_L1(const int32_T rtu_FIRST_PASS[32], const
  int16_T rtu_AUTO_MANUAL_SWITCH[32], boolean_T rty_INIT_JET_SELECT[32],
  boolean_T rty_INIT_STATE_ERROR[32])
{
  int32_T i;
  for (i = 0; i < 32; i++) {
    int32_T q0;
    int32_T q1;
    int32_T qY;
    int32_T rtu_FIRST_PASS_0;
    int16_T rtu_AUTO_MANUAL_SWITCH_0;
    rtu_FIRST_PASS_0 = rtu_FIRST_PASS[i];
    q1 = rtu_FIRST_PASS_0 * rtu_FIRST_PASS_0;
    if ((rtu_FIRST_PASS_0 < 0) && (q1 < MIN_int32_T - rtu_FIRST_PASS_0)) {
      q1 = MIN_int32_T;
    } else if ((rtu_FIRST_PASS_0 > 0) && (q1 > MAX_int32_T - rtu_FIRST_PASS_0))
    {
      q1 = MAX_int32_T;
    } else {
      q1 += rtu_FIRST_PASS_0;
    }

    rtu_AUTO_MANUAL_SWITCH_0 = rtu_AUTO_MANUAL_SWITCH[i];
    qY = rtu_AUTO_MANUAL_SWITCH_0 * rtu_AUTO_MANUAL_SWITCH_0;
    if (qY > 1073741823) {
      rtu_FIRST_PASS_0 = MAX_int32_T;
    } else {
      rtu_FIRST_PASS_0 = qY << 1;
    }

    if (q1 < rtu_FIRST_PASS_0 - MAX_int32_T) {
      qY = MAX_int32_T;
    } else {
      qY = rtu_FIRST_PASS_0 - q1;
    }

    q0 = q1 * qY;
    if ((qY < 0) && (q1 < MIN_int32_T - qY)) {
      qY = MIN_int32_T;
    } else if ((qY > 0) && (q1 > MAX_int32_T - qY)) {
      qY = MAX_int32_T;
    } else {
      qY += q1;
    }

    if ((q0 < 0) && (qY < MIN_int32_T - q0)) {
      qY = MIN_int32_T;
    } else if ((q0 > 0) && (qY > MAX_int32_T - q0)) {
      qY = MAX_int32_T;
    } else {
      qY += q0;
    }

    q1 *= rtu_FIRST_PASS_0;
    if ((qY < 0) && (q1 < MIN_int32_T - qY)) {
      q1 = MIN_int32_T;
    } else if ((qY > 0) && (q1 > MAX_int32_T - qY)) {
      q1 = MAX_int32_T;
    } else {
      q1 += qY;
    }

    if ((rtu_FIRST_PASS_0 > 0) && (q1 > MAX_int32_T - rtu_FIRST_PASS_0)) {
      qY = MAX_int32_T;
    } else {
      qY = rtu_FIRST_PASS_0 + q1;
    }

    rty_INIT_JET_SELECT[i] = (qY >= 0);
    rty_INIT_STATE_ERROR[i] = (rtu_FIRST_PASS_0 - q1 >= 0);
  }
}

void FirstPress_step(RT_MODEL_FirstPress_T *const FirstPress_M, int32_T
                     FirstPress_U_FIRST_PASS[32], int16_T
                     FirstPress_U_AUTO_MANUAL_SWITCH[32], boolean_T
                     FirstPress_Y_INIT_JET_SELECT[32], boolean_T
                     FirstPress_Y_INIT_STATE_ERROR[32], boolean_T
                     FirstPress_Y_INIT_JET_SELECT1[32], boolean_T
                     FirstPress_Y_INIT_STATE_ERROR1[32])
{
  FirstPress_First_Prass_Logic_L1(FirstPress_U_FIRST_PASS,
    FirstPress_U_AUTO_MANUAL_SWITCH, FirstPress_Y_INIT_JET_SELECT,
    FirstPress_Y_INIT_STATE_ERROR);
  FirstPress_First_Pass_Logic_P1(FirstPress_U_FIRST_PASS,
    FirstPress_U_AUTO_MANUAL_SWITCH, FirstPress_Y_INIT_JET_SELECT1,
    FirstPress_Y_INIT_STATE_ERROR1);
  UNUSED_PARAMETER(FirstPress_M);
}

void FirstPress_initialize(RT_MODEL_FirstPress_T *const FirstPress_M, int32_T
  FirstPress_U_FIRST_PASS[32], int16_T FirstPress_U_AUTO_MANUAL_SWITCH[32],
  boolean_T FirstPress_Y_INIT_JET_SELECT[32], boolean_T
  FirstPress_Y_INIT_STATE_ERROR[32], boolean_T FirstPress_Y_INIT_JET_SELECT1[32],
  boolean_T FirstPress_Y_INIT_STATE_ERROR1[32])
{
  rtmSetErrorStatus(FirstPress_M, (NULL));
  (void)memset(&FirstPress_U_FIRST_PASS[0], 0, sizeof(int32_T) << 5U);
  (void)memset(&FirstPress_U_AUTO_MANUAL_SWITCH[0], 0, sizeof(int16_T) << 5U);
  (void)memset(&FirstPress_Y_INIT_JET_SELECT[0], 0, sizeof(boolean_T) << 5U);
  (void)memset(&FirstPress_Y_INIT_STATE_ERROR[0], 0, sizeof(boolean_T) << 5U);
  (void)memset(&FirstPress_Y_INIT_JET_SELECT1[0], 0, sizeof(boolean_T) << 5U);
  (void)memset(&FirstPress_Y_INIT_STATE_ERROR1[0], 0, sizeof(boolean_T) << 5U);
  UNUSED_PARAMETER(FirstPress_M);
}

void FirstPress_terminate(RT_MODEL_FirstPress_T *const FirstPress_M)
{
  UNUSED_PARAMETER(FirstPress_M);
}
