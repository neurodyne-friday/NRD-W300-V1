/**
 * @file        EngDrv_Module.c
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

#define	__ENGMH_IF_C__

#include "Eng_CommonType.h"
#include "EngMH_Main.h"
#include "EngMH_IF.h"


void EngMH_IF_Initialize(void)
{
    EngMH_Initialize();
}

void *EngMH_IF_CreateHandler(void)
{
    void *pvHandleEngMH = NULL;
	
	pvHandleEngMH = EngMH_CreateHandler();
	return pvHandleEngMH;
}

//BOOL EngMH_IF_Main(void)
void EngMH_IF_Main(void)
{
    //return EngMH_Main();
    EngMH_Main();
}

