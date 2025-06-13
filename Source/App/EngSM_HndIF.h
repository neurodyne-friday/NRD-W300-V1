/**
 * @file        EngSM_HndIF.h
 * @brief       This is Header file for EngSM_HndIF.c
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
 * @date		07/11/2008(D/M/Y)
 * @version		V0.1
 */
 
#ifndef __ENGSM_HNDIF_H__
#define __ENGSM_HNDIF_H__

#undef EXTERN
#ifdef __ENGSM_HNDIF_C__
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN void EngSM_HndIF_CreateHandler(void);
EXTERN BOOL EngSM_HndIF_Initialize(void);
//EXTERN BOOL EngSM_HndIF_RegisterDevice(void);
EXTERN BOOL EngSM_HndIF_StartHandler(TEngHandlerID enComponentID, U32 ulClassifyID, void* pvHndObj);
EXTERN BOOL EngSM_HndIF_StopHandler(TEngHandlerID enComponentID, U32 ulClassifyID, void* pvHndObj);
//EXTERN void *EngSM_HndIF_GetHandler(TEngHandlerID enComponentID, U32 ulClassifyID);
//EXTERN void *EngSM_HndIF_GetHandlerFunc(TEngHandlerID enComponentID, U8* pubFuncName, U32 ulArgCnt);
EXTERN void EngSM_HndIF_SetHandler(TEngHandlerID enComponentID, U32 ulClassifyID, void *pvSetInfo);
EXTERN U32 EngSM_HndIF_SendEvent(TEngHandlerID enComponentID, U32 ulEventID, TStateMachine *pstStateMachine, U32 ulLParam, U32 ulRParam);
EXTERN void EngSM_HndIF_FollowDeviceStatus(TEngHandlerID enComponentID, U32 ulStatusID, U32 ulOldValue, U32 ulNewValue);
EXTERN BOOL EngSM_HndIF_StartTimingChart(TEngHandlerID enComponentID, void *pvTimingObj, U32 ulTimingID);
EXTERN void *EngSM_HndIF_GetFeature(TEngHandlerID enComponentID, U32 ulFeatureID);


#endif /* __ENGSM_HNDIF_H__ */
