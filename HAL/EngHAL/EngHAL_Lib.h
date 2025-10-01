/**
 * @file		EngHAL_Lib.h
 * @brief		This main code for HAL Component Library.
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
 
#ifndef __ENGHAL_LIB_H__
#define __ENGHAL_LIB_H__

#undef EXTERN
#ifdef __ENGHAL_LIB_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Eng_CommonType.h"
#include "EngHAL_Types.h"


EXTERN BOOL EngHAL_LibraryEntry(void);
EXTERN void EngHAL_Core_Init(void);

/* EngChip - ADC Interface */
EXTERN void EngHAL_ADC_Init(U32 ulHalName);
EXTERN U16 EngHAL_ADC_GetValue(U32 ulHalName);
void EngHAL_ADC_GetCurrentRaw(uint16_t *pIa, uint16_t *pIb, uint16_t *pIc); // 임시 구현
EXTERN void EngHAL_ADC_RegisterCallback(U32 ulEventId, void (*pfnCallback)(void)); // 임시 구현 - 추후 Observer 패턴 표준으로 변경 예정

/* EngChip - PWM Interface */
EXTERN void EngHAL_PWM_Init(U32 ulHalName);
EXTERN void EngHAL_PWM_SetDuty(U32 ulHalName, float fDuty);

/* EngChip - CAN Interface */
EXTERN void EngHAL_CAN_Init(U32 ulHalName);
EXTERN void EngHAL_CAN_EnableInterrupt(U32 ulHalName);
EXTERN void EngHAL_CAN_DisableInterrupt(U32 ulHalName);
EXTERN void EngHAL_CAN_RegisterCallback(U32 ulEventId, void (*pfnCallback)(void)); // 임시 구현 - 추후 Observer 패턴 표준으로 변경 예정
EXTERN BOOL EngHAL_CAN_IsRxFIFOEmpty(U32 ulHalName);
EXTERN BOOL EngHAL_CAN_IsTxFIFOEmpty(U32 ulHalName);
EXTERN BOOL EngHAL_CAN_IsTxFIFOFull(U32 ulHalName);
EXTERN void EngHAL_CAN_Transmit(U32 ulHalName, U8 pubData[], U8 ubLength);
EXTERN void EngHAL_CAN_Receive(U32 ulHalName);
EXTERN void EngHAL_CAN_RxFIFOMsgPendingCallback(U32 ulHalName);
EXTERN void EngHAL_CAN_PutByte(U32 ulHalName, U8 ubData);
EXTERN void EngHAL_CAN_SendBytes(U32 ulHalName);
EXTERN U8 EngHAL_CAN_GetByte(U32 ulHalName);
EXTERN U32 EngHAL_CAN_GetRxFifoFillLevel(U32 ulHalName);

/* EngChip - UART Interface */
EXTERN void EngHAL_UART_Init(U32 ulHalName);
EXTERN void EngHAL_UART_Transmit(U32 ulHalName, U8 pubData[], U16 uwLength);
EXTERN void EngHAL_UART_Receive(U32 ulHalName);
EXTERN void EngHAL_UART_EnableInterrupt(U32 ulHalName);
EXTERN void EngHAL_UART_DisableInterrupt(U32 ulHalName);
EXTERN BOOL EngHAL_UART_IsRxFIFOEmpty(U32 ulHalName);
EXTERN BOOL EngHAL_UART_IsTxFIFOEmpty(U32 ulHalName);
EXTERN void EngHAL_UART_SendByte(U32 ulHalName, U8 ubData);
EXTERN U8 EngHAL_UART_GetByte(U32 ulHalName);
EXTERN void EngHAL_UART_RegisterCallback(U32 ulEventId, void (*pfnCallback)(void)); // 임시 구현 - 추후 Observer 패턴 표준으로 변경 예정

