/**
 * @file        EngLib_Common.c
 * @brief       This is main code for Engine Library.
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

#define	__ENGLIB_MAIN_C__

#include "Eng_CommonType.h"

#include "EngLib_Main.h"

#define C_TASK_TO_ISR_MSG_Q_MAX 	50

static TMsgQCB s_stTaskToISRMsgQCB;
static TMsgQ s_astTaskToISRMsgQ[C_TASK_TO_ISR_MSG_Q_MAX];
static const U16 crc16tab[256]= {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

void EngLib_MainEntry(void)
{	
	EngLib_InitTaskToISRMessage(&s_stTaskToISRMsgQCB);
}

/* Task To ISR Send Message */
BOOL EngLib_InitTaskToISRMessage(TMsgQCB *pstMsgQCB)
{
	pstMsgQCB->fBusy = FALSE;
	pstMsgQCB->ulMsgQHead = 0;
	pstMsgQCB->ulMsgQTail = 0;
	pstMsgQCB->ulMsgQSize = C_TASK_TO_ISR_MSG_Q_MAX;
	pstMsgQCB->pstMsgQ = s_astTaskToISRMsgQ;
	
	return TRUE;
}

U32 EngLib_TaskToISRSendEvent(U32 ulEventID, U32 ulLParam, U32 ulRParam)
{
	U32 ulEventReturn = 0;
	TMsgQ stSendMsgQ = {0};

	stSendMsgQ.ulMsgID = ulEventID;
	stSendMsgQ.ulLParam = ulLParam;
	stSendMsgQ.ulRParam = ulRParam;

//	DBG_ENGIFSVC(ENG_DBG_STRING"Kernel Send Event ID=%x,%d,%d", ENG_TICK, "IFSvc", ulEventID, ulLParam, ulRParam);

	/* Send the received event to message queue of state machine */
	if(!EngLib_SendMsgQ(&s_stTaskToISRMsgQCB, &stSendMsgQ))
	{
		DBG_ENGLIB(ENG_DBG_STRING"Message Q of information is Full", ENG_TICK, "Lib");		
	}
	
	return (BOOL)ulEventReturn;
}

BOOL EngLib_TaskToISRReceiveEvent(TMsgQ *pstRcvMsgQ)
{
	return EngLib_ReceiveMsgQ(&s_stTaskToISRMsgQCB, pstRcvMsgQ);
}

BOOL EngLib_GetMsgQ(TMsgQCB *pstMsgQCB, TMsgQ *pstRcvMsgQ)
{
	BOOL fReturn = FALSE;

	*pstRcvMsgQ = pstMsgQCB->pstMsgQ[pstMsgQCB->ulMsgQHead];
	
	return fReturn;
}

BOOL EngLib_ReceiveMsgQ(TMsgQCB *pstMsgQCB, TMsgQ *pstRcvMsgQ)
{
	BOOL fReturn = FALSE;
	U32 ulMask = 0;
	
	ulMask = EngLib_SpinLock(1);

	/* Queue is not Empty */
	if(pstMsgQCB->ulMsgQHead != pstMsgQCB->ulMsgQTail)
	{
		*pstRcvMsgQ = pstMsgQCB->pstMsgQ[pstMsgQCB->ulMsgQHead];

		++pstMsgQCB->ulMsgQHead;
		pstMsgQCB->ulMsgQHead = pstMsgQCB->ulMsgQHead % pstMsgQCB->ulMsgQSize;
		fReturn = TRUE;
	}

	EngLib_SpinLock(ulMask);	
	
	return fReturn;
}

BOOL EngLib_SendMsgQ(TMsgQCB *pstMsgQCB, TMsgQ *pstSendMsgQ)
{
	BOOL fReturn = FALSE;
	U32 ulMask = 0;
	
	ulMask = EngLib_SpinLock(1);	

	/* Queue is not Full */
	if(((pstMsgQCB->ulMsgQTail + 1) % pstMsgQCB->ulMsgQSize) != pstMsgQCB->ulMsgQHead)
	{
		pstMsgQCB->fBusy = TRUE;
		pstMsgQCB->pstMsgQ[pstMsgQCB->ulMsgQTail] = *pstSendMsgQ;

		++pstMsgQCB->ulMsgQTail;
		pstMsgQCB->ulMsgQTail = pstMsgQCB->ulMsgQTail % pstMsgQCB->ulMsgQSize;
		pstMsgQCB->fBusy = FALSE;
		fReturn = TRUE;
	}

	EngLib_SpinLock(ulMask);
	
	return fReturn;
}

BOOL EngLib_SendMsgQWithoutFullChk(TMsgQCB *pstMsgQCB, TMsgQ *pstSendMsgQ)
{
	U32 ulMask = 0;
			
	ulMask = EngLib_SpinLock(1);	

	pstMsgQCB->fBusy = TRUE;
	pstMsgQCB->pstMsgQ[pstMsgQCB->ulMsgQTail] = *pstSendMsgQ;

	++pstMsgQCB->ulMsgQTail;
	pstMsgQCB->ulMsgQTail = pstMsgQCB->ulMsgQTail % pstMsgQCB->ulMsgQSize;
	pstMsgQCB->fBusy = FALSE;

	EngLib_SpinLock(ulMask);	
	
	return TRUE;
}

BOOL EngLib_IsMsgQEmpty(TMsgQCB *pstMsgQCB)
{
	return (pstMsgQCB->ulMsgQHead == pstMsgQCB->ulMsgQTail);
}

BOOL EngLib_IsMsgQFull(TMsgQCB *pstMsgQCB)
{
	return (((pstMsgQCB->ulMsgQTail + 1) % pstMsgQCB->ulMsgQSize) == pstMsgQCB->ulMsgQHead);
}

BOOL EngLib_IsReceivedMsgQ(TMsgQCB *pstMsgQCB)
{
	return (pstMsgQCB->ulMsgQHead != pstMsgQCB->ulMsgQTail);
}

BOOL EngLib_InitQueue(TQueue *pstQueue, void * pvBuffer, U32 ulBuffSize)
{
	if((pstQueue == NULL) || (pvBuffer == NULL))
	{
		return FALSE;
	}
	
	pstQueue->ulHead = 0;
	pstQueue->ulTail = 0;
	pstQueue->pvBuffer = pvBuffer;
	pstQueue->ulSize = ulBuffSize;	

	return TRUE;
}

BOOL EngLib_IsQueueEmpty(TQueue *pstQueue)
{
	return (pstQueue->ulHead == pstQueue->ulTail);
}

BOOL EngLib_IsQueueFull(TQueue *pstQueue)
{
	return (((pstQueue->ulTail + 1) % pstQueue->ulSize) == pstQueue->ulHead);
}


/* State Machine */
inline S32 EngLib_StateCompareMachine(const void *pvName, const void *pvElem)
{
	return (*(U32 *)pvName - ((TStateMachineTbl *)pvElem)->ulState);
}

TStateMachineTbl *EngLib_StateSearchMachine(TStateMachine *pstStateMachine, U32 ulState)
{
	TStateMachineTbl *pvElement = (TStateMachineTbl *)NULL;

	// pvElement = (TStateMachineTbl *)EngLib_BinarySearch(&ulState, pstStateMachine->pstSMT, pstStateMachine->ulMachineTblSize, sizeof(TStateMachineTbl), EngLib_StateCompareMachine);

	return pvElement;
}

TStateTransitionTbl *EngLib_StateSearchTransition(TStateMachine *pstStateMachine)
{
    TStateTransitionTbl *pstSTT = (TStateTransitionTbl *)NULL;
    U32 ulIdx = 0;

	ASSERT(pstStateMachine != NULL);
	pstSTT = &pstStateMachine->pstSTT[0];
	
	if(pstSTT == NULL)
	{
		ASSERT(0);
//		return NULL;
	}
	
    for(ulIdx = 0; ulIdx <= pstStateMachine->ulTransitionTblSize; ulIdx++)
    {
        if((pstSTT[ulIdx].ulState == pstStateMachine->ulState) && (pstSTT[ulIdx].ulEvent == pstStateMachine->ulEvent))
        {
            pstSTT = &pstSTT[ulIdx];
            return pstSTT;
        }
    }
    
    /* If searching is failed */
	pstSTT = (TStateTransitionTbl *)NULL;
	
    return pstSTT;
}

