/**
 * @file        EngDrv_Motor.c
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

#define	__ENGDRV_MOTOR_C__

#include "EngDrv_IF.h"
#include "EngDrv_Motor.h"
#include "EngDrv_SPI.h"
#include "EngCM_DriverConfig.h"

void EngDrv_Motor_ControlTask(void *p_arg)
{
	(void)p_arg;
    TMotor* pstMotor = NULL;

	while(1)
	{
        for(U32 ulDeviceKey = DEVICE_MOTOR_KEY_BASE; ulDeviceKey < MOTOR_NAME_MAX; ulDeviceKey++)
        {
            pstMotor = EngDrv_IF_GetMotor(ulDeviceKey);
            if(pstMotor->enType == MOTOR_TYPE_BLDC)
            {
		        EngDrv_Motor_BLDC_AdjustSpeed(pstMotor);
            }
        }
	}
}

void EngDrv_Motor_Create(void)
{
    TMotor* pstInstance = NULL;
    U8 ubCount = sizeof(s_astDeviceMotorTbl) / sizeof(TMotor);

    for(U32 ubIndex = 0; ubIndex < ubCount; ubIndex++)
    {
        pstInstance = &s_astDeviceMotorTbl[ubIndex];

        pstInstance->pfnInitialize = EngDrv_Motor_Initialize;
        /* STEP Interfaces */
        pstInstance->pfnSTEPSetEnable = EngDrv_Motor_STEP_SetEnable;
        pstInstance->pfnSTEPSetDirection = EngDrv_Motor_STEP_SetDirection;
        pstInstance->pfnSTEPSetHold = EngDrv_Motor_STEP_SetHold;
        pstInstance->pfnSTEPSetPulse = EngDrv_Motor_STEP_SetPulse;
        /* BLDC Interfaces */
        pstInstance->pfnBLDCSetEnable = EngDrv_Motor_BLDC_SetEnable;
        pstInstance->pfnBLDCStop = EngDrv_Motor_BLDC_Stop;
        pstInstance->pfnBLDCOff = EngDrv_Motor_BLDC_Off;
        pstInstance->pfnBLDCSetDirection = EngDrv_Motor_BLDC_SetDirection;
        pstInstance->pfnBLDCSetBrake = EngDrv_Motor_BLDC_SetBrake;
        pstInstance->pfnBLDCSetSpeed = EngDrv_Motor_BLDC_SetSpeed;
        pstInstance->pfnBLDCGetWheelCount = EngDrv_Motor_BLDC_GetWheelCount;
        pstInstance->pfnBLDCSetWheelCount = EngDrv_Motor_BLDC_SetWheelCount;
        /* Servo-RMDX Interfaces */
        pstInstance->pfnNotifiedByCAN = EngDrv_Motor_SERVO_RMDX_NotifiedByCAN;
    }
}

void EngDrv_Motor_Initialize(TMotor* pstMotor)
{
    TCAN* pstCAN = NULL;

    if(pstMotor->enType == MOTOR_TYPE_STEP)
    {
        pstMotor->pfnSTEPSetEnable(pstMotor, FALSE, TRUE);
        pstMotor->pfnSTEPSetDirection(pstMotor, MOTOR_DIR_FORWARD);
        pstMotor->pfnSTEPSetHold(pstMotor, TRUE, TRUE);

        pstMotor->ubMakePulse = FALSE;
        pstMotor->ubActOption = 0x0F;
        pstMotor->uwStepCount = 0;
    }
    else if(pstMotor->enType == MOTOR_TYPE_BLDC)
    {
#if defined (BOOT_LOADER)  //#ifdef BOOT_LOADER
        pstMotor->pfnBLDCSetEnable(pstMotor, FALSE);
        pstMotor->pfnBLDCSetDirection(pstMotor, MOTOR_DIR_BACKWARD);
        pstMotor->pfnBLDCSetBrake(pstMotor, FALSE);
#else

        pstMotor->pfnBLDCSetBrake(pstMotor, TRUE);
        pstMotor->pfnBLDCSetEnable(pstMotor, TRUE);

        pstMotor->pfnBLDCSetEnable(pstMotor, FALSE);
        pstMotor->pfnBLDCSetDirection(pstMotor, MOTOR_DIR_BACKWARD);
        pstMotor->pfnBLDCSetBrake(pstMotor, FALSE);

#endif
    }
    else if(pstMotor->enType == MOTOR_TYPE_SERVO_RMDX)
    {
        pstCAN = EngDrv_IF_GetCAN(pstMotor->ulCANDeviceKey);
        if(pstCAN)
        {
            pstMotor->stCANObserver.ulDeviceKey = pstMotor->ulDeviceKey;
            pstMotor->stCANObserver.pfnNotify = EngDrv_Motor_SERVO_RMDX_NotifiedByCAN;

            pstCAN->pfnAppendObserver(pstCAN, &pstMotor->stCANObserver);
        }
    }
    else if(pstMotor->enType == MOTOR_TYPE_SERVO_DYNAMIXEL)
    {

    }
}

