/**
 * @file		EngHAL_Base_STM32F4xx.c
 * @brief		This main code for HAL Base Inteface Component Library.
 *
 * <b> Copyright 2024 by Neurodyne Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Neurodyne.
 *
 * @author		Jeongseob Kim
 * @imp 		
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		07/11/2025(D/M/Y)
 * @version 	V0.1
 */

#define __ENGHAL_BASE_STM32F4xx_C__

#include "Eng_CommonType.h"
#include "EngHAL_Base_STM32F4xx.h"
#include "stm32f4xx_hal.h"

// declare stm32f4xx hal handlers
TIM_HandleTypeDef htim1;

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;


void EngHAL_Base_TIM1_Probe_State(const char* tag)
{
    volatile uint32_t apb2en = RCC->APB2ENR & RCC_APB2ENR_TIM1EN;
    volatile uint32_t arr_hw = TIM1->ARR;          // 하드웨어 ARR 직접 읽기
    volatile uint32_t psc_hw = TIM1->PSC;
    volatile uint32_t cr1    = TIM1->CR1;

    DBG_SWO(ENG_DBG_STRING"[%s] APB2.TIM1EN=%lu, ARR=%lu, PSC=%lu, CR1=0x%08lx\n", ENG_TICK, "EngHAL", tag, apb2en?1:0, arr_hw, psc_hw, cr1);
}

/**
 * @brief TIM1 CH4를 ARR/2로 설정하고, TRGO=OC4REF로 설정
 *        ADC 주입(Injected) 트리거용으로 사용
 *        (TIM1 Update 이벤트는 PWM HAL에서 이미 설정됨)
 * 
 * @param[in]		None
 * @range
 * @retval			None
 * @global
 * @remarks
 */
void EngHAL_Base_TIM1_Config_TRGO_Center(void)
{
    /* TIM1 CH4를 ARR/2로 설정하고, TRGO=OC4REF로 설정 */
    TIM_OC_InitTypeDef oc = {0};
    TIM_MasterConfigTypeDef mst = {0};

    //EngHAL_Base_TIM1_Probe_State("before TRGO");

    uint32_t arr = __HAL_TIM_GET_AUTORELOAD(&htim1);
    if (arr != htim1.Init.Period) {
        // 이 경우는 여전히 이상 상태: 클럭, Instance, 타이밍 재점검
        __HAL_TIM_SET_AUTORELOAD(&htim1, htim1.Init.Period);
        HAL_TIM_GenerateEvent(&htim1, TIM_EVENTSOURCE_UPDATE);
        arr = __HAL_TIM_GET_AUTORELOAD(&htim1);
        if (arr == 0) Error_Handler();
    }

    oc.OCMode     = TIM_OCMODE_PWM1;
    oc.Pulse      = (arr + 1u) / 2u;         /* 주기 중앙 */
    oc.OCPolarity = TIM_OCPOLARITY_HIGH;
    oc.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_OC_ConfigChannel(&htim1, &oc, TIM_CHANNEL_4);
    HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_4);

    //EngHAL_Base_TIM1_Probe_State("after TRGO");

    //mst.MasterOutputTrigger = TIM_TRGO_OC4REF;      /* OC4REF를 마스터 트리거로 */
    mst.MasterOutputTrigger = TIM_TRGO_UPDATE;
    mst.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim1, &mst);
}
