/**
 * @file		EngHAL_ETH_STM32F7xx.c
 * @brief		This main code for HAL Ethernet Component Library.
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


#define __ENGHAL_ETH_STM32F7XX_C__

#include "Eng_CommonType.h"
#include "EngHAL_ETH_STM32F7xx.h"
#include "lwip.h"
#include "lwip/api.h"
//#include "cmsis_os.h"

//#include "ethernetif.h"
//#include "lwip/ip.h"           // ip_pcb 및 관련 구조체 정의
//#include "lwip/ip4_addr.h"     // ip4_addr_t 정의
//#include "lwip/netif.h"
//#include "lan8742.h"

/**
  * @brief Ethernet Variables
  */

#define ETH_CHANNEL_COUNT   1
#define ETH_RX_DATA_SIZE    64 // able to support FD-CAN
#define ETH_TX_DATA_SIZE    64 // able to support FD-CAN

ETH_HandleTypeDef heth;
ETH_TxPacketConfig TxConfig;
extern struct netif gnetif;
struct netconn *conn;

#if defined ( __ICCARM__ ) /*!< IAR Compiler */
#pragma location=0x2007c000
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
#pragma location=0x2007c0a0
ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __CC_ARM )  /* MDK ARM Compiler */

__attribute__((at(0x2007c000))) ETH_DMADescTypeDef  DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
__attribute__((at(0x2007c0a0))) ETH_DMADescTypeDef  DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

#elif defined ( __GNUC__ ) /* GNU Compiler */

ETH_DMADescTypeDef DMARxDscrTabSection[ETH_RX_DESC_CNT] __attribute__((section(".RxDecripSection"))); /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTabSection[ETH_TX_DESC_CNT] __attribute__((section(".TxDecripSection"))); /* Ethernet Tx DMA Descriptors */
#endif

#define SERVER_IP_ADDR  "192.168.0.50"  // 연결할 TCP 서버의 IP 주소
#define SERVER_PORT     5005             // 서버 포트 번호
#define ETH_RECONNECT_INTERVAL_MS  (1000U)
#define ETH_STATUS_LOG_INTERVAL_MS (5000U)

const TIPv4Addr g_stServerIP = {192,168,0,50};
const U32 g_ulServerPort = 5005;
static U32 g_ulEthNextReconnectTick = 0;
static U32 g_ulEthConnectAttemptCount = 0;
static U32 g_ulEthConnectSuccessCount = 0;
static U32 g_ulEthConnectFailCount = 0;
static U32 g_ulEthTxFailCount = 0;
static U32 g_ulEthRxFailCount = 0;
static S32 g_slEthLastError = 0;
static U32 g_ulEthLastStatusLogTick = 0;
//struct dhcp *gdhcp;
//uint32_t gphy_status;

// 송신할 데이터 및 수신할 데이터를 위한 버퍼
uint8_t ethTxData[] = "Hello from NUCLEO-F767ZI via TCP/IP!";
uint8_t ethRxData[100];  // 수신 데이터 버퍼


typedef struct _THalETHRxBuffer
{
	U8 ubLength;
	U8 pubData[ETH_RX_DATA_SIZE];
} THalETHRxBuffer;

typedef struct _THalETHTxBuffer
{
	U8 ubLength;
	U8 pubData[ETH_TX_DATA_SIZE];
} THalETHTxBuffer;

THalETHRxBuffer astHalETHRxBuffer[ETH_CHANNEL_COUNT];
THalETHTxBuffer astHalETHTxBuffer[ETH_CHANNEL_COUNT];

static void EngHAL_ETH_LogStatus_F7xx(void)
{
    U32 ulNowTick = HAL_GetTick();

    if ((g_ulEthLastStatusLogTick == 0U)
        || ((ulNowTick - g_ulEthLastStatusLogTick) >= ETH_STATUS_LOG_INTERVAL_MS))
    {
        g_ulEthLastStatusLogTick = ulNowTick;
        DBG_UART(ENG_DBG_STRING"ETH status: try=%lu ok=%lu connFail=%lu txFail=%lu rxFail=%lu lastErr=%ld",
                 ENG_TICK, "EngChip",
                 g_ulEthConnectAttemptCount,
                 g_ulEthConnectSuccessCount,
                 g_ulEthConnectFailCount,
                 g_ulEthTxFailCount,
                 g_ulEthRxFailCount,
                 g_slEthLastError);
    }
}


