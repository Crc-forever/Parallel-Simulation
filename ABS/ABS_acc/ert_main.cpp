#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "ABS.h"
#include "SimulationEngine.h"
#include "ModelData.h"
#include "define.h"
#include "xxhash.h"


static thread_local RT_MODEL rtM_;
static thread_local RT_MODEL *const rtMPtr = &rtM_;
static thread_local int32_T rtU_Speed[32];
static thread_local int32_T rtU_FilterValue[32];
static thread_local int16_T rtU_Acc[32];
static thread_local int16_T rtU_P_i[32];
static thread_local int32_T rtU_Q[32];
static thread_local int32_T rtU_H[32];
static thread_local int32_T rtU_R[32];
static thread_local int32_T rtY_P_Update[32];
static thread_local int32_T rtY_Out1[32];
static thread_local int32_T rtY_Filter_Update[32];
static thread_local real32_T rtY_normalize_value[32];
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

    ABS_initialize(rtM, rtU_Speed, rtU_FilterValue, rtU_Acc, rtU_P_i, rtU_Q, rtU_H,
                 rtU_R, rtY_P_Update, rtY_Out1, rtY_Filter_Update,
                 rtY_normalize_value);
}

void SE_Interface_OneStep(const char* __restrict input_buf, const char* __restrict output_buf)
{
    
    // Fridge_Correct_U_DOOR_SENSOR = *((real_T*)(input_buf)); 
    // Fridge_Correct_U_TEMPERATURE = *((real_T*)(input_buf + sizeof(real_T))); 
    // Fridge_Correct_U_REF = *((real_T*)(input_buf + sizeof(real_T) * 2)); 

    ABS_step(rtM,
            ((int32_T*)(input_buf)),
            ((int32_T*)(input_buf + sizeof(int32_T)*32)),
            ((int16_T*)(input_buf + sizeof(int32_T)*64)),  
            ((int16_T*)(input_buf + sizeof(int32_T)*64 + sizeof(int16_T)*32)),  
            ((int32_T*)(input_buf + sizeof(int32_T)*64 + sizeof(int16_T)*64)),  
            ((int32_T*)(input_buf + sizeof(int32_T)*96 + sizeof(int16_T)*64)),  
            ((int32_T*)(input_buf + sizeof(int32_T)*128 + sizeof(int16_T)*64)),    
            ((int32_T*)(output_buf)), 
            ((int32_T*)(output_buf + sizeof(int32_T) * 32)), 
            ((int32_T*)(output_buf + sizeof(int32_T) * 64)),
            ((real32_T*)(output_buf + sizeof(int32_T) * 96))
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
