 /**
 * file        EngMH_Main.h
 * brief       This is type definition file for common
 *
 * <b> Copyright 2024 by Neurodyne, Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne, Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * author		Jeongseob Kim
 * imp			Jeongseob Kim
 * dept		    Embedded Developement Team
 * date		    19/02/2024(D/M/Y)
 * version		V0.1
 */

#ifndef __ENGMH_MAIN_H__
#define __ENGMH_MAIN_H__

#undef EXTERN
#ifdef __ENGMH_MAIN_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_Macro.h"
#include "EngMH_Types.h"

EXTERN void *EngMH_CreateHandler(void);
EXTERN void EngMH_Initialize(void);
EXTERN void EngMH_Constructor(TEngMotionHnd* pstMotionHandler);

EXTERN void EngMH_FollowDeviceStatus(U32 ulStatusID, U32 ulOldValue, U32 ulNewValue);
EXTERN BOOL EngMH_Main(void);

// temporary 
EXTERN void EngMH_Joint_Init(TJoint* pstJoint);
EXTERN void EngMH_Joint_Control(TJoint* pstJoint);


#endif // __ENGMH_MAIN_H__
