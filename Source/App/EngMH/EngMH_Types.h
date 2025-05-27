/**
 * @file        EngMH_Types.h
 * @brief       This is type definition file for common
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
 * @date		01/22/2009(D/M/Y)
 * @version		V0.1
 */


#ifndef __EngMH_TYPES_H__
#define __EngMH_TYPES_H__

#include "Eng_CommonType.h"

/**
 * @brief Joint Names
 */

typedef enum
{
	JOINT_NAME_HEAD_ROLL,
    //JOINT_NAME_HEAD_PITCH,
    JOINT_NAME_HEAD_YAW,

    JOINT_NAME_ARM_R_JOINT1,
    JOINT_NAME_ARM_R_JOINT2,
    JOINT_NAME_ARM_R_JOINT3,
    JOINT_NAME_ARM_R_JOINT4,
    JOINT_NAME_ARM_R_JOINT5,
    JOINT_NAME_ARM_R_JOINT6,

    JOINT_NAME_ARM_L_JOINT1,
    JOINT_NAME_ARM_L_JOINT2,
    JOINT_NAME_ARM_L_JOINT3,
    JOINT_NAME_ARM_L_JOINT4,
    JOINT_NAME_ARM_L_JOINT5,
    JOINT_NAME_ARM_L_JOINT6,

    JOINT_NAME_HAND_R_JOINT1,
    JOINT_NAME_HAND_R_JOINT2,
    JOINT_NAME_HAND_R_JOINT3,
    JOINT_NAME_HAND_R_JOINT4,
    JOINT_NAME_HAND_R_JOINT5,

    JOINT_NAME_HAND_L_JOINT1,
    JOINT_NAME_HAND_L_JOINT2,
    JOINT_NAME_HAND_L_JOINT3,
    JOINT_NAME_HAND_L_JOINT4,
    JOINT_NAME_HAND_L_JOINT5,

    JOINT_NAME_WAIST_YAW,

    JOINT_NAME_LEG_R_JOINT1,
    JOINT_NAME_LEG_R_JOINT2,
    JOINT_NAME_LEG_R_JOINT3,
    JOINT_NAME_LEG_R_JOINT4,
    JOINT_NAME_LEG_R_JOINT5,

    JOINT_NAME_LEG_L_JOINT1,
    JOINT_NAME_LEG_L_JOINT2,
    JOINT_NAME_LEG_L_JOINT3,
    JOINT_NAME_LEG_L_JOINT4,
    JOINT_NAME_LEG_L_JOINT5,

    JOINT_NAME_MAX,
    JOINT_NAME_UNSPECIFIED      = JOINT_NAME_MAX
} TJointName;


/*
 * @brief Part Type
 */
typedef enum
{
	ROBOT_PART_TYPE_HEAD_2DOF,
	ROBOT_PART_TYPE_ARM_RIGHT_6DOF,
    ROBOT_PART_TYPE_ARM_LEFT_6DOF,
    ROBOT_PART_TYPE_HAND_RIGHT_11DOF,
    ROBOT_PART_TYPE_HAND_LEFT_11DOF,
    ROBOT_PART_TYPE_WAIST_1DOF,
    ROBOT_PART_TYPE_WAIST_2DOF,
    ROBOT_PART_TYPE_LEG_RIGHT_5DOF,
    ROBOT_PART_TYPE_LEG_LEFT_5DOF,
	ROBOT_PART_TYPE_UNDEFINED
} TRobotPartType;

/*
 * @brief Balancing State
 */
typedef enum
{
	BALANCING_ST_WARMUP,
	BALANCING_ST_STANDBY,
	BALANCING_ST_ACTIVE,
	BALANCING_ST_SLEEP,
	BALANCING_ST_ERROR,
	BALANCING_ST_RECOVERY,
	BALANCING_ST_WAIT,
	BALANCING_ST_EDC,
	BALANCING_ST_TEST,
	BALANCING_ST_POWERON,	
	BALANCING_ST_LOWPOWRER,
	BALANCING_ST_UNSPECIFIED
} TBalacingState;

/**
 * @brief Balancing Control Structure Definitions
 */
