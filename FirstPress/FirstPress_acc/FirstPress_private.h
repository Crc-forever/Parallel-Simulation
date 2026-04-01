#ifndef FirstPress_private_h_
#define FirstPress_private_h_
#include "rtwtypes.h"
#include "FirstPress_types.h"
#include "FirstPress.h"

extern void FirstPress_First_Pass_Logic_P1(const int32_T rtu_FIRST_PASS[32],
  const int16_T rtu_AUTO_MANUAL_SWITCH[32], boolean_T rty_INIT_JET_SELECT[32],
  boolean_T rty_INIT_STATE_ERROR[32]);
extern void FirstPress_First_Prass_Logic_L1(const int32_T rtu_FIRST_PASS[32],
  const int16_T rtu_AUTO_MANUAL_SWITCH[32], boolean_T rty_INIT_JET_SELECT[32],
  boolean_T rty_INIT_STATE_ERROR[32]);

#endif

