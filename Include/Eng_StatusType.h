/**
 * @file        Eng_StatusType.h
 * @brief       This is the Device Status ID Header file.
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
 * @date		25/02/2009(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENG_STATUSTYPE_H__
#define __ENG_STATUSTYPE_H__

#define STATUS_SET					1
#define STATUS_RESET				2
#define STATUS_GET					3

#define STATUS_INITIAL_VAL			0x80000000					/* Device ID Status Init Value */
#define STATUS_GET_INDEX(id)		(id & 0x0000FFFF)			/* To get Status Index */
#define STATUS_GET_CLASSIFY(id)		((id & 0xFF000000) >> 24)	/* To get Status Classfy */
#define STATUS_GET_ATTRIBUTE(id)	((id & 0x00FF0000) >> 16)	/* To get Status Attribute */

#define STATUS_ATTR_INFO			0x00						/* Information */
#define STATUS_ATTR_VALUE			0x01						/* Value */
#define STATUS_ATTR_WARNING			0x02						/* Warning Status */
#define STATUS_ATTR_ERROR			0x03						/* Error Status */
#define STATUS_ATTR_FAULT			0x04						/* Unrecovable Error Status */

#define STATUS_NOMEANING_PRIORITY	0xFF						/* Priority is no meaning */


/**
 * Device Status ID Definition	[xx,xx,xxxx : Child,Attribute,Index]
 */
#define ENGSM_STS_PARENT_UNSPECIFIED							0x00000000	/* Unspecified */

#define ENGSM_STS_PARENT_ENGINE_STATE							0x01010000	/* Engine Device State */
#define ENGSM_STS_PARENT_MACHINE_DOOR_STATUS					0x02000001	/* Printer Machine Door Status */
#define ENGSM_STS_PARENT_PAPER_ERROR_STATUS						0x03000002	/* Engine Paper Error Status */
#define ENGSM_STS_PARENT_MOTOR_STATUS							0x04000003	/* Engine Motor Status */
#define ENGSM_STS_PARENT_FAN_STATUS								0x05000004	/* Engine Fan Status */
#define ENGSM_STS_PARENT_TRAY_1_STATUS							0x06000005	/* Tray1 Status */
#define ENGSM_STS_PARENT_TRAY_1_PAPER_SIZE						0x07010006	/* Paper size information in Tray1 */
#define ENGSM_STS_PARENT_TRAY_1_PAPER_TYPE						0x08010007	/* Paper Type information in Tray1 */
#define ENGSM_STS_PARENT_TRAY_1_FEEDER_METHOD					0x09010008	/* Feeder Method information in Tray1 */
#define ENGSM_STS_PARENT_TRAY_2_STATUS							0x06000009	/* Tray2 Status */
#define ENGSM_STS_PARENT_TRAY_2_PAPER_SIZE						0x0701000A	/* Paper size information in Tray2 */
#define ENGSM_STS_PARENT_TRAY_2_PAPER_TYPE						0x0801000B	/* Paper Type information in Tray2 */
#define ENGSM_STS_PARENT_TRAY_2_FEEDER_METHOD					0x0901000C	/* Feeder Method information in Tray2 */
#define ENGSM_STS_PARENT_TRAY_3_STATUS							0x0600000D	/* Tray3 Status */
#define ENGSM_STS_PARENT_TRAY_3_PAPER_SIZE						0x0701000E	/* Paper size information in Tray3 */
#define ENGSM_STS_PARENT_TRAY_3_PAPER_TYPE						0x0801000F	/* Paper Type information in Tray3 */
#define ENGSM_STS_PARENT_TRAY_3_FEEDER_METHOD					0x09010010	/* Feeder Method information in Tray3 */
#define ENGSM_STS_PARENT_TRAY_4_STATUS							0x06000011	/* Tray4 Status */
#define ENGSM_STS_PARENT_TRAY_4_PAPER_SIZE						0x07010012	/* Paper size information in Tray4 */
#define ENGSM_STS_PARENT_TRAY_4_PAPER_TYPE						0x08010013	/* Paper Type information in Tray4 */
#define ENGSM_STS_PARENT_TRAY_4_FEEDER_METHOD					0x09010014	/* Feeder Method information in Tray4 */
#define ENGSM_STS_PARENT_TRAY_5_STATUS							0x06000015	/* Tray4 Status */
#define ENGSM_STS_PARENT_TRAY_5_PAPER_SIZE						0x07010016	/* Paper size information in Tray4 */
#define ENGSM_STS_PARENT_TRAY_5_PAPER_TYPE						0x08010017	/* Paper Type information in Tray4 */
#define ENGSM_STS_PARENT_TRAY_5_FEEDER_METHOD					0x09010018	/* Feeder Method information in Tray4 */
#define ENGSM_STS_PARENT_TRAY_HCF_STATUS						0x06000019	/* HCF Status */
#define ENGSM_STS_PARENT_TRAY_HCF_PAPER_SIZE					0x0701001A	/* Paper size information in HCF */
#define ENGSM_STS_PARENT_TRAY_HCF_PAPER_TYPE					0x0801001B	/* Paper Type information in HCF */
#define ENGSM_STS_PARENT_TRAY_HCF_FEEDER_METHOD					0x0901001C	/* Feeder Method information in HCF */
#define ENGSM_STS_PARENT_TRAY_MP_STATUS							0x0600001D	/* MP Tray Status */
#define ENGSM_STS_PARENT_TRAY_MP_PAPER_SIZE						0x0701001E	/* Paper size information in MP Tray */
#define ENGSM_STS_PARENT_TRAY_MP_PAPER_TYPE						0x0801001F	/* Paper Type information in MP Tray */
#define ENGSM_STS_PARENT_TRAY_MP_FEEDER_METHOD					0x09010020	/* Feeder Method information in MP Tray */
#define ENGSM_STS_PARENT_TRAY_MANUAL_STATUS						0x06000021	/* Manual Feeder Status */
#define ENGSM_STS_PARENT_TRAY_MANUAL_PAPER_SIZE					0x07010022	/* Paper size information in Manual Feeder */
#define ENGSM_STS_PARENT_TRAY_MANUAL_PAPER_TYPE					0x08010023	/* Paper Type information in Manual Feeder */
#define ENGSM_STS_PARENT_TRAY_MANUAL_FEEDER_METHOD				0x09010024	/* Feeder Method information in Manual Feeder */
#define ENGSM_STS_PARENT_MISMATCHED_REASON_STATUS				0x0A000025	/* Paper Mismatched reason */
#define ENGSM_STS_PARENT_MISMATCHED_TRAY_NUMBER					0x0B010026	/* Paper Mismatched Tray Number */
#define ENGSM_STS_PARENT_MISMATCHED_PAPER_SIZE					0x07010027	/* Mismatched Paper size */
#define ENGSM_STS_PARENT_MISMATCHED_PAPER_TYPE					0x08010028	/* Mismatched Paper type */
#define ENGSM_STS_PARENT_MISMATCHED_REQ_PAPER_SIZE				0x07010029	/* Requested paper size information */
#define ENGSM_STS_PARENT_MISMATCHED_REQ_PAPER_TYPE				0x0801002A	/* Requested paper type information */
#define ENGSM_STS_PARENT_DUPLEX_UNIT_STATUS						0x0C00002B	/* Duplex Unit Status */
#define ENGSM_STS_PARENT_C_TONER_STATUS							0x0D01002C	/* Cyan Toner Status */
#define ENGSM_STS_PARENT_M_TONER_STATUS							0x0D01002D	/* Magenta Toner Status */
#define ENGSM_STS_PARENT_Y_TONER_STATUS							0x0D01002E	/* Yellow Toner Status */
#define ENGSM_STS_PARENT_K_TONER_STATUS							0x0D01002F	/* Black Toner Status  */
#define ENGSM_STS_PARENT_C_DRUM_STATUS							0x0E010030	/* Cyan Drum Status */
#define ENGSM_STS_PARENT_M_DRUM_STATUS							0x0E010031	/* Magenta Drum Status */
#define ENGSM_STS_PARENT_Y_DRUM_STATUS							0x0E010032	/* Yellow Drum Status */
#define ENGSM_STS_PARENT_K_DRUM_STATUS							0x0E010033	/* Black Drum Status */
#define ENGSM_STS_PARENT_TRANSFER_BELT_STATUS					0x0F000034	/* Transfer Belt Status */
#define ENGSM_STS_PARENT_ACR_STATUS								0x10010035	/* ACR Status */
#define ENGSM_STS_PARENT_CTD_STATUS								0x11010036	/* CTD Status */
#define ENGSM_STS_PARENT_WASTE_TANK_STATUS						0x12000037	/* Waste Tank Status */
#define ENGSM_STS_PARENT_FUSER_1_STATUS							0x13000038	/* Fuser Status */
#define ENGSM_STS_PARENT_FUSER_2_STATUS							0x13000039	/* Fuser Status */
#define ENGSM_STS_PARENT_TEMPERATURE_STATUS						0x1400003A	/* Temperature Status */
#define ENGSM_STS_PARENT_ENVIRONMENT_STATUS						0x1500003B	/* Environment Status */
#define ENGSM_STS_PARENT_LSU_STATUS								0x1600003C	/* LSU Status */
#define ENGSM_STS_PARENT_FINISHER_STATUS						0x1700003D	/* Finisher Fault */
#define ENGSM_STS_PARENT_FINISHER_WARNING						0x1800003E	/* Finisher Status */
#define ENGSM_STS_PARENT_FINISHER_FAULT							0x1900003F	/* Finisher Fault */
#define ENGSM_STS_PARENT_MAILBOX_FAULT							0x1A000040	/* Finisher Fault */
#define ENGSM_STS_PARENT_EXPANDER_STATUS						0x1B000041	/* Expander Status */
#define ENGSM_STS_PARENT_DIAG_STATUS							0x1C000042	/* Diagnostic Status */
#define ENGSM_STS_PARENT_SYSTEM_DEVICE_STATUS					0x1D000043	/* System Device Status */
#define ENGSM_STS_PARENT_TRAY_2_VERSION							0x1E010044	/* Feeder Method information in Tray2 */
#define ENGSM_STS_PARENT_TRAY_3_VERSION							0x1E010045	/* Feeder Method information in Tray2 */
#define ENGSM_STS_PARENT_TRAY_4_VERSION							0x1E010046	/* Feeder Method information in Tray2 */
#define ENGSM_STS_PARENT_TRAY_5_VERSION							0x1E010047	/* Feeder Method information in Tray2 */
#define ENGSM_STS_PARENT_HCF_VERSION							0x1E010048	/* Feeder Method information in Tray2 */
#define ENGSM_STS_PARENT_FINISHER_VERSION						0x1E010049	/* Feeder Method information in Tray2 */
#define ENGSM_STS_PARENT_EXPANDER_VERSION						0x1E01004A	/* Feeder Method information in Tray2 */
#define ENGSM_STS_PARENT_ABC_STATUS								0x1F00004B	/* AllInOne BLDC Controller Device Status */
#define ENGSM_STS_PARENT_TRANSFER_STATUS						0x2001004C	/* Transfer Status */


