/**
 * @file		EngHAL_Lib.c
 * @brief		This main code for HAL Component Library.
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
 * @imp 		
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		07/11/2008(D/M/Y)
 * @version 	V0.1
 */

#define __ENGHAL_LIB_C__

#include "Eng_CommonType.h"
#include "EngOS_Lib.h"
#include "EngHAL_Lib.h"
#include "EngCM_SystemConfig.h"


/* Private variables ---------------------------------------------------------*/


RTC_HandleTypeDef hrtc;
//TIM_HandleTypeDef htim1;
PCD_HandleTypeDef hpcd_USB_OTG_FS;

uint8_t txData[] = "Hello from UART3!\r\n";


#define HASH_CAN_BUCKET_SIZE	HAL_CAN_NAME_MAX
#define HASH_CAN_SLOT_SIZE 		1
#define HASH_CAN_FN(key) 		(key % HASH_CAN_BUCKET_SIZE)
static THalCANPorting *pastHashCANTable[HASH_CAN_BUCKET_SIZE][HASH_CAN_SLOT_SIZE];

#define HASH_UART_BUCKET_SIZE	HAL_UART_NAME_MAX
#define HASH_UART_SLOT_SIZE 	1
#define HASH_UART_FN(key) 		(key % HASH_UART_BUCKET_SIZE)
static THalUARTPorting *pastHashUARTTable[HASH_UART_BUCKET_SIZE][HASH_UART_SLOT_SIZE];

#define HASH_ETH_BUCKET_SIZE	HAL_ETH_NAME_MAX
#define HASH_ETH_SLOT_SIZE 	    1
#define HASH_ETH_FN(key) 		(key % HASH_ETH_BUCKET_SIZE)
static THalETHPorting *pastHashETHTable[HASH_ETH_BUCKET_SIZE][HASH_ETH_SLOT_SIZE];


/**
  * @brief All Components Initialization Function
  * @param None
  * @retval None
  */

BOOL EngHAL_LibraryEntry(void)
{
    THalFunction *pstHalFunction = NULL;

    /* Initilize all hal items */
    pstHalFunction = &astHalFunctionTbl[0];
    if(pstHalFunction != NULL)
    {
        /* CAN Initialize */
        if((void *)pstHalFunction->stCAN.pfnInit != NULL)
        {
            THalCANPorting *pstCANHal = &astHalCANTbl[0];
            while(pstCANHal->ulName != HAL_CAN_NAME_UNSPECIFIED)
            {
                pstHalFunction->stCAN.pfnInit(pstCANHal);
                pstCANHal++;
            }
        }

        /* Ethernet Initialize */
        if((void *)pstHalFunction->stETH.pfnInit != NULL)
        {
            THalETHPorting *pstETHHal = &astHalETHTbl[0];
            while(pstETHHal->ulName != HAL_ETH_NAME_UNSPECIFIED)
            {
                pstHalFunction->stETH.pfnInit(pstETHHal);
                pstETHHal++;
            }
        }

        /* UART Initialize */
        if((void *)pstHalFunction->stUART.pfnInit != NULL)
        {
            THalUARTPorting *pstUARTHal = &astHalUARTTbl[0];
            while(pstUARTHal->ulName != HAL_UART_NAME_UNSPECIFIED)
            {
                pstHalFunction->stUART.pfnInit(pstUARTHal);
                pstUARTHal++;
            }
        }

        /* ADC Initialize */
        if((void *)pstHalFunction->stADC.pfnInit != NULL)
        {
            THalADCPorting *pstADCHal = &astHalADCTbl[0];
            while(pstADCHal->ulName != HAL_ADC_NAME_UNSPECIFIED)
            {
                pstHalFunction->stADC.pfnInit(pstADCHal);
                pstADCHal++;
            }

        }
    }

    EngHAL_RTC_Init();
    EngHAL_TIM1_Init();
    EngHAL_USB_OTG_FS_PCD_Init();
}


void EngHAL_CAN_Init(U32 ulHalName)
{
	THalCANPorting *pstHalCANPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalCANPorting = EngHAL_FindHalCAN(ulHalName);
    
	if(pstHalCANPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stCAN.pfnInit != NULL)
	{
		pstHalFunction->stCAN.pfnInit(pstHalCANPorting);
	}
}

