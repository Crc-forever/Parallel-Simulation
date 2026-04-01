#include "Fridge_Correct_capi_host.h"
static Fridge_Correct_host_DataMapInfo_T root;
static int initialized = 0;
__declspec( dllexport ) rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        Fridge_Correct_host_InitializeDataMapInfo(&(root), "Fridge_Correct");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction(){return(getRootMappingInfo());}
