 /**
 * @file        EngTimerSvc_Main.h
 * @brief       This is header file for EngTimerSvc_Main.c
 *
 * <b> Copyright 2024 by Neurodyne, Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne, Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		03/11/2024(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGTIMERSVC__MAIN_H__
#define __ENGTIMERSVC__MAIN_H__

#include "Eng_Macro.h"

#undef EXTERN

#ifdef __ENGTIMERSVC_MAIN_C__
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN BOOL EngTimerSvc_Initialize(void);
EXTERN void EngTimerSvc_Execute(void);
EXTERN U32	EngTimerSvc_Add(U32 ulID, void (*pfnTask)(void), const U32 ulDelay, const U32 ulPeriod);
EXTERN U32 EngTimerSvc_Suspend(const U32 ulTaskIndex);
EXTERN U32 EngTimerSvc_Resume(const U32 ulTaskIndex);
EXTERN TEngTimerRetValue EngTimerSvc_Delete(const U32 ulTaskIndex);
EXTERN U32	EngTimerSvc_Compose(void);
EXTERN void EngTimerSvc_CountBySysTick(void);


#endif /* __ENGTIMERSVC__MAIN_H__ */