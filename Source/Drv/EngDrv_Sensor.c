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

//static void EngDrv_Sensor_TaskControl(void *p_arg);

OS_MUTEX osmMutexADC;

void EngDrv_Sensor_ControlTask(void *p_arg)
{
	(void)p_arg;

	while(1)
	{
        
		EngDrv_Sensor_UpdateSensorAll();
		
		EngDrv_Sensor_TalkToListener(NULL);

		/*
		// CST 1ms Timer
		g_vu32TimerCount++;
				
		RJB_CheckInIRSensor(); // note checking

        if(g_vu32TimerCount % 100 == 0)
        {
            MountingCheckStatus(0);
        }
        */
		
		OSTimeDly(1u, OS_OPT_TIME_DLY, &g_errDelay);
	}
}

void EngDrv_Sensor_Create(void)
{
    TSensor* pstInstance = NULL;
    U8 ubCount = sizeof(s_astDeviceSensorTbl) / sizeof(TSensor);

    for(U8 ubIndex = 0; ubIndex < ubCount; ubIndex++)
    {
        pstInstance = &s_astDeviceSensorTbl[ubIndex];

        pstInstance->pfnInitialize = EngDrv_Sensor_Initialize;
        pstInstance->pfnGet = EngDrv_Sensor_GetValue;
        pstInstance->pfnSetLevel = EngDrv_Sensor_SetLevel;

        pstInstance->pfnInitialize(pstInstance);
    }
}

void EngDrv_Sensor_Configuration(void)
{
	EngDrv_Sensor_ReadGPIOConfiguration();
    EngDrv_Sensor_LevelingGPIOConfiguration();

	//EngDrv_Sensor_InitializeAll();
}

void EngDrv_Sensor_ReadGPIOConfiguration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/**********************************************************************/
	/*                       Sensor Read Select                           */
	/**********************************************************************/
	
	// Enable GPIO clock 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

	//
	// GPIOC Pin 5	: RD_2
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	
	//
	// GPIOD Pin 6	: RD_1
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


	//
	// GPIOG Pin 11	: RD_3
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	//
	// GPIOH Pin 10	: RD_4
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOH, &GPIO_InitStructure);

	//
	// Active Low
	//
	GPIO_SetBits(GPIOC, GPIO_Pin_5);
	GPIO_SetBits(GPIOD, GPIO_Pin_6);
	GPIO_SetBits(GPIOG, GPIO_Pin_11);
	GPIO_SetBits(GPIOH, GPIO_Pin_10);


	/**********************************************************************/
	/*                       Sensor Read Data                             */
	/**********************************************************************/
	
	// Enable GPIOF clock 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	//
	// GPIOF Pin 0	: DATA00
	// GPIOF Pin 1	: DATA01
	// GPIOF Pin 2	: DATA02
	// GPIOF Pin 3	: DATA03
	// GPIOF Pin 4	: DATA04
	// GPIOF Pin 5	: DATA05
	// GPIOF Pin 12	: DATA06
	// GPIOF Pin 13	: DATA07
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
								| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	// 
	// 20240213 : IR Sensor Data 
	//
	// Enable GPIO clock 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

	//
	// GPIOB Pin 5	: ML_FCNDS_DATA
	// GPIOB Pin 6	: ML_FDNDS_DATA
	// GPIOB Pin 7	: ML_FENDS_DATA
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//
	// GPIOG Pin 10	: ML_FANDS_DATA
	// GPIOG Pin 12	: ML_FBNDS_DATA
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/**********************************************************************/
	/*                           Sensor Enable                            */
	/**********************************************************************/

	// 20240213  : Sensor Ctrl configuration
	
	// Enable GPIO clock 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
	
	//
	// GPIOC Pin 4	: LRJB_SENSOR_CTRL1
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//
	// GPIOE Pin 5	: IR_SENSOR_CTRL0
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	//
	// GPIOI Pin 10	: INT_SENSOR_CTRL2
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOI, &GPIO_InitStructure);
}

