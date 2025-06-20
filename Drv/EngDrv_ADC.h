/**
 * @file        EngDrv_ADC.h
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

#ifndef __ENGDRV_ADC_H__
#define __ENGDRV_ADC_H__

#undef EXTERN
#ifdef __ENGDRV_ADC_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"
#include <EngDrv_IF.h>

EXTERN void EngDrv_ADC_Create(void);
EXTERN void EngDrv_ADC_Configuration(void);
EXTERN void EngDrv_ADC_Initialize(TADC* pstADC);
EXTERN U32 EngDrv_ADC_GetValue(TADC* pstADC);

EXTERN U32 EngHAL_ADC_GetValue(U32 ulDeviceDey);
EXTERN void EngHAL_ADC_SelChannel(U32 ulDeviceDey);
EXTERN void EngHAL_ADC_SelChannel_LRJB(U32 ulDeviceKey);
EXTERN void EngHAL_ADC_SelMuxAddr(U32 ulDeviceDey);


#endif//__ENGDRV_CAN_H__