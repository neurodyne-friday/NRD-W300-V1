/**
 * @file        EngCM_DebugConfig.h
 * @brief       This is type definition file for Timer Service Component.
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


#ifndef __ENGCM_DEBUGCONFIG_H__
#define __ENGCM_DEBUGCONFIG_H__

#undef EXTERN
#ifdef __ENGCM_IF_C__
#define EXTERN
#else
#define EXTERN extern
#endif

/* 
 * define the assert macro
 */
#if defined(ENABLE_EFS_MODE) && !defined(EES_GV_UTE_SIMULATOR)
#include "VD_Library.h"
#endif


#ifdef ENG_DART_ANALYSYS
#define ASSERT(ulGetValue) ( EngOS_Assert(ulGetValue, __FILE__, __LINE__) )
#else
//#define ASSERT(ulGetValue) ( ENGAssert(ulGetValue, __FILE__, __LINE__) )
#if defined(ENABLE_EFS_MODE)
#include <assert.h>
#define VOID_ASSERT(ulGetValue) assert(ulGetValue)
#define VOID_REBOOT_ASSERT(ulGetValue) assert(ulGetValue)
#define ASSERT(ulGetValue) assert(ulGetValue)

#else
#define VOID_ASSERT(ulGetValue) if(!(ulGetValue)){ EngLib_IF_Assert(ulGetValue, __FILE__, __LINE__); return;}
#define VOID_REBOOT_ASSERT(ulGetValue) if(!(ulGetValue)){ EngOS_Assert(ulGetValue, __FILE__, __LINE__); return;}
#define ASSERT(ulGetValue) if(!(ulGetValue)){ EngLib_IF_Assert(ulGetValue, __FILE__, __LINE__); return 0;}
#endif
#endif


//#undef  ASSERT
//#define ASSERT(exp)     			((void)0)


/* 
 * define the print macro
 */

#define ENGINE_DBG
//#define ENG_CSI_DBG
#define ENG_FUSER_DISPLAY_DBG
#define ENG_SENSOR_DISPLAY_DBG
//#define ENG_HAL_SIGNAL_DBG

#define ENG_PRINT		printf


#define DBG_LV0			0
#define DBG_LV1			1
#define DBG_LV2			2
#define DBG_LV3			3

#define C_DEBUG_LV			DBG_LV2
#define C_DEBUG_HDD_LV		DBG_LV1


//For HDD Log
#ifdef HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE
	#define C_HDD_LOG_SAVE_NEW
	#define C_HDD_LOG_START_ADDRESS				0x00A00000
	#define C_HDD_LOG_TOTAL_SIZE				(256*1024)	//256K
	#define C_HDD_LOG_HEADER_SIZE				(4*8)
	#define C_HDD_LOG_DATA_SIZE					(C_HDD_LOG_TOTAL_SIZE - C_HDD_LOG_HEADER_SIZE)

	//Blow is old Hdd Log method
	#define C_HDD_LOG_SEND_SIZE					(2*1000)
	#define C_HDD_LOG_POLLING_INTERVAL			(50)		//500ms
	#define C_HDD_LOG_POLLING_INTERVAL_LV2		(10)		//100ms
	#define C_HDD_LOG_SAVE_TIMEOUT				(500)		//5s
#endif
#define DUMP_DBG_BUFF_SIZE						(150*1024)
#define DUMP_DBG_1LINE_BUFF_SIZE				(150)
#define DUMP_DBG_PRINT_DATA_SIZE				(25)

//For Dump Debug
#ifdef C_HDD_LOG_SAVE_NEW
	#define C_ENG_LOG_STATIC_ADDRESS			0x00A40000				//Engine WatchDog Area
#else
	#define C_ENG_LOG_STATIC_ADDRESS			0x00A40000				//Engine Log Area
