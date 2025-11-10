/**
 * @file        EngFOC_Main.h
 * @brief       This main code for FOC(Field Oriented Control) Component.
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
 * @date		08/11/2008(D/M/Y)
 * @version		V0.1
 */
 
#ifndef __ENGFOC_MAIN_H__
#define __ENGFOC_MAIN_H__

#undef EXTERN
#ifdef __ENGFOC_MAIN_C__
#define EXTERN
#else
#define EXTERN extern
#endif
 

EXTERN BOOL EngFOC_Initialize(void);
EXTERN void EngFOC_SetState(TEngState eNewState);
EXTERN TEngState EngFOC_GetState(void);

EXTERN void EngFOC_NotifyByADCIRQ(U8* pubData, U32 ulLength);
EXTERN void EngFOC_Task_CurrentControl(void *argument);
EXTERN void EngFOC_Task_SpeedControl(void *argument);
EXTERN void EngFOC_Task_PositionControl(void *argument);
EXTERN void EngFOC_SVPWM_CalcDuty(float v_alpha, float v_beta, float Vbus, float *Ta, float *Tb, float *Tc);

#endif /* __ENGFOC_MAIN_H__
 */
