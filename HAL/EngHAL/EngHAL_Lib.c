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
#include "EngCM_HalConfig.h"


/* Private variables ---------------------------------------------------------*/

//PCD_HandleTypeDef hpcd_USB_OTG_FS;

uint8_t txData[] = "Hello from UART3!\r\n";

/*
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
*/

/**
  * @brief All Components Initialization Function
  * @param None
  * @retval None
  */

BOOL EngHAL_LibraryEntry(void)
{
	EngHAL_Core_Init();

    THalFunction *pstHalFunction = NULL;

    /* Initilize all hal items */
    // pstHalFunction = &astHalFunctionTbl[0];
    // if(pstHalFunction != NULL)
    // {
    //     /* CAN Initialize */
    //     if((void *)pstHalFunction->stCAN.pfnInit != NULL)
    //     {
    //         THalCANPorting *pstCANHal = &astHalCANTbl[0];
    //         while(pstCANHal->ulName != HAL_CAN_NAME_UNSPECIFIED)
    //         {
    //             pstHalFunction->stCAN.pfnInit(pstCANHal);
    //             pstCANHal++;
    //         }
    //     }

    //     /* Ethernet Initialize */
    //     if((void *)pstHalFunction->stETH.pfnInit != NULL)
    //     {
    //         THalETHPorting *pstETHHal = &astHalETHTbl[0];
    //         while(pstETHHal->ulName != HAL_ETH_NAME_UNSPECIFIED)
    //         {
    //             pstHalFunction->stETH.pfnInit(pstETHHal);
    //             pstETHHal++;
    //         }
    //     }

    //     /* UART Initialize */
    //     if((void *)pstHalFunction->stUART.pfnInit != NULL)
    //     {
    //         THalUARTPorting *pstUARTHal = &astHalUARTTbl[0];
    //         while(pstUARTHal->ulName != HAL_UART_NAME_UNSPECIFIED)
    //         {
    //             pstHalFunction->stUART.pfnInit(pstUARTHal);
    //             pstUARTHal++;
    //         }
    //     }

    //     /* ADC Initialize */
    //     if((void *)pstHalFunction->stADC.pfnInit != NULL)
    //     {
    //         THalADCPorting *pstADCHal = &astHalADCTbl[0];
    //         while(pstADCHal->ulName != HAL_ADC_NAME_UNSPECIFIED)
    //         {
    //             pstHalFunction->stADC.pfnInit(pstADCHal);
    //             pstADCHal++;
    //         }

    //     }
    // }

    EngHAL_RTC_Init();
    EngHAL_TIM_Init();
    EngHAL_PWR_Init();
    //EngHAL_USB_OTG_FS_PCD_Init(); // make it later
}

void EngHAL_Core_Init(void)
{
	/* Initialize the HAL Library */
	EngHAL_Core_Init_F4xx();

	/* Configure the system clock */
	EngHAL_Core_SystemClock_Config_F4xx();

	/* Configure all configured peripherals before initialization */
	EngHAL_GPIO_Config_F4xx();
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

void EngHAL_CAN_RegisterCallback(U32 ulEventId, void (*pfnCallback)(void))
{
	EngHAL_CAN_RegisterCallback_F4xx(ulEventId, pfnCallback);
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
    EngHAL_RTC_Init_F4xx();
}

void EngHAL_RTC_GetDateTime(U8* pubDateTime)
{
    EngHAL_RTC_GetDateTime_F4xx(pubDateTime);
}


/**
  * @brief TIM Interface Functions
  * @param None
  * @retval None
  */
void EngHAL_TIM_Init(void)
{
    EngHAL_TIM_Init_F4xx();
}

/**
  * @brief PWR Interface Functions
  * @param None
  * @retval None
  */
void EngHAL_PWR_Init(void)
{
    EngHAL_PWR_Init_F4xx();
}

void EngHAL_PWR_RegisterCallback(U32 ulEventId, void (*pfnCallback)(void))
{
	EngHAL_PWR_RegisterCallback_F4xx(ulEventId, pfnCallback);
}

/**
  * @brief USB_OTG_FS Interface Functions
  * @param None
  * @retval None
  */
void EngHAL_USB_OTG_FS_PCD_Init(void)
{
    // hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
    // hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
    // hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
    // hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
    // hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
    // hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
    // hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
    // hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
    // hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
    // hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
    // if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
    // {
    //     Error_Handler();
    // }
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