#endif
#define C_ENG_LOG_TOTAL_SIZE					(256*1024)	//256K
#define C_ENG_LOG_HEADER_SIZE					(4*8)
#define C_ENG_LOG_DATA_SIZE						(C_ENG_LOG_TOTAL_SIZE - C_ENG_LOG_HEADER_SIZE)
#define C_ENG_LOG_1LINE_BUFF_SIZE				(300)

//For Uart Log
#ifdef FR_ENGLIB_UART_DEBUG
	#define C_ENG_LOG_PRINT_DATA_SIZE			(10)
#endif

//For Task Logging
#define C_TASK_LOG_MSG_Q_MAX 					600
#define C_TASK_LOG_DARG_NUM						7
#define C_TASK_LOG_SARG_SIZE					(C_ENG_LOG_1LINE_BUFF_SIZE/3)

#define ARG_DBUFF_SIZE_IRQ						(C_TASK_LOG_MSG_Q_MAX*3/4*C_TASK_LOG_DARG_NUM)
#define ARG_SBUFF_SIZE_IRQ						(C_TASK_LOG_MSG_Q_MAX*3/4*C_TASK_LOG_SARG_SIZE)
#define ARG_DBUFF_SIZE_TASK						(C_TASK_LOG_MSG_Q_MAX*1/4*C_TASK_LOG_DARG_NUM)
#define ARG_SBUFF_SIZE_TASK		


#ifdef __ENGLOG_LIB_C__
#include "EngLog_Types.h"

TLogParamInfo stLogInfoTbl[] = 
{
	/*	Id									Name						Lv			HDD		Dump	UART	*/
	{	DBG_ID_DUMP_LV0,					"DUMPLV0",					DBG_LV0,	TRUE,	TRUE,	0,		},
	{	DBG_ID_DUMP_LV1,					"DUMPLV1",					DBG_LV1,	TRUE,	TRUE,	0,		},
	{	DBG_ID_DUMP_LV2,					"DUMPLV2",					DBG_LV2,	TRUE,	TRUE,	0,		},
	{	DBG_ID_DUMP_LV3,					"DUMPLV3",					DBG_LV3,	TRUE,	TRUE,	0,		},
	{	DBG_ID_UART,						"UART",						DBG_LV3,	0,		0,		TRUE,	},
	{	DBG_ID_EMERGENCY,					"EMERGENCY",				DBG_LV1,	TRUE,	TRUE,	0,		},
	{	DBG_ID_ENGIFSVC,					"ENGIFSVC",					DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_ENGSM,						"ENGSM",					DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_ENGFOC,						"ENGFOC",					DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_ENGEH,						"ENGEH",					DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_ENGTM,						"ENGTM",					DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_ENGLIB,						"ENGLIB",					DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_ENGCM,						"ENGCM",					DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_MOTORDRV,					"MOTORDRV",					DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_SENSORDRV,					"SENSORDRV",				DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_ADCDRV,						"ADCDRV",					DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_UARTDRV,						"UARTDRV",					DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_UARTMSG,						"UARTMSG",					DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_SPIDRV,						"SPIDRV",					DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_POWERDRV,					"POWERDRV",					DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_STATE,						"STATE",					DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_SEMAPHORE,					"SEMAPHORE",				DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_ENGHAL_LIB,					"ENGHAL_LIB",				DBG_LV2,	0,		TRUE,	0,		},
	{	DBG_ID_ENGHAL_GPIO,					"ENGHAL_GPIO",				DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_ENGHAL_ENGTIMER,				"ENGHAL_ENGTIMER",			DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_SENSOR,						"SENSOR",					DBG_LV3,	0,		0,		0,		},
	{	DBG_ID_LMS_HEADER,					"LMS_HEADER",				DBG_LV1,	0,		0,		0,		},
	{	DBG_ID_LMS_COMMON_INFO,				"LMS_COMMON_INFO",			DBG_LV1,	TRUE,	TRUE,	0,		},
	{	DBG_ID_LMS_POWER_INFO, 				"LMS_POWER_INFO", 			DBG_LV1,	TRUE,	TRUE,	0,		},
	{	DBG_ID_LMS_ASSERT,					"LMS_ASSERT",				DBG_LV1,	TRUE,	0,		0,		},
	{	DBG_ID_LMS_DATE,					"LMS_DATE",					DBG_LV1,	TRUE,	0,		0,		},
	{	DBG_ID_LMS_STATE,					"LMS_STATE",				DBG_LV1,	TRUE,	0,		0,		},
	{	DBG_ID_LMS_BIG_DATA,				"LMS_BIG_DATA",				DBG_LV1,	TRUE,	0,		0,		},
	{	DBG_ID_LMS_STATUS,					"LMS_STATUS",				DBG_LV1,	TRUE,	0,		0,		},
	{	DBG_ID_LMS_LIFE,					"LMS_LIFE",					DBG_LV1,	TRUE,	0,		0,		},
	{	DBG_ID_LMS_DEVICE,					"LMS_DEVICE",				DBG_LV1,	0,		0,		0,		},
};
#endif


