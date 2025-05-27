/**
 * @file        EngSM_State.c
 * @brief       Each Handler performs appropriate task according to state operation processing.
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

#define __ENGSM_STATE_C__

#include "Eng_CommonType.h"

#include "EngMH_Types.h"

#include "EngSM_Main.h"
#include "EngSM_State.h"

//#include "EngEH_Error.h"

#ifdef ALT_IFSVC_OLDIF
#include "PEFW_IF.h"
#endif

#if defined(ENG_CONTINUOUS_TEST) && defined(ALT_IFSVC_NEWIF)
#include "EngIFSvc_Main.h"
#include "EngIFSvc_Common.h"
#endif

/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
BOOL EngSM_InitState(TEngSystemManager *pstSystemManager)
{
	pstSystemManager->stStateMachine.ulPrevState 			= ENG_ST_UNSPECIFIED;
	pstSystemManager->stStateMachine.ulState 				= ENG_ST_UNSPECIFIED;
	pstSystemManager->stStateMachine.ulEvent 				= ENG_EV_UNSPECIFIED;
	pstSystemManager->stStateMachine.ulReceivedEvent 		= ENG_EV_UNSPECIFIED;
	pstSystemManager->stStateMachine.ulGuardConditionEvent	= ENG_EV_UNSPECIFIED;
	pstSystemManager->stStateMachine.pfnGuardCondition 		= NULL;
	pstSystemManager->stStateMachine.pstSTT 				= s_astSystemMgrSTT;
	pstSystemManager->stStateMachine.pstSMT 				= s_astSystemMgrSMT;
	pstSystemManager->stStateMachine.ulTransitionTblSize 	= ARRAY_SIZE(s_astSystemMgrSTT);
	pstSystemManager->stStateMachine.ulMachineTblSize 		= ARRAY_SIZE(s_astSystemMgrSMT);
	pstSystemManager->stStateMachine.pvStateEntry			= pstSystemManager;
	//pstSystemManager->stStateMachine.ulLMSStateID 			= ENGSTATE_NAME_SM;

	EngLib_QuickSort(s_astSystemMgrSMT, ARRAY_SIZE(s_astSystemMgrSMT), sizeof(TStateMachineTbl), EngLib_StateCompareName);

#ifdef FR_TM_LMS_HEADER
	{
		static BOOL fDisplayState = TRUE;
		U32 ulIndex = 0;

		DBG_LMS_HEADER(ENG_LMS_HEADER_STRING, "StateMachine", pstSystemManager->stStateMachine.ulLMSStateID, "SystemSMT");

		if(fDisplayState == TRUE)
		{
			DBG_LMS_HEADER(ENG_LMS_MAIN_ITEM_STRING, ENG_LMS_SUB_DETAIL_VALUE, "SystemSMT");
			
			for(ulIndex = 0; ulIndex < (pstSystemManager->stStateMachine.ulMachineTblSize - 1); ulIndex++)
			{
				DBG_LMS_HEADER(ENG_LMS_SUB_ITEM_STRING, (100 * s_astSystemMgrSMT[ulIndex].ulState), s_astSystemMgrSMT[ulIndex].pubString);
			}
			
			fDisplayState = FALSE;
		}
	}
#endif

#ifdef FR_TM_LMS_COMMONINFO
	{
		TLmsCommonInfo *pstCommonInfo = (TLmsCommonInfo *)EngTM_IF_GetLms(LMS_KIND_COMMON_INFO);
		pstCommonInfo->pfnDisplayWarmUpTypeSA(LMS_SA_WARMUPTYPE_POWER_ON_TO_WARMUP);
		pstCommonInfo->pfnDisplayPowerOnSA(pstCommonInfo);
	}
#endif

	//EngSM_InitPrintingState(pstSystemManager);

//	DBG_ENGSM_STATE(ENG_DBG_STRING"SM_InitState", ENG_TICK, "SM");	

    return TRUE;
}

U32 EngSM_PowerOnEntry(TEngSystemManager *pstSystemManager)
{
	//EngCM_IF_SetSpeed(ENG_SPEED_CASE_WARMUP);

    return 0;
}


U32 EngSM_WarmupEntry(TEngSystemManager *pstSystemManager)
{
#ifdef FR_PH_PAPER_INTERVAL_CHECK
	TPaperIntervalCtrl *pstPaperIntervalCtrl = (TPaperIntervalCtrl *)EngSM_IF_GetFeature(ENGPH_FEATURE_PAPERINTERVAL);	
	pstPaperIntervalCtrl->pfnSetPaperIntervalMode(pstPaperIntervalCtrl, PAPER_INTERVAL_UNSPECIFIED);
#endif

//	EngCM_IF_SetSpeed(ENG_SPEED_CASE_WARMUP);
//	EngSM_HndIF_SendEvent(ENG_HND_PH, ENG_EV_SEND_TRAY_MOTOR_PPS, NULL, ENG_SPEED_CASE_WARMUP, 0);

#ifdef FR_SM_WARMUP_CRUM_CHK
	EngVM_Add(ENGVM_ARG_NUM3, C_SM_CRUM_DATA_ACCESS_DELAY, 0, EngSM_HndIF_StartHandler, ENG_HND_EH, ERROR_NAME_CRUM_DATA_REQ_TIMEOUT, NULL);
#endif

    return 0;
}


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
BOOL EngSM_WarmupActivity(TEngSystemManager *pstSystemManager)
{
	// TPaperWarmUpCtrl *pstPaperWarmUpCtrl = (TPaperWarmUpCtrl *)EngSM_IF_GetFeature(ENGPH_FEATURE_WARMUP);
	// TImageWarmUpCtrl *pstImageWarmUpCtrl = (TImageWarmUpCtrl *)EngSM_IF_GetFeature(ENGIH_FEATURE_WARMUP);
	// THeatingWarmUpCtrl *pstHeatingWarmUpCtrl = (THeatingWarmUpCtrl *)EngSM_IF_GetFeature(ENGHH_FEATURE_WARMUP);

	// /* Get each handler warmup state */
	// TStateMachine *pstPaperWarmupState = &pstPaperWarmUpCtrl->stStateMachine;
	// TStateMachine *pstImageWarmupState = &pstImageWarmUpCtrl->stStateMachine;
	// TStateMachine *pstHeatingWarmupState = &pstHeatingWarmUpCtrl->stStateMachine;

	// /* If warmup state of all handler is ended */
	// if((EngLib_StateGet(pstPaperWarmupState) == PAPER_WARMUP_ST_IDLE) &&
	//    (EngLib_StateGet(pstImageWarmupState) == IMAGE_WARMUP_ST_IDLE) &&
	//    (EngLib_StateGet(pstHeatingWarmupState) == HEATING_WARMUP_ST_IDLE))
	{
#ifdef FR_SM_WAIT_STATE		
		BOOL fContinuousWaitMode = FALSE;
		
		TEngSpeed *pstSpeed = EngCM_IF_GetSpeed();
		TEngSpeed *pstWaitSpeed = EngCM_IF_SearchSpeedCase(ENG_SPEED_CASE_WAIT_MODE);
		TEngErrorHnd *pstErrorHandler = (TEngErrorHnd *)EngSM_IF_GetFeature(ENGEH_HANDLER);
		U32 ulIsRecoverError = pstErrorHandler->pfnIsExistRecoveryError();
				
		if((EngSM_IsNeedToDoWaitJob(pstSystemManager) == TRUE)
			&& (pstSpeed->ulRatio == pstWaitSpeed->ulRatio)
			&& (ulIsRecoverError == FALSE)
		)
		{
			fContinuousWaitMode = TRUE;
		}

		if(fContinuousWaitMode)
		{
			EngSM_SendEvent(ENG_EV_ENTRY_WAIT, NULL, 0, 0);
		}
		else
#endif			
		{
			EngSM_SendEvent(ENG_EV_WARMUP_END, NULL, 0, 0);
		}
	}

	if(EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_ENGINE_STATE) == ENGSM_STS_CHILD_ENGINE_TEST)
	{
		EngSM_SendEvent(ENG_EV_TEST_MODE_ON, NULL, 0, 0);
	}

    return TRUE;
}

