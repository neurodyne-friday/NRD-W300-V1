/**
 * @file        EngSM_IF.c
 * @brief       This is I/F code for System Manager Component.
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
 * @date		03/11/2008(D/M/Y)
 * @version		V0.1
 */

#define	__ENGSM_IF_C__

#include "Eng_CommonType.h"

//#include "EngSM_Page.h"
#include "EngSM_Main.h"

#include "EngSM_IF.h"


/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
BOOL EngSM_IF_Initialize(void)
{
	DBG_ENGSM(ENG_DBG_STRING"EngSM_IF_Initialize", ENG_TICK, "SM");
	
	/* Initialize the Engine Library */
	EngLib_IF_Entry(INIT_STEP_2ND);
   	
    /* Initialize the Hardware */
    EngHAL_LibraryEntry();

    /* Do power on sequence: backup data restore */
	EngSM_PowerOn();

    /* Register the Hardware Interrupts */
	EngHAL_CAN_RegisterCallback(HAL_EVENT_CAN1_RX, EngSM_IF_NotifyEventByCAN1);
	EngHAL_PWR_RegisterCallback(HAL_EVENT_PWR_OFF, EngSM_IF_NotifyEventByPowerOff);

	/* Create & Initialize Device Driver */
	EngDrv_IF_Create();
	EngDrv_IF_Initialize();

    /* Initialize the Engine Dinamic Configuration Manager */
#ifdef FR_SM_ENGINE_FAST_BOOTUP
	EngCM_IF_FastEngineInitialize();
#else
	//EngCM_IF_Initialize();
#endif
	
	/* Initialize the Engine System Manager */
	EngSM_Initialize();

    return TRUE;
}

 
/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
// void EngSM_IF_StartPrint(TEngPage *pstObjPage)
// {
// 	DBG_ENGSM_PAGE(ENG_DBG_STRING"SM_IF_StartPrint", ENG_TICK, "SM");	

//     EngSM_StartPrint(pstObjPage, ENG_PAGE_CURR_ID);
// }

 
/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngSM_IF_StopPrint(void* pvObjPage)
{
	DBG_ENGSM_PAGE(ENG_DBG_STRING"SM_IF_StopPrint", ENG_TICK, "SM");	

   EngSM_StopPrint(pvObjPage);
}

#ifdef ALT_IFSVC_NEWIF_SIMPLEFIED

/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngSM_IF_StartDuplexReversePrint(TEngPage *pstObjPage)
{
	DBG_ENGSM_PAGE(ENG_DBG_STRING"SM_IF_StartDuplexReversePrint", ENG_TICK, "SM");	

	EngSM_StartDuplexReversePrint(pstObjPage);
}

/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngSM_IF_StopDuplexReversePrint(TEngPage *pstObjPage)
{
	DBG_ENGSM_PAGE(ENG_DBG_STRING"SM_IF_StopDuplexReversePrint", ENG_TICK, "SM");	

	EngSM_StopDuplexReversePrint(pstObjPage);
}

TEngPage *EngSM_IF_GetDuplexReversePage(void)
{
	return EngSM_GetDuplexReversePage();
}

#endif


/**
* @brief       		I/F to get information about system manager
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
//TEngSystemManager *EngSM_IF_GetManager(void)
//{
//	return EngSM_GetManager();
//}

//void *EngSM_IF_GetHandler(TEngHandlerID enComponentID, U32 ulClassifyID)
//{
//    return EngSM_HndIF_GetHandler(enComponentID, ulClassifyID);
//}

//void *EngSM_IF_GetHandlerFunc(TEngHandlerID enComponentID, U8* pubFuncName, U32 ulArgCnt)
//{
//	return EngSM_HndIF_GetHandlerFunc(enComponentID, pubFuncName, ulArgCnt);
//}

//void *EngSM_IF_GetSystemFunc(U8* pubFuncName, U32 ulArgCnt)
//{
//	return EngSM_GetSystemFunc(pubFuncName, ulArgCnt);
//}
	
// TEngPage *EngSM_IF_GetPage(TEngPageID enPageID)
// {
// 	return EngSM_GetPage(enPageID);
// }

/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
BOOL EngSM_IF_SetDeviceStatus(U32 ulStatusID, U32 ulNewValue, U32 ulSetReset)
{
    return EngSM_SetDeviceStatus(ulStatusID, ulNewValue, ulSetReset);
}

 
/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
U32 EngSM_IF_GetDeviceStatus(U32 ulStatusID)
{
    return EngSM_GetDeviceStatus(ulStatusID);
}

 
/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
U32 EngSM_IF_SendEvent(U32 ulEventID, TStateMachine *pstStateMachine, U32 ulLParam, U32 ulRParam)
{
	return EngSM_SendEvent(ulEventID, pstStateMachine, ulLParam, ulRParam);
}

 
/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
//void EngSM_IF_StartTimingChart(void *pvTimingObj, U32 ulTimingID)
//{
//    EngSM_StartTimingChart(pvTimingObj, ulTimingID);
//}


/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void *EngSM_IF_GetFeature(U32 ulFeatureID)
{
    return EngSM_GetFeature(ulFeatureID);
}

/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
BOOL EngSM_IF_IsIntervalTimeValid(TIntervalTimeType enType)
{
    return EngSM_IsIntervalTimeValid(enType);
}

/**
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
U32 EngSM_IF_GetIntervalTime(TIntervalTimeType enType)
{
    return EngSM_GetIntervalTime(enType);
}

/** 
* @brief       	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/

//BOOL EngSM_IF_Main(void)
void EngSM_IF_Main(void)
{
    //return EngSM_Main();
	EngSM_Main();
}

/** 
* @brief	   	Power off the system
* @param[in]	None
* @range			
* @retval		None
* @global			
* @remarks     		
*/

void EngSM_IF_NotifyEventByPowerOff(void)
{
	EngSM_PowerOff();
}

/**
 * @brief 	  	Event handler for CAN1
 * @param[in]	None
 * @range
 * @retval		None
 * @global
 * @remarks		This function is called when a CAN1 event occurs.
 */

void EngSM_IF_NotifyEventByCAN1(void)
{

}

/**
 * @brief 	  	Event handler for CAN2
 * @param[in]	None
 * @range
 * @retval		None
 * @global
 * @remarks		This function is called when a CAN2 event occurs.
 */
void EngSM_IF_NotifyEventByCAN2(void)
{

}
