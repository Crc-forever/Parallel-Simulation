#ifndef CPUTask_Sim_private_h_
#define CPUTask_Sim_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "CPUTask_Sim.h"
#include "CPUTask_Sim_types.h"
#if !defined(rt_VALIDATE_MEMORY)
#define rt_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
    ssSetErrorStatus(rtS, RT_MEMORY_ALLOCATION_ERROR);\
    }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((ptr));\
    (ptr) = (NULL);\
    }
#else
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((void *)(ptr));\
    (ptr) = (NULL);\
    }
#endif
#endif
extern void fficko2a02 ( int32_T * fhk2rmqawn , int32_T * a5zix1anfk ,
adf1c3xc20 * localDW , jjdkemctyj * localP ) ; extern void anjfxpvcef ( cf1kq4ncbc * localB , og1v340kmp * localP ) ; extern void jhnifdm04y ( const int32_T * oo4yjq1kku , const int32_T * pxqdlgll5t , cf1kq4ncbc * localB , i1t5gkpgw1 * localDW ) ;
#if defined(MULTITASKING)
#error Model (CPUTask_Sim) was built in \SingleTasking solver mode, however the MULTITASKING define is \present. If you have multitasking (e.g. -DMT or -DMULTITASKING) \defined on the Code Generation page of Simulation parameter dialog, please \remove it and on the Solver page, select solver mode \MultiTasking. If the Simulation parameter dialog is configured \correctly, please verify that your template makefile is \configured correctly.
#endif
#endif