/**
 * Classify		:STATUS_01
 * Device Item  :Engine, ENGSM_STS_PARENT_ENGINE_STATE
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_ENGINE_WARMUP							0x00000000	/* Printer warming-up */
#define ENGSM_STS_CHILD_ENGINE_STANDBY							0x00000001	/* Printer stand-by */
#define ENGSM_STS_CHILD_ENGINE_PRINTING							0x00000002	/* Printer printing */
#define ENGSM_STS_CHILD_ENGINE_SLEEP							0x00000003	/* Printer sleeping */
#if 0
#define ENGSM_STS_CHILD_ENGINE_SELF_TESTING						0x00000004	/* Printer self testing */
#define ENGSM_STS_CHILD_ENGINE_CLEANING							0x00000005	/* Printer cleaning */
#define ENGSM_STS_CHILD_ENGINE_ERROR							0x00000006	/* Printer error status */
#define ENGSM_STS_CHILD_ENGINE_RECOVERY							0x00000007	/* Printer Recoverying */
#define ENGSM_STS_CHILD_ENGINE_FUSER_CLEAN						0x00000008	/* Printer Fuser Cleaning */
#define ENGSM_STS_CHILD_ENGINE_LOW_POWER						0x00000009	/* Printer Low Power state */
#define ENGSM_STS_CHILD_ENGINE_WAITING							0x0000000A	/* Printer ACR State */
#define ENGSM_STS_CHILD_ENGINE_EDC						 		0x0000000B	/* Printer EDC State */
#define ENGSM_STS_CHILD_ENGINE_TEST								0x0000000C	/* Printer Test State */
#else
#define ENGSM_STS_CHILD_ENGINE_ERROR							0x00000004	/* Printer error status */
#define ENGSM_STS_CHILD_ENGINE_RECOVERY							0x00000005	/* Printer Recoverying */
#define ENGSM_STS_CHILD_ENGINE_WAITING							0x00000006	/* Printer ACR State */
#define ENGSM_STS_CHILD_ENGINE_EDC								0x00000007	/* Printer EDC State */
#define ENGSM_STS_CHILD_ENGINE_TEST								0x00000008	/* Printer Test State */
#define ENGSM_STS_CHILD_ENGINE_POWERON 							0x00000009	/* Printer PowerOn State */
#endif

/**
 * Classify		:STATUS_2
 * Device Item  :MachineDoorStatus, ENGSM_STS_PARENT_MACHINE_DOOR_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_FRONT_DOOR_OPENED						0x00000001	/* [Error] Front door is opened in printer body */
#define ENGSM_STS_CHILD_RIGHT_DOOR_OPENED						0x00000002	/* [Error] Right door is opened in printer body */
#define ENGSM_STS_CHILD_LEFT_DOOR_OPENED						0x00000004	/* [Error] Left door is opened in printer body */
#define ENGSM_STS_CHILD_TOP_DOOR_OPENED							0x00000008	/* [Error] Top door is opened in printer body */
#define ENGSM_STS_CHILD_REAR_DOOR_OPENED						0x00000010	/* [Error] Rear door is opened in printer body */
#define ENGSM_STS_CHILD_FUSER_DOOR_OPENED						0x00000020	/* [Error] Rear door is opened in printer body */
#define ENGSM_STS_CHILD_DUPLEX_DOOR_OPENED						0x00000040	/* [Error] Duplex door is opened */
#define ENGSM_STS_CHILD_DEVE_DOOR_OPENED						0x00000080	/* [Error] Deve door is opened */

#define ENGSM_STS_CHILD_MACHINE_DOOR_STATUS_ALL					0x0000FFFF

/**
 * Classify		:STATUS_3
 * Device Item  :PaperJamStatus, ENGSM_STS_PARENT_PAPER_ERROR_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_PAPER_EMPTY								0x00000001
//모든 Tray의 용지가 없거나, Feeding Tray에 용지가 없을 경우
#define ENGSM_STS_CHILD_PAPER_JAM_IN_MP_TRAY					0x00000002
//인쇄 동작시에 지정된 MP Tray에서 종이를 Pick-Up 한 후에 일정 시간동안 Feed Sensor에 도달하지 못하였을 경우.
#define ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY1						0x00000004
//인쇄 동작시에 지정된 Tray1에서 용지를 Pick-Up 후에 일정 시간동안 Feed Sensor에 도달하지 못하였을 경우.
#define ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY2						0x00000008
//Tray 2에서 Pickup 후 용지가 Feed Sensor에 도달하지 못한 경우.
//인쇄 동작시에 지정된 Tray2에서 용지를 Pick-Up 후에 일정시간동안 Feed Sensor에 도달하지 못하였을 경우.
//Warmup 시 Tray2의 Feed 센서에 용지가 감지된 경우
#define ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY3						0x00000010
//Tray 3에서 Pickup 후 용지가 Feed Sensor에 도달하지 못한 경우.
//인쇄 동작시에 지정된 Tray3에서 용지를 Pick-Up 후에 일정시간동안 Feed Sensor에 도달하지 못하였을 경우.
//Warmup 시 Tray3의 Feed 센서에 용지가 감지된 경우
#define ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY4						0x00000020
//Tray 4에서 Pickup 후 종이가 Feed Sensor에 도달하지 못한 경우.
//인쇄 동작시에 지정된 Tray4에서 종이를 Pick-Up 후에 일정시간동안 Feed Sensor에 도달하지 못하였을 경우.
//Warmup 시 Tray4의 Feed 센서에 용지가 감지된 경우
#define ENGSM_STS_CHILD_PAPER_JAM_INSIDE_MACHINE				0x00000040
//1. Warmup 시 Registration 또는 Feed Sensor에 종이가 걸려 있는 경우.
//2. 인쇄 동작시 Registration 또는 Feed sensor에 종이가 빠져나갈 시간이 지나도 종이가 계속 검지되는 경우.
//3. 인쇄 동작시 Exit Sensor에 종이가 검지되어야 할 시점에 검지되지 않은 경우.
#define ENGSM_STS_CHILD_PAPER_JAM_IN_EXIT_AREA					0x00000080
//1. Warmup 시 Exit Sensor에 종이가 걸려 있는 경우
#define ENGSM_STS_CHILD_PAPER_JAM_BOTTOM_OF_DUPLEX				0x00000100
//1. Warmup 중에 Duplex sensor에 종이가 있는 것으로 검지되는 경우.
//2. duplex path로 진입한 종이가 feed sensor에 검지되지 않는 경우
#define ENGSM_STS_CHILD_PAPER_JAM_TOP_OF_DUPLEX					0x00000200
//1. Warmup 중에 Duplex sensor에 종이가 있는 것으로 검지되는 경우.
//2. Simplex면을 찍고 역전한 종이가 Duplex Sensor에 도달하지 못한 경우.
#define ENGSM_STS_CHILD_PAPER_JAM_INSIDE_OF_DUPLEX				0x00000400
//1. Warmup 중에 Duplex path에 종이가 있는 것으로 검지 되는 경우.
//2. Duplex path로 들어간 종이가 duplex 내부에서 검지되지 않는 경우
#define ENGSM_STS_CHILD_OUTBIN_FULL								0x00000800
//600ms동안 연속으로 On 되어 있는 경우

#define ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY5						0x00001000
//Tray 5에서 Pickup 후 종이가 Feed Sensor에 도달하지 못한 경우.
//인쇄 동작시에 지정된 Tray5에서 종이를 Pick-Up 후에 일정시간동안 Feed Sensor에 도달하지 못하였을 경우.
//Warmup 시 Tray5의 Feed 센서에 용지가 감지된 경우

#define ENGSM_STS_CHILD_PAPER_JAM_OPTION_TRAY					0x00002000
//1. Warmup 시 Option Tray에 종이가 걸려 있는 경우

#define ENGSM_STS_CHILD_PAPER_EMPTY_OR_JAM_IN_TRAY1				0x00004000
//1. Empty Sensor가 없을 경우 Empty 발생시

#define ENGSM_STS_CHILD_PAPER_PICKUP_JAM						0x00008000

#define ENGSM_STS_CHILD_PAPER_ERROR_STATUS_ALL					0x0000FFFF
#define ENGSM_STS_CHILD_PAPER_JAM_ALL							0x0000F7FE
#define ENGSM_STS_CHILD_PAPER_PICKUP_JAM_ALL					(ENGSM_STS_CHILD_PAPER_JAM_IN_MP_TRAY | ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY1 | ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY2 | ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY3 | ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY4 | ENGSM_STS_CHILD_PAPER_JAM_IN_TRAY5 | ENGSM_STS_CHILD_PAPER_EMPTY_OR_JAM_IN_TRAY1 | ENGSM_STS_CHILD_PAPER_PICKUP_JAM)
#define ENGSM_STS_CHILD_PAPER_JAM_EXCEPT_PICKUP					(ENGSM_STS_CHILD_PAPER_JAM_INSIDE_MACHINE | ENGSM_STS_CHILD_PAPER_JAM_IN_EXIT_AREA | ENGSM_STS_CHILD_PAPER_JAM_BOTTOM_OF_DUPLEX | ENGSM_STS_CHILD_PAPER_JAM_TOP_OF_DUPLEX | ENGSM_STS_CHILD_PAPER_JAM_INSIDE_OF_DUPLEX)


/**
 * Classify		:STATUS_4
 * Device Item  :MotorStatus, ENGSM_STS_PARENT_MOTOR_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_MOTOR_MAIN_LOCKED_ERROR					0x00000001    /* [Fault] Main motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_FUSER_LOCKED_ERROR				0x00000002    /* [Fault] Fuser motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_DEV_LOCKED_ERROR					0x00000004    /* [Fault] Developer motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_OPC_LOCKED_ERROR					0x00000008    /* [Fault] OPC motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_K_OPCDEV_LOCKED_ERROR				0x00000010    /* [Fault] OPC&DEV motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_YMC_OPCDEV_LOCKED_ERROR			0x00000020    /* [Fault] OPC&DEV motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_DUPLEX_LOCKED_ERROR				0x00000040    /* [Fault] Duplex motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_C_TONER_LOCKED_ERROR				0x00000080    /* [Fault] C Toner motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_M_TONER_LOCKED_ERROR				0x00000100    /* [Fault] M Toner motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_Y_TONER_LOCKED_ERROR				0x00000200    /* [Fault] Y Toner motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_K_TONER_LOCKED_ERROR				0x00000400    /* [Fault] K Toner motor's ready signal is not occurred*/
#define ENGSM_STS_CHILD_MOTOR_ITB_LOCKED_ERROR					0x00000800    /* [Fault] ITB motor's ready signal is not occurred*/

#define ENGSM_STS_CHILD_MOTOR_STATUS_ALL						0x0000FFFF


/**
 * Classify		:STATUS_5
 * Device Item  :FanStatus, ENGSM_STS_PARENT_FAN_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_FAN_FUSER_LOCKED_ERROR					0x00000001    /* [Fault] Fuser fan is locked*/
