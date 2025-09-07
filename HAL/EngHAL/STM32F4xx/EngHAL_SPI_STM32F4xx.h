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



EXTERN THalStatusType EngHAL_SPI_Init_F4xx(THalSPIPorting *pstHalPorting);
EXTERN void EngHAL_SPI_Write_F4xx(THalSPIPorting *pstHalPorting, uint8_t *tx, uint16_t len);
EXTERN void EngHAL_SPI_WriteRead_F4xx(THalSPIPorting *pstHalPorting, uint8_t *tx, uint8_t *rx, uint16_t len);

/* =======================  BEGIN: MA702 support additions (Temporary)  ======================= */
#define MA702_FRAME_BITS        (16u)
#define MA702_ANGLE_BITS        (12u)
#define MA702_ANGLE_MASK_16     ((uint16_t)0xFFF0u)
#define MA702_ANGLE_SHIFT       (4u)

#define MA702_CMD_READ_REG(a5)  ( (uint16_t)((0x2u<<13) | (((uint16_t)(a5)&0x1Fu)<<8)) )
#define MA702_CMD_WRITE_REG(a5,v8) ( (uint16_t)((0x4u<<13) | (((uint16_t)(a5)&0x1Fu)<<8) | ((uint16_t)(v8)&0xFFu)) )

#define MA702_TIDLE_ANGLE_US    (1u)   /* 150ns→1us로 상향 */
#define MA702_TIDLE_REG_US      (1u)   /* 750ns→1us로 상향 */
#define MA702_TNVM_MS           (20u)  /* NVM commit */

EXTERN HAL_StatusTypeDef EngHAL_SPI_MA702_ReadAngle12_F4xx(THalSPIPorting *pstHalPorting, uint16_t *puwAngle12); /* 12-bit raw 각도 읽기 */
EXTERN float EngHAL_SPI_MA702_ReadAngleDeg_F4xx(THalSPIPorting *pstHalPorting); /* 편의 함수 */
EXTERN float EngHAL_SPI_MA702_ReadAngleRa_F4xxd(THalSPIPorting *pstHalPorting);
EXTERN HAL_StatusTypeDef EngHAL_SPI_MA702_ReadReg_F4xx(THalSPIPorting *pstHalPorting, uint8_t ubAddr5, uint8_t *pubVal); /* 레지스터 접근 */
EXTERN HAL_StatusTypeDef EngHAL_SPI_MA702_WriteReg_F4xx(THalSPIPorting *pstHalPorting, uint8_t ubAddr5, uint8_t ubVal, uint8_t *pubEcho);
/* =======================  END: MA702 support additions (Temporary)  ========================= */

#endif //__ENGHAL_SPI_STM32F4xx_H__
