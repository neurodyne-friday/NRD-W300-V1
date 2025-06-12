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
#include "EngIFSvc_IF.h"

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

/**************************/


void EngOS_DWT_Init(void); // will move to HAL layer


void EngOS_LibraryEntry(void)
{

}

void EngOS_RegistryJob(TJobProperty* pJobProperty)
{
	if(pJobProperty == NULL)
		return;

#if defined(ENGOS_CMSIS_V2)
	/* Init scheduler */
	osKernelInitialize();
	osThreadNew(pJobProperty->pfnJobFunc, NULL, NULL);
#elif defined(ENGOS_FREERTOS)
	xTaskCreate(pJobProperty->pfnJobFunc, pJobProperty->pubName, 512, NULL, 1, NULL);
#elif defined(ENGOS_UCOS)
#endif
}

void EngOS_PendingJob(TJobProperty* pJobProperty)
{
	if(pJobProperty == NULL)
		return;

#if defined(ENGOS_CMSIS_V2)
#elif defined(ENGOS_FREERTOS)
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
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

void EngOS_WaitingJob(TJobProperty* pJobProperty, U32 ulPreviousWakeTime)
{
	if(pJobProperty == NULL)
		return;

#if defined(ENGOS_CMSIS_V2)
#elif defined(ENGOS_FREERTOS)
	vTaskDelayUntil(&ulPreviousWakeTime, (TickType_t)pJobProperty->ulIntervalTime);
#elif defined(ENGOS_UCOS)
#endif
}


void EngOS_Task_Create(void)
{
    EngIFSvc_IF_Entry();

#if defined(ENGOS_CMSIS_V2)
	/* Init scheduler */
	osKernelInitialize();

	osThreadNew(EngOS_Task_Main, NULL, NULL);
#elif defined(ENGOS_FREERTOS)
	xTaskCreate(EngOS_Task_Main, "EngIFSvc_IF_Main", 512, NULL, 1, NULL);
#elif defined(ENGOS_UCOS)
#endif
}

void EngOS_Task_Main(void *p_arg)
{
#if defined(ENGOS_CMSIS)
	uint32_t nextWakeTicks;
	uint32_t startCycle, endCycle;
    uint32_t cycleDifference;
    float elapsedTimeUs;
	uint32_t tickFreq = osKernelGetTickFreq();
    uint32_t intervalTime = 1;  // 1msec cycle	
	uint32_t intervalTicks = (intervalTime * tickFreq) / 1000;  // msec to ticks

	// DWT Cycle Counter initialize
    EngOS_DWT_Init();

	// Save Tick at the time of task creation
	nextWakeTicks = osKernelGetTickCount();
#elif defined(ENGOS_FREERTOS)
	TickType_t xLastWakeTime;
	uint32_t startCycle, endCycle;
    uint32_t cycleDifference;
    float elapsedTimeUs;
    const TickType_t xFrequency = pdMS_TO_TICKS(1);  // 1msec cycle	

	// DWT Cycle Counter initialize
    EngOS_DWT_Init();

	// Save Tick at the time of task creation
    xLastWakeTime = xTaskGetTickCount();
#elif defined(ENGOS_UCOS)
#endif

	while(1)
	{
		// Start to measure time using DWT Cycle Counter
        startCycle = DWT->CYCCNT;

		// Temporary use
		EngTimerSvc_IF_Main();

		// Execute registered tasks
        EngIFSvc_IF_Main();

		// Finish time measure using DWT Cycle Counter
        endCycle = DWT->CYCCNT;
        cycleDifference = endCycle - startCycle;
        elapsedTimeUs = (float)cycleDifference / (SystemCoreClock / 1000000);  // convert usec

		//DBG_UART(ENG_DBG_STRING"Elapsed Time: %.2f usec \n", ENG_TICK, "EngOS", elapsedTimeUs);

        // Wait for the next cycle to start exactly 1ms later
#if defined(ENGOS_CMSIS_V2)
		nextWakeTicks += intervalTicks;
		osDelayUntil(nextWakeTicks);
#elif defined(ENGOS_FREERTOS)
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
#elif defined(ENGOS_UCOS)
#endif		
	}
}

void EngOS_StartJobs(void)
{
#if defined(ENGOS_CMSIS_V2)
	osKernelStart();
#elif defined(ENGOS_FREERTOS)
	vTaskStartScheduler();
#elif defined(ENGOS_UCOS)
#endif
}

void EngOS_EndJobs(void)
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

void EngOS_DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // TRCENA bit activate
	DWT->LAR = 0xC5ACCE55; 
    DWT->CYCCNT = 0;                                // Cycle-counter initialize
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;            // Cycle-counter activate
}
