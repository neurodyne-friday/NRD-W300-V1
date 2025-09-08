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

#define UART_CHANNEL_COUNT   4
#define UART_RX_DATA_SIZE    64
#define UART_TX_DATA_SIZE    64

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

HAL_EVENT_CALLBACK g_pfnHalUartEventCallback[HAL_EVENT_UART_MAX] = {0}; // UART-RX Callback pointer

static volatile U8 s_rxByte[UART_CHANNEL_COUNT];       /* single byte staging for HAL_UART_Receive_IT */
static volatile U8 s_txBusy[UART_CHANNEL_COUNT];       /* HAL is currently transmitting a byte */
static volatile U8 s_itEnabled[UART_CHANNEL_COUNT];    /* RX interrupt mode enabled */

/* Error counters (optional diagnostics) */
static volatile U32 s_errAny[UART_CHANNEL_COUNT];
static volatile U32 s_errOverrun[UART_CHANNEL_COUNT];
static volatile U32 s_errNoise[UART_CHANNEL_COUNT];
static volatile U32 s_errFrame[UART_CHANNEL_COUNT];
static volatile U32 s_errParity[UART_CHANNEL_COUNT];

static inline UART_HandleTypeDef* __get_uart_handle(U32 ch)
{
    switch (ch)
    {
        case 1: return &huart1;
        case 2: return &huart2;
        case 3: return &huart3;
        case 4: return &huart4;
        default: return NULL;
    }
}

static inline USART_TypeDef* __get_usart_instance(U32 ch)
{
    switch (ch)
    {
        case 1: return USART1;
        case 2: return USART2;
        case 3: return USART3;
        case 4: return UART4;
        default: return NULL;
    }
}

static inline IRQn_Type __get_uasrt_irqn(U32 ch)
{
    switch (ch)
    {
        case 1: return USART1_IRQn;
        case 2: return USART2_IRQn;
        case 3: return USART3_IRQn;
        case 4: return UART4_IRQn;
        default: return (IRQn_Type)0;
    }
}

static inline int __get_index_from_instance(USART_TypeDef *inst)
{
    if (inst == USART1) return 0;
    if (inst == USART2) return 1;
    if (inst == USART3) return 2;
    if (inst == UART4)  return 3;
    return -1;
}

static inline UART_HandleTypeDef* __get_handle_from_idx(int idx)
{
    switch (idx) {
        case 0: return &huart1;
        case 1: return &huart2;
        case 2: return &huart3;
        case 3: return &huart4;
        default: return NULL;
    }
}

static inline void __arm_rx_it(int idx)
{
    UART_HandleTypeDef *h = __get_handle_from_idx(idx);
    if(!h) 
        return;
    
    /* single-byte receive; callback will push into ring and re-arm */
    (void)HAL_UART_Receive_IT(h, (U8*)&s_rxByte[idx], 1u);
}


/**
  * @brief UART Interface Functions
  * @param None
  * @retval None
  */
BOOL EngHAL_UART_Init_F4xx(THalUARTPorting *pstHalPorting)
{
    UART_HandleTypeDef *h = __get_uart_handle(pstHalPorting->ulChannel);
    USART_TypeDef     *i = __get_usart_instance(pstHalPorting->ulChannel);

    if (h == NULL || i == NULL) 
        return FALSE;

    if(pstHalPorting == NULL)
        return FALSE;

    if(pstHalPorting->ulChannel > UART_CHANNEL_COUNT || pstHalPorting->ulChannel == 0)
        return FALSE;

    h->Instance = i;
    h->Init.BaudRate = pstHalPorting->ulBaudRate;
    h->Init.WordLength = UART_WORDLENGTH_8B;
    h->Init.StopBits = UART_STOPBITS_1;
    h->Init.Parity = UART_PARITY_NONE;
    h->Init.Mode = UART_MODE_TX_RX;
    h->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    h->Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(h) != HAL_OK)
    {
        Error_Handler();
    }

    astHalUARTRxBuffer[pstHalPorting->ulChannel - 1].ubLength = 0U;
    astHalUARTTxBuffer[pstHalPorting->ulChannel - 1].ubLength = 0U;

    return TRUE;
}

void EngHAL_UART_EnableInterrupt_F4xx(THalUARTPorting *pstHalPorting)
{
    if (pstHalPorting == NULL) 
        return;
    
    UART_HandleTypeDef *h = __get_uart_handle(pstHalPorting->ulChannel);
    IRQn_Type irqn = __get_uasrt_irqn(pstHalPorting->ulChannel);
    
    if (h == NULL || irqn == 0) 
        return;

    /* RXNE/ERR 인터럽트 활성화 */
    __HAL_UART_ENABLE_IT(h, UART_IT_RXNE);
    __HAL_UART_ENABLE_IT(h, UART_IT_ERR);

    HAL_NVIC_SetPriority(irqn, 5, 0);
    HAL_NVIC_EnableIRQ(irqn);
}

