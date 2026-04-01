#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "RoboticArmController.h"
#include "SimulationEngine.h"
#include "ModelData.h"
#include "define.h"
#include "xxhash.h"


static thread_local RT_MODEL_RoboticArmController_T RoboticArmController_M_;
static thread_local RT_MODEL_RoboticArmController_T *const RoboticArmController_MPtr =
  &RoboticArmController_M_;
static thread_local DW_RoboticArmController_T RoboticArmController_DW;
static thread_local B_RoboticArmController_T RoboticArmController_B;
static thread_local int32_T RoboticArmController_U_ArmId;
static thread_local int32_T RoboticArmController_U_Op;
static thread_local int32_T RoboticArmController_U_P1;
static thread_local int32_T RoboticArmController_U_P2;
static thread_local int32_T RoboticArmController_U_P3;
static thread_local int32_T RoboticArmController_Y_Res;
static thread_local int32_T RoboticArmController_Y_B;
thread_local RT_MODEL_RoboticArmController_T *const RoboticArmController_M =
    RoboticArmController_MPtr;


int_T main(int_T argc, const char *argv[]) {

    SimulationEngine SE;
    
    SE.init(argc, argv);

    SE.start();
    SE.finish();

    return 0;
}


void SE_Interface_Init()
{
    RT_MODEL_RoboticArmController_T *const RoboticArmController_M =
    RoboticArmController_MPtr;
    RoboticArmController_M->blockIO = &RoboticArmController_B;
    RoboticArmController_M->dwork = &RoboticArmController_DW;
    RoboticArmController_initialize(RoboticArmController_M, &RoboticArmController_U_ArmId,
                              &RoboticArmController_U_Op,
                              &RoboticArmController_U_P1,
                              &RoboticArmController_U_P2,
                              &RoboticArmController_U_P3,
                              &RoboticArmController_Y_Res,
                              &RoboticArmController_Y_B);
}

void SE_Interface_OneStep(const char* __restrict input_buf, const char* __restrict output_buf)
{
    
    // Fridge_Correct_U_DOOR_SENSOR = *((real_T*)(input_buf)); 
    // Fridge_Correct_U_TEMPERATURE = *((real_T*)(input_buf + sizeof(real_T))); 
    // Fridge_Correct_U_REF = *((real_T*)(input_buf + sizeof(real_T) * 2)); 

    RoboticArmController_step(RoboticArmController_M,
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

    XXH3_64bits_update(state, RoboticArmController_DW.ArmIdPool, sizeof(int32_T) * 256);
    XXH3_64bits_update(state, RoboticArmController_DW.ArmIdPoolF, sizeof(int32_T) * 256);
    XXH3_64bits_update(state, &RoboticArmController_B.OutportBufferForB, sizeof(int32_T));
    XXH3_64bits_update(state, &RoboticArmController_B.OutportBufferForB_k, sizeof(int32_T));
    XXH3_64bits_update(state, &RoboticArmController_B.OutportBufferForB_ky, sizeof(int32_T));
    XXH3_64bits_update(state, &RoboticArmController_B.Switch, sizeof(int32_T));
    XXH3_64bits_update(state, &RoboticArmController_B.Switch_i, sizeof(int32_T));
    XXH3_64bits_update(state, &RoboticArmController_B.Switch_l, sizeof(int32_T));
    XXH3_64bits_update(state, &RoboticArmController_B.Switch_p, sizeof(int32_T));
    
    unsigned long long hash = XXH3_64bits_digest(state);
    XXH3_freeState(state);
    return hash;
}

bool SE_Interface_CompareState(char* __restrict state_buf)
{
    bool cmp1 = 0 == (memcmp(RoboticArmController_DW.ArmIdPool, (int32_T*)(state_buf), sizeof(int32_T) * 256));
    bool cmp2 = 0 == (memcmp(RoboticArmController_DW.ArmIdPoolF, (int32_T*)(state_buf + sizeof(int32_T) * 256), sizeof(int32_T) * 256));
    bool cmp3 = RoboticArmController_B.OutportBufferForB == *((int32_T*)(state_buf + sizeof(int32_T) * 512));
    bool cmp4 = RoboticArmController_B.OutportBufferForB_k == *((int32_T*)(state_buf + sizeof(int32_T) * 513));
    bool cmp5 = RoboticArmController_B.OutportBufferForB_ky == *((int32_T*)(state_buf + sizeof(int32_T) * 514));
    bool cmp6 = RoboticArmController_B.Switch == *((int32_T*)(state_buf + sizeof(int32_T) * 515));
    bool cmp7 = RoboticArmController_B.Switch_i == *((int32_T*)(state_buf + sizeof(int32_T) * 516));
    bool cmp8 = RoboticArmController_B.Switch_l == *((int32_T*)(state_buf + sizeof(int32_T) * 517));
    bool cmp9 = RoboticArmController_B.Switch_p == *((int32_T*)(state_buf + sizeof(int32_T) * 518));
    
    return cmp1 && cmp2 && cmp3 && cmp4 && cmp5 && cmp6 && cmp7 && cmp8 && cmp9;
}

void SE_Interface_GetState(char* __restrict state_buf)
{
    memcpy((int32_T*)state_buf, RoboticArmController_DW.ArmIdPool, sizeof(int32_T) * 256);
    memcpy((int32_T*)(state_buf + sizeof(int32_T) * 256), RoboticArmController_DW.ArmIdPoolF, sizeof(int32_T) * 256);
    *((int32_T*)(state_buf + sizeof(int32_T) * 512)) = RoboticArmController_B.OutportBufferForB;
    *((int32_T*)(state_buf + sizeof(int32_T) * 513)) = RoboticArmController_B.OutportBufferForB_k;
    *((int32_T*)(state_buf + sizeof(int32_T) * 514)) = RoboticArmController_B.OutportBufferForB_ky;
    *((int32_T*)(state_buf + sizeof(int32_T) * 515)) = RoboticArmController_B.Switch;
    *((int32_T*)(state_buf + sizeof(int32_T) * 516)) = RoboticArmController_B.Switch_i;
    *((int32_T*)(state_buf + sizeof(int32_T) * 517)) = RoboticArmController_B.Switch_l;
    *((int32_T*)(state_buf + sizeof(int32_T) * 518)) = RoboticArmController_B.Switch_p;
}

void SE_Interface_SetState(char* __restrict state_buf)
{
    memcpy(RoboticArmController_DW.ArmIdPool, (int32_T*)state_buf, sizeof(int32_T) * 256);
    memcpy(RoboticArmController_DW.ArmIdPoolF, (int32_T*)(state_buf + sizeof(int32_T) * 256), sizeof(int32_T) * 256);
    RoboticArmController_B.OutportBufferForB = *((int32_T*)(state_buf + sizeof(int32_T) * 512));
    RoboticArmController_B.OutportBufferForB_k = *((int32_T*)(state_buf + sizeof(int32_T) * 513));
    RoboticArmController_B.OutportBufferForB_ky = *((int32_T*)(state_buf + sizeof(int32_T) * 514));
    RoboticArmController_B.Switch = *((int32_T*)(state_buf + sizeof(int32_T) * 515));
    RoboticArmController_B.Switch_i = *((int32_T*)(state_buf + sizeof(int32_T) * 516));
    RoboticArmController_B.Switch_l = *((int32_T*)(state_buf + sizeof(int32_T) * 517));
    RoboticArmController_B.Switch_p = *((int32_T*)(state_buf + sizeof(int32_T) * 518));
}