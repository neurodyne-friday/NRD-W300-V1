/**
 * @file        EngIFSvc_IF.c
 * @brief       This is I/F code for Engine IF Service Component.
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

#define	__ENGIFSVC_IF_C__

#include "Eng_CommonType.h"
#include "EngIFSvc_IF.h"
#include "EngIFSvc_Main.h"



/**
 * @brief 	  	Event handler for CAN1
 * @param[in]	None
 * @range
 * @retval		None
 * @global
 * @remarks		This function is called when a CAN1 event occurs.
 */

void EngIFSvc_IF_NotifyEventByCAN1(void)
{
	DBG_SWO(ENG_DBG_STRING"EngSM_IF_NotifyEventByCAN1", ENG_TICK, "SM");

	// EngIFSvc를 만들어서 CAN으로 부터 받은 데이터를 Protocol로 해석하여 EngSM으로 Event를 보낸다.
	// 아니면 EngIFSvc의 Callback 함수를 직접 CAN 이벤트에서 호출하도록 수정한다.
}

/**
 * @brief 	  	Event handler for CAN2
 * @param[in]	None
 * @range
 * @retval		None
 * @global
 * @remarks		This function is called when a CAN2 event occurs.
 */
void EngIFSvc_IF_NotifyEventByCAN2(void)
{

}
