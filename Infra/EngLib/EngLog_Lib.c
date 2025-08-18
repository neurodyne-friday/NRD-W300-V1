/**
 * @file        EngLog_Lib.c
 * @brief       This main code for Engine Log Component.
 *
 * <b> Copyright 2024 Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Samsung Electronics, Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp			
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		05/11/2009(D/M/Y)
 * @version		V0.1
 */

#define	__ENGLOG_LIB_C__

#include "Eng_CommonType.h"
#include "EngLib_Types.h"
#include "EngLog_Lib.h"

#ifdef FR_ENGLIB_LOG

/* Engine Log Info Data */
TEngLogInfo stEngLogInfo = {NULL};


#define C_TASK_LOG_BUFF_AREA_NUM	TASK_LOG_AREA_MAX

static U32 s_aulArgDBuffIRQ[ARG_DBUFF_SIZE_IRQ] = {0,};
static TQueue s_astArgDQueue[C_TASK_LOG_BUFF_AREA_NUM] = {0,};

static TMsgQCB s_stTaskLoggingMsgQCB;
static TMsgQ s_astTaskLoggingMsgQ[C_TASK_LOG_MSG_Q_MAX];

static U32 s_ulTaskLogSemaphoreID = 0;
static BOOL s_fEnableTaskLog = FALSE;
static void *s_apvInsertArgFuncHashTbl[MAX_U8+1] = {0,};


BOOL EngLog_InitTaskLogging(void)
{	
	EngLib_MemorySet(s_apvInsertArgFuncHashTbl, 0, sizeof(s_apvInsertArgFuncHashTbl));

	s_apvInsertArgFuncHashTbl['c'] = (void *)EngLog_InsertDataArg;
	// s_apvInsertArgFuncHashTbl['o'] = (void *)EngLog_InsertDataArg;
	// s_apvInsertArgFuncHashTbl['X'] = (void *)EngLog_InsertDataArg;
	// s_apvInsertArgFuncHashTbl['x'] = (void *)EngLog_InsertDataArg;
	// s_apvInsertArgFuncHashTbl['d'] = (void *)EngLog_InsertDataArg;
	// s_apvInsertArgFuncHashTbl['u'] = (void *)EngLog_InsertDataArg;
	// s_apvInsertArgFuncHashTbl['s'] = (void *)EngLog_InsertStrArg;

	EngLib_InitQueue(&s_astArgDQueue[TASK_LOG_AREA_IRQ], (void *)s_aulArgDBuffIRQ, ARG_DBUFF_SIZE_IRQ);
	// EngLib_InitQueue(&s_astArgSQueue[TASK_LOG_AREA_IRQ], (void *)s_aubArgSBuffIRQ, ARG_SBUFF_SIZE_IRQ);
	// EngLib_InitQueue(&s_astArgDQueue[TASK_LOG_AREA_TASK], (void *)s_aulArgDBuffTask, ARG_DBUFF_SIZE_TASK);
	// EngLib_InitQueue(&s_astArgSQueue[TASK_LOG_AREA_TASK], (void *)s_aubArgSBuffTask, ARG_SBUFF_SIZE_TASK);

	s_stTaskLoggingMsgQCB.fBusy = FALSE;
	s_stTaskLoggingMsgQCB.ulMsgQHead = 0;
	s_stTaskLoggingMsgQCB.ulMsgQTail = 0;
	s_stTaskLoggingMsgQCB.ulMsgQSize = C_TASK_LOG_MSG_Q_MAX;
	s_stTaskLoggingMsgQCB.pstMsgQ = s_astTaskLoggingMsgQ;
		
	return TRUE;
}

BOOL EngLog_InsertDataArg(TTaskLogArea enLogArea, U32 ulData)
{
	TQueue *pstQueue = &s_astArgDQueue[enLogArea];
	U32 *pulData = (U32 *)pstQueue->pvBuffer;
	
	/* Queue is Full */
	if(((pstQueue->ulTail + 1) % pstQueue->ulSize) == pstQueue->ulHead)
	{
		return FALSE;
	}

#ifdef TASK_LOG_DEBUGGING
	ENG_PRINT("I_ARGD[%d]:%d ", pstQueue->ulTail, ulData);
#endif

	pulData[pstQueue->ulTail] = ulData;
	
	if(++pstQueue->ulTail >= pstQueue->ulSize)
	{
		pstQueue->ulTail = 0;
	}

	return TRUE;
}

