/**
 * @file        EngLib_IF.h
 * @brief       This is header file for Engine Library Component.
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
 * @date		08/05/2009(D/M/Y)
 * @version		V0.1
 */

#ifndef __ENGLIB_IF_H__
#define __ENGLIB_IF_H__

#undef EXTERN
#ifdef __ENGLIB_IF_C__
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void EngLib_IF_Entry(TInitialStepType enInitStep);
EXTERN TEngLib *EngLib_IF_GetLibrary(void);
EXTERN void EngLib_IF_RegistryCallBackFunc(U8 *pubFuncName, U32 ulFuncHndl);

EXTERN BOOL EngLib_IF_Assert(U32 ulValue, U8 *pubFileName, U32 ulLine);
EXTERN void EngLib_VM_SendAssert(U32 ulValue, U8 *pubFileName, U32 ulLine);

#endif /* __ENGLIB_IF_H__ */