void EngHAL_CAN_EnableInterrupt(U32 ulHalName)
{
	THalCANPorting *pstHalCANPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalCANPorting = EngHAL_FindHalCAN(ulHalName);
    
	if(pstHalCANPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stCAN.pfnEnableInterrupt != NULL)
	{
		pstHalFunction->stCAN.pfnEnableInterrupt(pstHalCANPorting);
	}
}

void EngHAL_CAN_DisableInterrupt(U32 ulHalName)
{
	THalCANPorting *pstHalCANPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalCANPorting = EngHAL_FindHalCAN(ulHalName);
    
	if(pstHalCANPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stCAN.pfnDisableInterrupt != NULL)
	{
		pstHalFunction->stCAN.pfnDisableInterrupt(pstHalCANPorting);
	}
}

BOOL EngHAL_CAN_IsRxFIFOEmpty(U32 ulHalName)
{
	THalCANPorting *pstHalCANPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalCANPorting = EngHAL_FindHalCAN(ulHalName);
    
	if(pstHalCANPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stCAN.pfnIsRxFIFOEmpty != NULL)
	{
		return pstHalFunction->stCAN.pfnIsRxFIFOEmpty(pstHalCANPorting);
	}

    return FALSE;
}

BOOL EngHAL_CAN_IsTxFIFOEmpty(U32 ulHalName)
{
	THalCANPorting *pstHalCANPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalCANPorting = EngHAL_FindHalCAN(ulHalName);
    
	if(pstHalCANPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stCAN.pfnIsTxFIFOEmpty != NULL)
	{
		return pstHalFunction->stCAN.pfnIsTxFIFOEmpty(pstHalCANPorting);
	}

    return FALSE;
}

void EngHAL_CAN_Transmit(U32 ulHalName, U8 pubData[], U8 ubLength)
{
	THalCANPorting *pstHalCANPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalCANPorting = EngHAL_FindHalCAN(ulHalName);
    
	if(pstHalCANPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stCAN.pfnTransmitData != NULL)
	{
		pstHalFunction->stCAN.pfnTransmitData(pstHalCANPorting, pubData, ubLength);
	}
}

void EngHAL_CAN_Receive(U32 ulHalName)
{

}

void EngHAL_CAN_SendByte(U32 ulHalName, U8 ubData)
{
	THalCANPorting *pstHalCANPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalCANPorting = EngHAL_FindHalCAN(ulHalName);
    
	if(pstHalCANPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stCAN.pfnPutByte != NULL)
	{
		pstHalFunction->stCAN.pfnPutByte(pstHalCANPorting, ubData);
	}
}

U8 EngHAL_CAN_GetByte(U32 ulHalName)
{
	THalCANPorting *pstHalCANPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalCANPorting = EngHAL_FindHalCAN(ulHalName);
    
	if(pstHalCANPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stCAN.pfnGetByte != NULL)
	{
		pstHalFunction->stCAN.pfnGetByte(pstHalCANPorting);
	}
}



/**
  * @brief UART Interface Functions
  * @param None
  * @retval None
  */

void EngHAL_UART_Init(U32 ulHalName)
{
	THalUARTPorting *pstHalUARTPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalUARTPorting = EngHAL_FindHalUART(ulHalName);
    
	if(pstHalUARTPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stUART.pfnInit != NULL)
	{
		pstHalFunction->stUART.pfnInit(pstHalUARTPorting);
	}
}

void EngHAL_UART_Transmit(U32 ulHalName, U8 pubData[], U16 uwLength)
{
	THalUARTPorting *pstHalUARTPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalUARTPorting = EngHAL_FindHalUART(ulHalName);
    
	if(pstHalUARTPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stUART.pfnTransmitData != NULL)
	{
		pstHalFunction->stUART.pfnTransmitData(pstHalUARTPorting, pubData, uwLength);
	}
}

void EngHAL_UART_Receive(U32 ulHalName)
{

}


/**
  * @brief Ethernet Interface Functions
  * @param None
  * @retval None
  */

BOOL EngHAL_ETH_Init(U32 ulHalName)
{
	THalETHPorting *pstHalETHPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalETHPorting = EngHAL_FindHalETH(ulHalName);
    
	if(pstHalETHPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stETH.pfnInit != NULL)
	{
		pstHalFunction->stETH.pfnInit(pstHalETHPorting);
	}
}

