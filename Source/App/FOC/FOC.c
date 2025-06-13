#include <math.h>
#define M_PI 3.14159265358979323846
#define ENC_CPR 16384 // 2^14

#define INT_MAX_D 10
#define INT_MAX_Q 1
#define W_INT_MAX 30
#define POS_INT_MAX 10

// 전역 변수 (또는 RTOS 큐/Notification으로 전달)
float i_d_ref = 0.0f;    // d축 전류 목표값 (보통 0)
float i_q_ref = 0.0f;    // q축 전류 목표값 (토크 요구사항에 따라 갱신)
float theta_e = 0.0f;    // 현재 전기각 (엔코더로부터 계산)
float v_d_out, v_q_out;  // PI 제어 출력 (d,q축 전압 명령)
float v_alpha, v_beta;   // 역변환 후 α, β축 전압
uint16_t adc_val_phaseA, adc_val_phaseB;  // ADC DMA로부터 얻은 샘플 값

void SVPWM_CalcDuty(float v_alpha, float v_beta, float Vbus, float *Ta, float *Tb, float *Tc);

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
void SVPWM_CalcDuty(float v_alpha, float v_beta, float Vbus, float *Ta, float *Tb, float *Tc)
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
void CurrentControlTask(void *argument) 
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
void SpeedControlTask(void *argument) 
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
void PositionControlTask(void *argument) 
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

