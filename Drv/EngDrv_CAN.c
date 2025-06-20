/**
 * @file        EngDrv_CAN.c
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

#define	__ENGDRV_CAN_C__

#include "EngCM_DriverConfig.h"
#include "EngDrv_CAN.h"
#include "EngDrv_IF.h"
#if defined (BOOT_LOADER)  //#ifdef BOOT_LOADER
	#include "EngMD_Ctrl_BOOT.h"
#endif
#include "EngHAL_Lib.h"

static void EngDrv_CAN_ReceiveISR(void);
static void EngDrv_CAN_TransmitISR(void);

void EngDrv_CAN_Create(void)
{
	TCAN *pstInstance = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);

	pstInstance->astCanCommand = s_astCanCommand;

    pstInstance->pfnInitialize = EngDrv_CAN_Initialize;
    pstInstance->pfnAppendObserver = EngDrv_CAN_AppendObserver;
    pstInstance->pfnNotifyToObservers = EngDrv_CAN_NotifyToObservers;
	pstInstance->pfnHALRxCallback = EngDrv_CAN_HALRxCallback;
	pstInstance->pfnSendData = EngDrv_CAN_SendData;

	pstInstance->pfnInitialize(pstInstance);
}

void EngDrv_CAN_Initialize(TCAN* pstCAN)
{
	pstCAN->uwObserverCount = 0;
}

/* CAN Rx & Tx ISR
*/

static void EngDrv_CAN_ReceiveISR(void)
{
	TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
	static U16 rxIndex = 0;
	
}


static void EngDrv_CAN_TransmitISR(void)
{
	TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
}


/* CAN Observer Design Pattern  */

BOOL EngDrv_CAN_AppendObserver(TCAN* pstCAN, TCANObserver* pstObserver)
{
	if(pstCAN != NULL && pstCAN->uwObserverCount < CAN_MAX_OBSERVER_COUNT)
	{
    	pstCAN->stObservers[pstCAN->uwObserverCount].ulDeviceKey = pstObserver->ulDeviceKey;
		pstCAN->stObservers[pstCAN->uwObserverCount].pfnNotify = pstObserver->pfnNotify;
		pstCAN->uwObserverCount++;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void EngDrv_CAN_NotifyToObservers(TCAN* pstCAN, U8* pubData, U16 uwLength)
{
	TCANObserver* pstObserver = NULL;

	if(pstCAN != NULL)
	{
		for(U16 uwIndex = 0; uwIndex < pstCAN->uwObserverCount; uwIndex++)
		{
			pstObserver = &pstCAN->stObservers[uwIndex];
			if(pstObserver->pfnNotify != NULL)
			{
				pstObserver->pfnNotify(pstObserver->ulDeviceKey, pubData, uwLength);
			}
		}
	}
}

void EngDrv_CAN_HALRxCallback(U32 ulHalName, U8 pubData[], U16 uwLength)
{
	TCAN* pstCAN = NULL;

	pstCAN = EngDrv_IF_FindCANByHalName(ulHalName);
}

/* CAN Task Functions
*/

void EngDrv_CAN_ReceiveTask(void *p_arg)
{
	TCAN *pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
	
	U8 data, bcc, bcc_rcv;
	U8 controlType;
	U8 ubCanId = 0;
	
	(void)p_arg;

	while(1)
	{
		// Interrupt에서 CAN Data를 가져옴.

	}
}


void EngDrv_CAN_TransmitTask(void *p_arg)
{
	TCAN *pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
	U16 uwBufferedCount = 0;
	
	(void)p_arg;

	while(1)
	{
	}
}


void EngDrv_CAN_SendData(TCAN* pstCAN, U8 pubData[], U16 uwLength)
{
	U16 uwDlc;
	U8 ubCanId = 0;
	U8 pubDataBuffer[8] = {0,};

	for(U16 uwIndex = 0; uwIndex < uwLength; uwIndex += 8)
	{
		uwDlc = uwLength - uwIndex;

		if(uwDlc > 8)
		{
			uwDlc = 8;
		}

		memcpy((char *)pubDataBuffer, (char *)&pubData[uwIndex], uwDlc);
		EngHAL_CAN_Transmit(pstCAN->ulHalID, pubDataBuffer, uwDlc);
	}
}


void EngDrv_CAN_SendByte(TCAN* pstCAN, U8 ubData)
{
	U8 pubData[8] = {0, };

	pubData[0] = ubData;
	EngDrv_CAN_SendData(pstCAN, pubData, 1);
}


void EngDrv_CAN_ReceiveCommand(TCAN* pstCAN)
{
	TCanCommand* pstCanCommand = &pstCAN->astCanCommand;

	pstCanCommand->ubState = CAN_STATE_Ready;
}


/* CAN Utility functions
*/

void EngDrv_CAN_IncreaseTimer(void)
{
	TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
	pstCAN->vuwCanTimer++;
}

U16 EngDrv_CAN_GetBufferedCount(void)
{
	TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
	return pstCAN->aulCANTransmitCount[0] - pstCAN->aulCANTransmitCount[1];
}


U16 EngDrv_CAN_GetMaxBufferedCount(void)
{
	TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
	return pstCAN->uwMaxPendingTransmitCount;
}
