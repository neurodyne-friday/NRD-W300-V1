/**
 * @file        EngCM_SystemConfig.h
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

#ifndef __ENGCM_SYSTEMCONFIG_H__
#define __ENGCM_SYSTEMCONFIG_H__


/**
 * Engine Main Version
 */

#define C_ENG_MODEL_NAME		"C3510ND"
#define C_ENG_MODEL_NAME_OA		"C3510ND"
#define C_ENG_MODEL_NAME_IT		"C3510ND"

#define C_ENG_MODEL_CODE		0
#define C_ENG_MAJOR_VERSION		0	/* Major Version (use one character, 0~9) */
#define C_ENG_MIDDLE_VERSION	00	/* Middle Version(one character, 0~9) */
#define C_ENG_MINOR_VERSION		00	/* Minor Version ((two characters, 0~99) */

#define C_ENG_FULL_VERSION		"V1.35.84_170309"

#define C_ENG_CTSALL_VERSION	"V0.00.01_131221"


#define ENGVM_MAX_TASKS 					300			/**< Max number for Virtual cyclic Manager */

#define ENGOS_CMSIS
//#define ENGOS_FREERTOS
//#define ENGOS_UCOS

#endif /* __ENGCM_SYSTEMCONFIG_H__ */

