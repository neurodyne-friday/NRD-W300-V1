/**
 * @file        EngLog_IF.c
 * @brief       This is main code for Engine Log Library Component.
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
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		14/04/2009(D/M/Y)
 * @version		V0.1
 */

#define	__ENGLOG_IF_C__

#include "Eng_CommonType.h"
#include "EngLog_Types.h"
#include "EngLog_Lib.h"
#include "EngLog_IF.h"


/* Initialize the Engine Log Library */
void EngLog_IF_LibraryEntry(TInitialStepType enInitStep)
{
#ifdef FR_ENGLIB_LOG	
	EngLog_LibraryEntry(enInitStep);
#endif
}


void EngLog_IF_DumpPrintToUart(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_UART, pubStr, ap);
#else
	EngLog_DynamicDumpLog(DBG_ID_UART, pubStr, ap);
#endif

	va_end(ap);
#endif
}

void EngLog_IF_DumpPrintToSWO(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_SWO, pubStr, ap);
#else
	EngLog_DynamicDumpLog(DBG_ID_SWO, pubStr, ap);
#endif

	va_end(ap);
#endif
}


void EngLog_IF_DumpPrintEmergency(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

	/* Emergency Log is using only DynamicDumpLog */	
	EngLog_DynamicDumpLog(DBG_ID_EMERGENCY, pubStr, ap);

	va_end(ap);
#endif
}

void EngLog_IF_DumpPrintEngIFSvc(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_ENGIFSVC, pubStr, ap);
#else
	EngLog_DynamicDumpLog(DBG_ID_ENGIFSVC, pubStr, ap);
#endif

	va_end(ap);
#endif
}

void EngLog_IF_DumpPrintEngTimerSvc(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_ENGTMSVC, pubStr, ap);
#else	
	EngLog_DynamicDumpLog(DBG_ID_ENGTMSVC, pubStr, ap);
#endif

	va_end(ap);
#endif
}

void EngLog_IF_DumpPrintEngSM(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_ENGSM, pubStr, ap);
#else	
	EngLog_DynamicDumpLog(DBG_ID_ENGSM, pubStr, ap);
#endif

	va_end(ap);
#endif
}

void EngLog_IF_DumpPrintEngTM(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);
	
#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_ENGTM, pubStr, ap);
#else
	EngLog_DynamicDumpLog(DBG_ID_ENGTM, pubStr, ap);
#endif

	va_end(ap);
#endif
}

void EngLog_IF_DumpPrintEngFOC(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_ENGFOC, pubStr, ap);
#else
	EngLog_DynamicDumpLog(DBG_ID_ENGFOC, pubStr, ap);
#endif

	va_end(ap);
#endif
}


void EngLog_IF_DumpPrintEngEH(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_ENGEH, pubStr, ap);
#else
	EngLog_DynamicDumpLog(DBG_ID_ENGEH, pubStr, ap);
#endif

	va_end(ap);
#endif
}

void EngLog_IF_DumpPrintEngLib(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_ENGLIB, pubStr, ap);
#else
	EngLog_DynamicDumpLog(DBG_ID_ENGLIB, pubStr, ap);
#endif

	va_end(ap);
#endif
}

void EngLog_IF_DumpPrintState(const U8 *pubStr, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list ap;
	va_start(ap, pubStr);

#ifdef FR_ENGLIB_TASK_LOGGING
	EngLog_DynamicTaskLog(DBG_ID_STATE, pubStr, ap);
#else
	EngLog_DynamicDumpLog(DBG_ID_STATE, pubStr, ap);
#endif

	va_end(ap);
#endif
}



void EngLog_IF_PrintToUart(const U8 *format, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list args;
	TUART* pstUART = EngDrv_IF_GetUART(UART_NAME_MAIN);

	//EngLog_DynamicTaskLog(DBG_ID_UART, pubStr, ap);

	U8 aubTempBuff[C_ENG_LOG_1LINE_BUFF_SIZE] = {0};

	va_start(args, format);
	vsnprintf(aubTempBuff, sizeof(aubTempBuff), format, args);
	va_end(args);

	pstUART->pfnSendData(pstUART, aubTempBuff);
#endif
}

void EngLog_IF_PrintToSWO(const U8 *format, ...)
{
#ifdef FR_ENGLIB_LOG
	va_list args;
	//TUART* pstUART = EngDrv_IF_GetUART(UART_NAME_STLINK_DEBUG);

	//EngLog_DynamicTaskLog(DBG_ID_UART, pubStr, ap);

	U8 aubTempBuff[C_ENG_LOG_1LINE_BUFF_SIZE] = {0};

	va_start(args, format);
	vsnprintf(aubTempBuff, sizeof(aubTempBuff), format, args);
	va_end(args);

	// if(pstUART && pstUART->pfnSendData != NULL)
	// {
	// 	pstUART->pfnSendData(pstUART, aubTempBuff);
	// }

	// Send the string to SWO (ITM)
	for(int i = 0; i < sizeof(aubTempBuff); i++)
	{
		char ch = aubTempBuff[i];

		if ((ITM->TCR & ITM_TCR_ITMENA_Msk)==0 || (ITM->TER & 1U)==0) 
			return;
		
		while (ITM->PORT[0].u32 == 0) 
		{ 
			__NOP(); 
		}
		
		ITM->PORT[0].u8 = (uint8_t)ch;
	}
#endif
}