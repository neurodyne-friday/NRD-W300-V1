/**
 * file        EngCM_HalConfig.h
 * brief       This is type definition file for common
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
 * @dept		Embedded Firmware Team
 * @date		20/02/2024(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGCM_HALCONFIG_H__
#define __ENGCM_HALCONFIG_H__

#undef EXTERN
#ifdef __ENGHAL_LIB_C__
#define EXTERN
#else
#define EXTERN	extern
#endif

#include "EngHAL_Types.h"

#if defined(STM32F4XX_SUPPORT)
	#include "EngHAL_Core_STM32F4xx.h"
	#include "EngHAL_GPIO_STM32F4xx.h"
	#include "EngHAL_ADC_STM32F4xx.h"
	#include "EngHAL_PWM_STM32F4xx.h"
	#include "EngHAL_CAN_STM32F4xx.h"
	#include "EngHAL_UART_STM32F4xx.h"
	#include "EngHAL_PWR_STM32F4xx.h"
	#include "EngHAL_RTC_STM32F4xx.h"
	#include "EngHAL_SRAM_STM32F4xx.h"
	#include "EngHAL_SPI_STM32F4xx.h"
	#include "EngHAL_I2C_STM32F4xx.h"
#elif defined(STM32F7XX_SUPPORT)
	#include "EngHAL_GPIO_STM32F7xx.h"
	#include "EngHAL_ADC_STM32F7xx.h"
	#include "EngHAL_CAN_STM32F7xx.h"
	#include "EngHAL_ETH_STM32F7xx.h"
	#include "EngHAL_UART_STM32F7xx.h"
#endif


#ifdef	__ENGHAL_LIB_C__
EXTERN THalGPIOPorting astHalGPIOTbl[] =
{
    /*	Output Name						ChipType			        Port		PinNumber		THalGPIOInOut		Active					Bit			Initial			PinSelCh	PinSelBit	ChkSum			*/
    {   HAL_GPIO_NAME_INDICATOR,		HAL_CHIP_STM32F4xx,         PORT_B,		2,				HAL_GPIO_OUTPUT,	HAL_GPIO_ACTIVE_HIGH,   0,          HAL_GPIO_OFF,   0,          0,          0},
	{   HAL_GPIO_NAME_L6230_CH1_EN,		HAL_CHIP_STM32F4xx,         PORT_C,		10,				HAL_GPIO_OUTPUT,	HAL_GPIO_ACTIVE_HIGH,   0,          HAL_GPIO_OFF,   0,          0,          0},
    {   HAL_GPIO_NAME_L6230_CH2_EN,		HAL_CHIP_STM32F4xx,         PORT_C,		11,				HAL_GPIO_OUTPUT,	HAL_GPIO_ACTIVE_HIGH,   0,          HAL_GPIO_OFF,   0,          0,          0},
    {   HAL_GPIO_NAME_L6230_CH3_EN,		HAL_CHIP_STM32F4xx,         PORT_C,		12,				HAL_GPIO_OUTPUT,	HAL_GPIO_ACTIVE_HIGH,   0,          HAL_GPIO_OFF,   0,          0,          0},
	
    /*	Input Name						ChipType			        Channel		PinNumber		THalGPIOInOut		Active					Bit			Initial			PinSelCh	PinSelBit	ChkSum			*/
    {   HAL_GPIO_NAME_DIAG,				HAL_CHIP_STM32F4xx,         PORT_A,		6,				HAL_GPIO_INPUT,		HAL_GPIO_ACTIVE_HIGH,   0,          HAL_GPIO_OFF,   0,          0,          0},

	{	HAL_GPIO_NAME_UNSPECIFIED	}
};
#else
EXTERN THalGPIOPorting astHalGPIOTbl[HAL_GPIO_NAME_MAX];
#endif