U32 EngLib_StateActivity(TStateMachine *pstStateMachine, void *pvStateEntry)
{
	TStateMachineTbl *pstCurrSMT = (TStateMachineTbl *)NULL;
	U32 ulCurrState = ENG_ST_UNSPECIFIED;

	if(pstStateMachine->pstSMT == NULL)
	{
		return ENG_ST_UNSPECIFIED;
	}
	
	ASSERT(EngLib_IsEngineArea((U8*)pstStateMachine));

	/* Determine the state machine for a current state */
	ulCurrState = pstStateMachine->ulState;
	
	pstCurrSMT = EngLib_StateSearchMachine(pstStateMachine, ulCurrState);
	if(pstCurrSMT == NULL)
	{
		DBG_STATE(ENG_DBG_STRING"Not search a current state", ENG_TICK, "State");
		return ENG_ST_UNSPECIFIED;
	}

	pstStateMachine->ulTimeCount++;

	if(pstStateMachine->ulTimeCount >= pstStateMachine->ulTransitionTime)
	{
		if((pstStateMachine->fTransitionEnable == FALSE) && (pstStateMachine->ulTransitionTime > 0))
		{
			DBG_STATE(ENG_DBG_STRING"Transition Enable[%x/%d]:%d", ENG_TICK, "State", pvStateEntry, pstStateMachine->ulID, pstStateMachine->ulTransitionTime);
		}
		pstStateMachine->fTransitionEnable = TRUE;
	}
	
	/* Execute a current state action */
	if((void *)pstCurrSMT->pfnDoActivity != NULL)
	{
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
		EngTM_ETM_SaveTimeEvent((U32)pstCurrSMT->pfnDoActivity, 0);
#endif
		pstCurrSMT->pfnDoActivity(pvStateEntry);
		pstCurrSMT->enExecutedMask = (TStateMaskBit)((U32)pstCurrSMT->enExecutedMask | (U32)ENG_ST_ACTIVITY);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
		EngTM_ETM_SaveTimeEvent((U32)pstCurrSMT->pfnDoActivity, 1);
#endif
//		DBG_STATE("[%s] ", pstCurrSMT->pubString);
	}

	if(pstCurrSMT->ulTimeout != 0)
	{
		if(pstStateMachine->ulTimeCount == pstCurrSMT->ulTimeout)
		{
			DBG_EMERGENCY(ENG_DBG_STRING"Assert: State TimeOut Error(%s)", ENG_TICK, "State", pstCurrSMT->pubString);
			EngLib_DumpStack(NULL);
			ASSERT(0);
		}
	}
	
	return ENG_ST_UNSPECIFIED;
}

U32 EngLib_StateMachine(TStateMachine *pstStateMachine, U32 ulEvent, void *pvStateEntry)
{
	if(pstStateMachine->pstSMT == NULL)
	{
		return ENG_ST_UNSPECIFIED;
	}

	ASSERT(EngLib_IsEngineArea((U8*)pstStateMachine));

	pstStateMachine->ulEvent = ulEvent;	
	pstStateMachine->ulReceivedEvent = ulEvent;
	
	if(pstStateMachine->ulEvent != ENG_EV_UNSPECIFIED)
	{
	    TStateTransitionTbl *pstSTT = (TStateTransitionTbl *)NULL;
		U32 ulCurrState = ENG_ST_UNSPECIFIED;
		U32 ulNextState = ENG_ST_UNSPECIFIED;
	
		ulCurrState = pstStateMachine->ulState;
		
		/* Determine the next state when an event is received */
		ulNextState = ulCurrState;

		pstSTT = EngLib_StateSearchTransition(pstStateMachine);
		if(pstSTT == NULL)
		{
//			DBG_STATE("\r\n[State] Searching for transition is failed");
			return ENG_ST_UNSPECIFIED;
		}
		ulNextState = pstSTT->ulNextState;
		
		/* Is the guard condition of state transition satisfied? */
		if((void *)pstSTT->pfnGuardCondition != NULL)
		{
			U32 ulGuardConditionResult = 0;
			
			pstStateMachine->ulGuardConditionEvent = ulEvent;

			ulGuardConditionResult = pstSTT->pfnGuardCondition(pvStateEntry, &pstStateMachine->ulGuardConditionEvent, pstSTT->ulTimeout);
			
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstSTT->pfnGuardCondition, 0);
#endif
			if(ulGuardConditionResult == TRUE)
			{
				if(pstStateMachine->pfnGuardCondition)
				{
					pstStateMachine->pfnGuardCondition = NULL;
				}
				DBG_STATE(ENG_DBG_STRING"Guard Condition OK[%x/%d]:%d", ENG_TICK, "State", pvStateEntry, pstStateMachine->ulID, pstSTT->ulState);
				EngLib_StateGuardCondition(pstStateMachine, pstStateMachine->ulGuardConditionEvent, pvStateEntry);
			}
			else if((ulGuardConditionResult != 0) && EngLib_IsEngineArea((U8*)ulGuardConditionResult))
			{
				DBG_STATE(ENG_DBG_STRING"Guard Condition Reserved[%x/%d]:%d/%x", ENG_TICK, "State", pvStateEntry, pstStateMachine->ulID, pstSTT->ulState, ulGuardConditionResult);
				// pstStateMachine->pfnGuardCondition = ulGuardConditionResult;
			}

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstSTT->pfnGuardCondition, 1);
#endif
		}
		else
		{
			/* Execute the transition action function */
			if((void *)pstSTT->pfnTransitionAction != NULL)
			{
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
				EngTM_ETM_SaveTimeEvent((U32)pstSTT->pfnTransitionAction, 0);
#endif
				pstSTT->pfnTransitionAction(pvStateEntry);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
				EngTM_ETM_SaveTimeEvent((U32)pstSTT->pfnTransitionAction, 1);
#endif
			}
			
			/* Compare a current and next state */
			if(ulCurrState != ulNextState)
			{
			    TStateMachineTbl *pstCurrSMT = (TStateMachineTbl *)NULL;
    			TStateMachineTbl *pstNextSMT = (TStateMachineTbl *)NULL;

				/* Determine the state machine for a current state */
				pstCurrSMT = EngLib_StateSearchMachine(pstStateMachine, ulCurrState);
				if(pstCurrSMT == NULL)
				{
					DBG_STATE(ENG_DBG_STRING"Not search a next state", ENG_TICK, "State");
					return ENG_ST_UNSPECIFIED;
				}
				
				/* Execute the exit action for the current state */
				if((void *)pstCurrSMT->pfnExitAction != NULL)
				{
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
					EngTM_ETM_SaveTimeEvent((U32)pstCurrSMT->pfnExitAction, 0);
#endif
					pstCurrSMT->pfnExitAction(pvStateEntry);
					pstCurrSMT->enExecutedMask = (TStateMaskBit)((U32)pstCurrSMT->enExecutedMask | (U32)ENG_ST_EXIT);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
					EngTM_ETM_SaveTimeEvent((U32)pstCurrSMT->pfnExitAction, 1);
#endif
	//				DBG_STATE("\r\n[State] Exit << %s >>", pstCurrSMT->pubString);
				}
	
				/* Determine the state machine for a next state */
				pstNextSMT = EngLib_StateSearchMachine(pstStateMachine, ulNextState);
				if(pstNextSMT == NULL)
				{
					DBG_STATE(ENG_DBG_STRING"Not search a next state", ENG_TICK, "State");
					return ENG_ST_UNSPECIFIED;
				}

				/* Change the state */
				pstStateMachine->ulState = ulNextState;
				pstStateMachine->ulPrevState = ulCurrState;				
				
				/* Execute the entry action for a next state */			
				pstStateMachine->fTransitionEnable = FALSE;
				pstStateMachine->ulTransitionTime = 0;
				pstStateMachine->ulTimeCount = 0;
				
				if((void *)pstNextSMT->pfnEntryAction != NULL)
				{
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
					EngTM_ETM_SaveTimeEvent((U32)pstNextSMT->pfnEntryAction, 0);
#endif
					pstStateMachine->ulTransitionTime = pstNextSMT->pfnEntryAction(pvStateEntry);

					pstNextSMT->enExecutedMask = (TStateMaskBit)((U32)pstNextSMT->enExecutedMask | (U32)ENG_ST_ENTRY);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
					EngTM_ETM_SaveTimeEvent((U32)pstNextSMT->pfnEntryAction, 1);
#endif
	//				DBG_STATE("\r\n[State] Entry << %s >>", pstNextSMT->pubString);
				}
				
				DBG_STATE(ENG_DBG_STRING"<%d %s %d/%d>", ENG_TICK, "State", pstStateMachine->ulID, pstNextSMT->pubString, pstStateMachine->ulUniqueID, pstStateMachine->ulTransitionTime);
#ifdef FR_TM_LMS
				DBG_LMS_SA_TIMING_STATE(ENG_LMS_STATE_INFO" %s ", ENG_TICK, pstStateMachine->ulLMSStateID, (100 * pstNextSMT->ulState), pstNextSMT->pubString);
#endif
			}
			
			pstStateMachine->ulEvent = ENG_EV_UNSPECIFIED;
			
			return ulNextState;
		}
	}
	
	return ENG_ST_UNSPECIFIED;
}

U32 EngLib_StateGuardConditionActivity(TStateMachine *pstStateMachine, void *pvStateEntry)
{
	ASSERT(EngLib_IsEngineArea((U8*)pstStateMachine));

	if(pstStateMachine->pfnGuardCondition != NULL)
	{
		if(pstStateMachine->pfnGuardCondition(pvStateEntry, &pstStateMachine->ulGuardConditionEvent, 0) == TRUE)
		{
			DBG_STATE(ENG_DBG_STRING"Guard Condition Executed[%x/%d]:%x,%d", ENG_TICK, "State", pvStateEntry, pstStateMachine->ulID, pstStateMachine->pfnGuardCondition, pstStateMachine->ulGuardConditionEvent);
			EngLib_StateGuardCondition(pstStateMachine, pstStateMachine->ulGuardConditionEvent, pstStateMachine->pvStateEntry);
			pstStateMachine->pfnGuardCondition = NULL;
		}
	}
	
	return ENG_ST_UNSPECIFIED;
}