void EngLog_LibraryEntry(TInitialStepType enInitStep)
{
	if(enInitStep & INIT_STEP_1ST)
	{
#ifdef FR_ENGLIB_TASK_LOGGING
		EngLog_InitTaskLogging();
#endif

		/* Initial Engine Log Information */
		stEngLogInfo.pstParamInfoTbl = stLogInfoTbl;
		
		stEngLogInfo.pstDumpLog = NULL;
		stEngLogInfo.pstMicroSDLog = NULL;
		stEngLogInfo.pstTaskDump = NULL;
		stEngLogInfo.pstUartPrint = NULL;
		stEngLogInfo.pstSwoPrint = NULL;

		/* Initial for Engine Log Area Data */
		// EngLog_DumpLogCreate(&stEngLogInfo.pstDumpLog); // 추구 활성화

		/* Initial for HDD Log Area Data */
#if defined(HR_ENGLIB_DEBUG_MESSAGE_MICRO_SD_SAVE)
		EngLog_MicroSDLogCreate(&stEngLogInfo.pstMicroSDLog);
#endif

		/* Initial for Task Log Print Info */
#if defined(FR_ENGLIB_TASK_DUMP_DEBUG)
		EngLog_TaskDumpCreate(&stEngLogInfo.pstTaskDump);
#endif

		/* Initial for Uart Log Print Info */
#if defined(FR_ENGLIB_UART_DEBUG)
		EngLog_UartPrintCreate(&stEngLogInfo.pstUartPrint);
#endif

		/* Initial for SWO Log Print Info */
#if defined(FR_ENGLIB_SWO_DEBUG)
		EngLog_SWOPrintCreate(&stEngLogInfo.pstSwoPrint);
#endif

		EngLog_ClearAll();
	}

	if(enInitStep & INIT_STEP_2ND)
	{
		U32 ulStatus = 0;
		
#ifdef U_FR_ENGLIB_TASK_LOGGING
		// ulStatus = EngOS_OSALCreateSemaphore("STLOG", 1, &s_ulTaskLogSemaphoreID);
		// VOID_ASSERT(!ulStatus);

		// ulStatus = EngOS_OSALCreateTask((U8*)"TLog",
        //                 (U32(*)())EngLog_TaskLoggingManager,
        //                 NULL,
        //                 TASK_LOGGING_STACK_SIZE,
        //                 TASK_LOGGING_PRIORITY,
        //                 &ulTaskLoggingID
        //                 );
    	// VOID_ASSERT(!ulStatus);

		s_fEnableTaskLog = TRUE;
		EngOS_CreateJobProperty(
			&stEngLogInfo.pstTaskLoggingJob,
			"EngLog_TaskLogging",
			ulTaskLoggingID,
			TASK_LOGGING_STACK_SIZE,
			TASK_LOGGING_PRIORITY,
			0, 0, 0, 0, 0, 0, 0, 0
		);
#endif
	}
}

void* EngLog_DumpLogDataMemoryAlloc(void)
{
#if	!defined(C_ENG_LOG_STATIC_ADDRESS) || (C_ENG_LOG_STATIC_ADDRESS == 0x00000000) || defined(ENG_PC_SIM) || defined(ENABLE_EFS_MODE)
	static TDumpLogData s_stEngLog = {0};
	return &s_stEngLog;
#else
	return C_ENG_LOG_STATIC_ADDRESS;
#endif		
}


BOOL EngLog_DumpLogCreate(TDumpLog** pstEngLogInfo)
{
	static TDumpLog stDumpLog = {0};

	ASSERT(pstEngLogInfo);
	
	/* Alloc Memory for Engine Log Area Data */
	stDumpLog.pstDumpLogData = (TDumpLogData *)EngLog_DumpLogDataMemoryAlloc();
	ASSERT(stDumpLog.pstDumpLogData);

	stDumpLog.pstDumpLogData->ulLogIdentity = C_ENG_LOG_AREA_IDENTITY;
	stDumpLog.pstDumpLogData->ulLogStatusFlag = 0;
	stDumpLog.pstDumpLogData->ulWriteOffset = 0;
	stDumpLog.pstDumpLogData->ulLogDataSize = C_ENG_LOG_DATA_SIZE;

	stDumpLog.ulLogLevel = C_DEBUG_LV;
	
	*pstEngLogInfo = &stDumpLog;

	return TRUE;
}


