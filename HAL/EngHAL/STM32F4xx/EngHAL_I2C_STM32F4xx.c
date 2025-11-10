/**
 * @file		EngHAL_I2C_STM32F4xx.c
 * @brief		This main code for HAL I2C Component Library.
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


#define __ENGHAL_I2C_STM32F4xx_C__

#include "Eng_CommonType.h"
#include "EngHAL_I2C_STM32F4xx.h"
#include "stm32f4xx_hal.h"

static I2C_HandleTypeDef hi2c1;
static I2C_HandleTypeDef hi2c2;
static I2C_HandleTypeDef hi2c3;

static void MX_I2C1_Init(uint32_t clock_hz);
static void MX_I2C2_Init(uint32_t clock_hz);
static void MX_I2C3_Init(uint32_t clock_hz);
/*---------- helper -------------------------*/
static void I2C1_BusRecover(void);
static void EngHAL_I2C_DebugDump(U32 ulChannel);

typedef struct
{
    I2C_TypeDef    *I2C;
    GPIO_TypeDef   *SCL_Port;
    uint16_t        SCL_Pin;
    uint8_t         SCL_AF;
    GPIO_TypeDef   *SDA_Port;
    uint16_t        SDA_Pin;
    uint8_t         SDA_AF;
    uint32_t        RCC_APB1ENR_Bit;   /* APB1ENR I2C EN bit */
} I2C_LL_Map_t;

static I2C_HandleTypeDef* prvGetHandleByChannel(U32 ulChannel)
{
    switch(ulChannel)
    {
        case HAL_I2C_CHANNEL_1: return &hi2c1;
        case HAL_I2C_CHANNEL_2: return &hi2c2;
        case HAL_I2C_CHANNEL_3: return &hi2c3;
        default: return NULL;
    }
}

/* ---------- 보조: 채널→IRQ 매핑 ---------- */
static void prvI2C_DisableNVIC(THalI2CPorting *p)
{
    switch (p->ulChannel) {
    case HAL_I2C_CHANNEL_1: NVIC_DisableIRQ(I2C1_EV_IRQn); NVIC_DisableIRQ(I2C1_ER_IRQn); break;
    case HAL_I2C_CHANNEL_2: NVIC_DisableIRQ(I2C2_EV_IRQn); NVIC_DisableIRQ(I2C2_ER_IRQn); break;
    case HAL_I2C_CHANNEL_3: NVIC_DisableIRQ(I2C3_EV_IRQn); NVIC_DisableIRQ(I2C3_ER_IRQn); break;
    default: break;
    }
}
static void prvI2C_ClearPendingNVIC(THalI2CPorting *p)
{
    switch (p->ulChannel) {
    case HAL_I2C_CHANNEL_1: NVIC_ClearPendingIRQ(I2C1_EV_IRQn); NVIC_ClearPendingIRQ(I2C1_ER_IRQn); break;
    case HAL_I2C_CHANNEL_2: NVIC_ClearPendingIRQ(I2C2_EV_IRQn); NVIC_ClearPendingIRQ(I2C2_ER_IRQn); break;
    case HAL_I2C_CHANNEL_3: NVIC_ClearPendingIRQ(I2C3_EV_IRQn); NVIC_ClearPendingIRQ(I2C3_ER_IRQn); break;
    default: break;
    }
}

/* ---------- 보조: HAL 핸들 강제 초기 상태로 되돌리기 ---------- */
static void prvI2C_ForceUnlockAndResetHandle(THalI2CPorting *p)
{
    I2C_HandleTypeDef *h = prvGetHandleByChannel(p->ulChannel);
    if (!h) return;

    /* __HAL_UNLOCK(h) : Lock=HAL_UNLOCKED */
    h->Lock      = HAL_UNLOCKED;

    /* 내부 상태/모드/에러/전송정보 리셋 */
    h->ErrorCode = HAL_I2C_ERROR_NONE;
#if defined(HAL_I2C_MODULE_ENABLED)
    h->State     = HAL_I2C_STATE_RESET;
    h->Mode      = HAL_I2C_MODE_NONE;
#endif
    h->pBuffPtr  = NULL;
#if defined(I2C_CR2_LAST) || defined(I2C_FLTR_ANOFF) || 1
    h->XferCount   = 0;
    h->XferSize    = 0;
    h->XferOptions = 0;     /* I2C_NO_OPTION_FRAME (F4 HAL에선 0) */
    h->PreviousState = 0;
#endif
}

