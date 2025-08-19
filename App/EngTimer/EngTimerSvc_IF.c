/**
 * @file        EngTimerSvc_IF.c
 * @brief       This is Inteface code for Engine Timer Service Component.
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
 * @dept		S/W R&D Group / Digital Printing Division
 * @date		07/11/2024(D/M/Y)
 * @version		V0.1
 */

#define	__ENGTIMERSVC_IF_C__

#include "Eng_CommonType.h"

#include "EngTimerSvc_Types.h"
#include "EngTimerSvc_Main.h"
#include "EngTimerSvc_IF.h"

//#include "EngHAL_Types.h"


/**
* @brief		
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks		
*/
BOOL EngTimerSvc_IF_Initialize(void)
{
	return EngTimerSvc_Initialize();
}

/**
* @brief       	Interface function to run engine timer service 
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngTimerSvc_IF_Main(void)
{
	static U32 ulCnt = 0;

#ifdef FR_ENGLIB_WATCHDOG_LOGGING
	EngHAL_EngTimer_EnableTimerInt(HAL_ENGTIMER_NAME_WATCHDOG, TRUE);
#endif

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
	EngTM_ETM_CheckInterruptTimeDelay();
	EngTM_ETM_ResetTimer();
	
#if defined(WIN32)
	EngTM_ETM_GetReport();
#endif
	EngTM_ETM_SelectSaveTargetStorage();
	EngTM_ETM_EnableMeasure(TRUE);
	EngTM_ETM_SaveTimeEvent((U32)EngTimerSvc_IF_Main, 0);
#endif

#ifdef FR_TM_LMS_ISR
	{
		TLmsISR *pstLMSIsr = (TLmsISR *)EngTM_IF_GetLms(LMS_KIND_ISR);
		pstLMSIsr->pfnUpateISRCallTime(pstLMSIsr);
		pstLMSIsr->pfnClearISR();
	}	
#endif

#if defined(ENGINE_DBG)
#ifdef USE_SYSTICK
	EngTimerSvc_CountBySysTick();
#else
	ENG_COUNT();
#endif
#endif

#ifdef ENG_TESTMGR_MONITOR_REGISTER
	EngHAL_MonitorGPORegistor();
	EngHAL_MonitorMtrRegistor();
	EngHAL_MonitorPWMRegistor();
#endif

#ifdef WA_OH_DISPLAY_OPTION_COM_ERROR
	{
		static U32 ulReqScf = 0;

		TEngSystemManager *pstSystemManager = (TEngSystemManager *)EngSM_IF_GetFeature(ENGSM_GET_MANAGER);

		if(pstSystemManager->enEngState == ENG_ST_STANDBY)
		{
			if(ulReqScf != EngHAL_GPIO_GetInput(HAL_GPIO_NAME_CMD_REQ_SCF))
			{
				DBG_NEWIF_SIMPLEFIED("\r\n[%s:REGISTOR] ulReqScf <0x%x, 0x%x>", ENG_TICK, ulReqScf, EngHAL_GPIO_GetInput(HAL_GPIO_NAME_CMD_REQ_SCF));
				ulReqScf = EngHAL_GPIO_GetInput(HAL_GPIO_NAME_CMD_REQ_SCF);
			}
		}
	}
#endif

	//EngTimerSvc_Execute();

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
	EngTM_ETM_SaveTimeEvent((U32)EngTimerSvc_IF_Main, 1);
	EngTM_ETM_EnableMeasure(FALSE);
	EngTM_ETM_CalculateElapsedTimeAverage();
#endif	//FR_TESTMGR_ELAPSED_TIME_MEASURE

#ifdef FR_TM_LMS_COMMONINFO
	{
		TLmsCommonInfo *pstCommonInfo = (TLmsCommonInfo *)EngTM_IF_GetLms(LMS_KIND_COMMON_INFO);
		pstCommonInfo->pfnDisplayEnvironmentInfoSA();
	}
#endif
#ifdef FR_TM_LMS_VMCOUNT
	{
		TLmsVMCount *pstVMCount = (TLmsVMCount *)EngTM_IF_GetLms(LMS_KIND_VM_COUNT);
		pstVMCount->pfnDisplayVMCountSA(pstVMCount);
	}	
#endif	
#ifdef FR_TM_LMS_ISR
	{
		TLmsISR *pstLMSIsr = (TLmsISR *)EngTM_IF_GetLms(LMS_KIND_ISR);
		pstLMSIsr->pfnUpateISRExeTime(pstLMSIsr);
	}	
#endif
#ifdef FR_TM_LMS_DATE
	{
		TLmsDate *pstDate = (TLmsDate *)EngTM_IF_GetLms(LMS_KIND_DATE);
		pstDate->pfnDisplayPeriodDateSA();
	}	
#endif
#ifdef FR_TM_LMS_LIFE
	{
		TLmsLife *pstLmsLife = (TLmsLife *)EngTM_IF_GetLms(LMS_KIND_LIFE);
		pstLmsLife->pfnDisplayUIRemain(pstLmsLife);
	}
#endif

#ifdef FR_ENGLIB_WATCHDOG_LOGGING
//	{
//		static U32 ulTime = 0;

//		if(++ulTime % 500 == 0)
//		{
//			ENG_PRINT("{%d}", BCD8_TO_DEC(RTC_SEC_REG));
//		}
//	}

	EngHAL_EngTimer_EnableTimerInt(HAL_ENGTIMER_NAME_WATCHDOG, FALSE);
#endif
}

U32 EngTimerSvc_IF_Suspend(U32 ulTaskIndex)
{
	return EngTimerSvc_Suspend(ulTaskIndex);
}

U32 EngTimerSvc_IF_Resume(U32 ulTaskIndex)
{
	return EngTimerSvc_Resume(ulTaskIndex);
}

