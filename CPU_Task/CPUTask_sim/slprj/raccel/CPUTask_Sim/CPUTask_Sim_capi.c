#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "CPUTask_Sim_capi_host.h"
#define sizeof(...) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 17
#endif
#ifndef SS_INT64
#define SS_INT64 18
#endif
#else
#include "builtin_typeid_types.h"
#include "CPUTask_Sim.h"
#include "CPUTask_Sim_capi.h"
#include "CPUTask_Sim_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 27 , TARGET_STRING
( "CPUTask_Sim/Subsystem" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , {
1 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem" ) , TARGET_STRING ( "" ) , 1
, 0 , 0 , 0 , 0 } , { 2 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 3 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 4 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 5 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 6 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 7 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 8 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 9 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 10 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem4" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 11 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem4" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 12 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Merge" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 13 , 27 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Merge1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 14 , 12 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 15 , 12 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem2" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 16 , 18 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 17 , 18 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem2" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 18 , 24 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 19 , 24 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem2" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 0 } , { 20 , 12 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem2/Data Store Read" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 21 , 12 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem2/Data Store Read1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 22 , 18 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem2/Data Store Read" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 23 , 18 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem2/Data Store Read1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 24 , 24 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem2/Data Store Read" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 25 , 24 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem2/Data Store Read1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 26 , TARGET_STRING ( "CPUTask_Sim/Data Store Memory" ) , TARGET_STRING ( "InitialValue" ) , 0 , 0 , 0 } , { 27 , TARGET_STRING ( "CPUTask_Sim/Data Store Memory1" ) , TARGET_STRING ( "InitialValue" ) , 1 , 0 , 0 } , { 28 , TARGET_STRING ( "CPUTask_Sim/Data Store Memory2" ) , TARGET_STRING ( "InitialValue" ) , 1 , 0 , 0 } , { 29 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Merge" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 30 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Merge1" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 31 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Data Store Memory" ) , TARGET_STRING ( "InitialValue" ) , 0 , 0 , 0 } , { 32 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Data Store Memory1" ) , TARGET_STRING ( "InitialValue" ) , 0 , 0 , 0 } , { 33 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Data Store Memory" ) , TARGET_STRING ( "InitialValue" ) , 0 , 0 , 0 } , { 34 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Data Store Memory1" ) , TARGET_STRING ( "InitialValue" ) , 0 , 0 , 0 } , { 35 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Data Store Memory" ) , TARGET_STRING ( "InitialValue" ) , 0 , 0 , 0 } , { 36 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Data Store Memory1" ) , TARGET_STRING ( "InitialValue" ) , 0 , 0 , 0 } , { 37 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Data Store Memory" ) , TARGET_STRING ( "InitialValue" ) , 0 , 0 , 0 } , { 38 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Data Store Memory1" ) , TARGET_STRING ( "InitialValue" ) , 0 , 0 , 0 } , { 39 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem4/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 40 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem4/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 41 , TARGET_STRING ( "CPUTask_Sim/Subsystem1/If Action Subsystem/Constant" ) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 42 , TARGET_STRING ( "CPUTask_Sim/Subsystem1/If Action Subsystem/Constant1" ) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 43 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 44 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 45 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem2/res" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 46 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem2/value_out" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 47 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem2/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 48 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem2/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 49 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 50 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 51 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem2/res" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 52 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem2/value_out" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 53 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 54 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 55 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem2/res" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 56 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem2/value_out" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 57 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem/Constant" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 58 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 59 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem2/res" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 60 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem2/value_out" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 61 , TARGET_STRING ( "CPUTask_Sim/Subsystem1/If Action Subsystem/For Iterator Subsystem/For Iterator" ) , TARGET_STRING ( "IterationLimit" ) , 0 , 0 , 0 } , { 62 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem1/For Iterator Subsystem/Constant" ) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 63 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem1/For Iterator Subsystem/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 64 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem1/For Iterator Subsystem/Constant2" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 65 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem/Function-Call Subsystem1/For Iterator Subsystem/For Iterator" ) , TARGET_STRING ( "IterationLimit" ) , 0 , 0 , 0 } , { 66 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem1/For Iterator Subsystem/Constant" ) , TARGET_STRING ( "Value" ) , 1 , 0 , 0 } , { 67 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem1/For Iterator Subsystem/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 68 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem1/For Iterator Subsystem/Constant2" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 69 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem1/Function-Call Subsystem1/For Iterator Subsystem/For Iterator" ) , TARGET_STRING ( "IterationLimit" ) , 0 , 0 , 0 } , { 70 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem1/For Iterator Subsystem/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 71 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem1/For Iterator Subsystem/Constant2" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 72 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem2/Function-Call Subsystem1/For Iterator Subsystem/For Iterator" ) , TARGET_STRING ( "IterationLimit" ) , 0 , 0 , 0 } , { 73 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem1/For Iterator Subsystem/Constant1" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 74 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem1/For Iterator Subsystem/Constant2" ) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 75 , TARGET_STRING ( "CPUTask_Sim/Subsystem/Switch Case Action Subsystem3/Function-Call Subsystem1/For Iterator Subsystem/For Iterator" ) , TARGET_STRING ( "IterationLimit" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 } } ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 76 , 0 , TARGET_STRING ( "CPUTask_Sim/res" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 1 } , { 77 , 0 , TARGET_STRING ( "CPUTask_Sim/out" ) , TARGET_STRING ( "" ) , 2 , 0 , 0 , 0 , 1 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_ModelParameters rtModelParameters [ ] = { { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . bbkvllqsze , & rtB . evxnnnvraz ,
& rtB . bbkvllqsze , & rtB . evxnnnvraz , & rtB . bbkvllqsze , & rtB .
evxnnnvraz , & rtB . bbkvllqsze , & rtB . evxnnnvraz , & rtB . bbkvllqsze , &
rtB . evxnnnvraz , & rtB . bbkvllqsze , & rtB . evxnnnvraz , & rtB .
bbkvllqsze , & rtB . evxnnnvraz , & rtB . jhnifdm04yv . pjxodb2nb1 , & rtB .
jhnifdm04yv . e0womlsjmm , & rtB . cnsb0spyuq . pjxodb2nb1 , & rtB .
cnsb0spyuq . e0womlsjmm , & rtB . ax0jrtpwut . pjxodb2nb1 , & rtB .
ax0jrtpwut . e0womlsjmm , & rtB . jhnifdm04yv . pjxodb2nb1 , & rtB .
jhnifdm04yv . e0womlsjmm , & rtB . cnsb0spyuq . pjxodb2nb1 , & rtB .
cnsb0spyuq . e0womlsjmm , & rtB . ax0jrtpwut . pjxodb2nb1 , & rtB .
ax0jrtpwut . e0womlsjmm , & rtP . DataStoreMemory_InitialValue_glvqogqqzg , &
rtP . DataStoreMemory1_InitialValue_jiyg3kkzow , & rtP .
DataStoreMemory2_InitialValue , & rtP . Merge_InitialOutput , & rtP .
Merge1_InitialOutput , & rtP . DataStoreMemory_InitialValue , & rtP .
DataStoreMemory1_InitialValue , & rtP .
DataStoreMemory_InitialValue_lpsnntvi5e , & rtP .
DataStoreMemory1_InitialValue_brapdgvyi0 , & rtP .
DataStoreMemory_InitialValue_gzmuee1ywg , & rtP .
DataStoreMemory1_InitialValue_mnzngyb5ay , & rtP .
DataStoreMemory_InitialValue_pwe1ttvdh5 , & rtP .
DataStoreMemory1_InitialValue_cywkg1i2ev , & rtP . Constant_Value_iilw0smpge
, & rtP . Constant1_Value_moljqjpuv3 , & rtP . Constant_Value_mq0yqq5e0x , &
rtP . Constant1_Value_b00i5gskzd , & rtP . fficko2a024 . Constant_Value , &
rtP . fficko2a024 . Constant1_Value , & rtP . res_Y0 , & rtP . value_out_Y0 ,
& rtP . Constant_Value , & rtP . Constant1_Value_mvhnwcihcx , & rtP .
olreyz4euj . Constant_Value , & rtP . olreyz4euj . Constant1_Value , & rtP .
jhnifdm04yv . res_Y0 , & rtP . jhnifdm04yv . value_out_Y0 , & rtP .
axnaqsojmf . Constant_Value , & rtP . axnaqsojmf . Constant1_Value , & rtP .
cnsb0spyuq . res_Y0 , & rtP . cnsb0spyuq . value_out_Y0 , & rtP . ebgpvzxvo3
. Constant_Value , & rtP . ebgpvzxvo3 . Constant1_Value , & rtP . ax0jrtpwut
. res_Y0 , & rtP . ax0jrtpwut . value_out_Y0 , & rtP .
ForIterator_IterationLimit , & rtP . Constant_Value_dp3hb0zdw4 , & rtP .
Constant1_Value , & rtP . Constant2_Value , & rtP .
ForIterator_IterationLimit_hg54moyj5v , & rtP . Constant_Value_pwsvvqm1ni , &
rtP . Constant1_Value_cbj5azvbu2 , & rtP . Constant2_Value_az5chewn2m , & rtP
. ForIterator_IterationLimit_pmnerygy22 , & rtP . Constant1_Value_old3zd5smi
, & rtP . Constant2_Value_nvs1o44prj , & rtP .
ForIterator_IterationLimit_fr1lsyzo0v , & rtP . Constant1_Value_m12xkxpoza ,
& rtP . Constant2_Value_gpro0fhmc1 , & rtP .
ForIterator_IterationLimit_g3aj12bfdp , & rtY . e455jjhtvg , & rtY .
npoqspmaqz , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "int" ,
"int32_T" , 0 , 0 , sizeof ( int32_T ) , ( uint8_T ) SS_INT32 , 0 , 0 , 0 } ,
{ "signed char" , "int8_T" , 0 , 0 , sizeof ( int8_T ) , ( uint8_T ) SS_INT8
, 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } } ; static const uint_T rtDimensionArray [ ] = {
1 , 1 } ; static const real_T rtcapiStoredFloats [ ] = { 1.0 , 0.0 } ; static
const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( NULL ) , ( NULL ) , - 1 , 0
} , { ( const void * ) & rtcapiStoredFloats [ 0 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , ( int8_T ) 0 , ( uint8_T ) 0 } } ; static
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 26 ,
rtRootInputs , 0 , rtRootOutputs , 2 } , { rtBlockParameters , 50 ,
rtModelParameters , 0 } , { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap
, rtFixPtMap , rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float"
, { 2732562820U , 3618147763U , 1495580333U , 2324113380U } , ( NULL ) , 0 ,
( boolean_T ) 0 , rt_LoggedStateIdxList } ; const
rtwCAPI_ModelMappingStaticInfo * CPUTask_Sim_GetCAPIStaticMap ( void ) {
return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void CPUTask_Sim_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void CPUTask_Sim_host_InitializeDataMapInfo ( CPUTask_Sim_host_DataMapInfo_T
* dataMap , const char * path ) { rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ;
rtwCAPI_SetStaticMap ( dataMap -> mmi , & mmiStatic ) ;
rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetPath
( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
