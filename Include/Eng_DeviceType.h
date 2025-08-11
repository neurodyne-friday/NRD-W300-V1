/**
 * @file        Eng_DeviceType.h
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
 * @dept		Embedded Developement Team
 * @date		19/02/2024(D/M/Y)
 * @version		V0.1
 */


#ifndef __ENGDRV_DEVICETYPE_H__
#define __ENGDRV_DEVICETYPE_H__

#include "EngHAL_Types.h"
#include "EngOS_Types.h"

/**
 * Driver Handle ID
 */
typedef enum
{
    ENG_DRV_ADC,
    ENG_DRV_CLUTCH,
    ENG_DRV_FAN,
    ENG_DRV_CAN,
    ENG_DRV_MOTOR,
    ENG_DRV_SENSOR,
    ENG_DRV_UART,
    ENG_DRV_I2C,    
    ENG_DRV_SIO,
    ENG_DRV_SPI,
    ENG_DRV_POWER,
    ENG_DRV_CRUM,
    ENG_DRV_MAX
} TEngDrvId;

#define DEVICE_ADC_KEY_BASE			11000
#define DEVICE_ETH_KEY_BASE	        12000
#define DEVICE_CAN_KEY_BASE			13000
#define DEVICE_MOTOR_KEY_BASE		14000
#define DEVICE_SENSOR_KEY_BASE		15000
#define DEVICE_ENCODER_KEY_BASE		16000
#define DEVICE_UART_KEY_BASE		17000
#define DEVICE_EEPROM_KEY_BASE		18000
#define DEVICE_FLASH_KEY_BASE		19000
#define DEVICE_SOLENOID_KEY_BASE	20000
#define DEVICE_SIO_KEY_BASE			21000
#define DEVICE_SPI_KEY_BASE			22000
#define DEVICE_POWER_KEY_BASE		23000


/**
 * Device Information of CAN(Control Area Network)
 */

typedef enum
{
	CAN_NAME_MAIN   			= DEVICE_CAN_KEY_BASE,
    CAN_NAME_MAX,
    CAN_NAME_UNSPECIFIED        = CAN_NAME_MAX
} TCANName;

#define CAN_RX_MAX_COUNT    20//50//20
#define CAN_TX_MAX_COUNT	100//150//100
#define CAN_RX_MAX_SIZE		640//1280//640
#define CAN_TX_MAX_SIZE		500//3000

#define CAN_MAX_OBSERVER_COUNT	20

typedef struct _TCANObserver
{
    U32 ulDeviceKey;
    void (*pfnNotify)(U32 ulDeviceKey, U8* pubData, U16 uwLength);
} TCANObserver;

typedef struct _TCANRxBuffer
{
	U16 uwIndex;
	U16 uwLength;
	U8 ubState;
	U8 pubData[CAN_RX_MAX_SIZE];
} TCANRxBuffer;

typedef struct _TCANTxBuffer
{
	U16 uwLength;
	U8 pubData[CAN_TX_MAX_SIZE];
} TCANTxBuffer;

typedef struct _TCANRxMessage
{
	U16 uwIndex;
	U16 uwLength;
	U8 ubState;
	U8 pubData[CAN_RX_MAX_SIZE];
} TCANRxMessage;

typedef struct _TCANTxMessage
{
	U16 uwLength;
	U8 pubData[CAN_TX_MAX_SIZE];
} TCANTxMessage;

typedef struct _TCanCommand
{
    U16 uwCommand;
    U8 ubCmdByte1;
    U8 ubCmdByte2;
    U8 ubState;
    U8 ubModuleIndex;
	U16 uwLength;
	U8 *pubData;
} TCanCommand;

typedef enum _TCANState
{
    CAN_STATE_Waiting    = 0,
    CAN_STATE_Ready      = 1,
    CAN_STATE_Running    = 2,
    CAN_STATE_Error		 = 3
} TCANState;

