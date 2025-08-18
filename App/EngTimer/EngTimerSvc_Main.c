/**
 * @file        EngTimerSvc_Main.c
 * @brief       This is main code for Engine Timer Service Component.
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
 * @date		03/11/2024(D/M/Y)
 * @version		V0.1
 */

#define	__ENGTIMERSVC_MAIN_C__

#include "Eng_CommonType.h"
#include "EngTimerSvc_Types.h"
#include "EngTimerSvc_Main.h"

#include "EngCM_TimerSvcConfig.h"

static TEngTimerBlock s_astTimerList[TIMERSVC_ID_MAX];	/**< Array for engine timers */


/**
* @brief		
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks		
*/
BOOL EngTimerSvc_Initialize(void)
{
	TEngSystemManager *pstSystemManager = (TEngSystemManager *)EngSM_IF_GetFeature(ENGSM_GET_MANAGER);

	// DBG_ENGTMSVC(ENG_DBG_STRING"TimerSvc_Initialize", ENG_TICK, "TMSvc");
	/* Compose the Component Handler that will be added at the Engine Timer Service */
	EngTimerSvc_Compose();

	/* Register callback function */
	pstSystemManager->pfnTimerSvcSuspend	= EngTimerSvc_Suspend;
	pstSystemManager->pfnTimerSvcResume		= EngTimerSvc_Resume;
		
	return TRUE;
}

/**
* @brief       function to run engine timer service 	
* 
* @param[in]		None
* @range			
* @retval			None
* @global			
* @remarks     	
*/
void EngTimerSvc_Execute(void)
{
	U32 ulIndex = 0;
	TEngTimerBlock *pstTimerEntry = s_astTimerList;

	for(ulIndex = 0; ulIndex < TIMERSVC_ID_MAX; ulIndex++)
	{
		/* Check if there is a task at this location */
		if(pstTimerEntry[ulIndex].pfnTimerFunc)
		{
			if(pstTimerEntry[ulIndex].enStatus == TIMERSVC_STS_SUSPEND)
			{
				continue;
			}

			if(--pstTimerEntry[ulIndex].ulDelay == 0)
			{
				/* Run the task */
				VOID_ASSERT(pstTimerEntry[ulIndex].pfnTimerFunc != NULL);
				
#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
				EngTM_ETM_SaveTimeEvent((U32)pstTimerEntry[ulIndex].pfnTimerFunc, 0);
#endif
				(pstTimerEntry[ulIndex].pfnTimerFunc)();

#ifdef FR_TESTMGR_ELAPSED_TIME_MEASURE
				EngTM_ETM_SaveTimeEvent((U32)pstTimerEntry[ulIndex].pfnTimerFunc, 1);
#endif
				if(pstTimerEntry[ulIndex].ulPeriod)
				{
					/* Schedule regular tasks to run again */
					pstTimerEntry[ulIndex].ulDelay = pstTimerEntry[ulIndex].ulPeriod;
				}
				else
				{
					EngTimerSvc_Delete(ulIndex);
				}
			}
		}
	}
}

/**
* @brief       	function to add engine timer service job
* 
* @param[in]		void (*pfnTask)(void)
* @param[in]		const U32 ulDelay
* @param[in]		const U32 ulPeriod
* @range			
* @retval			U32 ulIndex
* @global			
* @remarks     	
*/
U32 EngTimerSvc_Add(U32 ulID, void (*pfnTask)(void), const U32 ulDelay, const U32 ulPeriod)
{
	U32 ulIndex = 0;
	TEngTimerBlock *pstTimerEntry = s_astTimerList;
	
	/* First find a task in the array if there is one */
	while((ulIndex < TIMERSVC_ID_MAX) && (pstTimerEntry[ulIndex].pfnTimerFunc != 0))
	{
		ulIndex++;
	}

	/* Have we reached the end of the list? */
	if(ulIndex >= TIMERSVC_ID_MAX)
	{
		return TIMERSVC_ID_MAX;
	}

	/* If we're here, there is a space in the task array */
	pstTimerEntry[ulIndex].enID = ulID;
	pstTimerEntry[ulIndex].pfnTimerFunc =(void(*)(void)) pfnTask;
	pstTimerEntry[ulIndex].ulDelay = ulDelay + 1;
	pstTimerEntry[ulIndex].ulPeriod = ulPeriod;

	// DBG_ENGTMSVC(ENG_DBG_STRING"Add %d", ENG_TICK, "TMSvc",ulIndex);
	
	return ulIndex; /* return ID of task to allow deletion or suspension */
}

