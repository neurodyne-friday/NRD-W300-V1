/**
 * @file        EngSM_Main.c
 * @brief       This main code for State Manager Component.
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
 * @imp			Jeongseob Kim
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		08/11/2008(D/M/Y)
 * @version		V0.1
 */

#define	__ENGSM_MAIN_C__

#include "Eng_CommonType.h"
#include "EngAPP_FOC.h"

/* Initilize the Engine System Manager infomation */
static TEngSystemManager s_stSystemManager;

static U32 s_ulEngSMMainTaskID;
static U32 s_ulIntervalTimer[INTERVAL_TIME_MAX] = {0,0,0,0};
static BOOL s_fIntervalTimerGetValid[INTERVAL_TIME_MAX] = {FALSE,FALSE,FALSE,FALSE};

#define ENGSM_TASK_STACK_SIZE	1024
#define ENGSM_TASK_PRIORITY		150


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/

BOOL EngAPP_Initialize(void)
{
	TEngSystemManager *pstSystemManager = &s_stSystemManager;
	
	DBG_ENGSM(ENG_DBG_STRING"EngSM_Initialize", ENG_TICK, "SM");
	

    /* Initialize Engine System Manager Information Storage Variable */
//	EngLib_MemorySet(pstSystemManager, 0, (sizeof(TEngSystemManager)));

	EngSM_Constructor(pstSystemManager);

    /* Initialize MessageQ Information of Engine System Manager */
	//EngSM_InitMessage(&pstSystemManager->stMsgQCB);
	//EngSM_InitJobMessage(&pstSystemManager->stJobQCB);

	/* Initialize the state, status, timing and page class for Engine System Manager */
	//EngSM_InitState(pstSystemManager);

	/* Create the Engine Component Handler */
	EngSM_HndIF_CreateHandler();

	/* Initialize the Engine Component(paper, image, heating, error, option) Handler */
	EngSM_HndIF_Initialize();

	/* Send the first event about power on */

	if((EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_ENGINE_STATE) == ENGSM_STS_CHILD_ENGINE_TEST)
#if defined(HR_SM_SET_BOARD_CONFIG) && defined(HR_SM_SET_BOARD_CONFIG_PBA_MODE)
//		|| ((EngCM_IF_IsUsingBoardConfiguration(BOARD_CONFIG_IDPTV3_MODE) == TRUE) && ((U16)EngCM_IF_GetBoardConfiguration(BOARD_CONFIG_IDPTV3_MODE) == C_SM_IDPTV3_MODE_INPUT))
		|| ((EngCM_IF_IsUsingBoardConfiguration(BOARD_CONFIG_PBA_MODE) == TRUE)	&& (EngCM_IF_GetBoardConfiguration(BOARD_CONFIG_PBA_MODE) == C_SM_PBA_MODE_IO_INPUT))
#endif
	)
	{
		EngSM_SendEvent(ENG_EV_TEST_MODE_ON, NULL, 0, 0);
	}
	else if(EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_ENGINE_STATE) == ENGSM_STS_CHILD_ENGINE_ERROR)
	{
		EngSM_HndIF_StartHandler(ENG_HND_EH, ERROR_NAME_ASSERT, NULL);
	}	
	else
	{
		EngSM_SendEvent(ENG_EV_POWER_ON, NULL, 0, 0);
	}

//	if(EngOS_OSALCreateTask("SM", EngSM_Main, 0, ENGSM_TASK_STACK_SIZE, ENGSM_TASK_PRIORITY, &s_ulEngSMMainTaskID))
//	{
//		ASSERT(0);
//	}

	EngSM_InitialIntervalTime();

	pstSystemManager->fPowerOn = TRUE;
	pstSystemManager->fEnterSleepP2Mode = FALSE;

    return TRUE;
}