#define ENGSM_STS_CHILD_FAN_FUSER_2_LOCKED_ERROR				0x00000002    /* [Fault] Fuser fan is locked*/
#define ENGSM_STS_CHILD_FAN_LSU_LOCKED_ERROR					0x00000004    /* [Fault] LSU fan is locked*/
#define ENGSM_STS_CHILD_FAN_DUPLEX_LOCKED_ERROR					0x00000008    /* [Fault] Duplex fan is locked*/
#define ENGSM_STS_CHILD_FAN_DUPLEX_2_LOCKED_ERROR				0x00000010    /* [Fault] Duplex fan 2 is locked*/
#define ENGSM_STS_CHILD_FAN_HVPS_LOCKED_ERROR					0x00000020    /* [Fault] HVPS fan is locked*/
#define ENGSM_STS_CHILD_FAN_SMPS_LOCKED_ERROR					0x00000040    /* [Fault] SMPS fan is locked*/
#define ENGSM_STS_CHILD_FAN_SYSTEM_LOCKED_ERROR					0x00000080    /* [Fault] System fan is locked*/
#define ENGSM_STS_CHILD_FAN_EXIT_LOCKED_ERROR					0x00000100    /* [Fault] Exit fan is locked*/
#define ENGSM_STS_CHILD_FAN_DEVELOPER_LOCKED_ERROR				0x00000200    /* [Fault] Developer fan is locked*/


#define ENGSM_STS_CHILD_FAN_STATUS_ALL							0x0000FFFF


/**
 * Classify		:STATUS_6
 * Device Item  :TrayStatus, ENGSM_STS_PARENT_TRAY_1_STATUS, ENGSM_STS_PARENT_TRAY_2_STATUS, ENGSM_STS_PARENT_TRAY_3_STATUS, ENGSM_STS_PARENT_TRAY_4_STATUS, ENGSM_STS_PARENT_TRAY_HCF_STATUS, ENGSM_STS_PARENT_TRAY_MP_STATUS, ENGSM_STS_PARENT_TRAY_MANUAL_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_TRAY_PAPER_EMPTY						0x00000001    /* Paper empty in tray*/
#define ENGSM_STS_CHILD_TRAY_PAPER_LOW_0						0x00000002    /* Paper Low in tray*/
#define ENGSM_STS_CHILD_TRAY_PAPER_LOW_1						0x00000004    /* Paper Low in tray*/
#define ENGSM_STS_CHILD_TRAY_PAPER_LOW_2						0x00000008    /* Paper Low in tray*/
#define ENGSM_STS_CHILD_TRAY_PAPER_LOW_3						0x00000010    /* Paper Low in tray*/
#define ENGSM_STS_CHILD_TRAY_NOT_INSTALLED						0x00000020    /* Tray is not installed*/
#define ENGSM_STS_CHILD_TRAY_OUT								0x00000040    /* Tray is opened*/
#define ENGSM_STS_CHILD_TRAY_DOOR_OPEN							0x00000080    /* Tray door is opened*/
#define ENGSM_STS_CHILD_TRAY_ELEVATING							0x00000100    /* Tray elevating*/
#define ENGSM_STS_CHILD_TRAY_ELEVATING_ERROR					0x00000200    /* Tray elevating*/
#define ENGSM_STS_CHILD_TRAY_COMM_ERROR							0x00000400    /* Tray comm error*/
#define ENGSM_STS_CHILD_TRAY_BOOTING							0x00000800    /* Tray booting */
#define ENGSM_STS_CHILD_TRAY_FEEDER_SENSOR_ERROR				0x00001000    /* Tray feeder sensor error */
#define ENGSM_STS_CHILD_TRAY_DOWNLOAD_READY						0x00002000    /* Tray download ready */
#define ENGSM_STS_CHILD_TRAY_CHECK_READY						0x00004000    /* Tray check ready */
#define ENGSM_STS_CHILD_TRAY_CONNECT_RESPONSE					0x00008000    /* Tray connecting status */
#define ENGSM_STS_CHILD_TRAY_IF_PAPER_EMPTY						0x00010000    /* To receive paper empty info from tray interface */
#define ENGSM_STS_CHILD_TRAY_IF_OUT								0x00020000    /* To receive tray out info from tray interface */
#define ENGSM_STS_CHILD_TRAY_CONNECT_RESPONSE_SEN				0x00040000    /* Tray connecting status */
#define ENGSM_STS_CHILD_TRAY_SIZE_NOT_CHECKED					0x00080000    /* Tray Size Chechking status */
#define ENGSM_STS_CHILD_TRAY_PICKUP_ROLLER_EMPTY				0x00100000    /* Tray Pickup Roller Empty */
#define ENGSM_STS_CHILD_TRAY_RETARD_ROLLER_EMPTY				0x00200000    /* Tray Retard Roller Empty */

#define ENGSM_STS_CHILD_TRAY_PAPER_LOW							(ENGSM_STS_CHILD_TRAY_PAPER_LOW_0 | ENGSM_STS_CHILD_TRAY_PAPER_LOW_1 | ENGSM_STS_CHILD_TRAY_PAPER_LOW_2 | ENGSM_STS_CHILD_TRAY_PAPER_LOW_3)    /* Paper Low in tray*/


/**
 * Classify		:STATUS_7
 * Device Item  :TrayPaperSize, ENGSM_STS_PARENT_TRAY_1_PAPER_SIZE
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_TRAY_LETTER_SIZE			 0x00000000    /* Tray Letter Size*/
#define ENGSM_STS_CHILD_TRAY_LEGAL_SIZE              0x00000001    /* Tray Legal Size*/
#define ENGSM_STS_CHILD_TRAY_A4_SIZE                 0x00000002    /* Tray A4 Size*/
#define ENGSM_STS_CHILD_TRAY_EXE_SIZE                0x00000003    /* Tray EXE Size*/
#define ENGSM_STS_CHILD_TRAY_B5_SIZE                 0x00000004    /* Tray B5 Size*/
#define ENGSM_STS_CHILD_TRAY_ISO_B5_SIZE             0x00000005    /* Tray ISO B5 Size*/
#define ENGSM_STS_CHILD_TRAY_COM10_SIZE              0x00000006    /* Tray COM10 Size*/
#define ENGSM_STS_CHILD_TRAY_MONARCH_SIZE            0x00000007    /* Tray MONARCH Size*/
#define ENGSM_STS_CHILD_TRAY_DL_SIZE                 0x00000008    /* Tray DL Size*/
#define ENGSM_STS_CHILD_TRAY_C5_SIZE                 0x00000009    /* Tray C5 Size*/
#define ENGSM_STS_CHILD_TRAY_POST_A6_SIZE            0x0000000A    /* Tray POST A6 Size*/
#define ENGSM_STS_CHILD_TRAY_C6_SIZE                 0x0000000B    /* Tray C6 Size*/
#define ENGSM_STS_CHILD_TRAY_FOLIO_SIZE              0x0000000C    /* Tray FOLIO Size*/
#define ENGSM_STS_CHILD_TRAY_A5_SIZE                 0x0000000D    /* Tray A5 Size*/
#define ENGSM_STS_CHILD_TRAY_STS_SIZE                0x0000000E    /* Tray STS Size*/
#define ENGSM_STS_CHILD_TRAY_A6_SIZE                 0x0000000F    /* Tray A6 Size*/
#define ENGSM_STS_CHILD_TRAY_LEDGER_SIZE             0x00000010    /* Tray LEDGER Size*/
#define ENGSM_STS_CHILD_TRAY_A3_SIZE                 0x00000011    /* Tray A3 Size*/
#define ENGSM_STS_CHILD_TRAY_JIG_B4_SIZE             0x00000012    /* Tray JIG B4 Size*/
#define ENGSM_STS_CHILD_TRAY_JPOST_SIZE              0x00000013    /* Tray JPOST Size*/
#define ENGSM_STS_CHILD_TRAY_JPOST_D_SIZE            0x00000014    /* Tray JPOST D Size*/
#define ENGSM_STS_CHILD_TRAY_CUSTOM_SIZE             0x00000015    /* Tray CUSTOM Size*/
#define ENGSM_STS_CHILD_TRAY_LETTER_R_SIZE           0x00000016    /* Tray Letter R Size*/
#define ENGSM_STS_CHILD_TRAY_A4_R_SIZE               0x00000017    /* Tray A4 R Size*/
#define ENGSM_STS_CHILD_TRAY_JIG_B5_R_SIZE           0x00000018    /* Tray JIG B5 R Size*/
#define ENGSM_STS_CHILD_TRAY_A5_R_SIZE               0x00000019    /* Tray A5 R Size*/
#define ENGSM_STS_CHILD_TRAY_EXEC_R_SIZE             0x0000001A    /* Tray EXEC R Size*/
#define ENGSM_STS_CHILD_TRAY_STATE_R_SIZE            0x0000001B    /* Tray STATE R Size*/
#define ENGSM_STS_CHILD_TRAY_A3_OVER_SIZE            0x0000001C    /* Tray A3 Over Size*/
#define ENGSM_STS_CHILD_TRAY_B5_ENV_SIZE             0x0000001D    /* Tray B5 Env Size*/
#define ENGSM_STS_CHILD_TRAY_OFICIO_SIZE             0x0000001E    /* Tray OFicio Size*/
#define ENGSM_STS_CHILD_TRAY_634_SIZE                0x0000001F    /* Tray 634 Size*/
#define ENGSM_STS_CHILD_TRAY_NO9_SIZE                0x00000020    /* Tray NO9 Size*/
#define ENGSM_STS_CHILD_TRAY_USPOST_SIZE             0x00000021    /* Tray US Post Size*/
#define ENGSM_STS_CHILD_TRAY_INDEX_SIZE              0x00000022    /* Tray Index Size*/
#define ENGSM_STS_CHILD_TRAY_B6_SIZE                 0x00000023    /* Tray B6 Size*/
#define ENGSM_STS_CHILD_TRAY_HAGAKI_SIZE             0x00000024    /* Tray HAGAKI Size*/
#define ENGSM_STS_CHILD_TRAY_ODD_SIZE                0x00000025    /* Tray ODD Size*/
#define ENGSM_STS_CHILD_TRAY_A6_R_SIZE               0x00000026    /* Tray A6 R Size*/
#define ENGSM_STS_CHILD_TRAY_POSTA6_R_SIZE           0x00000027    /* Tray Post A6 R Size*/
#define ENGSM_STS_CHILD_TRAY_JPOSTR_SIZE             0x00000028    /* Tray JPoster Size*/
#define ENGSM_STS_CHILD_TRAY_4X6_INCH_SIZE           0x00000029    /* Tray 4x6 Inch Size*/
#define ENGSM_STS_CHILD_TRAY_UNSPECIFIED_SIZE        0x0000002A    /* Tray Unspecified Size*/


