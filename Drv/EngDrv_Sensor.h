/**
 * @file        EngDrv_Sensor.h
 * @brief       This is type definition file for Sensor Driver
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

#ifndef __ENGDRV_SENSOR_H__
#define __ENGDRV_SENSOR_H__

#undef EXTERN
#ifdef __ENGDRV_SENSOR_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"

EXTERN void EngDrv_Sensor_Create(void);
EXTERN void EngDrv_Sensor_Configuration(void);
EXTERN void EngDrv_Sensor_ReadGPIOConfiguration(void);
EXTERN void EngDrv_Sensor_Initialize(TSensor* pstSensor);
EXTERN void EngDrv_Sensor_InitializeAll(void);
EXTERN void EngDrv_Sensor_AddListener(TSENSOR_CALLBACK pfnFunc);
EXTERN void EngDrv_Sensor_TalkToListener(U8 *parg);

EXTERN void EngDrv_Sensor_UpdateSensorAll(void);
EXTERN U8 EngDrv_Sensor_GetValue(TSensor* pstSensor);
EXTERN void EngDrv_Sensor_Read(TSensor* pstSensor);
EXTERN void EngDrv_Sensor_UpdateDataBus(void); // need to be modified 
EXTERN U16 EngDrv_Sensor_GetADCValue(U32 ulDeviceKay);


#endif /* __ENGDRV_SENSOR_H__ */
