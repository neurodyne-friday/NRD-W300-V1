/**
 * @file        EngDrv_Encoder.h
 * @brief       This is type definition file for Encoder Driver
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

#ifndef __ENGDRV_ENCODER_H__
#define __ENGDRV_ENCODER_H__

#undef EXTERN
#ifdef __ENGDRV_ENCODER_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"


EXTERN void EngDrv_Encoder_Create(void);
EXTERN void EngDrv_Encoder_Initialize(TEncoder* pstEncoder);
EXTERN void EngDrv_Encoder_Set(TEncoder* pstEncoder, S32 slCount);
EXTERN S32 EngDrv_Encoder_Get(TEncoder* pstEncoder);
EXTERN void EngDrv_Encoder_Reset(TEncoder* pstEncoder);

EXTERN void EngDrv_Encoder_SERVO_RMDX_NotifiedByCAN(U32 ulDeviceKey, U8* pubData, U16 uwLength);



#endif //__ENGDRV_ENCODER_H__
