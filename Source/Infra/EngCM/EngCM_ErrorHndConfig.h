/**
 * @file        EngCM_ErrorConfig.h
 * @brief       This is type definition file for common
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
 * @dept		Embedded Firmware Team
 * @date		20/02/2024(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGCM_ERRORCONFIG_H__
#define __ENGCM_ERRORCONFIG_H__


#define ERROR_CODE_GOOD                     0x5000

/* JAM */
#define ERROR_RAINS_JAM                     0x5121  // BOX A 진입 JAM
#define ERROR_RBINS_JAM                     0x5122  // BOX B 진입 JAM
#define ERROR_RCINS_JAM                     0x5124  // BOX C 진입 JAM
#define ERROR_RA_RBINS_JAM                  0x5123  // BOX A, B 진입 JAM
#define ERROR_RA_RCINS_JAM                  0x5125  // BOX A, C 진입 JAM
#define ERROR_RB_RCINS_JAM                  0x5126  // BOX B, C 진입 JAM
#define ERROR_RA_RB_RCINS_JAM               0x5127  // BOX A, B, C 진입 JAM

/* CHECK RJB : 지폐가 없을 때 Check RJB 명령 실행 시 Error Code */
#define ERROR_CHECK_RJB_RDANS               0x5130  
#define ERROR_CHECK_RJB_RAFPI               0x5131
#define ERROR_CHECK_RJB_RAINS               0x5132
#define ERROR_CHECK_RJB_RBINS               0x5133
#define ERROR_CHECK_RJB_RCINS               0x5134
#define ERROR_CHECK_RJB_RAFNS               0x5135
#define ERROR_CHECK_RJB_RBFNS               0x5136
#define ERROR_CHECK_RJB_RCFNS               0x5137
#define ERROR_CHECK_RJB_RAENS               0x5138
#define ERROR_CHECK_RJB_RBENS               0x5139
#define ERROR_CHECK_RJB_RCENS               0x5140
#define ERROR_CHECK_RJB_RFDRI               0x5141

/* BOX FULL */
#define ERROR_EEPROM_RESTORE_FAIL           0x5212
#define ERROR_RJB_A_ABNORMAL_STACK          0x5230  // BOX A Abnormal Stack - X
//#define ERROR_RJB_A_FULL                    0x5231  // BOX A 지폐 FULL
//#define ERROR_RJB_B_FULL                    0x5232  // BOX B 지폐 FULL
//#define ERROR_RJB_C_FULL                    0x5234  // BOX C 지폐 FULL
#define ERROR_RA_B_FULL                     0x5233  // BOX A, B 지폐 FULL
#define ERROR_RA_C_FULL                     0x5235  // BOX A, C 지폐 FULL
#define ERROR_RB_C_FULL                     0x5236  // BOX B, C 지폐 FULL
#define ERROR_RA_B_C_FULL                   0x5237  // BOX A, B, C 지폐 FULL
#define ERROR_RJB_A_NEAR_FULL               0x5239  // BOX A, 지폐 NEAR FULL

#define	ERROR_STATUS_O                      'O' // 0x4F
#define	ERROR_STATUS_F                      'F' // 0x46
#define	ERROR_STATUS_T                      'T' // 0x54

/* INITIALIZE */
#define ERROR_RJB_NOT_INITIALIZE            0x5240  // RJB 초기화 안됨
#define ERROR_RJB_RAFPI                     0x5241  // PLATE 하단 감지 인식 못함, 탈조
#define ERROR_RJB_WHEEL_INT                 0x5242  // WHEEL 이 동작 안함, 인터럽트 센서 동작 안함
#define ERROR_RJB_RDANS                     0x5243  // PLATE READY 감지 인식 못함, 탈조 //231215 장애 설명 일부 수정 
#define ERROR_RJB_RAFNS						0x524A	// PLATE FULL 감지 못함, 탈조 //231215 LRJB 동작에 따라 장애 추가
#define ERROR_RJB_A_PLATE_ABNORMAL          0x5244  // PLATE 이상 동작

/* COMMAND */
#define ERROR_COMMAND_UNDEFINED             0x50A0//0x5585  // 정의되지 않은 COMMAND 수신
#define ERROR_SUBCOMMAND_UNDEFINED          0x50A1//0x5586  // 정의되지 않은 SUB COMMAND 수신
#define ERROR_BCC                           0x50D0//0x5587   //Serial Data BCC 이상

/* MOTOR */
#define ERROR_MOTOR_OUT_PHASE				0x60B4//0x6556
#define ERROR_MOTOR_SPEED					0x60B5//0x6557	// Pickup Motor step out or speed err
#define ERROR_MOTOR_SPEED_LOW				0x6332

/* SENSOR */
#define ERROR_PATH_SEN_DARK					0x6111
#define ERROR_PATH_JAM_SNS0					0x6113	// SNS0(Path 1) Sensor 위치 지폐 Jam - 입금 Command 중
#define ERROR_PATH_JAM_SNS_RAPNS			0x6114	// SNS0(Path 1) Sensor 위치 지폐 Jam - 입금 Command 중
#define ERROR_PATH_JAM_SNS_RBPNS			0x6115	// SNS0(Path 1) Sensor 위치 지폐 Jam - 입금 Command 중
#define ERROR_TIMEOUT_ACCOUNT_START			0x60B3//0x64A3	// 내부 동작 Time Out - 입금 Command 중
#define ERROR_INITIAL_SENSOR_LEVEL			0x6241	//에러코드파일 없음.
#define ERROR_INITIAL_SENSOR_LEVEL_RANPS	0x6234	//
#define ERROR_INITIAL_SENSOR_LEVEL_RBNPS	0x6235	//

/* DIVERTER */
#define ERROR_DIVERTER_FANGD_HW_FAILURE_CUT 0x60C1//0x6560
#define ERROR_DIVERTER_FBNGD_HW_FAILURE_CUT 0x60C2//0x6561
#define ERROR_DIVERTER_FANGD_HW_FAILURE_SHORT 0x60C3//0x6562
#define ERROR_DIVERTER_FBNGD_HW_FAILURE_SHORT 0x60C4//0x6563



#endif /* __ENGCM_ERRORCONFIG_H__ */