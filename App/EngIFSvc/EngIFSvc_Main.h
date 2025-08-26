/**
 * @file        EngIFSvc_Main.h
 * @brief       This is type definition file for Engine IF Service componet.
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
 
#ifndef __ENGIFSVC_MAIN_H__
#define __ENGIFSVC_MAIN_H__

#include "Eng_Macro.h"

#undef EXTERN

#ifdef __ENGIFSVC_MAIN_C__
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN BOOL EngIFSvc_Initialize(void);
EXTERN void EngIFSvc_ProcessCommand(TRecvCommand* pstCommand);

/* Interface service handling */
EXTERN void EngIFSvc_ReceiveCommand(U8 *pubData, U16 uwLength);



#endif /* __ENGIFSVC_MAIN_H__ */

