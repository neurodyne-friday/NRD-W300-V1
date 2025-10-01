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

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;


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

void CAN1_RX0_IRQHandler(void) { HAL_CAN_IRQHandler(&hcan1); }
void CAN2_RX1_IRQHandler(void) { HAL_CAN_IRQHandler(&hcan2); }
void CAN1_TX_IRQHandler(void)  { HAL_CAN_IRQHandler(&hcan1); }
void CAN1_SCE_IRQHandler(void) { HAL_CAN_IRQHandler(&hcan1); }

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

    pstCANHandle->Init.Prescaler = 3;
    pstCANHandle->Init.Mode = CAN_MODE_NORMAL;
    pstCANHandle->Init.SyncJumpWidth = CAN_SJW_1TQ;
    pstCANHandle->Init.TimeSeg1 = CAN_BS1_12TQ;
    pstCANHandle->Init.TimeSeg2 = CAN_BS2_2TQ;
    pstCANHandle->Init.TimeTriggeredMode = DISABLE;
    pstCANHandle->Init.AutoBusOff = ENABLE;
    pstCANHandle->Init.AutoWakeUp = DISABLE;
    pstCANHandle->Init.AutoRetransmission = ENABLE;
    pstCANHandle->Init.ReceiveFifoLocked = DISABLE;
    pstCANHandle->Init.TransmitFifoPriority = DISABLE;

    if (HAL_CAN_Init(pstCANHandle) != HAL_OK)
    {
        Error_Handler();
    }

    // CAN filter configuration
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterActivation = ENABLE;
    if(pstHalPorting->ulChannel == 1)
    {
        sFilterConfig.FilterBank = 0;
        sFilterConfig.SlaveStartFilterBank = 14;
        sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    }
    else if(pstHalPorting->ulChannel == 2)
    {
        sFilterConfig.FilterBank = 14;
        //sFilterConfig.SlaveStartFilterBank = 14;
        sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO1;
    }
    else
    {
        return FALSE; // Invalid channel
    }

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

    if(pstHalPorting->ulChannel == 1)
    {
        pHndCAN = &hcan1;
        ulCAN_IT_RX_FIFO_MSG_PENDING = CAN_IT_RX_FIFO0_MSG_PENDING;
    }
    else if(pstHalPorting->ulChannel == 2)
    {
        pHndCAN = &hcan2;
        ulCAN_IT_RX_FIFO_MSG_PENDING = CAN_IT_RX_FIFO1_MSG_PENDING;
    }
    else
    {
        return;
    }

    // CAN 인터럽트 활성화 (수신 인터럽트)
    uint32_t ulInterruptFlags = (ulCAN_IT_RX_FIFO_MSG_PENDING 
        | CAN_IT_TX_MAILBOX_EMPTY
        | CAN_IT_ERROR_WARNING 
        | CAN_IT_ERROR_PASSIVE 
        | CAN_IT_BUSOFF 
        | CAN_IT_LAST_ERROR_CODE);
    if (HAL_CAN_ActivateNotification(pHndCAN, ulInterruptFlags) != HAL_OK)
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

    if(pstHalPorting->ulChannel == 1)
    {
        pHndCAN = &hcan1;
        ulCAN_IT_RX_FIFO_MSG_PENDING = CAN_IT_RX_FIFO0_MSG_PENDING;
    }
    else if(pstHalPorting->ulChannel == 2)
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
    CAN_HandleTypeDef* h = (pstHalPorting->ulChannel==1) ? &hcan1 : &hcan2;
    uint32_t fifo = (pstHalPorting->ulChannel==1) ? CAN_RX_FIFO0 : CAN_RX_FIFO1;
    return (HAL_CAN_GetRxFifoFillLevel(h, fifo) == 0);
}

BOOL EngHAL_CAN_IsTxFIFOEmpty_F4xx(THalCANPorting *pstHalPorting)
{
    CAN_HandleTypeDef* h = (pstHalPorting->ulChannel==1) ? &hcan1 : &hcan2;
    return (HAL_CAN_GetTxMailboxesFreeLevel(h) > 0);
}

