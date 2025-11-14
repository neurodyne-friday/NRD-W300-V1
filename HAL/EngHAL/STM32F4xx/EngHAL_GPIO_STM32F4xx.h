/**
 * @file        EngHAL_GPIO.h
 * @brief       This is type definition file for GPIO HAL
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

#ifndef __ENGHAL_GPIO_H__
#define __ENGHAL_GPIO_H__

#undef EXTERN
#ifdef __ENGHAL_GPIO_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"


EXTERN void EngHAL_GPIO_Config_F4xx(void);
EXTERN void EngHAL_GPIO_Init_F4xx(THalGPIOPorting* pstHalPorting);
EXTERN void EngHAL_GPIO_On_F4xx(THalGPIOPorting* pstHalPorting);
EXTERN void EngHAL_GPIO_Off_F4xx(THalGPIOPorting* pstHalPorting);
EXTERN THalGPIOOnOff EngHAL_GPIO_GetState_F4xx(THalGPIOPorting* pstHalPorting);

#endif //__ENGHAL_GPIO_H__
