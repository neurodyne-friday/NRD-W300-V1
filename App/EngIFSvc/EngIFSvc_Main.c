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

    // Clear previous response
    for(U8 i = 0; i < 8; i++)
    {
        pstCommand->pubResponse[i] = 0;
    }

    switch(pstCommand->ubId)
    {
        case 0x81: // Start Motor
            pstCommand->pubResponse[0] = 0x81; // echo command ID
            pstCommand->pubResponse[1] = (U8)EngFOC_IF_StartMotor();
            break;
        case 0x82: // Stop Motor
            pstCommand->pubResponse[0] = 0x82; // echo command ID
            pstCommand->pubResponse[1] = (U8)EngFOC_IF_StopMotor();
            break;
        case 0x83: // Torque Control
            pstCommand->pubResponse[0] = 0x83; // echo command ID
            {
                F32 torque = *((F32*)&pstCommand->pubParam[1]); // bytes 1-4
                U32 duration = *((U32*)&pstCommand->pubParam[5]); // bytes 5-7

                pstCommand->pubResponse[1] = (U8)EngFOC_IF_TorqueControl(torque, duration);
            }
            break;
        case 0x84: // Speed Control
            pstCommand->pubResponse[0] = 0x84; // echo command ID
            {
                F32 speed = *((F32*)&pstCommand->pubParam[1]); // bytes 1-4
                U32 duration = *((U32*)&pstCommand->pubParam[5]); // bytes 5-7

                pstCommand->pubResponse[1] = (U8)EngFOC_IF_SpeedControl(speed, duration);
            }
            break;
        case 0x85: // Position Control
            pstCommand->pubResponse[0] = 0x85; // echo command ID
            {
                F32 position = *((F32*)&pstCommand->pubParam[1]); // bytes 1-4
                U32 duration = *((U32*)&pstCommand->pubParam[5]); // bytes 5-7

                pstCommand->pubResponse[1] = (U8)EngFOC_IF_PositionControl(position, duration);
            }
            break;
        case 0x86: // Stop Control
            pstCommand->pubResponse[0] = 0x86; // echo command ID
            pstCommand->pubResponse[1] = (U8)EngFOC_IF_StopControl();
            break;
        case 0x91: // Set Parameter
            pstCommand->pubResponse[0] = 0x91; // echo command ID
            {
                U8 paramId = pstCommand->pubParam[1];   // Parameter ID
                U8 paramType = pstCommand->pubParam[2]; // Parameter Type
                U32 paramValue = *((U32*)&pstCommand->pubParam[4]); // Parameter Value (bytes 4-7)

                pstCommand->pubResponse[1] = paramId; // echo Parameter ID
                pstCommand->pubResponse[2] = paramType; // echo Parameter Type
                pstCommand->pubResponse[3] = (U8)EngFOC_IF_SetParameter(paramId, paramValue);
            }
            break;
        case 0x92: // Get Parameter
            pstCommand->pubResponse[0] = 0x92; // echo command ID
            {
                U8 paramId = pstCommand->pubParam[1];   // Parameter ID
                U8 paramType = pstCommand->pubParam[2]; // Parameter Type

                pstCommand->pubResponse[1] = paramId; // echo Parameter ID
                pstCommand->pubResponse[2] = paramType; // echo Parameter Type
                U32 paramValue = EngFOC_IF_GetParameter(paramId);
                *((U32*)&pstCommand->pubResponse[4]) = paramValue; // Parameter Value (bytes 4-7)
            }
            break;
        case 0x93: // Reset Parameter
            pstCommand->pubResponse[0] = 0x93; // echo command ID
            {
                U8 paramId = pstCommand->pubParam[1];   // Parameter ID
                //U8 paramType = pstCommand->pubParam[2]; // Parameter Type

                pstCommand->pubResponse[1] = paramId; // echo Parameter ID
                pstCommand->pubResponse[3] = (U8)EngFOC_IF_ResetParameter(paramId);
            }
            break;
        case 0x94: // Set Parameter as Default
            pstCommand->pubResponse[0] = 0x94; // echo command ID
            {
                U8 paramId = pstCommand->pubParam[1];   // Parameter ID
                U8 paramType = pstCommand->pubParam[2]; // Parameter Type
                U32 paramValue = *((U32*)&pstCommand->pubParam[4]); // Parameter Value (bytes 4-7)

                pstCommand->pubResponse[1] = paramId; // echo Parameter ID
                pstCommand->pubResponse[2] = paramType; // echo Parameter Type
                pstCommand->pubResponse[3] = (U8)EngFOC_IF_SetParameterAsDefault(paramId, paramValue);
                *((U32*)pstCommand->pubResponse[4]) = paramValue; // echo Parameter Value
            }
            break;
        case 0xA1: // Request Torque Value
            pstCommand->pubResponse[0] = 0xA1; // echo command ID
            {
                pstCommand->pubResponse[1] = TRUE; // Status OK
                F32 torque = EngFOC_IF_GetTorque();
                *((F32*)&pstCommand->pubResponse[4]) = torque; // Torque Value (bytes 4-7)
            }
            break;
        case 0xA2: // Request Speed Value
            pstCommand->pubResponse[0] = 0xA2; // echo command ID
            {
                pstCommand->pubResponse[1] = TRUE; // Status OK
                F32 speed = EngFOC_IF_GetSpeed();
                *((F32*)&pstCommand->pubResponse[4]) = speed; // Speed Value (bytes 4-7)
            }
            break;
        case 0xA3: // Request Position Value
            pstCommand->pubResponse[0] = 0xA3; // echo command ID
            {
                pstCommand->pubResponse[1] = TRUE; // Status OK
                F32 position = EngFOC_IF_GetPosition();
                *((F32*)&pstCommand->pubResponse[4]) = position; // Position Value (bytes 4-7)
            }
            break;
        case 0xA4: // Request PST(Pos/Spd/Tor) Value
            pstCommand->pubResponse[0] = 0xA4; // echo command ID
            {
                pstCommand->pubResponse[1] = TRUE; // Status OK
                F32 torque = EngFOC_IF_GetTorque();
                F32 speed = EngFOC_IF_GetSpeed();
                F32 position = EngFOC_IF_GetPosition();
                //*((U32*)&pstCommand->pubResponse[4]) = pst; // PST Value (bytes 4-7)
            }
            break;
        default:
            break;
    }
}

