/**
 * @file        EngLib_Main.h
 * @brief       This is header file for Engine Library.
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

#ifndef __ENGLIB_MAIN_H__
#define __ENGLIB_MAIN_H__

#undef EXTERN
#ifdef __ENGLIB_MAIN_C__
#define EXTERN
#else
#define EXTERN extern
#endif

typedef struct {
	U32 ErrCode;
	S8 ErrString[252];
} ErrBlock;

EXTERN void EngLib_MainEntry(void);

/* Task To ISR Send Message */
EXTERN BOOL EngLib_InitTaskToISRMessage(TMsgQCB *pstMsgQCB);
EXTERN U32 EngLib_TaskToISRSendEvent(U32 ulEventID, U32 ulLParam, U32 ulRParam);
EXTERN BOOL EngLib_TaskToISRReceiveEvent(TMsgQ *pstRcvMsgQ);

/* Message Queue */
EXTERN BOOL EngLib_GetMsgQ(TMsgQCB *pstMsgQCB, TMsgQ *pstRcvMsgQ);
EXTERN BOOL EngLib_ReceiveMsgQ(TMsgQCB *pstMsgQCB, TMsgQ *pstRcvMsgQ);
EXTERN BOOL EngLib_SendMsgQ(TMsgQCB *pstMsgQCB, TMsgQ *pstSendMsgQ);
EXTERN BOOL EngLib_SendMsgQWithoutFullChk(TMsgQCB *pstMsgQCB, TMsgQ *pstSendMsgQ);
EXTERN BOOL EngLib_IsMsgQEmpty(TMsgQCB *pstMsgQCB);
EXTERN BOOL EngLib_IsMsgQFull(TMsgQCB *pstMsgQCB);
EXTERN BOOL EngLib_IsReceivedMsgQ(TMsgQCB *pstMsgQCB);

/* Queue */
EXTERN BOOL EngLib_InitQueue(TQueue *pstQueue, void * pvBuffer, U32 ulBuffSize);
EXTERN BOOL EngLib_IsQueueEmpty(TQueue *pstQueue);
EXTERN BOOL EngLib_IsQueueFull(TQueue *pstQueue);

/* State Machine */
EXTERN S32 EngLib_StateCompareMachine(const void *pvName, const void *pvElem);
EXTERN TStateMachineTbl *EngLib_StateSearchMachine(TStateMachine *pstStateMachine, U32 ulState);
EXTERN TStateTransitionTbl *EngLib_StateSearchTransition(TStateMachine *pstStateMachine);
EXTERN U32 EngLib_StateActivity(TStateMachine *pstStateMachine, void *pvStateEntry);
EXTERN U32 EngLib_StateMachine(TStateMachine *pstStateMachine, U32 ulEvent, void *pvStateEntry);
EXTERN U32 EngLib_StateGuardCondition(TStateMachine *pstStateMachine, U32 ulEvent, void *pvStateEntry);
EXTERN U32 EngLib_StateChange(TStateMachine *pstStateMachine, U32 ulNextState, void *pvStateEntry);
EXTERN void EngLib_StateEvent(U32 ulEvent, TStateMachine *pstStateMachine);
EXTERN void EngLib_StateSet(U32 ulState, TStateMachine *pstStateMachine, void *pvStateEntry);
EXTERN U32 EngLib_StateGet(TStateMachine *pstStateMachine);
EXTERN void EngLib_StateExecutedStatusClear(TStateMachine *pstStateMachine);
EXTERN S32 EngLib_StateCompareName(const void *pvName, const void *pvElem);

/* List Head */
EXTERN void EngLib_ListHeadAdd(TListHead *new_h, TListHead *prev, TListHead *next);
EXTERN void EngLib_ListHeadAddHead(TListHead *new_h, TListHead *head);
EXTERN void EngLib_ListHeadAddTail(TListHead *new_h, TListHead *head);
EXTERN void EngLib_ListHeadDel(TListHead *entry);
EXTERN int EngLib_IsListHeadEmpty(TListHead *head);

/* Sort */
EXTERN void EngLib_QuickSort(void *base, U32 nmemb, U32 size, int (*compar)(const void *, const void *));

