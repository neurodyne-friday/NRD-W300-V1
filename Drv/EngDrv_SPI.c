/**
 * @file        EngDrv_SPI.c
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

#define	__ENGDRV_SPI_C__

#include "EngDrv_SPI.h"
#include "EngCM_DriverConfig.h"

void EngDrv_SPI_Create(void)
{
 	TSPI* pstInstance = NULL;
    U8 ubCount = sizeof(s_astDeviceSPITbl) / sizeof(TSPI);

    for(U8 ubIndex = 0; ubIndex < ubCount; ubIndex++)
    {
        pstInstance = &s_astDeviceSPITbl[ubIndex];

        pstInstance->pfnInitialize = EngDrv_SPI_Initialize;
    } 	
}

void EngDrv_SPI_Configuration(void)
{
}

void EngDrv_SPI_Initialize(TSPI* pstSPI)
{
}

S32 EngDrv_SPI_WriteRegister(TSPI* pstSPI, U8 ubAddress, U8 ubByte1, U8 ubByte2)
{
	if(!pstSPI)
		return 0;

	return 0;
}

S32 EngDrv_SPI_ReadRegister(TSPI* pstSPI, U8 ubAddress)
{
	U16 uwData = 0;

	if(!pstSPI)
		return 0;

	return uwData;
}

void EngDrv_SPI_WriteByte(TSPI* pstSPI, U8 ubByte)
{
	U8 ubIndex;

	if(!pstSPI)
		return;

	// SCLK Low
	EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_SCLK, FALSE);
	DelayNOP(5*3);
	
	for(ubIndex = 0; ubIndex < 8; ubIndex++ )
	{
		if(ubByte & (0x80 >> ubIndex))
		{
			// SDATI High
			EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_DI, TRUE);
		}
		else
		{
			// SDATI Low
			EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_DI, FALSE);
		}
		DelayNOP(5*3);

		// SCLK High
		EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_SCLK, TRUE);
		DelayNOP(5*3);
		
		// SCLK Low
		EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_SCLK, FALSE);
		DelayNOP(5*3);
	}
}

U8 EngDrv_SPI_ReadByte(TSPI* pstSPI)
{
	U8 ubIndex;
	U8 ubData = 0;

	if(!pstSPI)
		return 0;

	// SCLK Low
	EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_SCLK, FALSE);
	DelayNOP(5*3);
	
	for(ubIndex = 0; ubIndex < 8; ubIndex++)
	{
		// SCLK High
		EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_SCLK, TRUE);
		DelayNOP(5*3);

		// Read SDATO
		if(EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_DO, FALSE))
		{
			ubData |= (0x80 >> ubIndex);
		}
		else
		{
			ubData &= ~(0x80 >> ubIndex);
		}
		DelayNOP(5*3);
		
		// SCLK Low
		EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_SCLK, FALSE);
		DelayNOP(5*3);
	}

	return ubData;
}

U8 EngDrv_SPI_PortCtrl(TSPI* pstSPI, TSPIPortType ePortType, U8 ubSetValue)
{
	U8 ubRet = 0;

	if(pstSPI != NULL)
	{
		switch(ePortType)
		{
			case SPI_PORT_TYPE_CS:
				if(ubSetValue == TRUE)
					GPIO_SetBits(pstSPI->ulHalBaseCS, pstSPI->ulHalPinCS);
					//GPIO_SetBits(GPIOH, GPIO_Pin_8);
				else 
					GPIO_ResetBits(pstSPI->ulHalBaseCS, pstSPI->ulHalPinCS);
					//GPIO_ResetBits(GPIOH, GPIO_Pin_8);
				break;
			case SPI_PORT_TYPE_SCLK:
				if(ubSetValue == TRUE)
					GPIO_SetBits(pstSPI->ulHalBaseCLK, pstSPI->ulHalPinCLK);
					//GPIO_SetBits(GPIOH, GPIO_Pin_7);
				else 
					GPIO_ResetBits(pstSPI->ulHalBaseCLK, pstSPI->ulHalPinCLK);
					//GPIO_ResetBits(GPIOH, GPIO_Pin_7);
				break;
			case SPI_PORT_TYPE_DO:
				break;
			case SPI_PORT_TYPE_DI:
				if(ubSetValue == TRUE)
					GPIO_SetBits(pstSPI->ulHalBaseDI, pstSPI->ulHalPinDI);
				else 
					GPIO_ResetBits(pstSPI->ulHalBaseDI, pstSPI->ulHalPinDI);
				break;
		}
	}

	return ubRet;
}