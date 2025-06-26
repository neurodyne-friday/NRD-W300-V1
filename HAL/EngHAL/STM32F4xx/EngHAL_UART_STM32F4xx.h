/**
 * @file		EngHAL_UART_STM32F4xx.h
 * @brief		This main code for HAL UART Component Library.
 *
 * <b> Copyright 2024 by Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp 		
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		07/11/2008(D/M/Y)
 * @version 	V0.1
 */

#ifndef __ENGHAL_UART_H__
#define __ENGHAL_UART_H__

#undef EXTERN
#ifdef __ENGHAL_UART_C__
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN BOOL EngHAL_UART_Init_F4xx(THalUARTPorting *pstHalPorting);
EXTERN void EngHAL_UART_EnableInterrupt_F4xx(THalUARTPorting *pstHalPorting);
EXTERN void EngHAL_UART_DisableInterrupt_F4xx(THalUARTPorting *pstHalPorting);
EXTERN void EngHAL_UART_Transmit_F4xx(THalUARTPorting *pstHalPorting, U8 pubData[], U16 uwLength);
EXTERN void EngHAL_UART_Receive_F4xx(THalUARTPorting *pstHalPorting);
EXTERN void EngHAL_UART_SendByte_F4xx(THalUARTPorting *pstHalPorting, U8 ubData);
EXTERN U8 EngHAL_UART_GetByte_F4xx(THalUARTPorting *pstHalPorting);
EXTERN BOOL EngHAL_UART_IsRxFIFOEmpty_F4xx(THalUARTPorting *pstHalPorting);
EXTERN BOOL EngHAL_UART_IsTxFIFOEmpty_F4xx(THalUARTPorting *pstHalPorting);


#endif //__ENGHAL_UART_STM32F7XX_H__