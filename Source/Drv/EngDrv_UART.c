#include <string.h>
#include "EngDrv_IF.h"
#include "EngCM_DriverConfig.h"
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
	EngHAL_UART_Transmit(pstUART->ulHalID, pubData, strlen(pubData));
}