void EngDrv_Sensor_LevelingGPIOConfiguration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	// Enable GPIO clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);

	//
	// GPIOA Pin 5	: FDNDS_LEVEL0
	// GPIOA Pin 6	: FDNDS_LEVEL1
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//
	// GPIOD Pin 10  : ML_FLNIS_LEVEL1
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//
	// GPIOF Pin 6 : FANDS_LEVEL0
	// GPIOF Pin 7 : FANDS_LEVEL1
	// GPIOF Pin 9 : FBNDS_LEVEL0
	// GPIOF Pin 10 : FBNDS_LEVEL1
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	//
	// GPIOG Pin 2 : FENDS_LEVEL0
	// GPIOG Pin 3 : FENDS_LEVEL1
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	//
	// GPIOH Pin 4 : FCNDS_LEVEL0
	// GPIOH Pin 5 : FCNDS_LEVEL1
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	
	//
	// GPIOI Pin 0 : LRJB_RANPS_LEVEL0
	// GPIOI Pin 1 : LRJB_RANPS_LEVEL1
	// GPIOI Pin 3 : LRJB_RBNPS_LEVEL0
	// GPIOI Pin 4 : LRJB_RBNPS_LEVEL1
	// GPIOI Pin 5 : ML_FLNOS_LEVEL0
	// GPIOI Pin 6 : ML_FLNOS_LEVEL1
	// GPIOI Pin 7 : ML_FLNIS_LEVEL0
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3
								| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOI, &GPIO_InitStructure);
}


void EngDrv_Sensor_Initialize(TSensor* pstSensor)
{

}

void EngDrv_Sensor_InitializeAll()
{
	//
	// Sensor Off Test
    //
	EngDrv_Sensor_OnOffCheck();

	//
	// RJB : INT, Short, Long Sensor Power On.
	//
	EngHAL_Sensor_PowerControl(ENABLE);
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

	for(u8 ubIndex = 1; ubIndex < SENSOR_BUFFER_SIZE; ubIndex++)
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
		ubReadData = EngHAL_Sensor_ReadFromDataBus(pstSensor->eSelectDataBus);
		ubReadData = (ubReadData & (0x01 << ubBitShift)) >> ubBitShift;

		if(pstSensor->eIOActiveType == HAL_GPIO_ACTIVE_LOW)
			pstSensor->aubSensorValue[SENSOR_BUFFER_SIZE - 1] = !ubReadData;
		else
			pstSensor->aubSensorValue[SENSOR_BUFFER_SIZE - 1] = ubReadData;
	}

	// On check
	ubBitResult = 0x01;
	for(u8 ubIndex = 0; ubIndex < SENSOR_BUFFER_SIZE; ubIndex++)
	{
		ubBitResult &= pstSensor->aubSensorValue[ubIndex];
	}

	if(ubBitResult == 0x01)
		pstSensor->ubSensorValue = TRUE;

	// Off check
	ubBitResult = 0x00;
	for(u8 ubIndex = 0; ubIndex < SENSOR_BUFFER_SIZE; ubIndex++)
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


void EngDrv_Sensor_OnOffCheck(void)
{
    TSensor* pstSensor = NULL;

	// RJP, CST : INT, Short, Long Sensor Power Off.
    EngHAL_Sensor_PowerControl(DISABLE);

	// RJP Sensor Off Test
    pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJP_RANPS);
    if(EngDrv_Sensor_GetValue(pstSensor) == FALSE)
		EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);
    
    pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJP_RBNPS);
    if(EngDrv_Sensor_GetValue(pstSensor) == FALSE)
		EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

	// RJP, CST : INT, Short, Long Sensor Power On.
    EngHAL_Sensor_PowerControl(ENABLE);

	//if(pstModule->pfnIsInstalled(pstModule) == TRUE)
	if(EngDrv_Module_IsMounted() == FALSE)
	{
		// RJB : INT, Short, Long Sensor Power Off.
		EngHAL_Sensor_PowerControl(DISABLE);

        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RAINS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RBINS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RCFNS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RAENS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RBENS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RCENS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RDANS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RAFNS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RBFNS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);
		
        pstSensor = EngDrv_IF_GetSensor(SENSOR_NAME_RJB_RCFNS);
        if(EngDrv_Sensor_GetValue(pstSensor) == RESET)
			EngDrv_UartDebug_WriteLogData("\n\r%8d %s Sensor[%s] Off Error", g_vu32Timer, __func__, pstSensor->pubName);

		// RJB : INT, Short, Long Sensor Power On.
		EngHAL_Sensor_PowerControl(ENABLE);
	}
}

