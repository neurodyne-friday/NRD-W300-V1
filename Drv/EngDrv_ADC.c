/**
 * @file        EngDrv_ADC.c
 * @brief       This is type definition file for ADC Driver
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

#define	__ENGDRV_ADC_C__

#include "EngCM_DriverConfig.h"
#include "EngDrv_ADC.h"
#include "EngDrv_Sensor.h"
#include "EngDrv_IF.h"

#if defined(STM32F4XX_SUPPORT)
	#include "EngHAL_ADC_STM32F4xx.h"
#elif defined(STM32F7XX_SUPPORT)
	#include "EngHAL_ADC_STM32F7xx.h"
#endif


void EngDrv_ADC_Create(void)
{
	TADC* pstInstance = NULL;
    U8 ubCount = sizeof(s_astDeviceADCTbl) / sizeof(TADC);

    for(U8 ubIndex = 0; ubIndex < ubCount; ubIndex++)
    {
        pstInstance = &s_astDeviceADCTbl[ubIndex];

        pstInstance->pfnInitialize = EngDrv_ADC_Initialize;
        pstInstance->pfnGetValue = EngDrv_ADC_GetValue;
    }

}

void EngDrv_ADC_Configuration(void)
{
	EngHAL_ADC_Init_F4xx(NULL); // should change EngHAL_ADC_Init() to eliminate dependency
}

void EngDrv_ADC_Initialize(TADC* pstADC)
{
    pstADC->ulADCValue = 0;
}


U32 EngDrv_ADC_GetValue(TADC* pstADC)
{
	pstADC->ulADCValue = EngHAL_ADC_GetValue(pstADC->ulDeviceKey);
	return pstADC->ulADCValue;
}

EXTERN U32 EngHAL_ADC_GetValue(U32 ulDeviceKey)
{
    TADC* pstADC = EngDrv_IF_GetADC(ulDeviceKey); // should make Hal Instance and use it later
    U32 ulAdcValue;

    //OSMutexPend(pstADC->pstOsMutex, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
	
	//SelectADC0(adcType);
    if(ulDeviceKey > ADC_NAME_LRJB_ADC)
    {
        EngHAL_ADC_SelChannel_LRJB(ulDeviceKey);
        // Change ADC driver instance to assign on ADC-pathing of LRJB
        pstADC = EngDrv_IF_GetADC(ADC_NAME_LRJB_ADC); 
    }

    EngHAL_ADC_SelChannel(ADC_NAME_LRJB_ADC);

	DelayUS(100);

    if(pstADC->eChannel == ADC_CHANNEL_0)
    {
        DelayUS(100);
        ADC_SoftwareStartConv(ADC1);

        while(ADC_GetSoftwareStartConvStatus(ADC1))
        {
        }

        ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
        DelayUS(100);
        ulAdcValue = ADC_GetConversionValue(ADC1);
    }
    else if(pstADC->eChannel == ADC_CHANNEL_1)
    {
        DelayUS(100);
        ADC_SoftwareStartConv(ADC2);

        while(ADC_GetSoftwareStartConvStatus(ADC2))
        {
        }

        ADC_ClearFlag(ADC2, ADC_FLAG_EOC);
        DelayUS(100);
        ulAdcValue = ADC_GetConversionValue(ADC2);
    }

	ulAdcValue = ulAdcValue >> 2; //240328-KHR : ADC Value 10bit -> 8bit

	//OSMutexPost(&osmADC1,	OS_OPT_POST_NONE, &err);
    //OSMutexPost(pstADC->pstOsMutex, OS_OPT_POST_NONE, &err);

	return ulAdcValue;
}

void EngHAL_ADC_SelChannel(U32 ulDeviceKey)
{
    TADC* pstADC = EngDrv_IF_GetADC(ulDeviceKey); // should make Hal Instance and use it later
    
    if(pstADC->eChannel == ADC_CHANNEL_0)
    {
        GPIO_SetBits(GPIOC, GPIO_PIN_7);
        EngHAL_ADC_SelMuxAddr(ulDeviceKey);
        GPIO_ResetBits(GPIOC, GPIO_PIN_6);
    }
    else if(pstADC->eChannel == ADC_CHANNEL_1)
    {
        GPIO_SetBits(GPIOC, GPIO_PIN_6);
        EngHAL_ADC_SelMuxAddr(ulDeviceKey);
        GPIO_ResetBits(GPIOC, GPIO_PIN_7);
    }
}

void EngHAL_ADC_SelChannel_LRJB(U32 ulDeviceKey)
{
    switch(ulDeviceKey)
    {
        case ADC_NAME_RAINS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RAINS);
            break;
        case ADC_NAME_RBINS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RBINS);
            break;
        case ADC_NAME_RCINS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RCINS);
            break;
        case ADC_NAME_RBFNS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RBFNS);
            break;
        case ADC_NAME_RBENS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RBENS);
            break;
        case ADC_NAME_RCFNS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RCFNS);
            break;
        case ADC_NAME_RCENS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RCENS);
            break;
        case ADC_NAME_RDANS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RDANS);
            break;
        case ADC_NAME_RAFNS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RAFNS);
            break;
        case ADC_NAME_RAENS:
            EngHAL_Sensor_SelectADC(SENSOR_NAME_RJB_RAENS);
            break;
        default:
            break;
    }
}

void EngHAL_ADC_SelMuxAddr(U32 ulDeviceKey)
{
    TADC* pstADC = EngDrv_IF_GetADC(ulDeviceKey); // should make Hal Instance and use it later

    if((pstADC->eMuxAddr >> 2) & 0x01)
        GPIO_SetBits(GPIOC, GPIO_PIN_1);
    else
        GPIO_ResetBits(GPIOC, GPIO_PIN_1);

    if((pstADC->eMuxAddr >> 1) & 0x01)
        GPIO_SetBits(GPIOC, GPIO_PIN_14);
    else
        GPIO_ResetBits(GPIOC, GPIO_PIN_14);

    if((pstADC->eMuxAddr >> 0) & 0x01)
        GPIO_SetBits(GPIOC, GPIO_PIN_13);
    else
        GPIO_ResetBits(GPIOC, GPIO_PIN_13);
}