/**
 * Classify		:STATUS_8
 * Device Item  :TrayPaperType, ENGSM_STS_PARENT_TRAY_1_PAPER_TYPE
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_TRAY_DEFAULT_TYPE            0x00000000    /* Tray default paper type*/
#define ENGSM_STS_CHILD_TRAY_PLAIN_TYPE              0x00000001    /* Tray plain paper type*/
#define ENGSM_STS_CHILD_TRAY_THICK_TYPE              0x00000002    /* Tray Thick paper type*/
#define ENGSM_STS_CHILD_TRAY_THIN_TYPE               0x00000003    /* Tray thin paper type*/
#define ENGSM_STS_CHILD_TRAY_BOND_TYPE               0x00000004    /* Tray Bond paper type*/
#define ENGSM_STS_CHILD_TRAY_COLOR_PAPER_TYPE        0x00000005    /* Tray color paper Type*/
#define ENGSM_STS_CHILD_TRAY_CARD_STOCK_TYPE         0x00000006    /* Tray Card stock type*/
#define ENGSM_STS_CHILD_TRAY_LABEL_TYPE              0x00000007    /* Tray label paper type*/
#define ENGSM_STS_CHILD_TRAY_TRANSPARENCY_TYPE       0x00000008    /* Tray transparency paper type*/
#define ENGSM_STS_CHILD_TRAY_ENVELOPE_TYPE           0x00000009    /* Tray envelope paper type*/
#define ENGSM_STS_CHILD_TRAY_RECYCLED_TYPE           0x0000000A    /* Tray recycled paper type*/
#define ENGSM_STS_CHILD_TRAY_LETTER_HEAD             0x0000000B    /* Tray letter head paper type*/
#define ENGSM_STS_CHILD_TRAY_SPECIAL_TYPE            0x0000000C    /* Tray special paper type*/
#define ENGSM_STS_CHILD_TRAY_PREPRINTED_TYPE         0x0000000D    /* Tray preprinted paper type*/
#define ENGSM_STS_CHILD_TRAY_COTTON_TYPE             0x0000000E    /* Tray cotton paper type*/
#define ENGSM_STS_CHILD_TRAY_HEAVYWEIGHT_TYPE        0x0000000F    /* Tray heavy weight paper type*/
#define ENGSM_STS_CHILD_TRAY_HOLEPUNCHED_TYPE        0x00000010    /* Tray hole punched paper type*/
#define ENGSM_STS_CHILD_TRAY_ARCHIVE_TYPE            0x00000011    /* Tray archive paper type*/
#define ENGSM_STS_CHILD_TRAY_CUSTOM1_TYPE            0x00000012    /* Tray custom1 paper type*/
#define ENGSM_STS_CHILD_TRAY_CUSTOM2_TYPE            0x00000013    /* Tray custom2 paper type*/
#define ENGSM_STS_CHILD_TRAY_CUSTOM3_TYPE            0x00000014    /* Tray custom3 paper type*/
#define ENGSM_STS_CHILD_TRAY_CUSTOM4_TYPE            0x00000015    /* Tray custom4 paper type*/
#define ENGSM_STS_CHILD_TRAY_CUSTOM5_TYPE            0x00000016    /* Tray custom5 paper type*/
#define ENGSM_STS_CHILD_TRAY_CUSTOM6_TYPE            0x00000017    /* Tray custom6 paper type*/
#define ENGSM_STS_CHILD_TRAY_CUSTOM7_TYPE            0x00000018    /* Tray custom7 paper type*/
#define ENGSM_STS_CHILD_TRAY_PHOTO_PAPER_TYPE        0x00000019    /* Tray photo paper type*/
#define ENGSM_STS_CHILD_TRAY_OTHER_TYPE              0x0000001A    /* Tray other paper type*/
#define ENGSM_STS_CHILD_TRAY_PUNCHED_TYPE            0x0000001B    /* Tray punched paper type*/
#define ENGSM_STS_CHILD_TRAY_POSTCARD_TYPE           0x0000001C    /* Tray postcard paper type*/
#define ENGSM_STS_CHILD_TRAY_UNSPECIFIED_TYPE        0x0000001D    /* Tray unspecified paper type*/


/**
 * Classify		:STATUS_9
 * Device Item  :TrayFeederMethod, ENGSM_STS_PARENT_TRAY_1_FEEDER_METHOD
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_TRAY_FEEDER_DISABLE        	0x00000000    /* Tray Feeder Disable*/
#define ENGSM_STS_CHILD_TRAY_FEEDER_SIMPLEX       	0x00000001    /* Tray Feeder Simplex*/
#define ENGSM_STS_CHILD_TRAY_FEEDER_DUPLEX         	0x00000002    /* Tray Feeder Duplex*/


/**
 * Classify		:STATUS_10
 * Device Item  :PaperMismatch, ENGSM_STS_PARENT_MISMATCHED_REASON_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_PAPER_TYPE_MISMATCHED        0x00000001    /* [Warning]Paper type is mismatched*/
#define ENGSM_STS_CHILD_PAPER_SIZE_MISMATCHED        0x00000002    /* [Warning]Paper size is mismatched*/


/**
 * Classify		:STATUS_11
 * Device Item  :PaperMismatchTray, ENGSM_STS_PARENT_MISMATCHED_TRAY_NUMBER
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_PAPER_MISMATCHED_NO_MISMATCHED_TRAY                  0x00000000    /* paper is not mismatched*/
#define ENGSM_STS_CHILD_PAPER_MISMATCHED_TRAY_1                          	 0x00000001    /* Basic Tray Paper Mismatched*/
#define ENGSM_STS_CHILD_PAPER_MISMATCHED_TRAY_2                              0x00000002    /* Tray-1 Paper Mismatched*/
#define ENGSM_STS_CHILD_PAPER_MISMATCHED_TRAY_3                              0x00000003    /* Tray-2 Paper Mismatched*/
#define ENGSM_STS_CHILD_PAPER_MISMATCHED_TRAY_4                              0x00000004    /* Tray-3 Paper Mismatched*/
#define ENGSM_STS_CHILD_PAPER_MISMATCHED_TRAY_MP                             0x00000005    /* MP Tray Paper Mismatched*/
#define ENGSM_STS_CHILD_PAPER_MISMATCHED_MANUAL_FEEDER                       0x00000006    /* Manual Feeder Paper Mismatched*/


/**
 * Classify		:STATUS_12
 * Device Item  :DuplexUnit, ENGSM_STS_PARENT_DUPLEX_UNIT_STATUS
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_DUPLEX_UNIT_STATUS_OK                                0x00000000    /* Duplex unit status is OK*/
#define ENGSM_STS_CHILD_DUPLEX_UNIT_NOT_INSTALLED                            0x00000001    /* Duplex is not installed*/
#define ENGSM_STS_CHILD_DUPLEX_UNIT_INVALID                                  0x00000002    /* Duplex is invalid*/
#define ENGSM_STS_CHILD_DUPLEX_UNIT_COMM_ERROR                               0x00000004    /* Duplex is installed but, communication is failed*/


/**
 * Classify		:STATUS_13
 * Device Item  :TonerStatus, ENGSM_STS_PARENT_C_TONER_STATUS, ENGSM_STS_PARENT_M_TONER_STATUS, ENGSM_STS_PARENT_Y_TONER_STATUS, ENGSM_STS_PARENT_K_TONER_STATUS
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_TONER_STATUS_OK                                      0x00000000    /* Toner status is OK*/
#define ENGSM_STS_CHILD_TONER_LOW                                            0x00000001    /* Toner usage is low*/
#define ENGSM_STS_CHILD_TONER_EMPTY                                          0x00000002    /* Toner usage is empty*/
#define ENGSM_STS_CHILD_TONER_SUPPLY_ERROR                                   0x00000003    /* Toner Bottle is invalid (Gogh같은 모델에서 Toner Bottle을 사용하는 경우)*/
#define ENGSM_STS_CHILD_TONER_PAGE_COUNTER_EXPIRED                           0x00000004    /* Toner page counter is expired*/
#define ENGSM_STS_CHILD_TONER_REFILLED                                       0x00000005    /* Toner is refilled, not toner cartidge(Toner만 Refilled 된 경우)*/
#define ENGSM_STS_CHILD_TONER_CARTRIDGE_NOT_INSTALLED                        0x00000006    /* Not Installed Toner Cartidge*/
#define ENGSM_STS_CHILD_TONER_INVALID                                        0x00000007    /* Invalid Toner*/
#define ENGSM_STS_CHILD_TONER_CARTRIDGE_COMM_ERROR                           0x00000008    /* Fail to communicate with the CRUM in toner cartridge*/
#define ENGSM_STS_CHILD_TONER_INVALID_PASSWORD                               0x00000009    /* Toner password is not matched but, retring*/
#define ENGSM_STS_CHILD_TONER_NOT_GENUINE                                    0x0000000A    /* INVALID_PASSWORD_LOCKED:Even though password checking is tried 8 times but, not matched. Toner is unable to use anymore*/
#define ENGSM_STS_CHILD_TONER_DENSITY_SENSOR_ERROR                           0x0000000B    /* Toner/Cartridge density sensor is not operational*/
#define ENGSM_STS_CHILD_TONER_CARTRIDGE_EXHAUSTED                            0x0000000C    /* The life of achanical toner cartridge is exhausted*/
#define ENGSM_STS_CHILD_TONER_NEED_TO_REPLACE_BY_INFO_CLEAR                  0x0000000D    /* When user selects toner info clear option, even though toner status is empty, MFP shows message "need to replace toner" instead of toner empty.*/
#define ENGSM_STS_CHILD_TONER_TC_CALIBRATION_ERROR							 0x0000000E    /* */
#define ENGSM_STS_CHILD_TONER_SENSOR_SENSING_ERROR							 0x0000000F    /* */
#define ENGSM_STS_CHILD_TONER_EMPTY_CLEAR                             		 0x00000010    /* Can't printing device is hard stop condition */
#define ENGSM_STS_CHILD_TONER_EMPTY_CONTINUE                   				 0x00000011    /* Toner is empty so ask to user about continue */
#define ENGSM_STS_CHILD_TONER_EMPTY_STOP                      				 0x00000012    /* Toner is empty so ask to user about continue */
#define ENGSM_STS_CHILD_TONER_UNUSABLE          							 0x00000013    /* Toner is empty but printing is available */
#define ENGSM_STS_CHILD_TONER_UNUSABLE_STOP       							 0x00000014    /* Toner is empty but printing is available */
#define ENGSM_STS_CHILD_TONER_TERMINATION_ERROR             				 0x00000015    /* The toner cartridge is not valid for this machine(Termination Error) */
#define ENGSM_STS_CHILD_TONER_MISS_ISSUING_ERROR            				 0x00000016    /* The toner cartridge is not valid for this machine(Miss Issuing Error) */
#define ENGSM_STS_CHILD_TONER_SUPPLY_ERROR_1ST         			 			 0x00000017    /* Mono printing is just only available because of non-sec */
#define ENGSM_STS_CHILD_TONER_SUPPLY_ERROR_HIGH                   			 0x00000018    /* Toner is not samsung. so ask to user about continue */
#define ENGSM_STS_CHILD_TONER_SUPPLY_ERROR_LOW      						 0x00000019    /* Toner is not samsung but, printing is available */
#define ENGSM_STS_CHILD_TONER_INVALID_SUPPLYINDEX                            0x0000001A    /* Invalid Toner by supply index */
#define ENGSM_STS_CHILD_TONER_INVALID_COLOR_NOT_MATCHED                      0x0000001B    /* Invalid Toner by color not matched */
#define ENGSM_STS_CHILD_TONER_INVALID_AUTH_PROTOCOL 	                     0x0000001C    /* Invalid Toner by auth protocol */
#define ENGSM_STS_CHILD_TONER_COMPATIBLE_CHIP_FAULT 	                     0x0000001D    /* Invalid Toner by compatible chip fault */
#define ENGSM_STS_CHILD_TONER_TERMINATION_COSRW             				 0x0000001E    /* The toner cartridge is not valid for this machine(Termination COSRW Error) */
#define ENGSM_STS_CHILD_TONER_TERMINATION_DEATHCNT             				 0x0000001F    /* The toner cartridge is not valid for this machine(Termination DEATHCNT Error) */
#define ENGSM_STS_CHILD_TONER_IDPT_MISS_ISSUING_ERROR          				 0x00000020    /* IDPT CRUM_TEST missing */
#define ENGSM_STS_CHILD_TONER_INVALID_MODELID								 0x00000021    /* Invalid Toner by modelID */

