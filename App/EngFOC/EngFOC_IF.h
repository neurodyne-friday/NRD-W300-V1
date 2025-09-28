/**
 * @file        EngFOC_IF.h
 * @brief       This is I/F code for FOC(Field Oriented Control) Component.
 *
 * <b> Copyright 2025 by Neurodyne, Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne, Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		07/11/2024(D/M/Y)
 * @version		V0.1
 */
 
#ifndef __ENGFOC_IF_H__
#define __ENGFOC_IF_H__


EXTERN BOOL EngFOC_IF_Initialize(void);

/* command interface with FOC component */
EXTERN BOOL EngFOC_IF_StartMotor(void);
EXTERN BOOL EngFOC_IF_StopMotor(void);
EXTERN BOOL EngFOC_IF_TorqueControl(F32 fTorque, U32 ulDuration);
EXTERN BOOL EngFOC_IF_SpeedControl(F32 fSpeed, U32 ulDuration);
EXTERN BOOL EngFOC_IF_PositionControl(F32 fPosition, U32 ulDuration);
EXTERN BOOL EngFOC_IF_StopControl(void);

EXTERN BOOL EngFOC_IF_SetParameter(U32 ulParamID, U32 ulValue);
EXTERN U32  EngFOC_IF_GetParameter(U32 ulParamID);
EXTERN BOOL EngFOC_IF_ResetParameter(U32 ulParamID);
EXTERN BOOL EngFOC_IF_SetParameterAsDefault(U32 ulParamID, U32 ulValue);

EXTERN F32 EngFOC_IF_GetTorque(void);
EXTERN F32 EngFOC_IF_GetSpeed(void);
EXTERN F32 EngFOC_IF_GetPosition(void);

EXTERN void EngFOC_IF_NotifyByADCIRQ(void);


#endif /* __ENGFOC_IF_H__ */