void EngDrv_Sensor_SetLevel(TSensorName ulSensorName, TSensorLevel eLevel)
{
	TSensor* pstSensor = EngDrv_IF_GetSensor(ulSensorName);
	
	if(!pstSensor)
		return ;

	if(pstSensor->enType == SENSOR_TYPE_LONG)
	{
		if(eLevel < SENSOR_LEVEL_2)
		{
			EngHAL_Sensor_SetLevel(pstSensor->ulDeviceKey, eLevel);
		}
	}
	else if(pstSensor->enType == SENSOR_TYPE_SHORT)
	{
		EngHAL_Sensor_SetLevel(pstSensor->ulDeviceKey, eLevel);
	}
}

U16 EngDrv_Sensor_GetOnOffError(void)
{
    return 0;//g_u16SensorOnOffError[eModuleName];
}


/* HAL functions */

void EngHAL_Sensor_PowerControl(U8 ubOnOff)
{
    GPIO_ResetBits(GPIOC, GPIO_Pin_5); //RJB_BUS_CLK RESET

    if(ubOnOff == ENABLE)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_4);
        GPIO_SetBits(GPIOC, GPIO_Pin_0); // RJB Power?

		GPIO_SetBits(GPIOE, GPIO_Pin_5); // IR_SENSOR_CTRL0
		GPIO_SetBits(GPIOI, GPIO_Pin_10); // INT_SENSOR_CTRL2
		GPIO_SetBits(GPIOC, GPIO_Pin_4); // LRJB_SENSOR_CTRL1 -> RJBSensorPowerControl

		EngDrv_UartDebug_WriteLogData("\n\r%8d %s Enable", g_vu32Timer, __func__ );
    }
    else
    {
        GPIO_ResetBits(GPIOC, GPIO_Pin_4);
        GPIO_ResetBits(GPIOC, GPIO_Pin_0); // RJB Power?

		GPIO_ResetBits(GPIOE, GPIO_Pin_5);
		GPIO_ResetBits(GPIOI, GPIO_Pin_10);
		GPIO_ResetBits(GPIOC, GPIO_Pin_4);

		EngDrv_UartDebug_WriteLogData("\n\r%8d %s Disable", g_vu32Timer, __func__ );
    }

    //GPIO_SetBits(GPIOC, GPIO_Pin_5); //RJB_BUS_CLK SET
}

void EngHAL_LRJB_SelectAddress(THalLRJBAddressType eAddressType)
{
    GPIO_ResetBits(GPIOI, GPIO_Pin_11); //LRJB_BUS_CLK RESET

    if(eAddressType == HAL_LRJB_ADDRESS_TYPE_0)
    {
        GPIO_ResetBits(GPIOF, GPIO_Pin_14);	//LRJB_BUS_ADDR0
        GPIO_ResetBits(GPIOF, GPIO_Pin_15);	//LRJB_BUS_ADDR1
        GPIO_SetBits(GPIOG, GPIO_Pin_0);	//LRJB_BUS_ADDR2
        GPIO_SetBits(GPIOG, GPIO_Pin_1);	//LRJB_BUS_ADDR3
    }
    else if(eAddressType == HAL_LRJB_ADDRESS_TYPE_1)
    {
        GPIO_ResetBits(GPIOF, GPIO_Pin_14);
        GPIO_SetBits(GPIOF, GPIO_Pin_15);
        GPIO_ResetBits(GPIOG, GPIO_Pin_0);
        GPIO_SetBits(GPIOG, GPIO_Pin_1);
    }
    else if(eAddressType == HAL_LRJB_ADDRESS_TYPE_2)
    {
        GPIO_ResetBits(GPIOF, GPIO_Pin_14);
        GPIO_SetBits(GPIOF, GPIO_Pin_15);
        GPIO_SetBits(GPIOG, GPIO_Pin_0);
        GPIO_ResetBits(GPIOG, GPIO_Pin_1);
    }
    else if(eAddressType == HAL_LRJB_ADDRESS_TYPE_3)
    {
        GPIO_SetBits(GPIOF, GPIO_Pin_14);
        GPIO_ResetBits(GPIOF, GPIO_Pin_15);
        GPIO_ResetBits(GPIOG, GPIO_Pin_0);
        GPIO_SetBits(GPIOG, GPIO_Pin_1);
    }
    else if(eAddressType == HAL_LRJB_ADDRESS_TYPE_4)
    {
        GPIO_SetBits(GPIOF, GPIO_Pin_14);
        GPIO_ResetBits(GPIOF, GPIO_Pin_15);
        GPIO_SetBits(GPIOG, GPIO_Pin_0);
        GPIO_ResetBits(GPIOG, GPIO_Pin_1);
    }
    else
    {
        DelayUS(10);
        GPIO_SetBits(GPIOI, GPIO_Pin_11); // LRJB_BUS_CLK SET
    }
}

