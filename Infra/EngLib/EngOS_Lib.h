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

EXTERN void EngOS_Task_Register(TTaskProperty* pTaskProperty); // Registery Task/Thread/Etc...
EXTERN void EngOS_Task_Pending(TTaskProperty* pTaskProperty); // Use this in front of main routine
EXTERN void EngOS_Task_Waiting(TTaskProperty* pTaskProperty, U32* ulPreviousWakeTime); // Use this after main routine
EXTERN void EngOS_NotifyFromISR(TTaskProperty* pTaskProperty);

EXTERN TTaskProperty* EngOS_Task_CreateProperty(U8* pubName, void* pfnFunc, TTaskRunType eRunType, U32 ulInterval);
EXTERN TTaskProperty* EngOS_Task_GetProperty(U8* pubName);

EXTERN void EngOS_Task_StartAll(void);
EXTERN void EngOS_Task_EndAll(void);

EXTERN void EngOS_Delay(U32 ulDelayTime); // msec
EXTERN U32 EngOS_GetSysTick(void);

EXTERN SemaphoreId EngOS_CreateSemaphore(U8* pubSemaphoreName);
EXTERN void EngOS_ReleaseSemaphore(SemaphoreId id);


#endif /* __ENGOS_LIB_H__ */