typedef struct _TCAN
{
    U32 ulDeviceKey;
	U8 *pubName;
    TCANState eStatus;

    U32 ulHalID;

    //EngOS_Queue osqCanRxQ;
    //EngOS_Queue osqCanTxQ;
    //EngOS_Queue osqCanCommandQ;
    //EngOS_Semaphore osmCanTxQSemapore;
    //EngOS_Mutex osmCanMutex;

    //TCANRxBuffer astCanRxBuffer;
    //TCANTxBuffer astCanTxBuffer;

    //TCANRxMessage astCanRxMsg[CAN_RX_MAX_COUNT];
    //TCANTxMessage astCanTxMsg[CAN_TX_MAX_COUNT];

    TCanCommand astCanCommand;

    VU16 vuwCanTimer;

    U32 aulCANTransmitCount[2];
    U16 uwMaxPendingTransmitCount;

    U8 ubCanTaskCommand;

    // Inner functions
    void (*pfnInitialize)(struct _TCAN* pstCAN);
    BOOL (*pfnAppendObserver)(struct _TCAN* pstCAN, TCANObserver *pstObserver);
    void (*pfnNotifyToObservers)(struct _TCAN* pstCAN, U8* pubData, U16 uwLength);
    void (*pfnHALRxCallback)(U32 ulHalName, U8* pubData, U16 uwLength);
    void (*pfnSendData)(struct _TCAN* pstCAN, U8* pubData, U16 uwLength);

    // List array of Callback functions
    TCANObserver stObservers[CAN_MAX_OBSERVER_COUNT];
    U16 uwObserverCount;

} TCAN;


/**
 * Device Information of Ethernet
 */


typedef enum
{
	ETH_NAME_MAIN		    = DEVICE_ETH_KEY_BASE,
    ETH_NAME_MAX,
	ETH_NAME_UNSPECIFIED    = ETH_NAME_MAX
} TETHName;

typedef enum 
{
    ETH_STATE_DISCONNECTED,
    ETH_STATE_READYCONNECT,
    ETH_STATE_TRYCONNECT,
    ETH_STATE_CONNECTED,
    ETH_STATE_TIMEOUT,
    ETH_STATE_UNDEFINED,
} TETHState;

typedef struct _TETH
{
    U32 ulDeviceKey;
	U8 *pubName;

    TETHState eState;
 
    void (*pfnInitialize)(struct _TETH *pstETH);

} TETH;


/**
 * Device Information of Sensors
 */


typedef enum
{
	SENSOR_NAME_NONAME          = DEVICE_SENSOR_KEY_BASE,

    SENSOR_NAME_MAX,
    SENSOR_NAME_UNSPECIFIED     = SENSOR_NAME_MAX
} TSensorName;

typedef enum
{
	SENSOR_TYPE_INTERRUPT,
	SENSOR_TYPE_SHORT,
	SENSOR_TYPE_LONG,
	SENSOR_TYPE_UNSPECIFIED
} TSensorType;

typedef enum
{
	SENSOR_READ_TYPE_INSTANT,
	SENSOR_READ_TYPE_STABLE,
	SENSOR_READ_TYPE_UNSPECIFIED
} TSensorReadType;

typedef enum
{
	SENSOR_READ_CTRL_DIRECT,
	SENSOR_READ_CTRL_USEMUX,
	SENSOR_READ_CTRL_UNSPECIFIED
} TSensorReadCtrl;

typedef enum
{
	SENSOR_LEVEL_0,
    SENSOR_LEVEL_1,
    SENSOR_LEVEL_2,
	SENSOR_LEVEL_3,
	SENSOR_LEVEL_UNSPECIFIED
} TSensorLevel;

#define SENSOR_BUFFER_SIZE  3

typedef void (*TSENSOR_CALLBACK)(U8 *parg);

typedef struct _TSensor
{
	/************ Below variables are initialized in table ************/
    U32 ulDeviceKey;
	U8 *pubName;
    GPIO_TypeDef* pstHalBaseID;
    U32 ulHalPinID;
    TSensorType enType;
    THalGPIOActive eIOActiveType;
    TSensorReadType enReadType;
	TSensorReadCtrl enReadCtrl;
	/******************************************************************/

	U8 ubOnCnt;
	U8 ubOffCnt;
    U8 ubSensorValue;
    U8 ubOldSensorValue;
	U8 aubSensorValue[SENSOR_BUFFER_SIZE];
    U8 ubWrapperValue;
    U8 ubIsLevelSensor;

    // Internal functions
    void (*pfnInitialize)(struct _TSensor *pstSensor);
    U8 (*pfnGet)(struct _TSensor *pstSensor);
    //void (*pfnSetLevel)(struct _TSensor *pstSensor, U8 ubValue);
    void (*pfnSetLevel)(TSensorName ulSensorName, TSensorLevel eLevel);
    void (*pfnOnOffCheck)(struct _TSensor *pstSensor);
    void (*pfnGetOnOffError)(struct _TSensor *pstSensor);

} TSensor;


