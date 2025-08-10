/**
 * @file        EngDrv_IF.c
 * @brief       This is interface file for drivers
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
 * @date		21/02/2024(D/M/Y)
 * @version		V0.1
 */


#define __ENGDRV_IF_C__  

#include "EngCM_DriverConfig.h"


void EngDrv_IF_Create()
{
    EngDrv_CAN_Create();
    // EngDrv_Sensor_Create();
    // EngDrv_Motor_Create();
    EngDrv_ADC_Create();
    EngDrv_Encoder_Create();
    // EngDrv_EEPROM_Create();
    // EngDrv_Flash_Create();
    // EngDrv_SPI_Create();
    EngDrv_UART_Create();
}

void EngDrv_IF_Configuration()
{
    EngDrv_Sensor_Configuration();
    EngDrv_ADC_Configuration();
    // EngDrv_Solenoid_Configuration();
    // EngDrv_EEPROM_Configuration();
    // EngDrv_Flash_Configuration();
    // EngDrv_SPI_Configuration();
}


void EngDrv_IF_Initialize()
{
    TCAN* pstCAN = NULL;
    for(U32 ulDeviceKey = DEVICE_CAN_KEY_BASE; ulDeviceKey < CAN_NAME_MAX; ulDeviceKey++)
    {
        pstCAN = EngDrv_IF_GetCAN(ulDeviceKey);
        if(pstCAN != NULL)
        {
            pstCAN->pfnInitialize(pstCAN);
        }
    }
    
    /*
    TSensor* pstSensor = NULL;
    for(U32 ulDeviceKey = DEVICE_SENSOR_KEY_BASE; ulDeviceKey < SENSOR_NAME_MAX; ulDeviceKey++)
    {
        pstSensor = EngDrv_IF_GetSensor(ulDeviceKey);
        if(pstSensor != NULL)
        {
            pstSensor->pfnInitialize(pstSensor);
        }
    }
    EngDrv_Sensor_InitializeAll();
    */
    
    TADC* pstADC = NULL;
    for(U32 ulDeviceKey = DEVICE_ADC_KEY_BASE; ulDeviceKey < ADC_NAME_MAX; ulDeviceKey++)
    {
        pstADC = EngDrv_IF_GetADC(ulDeviceKey);
        if(pstADC != NULL)
        {
            pstADC->pfnInitialize(pstADC);
        }
    }

    TEncoder* pstEncoder = NULL;
    for(U32 ulDeviceKey = DEVICE_ENCODER_KEY_BASE; ulDeviceKey < ENCODER_NAME_MAX; ulDeviceKey++)
    {
        pstEncoder = EngDrv_IF_GetEncoder(ulDeviceKey);
        if(pstEncoder != NULL)
        {
            pstEncoder->pfnInitialize(pstEncoder);
        }
    }

    /*
    TEeprom* pstEeprom = NULL;
    for(U32 ulDeviceKey = DEVICE_EEPROM_KEY_BASE; ulDeviceKey < EEPROM_NAME_MAX; ulDeviceKey++)
    {
        pstEeprom = EngDrv_IF_GetEeprom(ulDeviceKey);
        if(pstEeprom != NULL)
        {
            pstEeprom->pfnInitialize(pstEeprom);
        }
    }
    */

    // TFlash* pstFlash = NULL;
    // for(U32 ulDeviceKey = DEVICE_FLASH_KEY_BASE; ulDeviceKey < FLASH_NAME_MAX; ulDeviceKey++)
    // {
    //     pstEeprom = EngDrv_IF_GetFlash(ulDeviceKey);
    //     if(pstFlash != NULL)
    //     {
    //         pstFlash->pfnInitialize(pstFlash);
    //     }
    // }
    // EngDrv_Flash_Initialize();

    /*
    TSolenoid* pstSolenoid = NULL;
    for(U32 ulDeviceKey = DEVICE_SOLENOID_KEY_BASE; ulDeviceKey < SOLENOID_NAME_MAX; ulDeviceKey++)
    {
        pstSolenoid = EngDrv_IF_GetSolenoid(ulDeviceKey);
        if(pstSolenoid != NULL)
        {
            pstSolenoid->pfnInitialize(pstSolenoid);
        }
    }
    */

   /*
    TSPI* pstSPI = NULL;
    for(U32 ulDeviceKey = DEVICE_SPI_KEY_BASE; ulDeviceKey < SPI_NAME_MAX; ulDeviceKey++)
    {
        pstSPI = EngDrv_IF_GetSPI(ulDeviceKey);
        if(pstSPI != NULL)
        {
            pstSPI->pfnInitialize(pstSPI);
        }
    }
    */

    TUART* pstUART = NULL;
    for(U32 ulDeviceKey = DEVICE_UART_KEY_BASE; ulDeviceKey < UART_NAME_MAX; ulDeviceKey++)
    {
        pstUART = EngDrv_IF_GetUART(ulDeviceKey);
        if(pstUART != NULL)
        {
            pstUART->pfnInitialize(pstUART);
        }
    }
}