/* Ensure the selected I2C instance is initialized (lazy init) */
static void prvEnsureI2CReady(THalI2CPorting *p)
{
    if(p == NULL) return;

    I2C_HandleTypeDef *h = prvGetHandleByChannel(p->ulChannel);
    if(h == NULL) return;

    if(h->State == HAL_I2C_STATE_RESET || h->Instance == NULL)
    {
        uint32_t clk = (p->ulClockSpeed > 0) ? p->ulClockSpeed : 400000U;
        switch(p->ulChannel)
        {
            case HAL_I2C_CHANNEL_1: MX_I2C1_Init(clk); break;
            case HAL_I2C_CHANNEL_2: MX_I2C2_Init(clk); break;
            case HAL_I2C_CHANNEL_3: MX_I2C3_Init(clk); break;
            default: break;
        }
    }
}

static void prvEnableGpioClk(GPIO_TypeDef *port)
{
    if (port == GPIOA)      __HAL_RCC_GPIOA_CLK_ENABLE();
    else if (port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    else if (port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
    else if (port == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
}

static BOOL prvGetI2CMap(THalI2CPorting *p, I2C_LL_Map_t *m)
{
    if (!p || !m) return FALSE;
    memset(m, 0, sizeof(*m));

    switch (p->ulChannel)
    {
        case HAL_I2C_CHANNEL_1: /* PB6=SCL, PB7=SDA (AF4) */
            m->I2C          = I2C1;
            m->SCL_Port     = GPIOB; m->SCL_Pin = GPIO_PIN_6; m->SCL_AF = GPIO_AF4_I2C1;
            m->SDA_Port     = GPIOB; m->SDA_Pin = GPIO_PIN_7; m->SDA_AF = GPIO_AF4_I2C1;
            m->RCC_APB1ENR_Bit = (1U << 21); /* I2C1EN */
            return TRUE;

        case HAL_I2C_CHANNEL_2: /* PB10=SCL, PB11=SDA (AF4) */
            m->I2C          = I2C2;
            m->SCL_Port     = GPIOB; m->SCL_Pin = GPIO_PIN_10; m->SCL_AF = GPIO_AF4_I2C2;
            m->SDA_Port     = GPIOB; m->SDA_Pin = GPIO_PIN_11; m->SDA_AF = GPIO_AF4_I2C2;
            m->RCC_APB1ENR_Bit = (1U << 22); /* I2C2EN */
            return TRUE;

        case HAL_I2C_CHANNEL_3: /* PA8=SCL, PC9=SDA (AF4) */
            m->I2C          = I2C3;
            m->SCL_Port     = GPIOA; m->SCL_Pin = GPIO_PIN_8; m->SCL_AF = GPIO_AF4_I2C3;
            m->SDA_Port     = GPIOC; m->SDA_Pin = GPIO_PIN_9; m->SDA_AF = GPIO_AF4_I2C3;
            m->RCC_APB1ENR_Bit = (1U << 23); /* I2C3EN */
            return TRUE;

        default:
            return FALSE;
    }
}

static inline void prvI2C_ClockEnable(const I2C_LL_Map_t *m)
{
    RCC->APB1ENR |= m->RCC_APB1ENR_Bit;
    (void)RCC->APB1ENR; /* read-back barrier */
}

static inline void prvI2C_ForceResetRelease(THalI2CPorting *p)
{
    switch (p->ulChannel)
    {
        case HAL_I2C_CHANNEL_1: __HAL_RCC_I2C1_FORCE_RESET(); __HAL_RCC_I2C1_RELEASE_RESET(); break;
        case HAL_I2C_CHANNEL_2: __HAL_RCC_I2C2_FORCE_RESET(); __HAL_RCC_I2C2_RELEASE_RESET(); break;
        case HAL_I2C_CHANNEL_3: __HAL_RCC_I2C3_FORCE_RESET(); __HAL_RCC_I2C3_RELEASE_RESET(); break;
        default: break;
    }
}

/* 1) 주변장치 비활성화 & SWRST */
static void prvI2C_DisableAndReset(THalI2CPorting *p, const I2C_LL_Map_t *m)
{
    if (!p || !m || !m->I2C) return;

    /* Disable interrupts if used (optional) */
#if defined(I2C_IT_EVT)
    I2C_HandleTypeDef *h = prvGetHandleByChannel(p->ulChannel);
    if (h) __HAL_I2C_DISABLE_IT(h, I2C_IT_EVT | I2C_IT_ERR | I2C_IT_BUF);
#endif

    /* Peripheral disable & SWRST pulse */
    CLEAR_BIT(m->I2C->CR1, I2C_CR1_PE);
    SET_BIT(m->I2C->CR1, I2C_CR1_SWRST);
    CLEAR_BIT(m->I2C->CR1, I2C_CR1_SWRST);

    /* RCC reset to clean internal state */
    prvI2C_ForceResetRelease(p);
}

/* 2) GPIO로 전환하여 9-clk 토글 + STOP 생성 (버스 클리어) */
static void prvI2C_BusClear(THalI2CPorting *p, const I2C_LL_Map_t *m)
{
    if (!p || !m) return;

    prvEnableGpioClk(m->SCL_Port);
    prvEnableGpioClk(m->SDA_Port);

    GPIO_InitTypeDef g = {0};
    g.Mode  = GPIO_MODE_OUTPUT_OD;
    g.Pull  = GPIO_PULLUP;
    g.Speed = GPIO_SPEED_FREQ_HIGH;

    g.Pin = m->SDA_Pin; HAL_GPIO_Init(m->SDA_Port, &g); /* SDA */
    g.Pin = m->SCL_Pin; HAL_GPIO_Init(m->SCL_Port, &g); /* SCL */

    /* 라인 High (풀업 의존) */
    HAL_GPIO_WritePin(m->SCL_Port, m->SCL_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(m->SDA_Port, m->SDA_Pin, GPIO_PIN_SET);
    HAL_Delay(1);

    /* SDA가 Low면 9클럭 토글 */
    for (int i=0; i<9; i++)
    {
        GPIO_PinState sda = HAL_GPIO_ReadPin(m->SDA_Port, m->SDA_Pin);
        if (sda == GPIO_PIN_SET) break;

        HAL_GPIO_WritePin(m->SCL_Port, m->SCL_Pin, GPIO_PIN_RESET); HAL_Delay(1);
        HAL_GPIO_WritePin(m->SCL_Port, m->SCL_Pin, GPIO_PIN_SET);   HAL_Delay(1);
    }

    /* STOP: SCL High에서 SDA High 해제 (둘 다 High) */
    HAL_GPIO_WritePin(m->SCL_Port, m->SCL_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(m->SDA_Port, m->SDA_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
}

/* 3) 핀 AF4-OD로 복구 */
static void prvI2C_RestoreAF(THalI2CPorting *p, const I2C_LL_Map_t *m)
{
    if (!p || !m) return;

    prvEnableGpioClk(m->SCL_Port);
    prvEnableGpioClk(m->SDA_Port);

    GPIO_InitTypeDef af = {0};
    af.Mode      = GPIO_MODE_AF_OD;
    af.Pull      = GPIO_PULLUP;      /* 외부 2.2~4.7kΩ 권장, 내부는 보조 */
    af.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;

    af.Pin       = m->SCL_Pin; af.Alternate = m->SCL_AF; HAL_GPIO_Init(m->SCL_Port, &af);
    af.Pin       = m->SDA_Pin; af.Alternate = m->SDA_AF; HAL_GPIO_Init(m->SDA_Port, &af);
}

/* 4) 현재 버스가 유휴인지 판단 */
static BOOL prvI2C_BusIsIdle(const I2C_LL_Map_t *m)
{
    if (!m) return FALSE;

    /* 입력레벨 확인용: 일시적으로 입력으로 읽고 싶다면 별도 처리 가능. 간략히 IDR 사용 */
    uint32_t scl = (m->SCL_Port->IDR & m->SCL_Pin);
    uint32_t sda = (m->SDA_Port->IDR & m->SDA_Pin);

    BOOL linesHigh = (scl && sda) ? TRUE : FALSE;
    BOOL busy = ((m->I2C->SR2 >> 1) & 0x1) ? TRUE : FALSE;

    return (linesHigh && !busy);
}



void EngHAL_I2C_Init_F4xx(THalI2CPorting *pstHalPorting)
{
    if(pstHalPorting == NULL) return;

    uint32_t clock = (pstHalPorting->ulClockSpeed > 0) ? pstHalPorting->ulClockSpeed : 400000U;

    if(pstHalPorting->ulChannel == HAL_I2C_CHANNEL_2)
    {
        MX_I2C2_Init(clock);
    }
    else if(pstHalPorting->ulChannel == HAL_I2C_CHANNEL_1)
    {
        MX_I2C1_Init(clock);
    }
    else if(pstHalPorting->ulChannel == HAL_I2C_CHANNEL_3)
    {
        MX_I2C3_Init(clock);
    }
    else
    {
        /* Unsupported channel */
        ASSERT(0);
    }
}

BOOL EngHAL_I2C_MemRead_F4xx(THalI2CPorting *pstHalPorting, U16 devAddr7b, U16 memAddr, U16 memAddrSize, U8 *pData, U16 len, U32 timeout)
{
    if(pstHalPorting == NULL || pData == NULL || len == 0) 
        return FALSE;

    //prvEnsureI2CReady(pstHalPorting); // 수행시간 많이 잡아먹나?? 
    I2C_HandleTypeDef *h = prvGetHandleByChannel(pstHalPorting->ulChannel);
    
    if(!h) 
        return FALSE;

    HAL_StatusTypeDef st = HAL_I2C_Mem_Read(h, (devAddr7b << 1), memAddr, (memAddrSize == 2) ? I2C_MEMADD_SIZE_16BIT : I2C_MEMADD_SIZE_8BIT, pData, len, timeout);
    if(st == HAL_OK)
        return TRUE;

    // EngHAL_I2C_RecoverAndReinit_F4xx(pstHalPorting);
    // st = HAL_I2C_Mem_Read(h, (devAddr7b<<1), memAddr, (memAddrSize==2)?I2C_MEMADD_SIZE_16BIT:I2C_MEMADD_SIZE_8BIT, pData, len, timeout);
    // if(st == HAL_OK)
    //     return TRUE;

    // if(st == HAL_BUSY) 
    // {
    //     prvI2C_ForceUnlockAndResetHandle(pstHalPorting); // 핸들 락/상태를 RESET으로 강제 후 재초기화
    //     EngHAL_I2C_RecoverAndReinit_F4xx(pstHalPorting); // 주변장치 DeInit/Init로 핸들 상태까지 HAL이 다시 세팅하도록 (MX_I2Cx_Init 안에서 HAL_I2C_Init 호출됨)
    //     st = HAL_I2C_Mem_Read(h, (devAddr7b<<1), memAddr, (memAddrSize==2)?I2C_MEMADD_SIZE_16BIT:I2C_MEMADD_SIZE_8BIT, pData, len, timeout); // 최종 재시도
    // }

    return (st == HAL_OK);
}

BOOL EngHAL_I2C_MemWrite_F4xx(THalI2CPorting *pstHalPorting, U16 devAddr7b, U16 memAddr, U16 memAddrSize, const U8 *pData, U16 len, U32 timeout)
{
    if(pstHalPorting == NULL || pData == NULL || len == 0) 
        return FALSE;
    
    I2C_HandleTypeDef *h = prvGetHandleByChannel(pstHalPorting->ulChannel);
    
    if(!h) 
        return FALSE;

    HAL_StatusTypeDef st = HAL_I2C_Mem_Write(h, (devAddr7b << 1), memAddr, (memAddrSize == 2) ? I2C_MEMADD_SIZE_16BIT : I2C_MEMADD_SIZE_8BIT, (uint8_t*)pData, len, timeout);
    
    return (st == HAL_OK) ? TRUE : FALSE;
}

BOOL EngHAL_I2C_Read_F4xx(THalI2CPorting *pstHalPorting, U16 devAddr7b, U8 *pData, U16 len, U32 timeout)
{
    if(pstHalPorting == NULL || pData == NULL || len == 0) 
        return FALSE;
    
    I2C_HandleTypeDef *h = prvGetHandleByChannel(pstHalPorting->ulChannel);
    
    if(!h) 
        return FALSE;

    HAL_StatusTypeDef st = HAL_I2C_Master_Receive(h, (devAddr7b << 1), pData, len, timeout);
    
    return (st == HAL_OK) ? TRUE : FALSE;
}

BOOL EngHAL_I2C_Write_F4xx(THalI2CPorting *pstHalPorting, U16 devAddr7b, const U8 *pData, U16 len, U32 timeout)
{
    if(pstHalPorting == NULL || pData == NULL || len == 0) 
        return FALSE;
    
    I2C_HandleTypeDef *h = prvGetHandleByChannel(pstHalPorting->ulChannel);
    
    if(!h) 
        return FALSE;

    HAL_StatusTypeDef st = HAL_I2C_Master_Transmit(h, (devAddr7b << 1), (uint8_t*)pData, len, timeout);
    
    return (st == HAL_OK) ? TRUE : FALSE;
}

/* --- AS5600 helpers (Temporary) ------------------------------------------------------- */
BOOL EngHAL_AS5600_ReadRawAngle_F4xx(THalI2CPorting *pstHalPorting, U16 *pRaw)
{
    if(pstHalPorting == NULL || pRaw == NULL) return FALSE;

    U8 buf[2] = {0};

    if(!EngHAL_I2C_MemRead_F4xx(pstHalPorting, AS5600_I2C_ADDR7, AS5600_REG_RAW_ANGLE_MSB, 1, buf, 2, AS5600_I2C_TIMEOUT))
        return FALSE;

    *pRaw = ((U16)buf[0] << 8) | buf[1];
    return TRUE;
}

BOOL EngHAL_AS5600_ReadAngle12_F4xx(THalI2CPorting *pstHalPorting, U16 *pAngle12)
{
    if(pstHalPorting == NULL || pAngle12 == NULL) return FALSE;

    U8 buf[2] = {0};
    
    if(!EngHAL_I2C_MemRead_F4xx(pstHalPorting, AS5600_I2C_ADDR7, AS5600_REG_ANGLE_MSB, 1, buf, 2, AS5600_I2C_TIMEOUT))
        return FALSE;

    /* 12-bit value in bits [11:0] */
    U16 v = ((U16)buf[0] << 8) | buf[1];
    *pAngle12 = (v & 0x0FFF);
    return TRUE;
}

/* === Private: Instance initializers ====================================== */

static void MX_I2C2_Init(uint32_t clock_hz)
{
    /* GPIO: PB10=SCL, PB11=SDA (AF4) */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP; /* External pull-ups recommended; internal pull-up as fallback */
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_RCC_I2C2_CLK_ENABLE();

    hi2c2.Instance = I2C2;
    hi2c2.Init.ClockSpeed = clock_hz;
    hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c2.Init.OwnAddress1 = 0;
    hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c2.Init.OwnAddress2 = 0;
    hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c2) != HAL_OK)
    {
        Error_Handler();
    }
}

static void MX_I2C1_Init(uint32_t clock_hz)
{
    /* GPIO: PB6=SCL, PB7=SDA (AF4) */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_RCC_I2C1_CLK_ENABLE();
    __HAL_RCC_I2C1_FORCE_RESET();
    __HAL_RCC_I2C1_RELEASE_RESET();

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = (clock_hz > 0U) ? clock_hz : 100000U;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    //if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    //{
    //    Error_Handler();
    //}

    HAL_StatusTypeDef st = HAL_I2C_Init(&hi2c1);
    // DBG_SWO(ENG_DBG_STRING"[I2C1 INIT] ret=%d state=%d err=0x%08lX APB1ENR=0x%08lX",ENG_TICK,"EngHAL_I2C", 
    //     st, (int)HAL_I2C_GetState(&hi2c1), HAL_I2C_GetError(&hi2c1), (unsigned long)RCC->APB1ENR);
    // DBG_SWO(ENG_DBG_STRING"[RCC] APB1ENR=0x%08lX APB1RSTR=0x%08lX",
    //     ENG_TICK,"EngHAL_I2C", (unsigned long)RCC->APB1ENR, (unsigned long)RCC->APB1RSTR);
        
    if (st != HAL_OK) 
    {
        DBG_SWO(ENG_DBG_STRING"[I2C1 INIT] HAL_I2C_Init FAILED!", ENG_TICK, "EngHAL_I2C");
    }
}

static void MX_I2C3_Init(uint32_t clock_hz)
{
    /* GPIO: PA8=SCL (AF4), PC9=SDA (AF4) */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* PA8 */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* PC9 */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C3;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    __HAL_RCC_I2C3_CLK_ENABLE();

    hi2c3.Instance = I2C3;
    hi2c3.Init.ClockSpeed = clock_hz;
    hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c3.Init.OwnAddress1 = 0;
    hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c3.Init.OwnAddress2 = 0;
    hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c3) != HAL_OK)
    {
        Error_Handler();
    }
}

static void I2C1_BusRecover(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* SCL/SDA를 GPIO로 일시 전환 (Open-Drain, Pull-up) */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    /* SDA=PB7, SCL=PB6 */
    GPIO_InitStruct.Pin = GPIO_PIN_7; HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_6; HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* 9클럭 토글 */
    for (int i=0; i<9; i++)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
        HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
        HAL_Delay(1);
    }

    /* STOP 생성: SCL=High에서 SDA High */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    HAL_Delay(1);

    /* 다시 AF로 복원 → HAL_I2C_Init 호출 */
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void EngHAL_I2C_Scan(THalI2CPorting *pstHalPorting)
{
    prvEnsureI2CReady(pstHalPorting);

    I2C_HandleTypeDef *h = prvGetHandleByChannel(pstHalPorting->ulChannel);

    if (!__HAL_RCC_I2C1_IS_CLK_ENABLED() || (I2C1->CR1 == 0x0000U))
    {
        uint32_t hz = (pstHalPorting && pstHalPorting->ulClockSpeed) ? pstHalPorting->ulClockSpeed : 100000U;
        MX_I2C1_Init(hz);
    }

    EngHAL_I2C_DebugDump(pstHalPorting->ulChannel);
    
    DBG_SWO(ENG_DBG_STRING"I2C ch=%d scan...", ENG_TICK, "EngHAL_I2C", pstHalPorting->ulChannel);

    for (uint8_t addr=1; addr<0x7F; addr++) 
    {
        if (HAL_I2C_IsDeviceReady(h, (addr<<1), 2, 5) == HAL_OK) 
        {
            DBG_SWO(ENG_DBG_STRING"Found 0x%02X", ENG_TICK, "EngHAL_I2C", addr);
        }
    }
}

/* === Public: 채널별 Recovery + Reinit =================================== */
void EngHAL_I2C_RecoverAndReinit_F4xx(THalI2CPorting *p)
{
    if (!p) return;

    I2C_LL_Map_t m;
    if (!prvGetI2CMap(p, &m)) return;

    /* 0) NVIC 비활성/보류 클리어: 스푸리어스 IRQ로 상태 다시 꼬임 방지 */
    prvI2C_DisableNVIC(p);
    prvI2C_ClearPendingNVIC(p);

    /* 1) HAL 핸들 상태/락 강제 초기화 */
    prvI2C_ForceUnlockAndResetHandle(p);

    /* 2) 주변장치 Disable+SWRST+RCC Reset */
    prvI2C_DisableAndReset(p, &m);

    /* 3) BUSY 또는 SDA Low 고착 시 GPIO 9-클럭 버스 클리어 */
    if (!prvI2C_BusIsIdle(&m))
    {
        prvI2C_BusClear(p, &m);
    }

    /* 4) 핀 AF4-OD로 복구 + 클록 보장(|=) */
    prvI2C_RestoreAF(p, &m);
    prvI2C_ClockEnable(&m);

    /* 5) HAL 재초기화 (채널별 MX) -> 핸들 State=READY 로 전환 */
    uint32_t hz = (p->ulClockSpeed > 0U) ? p->ulClockSpeed : 100000U;
    switch (p->ulChannel)
    {
        case HAL_I2C_CHANNEL_1: MX_I2C1_Init(hz); break;
        case HAL_I2C_CHANNEL_2: MX_I2C2_Init(hz); break;
        case HAL_I2C_CHANNEL_3: MX_I2C3_Init(hz); break;
        default: break;
    }
}

void EngHAL_I2C_BusClearOnly_F4xx(THalI2CPorting *p)
{
    if (!p) return;
    I2C_LL_Map_t m;
    if (!prvGetI2CMap(p, &m)) return;

    prvI2C_DisableAndReset(p, &m);
    prvI2C_BusClear(p, &m);
    /* 핀만 AF로 복원해 두고, 재초기화는 호출 측에서 수행 가능 */
    prvI2C_RestoreAF(p, &m);
}

static void EngHAL_I2C_DebugDump(U32 ulChannel)
{
    I2C_TypeDef * pstI2C = NULL;
    uint32_t pclk = HAL_RCC_GetPCLK1Freq();
    uint32_t moder = GPIOB->MODER;
    uint32_t otyper= GPIOB->OTYPER;
    uint32_t pupdr = GPIOB->PUPDR;
    uint32_t afrl  = GPIOB->AFR[0];

    if(ulChannel == HAL_I2C_CHANNEL_1) 
    {   pstI2C = I2C1;
    }
    else if(ulChannel == HAL_I2C_CHANNEL_2)
    {
        pstI2C = I2C2;
    }
    else if(ulChannel == HAL_I2C_CHANNEL_3)
    {
        pstI2C = I2C3;
    }
    else return;

    DBG_SWO(ENG_DBG_STRING"[I2C(ch=%d) DBG] PCLK1=%lu Hz", ENG_TICK, "EngHAL_I2C", ulChannel, (unsigned long)pclk);
    DBG_SWO(ENG_DBG_STRING"[I2C(ch=%d) DBG] CR1=0x%04X CR2=0x%04X CCR=0x%04X TRISE=0x%04X SR1=0x%04X SR2=0x%04X",
            ENG_TICK, "EngHAL_I2C", ulChannel,
            pstI2C->CR1, pstI2C->CR2, pstI2C->CCR, pstI2C->TRISE, pstI2C->SR1, pstI2C->SR2);

    /* PB6/PB7 핀 상태: MODER(10=AF), OTYPER(1=OD), PUPDR(01/10), AFRL(4=AF4=I2C) */
    DBG_SWO(ENG_DBG_STRING"[I2C(ch=%d) DBG] PB6: MODER=%u OTYPER=%u PUPDR=%u AF=%u LEVEL=%u",
            ENG_TICK, "EngHAL_I2C", ulChannel,
            (moder>>(6*2))&3, (otyper>>6)&1, (pupdr>>(6*2))&3, (afrl>>(6*4))&0xF, (GPIOB->IDR>>6)&1);
    DBG_SWO(ENG_DBG_STRING"[I2C(ch=%d) DBG] PB7: MODER=%u OTYPER=%u PUPDR=%u AF=%u LEVEL=%u",
            ENG_TICK, "EngHAL_I2C", ulChannel,
            (moder>>(7*2))&3, (otyper>>7)&1, (pupdr>>(7*2))&3, (afrl>>(7*4))&0xF, (GPIOB->IDR>>7)&1);

    /* BUSY 플래그 */
    DBG_SWO(ENG_DBG_STRING"[I2C(ch=%d) DBG] BUSY=%u (SR2)",
            ENG_TICK, "EngHAL_I2C", ulChannel,
            (pstI2C->SR2 >> 1) & 0x1);
}

