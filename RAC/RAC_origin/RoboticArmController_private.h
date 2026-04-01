#ifndef RoboticArmController_private_h_
#define RoboticArmController_private_h_
#include "rtwtypes.h"
#include "RoboticArmController_types.h"
#include "RoboticArmController.h"

extern void RoboticArmController_Error(int32_T *rty_Res, int32_T *rty_B);
extern void RoboticArmContr_FindArmIdInPool(int32_T rtu_ArmId, int32_T *rty_Out1,
  const int32_T rtd_ArmIdPool[256], const int32_T rtd_ArmIdPoolF[256], int32_T
  *rtd_FoundArm_n, int32_T rtp_POOL_SIZE);
extern int32_T RoboticArmController_Err(void);
extern void RoboticArmCon_FindArmIdInPool_f(int32_T rtu_ArmId, int32_T *rty_Out1,
  const int32_T rtd_ArmIdPool[256], const int32_T rtd_ArmIdPoolF[256], int32_T
  *rtd_FoundArm_g, int32_T rtp_POOL_SIZE);

#endif