U16 EngDrv_Sensor_GetADCValue(U32 ulDeviceKay)
{
    U16 uwValue = 0;
    TADCType eADCType;

    switch(ulDeviceKay)
    {
        case SENSOR_NAME_RJP_RANPS:
            eADCType = eADC_TYPE_RJP_RANPS;
            break;
        case SENSOR_NAME_RJP_RBNPS:
            eADCType = eADC_TYPE_RJP_RBNPS;
            break;
        case DIVERTER_NAME_RANGD:
            eADCType = eADC_DIVERTER_RANGD;
            break;
        case DIVERTER_NAME_RBNGD:
            eADCType = eADC_DIVERTER_RBNGD;
            break;
        //eADC_TYPE_24V_ADC,
    	//eADC_TYPE_RJB_ADC,
        default:
            return uwValue;
    }

    EngHAL_Sensor_SelectADC(ulDeviceKay);
    DelayUS(200);
    uwValue = EngHAL_Sensor_GetADCValue(eADCType);

    return uwValue;
}

void EngHAL_Sensor_PortControl(U8 ubAddress, GPIO_TypeDef* pHalBaseID, U32 ulHalPinID, U8 ubSet)
{
    EngHAL_LRJB_SelectAddress(ubAddress);

    if(ubSet)
        GPIO_SetBits(pHalBaseID, ulHalPinID);
    else
        GPIO_ResetBits(pHalBaseID, ulHalPinID);
}

