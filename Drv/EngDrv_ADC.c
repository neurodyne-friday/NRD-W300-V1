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
    ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	GPIO_InitTypeDef      GPIO_InitStructure;

	/**********************************************************************/
	/*                       ADC Port Initialize                          */
	/**********************************************************************/
	//
	// PA4 : ADC1_IN4 (ADC0)
	//		Bit 7 (RANGD_ADN)
	//		Bit 6 (RBNGD_ADN)
	//		Bit 5 
	//		Bit 4 
	//		Bit 3 
	//		Bit 2 (LRJB_ADC)
	//		Bit 1 (LRJB_SSEN_R1), RBNPS ADC
	//		Bit 0 (LRJB_SSEN_R0), RANPS ADC
	// PA2 : ADC2_IN2 (ADC1)
	//		Bit 7 (ML_FLNIS_ADC)
	//		Bit 6 (ML_FLNOS_ADC)
	//		Bit 5 (ML_FENDS_RX)
	//		Bit 4 (ML_FDNDS_RX)
	//		Bit 3 (ML_FCNDS_RX)
	//		Bit 2 (ML_FBNDS_RX)
	//		Bit 1 (ML_FANDS_RX)
	//		Bit 0 
	//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//
	// ADC1
	//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_28Cycles);
	ADC_Cmd(ADC1, ENABLE);

	//
	// ADC2
	//
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC2, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime_28Cycles);
	ADC_Cmd(ADC2, ENABLE);


	/**********************************************************************/
	/*                       ADC Select Initialize                        */
	/**********************************************************************/
	// Enable GPIO clock 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

	//
	// GPIOC Pin 1	: ADC_SEL2
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//
	// GPIOG Pin 13	: ADC_SEL0
	// GPIOG Pin 14	: ADC_SEL1
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	//
	// 20240313 YJH : ADC ENABLE PIN Ãß°¡
	//
	/**********************************************************************/
	/*                       ADC Enable Initialize                          */
	/**********************************************************************/
	// Enable GPIO clock 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	//
	// GPIOC Pin 6	: ADC0_ENABLE
	// GPIOC Pin 7  : ADC1_EANBLE
	//
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//
	// Create Mutex
	//
	OS_ERR err;
	
	OSMutexCreate(&g_osmADC0, "ADC1 Mutex", &err);
	OSMutexCreate(&g_osmADC1, "ADC2 Mutex", &err);
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
	OS_ERR err;
	CPU_TS ts;

	//OSMutexPend(&osmADC1, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
    OSMutexPend(pstADC->pstOsMutex, 0, OS_OPT_PEND_BLOCKING, &ts, &err);
	
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
	    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_28Cycles);
        DelayUS(100);
        ADC_SoftwareStartConv(ADC1);

        while(ADC_GetSoftwareStartConvStatus(ADC1))
        {
            OSTimeDly(1u, OS_OPT_TIME_DLY, &g_errDelay);
        }

        ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
        DelayUS(100);
        ulAdcValue = ADC_GetConversionValue(ADC1);
    }
    else if(pstADC->eChannel == ADC_CHANNEL_1)
    {
        ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime_28Cycles);
        DelayUS(100);
        ADC_SoftwareStartConv(ADC2);

        while(ADC_GetSoftwareStartConvStatus(ADC2))
        {
            OSTimeDly(1u, OS_OPT_TIME_DLY, &g_errDelay);
        }

        ADC_ClearFlag(ADC2, ADC_FLAG_EOC);
        DelayUS(100);
        ulAdcValue = ADC_GetConversionValue(ADC2);
    }

	ulAdcValue = ulAdcValue >> 2; //240328-KHR : ADC Value 10bit -> 8bit

	//OSMutexPost(&osmADC1,	OS_OPT_POST_NONE, &err);
    OSMutexPost(pstADC->pstOsMutex, OS_OPT_POST_NONE, &err);

	return ulAdcValue;
}

void EngHAL_ADC_SelChannel(U32 ulDeviceKey)
{
    TADC* pstADC = EngDrv_IF_GetADC(ulDeviceKey); // should make Hal Instance and use it later
    
    if(pstADC->eChannel == ADC_CHANNEL_0)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_7);
        EngHAL_ADC_SelMuxAddr(ulDeviceKey);
        GPIO_ResetBits(GPIOC, GPIO_Pin_6);
    }
    else if(pstADC->eChannel == ADC_CHANNEL_1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_6);
        EngHAL_ADC_SelMuxAddr(ulDeviceKey);
        GPIO_ResetBits(GPIOC, GPIO_Pin_7);
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
        GPIO_SetBits(GPIOC, GPIO_Pin_1);
    else
        GPIO_ResetBits(GPIOC, GPIO_Pin_1);

    if((pstADC->eMuxAddr >> 1) & 0x01)
        GPIO_SetBits(GPIOC, GPIO_Pin_14);
    else
        GPIO_ResetBits(GPIOC, GPIO_Pin_14);

    if((pstADC->eMuxAddr >> 0) & 0x01)
        GPIO_SetBits(GPIOC, GPIO_Pin_13);
    else
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