/**
* @brief		
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks		
*/
void EngAPP_Constructor(TEngSystemManager *pstSystemManager)
{
	pstSystemManager->enPrevEngState					= ENG_ST_UNSPECIFIED;
	pstSystemManager->enPrevStateBeforeSleep			= ENG_ST_UNSPECIFIED;
	pstSystemManager->enEngState						= ENG_ST_UNSPECIFIED;
	pstSystemManager->ulEvent							= ENG_EV_UNSPECIFIED;
	pstSystemManager->ulReceivedEvent					= ENG_EV_UNSPECIFIED;
}


// ADC 변환 완료 인터럽트 (혹은 DMA Half-Transfer Complete ISR)
void ADC_IRQHandler(void) 
{
    BaseType_t xHigherPTWoken = pdFALSE;

    // ADC 값 읽기 (예: ADC1=PhaseA, ADC2=PhaseB)
    adc_val_phaseA = ADC1->DR;
    adc_val_phaseB = ADC2->DR;
    
	// 전류제어 태스크에 신호 (세마포어나 직접 알림)
    vTaskNotifyGiveFromISR(CurrentControlTaskHandle, &xHigherPTWoken);
    portYIELD_FROM_ISR(xHigherPTWoken);
}


// SVPWM 계산 함수
void EngAPP_FOC_SVPWM_CalcDuty(float v_alpha, float v_beta, float Vbus, float *Ta, float *Tb, float *Tc)
{
    float Vref = sqrtf(v_alpha * v_alpha + v_beta * v_beta);
    float angle = atan2f(v_beta, v_alpha);  // -pi to pi

    if(angle < 0) 
    {
        angle += 2 * M_PI;        // 0 to 2pi
    }

    // 섹터 결정 (1~6), 한 섹터는 60도(pi/3)
    int sector = (int)(angle / (M_PI / 3.0f)) + 1;

    // 섹터 내부 각도 계산
    float angle_sector = angle - (sector - 1) * (M_PI / 3.0f);

    // PWM 주기 정규화 (0~1)
    float T1 = sqrtf(3) * (Vref / Vbus) * sinf((M_PI / 3.0f) - angle_sector);
    float T2 = sqrtf(3) * (Vref / Vbus) * sinf(angle_sector);
    float T0 = 1.0f - T1 - T2;

    float T_a, T_b, T_c;

    // 각 섹터별 PWM 듀티 계산
    switch (sector) 
    {
        case 1:
            T_a = (T1 + T2 + T0 / 2);
            T_b = (T2 + T0 / 2);
            T_c = (T0 / 2);
            break;
        case 2:
            T_a = (T1 + T0 / 2);
            T_b = (T1 + T2 + T0 / 2);
            T_c = (T0 / 2);
            break;
        case 3:
            T_a = (T0 / 2);
            T_b = (T1 + T2 + T0 / 2);
            T_c = (T2 + T0 / 2);
            break;
        case 4:
            T_a = (T0 / 2);
            T_b = (T1 + T0 / 2);
            T_c = (T1 + T2 + T0 / 2);
            break;
        case 5:
            T_a = (T2 + T0 / 2);
            T_b = (T0 / 2);
            T_c = (T1 + T2 + T0 / 2);
            break;
        case 6:
            T_a = (T1 + T2 + T0 / 2);
            T_b = (T0 / 2);
            T_c = (T1 + T0 / 2);
            break;
        default:
            // 기본적으로 모든 PWM OFF (안전상태)
            T_a = 0.5f;
            T_b = 0.5f;
            T_c = 0.5f;
            break;
    }

    // 결과값 저장 (0~1 사이의 값)
    *Ta = T_a;
    *Tb = T_b;
    *Tc = T_c;
}


