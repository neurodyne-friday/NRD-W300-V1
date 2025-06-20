 /**
 * @file        Eng_CommonType.h
 * @brief       This is type definition file for common
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
 * @dept		Embedded Developement Team
 * @date		19/02/2024(D/M/Y)
 * @version		V0.1
 */


#ifndef __ENG_COMMONTYPE_H__
#define __ENG_COMMONTYPE_H__

//#define ENG_PC_SIM
//#define ENG_BOARD_SIM
//#define ENG_VPL


#define PRIVATE	static

#include "Eng_Macro.h"


#define GET_LOW_WORD(a) 			(U16)(a & 0x0000ffff)
#define GET_HIGH_WORD(a)			(U16)((a & 0xffff0000) >> 16)
#define GET_LOW_BYTE(a) 			(U8)(a & 0x00ff)
#define GET_HIGH_BYTE(a)			(U8)((a & 0xff00) >> 8)
#define GET_TWO_WORD(a,b)			(U32)((a & 0xffff0000)|(b & 0x0000ffff))


#define	SET_BIT(dest, position)					((dest) |=  (0x1 << (position)))
#define	CLEAR_BIT(dest, position)				((dest) &= ~(0x1 << (position)))
#define	INVERT_BIT(dest, position)				((dest) ^=  (0x1 << (position)))

#define	SET_BITS(dest, bits, position)			((dest) |=  (((unsigned)bits) << (position)))
#define	CLEAR_BITS(dest, bits, position)		((dest) &= ~(((unsigned)bits) << (position)))
#define	INVERT_BITS(dest, bits, position)		((dest) ^=  (((unsigned)bits) << (position)))

#define	WRITE_BITS(dest, bits, data, position)	((dest) = ((unsigned)dest) & ~(((unsigned)bits) << (position)) | (((unsigned)data) << (position)))

#define CHECK_BIT_SET(dest, position)			((((unsigned)dest) >> (position)) & 0x1)
#define CHECK_BIT_CLEAR(dest, position)			(!((((unsigned)dest) >> (position)) & 0x1))

#define READ_BITS(dest, bits, position)			((((unsigned)dest) >> (position)) & (bits))


/*
 * Fixed Operation Macro
 *
 * FIX_ASSIGN( 3, 4)-> 3.04
 * FIX_ASSIGN(10,60)->10.60
 */

typedef unsigned long					FIX32;		/* For fixed point operation */

#define FIX_ASSIGN(i,p)	((FIX32)(i * 100L + p))
#define FIX_ADD(f1,f2)	((FIX32)(f1 + f2))
#define FIX_SUB(f1,f2)	((FIX32)(f1 - f2))
#define FIX_MUL(f1,f2)	((FIX32)((f1 * f2) / 100L))
#define FIX_DIV(f1,f2)	((FIX32)(f1 * 100L / f2))
#define FIX_INT(f)		(f / 100L)
#define FIX_POINT(f)	((f >= 0) ? (f % 100) : (-f % 100))


static inline void NullFunction(void){ }

#undef NULL
#define NULL							0

#ifndef UP
#define UP                              TRUE
#endif
#ifndef DOWN
#define DOWN                            FALSE
#endif

#define UPDOWN							2

#define START							TRUE
#define END								FALSE

#define T_BOOL	0
#define T_S8	1
#define T_U8	2
#define T_S16	3
#define T_U16	4
#define T_S32	5
#define T_U32	6
#define T_S64	7
#define T_U64	8
#define T_FLOAT	9

#define	EQ		==
#define	NE		!=
#define	LT		<
#define LE		<=
#define GT		>
#define GE		>=

#define BIT_NONE	0x00000000
#define BIT_0		0x00000001
#define BIT_1		0x00000002
#define BIT_2		0x00000004
#define BIT_3		0x00000008
#define BIT_4		0x00000010
#define BIT_5		0x00000020
#define BIT_6		0x00000040
#define BIT_7		0x00000080
#define BIT_8		0x00000100
#define BIT_9		0x00000200
#define BIT_10		0x00000400
#define BIT_11		0x00000800
#define BIT_12		0x00001000
#define BIT_13		0x00002000
#define BIT_14		0x00004000
#define BIT_15		0x00008000
#define BIT_16		0x00010000
#define BIT_17		0x00020000
#define BIT_18		0x00040000
#define BIT_19		0x00080000
#define BIT_20		0x00100000
#define BIT_21		0x00200000
#define BIT_22		0x00400000
#define BIT_23		0x00800000
#define BIT_24		0x01000000
#define BIT_25		0x02000000
#define BIT_26		0x04000000
#define BIT_27		0x08000000
#define BIT_28		0x10000000
#define BIT_29		0x20000000
#define BIT_30		0x40000000
#define BIT_31		0x80000000


