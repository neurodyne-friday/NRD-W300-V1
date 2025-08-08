/**
 * @file        EngHAL_PWR.h
 * @brief       This is type definition file for POWER HAL
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

#ifndef __ENGHAL_PWR_STM32F4xx_H__
#define __ENGHAL_PWR_STM32F4xx_H__

#undef EXTERN
#ifdef __ENGHAL_PWR_STM32F4xx_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"



EXTERN void EngHAL_PWR_Init_F4xx();
EXTERN void EngHAL_PWR_PVD_Config_F4xx();
EXTERN void EngHAL_PWR_RegisterCallback_F4xx(void (*pfnCallback)(void));

#endif //__ENGHAL_GPIO_H__
