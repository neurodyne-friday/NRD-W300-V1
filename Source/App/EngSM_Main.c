/**
 * @file        EngSM_Main.c
 * @brief       This main code for State Manager Component.
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
 * @date		08/11/2008(D/M/Y)
 * @version		V0.1
 */

#define	__ENGSM_MAIN_C__

#include "Eng_CommonType.h"
#include "EngSM_Main.h"
#include "EngFOC_Main.h"

/* Initilize the Engine System Manager infomation */
static TEngSystemManager s_stSystemManager;

static U32 s_ulEngSMMainTaskID;
static U32 s_ulIntervalTimer[INTERVAL_TIME_MAX] = {0,0,0,0};
static BOOL s_fIntervalTimerGetValid[INTERVAL_TIME_MAX] = {FALSE,FALSE,FALSE,FALSE};

#define ENGSM_TASK_STACK_SIZE	1024
#define ENGSM_TASK_PRIORITY		150


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/

BOOL EngSM_Initialize(void)
{
	TEngSystemManager *pstSystemManager = &s_stSystemManager;
	
	DBG_ENGSM(ENG_DBG_STRING"EngSM_Initialize", ENG_TICK, "SM");
	

    /* Initialize Engine System Manager Information Storage Variable */
//	EngLib_MemorySet(pstSystemManager, 0, (sizeof(TEngSystemManager)));

	EngSM_Constructor(pstSystemManager);

	/* Initialize the state, status, timing and page class for Engine System Manager */
	//EngSM_InitState(pstSystemManager);

	/* Create the Engine Component Handler */
	//EngSM_HndIF_CreateHandler();

	/* Initialize the Engine Component(paper, image, heating, error, option) Handler */
	//EngSM_HndIF_Initialize();

	/* Send the first event about power on */

	if((EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_ENGINE_STATE) == ENGSM_STS_CHILD_ENGINE_TEST)
#if defined(HR_SM_SET_BOARD_CONFIG) && defined(HR_SM_SET_BOARD_CONFIG_PBA_MODE)
//		|| ((EngCM_IF_IsUsingBoardConfiguration(BOARD_CONFIG_IDPTV3_MODE) == TRUE) && ((U16)EngCM_IF_GetBoardConfiguration(BOARD_CONFIG_IDPTV3_MODE) == C_SM_IDPTV3_MODE_INPUT))
		|| ((EngCM_IF_IsUsingBoardConfiguration(BOARD_CONFIG_PBA_MODE) == TRUE)	&& (EngCM_IF_GetBoardConfiguration(BOARD_CONFIG_PBA_MODE) == C_SM_PBA_MODE_IO_INPUT))
#endif
	)
	{
		EngSM_SendEvent(ENG_EV_TEST_MODE_ON, NULL, 0, 0);
	}
	else if(EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_ENGINE_STATE) == ENGSM_STS_CHILD_ENGINE_ERROR)
	{
		//EngSM_HndIF_StartHandler(ENG_HND_EH, ERROR_NAME_ASSERT, NULL);
	}	
	else
	{
		EngSM_SendEvent(ENG_EV_POWER_ON, NULL, 0, 0);
	}

	EngSM_InitialIntervalTime();

	// Create Jobs for FOC Handler
	EngFOC_Initialize();

	// Start OS-Jobs
	EngOS_StartJobs();

	pstSystemManager->fPowerOn = TRUE;
	pstSystemManager->fEnterSleepP2Mode = FALSE;

    return TRUE;
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
void EngSM_Constructor(TEngSystemManager *pstSystemManager)
{
	pstSystemManager->enPrevEngState					= ENG_ST_UNSPECIFIED;
	pstSystemManager->enPrevStateBeforeSleep			= ENG_ST_UNSPECIFIED;
	pstSystemManager->enEngState						= ENG_ST_UNSPECIFIED;
	pstSystemManager->ulEvent							= ENG_EV_UNSPECIFIED;
	pstSystemManager->ulReceivedEvent					= ENG_EV_UNSPECIFIED;
}

