/**
 * @file        EngSM_Types.h
 * @brief       This is type definition file for Engine System Manager componet.
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
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		07/11/2024(D/M/Y)
 * @version		V0.1
 */
 
#ifndef __ENGAPP_TYPES_H__
#define __ENGAPP_TYPES_H__

#include "EngTimerSvc_Types.h"


typedef U32 (*TENGSM_ETOK_F)(U32, U32);
typedef U32 (*TENGSM_SETERROR_F)(U8 *);
typedef U32 (*TENGSM_CLEARERROR_F)(U8 *);
typedef void (*TENGSM_CLEARALLERROR_F)(void);
typedef U32 (*TENGSM_REQINFO_PRESENDCMD_F)(U32, U32);
typedef U32 (*TENGSM_NEWIF_INTERRUPT_F)(U32, U32);
typedef void (*TENGSM_CONNECT_INTERRUP_F)(U32, void (*)(void));
typedef void (*TENGSM_NOTIFY_JAM2PASS_F)(void);
typedef BOOL (*TENGSM_SET_PRINTJOB_INFO_F)(U32 ulID, U32 *pulData, U32 ulSize);
typedef	BOOL (*TENGSM_GET_PRINTJOB_INFO_F)(U32 ulID, U32 *pulData, U32 ulSize);

typedef U32 (*TENGSM_TIMERSVC_SUSPEND_F)(const U32);
typedef U32 (*TENGSM_TIMERSVC_RESUME_F)(const U32);
	
/**
 * @brief .
 */
typedef struct
{
	U32 ulHandlerID;
	void (*Initialize)(void);								/**<  TBD  */
	void (*RegisterDevice)(void);							/**<  TBD  */
	BOOL (*StartHandler)(U32, void *);						/**<  TBD  */
	BOOL (*StopHandler)(U32, void *);						/**<  TBD  */
	void *(*GetHandlerInfo)(U32);							/**<  TBD  */
	void *(*GetHandlerFunc)(U8 *, U32);						/**<  TBD  */
	void (*SetHandlerInfo)(U32, void *);					/**<  TBD  */
	U32 (*SendEvent)(U32, TStateMachine *, U32, U32);		/**<  TBD  */
	void (*StartTiming)(void *, U32);						/**<  TBD  */
	void (*FollowDeviceStatus)(U32, U32, U32);				/**<  TBD  */
	void *(*GetFeature)(U32);							/**<  TBD  */
} TEngHndFramework;

/*
 * @brief Enumeration These are states that can affect our state machine of engine system manager
 */
typedef struct
{
    U8 *pubName;				/**<  TBD  */
    void (*pfnCompFunc)(void);	/**<  TBD  */	
    U32 ulArgCnt;				/**<  TBD  */
} THndIFFuncTable;

/*
 * @brief Structure Definitions
 */
typedef struct _TEngSystemManager
{
	TEngState enPrevEngState;						/**<  TBD  */
	TEngState enPrevStateBeforeSleep;
	TEngState enEngState;							/**<  TBD  */
	U32 ulEvent;
	U32 ulReceivedEvent;

	BOOL fPowerOn;
	BOOL fPowerOnFirstPage;
	BOOL fUltraLLCheckFlag;
	BOOL fHandlerNotContinuousCondition;
	BOOL fFastEngineBootUpStart;
	BOOL fLowPowerState;
	BOOL fLowPowerModeNotSupport;
//#ifdef SM_FR_SUPPORT_BORDERLESS_MODE
	BOOL fIsBorderlessMode;
//#endif
	
	BOOL fStackingMode;
	BOOL fQuietMode;
	TEngHumidity enHumidityMode;
	
	TMsgQCB stMsgQCB;
	TMsgQCB stJobQCB;
	TStateMachine stStateMachine;
	TStateMachine stPrintStateMachine;

	//TENGSM_VIRTUALPRINT_F pfnIFSvcVirtualPrint;
	TENGSM_ETOK_F pfnIFSvcEtoK;
	TENGSM_SETERROR_F pfnIFSvcSetError;
	TENGSM_CLEARERROR_F pfnIFSvcClearError;
	TENGSM_CLEARALLERROR_F pfnIFSvcClearAllError;
	TENGSM_REQINFO_PRESENDCMD_F pfnIFSvcIntReqInfoPreSendCmd;
	TENGSM_NEWIF_INTERRUPT_F pfnIFSvcNewIFInterrupt;
	TENGSM_CONNECT_INTERRUP_F pfnIFSvcConnectInterrupt;
	TENGSM_NOTIFY_JAM2PASS_F pfnIFSvcNotifyJam2Pass;
	TENGSM_SET_PRINTJOB_INFO_F pfnIFSvcSetPrintJobInfo;
	TENGSM_GET_PRINTJOB_INFO_F pfnIFSvcGetPrintJobInfo;

	TENGSM_TIMERSVC_SUSPEND_F pfnTimerSvcSuspend;
	TENGSM_TIMERSVC_RESUME_F pfnTimerSvcResume;

	BOOL fInterfaceReady;
	//BOOL fVideoReadyCmd;
	BOOL fEnableQuickCancel;
	BOOL fReadyBlocked;

	U32 ulContinuousPageCnt;
	U32 ulAccumulativePageCnt;

	U32 ulSimplex2inDuplexFlag;
	BOOL fPaperImageAddEnableFlag;
	BOOL fToDoRecoveryJob;
	
	TEngEnvironmentIndex enEnvironmentIdx;

	U32 ulEntryIDForNextPrintTime;
	U32 ulNextPrintTime;
	BOOL fClearNextPrintTime;
	U32 ulAdjustNextPrtTimeMask;
	
	BOOL fWaitEndJobStopTrayFlag;	

// FUSER MICOM FROM EVC
	BOOL bMMATestMode;
	U32	ulULLCondition;

	BOOL fEnterSleepP2Mode;
	BOOL fPower24VOnOffFlag;

	F32 fRefId;			// d축 전류 목표값 (보통 0)
	F32 fRefIq;			// q축 전류 목표값 (토크 요구사항에 따라 갱신)
	F32 fThetaE;		// 현재 전기각 (엔코더로부터 계산)
	F32 fOutVd;			// PI 제어 출력 (d축 전압 명령)
	F32 fOutVq;			// PI 제어 출력 (q축 전압 명령)
	F32 fVAlpha;		// 역변환 후 α축 전압
	F32 fVBeta;			// 역변환 후 β축 전압
	U16 uwADCPhaseA;	// ADC DMA로부터 얻은 샘플 값
	U16 uwADCPhaseB;	// ADC DMA로부터 얻은 샘플 값

} TEngSystemManager;

#endif /* __ENGAPP_TYPES_H__ */

// 전역 변수 (또는 RTOS 큐/Notification으로 전달)
//float i_d_ref = 0.0f;    // d축 전류 목표값 (보통 0)
//float i_q_ref = 0.0f;    // q축 전류 목표값 (토크 요구사항에 따라 갱신)
//float theta_e = 0.0f;    // 현재 전기각 (엔코더로부터 계산)
//float v_d_out, v_q_out;  // PI 제어 출력 (d,q축 전압 명령)
//float v_alpha, v_beta;   // 역변환 후 α, β축 전압
//uint16_t adc_val_phaseA, adc_val_phaseB;  // ADC DMA로부터 얻은 샘플 값