#include "LANSwitch.h"
#include "rtwtypes.h"
#include "LANSwitch_private.h"
#include <string.h>

void LANSwitch_Error(int32_T *rty_Result, int32_T *rty_MSG)
{
  *rty_Result = -10001;
  *rty_MSG = 0;
}

void LANSwitch_FindPortInPool(int32_T rtu_PortId, int32_T *rty_Out1, int32_T
  *rtd_Found_P_e, const int32_T rtd_PortPool[256], const int32_T rtd_PortPoolF
  [256], int32_T rtp_POOL_SIZE)
{
  int32_T s57_iter;
  for (s57_iter = 0; s57_iter < rtp_POOL_SIZE; s57_iter++) {
    if ((rtu_PortId == rtd_PortPool[s57_iter]) && (rtd_PortPoolF[s57_iter] == 1)
        && (*rtd_Found_P_e == -1)) {
      *rty_Out1 = s57_iter;
    } else {
      *rty_Out1 = *rtd_Found_P_e;
    }

    *rtd_Found_P_e = *rty_Out1;
  }
}

int32_T LANSwitch_Err(void)
{
  return -10003;
}

void LANSwitch_step(RT_MODEL_LANSwitch_T *const LANSwitch_M, int32_T
                    LANSwitch_U_PortId, int32_T LANSwitch_U_CMD, int32_T
                    LANSwitch_U_Arg1, int32_T LANSwitch_U_Arg2, int32_T
                    LANSwitch_U_Arg3, int32_T *LANSwitch_Y_Result, int32_T
                    *LANSwitch_Y_MSG)
{
  B_LANSwitch_T *LANSwitch_B = LANSwitch_M->blockIO;
  DW_LANSwitch_T *LANSwitch_DW = LANSwitch_M->dwork;
  int32_T rtb_Assignment[256];
  int32_T rtb_Assignment1[256];
  int32_T rtb_Assignment1_o[256];
  int32_T rtb_Assignment_h[256];
  int32_T Found_E;
  int32_T Switch_m;
  int32_T rtb_Subtract;
  int32_T rtb_Switch;
  int32_T rtb_Switch1;
  int32_T rtb_Switch1_f;
  int32_T rtb_Switch_c;
  int32_T rtb_Switch_l;
  int32_T s44_iter;
  boolean_T Found;
  boolean_T Switch_l4;
  boolean_T rtb_Equal;
  boolean_T rtb_Equal_pi;
  switch (LANSwitch_U_CMD) {
   case 10001:
    if (LANSwitch_U_PortId == 0) {
      LANSwitch_Error(LANSwitch_Y_Result, LANSwitch_Y_MSG);
    } else {
      Found = false;
      Found_E = -1;
      for (s44_iter = 0; s44_iter < 256; s44_iter++) {
        Switch_m = LANSwitch_DW->PortPoolF[s44_iter];
        if ((LANSwitch_DW->PortPool[s44_iter] == LANSwitch_U_PortId) &&
            (Switch_m == 1)) {
          Switch_l4 = true;
        } else {
          Switch_l4 = Found;
        }

        Found = Switch_l4;
        if ((Switch_m == 0) && (Found_E == -1)) {
          Switch_m = s44_iter;
        } else {
          Switch_m = Found_E;
        }

        Found_E = Switch_m;
      }

      if ((!Switch_l4) && (Switch_m != -1)) {
        *LANSwitch_Y_Result = 1;
        for (Found_E = 0; Found_E < 256; Found_E++) {
          rtb_Equal_pi = (Switch_m == Found_E);
          if (rtb_Equal_pi) {
            rtb_Switch_c = LANSwitch_U_PortId;
          } else {
            rtb_Switch_c = LANSwitch_DW->PortPool[Found_E];
          }

          if (Found_E == 0) {
            for (s44_iter = 0; s44_iter < 256; s44_iter++) {
              rtb_Assignment_h[s44_iter] = LANSwitch_DW->PortPool[s44_iter];
            }
          }

          rtb_Assignment_h[Found_E] = rtb_Switch_c;
          for (s44_iter = 0; s44_iter < 256; s44_iter++) {
            LANSwitch_DW->PortPool[s44_iter] = rtb_Assignment_h[s44_iter];
          }

          if (rtb_Equal_pi) {
            rtb_Switch1_f = 1;
          } else {
            rtb_Switch1_f = LANSwitch_DW->PortPoolF[Found_E];
          }

          if (Found_E == 0) {
            for (s44_iter = 0; s44_iter < 256; s44_iter++) {
              rtb_Assignment1_o[s44_iter] = LANSwitch_DW->PortPoolF[s44_iter];
            }
          }

          rtb_Assignment1_o[Found_E] = rtb_Switch1_f;
          for (s44_iter = 0; s44_iter < 256; s44_iter++) {
            LANSwitch_DW->PortPoolF[s44_iter] = rtb_Assignment1_o[s44_iter];
          }
        }

        if (Switch_m == 0) {
          LANSwitch_B->Switch_p = 1;
        } else if (Switch_m == 1) {
          LANSwitch_B->Switch_p = 2;
        } else if (Switch_m == 2) {
          LANSwitch_B->Switch_p = 3;
        } else {
          LANSwitch_B->Switch_p = 4;
        }
      } else {
        *LANSwitch_Y_Result = -10004;
      }

      *LANSwitch_Y_MSG = LANSwitch_B->Switch_p;
    }
    break;

   case 10002:
    if (LANSwitch_U_PortId == 0) {
      LANSwitch_Error(LANSwitch_Y_Result, LANSwitch_Y_MSG);
    } else {
      s44_iter = -1;
      Found_E = -1;
      LANSwitch_FindPortInPool(LANSwitch_U_PortId, &LANSwitch_B->Switch_l,
        &s44_iter, LANSwitch_DW->PortPool, LANSwitch_DW->PortPoolF, 256);
      for (s44_iter = 0; s44_iter < 256; s44_iter++) {
        if ((LANSwitch_U_Arg1 == LANSwitch_DW->PortPool[s44_iter]) &&
            (LANSwitch_DW->PortPoolF[s44_iter] == 1) && (Found_E == -1)) {
          Switch_m = s44_iter;
        } else {
          Switch_m = Found_E;
        }

        Found_E = Switch_m;
      }

      if ((LANSwitch_B->Switch_l != -1) && (Switch_m != -1)) {
        *LANSwitch_Y_Result = LANSwitch_U_Arg1;
        rtb_Subtract = LANSwitch_U_Arg3 - LANSwitch_U_Arg2;
        if (rtb_Subtract == 1) {
          LANSwitch_B->Switch_i = 101;
        } else if (rtb_Subtract == 2) {
          LANSwitch_B->Switch_i = 102;
        } else if (rtb_Subtract == 3) {
          LANSwitch_B->Switch_i = 103;
        } else if (rtb_Subtract == -1) {
          LANSwitch_B->Switch_i = -101;
        } else if (rtb_Subtract == -2) {
          LANSwitch_B->Switch_i = -102;
        } else if (rtb_Subtract == -3) {
          LANSwitch_B->Switch_i = -103;
        } else {
          LANSwitch_B->Switch_i = rtb_Subtract;
        }
      } else {
        *LANSwitch_Y_Result = LANSwitch_Err();
      }

      *LANSwitch_Y_MSG = LANSwitch_B->Switch_i;
    }
    break;

   case 10003:
    if (LANSwitch_U_PortId == 0) {
      LANSwitch_Error(LANSwitch_Y_Result, LANSwitch_Y_MSG);
    } else {
      Found_E = -1;
      LANSwitch_FindPortInPool(LANSwitch_U_PortId, &LANSwitch_B->Switch,
        &Found_E, LANSwitch_DW->PortPool, LANSwitch_DW->PortPoolF, 256);
      if (LANSwitch_B->Switch != -1) {
        *LANSwitch_Y_Result = LANSwitch_B->Switch;
        *LANSwitch_Y_MSG = 1;
      } else {
        *LANSwitch_Y_Result = -1;
        *LANSwitch_Y_MSG = -1;
      }
    }
    break;

   case 10004:
    if (LANSwitch_U_PortId == 0) {
      LANSwitch_Error(LANSwitch_Y_Result, LANSwitch_Y_MSG);
    } else {
      Found_E = -1;
      LANSwitch_FindPortInPool(LANSwitch_U_PortId, &rtb_Switch_l, &Found_E,
        LANSwitch_DW->PortPool, LANSwitch_DW->PortPoolF, 256);
      if (rtb_Switch_l == -1) {
        *LANSwitch_Y_Result = LANSwitch_Err();
      } else {
        for (Found_E = 0; Found_E < 256; Found_E++) {
          rtb_Equal = (LANSwitch_U_PortId == Found_E);
          if (rtb_Equal) {
            rtb_Switch = 0;
          } else {
            rtb_Switch = LANSwitch_DW->PortPool[Found_E];
          }

          if (Found_E == 0) {
            for (s44_iter = 0; s44_iter < 256; s44_iter++) {
              rtb_Assignment[s44_iter] = LANSwitch_DW->PortPool[s44_iter];
            }
          }

          rtb_Assignment[Found_E] = rtb_Switch;
          for (s44_iter = 0; s44_iter < 256; s44_iter++) {
            LANSwitch_DW->PortPool[s44_iter] = rtb_Assignment[s44_iter];
          }

          if (rtb_Equal) {
            rtb_Switch1 = 0;
          } else {
            rtb_Switch1 = LANSwitch_DW->PortPoolF[Found_E];
          }

          if (Found_E == 0) {
            for (s44_iter = 0; s44_iter < 256; s44_iter++) {
              rtb_Assignment1[s44_iter] = LANSwitch_DW->PortPoolF[s44_iter];
            }
          }

          rtb_Assignment1[Found_E] = rtb_Switch1;
          for (s44_iter = 0; s44_iter < 256; s44_iter++) {
            LANSwitch_DW->PortPoolF[s44_iter] = rtb_Assignment1[s44_iter];
          }
        }

        *LANSwitch_Y_Result = LANSwitch_U_PortId;
        LANSwitch_B->OutportBufferForMSG = LANSwitch_ConstB.Constant;
      }

      *LANSwitch_Y_MSG = LANSwitch_B->OutportBufferForMSG;
    }
    break;

   default:
    *LANSwitch_Y_Result = -10002;
    *LANSwitch_Y_MSG = 0;
    break;
  }
}

