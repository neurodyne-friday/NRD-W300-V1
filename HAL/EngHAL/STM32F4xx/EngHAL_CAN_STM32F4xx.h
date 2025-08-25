/**
 * @file		EngHAL_CAN_STM32F7xx.h
 * @brief		This main code for HAL CAN Component Library.
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

#ifndef __ENGHAL_CAN_H__
#define __ENGHAL_CAN_H__

#undef EXTERN
#ifdef __ENGHAL_CAN_C__
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN BOOL EngHAL_CAN_Init_F4xx(THalCANPorting *pstHalPorting);
EXTERN void EngHAL_CAN_EnableInterrupt_F4xx(THalCANPorting *pstHalPorting);
EXTERN void EngHAL_CAN_DisableInterrupt_F4xx(THalCANPorting *pstHalPorting);
EXTERN void EngHAL_CAN_RegisterCallback_F4xx(U32 ulEventId, void (*pfnCallback)(void));
EXTERN void EngHAL_CAN_Transmit_F4xx(THalCANPorting *pstHalPorting, U8 pubData[], U8 ubLength);
EXTERN void EngHAL_CAN_Receive_F4xx(THalCANPorting *pstHalPorting);
EXTERN BOOL EngHAL_CAN_IsRxFIFOEmpty_F4xx(THalCANPorting *pstHalPorting);
EXTERN BOOL EngHAL_CAN_IsTxFIFOEmpty_F4xx(THalCANPorting *pstHalPorting);
EXTERN U32 EngHAL_CAN_GetRxFifoFillLevel_STM32F4xx(THalCANPorting *pstHalPorting);


#endif //__ENGHAL_CAN_H__