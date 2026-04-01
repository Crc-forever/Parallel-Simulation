#include "RoboticArmController.h"
#include "rtwtypes.h"
#include "RoboticArmController_private.h"
#include <string.h>

void RoboticArmController_Error(int32_T *rty_Res, int32_T *rty_B)
{
  *rty_Res = -1;
  *rty_B = 0;
}

void RoboticArmContr_FindArmIdInPool(int32_T rtu_ArmId, int32_T *rty_Out1, const
  int32_T rtd_ArmIdPool[256], const int32_T rtd_ArmIdPoolF[256], int32_T
  *rtd_FoundArm_n, int32_T rtp_POOL_SIZE)
{
  int32_T s71_iter;
  for (s71_iter = 0; s71_iter < rtp_POOL_SIZE; s71_iter++) {
    if ((rtu_ArmId == rtd_ArmIdPool[s71_iter]) && (rtd_ArmIdPoolF[s71_iter] == 1)
        && (*rtd_FoundArm_n == -1)) {
      *rty_Out1 = s71_iter;
    } else {
      *rty_Out1 = *rtd_FoundArm_n;
    }

    *rtd_FoundArm_n = *rty_Out1;
  }
}

int32_T RoboticArmController_Err(void)
{
  return -3;
}

void RoboticArmCon_FindArmIdInPool_f(int32_T rtu_ArmId, int32_T *rty_Out1, const
  int32_T rtd_ArmIdPool[256], const int32_T rtd_ArmIdPoolF[256], int32_T
  *rtd_FoundArm_g, int32_T rtp_POOL_SIZE)
{
  int32_T s27_iter;
  for (s27_iter = 0; s27_iter < rtp_POOL_SIZE; s27_iter++) {
    if ((rtu_ArmId == rtd_ArmIdPool[s27_iter]) && (rtd_ArmIdPoolF[s27_iter] >= 1)
        && (*rtd_FoundArm_g == -1)) {
      *rty_Out1 = s27_iter;
    } else {
      *rty_Out1 = *rtd_FoundArm_g;
    }

    *rtd_FoundArm_g = *rty_Out1;
  }
}

