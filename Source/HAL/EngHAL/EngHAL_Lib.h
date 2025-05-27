/**
 * @file		EngHAL_Lib.h
 * @brief		This main code for HAL Component Library.
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
 
#ifndef __ENGHAL_LIB_H__
#define __ENGHAL_LIB_H__

#undef EXTERN
#ifdef __ENGHAL_LIB_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_CommonType.h"
#include "stm32f7xx_hal.h"
#include "EngHAL_Types.h"


EXTERN BOOL EngHAL_LibraryEntry(void);

/* EngChip - CAN Interface */
EXTERN void EngHAL_CAN_Init(U32 ulHalName);
EXTERN void EngHAL_CAN_EnableInterrupt(U32 ulHalName);
EXTERN void EngHAL_CAN_DisableInterrupt(U32 ulHalName);
EXTERN BOOL EngHAL_CAN_IsRxFIFOEmpty(U32 ulHalName);
EXTERN BOOL EngHAL_CAN_IsTxFIFOEmpty(U32 ulHalName);
EXTERN BOOL EngHAL_CAN_IsTxFIFOFull(U32 ulHalName);
EXTERN void EngHAL_CAN_Transmit(U32 ulHalName, U8 pubData[], U8 ubLength);
EXTERN void EngHAL_CAN_Receive(U32 ulHalName);
EXTERN void EngHAL_CAN_RxFIFOMsgPendingCallback(U32 ulHalName);
EXTERN void EngHAL_CAN_PutByte(U32 ulHalName, U8 ubData);
EXTERN void EngHAL_CAN_SendBytes(U32 ulHalName);
EXTERN U8 EngHAL_CAN_GetByte(U32 ulHalName);

/* EngChip - UART Interface */
EXTERN void EngHAL_UART_Init(U32 ulHalName);
EXTERN void EngHAL_UART_Transmit(U32 ulHalName, U8 pubData[], U16 uwLength);
EXTERN void EngHAL_UART_Receive(U32 ulHalName);

/* EngChip - Ethernet Interface */
EXTERN BOOL EngHAL_ETH_Init(U32 ulHalName);
EXTERN void EngHAL_ETH_Connect_Entry(U32 ulHalName);
EXTERN void EngHAL_ETH_Connect_Activity(U32 ulHalName);
EXTERN void EngHAL_ETH_Connect_Exit(U32 ulHalName);
EXTERN void EngHAL_ETH_Transmit(U32 ulHalName, U8 pubData[], U16 uwLength);

/* EngChip - ADC Interface */

/* EngChip - RTC Interface */
EXTERN void EngHAL_RTC_Init(void);
EXTERN void EngHAL_RTC_GetDateTime(U8* pubDateTime);

/* EngChip - TIM Interface */
EXTERN void EngHAL_TIM1_Init(void);

/* EngChip - USB_OTG Interface */
EXTERN void EngHAL_USB_OTG_FS_PCD_Init(void);


/* EngChip - Delay Timer Interface */
EXTERN void EngHAL_OS_Delay(uint32_t ticks);


/**
*	Common Function
*/

EXTERN THalCANPorting* EngHAL_FindHalCAN(U32 ulHalName);
EXTERN THalUARTPorting* EngHAL_FindHalUART(U32 ulHalName);

#endif //__ENGHAL_LIB_H__