void EngLog_DynamicTaskLog(U32 ulId, const U8 *pubStr, va_list ap)
{
 	TLogParamInfo *pstParamInfo = &stEngLogInfo.pstParamInfoTbl[ulId];

 	if(s_fEnableTaskLog == FALSE)
 	{
 		EngLog_DynamicDumpLog(ulId, pubStr, ap);
		
 		return;		
 	}
	
 	if(pstParamInfo != NULL)
 	{		
 		TDumpLog *pstDumpLog = stEngLogInfo.pstDumpLog;	
// #if defined(HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE) && defined(C_HDD_LOG_SAVE_NEW)
// 		THDDLog *pstHDDLog = stEngLogInfo.pstHDDLog;
// #endif
 		U32	ulEngState = EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_ENGINE_STATE);
 		TTaskLogArea enLogArea = TASK_LOG_AREA_IRQ;
 		TMsgQ stSendMsgQ = {0};

 		stSendMsgQ.ulLParam = 0;
		
 		/* Check condition to print log by HDD */
// #if defined(HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE) && defined(C_HDD_LOG_SAVE_NEW)		
// 		if((pstParamInfo->fPrintToHDD == TRUE)
// 			&& (pstParamInfo->ulLevel <= pstHDDLog->ulLogLevel)
// //			&& (ulEngState != ENGSM_STS_CHILD_ENGINE_STANDBY)
// //			&& (ulEngState != ENGSM_STS_CHILD_ENGINE_SLEEP)
// 		)
// 		{
// 			stSendMsgQ.ulLParam |= 0x1;
// 		}
// #endif

 		/* Check condition to print log by RAM Dump */
 		if((pstParamInfo->fPrintToDump == TRUE)
 			&& (pstParamInfo->ulLevel <= pstDumpLog->ulLogLevel)
 		)
 		{
 			stSendMsgQ.ulLParam |= 0x2;
 		}

 		/* Check condition to print log by UART */
 		if(pstParamInfo->fPrintToUart == TRUE)
 		{
 			stSendMsgQ.ulLParam |= 0x4;
 		}

 		/* Send Log to task */
 		if(stSendMsgQ.ulLParam)
 		{
 			// if(EngLib_CheckIRQMode() == FALSE)
 			// {
 			// 	enLogArea = TASK_LOG_AREA_TASK;
 			// 	EngOS_OSALSeizeSemaphore(s_ulTaskLogSemaphoreID, OSAL_SM_WAIT, 0);
 			// }

// 			if(EngLib_IsMsgQFull(&s_stTaskLoggingMsgQCB) == FALSE)
// 			{
// 				/* Check Task Log */
// 				if(EngLog_CheckTaskLog(enLogArea, pubStr, ap) == TRUE)
// 				{
// 					stSendMsgQ.ulMsgID = enLogArea;
// 					stSendMsgQ.ulRParam = (U32)pubStr;
			
// 					if(EngLib_SendMsgQ(&s_stTaskLoggingMsgQCB, &stSendMsgQ) == FALSE)
// 					{
// 						s_fEnableTaskLog = FALSE;
// 						DBG_EMERGENCY("\r\n[%s:Log]===== Warning T-Log MsgQFull_1[%d]:%d,%d =====", ENG_TICK, enLogArea, s_stTaskLoggingMsgQCB.ulMsgQHead, s_stTaskLoggingMsgQCB.ulMsgQTail); 
// 					}
// 				}
// 				else
// 				{					
// 					TQueue *pstDQueue = &s_astArgDQueue[enLogArea];
// 					TQueue *pstSQueue = &s_astArgSQueue[enLogArea];

// 					s_fEnableTaskLog = FALSE;
// 					DBG_EMERGENCY("\r\n[%s:Log]===== Warning T-Log ArgBuffFull[%d][%d,%d/%d,%d] =====", ENG_TICK, enLogArea, pstDQueue->ulHead, pstDQueue->ulTail, pstSQueue->ulHead, pstSQueue->ulTail);
// 				}
// 			}
// 			else
// 			{
// 				s_fEnableTaskLog = FALSE;
// 				DBG_EMERGENCY("\r\n[%s:Log]===== Warning T-Log MsgQFull_2[%d]:%d,%d =====", ENG_TICK, enLogArea, s_stTaskLoggingMsgQCB.ulMsgQHead, s_stTaskLoggingMsgQCB.ulMsgQTail);	
// 			}

// 			if(enLogArea == TASK_LOG_AREA_TASK)
// 			{
// 				EngOS_OSALReleaseSemaphore(s_ulTaskLogSemaphoreID);
// 			}

// 			if(s_fEnableTaskLog == FALSE)
// 			{
// #ifdef FR_TM_LMS_ASSERT
// 				if(stEngLib.pfnLMSTaskLogBufferFullEA != NULL)
// 				{
// 					stEngLib.pfnLMSTaskLogBufferFullEA();
// 				}
// #endif
// 			}
 		}
 	}
}


