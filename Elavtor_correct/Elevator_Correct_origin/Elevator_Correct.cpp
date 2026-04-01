#include "Elevator_Correct.h"
#include "rtwtypes.h"
#include <string.h>
#define Elevator_Cor_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define Elevator_Cor_IN_ateak_irekitzen ((uint8_T)2U)
#define Elevator_Correct_IN_Geldirik   ((uint8_T)1U)
#define Elevator_Correct_IN_ateak_ixten ((uint8_T)3U)
#define Elevator_Correct_IN_igotzen    ((uint8_T)4U)
#define Elevator_Correct_IN_jaisten    ((uint8_T)5U)

void Elevator_Correct_step(RT_MODEL_Elevator_Correct_T *const Elevator_Correct_M,
  real_T Elevator_Correct_U_pisua, real_T *Elevator_Correct_Y_Out1, real_T
  *Elevator_Correct_Y_Out2, real_T *Elevator_Correct_Y_Out3)
{
  DW_Elevator_Correct_T *Elevator_Correct_DW = Elevator_Correct_M->dwork;
  boolean_T c;
  if (Elevator_Correct_DW->temporalCounter_i1 < 15) {
    Elevator_Correct_DW->temporalCounter_i1++;
  }

  if (Elevator_Correct_DW->is_active_c3_Elevator_Correct == 0) {
    Elevator_Correct_DW->is_active_c3_Elevator_Correct = 1U;
    Elevator_Correct_DW->oraingoPisua = 0.0;
    Elevator_Correct_DW->is_c3_Elevator_Correct = Elevator_Correct_IN_Geldirik;
    *Elevator_Correct_Y_Out2 = 0.0;
    *Elevator_Correct_Y_Out1 = 0.0;
    *Elevator_Correct_Y_Out3 = 0.0;
  } else {
    switch (Elevator_Correct_DW->is_c3_Elevator_Correct) {
     case Elevator_Correct_IN_Geldirik:
      *Elevator_Correct_Y_Out1 = 0.0;
      if (Elevator_Correct_U_pisua != Elevator_Correct_DW->oraingoPisua) {
        Elevator_Correct_DW->temporalCounter_i1 = 0U;
        Elevator_Correct_DW->is_c3_Elevator_Correct =
          Elevator_Correct_IN_ateak_ixten;
        *Elevator_Correct_Y_Out2 = -1.0;
      }
      break;

     case Elevator_Cor_IN_ateak_irekitzen:
      *Elevator_Correct_Y_Out1 = 0.0;
      if (Elevator_Correct_DW->temporalCounter_i1 >= 3) {
        Elevator_Correct_DW->is_c3_Elevator_Correct =
          Elevator_Correct_IN_Geldirik;
        *Elevator_Correct_Y_Out2 = 0.0;
        *Elevator_Correct_Y_Out3 = Elevator_Correct_DW->oraingoPisua;
      }
      break;

     case Elevator_Correct_IN_ateak_ixten:
      if (Elevator_Correct_DW->temporalCounter_i1 >= 3) {
        if (Elevator_Correct_U_pisua > Elevator_Correct_DW->oraingoPisua) {
          *Elevator_Correct_Y_Out2 = 0.0;
          Elevator_Correct_DW->temporalCounter_i1 = 0U;
          Elevator_Correct_DW->is_c3_Elevator_Correct =
            Elevator_Correct_IN_igotzen;
          *Elevator_Correct_Y_Out1 = 15.0;
          *Elevator_Correct_Y_Out3 = Elevator_Correct_DW->oraingoPisua;
        } else if (Elevator_Correct_U_pisua < Elevator_Correct_DW->oraingoPisua)
        {
          *Elevator_Correct_Y_Out2 = 0.0;
          Elevator_Correct_DW->temporalCounter_i1 = 0U;
          Elevator_Correct_DW->is_c3_Elevator_Correct =
            Elevator_Correct_IN_jaisten;
          *Elevator_Correct_Y_Out1 = 10.0;
          *Elevator_Correct_Y_Out3 = Elevator_Correct_DW->oraingoPisua;
        }
      }
      break;

     case Elevator_Correct_IN_igotzen:
      *Elevator_Correct_Y_Out1 = 15.0;
      if (Elevator_Correct_U_pisua == Elevator_Correct_DW->oraingoPisua) {
        Elevator_Correct_DW->temporalCounter_i1 = 0U;
        Elevator_Correct_DW->is_c3_Elevator_Correct =
          Elevator_Cor_IN_ateak_irekitzen;
        *Elevator_Correct_Y_Out1 = 0.0;
        *Elevator_Correct_Y_Out2 = 1.0;
      } else {
        c = ((Elevator_Correct_DW->temporalCounter_i1 >= 10) &&
             (Elevator_Correct_DW->oraingoPisua < Elevator_Correct_U_pisua));
        if (c) {
          Elevator_Correct_DW->oraingoPisua++;
          Elevator_Correct_DW->temporalCounter_i1 = 0U;
          Elevator_Correct_DW->is_c3_Elevator_Correct =
            Elevator_Correct_IN_igotzen;
          *Elevator_Correct_Y_Out3 = Elevator_Correct_DW->oraingoPisua;
        }
      }
      break;

     default:
      *Elevator_Correct_Y_Out1 = 10.0;
      if (Elevator_Correct_U_pisua == Elevator_Correct_DW->oraingoPisua) {
        Elevator_Correct_DW->temporalCounter_i1 = 0U;
        Elevator_Correct_DW->is_c3_Elevator_Correct =
          Elevator_Cor_IN_ateak_irekitzen;
        *Elevator_Correct_Y_Out1 = 0.0;
        *Elevator_Correct_Y_Out2 = 1.0;
      } else {
        c = ((Elevator_Correct_DW->temporalCounter_i1 >= 5) &&
             (Elevator_Correct_DW->oraingoPisua > Elevator_Correct_U_pisua));
        if (c) {
          Elevator_Correct_DW->oraingoPisua--;
          Elevator_Correct_DW->temporalCounter_i1 = 0U;
          Elevator_Correct_DW->is_c3_Elevator_Correct =
            Elevator_Correct_IN_jaisten;
          *Elevator_Correct_Y_Out3 = Elevator_Correct_DW->oraingoPisua;
        }
      }
      break;
    }
  }
}

