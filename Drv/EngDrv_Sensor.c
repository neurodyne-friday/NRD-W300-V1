/**
 * @file        EngDrv_Sensor.c
 * @brief       This is type definition file for CAN Driver
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

#define	__ENGDRV_SENSOR_C__

#include "EngDrv_Sensor.h"
#include "EngDrv_IF.h"
#include "EngCM_DriverConfig.h"


void EngDrv_Sensor_Create(void)
{
    TSensor* pstInstance = NULL;
    U8 ubCount = sizeof(s_astDeviceSensorTbl) / sizeof(TSensor);

    for(U8 ubIndex = 0; ubIndex < ubCount; ubIndex++)
    {
        pstInstance = &s_astDeviceSensorTbl[ubIndex];

        pstInstance->pfnInitialize = EngDrv_Sensor_Initialize;
        pstInstance->pfnGet = EngDrv_Sensor_GetValue;
    }
}

void EngDrv_Sensor_Initialize(TSensor* pstSensor)
{

}


void EngDrv_Sensor_UpdateSensorAll()
{
	TSensor* pstSensor = NULL;

	if(g_vu32Timer < 200)
		return;	

	for(U32 ulDeviceKey = DEVICE_SENSOR_KEY_BASE; ulDeviceKey < SENSOR_NAME_MAX; ulDeviceKey++)
	{
		pstSensor = EngDrv_IF_GetSensor(ulDeviceKey);

		if(pstSensor)
		{
			EngDrv_Sensor_Read(pstSensor);

			if(pstSensor->ubOldSensorValue != pstSensor->ubSensorValue)
			{
				// debug log
				EngDrv_UartDebug_WriteLogData("\n\r\t>>[%s] Sensor: %s change value %d -> %d", __TIME__, pstSensor->pubName, pstSensor->ubOldSensorValue, pstSensor->ubSensorValue);
				pstSensor->ubOldSensorValue = pstSensor->ubSensorValue;
			}
		}
	}
}

/**
 * Sensor Callback Function Handling 
 */

void EngDrv_Sensor_AddListener(TSENSOR_CALLBACK pfnFunc)
{
   	pfnSensorCallback = pfnFunc;
}


void EngDrv_Sensor_TalkToListener(U8 *parg)
{
	if(pfnSensorCallback != NULL)
	{
		pfnSensorCallback(parg);
	}
}

void EngDrv_Sensor_Read(TSensor* pstSensor)
{
	U8 ubReadData = 0;
	U32 ubBitIndex = 0;
	U8 ubBitShift = 0;
	U8 ubBitResult = 0;

	if(pstSensor == NULL)
		return;

	for(U8 ubIndex = 1; ubIndex < SENSOR_BUFFER_SIZE; ubIndex++)
	{
		pstSensor->aubSensorValue[ubIndex - 1] = pstSensor->aubSensorValue[ubIndex];
	}

	if(pstSensor->enReadCtrl == SENSOR_READ_CTRL_DIRECT)
	{
		if(pstSensor->eIOActiveType == HAL_GPIO_ACTIVE_LOW)
			pstSensor->aubSensorValue[SENSOR_BUFFER_SIZE - 1] = !GPIO_ReadInputDataBit(pstSensor->pstHalBaseID, pstSensor->ulHalPinID);
		else
			pstSensor->aubSensorValue[SENSOR_BUFFER_SIZE - 1] = GPIO_ReadInputDataBit(pstSensor->pstHalBaseID, pstSensor->ulHalPinID);
	}
	else if(pstSensor->enReadCtrl == SENSOR_READ_CTRL_USEMUX)
	{
		ubBitIndex = (U8)pstSensor->ulHalPinID;
		while(ubBitIndex != 0x01)
		{
			ubBitShift++;
			ubBitIndex = ubBitIndex >> 1;

			if(ubBitShift > 15)
				return;
		}
		ubReadData = (ubReadData & (0x01 << ubBitShift)) >> ubBitShift;

		if(pstSensor->eIOActiveType == HAL_GPIO_ACTIVE_LOW)
			pstSensor->aubSensorValue[SENSOR_BUFFER_SIZE - 1] = !ubReadData;
		else
			pstSensor->aubSensorValue[SENSOR_BUFFER_SIZE - 1] = ubReadData;
	}

	// On check
	ubBitResult = 0x01;
	for(U8 ubIndex = 0; ubIndex < SENSOR_BUFFER_SIZE; ubIndex++)
	{
		ubBitResult &= pstSensor->aubSensorValue[ubIndex];
	}

	if(ubBitResult == 0x01)
		pstSensor->ubSensorValue = TRUE;

	// Off check
	ubBitResult = 0x00;
	for(U8 ubIndex = 0; ubIndex < SENSOR_BUFFER_SIZE; ubIndex++)
	{
		ubBitResult |= pstSensor->aubSensorValue[ubIndex];
	}

	if(ubBitResult == 0x00)
		pstSensor->ubSensorValue = FALSE;
}


U8 EngDrv_Sensor_GetValue(TSensor* pstSensor)
{
    return pstSensor->ubSensorValue;
}

void EngDrv_Sensor_UpdateDataBus(void)
{
    TSensor* pstSensor = NULL;

    for(U32 ulDeviceKey = DEVICE_SENSOR_KEY_BASE; ulDeviceKey < SENSOR_NAME_MAX; ulDeviceKey++)
    {
        pstSensor = EngDrv_IF_GetSensor(ulDeviceKey);
        //pstSensor->pfnUpdate(pstSensor);
    }
}

U16 EngDrv_Sensor_GetADCValue(U32 ulDeviceKay)
{
    U16 uwValue = 0;
    TADCType eADCType;

    switch(ulDeviceKay)
    {
        default:
            return uwValue;
    }

    EngHAL_Sensor_SelectADC(ulDeviceKay);
    uwValue = EngHAL_Sensor_GetADCValue(eADCType);

    return uwValue;
}
