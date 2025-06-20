 /**
 * @file        EngOS_Lib.h
 * * @brief       This is header file for EngOS Component
 *
 * <b> Copyright 2024 by Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		08/05/2009(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGOS_LIB_H__
#define __ENGOS_LIB_H__

#undef EXTERN
#ifdef __ENGOS_LIB_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "EngOS_Types.h"

/* OS Interface */
EXTERN void EngOS_LibraryEntry(void);
EXTERN void EngOS_RegistryJob(TJobProperty* pJobProperty); // Registery Task/Thread/Etc...
EXTERN void EngOS_PendingJob(TJobProperty* pJobProperty); // Use this in front of main routine
EXTERN void EngOS_WaitingJob(TJobProperty* pJobProperty, U32 ulPreviousWakeTime); // Use this after main routine
EXTERN void EngOS_NotifyFromISR(TJobProperty* pJobProperty);
EXTERN TJobProperty EngOS_CreateJobProperty(U8* pubName, void* pfnFunc, TJobRunType eRunType, U32 ulInterval);
EXTERN U32 EngOS_GetSysTick(void);

EXTERN void EngOS_StartJobs(void);
EXTERN void EngOS_EndJobs(void);

EXTERN void EngOS_Task_Main(void *p_arg);

EXTERN SemaphoreId EngOS_CreateSemaphore(U8* pubSemaphoreName);
EXTERN void EngOS_ReleaseSemaphore(SemaphoreId id);


#endif /* __ENGOS_LIB_H__ */