/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
BOOL EngSM_WarmupExit(TEngSystemManager *pstSystemManager)
{
#ifdef FR_SM_WARMUP_CRUM_CHK
	EngSM_HndIF_StopHandler(ENG_HND_EH, ERROR_NAME_CRUM_DATA_REQ_TIMEOUT, NULL);
#endif

#if defined(ENG_CONTINUOUS_TEST) && (defined(ENG_BOARD_SIM) || (!defined(ENG_PC_SIM)&&!defined(ENABLE_EFS_MODE)))
	EngTM_IF_SetVirtualPrintMode(TRUE);
	EngVM_Add(ENGVM_ARG_NUM2, 5*T1S, 0, EngTM_IF_VirtualPrintStart, NULL, 0);
#endif

    return TRUE;
}


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
#ifdef WA_SM_WARMUP_AT_EMPTY_OCCURED
static BOOL fEmptyWarmUpFlag = FALSE;
#endif

U32 EngSM_StandbyEntry(TEngSystemManager *pstSystemManager)
{
	TEngErrorHnd *pstErrorHandler = (TEngErrorHnd *)EngSM_IF_GetFeature(ENGEH_HANDLER);

	// EngCM_IF_SetSpeed(ENG_SPEED_CASE_NORMAL);

	// pstSystemManager->ulStnbyToPrintEnChkCnt = 0;
	// pstSystemManager->ulStandByToPrintPendState = PEND_NO_ERROR;

	pstErrorHandler->pfnClearRecoveryCntByWarmUp(ENG_ST_WARMUP);

#ifdef FR_OH_FINISHER_SUPPORT
	if(!(EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_FINISHER_STATUS) & ENGSM_STS_CHILD_FINISHER_NOT_INSTALLED))
	{
		TPaperFinisherCtrl *pstFinisherCtrl = (TPaperFinisherCtrl *)EngSM_IF_GetFeature(ENGPH_FEATURE_FINISHER); 

		if(pstFinisherCtrl->pfnGetFinisherDeviceType(pstFinisherCtrl) == OPTION_FINISHER_DEVICE_TYPE_FINISHER)
		{
			EngSM_HndIF_StartHandler(ENG_HND_EH, ERROR_NAME_FINISHER_NOT_READY, NULL);
		}
		else
		{
			EngSM_HndIF_StartHandler(ENG_HND_EH, ERROR_NAME_MAILBOX_NOT_READY, NULL);
		}
	}