EXTERN U32 g_ulEngTick;
EXTERN U32 g_ulEngTimer;
EXTERN U32 g_ulEngTickCnt;
EXTERN U32 g_ulContinuousCnt;
#ifdef __ENGCM_IF_C__
	EXTERN U8 g_aubEngTick[11] = {'0', 0, };
#else
	EXTERN U8 g_aubEngTick[11];
#endif


#ifdef ENGINE_DBG
	#define	ENG_TICK_SET()	(g_ulEngTick = g_ulEngTimer)
	#define	ENG_TICK_CNT	(g_ulEngTickCnt)
	#define	ENG_COUNT()		{(g_ulEngTimer++); g_ulEngTickCnt = ((g_ulEngTimer - g_ulEngTick) << 0); if(sprintf != NULL) sprintf(g_aubEngTick, "%u", ENG_TICK_CNT); else {g_aubEngTick[0] = '0'; g_aubEngTick[1] = '\0';}}
	#define ENG_TICK		(g_aubEngTick)
#else
	#define	ENG_TICK		g_aubEngTick
#endif



#define	ENG_DBG_STRING				"\r\n[%s:%s] "					//T mean RTC Time

#define	ENG_LMS_HEADER_STRING		"\r\n[L] %s; %5d; %s;"
#define	ENG_LMS_MAIN_ITEM_STRING	"\r\n[L] %s; %s;"
#define	ENG_LMS_SUB_ITEM_STRING		" %5d; %s;"
#define	ENG_LMS_DEVICE_STRING		"\r\n[%s:L] %5d %d"				//[EngTick:L] DeviceKey Value 
#define ENG_LMS_SUB_DETAIL_VALUE	"Enum"

#ifdef FR_TM_LMS
#define ENG_LMS_COMMON_TYPE1_SA_INFO	"\r\n[%s:L]"
#define ENG_LMS_COMMON_TYPE2_SA_INFO	"\r\n[%s:L] %5d "
#define ENG_LMS_COMMON_EA_INFO			"\r\n[%s:EA] %5d "
#define ENG_LMS_ACR_EA_INFO				"\r\n[%s:EA] %5d Acr Fail Error : %d "
#define ENG_LMS_CTD_EA_INFO				"\r\n[%s:EA] %5d Ctd Fail Error : %d "
#define ENG_LMS_WAIT_SA_INFO			"\r\n[%s:L] %5d %d %d "	
#define ENG_LMS_DATE_SA_INFO			"\r\n[%s:L] %5d %s "
#define	ENG_LMS_STATE_INFO				"\r\n[%s:L] %5d %d"	
#define	ENG_LMS_LIFE_MONO_INFO			"\r\n[%s:L] %5d %d %d"	
#define	ENG_LMS_LIFE_COLOR_INFO			"\r\n[%s:L] %5d %d %d %d %d %d"	
#define ENG_LMS_ITEM_ISR_CALL_INFO_1	"\r\n[%8d:L] %5d %d %d "
#define ENG_LMS_ITEM_ISR_CALL_INFO_2	"\r\n[%s:L] %5d %d %d "
#define ENG_LMS_ITEM_ISR_EXE_INFO_1		"\r\n[%8d:L] %5d %d %d "
#define ENG_LMS_ITEM_ISR_EXE_INFO_2		"\r\n[%s:L] %5d %d %d "
#define ENG_LMS_ITEM_VM_COUNT_INFO		"\r\n[%s:L] %5d %d "
#ifdef FR_SM_SLEEP_TO_PRINT	
#define ENG_LMS_ITEM_FPOT_INFO			"\r\n[%s:L] %5d %d "
#else
#define ENG_LMS_ITEM_FPOT_INFO			"\r\n[%d:L] %5d %d "
#endif
#define ENG_LMS_BIG_DATA_ERROR			"\r\n[%s:L] Ciritical Error "
#define ENG_LMS_BIG_DATA_HEADER			"\r\n[%s:BD] %d %d"
#define ENG_LMS_BIG_DATA_COMMENT		"\r\n// %s"
#define ENG_LMS_BIG_DATA_INFO			"\r\n¨Õ "
#define ENG_LMS_BIG_DATA_DATA			"\r\n¨Ð "

