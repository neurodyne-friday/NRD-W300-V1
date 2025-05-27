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

		//pstInstance->pfnInitialize(pstInstance);
    } 	
}

void EngDrv_SPI_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	// Enable GPIO clock 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

	//
	// GPIOA Pin 9	: LRJB_BLDC_SCLK
	// GPIOA Pin 10	: LRJB_BLDC_SCS
	// GPIOA Pin 11	: LRJB_BLDC_SDATAI
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//
	// GPIOH Pin 7	: ML_BLDC_SCLK
	// GPIOH Pin 8	: ML_BLDC_SCS
	// GPIOH Pin 9	: ML_BLDC_SDATAI
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
}

void EngDrv_SPI_Initialize(TSPI* pstSPI)
{
	// Create Mutex
	OS_ERR err;

	OSMutexCreate(pstSPI->osmMutex, "SPI Mutex", &err);
}

S32 EngDrv_SPI_WriteRegister(TSPI* pstSPI, U8 ubAddress, U8 ubByte1, U8 ubByte2)
{
	OS_ERR err;
	CPU_TS ts;

	if(!pstSPI)
		return 0;

	OSMutexPend(pstSPI->osmMutex, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
	
	// SCS High(Active High)
	EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_CS, TRUE);

	DelayNOP(10*3);
	EngDrv_SPI_WriteByte(pstSPI, REG_WRITE & ubAddress);
	DelayNOP(10*3);
	EngDrv_SPI_WriteByte(pstSPI, ubByte1);
	DelayNOP(10*3);
	EngDrv_SPI_WriteByte(pstSPI, ubByte2);
	DelayNOP(10*3);

	// SCS Low
	EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_CS, FALSE);
	DelayNOP(10*3);

	OSMutexPost(pstSPI->osmMutex, OS_OPT_POST_NONE, &err);
	
	return 0;
}

S32 EngDrv_SPI_ReadRegister(TSPI* pstSPI, U8 ubAddress)
{
	U16 uwData = 0;
	OS_ERR err;
	CPU_TS ts;

	if(!pstSPI)
		return 0;

	OSMutexPend(pstSPI->osmMutex, 0, OS_OPT_PEND_BLOCKING, &ts, &err);

	// SCS High(Active High)
	EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_CS, TRUE);
	DelayNOP(10*3);
	EngDrv_SPI_WriteByte(pstSPI, REG_READ | ubAddress);
	DelayNOP(10*3);
	uwData |= ((EngDrv_SPI_ReadByte(pstSPI) << 8) & 0xFF00);
	DelayNOP(10*3);
	uwData |= (EngDrv_SPI_ReadByte(pstSPI) & 0x00FF);
	DelayNOP(10*3);

	// SCS Low
	EngDrv_SPI_PortCtrl(pstSPI, SPI_PORT_TYPE_CS, FALSE);
	DelayNOP(10*3);

	OSMutexPost(pstSPI->osmMutex, OS_OPT_POST_NONE, &err);

	return uwData;
}

void EngDrv_SPI_WriteByte(TSPI* pstSPI, u8 ubByte)
{
	u8 ubIndex;

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

u8 EngDrv_SPI_ReadByte(TSPI* pstSPI)
{
	u8 ubIndex;
	u8 ubData = 0;

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

u8 EngDrv_SPI_PortCtrl(TSPI* pstSPI, TSPIPortType ePortType, u8 ubSetValue)
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
				if(pstSPI->ulDeviceKey == SPI_NAME_BLDC_ML)
				{
					GPIO_ResetBits(GPIOG, GPIO_Pin_11);
					DelayUS(1);

					ubRet  =  GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1) << 1);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2) << 2);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3) << 3);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4) << 4);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) << 5);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_12)<< 6);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13) << 7);

					GPIO_SetBits(GPIOG, GPIO_Pin_11);

					ubRet = (ubRet >> 3) & 0x01;
				}
				else if(pstSPI->ulDeviceKey == SPI_NAME_BLDC_RJP)
				{
					GPIO_ResetBits(GPIOG, GPIO_Pin_11);
					DelayUS(1);

					ubRet  =  GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1) << 1);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2) << 2);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3) << 3);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4) << 4);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) << 5);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_12)<< 6);
					ubRet |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13) << 7);

					GPIO_SetBits(GPIOG, GPIO_Pin_11);

					ubRet = (ubRet >> 4) & 0x01;
				}
				break;
			case SPI_PORT_TYPE_DI:
				if(ubSetValue == TRUE)
					GPIO_SetBits(pstSPI->ulHalBaseDI, pstSPI->ulHalPinDI);
					//GPIO_SetBits(GPIOH, GPIO_Pin_9);
				else 
					GPIO_ResetBits(pstSPI->ulHalBaseDI, pstSPI->ulHalPinDI);
					//GPIO_ResetBits(GPIOH, GPIO_Pin_9);
				break;
		}
	}

	return ubRet;
}