void Elevator_Correct_initialize(RT_MODEL_Elevator_Correct_T *const
  Elevator_Correct_M, real_T *Elevator_Correct_U_pisua, real_T
  *Elevator_Correct_Y_Out1, real_T *Elevator_Correct_Y_Out2, real_T
  *Elevator_Correct_Y_Out3)
{
  DW_Elevator_Correct_T *Elevator_Correct_DW = Elevator_Correct_M->dwork;
  (void) memset((void *)Elevator_Correct_DW, 0,
                sizeof(DW_Elevator_Correct_T));
  *Elevator_Correct_U_pisua = 0.0;
  *Elevator_Correct_Y_Out1 = 0.0;
  *Elevator_Correct_Y_Out2 = 0.0;
  *Elevator_Correct_Y_Out3 = 0.0;
  Elevator_Correct_DW->temporalCounter_i1 = 0U;
  *Elevator_Correct_Y_Out1 = 0.0;
  *Elevator_Correct_Y_Out2 = 0.0;
  *Elevator_Correct_Y_Out3 = 0.0;
  Elevator_Correct_DW->oraingoPisua = 0.0;
  Elevator_Correct_DW->is_active_c3_Elevator_Correct = 0U;
  Elevator_Correct_DW->is_c3_Elevator_Correct = Elevator_Cor_IN_NO_ACTIVE_CHILD;
}

void Elevator_Correct_terminate(RT_MODEL_Elevator_Correct_T *const
  Elevator_Correct_M)
{
  UNUSED_PARAMETER(Elevator_Correct_M);
}