#define ENG_LMS_VALUE1_STRING		" (%d)"
#define ENG_LMS_VALUE2_STRING		" (%d %d)"
#define ENG_LMS_VALUE3_STRING		" (%d %d %d)"
#define ENG_LMS_VALUE4_STRING		" (%d %d %d %d)"
#define ENG_LMS_VALUE5_STRING		" (%d %d %d %d %d)"
#endif


#ifdef ENGINE_DBG
	#define DBG_ENG								ENG_PRINT
	#define DBG_EMERGENCY_UART					ENG_PRINT
	#define DBG_UART							EngLog_IF_PrintToUart//EngLog_IF_DumpPrintToUart
	#define DBG_SWO								EngLog_IF_PrintToSWO//EngLog_IF_DumpPrintToUart
	#define DBG_ENGHAL_CAN_TO_SWO				//EngLog_IF_PrintToSWO
	#define DBG_EMERGENCY						EngLog_IF_DumpPrintEmergency
	#define DBG_ENGIFSVC						EngLog_IF_DumpPrintEngIFSvc
	#define DBG_ENGTMSVC		
	#define DBG_ENGSM							EngLog_IF_DumpPrintEngSM
	#define DBG_ENGMH							EngLog_IF_DumpPrintEngMH
#if defined(ENG_PC_SIM) && !defined(ENG_BOARD_SIM)
	#define DBG_ENGEH							ENG_PRINT
#else
	#define DBG_ENGEH							EngLog_IF_DumpPrintEngEH
#endif
	#define DBG_ENGTM							EngLog_IF_DumpPrintEngTM
	#define DBG_ENGLIB							EngLog_IF_DumpPrintEngLib
	#define DBG_ENGCM							EngLog_IF_DumpPrintEngCM
	#define DBG_UARTDRV							EngLog_IF_DumpPrintUartDrv
	#define DBG_UARTMSG							EngLog_IF_DumpPrintUartMsg
	#define DBG_SPIDRV							EngLog_IF_DumpPrintSPIDrv
	#define DBG_POWERDRV						EngLog_IF_DumpPrintFowerDrv
		
#if defined(ENG_PC_SIM) && !defined(ENG_BOARD_SIM)
	#define DBG_STATE							ENG_PRINT
#else
	#define DBG_STATE							EngLog_IF_DumpPrintState
#endif

	#define DBG_SEMAPHORE						EngLog_IF_DumpPrintSemaphore
	#define DBG_ENGHAL_LIB						EngLog_IF_DumpPrintEngHalLib
	#define DBG_ENGHAL_GPIO						EngLog_IF_DumpPrintEngHalGPIO
	#define DBG_ENGHAL_ENGTIMER					EngLog_IF_DumpPrintEngHalEngTimer
	
	#define DBG_TIMING_CSI
	
	#define DBG_TIMING_DEVICE					EngLog_IF_DumpPrintTimingDevice
	#define DBG_TIMING_ADC						EngLog_IF_DumpPrintTimingADC