U32 EngDrv_Motor_Control(TMotor *pstMotor, U32 ulControlCode, void *pvControlPtr)
{
    TMotorCtrlParameter *pstMotorCtrlParam = NULL;
    TMotorState enState = pstMotor->ulState;
    U32 ulVelocity = 0;

    switch(ulControlCode)
    {
        case MOTOR_CTRL_START:
            if((enState == MOTOR_ST_STOP) || (enState == MOTOR_ST_HOLD))
            {
                /* Check Start Motor Error */

                /* Motor Direction */

                /* Motor Mode Change */
            }
            break;
    }
}

void EngDrv_Motor_STEP_SetEnable(TMotor* pstMotor, BOOL bValue, BOOL bActiveLow)
{
    TMotorStepCtrlHalInfo* pstInfo = pstMotor->pstStepCtrlHalParam;
    
    if(bValue == TRUE)
    {
    }
    else
    {
    }
}


void EngDrv_Motor_STEP_SetDirection(TMotor* pstMotor, BOOL bValue)
{
    TMotorStepCtrlHalInfo* pstInfo = pstMotor->pstStepCtrlHalParam;

}

void EngDrv_Motor_STEP_SetHold(TMotor* pstMotor, BOOL bValue, BOOL bActiveLow)
{
    TMotorStepCtrlHalInfo* pstInfo = pstMotor->pstStepCtrlHalParam;

    if(bValue == TRUE)
    {
    }
    else
    {
    }
}

void EngDrv_Motor_STEP_SetPulse(TMotor* pstMotor, BOOL bValue)
{
    TMotorStepCtrlHalInfo* pstInfo = pstMotor->pstStepCtrlHalParam;
}

void EngDrv_Motor_STEP_Stop(TMotor* pstMotor, BOOL bHoldStop, BOOL bActiveLow)
{
   	if(bHoldStop == TRUE)
	{
		pstMotor->pfnSTEPSetEnable(pstMotor, TRUE, bActiveLow);
		pstMotor->pfnSTEPSetHold(pstMotor, bHoldStop, bActiveLow);
    }
    else
    {
        pstMotor->pfnSTEPSetEnable(pstMotor, FALSE, bActiveLow);
        pstMotor->pfnSTEPSetHold(pstMotor, bHoldStop, bActiveLow);
	}
}

void EngDrv_Motor_BLDC_SetEnable(TMotor* pstMotor, U8 ubEnable)
{
    if(pstMotor != NULL && pstMotor->enType == MOTOR_TYPE_BLDC)
    {
        switch(pstMotor->ulDeviceKey)
        {
            default:
                break;
        }

        pstMotor->bEnable = ubEnable ? TRUE : FALSE;
    }
}

void EngDrv_Motor_BLDC_Stop(TMotor* pstMotor)
{
    if(pstMotor != NULL && pstMotor->enType == MOTOR_TYPE_BLDC)
    {
        pstMotor->uwTargetSpeed = 0;

        //Break enable
        EngDrv_Motor_BLDC_SetBrake(pstMotor, TRUE);

        //BLDC Disable
        EngDrv_Motor_BLDC_SetEnable(pstMotor, FALSE);
        EngDrv_Motor_BLDC_SetDirection(pstMotor, MOTOR_DIR_BACKWARD);
    }
}

void EngDrv_Motor_BLDC_Off(TMotor* pstMotor)
{
    if(pstMotor != NULL && pstMotor->enType == MOTOR_TYPE_BLDC)
    {
        pstMotor->uwTargetSpeed = 0;

        //BLDC Disable
        EngDrv_Motor_BLDC_SetEnable(pstMotor, FALSE);

        //Break disable
        EngDrv_Motor_BLDC_SetBrake(pstMotor, FALSE);
        EngDrv_Motor_BLDC_SetDirection(pstMotor, MOTOR_DIR_BACKWARD);
    }
}

void EngDrv_Motor_BLDC_SetDirection(TMotor* pstMotor, U8 ubDirection)
{
    if(pstMotor != NULL && pstMotor->enType == MOTOR_TYPE_BLDC)
    {
        TMotorBLDCCtrlHalInfo* pstHalInfo = pstMotor->pstBLDCCtrlHalParam;

        pstMotor->bDir = ubDirection ? TRUE : FALSE;
    }
}

