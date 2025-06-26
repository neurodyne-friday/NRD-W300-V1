/**
 * @file		EngHAL_ADC_STM32F7xx.c
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

#define __ENGHAL_ADC_C__

#include "Eng_CommonType.h"
#include "EngHAL_ADC_STM32F4xx.h"

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

/**
  * @brief ADC Interface Functions
  * @param None
  * @retval None
  */

BOOL EngHAL_ADC_Init_F4xx(THalADCPorting *pstHalPorting)
{
    ADC_MultiModeTypeDef multimode = {0};
    ADC_ChannelConfTypeDef sConfig = {0};

	//__HAL_RCC_GPIOA_CLK_ENABLE();
	//__HAL_RCC_ADC1_CLK_ENABLE();
    //__HAL_RCC_ADC2_CLK_ENABLE();
    
    /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
     */
    if(pstHalPorting->ulChannel == 1)
    {
        hadc1.Instance = ADC1;
        hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
        hadc1.Init.Resolution = ADC_RESOLUTION_12B;
        hadc1.Init.ScanConvMode = DISABLE;
        hadc1.Init.ContinuousConvMode = DISABLE;
        hadc1.Init.DiscontinuousConvMode = DISABLE;
        hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
        hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
        hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
        hadc1.Init.NbrOfConversion = 1;
        hadc1.Init.DMAContinuousRequests = DISABLE;
        hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

        if (HAL_ADC_Init(&hadc1) != HAL_OK)
        {
            Error_Handler();
        }

        /** Configure the ADC multi-mode
         */
        multimode.Mode = ADC_TRIPLEMODE_REGSIMULT_AlterTrig;
        multimode.DMAAccessMode = ADC_DMAACCESSMODE_DISABLED;
        multimode.TwoSamplingDelay = ADC_TWOSAMPLINGDELAY_5CYCLES;
        if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
        {
            Error_Handler();
        }

        /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
         */
        sConfig.Channel = ADC_CHANNEL_10;
        sConfig.Rank = 1;
        sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
        if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
        {
            Error_Handler();
        }
    }

    /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
     */
    if(pstHalPorting->ulChannel == 2)
    {
        hadc2.Instance = ADC2;
        hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
        hadc2.Init.Resolution = ADC_RESOLUTION_12B;
        hadc2.Init.ScanConvMode = DISABLE;
        hadc2.Init.ContinuousConvMode = DISABLE;
        hadc2.Init.DiscontinuousConvMode = DISABLE;
        hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
        hadc2.Init.NbrOfConversion = 1;
        hadc2.Init.DMAContinuousRequests = DISABLE;
        hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

        if (HAL_ADC_Init(&hadc2) != HAL_OK)
        {
            Error_Handler();
        }

        /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
         */
        sConfig.Channel = ADC_CHANNEL_11;
        sConfig.Rank = 1;
        sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

        if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
        {
            Error_Handler();
        }
    }

    /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
     */
    if(pstHalPorting->ulChannel == 3)
    {
        hadc3.Instance = ADC3;
        hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
        hadc3.Init.Resolution = ADC_RESOLUTION_12B;
        hadc3.Init.ScanConvMode = DISABLE;
        hadc3.Init.ContinuousConvMode = DISABLE;
        hadc3.Init.DiscontinuousConvMode = DISABLE;
        hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
        hadc3.Init.NbrOfConversion = 1;
        hadc3.Init.DMAContinuousRequests = DISABLE;
        hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

        if (HAL_ADC_Init(&hadc3) != HAL_OK)
        {
            Error_Handler();
        }

        /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
         */
        sConfig.Channel = ADC_CHANNEL_12;
        sConfig.Rank = 1;
        sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
        
        if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
        {
            Error_Handler();
        }
    }
}

