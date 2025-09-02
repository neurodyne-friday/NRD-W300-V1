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
        pstInstance->pfnReadAngle = EngDrv_Encoder_ReadAngle;
        pstInstance->pfnReset = EngDrv_Encoder_Reset;
    } 
}

void EngDrv_Encoder_Initialize(TEncoder* pstEncoder)
{
    TCAN* pstCAN = NULL;

    if(pstEncoder->enType == ENCODER_TYPE_MAGNETIC)
    {

    }

}

void EngDrv_Encoder_Set(TEncoder* pstEncoder, S32 slCount)
{
    pstEncoder->slCounter = slCount;

    if(pstEncoder->enType == ENCODER_TYPE_MAGNETIC)
    {
        TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MAIN);
        U8 pubCommand[8] = {0, };

        pubCommand[0] = 0x63;
        pubCommand[4] = (U8)(slCount >> 24) & 0xFF;
        pubCommand[5] = (U8)(slCount >> 16) & 0xFF;
        pubCommand[6] = (U8)(slCount >> 8) & 0xFF;
        pubCommand[7] = (U8)(slCount >> 0) & 0xFF;

        pstCAN->pfnSendData(pstCAN, pubCommand, 8);
    }
}

F32 EngDrv_Encoder_ReadAngle(TEncoder* pstEncoder)
{
    U16 angle12 = 0;

    if(pstEncoder->enCommType == Encoder_CommType_I2C)
    {
        if (EngHAL_I2C_AS5600_ReadAngle12(pstEncoder->ulHalID, &angle12))
        {
            /* angle12를 0~360도로 변환(선택) */
            float deg = (angle12 * 360.0f) / 4096.0f;
            /* TODO: FOC 관측기나 속도 추정기에 연결 */
            pstEncoder->fAngle = deg;
        }
    }

    return pstEncoder->fAngle;
}

void EngDrv_Encoder_Reset(TEncoder* pstEncoder)
{
    if(pstEncoder->enType == ENCODER_TYPE_MAGNETIC)
    {
        TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MAIN);
        U8 pubCommand[8] = {0, };

        pubCommand[0] = 0x64; // Write the current multi-turn position of the encoder(ROM) as the motor zero offset

        pstCAN->pfnSendData(pstCAN, pubCommand, 8);
    }
}
