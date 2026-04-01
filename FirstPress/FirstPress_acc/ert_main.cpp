#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "FirstPress.h"
#include "SimulationEngine.h"
#include "ModelData.h"
#include "define.h"
#include "xxhash.h"


static thread_local RT_MODEL_FirstPress_T FirstPress_M_;
static thread_local RT_MODEL_FirstPress_T *const FirstPress_MPtr = &FirstPress_M_;
static thread_local int32_T FirstPress_U_FIRST_PASS[32];
static thread_local int16_T FirstPress_U_AUTO_MANUAL_SWITCH[32];
static thread_local boolean_T FirstPress_Y_INIT_JET_SELECT[32];
static thread_local boolean_T FirstPress_Y_INIT_STATE_ERROR[32];
static thread_local boolean_T FirstPress_Y_INIT_JET_SELECT1[32];
static thread_local boolean_T FirstPress_Y_INIT_STATE_ERROR1[32];
thread_local RT_MODEL_FirstPress_T *const FirstPress_M = FirstPress_MPtr;



int_T main(int_T argc, const char *argv[]) {

    SimulationEngine SE;
    
    SE.init(argc, argv);

    SE.start();
    SE.finish();

    return 0;
}


void SE_Interface_Init()
{
    RT_MODEL_FirstPress_T *const FirstPress_M = FirstPress_MPtr;


    FirstPress_initialize(FirstPress_M, FirstPress_U_FIRST_PASS,
                        FirstPress_U_AUTO_MANUAL_SWITCH,
                        FirstPress_Y_INIT_JET_SELECT,
                        FirstPress_Y_INIT_STATE_ERROR,
                        FirstPress_Y_INIT_JET_SELECT1,
                        FirstPress_Y_INIT_STATE_ERROR1);
}

void SE_Interface_OneStep(const char* __restrict input_buf, const char* __restrict output_buf)
{
    
    // Fridge_Correct_U_DOOR_SENSOR = *((real_T*)(input_buf)); 
    // Fridge_Correct_U_TEMPERATURE = *((real_T*)(input_buf + sizeof(real_T))); 
    // Fridge_Correct_U_REF = *((real_T*)(input_buf + sizeof(real_T) * 2)); 

    FirstPress_step(FirstPress_M,
            ((int32_T*)(input_buf)),
            ((int16_T*)(input_buf + sizeof(int32_T)*32)),
            ((boolean_T*)(output_buf)), 
            ((boolean_T*)(output_buf + sizeof(boolean_T) * 32)), 
            ((boolean_T*)(output_buf + sizeof(boolean_T) * 64)),
            ((boolean_T*)(output_buf + sizeof(boolean_T) * 96))
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
