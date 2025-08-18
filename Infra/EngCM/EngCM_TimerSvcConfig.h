/**
 * @file        EngCM_TimerSvcConfig.h
 * @brief       Configuration for Engine Timer Service
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
 * @date		25/10/2024(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGCM_TIMERSVCCONFIG_H__
#define __ENGCM_TIMERSVCCONFIG_H__


#ifdef __ENGTIMERSVC_MAIN_C__
#include "EngSM_IF.h"
//#include "EngEH_IF.h"
//#include "EngTM_IF.h"

/* Engine Component Entry Table */
static TEngTimerBlock s_astEngTimerTbl[TIMERSVC_ID_MAX] =
{
	//{	TIMERSVC_ID_VM_1MS,			EngVM_Execute2ms,		TIMERSVC_10MS + 4*TIMERSVC_1MS,		TIMERSVC_1MS	},
	//{	TIMERSVC_ID_VM_2MS,			EngVM_Execute2ms,		TIMERSVC_10MS + 4*TIMERSVC_2MS,		TIMERSVC_2MS	},
	//{	TIMERSVC_ID_VM_10MS, 		EngVM_Execute10ms,		TIMERSVC_10MS + 3*TIMERSVC_2MS,		TIMERSVC_10MS	},
	//{	TIMERSVC_ID_IF_SVC, 		EngIFSvc_IF_Main,		5*TIMERSVC_10MS + 2*TIMERSVC_2MS,	TIMERSVC_10MS	},
	{	TIMERSVC_ID_SYSTEM_MGR, 	EngSM_IF_Main,			5*TIMERSVC_10MS + 2*TIMERSVC_2MS, 	TIMERSVC_10MS	},
	//{	TIMERSVC_ID_MOTION_HND,		EngMH_IF_Main,			5*TIMERSVC_10MS,					TIMERSVC_10MS	},
	//{	TIMERSVC_ID_ERROR_HND,		EngEH_IF_Main,			TIMERSVC_100MS + 3*TIMERSVC_2MS,	TIMERSVC_2MS	},
	//{	TIMERSVC_ID_TEST_MGR,		EngTM_IF_Main,			5*TIMERSVC_10MS + 4*TIMERSVC_2MS,	TIMERSVC_10MS	},	
};
#endif


#endif /* __ENGCM_TIMERSVCCONFIG_H__ */