/* EngChip - Ethernet Interface */
EXTERN BOOL EngHAL_ETH_Init(U32 ulHalName);
EXTERN void EngHAL_ETH_Connect_Entry(U32 ulHalName);
EXTERN void EngHAL_ETH_Connect_Activity(U32 ulHalName);
EXTERN void EngHAL_ETH_Connect_Exit(U32 ulHalName);
EXTERN void EngHAL_ETH_Transmit(U32 ulHalName, U8 pubData[], U16 uwLength);

/* EngChip - RTC Interface */
EXTERN void EngHAL_RTC_Init(void);
EXTERN void EngHAL_RTC_GetDateTime(THalRTCData* pstRTCData);

/* EngChip - SRAM Interface */
EXTERN void EngHAL_SRAM_Init(void);
EXTERN BOOL EngHAL_SRAM_Save(const void *data, uint32_t len);
EXTERN BOOL EngHAL_SRAM_Load(void *out, uint32_t bufsize, uint32_t *out_len, uint32_t *out_seq);
EXTERN BOOL EngHAL_SRAM_IsValid(void);

/* EngChip - SPI Interface */
EXTERN void EngHAL_SPI_Init(U32 ulHalName);
EXTERN BOOL  EngHAL_SPI_MA702_ReadRaw12(U32 ulHalName, uint16_t *puwAngle12);
EXTERN float EngHAL_SPI_MA702_ReadDeg(U32 ulHalName);
EXTERN float EngHAL_SPI_MA702_ReadRad(U32 ulHalName);
EXTERN BOOL  EngHAL_SPI_MA702_ReadReg(U32 ulHalName, uint8_t ubAddr5, uint8_t *pubVal);
EXTERN BOOL  EngHAL_SPI_MA702_WriteReg(U32 ulHalName, uint8_t ubAddr5, uint8_t ubVal, uint8_t *pubEcho);

/* EngChip - I2C Interface */
EXTERN void EngHAL_I2C_Init(U32 ulHalName);
EXTERN BOOL EngHAL_I2C_MemRead(U32 ulHalName, U16 devAddr7b, U16 memAddr, U16 memAddrSize, U8 *pData, U16 len, U32 timeout);
EXTERN BOOL EngHAL_I2C_MemWrite(U32 ulHalName, U16 devAddr7b, U16 memAddr, U16 memAddrSize, const U8 *pData, U16 len, U32 timeout);
EXTERN BOOL EngHAL_I2C_Read(U32 ulHalName, U16 devAddr7b, U8 *pData, U16 len, U32 timeout);
EXTERN BOOL EngHAL_I2C_Write(U32 ulHalName, U16 devAddr7b, const U8 *pData, U16 len, U32 timeout);
/* Optional helpers for AS5600 */
EXTERN BOOL EngHAL_I2C_AS5600_ReadRawAngle(U32 ulHalName, U16 *pRaw);
EXTERN BOOL EngHAL_I2C_AS5600_ReadAngle12(U32 ulHalName, U16 *pAngle12);
EXTERN void EngHAL_I2C_AS5600_Scan(U32 ulHalName);

/* EngChip - Power Interface */
EXTERN void EngHAL_PWR_Init(void);
EXTERN void EngHAL_PWR_RegisterCallback(U32 ulEventId, void (*pfnCallback)(void)); // 임시 구현 - 추후 Observer 패턴 표준으로 변경 예정

/* EngChip - USB_OTG Interface */
EXTERN void EngHAL_USB_OTG_FS_PCD_Init(void);


/* EngChip - Delay Timer Interface */
EXTERN void EngHAL_OS_Delay(uint32_t ticks);


/**
*	Common Function
*/

EXTERN THalPWMPorting* EngHAL_FindHalPWM(U32 ulHalName);
EXTERN THalADCPorting* EngHAL_FindHalADC(U32 ulHalName);
EXTERN THalCANPorting* EngHAL_FindHalCAN(U32 ulHalName);
EXTERN THalUARTPorting* EngHAL_FindHalUART(U32 ulHalName);
EXTERN THalSPIPorting* EngHAL_FindHalSPI(U32 ulHalName);
EXTERN THalI2CPorting* EngHAL_FindHalI2C(U32 ulHalName);

#endif //__ENGHAL_LIB_H__