// 전류 제어 태스크 (높은 우선순위)
void EngAPP_Task_CurrentControl(void *argument) 
{
    // 보정용 상수 및 변수
    const float CURRENT_SCALE = ... ;   // ADC 값 -> 전류(A) 변환 스케일
    const float INV_SQRT3 = 0.5774f;    // 1/√3
    float i_a, i_b, i_c;
    float i_alpha, i_beta;
    float i_d, i_q;
    float err_d, err_q;
    static float int_d = 0.0f, int_q = 0.0f; // 적분 누적 (Integral term)
    const float Kp_d = ... , Ki_d = ...;
    const float Kp_q = ... , Ki_q = ...;
    // (필요시 크로스 보상계수: Ld, Lq, ω 등의 변수도 선언)
    
    for(;;) 
    {
        // ADC 인터럽트로부터 알림 대기 (블로킹 대기)
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        // ADC로 읽은 값을 전류 (i_a, i_b)로 환산
        i_a = (float)adc_val_phaseA * CURRENT_SCALE;
        i_b = (float)adc_val_phaseB * CURRENT_SCALE;
        // i_c는 KCL로 계산
        i_c = -(i_a + i_b);
        
        // Clarke 변환: abc -> αβ
        i_alpha = i_a;
        i_beta  = INV_SQRT3 * (i_a + 2 * i_b);
        
        // Park 변환: αβ -> dq (현재 전기각 theta_e는 엔코더로부터 업데이트 된 상태)
        float cosT = arm_cos_f32(theta_e);
        float sinT = arm_sin_f32(theta_e);
        i_d =  i_alpha * cosT + i_beta * sinT;
        i_q = -i_alpha * sinT + i_beta * cosT;
        
        // d축 전류 제어 (PI)
        err_d = i_d_ref - i_d;
        int_d += err_d;                        // 적분항 누적

        // Anti-windup: 적분 한계 처리
        if(int_d > INT_MAX_D) 
        {
            int_d = INT_MAX_D;
        }
        if(int_d < -INT_MAX_D) 
        {
            int_d = -INT_MAX_D;
        }
        v_d_out = Kp_d * err_d + Ki_d * int_d;
        
        // q축 전류 제어 (PI)
        err_q = i_q_ref - i_q;
        int_q += err_q;

        if(int_q > INT_MAX_Q) 
        {
            int_q = INT_MAX_Q;
        }
        if(int_q < -INT_MAX_Q) 
        {
            int_q = -INT_MAX_Q;
        }
        v_q_out = Kp_q * err_q + Ki_q * int_q;
        
        // (선택) 역기전력 보상 및 decoupling 보상
        // v_d_out += -(omega_e * Lq) * i_q; 
        // v_q_out +=  (omega_e * Ld) * i_d + omega_e * lambda_m;
        
        // 역 Park 변환: dq -> αβ 전압
        v_alpha = v_d_out * cosT - v_q_out * sinT;
        v_beta  = v_d_out * sinT + v_q_out * cosT;
        
        // 공간 벡터 PWM 계산: v_alpha, v_beta -> 타이머 CCR값
        float Ta, Tb, Tc;
        //SVPWM_CalcDuty(v_alpha, v_beta, Vbus, &Ta, &Tb, &Tc);
        SVPWM_CalcDuty(v_alpha, v_beta, 24.0, &Ta, &Tb, &Tc);

        // SVPWM_CalcDuty: 참조 전압을 기준으로 섹터 결정 후 T1, T2, T0 계산, 0.0~1.0의 Ta, Tb, Tc 듀티 반환
        TIM1->CCR1 = Ta * TIM1->ARR;
        TIM1->CCR2 = Tb * TIM1->ARR;
        TIM1->CCR3 = Tc * TIM1->ARR;
        
        // (다음 인터럽트까지 대기 상태로 대기)
    }
}