#endif

#ifdef WA_SM_WARMUP_AT_EMPTY_OCCURED
	fEmptyWarmUpFlag = FALSE;
#endif

#ifdef FR_TM_LMS_PAGECOUNT
	{
		TLmsPageCount *pstLMSPageCount = (TLmsPageCount *)EngTM_IF_GetLms(LMS_KIND_PAGE_COUNT);
		pstLMSPageCount->pfnClearContinuousCountSA(pstLMSPageCount);
	}
#endif
#ifdef FR_TM_LMS_LIFE
	{
		TLmsLife *pstLmsLife = (TLmsLife *)EngTM_IF_GetLms(LMS_KIND_LIFE);
		pstLmsLife->pfnDisplayFuserPageCount(pstLmsLife);
		pstLmsLife->pfnDisplayFuserUnitCycle(pstLmsLife);
	}
#endif

    return 0;
}


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
BOOL EngSM_StandbyActivity(TEngSystemManager *pstSystemManager)
{
	TEngErrorHnd *pstErrorHandler = (TEngErrorHnd *)EngSM_IF_GetFeature(ENGEH_HANDLER);
	// TEngPaperHnd *pstPaperHandler = (TEngPaperHnd *)EngSM_IF_GetFeature(ENGPH_HANDLER);
	// TEngImageHnd *pstImageHandler = (TEngImageHnd *)EngSM_IF_GetFeature(ENGIH_HANDLER);
	// TEngHeatingHnd *pstHeatingHandler = (TEngHeatingHnd *)EngSM_IF_GetFeature(ENGHH_HANDLER);
	
	BOOL fWaitStateChked = FALSE;
	U32 ulIsRecoverError = pstErrorHandler->pfnIsExistRecoveryError();
	static U32 ulBlockChkTimeCnt = 0;

	/* Get each handler Ready state */
	// TStateMachine *pstPaperState = &pstPaperHandler->stStateMachine;
	// TStateMachine *pstImageState = &pstImageHandler->stStateMachine;
	// TStateMachine *pstHeatingState = &pstHeatingHandler->stStateMachine;

	/* If Standby state of all handler is ended */
	// if((EngLib_StateGet(pstPaperState) != ENG_ST_STANDBY)
	// 	|| (EngLib_StateGet(pstImageState) != ENG_ST_STANDBY)
	// 	|| (EngLib_StateGet(pstHeatingState) != ENG_ST_STANDBY)
	// )
	//{
		return TRUE;
	//}
	
}


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
BOOL EngSM_StandbyExit(TEngSystemManager *pstSystemManager)
{
#ifdef FR_OH_FINISHER_SUPPORT
	EngSM_HndIF_StopHandler(ENG_HND_EH, ERROR_NAME_FINISHER_NOT_READY, NULL);
	EngSM_HndIF_StopHandler(ENG_HND_EH, ERROR_NAME_MAILBOX_NOT_READY, NULL);
#endif

    return TRUE;
}

