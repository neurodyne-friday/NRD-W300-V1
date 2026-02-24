/**
 * @file		EngHAL_SRAM_STM32F4xx.c
 * @brief		This main code for HAL Power Component Library.
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

#define __ENGHAL_SRAM_STM32F4xx_C__

#include "Eng_CommonType.h"
#include "EngHAL_SRAM_STM32F4xx.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* === 백업 저장 포맷 (BKP SRAM 4KB) ======================= */
#define BKPSRAM_SIZE           (4*1024U)
#define BKP_MAGIC              (0xB11CB11CU)

typedef struct __attribute__((packed)){
    uint32_t magic;   // 유효 마커
    uint32_t len;     // 페이로드 길이
    uint32_t crc;     // 간단 CRC32(아래 함수)
    uint32_t seq;     // 선택: 증가 카운터
} bkp_hdr_t;

/* BKP SRAM의 시작 주소 (장치 헤더에 정의됨) */
#define BKP_BASE_ADDR          ((uint8_t*)BKPSRAM_BASE)
#define BKP_HDR                ((bkp_hdr_t*)BKP_BASE_ADDR)
#define BKP_PAYLOAD            ((uint8_t*)(BKP_BASE_ADDR + sizeof(bkp_hdr_t)))
#define BKP_MAX_PAYLOAD        (BKPSRAM_SIZE - sizeof(bkp_hdr_t))

/* === 예시: 백업할 원본 데이터(약 4KB) ==================== */
#define CORE_DATA_MAX          (4096U - sizeof(bkp_hdr_t))
static uint8_t g_coreData[CORE_DATA_MAX];   // 앱이 평소에 채움
static uint32_t g_seq = 0;


/* === CRC32 (폴리노미얼 0xEDB88320, 간단 구현) ============ */
static uint32_t crc32_compute(const uint8_t *p, uint32_t len)
{
    uint32_t crc = 0xFFFFFFFFu;

    for (uint32_t i=0; i<len; ++i)
    {
        crc ^= p[i];
        for (int b=0; b<8; ++b)
        {
            crc = (crc>>1) ^ (0xEDB88320u & (-(int)(crc & 1)));
        }
    }
    
    return ~crc;
}

/**
  * @brief SRAM Interface Functions
  * @param None
  * @retval None
  */

void EngHAL_SRAM_Init_F4xx()
{
    /* PWR, BKPSRAM 클럭 */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_BKPSRAM_CLK_ENABLE();

    /* 백업 영역 쓰기 허용 */
    HAL_PWR_EnableBkUpAccess();

    /* Backup SRAM 레귤레이터 On (VBAT로 유지) */
    HAL_PWREx_EnableBkUpReg();

    /* Ready 비트 대기 */
    while ((PWR->CSR & PWR_CSR_BRR) == 0) { /* wait */ }
}


BOOL EngHAL_SRAM_Save_F4xx(const void *data, uint32_t len)
{
    if ((data == NULL) && (len > 0U))
    {
        return FALSE;
    }

    if (len > BKP_MAX_PAYLOAD)
    {
        return FALSE;
    }

    /* 헤더 잠시 비워두고 payload 먼저 복사 */
    memcpy(BKP_PAYLOAD, data, len);

    /* 헤더 작성 (마지막에 magic 기록) */
    bkp_hdr_t hdr = {0};
    hdr.len = len;
    hdr.seq = ++g_seq;
    hdr.crc = crc32_compute(BKP_PAYLOAD, len);

    /* 전원 강하 중간손상 방지: magic을 마지막에 씀 */
    BKP_HDR->magic = 0;              /* invalidate */
    BKP_HDR->len   = hdr.len;
    BKP_HDR->crc   = hdr.crc;
    BKP_HDR->seq   = hdr.seq;
    __DSB(); __ISB();
    BKP_HDR->magic = BKP_MAGIC;      /* validate */

    return TRUE;
}


BOOL EngHAL_SRAM_Load_F4xx(void *out, uint32_t bufsize, uint32_t *out_len, uint32_t *out_seq)
{
    if (!EngHAL_SRAM_IsValid_F4xx())
    {
        return FALSE;
    }

    uint32_t n = BKP_HDR->len;
    
    if (n > bufsize)
    {
        return FALSE;
    }

    if ((out == NULL) && (n > 0U))
    {
        return FALSE;
    }

    memcpy(out, BKP_PAYLOAD, n);
    
    if (out_len)
    {
         *out_len = n;
    }

    if (out_seq)
    {
        *out_seq = BKP_HDR->seq;
    } 

    return TRUE;
}


BOOL EngHAL_SRAM_IsValid_F4xx(void)
{
    if (BKP_HDR->magic != BKP_MAGIC)
    {
        return FALSE;
    }

    if (BKP_HDR->len > BKP_MAX_PAYLOAD)
    {
        return FALSE;
    }

    uint32_t crc = crc32_compute(BKP_PAYLOAD, BKP_HDR->len);
    return (crc == BKP_HDR->crc);
   
}