// 속도 제어 태스크 (중간 우선순위, 예: 1kHz 주기)
void EngAPP_Task_SpeedControl(void *argument) 
{
    const float Ts = 0.001f;          // 1kHz 주기 (초)
    const float Kp_speed = ... , Ki_speed = ...;
    static float int_w = 0.0f;
    float omega_ref = 0.0f;           // 속도 참조 (rad/s)
    float omega_meas;                 // 측정 속도
    float pos, prev_pos = 0.0f;
    
    TickType_t lastWakeTime = xTaskGetTickCount();

    for(;;) 
    {
        // 현재 위치 읽기 (엔코더 카운터 -> 기계 각도 [rad])
        uint32_t count = TIM_ENCODER->CNT; // TIM_ENCODER is specific register pointer when set encoder interface mode
        pos = (float)count * (2 * M_PI / ENC_CPR); // (2*M_PI/ENC_CPR) => can make define
        // 속도 계산 (pos 단위 [rad], prev_pos 이용)
        float diff = pos - prev_pos;

        // 엔코더 랩어라운드 처리
        if(diff > M_PI) 
        {
            diff -= 2 * M_PI;
        }

        if(diff < -M_PI) 
        {
            diff += 2 * M_PI;
        }
        
        omega_meas = diff / Ts;              // [rad/s]
        prev_pos = pos;
        
        // 속도 PI 제어
        float err_w = omega_ref - omega_meas;
        int_w += err_w * Ts;
        // 적분 anti-windup
        if(int_w > W_INT_MAX) 
        {
            int_w = W_INT_MAX;
        }

        if(int_w < -W_INT_MAX) 
        {
            int_w = -W_INT_MAX;
        }

        float torque_cmd = Kp_speed * err_w + Ki_speed * int_w;
        
        // 토크 명령을 i_q 참조값으로 (전류 한계 고려하여 클램핑)
        float iq_max = 10.0f;  // 최대 허용 q축 전류 [A]

        if(torque_cmd > iq_max) 
        {
            torque_cmd = iq_max;
        }
        if(torque_cmd < -iq_max)
        {
            torque_cmd = -iq_max;
        }

        i_q_ref = torque_cmd;
        // (i_d_ref는 여전히 0으로 유지)
        
        vTaskDelayUntil(&lastWakeTime, 1);  // 1ms 주기 대기
    }
}

// 위치 제어 태스크 (낮은 우선순위, 예: 100Hz 주기)
void EngAPP_Task_PositionControl(void *argument) 
{
    const float Tp = 0.01f;           // 100Hz 주기 (10ms)
    const float Kp_pos = ... , Ki_pos = ...;
    static float int_pos = 0.0f;
    float target_position = 0.0f;     // 목표 위치 [rad]
    
    TickType_t lastWakeTime = xTaskGetTickCount();
    
    for(;;) 
    {
        // 현재 각도 계산 (엔코더 카운터 -> 각도 [rad], 위 SpeedControlTask의 pos 재활용 가능)
        uint32_t count = TIM_ENCODER->CNT; // TIM_ENCODER is specific register pointer when set encoder interface mode
        float pos_curr = (float)count * (2*M_PI/ENC_CPR); // (2*M_PI/ENC_CPR) => can make define
        
        // 위치 PI 제어
        float err_pos = target_position - pos_curr;
        int_pos += err_pos * Tp;
        if(int_pos > POS_INT_MAX) 
        {
            int_pos = POS_INT_MAX;
        }
        if(int_pos < -POS_INT_MAX) 
        {
            int_pos = -POS_INT_MAX;
        }
        float omega_cmd = Kp_pos * err_pos + Ki_pos * int_pos;
        
        // 속도 명령 포화 (예: 최대 속도 제한)
        float max_speed = 100.0f; // [rad/s] 
        if(omega_cmd > max_speed) 
        {
            omega_cmd = max_speed;
        }
        if(omega_cmd < -max_speed) 
        {
            omega_cmd = -max_speed;
        }
        
        // 상위 속도 참조 갱신
        // (속도 제어 태스크의 omega_ref에 반영하거나 전역 변수로 공유)
        omega_ref = omega_cmd;
        
        vTaskDelayUntil(&lastWakeTime, (TickType_t)(Tp*1000));  // 10ms 주기 대기
    }
}


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
void EngSM_InitialIntervalTime(void)
{
	U32 ulIndex = 0;

	for(ulIndex = 0; ulIndex < INTERVAL_TIME_MAX; ulIndex++)
	{
		s_ulIntervalTimer[ulIndex] = 0;
		s_fIntervalTimerGetValid[ulIndex] = FALSE;
	}
}

