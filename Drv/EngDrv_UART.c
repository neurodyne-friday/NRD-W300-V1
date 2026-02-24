#include <string.h>
#include "EngDrv_IF.h"
#include "EngCM_DriverConfig.h"
#include "EngCM_DebugConfig.h"
#include "EngDrv_UART.h"

#define __ENGDRV_UART_C__


void EngDrv_UART_Create()
{
 	TUART* pstInstance = NULL;
    U8 ubCount = sizeof(s_astDeviceUARTTbl) / sizeof(TUART);

    for(U8 ubIndex = 0; ubIndex < ubCount; ubIndex++)
    {
        pstInstance = &s_astDeviceUARTTbl[ubIndex];

        pstInstance->pfnInitialize = EngDrv_UART_Initialize;
		pstInstance->pfnSendData = EngDrv_UART_SendData;
    } 	
}

void EngDrv_UART_Initialize(TUART *pstUART)
{

}

void EngDrv_UART_SendData(TUART *pstUART, U8 pubData[])
{
    U32 ulLength = 0;

    if ((pstUART == NULL) || (pubData == NULL))
    {
        return;
    }

    ulLength = strnlen((const char *)pubData, C_ENG_LOG_1LINE_BUFF_SIZE - 1U);
    if (ulLength == 0U)
    {
        return;
    }

    EngHAL_UART_Transmit(pstUART->ulHalID, pubData, (U16)ulLength);
}