#define PERCENT30	30
#define PERCENT40	40
#define PERCENT50	50
#define PERCENT60	60
#define PERCENT70	70
#define PERCENT80	80
#define PERCENT90	90
#define PERCENT100	100

#define TYPE_NONE	0
#define TYPE_1		1
#define TYPE_2		2
#define TYPE_3		3
#define TYPE_4		4
#define TYPE_5		5
#define TYPE_6		6
#define TYPE_7		7
#define TYPE_8		8
#define TYPE_9		9

#define STEP_1ST	1
#define STEP_2ND	2
#define STEP_3RD	3
#define STEP_4TH	4
#define STEP_5TH	5

#if (C_ENG_TIMER_PERIOD == C_ENG_TIMER_1MS)
#define T1MS		1
#define T2MS		(T1MS << 1)	//(2*T2MS)
#define T10MS		(5*T2MS)
#elif (C_ENG_TIMER_PERIOD == C_ENG_TIMER_2MS)
#define T1MS		0
#define T2MS		1
#define T10MS		(5*T2MS)
#elif (C_ENG_TIMER_PERIOD == C_ENG_TIMER_10MS)
#define T1MS		0
#define T2MS		0x10000001
#define T10MS		1
#endif

#define T100MS		(10*T10MS)
#define T1S			(10*T100MS)
#define T1M			(60*T1S)
#define T1H			(60*T1M)

///<#ifdef FR_TM_LMS
#define ENGINE_SM_STATE_KEY_BASE		50000
#define ENGINE_PH_STATE_KEY_BASE		51000
#define ENGINE_IH_STATE_KEY_BASE		52000
#define ENGINE_HH_STATE_KEY_BASE		53000
#define ENGINE_OH_STATE_KEY_BASE		54000

#define ENGINE_SM_INFO_KEY_BASE			60000	// System Info in LMS
#define ENGINE_SA_ITEM_KEY_BASE			70000	// Items for SA in LMS

typedef enum _TModuleState 
{
	MD_WAIT_STATE  = 0,
	MD_READY_STATE,
	MD_RUN_STATE,
    MD_ERROR_STATE,
    MD_RECOVERY_STATE,
    MD_SLEEP_STATE,
    MD_LOWPOWER_STATE,
    MD_POWERON_STATE,
    MD_NONE_STATE
} TModuleState;

typedef struct _TErrorDB
{
    U16 uwCode;
    U8 ubStatus;
	U8 ubReserved;
} TErrorDB;

typedef enum
{
	INTERVAL_TIME_JOB,
	INTERVAL_TIME_POWER_OFF,
	INTERVAL_TIME_SLEEP,
	INTERVAL_TIME_READY,
	INTERVAL_TIME_MAX,
	INTERVAL_TIME_UNSPECIFIED = INTERVAL_TIME_MAX
} TIntervalTimeType;

typedef enum
{
	INIT_STEP_1ST		= (0x1 << 0),
	INIT_STEP_2ND		= (0x1 << 1),
	INIT_STEP_3RD		= (0x1 << 2),
	INIT_STEP_4TH		= (0x1 << 3),
	INIT_STEP_ALL		= 0x0FFFFFFF,
	INIT_STEP_FINISH	= (0x1 << 31)
} TInitialStepType;


typedef enum
{
	HUMIDITY_NORMAL,
	HUMIDITY_H1,
	HUMIDITY_H2,
	HUMIDITY_H3,
	HUMIDITY_H4	
} TEngHumidity;


typedef enum
{
	ENVIRONMENT_ID0,
	ENVIRONMENT_ID1,
	ENVIRONMENT_ID2,
	ENVIRONMENT_ID3,
	ENVIRONMENT_ID4,
	ENVIRONMENT_ID5,
	ENVIRONMENT_ID6,
	ENVIRONMENT_ID7,
	ENVIRONMENT_ID8,
	ENVIRONMENT_ID9,
	ENVIRONMENT_ID10,
	ENVIRONMENT_UNSPECIFIED
} TEngEnvironmentIndex;