/**
 * Device Information of Motors
 */

// typedef enum
// {
//     MOTOR_NAME_HEAD_ROLL         = DEVICE_MOTOR_KEY_BASE, 
//     MOTOR_NAME_HEAD_YAW,
// 	MOTOR_NAME_RIGHT_SHOULDER1,
//     MOTOR_NAME_RIGHT_SHOULDER2,
//     MOTOR_NAME_RIGHT_SHOULDER3,
//     MOTOR_NAME_RIGHT_ELBOW,
//     MOTOR_NAME_RIGHT_WRIST1,
//     MOTOR_NAME_RIGHT_WRIST2,
//     MOTOR_NAME_MAX,
//     MOTOR_NAME_UNSPECIFIED = MOTOR_NAME_MAX
// } TMotorName;

// typedef enum
// {
// 	MOTOR_TYPE_STEP,
// 	MOTOR_TYPE_BLDC,
// 	MOTOR_TYPE_DC,
// 	MOTOR_TYPE_SERVO_RMDX,
//     MOTOR_TYPE_SERVO_DYNAMIXEL,
// 	MOTOR_TYPE_UNSPECIFIED
// } TMotorType;

// typedef enum
// {
// 	MOTOR_DIR_BACKWARD, //MOTOR_DIR_CW,
// 	MOTOR_DIR_FORWARD,  //MOTOR_DIR_CCW,
// 	MOTOR_DIR_UNSPECIFIED
// } TMotorDirection;

// typedef enum
// {
// 	MOTOR_MODE_FULL			= 0,
// 	MOTOR_MODE_HALF			= 1,
// 	MOTOR_MODE_QUARTER		= 2,
// 	MOTOR_MODE_EIGHTH		= 3,
// 	MOTOR_MODE_UNSPECIFIED
// } TMotorMode;

// typedef enum
// {
// 	MOTOR_ST_STOP,				/**< detent position */
// 	MOTOR_ST_EXCITATION,		/**< Settling time from detent position to equilibrium position : ~250ms */
// 	MOTOR_ST_ACCELERATION,		/**< Linear (motion in straight line) or Nonlinear (S-Curve) : ACC = dV/dT */
// 	MOTOR_ST_ACCELERATION2,		/**< Linear (motion in straight line) or Nonlinear (S-Curve) : ACC = dV/dT */
// 	MOTOR_ST_STEADY,			/**< Standard deviation of velocity at steady state : Ripple */
// 	MOTOR_ST_DECELERATION,		/**< Linear (motion in straight line) or Nonlinear (S-Curve) : DEC = dV/dT */
// 	MOTOR_ST_DE_EXCITATION,		/**< Settling time from equilibrium position to detent position : 10ms~ */
// 	MOTOR_ST_HOLD				/**< Keep up time at detent or equilibrium position */
// } TMotorState;

// typedef enum
// {
// 	MOTOR_CURRENT_LOW,
// 	MOTOR_CURRENT_MIDDLE,
// 	MOTOR_CURRENT_HIGH,
// 	MOTOR_CURRENT_PWM,
// 	MOTOR_CURRENT_UNSPECIFIED
// } TMotorCurrent;

// typedef enum
// {
// 	MOTOR_CTRL_INIT,
// 	MOTOR_CTRL_DOWNLOAD_SPEED_TABLE,
// 	MOTOR_CTRL_START,
// 	MOTOR_CTRL_CHANGE_SPEED,
// 	MOTOR_CTRL_BACKWARD_START,
// 	MOTOR_CTRL_HOLD,
// 	MOTOR_CTRL_STOP,
// 	MOTOR_CTRL_SET_CURRENT,
// 	MOTOR_CTRL_GET_STATE,
// 	MOTOR_CTRL_CHK_CONNECTION,
// 	MOTOR_CTRL_READY_CHK,
// 	MOTOR_CTRL_CHANGE_CURRVELOCITY,
// 	MOTOR_CTRL_CHECK_MOTOR_STOP_STABLE,	
// 	MOTOR_CTRL_GET_MOTOR_STOP_STABLE_TIME,	
// 	MOTOR_CTRL_GET_CURR_SPEED_RATIO,
// 	MOTOR_CTRL_GET_ENABLE_POINT_TIME,
// 	MOTOR_CTRL_GET_STEP_PPS,
// 	MOTOR_CTRL_GET_START_ELAPSED_TIME,
// 	MOTOR_CTRL_GET_MOTOR_ACC_TOTAL_TIME,
// 	MOTOR_CTRL_REGIST_LOAD_SENS_MONITOR_FUNC,
// 	MOTOR_CTRL_MAX
// } TMotorCtrlCode;