U32 EngLib_StateGuardCondition(TStateMachine *pstStateMachine, U32 ulEvent, void *pvStateEntry)
{
    TStateTransitionTbl *pstSTT = (TStateTransitionTbl *)NULL;
	U32 ulCurrState = ENG_ST_UNSPECIFIED;
	U32 ulNextState = ENG_ST_UNSPECIFIED;

	if(pstStateMachine->pstSMT == NULL)
	{
		return ENG_ST_UNSPECIFIED;
	}
	
	ASSERT(EngLib_IsEngineArea((U8*)pstStateMachine));

	pstStateMachine->ulEvent = ulEvent;
	pstStateMachine->ulReceivedEvent = ulEvent;
	
	ulCurrState = pstStateMachine->ulState;
	
	/* Determine the next state when an event is received */
	ulNextState = ulCurrState;
	
	pstSTT = EngLib_StateSearchTransition(pstStateMachine);
	if(pstSTT == NULL)
	{
//		DBG_STATE("\r\n[State] Searching for transition is failed");
		return ENG_ST_UNSPECIFIED;
	}
	ulNextState = pstSTT->ulNextState;


	/* Execute the transition action function */
	if((void *)pstSTT->pfnTransitionAction != NULL)
	{
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
		EngTM_ETM_SaveTimeEvent((U32)pstSTT->pfnTransitionAction, 0);
#endif

		pstSTT->pfnTransitionAction(pvStateEntry);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
		EngTM_ETM_SaveTimeEvent((U32)pstSTT->pfnTransitionAction, 1);
#endif
	}
	
	/* Compare a current and next state */
	if(ulCurrState != ulNextState)
	{
	    TStateMachineTbl *pstCurrSMT = (TStateMachineTbl *)NULL;
		TStateMachineTbl *pstNextSMT = (TStateMachineTbl *)NULL;

		/* Determine the state machine for a current state */
		pstCurrSMT = EngLib_StateSearchMachine(pstStateMachine, ulCurrState);
		if(pstCurrSMT == NULL)
		{
			DBG_STATE(ENG_DBG_STRING"Not search a next state", ENG_TICK, "State");
			return ENG_ST_UNSPECIFIED;
		}
		
		/* Execute the exit action for the current state */
		if((void *)pstCurrSMT->pfnExitAction != NULL)
		{
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstCurrSMT->pfnExitAction, 0);
#endif
			pstCurrSMT->pfnExitAction(pvStateEntry);
			pstCurrSMT->enExecutedMask = (TStateMaskBit)((U32)pstCurrSMT->enExecutedMask | (U32)ENG_ST_EXIT);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstCurrSMT->pfnExitAction, 1);
#endif
//			DBG_STATE("\r\n[State] Exit << %s >>", pstCurrSMT->pubString);
		}

		/* Determine the state machine for a next state */
		pstNextSMT = EngLib_StateSearchMachine(pstStateMachine, ulNextState);
		if(pstNextSMT == NULL)
		{
			DBG_STATE(ENG_DBG_STRING"Not search a next state", ENG_TICK, "State");
			return ENG_ST_UNSPECIFIED;
		}

		/* Change the state */
		pstStateMachine->ulState = ulNextState;
		pstStateMachine->ulPrevState = ulCurrState;
		
		/* Execute the entry action for a next state */
		pstStateMachine->fTransitionEnable = FALSE;
		pstStateMachine->ulTransitionTime = 0;
		pstStateMachine->ulTimeCount = 0;
				
		if((void *)pstNextSMT->pfnEntryAction != NULL)
		{
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstNextSMT->pfnEntryAction, 0);
#endif
			pstStateMachine->ulTransitionTime = pstNextSMT->pfnEntryAction(pvStateEntry);
			pstNextSMT->enExecutedMask = (TStateMaskBit)((U32)pstNextSMT->enExecutedMask | (U32)ENG_ST_ENTRY);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstNextSMT->pfnEntryAction, 1);
#endif
//			DBG_STATE("\r\n[State] Entry << %s >>", pstNextSMT->pubString);
		}

		DBG_STATE(ENG_DBG_STRING"<%d %s %d/%d>", ENG_TICK, "State", pstStateMachine->ulID, pstNextSMT->pubString, pstStateMachine->ulUniqueID, pstStateMachine->ulTransitionTime);

#ifdef FR_TM_LMS
		DBG_LMS_SA_TIMING_STATE(ENG_LMS_STATE_INFO" %s ", ENG_TICK, pstStateMachine->ulLMSStateID, (100 * pstNextSMT->ulState), pstNextSMT->pubString);
#endif		
		pstStateMachine->ulEvent = ENG_EV_UNSPECIFIED;
		
		return ulNextState;
	}
	
	return ENG_ST_UNSPECIFIED;
}

U32 EngLib_StateChange(TStateMachine *pstStateMachine, U32 ulNextState, void *pvStateEntry)
{
    TStateMachineTbl *pstCurrSMT = (TStateMachineTbl *)NULL;
    TStateMachineTbl *pstNextSMT = (TStateMachineTbl *)NULL;
	U32 ulCurrState = ENG_ST_UNSPECIFIED;

	ASSERT(EngLib_IsEngineArea((U8*)pstStateMachine));
	
	/* Determine the state machine for a current state */
	ulCurrState = pstStateMachine->ulState;
	
	if(pstStateMachine->pstSMT == NULL)
	{
		return ENG_ST_UNSPECIFIED;
	}
	
	pstCurrSMT = EngLib_StateSearchMachine(pstStateMachine, ulCurrState);
	if(pstCurrSMT == NULL)
	{
		DBG_STATE(ENG_DBG_STRING"Not search a current state", ENG_TICK, "State");
		return ENG_ST_UNSPECIFIED;
	}
	
	/* Determine the state machine for a next state */
	pstNextSMT = EngLib_StateSearchMachine(pstStateMachine, ulNextState);
	if(pstNextSMT == NULL)
	{
		DBG_STATE(ENG_DBG_STRING"Not search a next state", ENG_TICK, "State");
		return ENG_ST_UNSPECIFIED;
	}

	/* Compare a current and next state */
	if(ulCurrState != ulNextState)
	{
		/* Execute the exit action for the current state */
		if((void *)pstCurrSMT->pfnExitAction != NULL)
		{
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstCurrSMT->pfnExitAction, 0);
#endif
			pstCurrSMT->pfnExitAction(pvStateEntry);
			pstCurrSMT->enExecutedMask = (TStateMaskBit)((U32)pstCurrSMT->enExecutedMask | (U32)ENG_ST_EXIT);
			
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstCurrSMT->pfnExitAction, 1);
#endif
//			DBG_STATE("\r\n[State] Exit << %s >>", pstCurrSMT->pubString);
		}

		/* Change the state */
		pstStateMachine->ulState = ulNextState;
		pstStateMachine->ulPrevState = ulCurrState;		
		pstStateMachine->ulEvent = ENG_EV_UNSPECIFIED;
		pstStateMachine->ulReceivedEvent = ENG_EV_UNSPECIFIED;
		pstStateMachine->ulGuardConditionEvent = ENG_EV_UNSPECIFIED;

		/* Execute the entry action for a next state */
		pstStateMachine->fTransitionEnable = FALSE;
		pstStateMachine->ulTransitionTime = 0;
		pstStateMachine->ulTimeCount = 0;
		
		if((void *)pstNextSMT->pfnEntryAction != NULL)
		{
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstNextSMT->pfnEntryAction, 0);
#endif
			pstStateMachine->ulTransitionTime = pstNextSMT->pfnEntryAction(pvStateEntry);
			pstNextSMT->enExecutedMask = (TStateMaskBit)((U32)pstNextSMT->enExecutedMask | (U32)ENG_ST_ENTRY);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
			EngTM_ETM_SaveTimeEvent((U32)pstNextSMT->pfnEntryAction, 1);
#endif
//			DBG_STATE("\r\n[State] Entry << %s >>", pstNextSMT->pubString);
		}

		DBG_STATE(ENG_DBG_STRING"<%d %s %d/%d>", ENG_TICK, "State", pstStateMachine->ulID, pstNextSMT->pubString, pstStateMachine->ulUniqueID, pstStateMachine->ulTransitionTime);
#ifdef FR_TM_LMS
		DBG_LMS_SA_TIMING_STATE(ENG_LMS_STATE_INFO" %s ", ENG_TICK, pstStateMachine->ulLMSStateID, (100 * pstNextSMT->ulState), pstNextSMT->pubString);
#endif		
		return ulNextState;
	}
	
	return ENG_ST_UNSPECIFIED;
}

void EngLib_StateEvent(U32 ulEvent, TStateMachine *pstStateMachine)
{
	pstStateMachine->ulEvent = ulEvent;
	pstStateMachine->ulReceivedEvent = ulEvent;
}

void EngLib_StateSet(U32 ulState, TStateMachine *pstStateMachine, void *pvStateEntry)
{
	TStateMachineTbl *pstNextSMT = EngLib_StateSearchMachine(pstStateMachine, ulState);
	U32 ulCurrState = ENG_ST_UNSPECIFIED;
	
	if(pstNextSMT == NULL)
	{
		pstStateMachine->ulState = ENG_ST_UNSPECIFIED;
		DBG_STATE(ENG_DBG_STRING"Not search a next state", ENG_TICK, "State");
		return;
	}

	ulCurrState = pstStateMachine->ulState;
	pstStateMachine->ulState = ulState;
	pstStateMachine->ulPrevState = ulCurrState;

	/* Execute the entry action for a next state */
	pstStateMachine->fTransitionEnable = FALSE;
	pstStateMachine->ulTransitionTime = 0;
	pstStateMachine->ulTimeCount = 0;

	if(pstNextSMT->pfnEntryAction)
	{		
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
		EngTM_ETM_SaveTimeEvent((U32)pstNextSMT->pfnEntryAction, 0);
#endif
		pstStateMachine->ulTransitionTime = pstNextSMT->pfnEntryAction(pvStateEntry);
		pstNextSMT->enExecutedMask = (TStateMaskBit)((U32)pstNextSMT->enExecutedMask | (U32)ENG_ST_ENTRY);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
		EngTM_ETM_SaveTimeEvent((U32)pstNextSMT->pfnEntryAction, 1);
#endif

//		DBG_STATE("\r\n[State] Entry << %s >>", pstNextSMT->pubString);
	}

	DBG_STATE(ENG_DBG_STRING"<%d %s %d/%d>", ENG_TICK, "State", pstStateMachine->ulID, pstNextSMT->pubString, pstStateMachine->ulUniqueID, pstStateMachine->ulTransitionTime);
#ifdef FR_TM_LMS
	DBG_LMS_SA_TIMING_STATE(ENG_LMS_STATE_INFO" %s ", ENG_TICK, pstStateMachine->ulLMSStateID, (100 * pstNextSMT->ulState), pstNextSMT->pubString);
#endif
}