void EngDrv_Motor_BLDC_SetBrake(TMotor* pstMotor, U8 ubBrake)
{
    if(pstMotor != NULL && pstMotor->enType == MOTOR_TYPE_BLDC)
    {
        TMotorBLDCCtrlHalInfo* pstHalInfo = pstMotor->pstBLDCCtrlHalParam;

        pstMotor->bStopMode = ubBrake ? TRUE : FALSE;
    }
}


void EngDrv_Motor_BLDC_SetSpeed(TMotor* pstMotor, U16 uwValue)
{
    TSPI* pstSPI = NULL;
    TMotorBLDCCtrlHalInfo* pstHalInfo = NULL;
	U8 ubByte0 = 0x00;
	U8 ubByte1 = 0x00;
	U8 ubByte2 = 0x00;

    if(pstMotor != NULL && pstMotor->enType == MOTOR_TYPE_BLDC)
    {
        pstHalInfo = pstMotor->pstBLDCCtrlHalParam;
        pstSPI = EngDrv_IF_GetSPI(pstHalInfo->ulSPIDeviceKey);

        pstMotor->fVelocity = (F32)uwValue;

        //EngDrv_SPI_WriteRegister(pstSPI, ubByte0, ubByte1, ubByte2);
    }
}

U32 EngDrv_Motor_BLDC_GetWheelCount(TMotor* pstMotor)
{
    if(pstMotor != NULL && pstMotor->enType == MOTOR_TYPE_BLDC)
    {
        return pstMotor->ulCurWheelCount;
    }

    return 0;
}

void EngDrv_Motor_BLDC_SetWheelCount(TMotor* pstMotor, U32 ulValue)
{
    if(pstMotor != NULL && pstMotor->enType == MOTOR_TYPE_BLDC)
    {
        pstMotor->ulCurWheelCount = ulValue;
    }
}


void EngDrv_Motor_SERVO_RMDX_NotifiedByCAN(U32 ulDeviceKey, U8* pubData, U16 uwLength)
{
    TMotor* pstMotor = NULL;
    pstMotor = EngDrv_IF_GetMotor(ulDeviceKey);

    if(pstMotor)
    {
        // parsing can rx data
    }
}

void EngDrv_Motor_SERVO_RMDX_Enable(TMotor* pstMotor)
{

}

void EngDrv_Motor_SERVO_RMDX_Stop(TMotor* pstMotor)
{
    TCAN *pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
    U8 pubCommand[8] = {0, };

    pubCommand[0] = 0x81;

    pstCAN->pfnSendData(pstCAN, &pubCommand, 8);
}

void EngDrv_Motor_SERVO_RMDX_SetPosition(TMotor* pstMotor, S32 slPosition)
{
    TCAN *pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
    U8 pubCommand[8] = {0, };

    slPosition = MIN(slPosition, MOTOR_SERVO_RMDX_POS_LIMIT);
    slPosition = MAX(slPosition, -MOTOR_SERVO_RMDX_POS_LIMIT);

    pubCommand[0] = 0xA4;
    pubCommand[4] = (U8)(slPosition >> 24) & 0xFF;
    pubCommand[5] = (U8)(slPosition >> 16) & 0xFF;
    pubCommand[6] = (U8)(slPosition >> 8) & 0xFF;
    pubCommand[7] = (U8)(slPosition >> 0) & 0xFF;

    pstCAN->pfnSendData(pstCAN, &pubCommand, 8);
}

void EngDrv_Motor_SERVO_RMDX_SetVelocity(TMotor* pstMotor, S32 slVelocity)
{
    TCAN *pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
    U8 pubCommand[8] = {0, };

    slVelocity = MIN(slVelocity, MOTOR_SERVO_RMDX_VEL_LIMIT);
    slVelocity = MAX(slVelocity, -MOTOR_SERVO_RMDX_VEL_LIMIT);

    pubCommand[0] = 0xA2;
    pubCommand[4] = (U8)(slVelocity >> 24) & 0xFF;
    pubCommand[5] = (U8)(slVelocity >> 16) & 0xFF;
    pubCommand[6] = (U8)(slVelocity >> 8) & 0xFF;
    pubCommand[7] = (U8)(slVelocity >> 0) & 0xFF;

    pstCAN->pfnSendData(pstCAN, &pubCommand, 8);
}

void EngDrv_Motor_SERVO_RMDX_Shutdown(TMotor* pstMotor)
{
    TCAN *pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
    U8 pubCommand[8] = {0, };

    pubCommand[0] = 0x80;

    pstCAN->pfnSendData(pstCAN, &pubCommand, 8);
}

void EngDrv_Motor_SERVO_RMDX_SetID(TMotor* pstMotor, U16 uwID)
{
    TCAN *pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
    U8 pubCommand[8] = {0, };

    pubCommand[0] = 0x79;
    pubCommand[1] = (U8)(uwID & 0xFF);

    pstCAN->pfnSendData(pstCAN, &pubCommand, 8);
}