#ifdef	__ENGHAL_LIB_C__
EXTERN THalADCPorting astHalADCTbl[] =
{
    /*	Input Name						ChipType			        Channel        	*/
    {   HAL_ADC_NAME_CURRENT_PHA,		HAL_CHIP_STM32F4xx,			0,				},
    {   HAL_ADC_NAME_CURRENT_PHB,		HAL_CHIP_STM32F4xx,			11,				},
    {   HAL_ADC_NAME_CURRENT_PHC,		HAL_CHIP_STM32F4xx,			10,				},

    {   HAL_ADC_NAME_VBUS,				HAL_CHIP_STM32F4xx,			1,				},
    {   HAL_ADC_NAME_TEMP,				HAL_CHIP_STM32F4xx,			12,				},

	{	HAL_ADC_NAME_UNSPECIFIED	}
};
#else
EXTERN THalADCPorting astHalADCTbl[HAL_ADC_NAME_MAX];
#endif


#ifdef	__ENGHAL_LIB_C__
EXTERN THalPWMPorting astHalPWMTbl[] =
{
    /*	Input Name					ChipType			        ModuleNo		Channel		GPIOPort	GPIOPin		Period	*/
    {   HAL_PWM_NAME_UH,        	HAL_CHIP_STM32F4xx,         HAL_MODULE_1,	1,			PORT_A,		8,			4499,		},	// 4499 = 20kHz @ fTIM1=180MHz
	{   HAL_PWM_NAME_VH,        	HAL_CHIP_STM32F4xx,         HAL_MODULE_1,	2,			PORT_A,		9,			4499,		},
	{   HAL_PWM_NAME_WH,        	HAL_CHIP_STM32F4xx,         HAL_MODULE_1,	3,			PORT_A,		10,			4499,		},

	{	HAL_PWM_NAME_UNSPECIFIED	}
};
#else
EXTERN THalPWMPorting astHalPWMTbl[HAL_PWM_NAME_MAX];
#endif


#ifdef	__ENGHAL_LIB_C__
EXTERN THalCANPorting astHalCANTbl[] =
{
    /*	Input Name						ChipType			        Channel         ID Type                 ID			DLC		*/
    {   HAL_CAN_NAME_MOTOR_CTRL,        HAL_CHIP_STM32F4xx,         1,              HAL_CAN_ID_TYPE_STD,    0x12C,     	8       },

	{	HAL_CAN_NAME_UNSPECIFIED	}
};
#else
EXTERN THalCANPorting astHalCANTbl[HAL_CAN_NAME_MAX];
#endif


#ifdef	__ENGHAL_LIB_C__
EXTERN THalUARTPorting astHalUARTTbl[] =
{
    /*	Input Name						ChipType			        Channel		Baudrate			*/
    {   HAL_UART_NAME_USART2,			HAL_CHIP_STM32F4xx,         2,			115200				},
//	{   HAL_UART_NAME_USART3,			HAL_CHIP_STM32F4xx,         3,			115200				},
//	{   HAL_UART_NAME_UART4,			HAL_CHIP_STM32F4xx,         4,			115200				},

	{	HAL_UART_NAME_UNSPECIFIED	}
};
#else
EXTERN THalUARTPorting astHalUARTTbl[HAL_UART_NAME_MAX];
#endif

#ifdef	__ENGHAL_LIB_C__
EXTERN THalSPIPorting astHalSPITbl[] =
{
    /*	Input Name				ChipType				Channel 			Mode					Direction					DataSize				ClkPolarity			ClkPhase				NSS					BaudRatePrescaler				FirstBit				*/
	{   HAL_SPI_NAME_MA702,		HAL_CHIP_STM32F4xx,		HAL_SPI_CHANNEL_3, 	HAL_SPI_MODE_MASTER, 	HAL_SPI_DIRECTION_2LINES, 	HAL_SPI_DATASIZE_16BIT,	HAL_SPI_CLKPOL_LOW,	HAL_SPI_CLKPHASE_1EDGE,	HAL_SPI_NSS_SOFT,	HAL_SPI_BAUDRATEPRESCALER_8,	HAL_SPI_FIRSTBIT_MSB	},

	{	HAL_SPI_NAME_UNSPECIFIED	}
};
#else
EXTERN THalSPIPorting astHalSPITbl[HAL_SPI_NAME_MAX];
#endif