#define ENGSM_STS_CHILD_TONER_HARDSTOP_OFF                          		 0x01000000    /* Toner cartridge has been exhaust but the H/S is off by user */
#define ENGSM_STS_CHILD_TONER_HARDSTOP_NO                          			 0x02000000    /* Not hardstop condition */
#define ENGSM_STS_CHILD_TONER_HARDSTOP                             			 0x04000000    /* Can't printing device is hard stop condition */
#define ENGSM_STS_CHILD_TONER_HARDSTOP_EMPTY                      			 0x08000000    /* Toner is empry so ask to user about continue */
#define ENGSM_STS_CHILD_TONER_HARDSTOP_EMPTY_BUT_CONTINUE          			 0x10000000    /* Toner is empry but printing is available */
#define ENGSM_STS_CHILD_TONER_HARDSTOP_EMPTY_SO_STOP             			 0x20000000    /* Can't printing because toner is empty */
#define ENGSM_STS_CHILD_TONER_HARDSTOP_EMPTY_MONO_ONLY            			 0x40000000    /* Mono printing is just only available because of empty */
#define ENGSM_STS_CHILD_TONER_HARDSTOP_UNDEFINED                 			 0x80000000    /* Hardstop Status is not decided */
//#define ENGSM_STS_CHILD_TONER_HARDSTOP_NON_SEC                   			 0x00000000    /* Toner is not samsung. so ask to user about continue */
//#define ENGSM_STS_CHILD_TONER_HARDSTOP_NON_SEC_BUT_CONTINUE      			 0x00000000    /* Toner is not samsung but, printing is available */
//#define ENGSM_STS_CHILD_TONER_HARDSTOP_NON_SEC_SO_STOP            		 0x00000000    /* Can't printing because toner is not samsung  */
//#define ENGSM_STS_CHILD_TONER_HARDSTOP_NON_SEC_MONO_ONLY         			 0x00000000    /* Mono printing is just only available because of non-sec */
//#define ENGSM_STS_CHILD_TONER_HARDSTOP_EOM                       			 0x00000000    /* End Mark Of PrnHardStopStatus*/

/**
 * Classify		:STATUS_14
 * Device Item  :Drum, ENGSM_STS_PARENT_C_DRUM_STATUS, ENGSM_STS_PARENT_M_DRUM_STATUS, ENGSM_STS_PARENT_Y_DRUM_STATUS, ENGSM_STS_PARENT_K_DRUM_STATUS
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_DRUM_STATUS_OK                                       0x00000000    /* Drum status is OK*/
#define ENGSM_STS_CHILD_DRUM_INITIALIZING_ERROR                              0x00000001    /* Drum mixing time is over 180sec when new Drum is installed*/
#define ENGSM_STS_CHILD_DRUM_ALMOST_UNUSABLE                                 0x00000002    /* Drum is near the end of life.*/
#define ENGSM_STS_CHILD_DRUM_UNUSABLE                                        0x00000003    /* Drum life has been reached to max pages*/
#define ENGSM_STS_CHILD_DRUM_NOT_INSTALLED                                   0x00000004    /* Drum usage is not installed*/
#define ENGSM_STS_CHILD_DRUM_INVALID                                         0x00000005    /* Drum usage is installed but, it is not for this machine*/
#define ENGSM_STS_CHILD_DRUM_COMM_ERROR                                      0x00000006    /* Fail to communicate with the CRUM in Drum*/
#define ENGSM_STS_CHILD_DRUM_NOT_GENUINE                                     0x00000007    /* Installed drum is not genuine (Invalid Password Locked) */
#define ENGSM_STS_CHILD_DRUM_SENSING_ERROR                                   0x00000008    /* Charger Sensing Error */
#define ENGSM_STS_CHILD_DRUM_ERASER_ABNORMAL                                 0x00000009    /* Eraser Abnormal */
#define ENGSM_STS_CHILD_DRUM_ALMOST_WORN                                     0x0000000A    /* Installed drum is not genuine (Invalid Password Locked) */
#define ENGSM_STS_CHILD_DRUM_WORN                               			 0x0000000B    /* Charger Sensing Error */
#define ENGSM_STS_CHILD_DRUM_WORN_CLEAR                              		 0x0000000C    /* Eraser Abnormal */
#define ENGSM_STS_CHILD_DRUM_WORN_STOP                               		 0x0000000D    /* Eraser Abnormal */
#define ENGSM_STS_CHILD_DRUM_EMPTY_CLEAR                             		 0x0000000E    /* Can't printing device is hard stop condition */
#define ENGSM_STS_CHILD_DRUM_EMPTY_STOP                      				 0x0000000F    /* DRUM is empry so ask to user about continue */
#define ENGSM_STS_CHILD_DRUM_TERMINATION_ERROR             					 0x00000010    /* Can't printing because DRUM is empty */
#define ENGSM_STS_CHILD_DRUM_MISS_ISSUING_ERROR            					 0x00000011    /* Mono printing is just only available because of empty */

#define ENGSM_STS_CHILD_DRUM_HARDSTOP_OFF                          			 0x01000000    /* Toner cartridge has been exhaust but the H/S is off by user */
#define ENGSM_STS_CHILD_DRUM_HARDSTOP_NO                          			 0x02000000    /* Not hardstop condition */
#define ENGSM_STS_CHILD_DRUM_HARDSTOP                             			 0x04000000    /* Can't printing device is hard stop condition */
#define ENGSM_STS_CHILD_DRUM_HARDSTOP_EMPTY                      			 0x08000000    /* DRUM is empry so ask to user about continue */
#define ENGSM_STS_CHILD_DRUM_HARDSTOP_EMPTY_BUT_CONTINUE          			 0x10000000    /* DRUM is empry but printing is available */
#define ENGSM_STS_CHILD_DRUM_HARDSTOP_EMPTY_SO_STOP             			 0x20000000    /* Can't printing because DRUM is empty */
#define ENGSM_STS_CHILD_DRUM_HARDSTOP_EMPTY_MONO_ONLY            			 0x40000000    /* Mono printing is just only available because of empty */
#define ENGSM_STS_CHILD_DRUM_HARDSTOP_UNDEFINED                 			 0x80000000    /* Hardstop Status is not decided */
//#define ENGSM_STS_CHILD_DRUM_HARDSTOP_NON_SEC                   			 0x00000000    /* Toner is not samsung. so ask to user about continue */
//#define ENGSM_STS_CHILD_DRUM_HARDSTOP_NON_SEC_BUT_CONTINUE      			 0x00000000    /* Toner is not samsung but, printing is available */
//#define ENGSM_STS_CHILD_DRUM_HARDSTOP_NON_SEC_SO_STOP            		 	 0x00000000    /* Can't printing because toner is not samsung  */
//#define ENGSM_STS_CHILD_DRUM_HARDSTOP_NON_SEC_MONO_ONLY         			 0x00000000    /* Mono printing is just only available because of non-sec */
//#define ENGSM_STS_CHILD_DRUM_HARDSTOP_EOM                       			 0x00000000    /* End Mark Of PrnHardStopStatus*/

/**
 * Classify		:STATUS_15
 * Device Item  :TransBeltStatus, ENGSM_STS_PARENT_TRANSFER_BELT_STATUS
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_TRANSFER_BELT_STATUS_OK                              0x00000000    /* Transfer Belt status is OK*/
#define ENGSM_STS_CHILD_TRANSFER_BELT_ALMOST_UNUSABLE                        0x00000001    /* Transfer Belt usage is almost wear out*/
#define ENGSM_STS_CHILD_TRANSFER_BELT_UNUSABLE                               0x00000002    /* Transfer Belt usage is exhausted*/
#define ENGSM_STS_CHILD_TRANSFER_BELT_NOT_INSTALLED                          0x00000004    /* Transfer Belt is not installed*/
#define ENGSM_STS_CHILD_TRANSFER_BELT_INVALID                                0x00000008    /* Transfer Belt is invalid*/
#define ENGSM_STS_CHILD_TRANSFER_BELT_NOT_GENUINE                            0x00000010    /* INVALID_PASSWORD_LOCKED: Even though password checking is tried 8 times but, not matched. Transfer belt is unable to use anymore*/
#define ENGSM_STS_CHILD_TRANSFER_BELT_HOME_SENSOR_ERROR                      0x00000020    /* [Fault] ITB home sensor error*/
#define ENGSM_STS_CHILD_TRANSFER_BELT_MOTOR_ERROR                            0x00000040    /* [Fault] ITB Motor error         */
#define ENGSM_STS_CHILD_TRANSFER_BELT_DEVE_HOME_SENSOR_ERROR                 0x00000080    /* [Fault] ITB Motor error         */
#define ENGSM_STS_CHILD_TRANSFER_BELT_ALMOST_WORN                            0x00000200    /* Installed drum is not genuine (Invalid Password Locked) */
#define ENGSM_STS_CHILD_TRANSFER_BELT_WORN                               	 0x00000400    /* Charger Sensing Error */
#define ENGSM_STS_CHILD_TRANSFER_BELT_WORN_CLEAR                             0x00000800    /* Eraser Abnormal */
#define ENGSM_STS_CHILD_TRANSFER_BELT_WORN_STOP                              0x00001000    /* Eraser Abnormal */

#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_OFF                      	 0x01000000    /* Toner cartridge has been exhaust but the H/S is off by user */
#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_NO                          	 0x02000000    /* Not hardstop condition */
#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP                             	 0x04000000    /* Can't printing device is hard stop condition */
#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_EMPTY                      	 0x08000000    /* TRANSFER_BELT is empry so ask to user about continue */
#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_EMPTY_BUT_CONTINUE          	 0x10000000    /* TRANSFER_BELT is empry but printing is available */
#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_EMPTY_SO_STOP             	 0x20000000    /* Can't printing because TRANSFER_BELT is empty */
#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_EMPTY_MONO_ONLY            	 0x40000000    /* Mono printing is just only available because of empty */
#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_UNDEFINED                 	 0x80000000    /* Hardstop Status is not decided */
//#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_NON_SEC                   	 0x00000000    /* Toner is not samsung. so ask to user about continue */
//#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_NON_SEC_BUT_CONTINUE      	 0x00000000    /* Toner is not samsung but, printing is available */
//#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_NON_SEC_SO_STOP             0x00000000    /* Can't printing because toner is not samsung  */
//#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_NON_SEC_MONO_ONLY         	 0x00000000    /* Mono printing is just only available because of non-sec */
//#define ENGSM_STS_CHILD_TRANSFER_BELT_HARDSTOP_EOM                       	 0x00000000    /* End Mark Of PrnHardStopStatus*/

