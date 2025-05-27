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
// EXTERN void EngSM_StartPrint(TEngPage* pstObjPage, TEngPageID enPageID);
EXTERN void EngSM_StopPrint(void* pvObjPage);
#ifdef ALT_IFSVC_NEWIF_SIMPLEFIED
EXTERN void EngSM_StartDuplexReversePrint(TEngPage* pstObjPage);
EXTERN void EngSM_StopDuplexReversePrint(TEngPage* pstObjPage);
EXTERN TEngPage *EngSM_GetDuplexReversePage(void);
#endif
EXTERN TEngSystemManager *EngSM_GetManager(void);
EXTERN BOOL EngSM_SetDeviceStatus(U32 ulStatusID, U32 ulNewValue, U32 ulSetReset);
EXTERN U32 EngSM_GetDeviceStatus(U32 ulStatusID);
//EXTERN void *EngSM_GetSystemFunc(U8 *pubFuncName, U32 ulArgCnt);
EXTERN void EngSM_StartTimingChart(void *pvTimingObj, U32 ulTimingID);
EXTERN U32 EngSM_SendEvent(U32 ulEventID, TStateMachine *pstStateMachine, U32 ulLParam, U32 ulRParam);
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


#ifdef __ENGSM_MAIN_C__
static void *s_apfnStatusFuncTable[] = 
{
	 (void *)EngSM_EngineState,					/* ENGSM_STS_PARENT_ENGINE_STATE */
	// (void *)EngSM_MachineDoorStatus,			/* ENGSM_STS_PARENT_MACHINE_DOOR_STATUS */
	// (void *)EngSM_PaperErrorStatus,				/* ENGSM_STS_PARENT_PAPER_ERROR_STATUS */
	// (void *)EngSM_MotorStatus,					/* ENGSM_STS_PARENT_MOTOR_STATUS */
	// (void *)EngSM_FanStatus,					/* ENGSM_STS_PARENT_FAN_STATUS */
	// (void *)EngSM_Tray1Status,					/* ENGSM_STS_PARENT_TRAY_1_STATUS */
	// (void *)EngSM_Tray1PaperSize,				/* ENGSM_STS_PARENT_TRAY_1_PAPER_SIZE */
	// (void *)EngSM_Tray1PaperType,				/* ENGSM_STS_PARENT_TRAY_1_PAPER_TYPE */
	// (void *)EngSM_Tray1FeederMethod,			/* ENGSM_STS_PARENT_TRAY_1_FEEDER_METHOD */
	// (void *)EngSM_Tray2Status,					/* ENGSM_STS_PARENT_TRAY_2_STATUS */
	// (void *)EngSM_Tray2PaperSize,				/* ENGSM_STS_PARENT_TRAY_2_PAPER_SIZE */
	// (void *)EngSM_Tray2PaperType,				/* ENGSM_STS_PARENT_TRAY_2_PAPER_TYPE */
	// (void *)EngSM_Tray2FeederMethod,			/* ENGSM_STS_PARENT_TRAY_2_FEEDER_METHOD */
	// (void *)EngSM_Tray3Status,					/* ENGSM_STS_PARENT_TRAY_3_STATUS */
	// (void *)EngSM_Tray3PaperSize,				/* ENGSM_STS_PARENT_TRAY_3_PAPER_SIZE */
	// (void *)EngSM_Tray3PaperType,				/* ENGSM_STS_PARENT_TRAY_3_PAPER_TYPE */
	// (void *)EngSM_Tray3FeederMethod,			/* ENGSM_STS_PARENT_TRAY_3_FEEDER_METHOD */
	// (void *)EngSM_Tray4Status,					/* ENGSM_STS_PARENT_TRAY_4_STATUS */
	// (void *)EngSM_Tray4PaperSize,				/* ENGSM_STS_PARENT_TRAY_4_PAPER_SIZE */
	// (void *)EngSM_Tray4PaperType,				/* ENGSM_STS_PARENT_TRAY_4_PAPER_TYPE */
	// (void *)EngSM_Tray4FeederMethod,			/* ENGSM_STS_PARENT_TRAY_4_FEEDER_METHOD */
	// (void *)EngSM_Tray5Status,					/* ENGSM_STS_PARENT_TRAY_5_STATUS */
	// (void *)EngSM_Tray5PaperSize,				/* ENGSM_STS_PARENT_TRAY_5_PAPER_SIZE */
	// (void *)EngSM_Tray5PaperType,				/* ENGSM_STS_PARENT_TRAY_5_PAPER_TYPE */
	// (void *)EngSM_Tray5FeederMethod,			/* ENGSM_STS_PARENT_TRAY_5_FEEDER_METHOD */
	// (void *)EngSM_HCFStatus,					/* ENGSM_STS_PARENT_TRAY_HCF_STATUS */
	// (void *)EngSM_HCFPaperSize,					/* ENGSM_STS_PARENT_TRAY_HCF_PAPER_SIZE */
	// (void *)EngSM_HCFPaperType,					/* ENGSM_STS_PARENT_TRAY_HCF_PAPER_TYPE */
	// (void *)EngSM_HCFFeederMethod,				/* ENGSM_STS_PARENT_TRAY_HCF_FEEDER_METHOD */
	// (void *)EngSM_TrayMPStatus,					/* ENGSM_STS_PARENT_TRAY_MP_STATUS */
	// (void *)EngSM_TrayMPPaperSize,				/* ENGSM_STS_PARENT_TRAY_MP_PAPER_SIZE */
	// (void *)EngSM_TrayMPPaperType,				/* ENGSM_STS_PARENT_TRAY_MP_PAPER_TYPE */
	// (void *)EngSM_TrayMPFeederMethod,			/* ENGSM_STS_PARENT_TRAY_MP_FEEDER_METHOD */
	// (void *)EngSM_TrayManualStatus,				/* ENGSM_STS_PARENT_TRAY_MANUAL_STATUS */
	// (void *)EngSM_TrayManualPaperSize,			/* ENGSM_STS_PARENT_TRAY_MANUAL_PAPER_SIZE */
	// (void *)EngSM_TrayManualPaperType,			/* ENGSM_STS_PARENT_TRAY_MANUAL_PAPER_TYPE */
	// (void *)EngSM_TrayManualFeederMethod,		/* ENGSM_STS_PARENT_TRAY_MANUAL_FEEDER_METHOD */
	// (void *)EngSM_MismatchedReasonStatus,		/* ENGSM_STS_PARENT_MISMATCHED_REASON_STATUS */
	// (void *)EngSM_MismatchedTrayNumber,			/* ENGSM_STS_PARENT_MISMATCHED_TRAY_NUMBER */
	// (void *)EngSM_MismatchedPaperSize,			/* ENGSM_STS_PARENT_MISMATCHED_PAPER_SIZE */
	// (void *)EngSM_MismatchedPaperType,			/* ENGSM_STS_PARENT_MISMATCHED_PAPER_TYPE */
	// (void *)EngSM_MismatchedReqPaperSize,		/* ENGSM_STS_PARENT_MISMATCHED_REQ_PAPER_SIZE */
	// (void *)EngSM_MismatchedReqPaperType,		/* ENGSM_STS_PARENT_MISMATCHED_REQ_PAPER_TYPE */
	// (void *)EngSM_DuplexUnitStatus,				/* ENGSM_STS_PARENT_DUPLEX_UNIT_STATUS */
	// (void *)EngSM_CTonerStatus,					/* ENGSM_STS_PARENT_C_TONER_STATUS */
	// (void *)EngSM_MTonerStatus,					/* ENGSM_STS_PARENT_M_TONER_STATUS */
	// (void *)EngSM_YTonerStatus,					/* ENGSM_STS_PARENT_Y_TONER_STATUS */
	// (void *)EngSM_KTonerStatus,					/* ENGSM_STS_PARENT_K_TONER_STATUS */
	// (void *)EngSM_CDrumStatus,					/* ENGSM_STS_PARENT_C_DRUM_STATUS */
	// (void *)EngSM_MDrumStatus,					/* ENGSM_STS_PARENT_M_DRUM_STATUS */
	// (void *)EngSM_YDrumStatus,					/* ENGSM_STS_PARENT_Y_DRUM_STATUS */
	// (void *)EngSM_KDrumStatus,					/* ENGSM_STS_PARENT_K_DRUM_STATUS */
	// (void *)EngSM_TransferBeltStatus,			/* ENGSM_STS_PARENT_TRANSFER_BELT_STATUS */
	// (void *)EngSM_ACRStatus,					/* ENGSM_STS_PARENT_ACR_STATUS */
	// (void *)EngSM_CTDStatus,					/* ENGSM_STS_PARENT_CTD_STATUS */
	// (void *)EngSM_WasteTankStatus,				/* ENGSM_STS_PARENT_WASTE_TANK_STATUS */
	// (void *)EngSM_Fuser1Status,					/* ENGSM_STS_PARENT_FUSER_1_STATUS */
	// (void *)EngSM_Fuser2Status,					/* ENGSM_STS_PARENT_FUSER_2_STATUS */
	// (void *)EngSM_TemperatureStatus,			/* ENGSM_STS_PARENT_TEMPERATURE_STATUS */
	// (void *)EngSM_EnvironmentStatus,			/* ENGSM_STS_PARENT_ENVIRONMENT_STATUS */
	// (void *)EngSM_LSUStatus,					/* ENGSM_STS_PARENT_LSU_STATUS */
	// (void *)EngSM_FinisherStatus,				/* ENGSM_STS_PARENT_FINISHER_STATUS */
	// (void *)EngSM_FinisherWarning,				/* ENGSM_STS_PARENT_FINISHER_WARNING */
	// (void *)EngSM_FinisherFault,				/* ENGSM_STS_PARENT_FINISHER_FAULT */
	// (void *)EngSM_MailboxFault,					/* ENGSM_STS_PARENT_MAILBOX_FAULT */
	// (void *)EngSM_ExpanderStatus,				/* ENGSM_STS_PARENT_EXPANDER_STATUS */
	// (void *)EngSM_DiagnosticStatus,				/* ENGSM_STS_PARENT_DIAG_STATUS */
	// (void *)EngSM_SystemDeviceStatus,			/* ENGSM_STS_PARENT_SYSTEM_DEVICE_STATUS */
	// (void *)EngSM_Tray2Version,					/* ENGSM_STS_PARENT_TRAY_2_VERSION */
	// (void *)EngSM_Tray3Version,					/* ENGSM_STS_PARENT_TRAY_3_VERSION */
	// (void *)EngSM_Tray4Version,					/* ENGSM_STS_PARENT_TRAY_4_VERSION */
	// (void *)EngSM_Tray5Version,					/* ENGSM_STS_PARENT_TRAY_5_VERSION */	
	// (void *)EngSM_HCFVersion,					/* ENGSM_STS_PARENT_HCF_VERSION */	
	// (void *)EngSM_FinisherVersion,				/* ENGSM_STS_PARENT_FINISHER_VERSION */	
	// (void *)EngSM_ExpenderVersion,				/* ENGSM_STS_PARENT_EXPENDER_VERSION */	
	// (void *)EngSM_ABCStatus,					/* ENGSM_STS_PARENT_ABC_STATUS */	
	// (void *)EngSM_TransferStatus,				/* ENGSM_STS_PARENT_TRANSFER_STATUS*/
};
#endif //__ENGSM_MAIN_C__


#endif /* __ENGSM_MAIN_H__ */