void LANSwitch_initialize(RT_MODEL_LANSwitch_T *const LANSwitch_M, int32_T
  *LANSwitch_U_PortId, int32_T *LANSwitch_U_CMD, int32_T *LANSwitch_U_Arg1,
  int32_T *LANSwitch_U_Arg2, int32_T *LANSwitch_U_Arg3, int32_T
  *LANSwitch_Y_Result, int32_T *LANSwitch_Y_MSG)
{
  B_LANSwitch_T *LANSwitch_B = LANSwitch_M->blockIO;
  DW_LANSwitch_T *LANSwitch_DW = LANSwitch_M->dwork;
  (void) memset(((void *) LANSwitch_B), 0,
                sizeof(B_LANSwitch_T));
  (void) memset((void *)LANSwitch_DW, 0,
                sizeof(DW_LANSwitch_T));
  *LANSwitch_U_PortId = 0;
  *LANSwitch_U_CMD = 0;
  *LANSwitch_U_Arg1 = 0;
  *LANSwitch_U_Arg2 = 0;
  *LANSwitch_U_Arg3 = 0;
  *LANSwitch_Y_Result = 0;
  *LANSwitch_Y_MSG = 0;
  LANSwitch_B->OutportBufferForMSG = LANSwitch_ConstB.Constant;
}

void LANSwitch_terminate(RT_MODEL_LANSwitch_T *const LANSwitch_M)
{
  UNUSED_PARAMETER(LANSwitch_M);
}
