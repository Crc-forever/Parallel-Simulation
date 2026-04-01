#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "Elevator_Correct.h"
#include "SimulationEngine.h"
#include "ModelData.h"
#include "define.h"
#include "xxhash.h"


static thread_local RT_MODEL_Elevator_Correct_T Elevator_Correct_M_;
static thread_local RT_MODEL_Elevator_Correct_T *const Elevator_Correct_MPtr =
  &Elevator_Correct_M_;
static thread_local DW_Elevator_Correct_T Elevator_Correct_DW;
static thread_local real_T Elevator_Correct_U_pisua;
static thread_local real_T Elevator_Correct_Y_Out1;
static thread_local real_T Elevator_Correct_Y_Out2;
static thread_local real_T Elevator_Correct_Y_Out3;

thread_local RT_MODEL_Elevator_Correct_T *const Elevator_Correct_M =
    Elevator_Correct_MPtr;


int_T main(int_T argc, const char *argv[]) {

    SimulationEngine SE;
    
    SE.init(argc, argv);

    SE.start();
    SE.finish();

    return 0;
}


void SE_Interface_Init()
{
    Elevator_Correct_M->dwork = &Elevator_Correct_DW;
    Elevator_Correct_initialize(Elevator_Correct_M, &Elevator_Correct_U_pisua,
    &Elevator_Correct_Y_Out1, &Elevator_Correct_Y_Out2, &Elevator_Correct_Y_Out3);
}

void SE_Interface_OneStep(const char* __restrict input_buf, const char* __restrict output_buf)
{
    
    // Fridge_Correct_U_DOOR_SENSOR = *((real_T*)(input_buf)); 
    // Fridge_Correct_U_TEMPERATURE = *((real_T*)(input_buf + sizeof(real_T))); 
    // Fridge_Correct_U_REF = *((real_T*)(input_buf + sizeof(real_T) * 2)); 

    Elevator_Correct_step(Elevator_Correct_M, 
                        *((real_T*)(input_buf)),
                        ((real_T*)(output_buf)), 
                        ((real_T*)(output_buf + sizeof(real_T))), 
                        ((real_T*)(output_buf + sizeof(real_T) * 2))
                    );

    // *((real_T*)(output_buf)) = Fridge_Correct_Y_Out1;
    // *((real_T*)(output_buf + sizeof(real_T))) = Fridge_Correct_Y_Out2;
    // *((real_T*)(output_buf + sizeof(real_T) * 2)) = Fridge_Correct_Y_Out3;
    
}

unsigned long long SE_Interface_CalculateStateHash()
{
    XXH3_state_t* state = XXH3_createState();
    XXH3_64bits_reset(state);

    XXH3_64bits_update(state, &Elevator_Correct_DW.oraingoPisua, sizeof(real_T));
    XXH3_64bits_update(state, &Elevator_Correct_DW.is_active_c3_Elevator_Correct, sizeof(uint8_T));
    XXH3_64bits_update(state, &Elevator_Correct_DW.is_c3_Elevator_Correct, sizeof(uint8_T));
    XXH3_64bits_update(state, &Elevator_Correct_DW.temporalCounter_i1, sizeof(uint8_T));

    unsigned long long hash = XXH3_64bits_digest(state);
    XXH3_freeState(state);
    return hash;
}

bool SE_Interface_CompareState(char* __restrict state_buf)
{
    bool cmp1 = Elevator_Correct_DW.oraingoPisua == *((real_T*)(state_buf));
    bool cmp2 = Elevator_Correct_DW.is_active_c3_Elevator_Correct == *((uint8_T*)(state_buf + sizeof(real_T)));
    bool cmp3 = Elevator_Correct_DW.is_c3_Elevator_Correct == *((uint8_T*)(state_buf + sizeof(real_T) + sizeof(uint8_T)));
    bool cmp4 = Elevator_Correct_DW.temporalCounter_i1 == *((uint8_T*)(state_buf + sizeof(real_T) + sizeof(uint8_T)*2));

    return cmp1 && cmp2 && cmp3 && cmp4;
}

void SE_Interface_GetState(char* __restrict state_buf)
{
    *((real_T*)(state_buf)) = Elevator_Correct_DW.oraingoPisua;
    *((uint8_T*)(state_buf + sizeof(real_T))) = Elevator_Correct_DW.is_active_c3_Elevator_Correct;
    *((uint8_T*)(state_buf + sizeof(real_T) + sizeof(uint8_T))) = Elevator_Correct_DW.is_c3_Elevator_Correct;
    *((uint8_T*)(state_buf + sizeof(real_T) + sizeof(uint8_T)*2)) = Elevator_Correct_DW.temporalCounter_i1;
}

void SE_Interface_SetState(char* __restrict state_buf)
{
    Elevator_Correct_DW.oraingoPisua = *((real_T*)(state_buf));
    Elevator_Correct_DW.is_active_c3_Elevator_Correct = *((uint8_T*)(state_buf + sizeof(real_T)));
    Elevator_Correct_DW.is_c3_Elevator_Correct = *((uint8_T*)(state_buf + sizeof(real_T) + sizeof(uint8_T)));
    Elevator_Correct_DW.temporalCounter_i1 = *((uint8_T*)(state_buf + sizeof(real_T) + sizeof(uint8_T)*2));   
}