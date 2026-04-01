#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "CPUTask.h"
#include "SimulationEngine.h"
#include "ModelData.h"
#include "define.h"
#include "xxhash.h"


static thread_local RT_MODEL_CPUTask_T CPUTask_M_;
static thread_local RT_MODEL_CPUTask_T *const CPUTask_MPtr =
  &CPUTask_M_;
static thread_local DW_CPUTask_T CPUTask_DW;
static thread_local int32_T CPUTask_U_op;
static thread_local int32_T CPUTask_U_taskId;
static thread_local int32_T CPUTask_U_para;
static thread_local int32_T CPUTask_Y_res;
static thread_local int32_T CPUTask_Y_out;
thread_local RT_MODEL_CPUTask_T *const CPUTask_M = CPUTask_MPtr;


int_T main(int_T argc, const char *argv[]) {

    SimulationEngine SE;
    
    SE.init(argc, argv);

    SE.start();
    SE.finish();

    return 0;
}


void SE_Interface_Init()
{
    RT_MODEL_CPUTask_T *const CPUTask_M = CPUTask_MPtr;
    CPUTask_M->dwork = &CPUTask_DW;
    CPUTask_initialize(CPUTask_M, &CPUTask_U_op, &CPUTask_U_taskId,
                     &CPUTask_U_para, &CPUTask_Y_res, &CPUTask_Y_out);
}

void SE_Interface_OneStep(const char* __restrict input_buf, const char* __restrict output_buf)
{
    
    // Fridge_Correct_U_DOOR_SENSOR = *((real_T*)(input_buf)); 
    // Fridge_Correct_U_TEMPERATURE = *((real_T*)(input_buf + sizeof(real_T))); 
    // Fridge_Correct_U_REF = *((real_T*)(input_buf + sizeof(real_T) * 2)); 

    CPUTask_step(CPUTask_M,
                        *((int32_T*)(input_buf)),
                        *((int32_T*)(input_buf + sizeof(int32_T))), 
                        *((int32_T*)(input_buf + sizeof(int32_T) * 2)), 
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

    XXH3_64bits_update(state, CPUTask_DW.A, sizeof(int32_T) * 16);
    XXH3_64bits_update(state, CPUTask_DW.Aflag, sizeof(int8_T) * 16);
    XXH3_64bits_update(state, &CPUTask_DW.Init, sizeof(int8_T));
    
    unsigned long long hash = XXH3_64bits_digest(state);
    XXH3_freeState(state);
    return hash;
}

bool SE_Interface_CompareState(char* __restrict state_buf)
{
    bool cmp1 = 0 == (memcmp(CPUTask_DW.A, (int32_T*)(state_buf), sizeof(int32_T) * 16));
    bool cmp2 = 0 == (memcmp(CPUTask_DW.Aflag, (int8_T*)(state_buf + sizeof(int32_T) * 16), sizeof(int8_T) * 16));
    bool cmp3 = CPUTask_DW.Init == *((int8_T*)(state_buf + sizeof(int32_T) * 16 + sizeof(int8_T) * 16));
    
    return cmp1 && cmp2 && cmp3 ;
}
void SE_Interface_GetState(char* __restrict state_buf)
{
    memcpy((int32_T*)state_buf, CPUTask_DW.A, sizeof(int32_T) * 16);
    memcpy((int8_T*)(state_buf + sizeof(int32_T) * 16), CPUTask_DW.Aflag, sizeof(int8_T) * 16);
    *((int8_T*)(state_buf + sizeof(int32_T) * 16 + sizeof(int8_T) * 16)) = CPUTask_DW.Init;
}

void SE_Interface_SetState(char* __restrict state_buf)
{
    memcpy(CPUTask_DW.A, (int32_T*)state_buf, sizeof(int32_T) * 16);
    memcpy(CPUTask_DW.Aflag, (int8_T*)(state_buf + sizeof(int32_T) * 16), sizeof(int8_T) * 16);
    CPUTask_DW.Init = *((int8_T*)(state_buf + sizeof(int32_T) * 16 + sizeof(int8_T) * 16));
}