void EngHAL_Sensor_SetLevel(TSensorName ulSensorName, TSensorLevel eLevel)
{
	switch(ulSensorName)
	{
    case SENSOR_NAME_RJB_RAINS:
		if(eLevel == SENSOR_LEVEL_0)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_12, FALSE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_14, FALSE);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_12, TRUE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_14, FALSE);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_12, FALSE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_14, TRUE);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_12, TRUE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_14, TRUE);
		}
		break;
    case SENSOR_NAME_RJB_RBINS:
		if(eLevel == SENSOR_LEVEL_0)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_15, FALSE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_11, FALSE);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_15, TRUE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_11, FALSE);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_15, FALSE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_11, TRUE);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_0, GPIOH, GPIO_Pin_15, TRUE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_11, TRUE);
		}
		break;
    case SENSOR_NAME_RJB_RCINS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_12, FALSE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_14, FALSE);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_12, TRUE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_14, FALSE);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_12, FALSE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_14, TRUE);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_12, TRUE);
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_14, TRUE);
		}
		break;
    case SENSOR_NAME_RJB_RAENS:
    	if(eLevel == SENSOR_LEVEL_0)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_3, GPIOH, GPIO_Pin_11, FALSE);
		else if(eLevel == SENSOR_LEVEL_1)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_3, GPIOH, GPIO_Pin_11, TRUE);
		break;
    case SENSOR_NAME_RJB_RBENS:
    	if(eLevel == SENSOR_LEVEL_0)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_2, GPIOH, GPIO_Pin_11, FALSE);
		else if(eLevel == SENSOR_LEVEL_1)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_2, GPIOH, GPIO_Pin_11, TRUE);
		break;
    case SENSOR_NAME_RJB_RCENS:
    	if(eLevel == SENSOR_LEVEL_0)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_3, GPIOH, GPIO_Pin_12, FALSE);
		else if(eLevel == SENSOR_LEVEL_1)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_3, GPIOH, GPIO_Pin_12, TRUE);
		break;
    case SENSOR_NAME_RJB_RDANS:
    	if(eLevel == SENSOR_LEVEL_0)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_2, GPIOH, GPIO_Pin_15, FALSE);
		else if(eLevel == SENSOR_LEVEL_1)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_2, GPIOH, GPIO_Pin_15, TRUE);
		break;
    case SENSOR_NAME_RJB_RAFNS:
    	if(eLevel == SENSOR_LEVEL_0)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_2, GPIOH, GPIO_Pin_14, FALSE);
		else if(eLevel == SENSOR_LEVEL_1)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_2, GPIOH, GPIO_Pin_14, TRUE);
		break;
    case SENSOR_NAME_RJB_RBFNS:
    	if(eLevel == SENSOR_LEVEL_0)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_15, FALSE);
		else if(eLevel == SENSOR_LEVEL_1)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_1, GPIOH, GPIO_Pin_15, TRUE);
		break;
    case SENSOR_NAME_RJB_RCFNS:
    	if(eLevel == SENSOR_LEVEL_0)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_2, GPIOH, GPIO_Pin_12, FALSE);
		else if(eLevel == SENSOR_LEVEL_1)
			EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_2, GPIOH, GPIO_Pin_12, TRUE);
		break;
    case SENSOR_NAME_RJP_RANPS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			GPIO_ResetBits(GPIOI, GPIO_Pin_0);
			GPIO_ResetBits(GPIOI, GPIO_Pin_1);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			GPIO_SetBits(GPIOI, GPIO_Pin_0);
			GPIO_ResetBits(GPIOI, GPIO_Pin_1);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			GPIO_ResetBits(GPIOI, GPIO_Pin_0);
			GPIO_SetBits(GPIOI, GPIO_Pin_1);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			GPIO_SetBits(GPIOI, GPIO_Pin_0);
			GPIO_SetBits(GPIOI, GPIO_Pin_1);
		}
		break;
    case SENSOR_NAME_RJP_RBNPS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			GPIO_ResetBits(GPIOI, GPIO_Pin_3);
			GPIO_ResetBits(GPIOI, GPIO_Pin_4);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			GPIO_SetBits(GPIOI, GPIO_Pin_3);
			GPIO_ResetBits(GPIOI, GPIO_Pin_4);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			GPIO_ResetBits(GPIOI, GPIO_Pin_3);
			GPIO_SetBits(GPIOI, GPIO_Pin_4);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			GPIO_SetBits(GPIOI, GPIO_Pin_3);
			GPIO_SetBits(GPIOI, GPIO_Pin_4);
		}
		break;
    case SENSOR_NAME_ML_FANDS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_6);
			GPIO_ResetBits(GPIOF, GPIO_Pin_7);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_6);
			GPIO_ResetBits(GPIOF, GPIO_Pin_7);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_6);
			GPIO_SetBits(GPIOF, GPIO_Pin_7);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_6);
			GPIO_SetBits(GPIOF, GPIO_Pin_7);
		}
		break;
	case SENSOR_NAME_ML_FBNDS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);
			GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_9);
			GPIO_ResetBits(GPIOF, GPIO_Pin_10);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			GPIO_ResetBits(GPIOF, GPIO_Pin_9);
			GPIO_SetBits(GPIOF, GPIO_Pin_10);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			GPIO_SetBits(GPIOF, GPIO_Pin_9);
			GPIO_SetBits(GPIOF, GPIO_Pin_10);
		}
		break;
	case SENSOR_NAME_ML_FCNDS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			GPIO_ResetBits(GPIOH, GPIO_Pin_4);
			GPIO_ResetBits(GPIOH, GPIO_Pin_5);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			GPIO_SetBits(GPIOH, GPIO_Pin_4);
			GPIO_ResetBits(GPIOH, GPIO_Pin_5);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			GPIO_ResetBits(GPIOH, GPIO_Pin_4);
			GPIO_SetBits(GPIOH, GPIO_Pin_5);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			GPIO_SetBits(GPIOH, GPIO_Pin_4);
			GPIO_SetBits(GPIOH, GPIO_Pin_5);
		}
		break;
	case SENSOR_NAME_ML_FDNDS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
		}
		break;
	case SENSOR_NAME_ML_FENDS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			GPIO_ResetBits(GPIOG, GPIO_Pin_2);
			GPIO_ResetBits(GPIOG, GPIO_Pin_3);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			GPIO_SetBits(GPIOG, GPIO_Pin_2);
			GPIO_ResetBits(GPIOG, GPIO_Pin_3);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			GPIO_ResetBits(GPIOG, GPIO_Pin_2);
			GPIO_SetBits(GPIOG, GPIO_Pin_3);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			GPIO_SetBits(GPIOG, GPIO_Pin_2);
			GPIO_SetBits(GPIOG, GPIO_Pin_3);
		}
		break;
	case SENSOR_NAME_ML_FLNOS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			GPIO_ResetBits(GPIOI, GPIO_Pin_7);
			GPIO_ResetBits(GPIOI, GPIO_Pin_10);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			GPIO_SetBits(GPIOI, GPIO_Pin_7);
			GPIO_ResetBits(GPIOI, GPIO_Pin_10);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			GPIO_ResetBits(GPIOI, GPIO_Pin_7);
			GPIO_SetBits(GPIOI, GPIO_Pin_10);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			GPIO_SetBits(GPIOI, GPIO_Pin_7);
			GPIO_SetBits(GPIOI, GPIO_Pin_10);
		}
		break;
	case SENSOR_NAME_ML_FLNIS:
    	if(eLevel == SENSOR_LEVEL_0)
		{
			GPIO_ResetBits(GPIOI, GPIO_Pin_5);
			GPIO_ResetBits(GPIOI, GPIO_Pin_6);
		}
		else if(eLevel == SENSOR_LEVEL_1)
		{
			GPIO_SetBits(GPIOI, GPIO_Pin_5);
			GPIO_ResetBits(GPIOI, GPIO_Pin_6);
		}
		else if(eLevel == SENSOR_LEVEL_2)
		{
			GPIO_ResetBits(GPIOI, GPIO_Pin_5);
			GPIO_SetBits(GPIOI, GPIO_Pin_6);
		}
		else if(eLevel == SENSOR_LEVEL_3)
		{
			GPIO_SetBits(GPIOI, GPIO_Pin_5);
			GPIO_SetBits(GPIOI, GPIO_Pin_6);
		}
		break;
    default:
        break;
	}
}