typedef struct _TBalancingCtrl
{
	TBalacingState enState;
	
// 	THeatingReadyState	enReadyCtrlState;
// 	TEngHeatingInfo *pstInfo;

// //#ifdef FR_HH_CHANGE_DUTY_CONTROL_DETAIL
// 	U32 ulVMFuserCtrlID;
// //#endif

// 	U32 ulContinuousPageCnt;
// 	U32 ulAccumulativePageCnt;

// 	U32 ulPaperIntervalTimeCnt;
// 	TFuserPrintingDutyType enPrintingDutyType;
// 	U32 ulPickUpDelayTime;
// 	BOOL fPickUpCondition;
// 	U32 ulPickUpLowerTemp;
// 	U32 ulPickUpUpperTemp;
// 	U32 ulPickUpLowerSideTemp;
// 	U32 ulPickUpUpperSideTemp;
// 	BOOL fSleepToPrintPreHeating;
// 	BOOL fReadyPreHeatingTimeOut;
// 	BOOL fPaperWrapJamChecked;
// 	U32 ulFuserMotorStartTimeout;
// 	U32 ulPrePrintCurrTemp;
// 	BOOL fGetFirstPageInfo;
// //#ifdef WA_HH_ABNORMAL_ADC_CHECK_TIMING
// 	BOOL fEnterRecoveryState[2];
// //#endif
// 	BOOL fFirstWaitMode;
 	void (*pfnSetState)(struct _TBalancingCtrl *pstThis, U32 ulState);
// 	void (*pfnStartFixing)(struct _TFixingCtrl *pstThis);
// 	void (*pfnStopFixing)(struct _TFixingCtrl *pstThis);
// 	void (*pfnStartFuserMotor)(struct _TFixingCtrl *pstThis, TMotorSpeedCase enTableCase);
// 	void (*pfnStopFuserMotor)(struct _TFixingCtrl *pstThis);
// 	void (*pfnChangeMotorSpeed)(struct _TFixingCtrl *pstThis);
// 	void (*pfnDecideTargetTemp)(struct _TFixingCtrl *pstThis);
// 	U32 (*pfnReturnTargetTemp)(struct _TFixingCtrl *pstThis);	
// 	void (*pfnDecideCurrentTemp)(struct _TFixingCtrl *pstThis);
// 	void (*pfnControlFixing)(struct _TFixingCtrl *pstThis);
// 	U32 (*pfnConvertTemp2ADC)(U32 ulType, U32 ulTemp);
// 	S32 (*pfnConvertADC2Temp)(U32 ulType, U32 ulADCValue);
// 	S32 (*pfnGetTemperatureFromADC)(struct _TFixingCtrl *pstThis, U32 ulType);
// 	void (*pfnRelayOn)(struct _TFixingCtrl *pstThis);
// 	void (*pfnRelayOff)(struct _TFixingCtrl *pstThis);
// 	void (*pfnFuserBiasOn)(struct _TFixingCtrl *pstThis, TEngPaperSide enPaperSide);
// 	void (*pfnFuserBiasOff)(struct _TFixingCtrl *pstThis);
// 	void (*pfnUpdateFuserTemp)(struct _TFixingCtrl *pstThis);
// 	void (*pfnUpdateDeltaTemp)(S32 slDeltaTemp);
// 	void (*pfnEngChkPaperInterval)(struct _TFixingCtrl *pstThis);
// 	void (*pfnChangePrintDutyType)(struct _TFixingCtrl *pstThis, TFuserPrintingDutyType enDutyType);
// 	void (*pfnStartMonitoringPickupCondition)(struct _TFixingCtrl *pstThis);
// 	BOOL (*pfnCheckPickupCondition)(struct _TFixingCtrl *pstThis);
// 	BOOL (*pfnCheckStartEPCondition)(struct _TFixingCtrl *pstThis);
// #ifdef FR_HH_PICKUP_TARGET_TEMP_DELAY
// 	BOOL (*pfnCheckPrintingEPCondition)(struct _TFixingCtrl *pstThis);
// #endif
// 	BOOL (*pfnCheckStartSyncCondition)(struct _TFixingCtrl *pstThis);
// 	void (*pfnDecidePickUpTemp)(struct _TFixingCtrl *pstThis);
// 	U32 (*pfnGetPickUpLowerTemp)(struct _TFixingCtrl *pstThis);
// 	U32 (*pfnGetPickUpUpperTemp)(struct _TFixingCtrl *pstThis);
// 	U32 (*pfnGetPickUpLowerSideTemp)(struct _TFixingCtrl *pstThis);
// 	U32 (*pfnGetPickUpUpperSideTemp)(struct _TFixingCtrl *pstThis);
// 	U32 (*pfnGetFuserAbnormalADC)(U32 ulADCRequestId);
// 	void(*pfnStartFuserAbnormalADC)(struct _TFixingCtrl *pstThis);
// 	void(*pfnStopFuserAbnormalADC)(struct _TFixingCtrl *pstThis);
// 	void (*pfnResetAccPageCnt)(struct _TFixingCtrl *pstThis);
// 	void (*pfnStartIncreaseRestTimeCnt)(struct _TFixingCtrl *pstThis);
// 	void (*pfnSleepExitIncreaseTimeCnt)(struct _TFixingCtrl *pstThis);
// 	U32 (*pfnGetTargetTemp)(struct _TFixingCtrl *pstThis, TFuser *pstFuser);
// 	void (*pfnSetSleepToPrintMode)(struct _TFixingCtrl *pstThis, BOOL fOnOff);
// 	U32 (*pfnGetPickUpInfoForS2P)(struct _TFixingCtrl *pstThis, TS2PPickUpInfoType enInfoType);
// 	void (*pfnStartActionForPrePrint)(struct _TFixingCtrl *pstThis);
// 	void (*pfnStopActionForPrePrint)(struct _TFixingCtrl *pstThis);
// 	void (*pfnReStartFuserTempDisplay)(struct _TFixingCtrl *pstThis, U32 ulDisplayTime, BOOL fDumpMode);
// 	BOOL (*pfnCheckLsuTempCondition)(struct _TFixingCtrl *pstThis);
// 	BOOL (*pfnCheckMotorTempCondition)(struct _TFixingCtrl *pstThis);	
// 	U32 (*pfnGetFuserRevolutionCount)(struct _TFixingCtrl *pstThis);
// 	void (*pfnCheckNanoDustMode)(struct _TFixingCtrl *pstThis, U32 ulDustModeInfo1, U32 ulDustModeInfo2);
// 	void (*pfnCheckSmartTECMode)(struct _TFixingCtrl *pstThis, U32 ulSmartTECModeInfo1, U32 ulSmartTECModeInfo2);
// 	U32 (*pfnGetPickUpDelayForSmartTEC)(struct _TFixingCtrl *pstThis);
} TBalancingCtrl;


