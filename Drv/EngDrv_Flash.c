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


OS_MUTEX osmFlashMutex; // temp


void EngDrv_Flash_Create(void)
{

}

void EngDrv_Flash_Configuration(void)
{

}

void EngDrv_Flash_Initialize(void)
{
	OS_ERR err;
	OSMutexCreate(&osmFlashMutex, "Flash Mutex", &err);
}

u8 EngDrv_Flash_Erase(void)
{
    u8 ubRet = FALSE;
	FLASH_Status enStatus = FLASH_COMPLETE;

	OS_ERR err;
	CPU_TS ts;

	OSMutexPend(&osmFlashMutex, 0,  OS_OPT_PEND_BLOCKING, &ts, &err);
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	enStatus = FLASH_EraseSector(FLASH_SECTOR_ML, VoltageRange_3);

	FLASH_Lock();
	OSMutexPost(&osmFlashMutex, OS_OPT_POST_NONE, &err);

	if(enStatus == FLASH_COMPLETE)
	{
		ubRet = TRUE;
	}
	else
	{
		ubRet = FALSE;
	}

	return ubRet;
}

u8 EngDrv_Flash_WriteBlock(u32 ulAddress, u8* pubData, u16 uwSize)
{
    ulAddress = ulAddress * DEVFLASH_BLOCK_SIZE;	
	return EngDrv_Flash_WriteWord(ulAddress, (u32*)pubData, uwSize);
}

u8 EngDrv_Flash_WriteWord(u32 ulDest, u32 *pulSrc, u16 uwSize)
{
	u8 ubRet = FALSE;
	u32 ulBaseAddress = EngDrv_Flash_GetBaseAddress();
	FLASH_Status enStatus = FLASH_COMPLETE;

	OS_ERR err;
	CPU_TS ts;

	OSMutexPend(&osmFlashMutex, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
	FLASH_Unlock();
	FLASH_ClearFlag( FLASH_FLAG_EOP |  FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	for(u16 uwIndex = 0; uwIndex < uwSize / 4; uwIndex++ )
	{
		enStatus = FLASH_ProgramWord(ulBaseAddress + ulDest + uwIndex * 4, pulSrc[uwIndex]);

		if(enStatus != FLASH_COMPLETE)
		{
			break;
		}
	}

	FLASH_Lock();
	OSMutexPost(&osmFlashMutex, OS_OPT_POST_NONE, &err);

	if(enStatus == FLASH_COMPLETE)
	{
		ubRet = TRUE;
	}
	else
	{
		ubRet = FALSE;
	}

	return ubRet;
}

u8 EngDrv_Flash_ReadByte(u32 ulAdddress)
{
	u32 ulBaseAddress = EngDrv_Flash_GetBaseAddress();
	u8 ubReadByte = 0;

	if(ulBaseAddress)
	{
		ubReadByte = *(( volatile u8 *)(ulBaseAddress + ulAdddress));	
	}

	return ubReadByte;
}

u32 EngDrv_Flash_GetBaseAddress(void)
{
	u32 ulBaseAddress = 0;

	ulBaseAddress = FLASH_ADDRESS_ML;

	return ulBaseAddress;
}

u8 EngDrv_Flash_EraseSector(u16 sector)
{
	u8 retVal = FALSE;
	FLASH_Status status = FLASH_COMPLETE;

	OS_ERR err;
	CPU_TS ts;

	OSMutexPend(&osmFlashMutex,	0, OS_OPT_PEND_BLOCKING, &ts, &err);
	
	FLASH_Unlock();

	FLASH_ClearFlag(FLASH_FLAG_EOP |  FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	status = FLASH_EraseSector(sector, VoltageRange_3);

	FLASH_Lock();

	OSMutexPost(&osmFlashMutex, OS_OPT_POST_NONE, &err);

	if(status == FLASH_COMPLETE)
	{
		retVal = TRUE;
	}
	else
	{
		retVal = FALSE;
	}

	return retVal;
}

u8 EngDrv_Flash_WriteHalfWord(u32 address, u16 data)
{
	u8 retVal = FALSE;
	FLASH_Status status = FLASH_COMPLETE;

	OS_ERR err;
	CPU_TS ts;

	OSMutexPend(&osmFlashMutex, 0, OS_OPT_PEND_BLOCKING, &ts, &err);

	FLASH_Unlock();

	FLASH_ClearFlag(FLASH_FLAG_EOP |  FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
	
	FLASH_ProgramHalfWord(address, data);

	FLASH_Lock();
	
	OSMutexPost(&osmFlashMutex, OS_OPT_POST_NONE, &err);

	if(status == FLASH_COMPLETE)
	{
		retVal = TRUE;
	}
	else
	{
		retVal = FALSE;
	}

	return retVal;
}

