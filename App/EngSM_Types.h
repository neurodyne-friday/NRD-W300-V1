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
 
#ifndef __ENGSM_TYPES_H__
#define __ENGSM_TYPES_H__

//#include "EngTimerSvc_Types.h"


/*
 * @brief Enumeration Engine Handler ID Definition
 */
typedef enum
{
	ENG_HND_FOC,				/**<  TBD  */
	//ENG_HND_EH,					/**<  TBD  */
	ENG_HND_TOTAL				/**<  TBD  */
} TEngHandlerID;

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
	BOOL fUltraLLCheckFlag;
	BOOL fHandlerNotContinuousCondition;
	BOOL fFastEngineBootUpStart;
	BOOL fLowPowerState;
	BOOL fLowPowerModeNotSupport;
	
	BOOL fStackingMode;
	BOOL fQuietMode;
	TEngHumidity enHumidityMode;
	
	TMsgQCB stMsgQCB;
	TMsgQCB stJobQCB;
	TStateMachine stStateMachine;
	TStateMachine stPrintStateMachine;

	TENGSM_TIMERSVC_SUSPEND_F pfnTimerSvcSuspend;
	TENGSM_TIMERSVC_RESUME_F pfnTimerSvcResume;

	BOOL fInterfaceReady;
	//BOOL fVideoReadyCmd;
	BOOL fEnableQuickCancel;
	BOOL fReadyBlocked;

	U32 ulContinuousPageCnt;
	U32 ulAccumulativePageCnt;

	BOOL fWaitEndJobStopTrayFlag;	

	BOOL fEnterSleepMode;
	BOOL fPower24VOnOffFlag;

	U32 (*pfnCheckContinuousCondition)(struct _TEngSystemManager *pstThis);
	BOOL (*pfnCheckWaitToPrintCondition)(struct _TEngSystemManager *pstThis);
	BOOL (*pfnIsNeedToDoWaitJob)(struct _TEngSystemManager *pstThis);
} TEngSystemManager;

#endif /* __ENGSM_TYPES_H__ */

