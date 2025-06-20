/**
 * @file        EngDrv_Encoder.c
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

#define	__ENGDRV_ENCODER_C__

#include "EngDrv_IF.h"
#include "EngDrv_Encoder.h"
#include "EngCM_DriverConfig.h"

void EngDrv_Encoder_Create(void)
{
    TEncoder* pstInstance = NULL;
    U8 ubCount = sizeof(s_astDeviceEncoderTbl) / sizeof(TEncoder);

    for(U8 ubIndex = 0; ubIndex < ubCount; ubIndex++)
    {
        pstInstance = &s_astDeviceEncoderTbl[ubIndex];

        pstInstance->pfnInitialize = EngDrv_Encoder_Initialize;
        pstInstance->pfnSet = EngDrv_Encoder_Set;
        pstInstance->pfnGet = EngDrv_Encoder_Get;
        pstInstance->pfnReset = EngDrv_Encoder_Reset;

        pstInstance->pfnNotifiedByCAN = EngDrv_Encoder_SERVO_RMDX_NotifiedByCAN;
    } 
}

void EngDrv_Encoder_Initialize(TEncoder* pstEncoder)
{
    TCAN* pstCAN = NULL;

    if(pstEncoder->enType == ENCODER_TYPE_SERVO_RMDX)
    {
        pstCAN = EngDrv_IF_GetCAN(pstEncoder->ulCANDeviceKey);
        if(pstCAN)
        {
            pstEncoder->stCANObserver.ulDeviceKey = pstEncoder->ulDeviceKey;
            pstEncoder->stCANObserver.pfnNotify = EngDrv_Encoder_SERVO_RMDX_NotifiedByCAN;

            pstCAN->pfnAppendObserver(pstCAN, &pstEncoder->stCANObserver);
        }
    }

}

void EngDrv_Encoder_Set(TEncoder* pstEncoder, S32 slCount)
{
    pstEncoder->slCounter = slCount;

    if(pstEncoder->enType == ENCODER_TYPE_SERVO_RMDX)
    {
        TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
        U8 pubCommand[8] = {0, };

        pubCommand[0] = 0x63;
        pubCommand[4] = (U8)(slCount >> 24) & 0xFF;
        pubCommand[5] = (U8)(slCount >> 16) & 0xFF;
        pubCommand[6] = (U8)(slCount >> 8) & 0xFF;
        pubCommand[7] = (U8)(slCount >> 0) & 0xFF;

        pstCAN->pfnSendData(pstCAN, &pubCommand, 8);
    }
}

S32 EngDrv_Encoder_Get(TEncoder* pstEncoder)
{
    if(pstEncoder->enType == ENCODER_TYPE_SERVO_RMDX)
    {
        TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
        U8 pubCommand[8] = {0, };

        pubCommand[0] = 0x60;

        pstCAN->pfnSendData(pstCAN, &pubCommand, 8);
    }

    return pstEncoder->slCounter;
}

void EngDrv_Encoder_Reset(TEncoder* pstEncoder)
{
    if(pstEncoder->enType == ENCODER_TYPE_SERVO_RMDX)
    {
        TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
        U8 pubCommand[8] = {0, };

        pubCommand[0] = 0x64; // Write the current multi-turn position of the encoder(ROM) as the motor zero offset

        pstCAN->pfnSendData(pstCAN, &pubCommand, 8);
    }
}

void EngDrv_Encoder_SERVO_RMDX_NotifiedByCAN(U32 ulDeviceKey, U8* pubData, U16 uwLength)
{
    TEncoder* pstEncoder = NULL;
    pstEncoder = EngDrv_IF_GetEncoder(ulDeviceKey);

    if(pstEncoder)
    {
        S32 slCount = 0;
        U32 ulEncoderOffset = 0;
        
        // parsing can rx data
        if(pubData[0] == 0x60) // Read multi-turn encoder position
        {
            slCount = pubData[4] << 24;
            slCount += pubData[5] << 16;
            slCount += pubData[6] << 8;
            slCount += pubData[7];
        }
        else if(pubData[0] == 0x61) // Read multi-turn encoder original position
        {
            slCount = pubData[4] << 24;
            slCount += pubData[5] << 16;
            slCount += pubData[6] << 8;
            slCount += pubData[7];
        }
        else if(pubData[0] == 0x62) // Read multi-turn zero offset data
        {
            ulEncoderOffset = pubData[4] << 24;
            ulEncoderOffset += pubData[5] << 16;
            ulEncoderOffset += pubData[6] << 8;
            ulEncoderOffset += pubData[7];
        }
        else if(pubData[0] == 0x90) // Read single-turn zero offset data
        {

        }
    }
}
