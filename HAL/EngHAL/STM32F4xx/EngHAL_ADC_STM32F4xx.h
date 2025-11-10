/**
 * @file		EngHAL_ADC_STM32F4xx.h
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
 */

#ifndef __ENGHAL_ADC_STM32F7XX_H__
#define __ENGHAL_ADC_STM32F7XX_H__

#undef EXTERN
#ifdef __ENGHAL_ADC_STM32F7XX_C__
#define EXTERN
#else
#define EXTERN extern
#endif



EXTERN BOOL EngHAL_ADC_Init_F4xx(THalADCPorting *pstHalPorting);
EXTERN void EngHAL_ADC_GetCurrentRaw_F4xx(uint16_t *pIa, uint16_t *pIb, uint16_t *pIc);
EXTERN U16 EngHAL_ADC_GetValue_F4xx(THalADCPorting *pstHalPorting);

#endif //__ENGHAL_ADC_STM32F7XX_H__