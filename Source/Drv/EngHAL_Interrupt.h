/**
 * @file        EngHAL_Interrupt.h
 * @brief       This is type definition file for Interrupt HAL
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
 * @dept		Embedded Developement Team
 * @date		19/02/2024(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGHAL_INTERRUPT_H__
#define __ENGHAL_INTERRUPT_H__

#undef EXTERN
#ifdef __ENGHAL_INTERRUPT_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"

//EXTERN TISR* EngHAL_Interrupt_GetPtr(void);
//EXTERN void EngHAL_Interupt_Create(void);
//EXTERN void EngHAL_Interrupt_Add(TInterruptType eType, U8 ubIndex, void* pfnFunc);
//EXTERN void* EngHAL_Interrupt_Get(TInterruptType eType, U8 ubIndex);
EXTERN void EngHAL_Interrupt_TimerInt(U8 ubTimIntNum);
EXTERN void EngHAL_Interrupt_External(U8 ubExtIntNum);
EXTERN void EngHAL_Interrupt_UART(U8 ubUartIntNum);

#endif //__ENGHAL_INTERRUPT_H__