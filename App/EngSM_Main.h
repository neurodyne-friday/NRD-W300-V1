/**
 * @file        EngSM_Main.h
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
 
#ifndef __ENGSM_MAIN_H__
#define __ENGSM_MAIN_H__

#undef EXTERN
#ifdef __ENGSM_MAIN_C__
#define EXTERN
#else
#define EXTERN extern
#endif
 

EXTERN BOOL EngSM_Initialize(void);
EXTERN void EngSM_Constructor(TEngSystemManager *pstSystemManager);
EXTERN TEngSystemManager *EngSM_GetManager(void);
EXTERN BOOL EngSM_SetDeviceStatus(U32 ulStatusID, U32 ulNewValue, U32 ulSetReset);
EXTERN U32 EngSM_GetDeviceStatus(U32 ulStatusID);
EXTERN void EngSM_StartTimingChart(void *pvTimingObj, U32 ulTimingID);
EXTERN U32 EngSM_SendEvent(U32 ulEventID, TStateMachine *pstStateMachine, U32 ulLParam, U32 ulRParam);
EXTERN void *EngSM_GetFeature(U32 ulFeatureID);
EXTERN void EngSM_InitialIntervalTime(void);
EXTERN void EngSM_CountIntervalTime(void);
EXTERN BOOL EngSM_IsIntervalTimeValid(TIntervalTimeType enType);
EXTERN U32 EngSM_GetIntervalTime(TIntervalTimeType enType);
EXTERN BOOL EngSM_Main(void);

EXTERN BOOL EngSM_InitStatus(void);
EXTERN U32 EngSM_GetStatus(U32 ulStatusID);
EXTERN BOOL EngSM_SetStatus(U32 ulStatusID, U32 ulNewValue);

EXTERN U32 EngSM_EngineState(U32 ulSetGet, U32 ulDeviceStatusID, U32 ulValue);

EXTERN void EngSM_PowerOff(void);

/**
 * Status Type Definitions
 */
typedef U32 (*TENGSM_STATUS_CALLBACK_F)(U32, U32, U32);


#ifdef __ENGSM_MAIN_C__
static void *s_apfnStatusFuncTable[] = 
{
	 (void *)EngSM_EngineState,					/* ENGSM_STS_PARENT_ENGINE_STATE */
};
#endif //__ENGSM_MAIN_C__


#endif /* __ENGSM_MAIN_H__ */