/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
void EngSM_CountIntervalTime(void)
{
	TEngSystemManager *pstSystemManager = &s_stSystemManager;	
	U32	ulEngState = EngSM_IF_GetDeviceStatus(ENGSM_STS_PARENT_ENGINE_STATE);
	static U32 ulPrevEngState = 0;
	static U32 ulNonSleepModeCnt = 0;
	static BOOL fPowerOnInt = TRUE;
	static BOOL fRTCChecked = FALSE;
	static BOOL fPrintChecked = FALSE;

	if(fRTCChecked)
	{
		if(fPowerOnInt == TRUE)
		{
			U32 ulPowerOffTime = 0;//EngTM_IF_GetElapsedTime(RTCITEM_POWEROFF);

			ulPowerOffTime = MINUTE_TO_MS(ulPowerOffTime);
			s_ulIntervalTimer[INTERVAL_TIME_POWER_OFF] = ulPowerOffTime;								
			s_ulIntervalTimer[INTERVAL_TIME_JOB] = ulPowerOffTime;

			s_fIntervalTimerGetValid[INTERVAL_TIME_POWER_OFF] = TRUE;
			s_fIntervalTimerGetValid[INTERVAL_TIME_JOB] = TRUE;
			
			fPowerOnInt = FALSE;
			ulPrevEngState = ulEngState;
			
			DBG_ENGSM(ENG_DBG_STRING"Power Off ElapsedTime:%umin", ENG_TICK, "SM", MS_TO_MINUTE(ulPowerOffTime));
			return;		
		}
			
		if((ulPrevEngState != ENGSM_STS_CHILD_ENGINE_SLEEP) && (ulEngState == ENGSM_STS_CHILD_ENGINE_SLEEP))			//Sleep Entry
		{
			//EngTM_IF_SetCurrentTime(RTCITEM_SLEEP);
			//EngTM_IF_SetCurrentTime(RTCITEM_POWEROFF);

			s_ulIntervalTimer[INTERVAL_TIME_SLEEP] = 0;
			s_fIntervalTimerGetValid[INTERVAL_TIME_SLEEP] = FALSE;

			//DBG_LMS_DATE(ENG_DBG_STRING"SetSleepElapsedTime", ENG_TICK, "RTC");
		}
		else if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_SLEEP) && (ulEngState != ENGSM_STS_CHILD_ENGINE_SLEEP))		//Sleep Exit
		{
			U32 ulSleepElapsedTime = 0;//EngTM_IF_GetElapsedTime(RTCITEM_SLEEP);

			//DBG_LMS_DATE(ENG_DBG_STRING"SleepElapsedTime:%umin", ENG_TICK, "RTC", ulSleepElapsedTime);
			
			ulSleepElapsedTime = MINUTE_TO_MS(ulSleepElapsedTime);
			s_ulIntervalTimer[INTERVAL_TIME_SLEEP] = ulSleepElapsedTime;
			s_ulIntervalTimer[INTERVAL_TIME_JOB] = (ulSleepElapsedTime > (MAX_U32 - s_ulIntervalTimer[INTERVAL_TIME_JOB])) ? MAX_U32 : s_ulIntervalTimer[INTERVAL_TIME_JOB] + ulSleepElapsedTime;
			
			s_fIntervalTimerGetValid[INTERVAL_TIME_SLEEP] = TRUE;
		}
		else if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_PRINTING))	//Print Exit
		{
			s_ulIntervalTimer[INTERVAL_TIME_JOB] = 0;
		}
		else if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_WAITING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_WAITING))	//Wait Exit
		{
		}
		else if((ulEngState != ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_SLEEP))
		{
			s_ulIntervalTimer[INTERVAL_TIME_JOB] = U32_SUM_CHK_WITH_OVF(s_ulIntervalTimer[INTERVAL_TIME_JOB], 10);
		}
		else if(((ulEngState == ENGSM_STS_CHILD_ENGINE_WAITING) && (ulPrevEngState != ENGSM_STS_CHILD_ENGINE_WAITING))
			|| ((ulEngState == ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulPrevEngState != ENGSM_STS_CHILD_ENGINE_PRINTING))
		)
		{
		}

		if((ulPrevEngState != ENGSM_STS_CHILD_ENGINE_STANDBY) && (ulEngState == ENGSM_STS_CHILD_ENGINE_STANDBY))
		{
			s_ulIntervalTimer[INTERVAL_TIME_READY] = 0;
		}
		else if(ulEngState == ENGSM_STS_CHILD_ENGINE_STANDBY)
		{
			s_ulIntervalTimer[INTERVAL_TIME_READY] = U32_SUM_CHK_WITH_OVF(s_ulIntervalTimer[INTERVAL_TIME_READY], 10);
		}

		if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState != ENGSM_STS_CHILD_ENGINE_WAITING))
		{
		}
		else if(ulEngState == ENGSM_STS_CHILD_ENGINE_PRINTING)
		{
			fPrintChecked = TRUE;
		}
		else if((ulPrevEngState == ENGSM_STS_CHILD_ENGINE_PRINTING) && (ulEngState == ENGSM_STS_CHILD_ENGINE_WAITING))
		{
		}
		
		/* To save the latest run time for get power off elapsed time */
		if(ulEngState != ENGSM_STS_CHILD_ENGINE_SLEEP) 
		{
			if(++ulNonSleepModeCnt >= 5 * 60 * 100)			/* every 5minute */
			{
				//EngTM_IF_SetCurrentTime(RTCITEM_POWEROFF);

				ulNonSleepModeCnt = 0;
				//DBG_LMS_DATE(ENG_DBG_STRING"SetSleepElapsedTime2", ENG_TICK, "RTC");
			}
		}
		else
		{
			ulNonSleepModeCnt = 0;
		}
		
		ulPrevEngState = ulEngState;
	}
	else if(g_ulEngTickCnt >= 400)
	{
	 	fRTCChecked = TRUE;
	}
}

