/**
 * @file        EngHAL_I2C_STM32F4xx.h
 * @brief       This is type definition file for I2C HAL for STM32F4xx
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


#ifndef __ENGHAL_I2C_STM32F4xx_H__
#define __ENGHAL_I2C_STM32F4xx_H__

#ifdef __ENGHAL_I2C_STM32F4xx_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"

/* === Low-level (chip-specific) API used by EngCM_HalConfig function table === */
EXTERN void EngHAL_I2C_Init_F4xx(THalI2CPorting *pstHalPorting);
EXTERN BOOL EngHAL_I2C_MemRead_F4xx(THalI2CPorting *pstHalPorting, U16 devAddr7b, U16 memAddr, U16 memAddrSize, U8 *pData,U16 len, U32 timeout);
EXTERN BOOL EngHAL_I2C_MemWrite_F4xx(THalI2CPorting *pstHalPorting, U16 devAddr7b, U16 memAddr, U16 memAddrSize,const U8 *pData, U16 len, U32 timeout);
EXTERN BOOL EngHAL_I2C_Read_F4xx(THalI2CPorting *pstHalPorting, U16 devAddr7b, U8 *pData, U16 len, U32 timeout);
EXTERN BOOL EngHAL_I2C_Write_F4xx(THalI2CPorting *pstHalPorting, U16 devAddr7b, const U8 *pData, U16 len, U32 timeout);

/* === Optional helper for AS5600 (commonly used with this project) === */
#define AS5600_I2C_ADDR7          (0x36u)
#define AS5600_REG_RAW_ANGLE_MSB  (0x0Cu)
#define AS5600_REG_RAW_ANGLE_LSB  (0x0Du)
#define AS5600_REG_ANGLE_MSB      (0x0Eu)
#define AS5600_REG_ANGLE_LSB      (0x0Fu)

EXTERN BOOL EngHAL_AS5600_ReadRawAngle_F4xx(THalI2CPorting *pstHalPorting, U16 *pRaw);
EXTERN BOOL EngHAL_AS5600_ReadAngle12_F4xx(THalI2CPorting *pstHalPorting, U16 *pAngle12);

#endif /* __ENGHAL_I2C_STM32F4xx_H__ */
