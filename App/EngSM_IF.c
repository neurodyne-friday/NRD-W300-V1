/**
 * @file        EngSM_IF.c
 * @brief       This is I/F code for System Manager Component.
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
 * @date		03/11/2008(D/M/Y)
 * @version		V0.1
 */

#define	__ENGSM_IF_C__

#include "Eng_CommonType.h"
#include "EngSM_IF.h"
#include "EngSM_Main.h"
#include "EngIFSvc_IF.h"
#include "EngFOC_IF.h"


/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
BOOL EngSM_IF_Initialize(void)
{
	TTaskProperty* pstTaskProperty = NULL;
	DBG_ENGSM(ENG_DBG_STRING"EngSM_IF_Initialize", ENG_TICK, "EngSM");
	
	/* Initialize the Engine Library */
	EngLib_IF_Entry(INIT_STEP_1ST);
	EngLib_IF_Entry(INIT_STEP_2ND);
   	
    /* Register the Hardware Interrupts */
#ifndef USE_ENGOS_CURRENT_TASK_LOOP
	EngLib_IF_RegistryCallBackFunc("EngFOC_IF_NotifyByADCIRQ", HAL_EVENT_ADC_IRQ, EngFOC_IF_NotifyByADCIRQ);
#endif
	EngLib_IF_RegistryCallBackFunc("EngIFSvc_IF_NotifyByCAN1Rx", HAL_EVENT_CAN1_RX, EngIFSvc_IF_NotifyByCAN1Rx);
	EngLib_IF_RegistryCallBackFunc("EngSM_IF_NotifyByPowerOff", HAL_EVENT_PWR_OFF, EngSM_IF_NotifyByPowerOff);

    /* Initialize the Hardware */   
    EngHAL_LibraryEntry();

    /* Do power on sequence: backup data restore */
	EngSM_PowerOn();

	/* Create & Initialize Device Driver */
	EngDrv_IF_Create();
	EngDrv_IF_Initialize();

    /* Initialize the Engine Dinamic Configuration Manager */
#ifdef FR_SM_ENGINE_FAST_BOOTUP
	EngCM_IF_FastEngineInitialize();
#else
	//EngCM_IF_Initialize();
#endif

	/* Create and register SM Task */
    EngOS_Task_Register(EngOS_Task_CreateProperty("SystemManagerTask", 
		EngSM_IF_Main, TASK_RUNTYPE_Cycle, 1));

	/* Initialize the Engine System Manager */
    return EngSM_Initialize();
}

/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngSM_IF_Start(void)
{
	// Set system state to ACTIVE
	EngSM_IF_SetState(ENG_ST_ACTIVE);
}


/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
BOOL EngSM_IF_SetDeviceStatus(U32 ulStatusID, U32 ulNewValue, U32 ulSetReset)
{
    return EngSM_SetDeviceStatus(ulStatusID, ulNewValue, ulSetReset);
}

 
/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
U32 EngSM_IF_GetDeviceStatus(U32 ulStatusID)
{
    return EngSM_GetDeviceStatus(ulStatusID);
}

 
/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
U32 EngSM_IF_SendEvent(U32 ulEventID, TStateMachine *pstStateMachine, U32 ulLParam, U32 ulRParam)
{
	return EngSM_SendEvent(ulEventID, pstStateMachine, ulLParam, ulRParam);
}


/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void *EngSM_IF_GetFeature(U32 ulFeatureID)
{
    return EngSM_GetFeature(ulFeatureID);
}

/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
BOOL EngSM_IF_IsIntervalTimeValid(TIntervalTimeType enType)
{
    return EngSM_IsIntervalTimeValid(enType);
}

/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
U32 EngSM_IF_GetIntervalTime(TIntervalTimeType enType)
{
    return EngSM_GetIntervalTime(enType);
}

/** 
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/

void EngSM_IF_Main(void)
{
	TTaskProperty *pstTaskProperty = EngOS_Task_GetProperty("SystemManagerTask");
	U32 lastWakeTime = EngOS_GetSysTick();

	if(pstTaskProperty == NULL)
	{
		DBG_ENGSM(ENG_DBG_STRING"Error!! Task Property is NULL", ENG_TICK, "SM");
		return;

	}
	for(;;) 
	{
		EngSM_Main();

		//EngHAL_CAN_GetRxFifoFillLevel(HAL_CAN_NAME_MOTOR_CTRL);

		EngOS_Task_Waiting(pstTaskProperty, &lastWakeTime);
	}
}


/** 
* @brief	   	Set system state value
* @param[in]	None
* @range			
* @retval		None
* @global			
* @remarks     		
*/
void EngSM_IF_SetState(TEngState eNewState)
{
	EngSM_SetState(eNewState);
}

/** 
* @brief	   	Get system state value
* @param[in]	None
* @range			
* @retval		None
* @global			
* @remarks     		
*/
TEngState EngSM_IF_GetState(void)
{
	return EngSM_GetState();
}

/** 
* @brief	   	Power off the system
* @param[in]	None
* @range			
* @retval		None
* @global			
* @remarks     		
*/

void EngSM_IF_NotifyByPowerOff(U8* pubData, U32 ulLength)
{
	EngSM_PowerOff();
}
