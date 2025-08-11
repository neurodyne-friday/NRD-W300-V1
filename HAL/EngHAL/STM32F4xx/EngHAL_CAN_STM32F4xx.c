/**
 * @file		EngHAL_CAN_STM32F7xx.c
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


#define __ENGHAL_CAN_C__

#include "Eng_CommonType.h"
#include "EngHAL_CAN_STM32F4xx.h"

/**
  * @brief CAN Variables
  */

#define CAN_CHANNEL_COUNT   2
#define CAN_RX_DATA_SIZE    64 // able to support FD-CAN
#define CAN_TX_DATA_SIZE    64 // able to support FD-CAN

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

typedef struct _THalCANRxBuffer
{
	U8 ubLength;
	U8 pubData[CAN_RX_DATA_SIZE];
} THalCANRxBuffer;

typedef struct _THalCANTxBuffer
{
	U8 ubLength;
	U8 pubData[CAN_TX_DATA_SIZE];
} THalCANTxBuffer;

THalCANRxBuffer astHalCANRxBuffer[CAN_CHANNEL_COUNT];
THalCANTxBuffer astHalCANTxBuffer[CAN_CHANNEL_COUNT];

HAL_EVENT_CALLBACK g_pfnHalCanEventCallback[HAL_EVENT_CAN_MAX] = {0}; // CAN-RX Callback pointer

/**
  * @brief CAN Interface Functions
  * @param None
  * @retval None
  */