BOOL EngSM_ActiveActivity(TEngSystemManager *pstSystemManager)
{
	return TRUE;
}

BOOL EngSM_ActiveExit(TEngSystemManager *pstSystemManager)
{
	return TRUE;
}

U32 EngSM_SleepEntry(TEngSystemManager *pstSystemManager)
{
	return 0;
}

BOOL EngSM_SleepActivity(TEngSystemManager *pstSystemManager)
{
	return TRUE;
}

BOOL EngSM_SleepExit(TEngSystemManager *pstSystemManager)
{
	return TRUE;
}

U32 EngSM_ErrorEntry(TEngSystemManager *pstSystemManager)
{
	return 0;
}

BOOL EngSM_ErrorActivity(TEngSystemManager *pstSystemManager)
{
	return TRUE;
}

BOOL EngSM_ErrorExit(TEngSystemManager *pstSystemManager)
{
	return TRUE;
}

U32 EngSM_RecoveryEntry(TEngSystemManager *pstSystemManager)
{
	return 0;
}

BOOL EngSM_RecoveryActivity(TEngSystemManager *pstSystemManager)
{
	return TRUE;
}

BOOL EngSM_RecoveryExit(TEngSystemManager *pstSystemManager)
{
	return TRUE;
}

U32 EngSM_GC_StartJob(TEngSystemManager *pstSystemManager, U32 *pulEvent, U32 ulTimeout)
{
	TEngErrorHnd *pstErrorHandler = (TEngErrorHnd *)EngSM_IF_GetFeature(ENGEH_HANDLER);
#ifdef WA_PH_MP_EMPTY_UPDATE_TIMING_CHANGE
	TPaperFeedingCtrl *pstFeedingCtrl = (TPaperFeedingCtrl *)EngSM_IF_GetFeature(ENGPH_FEATURE_FEEDING);
#endif
	TEngState enNextState = ENG_ST_UNSPECIFIED;

	if(pstErrorHandler->pfnIsExistWhichKindError(ERROR_KIND_NORMAL | ERROR_KIND_CRITICAL | ERROR_KIND_FATAL))
	{
		*pulEvent = ENG_EV_OCCURRED_ERROR;
		
#ifdef WA_PH_MP_EMPTY_UPDATE_TIMING_CHANGE
		if((pstFeedingCtrl->pfnCheckStartPrintCondition != NULL)
		&& (pstFeedingCtrl->pfnCheckStartPrintCondition(pstFeedingCtrl) == TRUE))
#endif
		{
			enNextState = EngLib_StateGuardCondition(&pstSystemManager->stStateMachine, *pulEvent, pstSystemManager);
			EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);
		}
	}
	else if(pstErrorHandler->pfnIsExistWhichKindError(ERROR_KIND_INACTION))
	{
		/* Not to do any action because of inaction error */
#ifdef ALT_IFSVC_NEWIF_SIMPLEFIED
#ifdef FR_SM_ACR_CTD_PRINT_STATE
		{
			TEngPage *pstEngPageEntry = EngSM_GetPage(ENG_PAGE_CURR_ID);

			if((pstEngPageEntry->ulACRCTDMode)
#ifdef FR_IH_VACR_SHORT_ACR
				|| (pstEngPageEntry->fShortACRMode == TRUE)
#endif
#ifdef FR_IH_IDCTRL_CHECK_CTD
				|| (pstEngPageEntry->fCheckCTDMode == TRUE)
#endif

				)
			{
				enNextState = EngLib_StateGuardCondition(&pstSystemManager->stStateMachine, *pulEvent, pstSystemManager);
				EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);
			}
		}
