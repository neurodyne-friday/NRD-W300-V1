/**
 * @file        EngDrv_UART.h
 * @brief       This is type definition file for Engine OS Interface Component.
 *
 * <b> Copyright 2024 by Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeognseob Kim
 * @imp			Jeognseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		03/11/2008(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGDRV_UART_H__
#define __ENGDRV_UART_H__

#undef EXTERN
#ifdef __ENGDRV_UART_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_CommonType.h"


EXTERN void EngDrv_UART_Create(void);
EXTERN void EngDrv_UART_Initialize(TUART *pstUART);

EXTERN void EngDrv_UART_SendData(TUART *pstUART, U8 pubData[]);


#endif
