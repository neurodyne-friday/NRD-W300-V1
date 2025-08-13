/**
 * @file        EngLog_Types.h
 * @brief       This is type definition file for Engine Log Component.
 *
 * <b> Copyright 2024 Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Samsung Electronics, Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		03/11/2008(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGLOG_TYPES_H__
#define __ENGLOG_TYPES_H__


#define C_ENG_LOG_FLAG_RESERVED				BIT_0
#define C_ENG_LOG_FLAG_BUFFER_FULL			BIT_1
#define C_ENG_LOG_FLAG_BLOCK_WRITING		BIT_2

#define C_ENG_MICRO_SD_LOG_AREA_IDENTITY	0x00010005
#define C_ENG_LOG_AREA_IDENTITY				0x00010006
#define C_ENG_LOG_EMERGENCY_SIGNAL			0x00505505

typedef enum
{
	TASK_LOG_AREA_IRQ,
	TASK_LOG_AREA_TASK,
	TASK_LOG_AREA_MAX,
} TTaskLogArea;


typedef enum
{
	DBG_ID_DUMP_LV0,
	DBG_ID_DUMP_LV1,
	DBG_ID_DUMP_LV2,
	DBG_ID_DUMP_LV3,
	DBG_ID_UART,
	DBG_ID_SWO,
	DBG_ID_EMERGENCY,
	DBG_ID_ENGIFSVC,						
	DBG_ID_ENGTMSVC,
	DBG_ID_ENGSM,
	DBG_ID_ENGFOC,
	DBG_ID_ENGEH,
	DBG_ID_ENGTM,
	DBG_ID_ENGLIB,
	DBG_ID_ENGCM,
	DBG_ID_MOTORDRV,
	DBG_ID_SENSORDRV,
	DBG_ID_ADCDRV,
	DBG_ID_UARTDRV,
	DBG_ID_UARTMSG,
	DBG_ID_SPIDRV,
	DBG_ID_POWERDRV,
	DBG_ID_STATE,
	DBG_ID_SEMAPHORE,
	DBG_ID_ENGHAL_LIB,						
	DBG_ID_ENGHAL_GPIO,
	DBG_ID_ENGHAL_ENGTIMER,
	DBG_ID_SENSOR,							
	DBG_ID_LMS_HEADER,						
	DBG_ID_LMS_COMMON_INFO,				
	DBG_ID_LMS_POWER_INFO, 					
	DBG_ID_LMS_ASSERT,						
	DBG_ID_LMS_DATE,						
	DBG_ID_LMS_STATE,						
	DBG_ID_LMS_BIG_DATA,					
	DBG_ID_LMS_STATUS,						
	DBG_ID_LMS_LIFE,						
	DBG_ID_LMS_DEVICE,
	DBG_ID_MAX
} TDebugId;


typedef struct
{
	TDebugId enId;
	U8 *pubName;
	U32 ulLevel;
	BOOL fPrintToDump;
	BOOL fPrintToUart;
	BOOL fPrintToSWO;
	BOOL fPrintToMicroSD;
}TLogParamInfo;


/**
 * @brief    Structure for Engine Log Area Data 
 */
typedef struct
{
	U32 ulLogIdentity;
	U32 ulWriteOffset;
	U32 ulReserved1;
	U32 ulLogDataSize;
	U32 ulLogStatusFlag;
	U32 ulReserved2;
	U32 ulReserved3;
	U32 ulReserved4;
	U8 aubLogData[C_ENG_LOG_DATA_SIZE];
} TDumpLogData;

typedef struct
{
	TDumpLogData *pstDumpLogData;
	U32 ulLogLevel;
} TDumpLog;


/**
 * @brief    Structure for MicroSD Log
 */
typedef struct
{
	U32 ulLogIdentity;
	U32 ulWriteOffset;
	U32 ulReadOffset;
	U32 ulLogAreaTotalSize;
	U32 ulLogStatusFlag;
	U32 ulEmergency;
	U32 ulReserved1;
	U32 ulReserved2;

#ifdef HR_ENGLIB_DEBUG_MESSAGE_MICRO_SD_SAVE
	U8 aubLogData[C_HDD_LOG_DATA_SIZE];
#endif
} TMicroSDLogData;

typedef struct
{
	TMicroSDLogData *pstMicroSDLogData;
	U32 ulLogLevel;
	U32 ulDumpDataHDDPoint;
	BOOL fHDDLogRequestEnable;
} TMicroSDLog;

/**
 * @brief    Structure for Log Print By Kernel Task
 */
typedef struct
{
	U32 ulInfo;							//0 : Only Uart Display, 1>=: Flash BackUp & Uart Display
	U32 ulSize;
	U8 aulData[C_ENG_LOG_DATA_SIZE];
	U32 ulPrintDataID;
} TTaskDump;

/**
 * @brief    Structure for Log Print by UART
 */
typedef struct
{
	U32 ulPrintedLenth;
	U32 ulPrintDataID;
} TUartPrint;

/**
 * @brief    Structure for Log Print by SWO
 */
typedef struct
{
	U32 ulPrintedLenth;
	U32 ulPrintDataID;
} TSWOPrint;

/**
 * @brief    Structure for Engine Log Information.
 */
typedef struct
{
	TLogParamInfo *pstParamInfoTbl;
	TDumpLog *pstDumpLog;
	TMicroSDLog *pstMicroSDLog;
	TTaskDump *pstTaskDump;
	TUartPrint *pstUartPrint;
	TSWOPrint *pstSwoPrint;
} TEngLogInfo;



#endif /* __ENGLOG_TYPES_H__ */

