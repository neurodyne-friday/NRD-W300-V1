/**
 * @file		EngHAL_UART_STM32F4xx.c
 * @brief		This main code for HAL CAN Component Library.
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


#define __ENGHAL_UART_C__

#include "Eng_CommonType.h"
#include "EngHAL_UART_STM32F4xx.h"


/**
  * @brief UART Variables
  */

#define UART_CHANNEL_COUNT   2
#define UART_RX_DATA_SIZE    64 // able to support FD-CAN
#define UART_TX_DATA_SIZE    64 // able to support FD-CAN

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart4;

typedef struct _THalUARTRxBuffer
{
	U8 ubLength;
	U8 pubData[UART_RX_DATA_SIZE];
} THalUARTRxBuffer;

typedef struct _THalUARTTxBuffer
{
	U8 ubLength;
	U8 pubData[UART_TX_DATA_SIZE];
} THalUARTTxBuffer;

THalUARTRxBuffer astHalUARTRxBuffer[UART_CHANNEL_COUNT];
THalUARTTxBuffer astHalUARTTxBuffer[UART_CHANNEL_COUNT];


/**
  * @brief CAN Interface Functions
  * @param None
  * @retval None
  */
BOOL EngHAL_UART_Init_F4xx(THalUARTPorting *pstHalPorting)
{
    UART_HandleTypeDef* pUartHandle = NULL;

    if(pstHalPorting == NULL)
        return FALSE;

    if(pstHalPorting->ulChannel == 2)
    {
        pUartHandle = &huart2;
        pUartHandle->Instance = USART2;
    }
    else if(pstHalPorting->ulChannel == 3)
    {
        pUartHandle = &huart3;
        pUartHandle->Instance = USART3;
    }
    else if(pstHalPorting->ulChannel == 4)
    {
        pUartHandle = &huart4;
        pUartHandle->Instance = UART4;
    }
    else
    {
        return FALSE;
    }

    pUartHandle->Init.BaudRate = pstHalPorting->ulBaudRate;
    pUartHandle->Init.WordLength = UART_WORDLENGTH_8B;
    pUartHandle->Init.StopBits = UART_STOPBITS_1;
    pUartHandle->Init.Parity = UART_PARITY_NONE;
    pUartHandle->Init.Mode = UART_MODE_TX_RX;
    pUartHandle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    pUartHandle->Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(pUartHandle) != HAL_OK)
    {
        Error_Handler();
    }

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }

    return TRUE;
}

void EngHAL_UART_Transmit_F4xx(THalUARTPorting *pstHalPorting, U8 pubData[], U16 uwLength)
{
    UART_HandleTypeDef* pUartHandle = NULL;

    if(pstHalPorting == NULL)
        return ;

    if(pstHalPorting->ulChannel == 3)
    {
        pUartHandle = &huart3;
    }
    else if(pstHalPorting->ulChannel == 4)
    {
        pUartHandle = &huart4;
    }
    else
    {
        return ;
    }    

    HAL_UART_Transmit(pUartHandle, pubData, uwLength, HAL_MAX_DELAY);
}

void EngHAL_UART_Receive_F4xx(THalUARTPorting *pstHalPorting)
{

}