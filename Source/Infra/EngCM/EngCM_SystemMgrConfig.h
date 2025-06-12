/**
 * @file        EngCM_SystemMgrConfig.h
 * @brief       This is engins system configuration.
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

#ifndef __ENGCM_SYSTEMMGRCONFIG_H__
#define __ENGCM_SYSTEMMGRCONFIG_H__


#ifdef __ENGSM_HNDIF_C__
#include "EngMH_IF.h"
#include "EngEH_IF.h"

static void *(*s_apfnEngHnd_Create[])()=
{
	EngMH_IF_CreateHandler,
	EngEH_IF_CreateHandler,
    NULL
};
#endif //__ENGSM_HNDIF_C__




#ifdef __ENGSM_STATE_C__
#include "EngSM_State.h"

static TStateTransitionTbl s_astSystemMgrSTT[] =
{
	/*	Current State		Guard Condition				Event								Next State			Transition Action	*/
	//{	ENG_ST_WARMUP,		EngSM_GC_StartJob,			ENG_EV_START_FAST_FPOT, 			ENG_ST_ACTIVE,		EngSM_TA_StartFastFpot	},
	{	ENG_ST_WARMUP,		NULL,						ENG_EV_OCCURRED_ERROR,				ENG_ST_ERROR,		NULL				},
    {	ENG_ST_WARMUP,		NULL,						ENG_EV_WARMUP_END,					ENG_ST_STANDBY,		NULL				},
    //{	ENG_ST_WARMUP,		NULL,						ENG_EV_WARMUP_TIMEOUT,				ENG_ST_STANDBY,		NULL				},
	{	ENG_ST_WARMUP,		NULL,						ENG_EV_OCCURRED_RECOVERY_ERROR,		ENG_ST_RECOVERY,	NULL				},
	{	ENG_ST_WARMUP, 		EngSM_GC_StartWait,			ENG_EV_ENTRY_WAIT,					ENG_ST_WAIT,		NULL 				},
	{	ENG_ST_WARMUP,		NULL,						ENG_EV_TEST_MODE_ON,				ENG_ST_TEST,		NULL				},    

//    {	ENG_ST_STANDBY,		NULL,						ENG_EV_SET_PREPRINT,				ENG_ST_STANDBY,		EngSM_TA_SetPrePrint	},
//    {	ENG_ST_STANDBY,		NULL,						ENG_EV_RESET_PREPRINT,				ENG_ST_STANDBY,		EngSM_TA_ResetPrePrint	},
    {	ENG_ST_STANDBY,		NULL,						ENG_EV_SLEEP_COMMAND,				ENG_ST_SLEEP,		NULL				},
	{	ENG_ST_STANDBY,		NULL,						ENG_EV_OCCURRED_ERROR,				ENG_ST_ERROR,		NULL				},
	{	ENG_ST_STANDBY,		NULL,						ENG_EV_OCCURRED_RECOVERY_ERROR,		ENG_ST_RECOVERY,	NULL				},
    {	ENG_ST_STANDBY,		NULL,						ENG_EV_ENTER_DIAGNOSTIC,			ENG_ST_EDC,			NULL				},
	// {	ENG_ST_STANDBY,		NULL,						ENG_EV_END_FRAME_JIG_MODE,			ENG_ST_WARMUP,		NULL				},
	// {	ENG_ST_STANDBY,		NULL,						ENG_EV_END_CRUM_WRITING_JIG_MODE,	ENG_ST_WARMUP,		NULL				},
	{	ENG_ST_STANDBY,		NULL,						ENG_EV_WARMUP_START,				ENG_ST_WARMUP,		NULL				},

	{	ENG_ST_STANDBY,		EngSM_GC_StartJob,			ENG_EV_START_JOB,					ENG_ST_ACTIVE,		NULL				},
	{	ENG_ST_STANDBY,		EngSM_GC_StartWait,			ENG_EV_ENTRY_WAIT,					ENG_ST_WAIT,		NULL				},

//    {	ENG_ST_SLEEP,		EngSM_GC_SleepToPrint,		ENG_EV_START_SLEEPTOPRINT,			ENG_ST_STANDBY,		EngSM_TA_SleepToPrint	},
//    {	ENG_ST_SLEEP,		EngSM_GC_WakeupCommand,		ENG_EV_START_PAGE,					ENG_ST_WARMUP,		EngSM_TA_SleepToPrint	},
//    {	ENG_ST_SLEEP,		EngSM_GC_WakeupCommand,		ENG_EV_WAKEUP_COMMAND,				ENG_ST_WARMUP,		EngSM_TA_SleepToWakeUp	},
//    {	ENG_ST_SLEEP,		EngSM_GC_WakeupCommand,		ENG_EV_SELF_WAKEUP,					ENG_ST_WARMUP,		EngSM_TA_SleepToWakeUp	},
	{	ENG_ST_SLEEP,		NULL,						ENG_EV_OCCURRED_ERROR,				ENG_ST_ERROR,		NULL				},
    {	ENG_ST_SLEEP,		NULL,						ENG_EV_ENTER_DIAGNOSTIC,			ENG_ST_EDC,			NULL				},
