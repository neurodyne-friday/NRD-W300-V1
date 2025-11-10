/**
 * @file		EngCM_FeatureConfig.h
 * @brief			
 *\n < Copyright 2024 by Neurodyne, Inc. All rights reserved.>
 * 
 * This software is the confidential and proprietary information 
 * of Neurodyne, Inc. (Confidential Information). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @dept		Embedded FW Team
 * @date		06/03/2024(D/M/Y)
 * @version		V0.1
*/


#define D_NEW_PLATFORM
#define U_BOOT_LOADER

#if (!defined(BOOT_LOADER) && defined(D_BOOT_LOADER))
    #define BOOT_LOADER
#endif


#define USE_SYSTICK
//#define USE_LWIP
//#define USE_DHCP        /* enable DHCP, if disabled static address is used*/
#define USE_SWO
//#define USE_ENGOS_CURRENT_TASK_LOOP


/** 
 * @brief To support EngLog
 */ 
#define FR_ENGLIB_LOG
//#define HR_ENGLIB_DEBUG_MESSAGE_MICRO_SD_SAVE
#define FR_ENGLIB_TASK_LOGGING
//#define FR_ENGLIB_TASK_DUMP_DEBUG
//#define FR_ENGLIB_UART_DEBUG
#define FR_ENGLIB_SWO_DEBUG