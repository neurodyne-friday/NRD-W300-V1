 /**
 * file        EngMH_IF.h
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

#ifndef __ENGMH_IF_H__
#define __ENGMH_IF_H__

#undef EXTERN
#ifdef __ENGMH_IF_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_Macro.h"

EXTERN void EngMH_IF_Initialize(void);
EXTERN void *EngMH_IF_CreateHandler(void);
//EXTERN BOOL EngMH_IF_Main(void);
EXTERN void EngMH_IF_Main(void);

#endif // __ENGMH_IF_H__
