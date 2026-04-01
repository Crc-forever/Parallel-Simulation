#ifndef Fridge_Correct_cap_host_h__
#define Fridge_Correct_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap_simtarget.h"
typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
Fridge_Correct_host_DataMapInfo_T ;
#ifdef __cplusplus
extern "C" {
#endif
void Fridge_Correct_host_InitializeDataMapInfo ( Fridge_Correct_host_DataMapInfo_T * dataMap , const char * path ) ;
#ifdef __cplusplus
}
#endif
#endif
#endif
