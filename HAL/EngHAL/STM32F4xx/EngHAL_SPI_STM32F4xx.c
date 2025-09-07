/**
 * @file		EngHAL_SPI_STM32F4xx.c
 * @brief		This main code for HAL SPI Component Library.
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

#define __ENGHAL_SPI_STM32F4xx_C__

#include "Eng_CommonType.h"
#include "EngHAL_SPI_STM32F4xx.h"
#include "stm32f4xx_hal.h"

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi4;

#define SPI1_CS_GPIO_Port   GPIOA
#define SPI1_CS_Pin         GPIO_PIN_4

#define SPI3_CS_GPIO_Port   GPIOA
#define SPI3_CS_Pin         GPIO_PIN_15


static THalStatusType EngHAL_SPI_Handle_Init(THalSPIPorting *pstHalPorting, SPI_HandleTypeDef *h);

/**
  * @brief SPI Interface Functions
  * @param None
  * @retval None
  */

THalStatusType EngHAL_SPI_Init_F4xx(THalSPIPorting *pstHalPorting)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(!pstHalPorting)
        return HAL_STATUS_ERROR;

    if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_1)
    {
        EngHAL_SPI_Handle_Init(pstHalPorting, &hspi1);

        /* SPI1 CS Pin Configuration */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = SPI1_CS_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(SPI1_CS_GPIO_Port, &GPIO_InitStruct);
        /* Set CS pin high */
        HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);
    }
    else if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_2)
    {
        /* SPI2 Initialization - Not used currently */
        return HAL_STATUS_ERROR;
    }
    else if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_3)
    {
        EngHAL_SPI_Handle_Init(pstHalPorting, &hspi3);

        /* SPI3 CS Pin Configuration */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = SPI3_CS_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(SPI3_CS_GPIO_Port, &GPIO_InitStruct);
        /* Set CS pin high */
        HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
    }
    else if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_4)
    {
        /* SPI4 Initialization - Not used currently */
        return HAL_STATUS_ERROR;
    }
    else
    {
        /* Error */
        return;
    }
}


void EngHAL_SPI_Write_F4xx(THalSPIPorting *pstHalPorting, uint8_t *tx, uint16_t len)
{
    if(pstHalPorting == NULL || tx == NULL || len == 0)
        return;

    if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_1)
    {
        HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);   // CS Low
        HAL_StatusTypeDef st = HAL_SPI_Transmit(&hspi1, tx, len, HAL_MAX_DELAY);
        HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);     // CS High
    }
    else if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_3)
    {
        HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);   // CS Low
        HAL_StatusTypeDef st = HAL_SPI_Transmit(&hspi3, tx, len, HAL_MAX_DELAY);
        HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);     // CS High
    }
    else
    {
        /* Error */
        return;
    }
}

void EngHAL_SPI_WriteRead_F4xx(THalSPIPorting *pstHalPorting, uint8_t *tx, uint8_t *rx, uint16_t len)
{
    if(pstHalPorting == NULL || tx == NULL || len == 0)
        return;

    if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_1)
    {
        HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);   // CS Low
        HAL_StatusTypeDef st = HAL_SPI_TransmitReceive(&hspi1, tx, rx, len, HAL_MAX_DELAY);
        HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);     // CS High
        return st;
    }
    else if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_3)
    {
        HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);   // CS Low
        HAL_StatusTypeDef st = HAL_SPI_TransmitReceive(&hspi3, tx, rx, len, HAL_MAX_DELAY);
        HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);     // CS High
        return st;
    }
    else
    {
        /* Error */
        return HAL_ERROR;
    }
}

