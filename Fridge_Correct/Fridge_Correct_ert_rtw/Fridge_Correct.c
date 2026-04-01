#include "Fridge_Correct.h"
#include "rtwtypes.h"
#include <string.h>
#define Fridge_Corre_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define Fridge_Correct_IN_CLOSE_HOT    ((uint8_T)1U)
#define Fridge_Correct_IN_CLOSE_NORM   ((uint8_T)2U)
#define Fridge_Correct_IN_OPEN         ((uint8_T)3U)
#define Fridge_Correct_IN_OPEN_15_SEC  ((uint8_T)4U)

void Fridge_Correct_step(RT_MODEL_Fridge_Correct_T *const Fridge_Correct_M,
  real_T Fridge_Correct_U_DOOR_SENSOR, real_T Fridge_Correct_U_TEMPERATURE,
  real_T Fridge_Correct_U_REF, real_T *Fridge_Correct_Y_Out1, real_T
  *Fridge_Correct_Y_Out2, real_T *Fridge_Correct_Y_Out3)
{
  DW_Fridge_Correct_T *Fridge_Correct_DW = Fridge_Correct_M->dwork;
  if (Fridge_Correct_DW->temporalCounter_i1 < 15) {
    Fridge_Correct_DW->temporalCounter_i1++;
  }

  if (Fridge_Correct_DW->is_active_c3_Fridge_Correct == 0) {
    Fridge_Correct_DW->is_active_c3_Fridge_Correct = 1U;
    Fridge_Correct_DW->is_c3_Fridge_Correct = Fridge_Correct_IN_CLOSE_NORM;
  } else {
    switch (Fridge_Correct_DW->is_c3_Fridge_Correct) {
     case Fridge_Correct_IN_CLOSE_HOT:
      if (Fridge_Correct_U_TEMPERATURE <= Fridge_Correct_U_REF) {
        Fridge_Correct_DW->is_c3_Fridge_Correct = Fridge_Correct_IN_CLOSE_NORM;
      } else if (Fridge_Correct_U_DOOR_SENSOR == 1.0) {
        Fridge_Correct_DW->temporalCounter_i1 = 0U;
        Fridge_Correct_DW->is_c3_Fridge_Correct = Fridge_Correct_IN_OPEN;
      } else {
        *Fridge_Correct_Y_Out3 = 1.0;
      }
      break;

     case Fridge_Correct_IN_CLOSE_NORM:
      if (Fridge_Correct_U_DOOR_SENSOR == 1.0) {
        Fridge_Correct_DW->temporalCounter_i1 = 0U;
        Fridge_Correct_DW->is_c3_Fridge_Correct = Fridge_Correct_IN_OPEN;
      } else if (Fridge_Correct_U_TEMPERATURE > Fridge_Correct_U_REF + 2.0) {
        Fridge_Correct_DW->is_c3_Fridge_Correct = Fridge_Correct_IN_CLOSE_HOT;
      } else {
        *Fridge_Correct_Y_Out1 = 0.0;
        *Fridge_Correct_Y_Out2 = 0.0;
        *Fridge_Correct_Y_Out3 = 0.0;
      }
      break;

     case Fridge_Correct_IN_OPEN:
      if (Fridge_Correct_DW->temporalCounter_i1 >= 15) {
        Fridge_Correct_DW->is_c3_Fridge_Correct = Fridge_Correct_IN_OPEN_15_SEC;
      } else if (Fridge_Correct_U_DOOR_SENSOR == 0.0) {
        Fridge_Correct_DW->is_c3_Fridge_Correct = Fridge_Correct_IN_CLOSE_NORM;
      } else {
        *Fridge_Correct_Y_Out1 = 1.0;
        *Fridge_Correct_Y_Out2 = 0.0;
        *Fridge_Correct_Y_Out3 = 0.0;
      }
      break;

     default:
      if (Fridge_Correct_U_DOOR_SENSOR == 0.0) {
        Fridge_Correct_DW->is_c3_Fridge_Correct = Fridge_Correct_IN_CLOSE_NORM;
      } else {
        *Fridge_Correct_Y_Out1 = 1.0;
        *Fridge_Correct_Y_Out2 = 1.0;
      }
      break;
    }
  }
}

void Fridge_Correct_initialize(RT_MODEL_Fridge_Correct_T *const Fridge_Correct_M,
  real_T *Fridge_Correct_U_DOOR_SENSOR, real_T *Fridge_Correct_U_TEMPERATURE,
  real_T *Fridge_Correct_U_REF, real_T *Fridge_Correct_Y_Out1, real_T
  *Fridge_Correct_Y_Out2, real_T *Fridge_Correct_Y_Out3)
{
  DW_Fridge_Correct_T *Fridge_Correct_DW = Fridge_Correct_M->dwork;
  (void) memset((void *)Fridge_Correct_DW, 0,
                sizeof(DW_Fridge_Correct_T));
  *Fridge_Correct_U_DOOR_SENSOR = 0.0;
  *Fridge_Correct_U_TEMPERATURE = 0.0;
  *Fridge_Correct_U_REF = 0.0;
  *Fridge_Correct_Y_Out1 = 0.0;
  *Fridge_Correct_Y_Out2 = 0.0;
  *Fridge_Correct_Y_Out3 = 0.0;
  Fridge_Correct_DW->temporalCounter_i1 = 0U;
  *Fridge_Correct_Y_Out1 = 0.0;
  *Fridge_Correct_Y_Out2 = 0.0;
  *Fridge_Correct_Y_Out3 = 0.0;
  Fridge_Correct_DW->is_active_c3_Fridge_Correct = 0U;
  Fridge_Correct_DW->is_c3_Fridge_Correct = Fridge_Corre_IN_NO_ACTIVE_CHILD;
}

void Fridge_Correct_terminate(RT_MODEL_Fridge_Correct_T *const Fridge_Correct_M)
{
  UNUSED_PARAMETER(Fridge_Correct_M);
}