void EngHAL_ETH_Connect_Entry(U32 ulHalName)
{
	THalETHPorting *pstHalETHPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalETHPorting = EngHAL_FindHalETH(ulHalName);
    
	if(pstHalETHPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stETH.pfnInit != NULL)
	{
		pstHalFunction->stETH.pfnConnetEntry(pstHalETHPorting);
	}
}

void EngHAL_ETH_Connect_Activity(U32 ulHalName)
{
	THalETHPorting *pstHalETHPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalETHPorting = EngHAL_FindHalETH(ulHalName);
    
	if(pstHalETHPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stETH.pfnInit != NULL)
	{
		pstHalFunction->stETH.pfnConnetActivity(pstHalETHPorting);
	}
}

void EngHAL_ETH_Connect_Exit(U32 ulHalName)
{
	THalETHPorting *pstHalETHPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalETHPorting = EngHAL_FindHalETH(ulHalName);
    
	if(pstHalETHPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stETH.pfnInit != NULL)
	{
		pstHalFunction->stETH.pfnConnetExit(pstHalETHPorting);
	}
}


/**
  * @brief RTC Interface Functions
  * @param None
  * @retval None
  */
void EngHAL_RTC_Init(void)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    /** Initialize RTC Only
     */
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initialize RTC and set the Time and Date
     */
    sTime.Hours = 0x0;
    sTime.Minutes = 0x0;
    sTime.Seconds = 0x0;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }
    sDate.WeekDay = RTC_WEEKDAY_MONDAY;
    sDate.Month = RTC_MONTH_JANUARY;
    sDate.Date = 0x1;
    sDate.Year = 0x0;

    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }
}

void EngHAL_RTC_GetDateTime(U8* pubDateTime)
{
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
    
    if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK) {
        Error_Handler();
    }

    //printf("Time: %02x:%02x:%02x\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
    //printf("Date: %02x/%02x/20%02x\n", sDate.Date, sDate.Month, sDate.Year);
    sprintf(pubDateTime, "%02x/%02x/20%02x %02x:%02x:%02x", sDate.Date, sDate.Month, sDate.Year, sTime.Hours, sTime.Minutes, sTime.Seconds);
}


/**
  * @brief TIM Interface Functions
  * @param None
  * @retval None
  */
void EngHAL_TIM1_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_SlaveConfigTypeDef sSlaveConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 0;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 65535;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    
    if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    
    sSlaveConfig.SlaveMode = TIM_SLAVEMODE_TRIGGER;
    sSlaveConfig.InputTrigger = TIM_TS_ITR0;
    if (HAL_TIM_SlaveConfigSynchro(&htim1, &sSlaveConfig) != HAL_OK)
    {
        Error_Handler();
    }
    
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}


/**
  * @brief USB_OTG_FS Interface Functions
  * @param None
  * @retval None
  */
void EngHAL_USB_OTG_FS_PCD_Init(void)
{
    hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
    hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
    hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
    hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
    hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
    hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
    hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
    hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
    hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
    hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
    if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief Delay Timer Interface Functions
  * @param None
  * @retval None
  */
void EngHAL_OS_Delay(uint32_t ticks)
{
    osDelay(ticks);
}


/**
  * @brief Find HAL Instance interface
  * @param None
  * @retval None
  */
THalCANPorting* EngHAL_FindHalCAN(U32 ulHalName)
{
	THalCANPorting *pstHalCANPorting = NULL;

    for(U8 ubIndex = 0; ubIndex < HAL_CAN_NAME_MAX; ubIndex++)
    {
        if(ulHalName == astHalCANTbl[ubIndex].ulName)
        {
            pstHalCANPorting = &astHalCANTbl[ubIndex];
            return pstHalCANPorting;
        }
    }

    return pstHalCANPorting;
}

THalUARTPorting* EngHAL_FindHalUART(U32 ulHalName)
{
	THalUARTPorting *pstHalUARTPorting = NULL;

    for(U8 ubIndex = 0; ubIndex < HAL_UART_NAME_MAX; ubIndex++)
    {
        if(ulHalName == astHalUARTTbl[ubIndex].ulName)
        {
            pstHalUARTPorting = &astHalUARTTbl[ubIndex];
            return pstHalUARTPorting;
        }
    }

    return pstHalUARTPorting;
}