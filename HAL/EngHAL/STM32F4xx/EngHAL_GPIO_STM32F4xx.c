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
#include "EngHAL_PWR_STM32F4xx.h"
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


void EngHAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{

}
