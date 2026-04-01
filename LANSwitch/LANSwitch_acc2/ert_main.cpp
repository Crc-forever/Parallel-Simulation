#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "LANSwitch.h"
#include "SimulationEngine.h"
#include "ModelData.h"
#include "define.h"
#include "xxhash.h"


static thread_local RT_MODEL_LANSwitch_T LANSwitch_M_;
static thread_local RT_MODEL_LANSwitch_T *const LANSwitch_MPtr = &LANSwitch_M_;
static thread_local DW_LANSwitch_T LANSwitch_DW;
static thread_local B_LANSwitch_T LANSwitch_B;
static thread_local int32_T LANSwitch_U_PortId;
static thread_local int32_T LANSwitch_U_CMD;
static thread_local int32_T LANSwitch_U_Arg1;
static thread_local int32_T LANSwitch_U_Arg2;
static thread_local int32_T LANSwitch_U_Arg3;
static thread_local int32_T LANSwitch_Y_Result;
static thread_local int32_T LANSwitch_Y_MSG;
thread_local RT_MODEL_LANSwitch_T *const LANSwitch_M = LANSwitch_MPtr;


int_T main(int_T argc, const char *argv[]) {

    SimulationEngine SE;
    
    SE.init(argc, argv);

    SE.start();
    SE.finish();

    return 0;
}


void SE_Interface_Init()
{
    RT_MODEL_LANSwitch_T *const LANSwitch_M = LANSwitch_MPtr;
    LANSwitch_M->blockIO = &LANSwitch_B;
    LANSwitch_M->dwork = &LANSwitch_DW;
    LANSwitch_initialize(LANSwitch_M, &LANSwitch_U_PortId, &LANSwitch_U_CMD,
                       &LANSwitch_U_Arg1, &LANSwitch_U_Arg2, &LANSwitch_U_Arg3,
                       &LANSwitch_Y_Result, &LANSwitch_Y_MSG);
}

void SE_Interface_OneStep(const char* __restrict input_buf, const char* __restrict output_buf)
{
    
    // Fridge_Correct_U_DOOR_SENSOR = *((real_T*)(input_buf)); 
    // Fridge_Correct_U_TEMPERATURE = *((real_T*)(input_buf + sizeof(real_T))); 
    // Fridge_Correct_U_REF = *((real_T*)(input_buf + sizeof(real_T) * 2)); 

    LANSwitch_step(LANSwitch_M, 
                        *((int32_T*)(input_buf)),
                        *((int32_T*)(input_buf + sizeof(int32_T))), 
                        *((int32_T*)(input_buf + sizeof(int32_T) * 2)), 
                        *((int32_T*)(input_buf + sizeof(int32_T) * 3)),
                        *((int32_T*)(input_buf + sizeof(int32_T) * 4)),
                        ((int32_T*)(output_buf)), 
                        ((int32_T*)(output_buf + sizeof(int32_T))));

    // *((real_T*)(output_buf)) = Fridge_Correct_Y_Out1;
    // *((real_T*)(output_buf + sizeof(real_T))) = Fridge_Correct_Y_Out2;
    // *((real_T*)(output_buf + sizeof(real_T) * 2)) = Fridge_Correct_Y_Out3;
    
}

unsigned long long SE_Interface_CalculateStateHash()
{
    XXH3_state_t* state = XXH3_createState();
    XXH3_64bits_reset(state);

    XXH3_64bits_update(state, LANSwitch_DW.PortPool, sizeof(int32_T) * 256);
    XXH3_64bits_update(state, LANSwitch_DW.PortPoolF, sizeof(int32_T) * 256);
    XXH3_64bits_update(state, &LANSwitch_B.OutportBufferForMSG, sizeof(int32_T));
    XXH3_64bits_update(state, &LANSwitch_B.Switch, sizeof(int32_T));
    XXH3_64bits_update(state, &LANSwitch_B.Switch_i, sizeof(int32_T));
    XXH3_64bits_update(state, &LANSwitch_B.Switch_l, sizeof(int32_T));
    XXH3_64bits_update(state, &LANSwitch_B.Switch_p, sizeof(int32_T));

    unsigned long long hash = XXH3_64bits_digest(state);
    XXH3_freeState(state);
    return hash;
}

bool SE_Interface_CompareState(char* __restrict state_buf)
{
    bool cmp1 = 0 == (memcmp(LANSwitch_DW.PortPool, (int32_T*)(state_buf), sizeof(int32_T) * 256));
    bool cmp2 = 0 == (memcmp(LANSwitch_DW.PortPoolF, (int32_T*)(state_buf + sizeof(int32_T) * 256), sizeof(int32_T) * 256));
    bool cmp3 = LANSwitch_B.OutportBufferForMSG == *((int32_T*)(state_buf + sizeof(int32_T) * 512));
    bool cmp4 = LANSwitch_B.Switch == *((int32_T*)(state_buf + sizeof(int32_T) * 513));
    bool cmp5 = LANSwitch_B.Switch_i == *((int32_T*)(state_buf + sizeof(int32_T) * 514));
    bool cmp6 = LANSwitch_B.Switch_l == *((int32_T*)(state_buf + sizeof(int32_T) * 515));
    bool cmp7 = LANSwitch_B.Switch_p == *((int32_T*)(state_buf + sizeof(int32_T) * 516));
    
    return cmp1 && cmp2 && cmp3 && cmp4 && cmp5 && cmp6 && cmp7;
}

void SE_Interface_GetState(char* __restrict state_buf)
{
    memcpy((int32_T*)state_buf, LANSwitch_DW.PortPool, sizeof(int32_T) * 256);
    memcpy((int32_T*)(state_buf + sizeof(int32_T) * 256), LANSwitch_DW.PortPoolF, sizeof(int32_T) * 256);
    *((int32_T*)(state_buf + sizeof(int32_T) * 512)) = LANSwitch_B.OutportBufferForMSG;
    *((int32_T*)(state_buf + sizeof(int32_T) * 513)) = LANSwitch_B.Switch;
    *((int32_T*)(state_buf + sizeof(int32_T) * 514)) = LANSwitch_B.Switch_i;
    *((int32_T*)(state_buf + sizeof(int32_T) * 515)) = LANSwitch_B.Switch_l;
    *((int32_T*)(state_buf + sizeof(int32_T) * 516)) = LANSwitch_B.Switch_p;
}

void SE_Interface_SetState(char* __restrict state_buf)
{
    memcpy(LANSwitch_DW.PortPool, (int32_T*)state_buf,  sizeof(int32_T) * 256);
    memcpy( LANSwitch_DW.PortPoolF, (int32_T*)(state_buf + sizeof(int32_T) * 256), sizeof(int32_T) * 256);
    LANSwitch_B.OutportBufferForMSG = *((int32_T*)(state_buf + sizeof(int32_T) * 512));
    LANSwitch_B.Switch = *((int32_T*)(state_buf + sizeof(int32_T) * 513));
    LANSwitch_B.Switch_i = *((int32_T*)(state_buf + sizeof(int32_T) * 514));
    LANSwitch_B.Switch_l = *((int32_T*)(state_buf + sizeof(int32_T) * 515));
    LANSwitch_B.Switch_p = *((int32_T*)(state_buf + sizeof(int32_T) * 516));
}