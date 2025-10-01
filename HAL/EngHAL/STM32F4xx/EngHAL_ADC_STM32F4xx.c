/**
 * @file		EngHAL_ADC_STM32F4xx.c
 * @brief		This main code for HAL ADC Component Library.
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
 * 
 * NOTE:
 *  - We use the ADC "Injected" group (not DMA). A single ADC IRQ (JEOS) occurs
 *    per PWM period and wakes the current loop at 20 kHz.
 *  - TIM1 CH4 is configured at ARR/2; TRGO = OC4REF; ADC triggers on TRGO rising edge
 *    (center of the PWM period). TIM1.RCR must be 1 (이미 PWM HAL에서 설정).
 */

#define __ENGHAL_ADC_C__

#include "Eng_CommonType.h"
#include "EngHAL_ADC_STM32F4xx.h"

/* Already defined by PWM HAL */

ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
ADC_HandleTypeDef hadc3;

/* Latest Current Sample(12-bit raw) */
static volatile uint16_t s_u16IA = 0;
static volatile uint16_t s_u16IB = 0;
static volatile uint16_t s_u16IC = 0;

/* 주입(Injected) 시퀀스에 들어간 채널과 진행상태 */
static uint32_t s_injectedCh[3] = {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};
static uint8_t  s_injectedCount = 0;
static uint8_t  s_adcStarted    = 0;

HAL_EVENT_CALLBACK g_pfnHalAdcEventCallback[HAL_EVENT_ADC_MAX] = {0};

/* ---------- Util functions to use inner hal ---------- */
static uint32_t _map_adc_ch_from_number(uint32_t ulChannelNumber)
{
    switch(ulChannelNumber)
    {
        case 0:  return ADC_CHANNEL_0;   /* PA0  */
        case 1:  return ADC_CHANNEL_1;   /* PA1  */
        case 7:  return ADC_CHANNEL_7;   /* PA7  */
        case 8:  return ADC_CHANNEL_8;   /* PB0  */
        case 10: return ADC_CHANNEL_10;  /* PC0  */
        case 11: return ADC_CHANNEL_11;  /* PC1  */
        case 12: return ADC_CHANNEL_12;  /* PC2  */
        case 13: return ADC_CHANNEL_13;  /* PC3  */
        default: return 0xFFFFFFFFu;
    }
}

static void _enable_gpio_for_adc_ch(uint32_t hal_channel)
{
    switch(hal_channel)
    {
        case ADC_CHANNEL_0:  
            __HAL_RCC_GPIOA_CLK_ENABLE(); 
            HAL_GPIO_Init(GPIOA, &(GPIO_InitTypeDef){
                .Pin=GPIO_PIN_0, .Mode=GPIO_MODE_ANALOG, .Pull=GPIO_NOPULL});  
            break;
        case ADC_CHANNEL_1:
            __HAL_RCC_GPIOA_CLK_ENABLE(); 
            HAL_GPIO_Init(GPIOA, &(GPIO_InitTypeDef){
                .Pin=GPIO_PIN_1, .Mode=GPIO_MODE_ANALOG, .Pull=GPIO_NOPULL});  
            break;
        case ADC_CHANNEL_7:  
            __HAL_RCC_GPIOA_CLK_ENABLE(); 
            HAL_GPIO_Init(GPIOA, &(GPIO_InitTypeDef){
                .Pin=GPIO_PIN_7, .Mode=GPIO_MODE_ANALOG, .Pull=GPIO_NOPULL});
            break;
        case ADC_CHANNEL_8:  
            __HAL_RCC_GPIOB_CLK_ENABLE(); 
            HAL_GPIO_Init(GPIOB, &(GPIO_InitTypeDef){
                .Pin=GPIO_PIN_0, .Mode=GPIO_MODE_ANALOG, .Pull=GPIO_NOPULL});  
            break;
        case ADC_CHANNEL_10: 
            __HAL_RCC_GPIOC_CLK_ENABLE(); 
            HAL_GPIO_Init(GPIOC, &(GPIO_InitTypeDef){
                .Pin=GPIO_PIN_0, .Mode=GPIO_MODE_ANALOG, .Pull=GPIO_NOPULL});  
            break;
        case ADC_CHANNEL_11: 
            __HAL_RCC_GPIOC_CLK_ENABLE(); 
            HAL_GPIO_Init(GPIOC, &(GPIO_InitTypeDef){
                .Pin=GPIO_PIN_1, .Mode=GPIO_MODE_ANALOG, .Pull=GPIO_NOPULL});  
            break;
        case ADC_CHANNEL_12: 
            __HAL_RCC_GPIOC_CLK_ENABLE(); 
            HAL_GPIO_Init(GPIOC, &(GPIO_InitTypeDef){
                .Pin=GPIO_PIN_2, .Mode=GPIO_MODE_ANALOG, .Pull=GPIO_NOPULL});  
            break;
        case ADC_CHANNEL_13: 
            __HAL_RCC_GPIOC_CLK_ENABLE(); 
            HAL_GPIO_Init(GPIOC, &(GPIO_InitTypeDef){
                .Pin=GPIO_PIN_3, .Mode=GPIO_MODE_ANALOG, .Pull=GPIO_NOPULL});  
            break;
        default: 
            break;
    }
}