typedef struct _TJoint
{
    U32 ulJointId;
    U8 *pubName;
    U32 ulDeviceKey;
    U32 ulHaId;
    
    /* Referece Targets */
    float fAngularPosTarget;
    float fAngularVelTarget;
    float fAngularAccTarget;

    /* Position */
    float fAngularPosCur;
    float fAngularPosOld;
    /* Velocity */
    float fAngularVelCur;
    float fAngularVelOld;
    /* Acceleration */
    float fAngularAccCur;
    float fAngularAccOld;

    /* Error */
    float fAngularPosError;
    float fAngularPosErrorOld;
    float fAngularPosErrorDiff;
    float fAngularVelError;
    float fAngularVelErrorOld;
    float fAngularVelErrorDiff;
    float fAngularAccError;
    float fAngularAccErrorOld;
    float fAngularAccErrorDiff;

    /* Sensory */
    float fTorque;
    float fPressure;

    /* Interface */
    void (*pfnInit)(struct _TJoint *pstJoint);
    void (*pfnControl)(struct _TJoint *pstJoint);
} TJoint;


typedef struct _TEngMotionHnd
{
   	TEngState enEngState;
	TEngState enPrevStateBeforeSleep;
	U32 ulEvent;
	U32 ulReceivedEvent;

    TStateMachine stStateMachine;

    TJoint* pstJoints;

} TEngMotionHnd;


#endif