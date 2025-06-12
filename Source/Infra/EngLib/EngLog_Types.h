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

#define C_ENG_HDD_LOG_AREA_IDENTITY			0x00010005
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
	DBG_ID_EMERGENCY,
	DBG_ID_ENGIFSVC,						
	DBG_ID_ENGIFSVC_DETAIL,		
	DBG_ID_ENGIFSVC_EI,
	DBG_ID_ENGTMSVC,
	DBG_ID_ENGSM,
	DBG_ID_ENGSM_PAGE,
	DBG_ID_ENGSM_STATE,
	DBG_ID_ENGSM_STATUS,
	DBG_ID_ENGSM_TIMING,
	DBG_ID_ENGMH,
	DBG_ID_ENGEH,
	DBG_ID_ENGEH_DETAIL,
	DBG_ID_ENGTM,
	DBG_ID_ENGLIB,
	DBG_ID_ENGDM,
	DBG_ID_ENGDW,
	DBG_ID_ENGVM,
	DBG_ID_ENGCM,
	DBG_ID_ENGEDC,
	DBG_ID_MOTORDRV,
	DBG_ID_SENSORDRV,
	DBG_ID_ADCDRV,
	DBG_ID_HVPSDRV,
	DBG_ID_DEVEDRV,
	DBG_ID_FANDRV,
	DBG_ID_CLUTCHDRV,
	DBG_ID_UARTDRV,
	DBG_ID_UARTMSG,
	DBG_ID_SIODRV,
	DBG_ID_SPIDRV,
	DBG_ID_POWERDRV,
	DBG_ID_ENGPIFC,						
	DBG_ID_ENGIH_ENV,		
	DBG_ID_STATE,
	DBG_ID_SEMAPHORE,
	DBG_ID_ENGHAL_LIB,						
	DBG_ID_ENGHAL_GPIO,
	DBG_ID_ENGHAL_I2C,
	DBG_ID_ENGHAL_ENGTIMER,
	DBG_ID_FAST_FPOT,
	DBG_ID_SLEEP_TO_PRINT,
	DBG_ID_TRAY_DOWNLOAD,				
	DBG_ID_CTS,								
	DBG_ID_CSI_TEST,		
	DBG_ID_TONER_SUPPLY,
	DBG_ID_TONER_DRAIN,					
	DBG_ID_FOOTER,							
	DBG_ID_PAPER_INTERVAL_CHECK,
	DBG_ID_HEATING_READY,			
	DBG_ID_MANUAL_DETECT,
	DBG_ID_MAA,
	DBG_ID_MAA_PSEUDO,						
	DBG_ID_OVER_VOLTAGE,
	DBG_ID_SPEED_DOWN,			
	DBG_ID_DEVIATION_CTRL,	
	DBG_ID_ETM_CTRL,						
	DBG_ID_TIMING_CSI,
	DBG_ID_TIMING_DEVICE,		
	DBG_ID_TIMING_ADC,
	DBG_ID_MICOM,			
	DBG_ID_TIMING_SENSOR_SW,
	DBG_ID_TIMING_SENSOR,					
	DBG_ID_TIMING_SENSOR_EMERGENCY,			
	DBG_ID_TIMING_CLUTCH,					
	DBG_ID_TIMING_MOTOR,					
	DBG_ID_TIMING_COMMON_INFO,				
	DBG_ID_TIMING_STATE,
	DBG_ID_TIMING_FAN,
	DBG_ID_ENGWAIT,
	DBG_ID_SENSOR,							
	DBG_ID_LMS_HEADER,						
	DBG_ID_LMS_SA_TIMING_STATE, 			
	DBG_ID_LMS_COMMON_INFO,				
	DBG_ID_LMS_POWER_INFO, 					
	DBG_ID_LMS_ACRCTD_INFO, 				
	DBG_ID_LMS_WAIT_INFO, 					
	DBG_ID_LMS_HVPS_STATUS,					
	DBG_ID_LMS_ASSERT,						
	DBG_ID_LMS_SPECS,						
	DBG_ID_LMS_CONTINUOUS_COUNT,			
	DBG_ID_LMS_DATE,						
	DBG_ID_LMS_STATE,						
	DBG_ID_LMS_ISR_CALL, 					
	DBG_ID_LMS_ISR_EXE,						
	DBG_ID_LMS_VM_COUNT, 					
	DBG_ID_LMS_FPOT,						
	DBG_ID_LMS_FUSER, 						
	DBG_ID_LMS_BIG_DATA,					
	DBG_ID_LMS_STATUS,						
	DBG_ID_LMS_LIFE,						
	DBG_ID_LMS_IMAGE,
	DBG_ID_LMS_PAPER,
	DBG_ID_LMS_DEVICE,
#ifdef FR_EMBEDDED_ENGINE_SIMULATOR
	DBG_ID_EES,
#endif
	DBG_ID_NEWIF,							
	DBG_ID_NEWIF_CORE,						
	DBG_ID_NEWIF_VERIFICATION,				
	DBG_ID_NEWIF_REQINFO,					
	DBG_ID_NEWIF_REQINFO_CORE,				
	DBG_ID_NEWIF_PRINTJOB,					
	DBG_ID_NEWIF_COMMAND,
	DBG_ID_NEWIF_SIMPLEFIED,	
	DBG_ID_NEWIF_DOWNLOAD,
	DBG_ID_MAX
} TDebugId;


typedef struct
{
	TDebugId enId;
	U8 *pubName;
	U32 ulLevel;
	BOOL fPrintToHDD;
	BOOL fPrintToDump;
	BOOL fPrintToUart;
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
 * @brief    Structure for HDD Log
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

#ifdef HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE
	U8 aubLogData[C_HDD_LOG_DATA_SIZE];
#endif
} THDDLogData;

typedef struct
{
	THDDLogData *pstHDDLogData;
	U32 ulLogLevel;
	U32 ulDumpDataHDDPoint;
	BOOL fHDDLogRequestEnable;
} THDDLog;

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
 * @brief    Structure for Engine Log Information.
 */
typedef struct
{
	TLogParamInfo *pstParamInfoTbl;
	TDumpLog *pstDumpLog;
	THDDLog *pstHDDLog;
	TTaskDump *pstTaskDump;
	TUartPrint *pstUartPrint;
} TEngLogInfo;



#endif /* __ENGLOG_TYPES_H__ */

