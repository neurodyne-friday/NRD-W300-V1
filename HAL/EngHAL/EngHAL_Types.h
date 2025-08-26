/**
 * @file        EngHAL_Types.h
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



#ifndef __ENGHAL_TYPES_H__
#define __ENGHAL_TYPES_H__

#define	VPint		*(volatile unsigned int *)
#define	VPshort		*(volatile unsigned short *)
#define	VPchar		*(volatile unsigned char *)

#include "Eng_Macro.h"

typedef enum
{
	HAL_CHIP_STM32F4xx,   // STM32F24xx
	HAL_CHIP_STM32F7xx,   // STM32F27xx
	HAL_CHIP_MAX,
	HAL_CHIP_UNSPECIFIED = HAL_CHIP_MAX
} THalChipType;


/**
 * @brief Declare of The HAL Event CALLBACK & ID
 */

typedef void (*HAL_EVENT_CALLBACK)(void);


/* Power Event */
#define HAL_EVENT_PWR_ON	0	// Power On Event
#define HAL_EVENT_PWR_OFF	1	// Power Off Event
#define HAL_EVENT_PWR_MAX	2	// Maximum Event ID

/* CAN Event */
#define HAL_EVENT_CAN1_RX	0	// CAN0 Receive Event
#define HAL_EVENT_CAN2_RX	1	// CAN1 Receive Event
#define HAL_EVENT_CAN_MAX	2	// Maximum Event ID



/**
 * The GPIO HAL 
 */
typedef enum
{
	/* Output */
	HAL_GPIO_NAME_INDICATOR,	// PC5
	HAL_GPIO_NAME_USART_TX,		// PA2

	HAL_GPIO_NAME_SPI1_NSS,		// PA4
	HAL_GPIO_NAME_SPI1_SCLK,	// PA5
	HAL_GPIO_NAME_SPI1_MOSI,	// PA7

	HAL_GPIO_NAME_PWM_A,		// PA10
	HAL_GPIO_NAME_PWM_B,		// PA8
	HAL_GPIO_NAME_PWM_C,		// PA9

	HAL_GPIO_NAME_DRV_ENABLE,	// PA11
	HAL_GPIO_NAME_DRV_CAL,		// PA12

	HAL_GPIO_NAME_CAN_TX,		// PB6

	HAL_GPIO_NAME_SPI3_NSS,		// PA15
	HAL_GPIO_NAME_SPI3_SCLK,	// PC10
	HAL_GPIO_NAME_SPI3_MOSI,	// PC12
    
	HAL_GPO_NAME_MAX,
	HAL_GPO_NAME_UNSPECIFIED = HAL_GPO_NAME_MAX
} THalGPOName;

typedef enum
{
	/* Input */
    HAL_GPIO_NAME_CURRENT_A,	// PC0
	HAL_GPIO_NAME_CURRENT_B,	// PC1

	HAL_GPIO_NAME_SPI1_MISO,	// PC6

	HAL_GPIO_NAME_SPI3_MISO,	// PC11
    
	HAL_GPI_NAME_MAX,
	HAL_GPI_NAME_UNSPECIFIED = HAL_GPI_NAME_MAX
} THalGPIName;

typedef enum
{
	HAL_GPIO_OFF,
	HAL_GPIO_ON,
	HAL_GPIO_TOGGLE,
	//HAL_GPIO_NONE = MAX_S32
} THalGPIOOnOff;

typedef enum
{
	HAL_GPIO_INPUT,
	HAL_GPIO_OUTPUT,
	HAL_GPIO_INOUT_NONE
} THalGPIOInOut;

typedef enum
{
	HAL_GPIO_ACTIVE_LOW,
	HAL_GPIO_ACTIVE_HIGH,
	HAL_GPIO_ACTIVE_NONE
} THalGPIOActive;

typedef struct
{
   	U32 ulName;
	THalChipType enChipType;
	U32 ulChannel;

	THalGPIOActive ulActive;
	U32 ulBit;
	THalGPIOOnOff enInitState;
	U32 ulPinSelChannel;
	U32 ulPinSelBit;
	U32 ulChkSum;
} THalGPIOPorting;


/**
 * The ADC HAL 
 */
typedef enum
{
	HAL_ADC_NAME_DUMMY1,
	HAL_ADC_NAME_MAX,
	HAL_ADC_NAME_UNSPECIFIED = HAL_ADC_NAME_MAX
} THalADCName;

