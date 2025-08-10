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

TCANRxBuffer s_astCanRxBuffer;
TCANTxBuffer s_astCanTxBuffer;

TCanCommand s_astCanCommand;

EXTERN TCAN s_astDeviceCanTbl[] =		
{
	/*	DeviceKey					Name		Status					*/
	{	CAN_NAME_MOTOR_CTRL,		"CAN1",		CAN_STATE_Waiting,		},	

	{	CAN_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
extern TCANRxBuffer s_astCanRxBuffer;
extern TCANTxBuffer s_astCanTxBuffer;

extern TCanCommand s_astCanCommand;

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
	/*	DeviceKey				Name		GPIO_TypeDef	HalID			SensorType				GPIOActiveType			SensorReadType				SensorReadCtrl				SelectDataBus			*/
	/* ML Sensors */
	{	SENSOR_NAME_ML_FANDS,	"FANDS",	GPIOG,			SENSOR_TYPE_SHORT,		HAL_GPIO_ACTIVE_LOW,	SENSOR_READ_TYPE_STABLE,	SENSOR_READ_CTRL_DIRECT,	SENSOR_READ_BUS_UNSPECIFIED	},	

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


/* Motor Driver Instance
*/

#ifdef __ENGDRV_IF_C__

EXTERN TMotor s_astDeviceMotorTbl[] =
{
	/*	DeviceKey					Name				MotorType						HalID	STEPHalInfo	BLDCHalInfo						*/
	{	MOTOR_NAME_HEAD_ROLL,		"Head Roll",		MOTOR_TYPE_SERVO_DYNAMIXEL,		0,		NULL,		NULL		},	
	{	MOTOR_NAME_HEAD_YAW,		"Head Yaw",			MOTOR_TYPE_SERVO_DYNAMIXEL,		0,		NULL,		NULL		},	
	{	MOTOR_NAME_RIGHT_SHOULDER1,	"R-Shoulder1",		MOTOR_TYPE_SERVO_RMDX,			0,		NULL,		NULL		},	
	{	MOTOR_NAME_RIGHT_SHOULDER2,	"R-Shoulder2",		MOTOR_TYPE_SERVO_RMDX,			0,		NULL,		NULL		},	
	{	MOTOR_NAME_RIGHT_SHOULDER3,	"R-Shoulder3",		MOTOR_TYPE_SERVO_RMDX,			0,		NULL,		NULL		},	
	//{	MOTOR_NAME_RIGHT_ELBOW,		"R-Elbow",			MOTOR_TYPE_SERVO_RMDX,			0,		NULL,		NULL		},	
	//{	MOTOR_NAME_RIGHT_WRIST1,	"R-Wrist1",			MOTOR_TYPE_BLDC,				0,		NULL,		NULL		},	
	//{	MOTOR_NAME_RIGHT_WRIST2,	"R-Wrist2",			MOTOR_TYPE_BLDC,				0,		NULL,		NULL		},	

	{	MOTOR_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
EXTERN TMotor s_astDeviceMotorTbl[DEVICE_MOTOR_MAX_NUMS];
#endif


/* ADC Driver Instance
*/

#ifdef __ENGDRV_IF_C__
EXTERN TADC s_astDeviceADCTbl[] =
{
	/*	DeviceKey				Name		TADCChannel		TADCMuxAddress	OS_MUTEX				*/
	/* ML */
	{	ADC_NAME_FANGD,			"FANGD",	ADC_CHANNEL_1,	ADC_MUX_ADDR_1,			},	
	{	ADC_NAME_FBNGD,			"FBNGD",	ADC_CHANNEL_1,	ADC_MUX_ADDR_2,			},	
	{	ADC_NAME_FCNGD,			"FCNGD",	ADC_CHANNEL_1,	ADC_MUX_ADDR_3,			},	
	
	{	ADC_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
EXTERN TADC s_astDeviceADCTbl[DEVICE_ADC_MAX_NUMS];
#endif


/* Solenoid Driver Instance
*/

#ifdef __ENGDRV_IF_C__

EXTERN TSolenoid s_astDeviceSolenoidTbl[] =
{
	/*	DeviceKey				Name								*/
	{	SOLENOID_NAME_MAIN,		"Sol",								},	

	{	SOLENOID_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
EXTERN TSolenoid s_astDeviceSolenoidTbl[DEVICE_SOLENOID_MAX_NUMS];
#endif


/* Encoder Driver Instance
*/

#ifdef __ENGDRV_IF_C__
EXTERN TEncoder s_astDeviceEncoderTbl[] =
{
	/*	DeviceKey						Name					Type						HalID	Encoder CAN ID	CAN_DeviceKey			*/
	{	ENCODER_NAME_MAIN,				"Main Encoder",			ENCODER_TYPE_SERVO_RMDX,	0,		0,				CAN_NAME_MOTOR_CTRL		},	

	{	ENCODER_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
EXTERN TEncoder s_astDeviceEncoderTbl[DEVICE_ENCODER_MAX_NUMS];
#endif


/* EEPROM Driver Instance
*/

#ifdef __ENGDRV_IF_C__
EXTERN TEeprom s_astDeviceEepromTbl[] =
{
	/*	DeviceKey			Name			CtrlHalInfo	HalPinSK		OS_MUTEX	*/
	{	EEPROM_NAME_RJB,	"EEPROM_RJB",	NULL,		NULL		},	

	{	EEPROM_NAME_UNSPECIFIED	}
};
#else // __ENGDRV_IF_C__
extern MutexId* g_osmMutexEepromRJB;

EXTERN TEeprom s_astDeviceEepromTbl[DEVICE_EEPROM_MAX_NUMS];
#endif


/* SPI Driver Instance
*/

#ifdef __ENGDRV_IF_C__
EXTERN TSPI s_astDeviceSPITbl[] =
{
	/*	DeviceKey			Name			HalBaseCS	HalPinCS	HalBaseCLK	HalPinCLK	HalBaseDO	HalPinDO 	HalBaseDI	HalPinDI 	OS_MUTEX		*/
	{	SPI_NAME_BLDC_ML,	"SPI BLDC_ML",	GPIOH,		0,	GPIOH,		0,	NULL,		0,			GPIOH,		0,	NULL	},	
	{	SPI_NAME_BLDC_RJP,	"SPI BLDC_RJP",	GPIOF,		0,	GPIOF,		0,	GPIOB,		0,GPIOF,		0,	NULL	},	

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
//#include "EngDrv_Motor.h"
#include "EngDrv_ADC.h"
#include "EngDrv_Encoder.h"
//#include "EngDrv_EEPROM.h"
#include "EngDrv_Flash.h"
#include "EngDrv_SPI.h"
#include "EngDrv_UART.h"
#include "EngDrv_IF.h"
#endif // __ENGDRV_IF_C__

#endif /* __ENGCM_DRIVERCONFIG_H__ */