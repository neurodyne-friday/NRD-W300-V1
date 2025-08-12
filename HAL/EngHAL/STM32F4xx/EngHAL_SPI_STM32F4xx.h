/**
 * @file        EngHAL_SPI_STM32F4xx.h
 * @brief       This is type definition file for SPI HAL for STM32F4xx
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

#ifndef __ENGHAL_SPI_STM32F4xx_H__
#define __ENGHAL_SPI_STM32F4xx_H__

#undef EXTERN
#ifdef __ENGHAL_SPI_STM32F4xx_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"



EXTERN void EngHAL_SPI_Init_F4xx(THalSPIPorting *pstHalPorting);
EXTERN void EngHAL_SPI_Write_F4xx(THalSPIPorting *pstHalPorting, uint8_t *tx, uint16_t len);
EXTERN void EngHAL_SPI_WriteRead_F4xx(THalSPIPorting *pstHalPorting, uint8_t *tx, uint8_t *rx, uint16_t len);

#endif //__ENGHAL_SPI_STM32F4xx_H__