typedef enum
{
	eADC_TYPE_24V_ADC,
	eADC_TYPE_RJB_ADC,
	eADC_TYPE_RJP_RANPS,
	eADC_TYPE_RJP_RBNPS,
	eADC_DIVERTER_RANGD,
	eADC_DIVERTER_RBNGD,
	eADC_TYPE_MAX
} TADCType;

typedef struct
{
   	U32 ulName;
	THalChipType enChipType;
	U32 ulChannel;
} THalADCPorting;


/**
 * The CAN HAL 
 */

#define HOST_CAN_ID		0x118


typedef enum
{
	HAL_CAN_NAME_MOTOR_CTRL,
	HAL_CAN_NAME_MAX,
	HAL_CAN_NAME_UNSPECIFIED = HAL_CAN_NAME_MAX
} THalCANName;

typedef enum
{
	HAL_CAN_ID_TYPE_STD,
	HAL_CAN_ID_TYPE_EXT,
	HAL_CAN_ID_TYPE_NONE,
} THalCANIdType;

typedef struct
{
   	U32 ulName;
	THalChipType enChipType;
	U32 ulChannel;

	THalCANIdType ulIdType;
	U32 ulId;
	U32 ulDLC;
	U8 pubData[8];
} THalCANPorting;

/**
 * The Ethernet HAL 
 */
typedef enum
{
	HAL_ETH_NAME_MAIN,
	HAL_ETH_NAME_MAX,
	HAL_ETH_NAME_UNSPECIFIED = HAL_ETH_NAME_MAX
} THalEthName;

typedef enum
{
	HAL_ETH_IP_V4,
	HAL_ETH_IP_V6
} THalETHIPType;

typedef enum
{
	HAL_ETH_LWIP_ON,
	HAL_ETH_LWIP_OFF
} THalETHLWIPOnOff;

typedef enum
{
	HAL_ETH_DHCP_ON, // USE DHCP
	HAL_ETH_DHCP_OFF
} THalETHDHCPOnOff;

typedef struct _TIPv4Addr
{
	U8 ubAddr0;
	U8 ubAddr1;
	U8 ubAddr2;
	U8 ubAddr3;
} TIPv4Addr;

typedef struct _TIPv6Addr
{
	U8 ubAddr0;
	U8 ubAddr1;
	U8 ubAddr2;
	U8 ubAddr3;
	U8 ubAddr4;
	U8 ubAddr5;
} TIPv6Addr;

typedef enum
{
	HAL_ETH_STATE_INIT				= 0,
	HAL_ETH_STATE_DHCP_PROCESS		= 1,
	HAL_ETH_STATE_DHCP_SUCCESS		= 2,
	HAL_ETH_STATE_DHCP_FAIL			= 3,
	HAL_ETH_STATE_LINK_DOWN			= 4,			
	HAL_ETH_STATE_CONNECTED			= 5,
	HAL_ETH_STATE_CANT_CONNECT		= 6
} THalETHState;

typedef enum
{
	ETH_DHCP_OFF				= 0,
	ETH_DHCP_START				= 1,
	ETH_DHCP_WAIT_ADDRESS		= 2,
	ETH_DHCP_ADDRESS_ASSIGNED	= 3,
	ETH_DHCP_TIMEOUT			= 4,
	ETH_DHCP_LINK_DOWN			= 5
} THalETHDHCPState;

#define DHCP_MAX_TRIES	5

typedef struct
{
   	U32 ulName;
	THalChipType enChipType;
	U32 ulChannel;

	THalETHIPType enIPType;
	THalETHLWIPOnOff enLWIPOnOff;
	THalETHDHCPOnOff enDHCPOnOff;
	THalETHState enState;

//union{
	TIPv4Addr stIPAddr;
//	TIPv6Addr stIPAddr;
//};
	TIPv4Addr stNetMaskAddr;
	TIPv4Addr stGateWayAddr;
} THalETHPorting;


/**
 * The UART HAL 
 */
typedef enum
{
	HAL_UART_NAME_USART3,
	HAL_UART_NAME_UART4,
	HAL_UART_NAME_MAX,
	HAL_UART_NAME_UNSPECIFIED = HAL_UART_NAME_MAX
} THalUARTName;

typedef struct
{
   	U32 ulName;
	THalChipType enChipType;
	U32 ulChannel;
	U32 ulBaudRate;
} THalUARTPorting;

/**
 * The SPI HAL 
 */
typedef enum
{
	HAL_SPI_NAME_MOTOR_DRV,
	HAL_SPI_NAME_ENCODER,
	HAL_SPI_NAME_MAX,
	HAL_SPI_NAME_UNSPECIFIED = HAL_SPI_NAME_MAX
} THalSPIName;

