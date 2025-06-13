/**
 * @file        EngAPP_FOC.h
 * @brief       This main code for State Manager Component.
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
 
#ifndef __ENGAPP_FOC_H__
#define __ENGAPP_FOC_H__

#undef EXTERN
#ifdef __ENGAPP_FOC_C__
#define EXTERN
#else
#define EXTERN extern
#endif
 

EXTERN BOOL EngAPP_Initialize(void);
EXTERN void EngAPP_Constructor(TEngSystemManager *pstSystemManager);
EXTERN void EngAPP_StopPrint(void* pvObjPage);
EXTERN TEngSystemManager *EngAPP_GetManager(void);
EXTERN BOOL EngAPP_SetDeviceStatus(U32 ulStatusID, U32 ulNewValue, U32 ulSetReset);
EXTERN U32 EngAPP_GetDeviceStatus(U32 ulStatusID);
//EXTERN void *EngSM_GetSystemFunc(U8 *pubFuncName, U32 ulArgCnt);
EXTERN void EngAPP_StartTimingChart(void *pvTimingObj, U32 ulTimingID);
EXTERN U32 EngAPP_SendEvent(U32 ulEventID, TStateMachine *pstStateMachine, U32 ulLParam, U32 ulRParam);
EXTERN void *EngSM_GetFeature(U32 ulFeatureID);
// EXTERN S32 EngSM_CheckAdjustNextPrintTime(BOOL fInitialCheckStatus, TEngPage *pstPrevPage, TEngPage *pstCurrPage);
EXTERN void EngSM_InitialIntervalTime(void);
EXTERN void EngSM_CountIntervalTime(void);
EXTERN BOOL EngSM_IsIntervalTimeValid(TIntervalTimeType enType);
EXTERN U32 EngSM_GetIntervalTime(TIntervalTimeType enType);
EXTERN BOOL EngSM_Main(void);

EXTERN BOOL EngSM_InitStatus(void);
EXTERN U32 EngSM_GetStatus(U32 ulStatusID);
EXTERN BOOL EngSM_SetStatus(U32 ulStatusID, U32 ulNewValue);

EXTERN U32 EngSM_EngineState(U32 ulSetGet, U32 ulDeviceStatusID, U32 ulValue);

/**
 * Status Type Definitions
 */
typedef U32 (*TENGSM_STATUS_CALLBACK_F)(U32, U32, U32);

void EngAPP_FOC_SVPWM_CalcDuty(float v_alpha, float v_beta, float Vbus, float *Ta, float *Tb, float *Tc);


#endif /* __ENGAPP_FOC_H__ */