// will be upgrade this function
void *EngDrv_IF_GetDevice(U32 ulDeviceKey)
{
    void *pvEntry = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_ADC_KEY_BASE && ulDeviceKey < DEVICE_CAN_KEY_BASE)
    {
        return NULL;//(void*)EngDrv_IF_GetModule(ulDeviceKey);
    }
    else if(ulDeviceKey >= DEVICE_CAN_KEY_BASE && ulDeviceKey < DEVICE_MOTOR_KEY_BASE)
    {
        return NULL;//(void*)EngDrv_IF_GetCAN(ulDeviceKey);    
    }
    else if(ulDeviceKey >= DEVICE_SENSOR_KEY_BASE && ulDeviceKey < DEVICE_UART_KEY_BASE)
    {
        return NULL;//(void*)EngDrv_IF_GetSensor(ulDeviceKey);
    }

    return pvEntry;
}

TCAN *EngDrv_IF_GetCAN(U32 ulDeviceKey)
{
    TCAN *pstCAN = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_CAN_KEY_BASE && ulDeviceKey < CAN_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < DEVICE_MOTOR_KEY_BASE - DEVICE_CAN_KEY_BASE; ulIndex++)
        {
            pstCAN = &s_astDeviceCanTbl[ulIndex];
            if(ulDeviceKey == pstCAN->ulDeviceKey)
            {
                return pstCAN;
            }
        }
    }

    return NULL;
}

TETH *EngDrv_IF_GetETH(U32 ulDeviceKey)
{
    TETH *pstETH = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_ETH_KEY_BASE && ulDeviceKey < ETH_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < ETH_NAME_MAX - DEVICE_ETH_KEY_BASE; ulIndex++)
        {
            pstETH = &s_astDeviceETHTbl[ulIndex];
            if(ulDeviceKey == pstETH->ulDeviceKey)
            {
                return pstETH;
            }
        }
    }

    return NULL;    
}

TSensor *EngDrv_IF_GetSensor(U32 ulDeviceKey)
{
    TSensor *pstSensor = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_SENSOR_KEY_BASE && ulDeviceKey < SENSOR_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < SENSOR_NAME_MAX - DEVICE_SENSOR_KEY_BASE; ulIndex++)
        {
            pstSensor = &s_astDeviceSensorTbl[ulIndex];
            if(ulDeviceKey == pstSensor->ulDeviceKey)
            {
                return pstSensor;
            }
        }
    }

    return NULL;
}

TMotor *EngDrv_IF_GetMotor(U32 ulDeviceKey)
{
    TMotor *pstMotor = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_MOTOR_KEY_BASE && ulDeviceKey < MOTOR_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < DEVICE_SENSOR_KEY_BASE - DEVICE_MOTOR_KEY_BASE; ulIndex++)
        {
            pstMotor = &s_astDeviceMotorTbl[ulIndex];
            if(ulDeviceKey == pstMotor->ulDeviceKey)
            {
                return pstMotor;
            }
        }
    }

    return NULL;
}

TADC *EngDrv_IF_GetADC(U32 ulDeviceKey)
{
    TADC *pstADC = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_ADC_KEY_BASE && ulDeviceKey < ADC_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < ADC_NAME_MAX - DEVICE_ADC_KEY_BASE; ulIndex++)
        {
            pstADC = &s_astDeviceADCTbl[ulIndex];
            if(ulDeviceKey == pstADC->ulDeviceKey)
            {
                return pstADC;
            }
        }
    }

    return NULL;
}