void RoboticArmController_step(RT_MODEL_RoboticArmController_T *const
  RoboticArmController_M, int32_T RoboticArmController_U_ArmId, int32_T
  RoboticArmController_U_Op, int32_T RoboticArmController_U_P1, int32_T
  RoboticArmController_U_P2, int32_T RoboticArmController_U_P3, int32_T
  *RoboticArmController_Y_Res, int32_T *RoboticArmController_Y_B)
{
  B_RoboticArmController_T *RoboticArmController_B =
    RoboticArmController_M->blockIO;
  DW_RoboticArmController_T *RoboticArmController_DW =
    RoboticArmController_M->dwork;
  int32_T rtb_Assignment[256];
  int32_T rtb_Assignment1[256];
  int32_T rtb_Assignment1_c[256];
  int32_T rtb_Assignment1_j[256];
  int32_T rtb_Assignment1_o[256];
  int32_T rtb_Assignment_c[256];
  int32_T rtb_Assignment_h[256];
  int32_T rtb_Assignment_k[256];
  int32_T Found_E;
  int32_T Switch_m;
  int32_T rtb_Subtract;
  int32_T rtb_Switch;
  int32_T rtb_Switch1;
  int32_T rtb_Switch1_e;
  int32_T rtb_Switch1_f;
  int32_T rtb_Switch1_h;
  int32_T rtb_Switch_a;
  int32_T rtb_Switch_b;
  int32_T rtb_Switch_c;
  int32_T rtb_Switch_ci;
  int32_T rtb_Switch_l;
  int32_T rtb_Switch_mm;
  int32_T s96_iter;
  boolean_T Found;
  boolean_T Switch_l4;
  boolean_T rtb_Equal;
  boolean_T rtb_Equal_a;
  boolean_T rtb_Equal_d1;
  boolean_T rtb_Equal_pi;
  switch (RoboticArmController_U_Op) {
   case 10001:
    if (RoboticArmController_U_ArmId == 0) {
      RoboticArmController_Error(RoboticArmController_Y_Res,
        RoboticArmController_Y_B);
    } else {
      Found = false;
      Found_E = -1;
      for (s96_iter = 0; s96_iter < 256; s96_iter++) {
        Switch_m = RoboticArmController_DW->ArmIdPoolF[s96_iter];
        if ((RoboticArmController_DW->ArmIdPool[s96_iter] ==
             RoboticArmController_U_ArmId) && (Switch_m == 1)) {
          Switch_l4 = true;
        } else {
          Switch_l4 = Found;
        }

        Found = Switch_l4;
        if ((Switch_m == 0) && (Found_E == -1)) {
          Switch_m = s96_iter;
        } else {
          Switch_m = Found_E;
        }

        Found_E = Switch_m;
      }

      if ((!Switch_l4) && (Switch_m != -1)) {
        *RoboticArmController_Y_Res = 1;
        for (Found_E = 0; Found_E < 256; Found_E++) {
          rtb_Equal_pi = (Switch_m == Found_E);
          if (rtb_Equal_pi) {
            rtb_Switch_c = RoboticArmController_U_ArmId;
          } else {
            rtb_Switch_c = RoboticArmController_DW->ArmIdPool[Found_E];
          }

          if (Found_E == 0) {
            for (s96_iter = 0; s96_iter < 256; s96_iter++) {
              rtb_Assignment_h[s96_iter] = RoboticArmController_DW->
                ArmIdPool[s96_iter];
            }
          }

          rtb_Assignment_h[Found_E] = rtb_Switch_c;
          for (s96_iter = 0; s96_iter < 256; s96_iter++) {
            RoboticArmController_DW->ArmIdPool[s96_iter] =
              rtb_Assignment_h[s96_iter];
          }

          if (rtb_Equal_pi) {
            rtb_Switch1_f = 1;
          } else {
            rtb_Switch1_f = RoboticArmController_DW->ArmIdPoolF[Found_E];
          }

          if (Found_E == 0) {
            for (s96_iter = 0; s96_iter < 256; s96_iter++) {
              rtb_Assignment1_o[s96_iter] = RoboticArmController_DW->
                ArmIdPoolF[s96_iter];
            }
          }

          rtb_Assignment1_o[Found_E] = rtb_Switch1_f;
          for (s96_iter = 0; s96_iter < 256; s96_iter++) {
            RoboticArmController_DW->ArmIdPoolF[s96_iter] =
              rtb_Assignment1_o[s96_iter];
          }
        }

        if (Switch_m == 0) {
          RoboticArmController_B->Switch_p = 1;
        } else if (Switch_m == 1) {
          RoboticArmController_B->Switch_p = 2;
        } else if (Switch_m == 2) {
          RoboticArmController_B->Switch_p = 3;
        } else {
          RoboticArmController_B->Switch_p = 4;
        }
      } else {
        *RoboticArmController_Y_Res = -4;
      }

      *RoboticArmController_Y_B = RoboticArmController_B->Switch_p;
    }
    break;

   case 10002:
    if (RoboticArmController_U_ArmId == 0) {
      RoboticArmController_Error(RoboticArmController_Y_Res,
        RoboticArmController_Y_B);
    } else {
      s96_iter = -1;
      Found_E = -1;
      RoboticArmContr_FindArmIdInPool(RoboticArmController_U_ArmId,
        &RoboticArmController_B->Switch_l, RoboticArmController_DW->ArmIdPool,
        RoboticArmController_DW->ArmIdPoolF, &s96_iter, 256);
      for (s96_iter = 0; s96_iter < 256; s96_iter++) {
        if ((RoboticArmController_U_P1 == RoboticArmController_DW->
             ArmIdPool[s96_iter]) && (RoboticArmController_DW->
             ArmIdPoolF[s96_iter] == 1) && (Found_E == -1)) {
          Switch_m = s96_iter;
        } else {
          Switch_m = Found_E;
        }

        Found_E = Switch_m;
      }

      if ((RoboticArmController_B->Switch_l != -1) && (Switch_m != -1)) {
        *RoboticArmController_Y_Res = RoboticArmController_U_P1;
        rtb_Subtract = RoboticArmController_U_P3 - RoboticArmController_U_P2;
        if (rtb_Subtract == 1) {
          RoboticArmController_B->Switch_i = 101;
        } else if (rtb_Subtract == 2) {
          RoboticArmController_B->Switch_i = 102;
        } else if (rtb_Subtract == 3) {
          RoboticArmController_B->Switch_i = 103;
        } else if (rtb_Subtract == -1) {
          RoboticArmController_B->Switch_i = -101;
        } else if (rtb_Subtract == -2) {
          RoboticArmController_B->Switch_i = -102;
        } else if (rtb_Subtract == -3) {
          RoboticArmController_B->Switch_i = -103;
        } else {
          RoboticArmController_B->Switch_i = rtb_Subtract;
        }
      } else {
        *RoboticArmController_Y_Res = RoboticArmController_Err();
      }

      *RoboticArmController_Y_B = RoboticArmController_B->Switch_i;
    }
    break;

   case 10004:
    if (RoboticArmController_U_ArmId == 0) {
      RoboticArmController_Error(RoboticArmController_Y_Res,
        RoboticArmController_Y_B);
    } else {
      Found_E = -1;
      RoboticArmContr_FindArmIdInPool(RoboticArmController_U_ArmId,
        &RoboticArmController_B->Switch, RoboticArmController_DW->ArmIdPool,
        RoboticArmController_DW->ArmIdPoolF, &Found_E, 256);
      if (RoboticArmController_B->Switch != -1) {
        *RoboticArmController_Y_Res = RoboticArmController_B->Switch;
        *RoboticArmController_Y_B = 1;
      } else {
        *RoboticArmController_Y_Res = -1;
        *RoboticArmController_Y_B = -1;
      }
    }
    break;

   case 10008:
    if (RoboticArmController_U_ArmId == 0) {
      RoboticArmController_Error(RoboticArmController_Y_Res,
        RoboticArmController_Y_B);
    } else {
      Found_E = -1;
      RoboticArmCon_FindArmIdInPool_f(RoboticArmController_U_ArmId,
        &rtb_Switch_l, RoboticArmController_DW->ArmIdPool,
        RoboticArmController_DW->ArmIdPoolF, &Found_E, 256);
      if (rtb_Switch_l == -1) {
        *RoboticArmController_Y_Res = RoboticArmController_Err();
      } else {
        for (Found_E = 0; Found_E < 256; Found_E++) {
          rtb_Equal_d1 = (RoboticArmController_U_ArmId == Found_E);
          if (rtb_Equal_d1) {
            rtb_Switch_b = 0;
          } else {
            rtb_Switch_b = RoboticArmController_DW->ArmIdPool[Found_E];
          }

          if (Found_E == 0) {
            for (s96_iter = 0; s96_iter < 256; s96_iter++) {
              rtb_Assignment_c[s96_iter] = RoboticArmController_DW->
                ArmIdPool[s96_iter];
            }
          }

          rtb_Assignment_c[Found_E] = rtb_Switch_b;
          for (s96_iter = 0; s96_iter < 256; s96_iter++) {
            RoboticArmController_DW->ArmIdPool[s96_iter] =
              rtb_Assignment_c[s96_iter];
          }

          if (rtb_Equal_d1) {
            rtb_Switch1_e = 0;
          } else {
            rtb_Switch1_e = RoboticArmController_DW->ArmIdPoolF[Found_E];
          }

          if (Found_E == 0) {
            for (s96_iter = 0; s96_iter < 256; s96_iter++) {
              rtb_Assignment1_j[s96_iter] = RoboticArmController_DW->
                ArmIdPoolF[s96_iter];
            }
          }

          rtb_Assignment1_j[Found_E] = rtb_Switch1_e;
          for (s96_iter = 0; s96_iter < 256; s96_iter++) {
            RoboticArmController_DW->ArmIdPoolF[s96_iter] =
              rtb_Assignment1_j[s96_iter];
          }
        }

        *RoboticArmController_Y_Res = RoboticArmController_U_ArmId;
        RoboticArmController_B->OutportBufferForB_ky =
          RoboticArmController_ConstB.Constant_l;
      }

      *RoboticArmController_Y_B = RoboticArmController_B->OutportBufferForB_ky;
    }
    break;

   case 10016:
    if (RoboticArmController_U_ArmId == 0) {
      RoboticArmController_Error(RoboticArmController_Y_Res,
        RoboticArmController_Y_B);
    } else {
      Found_E = -1;
      RoboticArmCon_FindArmIdInPool_f(RoboticArmController_U_ArmId,
        &rtb_Switch_ci, RoboticArmController_DW->ArmIdPool,
        RoboticArmController_DW->ArmIdPoolF, &Found_E, 256);
      if (rtb_Switch_ci == -1) {
        *RoboticArmController_Y_Res = RoboticArmController_Err();
      } else {
        for (Found_E = 0; Found_E < 256; Found_E++) {
          rtb_Equal_a = (RoboticArmController_U_ArmId == Found_E);
          if (rtb_Equal_a) {
            rtb_Switch_a = 1;
          } else {
            rtb_Switch_a = RoboticArmController_DW->ArmIdPool[Found_E];
          }

          if (Found_E == 0) {
            for (s96_iter = 0; s96_iter < 256; s96_iter++) {
              rtb_Assignment_k[s96_iter] = RoboticArmController_DW->
                ArmIdPool[s96_iter];
            }
          }

          rtb_Assignment_k[Found_E] = rtb_Switch_a;
          for (s96_iter = 0; s96_iter < 256; s96_iter++) {
            RoboticArmController_DW->ArmIdPool[s96_iter] =
              rtb_Assignment_k[s96_iter];
          }

          if (rtb_Equal_a) {
            if (RoboticArmController_U_P3 == 5) {
              rtb_Switch1_h = 5;
            } else if (RoboticArmController_U_P2 == 4) {
              rtb_Switch1_h = 4;
            } else if (RoboticArmController_U_P1 == 3) {
              rtb_Switch1_h = 3;
            } else {
              rtb_Switch1_h = 1;
            }
          } else {
            rtb_Switch1_h = RoboticArmController_DW->ArmIdPoolF[Found_E];
          }

          if (Found_E == 0) {
            for (s96_iter = 0; s96_iter < 256; s96_iter++) {
              rtb_Assignment1_c[s96_iter] = RoboticArmController_DW->
                ArmIdPoolF[s96_iter];
            }
          }

          rtb_Assignment1_c[Found_E] = rtb_Switch1_h;
          for (s96_iter = 0; s96_iter < 256; s96_iter++) {
            RoboticArmController_DW->ArmIdPoolF[s96_iter] =
              rtb_Assignment1_c[s96_iter];
          }
        }

        *RoboticArmController_Y_Res = RoboticArmController_U_ArmId;
        RoboticArmController_B->OutportBufferForB_k =
          RoboticArmController_ConstB.Constant_g;
      }

      *RoboticArmController_Y_B = RoboticArmController_B->OutportBufferForB_k;
    }
    break;

   case 10032:
    if (RoboticArmController_U_ArmId == 0) {
      RoboticArmController_Error(RoboticArmController_Y_Res,
        RoboticArmController_Y_B);
    } else {
      Found_E = -1;
      for (s96_iter = 0; s96_iter < 256; s96_iter++) {
        if ((RoboticArmController_U_ArmId == RoboticArmController_DW->
             ArmIdPool[s96_iter]) && (RoboticArmController_DW->
             ArmIdPoolF[s96_iter] == 5) && (Found_E == -1)) {
          rtb_Switch_mm = s96_iter;
        } else {
          rtb_Switch_mm = Found_E;
        }

        Found_E = rtb_Switch_mm;
      }

      if (rtb_Switch_mm == -1) {
        *RoboticArmController_Y_Res = RoboticArmController_Err();
      } else {
        for (Found_E = 0; Found_E < 256; Found_E++) {
          rtb_Equal = (RoboticArmController_U_ArmId == Found_E);
          if (rtb_Equal) {
            rtb_Switch = 1;
          } else {
            rtb_Switch = RoboticArmController_DW->ArmIdPool[Found_E];
          }

          if (Found_E == 0) {
            for (s96_iter = 0; s96_iter < 256; s96_iter++) {
              rtb_Assignment[s96_iter] = RoboticArmController_DW->
                ArmIdPool[s96_iter];
            }
          }

          rtb_Assignment[Found_E] = rtb_Switch;
          for (s96_iter = 0; s96_iter < 256; s96_iter++) {
            RoboticArmController_DW->ArmIdPool[s96_iter] =
              rtb_Assignment[s96_iter];
          }

          if (rtb_Equal) {
            if (RoboticArmController_U_P3 == 8) {
              rtb_Switch1 = 8;
            } else if (RoboticArmController_U_P2 == 7) {
              rtb_Switch1 = 7;
            } else if (RoboticArmController_U_P1 == 6) {
              rtb_Switch1 = 6;
            } else {
              rtb_Switch1 = 1;
            }
          } else {
            rtb_Switch1 = RoboticArmController_DW->ArmIdPoolF[Found_E];
          }

          if (Found_E == 0) {
            for (s96_iter = 0; s96_iter < 256; s96_iter++) {
              rtb_Assignment1[s96_iter] = RoboticArmController_DW->
                ArmIdPoolF[s96_iter];
            }
          }

          rtb_Assignment1[Found_E] = rtb_Switch1;
          for (s96_iter = 0; s96_iter < 256; s96_iter++) {
            RoboticArmController_DW->ArmIdPoolF[s96_iter] =
              rtb_Assignment1[s96_iter];
          }
        }

        *RoboticArmController_Y_Res = RoboticArmController_U_ArmId;
        RoboticArmController_B->OutportBufferForB =
          RoboticArmController_ConstB.Constant;
      }

      *RoboticArmController_Y_B = RoboticArmController_B->OutportBufferForB;
    }
    break;

   default:
    *RoboticArmController_Y_Res = -2;
    *RoboticArmController_Y_B = 0;
    break;
  }
}

