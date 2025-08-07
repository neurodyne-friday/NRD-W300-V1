/**
 * @file		EngHAL_PWR_STM32F4xx.c
 * @brief		This main code for HAL Power Component Library.
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
#include "stm32f4xx_hal_pwr.h"
#include "stm32f4xx_hal_pwr_ex.h"

//TIM_HandleTypeDef htim1;

/**
  * @brief PWR Interface Functions
  * @param None
  * @retval None
  */

void EngHAL_PWR_Init_F4xx()
{
    EngHAL_PWR_PVDOn_F4xx();
}


void EngHAL_PWR_PVDOn_F4xx()
{
    /* PVD threshold level-6 ≒ 2.8 V, Enable Interrupt */
    PWR->CR |= (PWR_CR_PLS_2 | PWR_CR_PLS_1);   // Level-6
    PWR->CR |= PWR_CR_PVDE;                     // PVD Enable
    EXTI->IMR |= EXTI_IMR_IM16;                 // EXTI16 IRQ Unmask
    EXTI->FTSR |= EXTI_FTSR_TR16;               // Falling-edge detect
    NVIC_EnableIRQ(PVD_IRQn);

}

void PVD_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR16)
    {
        EXTI->PR = EXTI_PR_PR16;        // pending clear
        /* 여기서 플래시/EEPROM·BKP레지스터에 중요 데이터 기록 */
        //save_encoder_count();
    }
}

void EngHAL_PWR_Resume(void)
{
    /* 1) 리셋 원인 점검 */
    uint32_t rst = RCC->CSR;          // 리셋 상태 레지스터
    BOOL was_bor = rst & RCC_CSR_BORRSTF;
    BOOL was_pwr = rst & RCC_CSR_PORRSTF;
    /* 리셋 플래그 지우기 */
    RCC->CSR |= RCC_CSR_RMVF;

/*
    // 2) 백업 레지스터 유효성 확인 
    if ((RST->CSR & RCC_CSR_BORRSTF) &&       // 전원리셋이었고
        (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR19) == 0xA5A5)) // 마지막 마커
    {
        // 3) 엔코더 누적 카운터 복원
        uint64_t cnt  = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0) |
                        ((uint64_t)HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) << 32);
        g_encoderCount = cnt;
    }
    else {
        // 초기화 or 손상된 경우 
        g_encoderCount = 0;
    }

    // 4) 시스템 클록, 주변장치 재설정
    SystemClock_Config();
    Periph_Init();

    // 5) 백업 영역 갱신/마커 복구
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR19, 0xA5A5);    
*/    
}