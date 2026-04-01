#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "Cp_Lambda_Calculation.h"
#include "SimulationEngine.h"
#include "ModelData.h"
#include "define.h"
#include "xxhash.h"


static thread_local RT_MODEL rtM_;
static thread_local RT_MODEL *const rtMPtr = &rtM_;
static thread_local real_T rtU_GeneratorSpeed;
static thread_local real_T rtU_Wind;
static thread_local real_T rtY_Percentage;
static thread_local real_T rtY_Out1;
static thread_local real_T rtY_Out2;
static thread_local real_T rtY_Out3;
static thread_local real_T rtY_Out4;
static thread_local real_T rtY_PercentagePowerDelivered;
static thread_local real_T Pacemaker_Correct_Y_Out7;
thread_local RT_MODEL *const rtM = rtMPtr;


int_T main(int_T argc, const char *argv[]) {

    SimulationEngine SE;
    
    SE.init(argc, argv);

    SE.start();
    SE.finish();

    return 0;
}


void SE_Interface_Init()
{
    RT_MODEL *const rtM = rtMPtr;

    Cp_Lambda_Calculation_initialize(rtM, &rtU_GeneratorSpeed, &rtU_Wind,
        &rtY_Percentage, &rtY_Out1, &rtY_Out2, &rtY_Out3, &rtY_Out4,
        &rtY_PercentagePowerDelivered);
}

void SE_Interface_OneStep(const char* __restrict input_buf, const char* __restrict output_buf)
{
    
    // Fridge_Correct_U_DOOR_SENSOR = *((real_T*)(input_buf)); 
    // Fridge_Correct_U_TEMPERATURE = *((real_T*)(input_buf + sizeof(real_T))); 
    // Fridge_Correct_U_REF = *((real_T*)(input_buf + sizeof(real_T) * 2)); 

    Cp_Lambda_Calculation_step(rtM, 
                        *((real_T*)(input_buf)),
                        *((real_T*)(input_buf + sizeof(real_T))),  
                        ((real_T*)(output_buf)), 
                        ((real_T*)(output_buf + sizeof(real_T))), 
                        ((real_T*)(output_buf + sizeof(real_T) * 2)),
                        ((real_T*)(output_buf + sizeof(real_T) * 3)),
                        ((real_T*)(output_buf + sizeof(real_T) * 4)),
                        ((real_T*)(output_buf + sizeof(real_T) * 5))
                    );

    // *((real_T*)(output_buf)) = Fridge_Correct_Y_Out1;
    // *((real_T*)(output_buf + sizeof(real_T))) = Fridge_Correct_Y_Out2;
    // *((real_T*)(output_buf + sizeof(real_T) * 2)) = Fridge_Correct_Y_Out3;
    
}

unsigned long long SE_Interface_CalculateStateHash()
{
    /*XXH3_state_t* state = XXH3_createState();
    XXH3_64bits_reset(state);

    XXH3_64bits_update(state, &Pacemaker_Correct_B.Floor, sizeof(real_T));
    XXH3_64bits_update(state, &Pacemaker_Correct_DW.Flag, sizeof(real_T));
    XXH3_64bits_update(state, &Pacemaker_Correct_DW.temporalCounter_i1, sizeof(uint32_T));
    XXH3_64bits_update(state, &Pacemaker_Correct_DW.is_active_c3_Pacemaker_Correct, sizeof(uint8_T));
    XXH3_64bits_update(state, &Pacemaker_Correct_DW.is_c3_Pacemaker_Correct, sizeof(uint8_T));

    unsigned long long hash = XXH3_64bits_digest(state);
    XXH3_freeState(state);*/
    return 0;
}

bool SE_Interface_CompareState(char* __restrict state_buf)
{
    /*bool cmp1 = Pacemaker_Correct_B.Floor == *((real_T*)(state_buf));
    bool cmp2 = Pacemaker_Correct_DW.Flag == *((real_T*)(state_buf + sizeof(real_T)));
    bool cmp3 = Pacemaker_Correct_DW.temporalCounter_i1 == *((uint32_T*)(state_buf + sizeof(real_T) * 2));
    bool cmp4 = Pacemaker_Correct_DW.is_active_c3_Pacemaker_Correct == *((uint8_T*)(state_buf + sizeof(real_T) * 2 + sizeof(uint32_T)));
    bool cmp5 = Pacemaker_Correct_DW.is_c3_Pacemaker_Correct == *((uint8_T*)(state_buf + sizeof(real_T) * 2 + sizeof(uint32_T) + sizeof(uint8_T)));

    return cmp1 && cmp2 && cmp3 && cmp4 && cmp5;*/
    return 1;
}

void SE_Interface_GetState(char* __restrict state_buf)
{
    return;
    /**((real_T*)(state_buf)) = Pacemaker_Correct_B.Floor;
    *((real_T*)(state_buf + sizeof(real_T))) = Pacemaker_Correct_DW.Flag;
    *((uint32_T*)(state_buf + sizeof(real_T) * 2)) = Pacemaker_Correct_DW.temporalCounter_i1;
    *((uint8_T*)(state_buf + sizeof(real_T) * 2 + sizeof(uint32_T))) = Pacemaker_Correct_DW.is_active_c3_Pacemaker_Correct;
    *((uint8_T*)(state_buf + sizeof(real_T) * 2 + sizeof(uint32_T) + sizeof(uint8_T))) = Pacemaker_Correct_DW.is_c3_Pacemaker_Correct;*/
}

void SE_Interface_SetState(char* __restrict state_buf)
{
    return;/*
    Pacemaker_Correct_B.Floor = *((real_T*)(state_buf));
    Pacemaker_Correct_DW.Flag = *((real_T*)(state_buf + sizeof(real_T)));
    Pacemaker_Correct_DW.temporalCounter_i1 = *((uint32_T*)(state_buf + sizeof(real_T) * 2));   
    Pacemaker_Correct_DW.is_active_c3_Pacemaker_Correct = *((uint8_T*)(state_buf + sizeof(real_T) * 2 + sizeof(uint32_T)));
    Pacemaker_Correct_DW.is_c3_Pacemaker_Correct = *((uint8_T*)(state_buf + sizeof(real_T) * 2 + sizeof(uint32_T) + sizeof(uint8_T)));*/
}