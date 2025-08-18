/**
 * @file        EngTimerSvc_IF.h
 * @brief       This is header file for EngTimerSvc_IF.c
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
 * @date		07/11/2024(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGTIMERSVC_IF_H__
#define __ENGTIMERSVC_IF_H__

#include "Eng_Macro.h"

#undef EXTERN
#ifdef __ENGTIMERSVC_IF_C__
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN BOOL EngTimerSvc_IF_Initialize(void);
EXTERN void EngTimerSvc_IF_Main(void);
EXTERN U32 EngTimerSvc_IF_Suspend(U32 ulTaskIndex);
EXTERN U32 EngTimerSvc_IF_Resume(U32 ulTaskIndex);


#endif /* __ENGTIMERSVC_IF_H__ */

