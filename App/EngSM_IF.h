/**
 * @file        EngSM_IF.h
 * @brief       This is header file for EngSM_IF.c
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
 
#ifndef __ENGSM_IF_H__
#define __ENGSM_IF_H__

#undef EXTERN
#ifdef __ENGSM_IF_C__
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN BOOL EngSM_IF_Initialize(void);
//EXTERN void *EngSM_IF_GetHandler(TEngHandlerID enComponentID, U32 ulClassifyID);
//EXTERN void *EngSM_IF_GetHandlerFunc(TEngHandlerID enComponentID, U8* pubFuncName, U32 ulArgCnt);
//EXTERN void *EngSM_IF_GetSystemFunc(U8* pubFuncName, U32 ulArgCnt);
//EXTERN TEngSystemManager *EngSM_IF_GetManager(void);
EXTERN BOOL EngSM_IF_SetDeviceStatus(U32 ulStatusID, U32 ulNewValue, U32 ulSetReset);
EXTERN BOOL EngSM_IF_ResetDeviceStatus(U32 ulStatusID, U32 ulNewValue);
EXTERN U32 EngSM_IF_GetDeviceStatus(U32 ulStatusID);
EXTERN U32 EngSM_IF_SendEvent(U32 ulEventID, TStateMachine *pstStateMachine, U32 ulLParam, U32 ulRParam);
//EXTERN void EngSM_IF_StartTimingChart(void *pvTimingObj, U32 ulTimingID);
EXTERN void *EngSM_IF_GetFeature(U32 ulFeatureID);
EXTERN BOOL EngSM_IF_IsIntervalTimeValid(TIntervalTimeType enType);
EXTERN U32  EngSM_IF_GetIntervalTime(TIntervalTimeType enType);
//EXTERN BOOL EngSM_IF_Main(void);
EXTERN void EngSM_IF_Main(void);

/* Interface with hardware events */
EXTERN void EngSM_IF_NotifyEventByPowerOff(void);
EXTERN void EngSM_IF_NotifyEventByCAN1(void);
EXTERN void EngSM_IF_NotifyEventByCAN2(void);

#endif /* __ENGSM_IF_H__ */
