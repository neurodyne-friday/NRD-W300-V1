/**
 * @file        EngIFSvc_Types.h
 * @brief       This is type definition file for Engine IF Service componet.
 *
 * <b> Copyright 2025 by Neurodyne, Inc. All rights reserved.</b>
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
 
#ifndef __ENGIFSVC_TYPES_H__
#define __ENGIFSVC_TYPES_H__

#include "Eng_CommonType.h"


/*
 * @brief Structure Definitions of Parameter Data
 */

typedef enum _TParamType
{
    PARAM_TYPE_UINT8,
    PARAM_TYPE_UINT16,
    PARAM_TYPE_UINT32,
    PARAM_TYPE_INT8,
    PARAM_TYPE_INT16,
    PARAM_TYPE_INT32,
    PARAM_TYPE_FP16,
    PARAM_TYPE_FP32,
    PARAM_TYPE_MAX
} TParamType;


typedef enum _TParamUnit
{
    PARAM_UNIT_NONE,
    PARAM_UNIT_MS,          // milisecond
    PARAM_UNIT_RAD,         // radian
    PARAM_UNIT_RAD_SEC,     // rad/sec
    PARAM_UNIT_NM,          // newton meter
    PARAM_UNIT_RPM,         // revolution per minute
    PARAM_UNIT_VOLT,        // volt
    PARAM_UNIT_AMPERE,      // ampere
    PARAM_UNIT_WATT,        // watt
    PARAM_UNIT_HERTZ,       // hertz
    PARAM_UNIT_CELSIUS,     // celsius
    PARAM_UNIT_REFERENCE,   // reference param unit table
    PARAM_UNIT_MAX
} TParamUnit;


typedef struct _TParameter
{
	U32 ulId;			// Parameter ID
    U8* pubName;		// Parameter Name
    TParamType eType;   // Parameter Type
    TParamUnit eUnit;   // Parameter Unit
} TParameter;

typedef struct _TCmdParam
{
	U32 ulId;			// Parameter ID
    U8* pubName;		// Parameter Name
    TParamType eType;   // Parameter Type
    TParamUnit eUnit;   // Parameter Unit
} TCmdParam;


// Structure for receiving command from Host
typedef struct _TRecvCommand
{
    U8* pubName;		// Command Name
	U8 ubId;			// Command ID
    U8 pubParam[7];     // Command Parameter
} TRecvCommand;



#endif /* __ENGIFSVC_TYPES_H__ */

