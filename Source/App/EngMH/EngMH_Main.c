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

#define	__ENGMH_MAIN_C__

#include "Eng_CommonType.h"

#include "EngMH_Types.h"

#include "EngMH_IF.h"
#include "EngMH_Main.h"

#include "EngMH_BalancingCtrl.h"
#include "EngMH_WalkingCtrl.h"
#include "EngMH_WatchingCtrl.h"


/* Initialize the Engine Motion handler information */
static TEngHndFramework s_stMotionHandleFramework;
static TEngMotionHnd s_stMotionHandler;

void *EngMH_CreateHandler(void)
{
	TEngHndFramework *pstMotionHandleFramework = &s_stMotionHandleFramework;
		
    pstMotionHandleFramework->ulHandlerID		= ENG_HND_MH;
    pstMotionHandleFramework->Initialize		= EngMH_IF_Initialize;
	pstMotionHandleFramework->RegisterDevice	= NULL;
    pstMotionHandleFramework->StartHandler		= NULL;//EngMH_IF_StartHandler;
    pstMotionHandleFramework->StopHandler		= NULL;//EngMH_IF_StopHandler;
    pstMotionHandleFramework->GetHandlerInfo	= NULL;//EngMH_IF_GetHandler;
    pstMotionHandleFramework->GetHandlerFunc	= NULL;//EngMH_IF_GetHandlerFunc;
    pstMotionHandleFramework->SetHandlerInfo	= NULL;//EngMH_IF_SetHandler;
    pstMotionHandleFramework->SendEvent			= NULL;//EngMH_IF_SendEvent;
    pstMotionHandleFramework->StartTiming		= NULL;
    pstMotionHandleFramework->FollowDeviceStatus= NULL;
    pstMotionHandleFramework->GetFeature		= NULL;//EngMH_IF_GetFeature;	

 	DBG_ENGMH(ENG_DBG_STRING"CreateHandler", ENG_TICK, "MH");

    return (pstMotionHandleFramework);
}

void EngMH_Initialize(void)
{
	TEngMotionHnd *pstMotionHandler = &s_stMotionHandler;

	EngMH_Constructor(pstMotionHandler);
}

void EngMH_Constructor(TEngMotionHnd* pstMotionHandler)
{
	pstMotionHandler->pstJoints = &s_astJointTbl;
	TJoint* pstJoint = NULL;

	// for(U8 ubIndex = 0; ubIndex < JOINT_NAME_MAX; ubIndex++)
	// {
	// 	pstJoint = &pstMotionHandler->pstJoints[ubIndex];
	// 	pstJoint->pfnInit 		= EngMH_Joint_Init;
	// 	pstJoint->pfnControl	= EngMH_Joint_Control;
	// }
}


/**
* @brief       	
* 
* @param[in]		U32 ulStatusID
* @param[in]		U32 ulOldValue
* @param[in]		U32 ulNewValue
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngMH_FollowDeviceStatus(U32 ulStatusID, U32 ulOldValue, U32 ulNewValue)
{
	TEngMotionHnd *pstMotionHandler = &s_stMotionHandler;
	
	TBalancingCtrl *pstBalanceCtrl = (TBalancingCtrl *)EngSM_IF_GetFeature(ENGMH_FEATURE_BALANCING);
	//TWatchingCtrl *pstWatchingCtrl = (TWatchingCtrl *)EngSM_IF_GetFeature(ENGPH_FEATURE_WATCHING);

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
	EngTM_ETM_SaveTimeEvent((U32)EngHH_FollowDeviceStatus, 0);
#endif

//	DBG_ENGHH("\r\n[EngHH] ulStatusID(0x%x):ulNewValue(0x%x)", ulStatusID, ulNewValue);
 
    switch(ulStatusID)
    {
        case ENGSM_STS_PARENT_ENGINE_STATE:
        	pstBalanceCtrl->pfnSetState(pstBalanceCtrl, ulNewValue);
        	//pstWatchingCtrl->pfnSetState(pstWatchingCtrl, ulNewValue);

			EngLib_StateChange(&pstMotionHandler->stStateMachine, ulNewValue, pstMotionHandler);
			pstMotionHandler->enEngState = ulNewValue;

			if(ulNewValue != ENG_ST_STANDBY)
			{
        		/* Delete the below function if print command is received during preprint */
        		//EngVM_DeleteByFunc(EngHH_ResetPreprintAfterTimeout);
        	
				//if(pstBalanceCtrl->pfnStopActionForPrePrint != NULL)
				//{
				//	EngVM_DeleteByFunc(pstFixingCtrl->pfnStopActionForPrePrint);
				//}
			}
			break;
			
        default:    
            break;
    }

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
	EngTM_ETM_SaveTimeEvent((U32)EngHH_FollowDeviceStatus, 1);
#endif

}

BOOL EngMH_Main(void)
{
	TEngMotionHnd *pstMotionHandler = &s_stMotionHandler;
	TJoint* pstJoint = NULL;

	for(U8 ubIndex = 0; ubIndex < JOINT_NAME_MAX; ubIndex++)
	{
		pstJoint = &pstMotionHandler->pstJoints[ubIndex];
		if(pstJoint != NULL)
		{
			if(pstJoint->pfnControl != NULL)
			{
				pstJoint->pfnControl(pstJoint);
			}
		}
	}
}


void EngMH_Joint_Init(TJoint* pstJoint)
{

}

void EngMH_Joint_Control(TJoint* pstJoint)
{

}