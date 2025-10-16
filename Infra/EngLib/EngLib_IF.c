/**
 * @file        EngLib_IF.c
 * @brief       This is main code for Engine Library Component.
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
 * @date		14/04/2009(D/M/Y)
 * @version		V0.1
 */

#define	__ENGLIB_IF_C__

#include "Eng_CommonType.h"

#include "EngLib_Types.h"
#include "EngLog_IF.h"
#include "EngLib_IF.h"

// static TEngLibCallBackFunc astCallBackFuncList[] = 
// {
// 	{	"pfnIFSvcEtoK", 			(U32*)&stEngLib.pfnIFSvcEtoK				}, 
// 	{	"pfnGetErrorTableInfo", 	(U32*)&stEngLib.pfnGetErrorTableInfo		}, 
// 	{	"pfnIFSvcNewIFInterrupt",	(U32*)&stEngLib.pfnIFSvcNewIFInterrupt		},
// 	{	"pfnSMHndIFStartHandler",	(U32*)&stEngLib.pfnSMHndIFStartHandler		},
// 	{	"pfnSMHndIFSendEvent",		(U32*)&stEngLib.pfnSMHndIFSendEvent			},
// 	{	"pfnLMSAssertEA",			(U32*)&stEngLib.pfnLMSAssertEA				},
// 	{	"pfnGetCurrentRTCTime",		(U32*)&stEngLib.pfnGetCurrentRTCTime		},
// 	{	"pfnInDecreaseVMCountSA",	(U32*)&stEngLib.pfnInDecreaseVMCountSA		},
// 	{	"pfnCheckVMCountOverEA",	(U32*)&stEngLib.pfnCheckVMCountOverEA		},
// 	{	"pfnVMCallByTaskEA",		(U32*)&stEngLib.pfnVMCallByTaskEA			},		
// 	{	"pfnLMSTaskLogBufferFullEA",(U32*)&stEngLib.pfnLMSTaskLogBufferFullEA	},
// 	{	"pfnFOCNotifyByADCIRQ",		(U32*)&stEngLib.pfnFOCNotifyByADCIRQ		},
// };

static TEngLibCallBackFunc astCallBackFuncList[MAX_ENG_LIB_CALLBACK_FUNC] = {0,};

void EngLib_IF_Entry(TInitialStepType enInitStep)
{		
	/* Initialize the Engine Log Library */
#ifdef FR_ENGLIB_LOG	
	EngLog_IF_LibraryEntry(enInitStep);
#endif

	if(enInitStep & INIT_STEP_1ST)
	{
		EngLib_IF_InitCallBackFuncList();
	}

	if(enInitStep & INIT_STEP_2ND)
	{
		DBG_ENGLIB(ENG_DBG_STRING"EngLib_IF_Entry", ENG_TICK, "Lib");
		
		/* Initialize the Engine Common Library */
		EngLib_MainEntry();
	}
}

TEngLib *EngLib_IF_GetLibrary(void)
{
	return &stEngLib;
}

void EngLib_IF_InitCallBackFuncList()
{
	U32 ulCnt = 0;

	TEngLibCallBackFunc *pstHead = &astCallBackFuncList[0];

	for(ulCnt = 0; ulCnt < MAX_ENG_LIB_CALLBACK_FUNC; ulCnt++)
	{
		pstHead = &astCallBackFuncList[ulCnt];

		pstHead->pubFuncName = NULL;
		pstHead->ulFuncHndlID = 0;
		pstHead->pfnCallBackFunc = NULL;

		if(ulCnt + 1 < MAX_ENG_LIB_CALLBACK_FUNC)
		{
			pstHead->pNext = &astCallBackFuncList[ulCnt+1];
		}
	}
}

