 /**
 * @file        Eng_Macro.h
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
 * author	Jeongseob Kim
 * imp		Jeongseob Kim
 * dept		Embedded Developement Team
 * date		19/02/2024(D/M/Y)
 * version	V0.1
 */

#ifndef __ENG_MACRO_H__
#define __ENG_MACRO_H__


#ifndef BOOL
//typedef int                             BOOL;
typedef unsigned char                   BOOL;
#endif
typedef unsigned char                   U8;         /* Size of 1 U8  base on ARM Compiler   */
typedef signed char                     S8;         /* Size of 1 U8  base on ARM Compiler   */
typedef unsigned short                  U16;        /* Size of 2 bytes base on ARM Compiler */
typedef signed short                    S16;        /* Size of 2 bytes base on ARM Compiler */
typedef unsigned long                   U32;        /* Size of 4 bytes base on ARM Compiler */
typedef signed long                     S32;        /* Size of 4 bytes base on ARM Compiler */
typedef float                           F32;        /* Size of 4 bytes base on ARM Compiler */
typedef double                          D32;        /* Size of 8 bytes base on ARM Compiler */

typedef volatile unsigned char          REG8;
typedef volatile unsigned short         REG16;
typedef volatile unsigned long          REG32;

#ifndef NULL
//    #ifdef __cplusplus
        #define NULL 0
//    #else
//        #define NULL ((void *)0)
//    #endif
#endif

#ifndef TRUE
#define TRUE                            1
#endif
#ifndef FALSE
#define FALSE                           0
#endif

#ifndef ON
#define ON                              TRUE
#endif
#ifndef OFF
#define OFF                             FALSE
#endif

#ifndef YES
#define YES                             TRUE        /**< Signal not to use something */
#endif
#ifndef NO
#define NO                              FALSE       /**< Signal to use something */ 
#endif

#ifndef SUPPORT
#define SUPPORT                         TRUE
#endif
#ifndef NOT_SUPPORT
#define NOT_SUPPORT                     FALSE
#endif

#define EOF                             (-1)

#define MAX_U8                          255
#define MAX_S8                          127
#define MIN_S8                          (-128)
                                        
#define MAX_U16                         65535
#define MAX_S16                         32767 
#define MIN_S16                         (-32768)
                                        
#define MAX_U32                         0xffffffff
#define MAX_S32                         2147483647
#define MIN_S32                         (-2147483647-1)


#define MIN(a,b)                        ((a) < (b) ? (a):(b))
#define MAX(a,b)                        ((a) < (b) ? (b):(a))
#define ABS(x)                          ( (x) >= 0 ? (x) : -(x) )
#define ARRAY_SIZE(x)                   (sizeof(x)/sizeof(x[0]))
#define CONVERT_BIG_ENDIAN_16(x)        ((( (x) >> 8) & 0x00FFU) | (( (x) << 8) & 0xFF00U) )
#define CONVERT_BIG_ENDIAN_32(x)        ((( (x) << 24) & 0xFF000000UL) \
                                        | (((x) << 8)  & 0x00FF0000UL) \
                                        | (((x) >> 8)  & 0x0000FF00UL) \
                                        | (((x) >> 24) & 0x000000FFUL))

#define SWAP(x, y)                      do {                    \
                                                int z;          \
                                                z = *x;         \
                                                *x = *y;        \
                                                *y = z;         \
                                        } while (0)

#define SEC_TO_MS(sec)			(((sec) > MAX_U32 / 1000) ? MAX_U32 : (sec) * 1000)
#define MINUTE_TO_MS(minute)		(((minute) > MAX_U32 / 60 / 1000) ? MAX_U32 : (minute) * 60 * 1000)
#define MS_TO_SEC(ms)			((ms) / 1000)
#define MS_TO_MINUTE(ms)		((ms) / 60 / 1000)


/*Size definition*/
#define _1KBYTE         0x00000400
#define _4KBYTE         0x00001000
#define _8KBYTE         0x00002000
#define _16KBYTE        0x00004000
#define _32KBYTE        0x00008000
#define _64KBYTE        0x00010000
#define _128KBYTE       0x00020000
#define _256KBYTE       0x00040000
#define _512KBYTE       0x00080000

#define _1MBYTE         0x00100000
#define _2MBYTE         0x00200000
#define _4MBYTE         0x00400000
#define _8MBYTE         0x00800000
#define _16MBYTE        0x01000000
#define _32MBYTE        0x02000000
#define _64MBYTE        0x04000000
#define _128MBYTE       0x08000000
#define _256MBYTE       0x10000000
#define _512MBYTE       0x20000000

#define _1GBYTE         0x40000000
#define _2GBYTE         0x80000000

#if defined(__GNUC__)
#define PACKED_TYPEDEF              typedef
#define _WRS_PACK_ALIGN(x) 			__attribute__((packed, aligned(x)))
#define _WRS_DATA_ALIGN_BYTES(x) 	__attribute__((aligned(x)))
#define WRS_PACK_ALIGN(x)			_WRS_PACK_ALIGN(x)
#define WRS_DATA_ALIGN_BYTES(x)		_WRS_DATA_ALIGN_BYTES(x)
#else
#define PACKED_TYPEDEF              __packed typedef
#define WRS_PACK_ALIGN(x)			
#define WRS_DATA_ALIGN_BYTES(x)
#endif

/*******************************  Macro  *******************************/
#define	REGI_ADDR(X)			&(X)

// #define SET_BIT(BitPort, BitNum)        BitPort |= ((U32)1<<(BitNum))
// #define CLR_BIT(BitPort, BitNum)        BitPort &= (~((U32)1<<(BitNum)))     
// #define TGL_BIT(val,bit)	        (val)   ^= ((U32)1<<(bit))

//Sum and detect overflow */
#define U32_SUM_CHK_WITH_OVF(a,b)	(((a&b&0x80000000) || (((a&0x7FFFFFFF) + (b&0x7FFFFFFF)) & 0x80000000)) ? 0xFFFFFFFF : a+b)
                                      
/*******************************  Device and OS dependency  *******************************/

#define STM32F4XX_SUPPORT
//#define STM32F7XX_SUPPORT

#if defined(STM32F4XX_SUPPORT)
#include "stm32f4xx.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_can.h"
//#include "stm32f4xx_hal_can_legacy.h"
#elif defined(STM32F7XX_SUPPORT)
#include "stm32f7xx.h"
#include "stm32f7xx_hal_flash.h"
//#include "stm32f7xx_hal_can.h"
//#include "stm32f7xx_hal_can_legacy.h"
#endif

#define OS_SUPPORT_RTOS
//#define OS_SUPPORT_UCOS

#ifdef OS_SUPPORT_UCOS
//#include "bsp.h"
#include "os.h"
//#include "os_utilities.h"
#include "includes.h"
#elif defined(OS_SUPPORT_RTOS)
#endif


//#define     __IO    volatile             /*!< Defines 'read / write' permissions */
//typedef __IO uint32_t  vu32;
//typedef __IO uint16_t vu16;
//typedef __IO uint8_t  vu8;

                                      
#define VU8             REG8
#define VU16            REG16
#define VU32            REG32

extern VU32 g_vu32GlobalTime;
extern VU16 g_vu16GlobalShortTime;
extern VU32 g_vu32Timer;
extern VU32 g_vu32TimerCount;
//extern OS_ERR g_errDelay;

#endif /* __ENG_MACRO_H__ */
