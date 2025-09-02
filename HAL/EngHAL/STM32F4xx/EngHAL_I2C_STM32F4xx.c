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
    
    I2C_HandleTypeDef *h = prvGetHandleByChannel(pstHalPorting->ulChannel);
    
    if(!h) 
        return FALSE;

    HAL_StatusTypeDef st = HAL_I2C_Mem_Read(h, (devAddr7b << 1), memAddr, (memAddrSize == 2) ? I2C_MEMADD_SIZE_16BIT : I2C_MEMADD_SIZE_8BIT, pData, len, timeout);
    
    return (st == HAL_OK) ? TRUE : FALSE;
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

/* --- AS5600 helpers ------------------------------------------------------- */
BOOL EngHAL_AS5600_ReadRawAngle_F4xx(THalI2CPorting *pstHalPorting, U16 *pRaw)
{
    if(pstHalPorting == NULL || pRaw == NULL) return FALSE;

    U8 buf[2] = {0};

    if(!EngHAL_I2C_MemRead_F4xx(pstHalPorting, AS5600_I2C_ADDR7, AS5600_REG_RAW_ANGLE_MSB, 1, buf, 2, 10))
        return FALSE;

    *pRaw = ((U16)buf[0] << 8) | buf[1];
    return TRUE;
}

BOOL EngHAL_AS5600_ReadAngle12_F4xx(THalI2CPorting *pstHalPorting, U16 *pAngle12)
{
    if(pstHalPorting == NULL || pAngle12 == NULL) return FALSE;

    U8 buf[2] = {0};
    
    if(!EngHAL_I2C_MemRead_F4xx(pstHalPorting, AS5600_I2C_ADDR7, AS5600_REG_ANGLE_MSB, 1, buf, 2, 10))
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

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = clock_hz;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    {
        Error_Handler();
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