#ifdef __ENGHAL_LIB_C__
EXTERN THalI2CPorting astHalI2CTbl[] =
{
    /*   HAL Name				ChipType				Channel				Clock(Hz) */
    {   HAL_I2C_NAME_AS5600,	HAL_CHIP_STM32F4xx,		HAL_I2C_CHANNEL_1,	400000		},

    {   HAL_I2C_NAME_UNSPECIFIED  }
};
#else
EXTERN THalI2CPorting astHalI2CTbl[HAL_I2C_NAME_MAX];
#endif


#ifdef	__ENGHAL_LIB_C__
EXTERN THalETHPorting astHalETHTbl[] =
{
    /*	HAL Name						ChipType			        Channel		IPType			LWIPOnOff			DHCPOnOff			STATE				*/
    {   HAL_ETH_NAME_MAIN,				HAL_CHIP_STM32F7xx,         0,			HAL_ETH_IP_V4,	HAL_ETH_LWIP_ON,	HAL_ETH_DHCP_ON,	HAL_ETH_STATE_INIT,
		{192,	168,	0,		100},	/* Static IP Address */
		{255,	255,	255,	0},		/* Net Mask */
		{192,	168,	0,		1}		/* Gateway Address */
	},

	{	HAL_ETH_NAME_UNSPECIFIED	}
};
#else
EXTERN THalETHPorting astHalETHTbl[HAL_ETH_NAME_MAX];
#endif


/**
 * HAL Function Table
 */
#ifdef	__ENGHAL_LIB_C__
static THalFunction astHalFunctionTbl[] =
{	
	{
		HAL_CHIP_STM32F4xx,									/* 0 */
		
		/* THalGPIOFunction */
		NULL,
		NULL,
		NULL,

		/* THalADCFunction */
		EngHAL_ADC_Init_F4xx,
		NULL,

		/* THalPWMFunction */
		EngHAL_PWM_Init_F4xx,
		NULL,

        /* THalCANFunction */
		EngHAL_CAN_Init_F4xx,
		EngHAL_CAN_EnableInterrupt_F4xx,
		EngHAL_CAN_DisableInterrupt_F4xx,
		EngHAL_CAN_IsRxFIFOEmpty_F4xx,
		EngHAL_CAN_IsTxFIFOEmpty_F4xx,
		EngHAL_CAN_Transmit_F4xx,
		EngHAL_CAN_Receive_F4xx,
		NULL,
		NULL,
		
		/* THalETHFunction */
		NULL,//EngHAL_ETH_Init_F4xx,
		NULL,//EngHAL_ETH_Connect_Entry_F4xx,
		NULL,//EngHAL_ETH_Connect_Activity_F4xx,
		NULL,//EngHAL_ETH_Connect_Exit_F4xx,
		NULL,//EngHAL_ETH_Transmit_F4xx,

		/* THalUARTFunction */
		EngHAL_UART_Init_F4xx,
		EngHAL_UART_EnableInterrupt_F4xx,
		EngHAL_UART_DisableInterrupt_F4xx,
		EngHAL_UART_IsRxFIFOEmpty_F4xx,
		EngHAL_UART_IsTxFIFOEmpty_F4xx,
		EngHAL_UART_Transmit_F4xx,
		EngHAL_UART_Receive_F4xx,
		EngHAL_UART_SendByte_F4xx,
		EngHAL_UART_GetByte_F4xx,

		/* THalSPIFunction */
		EngHAL_SPI_Init_F4xx,
		EngHAL_SPI_Write_F4xx,
		EngHAL_SPI_WriteRead_F4xx,

		/* THalI2CFunction */
		EngHAL_I2C_Init_F4xx,
		EngHAL_I2C_MemRead_F4xx,
		EngHAL_I2C_MemWrite_F4xx,
		EngHAL_I2C_Read_F4xx,
		EngHAL_I2C_Write_F4xx,

	},
	{	HAL_CHIP_UNSPECIFIED	}
};
#endif


#endif /* __ENGCM_HALCONFIG_H__ */

