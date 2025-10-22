/**
 * @file        EngFOC_IF.c
 * @brief       This is I/F code for FOC(Field Oriented Control) Component.
 *
 * <b> Copyright 2024 by Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		03/11/2008(D/M/Y)
 * @version		V0.1
 */

#define	__ENGFOC_IF_C__

#include "Eng_CommonType.h"
#include "EngFOC_IF.h"
#include "EngFOC_Main.h"



BOOL EngFOC_IF_Initialize(void)
{
    return EngFOC_Initialize();
}

void EngFOC_IF_SetState(TEngState eNewState)
{
    EngFOC_SetState(eNewState);
}

TEngState EngFOC_IF_GetState(void)
{
    return EngFOC_GetState();
}

/**
 * command interface with FOC component 
*/

BOOL EngFOC_IF_StartMotor(void)
{
    return TRUE;
}

BOOL EngFOC_IF_StopMotor(void)
{
    return TRUE;
}

BOOL EngFOC_IF_TorqueControl(F32 fTorque, U32 ulDuration)
{
    return TRUE;
}

BOOL EngFOC_IF_SpeedControl(F32 fSpeed, U32 ulDuration)
{
    return TRUE;
}

BOOL EngFOC_IF_PositionControl(F32 fPosition, U32 ulDuration)
{
    return TRUE;
}

BOOL EngFOC_IF_StopControl(void)
{
    return TRUE;
}

BOOL EngFOC_IF_SetParameter(U32 ulParamID, U32 ulValue)
{
    return TRUE;
}

U32 EngFOC_IF_GetParameter(U32 ulParamID)
{
    return 0;
}

BOOL EngFOC_IF_ResetParameter(U32 ulParamID)
{
    return TRUE;
}

BOOL EngFOC_IF_SetParameterAsDefault(U32 ulParamID, U32 ulValue)
{
    return TRUE;
}

F32 EngFOC_IF_GetTorque(void)
{
    return 0.0f;
}

F32 EngFOC_IF_GetSpeed(void)
{
    return 0.0f;
}

F32 EngFOC_IF_GetPosition(void)
{
    return 0.0f;
}

void EngFOC_IF_NotifyByADCIRQ(U8* pubData, U32 ulLength)
{
    EngFOC_NotifyByADCIRQ(pubData, ulLength);
}