// typedef enum
// {
// 	MOTOR_BLDC_HALL_SENSOR_A,
// 	MOTOR_BLDC_HALL_SENSOR_B,
// 	MOTOR_BLDC_HALL_SENSOR_C,
// 	MOTOR_BLDC_HALL_SENSOR_MAX
// } TMotorBLDCHallType;

// typedef enum
// {
// 	MOTOR_BLDC_SPEED_IDLE,
// 	MOTOR_BLDC_SPEED_LOCK,
// 	MOTOR_BLDC_SPEED_ADJUST,
// 	MOTOR_BLDC_SPEED_MAX
// } TMotorBLDCSpeedState;


// typedef struct
// {
// 	TMotorState enState;
// 	TMotorCurrent enCurrent;
// 	U32 ulTime;
// 	//TMotorSpeedTable *pstSpeedTbl;
// } TMotorCtrlParameter;

// typedef struct
// {
// 	F32 fPGain;
//     F32 fIGain;
//     F32 fDGain;
// } TMotorPIDCtrlGain;

// typedef struct
// {
// 	GPIO_TypeDef* pstEnablePort;
// 	U32 ulEnablePin;
// 	GPIO_TypeDef* pstDirectionPort;
// 	U32 ulDirectionPin;
// 	GPIO_TypeDef* pstHoldPort;
// 	U32 ulHoldPin;
// 	GPIO_TypeDef* pstPulsePort;
// 	U32 ulPulsePin;
// 	GPIO_TypeDef* pstMD0Port;
// 	U32 ulMD0Pin;
// 	GPIO_TypeDef* pstMD1Port;
// 	U32 ulMD1Pin;
// } TMotorStepCtrlHalInfo;


// typedef struct
// {
// 	U32 ulSPIDeviceKey; // if use SPI config type

// 	GPIO_TypeDef* pstEnablePort;
// 	U32 ulEnablePin;
// 	GPIO_TypeDef* pstDirectionPort;
// 	U32 ulDirectionPin;
// 	GPIO_TypeDef* pstBrakePort;
// 	U32 ulBrakePin;
// 	GPIO_TypeDef* pstClkPort;
// 	U32 ulClkPin;
// 	GPIO_TypeDef* pstFaultPort;
// 	U32 ulFaultPin;
// 	GPIO_TypeDef* pstLockPort;
// 	U32 ulLockPin;
// 	GPIO_TypeDef* pstFGOutPort;
// 	U32 ulFGOutPin;
// } TMotorBLDCCtrlHalInfo;

// /*
//  * SERVO_RMDX PARAMETERS
//  */

// #define MOTOR_SERVO_RMDX_POS_KP_COEF	0.00039062
// #define MOTOR_SERVO_RMDX_POS_KI_COEF	0.00003906
// #define MOTOR_SERVO_RMDX_VEL_KP_COEF	0.00039062
// #define MOTOR_SERVO_RMDX_VEL_KI_COEF	0.00003906
// #define MOTOR_SERVO_RMDX_CUR_KP_COEF	0.01171875
// #define MOTOR_SERVO_RMDX_CUR_KI_COEF	0.00039062

// #define MOTOR_SERVO_RMDX_POS_COEF		0.01
// #define MOTOR_SERVO_RMDX_POS_LIMIT		500         // deg
// #define MOTOR_SERVO_RMDX_VEL_COEF		0.01
// #define MOTOR_SERVO_RMDX_VEL_LIMIT		500         // deg/sec


// typedef struct _TMotor
// {
// 	/************ Below variables are initialized in table ************/
// 	U32 ulDeviceKey;

// 	U8 *pubName;
// 	TMotorType enType;
// 	U32 ulHalID;

//     TMotorStepCtrlHalInfo *pstStepCtrlHalParam;
//     TMotorBLDCCtrlHalInfo *pstBLDCCtrlHalParam;

