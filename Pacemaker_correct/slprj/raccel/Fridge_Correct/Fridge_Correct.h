#ifndef Fridge_Correct_h_
#define Fridge_Correct_h_
#ifndef Fridge_Correct_COMMON_INCLUDES_
#define Fridge_Correct_COMMON_INCLUDES_
#include <stdlib.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "Fridge_Correct_types.h"
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include <string.h>
#define MODEL_NAME Fridge_Correct
#define NSAMPLE_TIMES (1) 
#define NINPUTS (3)       
#define NOUTPUTS (3)     
#define NBLOCKIO (3) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T m0qpgyoz0w ; real_T kyy02fekha ; real_T ncy4yn3q4v ;
} B ; typedef struct { struct { void * AQHandles ; } bn2gs54ejo ; struct {
void * AQHandles ; } aomxoqah10 ; struct { void * AQHandles ; } bovl2mqq0g ;
int32_T kni5fvgqws ; uint32_T escahx4xjm ; uint8_T bw4h3igjka ; uint8_T
jslddb50oc ; } DW ; typedef struct { real_T k5iabpstuv ; real_T jakjdij4v1 ;
real_T g0lgepzs4w ; } ExtU ; typedef struct { real_T dxgl1gtolp ; real_T
k2zhq44y3w ; real_T avrmn2nowg ; } ExtY ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; extern const char_T *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern DW rtDW ; extern ExtU rtU
; extern ExtY rtY ; extern mxArray * mr_Fridge_Correct_GetDWork ( ) ; extern
void mr_Fridge_Correct_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_Fridge_Correct_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * Fridge_Correct_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern DataMapInfo * rt_dataMapInfoPtr ;
extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ; void MdlOutputs ( int_T
tid ) ; void MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) ;
#endif
