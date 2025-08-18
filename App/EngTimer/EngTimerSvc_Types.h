/**
 * @file        EngTimerSvc_Types.h
 * @brief       This is type definition file for Engine Timer Service Component.
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
 * @date		03/11/2024(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGTIMERSVC_TYPES_H__
#define __ENGTIMERSVC_TYPES_H__

#include "Eng_CommonType.h"

#define TIMERSVC_1MS		1
#define TIMERSVC_2MS		2
#define TIMERSVC_10MS		10
#define TIMERSVC_50MS		(5*TIMERSVC_10MS)
#define TIMERSVC_100MS		(10*TIMERSVC_10MS)
#define TIMERSVC_1S			(10*TIMERSVC_100MS)


/**
 * @brief    Enumeration for Engine TimerSvc ID
 */
typedef enum
{
//	TIMERSVC_ID_VM_1MS,			/**< Timer Service ID for virtual cyclic manager  */
//	TIMERSVC_ID_VM_2MS,			/**< Timer Service ID for virtual cyclic manager  */
//	TIMERSVC_ID_VM_5MS, 		/**< Timer Service ID for virtual cyclic manager  */
//	TIMERSVC_ID_VM_10MS, 		/**< Timer Service ID for virtual cyclic manager  */
	TIMERSVC_ID_IF_SVC,			/**< Timer Service ID for interface service  */
	TIMERSVC_ID_SYSTEM_MGR,		/**< Timer Service ID for system manager */
	TIMERSVC_ID_MOTION_HND,		/**< Timer Service ID for motion handle */
	TIMERSVC_ID_ERROR_HND,		/**< Timer Service ID for error handle */
	TIMERSVC_ID_TEST_MGR, 		/**< Timer Service ID for Test Manager */
	TIMERSVC_ID_MAX				/**< Timer Service Max ID */
} TEngTimerID;

/**
 * @brief    Enumeration for Engine TimerSvc return value
 */
typedef enum
{
	TIMERSVC_RET_ERROR,			/**< Error  */
	TIMERSVC_RET_NORMAL			/**< Normal */
} TEngTimerRetValue;

/**
 * @brief    Enumeration for Engine TimerSvc Status
 */
typedef enum
{
	TIMERSVC_STS_STOP		= 0x00,		/**< STOP Status */
	TIMERSVC_STS_RUN		= 0x01,		/**< RUN Status ID */
	TIMERSVC_STS_SUSPEND	= 0x02,		/**< SUSPEND Status */
	TIMERSVC_STS_RESUME		= 0x04		/**< RESUME Status  */
} TEngTimerStatus;

/**
 * @brief    Structure for Engine Component Entry Table
 */
typedef struct
{
	TEngTimerID enID;				/**< engine timer ID */
	void (*pfnTimerFunc)(void);		/**< timer function pointer */
	U32 ulDelay;					/**< timer execution delay */
	U32 ulPeriod;					/**< timer execution period */
	TEngTimerStatus enStatus;		/**< timer status  */
} TEngTimerBlock;

#endif /* __ENGTIMERSVC_H__ */