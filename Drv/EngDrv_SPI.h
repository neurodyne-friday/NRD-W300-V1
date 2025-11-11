/**
 * @file        EngDrv_SPI.h
 * @brief       This is type definition file for SPI Driver
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

#ifndef __ENGDRV_SPI_H__
#define __ENGDRV_SPI_H__

#undef EXTERN
#ifdef __ENGDRV_SPI_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"

EXTERN void EngDrv_SPI_Create(void);
EXTERN void EngDrv_SPI_Configuration(void);
EXTERN void EngDrv_SPI_Initialize(TSPI* pstSPI);
EXTERN void EngDrv_SPI_WriteByte(TSPI* pstSPI, U8 ubByte);
EXTERN U8 EngDrv_SPI_ReadByte(TSPI* pstSPI);
EXTERN S32 EngDrv_SPI_WriteRegister(TSPI* pstSPI, U8 ubAddress, U8 ubByte1, U8 ubByte2);
EXTERN S32 EngDrv_SPI_ReadRegister(TSPI* pstSPI, U8 ubAddress);
EXTERN U8 EngDrv_SPI_PortCtrl(TSPI* pstSPI, TSPIPortType enType, U8 ubSetValue);

#endif //__ENGDRV_SPI_H__