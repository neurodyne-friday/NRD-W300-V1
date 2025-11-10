/**
 * @file        EngOS_Lib.c
 * @brief       This is main code for Engine Configuration Manager Component.
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
 * @date		14/04/2009(D/M/Y)
 * @version		V0.1
 */

#define	__ENGOS_LIB_C__

#include "Eng_CommonType.h"
#include "EngLib_Types.h"
//#include "EngOS_Types.h"
#include "EngOS_Lib.h"
//#include "EngIFSvc_IF.h"

/**************************
* Task Variables
***************************/
#if defined(ENGOS_FREERTOS)
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;
#include "queue.h"
QueueHandle_t xQueue;
#elif defined(ENGOS_UCOS)
#endif

static TOSTaskManager g_stOSTaskManager;

/**************************/


void EngOS_LibraryEntry(void)
{
	g_stOSTaskManager.ubUsedCount = 0;
}

void EngOS_Task_Register(TTaskProperty* pProperty)
{
	if(pProperty == NULL)
		return;

#if defined(ENGOS_CMSIS_V2)
	/* Init scheduler */
	osKernelInitialize();
	osThreadNew(pJobProperty->pfnJobFunc, NULL, NULL);
#elif defined(ENGOS_FREERTOS)
	BaseType_t ok = pdFALSE;
	if(pProperty->eRunType == TASK_RUNTYPE_Cycle)
		ok = xTaskCreate(pProperty->pfnTaskFunc, pProperty->pubName, 512, NULL, 1, NULL);
	else
		ok = xTaskCreate(pProperty->pfnTaskFunc, pProperty->pubName, 512, NULL, tskIDLE_PRIORITY + 3, &pProperty->stTaskHandle);
	configASSERT(ok == pdPASS);
#elif defined(ENGOS_UCOS)
#endif

	//EngHAL_Delay(2); // Task Create Delay
}

void EngOS_Task_Pending(TTaskProperty* pProperty)
{
	if(pProperty == NULL)
		return;

#if defined(ENGOS_CMSIS_V2)
	osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);
#elif defined(ENGOS_FREERTOS)
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
#elif defined(ENGOS_UCOS)
#endif
}


void EngOS_Delay(U32 ulDelayTime)
{
#if defined(ENGOS_CMSIS_V2)
#elif defined(ENGOS_FREERTOS)
	vTaskDelay(pdMS_TO_TICKS(ulDelayTime));
#elif defined(ENGOS_UCOS)
#endif
}


U32 EngOS_GetSysTick(void)
{
#if defined(ENGOS_CMSIS_V2)
#elif defined(ENGOS_FREERTOS)
	return (U32)xTaskGetTickCount();
#elif defined(ENGOS_UCOS)
#endif
}

void EngOS_Task_Waiting(TTaskProperty* pProperty, U32* ulPreviousWakeTime)
{
	if(pProperty == NULL)
		return;

#if defined(ENGOS_CMSIS_V2)
#elif defined(ENGOS_FREERTOS)
	vTaskDelayUntil(ulPreviousWakeTime, pdMS_TO_TICKS(pProperty->ulIntervalTime));
#elif defined(ENGOS_UCOS)
#endif
}

void EngOS_NotifyFromISR(TTaskProperty* pProperty)
{
	if(pProperty == NULL)
		return;

#if defined(ENGOS_CMSIS_V2)
#elif defined(ENGOS_FREERTOS)
    BaseType_t xHigherPTWoken = pdFALSE;
	vTaskNotifyGiveFromISR(pProperty->stTaskHandle, &xHigherPTWoken);
	portYIELD_FROM_ISR(xHigherPTWoken);
#elif defined(ENGOS_UCOS)
#endif
}

TTaskProperty* EngOS_Task_CreateProperty(U8* pubName, void* pfnFunc(void*), TTaskRunType eRunType, U32 ulInterval)
{
	if(g_stOSTaskManager.ubUsedCount >= OS_TASK_MAX_SIZE)
	{
		return NULL;
	}

	TTaskProperty* pstProperty = &g_stOSTaskManager.astTaskProperties[g_stOSTaskManager.ubUsedCount];
	pstProperty->pubName = pubName;
	pstProperty->pfnTaskFunc = pfnFunc;
	pstProperty->eRunType = eRunType;
	pstProperty->ulIntervalTime = ulInterval;
#if defined(ENGOS_CMSIS_V2)
#elif defined(ENGOS_FREERTOS)
	pstProperty->stTaskHandle = NULL;
#elif defined(ENGOS_UCOS)
#endif    

	g_stOSTaskManager.ubUsedCount++;

	return pstProperty;
}

TTaskProperty* EngOS_Task_GetProperty(U8* pubName)
{
	for(U8 ubIndex = 0; ubIndex < g_stOSTaskManager.ubUsedCount; ubIndex++)
	{
		if(strcmp(pubName, g_stOSTaskManager.astTaskProperties[ubIndex].pubName) == 0)
		{
			return &g_stOSTaskManager.astTaskProperties[ubIndex];
		}
	}

	return NULL;
}

void EngOS_Task_StartAll(void)
{
#if defined(ENGOS_CMSIS_V2)
	osKernelStart();
#elif defined(ENGOS_FREERTOS)
	vTaskStartScheduler();
#elif defined(ENGOS_UCOS)
#endif
}

void EngOS_Task_EndAll(void)
{
#if defined(ENGOS_CMSIS_V2)
#elif defined(ENGOS_FREERTOS)
	vTaskEndScheduler();
#elif defined(ENGOS_UCOS)
#endif
}


SemaphoreId EngOS_CreateSemaphore(U8* pubSemaphoreName)
{
#ifdef ENGOS_CMSIS_V2
	return (SemaphoreId)osSemaphoreNew(1, 0, NULL); // Binary semaphore
#endif
}

void EngOS_ReleaseSemaphore(SemaphoreId id)
{
#ifdef ENGOS_CMSIS_V2
	osSemaphoreRelease(id);
#endif
}

