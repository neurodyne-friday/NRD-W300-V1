/**
 * @file		EngHAL_Core_STM32F4xx.c
 * @brief		This main code for HAL Core Component Library.
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

#define __ENGHAL_CORE_STM32F4xx_C__

#include "Eng_CommonType.h"
#include "EngHAL_Core_STM32F4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"


/**
  * @brief Core Interface Functions
  * @param None
  * @retval None
  */

void EngHAL_Core_Init_F4xx()
{
    HAL_Init();
}


void EngHAL_Core_SystemClock_Config_F4xx()
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 180;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;
    
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Activate the Over-Drive mode
     */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }

    /* Distribure LSI to RTC */
    HAL_PWR_EnableBkUpAccess();                   // Enable backup access
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_RCC_RTC_ENABLE();                       // RTC clock enable
}

void EngHAL_Core_SWO_Config_F4xx(uint32_t cpuHz, uint32_t swoHz)
{
    // DBGMCU_CR Configuration: Trace activate
    DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;

    // TPIU Configuration: Async Trace activate
    TPI->SPPR = 0x00000002; // NRZ Async
    TPI->ACPR = (cpuHz / swoHz) - 1; // 2MHz Baud Rate

    // DWT enable
    DWT->CTRL = 0x400003FE;

    // ITM activate
    ITM->LAR = 0xC5ACCE55; // Lock Access Register: ITM activate
    ITM->TCR = 0x0001000D; // Trace Control Register Configuration
    ITM->TER = 0x00000001; // Trace Enable Register Configuration 
}

void EngHAL_Core_DWT_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // TRCENA bit activate
    DWT->CYCCNT = 0;                                // Cycle-counter initialize
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;            // Cycle-counter activate
}
