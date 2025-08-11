/**
 * @file        EngHAL_Interrupt.c
 * @brief       This is type definition file for Interrupt HAL
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

#define	__ENGHAL_INTERRUPT_C__

#include "EngHAL_Interrupt.h"
/* Temporary */
#include "EngDrv_IF.h"
//#include "EngDrv_Motor.h"
/* End of Temporary*/

/*
static TISR g_stISRPtr;

TISR* EngHAL_Interrupt_GetPtr()
{
    return &g_stISRPtr;
}

void EngHAL_Interupt_Create()
{
    TISR* pstISRs = EngHAL_Interrupt_GetPtr();
    pstISRs->pfnISR = NULL;
    pstISRs->Type = INTERRUPT_TYPE_UNSECIFIED;
    pstISRs->pstPrev = NULL;
    pstISRs->pstNext = NULL;
}

void EngHAL_Interrupt_Add(TInterruptType eType, U8 ubIndex, void* pfnFunc)
{
    TISR* pThis = EngHAL_Interrupt_GetPtr();
    TISR* pPrev = NULL;

    while(pThis->pfnISR != NULL)
    {
        pPrev = pThis;
        pThis = pThis->pstNext;
    }

    pThis->Type = eType;
    pThis->ubIndex = ubIndex;
    pThis->pfnISR = pfnFunc;
    pThis->pstPrev = pPrev;
    pThis->pstNext = NULL;
}

void* EngHAL_Interrupt_Get(TInterruptType eType, U8 ubIndex)
{
    TISR* pThis = EngHAL_Interrupt_GetPtr();

    while(pThis->pfnISR != NULL)
    {
        if(pThis->Type == eType && pThis->ubIndex == ubIndex)
        {
            return pThis->pfnISR;
        }

        pThis = pThis->pstNext;
    }

    return NULL;
}
*/

void EngHAL_Interrupt_TimerInt(U8 ubTimIntNum)
{
    if(ubTimIntNum == 3)
    {
        TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MAIN);

        // Global Timer

        // CAN Timer
        pstCAN->vuwCanTimer++;

        // BLDC Motor Speed Control
        if(g_vu32GlobalTime % 250 == 0)
		{
            //TMotor* pstMotor_FLNDM = EngDrv_IF_GetMotor(MOTOR_NAME_ML_FLNDM);
            //TMotor* pstMotor_RPNDM = EngDrv_IF_GetMotor(MOTOR_NAME_RJP_RPNDM);

			//BLDCCheckCurrentLineSpeed(250);
            //EngDrv_Motor_BLDC_CheckCurrentLineSpeed(pstMotor_RPNDM, 250);
            //EngDrv_Motor_BLDC_CheckCurrentLineSpeed(pstMotor_FLNDM, 250);
		}
    }
    else if(ubTimIntNum == 7)
    {
        
    }
}

void EngHAL_Interrupt_External(U8 ubExtIntNum)
{
    if(ubExtIntNum == 9)
    {
        // ML BLDC Wheel Count & Hall Count ???
        //TMotor* pstMotor_FLNDM = EngDrv_IF_GetMotor(MOTOR_NAME_ML_FLNDM);

        //pstMotor_FLNDM->ulCurWheelCount++;
        //pstMotor_FLNDM->aulCurHallCount[MOTOR_BLDC_HALL_SENSOR_A]++;
    }
    else if(ubExtIntNum == 15)
    {
        // RJP BLDC Wheel Count & Hall Count ???
        //TMotor* pstMotor_RPNDM = EngDrv_IF_GetMotor(MOTOR_NAME_RJP_RPNDM);

        //pstMotor_RPNDM->ulCurWheelCount++;
        //pstMotor_RPNDM->aulCurHallCount[MOTOR_BLDC_HALL_SENSOR_A]++;
    }
}

void EngHAL_Interrupt_UART(U8 ubUartIntNum)
{
    if(ubUartIntNum == 1)
    {

    }
}