//     BOOL bEnable;
//     BOOL bDir;
//     BOOL bStopMode;

// 	/******************************************************************/

//     // CW: (+), CCW: (-)
//     F32 fPosition;      // rad
//     F32 fVelocity;      // rad/sec
//     F32 fAccelaration;  // rad/sec^2

//     U32 ulState;

// 	/* STEP Parameters */
// 	U8 ubMakePulse;
// 	U8 ubActOption;
// 	U16 uwStepCount;

//     /* BLDC Parameters */
//     U16 uwTargetSpeed;
//     U16 uwSpeedRegister; // DRV8308 SPEED Value
//     U32 aulCurHallCount[MOTOR_BLDC_HALL_SENSOR_MAX]; // Hall Sensor
//     U32 aulOldHallCount[MOTOR_BLDC_HALL_SENSOR_MAX];
//     U32 ulCurWheelCount; // Encoder
//     U32 ulOldWheelCount;

//     /* Servo-RMDX Parameters */
//     U8 ubMotorCANID;
//     U32 ulCANDeviceKey;
//     TCANObserver stCANObserver;
//     U16 uwMaxSpeed;
//     TMotorPIDCtrlGain stPIDGain;

//     /* Common Interfaces */
//     void (*pfnInitialize)(struct _TMotor *pstMotor);
// 	void (*pfnStart)(struct _TMotor *pstMotor);
// 	void (*pfnChangeSpeed)(struct _TMotor *pstMotor, U32 ulVelocity);
// 	void (*pfnStartBackward)(struct _TMotor *pstMotor);
// 	/* STEP Interfaces */
//     void (*pfnSTEPSetEnable)(struct _TMotor *pstMotor, BOOL bValue, BOOL bActiveLow);
//     void (*pfnSTEPSetDirection)(struct _TMotor *pstMotor, BOOL bValue);
//     void (*pfnSTEPSetHold)(struct _TMotor *pstMotor, BOOL bValue, BOOL bActiveLow);
//     void (*pfnSTEPSetPulse)(struct _TMotor *pstMotor, BOOL bValue);
// 	void (*pfnSTEPStop)(struct _TMotor *pstMotor, BOOL bHoldStop, BOOL bActiveLow);
//     /* BLDC Interfaces */
//     void (*pfnBLDCSetEnable)(struct _TMotor *pstMotor, U8 ubEnable);
//     void (*pfnBLDCStop)(struct _TMotor *pstMotor);
//     void (*pfnBLDCOff)(struct _TMotor *pstMotor);
//     void (*pfnBLDCSetDirection)(struct _TMotor *pstMotor, U8 ubDirection);
//     void (*pfnBLDCSetBrake)(struct _TMotor *pstMotor, U8 ubBrake);
//     void (*pfnBLDCSetSpeed)(struct _TMotor *pstMotor, U16 uwValue);
//     U32 (*pfnBLDCGetWheelCount)(struct _TMotor *pstMotor);
//     void (*pfnBLDCSetWheelCount)(struct _TMotor *pstMotor, U32 ulValue);
//     /* Servo-RMDX Interfaces */
//     void (*pfnNotifiedByCAN)(U32 ulDeviceKey, U8* pubData, U16 uwLength);
//     void (*pfnRMDXEnable)(struct _TMotor *pstMotor);
//     void (*pfnRMDXStop)(struct _TMotor *pstMotor);
//     void (*pfnRMDXSetPosition)(struct _TMotor *pstMotor, S32 uwValue);
//     void (*pfnRMDXSetVelocity)(struct _TMotor *pstMotor, S32 uwValue);
//     void (*pfnRMDXShutdown)(struct _TMotor *pstMotor);
//     void (*pfnRMDXSetID)(struct _TMotor *pstMotor, U16 uwID);
// } TMotor;


/**
 * Device Information of ADCs
 */

typedef enum
{
	ADC_NAME_CURRENT1			    = DEVICE_ADC_KEY_BASE,
    ADC_NAME_CURRENT2,

    ADC_NAME_MAX,
    ADC_NAME_UNSPECIFIED       = ADC_NAME_MAX
} TADCName;

typedef enum
{
	ADC_CH_0,
	ADC_CH_1,
	ADC_CH_UNSPECIFIED
} TADCChannel;