void EngHAL_CAN_Transmit_F4xx(THalCANPorting *pstHalPorting, U8 pubData[], U8 ubLength)
{
    CAN_HandleTypeDef* pHndCAN = NULL;
    CAN_TxHeaderTypeDef TxHeader;
    uint32_t TxMailbox;

    if(pstHalPorting->ulChannel == 1)
    {
        pHndCAN = &hcan1;
        EngHAL_CAN_LogErrors(pHndCAN);
    }
    else if(pstHalPorting->ulChannel == 2)
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
        TxHeader.StdId = HOST_CAN_ID;//pstHalPorting->ulId;
        //TxHeader.ExtId = 0x01;
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

    HAL_StatusTypeDef st = HAL_CAN_AddTxMessage(pHndCAN, &TxHeader, pubData, &TxMailbox);
    if (st == HAL_OK) 
    {
        return;
    }
    
    if (st == HAL_BUSY) 
    {
        // 상위(Drv)에서 소프트 큐에 적재하거나, 다음 주기에 재시도
        return;
    }
    
    Error_Handler();// HAL_ERROR 등만 치명 처리
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

    if(pstHalPorting->ulChannel == 1)
    {
        pHndCAN = &hcan1;
    }
    else if(pstHalPorting->ulChannel == 2)
    {
        pHndCAN = &hcan2;
    }
    else
    {
        return;
    }

    pRxBuffer = &astHalCANRxBuffer[pstHalPorting->ulChannel - 1];

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
    THalCANPorting* pstHalPorting = NULL;
    THalCANRxBuffer* pRxBuffer = NULL;
    CAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8] = {0,};

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
    {
        Error_Handler();
    }

    pstHalPorting = EngHAL_FindHalCAN(HAL_CAN_NAME_MOTOR_CTRL);
    if(pstHalPorting != NULL && pstHalPorting->ulId == RxHeader.StdId)
    {
        pRxBuffer = &astHalCANRxBuffer[0];

        for (int i = 0; i < RxHeader.DLC; i++)
        {
            pRxBuffer->pubData[i] = RxData[i];
            pstHalPorting->pubData[i] = RxData[i];
        }

        DBG_ENGHAL_CAN_TO_SWO(ENG_DBG_STRING"Id = 0x%x, DLC=%d, Data = 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x"
        , ENG_TICK, "EngHAL_CAN", RxHeader.StdId, RxHeader.DLC
        , RxData[0], RxData[1], RxData[2], RxData[3], RxData[4], RxData[5], RxData[6], RxData[7]);

        pRxBuffer->ubLength = RxHeader.DLC;
        pstHalPorting->ulDLC = RxHeader.DLC;

        if(g_pfnHalCanEventCallback[HAL_EVENT_CAN1_RX] != NULL)
        {
            g_pfnHalCanEventCallback[HAL_EVENT_CAN1_RX](); // Call the registered callback for CAN1 RX
        }
    }
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

    //taskENTER_CRITICAL();
    pRxBuffer = &astHalCANRxBuffer[1];

    //printf("Received CAN message with ID: 0x%03X, Data: ", RxHeader.StdId);
    for (int i = 0; i < RxHeader.DLC; i++)
    {
        pRxBuffer->pubData[i] = RxData[i];
    }
    pRxBuffer->ubLength = RxHeader.DLC;
    //taskEXIT_CRITICAL();

    if(g_pfnHalCanEventCallback[HAL_EVENT_CAN2_RX] != NULL)
    {
        g_pfnHalCanEventCallback[HAL_EVENT_CAN2_RX](); // Call the registered callback for CAN2 RX
    }
}