static void _adc1_base_init(void)
{
    __HAL_RCC_ADC1_CLK_ENABLE();

    hadc1.Instance                      = ADC1;
    hadc1.Init.ClockPrescaler           = ADC_CLOCK_SYNC_PCLK_DIV4; /* 예: PCLK2=90MHz → ADCclk=22.5MHz */
    hadc1.Init.Resolution               = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode             = ENABLE;
    hadc1.Init.ContinuousConvMode       = DISABLE;
    hadc1.Init.DiscontinuousConvMode    = DISABLE;
    hadc1.Init.NbrOfConversion          = 1; /* Regular 그룹은 FOC에 미사용 */
    hadc1.Init.ExternalTrigConv         = ADC_SOFTWARE_START;
    hadc1.Init.ExternalTrigConvEdge     = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DataAlign                = ADC_DATAALIGN_RIGHT;
    hadc1.Init.DMAContinuousRequests    = DISABLE;
    hadc1.Init.EOCSelection             = ADC_EOC_SINGLE_CONV;

    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }
}

static void _adc1_config_injected_rank(uint32_t hal_channel, uint32_t rank)
{
    ADC_InjectionConfTypeDef inj = {0};

    inj.InjectedChannel               = hal_channel;
    inj.InjectedRank                  = rank;
    inj.InjectedNbrOfConversion       = 3; /* 총 3개(IA,IB,IC) */
    inj.InjectedSamplingTime          = ADC_SAMPLETIME_15CYCLES;
    inj.ExternalTrigInjecConvEdge     = ADC_EXTERNALTRIGINJECCONVEDGE_RISING; /* 주기당 1회 */
    inj.ExternalTrigInjecConv         = ADC_EXTERNALTRIGINJECCONV_T1_TRGO;    /* TIM1 TRGO=OC4REF */
    inj.AutoInjectedConv              = DISABLE;
    inj.InjectedDiscontinuousConvMode = DISABLE;
    inj.InjectedOffset                = 0;

    if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &inj) != HAL_OK)
    {
        Error_Handler();
    }
}


/**
  * @brief ADC Interface Functions
  * @param None
  * @retval None
  */

