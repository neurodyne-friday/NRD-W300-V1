/**
 * @file        EngHAL_TIM.h
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

#ifndef __ENGHAL_TIM_H__
#define __ENGHAL_TIM_H__

#undef EXTERN
#ifdef __ENGHAL_TIM_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"



EXTERN void EngHAL_TIM_Init_F4xx();

#endif //__ENGHAL_GPIO_H__
