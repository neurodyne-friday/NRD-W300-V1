/**
 * @file        EngLog_Lib.h
 * @brief       This main code for Engine Log Component.
 *
 * <b> Copyright 2024 Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Neurodyne.
 *
 * @author		Jeongseob Kim
 * @imp			
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		05/11/2009(D/M/Y)
 * @version		V0.1
 */
 
#ifndef __ENGLOG_LIB_H__
#define __ENGLOG_LIB_H__

#include "EngLog_Types.h"

#undef EXTERN
#ifdef __ENGLOG_LIB_C__
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN BOOL EngLog_InitTaskLogging(void);
EXTERN void EngLog_LibraryEntry(TInitialStepType enInitStep);
EXTERN BOOL EngLog_InsertDataArg(TTaskLogArea enLogArea, U32 ulData);
EXTERN void* EngLog_DumpLogDataMemoryAlloc(void);
EXTERN BOOL EngLog_DumpLogCreate(TDumpLog** pstEngLogInfo);

EXTERN void EngLog_DynamicTaskLog(U32 ulId, const U8 *pubStr, va_list ap);
EXTERN void EngLog_DynamicDumpLog(U32 ulId, const U8 *pubStr, va_list ap);
EXTERN void EngLog_SaveStrToDumpLogBuffer(TDumpLogData *pstDumpLogData, const U8 *pubSrcStr, U32 ulStrLen);

#if defined(FR_ENGLIB_UART_DEBUG)
EXTERN BOOL EngLog_UartPrintCreate(TUartPrint** pstUartPrintInfo);
#endif

#if defined(FR_ENGLIB_SWO_DEBUG)
EXTERN BOOL EngLog_SWOPrintCreate(TSWOPrint** pstSwoPrintInfo);
#endif


EXTERN void EngLog_ClearAll(void);

#endif /* __ENGTM_FRAME_JIG_H__ */

