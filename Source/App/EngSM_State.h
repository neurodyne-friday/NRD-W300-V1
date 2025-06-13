/**
 * @file        EngSM_State.h
 * @brief       This main code for State Manager Page Class.
 *
 * <b> Copyright 2024 Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Samsung Electronics, Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		06/11/2008(D/M/Y)
 * @version		V0.1
 */
 
#ifndef __ENGSM_STATE_H__
#define __ENGSM_STATE_H__

#undef EXTERN
#ifdef __ENGSM_STATE_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_DeviceType.h"
#include "EngIFSvc_Types.h"
#include "EngSM_Types.h"


EXTERN U32 EngSM_PowerOnEntry(TEngSystemManager *pstSystemManager);
EXTERN U32 EngSM_WarmupEntry(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_WarmupActivity(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_WarmupExit(TEngSystemManager *pstSystemManager);
EXTERN U32 EngSM_StandbyEntry(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_StandbyActivity(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_StandbyExit(TEngSystemManager *pstSystemManager);
EXTERN U32 EngSM_ActiveEntry(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_ActiveActivity(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_ActiveExit(TEngSystemManager *pstSystemManager);
EXTERN U32 EngSM_SleepEntry(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_SleepActivity(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_SleepExit(TEngSystemManager *pstSystemManager);
EXTERN U32 EngSM_ErrorEntry(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_ErrorActivity(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_ErrorExit(TEngSystemManager *pstSystemManager);
EXTERN U32 EngSM_RecoveryEntry(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_RecoveryActivity(TEngSystemManager *pstSystemManager);
EXTERN BOOL EngSM_RecoveryExit(TEngSystemManager *pstSystemManager);


EXTERN U32 EngSM_GC_StartJob(TEngSystemManager *pstSystemManager, U32 *pulEvent, U32 ulTimeout);

EXTERN U32 EngSM_GC_StartWait(TEngSystemManager *pstSystemManager, U32 *pulEvent, U32 ulTimeout);


#endif /* __ENGSM_STATE_H__ */

