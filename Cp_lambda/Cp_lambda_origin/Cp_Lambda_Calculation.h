
#ifndef Cp_Lambda_Calculation_h_
#define Cp_Lambda_Calculation_h_
#ifndef Cp_Lambda_Calculation_COMMON_INCLUDES_
#define Cp_Lambda_Calculation_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                             
typedef struct tag_RTM RT_MODEL;


struct tag_RTM {
  char_T rt_unused;
};


extern void Cp_Lambda_Calculation_initialize(RT_MODEL *const rtM, real_T
  *rtU_GeneratorSpeed, real_T *rtU_Wind, real_T *rtY_Percentage, real_T
  *rtY_Out1, real_T *rtY_Out2, real_T *rtY_Out3, real_T *rtY_Out4, real_T
  *rtY_PercentagePowerDelivered);
extern void Cp_Lambda_Calculation_step(RT_MODEL *const rtM, real_T
  rtU_GeneratorSpeed, real_T rtU_Wind, real_T *rtY_Percentage, real_T *rtY_Out1,
  real_T *rtY_Out2, real_T *rtY_Out3, real_T *rtY_Out4, real_T
  *rtY_PercentagePowerDelivered);


#endif                                 /* Cp_Lambda_Calculation_h_ */