void RoboticArmController_initialize(RT_MODEL_RoboticArmController_T *const
  RoboticArmController_M, int32_T *RoboticArmController_U_ArmId, int32_T
  *RoboticArmController_U_Op, int32_T *RoboticArmController_U_P1, int32_T
  *RoboticArmController_U_P2, int32_T *RoboticArmController_U_P3, int32_T
  *RoboticArmController_Y_Res, int32_T *RoboticArmController_Y_B)
{
  B_RoboticArmController_T *RoboticArmController_B =
    RoboticArmController_M->blockIO;
  DW_RoboticArmController_T *RoboticArmController_DW =
    RoboticArmController_M->dwork;
  (void) memset(((void *) RoboticArmController_B), 0,
                sizeof(B_RoboticArmController_T));
  (void) memset((void *)RoboticArmController_DW, 0,
                sizeof(DW_RoboticArmController_T));
  *RoboticArmController_U_ArmId = 0;
  *RoboticArmController_U_Op = 0;
  *RoboticArmController_U_P1 = 0;
  *RoboticArmController_U_P2 = 0;
  *RoboticArmController_U_P3 = 0;
  *RoboticArmController_Y_Res = 0;
  *RoboticArmController_Y_B = 0;
  RoboticArmController_B->OutportBufferForB_ky =
    RoboticArmController_ConstB.Constant_l;
  RoboticArmController_B->OutportBufferForB_k =
    RoboticArmController_ConstB.Constant_g;
  RoboticArmController_B->OutportBufferForB =
    RoboticArmController_ConstB.Constant;
}

void RoboticArmController_terminate(RT_MODEL_RoboticArmController_T *const
  RoboticArmController_M)
{
  UNUSED_PARAMETER(RoboticArmController_M);
}