void EngLog_DynamicDumpLog(U32 ulId, const U8 *pubStr, va_list ap)
{
	TLogParamInfo *pstParamInfo = &stEngLogInfo.pstParamInfoTbl[ulId];

	if(pstParamInfo != NULL)
	{
		U32 ulLevel = pstParamInfo->ulLevel;

		TDumpLog *pstDumpLog = stEngLogInfo.pstDumpLog;
		BOOL fDumpLogSaveEnable = FALSE;
		
#if defined(HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE) && defined(C_HDD_LOG_SAVE_NEW)
		THDDLog *pstHDDLog = stEngLogInfo.pstHDDLog;
		BOOL fHDDLogSaveEnavle = FALSE;
#endif
		BOOL fPrintLogToUartDirectly = FALSE;
		BOOL IsEmergency = FALSE;
		U32	ulEngState = EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_ENGINE_STATE);

		/* Check condition to print log by HDD */
#if defined(HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE) && defined(C_HDD_LOG_SAVE_NEW)
		if((pstHDDLog != NULL)
			&& (pstHDDLog->pstHDDLogData != NULL)
		)
		{
			if(pstHDDLog->pstHDDLogData->ulEmergency == C_ENG_LOG_EMERGENCY_SIGNAL)
			{
				IsEmergency = TRUE;
			}
			
			if((!(pstHDDLog->pstHDDLogData->ulLogStatusFlag & C_ENG_LOG_FLAG_BLOCK_WRITING))
				&& (pstParamInfo->fPrintToHDD == TRUE)
				&& (ulLevel <= pstHDDLog->ulLogLevel)
	//			&& (ulEngState != ENGSM_STS_CHILD_ENGINE_STANDBY)
	//			&& (ulEngState != ENGSM_STS_CHILD_ENGINE_SLEEP)
			)
			{
				fHDDLogSaveEnavle = TRUE;
			}
		}
#endif

		/* Check condition to print log by RAM Dump */
		if((pstDumpLog != NULL)
			&& (pstDumpLog->pstDumpLogData != NULL)
			&& (!(pstDumpLog->pstDumpLogData->ulLogStatusFlag & C_ENG_LOG_FLAG_BLOCK_WRITING))
			&& (pstParamInfo->fPrintToDump == TRUE)
			&& (ulLevel <= pstDumpLog->ulLogLevel)
			&& (IsEmergency == FALSE)
		)
		{
			fDumpLogSaveEnable = TRUE;
		}

		/* Check condition to print log by UART */
		if(pstParamInfo->fPrintToUart == TRUE)
		{
			fPrintLogToUartDirectly = TRUE;
		}
		
		if((fDumpLogSaveEnable == TRUE)
#if defined(HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE) && defined(C_HDD_LOG_SAVE_NEW)
			|| (fHDDLogSaveEnavle == TRUE)
#endif
			|| (fPrintLogToUartDirectly == TRUE)
		)
		{
			U8 aubTempBuff[C_ENG_LOG_1LINE_BUFF_SIZE+1];// = {0};
			S32 slRemainLength = 0;

			slRemainLength = EngLib_SimpleVNSprintf(aubTempBuff, pubStr, ap, C_ENG_LOG_1LINE_BUFF_SIZE);
			
			if(slRemainLength < 0)
			{
				if(fDumpLogSaveEnable == TRUE)
				{
					EngLog_SaveStrToDumpLogBuffer(pstDumpLog->pstDumpLogData, "... LogMsg too long!", strlen("... LogMsg too long!"));
				}
			}
			else
			{
				/* Print log to RAM Dump */
				if(fDumpLogSaveEnable == TRUE)
				{
					EngLog_SaveStrToDumpLogBuffer(pstDumpLog->pstDumpLogData, aubTempBuff, C_ENG_LOG_1LINE_BUFF_SIZE-slRemainLength);
				}

				/* Print log to HDD */
#if defined(HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE) && defined(C_HDD_LOG_SAVE_NEW)		
				if(fHDDLogSaveEnavle == TRUE)
				{
					EngLog_SaveStrToHDDLogBuffer(pstHDDLog->pstHDDLogData, aubTempBuff, C_ENG_LOG_1LINE_BUFF_SIZE-slRemainLength);
				}
#endif		
				/* Print log to Uart directly */
				if(fPrintLogToUartDirectly == TRUE)
				{
					aubTempBuff[C_ENG_LOG_1LINE_BUFF_SIZE-slRemainLength] = '\0';
					ENG_PRINT("%s", aubTempBuff);
				}
			}
		}
	}
}