THalStatusType EngHAL_SPI_Handle_Init(THalSPIPorting *pstHalPorting, SPI_HandleTypeDef *h)
{
    if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_1)
    {
        h->Instance = SPI1;
    }
    else if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_2)
    {
        h->Instance = SPI2;
    }
    else if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_3)
    {
        h->Instance = SPI3;
    }
    else if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_4)
    {
        h->Instance = SPI4;
    }
    else
    {
        return HAL_STATUS_ERROR;
    }

    if(pstHalPorting->enMode == HAL_SPI_MODE_MASTER)
        h->Init.Mode = SPI_MODE_MASTER;
    else
        h->Init.Mode = SPI_MODE_SLAVE;

    if(pstHalPorting->enDirection == HAL_SPI_DIRECTION_2LINES)
        h->Init.Direction = SPI_DIRECTION_2LINES;
    else if(pstHalPorting->enDirection == HAL_SPI_DIRECTION_2LINES_RXONLY)
        h->Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
    else
        h->Init.Direction = SPI_DIRECTION_1LINE;

    if(pstHalPorting->enDataSize == HAL_SPI_DATASIZE_8BIT)
        h->Init.DataSize = SPI_DATASIZE_8BIT;
    else
        h->Init.DataSize = SPI_DATASIZE_16BIT;

    if(pstHalPorting->enClkPolarity == HAL_SPI_CLKPOL_LOW)
        h->Init.CLKPolarity = SPI_POLARITY_LOW;
    else
        h->Init.CLKPolarity = SPI_POLARITY_HIGH;

    if(pstHalPorting->enClkPhase == HAL_SPI_CLKPHASE_1EDGE)
        h->Init.CLKPhase = SPI_PHASE_1EDGE;
    else
        h->Init.CLKPhase = SPI_PHASE_2EDGE;

    if(pstHalPorting->enNSS == HAL_SPI_NSS_SOFT)
        h->Init.NSS = SPI_NSS_SOFT;
    else if(pstHalPorting->enNSS == HAL_SPI_NSS_HARD_INPUT)
        h->Init.NSS = SPI_NSS_HARD_INPUT;
    else
        h->Init.NSS = SPI_NSS_HARD_OUTPUT;

    if(pstHalPorting->enBaudRatePrescaler == HAL_SPI_BAUDRATEPRESCALER_2)
        h->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    else if(pstHalPorting->enBaudRatePrescaler == HAL_SPI_BAUDRATEPRESCALER_4)
        h->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    else if(pstHalPorting->enBaudRatePrescaler == HAL_SPI_BAUDRATEPRESCALER_8)
        h->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    else if(pstHalPorting->enBaudRatePrescaler == HAL_SPI_BAUDRATEPRESCALER_16)
        h->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
    else if(pstHalPorting->enBaudRatePrescaler == HAL_SPI_BAUDRATEPRESCALER_32)
        h->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
    else if(pstHalPorting->enBaudRatePrescaler == HAL_SPI_BAUDRATEPRESCALER_64)
        h->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    else if(pstHalPorting->enBaudRatePrescaler == HAL_SPI_BAUDRATEPRESCALER_128)
        h->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    else
        h->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;

    if(pstHalPorting->enFirstBit == HAL_SPI_FIRSTBIT_MSB)
        h->Init.FirstBit = SPI_FIRSTBIT_MSB;
    else
        h->Init.FirstBit = SPI_FIRSTBIT_LSB;

    h->Init.TIMode = SPI_TIMODE_DISABLE;
    h->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    h->Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(h) != HAL_OK)
    {
        return HAL_STATUS_ERROR;
    }

    return HAL_STATUS_OK;
}

/* =======================  BEGIN: MA702 support additions (Temporary) ======================= */

static inline SPI_HandleTypeDef* __ma702_get_handle(THalSPIPorting *p)
{
    if (!p) return NULL;
    switch ((THalSPIChannel)p->ulChannel) {
    case HAL_SPI_CHANNEL_1: return &hspi1;
    case HAL_SPI_CHANNEL_2: return &hspi2;
    case HAL_SPI_CHANNEL_3: return &hspi3;
    case HAL_SPI_CHANNEL_4: return &hspi4;
    default: return NULL;
    }
}

static inline void __ma702_cs_low(void){ HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET); }
static inline void __ma702_cs_high(void){ HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET); }
static void __ma702_delay_us(uint32_t us){ volatile uint32_t i; while(us--){ for(i=0;i<50;i++){__NOP();} } }


