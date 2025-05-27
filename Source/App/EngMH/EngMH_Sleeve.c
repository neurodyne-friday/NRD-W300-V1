#include "Eng_CommonType.h"
#include "EngMH_Types.h"
#ifdef BOOT_LOADER
	#include "EngMD_Ctrl_BOOT.h"
	vu8 g_vu8State[MAX_MODULE_NUM];
#endif

PRIVATE TSleeveDB s_stSleeveDB;

TSleeveDB* EngMH_Sleeve_GetDB(void)
{
	return &s_stSleeveDB;
}

void EngMH_Sleeve_Control(void)
{
	TSleeveDB* pstDB = EngMH_Sleeve_GetDB();
	TCAN* pstCAN = EngDrv_IF_GetCAN(CAN_NAME_MOTOR_CTRL);
	TCanCommand* pstCommand;
	OS_ERR		err;
    OS_MSG_SIZE	msg_size;
    CPU_TS		ts;

	
	while(1)
	{
#ifndef BOOT_LOADER
		
		if(err == OS_ERR_NONE)
		{
			EngMD_RJP_Main(TRUE);
		}
		else
		{
			EngMD_RJP_Main(FALSE);
		}
#else
		//240328-KHR : 한시적으로 Boot시 Dip Switch 4번이 1초 이상 On일 경우 AP로 Jump, boot후 Dip Switch 변경 인식 안함.
		if((EngMD_GetBoardType() & 0x08) == 0x00 && u16Cnt++ >= 100)		//10msec 단위로 Pend Timeout 발생하므로 100회 수행시 1sec.
		{
			//ExecuteApplication();
			EngMD_Ctrl_BOOT_ExecuteApplication();
		}
	#ifdef D_NEW_PLATFORM
		pstCommand = OSQPend(&pstModule->osqCommandQ, 10, OS_OPT_PEND_BLOCKING, &msg_size, &ts, &err);
	#else//D_NEW_PLATFORM
		commandData = OSQPend(&g_sModuleCommandQ[MODULE_TRAY], 10, OS_OPT_PEND_BLOCKING, &msg_size, &ts, &err);
	#endif//D_NEW_PLATFORM

		if(err != OS_ERR_NONE)
		{
			continue;
		}

		if(pstCommand->uwLength < 1)
		{
			//ComposeResponse(commandData->module, commandData->command, ERR_INVALID_COMMAND, NULL, 0);
			EngMD_Ctrl_BOOT_ComposeResponse(pstCommand->ubModuleIndex, pstCommand->uwCommand, ERR_INVALID_COMMAND, NULL, 0);
			continue;
		}

		//SetCommandState(commandData->module, BOOT_STATE_RUNNING);
		SetCommandState(pstCommand->ubModuleIndex, BOOT_STATE_RUNNING);

		// Process Command
		//
		//switch( commandData->command )
		switch(pstCommand->uwCommand)
		{
			case RJP_COMMAND_D0: // BOOT JUMP
			case DOWNLOAD_PROTECT_MEMORY:
			case DOWNLOAD_UNPROTECT_MEMORY:
				//ComposeResponse(commandData->module, commandData->command, ERR_NONE, NULL, 0);
				EngMD_Ctrl_BOOT_ComposeResponse(pstCommand->ubModuleIndex, pstCommand->uwCommand, ERR_NONE, NULL, 0);
				break;
			case RJP_COMMAND_A0: // AP JUMP
				//if( VerifyCrc(commandData) == TRUE )
				if(EngMD_Ctrl_BOOT_VerifyCrc(pstCommand) == TRUE)
				{
					//ExecuteApplication();
					EngMD_Ctrl_BOOT_ExecuteApplication();
				}
				break;
			case RJP_COMMAND_RV: // Read Version
				//GetReadVersionInBoot(commandData);
				EngMD_Ctrl_BOOT_GetReadVersionInBoot(pstCommand);
				break;
			case DOWNLOAD_DELETE_MEMORY: // Download Command
				//DeleteMemory(commandData);
				EngMD_Ctrl_BOOT_DeleteMemory(pstCommand);
				break;
			case DOWNLOAD_READ_MEMORY:
				//ReadMemory(commandData);
				EngMD_Ctrl_BOOT_ReadMemory(pstCommand);
				break;
			case DOWNLOAD_WRITE_MEMORY:
				//WriteMemory(commandData);
				EngMD_Ctrl_BOOT_WriteMemory(pstCommand);
				break;
			case DOWNLOAD_BEGIN_IAP:
				//BeginIAP(commandData);
				EngMD_Ctrl_BOOT_BeginIAP(pstCommand);
				break;
			case DOWNLOAD_VERIFY_CRC:
				//VerifyCrc(commandData);
				EngMD_Ctrl_BOOT_VerifyCrc(pstCommand);
				break;
			case DOWNLOAD_END_IAP:
				//EndIAP(commandData);
				EngMD_Ctrl_BOOT_EndIAP(pstCommand);
				break;
			default: // Undefined Command
				//ComposeResponse(commandData->module, commandData->command, ERR_UNDEFINED_COMMAND, NULL, 0);
				EngMD_Ctrl_BOOT_ComposeResponse(pstCommand->ubModuleIndex, pstCommand->uwCommand, ERR_UNDEFINED_COMMAND, NULL, 0);
				break;
		}

		//SetCommandState(commandData->module, BOOT_STATE_WAITING);
		SetCommandState(pstCommand->ubModuleIndex, BOOT_STATE_WAITING);
#endif //	#ifndef BOOT_LOADER
	}
}


//End Of File