typedef enum
{
	HAL_SPI_CHANNEL_1,
	HAL_SPI_CHANNEL_2,
	HAL_SPI_CHANNEL_3,
	HAL_SPI_CHANNEL_4,
	HAL_SPI_CHANNEL_NONE
} THalSPIChannel;


typedef struct
{
   	U32 ulName;
	THalChipType enChipType;
	U32 ulChannel;
} THalSPIPorting;


/**
 * The RTC HAL 
 */
typedef struct _THalRTCData
{
	U32 ulTag;				// 'RTCs' 마커 = 0x52544373 (디버그용)
    U8  ubYear;				// 0~99  (RTC_FORMAT_BIN 기준)
    U8  ubMonth;			// 1~12
    U8  ubDay;				// 1~31
    U8  ubWeekDay;			// 1~7
    U8  ubHour;				// 0~23
    U8  ubMinute;			// 0~59
    U8  ubSecond;			// 0~59
    U8  ubReserved;			// 정렬용
    U16 uwSubSecond;		// RTC->SSR 현재 값
    U16 uwSecondFraction;	// RTC->PRER의 SynchPrediv (초 분해능 계산용)
} THalRTCData;


/**
 * @brief .
 */
typedef struct
{
	void (*pfnInit)(THalADCPorting *);						/* 0 */
	void (*pfnGet)(THalADCPorting *, U8*); 					/* 1 */
} THalADCFunction;


/**
 * @brief .
 */
typedef struct
{
	void (*pfnInit)(THalCANPorting *);						/* 0 */
	void (*pfnEnableInterrupt)(THalCANPorting *);			/* 1 */
	void (*pfnDisableInterrupt)(THalCANPorting *);			/* 2 */
	BOOL (*pfnIsRxFIFOEmpty)(THalCANPorting *);				/* 3 */
	BOOL (*pfnIsTxFIFOEmpty)(THalCANPorting *);				/* 4 */
	void (*pfnTransmitData)(THalCANPorting *, U8*, U8); 	/* 5 */
	void (*pfnReceiveData)(THalCANPorting *); 				/* 6 */	
	void (*pfnPutByte)(THalCANPorting *, U8); 				/* 7 */	
	U8 (*pfnGetByte)(THalCANPorting *); 					/* 8 */	
} THalCANFunction;


/**
 * @brief .
 */
typedef struct
{
	void (*pfnInit)(THalETHPorting *);						/* 0 */
	void (*pfnConnetEntry)(THalETHPorting *);				/* 1 */
	void (*pfnConnetActivity)(THalETHPorting *);			/* 2 */
	void (*pfnConnetExit)(THalETHPorting *);				/* 3 */
	void (*pfnTransmitData)(THalETHPorting *, U8*, U16); 	/* 4 */
} THalETHFunction;



/**
 * @brief .
 */
typedef struct
{
	void (*pfnInit)(THalUARTPorting *);						/* 0 */
	void (*pfnEnableInterrupt)(THalUARTPorting *);			/* 1 */
	void (*pfnDisableInterrupt)(THalUARTPorting *);			/* 2 */
	BOOL (*pfnIsRxFIFOEmpty)(THalUARTPorting *);			/* 3 */
	BOOL (*pfnIsTxFIFOEmpty)(THalUARTPorting *);			/* 4 */
	void (*pfnTransmitData)(THalUARTPorting *, U8*, U16); 	/* 5 */
	void (*pfnReceiveData)(THalUARTPorting *); 				/* 6 */	
	void (*pfnPutByte)(THalUARTPorting *, U8); 				/* 7 */	
	U8 (*pfnGetByte)(THalUARTPorting *); 					/* 8 */	
} THalUARTFunction;


/**
 * @brief .
 */
typedef struct
{
	void (*pfnInit)(THalSPIPorting *);						/* 0 */
} THalSPIFunction;



/**
 * @brief The structure of HAL Function
 */
typedef struct
{
	THalChipType enChipType;									// 0
	THalCANFunction stCAN;										// 8
	THalETHFunction stETH;										// 5
	THalUARTFunction stUART;									// 8
	// THalGPIOFunction stGPIO;									// 4
	// THalPWMFunction stPWM;									// 4
	THalSPIFunction stSPI;										// 1
	THalADCFunction stADC;										// 2
	// THalMotorFunction stMotor;								// 9
	// THalDMUFunction stDMU;									// 2
	// THalIICFunction stIIC;									// 10
	// THalEngTimerFunction stEngTimer;							// 23
	// THalEINTFunction stEINT;									// 5
} THalFunction;


#endif /* __ENGHAL_TYPES_H__ */
