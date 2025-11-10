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

#define M_PI 3.14159265358979323846
#define ENC_CPR 16384 // 2^14
#define INV_SQRT3 0.5773502691896257f // 1/sqrt(3)

#define INT_MAX_D 10
#define INT_MAX_Q 1
#define W_INT_MAX 30
#define POS_INT_MAX 10

#define V_BUS 24.0 //24v or 48v?
#define CURRENT_SCALE 0.001596;  // ADC 값 -> 전류(A) 변환 스케일, 1ADC = 0.001596A (예: 3.3V/4096/0.82*1/0.15)
#define CURRENT_OFFSET_A 2048  // ADC 오프셋 (중간값)
#define CURRENT_OFFSET_B 2048
#define CURRENT_OFFSET_C 2048

#define POLE_PAIRS 7  // YT2804 모터 극쌍 수

/*
 * @brief Structure Definitions
 */
typedef struct _TEngFOCManager
{
	TEngState enPrevEngState;						/**<  TBD  */
	TEngState enEngState;							/**<  TBD  */

	// Measurements
	F32 fAngle;			// Current Mechanical Angle (rad, 엔코더로부터 계산)
	F32 fOmega;			// Current Angular Velocity (rad/s, 엔코더로부터 계산)

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
	F32 fIa;			// 상 A 전류 (실제값, A)
	F32 fIb;			// 상 B 전류 (실제값, A)
	F32 fIc;			// 상 C 전류 (실제값, A)

	F32 fRefOmega;		// 속도 레퍼런스

	// Gains
	F32 fKp_d;			// d축 비례 이득
	F32 fKi_d;			// d축 적분 이득
	F32 fKp_q;			// q축 비례 이득
	F32 fKi_q;			// q축 적분 이득

	F32 fKp_omega;		// 속도 제어 비례 이득
	F32 fKi_omega;		// 속도 제어 적분 이득

	F32 fKp_pos;		// 위치 제어 비례 이득
	F32 fKi_pos;		// 위치 제어 적분 이득

} TEngFOCManager;

#endif /* __ENGFOC_TYPES_H__ */