#if defined(ENG_PC_SIM) && !defined(ENG_BOARD_SIM)
	#define DBG_TIMING_SENSOR_SW				ENG_PRINT
	#define DBG_TIMING_SENSOR
	#define DBG_TIMING_SENSOR_EMERGENCY			ENG_PRINT
	#define DBG_TIMING_CLUTCH					ENG_PRINT
	#define DBG_TIMING_MOTOR					ENG_PRINT
	#define DBG_TIMING_COMMON_INFO				ENG_PRINT	
	#define DBG_TIMING_FAN						ENG_PRINT
#else
	#define DBG_TIMING_SENSOR_SW				EngLog_IF_DumpPrintTimingSensorSW
	#define DBG_TIMING_SENSOR					EngLog_IF_DumpPrintTimingSensor
	#define DBG_TIMING_SENSOR_EMERGENCY			EngLog_IF_DumpPrintTimingSensorEmergency
	#define DBG_TIMING_MOTOR					EngLog_IF_DumpPrintTimingMotor
	#define DBG_TIMING_COMMON_INFO				EngLog_IF_DumpPrintTimingCommonInfo	
	#define DBG_TIMING_FAN						EngLog_IF_DumpPrintTimingFan
#endif

	#define DBG_TIMING_STATE					EngLog_IF_DumpPrintTimingState
		
	#define DBG_TEMP_TEST						EngLog_IF_DumpPrintTempTest

#ifdef FR_TM_LMS
	#define DBG_LMS_HEADER						EngLog_IF_DumpPrintLMSHeader
	#define DBG_LMS_SA_TIMING_STATE 			EngLog_IF_DumpPrintLMSSATimingState
			
	#define DBG_LMS_COMMON_INFO					EngLog_IF_DumpPrintLMSCommonInfo
	#define DBG_LMS_POWER_INFO 					EngLog_IF_DumpPrintLMSPowerInfo
	#define DBG_LMS_ACRCTD_INFO 				EngLog_IF_DumpPrintLMSAcrCtdInfo
	#define DBG_LMS_WAIT_INFO 					EngLog_IF_DumpPrintLMSWaitInfo
	#define DBG_LMS_HVPS_STATUS					EngLog_IF_DumpPrintLMSHVPSStatus
	#define DBG_LMS_ASSERT						EngLog_IF_DumpPrintLMSAssert	
	#define DBG_LMS_SPECS						EngLog_IF_DumpPrintLMSSpecs	
	#define DBG_LMS_CONTINUOUS_COUNT			EngLog_IF_DumpPrintLMSContinuousCount
	#define DBG_LMS_DATE						EngLog_IF_DumpPrintLMSDate	
	#define DBG_LMS_STATE						EngLog_IF_DumpPrintLMSState	
	#define DBG_LMS_ISR_CALL 					EngLog_IF_DumpPrintLMSISRCall
	#define DBG_LMS_ISR_EXE						EngLog_IF_DumpPrintLMSISRExecute
	#define DBG_LMS_VM_COUNT 					EngLog_IF_DumpPrintLMSVMCount
	#define DBG_LMS_FPOT						EngLog_IF_DumpPrintLMSFPOT
	#define DBG_LMS_FUSER 						EngLog_IF_DumpPrintLMSFuser
	#define DBG_LMS_BIG_DATA					EngLog_IF_DumpPrintLMSBigData
	#define DBG_LMS_STATUS						EngLog_IF_DumpPrintLMSStatus	
	#define DBG_LMS_LIFE						EngLog_IF_DumpPrintLMSLife	
	#define DBG_LMS_IMAGE						EngLog_IF_DumpPrintLMSImage
	#define DBG_LMS_PAPER						EngLog_IF_DumpPrintLMSPaper
	#define DBG_LMS_DEVICE						EngLog_IF_DumpPrintLMSDevice
