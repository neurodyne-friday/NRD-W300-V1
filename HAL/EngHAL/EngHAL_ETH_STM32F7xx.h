/**
 * @file		EngHAL_ETH_STM32F7xx.h
 * @brief		This main code for HAL Ethernet Component Library.
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

#ifndef __ENGHAL_ETH_STM32F7XX_H__
#define __ENGHAL_ETH_STM32F7XX_H__

#undef EXTERN
#ifdef __ENGHAL_ETH_STM32F7XX_C__
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN BOOL EngHAL_ETH_Init_F7xx(THalETHPorting *pstHalPorting);
EXTERN void EngHAL_ETH_Connect_Entry_F7xx(THalETHPorting *pstHalPorting);
EXTERN void EngHAL_ETH_Connect_Activity_F7xx(THalETHPorting *pstHalPorting);
EXTERN void EngHAL_ETH_Connect_Exit_F7xx(THalETHPorting *pstHalPorting);
EXTERN void EngHAL_ETH_Transmit_F7xx(THalETHPorting *pstHalPorting, U8* pubData, U16 uwLength);

/* Internal functions */
EXTERN void EngHAL_ETH_LWIP_Init_F7xx(THalETHPorting *pstHalPorting);
EXTERN void EngHAL_ETH_SetIP_F7xx(THalETHPorting *pstHalPorting);

#endif //__ENGHAL_ETH_STM32F7XX_H__