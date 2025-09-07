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
				pstHalFunction->stCAN.pfnEnableInterrupt(pstCANHal);
                pstCANHal++;
            }
        }

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

        /* SPI Initialize */
        if((void *)pstHalFunction->stUART.pfnInit != NULL)
        {
            THalSPIPorting *pstSPIHal = &astHalSPITbl[0];
            while(pstSPIHal->ulName != HAL_SPI_NAME_UNSPECIFIED)
            {
                pstHalFunction->stSPI.pfnInit(pstSPIHal);
                pstSPIHal++;
            }
        }

		/* I2C Initialize */
        if((void *)pstHalFunction->stI2C.pfnInit != NULL)
        {
            THalI2CPorting *pstI2CHal = &astHalI2CTbl[0];
            while(pstI2CHal->ulName != HAL_I2C_NAME_UNSPECIFIED)
            {
                pstHalFunction->stI2C.pfnInit(pstI2CHal);
                pstI2CHal++;
            }
        }

    //     }
    }

    EngHAL_RTC_Init();
    EngHAL_TIM_Init();
    EngHAL_PWR_Init();
	EngHAL_SRAM_Init();
    //EngHAL_USB_OTG_FS_PCD_Init(); // make it later
}

void EngHAL_Core_Init(void)
{
	/* Initialize the HAL Library */
	EngHAL_Core_Init_F4xx();

	/* Configure the system clock */
	EngHAL_Core_SystemClock_Config_F4xx();

	/* Configure the system clock */
#ifdef FR_ENGLIB_SWO_DEBUG
	EngHAL_Core_SWO_Config_F4xx(180000000UL, 2000000UL);
#endif

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

U32 EngHAL_CAN_GetRxFifoFillLevel(U32 ulHalName)
{
	THalCANPorting *pstHalCANPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalCANPorting = EngHAL_FindHalCAN(ulHalName);
    
	if(pstHalCANPorting == NULL)
	{
		ASSERT(0);
		return;
	}

	return EngHAL_CAN_GetRxFifoFillLevel_STM32F4xx(pstHalCANPorting);
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

void EngHAL_RTC_GetDateTime(THalRTCData* pstRTCData)
{
    EngHAL_RTC_GetDateTime_F4xx(pstRTCData);
}


/**
  * @brief SRAM Interface Functions
  * @param None
  * @retval None
  */
void EngHAL_SRAM_Init(void)
{
	EngHAL_SRAM_Init_F4xx();
}

BOOL EngHAL_SRAM_Save(const void *data, uint32_t len)
{
	return EngHAL_SRAM_Save_F4xx(data, len);
}

BOOL EngHAL_SRAM_Load(void *out, uint32_t bufsize, uint32_t *out_len, uint32_t *out_seq)
{
	return EngHAL_SRAM_Load_F4xx(out, bufsize, out_len, out_seq);
}

BOOL EngHAL_SRAM_IsValid(void)
{
	return EngHAL_SRAM_IsValid_F4xx();
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
  * @brief SPI Interface Functions
  * @param None
  * @retval None
  */
void EngHAL_SPI_Init(U32 ulHalName)
{
	THalSPIPorting *pstHalSPIPorting = NULL;
	THalFunction *pstHalFunction = NULL;

    pstHalSPIPorting = EngHAL_FindHalSPI(ulHalName);
    
	if(pstHalSPIPorting == NULL)
	{
		ASSERT(0);
		return;
	}
	
	pstHalFunction = &astHalFunctionTbl[0];

	if((void *)pstHalFunction->stSPI.pfnInit != NULL)
	{
		pstHalFunction->stSPI.pfnInit(pstHalSPIPorting);
	}
}

BOOL EngHAL_SPI_MA702_ReadRaw12(U32 ulHalName, uint16_t *ang12)
{
    THalSPIPorting *p = EngHAL_FindHalSPI(ulHalName);
    if (!p || !ang12) return FALSE;
    return (EngHAL_SPI_MA702_ReadAngle12_F4xx(p, ang12) == HAL_OK);
}

float EngHAL_SPI_MA702_ReadDeg(U32 ulHalName)
{
    THalSPIPorting *p = EngHAL_FindHalSPI(ulHalName);
    if (!p) return -1.0f;
    return EngHAL_SPI_MA702_ReadAngleDeg_F4xx(p);
}

float EngHAL_SPI_MA702_ReadRad(U32 ulHalName)
{
    THalSPIPorting *p = EngHAL_FindHalSPI(ulHalName);
    if (!p) return -1.0f;
    return EngHAL_SPI_MA702_ReadAngleRad_F4xx(p);
}

BOOL EngHAL_SPI_MA702_ReadReg(U32 ulHalName, uint8_t addr5, uint8_t *val)
{
    THalSPIPorting *p = EngHAL_FindHalSPI(ulHalName);
    if (!p || !val) return FALSE;
    return (EngHAL_SPI_MA702_ReadReg_F4xx(p, addr5, val) == HAL_OK);
}

BOOL EngHAL_SPI_MA702_WriteReg(U32 ulHalName, uint8_t addr5, uint8_t v, uint8_t *echo)
{
    THalSPIPorting *p = EngHAL_FindHalSPI(ulHalName);
    if (!p) return FALSE;
    return (EngHAL_SPI_MA702_WriteReg_F4xx(p, addr5, v, echo) == HAL_OK);
}


/**
  * @brief I2C Interface Functions
  * @param None
  * @retval None
  */

void EngHAL_I2C_Init(U32 ulHalName)
{
    THalI2CPorting *pstHalI2C = EngHAL_FindHalI2C(ulHalName);

    if(pstHalI2C == NULL)
	{ 
		ASSERT(0); 
		return; 
	}

    THalFunction *pstHalFunction = &astHalFunctionTbl[0];
	if((void*)pstHalFunction->stI2C.pfnInit != NULL)
    {
        pstHalFunction->stI2C.pfnInit(pstHalI2C);
    }
}

BOOL EngHAL_I2C_MemRead(U32 ulHalName, U16 devAddr7b, U16 memAddr, U16 memAddrSize, U8 *pData, U16 len, U32 timeout)
{
    THalI2CPorting *pstHalI2C = EngHAL_FindHalI2C(ulHalName);
    if(pstHalI2C == NULL) { ASSERT(0); return FALSE; }

    THalFunction *pstHalFunction = &astHalFunctionTbl[0];
    if((void*)pstHalFunction->stI2C.pfnMemRead != NULL)
    {
        return pstHalFunction->stI2C.pfnMemRead(pstHalI2C, devAddr7b, memAddr, memAddrSize, pData, len, timeout);
    }
    return FALSE;
}

BOOL EngHAL_I2C_MemWrite(U32 ulHalName, U16 devAddr7b, U16 memAddr, U16 memAddrSize, const U8 *pData, U16 len, U32 timeout)
{
    THalI2CPorting *pstHalI2C = EngHAL_FindHalI2C(ulHalName);
    if(pstHalI2C == NULL) 
	{ 
		ASSERT(0); 
		return FALSE;
	}

    THalFunction *pstHalFunction = &astHalFunctionTbl[0];
    if((void*)pstHalFunction->stI2C.pfnMemWrite != NULL)
    {
        return pstHalFunction->stI2C.pfnMemWrite(pstHalI2C, devAddr7b, memAddr, memAddrSize, pData, len, timeout);
    }
    return FALSE;
}

BOOL EngHAL_I2C_Read(U32 ulHalName, U16 devAddr7b, U8 *pData, U16 len, U32 timeout)
{
    THalI2CPorting *pstHalI2C = EngHAL_FindHalI2C(ulHalName);
    if(pstHalI2C == NULL) 
	{ 
		ASSERT(0); 
		return FALSE; 
	}

    THalFunction *pstHalFunction = &astHalFunctionTbl[0];
    if((void*)pstHalFunction->stI2C.pfnRead != NULL)
    {
        return pstHalFunction->stI2C.pfnRead(pstHalI2C, devAddr7b, pData, len, timeout);
    }
    return FALSE;
}

BOOL EngHAL_I2C_Write(U32 ulHalName, U16 devAddr7b, const U8 *pData, U16 len, U32 timeout)
{
    THalI2CPorting *pstHalI2C = EngHAL_FindHalI2C(ulHalName);
    if(pstHalI2C == NULL) 
	{ 
		ASSERT(0); 
		return FALSE; 
	}

    THalFunction *pstHalFunction = &astHalFunctionTbl[0];
    if((void*)pstHalFunction->stI2C.pfnWrite != NULL)
    {
        return pstHalFunction->stI2C.pfnWrite(pstHalI2C, devAddr7b, pData, len, timeout);
    }
    return FALSE;
}

/* AS5600 helpers (using I2C HAL) */
BOOL EngHAL_I2C_AS5600_ReadRawAngle(U32 ulI2CHalName, U16 *pRaw)
{
    THalI2CPorting *pstHalI2C = EngHAL_FindHalI2C(ulI2CHalName);
    
	if(pstHalI2C == NULL) 
	{ 
		ASSERT(0); 
		return FALSE; 
	}
    
	return EngHAL_AS5600_ReadRawAngle_F4xx(pstHalI2C, pRaw);
}

BOOL EngHAL_I2C_AS5600_ReadAngle12(U32 ulI2CHalName, U16 *pAngle12)
{
    THalI2CPorting *pstHalI2C = EngHAL_FindHalI2C(ulI2CHalName);
    
	if(pstHalI2C == NULL) 
	{ 
		ASSERT(0); 
		return FALSE; 
	}

    return EngHAL_AS5600_ReadAngle12_F4xx(pstHalI2C, pAngle12);
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

THalSPIPorting* EngHAL_FindHalSPI(U32 ulHalName)
{
	THalSPIPorting *pstHalSPIPorting = NULL;

	for(U8 ubIndex = 0; ubIndex < HAL_SPI_NAME_MAX; ubIndex++)
	{
		if(ulHalName == astHalSPITbl[ubIndex].ulName)
		{
			pstHalSPIPorting = &astHalSPITbl[ubIndex];
			return pstHalSPIPorting;
		}
	}

	return pstHalSPIPorting;
}

THalI2CPorting* EngHAL_FindHalI2C(U32 ulHalName)
{
    THalI2CPorting *pstHalI2C = NULL;

    for(U8 ubIndex = 0; ubIndex < HAL_I2C_NAME_MAX; ubIndex++)
    {
        if(ulHalName == astHalI2CTbl[ubIndex].ulName)
        {
            pstHalI2C = &astHalI2CTbl[ubIndex];
            break;
        }
    }
    return pstHalI2C;
}