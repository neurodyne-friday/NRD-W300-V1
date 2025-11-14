/**
 * @file		EngHAL_GPIO_STM32F4xx.c
 * @brief		This main code for HAL GPIO Component Library.
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

#define __ENGHAL_PWR_STM32F4xx_C__

#include "Eng_CommonType.h"
#include "EngHAL_Base_STM32F4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_gpio_ex.h"


/**
  * @brief GPIO Interface Functions
  * @param None
  * @retval None
  */

void EngHAL_GPIO_Config_F4xx()
{
    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}


void EngHAL_GPIO_Init_F4xx(THalGPIOPorting* pstHalPorting)
{
    if(!pstHalPorting) return;

    switch(pstHalPorting->ubGPIOPort)
    {
		case PORT_A:
			__HAL_RCC_GPIOA_CLK_ENABLE();
			break;
		case PORT_B:
			__HAL_RCC_GPIOB_CLK_ENABLE();
			break;
		case PORT_C:
			__HAL_RCC_GPIOC_CLK_ENABLE();
			break;
		default:
			break;
    }

	GPIO_TypeDef* GPIO_Port = EngHAL_Base_GetGPIOPort(pstHalPorting->ubGPIOPort);
	U16 uwPin = EngHAL_Base_GetGPIOPin(pstHalPorting->ubGPIOPin);
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin   |= uwPin;
    GPIO_InitStruct.Mode  = pstHalPorting->enInOut == HAL_GPIO_OUTPUT? GPIO_MODE_OUTPUT_PP : GPIO_MODE_INPUT;       /* 푸시풀 출력 */
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	if(GPIO_Port != NULL)
    	HAL_GPIO_Init(GPIO_Port, &GPIO_InitStruct);
	else
		return;

    /* 안전을 위해 초기 상태는 Disable(OFF) */
    HAL_GPIO_WritePin(GPIO_Port, uwPin, pstHalPorting->enInitState == HAL_GPIO_ON ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void EngHAL_GPIO_On_F4xx(THalGPIOPorting* pstHalPorting)
{
	if(!pstHalPorting) return;

	if(pstHalPorting->enInOut != HAL_GPIO_OUTPUT)
		return;

	GPIO_TypeDef* GPIO_Port = EngHAL_Base_GetGPIOPort(pstHalPorting->ubGPIOPort);
	U16 uwPin = EngHAL_Base_GetGPIOPin(pstHalPorting->ubGPIOPin);
	if(GPIO_Port != NULL)
		HAL_GPIO_WritePin(GPIO_Port, uwPin, GPIO_PIN_SET);
	else
		return;
}

void EngHAL_GPIO_Off_F4xx(THalGPIOPorting* pstHalPorting)
{
	if(!pstHalPorting) return;

	if(pstHalPorting->enInOut != HAL_GPIO_OUTPUT)
		return;

	GPIO_TypeDef* GPIO_Port = EngHAL_Base_GetGPIOPort(pstHalPorting->ubGPIOPort);
	U16 uwPin = EngHAL_Base_GetGPIOPin(pstHalPorting->ubGPIOPin);
	if(GPIO_Port != NULL)
		HAL_GPIO_WritePin(GPIO_Port, uwPin, GPIO_PIN_RESET);
	else
		return;
}

THalGPIOOnOff EngHAL_GPIO_GetState_F4xx(THalGPIOPorting* pstHalPorting)
{
	if(!pstHalPorting) return HAL_GPIO_OFF;

	if(pstHalPorting->enInOut != HAL_GPIO_INPUT)
		return HAL_GPIO_OFF;

	GPIO_TypeDef* GPIO_Port = EngHAL_Base_GetGPIOPort(pstHalPorting->ubGPIOPort);
	U16 uwPin = EngHAL_Base_GetGPIOPin(pstHalPorting->ubGPIOPin);
	if(GPIO_Port != NULL)
	{
		GPIO_PinState state = HAL_GPIO_ReadPin(GPIO_Port, uwPin);
		return (state == GPIO_PIN_SET) ? HAL_GPIO_ON : HAL_GPIO_OFF;
	}
	else
		return HAL_GPIO_OFF;
}