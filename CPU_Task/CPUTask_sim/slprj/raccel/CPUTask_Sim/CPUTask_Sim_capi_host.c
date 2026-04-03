#include "CPUTask_Sim_capi_host.h"
static CPUTask_Sim_host_DataMapInfo_T root;
static int initialized = 0;
__declspec( dllexport ) rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        CPUTask_Sim_host_InitializeDataMapInfo(&(root), "CPUTask_Sim");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction(){return(getRootMappingInfo());}