#ifdef FR_IFSVC_SPECS_CODE
#define ENGSM_STS_CHILD_DR_ENGAGE_ERROR                    					 0x00000100    /* DR Engage Error */
#define ENGSM_STS_CHILD_DR_DISENGAGE_ERROR									 0x00000200    /* DR Disengage Error */	
#else
#define ENGSM_STS_CHILD_DR_ENGAGE_ERROR                   					 ENGSM_STS_CHILD_TRANSFER_BELT_DEVE_HOME_SENSOR_ERROR	/* [Fault] Fuser Gap Envlope mode error*/
#define ENGSM_STS_CHILD_DR_DISENGAGE_ERROR									 ENGSM_STS_CHILD_TRANSFER_BELT_DEVE_HOME_SENSOR_ERROR   	/* [Fault] FSA error*/	
#endif


/**
 * Classify		:STATUS_16
 * Device Item  :ACRStatus, ENGSM_STS_PARENT_ACR_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_ACR_STATUS_OK                      0x00000000    /* [Fault] ACR Sensor error*/
#define ENGSM_STS_CHILD_ACR_SENSOR_ERROR                   0x00000001    /* [Fault] ACR Sensor error*/
#define ENGSM_STS_CHILD_ACR_FAIL                           0x00000002    /* [Fault] ACR Fail*/


/**
 * Classify		:STATUS_17
 * Device Item  :CTDStatus, ENGSM_STS_PARENT_CTD_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_CTD_STATUS_OK                      0x00000000    /* [Fault] CTD Sensor error*/
#define ENGSM_STS_CHILD_CTD_SENSOR_ERROR                   0x00000001    /* [Fault] CTD Sensor error*/
#define ENGSM_STS_CHILD_CTD_FAIL                           0x00000002    /* [Fault] CTD Fail*/


/**
 * Classify		:STATUS_18
 * Device Item  :WasteTankStatus, ENGSM_STS_PARENT_WASTE_TANK_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_WASTE_STATUS_OK                     	     0x00000000    /* [Fault] CTD Sensor error*/
#define ENGSM_STS_CHILD_WASTE_TANK_NOT_INSTALLED                     0x00000001    /* Toner Waste Tank is not installed*/
#define ENGSM_STS_CHILD_WASTE_TANK_NEAR_FULL                         0x00000002    /* Toner Waste Tank is fullled*/
#define ENGSM_STS_CHILD_WASTE_TANK_FULL                              0x00000004    /* Toner Waste Tank is fullled*/
#define ENGSM_STS_CHILD_WASTE_TANK_MOTOR_ERROR                       0x00000008    /* Toner Waste Tank is fullled*/


/**
 * Classify		:STATUS_19
 * Device Item  :FuserStatus, ENGSM_STS_PARENT_FUSER_1_STATUS, ENGSM_STS_PARENT_FUSER_2_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_FUSER_ALMOST_UNUSABLE                            0x00000001    /* [Warning]Fuser usage is almost wear out*/
#define ENGSM_STS_CHILD_FUSER_UNUSABLE                                   0x00000002    /* [Warning]Fuser usage is exhausted*/
#define ENGSM_STS_CHILD_FUSER_NOT_INSTALLED                              0x00000004    /* [Fault]  Fuser is not installed*/
#define ENGSM_STS_CHILD_FUSER_INVALID                                    0x00000008    /* [Error]  Fuser is invalid*/
#define ENGSM_STS_CHILD_FUSER_FUSE_ABNORMAL                              0x00000010    /* [Error]  Fuser is invalid*/
#define ENGSM_STS_CHILD_FUSER_INIT_ERROR                                 0x00000020    /* [Error]  Fuser is invalid*/
#define ENGSM_STS_CHILD_FUSER_COMM_ERROR                                 0x00000040    /* [Error]  Fuser is installed but, communication is failed*/
#define ENGSM_STS_CHILD_FUSER_WARMUP_TIMEOUT                             0x00000080    /* [Error]  Developer temperature is not increased until specific time during warm-up*/
#define ENGSM_STS_CHILD_FUSER_OPEN_HEAT_ERROR                            0x00000100    /* [Fault] Open heating is occurred on fuser unit*/
#define ENGSM_STS_CHILD_FUSER_LOW_HEAT_ERROR                             0x00000200    /* [Fault] Low heating is occurred on fuser unit*/
#define ENGSM_STS_CHILD_FUSER_OVER_HEAT_ERROR                            0x00000400    /* [Fault] Over heating is occurred on fuser unit*/
#define ENGSM_STS_CHILD_FUSER_ABNORMAL_ADC                               0x00000800    /* [Fault] ADC Slope error (Abnormal ADC)*/
#define ENGSM_STS_CHILD_FUSER_THERMISTER_OPEN_ERROR                      0x00001000    /* [Fault] Thermister in fuser unit is opened*/
#define ENGSM_STS_CHILD_FUSER_THERMISTER_SHORT_ERROR                     0x00002000    /* [Fault] Thermister in fuser unit is shorted*/
#define ENGSM_STS_CHILD_FUSER_THERMOSTAT_OPEN_ERROR                      0x00004000    /* [Fault] Thermostat in fuser unit is opened*/
#define ENGSM_STS_CHILD_FUSER_DIFFERENTIAL_HEAT_ERROR                    0x00008000    /* [Fault] Differential heat error*/
#define ENGSM_STS_CHILD_FUSER_DC_POWER_FAULT_ERROR                       0x00010000    /* [Fault] DC Power Fault error*/
#define ENGSM_STS_CHILD_FUSER_FUSE_OPEN_ERROR							 0x00020000    /* [Fault] Fuser Fuse not open error*/
#define ENGSM_STS_CHILD_FUSER_NCTH_ALIVE_ERROR							 0x00040000    /* [Fault] NCTH chip Alive Check error*/	
#define ENGSM_STS_CHILD_FUSER_GAP_NORMAL_MODE_ERROR                      0x00080000    /* [Fault] Fuser Gap Normal mode error*/

#ifdef FR_IFSVC_SPECS_CODE
#define ENGSM_STS_CHILD_FUSER_GAP_ENVLOPE_MODE_ERROR                     0x00100000    /* [Fault] Fuser Gap Envlope mode error*/
#define ENGSM_STS_CHILD_FUSER_FSA_ERROR									 0x00200000    /* [Fault] FSA error*/	
#define ENGSM_STS_CHILD_FUSER_ABNORMAL_ADC_ERROR						 0x00400000    /* [Fault] Abnormal error*/	
#define ENGSM_STS_CHILD_FUSER_PRINT_LOW_HEAT_ERROR						 0x00800000    /* [Fault] Printing low heat error*/	
#define ENGSM_STS_CHILD_FUSER_RELAY_FEEDBACK_ERROR						 0x01000000    /* [Fault] Relay Feedback Error */	
#else
#define ENGSM_STS_CHILD_FUSER_GAP_ENVLOPE_MODE_ERROR                     ENGSM_STS_CHILD_FUSER_GAP_NORMAL_MODE_ERROR	/* [Fault] Fuser Gap Envlope mode error*/
#define ENGSM_STS_CHILD_FUSER_FSA_ERROR									 ENGSM_STS_CHILD_FUSER_OPEN_HEAT_ERROR   		/* [Fault] FSA error*/	
#define ENGSM_STS_CHILD_FUSER_ABNORMAL_ADC_ERROR						 ENGSM_STS_CHILD_FUSER_OPEN_HEAT_ERROR   		/* [Fault] Abnormal error*/	
#define ENGSM_STS_CHILD_FUSER_PRINT_LOW_HEAT_ERROR						 ENGSM_STS_CHILD_FUSER_LOW_HEAT_ERROR    		/* [Fault] Printing low heat error*/	
#define ENGSM_STS_CHILD_FUSER_RELAY_FEEDBACK_ERROR						 ENGSM_STS_CHILD_FUSER_OVER_HEAT_ERROR
#endif

#define ENGSM_STS_CHILD_FUSER_WRAP_JAM_ERROR							 0x00400000    /* [Fault] Fuser Wrap Jam error*/	

#define ENGSM_STS_CHILD_FUSER_STATUS_ALL								0x01FFFFFF
#define ENGSM_STS_CHILD_FUSER_ERROR_ALL									(ENGSM_STS_CHILD_FUSER_OPEN_HEAT_ERROR | ENGSM_STS_CHILD_FUSER_LOW_HEAT_ERROR | ENGSM_STS_CHILD_FUSER_OVER_HEAT_ERROR | ENGSM_STS_CHILD_FUSER_FSA_ERROR | ENGSM_STS_CHILD_FUSER_ABNORMAL_ADC_ERROR | ENGSM_STS_CHILD_FUSER_PRINT_LOW_HEAT_ERROR | ENGSM_STS_CHILD_FUSER_WRAP_JAM_ERROR)


/**
 * Classify		:STATUS_20
 * Device Item  :TempStatus, ENGSM_STS_PARENT_TEMPERATURE_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_INNER_TEMP_SENSOR_OPEN_ERROR              	   	0x00000001    /* [Fault] Inner Temperature sensor is checked as opened status(MFP 기내 온도 및 습도 측정을 위한 Sensor에 이상이 발생 하였음을 알려 준다)*/
#define ENGSM_STS_CHILD_INNER_TEMP_SENSOR_SHORT_ERROR             	   	0x00000002    /* [Fault] Inner Temperature sensor is checked as short status*/
#define ENGSM_STS_CHILD_OUTER_TEMP_SENSOR_OPEN_ERROR              	   	0x00000004    /* [Fault] Outer Temperature sensor is checked as opened status*/
#define ENGSM_STS_CHILD_OUTER_TEMP_SENSOR_SHORT_ERROR             	   	0x00000008    /* [Fault] Outer Temperature sensor is checked as short status*/
#define ENGSM_STS_CHILD_HUMIDITY_SENSOR_OPEN_ERROR                      0x00000010    /* [Fault] Humidity sensor is checked as opened status*/
#define ENGSM_STS_CHILD_HUMIDITY_SENSOR_SHORT_ERROR                     0x00000020    /* [Fault] Humidity sensor is checked as short status*/

#define ENGSM_STS_CHILD_TEMPERATURE_STATUS_ALL							0x0000FFFF


/**
 * Classify		:STATUS_21
 * Device Item  :EnvironmentStatus, ENGSM_STS_PARENT_ENVIRONMENT_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_ENVIRONMENT_HH_ULTRA              	   			0x00000001    /* [Fault] Inner Temperature sensor is checked as opened status(MFP 기내 온도 및 습도 측정을 위한 Sensor에 이상이 발생 하였음을 알려 준다)*/
#define ENGSM_STS_CHILD_ENVIRONMENT_HH            	   					0x00000002    /* [Fault] Inner Temperature sensor is checked as short status*/
#define ENGSM_STS_CHILD_ENVIRONMENT_HN              	   				0x00000004    /* [Fault] Outer Temperature sensor is checked as opened status*/
#define ENGSM_STS_CHILD_ENVIRONMENT_NH             	   					0x00000008    /* [Fault] Outer Temperature sensor is checked as short status*/
#define ENGSM_STS_CHILD_ENVIRONMENT_NN                    				0x00000010    /* [Fault] Humidity sensor is checked as opened status*/
#define ENGSM_STS_CHILD_ENVIRONMENT_NL                  				0x00000020    /* [Fault] Humidity sensor is checked as short status*/
#define ENGSM_STS_CHILD_ENVIRONMENT_LN              	  				0x00000040    /* [Fault] Outer Temperature sensor is checked as opened status*/
#define ENGSM_STS_CHILD_ENVIRONMENT_LL             	 				  	0x00000080    /* [Fault] Outer Temperature sensor is checked as short status*/
#define ENGSM_STS_CHILD_ENVIRONMENT_LL_ULTRA                 			0x00000100    /* [Fault] Humidity sensor is checked as opened status*/