U32 EngHAL_CAN_GetRxFifoFillLevel_STM32F4xx(THalCANPorting *pstHalPorting)
{
    if(pstHalPorting->ulChannel == 1)
    {
        uint32_t fill = HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0 /* 또는 FIFO1, 설정에 맞춤 */);
        if (fill > 0) 
        {
            CAN_RxHeaderTypeDef rxh; uint8_t data[8];
            HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0 /* 또는 1 */, &rxh, data);
            DBG_ENGHAL_CAN_TO_SWO(ENG_DBG_STRING"EngHAL_CAN_GetRxFifoFillLevel_STM32F4xx", ENG_TICK, "EngHAL_CAN");
        }
    }
    else if(pstHalPorting->ulChannel == 2)
    {
        uint32_t fill = HAL_CAN_GetRxFifoFillLevel(&hcan2, CAN_RX_FIFO1 /* 또는 FIFO0, 설정에 맞춤 */);
        if (fill > 0) 
        {
            CAN_RxHeaderTypeDef rxh; uint8_t data[8];
            HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO1 /* 또는 0 */, &rxh, data);
            // 여기에 LED 토글/카운터 증가/간단 로그 등 넣어 실제 수신 확인
        }
    }
}

void EngHAL_CAN_LogErrors(CAN_HandleTypeDef *hcan)
{
    uint32_t esr = hcan->Instance->ESR;
    uint32_t rec = (esr >> 24) & 0xFF;   // Receive Error Counter
    uint32_t tec = (esr >> 16) & 0xFF;   // Transmit Error Counter
    uint32_t lec = (esr >> 4)  & 0x07;   // Last Error Code: 1=Stuff,2=Form,3=ACK,4=BitRecessive,5=BitDominant,6=CRC

    DBG_ENGHAL_CAN_TO_SWO(ENG_DBG_STRING"ESR=0x%08lX REC=%lu TEC=%lu LEC=%lu", ENG_TICK, "EngHAL_CAN", esr, rec, tec, lec);
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef* hcan)
{
    uint32_t he = HAL_CAN_GetError(hcan);
    uint32_t esr = hcan->Instance->ESR;
    uint32_t rec = (esr >> 24) & 0xFF;
    uint32_t tec = (esr >> 16) & 0xFF;
    uint32_t lec = (esr >>  4) & 0x07;

    DBG_ENGHAL_CAN_TO_SWO(ENG_DBG_STRING"[CAN ERR] HE=0x%08lX%s%s%s%s%s%s  ESR=0x%08lX REC=%lu TEC=%lu LEC=%lu\n",
        ENG_TICK, "EngHAL_CAN",
        he,
        (he & HAL_CAN_ERROR_ACK)       ? " ACK" : "",
        (he & HAL_CAN_ERROR_RX_FOV0)   ? " RXFOV" : "",
        (he & HAL_CAN_ERROR_TX_ALST0)  ? " TXALST0" : "",
        (he & HAL_CAN_ERROR_TX_TERR0)  ? " TXTERR0" : "",
        (he & HAL_CAN_ERROR_BOF)       ? " BOFF" : "",
        (he & HAL_CAN_ERROR_EPV)       ? " EPV" : "",
        esr, rec, tec, lec);

    if (he & HAL_CAN_ERROR_BOF) 
    {
        HAL_CAN_Stop(hcan);
        // 필요시 대기/카운터 초기화
        HAL_CAN_Start(hcan);
        
        uint32_t ulCAN_IT_RX_FIFO_MSG_PENDING = 0;
        ulCAN_IT_RX_FIFO_MSG_PENDING = CAN_IT_RX_FIFO0_MSG_PENDING;
        uint32_t ulInterruptFlags = (ulCAN_IT_RX_FIFO_MSG_PENDING 
        | CAN_IT_TX_MAILBOX_EMPTY
        | CAN_IT_ERROR_WARNING 
        | CAN_IT_ERROR_PASSIVE 
        | CAN_IT_BUSOFF 
        | CAN_IT_LAST_ERROR_CODE);
        HAL_CAN_ActivateNotification(hcan, ulInterruptFlags);
        // 소프트 TX 큐 리셋 등
    }
}