U32 EngLib_StateGet(TStateMachine *pstStateMachine)
{
	ASSERT(EngLib_IsEngineArea((U8*)pstStateMachine));
		
	return pstStateMachine->ulState;
}

void EngLib_StateExecutedStatusClear(TStateMachine *pstStateMachine)
{
	TStateMachineTbl *pstCurrSMT = NULL;
	U32 ulIdx = 0;

	if(pstStateMachine == NULL)
	{
		return;
	}

	pstCurrSMT = pstStateMachine->pstSMT;

	for(ulIdx = 0 ; ; pstCurrSMT++, ulIdx++)
	{
		if((pstCurrSMT != NULL)
			&& (pstCurrSMT->ulState != ENG_ST_UNSPECIFIED)
			&& (ulIdx < pstStateMachine->ulMachineTblSize)
		)
		{
			pstCurrSMT->enExecutedMask = ENG_ST_NONE;
		}
		else
		{
			break;
		}
	}
}

S32 EngLib_StateCompareName(const void *pvName, const void *pvElem)
{
	return (*(U32 *)pvName - ((TStateMachineTbl *)pvElem)->ulState);
}

/* List Head */
void EngLib_ListHeadAdd(TListHead *new_h, TListHead *prev, TListHead *next)
{
	U32 ulMask = 0;
		
	ulMask = EngLib_SpinLock(1);	
	
    next->prev = new_h;
    new_h->next = next;
    new_h->prev = prev;
    prev->next = new_h;

	EngLib_SpinLock(ulMask);
}

void EngLib_ListHeadAddHead(TListHead *new_h, TListHead *head)
{
    EngLib_ListHeadAdd(new_h, head, head->next);
}

void EngLib_ListHeadAddTail(TListHead *new_h, TListHead *head)
{
    EngLib_ListHeadAdd(new_h, head->prev, head);
}

void EngLib_ListHeadDel(TListHead *entry)
{
	if((entry->next != NULL) && (entry->prev != NULL))
	{
		U32 ulMask = 0;
		
		ulMask = EngLib_SpinLock(1);

	    entry->next->prev = entry->prev;
	    entry->prev->next = entry->next;
	    
	    entry->next = (TListHead *) 0;
	    entry->prev = (TListHead *) 0;

		EngLib_SpinLock(ulMask);
    }
}

int EngLib_IsListHeadEmpty(TListHead *head)
{
    return head->next == head;
}

/* Sort */
void EngLib_QuickSort(void *base, U32 nmemb, U32 size, int (*compar)(const void *, const void *))
{
    char *i;
    char *j;
    char *x;
    char *r;
    auto struct stk
    {
        char *l;
        char *r;
    } stack[16];
    struct stk *sp;

    sp = stack;
    r = (char *) base + (nmemb-1)*size;
    
    for (;;)
    {
        do {
            x = (char *)base + (r - (char *) base) / size / 2 * size;
            i = (char *)base;
            j = (char *)r;
            
            do {
                while ((*compar)((const void *) i, (const void *) x) < 0)
                {
	                i += size;
                }
                while ((*compar)((const void *) x,(const void *) j) < 0)
                {
	                j -= size;
                }
                
                if (i < j)
                {
                    EngLib_SwapMem(i, j, size);
                    if(i == x)
                    {
                        x = j;
                    }
                    else if (j == x)
                    {
                        x = i;
                    }
                }
                
                if (i <= j)
                {
                    i += size;
                    j -= size;
                }
           } while (i <= j);
           
           if(j-(char *)base < r-i)
           {
               if (i < r)
               {
                   sp->l = i;
                   sp->r = r;
                   ++sp;
               }
               r = j;
           }
           else
           {
               if((char *) base < j)
               {
                   sp->l = (char *)base;
                   sp->r = j;
                   ++sp;
               }
               base = i;
           }
        } while ((char *) base < r);

        if (sp <= stack)
        {
	        break;
        }
        
        --sp;
        base = sp->l;
        r = sp->r;
    }
}

/* Search */
void * EngLib_BinarySearch(const void *key, const void *base, U32 nmemb, U32 size, int (*compar)(const void *, const void *))
{
	U32 l, u, idx;
	const void *p;
	int comparison;

	l = 0;
	u = nmemb;
	
	while (l < u)
	{
		idx = (l + u) / 2;
		p = (void *) (((const char *) base) + (idx * size));
		comparison = (*compar)(key, p);
		if (comparison < 0)
		{
			u = idx;
		}
		else if(comparison > 0)
		{
			l = idx + 1;
		}
		else
		{
			return (void *) p;
		}
	}
	return NULL;
}

