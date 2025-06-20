/**
 * @file        EngDrv_CAN.h
 * @brief       This is type definition file for CAN Driver
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

#ifndef __ENGDRV_CAN_H__
#define __ENGDRV_CAN_H__

#undef EXTERN
#ifdef __ENGDRV_CAN_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_CommonType.h"


EXTERN void EngDrv_CAN_Create(void);
EXTERN void EngDrv_CAN_Initialize(TCAN* pstCAN);
EXTERN BOOL EngDrv_CAN_AppendObserver(TCAN* pstCAN, TCANObserver* pstObserver);
EXTERN void EngDrv_CAN_NotifyToObservers(TCAN* pstCAN, U8* pubData, U16 uwLength);
EXTERN void EngDrv_CAN_HALRxCallback(U32 ulHalName, U8 pubData[], U16 uwLength);

EXTERN void EngDrv_CAN_SendData(TCAN* pstCAN, U8 pubData[], U16 uwLength);
EXTERN void EngDrv_CAN_SendByte(TCAN* pstCAN, U8 ubData);
EXTERN void EngDrv_CAN_ReceiveCommand(TCAN* pstCAN);


// ----- utility functions
EXTERN void EngDrv_CAN_IncreaseTimer(void);
EXTERN U16 EngDrv_CAN_GetBufferedCount(void);
EXTERN U16 EngDrv_CAN_GetMaxBufferedCount(void);


#endif /* __ENGDRV_CAN_H__ */
