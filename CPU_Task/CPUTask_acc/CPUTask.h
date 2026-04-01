#ifndef CPUTask_h_
#define CPUTask_h_
#ifndef CPUTask_COMMON_INCLUDES_
#define CPUTask_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "math.h"
#endif

#include "CPUTask_types.h"
#include <string.h>
#include "rt_defines.h"

typedef struct {
  int32_T A[16];
  int8_T Aflag[16];
  int8_T Init;
} DW_CPUTask_T;

struct tag_RTM_CPUTask_T {
  DW_CPUTask_T *dwork;
};

extern void CPUTask_initialize(RT_MODEL_CPUTask_T *const CPUTask_M, int32_T
  *CPUTask_U_op, int32_T *CPUTask_U_taskId, int32_T *CPUTask_U_para, int32_T
  *CPUTask_Y_res, int32_T *CPUTask_Y_out);
extern void CPUTask_step(RT_MODEL_CPUTask_T *const CPUTask_M, int32_T
  CPUTask_U_op, int32_T CPUTask_U_taskId, int32_T CPUTask_U_para, int32_T
  *CPUTask_Y_res, int32_T *CPUTask_Y_out);
extern void CPUTask_terminate(RT_MODEL_CPUTask_T *const CPUTask_M);

#endif