/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
BOOL EngSM_IsIntervalTimeValid(TIntervalTimeType enType)
{
	BOOL fIntervalTimeValid = FALSE;

	if(enType < INTERVAL_TIME_MAX)
	{
		fIntervalTimeValid = s_fIntervalTimerGetValid[enType];
	}
		
	return fIntervalTimeValid;
}


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
U32 EngSM_GetIntervalTime(TIntervalTimeType enType)
{
	U32 ulIntervalTime = 0;

	if(enType < INTERVAL_TIME_MAX)
	{
		ulIntervalTime = s_ulIntervalTimer[enType];
	}
		
//	DBG_ENGSM(ENG_DBG_STRING"ReturnIntervalTime[%d]:%dsec", ENG_TICK, "SM", enType, s_ulIntervalTimer/1000);

	return ulIntervalTime;
}

/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
BOOL EngSM_Main(void)
{
	TEngSystemManager *pstSystemManager = &s_stSystemManager;
	TMsgQCB *pstSystemMgrMsgQCB = &pstSystemManager->stMsgQCB;	/* Message Handler for Engine System Manager */
	TMsgQ stRcvMsgQ = {0};
	TEngState enNextState = ENG_ST_UNSPECIFIED;

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
	EngTM_ETM_SaveTimeEvent((U32)EngSM_Main, 0);
#endif

	while(EngLib_TaskToISRReceiveEvent(&stRcvMsgQ))
	{
		DBG_ENGSM(ENG_DBG_STRING"SendMsg:%x,%d,%d", ENG_TICK, "SM", stRcvMsgQ.ulMsgID, stRcvMsgQ.ulLParam, stRcvMsgQ.ulRParam);
		EngSM_SendEvent(stRcvMsgQ.ulMsgID, NULL, stRcvMsgQ.ulLParam, stRcvMsgQ.ulRParam);
	}

	/* Message Handler for Engine System Manager */
	while(EngLib_ReceiveMsgQ(pstSystemMgrMsgQCB, &stRcvMsgQ))
	{
		;//EngSM_DispatchMessage(&stRcvMsgQ);
	}

	/* Execute the state activity of Engine System Manager */
	enNextState = EngLib_StateActivity(&pstSystemManager->stStateMachine, pstSystemManager);
	enNextState = EngLib_StateGuardConditionActivity(&pstSystemManager->stStateMachine, pstSystemManager);

	/* Update the Status DB of Engine System Manager */
	EngSM_SetStatus(ENGSM_STS_PARENT_ENGINE_STATE, enNextState);
	
	EngSM_CountIntervalTime();

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
	EngTM_ETM_SaveTimeEvent((U32)EngSM_Main, 1);
#endif

#if defined(HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE) && !defined(C_HDD_LOG_SAVE_NEW)
	EngLib_IF_ManagerForHDDLog();
#endif
	
	return TRUE;
}

