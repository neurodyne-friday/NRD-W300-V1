/**
 * @file        EngLib_Types.h
 * @brief       This is type definition file for Engine Library Component.
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

#ifndef __ENGLIB_TYPES_H__
#define __ENGLIB_TYPES_H__

#include "Eng_Macro.h"

#if defined(__GNUC__)
#define BEGIN_STRUCT_PACKED(tagname) typedef struct _##tagname
#elif defined(__arm) || defined(__arm__) || defined(__CC_ARM)
#define BEGIN_STRUCT_PACKED(tagname) typedef __packed struct _##tagname
#else // default compiler
#define BEGIN_STRUCT_PACKED(tagname) typedef struct _##tagname
#endif

#if defined(__GNUC__)
#define END_STRUCT_PACKED(name) 	__attribute__ ((packed)) name
#elif defined(__arm__) || defined(__CC_ARM)
#define END_STRUCT_PACKED(name) 	name
#else // default compiler
#define END_STRUCT_PACKED(name) 	name
#endif

/**
 * @brief . For List Head
 */

typedef struct _TListHead
{
	struct _TListHead *next, *prev;
} TListHead;

#define LISTHEAD_INIT(ptr) do { \
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

#define LISTHEAD_ENTRY(ptr, type, member) \
((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define LISTHEAD_FOR_EACH(pos, head) \
    for (pos = (head)->next; pos != (head); \
pos = pos->next)

#define LISTHEAD_FOR_EACH_SAFE(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
pos = n, n = pos->next)


#define ZEROPAD 1               // Pad with zero
#define SIGN    2               // Unsigned/signed long
#define PLUS    4               // Show plus
#define SPACE   8               // Space if plus
#define LEFT    16              // Left justified
#define SPECIAL 32              // 0x
#define LARGE   64              // Use 'ABCDEF' instead of 'abcdef'

#define is_digit(c) ((c) >= '0' && (c) <= '9')
#define random(num)	(rand() % (num));

#define P_16        0xA001


/**
 * @brief . For State machine
 */

#define ENG_ST_UNSPECIFIED	MAX_S32
#define ENG_EV_UNSPECIFIED	MAX_S32

typedef enum
{
	ENG_ST_NONE					= 0,
	ENG_ST_ENTRY				= (0x1 << 0),
	ENG_ST_ACTIVITY				= (0x1 << 1),
	ENG_ST_EXIT					= (0x1 << 2),
	ENG_ST_ALL					= 0x7FFFFFFF
}TStateMaskBit;

/**
 * @brief .
 */
typedef struct
{
	U32 ulState;									/**<  Current State  */ 
	U32 (*pfnGuardCondition)(void *, U32 *, U32);	/**<  Guard Condition  */ 
    U32 ulEvent;									/**<  Event */ 
	U32 ulNextState;								/**<  Next State  */ 	
	void (*pfnTransitionAction)(void *);			/**<  Transition Action  */
	U32 ulTimeout;									/**<  StateTransition Activity Timeout */
} TStateTransitionTbl;

/**
 * @brief .
 */
typedef struct
{
	U32 ulState;							/**<  State ID  */	
	U32 (*pfnEntryAction)(void *);			/**<  Entry function    */ 	
	U32 (*pfnDoActivity)(void *);			/**<  Current state activity function    */ 
	BOOL (*pfnExitAction)(void *);			/**<  Exit function   */ 	
	U8	*pubString;							/**<  State description for debug    */
	U32 ulTimeout;							/**<  StateMachine Activity Timeout */
	TStateMaskBit enExecutedMask;			/**<  This is setted when state was executed */
} TStateMachineTbl;

/**
 * @brief .
 */
typedef struct
{
	U32 ulID;  						/**<  StateMachine ID */ 
	U32 ulPrevState;				/**<  Previous State ID  */ 
	U32 ulState;  					/**<  State ID  */ 
	U32 ulEvent;					/**<  Event  */ 
	U32 ulLMSStateID;				/**<  BBP State ID  */ 
	U32 ulUniqueID;					/**<  Unique ID  */ 
	U32 ulReceivedEvent;			/**<  Received Event  */ 
	U32 ulGuardConditionEvent;		/**<  Received Event  */ 
	U32 (*pfnGuardCondition)(void *, U32 *, U32);	/**<  Guard Condition  */ 
	TStateTransitionTbl *pstSTT;	/**<  state transition table   */
	TStateMachineTbl *pstSMT;		/**<  state machine table   */
	U32 ulTransitionTblSize;		/**<  State transition table size  */
	U32 ulMachineTblSize;			/**<  State machine table size  */
	void *pvStateEntry;				/**<  StateEntry  */
	BOOL fTransitionEnable;			/**<  StateMachine Transition Enable */
	U32 ulTransitionTime;			/**<  StateMachine Transition Time */
	U32 ulTimeCount;				/**<  StateMachine Activity Count */
} TStateMachine;


/**
 * @brief .For Message Queue
 */
typedef struct
{
	U32 ulMsgID;					/**<  Message ID  */ 
	U32 ulLParam;					/**<  Parameter   */ 
	U32 ulRParam;
} TMsgQ;

/**
 * @brief .
 */
typedef struct
{
	volatile BOOL fBusy;
	U32 ulMsgQHead;					/**<  Message Queue Head  */
	U32 ulMsgQTail;					/**<  Message Queue Tail  */
	U32 ulMsgQSize;					/**<  Message Queue Size  */
	TMsgQ *pstMsgQ;					/**<  Message Queue buffer*/ 
} TMsgQCB;

/**
 * @brief .
 */
typedef struct
{
	U32 ulHead;					/**<  Queue Head  */
	U32 ulTail;					/**<  Queue Tail  */
	U32 ulSize;					/**<  Queue Size  */
	void *pvBuffer;				/**<  Queue buffer*/ 
} TQueue;

/**
 * @brief Using the concept of counting semaphore
 */
typedef struct
{
	S8 sbCount;						/**<  Count */ 
//	TEngHandlerID enHndID;			/**<  Handler ID or Queue */
} TSemaphore;


/**
 * @brief For callback lib function
 */
typedef struct
{
	U8	*pubFuncName;
	U32 *pulCallBackFunc;
} TEngLibCallBackFunc;

typedef U32 (*TENGLIB_ETOK_F)(U32, U32);
typedef BOOL (*TENGLIB_ERROR_TBL_INFO_F)(U8 *, U32);
typedef U32 (*TENGLIB_NEWIF_INTERRUPT_F)(U32, U32);
typedef BOOL (*TENGLIB_SM_HNDIF_START_HND_F)(U32, U32, void*);
typedef U32 (*TENGLIB_SM_HNDIF_SENDEVENT_F)(U32, U32, TStateMachine *, U32, U32);

typedef void (*TENGLIB_LMS_ASSERT_EA_F)(U8 *, U32);
typedef U8 * (*TENGLIB_TM_GET_CURRENT_RTC_TIME_F)(U8 *);
typedef void (*TENGLIB_LMS_VM_DEC_SA_F)(BOOL);
typedef void (*TENGLIB_LMS_VM_OVER_EA_F)(U32, void*);
typedef void (*TENGLIB_LMS_VM_CALL_EA_F)(U32, void*);
typedef void (*TENGLIB_LMS_TASKLOG_BUFF_FULL_EA_F)(void);



typedef struct
{
	/* Call Back Function From Upper Layer */
	TENGLIB_ETOK_F pfnIFSvcEtoK;
	TENGLIB_ERROR_TBL_INFO_F pfnGetErrorTableInfo;
	TENGLIB_NEWIF_INTERRUPT_F pfnIFSvcNewIFInterrupt;
	TENGLIB_SM_HNDIF_START_HND_F pfnSMHndIFStartHandler;
	TENGLIB_SM_HNDIF_SENDEVENT_F pfnSMHndIFSendEvent;
	TENGLIB_LMS_ASSERT_EA_F pfnLMSAssertEA;
	TENGLIB_TM_GET_CURRENT_RTC_TIME_F pfnGetCurrentRTCTime;
	TENGLIB_LMS_VM_DEC_SA_F pfnInDecreaseVMCountSA;
	TENGLIB_LMS_VM_OVER_EA_F pfnCheckVMCountOverEA;
	TENGLIB_LMS_VM_CALL_EA_F pfnVMCallByTaskEA;	
	TENGLIB_LMS_TASKLOG_BUFF_FULL_EA_F pfnLMSTaskLogBufferFullEA;
} TEngLib;

#ifdef __ENGLIB_IF_C__
TEngLib stEngLib = {0};
#else
extern TEngLib stEngLib;
#endif

#endif /* __ENGLIB_TYPES_H__ */

