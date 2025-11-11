/**
 * @file        EngDrv_Flash.c
 * @brief       This is type definition file for Flash Driver
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

#define	__ENGDRV_FLASH_C__

#include "EngDrv_Flash.h"
#include "EngDrv_IF.h"
#include "EngCM_DriverConfig.h"



void EngDrv_Flash_Create(void)
{

}

void EngDrv_Flash_Configuration(void)
{

}

void EngDrv_Flash_Initialize(void)
{
}

U8 EngDrv_Flash_Erase(void)
{
    U8 ubRet = FALSE;

	return ubRet;
}

U8 EngDrv_Flash_WriteBlock(U32 ulAddress, U8* pubData, U16 uwSize)
{
    //ulAddress = ulAddress * DEVFLASH_BLOCK_SIZE;	
	return EngDrv_Flash_WriteWord(ulAddress, (U32*)pubData, uwSize);
}

U8 EngDrv_Flash_WriteWord(U32 ulDest, U32 *pulSrc, U16 uwSize)
{
	U8 ubRet = FALSE;
	U32 ulBaseAddress = EngDrv_Flash_GetBaseAddress();
	

	return ubRet;
}

U8 EngDrv_Flash_ReadByte(U32 ulAdddress)
{
	U32 ulBaseAddress = EngDrv_Flash_GetBaseAddress();
	U8 ubReadByte = 0;

	if(ulBaseAddress)
	{
		ubReadByte = *(( volatile U8 *)(ulBaseAddress + ulAdddress));	
	}

	return ubReadByte;
}

U32 EngDrv_Flash_GetBaseAddress(void)
{
	U32 ulBaseAddress = 0;

	ulBaseAddress = FLASH_ADDRESS_ML;

	return ulBaseAddress;
}

U8 EngDrv_Flash_EraseSector(U16 sector)
{
	U8 retVal = FALSE;

	return retVal;
}

U8 EngDrv_Flash_WriteHalfWord(U32 address, U16 data)
{
	U8 retVal = FALSE;

	return retVal;
}