BOOL EngHAL_ETH_Init_F7xx(THalETHPorting *pstHalPorting)
{
    ETH_HandleTypeDef* pEthHandle = NULL;
    static uint8_t MACAddr[6];

    if(pstHalPorting == NULL)
        return FALSE;

    if(pstHalPorting->ulChannel == 0)
    {
        pEthHandle = &heth;
        pEthHandle->Instance = ETH;
    }
    else
    {
        return FALSE;
    }

    if(pstHalPorting->enLWIPOnOff == HAL_ETH_LWIP_OFF)
    {
        pEthHandle->Init.MACAddr = &MACAddr[0];
        pEthHandle->Init.MediaInterface = HAL_ETH_RMII_MODE;
        pEthHandle->Init.TxDesc = DMATxDscrTabSection;
        pEthHandle->Init.RxDesc = DMARxDscrTabSection;
        pEthHandle->Init.RxBuffLen = 1524;

        if (HAL_ETH_Init(pEthHandle) != HAL_OK)
        {
            Error_Handler();
        }

        memset(&TxConfig, 0 , sizeof(ETH_TxPacketConfig));
        TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM | ETH_TX_PACKETS_FEATURES_CRCPAD;
        TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
        TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;

        HAL_ETH_MspInit(pEthHandle);
    }
}

void EngHAL_ETH_Connect_Entry_F7xx(THalETHPorting *pstHalPorting)
{
    ip_addr_t server_ip;
    err_t err = ERR_ARG;

    if(pstHalPorting == NULL)
    {
        return;
    }

    EngHAL_ETH_LWIP_Init_F7xx(pstHalPorting);

    IP4_ADDR(&server_ip, g_stServerIP.ubAddr0, g_stServerIP.ubAddr1, g_stServerIP.ubAddr2, g_stServerIP.ubAddr3);
    g_ulEthConnectAttemptCount++;

    if (conn != NULL)
    {
        netconn_close(conn);
        netconn_delete(conn);
        conn = NULL;
    }

    conn = netconn_new(NETCONN_TCP);
    
    if (conn != NULL)
    {
        uint32_t src_ip = netif_ip4_addr(&gnetif)->addr;
        uint32_t dst_ip = ip4_addr_get_u32(ip_2_ip4(&server_ip));
        uint32_t subnet_mask = gnetif.netmask.addr;

        if (!netif_is_up(&gnetif)) 
        {
            DBG_UART(ENG_DBG_STRING"Network interface is not activated", ENG_TICK, "EngChip");
            netif_set_up(&gnetif);
            DBG_UART(ENG_DBG_STRING"Network interface is now activated", ENG_TICK, "EngChip");
        }

        DBG_UART(ENG_DBG_STRING"Connecting to %s:%d \n", ENG_TICK, "EngChip", ip4addr_ntoa(&server_ip), SERVER_PORT);
        err = netconn_connect(conn, &server_ip, SERVER_PORT);

        if ((src_ip & subnet_mask) != (dst_ip & subnet_mask)) 
        {
            DBG_UART(ENG_DBG_STRING"Src and dest are in different subnets", ENG_TICK, "EngChip");
            //conn->pcb.ip->local_ip.addr = gnetif.ip_addr.addr;
            //conn->pcb.ip->remote_ip.addr = gnetif.gw.addr;  // 게이트웨이를 통해 연결
        }
        else
        {
            DBG_UART(ENG_DBG_STRING"Confirmed to source and destination are in same subnets", ENG_TICK, "EngChip");
        }

        DBG_UART(ENG_DBG_STRING"Local IP: %s", ENG_TICK, "EngChip", ip4addr_ntoa(netif_ip4_addr(&gnetif)));
        DBG_UART(ENG_DBG_STRING"Remote IP: %s", ENG_TICK, "EngChip", ip4addr_ntoa(ip_2_ip4(&server_ip)));
        
        if (err == ERR_OK)
        {
            DBG_UART(ENG_DBG_STRING"Assigned IP: %s", ENG_TICK, "EngChip", ip4addr_ntoa(netif_ip4_addr(&gnetif)));
            g_ulEthConnectSuccessCount++;
            g_slEthLastError = ERR_OK;
            g_ulEthNextReconnectTick = 0;
        } 
        else 
        {
            DBG_UART(ENG_DBG_STRING"Connection failed with error: %d", ENG_TICK, "EngChip", err);
            g_ulEthConnectFailCount++;
            g_slEthLastError = (S32)err;
            netconn_close(conn);
            netconn_delete(conn);
            conn = NULL;
            g_ulEthNextReconnectTick = HAL_GetTick() + ETH_RECONNECT_INTERVAL_MS;
        }
    } 
    else 
    {
        DBG_UART(ENG_DBG_STRING"Failed to create socket", ENG_TICK, "EngChip", err);
        g_ulEthConnectFailCount++;
        g_slEthLastError = (S32)ERR_MEM;
        g_ulEthNextReconnectTick = HAL_GetTick() + ETH_RECONNECT_INTERVAL_MS;
    }

    EngHAL_ETH_LogStatus_F7xx();
}

