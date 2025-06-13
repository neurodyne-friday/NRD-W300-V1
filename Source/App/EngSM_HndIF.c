/**
 * @file        EngSM_HndIF.c
 * @brief       This is main code for Engine Handler Interface
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
 * @date		07/11/2008(D/M/Y)
 * @version		V0.1
 */

#define	__ENGSM_HNDIF_C__

#include "Eng_CommonType.h"

#include "EngSM_HndIF.h"
//#include "EngSM_State.h"


static TEngHndFramework *s_apstEngHndFramework[ENG_HND_TOTAL];

/**
* @brief       		Perform task that connect each handler's Interface.
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngSM_HndIF_CreateHandler(void)
{
    U32 ulIndex = 0;
    void *pvHandle = NULL;

	EngLib_MemorySet(s_apstEngHndFramework, 0, (sizeof(TEngHndFramework *) * ENG_HND_TOTAL));

	DBG_ENGSM(ENG_DBG_STRING"SM_HndIF_CreateHandler", ENG_TICK, "SM");

    while(1)
    {
        if((void *)s_apfnEngHnd_Create[ulIndex] != NULL)
        {
            pvHandle = (*s_apfnEngHnd_Create[ulIndex])();
            VOID_ASSERT(pvHandle != NULL);
            s_apstEngHndFramework[ulIndex] = (TEngHndFramework *)pvHandle;
            ulIndex++;
        }
        else
        {
            break;
        }
    }
    
}

/**
* @brief       		I/F Function that initializes designated handler.
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
BOOL EngSM_HndIF_Initialize(void)
{
    U32  ulIndex = 0;

	DBG_ENGSM(ENG_DBG_STRING"SM_HndIF_Initialize", ENG_TICK, "SM");

    for(ulIndex = 0; ulIndex < ENG_HND_TOTAL; ulIndex++)
    {
    	if((void *)s_apstEngHndFramework[ulIndex]->Initialize == NULL)
   		{
			ASSERT(0);
		}
   	}
	
    s_apstEngHndFramework[ENG_HND_MH]->Initialize();
	s_apstEngHndFramework[ENG_HND_EH]->Initialize();

	EngLib_IF_RegistryCallBackFunc("pfnSMHndIFStartHandler", EngSM_HndIF_StartHandler);
	EngLib_IF_RegistryCallBackFunc("pfnSMHndIFSendEvent", EngSM_HndIF_SendEvent);
	
	return TRUE;
}

/** 
* @brief       		I/F Function that do designated handler so as to do start
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
BOOL EngSM_HndIF_StartHandler(TEngHandlerID enComponentID, U32 ulClassifyID, void* pvHndObj)
{
    U32  ulIndex = 0;
    BOOL fResult=FALSE;

    while(1)
    {
        if(s_apstEngHndFramework[ulIndex] == NULL)
        {
        	fResult = TRUE;
            break;
        }
        
        if(s_apstEngHndFramework[ulIndex]->ulHandlerID == (U32)enComponentID)
        {
            s_apstEngHndFramework[ulIndex]->StartHandler(ulClassifyID, pvHndObj);
        	fResult = TRUE;
            break;
        }
        ulIndex++;
    }

//	DBG_ENGSM("\n[EngSM] EngSM_HndIF_StartHandler HndID=%d", enComponentID);

	return fResult;
}

/** 
* @brief       		I/F Function that do designated handler so as to do stop
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
BOOL EngSM_HndIF_StopHandler(TEngHandlerID enComponentID, U32 ulClassifyID, void* pvHndObj)
{
    U32  ulIndex = 0;
    BOOL fResult = FALSE;

    while(1)
    {
        if(s_apstEngHndFramework[ulIndex] == NULL)
        {
        	fResult = TRUE;
            break;
        }
        
        if(s_apstEngHndFramework[ulIndex]->ulHandlerID == (U32)enComponentID)
        {
            s_apstEngHndFramework[ulIndex]->StopHandler(ulClassifyID, pvHndObj);
        	fResult = TRUE;
            break;
        }
        ulIndex++;
    }

//	DBG_ENGSM("\n[EngSM] EngSM_HndIF_StopHandler HndID=%d", enComponentID);

	return fResult;
}

/** 
* @brief       		I/F Function to update information to designated handler
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngSM_HndIF_SetHandler(TEngHandlerID enComponentID, U32 ulClassifyID, void *pvSetInfo)
{
    U32  ulIndex = 0;

    while(1)
    {
        if(s_apstEngHndFramework[ulIndex] == NULL)
        {
            break;
        }
        
        if(s_apstEngHndFramework[ulIndex]->ulHandlerID == (U32)enComponentID)
        {
            s_apstEngHndFramework[ulIndex]->SetHandlerInfo(ulClassifyID, pvSetInfo);
            break;
        }
        ulIndex++;
    }
    
//	DBG_ENGSM("\n[EngSM] EngSM_HndIF_SetHandler : HndID=%d, ClassifyID=%d", enComponentID, ulClassifyID);
}

/** 
* @brief       		I/F Function to pass Event information to designated handler information 
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
U32 EngSM_HndIF_SendEvent(TEngHandlerID enComponentID, U32 ulEventID, TStateMachine *pstStateMachine, U32 ulLParam, U32 ulRParam)
{
    U32  ulIndex = 0;
    U32 ulResult = FALSE;

    while(1)
    {
        if(s_apstEngHndFramework[ulIndex] == NULL)
        {
        	ulResult = FALSE;
            break;
        }
        
        if(s_apstEngHndFramework[ulIndex]->ulHandlerID == (U32)enComponentID)
        {
            ulResult = s_apstEngHndFramework[ulIndex]->SendEvent(ulEventID, pstStateMachine, ulLParam, ulRParam);
            break;
        }
        ulIndex++;
    }

//	DBG_ENGSM("\n[EngSM] EngSM_HndIF_SendEvent : HndID=%d, EventID=%x, LParam=%d, RParam=%d", enComponentID, ulEventID, ulLParam, ulRParam);

	return ulResult;
}

/** 
* @brief       		I/F Function to pass Status information to designated handler.
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngSM_HndIF_FollowDeviceStatus(TEngHandlerID enComponentID, U32 ulStatusID, U32 ulOldValue, U32 ulNewValue)
{
    U32  ulIndex = 0;
    BOOL fResult=FALSE;

    while(1)
    {
        if(s_apstEngHndFramework[ulIndex] == NULL)
        {
            break;
        }
        
        if(s_apstEngHndFramework[ulIndex]->ulHandlerID == (U32)enComponentID)
        {
            s_apstEngHndFramework[ulIndex]->FollowDeviceStatus(ulStatusID, ulOldValue, ulNewValue);
            break;
        }
        ulIndex++;
    }
    
//	DBG_ENGSM("\n[EngSM] EngSM_HndIF_FollowDeviceStatus : HndID=%d, ulStatusID=%d, OldValue=%d, NewValue=%d", enComponentID, ulStatusID, ulOldValue, ulNewValue);
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

BOOL EngSM_HndIF_StartTimingChart(TEngHandlerID enComponentID, void *pvTimingObj, U32 ulTimingID)
{
    U32  ulIndex = 0;
    BOOL fResult=FALSE;

    while(1)
    {
        if(s_apstEngHndFramework[ulIndex] == NULL)
        {
        	fResult = TRUE;
            break;
        }
        
        if(s_apstEngHndFramework[ulIndex]->ulHandlerID == (U32)enComponentID)
        {
            s_apstEngHndFramework[ulIndex]->StartTiming(pvTimingObj, ulTimingID);
        	fResult = TRUE;
            break;
        }
        ulIndex++;
    }

	return fResult;
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
void *EngSM_HndIF_GetFeature(TEngHandlerID enComponentID, U32 ulFeatureID)
{
    U32  ulIndex = 0;
	void *pvGetFeature = NULL;

    while(1)
    {
        if(s_apstEngHndFramework[ulIndex] == NULL)
        {
            break;
        }
        
        if(s_apstEngHndFramework[ulIndex]->ulHandlerID == (U32)enComponentID)
        {
            pvGetFeature = s_apstEngHndFramework[ulIndex]->GetFeature(ulFeatureID);
            break;
        }
        ulIndex++;
    }

	return pvGetFeature;
}

