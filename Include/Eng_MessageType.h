/**
 * @file        EngCM_MessageConfig.h
 * @brief       This is the Device Status ID Header file for Gasherbrum Platform Version 3.
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
 * @date		10/04/2024(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENG_MESSAGECONFIG_H__
#define __ENG_MESSAGECONFIG_H__


#define MESSAGE_INITIAL_VAL			MAX_S32							/* Message Init Value  */
#define MESSAGE_GET_INDEX(id)		(id & 0x0000FFFF)				/* To get Message ID  */
#define MESSAGE_GET_SOURCE(id)		((id & 0xFF000000) >> 24)		/* To get Message Source */
#define MESSAGE_GET_TYPE(id)		((id & 0x00FF0000) >> 16)		/* To get Message Type */

/**
 * Engine Message Source
 */
#define MESSAGE_SOURCE_SM			0x01							/* EngSystemMgr */
#define MESSAGE_SOURCE_MH			0x02							/* EngMotionHnd */
#define MESSAGE_SOURCE_EH			0x04							/* EngErrorHnd */
#define MESSAGE_SOURCE_SVC			0x08							/* EngIFSvc */

/**
 * Engine Message Type
 */
#define MESSAGE_TYPE_SPOT			0x01							/* Spot */
#define MESSAGE_TYPE_STATEMACHINE	0x02							/* StateMachine */
#define MESSAGE_TYPE_INFORMATION	0x04							/* Information */
#define MESSAGE_TYPE_WARNING		0x08							/* Warning */
#define MESSAGE_TYPE_ERROR			0x10							/* Error */


#define MESSAGE_MAX_COUNT			0x00000040						/* Maximun count of Message ID */


/**
 * Engine System Manager Message ID Definition
 */
#define ENG_EV_POWER_ON								0x01020001
#define ENG_EV_TEST_MODE_ON							0x01020002
#define ENG_EV_FAST_BOOT_UP 						0x01020003
#define	ENG_EV_START_JOB							0x01020010
#define	ENG_EV_WAIT_END_JOB							0x01020011
#define	ENG_EV_END_JOB								0x01020012

#define ENG_EV_GOTO_STANDBY							0x01020120
#define ENG_EV_GOTO_ERROR							0x01020130

#define	ENG_EV_SLEEP_COMMAND						0x01020045
#define	ENG_EV_WAKEUP_COMMAND						0x01020046
#define	ENG_EV_WAKEUP_COMMAND_STANDBY				0x01020047

#define	ENG_EV_ENTRY_WAIT							0x01020080

#define ENG_EV_SENSOR_CALIBRATION				    0x01020075

#define	ENG_EV_WARMUP_START							0x01020100
#define	ENG_EV_WARMUP_END							0x01020101

#define	ENG_EV_OCCURRED_ERROR						0x01020200
#define	ENG_EV_OCCURRED_EXCEPTION					0x01020201
#define	ENG_EV_OCCURRED_RECOVERY_ERROR				0x01020210
#define	ENG_EV_RECOVERED_ERROR						0x01020211
#define ENG_EV_RECOVERED_ERROR_AT_POWERON			0x01020213

#define	ENG_EV_ENTER_DIAGNOSTIC						0x01020400
#define	ENG_EV_LEAVE_DIAGNOSTIC						0x01020410

#define	ENG_EV_SET_ALTITUDE_MODE					0x01010150
#define	ENG_EV_SET_HUMIDITY_MODE					0x01010151

#define	ENG_EV_SET_LOG_LEVEL						0x01010180
#define	ENG_EV_SET_LOCAL_TIME						0x01010181

#define ENG_EV_CHK_START_ACTIVE_CONDITION			0x01010500
#define ENG_EV_CHK_STNBY_TO_ACTIVE_CONDITION		0x01010510
#define ENG_EV_CHK_STNBY_TO_WAIT_CONDITION			0x01010520
#define ENG_EV_ENQUEUE_JOB							0x01010560
#define ENG_EV_DEQUEUE_JOB							0x01010570


/**
 * Engine Error Handler Message ID Definition
 */
#define	ENG_EV_SELF_WAKEUP							0x10020010
#define	ENG_EV_COVER_OPEN_CLOSED					0x10020020
#define ENG_EV_COVER_OPEN_CLOSED_AT_POWERON 		0x10020025
#define	ENG_EV_SENSOR_CLEARED_AT_SLEEP				0x10020050


/**
 * Engine Interface Service Message ID Definition
 */
#define ENG_EV_CHANGE_COMMAND   					0x40010010

#define ENG_EV_CHECK_SMART_TEC_MODE					0x40013001

#define	ENG_EV_TIMERSVC_ON_OFF						0x40020000

#define ENG_EV_MICRO_POWERSAVE_3V_ON				0x40040130
#define ENG_EV_MICRO_POWERSAVE_3V_OFF				0x40040140
#define ENG_EV_MICRO_POWERSAVE_24V_ON				0x40040150
#define ENG_EV_MICRO_POWERSAVE_24V_OFF				0x40040160
#define ENG_EV_MICRO_POWER_OFF						0x40040170
#define ENG_EV_24V_OFF_CONFIRM						0x40010530

#endif /* __ENG_MESSAGECONFIG_H__ */