/**
* @brief       function to delete engine timer service job	
* 
* @param[in]		const U32 ulTaskIndex
* @range			
* @retval			TEngTimerRetValue enRetValue
* @global			
* @remarks     	
*/
TEngTimerRetValue EngTimerSvc_Delete(const U32 ulTaskIndex)
{
	TEngTimerRetValue enRetValue = TIMERSVC_RET_ERROR;
	TEngTimerBlock *pstTimerEntry = s_astTimerList;
	U32 ulIdx = 0;
	
	for(ulIdx = 0; ulIdx < TIMERSVC_ID_MAX; ulIdx++)
	{
		if((pstTimerEntry[ulIdx].pfnTimerFunc != NULL) && (pstTimerEntry[ulIdx].enID == ulTaskIndex))
		{
			if(pstTimerEntry[ulIdx].pfnTimerFunc == 0)
			{
				enRetValue = TIMERSVC_RET_ERROR;
			}
			else
			{
				pstTimerEntry[ulIdx].pfnTimerFunc = 0;
				pstTimerEntry[ulIdx].ulDelay = 0;
				pstTimerEntry[ulIdx].ulPeriod = 0;
				enRetValue = TIMERSVC_RET_NORMAL;

				// DBG_ENGTMSVC(ENG_DBG_STRING"Delete %d", ENG_TICK, "TMSvc",ulTaskIndex);
			}
			break;
		}
	}

	return enRetValue; /* return status */
}

U32 EngTimerSvc_Suspend(const U32 ulTaskIndex)
{
	TEngTimerRetValue enRetValue = TIMERSVC_RET_ERROR;
	TEngTimerBlock *pstTimerEntry = s_astTimerList;
	U32 ulIdx = 0;
	
	for(ulIdx = 0; ulIdx < TIMERSVC_ID_MAX; ulIdx++)
	{
		if((pstTimerEntry[ulIdx].pfnTimerFunc != NULL) && (pstTimerEntry[ulIdx].enID == ulTaskIndex))
		{
			if(pstTimerEntry[ulIdx].pfnTimerFunc == 0)
			{
				enRetValue = TIMERSVC_RET_ERROR;
			}
			else
			{
				pstTimerEntry[ulIdx].enStatus = TIMERSVC_STS_SUSPEND;
				enRetValue = TIMERSVC_RET_NORMAL;

				// DBG_ENGTMSVC(ENG_DBG_STRING"Suspend %d", ENG_TICK, "TMSvc",ulTaskIndex);
			}
			break;
		}
	}
	return enRetValue;
}

U32 EngTimerSvc_Resume(const U32 ulTaskIndex)
{
	TEngTimerRetValue enRetValue = TIMERSVC_RET_ERROR;
	TEngTimerBlock *pstTimerEntry = s_astTimerList;
	U32 ulIdx = 0;
	
	for(ulIdx = 0; ulIdx < TIMERSVC_ID_MAX; ulIdx++)
	{
		if((pstTimerEntry[ulIdx].pfnTimerFunc != NULL) && (pstTimerEntry[ulIdx].enID == ulTaskIndex))
		{
			if(pstTimerEntry[ulIdx].pfnTimerFunc == 0)
			{
				enRetValue = TIMERSVC_RET_ERROR;
			}
			else
			{
				pstTimerEntry[ulIdx].enStatus = TIMERSVC_STS_RESUME;
				enRetValue = TIMERSVC_RET_NORMAL;

				// DBG_ENGTMSVC(ENG_DBG_STRING"Resume %d", ENG_TICK, "TMSvc",ulTaskIndex);
			}
			break;
		}
	}

	return enRetValue;
}

/**
* @brief       	function to compose the Component Handler that will be added at the Engine Timer Service 
* 
* @param[in]		None
* @range			
* @retval		U32	ulTimerID
* @global			
* @remarks     	
*/
U32 EngTimerSvc_Compose(void)
{
	U32 ulTimerID = 0;
	U32 ulIndex = 0;
	U32 ulTimerTblSize = ARRAY_SIZE(s_astEngTimerTbl);	/* Get Engine Component List */
	TEngTimerBlock *pstTimerTbl = s_astEngTimerTbl;

	/* Start Engine Component */
	for(ulIndex = 0; ulIndex < ulTimerTblSize; ulIndex++)
	{
		if(pstTimerTbl[ulIndex].pfnTimerFunc)
		{
			ulTimerID = EngTimerSvc_Add(pstTimerTbl[ulIndex].enID, pstTimerTbl[ulIndex].pfnTimerFunc, pstTimerTbl[ulIndex].ulDelay, pstTimerTbl[ulIndex].ulPeriod); 
		}
	}
	
	// DBG_ENGTMSVC(ENG_DBG_STRING"Number of Registered Timer Svc = %d", ENG_TICK, "TMSvc", ulTimerID);
	
	if(ulTimerID > TIMERSVC_ID_MAX)
	{
		// DBG_ENGTMSVC(ENG_DBG_STRING"Timer Service ID BUFFER OVER", ENG_TICK, "TMSvc");
		
	}

	return ulTimerID;
}


void EngTimerSvc_CountBySysTick(void)
{
	g_ulEngTimer = uwTick; // get from sysTick of stm32
	g_ulEngTickCnt = ((g_ulEngTimer - g_ulEngTick) << 0);

	if(sprintf != NULL)
	{
		sprintf(g_aubEngTick, "%u", ENG_TICK_CNT);
	}
	else 
	{
		g_aubEngTick[0] = '0'; g_aubEngTick[1] = '\0';
	}
}