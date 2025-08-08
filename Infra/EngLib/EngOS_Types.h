/**
 * @file        EngOS_Types.h
 * @brief       This is type definition file for Engine OS Interface Component.
 *
 * <b> Copyright 2024 by Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeognseob Kim
 * @imp			Jeognseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		03/11/2008(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGOS_TYPES_H__
#define __ENGOS_TYPES_H__

#include "EngCM_SystemConfig.h"
#include "Eng_Macro.h"

#if defined(ENGOS_CMSIS_V2)
    #include "FreeRTOS.h"
    #include "task.h"

    typedef osMutexId_t         MutexId;
    typedef osSemaphoreId_t     SemaphoreId;
    typedef osMessageQueueId_t  MsgQueueId;
#elif defined(ENGOS_FREERTOS)
    #include "FreeRTOS.h"
    #include "task.h"
    #include "semphr.h"

    typedef SemaphoreHandle_t   MutexId;
    typedef SemaphoreHandle_t   SemaphoreId;
    typedef SemaphoreHandle_t   MsgQueueId;
#elif defined(ENGOS_UCOS)
    #define EngOS_Mutex OS_MUTEX 
    #define EngOS_Semaphore OS_SEMAPHORE
    #define EngOS_Queue OS_Q
#endif

typedef enum _TTaskRunType
{
    TASK_RUNTYPE_Interrupt,
    TASK_RUNTYPE_Cycle,
    TASK_RUNTYPE_Undefiined
} TTaskRunType;

typedef struct _TTaskProperty
{
    U8* pubName;
    void* pfnTaskFunc;
    TTaskRunType eRunType;
    U32 ulIntervalTime; // msec

#if defined(ENGOS_CMSIS_V2)
    osThreadId_t stTaskHandle;
#elif defined(ENGOS_FREERTOS)
    TaskHandle_t stTaskHandle;
#elif defined(ENGOS_UCOS)
#endif    
} TTaskProperty;

/*
 * @brief Structure Definitions
 */

#define OS_TASK_MAX_SIZE    10

typedef struct _TOSTaskManager
{
    TTaskProperty astTaskProperties[OS_TASK_MAX_SIZE];
    U8 ubUsedCount;

} TOSTaskManager;

#endif //__ENGOS_TYPES_H__