typedef enum
{
    UK           = 0,
    FRANCE       = 1,
    AUSTRIA      = 2,
    SWITZERLAND  = 3,
    ITALY        = 4,
    SPAIN        = 5,
    PORTUGAL     = 6,
    NORWAY       = 7,
    FINLAND      = 8,
    SWEDEN       = 9,
    NETHERLANDS  = 10,
    DENMARK      = 11,
    BELGIUM      = 12,
    HUNGARY      = 13,
    POLAND       = 14,
    CZECH        = 15,
    ROMANIA      = 16,
    BULGARIA     = 17,
    IRELAND      = 18,
    GERMANY      = 19,
    GREECE       = 20,
    TURKEY       = 21,
    RUSSIA       = 22,
    SOUTHAFRICA  = 23,
    INDIA        = 24,
    SRILANKA     = 25,
    USA          = 26,
    CANADA       = 27,
    BRAZIL       = 28,
    CHILE        = 29,
    MEXICO       = 30,
    ARGENTINA    = 31,
    PERU         = 32,
    OMAN         = 33,
    BANGLADESH   = 34,
    KUWAIT       = 35,
    MOROCO       = 36,
    ALGERIA      = 37,
    PAKISTAN     = 38,
    UAE          = 39,
    HONGKONG     = 40,
    UKRAINE      = 41,
    KAZAKHSTAN   = 42,
    UZBEKISTAN   = 43,
    ESTONIA      = 44,
    LATVIA       = 45,
    LITHUANIA    = 46,
    PUERTORICO   = 47,
    VENEZUELA    = 48,
    AUSTRALIA    = 49,
    TAIWAN       = 50,
    SINGAPORE    = 51,
    KOREA        = 52,
    LUXEMBOURG   = 53,
    COLOMBIA     = 54,
    SAUDIARABIA  = 55,
    ISRAEL       = 56,
    IRAN         = 57,
    URUGUAY      = 58,
    CHINA        = 59,
    THAILAND     = 60,
    TRINIDAD     = 61,
    EGYPT        = 62,
    JORDAN       = 63,
    LEBANON      = 64,
    QATAR        = 65,
    TUNISIA      = 66,
    YEMEN        = 67,
    CYPRUS       = 68,
    ICELAND      = 69,
    YUGOSLAVIA   = 70,
    NEWZEALAND   = 71,
    MALAYSIA     = 72,
    PANAMA       = 73,
    SLOVENIA     = 74,
    CROATIA      = 75,
    SERBIA       = 76,
    GUATEMALA    = 77,
    ECUADOR      = 78,
    COSTARICA    = 79,
    DOMINICANREPUBLIC  = 80,
    NETHERLANDARTILLES = 81,
    ARTIGUA      = 82,
    BAHAMAS      = 83,
    BARBADOS     = 84,
    BELIZE       = 85,
    BERMUDA      = 86,
    BONAIRE      = 87,
    ELSALVADOR   = 88,
    GRANDCAYMAN  = 89,
    GUYANA       = 90,
    HAITI        = 91,
    HONDURAS     = 92,
    JAMICA       = 93,
    SURINAME     = 94,
    TURKSCAICOS  = 95,
    BOLIVIA      = 96,
    GRENADA      = 97,
    PARAGUAY     = 98,
    STVINCENT    = 99,
    STMAARTEN    = 100,
    STLUCIA      = 101,
    IRAQ         = 102,
    BAHRAIN      = 103,
    NICARAGUA    = 104,
    SLOVAKIA     = 105,
    INDONESIA    = 106,
    VIETNAM      = 107,
    CAMBODIA     = 108,
    PHILIPPINES  = 109,
    SYRIA        = 110,
    MALTA        = 111,
    LIECHTENSTEIN = 112,
    ALBANIA      = 113,
    MACEDONIA    = 114,
    BOSNIA       = 115,
    LAOS         = 116,
    NEPAL        = 117,
    LIBYA        = 118,
    NIGERIA      = 119,
    KENYA        = 120,
    TANZANIA     = 121,
    SUDAN        = 122,
    PALESTINE    = 123,
	MONTENEGRO   = 124,
    MAXCOUNTRY   = 125
} TCountry;


typedef enum
{
	ENG_ST_WARMUP 	    = 0,
	ENG_ST_STANDBY,
	ENG_ST_ACTIVE,
	ENG_ST_SLEEP,
	ENG_ST_ERROR,
	ENG_ST_RECOVERY,
	ENG_ST_WAIT,
	ENG_ST_EDC,         // EDC(Electronic Data Capture)
	ENG_ST_TEST,
	ENG_ST_POWERON,	
	ENG_ST_MAX
} TEngState;



#ifdef WIN32
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <memory.h>
#include <conio.h>
#else
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "stdlib.h"
#endif


#include "EngCM_DebugConfig.h"

#include "EngLib_Types.h"

#include "Eng_FeatureType.h"
#include "Eng_MessageType.h"
#include "Eng_StatusType.h"
#include "EngSM_Types.h"

#include "EngCM_FeatureConfig.h"
#include "EngCM_SystemConfig.h"
#include "EngCM_SystemMgrConfig.h"
#include "EngCM_DriverConfig.h"
#include "EngCM_ErrorHndConfig.h"
#include "EngCM_HalConfig.h"

#include "EngLib_IF.h"
#include "EngLib_Main.h"
#include "EngLog_IF.h"
#include "EngOS_Lib.h"

#include "EngFOC_Types.h"
//#include "EngEH_Types.h"

#include "EngDrv_IF.h"

#include "EngHAL_Lib.h"

#endif // __ENG_COMMONTYPE_H__