HAL_StatusTypeDef EngHAL_SPI_MA702_ReadAngle12_F4xx(THalSPIPorting *p, uint16_t *ang12)
{
    if (!p || !ang12) return HAL_ERROR;
    SPI_HandleTypeDef *h = __ma702_get_handle(p);
    if (!h) return HAL_ERROR;

    uint16_t tx=0, rx=0;
    __ma702_cs_low();
    HAL_StatusTypeDef st = HAL_SPI_TransmitReceive(h, (uint8_t*)&tx, (uint8_t*)&rx, 1 /* 1x16bit */, HAL_MAX_DELAY);
    __ma702_cs_high();
    if (st != HAL_OK) return st;

    rx = (rx & MA702_ANGLE_MASK_16) >> MA702_ANGLE_SHIFT; /* [15:4] */
    *ang12 = rx;
    __ma702_delay_us(MA702_TIDLE_ANGLE_US);
    return HAL_OK;
}

float EngHAL_SPI_MA702_ReadAngleDeg_F4xx(THalSPIPorting *p)
{
    uint16_t raw=0;
    if (EngHAL_SPI_MA702_ReadAngle12(p, &raw) != HAL_OK) return -1.0f;
    return ((float)raw) * (360.0f / (float)(1u << MA702_ANGLE_BITS));
}

float EngHAL_SPI_MA702_ReadAngleRad_F4xx(THalSPIPorting *p)
{
    uint16_t raw=0;
    if (EngHAL_SPI_MA702_ReadAngle12(p, &raw) != HAL_OK) return -1.0f;
    return ((float)raw) * (6.283185307179586f / (float)(1u << MA702_ANGLE_BITS));
}

HAL_StatusTypeDef EngHAL_SPI_MA702_ReadReg_F4xx(THalSPIPorting *p, uint8_t addr5, uint8_t *val)
{
    if (!p || !val) return HAL_ERROR;
    SPI_HandleTypeDef *h = __ma702_get_handle(p);
    if (!h) return HAL_ERROR;

    uint16_t cmd  = MA702_CMD_READ_REG(addr5);
    uint16_t rx   = 0;

    __ma702_cs_low();
    HAL_StatusTypeDef st = HAL_SPI_TransmitReceive(h, (uint8_t*)&cmd, (uint8_t*)&rx, 1, HAL_MAX_DELAY);
    __ma702_cs_high();
    if (st != HAL_OK) return st;

    __ma702_delay_us(MA702_TIDLE_REG_US);

    uint16_t dummy = 0;
    rx = 0;
    __ma702_cs_low();
    st = HAL_SPI_TransmitReceive(h, (uint8_t*)&dummy, (uint8_t*)&rx, 1, HAL_MAX_DELAY);
    __ma702_cs_high();
    if (st != HAL_OK) return st;

    *val = (uint8_t)((rx >> 8) & 0xFFu);
    __ma702_delay_us(MA702_TIDLE_REG_US);
    return HAL_OK;
}

HAL_StatusTypeDef EngHAL_SPI_MA702_WriteReg_F4xx(THalSPIPorting *p, uint8_t addr5, uint8_t v, uint8_t *echo)
{
    if (!p) return HAL_ERROR;
    SPI_HandleTypeDef *h = __ma702_get_handle(p);
    if (!h) return HAL_ERROR;

    uint16_t frame = MA702_CMD_WRITE_REG(addr5, v);
    uint16_t rx    = 0;

    __ma702_cs_low();
    HAL_StatusTypeDef st = HAL_SPI_TransmitReceive(h, (uint8_t*)&frame, (uint8_t*)&rx, 1, HAL_MAX_DELAY);
    __ma702_cs_high();
    if (st != HAL_OK) return st;

    HAL_Delay(MA702_TNVM_MS); /* NVM commit ´ë±â */

    uint16_t dummy = 0;
    rx = 0;
    __ma702_cs_low();
    st = HAL_SPI_TransmitReceive(h, (uint8_t*)&dummy, (uint8_t*)&rx, 1, HAL_MAX_DELAY);
    __ma702_cs_high();
    if (st != HAL_OK) return st;

    if (echo) *echo = (uint8_t)((rx >> 8) & 0xFFu);
    __ma702_delay_us(MA702_TIDLE_REG_US);
    return HAL_OK;
}

/* =======================  END: MA702 support additions (Temporary) ========================= */