//	{	ENG_ST_SLEEP,		EngSM_GC_SleepToPrint,		ENG_EV_WAKEUP_COMMAND_STANDBY,		ENG_ST_STANDBY,		EngSM_TA_SleepToPrint	},

#ifdef FR_SM_ENGINE_FAST_BOOTUP
//	{	ENG_ST_ERROR,		EngSM_GC_CheckErrorAtPowerOn,ENG_EV_COVER_OPEN_CLOSED,			ENG_ST_WARMUP,		EngSM_TA_ErrorCleared	},
//	{	ENG_ST_ERROR,		EngSM_GC_CheckErrorAtPowerOn,ENG_EV_COVER_OPEN_CLOSED_AT_POWERON,ENG_ST_POWERON,	EngSM_TA_ErrorCleared	},
#else
//    {	ENG_ST_ERROR,		EngSM_GC_CheckCriticalError,ENG_EV_COVER_OPEN_CLOSED,			ENG_ST_WARMUP,		EngSM_TA_ErrorCleared	},
#endif		
    // {	ENG_ST_ERROR,		EngSM_GC_CheckCriticalError,ENG_EV_EMPTY_CLEARED_AT_PICKUPJAM,	ENG_ST_WARMUP,		EngSM_TA_ErrorCleared	},
    // {	ENG_ST_ERROR,		EngSM_GC_CheckCriticalError,ENG_EV_SENSOR_CLEARED_AT_SLEEP,		ENG_ST_WARMUP,		NULL				},
    // {	ENG_ST_ERROR,		EngSM_GC_CheckCriticalError,ENG_EV_WTB_NOT_INSTALL_CLEARED,		ENG_ST_WARMUP,		EngSM_TA_ErrorCleared	},
	// {	ENG_ST_ERROR,		NULL,						ENG_EV_ERROR_RECOVERY_BY_WARMUP,	ENG_ST_WARMUP,		EngSM_TA_ErrorCleared	},
	// {	ENG_ST_ERROR,		NULL,						ENG_EV_START_CRUM_WRITING_JIG_MODE,	ENG_ST_WARMUP,		EngSM_TA_ErrorCleared	},
    {	ENG_ST_ERROR,		NULL,						ENG_EV_SLEEP_COMMAND,				ENG_ST_SLEEP,		NULL				},
    {	ENG_ST_ERROR,		NULL,						ENG_EV_ENTER_DIAGNOSTIC,			ENG_ST_EDC,			NULL				},
//	{	ENG_ST_ERROR,		EngSM_GC_CheckCriticalError,ENG_EV_CRUM_DATA_REQ_CLEARED,		ENG_ST_STANDBY,		EngSM_TA_ErrorCleared	},

// #if defined(FR_SM_ENGINE_FAST_BOOTUP) || defined(FR_SM_ENGINE_SELF_FAST_BOOTUP)
// 	{	ENG_ST_RECOVERY,	EngSM_GC_PowerOnRecovered,	ENG_EV_RECOVERED_ERROR, 			ENG_ST_WARMUP,		NULL				},
// 	{	ENG_ST_RECOVERY,	EngSM_GC_PowerOnRecovered,	ENG_EV_RECOVERED_ERROR_AT_POWERON,	ENG_ST_POWERON, 	NULL				},
// #else
 	{	ENG_ST_RECOVERY,	NULL,						ENG_EV_RECOVERED_ERROR, 			ENG_ST_STANDBY, 	NULL				},
// 	{	ENG_ST_RECOVERY,	NULL,						ENG_EV_WARMUP_AFTER_RECOVERED_ERROR,ENG_ST_WARMUP,		NULL				},
// #endif		
 	{	ENG_ST_RECOVERY,	NULL,						ENG_EV_OCCURRED_ERROR,				ENG_ST_ERROR,		NULL				},