#endif
#endif
	}
	else
	{
#ifdef FR_OH_FINISHER_SUPPORT
		TPaperFinisherCtrl *pstFinisherCtrl = (TPaperFinisherCtrl *)EngSM_IF_GetFeature(ENGPH_FEATURE_FINISHER);

		if(EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_FINISHER_STATUS) & ENGSM_STS_CHILD_FINISHER_NOT_INSTALLED)
		{
#ifdef WA_PH_MP_EMPTY_UPDATE_TIMING_CHANGE
			if((pstFeedingCtrl->pfnCheckStartPrintCondition != NULL)
			&& (pstFeedingCtrl->pfnCheckStartPrintCondition(pstFeedingCtrl) == TRUE))
#endif
			{			
				enNextState = EngLib_StateGuardCondition(&pstSystemManager->stStateMachine, *pulEvent, pstSystemManager);
				EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);
			}
		}
		else if(pstFinisherCtrl->enState == FINISHER_ST_READY)
		{
#ifdef WA_PH_MP_EMPTY_UPDATE_TIMING_CHANGE
			if((pstFeedingCtrl->pfnCheckStartPrintCondition != NULL)
			&& (pstFeedingCtrl->pfnCheckStartPrintCondition(pstFeedingCtrl) == TRUE))
#endif
			{			
				enNextState = EngLib_StateGuardCondition(&pstSystemManager->stStateMachine, *pulEvent, pstSystemManager);
				EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);
			}
		}
#else
#ifdef WA_PH_MP_EMPTY_UPDATE_TIMING_CHANGE
		if((pstFeedingCtrl->pfnCheckStartPrintCondition != NULL)
		&& (pstFeedingCtrl->pfnCheckStartPrintCondition(pstFeedingCtrl) == TRUE))
#endif
		{
			enNextState = EngLib_StateGuardCondition(&pstSystemManager->stStateMachine, *pulEvent, pstSystemManager);
			EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);
		}
#endif
	}

	return 0;
}



U32 EngSM_GC_StartWait(TEngSystemManager *pstSystemManager, U32 *pulEvent, U32 ulTimeout)
{
	TEngErrorHnd *pstErrorHandler = (TEngErrorHnd *)EngSM_IF_GetFeature(ENGEH_HANDLER);
#ifdef WA_PH_MP_EMPTY_UPDATE_TIMING_CHANGE
	TPaperFeedingCtrl *pstFeedingCtrl = (TPaperFeedingCtrl *)EngSM_IF_GetFeature(ENGPH_FEATURE_FEEDING);
#endif
	TEngState enNextState = ENG_ST_UNSPECIFIED;

	if(pstErrorHandler->pfnIsExistWhichKindError(ERROR_KIND_NORMAL | ERROR_KIND_CRITICAL | ERROR_KIND_FATAL))
	{
		*pulEvent = ENG_EV_OCCURRED_ERROR;

#ifdef WA_PH_MP_EMPTY_UPDATE_TIMING_CHANGE
		if((pstFeedingCtrl->pfnCheckStartPrintCondition != NULL)
		&& (pstFeedingCtrl->pfnCheckStartPrintCondition(pstFeedingCtrl) == TRUE))
#endif
		{
			enNextState = EngLib_StateGuardCondition(&pstSystemManager->stStateMachine, *pulEvent, pstSystemManager);
			EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);
		}
	}
	else if(pstErrorHandler->pfnIsExistError(ERROR_NAME_ULTRA_LL))
	{
		/* Not to do any action because of inaction error */
	}
	else
	{
#ifdef WA_PH_MP_EMPTY_UPDATE_TIMING_CHANGE
		if((pstFeedingCtrl->pfnCheckStartPrintCondition != NULL)
		&& (pstFeedingCtrl->pfnCheckStartPrintCondition(pstFeedingCtrl) == TRUE))
#endif
		{
			enNextState = EngLib_StateGuardCondition(&pstSystemManager->stStateMachine, *pulEvent, pstSystemManager);
			EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);
		}
	}

	return 0;
}


