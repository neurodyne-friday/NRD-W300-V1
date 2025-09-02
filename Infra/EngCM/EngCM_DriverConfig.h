/**
 * @file        EngCM_DriverConfig.h
 * @brief       This is type definition file for common
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

#ifndef __ENGCM_DRIVERCONFIG_H__
#define __ENGCM_DRIVERCONFIG_H__

#undef EXTERN
#ifdef __ENGDRV_IF_C__
#define EXTERN
#else
#define EXTERN	extern
#endif

#include "Eng_DeviceType.h"


#define DEVICE_ADC_MAX_NUMS 		10
#define DEVICE_ETH_MAX_NUMS			2
#define DEVICE_CAN_MAX_NUMS			2
#define DEVICE_SENSOR_MAX_NUMS		28
#define DEVICE_MOTOR_MAX_NUMS		6
#define DEVICE_ENCODER_MAX_NUMS		2
#define DEVICE_EEPROM_MAX_NUMS		1
#define DEVICE_SOLENOID_MAX_NUMS	1
#define DEVICE_UART_MAX_NUMS		3
#define DEVICE_SPI_MAX_NUMS			2


/* 
 * CAN Driver Instance
 */
#ifdef __ENGDRV_IF_C__
EXTERN TCAN s_astDeviceCanTbl[] =		
{
	/*	DeviceKey				Name		Status					*/
	{	CAN_NAME_MAIN,			"CAN1",		CAN_STATE_Waiting,		},	

	{	CAN_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
EXTERN TCAN s_astDeviceCanTbl[DEVICE_CAN_MAX_NUMS];
#endif // __ENGDRV_IF_C__


/* 
 * Sensor Driver Instance
 */
#ifdef __ENGDRV_IF_C__
// Temporary use - list of Callback functions for sensor events
TSENSOR_CALLBACK pfnSensorCallback;

EXTERN TSensor s_astDeviceSensorTbl[] =
{
	/*	DeviceKey				Name		GPIO_TypeDef	HalID			SensorType				GPIOActiveType			SensorReadType				SensorReadCtrl					*/
	/* ML Sensors */
	{	SENSOR_NAME_NONAME,		"Test",		GPIOG,			SENSOR_TYPE_SHORT,		HAL_GPIO_ACTIVE_LOW,	SENSOR_READ_TYPE_STABLE,	SENSOR_READ_CTRL_DIRECT,	},	

	{	SENSOR_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
extern TSENSOR_CALLBACK pfnSensorCallback;

EXTERN TSensor s_astDeviceSensorTbl[DEVICE_SENSOR_MAX_NUMS];
#endif


/* ETH Driver Instance
*/

#ifdef __ENGDRV_IF_C__
EXTERN TETH s_astDeviceETHTbl[] =
{
	/*	DeviceKey			Name			*/
	{	ETH_NAME_MAIN, 		"Main",			},	

	{	ETH_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
EXTERN TETH s_astDeviceETHTbl[DEVICE_ETH_MAX_NUMS];
#endif


/* ADC Driver Instance
*/

#ifdef __ENGDRV_IF_C__
EXTERN TADC s_astDeviceADCTbl[] =
{
	/*	DeviceKey				Name				TADCChannel		TADCMuxAddress			*/
	/* ML */
	{	ADC_NAME_CURRENT1,		"CurrentSensor1",	ADC_CHANNEL_1,	ADC_MUX_ADDR_1,			},	
	{	ADC_NAME_CURRENT1,		"CurrentSensor2",	ADC_CHANNEL_1,	ADC_MUX_ADDR_2,			},	
	
	{	ADC_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
EXTERN TADC s_astDeviceADCTbl[DEVICE_ADC_MAX_NUMS];
#endif


/* Encoder Driver Instance
*/

#ifdef __ENGDRV_IF_C__
EXTERN TEncoder s_astDeviceEncoderTbl[] =
{
	/*	DeviceKey						Name				Type					CommType				HalID					*/
	{	ENCODER_NAME_MAIN,				"AS5600",			ENCODER_TYPE_MAGNETIC,	Encoder_CommType_I2C,	HAL_I2C_NAME_AS5600		},	

	{	ENCODER_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
EXTERN TEncoder s_astDeviceEncoderTbl[DEVICE_ENCODER_MAX_NUMS];
#endif


/* SPI Driver Instance
*/

#ifdef __ENGDRV_IF_C__
EXTERN TSPI s_astDeviceSPITbl[] =
{
	/*	DeviceKey			Name			HalBaseCS	HalPinCS	HalBaseCLK	HalPinCLK	HalBaseDO	HalPinDO 	HalBaseDI	HalPinDI 	OS_MUTEX		*/
	{	SPI_NAME_ENCODER,	"SPI-Encoder",	GPIOH,		0,	GPIOH,		0,	NULL,		0,			GPIOH,		0,	NULL	},	

	{	SPI_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
extern MutexId* g_osmMutexSPI_BLDCML;
extern MutexId* g_osmMutexSPI_BLDCRJP;

EXTERN TSPI s_astDeviceSPITbl[DEVICE_SPI_MAX_NUMS];
#endif


/* UART Driver Instance
*/

#ifdef __ENGDRV_IF_C__
EXTERN TUART s_astDeviceUARTTbl[] =
{
	/*	DeviceKey				Name				HalID					UARTRxType		*/
	{	UART_NAME_MAIN,			"Main Uart",		HAL_UART_NAME_UART4,	UART_RX_TYPE_ISR	},	
	{	UART_NAME_STLINK_DEBUG,	"ST-Link Debug",	HAL_UART_NAME_USART3,	UART_RX_TYPE_ISR	},	

	{	UART_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
EXTERN TUART s_astDeviceUARTTbl[DEVICE_UART_MAX_NUMS];
#endif


#ifdef __ENGDRV_IF_C__
#include "EngDrv_CAN.h"
//#include "EngDrv_Ethernet.h"
#include "EngDrv_Sensor.h"
#include "EngDrv_ADC.h"
#include "EngDrv_Encoder.h"
#include "EngDrv_Flash.h"
#include "EngDrv_SPI.h"
#include "EngDrv_UART.h"
#include "EngDrv_IF.h"
#endif // __ENGDRV_IF_C__

#endif /* __ENGCM_DRIVERCONFIG_H__ */