/**
 * Classify		:STATUS_22
 * Device Item  :LSUStatus, ENGSM_STS_PARENT_LSU_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_LSU_C_LOCK_ERROR                                 0x00000001    /* [Fault] Cyan LSU is locked (Lready error is occurred)*/
#define ENGSM_STS_CHILD_LSU_M_LOCK_ERROR                                 0x00000002    /* [Fault] Magenta LSU is locked(Lready error is occurred)*/
#define ENGSM_STS_CHILD_LSU_Y_LOCK_ERROR                                 0x00000004    /* [Fault] Yellow LSU is locked(Lready error is occurred)*/
#define ENGSM_STS_CHILD_LSU_K_LOCK_ERROR                                 0x00000008    /* [Fault] Black LSU is locked(Lready error is occurred)*/
#define ENGSM_STS_CHILD_LSU_C_HSYNC_ERROR                                0x00000010    /* [Fault] Cyan LSU H-sync error */
#define ENGSM_STS_CHILD_LSU_M_HSYNC_ERROR                                0x00000020    /* [Fault] Magenta LSU H-sync error */
#define ENGSM_STS_CHILD_LSU_Y_HSYNC_ERROR                                0x00000040    /* [Fault] Yellow LSU H-sync error */
#define ENGSM_STS_CHILD_LSU_K_HSYNC_ERROR                                0x00000080    /* [Fault] Black LSU H-sync error */
#define ENGSM_STS_CHILD_LSU_READY_ERROR                           	     0x00000100    /* [Fault] LSU Ready error */
#define ENGSM_STS_CHILD_LSU_READY_SIGNAL_ERROR                     	     0x00000200    /* [Fault] LSU Ready signal error */
#define ENGSM_STS_CHILD_LSU_STEADY_ERROR                     	     	 0x00000400    /* [Fault] LSU Ready run error */
#define ENGSM_STS_CHILD_LSU_SHUTTER_ERROR                                0x00000800    /* [Fault] LSU Shutter error*/
#define ENGSM_STS_CHILD_LSU_INSTALL_ERROR                                0x00001000    /* [Fault] LSU Install error*/
#define ENGSM_STS_CHILD_LSU_HEAT_ERROR	                                 0x00002000    /* [Fault] LSU Install error*/


#define ENGSM_STS_CHILD_LSU_STATUS_ALL					0x0000FFFF


/**
 * Classify		:STATUS_23
 * Device Item  :FinisherStatus, ENGSM_STS_PARENT_FINISHER_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_FINISHER_NOT_INSTALLED                           0x00000001    /* [Error]Finisher is not installed*/
#define ENGSM_STS_CHILD_FINISHER_STACK_FULL                              0x00000002    /* [Error]Finisher stack is fulled*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_CARTRIDGE_NOT_INSTALLED         0x00000004    /* [Warningr]Staple cartridge in finisher is not installed*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_EMPTY                           0x00000008    /* [Warning]Stapler Empty*/
#define ENGSM_STS_CHILD_FINISHER_DOOR_OPEN                               0x00000010    /* [Error]Finisher door is opened*/
#define ENGSM_STS_CHILD_FINISHER_COMM_ERROR                              0x00000020    /* [Fault]Finisher is installed but, communication is failed*/
#define ENGSM_STS_CHILD_FINISHER_PADDLE_FAULT                            0x00000040    /* [Fault]Finisher faddle unit is not operational*/
#define ENGSM_STS_CHILD_FINISHER_FRONT_JOGGER_FAULT                      0x00000080    /* [Fault]Finisher front jogger is not operational*/
#define ENGSM_STS_CHILD_FINISHER_REAR_JOGGER_FAULT                       0x00000100    /* [Fault]Finisher rear jogger fault*/
#define ENGSM_STS_CHILD_FINISHER_SUPPORT_FINGER_FAULT                    0x00000200    /* [Fault]Finisher supported finger fault*/
#define ENGSM_STS_CHILD_FINISHER_EJECTOR_FAULT                           0x00000400    /* [Fault]Ejector fault */
#define ENGSM_STS_CHILD_FINISHER_STAPLER_FAULT                           0x00000800    /* [Fault]Stapler fault*/
#define ENGSM_STS_CHILD_FINISHER_STACKER_FAULT                           0x00001000    /* [Fault]Stacker fault*/
#define ENGSM_STS_CHILD_FINISHER_JAM_0                                   0x00002000    /* [Error]Finisher jam 0*/
#define ENGSM_STS_CHILD_FINISHER_JAM_1                                   0x00004000    /* [Error]Finisher jam 1*/
#define ENGSM_STS_CHILD_FINISHER_JAM_2                                   0x00008000    /* [Error]Finisher jam 2*/
#define ENGSM_STS_CHILD_FINISHER_DUPLEX_JAM                 	         0x00010000    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_FINISHER_FAULT                 	        		 0x00020000    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_MAILBOX_BIN_JAM                 	       	  	 0x00040000    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_MAILBOX_GATE_UPPER_FAULT            	     	 0x00080000    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_MAILBOX_GATE_LOWER_FAULT                 		 0x00100000    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_FINISHER_JAM                 					 0x00200000    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_OUTPUT_TRAY_STANDARD_FULL                        0x00400000    /* [Error]Finisher stack is fulled*/
#define ENGSM_STS_CHILD_OUTPUT_TRAY1_FULL                              	 0x00800000    /* [Error]Finisher stack is fulled*/
#define ENGSM_STS_CHILD_OUTPUT_TRAY2_FULL                              	 0x01000000    /* [Error]Finisher stack is fulled*/
#define ENGSM_STS_CHILD_OUTPUT_TRAY3_FULL                              	 0x02000000    /* [Error]Finisher stack is fulled*/
#define ENGSM_STS_CHILD_OUTPUT_TRAY4_FULL                              	 0x04000000    /* [Error]Finisher stack is fulled*/
#define ENGSM_STS_CHILD_FINISHER_DOWNLOAD_READY							 0x08000000    /* Finisher Download Ready*/

#define ENGSM_STS_CHILD_FINISHER_STATUS_ERROR							 0x0FFFFFFE	   	//	 0000 0000 1100 0000 0011 1111 1111 1110     
#define ENGSM_STS_CHILD_FINISHER_STATUS_ALL								 0x0FFFFFFE


/**
 * Classify		:STATUS_24
 * Device Item  :FinisherWarning, ENGSM_STS_PARENT_FINISHER_WARNING
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_FINISHER_NEAR_FULL_STACK                         0x00000001    /* [Error]Finisher jam 0*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_LOW                             0x00000002    /* [Error]Finisher jam 1*/
//#define ENGSM_STS_CHILD_FINISHER_DIVERTER_FAULT                          0x00000004    /* [Error]Finisher jam 2*/
//#define ENGSM_STS_CHILD_FINISHER_STACKER_DOWNWARD_FAULT                  0x00000008    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_FINISHER_FRONT_JOGGER_FAULT_TO                   0x00000010    /* [Error]Finisher jam 0*/
#define ENGSM_STS_CHILD_FINISHER_REAR_JOGGER_FAULT_TO                    0x00000020    /* [Error]Finisher jam 1*/
#define ENGSM_STS_CHILD_FINISHER_SUPPORT_FINGER_FAULT_TO                 0x00000040    /* [Error]Finisher jam 2*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_JAW_FAULT_TO                	 0x00000080    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_SAFEFY_NOT                	     0x00000100    /* [Error]Finisher duplex jam*/
//#define ENGSM_STS_CHILD_FINISHER_STAPLER_PRIMING_FAULT                	 0x00000200    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_MAILBOX_GATE_UPPER_FAULT_TO            	     	 0x00000400    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_MAILBOX_GATE_LOWER_FAULT_TO                 	 0x00000800    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_MAILBOX_TRAY1_EMPTY								 0x00001000    /* [Warning]Mailbox Tray Empty*/
#define ENGSM_STS_CHILD_MAILBOX_TRAY2_EMPTY								 0x00002000    /* [Warning]Mailbox Tray Empty*/
#define ENGSM_STS_CHILD_MAILBOX_TRAY3_EMPTY								 0x00004000    /* [Warning]Mailbox Tray Empty*/
#define ENGSM_STS_CHILD_MAILBOX_TRAY4_EMPTY								 0x00008000    /* [Warning]Mailbox Tray Empty*/

#define ENGSM_STS_CHILD_FINISHER_STATUS_WARNING							 0x0000FFFF		//	 0000 0000 1111 1111 1111	


/**
 * Classify		:STATUS_25
 * Device Item  :FinisherFault, ENGSM_STS_PARENT_FINISHER_FAULT
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_FINISHER_FRONT_JOGGER_FAULT_FROM_HOME			0x00000001    /* [Error]Finisher is not installed*/
#define ENGSM_STS_CHILD_FINISHER_FRONT_JOGGER_FAULT_TO_HOME				0x00000002    /* [Error]Finisher stack is fulled*/
#define ENGSM_STS_CHILD_FINISHER_REAR_JOGGER_FAULT_FROM_HOME			0x00000004    /* [Warningr]Staple cartridge in finisher is not installed*/
#define ENGSM_STS_CHILD_FINISHER_REAR_JOGGER_FAULT_TO_HOME				0x00000008    /* [Warning]Stapler Empty*/
#define ENGSM_STS_CHILD_FINISHER_SUPPORT_FINGER_FAULT_FROM_HOME			0x00000010    /* [Error]Finisher door is opened*/
#define ENGSM_STS_CHILD_FINISHER_SUPPORT_FINGER_FAULT_TO_HOME			0x00000020    /* [Fault]Finisher is installed but, communication is failed*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_JAW_FAULT_FROM_HOME			0x00000040    /* [Fault]Finisher faddle unit is not operational*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_JAW_FAULT_TO_HOME				0x00000080    /* [Fault]Finisher front jogger is not operational*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_SAFETY_NOT_DETECTED			0x00000100    /* [Fault]Finisher rear jogger fault*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_PRIMING_FAULT					0x00000200    /* [Fault]Finisher supported finger fault*/
#define ENGSM_STS_CHILD_FINISHER_STACKER_UPWARD_FAULT					0x00000400    /* [Fault]Ejector fault */
#define ENGSM_STS_CHILD_FINISHER_STACKER_DOWNWARD_FAULT					0x00000800    /* [Fault]Stapler fault*/
#define ENGSM_STS_CHILD_FINISHER_DIVERTER_FAULT							0x00001000    /* [Fault]Stacker fault*/
#define ENGSM_STS_CHILD_FINISHER_SHEET_NOT_FED_WITHIN_TIME				0x00002000    /* [Error]Finisher door is opened*/
#define ENGSM_STS_CHILD_FINISHER_JAM_FROM_ENTERANCE						0x00004000    /* [Error]Finisher jam 0*/
#define ENGSM_STS_CHILD_FINISHER_JAM_OVER_ENTRANCE_DURING_INIT			0x00008000    /* [Error]Finisher jam 1*/
#define ENGSM_STS_CHILD_FINISHER_JAM_TO_EXIT							0x00010000    /* [Error]Finisher jam 2*/
#define ENGSM_STS_CHILD_FINISHER_JAM_FROM_EXIT							0x00020000    /* [Error]Finisher duplex jam*/
#define ENGSM_STS_CHILD_FINISHER_JAM_OVER_EXIT_DURING_INIT				0x00040000    /* [Error]Finisher jam 0*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_EMPTY_OR_NOT_CARTRIDGE			0x00080000    /* [Error]Finisher is not installed*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_LOW_STAPLES					0x00100000    /* [Error]Finisher is not installed*/
#define ENGSM_STS_CHILD_FINISHER_STAPLER_DOOR_OPEN						0x00200000    /* [Error]Finisher is not installed*/
#define ENGSM_STS_CHILD_FINISHER_JAM_DOOR_OPEN							0x00400000    /* [Error]Finisher is not installed*/