void EngHAL_UART_DisableInterrupt_F4xx(THalUARTPorting *pstHalPorting)
{
    if (pstHalPorting == NULL) 
        return;
    
    UART_HandleTypeDef *h = __get_uart_handle(pstHalPorting->ulChannel);
    IRQn_Type irqn = __get_uasrt_irqn(pstHalPorting->ulChannel);
    
    if (h == NULL || irqn == 0) 
        return;

    __HAL_UART_DISABLE_IT(h, UART_IT_RXNE);
    __HAL_UART_DISABLE_IT(h, UART_IT_ERR);

    HAL_NVIC_DisableIRQ(irqn);
}

void EngHAL_UART_Transmit_F4xx(THalUARTPorting *pstHalPorting, U8 pubData[], U16 uwLength)
{
    UART_HandleTypeDef *h = __get_uart_handle(pstHalPorting->ulChannel);;

    if(pstHalPorting == NULL || h == NULL || pubData == NULL || uwLength == 0)
        return ;

    HAL_UART_Transmit(h, pubData, uwLength, HAL_MAX_DELAY);
}

void EngHAL_UART_Receive_F4xx(THalUARTPorting *pstHalPorting)
{

}

void EngHAL_UART_SendByte_F4xx(THalUARTPorting *pstHalPorting, U8 ubData)
{
    if (pstHalPorting == NULL) 
        return;
    UART_HandleTypeDef *h = __get_uart_handle(pstHalPorting->ulChannel);

    if (h == NULL) 
        return;

    HAL_UART_Transmit(h, &ubData, 1, HAL_MAX_DELAY);
}

U8 EngHAL_UART_GetByte_F4xx(THalUARTPorting *pstHalPorting)
{
    U8 b = 0;

    if (pstHalPorting == NULL) 
        return 0;
    
    UART_HandleTypeDef *h = __get_uart_handle(pstHalPorting->ulChannel);
    
    if (h == NULL) 
        return 0;

    if (HAL_UART_Receive(h, &b, 1, 0) == HAL_OK)
        return b;

    return 0;
}

BOOL EngHAL_UART_IsRxFIFOEmpty_F4xx(THalUARTPorting *pstHalPorting)
{
    if (pstHalPorting == NULL) 
        return TRUE;
    
    UART_HandleTypeDef *h = __get_uart_handle(pstHalPorting->ulChannel);
    
    if (h == NULL) 
        return TRUE;

    return (__HAL_UART_GET_FLAG(h, UART_FLAG_RXNE) == RESET) ? TRUE : FALSE;
}

BOOL EngHAL_UART_IsTxFIFOEmpty_F4xx(THalUARTPorting *pstHalPorting)
{
    if (pstHalPorting == NULL) 
        return TRUE;
    
    UART_HandleTypeDef *h = __get_uart_handle(pstHalPorting->ulChannel);
    
    if (h == NULL) 
        return TRUE;

    return (__HAL_UART_GET_FLAG(h, UART_FLAG_TXE) == SET) ? TRUE : FALSE;
}

void EngHAL_UART_RegisterCallback_F4xx(U32 ulEventId, void (*pfnCallback)(void))
{
    g_pfnHalUartEventCallback[ulEventId] = pfnCallback;
}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) 
{
    int idx = __get_index_from_instance(huart->Instance);
    if (idx < 0) 
        return;

    U32 e = HAL_UART_GetError(huart);
    s_errAny[idx]++;

    if (e & HAL_UART_ERROR_ORE) s_errOverrun[idx]++;
    if (e & HAL_UART_ERROR_NE)  s_errNoise[idx]++;
    if (e & HAL_UART_ERROR_FE)  s_errFrame[idx]++;
    if (e & HAL_UART_ERROR_PE)  s_errParity[idx]++;

    /* HAL 내부에서 에러 플래그 클리어함; 수신이 멈추지 않도록 즉시 재-암 */
    if (s_itEnabled[idx]) {
        __arm_rx_it(idx);
    }

    /* App hook for logging/recovery */
    //EngHAL_UART_OnError((U32)(idx == 0 ? 2 : (idx == 1 ? 3 : 4)), e);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
    int idx = __get_index_from_instance(huart->Instance);
    if (idx < 0) 
        return;

    U8 b = (U8)s_rxByte[idx];
    //prv_rx_ring_push(idx, b);
    /* App hook */
    //EngHAL_UART_OnRxByte((U32)(idx == 0 ? 2 : (idx == 1 ? 3 : 4)), b);

    /* Re-arm for next byte */
    __arm_rx_it(idx);

    if(g_pfnHalUartEventCallback[idx] != NULL)
    {
        g_pfnHalUartEventCallback[idx](); // Call the registered callback for UART RX
    }
}