TEngSystemManager *EngSM_GetManager(void)
{
    return &s_stSystemManager;
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
BOOL EngSM_SetDeviceStatus(U32 ulStatusID, U32 ulNewValue, U32 ulSetReset)
{
	BOOL fReturnVal = FALSE;

	if(ulSetReset == STATUS_SET)
	{
	    fReturnVal = EngSM_SetStatus(ulStatusID, ulNewValue);
    }
    else if(ulSetReset == STATUS_RESET)
    {
    	fReturnVal = EngSM_ResetStatus(ulStatusID, ulNewValue);
    }

    return fReturnVal;
}

/**
* @brief			To get DeviceStatus information.
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
U32 EngSM_GetDeviceStatus(U32 ulStatusID)
{
    //return EngSM_GetStatus(ulStatusID);
	return 0;
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
void EngSM_StartTimingChart(void *pvTimingObj, U32 ulTimingID)
{
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
U32 EngSM_SendEvent(U32 ulEventID, TStateMachine *pstStateMachine, U32 ulLParam, U32 ulRParam)
{
	U32 ulEventReturn = 0;
	TEngSystemManager *pstSystemManager = &s_stSystemManager;
	TMsgQCB *pstSystemMgrMsgQCB = &pstSystemManager->stMsgQCB;
	TMsgQ stSendMsgQ = {0};
	TEngState enNextState = ENG_ST_UNSPECIFIED;

	stSendMsgQ.ulMsgID = ulEventID;
	stSendMsgQ.ulLParam = ulLParam;
	stSendMsgQ.ulRParam = ulRParam;

//	DBG_ENGSM("\r\n[EngSM] Send Event ID=%x,%d,%d", ulEventID, ulLParam, ulRParam);

	switch(MESSAGE_GET_TYPE(ulEventID))
	{
		case MESSAGE_TYPE_SPOT:
			//ulEventReturn = EngSM_DispatchMessage(&stSendMsgQ);
			break;

		case MESSAGE_TYPE_STATEMACHINE:
			//ulEventReturn = EngSM_DispatchMessage(&stSendMsgQ);

			/* Send the received event to print state machine */
			EngLib_StateMachine(&pstSystemManager->stPrintStateMachine, ulEventID, pstSystemManager);

			/* Change the state machine of Engine System Manager according to the event */
			enNextState = (TEngState)EngLib_StateMachine(&pstSystemManager->stStateMachine, ulEventID, pstSystemManager);

			/* Update the Status DB of Engine System Manager */
			EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);

			break;

		case MESSAGE_TYPE_INFORMATION:
			/* Send the received event to message queue of state machine */
			if(!EngLib_SendMsgQ(pstSystemMgrMsgQCB, &stSendMsgQ))
			{
				DBG_ENGSM(ENG_DBG_STRING"Message Q of information is Full", ENG_TICK, "SM");
				
			}
			break;

		default:
			DBG_ENGSM(ENG_DBG_STRING"Event ID is not valid", ENG_TICK, "SM");
			break;
	}
	
	return (BOOL)ulEventReturn;
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
void *EngSM_GetFeature(U32 ulFeatureID)
{
	TEngSystemManager *pstSystemManager = &s_stSystemManager;
	U32 ulComponent = FEATURE_GET_SOURCE(ulFeatureID);
	void *pvEntry = NULL;

	switch(ulComponent)
	{
		case ENGSM_FEATURE:
			switch(ulFeatureID)
			{
				case ENGSM_GET_MANAGER:
					pvEntry = (void *)&s_stSystemManager;
					// TEngSystemManager *pstSystemManager = (TEngSystemManager *)EngSM_IF_GetFeature(ENGSM_GET_MANAGER);
					break;					
				default:
					break;
			}
			break;
		default:
			break;
	}

	ASSERT(pvEntry);
	
	return pvEntry;
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
void EngSM_InitialIntervalTime(void)
{
	U32 ulIndex = 0;

	for(ulIndex = 0; ulIndex < INTERVAL_TIME_MAX; ulIndex++)
	{
		s_ulIntervalTimer[ulIndex] = 0;
		s_fIntervalTimerGetValid[ulIndex] = FALSE;
	}
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
void EngSM_CountIntervalTime(void)
{
	TEngSystemManager *pstSystemManager = &s_stSystemManager;	
	U32	ulEngState = EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_ENGINE_STATE);
	static U32 ulPrevEngState = 0;
	static U32 ulNonSleepModeCnt = 0;
	static BOOL fPowerOnInt = TRUE;
	static BOOL fRTCChecked = FALSE;
	static BOOL fPrintChecked = FALSE;

	if(fRTCChecked)
	{
		if(fPowerOnInt == TRUE)
		{
			U32 ulPowerOffTime = 0;//EngTM_IF_GetElapsedTime(RTCITEM_POWEROFF);

			ulPowerOffTime = MINUTE_TO_MS(ulPowerOffTime);
			s_ulIntervalTimer[INTERVAL_TIME_POWER_OFF] = ulPowerOffTime;								
			s_ulIntervalTimer[INTERVAL_TIME_JOB] = ulPowerOffTime;

			s_fIntervalTimerGetValid[INTERVAL_TIME_POWER_OFF] = TRUE;
			s_fIntervalTimerGetValid[INTERVAL_TIME_JOB] = TRUE;
			
			fPowerOnInt = FALSE;
			ulPrevEngState = ulEngState;
			
			DBG_ENGSM(ENG_DBG_STRING"Power Off ElapsedTime:%umin", ENG_TICK, "SM", MS_TO_MINUTE(ulPowerOffTime));
			return;		
		}
			
		if((ulPrevEngState != ENGSM_STS_CHILD_ENGINE_SLEEP) && (ulEngState == ENGSM_STS_CHILD_ENGINE_SLEEP))			//Sleep Entry
		{
			//EngTM_IF_SetCurrentTime(RTCITEM_SLEEP);
			//EngTM_IF_SetCurrentTime(RTCITEM_POWEROFF);

			s_ulIntervalTimer[INTERVAL_TIME_SLEEP] = 0;
			s_fIntervalTimerGetValid[INTERVAL_TIME_SLEEP] = FALSE;

			//DBG_LMS_DATE(ENG_DBG_STRING"SetSleepElapsedTime", ENG_TICK, "RTC");
		}
		else if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_SLEEP) && (ulEngState != ENGSM_STS_CHILD_ENGINE_SLEEP))		//Sleep Exit
		{
			U32 ulSleepElapsedTime = 0;//EngTM_IF_GetElapsedTime(RTCITEM_SLEEP);

			//DBG_LMS_DATE(ENG_DBG_STRING"SleepElapsedTime:%umin", ENG_TICK, "RTC", ulSleepElapsedTime);
			
			ulSleepElapsedTime = MINUTE_TO_MS(ulSleepElapsedTime);
			s_ulIntervalTimer[INTERVAL_TIME_SLEEP] = ulSleepElapsedTime;
			s_ulIntervalTimer[INTERVAL_TIME_JOB] = (ulSleepElapsedTime > (MAX_U32 - s_ulIntervalTimer[INTERVAL_TIME_JOB])) ? MAX_U32 : s_ulIntervalTimer[INTERVAL_TIME_JOB] + ulSleepElapsedTime;
			
			s_fIntervalTimerGetValid[INTERVAL_TIME_SLEEP] = TRUE;
		}
		else if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_PRINTING))	//Print Exit
		{
			s_ulIntervalTimer[INTERVAL_TIME_JOB] = 0;
		}
		else if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_WAITING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_WAITING))	//Wait Exit
		{
		}
		else if((ulEngState != ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_SLEEP))
		{
			s_ulIntervalTimer[INTERVAL_TIME_JOB] = U32_SUM_CHK_WITH_OVF(s_ulIntervalTimer[INTERVAL_TIME_JOB], 10);
		}
		else if(((ulEngState == ENGSM_STS_CHILD_ENGINE_WAITING) && (ulPrevEngState != ENGSM_STS_CHILD_ENGINE_WAITING))
			|| ((ulEngState == ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulPrevEngState != ENGSM_STS_CHILD_ENGINE_PRINTING))
		)
		{
		}

		if((ulPrevEngState != ENGSM_STS_CHILD_ENGINE_STANDBY) && (ulEngState == ENGSM_STS_CHILD_ENGINE_STANDBY))
		{
			s_ulIntervalTimer[INTERVAL_TIME_READY] = 0;
		}
		else if(ulEngState == ENGSM_STS_CHILD_ENGINE_STANDBY)
		{
			s_ulIntervalTimer[INTERVAL_TIME_READY] = U32_SUM_CHK_WITH_OVF(s_ulIntervalTimer[INTERVAL_TIME_READY], 10);
		}

		if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_WAITING))
		{
		}
		else if(ulEngState == ENGSM_STS_CHILD_ENGINE_PRINTING)
		{
			fPrintChecked = TRUE;
		}
		else if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState == ENGSM_STS_CHILD_ENGINE_WAITING))
		{
		}
		
		/* To save the latest run time for get power off elapsed time */
		if(ulEngState != ENGSM_STS_CHILD_ENGINE_SLEEP) 
		{
			if(++ulNonSleepModeCnt >= 5 * 60 * 100)			/* every 5minute */
			{
				//EngTM_IF_SetCurrentTime(RTCITEM_POWEROFF);

				ulNonSleepModeCnt = 0;
				//DBG_LMS_DATE(ENG_DBG_STRING"SetSleepElapsedTime2", ENG_TICK, "RTC");
			}
		}
		else
		{
			ulNonSleepModeCnt = 0;
		}
		
		ulPrevEngState = ulEngState;
	}
	else if(g_ulEngTickCnt >= 400)
	{
	 	fRTCChecked = TRUE;
	}
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
BOOL EngSM_IsIntervalTimeValid(TIntervalTimeType enType)
{
	BOOL fIntervalTimeValid = FALSE;

	if(enType < INTERVAL_TIME_MAX)
	{
		fIntervalTimeValid = s_fIntervalTimerGetValid[enType];
	}
		
	return fIntervalTimeValid;
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
U32 EngSM_GetIntervalTime(TIntervalTimeType enType)
{
	U32 ulIntervalTime = 0;

	if(enType < INTERVAL_TIME_MAX)
	{
		ulIntervalTime = s_ulIntervalTimer[enType];
	}
		
//	DBG_ENGSM(ENG_DBG_STRING"ReturnIntervalTime[%d]:%dsec", ENG_TICK, "SM", enType, s_ulIntervalTimer/1000);

	return ulIntervalTime;
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
BOOL EngSM_Main(void)
{
	TEngSystemManager *pstSystemManager = &s_stSystemManager;
	TMsgQCB *pstSystemMgrMsgQCB = &pstSystemManager->stMsgQCB;	/* Message Handler for Engine System Manager */
	TMsgQ stRcvMsgQ = {0};
	TEngState enNextState = ENG_ST_UNSPECIFIED;

	while(EngLib_TaskToISRReceiveEvent(&stRcvMsgQ))
	{
		DBG_ENGSM(ENG_DBG_STRING"SendMsg:%x,%d,%d", ENG_TICK, "SM", stRcvMsgQ.ulMsgID, stRcvMsgQ.ulLParam, stRcvMsgQ.ulRParam);
		EngSM_SendEvent(stRcvMsgQ.ulMsgID, NULL, stRcvMsgQ.ulLParam, stRcvMsgQ.ulRParam);
	}

	/* Message Handler for Engine System Manager */
	while(EngLib_ReceiveMsgQ(pstSystemMgrMsgQCB, &stRcvMsgQ))
	{
		;//EngSM_DispatchMessage(&stRcvMsgQ);
	}

	/* Execute the state activity of Engine System Manager */
	enNextState = EngLib_StateActivity(&pstSystemManager->stStateMachine, pstSystemManager);
	enNextState = EngLib_StateGuardConditionActivity(&pstSystemManager->stStateMachine, pstSystemManager);

	/* Update the Status DB of Engine System Manager */
	EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);
	
	EngSM_CountIntervalTime();
	
	return TRUE;
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
BOOL EngSM_InitStatus(void)
{
	DBG_ENGSM(ENG_DBG_STRING"SM_InitStatus", ENG_TICK, "SM");
	
	return TRUE;
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
U32 EngSM_GetStatus(U32 ulStatusID)
{
    U32 ulReturnValue = 0;
    //TENGSM_STATUS_CALLBACK_F pfnStatusInternalFunc = NULL;

    /* Get Status ID & Check Invalid Range */
    if((ulStatusID == ENGSM_STS_PARENT_UNSPECIFIED)
		|| (STATUS_GET_INDEX(ulStatusID) > ARRAY_SIZE(s_apfnStatusFuncTable))
	)
    {
		DBG_ENGSM(ENG_DBG_STRING"Warning!! (Invalid ID Value=%x)", ENG_TICK, "SM",ulStatusID);
        
        return STATUS_INITIAL_VAL;
    }

    /* Change Status ID for internal using */
    ulStatusID = STATUS_GET_INDEX(ulStatusID);

    return ulReturnValue;
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
BOOL EngSM_SetStatus(U32 ulStatusID, U32 ulNewValue)
{
    U32 ulChangedStatusID = 0;
    U32 ulStatusAttibute = 0;
    U32 ulOldValue = 0;
    TENGSM_STATUS_CALLBACK_F pfnStatusInternalFunc = NULL;

	if(ulStatusID == ENGSM_STS_PARENT_UNSPECIFIED)
	{
		DBG_ENGSM(ENG_DBG_STRING"Warning!! (Invalid ID Value=%x)", ENG_TICK, "SM",ulStatusID);
		return FALSE;
	}

    /* Get Status ID & Check Invalid Range */
    if(STATUS_GET_INDEX(ulStatusID) > ARRAY_SIZE(s_apfnStatusFuncTable))
    {
		DBG_ENGSM(ENG_DBG_STRING"Warning!! (Invalid ID Value=%x)", ENG_TICK, "SM",ulStatusID);

        return STATUS_INITIAL_VAL;
    }

    /* Change Status ID for internal using */
    ulChangedStatusID = STATUS_GET_INDEX(ulStatusID);

    /*
     * Check whether status value is changed or not
     * If not changed, just return with debug message
     * At this time, return value is TRUE
     */
    pfnStatusInternalFunc = (TENGSM_STATUS_CALLBACK_F)s_apfnStatusFuncTable[ulChangedStatusID];
    ulOldValue = (*pfnStatusInternalFunc)(STATUS_GET, ulChangedStatusID, 0);

    /* Get Status Attribute for internal using */
    ulStatusAttibute = STATUS_GET_ATTRIBUTE(ulStatusID);

    if(ulStatusAttibute == STATUS_ATTR_VALUE)
    {
	    if(ulOldValue == ulNewValue)
	    {
//	        DBG_ENGSM("\r\n[EngSM] Warning!! Setting Value is identical!! (value=%x)", ulOldValue);
	        return TRUE;
	    }
    }
	else if(ulStatusAttibute == STATUS_ATTR_INFO)
	{
	    if(ulOldValue & ulNewValue)
	    {
//	        DBG_ENGSM("\r\n[EngSM] Warning!! Setting Value is identical!! (value=%x)", ulOldValue);
	        return TRUE;
	    }
	}

    /* Call specific function */
    if((*pfnStatusInternalFunc)(STATUS_SET, ulChangedStatusID, ulNewValue))
	{
	    /* If callback is registered on specific status id, then it would be called */
	    //EngSM_FollowDeviceStatus(ulStatusID, ulOldValue, ulNewValue);

		// if((ulStatusID == ENGSM_STS_PARENT_ENGINE_STATE) 
		// 	&& ((ulNewValue == ENG_ST_WARMUP) || (ulNewValue == ENG_ST_ERROR))
		// )
		{
			//EngSM_HndIF_FollowDeviceStatus(ENG_HND_MH, ulStatusID, ulOldValue, ulNewValue);
			//EngSM_HndIF_FollowDeviceStatus(ENG_HND_PH, ulStatusID, ulOldValue, ulNewValue);
			//EngSM_HndIF_FollowDeviceStatus(ENG_HND_IH, ulStatusID, ulOldValue, ulNewValue);	
		}
		// else
		// {
		// 	EngVM_Add(ENGVM_ARG_NUM4|ENGVM_ARG_1MS|ENGVM_ARG_INFINITE, 1*T1MS, 0, EngSM_HndIF_FollowDeviceStatus, ENG_HND_MH, ulStatusID, ulOldValue, ulNewValue);
		//     EngVM_Add(ENGVM_ARG_NUM4|ENGVM_ARG_2MS|ENGVM_ARG_INFINITE, 3*T2MS, 0, EngSM_HndIF_FollowDeviceStatus, ENG_HND_PH, ulStatusID, ulOldValue, ulNewValue);
		//     EngVM_Add(ENGVM_ARG_NUM4|ENGVM_ARG_2MS|ENGVM_ARG_INFINITE, 5*T2MS, 0, EngSM_HndIF_FollowDeviceStatus, ENG_HND_IH, ulStatusID, ulOldValue, ulNewValue);
		// }
	}

    return TRUE;
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
U32 EngSM_EngineState(U32 ulSetGet, U32 ulDeviceStatusID, U32 ulValue)
{
    U32 ulReturnValue = FALSE;

    switch(ulSetGet)
    {
        case STATUS_SET:
            if(STATUS_GET_INDEX(ulValue) <= STATUS_GET_INDEX(ENGSM_STS_CHILD_ENGINE_POWERON))
            {
				//s_ulEngDeviceStatus = ulValue;
				ulReturnValue = TRUE;
            }
            else
            {
//				DBG_ENGSM("\r\n[EngSM_Status] Warning!! Invalid value (RW:%d, ID:%x, Value:%x)", ulSetGet, ulDeviceStatusID, ulValue);
            }
            break;

        case STATUS_GET:
			//ulReturnValue = s_ulEngDeviceStatus;
			ulReturnValue = TRUE;
            break;

        default:
            break;
	}

    return ulReturnValue;
}