#if defined(FR_ENGLIB_UART_DEBUG)
BOOL EngLog_UartPrintCreate(TUartPrint** pstUartPrintInfo)
{
	static TUartPrint stUartPrint = {0};

	ASSERT(pstUartPrintInfo);
		
	stUartPrint.ulPrintedLenth = 0;
	stUartPrint.ulPrintDataID = 0;	
	
	*pstUartPrintInfo = &stUartPrint;

	return TRUE;
}
#endif

#if defined(FR_ENGLIB_SWO_DEBUG)
BOOL EngLog_SWOPrintCreate(TSWOPrint** pstSwoPrintInfo)
{
	static TSWOPrint stSwoPrint = {0};

	ASSERT(pstSwoPrintInfo);
		
	stSwoPrint.ulPrintedLenth = 0;
	stSwoPrint.ulPrintDataID = 0;	
	
	*pstSwoPrintInfo = &stSwoPrint;

	/* Initialize Hardware SWO */

	return TRUE;
}
#endif


inline void EngLog_SaveStrToDumpLogBuffer(TDumpLogData *pstDumpLogData, const U8 *pubSrcStr, U32 ulStrLen)
{	
	if(pstDumpLogData != NULL)
	{
		/* Save the string to main buffer */
		if(ulStrLen <= C_ENG_LOG_DATA_SIZE - pstDumpLogData->ulWriteOffset)
		{
			/* When the string size to save is less than remained buffer size */
			EngLib_MemoryCopy(pstDumpLogData->aubLogData + pstDumpLogData->ulWriteOffset, pubSrcStr, ulStrLen);

			pstDumpLogData->ulWriteOffset += ulStrLen;
			
			if(pstDumpLogData->ulWriteOffset >= C_ENG_LOG_DATA_SIZE)
			{
				pstDumpLogData->ulWriteOffset = 0;
			}
		}
		else
		{
			/* When the string size to save is over than remained buffer size */
			U32 ulTmpOffset = 0;

			ulTmpOffset = C_ENG_LOG_DATA_SIZE - pstDumpLogData->ulWriteOffset;
			
			EngLib_MemoryCopy(pstDumpLogData->aubLogData + pstDumpLogData->ulWriteOffset, pubSrcStr, ulTmpOffset);

			pstDumpLogData->ulWriteOffset = ulStrLen - ulTmpOffset;
			
			EngLib_MemoryCopy(pstDumpLogData->aubLogData, pubSrcStr + ulTmpOffset, pstDumpLogData->ulWriteOffset);
			
			pstDumpLogData->ulLogStatusFlag |= C_ENG_LOG_FLAG_BUFFER_FULL;
		}
	}
}


void EngLog_ClearAll(void)
{
	if((stEngLogInfo.pstDumpLog != NULL)
		&& (stEngLogInfo.pstDumpLog->pstDumpLogData != NULL)
	)
	{
		stEngLogInfo.pstDumpLog->pstDumpLogData->ulWriteOffset = 0;
		stEngLogInfo.pstDumpLog->pstDumpLogData->ulLogStatusFlag = 0;
	}

#ifdef FR_ENGLIB_UART_DEBUG	
	if(stEngLogInfo.pstUartPrint != NULL)
	{
		stEngLogInfo.pstUartPrint->ulPrintedLenth = 0;
	}
#endif

#ifdef FR_ENGLIB_SWO_DEBUG	
	if(stEngLogInfo.pstSwoPrint != NULL)
	{
		stEngLogInfo.pstSwoPrint->ulPrintedLenth = 0;
	}
#endif

#ifdef HR_ENGLIB_DEBUG_MESSAGE_MICRO_SD_SAVE
	if(stEngLogInfo.pstMicroSDLog != NULL)
	{
		stEngLogInfo.pstMicroSDLog->ulDumpDataHDDPoint = 0;
	}
#endif
}

#endif	/* FR_ENGLIB_LOG */

