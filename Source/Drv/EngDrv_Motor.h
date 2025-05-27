/**
 * @file        EngDrv_Motor.h
 * @brief       This is type definition file for Motor Driver
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

#ifndef __ENGDRV_MOTOR_H__
#define __ENGDRV_MOTOR_H__

#undef EXTERN
#ifdef __ENGDRV_MOTOR_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"

EXTERN void EngDrv_Motor_Create(void);
EXTERN void EngDrv_Motor_Initialize(TMotor* pstMotor);

EXTERN void EngDrv_Motor_STEP_SetEnable(TMotor* pstMotor, BOOL bValue, BOOL bActiveLow);
EXTERN void EngDrv_Motor_STEP_SetDirection(TMotor* pstMotor, BOOL bValue);
EXTERN void EngDrv_Motor_STEP_SetHold(TMotor* pstMotor, BOOL bValue, BOOL bActiveLow);
EXTERN void EngDrv_Motor_STEP_SetPulse(TMotor* pstMotor, BOOL bValue);
EXTERN void EngDrv_Motor_STEP_Stop(TMotor* pstMotor, BOOL bHoldStop, BOOL bActiveLow);

EXTERN void EngDrv_Motor_BLDC_SetEnable(TMotor* pstMotor, U8 ubEnable);
EXTERN void EngDrv_Motor_BLDC_Stop(TMotor* pstMotor);
EXTERN void EngDrv_Motor_BLDC_Off(TMotor* pstMotor);
EXTERN void EngDrv_Motor_BLDC_SetDirection(TMotor* pstMotor, U8 ubDirection);
EXTERN void EngDrv_Motor_BLDC_SetBrake(TMotor* pstMotor, U8 ubBrake);
EXTERN void EngDrv_Motor_BLDC_SetSpeed(TMotor* pstMotor, U16 uwValue);
EXTERN U32 EngDrv_Motor_BLDC_GetWheelCount(TMotor* pstMotor);
EXTERN void EngDrv_Motor_BLDC_SetWheelCount(TMotor* pstMotor, U32 ulValue);

EXTERN void EngDrv_Motor_SERVO_RMDX_NotifiedByCAN(U32 ulDeviceKey, U8* pubData, U16 uwLength);
EXTERN void EngDrv_Motor_SERVO_RMDX_Enable(TMotor* pstMotor);
EXTERN void EngDrv_Motor_SERVO_RMDX_Stop(TMotor* pstMotor);
EXTERN void EngDrv_Motor_SERVO_RMDX_SetPosition(TMotor* pstMotor, S32 slPosition);
EXTERN void EngDrv_Motor_SERVO_RMDX_SetVelocity(TMotor* pstMotor, S32 slVelocity);
EXTERN void EngDrv_Motor_SERVO_RMDX_Shutdown(TMotor* pstMotor);
EXTERN void EngDrv_Motor_SERVO_RMDX_SetID(TMotor* pstMotor, U16 uwID);


#endif //__ENGDRV_MOTOR_H__