BOOL EngLib_IF_RegistryCallBackFunc(U8 *pubFuncName, U32 ulFuncHndlID,  TENGLIB_HAL_EVENT_CALLBACK_F pFuncHndl)
{
	U32 ulCnt = 0;

	TEngLibCallBackFunc *pstHead = &astCallBackFuncList[0];

	while(pstHead->ulFuncHndlID != 0 && pstHead->pubFuncName != NULL)
	{
		pstHead = pstHead->pNext;
		ulCnt++;

		if(ulCnt >= MAX_ENG_LIB_CALLBACK_FUNC)
		{
			DBG_EMERGENCY("\r\n[%s:EH]EngLib_IF_RegistryCallBackFunc: Overflow", ENG_TICK);
			return FALSE;
		}
	}

	if(pstHead->pubFuncName == NULL)
	{
		pstHead->pubFuncName = pubFuncName;
		pstHead->ulFuncHndlID = ulFuncHndlID;
		pstHead->pfnCallBackFunc = pFuncHndl;

		DBG_SWO(ENG_DBG_STRING"EngLib_IF_RegistryCallBackFunc: Registered=>%s, ID=%d", ENG_TICK, "EngLib", pubFuncName, ulFuncHndlID);
		return TRUE;
	}

	return FALSE;
}

void EngLib_IF_NotifyCallBackFunc(U32 ulFuncHndlID, U8* pubData, U32 ulLength)
{
	TEngLibCallBackFunc *pstHead = &astCallBackFuncList[0];

	while(pstHead->ulFuncHndlID != 0 && pstHead->pubFuncName != NULL)
	{
		if(pstHead->ulFuncHndlID == ulFuncHndlID)
		{
			if(pstHead->pfnCallBackFunc != NULL)
			{
				void (*pfnCallback)(U8*, U32) = (void (*)(U8*, U32))pstHead->pfnCallBackFunc;
				pfnCallback(pubData, ulLength);
			}
			return;
		}

		pstHead = pstHead->pNext;
	}

	DBG_EMERGENCY("\r\n[%s:EH]EngLib_IF_NotifyCallBackFunc: Not Found(%d)", ENG_TICK, ulFuncHndlID);
}

BOOL EngLib_IF_Assert(U32 ulValue, U8 *pubFileName, U32 ulLine)
{
	BOOL fRetVal = FALSE;
	
	if(!ulValue)
	{
		DBG_EMERGENCY("\r\n[%s:EH]EngAssert:%s, Line:%d", ENG_TICK, pubFileName, ulLine);
		ENG_PRINT("\r\n[%s:EH]EngAssert:%s, Line:%d", ENG_TICK, pubFileName, ulLine);

//		EngLib_DumpStack(NULL);
		
#ifdef FR_TM_LMS_ASSERT
		if(stEngLib.pfnLMSAssertEA != NULL)
		{
			stEngLib.pfnLMSAssertEA(pubFileName, ulLine);
		}
#endif

		//if(stEngLib.pfnSMHndIFStartHandler != NULL)
		//{
			//stEngLib.pfnSMHndIFStartHandler(ENG_HND_EH, ERROR_NAME_ENG_ASSERT, NULL);
		//}
		
		if((0 == C_ENG_MAJOR_VERSION) || (1 == C_ENG_MAJOR_VERSION))
		{
			// EngVM_DeleteByFunc(EngLib_VM_SendAssert);
//			EngVM_Add(ENGVM_ARG_NUM3|ENGVM_ARG_INFINITE, 0, 5*T100MS, EngLib_VM_SendAssert, ulValue, pubFileName, ulLine);
		}

		fRetVal = TRUE;
	}

	return fRetVal;
}

void EngLib_VM_SendAssert(U32 ulValue, U8 *pubFileName, U32 ulLine)
{
#if defined(HR_ENGLIB_DEBUG_MESSAGE_HDD_SAVE) && !defined(C_HDD_LOG_SAVE_NEW)
	if(EngLib_IF_IsLogSaveCompleteToHDD() == TRUE)
#endif
	{
		EngOS_Assert(ulValue, pubFileName, ulLine);
	}
}