/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
BOOL EngSM_InitStatus(void)
{
	DBG_ENGSM(ENG_DBG_STRING"SM_InitStatus", ENG_TICK, "SM");
	
	return TRUE;
}


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
U32 EngSM_GetStatus(U32 ulStatusID)
{
    U32 ulReturnValue = 0;
    //TENGSM_STATUS_CALLBACK_F pfnStatusInternalFunc = NULL;

    /* Get Status ID & Check Invalid Range */
    if((ulStatusID == ENGSM_STS_PARENT_UNSPECIFIED)
		|| (STATUS_GET_INDEX(ulStatusID) > ARRAY_SIZE(s_apfnStatusFuncTable))
	)
    {
		DBG_ENGSM(ENG_DBG_STRING"Warning!! (Invalid ID Value=%x)", ENG_TICK, "SM",ulStatusID);
        
        return STATUS_INITIAL_VAL;
    }

    /* Change Status ID for internal using */
    ulStatusID = STATUS_GET_INDEX(ulStatusID);

    /* Get Status Value */
    //pfnStatusInternalFunc = (TENGSM_STATUS_CALLBACK_F)s_apfnStatusFuncTable[ulStatusID];
    //ulReturnValue = (*pfnStatusInternalFunc)(STATUS_GET, ulStatusID, 0);

    return ulReturnValue;
}