/*
adcType == 0
RESET, RESET, RESET
adcType == 1
RESET, RESET, SET
adcType == 2
RESET, SET, RESET
adcType == 3 -> (3 - 3) = 0
RESET, RESET, RESET
adcType == 4 -> (4 - 3) = 1
RESET, RESET, SET
adcType == 5 -> (5 - 3) = 2
RESET, SET, RESET
adcType == 6 -> (6 - 3) = 3
RESET, SET, SET
adcType == 7 -> (7 - 3) = 4
SET, RESET, RESET
adcType == 8 -> (8 - 3) = 5
SET, RESET, SET
adcType == 9 -> (9 - 3) = 6
SET, SET, RESET
*/
void EngHAL_Sensor_SelectADC(TSensorName eSensorName)
{
    TSensor* pstSensor = EngDrv_IF_GetSensor(eSensorName);

	switch(eSensorName)
	{
        case SENSOR_NAME_RJB_RAINS:
        case SENSOR_NAME_RJB_RBINS:
        case SENSOR_NAME_RJB_RCINS:
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_3, GPIOC, GPIO_Pin_2, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_3, GPIOC, GPIO_Pin_3, TRUE);
            break;
        case SENSOR_NAME_RJB_RBFNS:
        case SENSOR_NAME_RJB_RBENS:
        case SENSOR_NAME_RJB_RCFNS:
        case SENSOR_NAME_RJB_RAFNS:
        case SENSOR_NAME_RJB_RDANS:
        case SENSOR_NAME_RJB_RAENS:
        case SENSOR_NAME_RJB_RCENS:
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_3, GPIOC, GPIO_Pin_2, TRUE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_3, GPIOC, GPIO_Pin_3, FALSE);
            break;
        default:
            return;
	}

    DelayNOP(200*2);

    switch(eSensorName)
	{
        case SENSOR_NAME_RJB_RAINS: //0
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, FALSE);
            break;
        case SENSOR_NAME_RJB_RBINS: //1
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, TRUE);
            break;
        case SENSOR_NAME_RJB_RCINS: //2
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, TRUE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, FALSE);
            break;
        case SENSOR_NAME_RJB_RAENS: //3
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, FALSE);
            break;
        case SENSOR_NAME_RJB_RBENS: //4
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, TRUE);
            break;
        case SENSOR_NAME_RJB_RDANS: //5
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, TRUE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, FALSE);
            break;
        case SENSOR_NAME_RJB_RCENS: //6
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, TRUE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, TRUE);
            break;
        case SENSOR_NAME_RJB_RAFNS: //7
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, TRUE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, FALSE);
            break;
        case SENSOR_NAME_RJB_RBFNS: //8
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, TRUE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, FALSE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, TRUE);
            break;
        case SENSOR_NAME_RJB_RCFNS: //9
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_2, TRUE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_1, TRUE);
            EngHAL_Sensor_PortControl(HAL_LRJB_ADDRESS_TYPE_4, GPIOC, GPIO_Pin_0, FALSE);
            break;
        default:
            break;
    }
}

