 /**
 * @file        EngOS_Lib.h
 * * @brief       This is header file for EngOS Component
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
 * @date		08/05/2009(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGOS_LIB_H__
#define __ENGOS_LIB_H__

#undef EXTERN
#ifdef __ENGOS_LIB_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "EngOS_Types.h"

/* OS Interface */
EXTERN void EngOS_Task_Create(void);
EXTERN void EngOS_Task_Main(void *p_arg);
EXTERN void EngOS_Task_Start(void);
EXTERN void EngOS_Task_End(void);

EXTERN SemaphoreId EngOS_CreateSemaphore(U8* pubSemaphoreName);
EXTERN void EngOS_ReleaseSemaphore(SemaphoreId id);


#endif /* __ENGOS_LIB_H__ */

