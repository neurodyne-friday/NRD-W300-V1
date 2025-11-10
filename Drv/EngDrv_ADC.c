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
//#include "EngDrv_Sensor.h"
#include "EngDrv_IF.h"
#include "EngHAL_Lib.h"


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
}

void EngDrv_ADC_Initialize(TADC* pstADC)
{
    pstADC->uwADCValue = 0;
}


U16 EngDrv_ADC_GetValue(TADC* pstADC)
{
	return EngHAL_ADC_GetValue(pstADC->ulHalID);
}
