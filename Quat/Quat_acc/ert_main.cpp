#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "Quat.h"
#include "SimulationEngine.h"
#include "ModelData.h"
#include "define.h"
#include "xxhash.h"


static thread_local RT_MODEL rtM_;
static thread_local RT_MODEL *const rtMPtr = &rtM_;
static thread_local int32_T rtU_Inport[8];
static thread_local int32_T rtU_Inport1[8];
static thread_local int32_T rtU_Inport2[8];
static thread_local int32_T rtU_Inport3[8];
static thread_local int32_T rtU_Inport4[8];
static thread_local int32_T rtU_Inport5[8];
static thread_local int32_T rtU_Inport6[8];
static thread_local int32_T rtU_Inport7[8];
static thread_local real32_T rtY_Outport[8];
static thread_local real32_T rtY_Outport1[8];
static thread_local real32_T rtY_Outport2[8];
static thread_local real32_T rtY_Outport3[8];
static thread_local real32_T rtY_Outport4[8];
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

    Quat_initialize(rtM, rtU_Inport, rtU_Inport1, rtU_Inport2, rtU_Inport3,
                  rtU_Inport4, rtU_Inport5, rtU_Inport6, rtU_Inport7,
                  rtY_Outport, rtY_Outport1, rtY_Outport2, rtY_Outport3,
                  rtY_Outport4);
}

void SE_Interface_OneStep(const char* __restrict input_buf, const char* __restrict output_buf)
{
    
    // Fridge_Correct_U_DOOR_SENSOR = *((real_T*)(input_buf)); 
    // Fridge_Correct_U_TEMPERATURE = *((real_T*)(input_buf + sizeof(real_T))); 
    // Fridge_Correct_U_REF = *((real_T*)(input_buf + sizeof(real_T) * 2)); 

    Quat_step(rtM,
            ((int32_T*)(input_buf)),
            ((int32_T*)(input_buf + sizeof(int32_T)*8*1)),
            ((int32_T*)(input_buf + sizeof(int32_T)*8*2)),
            ((int32_T*)(input_buf + sizeof(int32_T)*8*3)), 
            ((int32_T*)(input_buf + sizeof(int32_T)*8*4)),
            ((int32_T*)(input_buf + sizeof(int32_T)*8*5)), 
            ((int32_T*)(input_buf + sizeof(int32_T)*8*6)),
            ((int32_T*)(input_buf + sizeof(int32_T)*8*7)),  
            ((real32_T*)(output_buf)), 
            ((real32_T*)(output_buf + sizeof(real32_T) *8*1)), 
            ((real32_T*)(output_buf + sizeof(real32_T) *8*2)),
            ((real32_T*)(output_buf + sizeof(real32_T) *8*3)),
            ((real32_T*)(output_buf + sizeof(real32_T) *8*4))
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
