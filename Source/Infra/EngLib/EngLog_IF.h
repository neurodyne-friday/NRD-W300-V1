/**
 * @file        EngLog_IF.h
 * @brief       This is header file for Engine Log Library Component.
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
 * @date		08/05/2009(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGLOG_IF_H__
#define __ENGLOG_IF_H__

#undef EXTERN
#ifdef __ENGLOG_IF_C__
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void EngLog_IF_LibraryEntry(TInitialStepType enInitStep);
EXTERN void EngLog_IF_DumpPrintToUart(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintEmergency(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintEngIFSvc(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintEngTimerSvc(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintEngSM(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintEngTM(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintEngMH(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintEngEH(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintEngLib(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintEngVM(const U8 *pubStr, ...);
EXTERN void EngLog_IF_DumpPrintState(const U8 *pubStr, ...);

EXTERN void EngLog_IF_PrintToUart(const U8 *format, ...);

#endif /* __EngLog_IF_H__ */