#define ENGSM_STS_CHILD_FINISHER_STATUS_FAULT							0x00001FFF		//	 0000 0000 1111 1111 1111	
#define ENGSM_STS_CHILD_FINISHER_STATUS_JAM								0x0007E000		//   0001 1110 0011 1111 1100 0000 0000 0000
#define ENGSM_STS_CHILD_FINISHER_STATUS_DOOR_OPEN						(ENGSM_STS_CHILD_FINISHER_STAPLER_DOOR_OPEN | ENGSM_STS_CHILD_FINISHER_JAM_DOOR_OPEN)

#define ENGSM_STS_CHILD_FINISHER_FAULT_STATUS_ALL						0x00FFFFFF


/**
 * Classify		:STATUS_26
 * Device Item  :MailboxFault, ENGSM_STS_PARENT_MAILBOX_FAULT
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_MAILBOX_UPPER_DIVERTER_FAULT_FROM_HOME			0x00000001    /* [Error]Finisher is not installed*/
#define ENGSM_STS_CHILD_MAILBOX_UPPER_DIVERTER_FAULT_TO_HOME			0x00000002    /* [Error]Finisher stack is fulled*/
#define ENGSM_STS_CHILD_MAILBOX_LOWER_DIVERTER_FAULT_FROM_HOME			0x00000004    /* [Warningr]Staple cartridge in finisher is not installed*/
#define ENGSM_STS_CHILD_MAILBOX_LOWER_DIVERTER_FAULT_TO_HOME			0x00000008    /* [Warning]Stapler Empty*/
#define ENGSM_STS_CHILD_MAILBOX_SHEET_NOT_FED_WITHIN_TIME				0x00000010    /* [Error]Finisher door is opened*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_FROM_ENTERANCE						0x00000020    /* [Fault]Finisher is installed but, communication is failed*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_OVER_ENTRANCE_DURING_INIT			0x00000040    /* [Fault]Finisher faddle unit is not operational*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_FROM_TRAY1_EXIT						0x00000080    /* [Fault]Finisher front jogger is not operational*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_TO_TRAY1_EXIT						0x00000100    /* [Fault]Finisher rear jogger fault*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_OVER_TRAY1_EXIT_SENSOR_DURING_INIT	0x00000200    /* [Fault]Finisher supported finger fault*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_FROM_TRAY2_EXIT						0x00000400    /* [Fault]Ejector fault */
#define ENGSM_STS_CHILD_MAILBOX_JAM_TO_TRAY2_EXIT						0x00000800    /* [Fault]Stapler fault*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_OVER_TRAY2_EXIT_SENSOR_DURING_INIT	0x00001000    /* [Fault]Stacker fault*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_FROM_TRAY3_EXIT						0x00002000    /* [Fault]Ejector fault */
#define ENGSM_STS_CHILD_MAILBOX_JAM_TO_TRAY3_EXIT						0x00004000    /* [Fault]Stapler fault*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_OVER_TRAY3_EXIT_SENSOR_DURING_INIT	0x00008000    /* [Fault]Stacker fault*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_FROM_TRAY4_EXIT						0x00010000    /* [Fault]Ejector fault */
#define ENGSM_STS_CHILD_MAILBOX_JAM_TO_TRAY4_EXIT						0x00020000    /* [Fault]Stapler fault*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_OVER_TRAY4_EXIT_SENSOR_DURING_INIT	0x00040000    /* [Fault]Stacker fault*/
#define ENGSM_STS_CHILD_MAILBOX_JAM_DOOR_OPEN							0x00080000    /* [Error]Finisher is not installed*/

#define ENGSM_STS_CHILD_MAILBOX_STATUS_FAULT							0x0000000F		//	 0000 0000 0000 0000 0000 1111	
#define ENGSM_STS_CHILD_MAILBOX_STATUS_JAM								0x0007FFF0		//	 0000 0111 1111 1111 1111 0000	
#define ENGSM_STS_CHILD_MAILBOX_STATUS_DOOR_OPEN						(ENGSM_STS_CHILD_MAILBOX_JAM_DOOR_OPEN)

#define ENGSM_STS_CHILD_MAILBOX_FAULT_STATUS_ALL						0x000FFFFF


/**
 * Classify		:STATUS_27
 * Device Item  :ExpanderStatus, ENGSM_STS_PARENT_EXPANDER_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_EXPANDER_STATUS_OK								0x00000000    /* Tray is not installed*/
#define ENGSM_STS_CHILD_EXPANDER_NOT_INSTALLED							0x00000001    /* Tray is not installed*/
#define ENGSM_STS_CHILD_EXPANDER_OPEN									0x00000002    /* Tray is opened*/
#define ENGSM_STS_CHILD_EXPANDER_COMM_ERROR								0x00000003    /* Tray comm error*/

#define ENGSM_STS_CHILD_EXPANDER_STATUS_ALL								0x0000FFFF

/**
 * Classify		:STATUS_28
 * Device Item  :EDCStatus, ENGSM_STS_PARENT_DIAG_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_DIAG_OPEN_HEAT_ERROR                         0x00000001    /* [Error] Checking now low heat error during self diagnostic*/
#define ENGSM_STS_CHILD_DIAG_LOW_HEAT_ERROR                          0x00000002    /* [Error] Checking now low heat error during self diagnostic*/
#define ENGSM_STS_CHILD_DIAG_OVER_HEAT_ERROR                         0x00000004    /* [Error] Checking now low heat error during self diagnostic*/
#define ENGSM_STS_CHILD_DIAG_LREADY_ERROR                            0x00000008    /* [Error] Checking now LReady error during self diagnostic*/
#define ENGSM_STS_CHILD_DIAG_HSYNC_ERROR                             0x00000010    /* [Error] Checking now Hsync error during self diagnostic*/
#define ENGSM_STS_CHILD_DIAG_DEVELOPER_HOME_RECOVERY                 0x00000020    /* [Error] Developer home recoverying*/
#define ENGSM_STS_CHILD_DIAG_TONER_MIXING                            0x00000040    /* [Error] Toner mixing or supplying*/
#define ENGSM_STS_CHILD_DIAG_DEVELOPER_INITIALIZING                  0x00000080    /* [Error] Initializing developer when new developer is installed*/
#define ENGSM_STS_CHILD_DIAG_CTD_PROCESSING                          0x00000100    /* [Error] CTD Algorithm is processing */
#define ENGSM_STS_CHILD_DIAG_CHARGING_PROCESSING                     0x00000200    /* [Error] charging algorithm is processing*/
#define ENGSM_STS_CHILD_DIAG_ACR_PROCESSING                          0x00000400    /* [Error] ACR Operation is processing*/
#define ENGSM_STS_CHILD_DIAG_DELAY_PRINTING_FOR_COOLING              0x00000800    /* [Error] Time delay printing state to decrease temperature development degree*/
#define ENGSM_STS_CHILD_DIAG_LIFTING_ERROR                           0x00001000    /* [Error] Checking now Tray Lifting error during self diagnostic*/
#define ENGSM_STS_CHILD_DIAG_MOTOR_READY_ERROR                       0x00002000    /* [Error] Checking now LReady error during self diagnostic*/

#define ENGSM_STS_CHILD_DIAG_STATUS_ALL								 0x0000FFFF

/**
 * Classify		:STATUS_29
 * Device Item  :SystemDevice, ENGSM_STS_PARENT_SYSTEM_DEVICE_STATUS
 * Status Kinds :Info
 */
#define ENGSM_STS_CHILD_SYSTEM_INITIALIZING                                  0x00000000    /* System is powering up*/
#define ENGSM_STS_CHILD_SYSTEM_INITIALIZED                                   0x00000001    /* system is idle*/
#define ENGSM_STS_CHILD_SYSTEM_DOWNLOADING                                   0x00000002    /* system is in downloading mode*/
#define ENGSM_STS_CHILD_SYSTEM_SELF_TESTING                                  0x00000003    /* system is doing selftest*/
#define ENGSM_STS_CHILD_SYSTEM_POWER_SAVING                                  0x00000004    /* system is in power saving mode*/
#define ENGSM_STS_CHILD_SYSTEM_ERROR                                         0x00000005    /* system has error*/


/**
 * Classify		:STATUS_30
 * Device Item  :TrayVersion, ENGSM_STS_PARENT_TRAY_2_VERSION, ENGSM_STS_PARENT_TRAY_3_VERSION, ENGSM_STS_PARENT_TRAY_4_VERSION, ENGSM_STS_PARENT_HCF_VERSION, ENGSM_STS_PARENT_FINISHER_VERSION, ENGSM_STS_PARENT_EXPANDER_VERSION
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_OPTION_MAJOR_VERSION   		0x000000FF    /* Tray Major Version */
#define ENGSM_STS_CHILD_OPTION_MIDDLE_VERSION      	0x000000FF    /* Tray Middle Version */
#define ENGSM_STS_CHILD_OPTION_MINOR_VERSION       	0x000000FF    /* Tray Minor Version */


/**
 * Classify		:STATUS_31
 * Device Item  :ALL_IN_ONE_BLDC_CONTROLLER(ABCStatus), ENGSM_STS_PARENT_ABC_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_COMMUNICATION_ERR                                   0x00000001    /* system is idle*/
#define ENGSM_STS_CHILD_ALIVE_ERR                                   		0x00000002    /* system is idle*/

/**
 * Classify		:STATUS_32
 * Device Item  :ENGSM_STS_PARENT_TRANSFER_STATUS
 * Status Kinds :DirectValue
 */
#define ENGSM_STS_CHILD_TRANSFER_STATUS_OK                                      0x00000000    /* Drum status is OK*/
#define ENGSM_STS_CHILD_TRANSFER_INITIALIZING_ERROR                             0x00000001    /* Drum mixing time is over 180sec when new Drum is installed*/
#define ENGSM_STS_CHILD_TRANSFER_ALMOST_UNUSABLE                                0x00000002    /* Drum is near the end of life.*/
#define ENGSM_STS_CHILD_TRANSFER_UNUSABLE                                       0x00000004    /* Drum life has been reached to max pages*/
#define ENGSM_STS_CHILD_TRANSFER_NOT_INSTALLED                                  0x00000008    /* Drum usage is not installed*/
#define ENGSM_STS_CHILD_TRANSFER_SENSING_ERR		                       	    0x00100000    /* Transfer Sensing Error */


#endif /* __ENG_STATUSTYPE_H__ */

