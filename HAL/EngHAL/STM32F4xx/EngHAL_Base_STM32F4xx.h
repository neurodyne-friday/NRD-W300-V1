/**
 * @file        EngHAL_Base_STM32F4xx.h
 * @brief       This is type definition file for Base HAL Interface of STM32F4xx series
 *
 * <b> Copyright 2024 by Neurodyne, Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne, Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Neurodyne.
 *
 * @author		Jeongseob Kim
 * @imp			Jeongseob Kim
 * @dept		Embedded Developement Team
 * @date		19/02/2025(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGHAL_BASE_STM32F4xx_H__
#define __ENGHAL_BASE_STM32F4xx_H__

#undef EXTERN
#ifdef __ENGHAL_BASE_STM32F4xx_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"
#include "stm32f4xx_hal.h"


EXTERN void EngHAL_Base_TIM1_Probe_State(const char* tag);
EXTERN void EngHAL_Base_TIM1_Config_TRGO_Center(void);

EXTERN GPIO_TypeDef* EngHAL_Base_GetGPIOPort(U8 ubPort);
EXTERN U16 EngHAL_Base_GetGPIOPin(U8 ubPin);

#endif //__ENGHAL_BASE_STM32F4xx_H__
