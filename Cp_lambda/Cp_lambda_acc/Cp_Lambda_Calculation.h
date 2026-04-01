/*
 * File: Cp_Lambda_Calculation.h
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

#ifndef Cp_Lambda_Calculation_h_
#define Cp_Lambda_Calculation_h_
#ifndef Cp_Lambda_Calculation_COMMON_INCLUDES_
#define Cp_Lambda_Calculation_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                              /* Cp_Lambda_Calculation_COMMON_INCLUDES_ */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Real-time Model Data Structure */
struct tag_RTM {
  char_T rt_unused;
};

/* Model entry point functions */
extern void Cp_Lambda_Calculation_initialize(RT_MODEL *const rtM, real_T
  *rtU_GeneratorSpeed, real_T *rtU_Wind, real_T *rtY_Percentage, real_T
  *rtY_Out1, real_T *rtY_Out2, real_T *rtY_Out3, real_T *rtY_Out4, real_T
  *rtY_PercentagePowerDelivered);
extern void Cp_Lambda_Calculation_step(RT_MODEL *const rtM, real_T
  rtU_GeneratorSpeed, real_T rtU_Wind, real_T *rtY_Percentage, real_T *rtY_Out1,
  real_T *rtY_Out2, real_T *rtY_Out3, real_T *rtY_Out4, real_T
  *rtY_PercentagePowerDelivered);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Cp_new' : Unused code path elimination
 * Block '<S1>/Display1' : Unused code path elimination
 * Block '<S1>/K=(K_del*K_opo//K_op1)^(1//3)' : Unused code path elimination
 * Block '<S1>/Lambda_new' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Cp_Lambda_Calculation'
 * '<S1>'   : 'Cp_Lambda_Calculation/Deloaded Optimal Operating Point of Variable Speed Wind Turbine'
 * '<S2>'   : 'Cp_Lambda_Calculation/Deloaded Optimal Operating Point of Variable Speed Wind Turbine/cp(lambda,beta)'
 */
#endif                                 /* Cp_Lambda_Calculation_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
