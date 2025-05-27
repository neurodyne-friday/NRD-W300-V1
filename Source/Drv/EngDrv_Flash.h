/**
 * @file        EngDrv_EEPROM.h
 * @brief       This is type definition file for EEPROM Driver
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

#ifndef __ENGDRV_FLASH_H__
#define __ENGDRV_FLASH_H__

#undef EXTERN
#ifdef __ENGDRV_FLASH_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"

EXTERN void EngDrv_Flash_Create(void);
EXTERN void EngDrv_Flash_Configuration(void);
EXTERN void EngDrv_Flash_Initialize(void);

EXTERN U8 EngDrv_Flash_Erase(void);
EXTERN U8 EngDrv_Flash_WriteBlock(U32 ulAddress, U8* pubData, U16 uwSize);
EXTERN U8 EngDrv_Flash_WriteWord(U32 ulDest, U32 *pulSrc, U16 uwSize);
EXTERN U8 EngDrv_Flash_ReadByte(U32 ulAdddress);
EXTERN U32 EngDrv_Flash_GetBaseAddress(void);
EXTERN U8 EngDrv_Flash_EraseSector(U16 sector);
EXTERN U8 EngDrv_Flash_WriteHalfWord(U32 address, U16 data);

#endif //__ENGDRV_FLASH_H__