/* Search */
EXTERN void * EngLib_BinarySearch(const void *key, const void *base, U32 nmemb, U32 size, int (*compar)(const void *, const void *));
EXTERN U32 EngLib_AscendingAboveBelowArraySearchS16(S16 *paswTbl, U32 ulTblSize, S16 swKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_AscendingAboveBelowArraySearchU16(U16 *pauwTbl, U32 ulTblSize, U16 uwKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_AscendingAboveBelowArraySearchS32(S32 *paslTbl, U32 ulTblSize, S32 slKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_AscendingAboveBelowArraySearchU32(U32 *paulTbl, U32 ulTblSize, U32 ulKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_AscendingAboveUnderArraySearchS16(S16 *paswTbl, U32 ulTblSize, S16 swKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_AscendingAboveUnderArraySearchU16(U16 *pauwTbl, U32 ulTblSize, U16 uwKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_AscendingAboveUnderArraySearchS32(S32 *paslTbl, U32 ulTblSize, S32 slKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_AscendingAboveUnderArraySearchU32(U32 *paulTbl, U32 ulTblSize, U32 ulKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_DescendingBelowAboveArraySearchS16(S16 *paswTbl, U32 ulTblSize, S16 swKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_DescendingBelowAboveArraySearchU16(U16 *pauwTbl, U32 ulTblSize, U16 uwKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_DescendingBelowAboveArraySearchS32(S32 *paslTbl, U32 ulTblSize, S32 slKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_DescendingBelowAboveArraySearchU32(U32 *paulTbl, U32 ulTblSize, U32 ulKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_DescendingUnderAboveArraySearchS16(S16 *paswTbl, U32 ulTblSize, S16 swKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_DescendingUnderAboveArraySearchU16(U16 *pauwTbl, U32 ulTblSize, U16 uwKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_DescendingUnderAboveArraySearchS32(S32 *paslTbl, U32 ulTblSize, S32 slKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);
EXTERN U32 EngLib_DescendingUnderAboveArraySearchU32(U32 *paulTbl, U32 ulTblSize, U32 ulKeyValue, U32 ulBaseIdx, BOOL fRefLowValue);

/* Average */
EXTERN U32 EngLib_GetArrayAverageU32(U32 *paulArray, U32 ulCnt);
EXTERN U32 EngLib_GetArrayAverageAbnormalValueCutU32(U32 *paulArray, U32 ulAdcChkNum, U32 ulWasteNum);
EXTERN U32 EngLib_GetAverageArrayMinMaxCutU32(U32 *paulArray, U32 ulAdcChkNum, U32 ulWasteNum);
EXTERN S32 EngLib_GetAverageArrayCutPrePost(S32 *paulArray, U32 ulAdcChkNum, U32 ulPreWasteNum, U32 ulPostWasteNum);

/* Min Max */
EXTERN U32 EngLib_ArrayGetMax(U32 *paulArray, U32 ulCnt);
EXTERN U32 EngLib_ArrayGetMin(U32 *paulArray, U32 ulCnt);

/* Math */
EXTERN D32 EngLib_POW(D32 dx, U32 uly);

/* CRC */
EXTERN void EngLib_InitCRC16Tab(U16 *puwCRCBuff);
EXTERN U16 EngLib_UpdateCRC16(U16 *pubCRCBuff, U16 uwCrc, U8 ubC );
EXTERN U16 EngLib_CalcCRC16(U16 *pubCRCBuff, U16 uwCRC, U32 ulBufSize, U8 *pubBuf);

/* Swap */
EXTERN void EngLib_SwapMem(char *a, char *b, int size);

EXTERN S32 EngLib_GetBitIndex(U32 ulBit);

/* semaphore */
EXTERN void EngLib_InitSemaphore(TSemaphore *pstSemaphore);
EXTERN BOOL EngLib_WaitSemaphore(TSemaphore *pstSemaphore);
EXTERN BOOL EngLib_SemaphoreSignal(TSemaphore *pstSemaphore);

/* String & print */
EXTERN U32 EngLib_StrnLength(const char *s, unsigned int count);
EXTERN S32 EngLib_AtoI(const char *s);
EXTERN U8 *EngLib_Number(char *str, unsigned int num, int base, int type, int *length);
EXTERN S32 EngLib_SimpleVNSprintf(char *buffer, const char *format, va_list argptr, int length);
EXTERN S32 EngLib_SimpleNSprintf(char *buffer, int length, const U8 *format, ...);

EXTERN void* EngLib_MemorySet(void *pstDest, S32 slData, U32 ulSize);
EXTERN void* EngLib_MemoryCopy(void *pstDest, void *pstSrc, U32 ulSize);

EXTERN BOOL EngLib_CheckIRQMode(void);
EXTERN void EngLib_CallBackWatchDog(void);
EXTERN void EngLib_DumpRegister(U32 *pulRegs);
EXTERN void EngLib_DumpStack(U32 *pulStackAddr);
EXTERN U32 EngLib_SpinLock(U32 ulMask);

#define IOC_BIT (1 << 0) /* Invalid op cumulative */
#define DZC_BIT (1 << 1) /* Divide zero cumulative */
#define OFC_BIT (1 << 2) /* Overflow cumulative */
#define UFC_BIT (1 << 3) /* Underflow cumulative */
#define IXC_BIT (1 << 4) /* Inexact cumulative */
#define ND_BIT (1 << 8) /* No denormalised numbers */
#define IOE_BIT (1 << 16) /* Invalid operation exception */
#define DZE_BIT (1 << 17) /* Divide zero exception */
#define OFE_BIT (1 << 18) /* Overflow exception */
#define UFE_BIT (1 << 19) /* Underflow exception */
#define IXE_BIT (1 << 20) /* Inexact exception */
#define FP_SW_LIB 0x40000000
#define FP_SW_EMU 0x01000000
#define FP_HW_FPA 0x81000000

EXTERN void __rt_trap(ErrBlock *err, U32 *pulRegs);
EXTERN BOOL EngLib_IsEngineArea(U8* pubAddress);
EXTERN U16 EngLib_CRC_16_CCITT(const char *buf, int len);

#endif /* __ENGLIB_MAIN_H__ */

