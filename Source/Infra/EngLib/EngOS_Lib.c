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
#ifdef ENGOS_FREERTOS
TaskHandle_t Task1Handle = NULL;
TaskHandle_t Task2Handle = NULL;
#include "queue.h"
QueueHandle_t xQueue;
#elif ENGOS_UCOS
#endif

/**************************/


void EngOS_DWT_Init(void); // will move to HAL layer


void EngOS_Task_Create(void)
{
    EngIFSvc_IF_Entry();

#ifdef ENGOS_CMSIS
	/* Init scheduler */
	osKernelInitialize();

	osThreadNew(EngOS_Task_Main, NULL, NULL);
#elif ENGOS_FREERTOS
	xTaskCreate(EngOS_Task_Main, "EngIFSvc_IF_Main", 512, NULL, 1, NULL);
#elif ENGOS_UCOS
#endif
}

void EngOS_Task_Main(void *p_arg)
{
#ifdef ENGOS_CMSIS
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
#elif ENGOS_FREERTOS
	TickType_t xLastWakeTime;
	uint32_t startCycle, endCycle;
    uint32_t cycleDifference;
    float elapsedTimeUs;
    const TickType_t xFrequency = pdMS_TO_TICKS(1);  // 1msec cycle	

	// DWT Cycle Counter initialize
    EngOS_DWT_Init();

	// Save Tick at the time of task creation
    xLastWakeTime = xTaskGetTickCount();
#elif ENGOS_UCOS
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
#ifdef ENGOS_CMSIS
		nextWakeTicks += intervalTicks;
		osDelayUntil(nextWakeTicks);
#elif ENGOS_FREERTOS
		vTaskDelayUntil(&xLastWakeTime, xFrequency);
#elif ENGOS_UCOS
#endif		
	}
}

void EngOS_Task_Start(void)
{
#ifdef ENGOS_CMSIS
	osKernelStart();
#elif ENGOS_FREERTOS
	vTaskStartScheduler();
#elif ENGOS_UCOS
#endif
}

void EngOS_Task_End(void)
{
#ifdef ENGOS_CMSIS
#elif ENGOS_FREERTOS
	vTaskEndScheduler();
#elif ENGOS_UCOS
#endif
}

SemaphoreId EngOS_CreateSemaphore(U8* pubSemaphoreName)
{
#ifdef ENGOS_CMSIS
	return (SemaphoreId)osSemaphoreNew(1, 0, NULL); // Binary semaphore
#endif
}

void EngOS_ReleaseSemaphore(SemaphoreId id)
{
#ifdef ENGOS_CMSIS
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