void EngIFSvc_ResponseCommand(TRecvCommand* pstCommand)
{
    if(pstCommand == NULL)
        return;

    TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MAIN);
    if(pstCAN == NULL || pstCAN->pfnSendData == NULL)
        return;

    // Send response via CAN or other communication interface
    // This is a placeholder for actual implementation
    switch(pstCommand->ubId)
    {
        case 0x81: // Start Motor
        case 0x82: // Stop Motor
        case 0x83: // Torque Control
        case 0x84: // Speed Control
        case 0x85: // Position Control
        case 0x86: // Stop Control
        case 0x91: // Set Parameter
        case 0x92: // Get Parameter
        case 0x93: // Reset Parameter
        case 0x94: // Set Parameter as Default
        case 0xA1: // Request Torque Value
        case 0xA2: // Request Speed Value
        case 0xA3: // Request Position Value
        case 0xA4: // Request PST(Pos/Spd/Tor) Value
            pstCAN->pfnSendData(pstCAN, pstCommand->pubResponse, 8);
            DBG_SWO(ENG_DBG_STRING"Response Sent for Command ID: 0x%x", ENG_TICK, "EngIFSvc", pstCommand->ubId);
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

    DBG_SWO(ENG_DBG_STRING"Received Command ID: 0x%x", ENG_TICK, "EngIFSvc", s_stRecvCommand.ubId);

    EngIFSvc_ProcessCommand(&s_stRecvCommand);
    EngIFSvc_ResponseCommand(&s_stRecvCommand);
}