typedef enum // 3-bit adress for 8ch multiplexer 
{
	ADC_MUX_ADDR_0,
	ADC_MUX_ADDR_1,
	ADC_MUX_ADDR_2,
	ADC_MUX_ADDR_3,
	ADC_MUX_ADDR_4,
	ADC_MUX_ADDR_5,
	ADC_MUX_ADDR_6,
	ADC_MUX_ADDR_7,
	ADC_MUX_ADDR_MAX
} TADCMuxAddress;


typedef struct _TADC
{
	/************ Below variables are initialized in table ************/
	U32 ulDeviceKey;
	U8 *pubName;
    TADCChannel eChannel;
    TADCMuxAddress eMuxAddr;
    //GPIO_TypeDef* pstHalBaseID;
	//U32 ulHalPinID;
    MutexId* pstOsMutex;

	/******************************************************************/

    U32 ulADCValue;
  
    void (*pfnInitialize)(struct _TADC *pstADC);
    U32 (*pfnGetValue)(struct _TADC *pstADC);

} TADC;


/**
 * Device Information of Encoders
 */

typedef enum
{
	ENCODER_NAME_MAIN               = DEVICE_ENCODER_KEY_BASE,
	
    ENCODER_NAME_MAX,
    ENCODER_NAME_UNSPECIFIED        = ENCODER_NAME_MAX
} TEncoderName;

typedef enum
{
	ENCODER_TYPE_MAGNETIC,
	ENCODER_TYPE_UNSPECIFIED
} TEncoderType;


typedef struct _TEncoder
{
    /************ Below variables are initialized in table ************/
    U32 ulDeviceKey;

	U8 *pubName;
    TEncoderType enType;
    U32 ulHalID;

    /* Servo-RMDX Parameters */
    U8 ubEncoderCANID;
    U32 ulCANDeviceKey;
    TCANObserver stCANObserver;

    /******************************************************************/

    S32 slCounter;
 
    void (*pfnInitialize)(struct _TEncoder *pstEncoder);
    void (*pfnSet)(struct _TEncoder *pstEncoder, S32 slCount);
    S32 (*pfnGet)(struct _TEncoder *pstEncoder);
    void  (*pfnReset)(struct _TEncoder *pstEncoder);
    /* Servo-RMDX Interfaces */
    void (*pfnNotifiedByCAN)(U32 ulDeviceKey, U8* pubData, U16 uwLength);

} TEncoder;


// /**
//  * Device Information of EEPROM
//  */


// typedef enum
// {
// 	EEPROM_NAME_RJB			= DEVICE_EEPROM_KEY_BASE,
//     EEPROM_NAME_MAX,
// 	EEPROM_NAME_UNSPECIFIED     = EEPROM_NAME_MAX
// } TEepromName;

// #define EEPROM_MEM_SIZE			2048//0x1ff
// #define EEPROM_SIZE				10 //6 128바이트  8 //512바이트 
// #define EEPROM_SKLOW			10//신호유지 카운트(1200=>100으로 감소) 20110216

// #define RJB_EEPROM_MEM_SIZE		2048//0x1ff
// #define RJB_EEPROM_SIZE			10 //6 128바이트  8 //512바이트 
// #define RJB_EEPROM_SKLOW		50//신호유지 카운트(1200=>100으로 감소) 20110216

// #define DEVFLASH_BLOCK_SIZE     512

// typedef enum 
// {
//     eEEPROM_ConfigType_CS,
//     eEEPROM_ConfigType_SCLK,
//     eEEPROM_ConfigType_DO,
//     eEEPROM_ConfigType_DI,
//     eEEPROM_ConfigType_UNDEFINED,
// } TEEPROMConfigType;

// typedef struct
// {
// 	GPIO_TypeDef* pstHalBaseID_SK;
// 	U32 ulHalPinID_SK;
// 	GPIO_TypeDef* pstHalBaseID_CS;
// 	U32 ulHalPinID_CS;
// 	GPIO_TypeDef* pstHalBaseID_DI;
// 	U32 ulHalPinID_DI;
// 	GPIO_TypeDef* pstHalBaseID_DO;
// 	U32 ulHalPinID_DO;
// } TEEPROMCtrlHalInfo;

// typedef struct _TEeprom
// {
// 	/************ Below variables are initialized in table ************/
//     U32 ulDeviceKey;
// 	U8 *pubName;
//     TEEPROMCtrlHalInfo* pstCtrlHalInfo;
//     MutexId* osmMutex;
// 	/******************************************************************/
 
