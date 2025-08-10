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

U32 EngHAL_ADC_GetValue(U32 ulDeviceKey)
{
    TADC* pstADC = EngDrv_IF_GetADC(ulDeviceKey); // should make Hal Instance and use it later
    U32 ulAdcValue = 0;

	return ulAdcValue;
}

void EngHAL_ADC_SelChannel(U32 ulDeviceKey)
{
    TADC* pstADC = EngDrv_IF_GetADC(ulDeviceKey); // should make Hal Instance and use it later
}