U16 EngHAL_Sensor_GetADCValue(TADCType eType)
{
    U16 uwRet;
	OS_ERR err;
	CPU_TS ts;

	OSMutexPend(&osmMutexADC, 0, OS_OPT_PEND_BLOCKING, &ts,&err);
	
	DelayUS(200);

	switch(eType)
	{
	case eADC_TYPE_24V_ADC:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_28Cycles);
		break;
	case eADC_TYPE_RJB_ADC:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_28Cycles);
		break;
	case eADC_DIVERTER_RANGD:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_28Cycles);
		break;
	case eADC_DIVERTER_RBNGD:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_28Cycles);
		break;
	case eADC_TYPE_RJP_RANPS:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_28Cycles);
		break;
	case eADC_TYPE_RJP_RBNPS:
		ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_28Cycles);
		break;
	}

	DelayUS(200);

	ADC_SoftwareStartConv(ADC1);
	
    while(ADC_GetSoftwareStartConvStatus(ADC1))
	{
		OSTimeDly(1*2, OS_OPT_TIME_DLY, &g_errDelay);
	}
	
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);

	DelayUS(200);

	uwRet = ADC_GetConversionValue(ADC1);

	OSMutexPost(&osmMutexADC, OS_OPT_POST_NONE, &err);

	return (uwRet >> 2);	
}

U8 EngHAL_Sensor_ReadFromDataBus(TSensorReadDataBus eReadDataNum)
{
	U8 ubData = 0;
	
	switch(eReadDataNum)
	{
		case SENSOR_READ_BUS_1:
			GPIO_ResetBits(GPIOD, GPIO_Pin_6);
			break;
		case SENSOR_READ_BUS_2:
			GPIO_ResetBits(GPIOC, GPIO_Pin_5);
			break;
		case SENSOR_READ_BUS_3:
			GPIO_ResetBits(GPIOG, GPIO_Pin_11);
			break;
		case SENSOR_READ_BUS_4:
			GPIO_ResetBits(GPIOH, GPIO_Pin_10);
			break;
		default:
			ubData = 0;
			break;
	}

	DelayUS(1);

	ubData  =  GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0);
	ubData |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1) << 1);
	ubData |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2) << 2);
	ubData |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3) << 3);
	ubData |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4) << 4);
	ubData |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5) << 5);
	ubData |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_12) << 6);
	ubData |= (GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13) << 7);

	switch(eReadDataNum)
	{
		case SENSOR_READ_BUS_1:
			GPIO_SetBits(GPIOD, GPIO_Pin_6);
			break;
		case SENSOR_READ_BUS_2:
			GPIO_SetBits(GPIOC, GPIO_Pin_5);
			break;
		case SENSOR_READ_BUS_3:
			GPIO_SetBits(GPIOG, GPIO_Pin_11);
			break;
		case SENSOR_READ_BUS_4:
			GPIO_SetBits(GPIOH, GPIO_Pin_10);
			break;
		default:
			ubData = 0;
			break;
	}

	return ubData;
}