BOOL EngHAL_ADC_Init_F4xx(THalADCPorting *pstHalPorting)
{
    if(!pstHalPorting) 
        return FALSE;
    
    if(pstHalPorting->enChipType != HAL_CHIP_STM32F4xx) 
        return FALSE;

    /* IA/IB/IC만 주입 그룹에 포함 (VBUS, TEMP는 필요 시 Regular로 별도 사용) */
    if( pstHalPorting->ulName != HAL_ADC_NAME_CURRENT_PHA &&
        pstHalPorting->ulName != HAL_ADC_NAME_CURRENT_PHB &&
        pstHalPorting->ulName != HAL_ADC_NAME_CURRENT_PHC )
    {
        /* VBUS/TEMP 등은 핀만 Analog로 풀어둠 */
        uint32_t ch = _map_adc_ch_from_number(pstHalPorting->ulChannel);
        if(ch != 0xFFFFFFFFu) 
            _enable_gpio_for_adc_ch(ch);
        return TRUE;
    }

    /* EngCM 채널 번호 → HAL 상수 */
    uint32_t hal_ch = _map_adc_ch_from_number(pstHalPorting->ulChannel);
    if(hal_ch == 0xFFFFFFFFu) 
        return FALSE;

    _enable_gpio_for_adc_ch(hal_ch);

    /* 첫 호출에서 ADC, TIM1-TRGO 세팅 */
    if(s_injectedCount == 0)
    {
        _adc1_base_init();
        EngHAL_Base_TIM1_Config_TRGO_Center();
    }

    /* 순차적으로 rank1~3 채워 넣기 (순서: IA→IB→IC) */
    if(s_injectedCount < 3)
    {
        s_injectedCh[s_injectedCount] = hal_ch;
        _adc1_config_injected_rank(hal_ch,
            (s_injectedCount == 0) ? ADC_INJECTED_RANK_1 :
            (s_injectedCount == 1) ? ADC_INJECTED_RANK_2 :
                                     ADC_INJECTED_RANK_3);
        s_injectedCount++;
    }

    /* 3개 모두 설정되면 외부트리거 기반 주입변환(인터럽트) 시작 */
    if(s_injectedCount == 3 && !s_adcStarted)
    {
        HAL_NVIC_SetPriority(ADC_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(ADC_IRQn);

        if (HAL_ADCEx_InjectedStart_IT(&hadc1) != HAL_OK)
        {
            Error_Handler();
        }
        s_adcStarted = 1u;
    }

    return TRUE;
}

/* 최신 원시 전류 샘플 얻기 (12-bit, right-aligned) */
void EngHAL_ADC_GetCurrentRaw_F4xx(uint16_t *pIa, uint16_t *pIb, uint16_t *pIc)
{
    if(pIa) *pIa = s_u16IA;
    if(pIb) *pIb = s_u16IB;
    if(pIc) *pIc = s_u16IC;
}

U16 EngHAL_ADC_GetValue_F4xx(THalADCPorting *pstHalPorting)
{
    if(!pstHalPorting) 
        return 0;
    
    if(pstHalPorting->enChipType != HAL_CHIP_STM32F4xx) 
        return 0;

    uint32_t hal_ch = _map_adc_ch_from_number(pstHalPorting->ulChannel);
    if(hal_ch == 0xFFFFFFFFu) return 0;

    /* IA/IB/IC는 EngHAL_ADC_GetCurrentRaw()로 읽도록 하고,
       VBUS/TEMP 등은 Regular 변환으로 읽기 */
    if(pstHalPorting->ulName == HAL_ADC_NAME_CURRENT_PHA)
        return s_u16IA;
    if(pstHalPorting->ulName == HAL_ADC_NAME_CURRENT_PHB)
        return s_u16IB;
    if(pstHalPorting->ulName == HAL_ADC_NAME_CURRENT_PHC)
        return s_u16IC;

    /* Regular 변환 설정 */
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel      = hal_ch;
    sConfig.Rank         = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;

    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    /* 변환 시작 */
    if (HAL_ADC_Start(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }

    /* 변환 완료 대기 */
    if (HAL_ADC_PollForConversion(&hadc1, 10) != HAL_OK)
    {
        Error_Handler();
    }

    /* 변환 결과 읽기 */
    uint16_t val = (uint16_t)HAL_ADC_GetValue(&hadc1);

    /* 변환 정지 */
    if (HAL_ADC_Stop(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }

    return val;
}

void EngHAL_ADC_RegisterCallback_F4xx(ulEventId, pfnCallback)
{
    if(ulEventId < HAL_EVENT_ADC_MAX)
    {
        g_pfnHalAdcEventCallback[HAL_EVENT_ADC_IRQ] = pfnCallback;
    }
}

/* ---------- HAL 콜백 ---------- */
// void ADC_IRQHandler(void)
// {
//     HAL_ADC_IRQHandler(&hadc1);
// }

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if(hadc->Instance != ADC1) 
        return;

    /* rank1~rank3 순으로 읽기 */
    uint16_t v1 = (uint16_t)HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_1);
    uint16_t v2 = (uint16_t)HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_2);
    uint16_t v3 = (uint16_t)HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_3);

    /* 기본 순서(IA→IB→IC)로 매핑 저장 */
    s_u16IA = v1;
    s_u16IB = v2;
    s_u16IC = v3;

    if(g_pfnHalAdcEventCallback[HAL_EVENT_ADC_IRQ] != NULL)
        g_pfnHalAdcEventCallback[HAL_EVENT_ADC_IRQ]();
}