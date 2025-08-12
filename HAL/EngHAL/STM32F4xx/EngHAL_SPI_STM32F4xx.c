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
SPI_HandleTypeDef hspi3;

#define SPI1_CS_GPIO_Port   GPIOA
#define SPI1_CS_Pin         GPIO_PIN_4

#define SPI3_CS_GPIO_Port   GPIOA
#define SPI3_CS_Pin         GPIO_PIN_15

static void MX_SPI1_Init(void);
static void MX_SPI3_Init(void);

/**
  * @brief SPI Interface Functions
  * @param None
  * @retval None
  */

void EngHAL_SPI_Init_F4xx(THalSPIPorting *pstHalPorting)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(pstHalPorting == NULL)
        return;

    /* Motor Driver */
    if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_1)
    {
        MX_SPI1_Init();

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
    /* Encoder */
    else if(pstHalPorting->ulChannel == HAL_SPI_CHANNEL_3)
    {
        MX_SPI3_Init();

        /* SPI3 CS Pin Configuration */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = SPI3_CS_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(SPI3_CS_GPIO_Port, &GPIO_InitStruct);
        /* Set CS pin high */
        HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_SET);
    }
    else
    {
        /* Error */
        return;
    }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{
    /* SPI1 parameter configuration*/
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        Error_Handler();
    }

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{
    /* SPI3 parameter configuration*/
    hspi3.Instance = SPI3;
    hspi3.Init.Mode = SPI_MODE_MASTER;
    hspi3.Init.Direction = SPI_DIRECTION_2LINES;
    hspi3.Init.DataSize = SPI_DATASIZE_16BIT;
    hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi3.Init.NSS = SPI_NSS_SOFT;
    hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi3.Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(&hspi3) != HAL_OK)
    {
        Error_Handler();
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
