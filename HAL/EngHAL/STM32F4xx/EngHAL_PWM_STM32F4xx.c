/**
 * @file		EngHAL_PWM_STM32F4xx.c
 * @brief		This main code for HAL PWM Component Library.
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

#define __ENGHAL_PWM_C__

#include "Eng_CommonType.h"
#include "EngHAL_PWM_STM32F4xx.h"

TIM_HandleTypeDef htim1;

/**
  * @brief TIM Interface Functions
  * @param None
  * @retval None
  */

void EngHAL_PWM_Init_F4xx(THalPWMPorting *pstHalPorting)
{
    if(!pstHalPorting)
        return;

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    U32 ulChannel = TIM_CHANNEL_1; // default

    switch(pstHalPorting->ubGPIOPin)
    {
        case 1: GPIO_InitStruct.Pin |= GPIO_PIN_1; break;
        case 2: GPIO_InitStruct.Pin |= GPIO_PIN_2; break;
        case 3: GPIO_InitStruct.Pin |= GPIO_PIN_3; break;
        case 4: GPIO_InitStruct.Pin |= GPIO_PIN_4; break;
        case 5: GPIO_InitStruct.Pin |= GPIO_PIN_5; break;
        case 6: GPIO_InitStruct.Pin |= GPIO_PIN_6; break;
        case 7: GPIO_InitStruct.Pin |= GPIO_PIN_7; break;
        case 8: GPIO_InitStruct.Pin |= GPIO_PIN_8; break;
        case 9: GPIO_InitStruct.Pin |= GPIO_PIN_9; break;
        case 10: GPIO_InitStruct.Pin |= GPIO_PIN_10; break;
        case 11: GPIO_InitStruct.Pin |= GPIO_PIN_11; break;
        case 12: GPIO_InitStruct.Pin |= GPIO_PIN_12; break;
        case 13: GPIO_InitStruct.Pin |= GPIO_PIN_13; break;
        case 14: GPIO_InitStruct.Pin |= GPIO_PIN_14; break;
        case 15: GPIO_InitStruct.Pin |= GPIO_PIN_15; break;
        default: return; // Error
    }

    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;

    switch(pstHalPorting->ubGPIOPort)
    {
        case PORT_A: HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); break;
        case PORT_B: HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); break;
        case PORT_C: HAL_GPIO_Init(GPIOC, &GPIO_InitStruct); break;
        case PORT_D: HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); break;
        case PORT_E: HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); break;
        case PORT_F: HAL_GPIO_Init(GPIOF, &GPIO_InitStruct); break;
        case PORT_G: HAL_GPIO_Init(GPIOG, &GPIO_InitStruct); break;
        case PORT_H: HAL_GPIO_Init(GPIOH, &GPIO_InitStruct); break;
        default: return; // Error
    }
    
    switch(pstHalPorting->ulChannel)
    {
        case 1: ulChannel = TIM_CHANNEL_1; break;
        case 2: ulChannel = TIM_CHANNEL_2; break;
        case 3: ulChannel = TIM_CHANNEL_3; break;
        case 4: ulChannel = TIM_CHANNEL_4; break;
        default: return; // Error
    }

    TIM_OC_InitTypeDef oc = {0};
    oc.Pulse = 0;
    oc.OCPolarity = TIM_OCPOLARITY_HIGH;
    oc.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    oc.OCFastMode = TIM_OCFAST_DISABLE;
    oc.OCIdleState = TIM_OCIDLESTATE_RESET;
    oc.OCNIdleState = TIM_OCNIDLESTATE_RESET;

    // === BDTR: MOE 등 ===
    TIM_BreakDeadTimeConfigTypeDef bdtr = {0};
    bdtr.OffStateRunMode  = TIM_OSSR_DISABLE;
    bdtr.OffStateIDLEMode = TIM_OSSI_DISABLE;
    bdtr.LockLevel        = TIM_LOCKLEVEL_OFF;
    bdtr.DeadTime         = 0;                  // L6230 사용 시 MCU 데드타임 불필요
    bdtr.BreakState       = TIM_BREAK_DISABLE;  // 하드 BKIN 미사용 시
    bdtr.AutomaticOutput  = TIM_AUTOMATICOUTPUT_DISABLE;

    if(pstHalPorting->ulModuleNo == HAL_MODULE_1)
    {
        htim1.Instance = TIM1;
        htim1.Init.Prescaler = 0;
        htim1.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;
        htim1.Init.Period = pstHalPorting->ulPeriod;      // 목표 PWM 주파수에 맞춰 계산
        htim1.Init.RepetitionCounter = 1;
        htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
        HAL_TIM_PWM_Init(&htim1);

        oc.OCMode = TIM_OCMODE_PWM1;

        if (HAL_TIM_PWM_ConfigChannel(&htim1, &oc, ulChannel) != HAL_OK)
        {
            Error_Handler();
        }

        if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &bdtr) != HAL_OK)
        {
            Error_Handler();
        }

        if(HAL_TIM_PWM_Start(&htim1, ulChannel) != HAL_OK)
        {
            Error_Handler();
        }
    }

    //__HAL_TIM_MOE_ENABLE(&htim1);
    //HAL_TIM_MspPostInit(&htim1);
}

