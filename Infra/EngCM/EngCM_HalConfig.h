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
#ifdef __ENGDW_LIB_C__
#define EXTERN
#else
#define EXTERN	extern
#endif

#include "EngHAL_Types.h"

#if defined(STM32F4XX_SUPPORT)
	#include "EngHAL_GPIO_STM32F4xx.h"
	#include "EngHAL_ADC_STM32F4xx.h"
	#include "EngHAL_CAN_STM32F4xx.h"
	#include "EngHAL_TIM_STM32F4xx.h"
	#include "EngHAL_UART_STM32F4xx.h"
	#include "EngHAL_PWR_STM32F4xx.h"
	#include "EngHAL_RTC_STM32F4xx.h"
#elif defined(STM32F7XX_SUPPORT)
	#include "EngHAL_GPIO_STM32F7xx.h"
	#include "EngHAL_ADC_STM32F7xx.h"
	#include "EngHAL_CAN_STM32F7xx.h"
	#include "EngHAL_ETH_STM32F7xx.h"
	#include "EngHAL_UART_STM32F7xx.h"
#endif


#ifdef	__ENGHAL_LIB_C__
EXTERN THalGPIOPorting astHalGPOTbl[] =
{
    /*	Input Name						AsicType			        Channel					Active					Bit			Initial			PinSelCh	PinSelBit	ChkSum			*/
    //{   HAL_GPIO_NAME_ML_BLDC_EN,       HAL_CHIP_LM60_TRAY,         0,                      HAL_GPIO_ACTIVE_HIGH,   0,          HAL_GPIO_OFF,   0,          0,          0},
	{	HAL_GPO_NAME_UNSPECIFIED	}
};
#else
EXTERN THalGPIOPorting astHalGPOTbl[HAL_GPO_NAME_MAX];
#endif

#ifdef	__ENGHAL_LIB_C__
EXTERN THalGPIOPorting astHalGPITbl[] =
{
    /*	Input Name						AsicType			        Channel					Active					Bit			Initial			PinSelCh	PinSelBit	ChkSum			*/
    //{   HAL_GPIO_NAME_FANDS,            HAL_CHIP_LM60_TRAY,         0,                      HAL_GPIO_ACTIVE_HIGH,   0,          HAL_GPIO_OFF,   0,          0,          0},

	{	HAL_GPI_NAME_UNSPECIFIED	}
};
#else
EXTERN THalGPIOPorting astHalGPITbl[HAL_GPI_NAME_MAX];
#endif

#ifdef	__ENGHAL_LIB_C__
EXTERN THalADCPorting astHalADCTbl[] =
{
    /*	Input Name						ChipType			        Channel         		*/
    {   HAL_ADC_NAME_DUMMY1,            HAL_CHIP_STM32F7xx,         0,                      },

	{	HAL_ADC_NAME_UNSPECIFIED	}
};
#else
EXTERN THalADCPorting astHalADCTbl[HAL_ADC_NAME_MAX];
#endif


#ifdef	__ENGHAL_LIB_C__
EXTERN THalCANPorting astHalCANTbl[] =
{
    /*	Input Name						ChipType			        Channel         ID Type                 ID			DLC		*/
    {   HAL_CAN_NAME_MOTOR_CTRL,        HAL_CHIP_STM32F7xx,         0,              HAL_CAN_ID_TYPE_STD,    0x280,      8       },

	{	HAL_CAN_NAME_UNSPECIFIED	}
};
#else
EXTERN THalCANPorting astHalCANTbl[HAL_CAN_NAME_MAX];
#endif


#ifdef	__ENGHAL_LIB_C__
EXTERN THalUARTPorting astHalUARTTbl[] =
{
    /*	Input Name						ChipType			        Channel		Baudrate			*/
    {   HAL_UART_NAME_USART3,			HAL_CHIP_STM32F7xx,         3,			115200				},
    {   HAL_UART_NAME_UART4,			HAL_CHIP_STM32F7xx,         4,			115200				},

	{	HAL_UART_NAME_UNSPECIFIED	}
};
#else
EXTERN THalUARTPorting astHalUARTTbl[HAL_UART_NAME_MAX];
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
		NULL,
		NULL,
		NULL,
		NULL,
		EngHAL_UART_Transmit_F4xx,
		EngHAL_UART_Receive_F4xx,
		NULL,
		NULL,

		/* THalGPIOFunction */
		NULL,											/* 5 */		
		
		/* THalPWMFunction */
		/* THalADCFunction */
		/* THalMotorFunction */
		

	},
	{	HAL_CHIP_UNSPECIFIED	}
};
#endif


#endif /* __ENGCM_HALCONFIG_H__ */

