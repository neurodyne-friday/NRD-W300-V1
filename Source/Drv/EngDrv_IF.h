/**
 * @file        EngDrv_IF.h
 * @brief       This is interface file for drivers
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
 * @date		21/02/2024(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGDRV_IF_H__
#define __ENGDRV_IF_H__

#undef EXTERN
#ifdef __ENGDRV_IF_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"
#include "EngHAL_Types.h"

EXTERN void EngDrv_IF_Create();         // #1
EXTERN void EngDrv_IF_Configuration();  // #2
EXTERN void EngDrv_IF_Initialize();     // #3

EXTERN void *EngDrv_IF_GetDevice(U32 ulDeviceKey);
EXTERN TCAN *EngDrv_IF_GetCAN(U32 ulDeviceKey);
EXTERN TETH *EngDrv_IF_GetETH(U32 ulDeviceKey);
EXTERN TSensor *EngDrv_IF_GetSensor(U32 ulDeviceKey);
EXTERN TMotor *EngDrv_IF_GetMotor(U32 ulDeviceKey);
EXTERN TADC *EngDrv_IF_GetADC(U32 ulDeviceKey);
EXTERN TSolenoid *EngDrv_IF_GetSolenoid(U32 ulDeviceKey);
EXTERN TEncoder *EngDrv_IF_GetEncoder(U32 ulDeviceKey);
EXTERN TEeprom *EngDrv_IF_GetEeprom(U32 ulDeviceKey);
EXTERN TSPI* EngDrv_IF_GetSPI(U32 ulDeviceKey);
EXTERN TUART* EngDrv_IF_GetUART(U32 ulDeviceKey);

EXTERN TCAN *EngDrv_IF_FindCANByHalName(U32 ulHalName);


#endif /* __ENGDRV_IF_H__ */