BOOL EngHAL_CAN_Init_F4xx(THalCANPorting *pstHalPorting)
{
    CAN_HandleTypeDef* pstCANHandle = NULL;
    CAN_FilterTypeDef sFilterConfig;

    if(pstHalPorting == NULL)
        return FALSE;

    if(pstHalPorting->ulChannel == 1)
    {
        pstCANHandle = &hcan1;
        pstCANHandle->Instance = CAN1;
    }
    else if(pstHalPorting->ulChannel == 2)
    {
        pstCANHandle = &hcan2;
        pstCANHandle->Instance = CAN2;
    }
    else
    {
        return FALSE;
    }

    pstCANHandle->Init.Prescaler = 18;//16;
    pstCANHandle->Init.Mode = CAN_MODE_NORMAL;
    pstCANHandle->Init.SyncJumpWidth = CAN_SJW_1TQ;
    pstCANHandle->Init.TimeSeg1 = CAN_BS1_1TQ;
    pstCANHandle->Init.TimeSeg2 = CAN_BS2_1TQ;
    pstCANHandle->Init.TimeTriggeredMode = DISABLE;
    pstCANHandle->Init.AutoBusOff = DISABLE;
    pstCANHandle->Init.AutoWakeUp = DISABLE;
    pstCANHandle->Init.AutoRetransmission = DISABLE;
    pstCANHandle->Init.ReceiveFifoLocked = DISABLE;
    pstCANHandle->Init.TransmitFifoPriority = DISABLE;

    if (HAL_CAN_Init(pstCANHandle) != HAL_OK)
    {
        Error_Handler();
    }

    // CAN filter configuration
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    // Set filter
    if (HAL_CAN_ConfigFilter(pstCANHandle, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void EngHAL_CAN_EnableInterrupt_F4xx(THalCANPorting *pstHalPorting)
{
    CAN_HandleTypeDef* pHndCAN = NULL;
    uint32_t ulCAN_IT_RX_FIFO_MSG_PENDING = 0;

    if(pstHalPorting->ulChannel == 0)
    {
        pHndCAN = &hcan1;
        ulCAN_IT_RX_FIFO_MSG_PENDING = CAN_IT_RX_FIFO0_MSG_PENDING;
    }
    else if(pstHalPorting->ulChannel == 1)
    {
        pHndCAN = &hcan2;
        ulCAN_IT_RX_FIFO_MSG_PENDING = CAN_IT_RX_FIFO1_MSG_PENDING;
    }
    else
    {
        return;
    }

    // CAN 인터럽트 활성화 (수신 인터럽트)
    if (HAL_CAN_ActivateNotification(pHndCAN, ulCAN_IT_RX_FIFO_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }

    // CAN 시작
    if (HAL_CAN_Start(pHndCAN) != HAL_OK)
    {
        Error_Handler();
    }
}

void EngHAL_CAN_DisableInterrupt_F4xx(THalCANPorting *pstHalPorting)
{
    CAN_HandleTypeDef* pHndCAN = NULL;
    uint32_t ulCAN_IT_RX_FIFO_MSG_PENDING = 0;

    if(pstHalPorting->ulChannel == 0)
    {
        pHndCAN = &hcan1;
        ulCAN_IT_RX_FIFO_MSG_PENDING = CAN_IT_RX_FIFO0_MSG_PENDING;
    }
    else if(pstHalPorting->ulChannel == 1)
    {
        pHndCAN = &hcan2;
        ulCAN_IT_RX_FIFO_MSG_PENDING = CAN_IT_RX_FIFO1_MSG_PENDING;
    }
    else
    {
        return;
    }

    // CAN 인터럽트 활성화 (수신 인터럽트)
    if (HAL_CAN_DeactivateNotification(pHndCAN, ulCAN_IT_RX_FIFO_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }

    // CAN 시작
    if (HAL_CAN_Start(pHndCAN) != HAL_OK)
    {
        Error_Handler();
    }
}

void EngHAL_CAN_RegisterCallback_F4xx(U32 ulEventId, void (*pfnCallback)(void))
{
    g_pfnHalCanEventCallback[ulEventId] = pfnCallback;
}

BOOL EngHAL_CAN_IsRxFIFOEmpty_F4xx(THalCANPorting *pstHalPorting)
{
    THalCANRxBuffer* pRxBuffer = NULL;

    if(pstHalPorting->ulChannel < CAN_CHANNEL_COUNT)
    {
        pRxBuffer = &astHalCANRxBuffer[pstHalPorting->ulChannel];
        if(pRxBuffer->ubLength == 0)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        Error_Handler();
    }
}

BOOL EngHAL_CAN_IsTxFIFOEmpty_F4xx(THalCANPorting *pstHalPorting)
{
    THalCANTxBuffer* pTxBuffer = NULL;

    if(pstHalPorting->ulChannel < CAN_CHANNEL_COUNT)
    {
        pTxBuffer = &astHalCANTxBuffer[pstHalPorting->ulChannel];
        if(pTxBuffer->ubLength == 0)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        Error_Handler();
    }
}

U8 EngHAL_CAN_GetByte_F4xx(THalCANPorting *pstHalPorting)
{
    THalCANRxBuffer* pRxBuffer = NULL;

    if(pstHalPorting->ulChannel < CAN_CHANNEL_COUNT)
    {
        pRxBuffer = &astHalCANRxBuffer[pstHalPorting->ulChannel];
        if(pRxBuffer->ubLength > 0)
        {
            return pRxBuffer->pubData[pRxBuffer->ubLength-1];
        }
        else
        {
            return 0;
        }
    }
    else
    {
        Error_Handler();
    }
}

void EngHAL_CAN_Transmit_F4xx(THalCANPorting *pstHalPorting, U8 pubData[], U8 ubLength)
{
    CAN_HandleTypeDef* pHndCAN = NULL;
    CAN_TxHeaderTypeDef TxHeader;
    uint32_t TxMailbox;

    if(pstHalPorting->ulChannel == 0)
    {
        pHndCAN = &hcan1;
    }
    else if(pstHalPorting->ulChannel == 1)
    {
        pHndCAN = &hcan2;
    }
    else
    {
        return;
    }

    // Tx Message Header Config
    if(pstHalPorting->ulIdType == HAL_CAN_ID_TYPE_STD)
    {
        TxHeader.StdId = pstHalPorting->ulId;
        TxHeader.ExtId = 0x01;
        TxHeader.IDE = CAN_ID_STD;
        TxHeader.DLC = ubLength;
    }
    else
    {
        TxHeader.StdId = 0x01;
        TxHeader.ExtId = pstHalPorting->ulId;
        TxHeader.IDE = CAN_ID_EXT;
        TxHeader.DLC = ubLength; 
    }
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.TransmitGlobalTime = DISABLE;

    // Transmit CAN Message
    if (HAL_CAN_AddTxMessage(pHndCAN, &TxHeader, pubData, &TxMailbox) != HAL_OK) 
    {
        Error_Handler();
    }

    // Waiting for complete to transmit
    while (HAL_CAN_IsTxMessagePending(pHndCAN, TxMailbox));
}


/**
  * @name EngChip_CAN_Receive
  * @brief This function should be used Task or Thread function because it need to be watching countinously 
  */

void EngHAL_CAN_Receive_F4xx(THalCANPorting *pstHalPorting)
{
    CAN_HandleTypeDef* pHndCAN = NULL;
    THalCANRxBuffer* pRxBuffer = NULL;
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];

    if(pstHalPorting->ulChannel == 0)
    {
        pHndCAN = &hcan1;
    }
    else if(pstHalPorting->ulChannel == 1)
    {
        pHndCAN = &hcan2;
    }
    else
    {
        return;
    }

    pRxBuffer = &astHalCANRxBuffer[pstHalPorting->ulChannel];

    if (HAL_CAN_GetRxMessage(pHndCAN, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) 
    {
        for (int i = 0; i < RxHeader.DLC; i++)
        {
            pRxBuffer->pubData[i] = RxData[i];
        }

        pRxBuffer->ubLength = RxHeader.DLC;
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    THalCANRxBuffer* pRxBuffer = NULL;
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
    {
        Error_Handler();
    }

    taskENTER_CRITICAL();
    pRxBuffer = &astHalCANRxBuffer[0];

    //printf("Received CAN message with ID: 0x%03X, Data: ", RxHeader.StdId);
    for (int i = 0; i < RxHeader.DLC; i++)
    {
        //printf("%02X ", RxData[i]);
        pRxBuffer->pubData[i] = RxData[i];
    }
    pRxBuffer->ubLength = RxHeader.DLC;
    taskEXIT_CRITICAL();
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    THalCANRxBuffer* pRxBuffer = NULL;
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &RxHeader, RxData) != HAL_OK)
    {
        Error_Handler();
    }

    taskENTER_CRITICAL();
    pRxBuffer = &astHalCANRxBuffer[1];

    //printf("Received CAN message with ID: 0x%03X, Data: ", RxHeader.StdId);
    for (int i = 0; i < RxHeader.DLC; i++)
    {
        //printf("%02X ", RxData[i]);
        pRxBuffer->pubData[i] = RxData[i];
    }
    pRxBuffer->ubLength = RxHeader.DLC;
    taskEXIT_CRITICAL();
}