/* 오름차순 정렬된 이상(above) 이하(below) 범위내 Search @ Type:S16 */
U32 EngLib_AscendingAboveBelowArraySearchS16(S16 *paswTbl, U32 ulTblSize, S16 swKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	S16 swLower = 0;
	S16 swUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			swLower = paswTbl[slIdx];
			swUpper = ((slIdx+1) < (S32)ulTblSize) ? paswTbl[slIdx+1] : paswTbl[slIdx] - 1;
		}
		else
		{
			swLower = ((slIdx-1) < 0) ? paswTbl[slIdx] : paswTbl[slIdx-1] + 1;
			swUpper = paswTbl[slIdx];
		}
		
		if((swLower <= swKeyValue) && (swKeyValue <= swUpper))
		{
			break;
		}
		else if(swKeyValue < swLower)
		{
			slIdx--;
		}
		else
		{
			slIdx++;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 오름차순 정렬된 이상(above) 이하(below) 범위내 Search @ Type:U16 */
U32 EngLib_AscendingAboveBelowArraySearchU16(U16 *pauwTbl, U32 ulTblSize, U16 uwKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	U16 uwLower = 0;
	U16 uwUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			uwLower = pauwTbl[slIdx];
			uwUpper = ((slIdx+1) < (S32)ulTblSize) ? pauwTbl[slIdx+1] : pauwTbl[slIdx] - 1;
		}
		else
		{
			uwLower = ((slIdx-1) < 0) ? pauwTbl[slIdx] : pauwTbl[slIdx-1] + 1;
			uwUpper = pauwTbl[slIdx];
		}
		
		if((uwLower <= uwKeyValue) && (uwKeyValue <= uwUpper))
		{
			break;
		}
		else if(uwKeyValue < uwLower)
		{
			slIdx--;
		}
		else
		{
			slIdx++;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 오름차순 정렬된 이상(above) 이하(below) 범위내 Search @ Type:S32 */
U32 EngLib_AscendingAboveBelowArraySearchS32(S32 *paslTbl, U32 ulTblSize, S32 slKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	S32 slLower = 0;
	S32 slUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			slLower = paslTbl[slIdx];
			slUpper = ((slIdx+1) < (S32)ulTblSize) ? paslTbl[slIdx+1] : paslTbl[slIdx] - 1;
		}
		else
		{
			slLower = ((slIdx-1) < 0) ? paslTbl[slIdx] : paslTbl[slIdx-1] + 1;
			slUpper = paslTbl[slIdx];
		}
		
		if((slLower <= slKeyValue) && (slKeyValue <= slUpper))
		{
			break;
		}
		else if(slKeyValue < slLower)
		{
			slIdx--;
		}
		else
		{
			slIdx++;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 오름차순 정렬된 이상(above) 이하(below) 범위내 Search @ Type:U32 */
U32 EngLib_AscendingAboveBelowArraySearchU32(U32 *paulTbl, U32 ulTblSize, U32 ulKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	U32 ulLower = 0;
	U32 ulUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			ulLower = paulTbl[slIdx];
			ulUpper = ((slIdx+1) < (S32)ulTblSize) ? paulTbl[slIdx+1] : paulTbl[slIdx] - 1;
		}
		else
		{
			ulLower = ((slIdx-1) < 0) ? paulTbl[slIdx] : paulTbl[slIdx-1] + 1;
			ulUpper = paulTbl[slIdx];
		}
		
		if((ulLower <= ulKeyValue) && (ulKeyValue <= ulUpper))
		{
			break;
		}
		else if(ulKeyValue < ulLower)
		{
			slIdx--;
		}
		else
		{
			slIdx++;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 오름차순 정렬된 이상(above) 미만(under) 범위내 Search @ Type:S16 */
U32 EngLib_AscendingAboveUnderArraySearchS16(S16 *paswTbl, U32 ulTblSize, S16 swKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	S16 swLower = 0;
	S16 swUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			swLower = paswTbl[slIdx];
			swUpper = ((slIdx+1) < (S32)ulTblSize) ? paswTbl[slIdx+1] : paswTbl[slIdx];
		}
		else
		{
			swLower = ((slIdx-1) < 0) ? paswTbl[slIdx] : paswTbl[slIdx-1];
			swUpper = paswTbl[slIdx];
		}
		
		if((swLower <= swKeyValue) && (swKeyValue < swUpper))
		{
			break;
		}
		else if(swKeyValue < swLower)
		{
			slIdx--;
		}
		else
		{
			slIdx++;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 오름차순 정렬된 이상(above) 미만(under) 범위내 Search @ Type:U16 */
U32 EngLib_AscendingAboveUnderArraySearchU16(U16 *pauwTbl, U32 ulTblSize, U16 uwKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	U16 uwLower = 0;
	U16 uwUpper = 0;

	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			uwLower = pauwTbl[slIdx];
			uwUpper = ((slIdx+1) < (S32)ulTblSize) ? pauwTbl[slIdx+1] : pauwTbl[slIdx];
		}
		else
		{
			uwLower = ((slIdx-1) < 0) ? pauwTbl[slIdx] : pauwTbl[slIdx-1];
			uwUpper = pauwTbl[slIdx];
		}
		
		if((uwLower <= uwKeyValue) && (uwKeyValue < uwUpper))
		{
			break;
		}
		else if(uwKeyValue < uwLower)
		{
			slIdx--;
		}
		else
		{
			slIdx++;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 오름차순 정렬된 이상(above) 미만(under) 범위내 Search @ Type:S32 */
U32 EngLib_AscendingAboveUnderArraySearchS32(S32 *paslTbl, U32 ulTblSize, S32 slKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	S32 slLower = 0;
	S32 slUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			slLower = paslTbl[slIdx];
			slUpper = ((slIdx+1) < (S32)ulTblSize) ? paslTbl[slIdx+1] : paslTbl[slIdx];
		}
		else
		{
			slLower = ((slIdx-1) < 0) ? paslTbl[slIdx] : paslTbl[slIdx-1];
			slUpper = paslTbl[slIdx];
		}
		
		if((slLower <= slKeyValue) && (slKeyValue < slUpper))
		{
			break;
		}
		else if(slKeyValue < slLower)
		{
			slIdx--;
		}
		else
		{
			slIdx++;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 오름차순 정렬된 이상(above) 미만(under) 범위내 Search @ Type:U32 */
U32 EngLib_AscendingAboveUnderArraySearchU32(U32 *paulTbl, U32 ulTblSize, U32 ulKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	U32 ulLower = 0;
	U32 ulUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			ulLower = paulTbl[slIdx];
			ulUpper = ((slIdx+1) < (S32)ulTblSize) ? paulTbl[slIdx+1] : paulTbl[slIdx];
		}
		else
		{
			ulLower = ((slIdx-1) < 0) ? paulTbl[slIdx] : paulTbl[slIdx-1];
			ulUpper = paulTbl[slIdx];
		}
		
		if((ulLower <= ulKeyValue) && (ulKeyValue < ulUpper))
		{
			break;
		}
		else if(ulKeyValue < ulLower)
		{
			slIdx--;
		}
		else
		{
			slIdx++;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 내림차순 정렬된 이하(below) 이상(above) 범위내 Search @ Type:S16 */
U32 EngLib_DescendingBelowAboveArraySearchS16(S16 *paswTbl, U32 ulTblSize, S16 swKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	S16 swLower = 0;
	S16 swUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			swLower = paswTbl[slIdx];
			swUpper = ((slIdx-1) < 0) ? paswTbl[slIdx] : paswTbl[slIdx-1] - 1;
		}
		else
		{
			swLower = ((slIdx+1) < (S32)ulTblSize) ? paswTbl[slIdx+1] + 1 : paswTbl[slIdx];
			swUpper = paswTbl[slIdx];
		}
		
		if((swLower <= swKeyValue) && (swKeyValue <= swUpper))
		{
			break;
		}
		else if(swKeyValue < swLower)
		{
			slIdx++;
		}
		else
		{
			slIdx--;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 내림차순 정렬된 이하(below) 이상(above) 범위내 Search @ Type:U16 */
U32 EngLib_DescendingBelowAboveArraySearchU16(U16 *pauwTbl, U32 ulTblSize, U16 uwKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	U16 uwLower = 0;
	U16 uwUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			uwLower = pauwTbl[slIdx];
			uwUpper = ((slIdx-1) < 0) ? pauwTbl[slIdx] : pauwTbl[slIdx-1] - 1;
		}
		else
		{
			uwLower = ((slIdx+1) < (S32)ulTblSize) ? pauwTbl[slIdx+1] + 1 : pauwTbl[slIdx];
			uwUpper = pauwTbl[slIdx];
		}
		
		if((uwLower <= uwKeyValue) && (uwKeyValue < uwUpper))
		{
			break;
		}
		else if(uwKeyValue < uwLower)
		{
			slIdx++;
		}
		else
		{
			slIdx--;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 내림차순 정렬된 이하(below) 이상(above) 범위내 Search @ Type:S32 */
U32 EngLib_DescendingBelowAboveArraySearchS32(S32 *paslTbl, U32 ulTblSize, S32 slKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	S32 slLower = 0;
	S32 slUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			slLower = paslTbl[slIdx];
			slUpper = ((slIdx-1) < 0) ? paslTbl[slIdx] : paslTbl[slIdx-1] - 1;
		}
		else
		{
			slLower = ((slIdx+1) < (S32)ulTblSize) ? paslTbl[slIdx+1] + 1 : paslTbl[slIdx];
			slUpper = paslTbl[slIdx];
		}
		
		if((slLower <= slKeyValue) && (slKeyValue < slUpper))
		{
			break;
		}
		else if(slKeyValue < slLower)
		{
			slIdx++;
		}
		else
		{
			slIdx--;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 내림차순 정렬된 이하(below) 이상(above) 범위내 Search @ Type:U32 */
U32 EngLib_DescendingBelowAboveArraySearchU32(U32 *paulTbl, U32 ulTblSize, U32 ulKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	U32 ulLower = 0;
	U32 ulUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			ulLower = paulTbl[slIdx];
			ulUpper = ((slIdx-1) < 0) ? paulTbl[slIdx] : paulTbl[slIdx-1] - 1;
		}
		else
		{
			ulLower = ((slIdx+1) < (S32)ulTblSize) ? paulTbl[slIdx+1] + 1 : paulTbl[slIdx];
			ulUpper = paulTbl[slIdx];
		}
		
		if((ulLower <= ulKeyValue) && (ulKeyValue < ulUpper))
		{
			break;
		}
		else if(ulKeyValue < ulLower)
		{
			slIdx++;
		}
		else
		{
			slIdx--;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}


/* 내림차순 정렬된 미만(under) 이상(above) 범위내 Search @ Type:S16 */
U32 EngLib_DescendingUnderAboveArraySearchS16(S16 *paswTbl, U32 ulTblSize, S16 swKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	S16 swLower = 0;
	S16 swUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			swLower = paswTbl[slIdx];
			swUpper = ((slIdx-1) < 0) ? paswTbl[slIdx] : paswTbl[slIdx-1];
		}
		else
		{
			swLower = ((slIdx+1) < (S32)ulTblSize) ? paswTbl[slIdx+1] : paswTbl[slIdx];
			swUpper = paswTbl[slIdx];
		}
		
		if((swLower <= swKeyValue) && (swKeyValue < swUpper))
		{
			break;
		}
		else if(swKeyValue < swLower)
		{
			slIdx++;
		}
		else
		{
			slIdx--;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 내림차순 정렬된 미만(under) 이상(above) 범위내 Search @ Type:U16 */
U32 EngLib_DescendingUnderAboveArraySearchU16(U16 *pauwTbl, U32 ulTblSize, U16 uwKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	U16 uwLower = 0;
	U16 uwUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			uwLower = pauwTbl[slIdx];
			uwUpper = ((slIdx-1) < 0) ? pauwTbl[slIdx] : pauwTbl[slIdx-1];
		}
		else
		{
			uwLower = ((slIdx+1) < (S32)ulTblSize) ? pauwTbl[slIdx+1] : pauwTbl[slIdx];
			uwUpper = pauwTbl[slIdx];
		}
		
		if((uwLower <= uwKeyValue) && (uwKeyValue < uwUpper))
		{
			break;
		}
		else if(uwKeyValue < uwLower)
		{
			slIdx++;
		}
		else
		{
			slIdx--;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 내림차순 정렬된 미만(under) 이상(above) 범위내 Search @ Type:S32 */
U32 EngLib_DescendingUnderAboveArraySearchS32(S32 *paslTbl, U32 ulTblSize, S32 slKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	S32 slLower = 0;
	S32 slUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			slLower = paslTbl[slIdx];
			slUpper = ((slIdx-1) < 0) ? paslTbl[slIdx] : paslTbl[slIdx-1];
		}
		else
		{
			slLower = ((slIdx+1) < (S32)ulTblSize) ? paslTbl[slIdx+1] : paslTbl[slIdx];
			slUpper = paslTbl[slIdx];
		}
		
		if((slLower <= slKeyValue) && (slKeyValue < slUpper))
		{
			break;
		}
		else if(slKeyValue < slLower)
		{
			slIdx++;
		}
		else
		{
			slIdx--;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* 내림차순 정렬된 미만(under) 이상(above) 범위내 Search @ Type:U32 */
U32 EngLib_DescendingUnderAboveArraySearchU32(U32 *paulTbl, U32 ulTblSize, U32 ulKeyValue, U32 ulBaseIdx, BOOL fRefLowValue)
{
	S32 slIdx = 0;
	U32 ulLower = 0;
	U32 ulUpper = 0;
	
	if(ulBaseIdx >= ulTblSize)
	{
		ulBaseIdx = ulTblSize-1;
	}
	
	for(slIdx = (S32)ulBaseIdx; (slIdx >= 0) && (slIdx < (S32)ulTblSize); )
	{
		if(fRefLowValue)
		{
			ulLower = paulTbl[slIdx];
			ulUpper = ((slIdx-1) < 0) ? paulTbl[slIdx] : paulTbl[slIdx-1];
		}
		else
		{
			ulLower = ((slIdx+1) < (S32)ulTblSize) ? paulTbl[slIdx+1] : paulTbl[slIdx];
			ulUpper = paulTbl[slIdx];
		}
		
		if((ulLower <= ulKeyValue) && (ulKeyValue < ulUpper))
		{
			break;
		}
		else if(ulKeyValue < ulLower)
		{
			slIdx++;
		}
		else
		{
			slIdx--;
		}
	}

	if(slIdx < 0)
	{
		slIdx = 0;
	}
	else if(slIdx >= (S32)ulTblSize)
	{
		slIdx = (S32)(ulTblSize-1);
	}

	return (U32)slIdx;
}

/* Average */
U32 EngLib_GetArrayAverageU32(U32 *paulArray, U32 ulCnt)
{
	U32 ulIdx;
	U32 ulSum = 0;

	ASSERT(ulCnt);
	
	for(ulIdx = 0; ulIdx < ulCnt; ulIdx++)
	{
		ulSum += paulArray[ulIdx];
	}
	return (ulSum / ulCnt);
}

/* Average by Abnormal Value Cutting */
U32 EngLib_GetArrayAverageAbnormalValueCutU32(U32 *paulArray, U32 ulAdcChkNum, U32 ulWasteNum)
{
	if(ulAdcChkNum >= 2)
	{
		#define C_MAX_CUT_NUM	10
		U32 ulIdx1 = 0;
		U32 ulIdx2 = 0;
		U32 aulAbnormalData[2][C_MAX_CUT_NUM] = { 0, };
		U32 ulDataSum = 0;
		U32 ulAverage = 0;
		U32 ulDataOffset1 = 0;
		U32 ulDataOffset2 = 0;
		U32 ulTempData1 = 0;
		U32 ulTempData2 = 0;
		U32 ulAbnormalDataSum = 0;

		ASSERT(ulAdcChkNum > ulWasteNum);
		ASSERT(ulWasteNum <= C_MAX_CUT_NUM);

		for(ulIdx1 = 0; ulIdx1 < ulAdcChkNum; ulIdx1++)
		{
			ulDataSum += paulArray[ulIdx1];
 		}
		ulAverage = ulDataSum / ulAdcChkNum;

		for(ulIdx1 = 0; ulIdx1 < ulWasteNum; ulIdx1++)
		{
			aulAbnormalData[1][ulIdx1] = ulAverage;
		}
		
		for(ulIdx1 = 0; ulIdx1 < ulAdcChkNum; ulIdx1++)
		{
			ulDataOffset1 = (paulArray[ulIdx1] > ulAverage) ? paulArray[ulIdx1] - ulAverage : ulAverage - paulArray[ulIdx1];
			ulTempData1 = paulArray[ulIdx1];
			ulAbnormalDataSum = 0;
			
			for(ulIdx2 = 0; ulIdx2<ulWasteNum; ulIdx2++)
			{
				//Check Max Value
				if(aulAbnormalData[0][ulIdx2] < ulDataOffset1)
				{
					ulDataOffset2 = aulAbnormalData[0][ulIdx2];
					ulTempData2 = aulAbnormalData[1][ulIdx2];
					aulAbnormalData[0][ulIdx2] = ulDataOffset1;
					aulAbnormalData[1][ulIdx2] = ulTempData1;
					ulDataOffset1 = ulDataOffset2;
					ulTempData1 = ulTempData2;
				}
				ulAbnormalDataSum += aulAbnormalData[1][ulIdx2];
			}
		}

		if(ulAbnormalDataSum > 0)
		{
			ulDataSum -= ulAbnormalDataSum;
			return (ulDataSum / (ulAdcChkNum - ulWasteNum));
		}
		else
		{
			return (ulDataSum / ulAdcChkNum);
		}
	}
	else
	{
		return paulArray[0];
	}
}

/* Average by Min/Max Cutting */
U32 EngLib_GetAverageArrayMinMaxCutU32(U32 *paulArray, U32 ulAdcChkNum, U32 ulWasteNum)
{
	if(ulAdcChkNum >= 2)
	{
		#define C_MAX_CUT_NUM	10
		U32 ulIdx1 = 0;
		U32 ulIdx2 = 0;
		U32 ulTempMinData1 = 0;
		U32 ulTempMinData2 = 0;
		U32 ulTempMaxData1 = 0;
		U32 ulTempMaxData2 = 0;
		U32 aulMinData[C_MAX_CUT_NUM] = { MAX_U32, MAX_U32, MAX_U32, MAX_U32, MAX_U32, MAX_U32, MAX_U32, MAX_U32, MAX_U32, MAX_U32 };
		U32 aulMaxData[C_MAX_CUT_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		U32 ulMinDataSum = 0;
		U32 ulMaxDataSum = 0;
		U32 ulResultSum = 0;

		ASSERT(ulAdcChkNum > ulWasteNum * 2);
		ASSERT(ulWasteNum <= C_MAX_CUT_NUM);
		
		for(ulIdx1 = 0; ulIdx1 < ulAdcChkNum; ulIdx1++)
		{
			ulResultSum += paulArray[ulIdx1];

			ulTempMinData1 = paulArray[ulIdx1];
			ulTempMaxData1 = paulArray[ulIdx1];
			ulMinDataSum = 0;
			ulMaxDataSum = 0;
			for(ulIdx2 = 0; ulIdx2<ulWasteNum; ulIdx2++)
			{
				//Check Min Value
				if(aulMinData[ulIdx2] > ulTempMinData1)
				{
					ulTempMinData2 = aulMinData[ulIdx2];
					aulMinData[ulIdx2] = ulTempMinData1;
					ulTempMinData1 = ulTempMinData2;
				}
				ulMinDataSum += aulMinData[ulIdx2];
					
				//Check Max Value
				if(aulMaxData[ulIdx2] < ulTempMaxData1)
				{
					ulTempMaxData2 = aulMaxData[ulIdx2];
					aulMaxData[ulIdx2] = ulTempMaxData1;
					ulTempMaxData1 = ulTempMaxData2;
				}
				ulMaxDataSum += aulMaxData[ulIdx2];
			}
		}

		ulResultSum -= (ulMinDataSum + ulMaxDataSum);

		if(ulAdcChkNum - (ulWasteNum * 2) == 0)
		{
			ASSERT(0);
		}
		else
		{
			return (ulResultSum / (ulAdcChkNum - (ulWasteNum * 2)));
		}
	}
	else
	{
		return paulArray[0];
	}
}

S32 EngLib_GetAverageArrayCutPrePost(S32 *paulArray, U32 ulAdcChkNum, U32 ulPreWasteNum, U32 ulPostWasteNum)
{
	if(ulAdcChkNum>=2)
	{
		U32 ulIdx_1;
		U32 ulIdx_2;
		S32 ulArrayTemp;
		S32 ulResultSum = 0;

		ASSERT(ulAdcChkNum > ulPreWasteNum+ulPostWasteNum);

		/* Sort Array */
		for(ulIdx_1 = 0; ulIdx_1 < (ulAdcChkNum-1); ulIdx_1++)
		{
			for(ulIdx_2 = ulIdx_1+1; ulIdx_2 < ulAdcChkNum; ulIdx_2++)
			{
				if(paulArray[ulIdx_2] >= paulArray[ulIdx_1])
				{
					ulArrayTemp = paulArray[ulIdx_1];
					
					paulArray[ulIdx_1] = paulArray[ulIdx_2];
					paulArray[ulIdx_2] = ulArrayTemp;
				}
			}
		}
		
		/* Calculate Average */
		for(ulIdx_1 = ulPreWasteNum; ulIdx_1 < (ulAdcChkNum - ulPostWasteNum); ulIdx_1++)
		{
			ulResultSum += paulArray[ulIdx_1];
		}

		return (ulResultSum / (S32)(ulAdcChkNum - (ulPreWasteNum + ulPostWasteNum)));
	}
	else
	{
		return paulArray[0];
	}
}

/* Min Max */
U32 EngLib_ArrayGetMax(U32 *paulArray, U32 ulCnt)
{
	U32 ulIdx;
	U32 ulMax = paulArray[0];

	for(ulIdx = 0; ulIdx < ulCnt; ulIdx++)
	{
		if(paulArray[ulIdx] > ulMax)
		{
			ulMax = paulArray[ulIdx];
		}
	}

	return ulMax;
}

U32 EngLib_ArrayGetMin(U32 *paulArray, U32 ulCnt)
{
	U32 ulIdx;
	U32 ulMin = paulArray[0];

	for(ulIdx = 0; ulIdx < ulCnt; ulIdx++)
	{
		if(paulArray[ulIdx] < ulMin)
		{
			ulMin = paulArray[ulIdx];
		}
	}

	return ulMin;
}

/* Math */
D32 EngLib_POW(D32 dx, U32 uly)
{
	D32 dRetVal = 1.0;
	U32 ulIdx = 0;
	
	for(ulIdx = 0; ulIdx < uly; ulIdx++)
	{
		dRetVal *= dx;
	}

	return dRetVal;
}

/**
 * @brief		Cyclic redundancy check Initilalization.
 * @author		
 * @date		2010/03/00
 * @param	 	void 
 * @return		void
 * @todo			
*/
void EngLib_InitCRC16Tab(U16 *puwCRCBuff)
{
    U16 uwCrc, uwC, uw_i, uw_j;

    for (uw_i=0; uw_i<256; uw_i++)
    {
        uwCrc = 0;
        uwC   = uw_i;

        for (uw_j=0; uw_j<8; uw_j++)
        {
            if ((uwCrc ^ uwC) & 0x0001 )
            {
                uwCrc = (uwCrc >> 1 ) ^ P_16;
            }

            else
            {
                uwCrc =   uwCrc >> 1;
            }
            uwC = uwC >> 1;
        }
        puwCRCBuff[uw_i] = uwCrc;
    }
}  /* EngLib_InitCRC16Tab */

    /*******************************************************************\
    *                                                                   *
    *   unsigned short EngLib_UpdateCRC16( unsigned long crc, char c );      *
    *                                                                   *
    *   The function EngLib_UpdateCRC16 calculates a  new  CRC-16  value     *
    *   based  on  the  previous value of the CRC and the next byte     *
    *   of the data to be checked.                                      *
    *                                                                   *
    \*******************************************************************/

/**
 * @brief		The function EngLib_UpdateCRC16 calculates a new CRC-16 value based  on  the  previous value of the CRC and the next byte.
 * @author		
 * @date		2010/03/00
 * @param	 	unsigned long,  char
 * @return		unsigned long
 * @todo			
*/
U16 EngLib_UpdateCRC16(U16 *pubCRCBuff, U16 uwCrc, U8 ubC )
{

    U16 uw_tmp, uw_c;
    uw_c = ubC;
//    if ( ! crc_tab16_init ) EngLib_InitCRC16Tab();
    uw_tmp =  uwCrc^uw_c;
    uwCrc = (uwCrc >> 8) ^ pubCRCBuff[ uw_tmp & 0xff ];
    return uwCrc;

}  /* EngLib_UpdateCRC16 */

/**
 * @brief		Calculate Cyclic redundancy check.
 * @author		
 * @date		2010/03/00
 * @param	 	void 
 * @return		void
 * @todo			
*/

U16 EngLib_CalcCRC16(U16 *pubCRCBuff, U16 uwCRC, U32 ulBufSize, U8 *pubBuf)	
{
	U32 ulIndex;
	for(ulIndex=0;ulIndex<ulBufSize;ulIndex++)
	{
		uwCRC = EngLib_UpdateCRC16(pubCRCBuff, uwCRC, *(pubBuf+ulIndex));
	}		
	return uwCRC;	
}

/* Swap */
void EngLib_SwapMem(char *a, char *b, int size)
{
	register char t;
	register int i;

	for(i = 0; i < size; ++i,++b,++a)
	{
		t = *a;
		*a = *b;
		*b = t;
	}
}

S32 EngLib_GetBitIndex(U32 ulBit)
{
	volatile S32 slIdx = 0;
	
	if(ulBit == 0)
	{
		return -1;
	}

	while(!(ulBit & (0x1<<slIdx)))
	{
		slIdx++;
	}

	return slIdx;
}

/* semaphore */
void EngLib_InitSemaphore(TSemaphore *pstSemaphore)
{
	pstSemaphore->sbCount = 1;
}

BOOL EngLib_WaitSemaphore(TSemaphore *pstSemaphore)
{
	BOOL fBlock = FALSE;

	pstSemaphore->sbCount--;
	if(pstSemaphore->sbCount < 0)
	{
		fBlock = TRUE;
	}
	
	return fBlock;
}

BOOL EngLib_SemaphoreSignal(TSemaphore *pstSemaphore)
{
	BOOL fUnblock = TRUE;

	pstSemaphore->sbCount++;
	if(pstSemaphore->sbCount <= 0)
	{
		fUnblock = FALSE;
	}

	return fUnblock;
}

static const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
static const char upper_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

U32 EngLib_StrnLength(const char *s, unsigned int count)
{
	const char *sc;
	for(sc = s; *sc != '\0' && count--; ++sc);
	return sc - s;
}

S32 EngLib_AtoI(const char *s)
{
	int i = 0;
	
	while(is_digit(*s))
	{
		i = i*10 + *(s++) - '0';
	}
	return i;
}

U8 *EngLib_Number(char *str, unsigned int num, int base, int type, int *length)
{
	char sign, tmp[30];
	const char *dig = digits;
	int i;
	int pos=0;

	sign = 0;
	
	if(type & SIGN)
	{
		if((int)num < 0)
		{
			sign = '-';
			num = (unsigned int)((int)num * -1);
		}
	}

	i = 0;

	if(num == 0)
	{
		tmp[i++] = '0';
	}
	else
	{
		while(num != 0)
		{
			pos = ((unsigned long) num) % (unsigned)base;
			tmp[i++] = dig[pos];
			num = ((unsigned long) num) / (unsigned)base;
		}

		if(sign == '-')
		{
			tmp[i++] = sign;
		}
	}

	i = (i > *length) ? *length : i;
	*length -= i;
	
	while(i > 0)
	{
		*str++ = tmp[i-1];
		i--;
	}

	return str;
}

S32 EngLib_SimpleVNSprintf(char *buffer, const char *format, va_list argptr, int length)
{
	unsigned int num;
	int errcnt=0;
	char *str;
	char *s;

	int flags = 0;            // Flags to number()

	for(str = buffer; *format; format++)
	{	
		if(length <= 0)
		{
			return -1;
		}
		
		if(*format != '%')
		{
			*str++ = *format;
			length--;
			continue;
		}

		repeat:
			format++; // This also skips first '%'

		flags = 0; 
		switch (*format)
		{
			case 'c':
				*str++ = (unsigned char) va_arg(argptr, int);
				length--;
				break;

			case 's':
				s = va_arg(argptr, char *);
				if(s == 0)
				{
					s = "NULL";
				}
			
				for( ; (*s != '\0') && (length > 0); length--)
				{
					*str++ = *s++;
				}
				break;

			case 'o':
				num = va_arg(argptr, unsigned int);			
				str = EngLib_Number(str, num, 8, 0, &length);
				break;

			case 'X':
			case 'x':
				num = va_arg(argptr, unsigned int);
				str = EngLib_Number(str, num, 16, 0, &length);
				break;

			case 'd':
				flags |= SIGN;
				num = va_arg(argptr, unsigned int);
				str = EngLib_Number(str, num, 10, flags, &length);					
				break;
				
			case 'u':
				num = va_arg(argptr, unsigned int);
				str = EngLib_Number(str, num, 10, flags, &length);
				break;

#if 0
			case 'T':
				s = (char *)(EngTM_IF_GetCurrentRTCTime("%d-%02d-%02d %02d:%02d:%02d"));
				if(s)
				{
					for( ; (*s != '\0') && (length > 0); length--)
					{
						*str++ = *s++;
					}
				}
				break;
#endif

			default:
				goto repeat;
				break;
		}
	}
	
	return length;
}

S32 EngLib_SimpleNSprintf(char *buffer, int length, const U8 *format, ...)
{
	int slRemainLength = 0;
	va_list ap;
	va_start(ap, format);
	
	slRemainLength = EngLib_SimpleVNSprintf(buffer, (const char *)format, ap, length);

	va_end(ap);

	return slRemainLength;
}

void* EngLib_MemorySet(void *pstDest, S32 slData, U32 ulSize)
{
	if(pstDest != NULL)
	{
		return memset(pstDest, slData, ulSize);
	}
	else
	{
		DBG_EMERGENCY("\r\n[%s:LIB] EngLib_MemorySet Exception : 0x%x <- %d, %d", ENG_TICK, pstDest, slData, ulSize);
		EngLib_DumpStack(NULL);

		return 0;
	}
}

void* EngLib_MemoryCopy(void *pstDest, void *pstSrc, U32 ulSize)
{
	if(pstDest != NULL)
	{
		return memcpy(pstDest, pstSrc, ulSize);
	}
	else
	{
		DBG_EMERGENCY("\r\n[%s:LIB] EngLib_MemoryCopy Exception : 0x%x <- 0x%x, %d", ENG_TICK, pstDest, pstSrc, ulSize);
		EngLib_DumpStack(NULL);

		return 0;
	}
}

BOOL EngLib_CheckIRQMode(void)
{
	unsigned int ulMode = 0;
#ifndef ENABLE_EFS_MODE
	
	// __asm {
    // 	MRS ulMode, CPSR
	// }

//	DBG_EMERGENCY(ENG_DBG_STRING"ChkIRQ:0x%0x", ENG_TICK, "Lib", ulMode);
	
	if(((ulMode & 0x1F) == 0x12) /* 10010b IRQ Mode */
		|| ((ulMode & 0x1F) == 0x1F) /* 10010b System Mode */
	)
	{
		return TRUE; /* printf("IRQ\n"); */
	}
	else
	{
		return FALSE; /* printf("non IRQ\n"); */
	}
#else
	return FALSE;
#endif
}

void EngLib_CallBackWatchDog(void)
{
	U8 *pubTime = NULL;

	if(stEngLib.pfnGetCurrentRTCTime)
	{
		pubTime = stEngLib.pfnGetCurrentRTCTime("%d-%02d-%02d %02d:%02d:%02d");
	}

	/* Call handler */
	if(stEngLib.pfnSMHndIFSendEvent)
	{
		//stEngLib.pfnSMHndIFSendEvent(ENG_HND_MH, ENG_EV_OCCURRED_EXCEPTION, NULL, NULL, 0);
	}
	
	EngLib_DumpStack(NULL);
	DBG_EMERGENCY("\r\n[%s:WD] === WatchDogCalled(%s) ===", ENG_TICK, pubTime);					DBG_EMERGENCY_UART("\r\n[%s:WD] === WatchDogCalled(%s/%x) ===", ENG_TICK, pubTime);

//	EngLog_StopLogging();
}

void EngLib_DumpRegister(U32 *pulRegs)
{
    DBG_EMERGENCY("\r\n----------------------------");  										DBG_EMERGENCY_UART("\r\n----------------------------");    
	DBG_EMERGENCY("\r\nSP =%x ",  pulRegs[13]);													DBG_EMERGENCY_UART("\r\nSP =%x ",  pulRegs[13]);
	DBG_EMERGENCY("LR =%x", pulRegs[14]);														DBG_EMERGENCY_UART("LR =%x", pulRegs[14]);
	DBG_EMERGENCY("\r\nR0 =%x ",  pulRegs[0]);													DBG_EMERGENCY_UART("\r\nR0 =%x ",  pulRegs[0]);
	DBG_EMERGENCY("R1 =%x ",  pulRegs[1]);														DBG_EMERGENCY_UART("R1 =%x ",  pulRegs[1]);
	DBG_EMERGENCY("R2 =%x ",  pulRegs[2]);														DBG_EMERGENCY_UART("R2 =%x ",  pulRegs[2]);
	DBG_EMERGENCY("R3 =%x ",  pulRegs[3]);														DBG_EMERGENCY_UART("R3 =%x ",  pulRegs[3]);
	DBG_EMERGENCY("\r\nR4 =%x", pulRegs[4]);													DBG_EMERGENCY_UART("\r\nR4 =%x", pulRegs[4]);
	DBG_EMERGENCY("R5 =%x ",  pulRegs[5]);														DBG_EMERGENCY_UART("R5 =%x ",  pulRegs[5]);
	DBG_EMERGENCY("R6 =%x ",  pulRegs[6]);														DBG_EMERGENCY_UART("R6 =%x ",  pulRegs[6]);
	DBG_EMERGENCY("R7 =%x ",  pulRegs[7]);														DBG_EMERGENCY_UART("R7 =%x ",  pulRegs[7]);
	DBG_EMERGENCY("R8 =%x ",  pulRegs[8]);														DBG_EMERGENCY_UART("R8 =%x ",  pulRegs[8]);
	DBG_EMERGENCY("\r\nR9 =%x", pulRegs[9]);													DBG_EMERGENCY_UART("\r\nR9 =%x", pulRegs[9]);
	DBG_EMERGENCY("R10=%x ",  pulRegs[10]);														DBG_EMERGENCY_UART("R10=%x ",  pulRegs[10]);
	DBG_EMERGENCY("R11=%x ",  pulRegs[11]);														DBG_EMERGENCY_UART("R11=%x ",  pulRegs[11]);
	DBG_EMERGENCY("\r\nR12=%x", pulRegs[12]);													DBG_EMERGENCY_UART("\r\nR12=%x", pulRegs[12]);
	DBG_EMERGENCY("\r\nPC =%x", pulRegs[15] );													DBG_EMERGENCY_UART("\r\nPC =%x", pulRegs[15] );

	/* Dump Stack */
	// EngLib_DumpStack(pulRegs[13]);
}

void EngLib_DumpStack(U32 *pulStackAddr)
{
	U32 ulCnt = 0;
	U8 *pubTime = NULL;

#ifndef ENABLE_EFS_MODE
	if(pulStackAddr == NULL)
	{
		// __asm
		// {
		// 	mov pulStackAddr, sp		
		// }
	}

	if(stEngLib.pfnGetCurrentRTCTime)
	{
		pubTime = stEngLib.pfnGetCurrentRTCTime("%d-%02d-%02d %02d:%02d:%02d");
	}

	DBG_EMERGENCY("\r\n***** Stack Dump(%s / %s) *****", C_ENG_FULL_VERSION, pubTime);			DBG_EMERGENCY_UART("\r\n***** Stack Dump(%s / %s) *****", C_ENG_FULL_VERSION, pubTime);	
	DBG_EMERGENCY("\r\nSP = 0x%x", pulStackAddr);												DBG_EMERGENCY_UART("\r\nSP = 0x%x", pulStackAddr);
	
	if(pulStackAddr != NULL)
	{
		for(ulCnt = 0; ulCnt < 16*16; ulCnt++, pulStackAddr++)
		{
			if(ulCnt % 16 == 0)
			{
				DBG_EMERGENCY("\r\n");															DBG_EMERGENCY_UART("\r\n");
			}
			DBG_EMERGENCY("0x%08x ",  *pulStackAddr);											DBG_EMERGENCY_UART("0x%08x ",  *pulStackAddr);
		}
	}
	DBG_EMERGENCY("\r\n*************************************************");						DBG_EMERGENCY_UART("\r\n*************************************************");	
#endif
}

/*** SpinLock Useage *****

   	U32 ulMask = 0;
	ulMask = EngLib_SpinLock(1);
	...
	...
	EngLib_SpinLock(ulMask);
*/
U32 EngLib_SpinLock(U32 ulMask)
{
	U32 ulRetVal = 0;	
#ifndef ENABLE_EFS_MODE
	// __asm
	// {
	// 	MRS     r1, CPSR			//; Read the old CPSR
    //     BIC     r2, r1, #0x80		//; Clear the interrupt bit in the old CPSR
    //     CMP     ulMask, #1			// ; Test the level of interrupt to set
    //     ORRHS   r2, r2, #0x80		//; >= 1 => set the interrupt bit
    //     MSR     CPSR_cf, r2			//; Write the new CPSR
    //     MOVS    r1, r1, LSL #25		//; Get the old interrupt bit into carry
    //     MOV     r0, #0				//; Return 0 if clear
    //     MOVCS   r0, #1				//; 1 if set
    //     mov ulRetVal, r0			
	// }
#endif
	return ulRetVal;
}

static S32 __fp_status_flags = DZE_BIT + OFE_BIT + IOE_BIT;

U32 *__rt_fp_status_addr()
{
    DBG_EMERGENCY("\r\n__rt_fp_status_addr: FP exception, &__fp_status_flags = 0x%x", &__fp_status_flags );
	DBG_EMERGENCY_UART("\r\n__rt_fp_status_addr: FP exception, &__fp_status_flags = 0x%x", &__fp_status_flags );
	
    return &__fp_status_flags;
}

void __rt_trap(ErrBlock *err, U32 *pulRegs)
{
	U32 ulCnt = 0;

	/* Change To Error Mode */
	//stEngLib.pfnSMHndIFStartHandler(ENG_HND_EH, ERROR_NAME_EXCEPTION, NULL);

	/* Error Code 
	0x80000020 - Integer divide by zero.
	0x80000200 - Invalid floating-point operation.
	0x80000201 - Floating-point overflow.
	0x80000202 - Floating-point divide by zero.
	*/

	DBG_EMERGENCY("\r\n-----------------------------------------------------");    								DBG_EMERGENCY_UART("\r\n-----------------------------------------------------"); 
    DBG_EMERGENCY("\r\nFloating Point Exception");    															DBG_EMERGENCY_UART("\r\nFloating Point Exception");    
    DBG_EMERGENCY("\r\n-----------------------------------------------------");  								DBG_EMERGENCY_UART("\r\n-----------------------------------------------------"); 
	
	/*dump programming counter and floating status flags*/
    DBG_EMERGENCY("\r\n__rt_trap: (PC = 0x%x), __fp_status_flags = 0x%x", pulRegs[15], __fp_status_flags);		DBG_EMERGENCY_UART("\r\n__rt_trap: (PC = 0x%x), __fp_status_flags = 0x%x", pulRegs[15], __fp_status_flags);

	/*dump error code and error string*/
    DBG_EMERGENCY("\r\n__rt_trap: Error Code = 0x%x, %s",  err->ErrCode, err->ErrString);						DBG_EMERGENCY_UART("\r\n__rt_trap: Error Code = 0x%x, %s",  err->ErrCode, err->ErrString);
	
	/* Dump Register */
	EngLib_DumpRegister(pulRegs);

	/* Call handler */
	if(stEngLib.pfnSMHndIFSendEvent)
	{
		//stEngLib.pfnSMHndIFSendEvent(ENG_HND_MH, ENG_EV_OCCURRED_EXCEPTION, NULL, NULL, 0);
	}

	DBG_EMERGENCY("\r\n------------------ RT_Trap_End ------------------");										DBG_EMERGENCY_UART("\r\n------------------ RT_Trap_End ------------------");
}

//extern U8 *_ImageEngineStart;	//Defined in begina.s file
//extern U8 *_ImageEngineEnd;		//Defined in begina.s file

BOOL EngLib_IsEngineArea(U8* pubAddress)
{	

#ifndef ENABLE_EFS_MODE
	// if((_ImageEngineStart > pubAddress)
	// 	|| (_ImageEngineEnd < pubAddress)
	// )
	// {
	// 	DBG_EMERGENCY(ENG_DBG_STRING"NotEngineArea(0x%x-0x%x) : 0x%x", ENG_TICK, "Lib", _ImageEngineStart, _ImageEngineEnd, pubAddress);
	// 	EngLib_DumpStack(NULL);
	// 	return FALSE;
	// }
#endif
	return TRUE;
}

U16 EngLib_CRC_16_CCITT(const char *buf, int len)
{
	U32 ulCounter;
	U16 uwCRC = 0;
	for( ulCounter = 0; ulCounter < (U32)len; ulCounter++)
		uwCRC = (uwCRC<<8) ^ crc16tab[((uwCRC>>8) ^ *(char *)buf++)&0x00FF];
	return uwCRC;
}

