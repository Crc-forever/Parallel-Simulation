#ifndef CPUTask_Sim_h_
#define CPUTask_Sim_h_
#ifndef CPUTask_Sim_COMMON_INCLUDES_
#define CPUTask_Sim_COMMON_INCLUDES_
#include <stdlib.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "simtarget/slSimTgtExcelReaderCAPI.h"
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
#include "CPUTask_Sim_types.h"
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include <string.h>
#define MODEL_NAME CPUTask_Sim
#define NSAMPLE_TIMES (2) 
#define NINPUTS (0)       
#define NOUTPUTS (2)     
#define NBLOCKIO (10) 
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
typedef struct { int8_T o4lcay5ifo ; } adf1c3xc20 ; typedef struct { int32_T
pjxodb2nb1 ; int32_T e0womlsjmm ; } cf1kq4ncbc ; typedef struct { int8_T
gnp0dzznxb ; } i1t5gkpgw1 ; typedef struct { int32_T bbkvllqsze ; int32_T
evxnnnvraz ; cf1kq4ncbc ax0jrtpwut ; cf1kq4ncbc cnsb0spyuq ; cf1kq4ncbc
jhnifdm04yv ; } B ; typedef struct { struct { real_T TempDoubleOutput ; }
be1ypkg3oi ; struct { void * ExcelLoader [ 3 ] ; } da55vtlacw ; struct { void
* AQHandles ; } m3nqpukfpp ; struct { void * AQHandles ; } pddfetaq22 ;
struct { void * AQHandles ; } iiocir3hzh ; int32_T jfxiebzt11 [ 16 ] ;
int32_T fmekapcoh3 ; int32_T nthmb1rxyk ; int32_T goiz0aciqk ; int32_T
bdc5i1qumz ; int32_T lybbyc3wp4 ; int32_T d2sncbrt0x ; int32_T k5kdf43z5e ;
int32_T mtop4afcg4 ; int8_T ka2crnf4zk [ 16 ] ; int8_T gn4mbidhbe ; int8_T
m31ezypo53 ; int8_T ly4sytvojr ; int8_T l2hwiyqftr ; int8_T k1vr2ypctj ;
int8_T cvtoivpdg4 ; int8_T ljgif2qtik ; int8_T b3a5gs5r5m ; int8_T ocomjcomln
; int8_T mpsw5o2vtm ; int8_T kwoyf2vgju ; int8_T epgh3rv3tm ; int8_T
olzc4eepgs ; int8_T lo3dyuq41b ; int8_T c5xvbnkpnx ; i1t5gkpgw1 ax0jrtpwut ;
adf1c3xc20 ebgpvzxvo3 ; i1t5gkpgw1 cnsb0spyuq ; adf1c3xc20 axnaqsojmf ;
i1t5gkpgw1 jhnifdm04yv ; adf1c3xc20 olreyz4euj ; adf1c3xc20 fficko2a024 ; }
DW ; typedef struct { int32_T e455jjhtvg ; int32_T npoqspmaqz ; } ExtY ;
typedef struct { rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct
jjdkemctyj_ { int32_T Constant_Value ; int32_T Constant1_Value ; } ; struct
og1v340kmp_ { int32_T res_Y0 ; int32_T value_out_Y0 ; } ; struct P_ { int32_T
ForIterator_IterationLimit ; int32_T ForIterator_IterationLimit_hg54moyj5v ;
int32_T Constant1_Value ; int32_T Constant2_Value ; int32_T res_Y0 ; int32_T
value_out_Y0 ; int32_T Constant_Value ; int32_T Constant1_Value_mvhnwcihcx ;
int32_T DataStoreMemory_InitialValue ; int32_T DataStoreMemory1_InitialValue
; int32_T ForIterator_IterationLimit_pmnerygy22 ; int32_T
Constant1_Value_cbj5azvbu2 ; int32_T Constant2_Value_az5chewn2m ; int32_T
DataStoreMemory_InitialValue_lpsnntvi5e ; int32_T
DataStoreMemory1_InitialValue_brapdgvyi0 ; int32_T
ForIterator_IterationLimit_fr1lsyzo0v ; int32_T Constant1_Value_old3zd5smi ;
int32_T Constant2_Value_nvs1o44prj ; int32_T
DataStoreMemory_InitialValue_gzmuee1ywg ; int32_T
DataStoreMemory1_InitialValue_mnzngyb5ay ; int32_T
ForIterator_IterationLimit_g3aj12bfdp ; int32_T Constant1_Value_m12xkxpoza ;
int32_T Constant2_Value_gpro0fhmc1 ; int32_T
DataStoreMemory_InitialValue_pwe1ttvdh5 ; int32_T
DataStoreMemory1_InitialValue_cywkg1i2ev ; int32_T Constant_Value_iilw0smpge
; int32_T Constant1_Value_moljqjpuv3 ; int32_T Merge_InitialOutput ; int32_T
Merge1_InitialOutput ; int32_T DataStoreMemory_InitialValue_glvqogqqzg ;
int8_T Constant_Value_mq0yqq5e0x ; int8_T Constant1_Value_b00i5gskzd ; int8_T
Constant_Value_dp3hb0zdw4 ; int8_T Constant_Value_pwsvvqm1ni ; int8_T
DataStoreMemory1_InitialValue_jiyg3kkzow ; int8_T
DataStoreMemory2_InitialValue ; og1v340kmp ax0jrtpwut ; jjdkemctyj ebgpvzxvo3
; og1v340kmp cnsb0spyuq ; jjdkemctyj axnaqsojmf ; og1v340kmp jhnifdm04yv ;
jjdkemctyj olreyz4euj ; jjdkemctyj fficko2a024 ; } ; extern const char_T *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern DW rtDW ; extern ExtY rtY
; extern P rtP ; extern mxArray * mr_CPUTask_Sim_GetDWork ( ) ; extern void
mr_CPUTask_Sim_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_CPUTask_Sim_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * CPUTask_Sim_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern DataMapInfo * rt_dataMapInfoPtr ;
extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ; void MdlOutputs ( int_T
tid ) ; void MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) ;
#endif