#endif	

#ifdef FR_EMBEDDED_ENGINE_SIMULATOR
	#define DBG_EES								EngLog_IF_DumpPrintEES
#endif

	#define DBG_NEWIF							EngLog_IF_DumpPrintLMSNewIF
	#define DBG_NEWIF_CORE						EngLog_IF_DumpPrintNewIFCore
	#define DBG_NEWIF_VERIFICATION				EngLog_IF_DumpPrintNewIFVerification
	#define DBG_NEWIF_REQINFO					EngLog_IF_DumpPrintNewIFRequestInfo
	#define DBG_NEWIF_REQINFO_CORE				EngLog_IF_DumpPrintNewIFRequestInfoCore
	#define DBG_NEWIF_PRINTJOB					EngLog_IF_DumpPrintNewIFPrintJob
	#define DBG_NEWIF_COMMAND					EngLog_IF_DumpPrintNewIFCommand
	#define DBG_NEWIF_SIMPLEFIED				EngLog_IF_DumpPrintNewIFSimplefied
	#define DBG_NEWIF_DOWNLOAD					EngLog_IF_DumpPrintNewIFDownload
#else
	#define DBG_ENG
	#define DBG_EMERGENCY_UART					
	#define DBG_EMERGENCY
	#define DBG_ENGIFSVC
	#define DBG_ENGTMSVC
	#define DBG_ENGSM
	#define DBG_ENGEH
	#define DBG_ENGTM
	#define DBG_ENGLIB
	#define DBG_ENGDM
	#define DBG_ENGDW
	#define DBG_ENGVM
	#define DBG_ENGCM
	#define DBG_ENGEDC
	#define DBG_CRUMDRV 	
	#define DBG_EASYCHIPDRV					
	#define DBG_FUSERDRV
	#define DBG_LSUDRV
	#define DBG_MOTORDRV
	#define DBG_SENSORDRV
	#define DBG_ADCDRV			//ENG_DUMP_LV3
	#define DBG_HVPSDRV			
	#define DBG_DEVEDRV			
	#define DBG_FANDRV			
	#define DBG_CLUTCHDRV		
	#define DBG_UARTDRV		
	#define DBG_UARTMSG				//ENG_DUMP_LV3
	#define DBG_SIODRV
	#define DBG_SPIDRV
	#define DBG_OPTIONTRAYDRV
	#define DBG_OPTIONFINISHERDRV
	#define DBG_POWERDRV
	
	#define DBG_ENGPIFC
	#define DBG_ENGIH_ENV
	#define DBG_OPTIONTRAY_RESET
	#define DBG_OPTIONTRAY_MULTI
	#define DBG_OPTIONTRAY_ALLMTR
	#define DBG_OPTIONTRAY_FEEDSEN
	#define DBG_FINISHER_IF
	#define DBG_FINISHER_DOWNLOAD

	#define DBG_STATE
	#define DBG_SEMAPHORE

	#define DBG_ENGHAL_LIB
	#define DBG_ENGHAL_GPIO
	#define DBG_ENGHAL_I2C	
	#define DBG_ENGHAL_ENGTIMER

	#define DBG_FAST_FPOT
	#define DBG_SLEEP_TO_PRINT	
	#define DBG_TRAY_DOWNLOAD
	#define DBG_CTS
	#define DBG_CSI_TEST
	#define DBG_TONER_SUPPLY
	#define DBG_TONER_DRAIN
	#define DBG_FOOTER
	#define DBG_PAPER_INTERVAL_CHECK
	#define DBG_HEATING_READY
	#define DBG_MANUAL_DETECT
	#define DBG_MAA
	#define DBG_MAA_PSEUDO
	#define DBG_OVER_VOLTAGE
	#define DBG_FUSER_IDLING
	#define DBG_FUSER_PPS_CHANGE		
	#define DBG_BAND_CTRL
	#define DBG_ULTRA_LL_CTRL
	#define DBG_FUSER_GAP
	#define DBG_SPEED_DOWN			
	#define DBG_DOT_COUNT
	#define DBG_NANO_DUST
	
	#define DBG_CHARGER_CTRL
	#define DBG_DEVELOPMENT_CTRL	
	#define DBG_EXPOSER_CTRL
	#define DBG_TRANSFER_CTRL
	#define DBG_MICOM_CTRL					

	#define DBG_DEVIATION_CTRL
	#define DBG_ETM_CTRL
	#define DBG_VIRTUAL_PRINT_CTRL
	
	#define DBG_TIMING_CSI
	
	#define DBG_TIMING_DEVICE
	#define DBG_TIMING_ADC
	#define DBG_TIMING_HVPS
	#define DBG_TIMING_SENSOR_SW
	#define DBG_TIMING_SENSOR
	#define DBG_TIMING_SENSOR_EMERGENCY	
	#define DBG_TIMING_CLUTCH
	#define DBG_TIMING_MOTOR
	#define DBG_TIMING_FUSER
	#define DBG_TIMING_LSU
	#define DBG_TIMING_STATE
	#define DBG_TIMING_COMMON_INFO
	#define DBG_TIMING_FAN

	#define DBG_ENGWAIT
	#define	DBG_ENGCTD
	#define DBG_IDCCTRL_VITAL
	#define DBG_CTDDRV
	#define DBG_SENSOR
	#define DBG_FUSER_TEMP
	#define DBG_NCTH_FUSER_TEMP
	#define DBG_MICOM			

	#define	DBG_ACRCTRL
	#define	DBG_ACRSTATE
	#define DBG_ACRDRV