void EngHAL_ETH_Connect_Activity_F7xx(THalETHPorting *pstHalPorting)
{
    struct netbuf *buf = NULL;
    err_t err;

    if (pstHalPorting == NULL)
    {
        return;
    }

    if (conn == NULL)
    {
        if ((g_ulEthNextReconnectTick == 0U) || (HAL_GetTick() >= g_ulEthNextReconnectTick))
        {
            DBG_UART(ENG_DBG_STRING"TCP reconnect attempt", ENG_TICK, "EngChip");
            EngHAL_ETH_Connect_Entry_F7xx(pstHalPorting);
            g_ulEthNextReconnectTick = HAL_GetTick() + ETH_RECONNECT_INTERVAL_MS;
        }

        EngHAL_ETH_LogStatus_F7xx();

        osDelay(1000);
        return;
    }
    
    err = netconn_write(conn, ethTxData, sizeof(ethTxData), NETCONN_COPY);
    if (err != ERR_OK)
    {
        DBG_UART(ENG_DBG_STRING"Error sending data: %d", ENG_TICK, "EngChip", err);
        g_ulEthTxFailCount++;
        g_slEthLastError = (S32)err;
        netconn_close(conn);
        netconn_delete(conn);
        conn = NULL;
        g_ulEthNextReconnectTick = HAL_GetTick() + ETH_RECONNECT_INTERVAL_MS;
        EngHAL_ETH_LogStatus_F7xx();
        osDelay(1000);
        return;
    }

    err = netconn_recv(conn, &buf);
    if (err == ERR_OK)
    {
        void *dataptr;
        u16_t len;

        if (netbuf_data(buf, &dataptr, &len) == ERR_OK) 
        {
            u16_t copyLen = len;
            if (copyLen >= sizeof(ethRxData))
            {
                copyLen = (u16_t)(sizeof(ethRxData) - 1U);
            }

            memcpy(ethRxData, dataptr, copyLen);
            ethRxData[copyLen] = '\0';

            //printf("Received: %s\n", ethRxData);
            DBG_UART(ENG_DBG_STRING"Received: %s", ENG_TICK, "EngChip", ethRxData);
        }

        netbuf_delete(buf);
    } 
    else 
    {
        //printf("Error receiving data: %d\n", err);
        DBG_UART(ENG_DBG_STRING"Error receiving data: %d", ENG_TICK, "EngChip", err);
        g_ulEthRxFailCount++;
        g_slEthLastError = (S32)err;
        netconn_close(conn);
        netconn_delete(conn);
        conn = NULL;
        g_ulEthNextReconnectTick = HAL_GetTick() + ETH_RECONNECT_INTERVAL_MS;
    }

    EngHAL_ETH_LogStatus_F7xx();

    osDelay(1000); 
}

void EngHAL_ETH_Connect_Exit_F7xx(THalETHPorting *pstHalPorting)
{
    (void)pstHalPorting;

    if (conn != NULL)
    {
        netconn_close(conn);
        netconn_delete(conn);
        conn = NULL;
    }

    g_ulEthNextReconnectTick = 0;
    g_ulEthLastStatusLogTick = 0;
}

void EngHAL_ETH_Transmit_F7xx(THalETHPorting *pstHalPorting, U8* pubData, U16 uwLength)
{
}


/* 
 * Internal functions 
 */

void EngHAL_ETH_LWIP_Init_F7xx(THalETHPorting *pstHalPorting)
{
    ETH_HandleTypeDef* pEthHandle = NULL;

    if(pstHalPorting->enLWIPOnOff == HAL_ETH_LWIP_ON)
    {
        MX_LWIP_Init();

        if(pstHalPorting->enDHCPOnOff == HAL_ETH_DHCP_ON)
        {
            dhcp_start(&gnetif);
        }
    }
}

void EngHAL_ETH_SetIP_F7xx(THalETHPorting *pstHalPorting)
{
    ip_addr_t ipaddr, netmask, gw;
    TIPv4Addr* pstIPAddr;
    TIPv4Addr* pstNMAddr;
    TIPv4Addr* pstGWAddr;

    if(pstHalPorting == NULL)
        return FALSE;

    pstIPAddr = &pstHalPorting->stIPAddr;
    pstNMAddr = &pstHalPorting->stNetMaskAddr;
    pstGWAddr = &pstHalPorting->stGateWayAddr;

    // Static IP Address, Subnet Mask, Gateway configuration
    IP4_ADDR(&ipaddr, pstIPAddr->ubAddr0, pstIPAddr->ubAddr1, pstIPAddr->ubAddr2, pstIPAddr->ubAddr3);  // IP Address
    IP4_ADDR(&netmask, pstNMAddr->ubAddr0, pstNMAddr->ubAddr1, pstNMAddr->ubAddr2, pstNMAddr->ubAddr3); // Subnet Mask
    IP4_ADDR(&gw, pstGWAddr->ubAddr0, pstGWAddr->ubAddr1, pstGWAddr->ubAddr2, pstGWAddr->ubAddr3);      // Default Gateway

    netif_set_addr(&gnetif, &ipaddr, &netmask, &gw);
    netif_set_up(&gnetif);

    DBG_UART(ENG_DBG_STRING"IP address set to: %s", ENG_TICK, "EngHAL", ip4addr_ntoa(netif_ip4_addr(&gnetif)));
    DBG_UART(ENG_DBG_STRING"Gateway set to: %s \n", ENG_TICK, "EngHAL", ip4addr_ntoa(&gw));
}