TSolenoid *EngDrv_IF_GetSolenoid(U32 ulDeviceKey)
{
    TSolenoid *pstSolenoid = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_SOLENOID_KEY_BASE && ulDeviceKey < SOLENOID_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < DEVICE_SIO_KEY_BASE - DEVICE_SOLENOID_KEY_BASE; ulIndex++)
        {
            pstSolenoid = &s_astDeviceSolenoidTbl[ulIndex];
            if(ulDeviceKey == pstSolenoid->ulDeviceKey)
            {
                return pstSolenoid;
            }
        }
    }

    return NULL;   
}

TEncoder *EngDrv_IF_GetEncoder(U32 ulDeviceKey)
{
    TEncoder *pstEncoder = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_ENCODER_KEY_BASE && ulDeviceKey < ENCODER_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < ENCODER_NAME_MAX - DEVICE_ENCODER_KEY_BASE; ulIndex++)
        {
            pstEncoder = &s_astDeviceEncoderTbl[ulIndex];
            if(ulDeviceKey == pstEncoder->ulDeviceKey)
            {
                return pstEncoder;
            }
        }
    }

    return NULL;
}

TEeprom *EngDrv_IF_GetEeprom(U32 ulDeviceKey)
{
    TEeprom *pstEeprom = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_EEPROM_KEY_BASE && ulDeviceKey < EEPROM_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < DEVICE_SIO_KEY_BASE - DEVICE_EEPROM_KEY_BASE; ulIndex++)
        {
            pstEeprom = &s_astDeviceEepromTbl[ulIndex];
            if(ulDeviceKey == pstEeprom->ulDeviceKey)
            {
                return pstEeprom;
            }
        }
    }

    return NULL;
}

// TFlash *EngDrv_IF_GetFlash(U32 ulDeviceKey)
// {
//     TFlash *pstFlash = NULL;
//     U32 ulIndex = 0;

//     if(ulDeviceKey >= DEVICE_FLASH_KEY_BASE && ulDeviceKey < FLASH_NAME_MAX)
//     {
//         for(ulIndex = 0; ulIndex < FLASH_NAME_MAX - DEVICE_FLASH_KEY_BASE; ulIndex++)
//         {
//             pstFlash = &s_astDeviceFlashTbl[ulIndex];
//             if(ulDeviceKey == pstFlash->ulDeviceKey)
//             {
//                 return pstFlash;
//             }
//         }
//     }

//     return NULL;
// }

TSPI* EngDrv_IF_GetSPI(U32 ulDeviceKey)
{
    TSPI *pstSPI = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_SPI_KEY_BASE && ulDeviceKey < SPI_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < DEVICE_POWER_KEY_BASE - DEVICE_SPI_KEY_BASE; ulIndex++)
        {
            pstSPI = &s_astDeviceSPITbl[ulIndex];
            if(ulDeviceKey == pstSPI->ulDeviceKey)
            {
                return pstSPI;
            }
        }
    }

    return NULL;
}

TUART* EngDrv_IF_GetUART(U32 ulDeviceKey)
{
    TUART *pstUART = NULL;
    U32 ulIndex = 0;

    if(ulDeviceKey >= DEVICE_UART_KEY_BASE && ulDeviceKey < UART_NAME_MAX)
    {
        for(ulIndex = 0; ulIndex < UART_NAME_MAX - DEVICE_UART_KEY_BASE; ulIndex++)
        {
            pstUART = &s_astDeviceUARTTbl[ulIndex];
            if(ulDeviceKey == pstUART->ulDeviceKey)
            {
                return pstUART;
            }
        }
    }

    return NULL;
}


TCAN *EngDrv_IF_FindCANByHalName(U32 ulHalName)
{
    TCAN *pstCAN = NULL;
    U32 ulIndex = 0;

    for(ulIndex = 0; ulIndex < CAN_NAME_MAX - DEVICE_CAN_KEY_BASE; ulIndex++)
    {
        pstCAN = &s_astDeviceCanTbl[ulIndex];
        if(pstCAN->ulHalID == ulHalName)
        {
            return pstCAN;
        }
    }

    return NULL;
}