#ifdef FR_TM_LMS
	#define DBG_LMS_HEADER
	#define DBG_LMS_SA_TIMING_STATE 
			
	#define DBG_LMS_COMMON_INFO			
	#define DBG_LMS_POWER_INFO 			
	#define DBG_LMS_ACRCTD_INFO 		
	#define DBG_LMS_WAIT_INFO 			
	#define DBG_LMS_HVPS_STATUS			
	#define DBG_LMS_ASSERT					
	#define DBG_LMS_SPECS					
	#define DBG_LMS_CONTINUOUS_COUNT	
	#define DBG_LMS_DATE					
	#define DBG_LMS_STATE					
	#define DBG_LMS_ISR_CALL 			
	#define DBG_LMS_ISR_EXE				
	#define DBG_LMS_VM_COUNT 			
	#define DBG_LMS_FPOT				
	#define DBG_LMS_FUSER 				
	#define DBG_LMS_BIG_DATA			
	#define DBG_LMS_STATUS	
	#define DBG_LMS_LIFE
#endif	
#ifdef FR_EMBEDDED_ENGINE_SIMULATOR
	#define DBG_EES
#endif
	#define DBG_NEWIF
	#define DBG_NEWIF_CORE
	#define DBG_NEWIF_VERIFICATION
	#define DBG_NEWIF_REQINFO
	#define DBG_NEWIF_REQINFO_CORE				
	#define DBG_NEWIF_PRINTJOB
	#define DBG_NEWIF_COMMAND
	#define DBG_NEWIF_SIMPLEFIED
	#define DBG_NEWIF_DOWNLOAD
#endif	//ENGINE_DBG


#ifndef ENG_CSI_DBG
#undef DBG_TIMING_CSI
#define DBG_TIMING_CSI
#endif

#ifndef ENG_FUSER_DISPLAY_DBG
#undef DBG_FUSER_TEMP
#define DBG_FUSER_TEMP
#endif

#ifndef ENG_SENSOR_DISPLAY_DBG
#undef DBG_TIMING_SENSOR_SW
#define DBG_TIMING_SENSOR_SW
#endif


/* 
 * define the common test
 */

//#define ENG_CONTINUOUS_TEST

//#define ENG_JAM_FREE_TEST


#endif /* __ENGCM_DEBUGCONFIG_H__ */