//     void (*pfnInitialize)(struct _TEeprom *pstEeprom);

// } TEeprom;


/**
 * Device Information of Flash
 */

typedef enum
{
	FLASH_NAME_MAIN				= DEVICE_EEPROM_KEY_BASE,

    FLASH_NAME_MAX,
	FLASH_NAME_UNSPECIFIED     = FLASH_NAME_MAX
} TFlashName;


#define FLASH_SECTOR_SIZE		0x20000

#define FLASH_ADDRESS_RJB		0x08160000
#define FLASH_ADDRESS_RJP		0x08180000
#define FLASH_ADDRESS_ML		0x081A0000


typedef struct _TFlash
{
	/************ Below variables are initialized in table ************/
    U32 ulDeviceKey;
	U8 *pubName;
	/******************************************************************/
 
    void (*pfnInitialize)(struct _TFlash *pstFlash);

} TFlash;


/**
 * Device Information of SPI
 */

#define REG_WRITE				0x7F
#define REG_READ				0x80

typedef enum
{
	SPI_NAME_ENCODER		= DEVICE_SPI_KEY_BASE,
	
    SPI_NAME_MAX,
	SPI_NAME_UNSPECIFIED    = SPI_NAME_MAX
} TSPIName;

typedef enum 
{
    SPI_PORT_TYPE_CS,
    SPI_PORT_TYPE_SCLK,
    SPI_PORT_TYPE_DO,
    SPI_PORT_TYPE_DI,
    SPI_PORT_TYPE_UNDEFINED,
} TSPIPortType;

typedef struct _TSPI
{
    U32 ulDeviceKey;
	U8 *pubName;

    GPIO_TypeDef* ulHalBaseCS;
    U32 ulHalPinCS;
    GPIO_TypeDef* ulHalBaseCLK;
    U32 ulHalPinCLK;
    GPIO_TypeDef* ulHalBaseDO;
    U32 ulHalPinDO;
    GPIO_TypeDef* ulHalBaseDI;
    U32 ulHalPinDI;

    MutexId* osmMutex;
 
    void (*pfnInitialize)(struct _TSPI *pstSPI);

} TSPI;


/**
 * Device Information of Interrupt -> Temporary, it should define in other level (ex: Eng_Library, Eng_Infra, etc..)
 */


typedef enum 
{
    INTERRUPT_TYPE_TIMER,
    INTERRUPT_TYPE_EXTERNAL,
    INTERRUPT_TYPE_UNSECIFIED,
} TInterruptType;

typedef struct _TISR
{
	TInterruptType Type;
	U8 ubIndex;
	void (*pfnISR)(void);
	struct _TISR* pstPrev;
	struct _TISR* pstNext;
} TISR;




/**
 * Device Infomation of Uart
 */
typedef enum
{
	UART_NAME_MAIN					= DEVICE_UART_KEY_BASE,
	UART_NAME_STLINK_DEBUG,	
	UART_NAME_MAX,
	UART_NAME_UNSPECIFIED = UART_NAME_MAX
} TUARTName;

typedef enum
{
	UART_RX_TYPE_ISR,
	UART_RX_TYPE_POLLING,
	UART_RX_TYPE_UNSPECIFIED
} TUARTRxType;


typedef struct _TUART
{
	/************ Below variables are initialized in table ************/
	U32 ulDeviceKey;
	U8 *pubName;
	U32 ulHalID;
	TUARTRxType enRxType;
	
	//U32 ulChkSum;
	/******************************************************************/

//	U32 ulRxDate;
//	void *pubTxDate;

	void (*pfnInitialize)(struct _TUART *pstUART);
//	void (*pfnRxD)(struct _TUART *pstUART);
	U32 (*pfnRxD)(void);
	void (*pfnSendData)(struct _TUART *pstUART, U8 pubData[]);
	void (*pfnTxDBulk)(struct _TUART *pstUART, void *pubTxData);
	U32 (*pfnRequestCmd)(struct _TUART *pstUART);

	U8 ubData;
	
	TEngDrvId enDrvID;
	U32 ulHandleID;
	U32 ulVMID;
	void* pvOption;
	U8* pubData;
	U8 ubSize;
} TUART;



#endif /* __ENGDRV_DEVICETYPE_H__ */
