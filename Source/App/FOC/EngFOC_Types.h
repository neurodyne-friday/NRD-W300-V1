/**
 * @file        EngFOC_Types.h
 * @brief       This is type definition file for Engine System Manager componet.
 *
 * <b> Copyright 2024 by Neurodyne, Inc. All rights reserved.</b>
 *
 * This software is the confidential and proprietary information
 * of Neurodyne, Inc. ("Confidential Information"). \n
 * You shall not disclose such Confidential Information and shall use
 * it only in accordance with the terms of the license agreement
 * you entered into with Samsung.
 *
 * @author		Jeongseob Kim
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		07/11/2024(D/M/Y)
 * @version		V0.1
 */
 
#ifndef __ENGFOC_TYPES_H__
#define __ENGFOC_TYPES_H__

#include "Eng_CommonType.h"


/*
 * @brief Structure Definitions
 */
typedef struct _TEngFOCManager
{
	TEngState enPrevEngState;						/**<  TBD  */
	TEngState enEngState;							/**<  TBD  */
	
// 전역 변수 (또는 RTOS 큐/Notification으로 전달)
//float i_d_ref = 0.0f;    // d축 전류 목표값 (보통 0)
//float i_q_ref = 0.0f;    // q축 전류 목표값 (토크 요구사항에 따라 갱신)
//float theta_e = 0.0f;    // 현재 전기각 (엔코더로부터 계산)
//float v_d_out, v_q_out;  // PI 제어 출력 (d,q축 전압 명령)
//float v_alpha, v_beta;   // 역변환 후 α, β축 전압
//uint16_t adc_val_phaseA, adc_val_phaseB;  // ADC DMA로부터 얻은 샘플 값

	F32 fRefId;			// d축 전류 목표값 (보통 0)
	F32 fRefIq;			// q축 전류 목표값 (토크 요구사항에 따라 갱신)
	F32 fThetaE;		// 현재 전기각 (엔코더로부터 계산)
	F32 fOutVd;			// PI 제어 출력 (d축 전압 명령)
	F32 fOutVq;			// PI 제어 출력 (q축 전압 명령)
	F32 fVAlpha;		// 역변환 후 α축 전압
	F32 fVBeta;			// 역변환 후 β축 전압
	U16 uwADCPhaseA;	// ADC DMA로부터 얻은 샘플 값
	U16 uwADCPhaseB;	// ADC DMA로부터 얻은 샘플 값

} TEngFOCManager;

#endif /* __ENGFOC_TYPES_H__ */

