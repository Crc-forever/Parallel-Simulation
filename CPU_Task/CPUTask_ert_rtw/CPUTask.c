#include "CPUTask.h"
#include "rtwtypes.h"
#include "CPUTask_private.h"
#include <string.h>

void CPUTask_FunctionCallSubsystem(int32_T *rtd_find_n, int32_T *rtd_ret_index_a)
{
  *rtd_find_n = 0;
  *rtd_ret_index_a = -1;
}

void CPUTask_step(RT_MODEL_CPUTask_T *const CPUTask_M, int32_T CPUTask_U_op,
                  int32_T CPUTask_U_taskId, int32_T CPUTask_U_para, int32_T
                  *CPUTask_Y_res, int32_T *CPUTask_Y_out)
{
  DW_CPUTask_T *CPUTask_DW = CPUTask_M->dwork;
  int32_T rtb_Assignment[16];
  int32_T rtb_Assignment1[16];
  int32_T i;
  int32_T rtb_Switch;
  int32_T s11_iter;
  int32_T s26_iter;
  int8_T rtb_Assignment1_c[16];
  int8_T rtb_Assignment1_m[16];
  boolean_T rtb_OR_a;
  boolean_T rtb_OR_l;
  boolean_T rtb_OR_n;
  boolean_T s26_iter_tmp;
  if (CPUTask_DW->Init <= 0) {
    CPUTask_DW->Init = 1;
    for (s26_iter = 0; s26_iter < 16; s26_iter++) {
      CPUTask_DW->Aflag[s26_iter] = 0;
    }
  }

  switch (CPUTask_U_op) {
   case 1:
    CPUTask_FunctionCallSubsystem(&s26_iter, CPUTask_Y_out);
    for (s11_iter = 0; s11_iter < 16; s11_iter++) {
      rtb_OR_a = ((s26_iter != 0) || (CPUTask_DW->Aflag[s11_iter] != 0));
      if (rtb_OR_a) {
        rtb_Switch = CPUTask_DW->A[s11_iter];
      } else {
        rtb_Switch = CPUTask_U_taskId;
      }

      if (s11_iter == 0) {
        for (i = 0; i < 16; i++) {
          rtb_Assignment[i] = CPUTask_DW->A[i];
        }
      }

      rtb_Assignment[s11_iter] = rtb_Switch;
      for (i = 0; i < 16; i++) {
        CPUTask_DW->A[i] = rtb_Assignment[i];
        if (s11_iter == 0) {
          rtb_Assignment1_c[i] = CPUTask_DW->Aflag[i];
        }
      }

      if (rtb_OR_a) {
        rtb_Assignment1_c[s11_iter] = CPUTask_DW->Aflag[s11_iter];
      } else {
        rtb_Assignment1_c[s11_iter] = 1;
      }

      for (i = 0; i < 16; i++) {
        CPUTask_DW->Aflag[i] = rtb_Assignment1_c[i];
      }

      s26_iter_tmp = !rtb_OR_a;
      s26_iter = (s26_iter_tmp || (s26_iter != 0));
      if (s26_iter_tmp) {
        *CPUTask_Y_out = s11_iter;
      }
    }

    if (s26_iter != 0) {
      *CPUTask_Y_res = 1;
    } else {
      *CPUTask_Y_res = -1;
    }
    break;

   case 2:
    CPUTask_FunctionCallSubsystem(&s26_iter, CPUTask_Y_out);
    for (s11_iter = 0; s11_iter < 16; s11_iter++) {
      rtb_OR_n = ((s26_iter != 0) || (CPUTask_DW->Aflag[s11_iter] == 0) ||
                  (CPUTask_DW->A[s11_iter] - CPUTask_U_taskId != 0));
      s26_iter_tmp = !rtb_OR_n;
      if (s26_iter_tmp) {
        *CPUTask_Y_out = s11_iter;
      }

      if (s11_iter == 0) {
        for (i = 0; i < 16; i++) {
          rtb_Assignment1_m[i] = CPUTask_DW->Aflag[i];
        }
      }

      if (rtb_OR_n) {
        rtb_Assignment1_m[s11_iter] = CPUTask_DW->Aflag[s11_iter];
      } else {
        rtb_Assignment1_m[s11_iter] = 0;
      }

      for (i = 0; i < 16; i++) {
        CPUTask_DW->Aflag[i] = rtb_Assignment1_m[i];
      }

      s26_iter = (s26_iter_tmp || (s26_iter != 0));
    }

    *CPUTask_Y_res = s26_iter;
    break;

   case 3:
    CPUTask_FunctionCallSubsystem(&s26_iter, CPUTask_Y_out);
    for (s11_iter = 0; s11_iter < 16; s11_iter++) {
      rtb_OR_l = ((s26_iter != 0) || (CPUTask_DW->Aflag[s11_iter] == 0) ||
                  (CPUTask_DW->A[s11_iter] - CPUTask_U_taskId != 0));
      s26_iter_tmp = !rtb_OR_l;
      if (s26_iter_tmp) {
        *CPUTask_Y_out = s11_iter;
      }

      s26_iter = (s26_iter_tmp || (s26_iter != 0));
      if (s11_iter == 0) {
        for (i = 0; i < 16; i++) {
          rtb_Assignment1[i] = CPUTask_DW->A[i];
        }
      }

      if (rtb_OR_l) {
        rtb_Assignment1[s11_iter] = CPUTask_DW->A[s11_iter];
      } else {
        rtb_Assignment1[s11_iter] = CPUTask_U_para;
      }

      for (i = 0; i < 16; i++) {
        CPUTask_DW->A[i] = rtb_Assignment1[i];
      }
    }

    *CPUTask_Y_res = s26_iter;
    break;

   case 4:
    CPUTask_FunctionCallSubsystem(&s26_iter, CPUTask_Y_out);
    for (s11_iter = 0; s11_iter < 16; s11_iter++) {
      s26_iter_tmp = ((s26_iter == 0) && (CPUTask_DW->Aflag[s11_iter] != 0) &&
                      (CPUTask_DW->A[s11_iter] - CPUTask_U_taskId == 0));
      if (s26_iter_tmp) {
        *CPUTask_Y_out = s11_iter;
      }

      s26_iter = (s26_iter_tmp || (s26_iter != 0));
    }

    *CPUTask_Y_res = s26_iter;
    break;

   default:
    *CPUTask_Y_res = -1;
    *CPUTask_Y_out = -1;
    break;
  }
}

void CPUTask_initialize(RT_MODEL_CPUTask_T *const CPUTask_M, int32_T
  *CPUTask_U_op, int32_T *CPUTask_U_taskId, int32_T *CPUTask_U_para, int32_T
  *CPUTask_Y_res, int32_T *CPUTask_Y_out)
{
  DW_CPUTask_T *CPUTask_DW = CPUTask_M->dwork;
  (void) memset((void *)CPUTask_DW, 0,
                sizeof(DW_CPUTask_T));
  *CPUTask_U_op = 0;
  *CPUTask_U_taskId = 0;
  *CPUTask_U_para = 0;
  *CPUTask_Y_res = 0;
  *CPUTask_Y_out = 0;
}

void CPUTask_terminate(RT_MODEL_CPUTask_T *const CPUTask_M)
{
  UNUSED_PARAMETER(CPUTask_M);
}