// #ifdef FR_SM_WAIT_STATE
//     {	ENG_ST_WAIT,		NULL,						ENG_EV_ENTRY_WAIT,					ENG_ST_WAIT,		NULL				},
// //    {	ENG_ST_WAIT,		NULL,						ENG_EV_START_PAGE,					ENG_ST_STANDBY,		NULL				},
// 	{	ENG_ST_WAIT,		NULL,						ENG_EV_OCCURRED_ERROR,				ENG_ST_ERROR,		EngSM_TA_HardStopWaitMode	},
// 	{	ENG_ST_WAIT,		NULL,						ENG_EV_OCCURRED_RECOVERY_ERROR,		ENG_ST_RECOVERY,	EngSM_TA_HardStopWaitMode	},
// 	{	ENG_ST_WAIT,		EngSM_GC_QuitWaitMode,		ENG_EV_QUIT_WAIT_MODE,				ENG_ST_STANDBY,		NULL,				},	
// #ifdef HR_IH_WAIT_CONTINUOUS_PRINT
// 	{	ENG_ST_WAIT,		EngSM_GC_StartJobFromWait,	ENG_EV_START_JOB,					ENG_ST_ACTIVE,		NULL	},
// #else
// 	{	ENG_ST_WAIT,		EngSM_GC_StartJob,			ENG_EV_START_JOB,					ENG_ST_ACTIVE,		NULL	},
// #endif
// #endif

// 	{	ENG_ST_EDC,			EngSM_GC_LeaveDiagnostic,	ENG_EV_LEAVE_DIAGNOSTIC,			ENG_ST_WARMUP,		NULL				},
// 	{	ENG_ST_EDC,			NULL,						ENG_EV_OCCURRED_ERROR,				ENG_ST_ERROR,		NULL				},

// 	{	ENG_ST_POWERON, 	NULL,						ENG_EV_FAST_BOOT_UP,				ENG_ST_WARMUP,		NULL				},
 	{	ENG_ST_POWERON,		NULL,						ENG_EV_OCCURRED_ERROR,				ENG_ST_ERROR,		NULL				},
	{	ENG_ST_POWERON,		NULL,						ENG_EV_OCCURRED_RECOVERY_ERROR,		ENG_ST_RECOVERY,	NULL				},		
// 	{	ENG_ST_POWERON, 	EngSM_GC_PowerOnStop,		ENG_EV_TEST_MODE_ON,				ENG_ST_TEST,		NULL				},		

// #if defined(FR_SM_ENGINE_FAST_BOOTUP) || defined(FR_SM_ENGINE_SELF_FAST_BOOTUP)
// 	{	ENG_ST_UNSPECIFIED, EngSM_GC_PowerOnCommand,	ENG_EV_POWER_ON,					ENG_ST_POWERON, 	NULL				},
// #else
//     {	ENG_ST_UNSPECIFIED,	EngSM_GC_PowerOnCommand,	ENG_EV_POWER_ON,					ENG_ST_WARMUP,		NULL				},
// #endif
     {	ENG_ST_UNSPECIFIED,	NULL,						ENG_EV_TEST_MODE_ON,				ENG_ST_TEST,		NULL				},
     {	ENG_ST_UNSPECIFIED,	NULL,						ENG_EV_OCCURRED_ERROR,				ENG_ST_ERROR,		NULL				},    
     {	ENG_ST_UNSPECIFIED,	NULL,						ENG_EV_UNSPECIFIED,					ENG_ST_UNSPECIFIED,	NULL				}
};

static TStateMachineTbl s_astSystemMgrSMT[] =
{
	{	ENG_ST_WARMUP,		EngSM_WarmupEntry,		EngSM_WarmupActivity,	EngSM_WarmupExit,	"SM Warmup"		},
	{	ENG_ST_STANDBY, 	EngSM_StandbyEntry,		EngSM_StandbyActivity,	EngSM_StandbyExit,	"SM Standby"	},
	{	ENG_ST_ACTIVE, 		EngSM_ActiveEntry,		EngSM_ActiveActivity,	EngSM_ActiveExit,	"SM Active"		},
	{	ENG_ST_SLEEP, 		EngSM_SleepEntry,		EngSM_SleepActivity,	EngSM_SleepExit,	"SM Sleep"		},
	{	ENG_ST_ERROR, 		EngSM_ErrorEntry,		EngSM_ErrorActivity,	EngSM_ErrorExit,	"SM Error"		},
	{	ENG_ST_RECOVERY, 	EngSM_RecoveryEntry,	EngSM_RecoveryActivity,	EngSM_RecoveryExit,	"SM Recovery"	},
	// {	ENG_ST_WAIT, 		EngSM_WaitingEntry,		EngSM_WaitActivity,		EngSM_WaitingExit,	"SM Wait"		},
	// {	ENG_ST_EDC, 		NULL,					NULL,					NULL,				"SM Diagnostic"	},
	// {	ENG_ST_TEST, 		EngSM_TestEntry,		EngSM_TestActivity,		NULL,				"SM Test"		},
	// {	ENG_ST_POWERON, 	EngSM_PowerOnEntry, 	NULL,					NULL,				"SM PowerOn" 	, C_SM_POWERON_TIMEOUT},		
	{	ENG_ST_UNSPECIFIED, NULL,					NULL,					NULL,				"SM Unspecified"	}
};

#endif //__ENGSM_STATE_C__



#endif /* __ENGCM_SYSTEMMGRCONFIG_H__ */

