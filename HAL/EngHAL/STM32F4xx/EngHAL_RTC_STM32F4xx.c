/**
 * @file		EngHAL_RTC_STM32F4xx.c
 * @brief		This main code for HAL RTC Component Library.
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

#define __ENGHAL_RTC_STM32F4xx_C__

#include "Eng_CommonType.h"
#include "EngHAL_RTC_STM32F4xx.h"
#include "stm32f4xx_hal_rtc.h"
#include "stm32f4xx_hal_rtc_ex.h"


RTC_HandleTypeDef hrtc;


/**
  * @brief PWR Interface Functions
  * @param None
  * @retval None
  */

void EngHAL_RTC_Init_F4xx()
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    /** Initialize RTC Only
     */
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initialize RTC and set the Time and Date
     */
    sTime.Hours = 0x0;
    sTime.Minutes = 0x0;
    sTime.Seconds = 0x0;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }
    sDate.WeekDay = RTC_WEEKDAY_MONDAY;
    sDate.Month = RTC_MONTH_JANUARY;
    sDate.Date = 0x1;
    sDate.Year = 0x0;

    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }    
}


void EngHAL_RTC_GetDateTime_F4xx(U8* pubDateTime)
{
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
    
    if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK) {
        Error_Handler();
    }

    //printf("Time: %02x:%02x:%02x\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
    //printf("Date: %02x/%02x/20%02x\n", sDate.Date, sDate.Month, sDate.Year);
    sprintf(pubDateTime, "%02x/%02x/20%02x %02x:%02x:%02x", sDate.Date, sDate.Month, sDate.Year, sTime.Hours, sTime.Minutes, sTime.Seconds);
}
