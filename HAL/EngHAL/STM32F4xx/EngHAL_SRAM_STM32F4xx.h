/**
 * @file        EngHAL_SRAM_STM32F4xx.h
 * @brief       This is type definition file for SRAM HAL
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

#ifndef __ENGHAL_SRAM_STM32F4xx_H__
#define __ENGHAL_SRAM_STM32F4xx_H__

#undef EXTERN
#ifdef __ENGHAL_SRAM_STM32F4xx_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"


EXTERN void EngHAL_SRAM_Init_F4xx();
EXTERN BOOL EngHAL_SRAM_Save_F4xx(const void *data, uint32_t len);
EXTERN BOOL EngHAL_SRAM_Load_F4xx(void *out, uint32_t bufsize, uint32_t *out_len, uint32_t *out_seq);
EXTERN BOOL EngHAL_SRAM_IsValid_F4xx(void);

#endif //__ENGHAL_GPIO_H__