/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
BOOL EngSM_SetStatus(U32 ulStatusID, U32 ulNewValue)
{
    U32 ulChangedStatusID = 0;
    U32 ulStatusAttibute = 0;
    U32 ulOldValue = 0;
    TENGSM_STATUS_CALLBACK_F pfnStatusInternalFunc = NULL;

	if(ulStatusID == ENGSM_STS_PARENT_UNSPECIFIED)
	{
		DBG_ENGSM(ENG_DBG_STRING"Warning!! (Invalid ID Value=%x)", ENG_TICK, "SM",ulStatusID);
		return FALSE;
	}

    /* Get Status ID & Check Invalid Range */
    if(STATUS_GET_INDEX(ulStatusID) > ARRAY_SIZE(s_apfnStatusFuncTable))
    {
		DBG_ENGSM(ENG_DBG_STRING"Warning!! (Invalid ID Value=%x)", ENG_TICK, "SM",ulStatusID);

        return STATUS_INITIAL_VAL;
    }

    /* Change Status ID for internal using */
    ulChangedStatusID = STATUS_GET_INDEX(ulStatusID);

    /*
     * Check whether status value is changed or not
     * If not changed, just return with debug message
     * At this time, return value is TRUE
     */
    pfnStatusInternalFunc = (TENGSM_STATUS_CALLBACK_F)s_apfnStatusFuncTable[ulChangedStatusID];
    ulOldValue = (*pfnStatusInternalFunc)(STATUS_GET, ulChangedStatusID, 0);

    /* Get Status Attribute for internal using */
    ulStatusAttibute = STATUS_GET_ATTRIBUTE(ulStatusID);

    if(ulStatusAttibute == STATUS_ATTR_VALUE)
    {
	    if(ulOldValue == ulNewValue)
	    {
//	        DBG_ENGSM("\r\n[EngSM] Warning!! Setting Value is identical!! (value=%x)", ulOldValue);
	        return TRUE;
	    }
    }
	else if(ulStatusAttibute == STATUS_ATTR_INFO)
	{
	    if(ulOldValue & ulNewValue)
	    {
//	        DBG_ENGSM("\r\n[EngSM] Warning!! Setting Value is identical!! (value=%x)", ulOldValue);
	        return TRUE;
	    }
	}

    /* Call specific function */
    if((*pfnStatusInternalFunc)(STATUS_SET, ulChangedStatusID, ulNewValue))
	{
	    /* If callback is registered on specific status id, then it would be called */
	    //EngSM_FollowDeviceStatus(ulStatusID, ulOldValue, ulNewValue);

		// if((ulStatusID == ENGSM_STS_PARENT_ENGINE_STATE) 
		// 	&& ((ulNewValue == ENG_ST_WARMUP) || (ulNewValue == ENG_ST_ERROR))
		// )
		{
			EngSM_HndIF_FollowDeviceStatus(ENG_HND_MH, ulStatusID, ulOldValue, ulNewValue);
			//EngSM_HndIF_FollowDeviceStatus(ENG_HND_PH, ulStatusID, ulOldValue, ulNewValue);
			//EngSM_HndIF_FollowDeviceStatus(ENG_HND_IH, ulStatusID, ulOldValue, ulNewValue);	
		}
		// else
		// {
		// 	EngVM_Add(ENGVM_ARG_NUM4|ENGVM_ARG_1MS|ENGVM_ARG_INFINITE, 1*T1MS, 0, EngSM_HndIF_FollowDeviceStatus, ENG_HND_MH, ulStatusID, ulOldValue, ulNewValue);
		//     EngVM_Add(ENGVM_ARG_NUM4|ENGVM_ARG_2MS|ENGVM_ARG_INFINITE, 3*T2MS, 0, EngSM_HndIF_FollowDeviceStatus, ENG_HND_PH, ulStatusID, ulOldValue, ulNewValue);
		//     EngVM_Add(ENGVM_ARG_NUM4|ENGVM_ARG_2MS|ENGVM_ARG_INFINITE, 5*T2MS, 0, EngSM_HndIF_FollowDeviceStatus, ENG_HND_IH, ulStatusID, ulOldValue, ulNewValue);
		// }
	}

    return TRUE;
}


/**
* @brief
*
* @param[in]		None
* @range
* @retval			None
* @global
* @remarks
*/
U32 EngSM_EngineState(U32 ulSetGet, U32 ulDeviceStatusID, U32 ulValue)
{
    U32 ulReturnValue = FALSE;

    switch(ulSetGet)
    {
        case STATUS_SET:
            if(STATUS_GET_INDEX(ulValue) <= STATUS_GET_INDEX(ENGSM_STS_CHILD_ENGINE_POWERON))
            {
				//s_ulEngDeviceStatus = ulValue;
				ulReturnValue = TRUE;
            }
            else
            {
//				DBG_ENGSM("\r\n[EngSM_Status] Warning!! Invalid value (RW:%d, ID:%x, Value:%x)", ulSetGet, ulDeviceStatusID, ulValue);
            }
            break;

        case STATUS_GET:
			//ulReturnValue = s_ulEngDeviceStatus;
			ulReturnValue = TRUE;
            break;

        default:
            break;
	}

    return ulReturnValue;
}
