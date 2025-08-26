/**
 * @file        EngIFSvc_Main.c
 * @brief       This is main code for Engine IF Service Component.
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

#define	__ENGIFSVC_MAIN_C__

#include "Eng_CommonType.h"
#include "EngIFSvc_Main.h"


static TRecvCommand s_stRecvCommand;	/**< engine command */


BOOL EngIFSvc_Initialize(void)
{
    s_stRecvCommand.pubName = NULL;
    s_stRecvCommand.ubId = 0;
    for(U8 i = 0; i < 7; i++)
    {
        s_stRecvCommand.pubParam[i];
    }
}


void EngIFSvc_ProcessCommand(TRecvCommand* pstCommand)
{
    if(pstCommand == NULL)
        return;

    switch(pstCommand->ubId)
    {
        case 0x81: // Start Motor
            //EngFOC_IF_StartMotor();
            break;
        case 0x82: // Stop Motor
            //EngFOC_IF_StopMotor();
            break;
        case 0x83: // Torque Control
            //EngFOC_IF_TorqueControl(torque, duration);
            break;
        case 0x84: // Speed Control
            //EngFOC_IF_SpeedControl(speed, duration);
            break;
        case 0x85: // Position Control
            //EngFOC_IF_PositionControl(position, duration);
            break;
        case 0x86: // Stop Control
            //EngFOC_IF_StopControl();
            break;
        case 0x91: // Set Parameter
            //EngFOC_IF_SetParameter(paramId, paramValue);
            break;
        case 0x92: // Get Parameter
            //EngFOC_IF_GetParameter(paramId);
            break;
        case 0x93: // Reset Parameter
            //EngFOC_IF_ResetParameter(paramId);
            break;
        case 0x94: // Set Parameter as Default
            //EngFOC_IF_SetParameterAsDefault(paramId, paramValue);
            break;
        case 0xA1: // Request Torque Value
            //EngFOC_IF_GetTorque();
            break;
        case 0xA2: // Request Speed Value
            //EngFOC_IF_GetSpeed();
            break;
        case 0xA3: // Request Position Value
            //EngFOC_IF_GetPosition();
            break;
        case 0xA4: // Request PST(Pos/Spd/Tor) Value
            //EngFOC_IF_GetPST();
            break;
        default:
            break;
    }
}


void EngIFSvc_ReceiveCommand(U8 *pubData, U16 uwLength)
{
    if(pubData == NULL || uwLength == 0)
        return;

    s_stRecvCommand.ubId = pubData[0];
    for(U8 i = 1; i < 8; i++)
    {
        s_stRecvCommand.pubParam[i];
    }

    EngIFSvc_ProcessCommand(&s_stRecvCommand);
}



