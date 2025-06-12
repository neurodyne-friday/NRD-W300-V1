 /**
 * @file        Eng_CommandTypes.h
 * @brief       This is type definition file for common
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
 * @dept		Embedded Developement Team
 * @date		19/02/2024(D/M/Y)
 * @version		V0.1
 */


/* Command - General */
#define COMMAND_FACTORY                     'F'
#define COMMAND_INITIALIZE                  'I' 
#define COMMAND_READ_STATUS                 'S' 
#define COMMAND_PROCESS_LOG                 'R' 
#define COMMAND_EXECUTE_DOWNLOAD            'D' 
#define COMMAND_TEST                        'T' 
#define COMMAND_SERIAL_WRITE			    'W' 
#define COMMAND_SERIAL_READ				    'C' 
#define COMMAND_USER_OPERATION			    'U'
#define SUB_USER_OPERATION			        'O'

/* Command - Cash-In */
#define COMMAND_CASH_IN                     'S' 
#define COMMAND_READ                        'R'
#define COMMAND_WRITE                       'W'
#define COMMAND_CLEAR                       'C'
#define COMMAND_RESET_JAM				    'J'
#define COMMAND_EXECUTE_APPLICATION		    'A' 


/* SubCommand - Application */
#define SUBCOMMAND_APPLICATION_JUMP         '0'
#define SUBCOMMAND_ACCOUNT_END              'E'
#define SUBCOMMAND_EXECUTE_APPLICATION	    'A' 

/* SubCommand - Downloader */
#define SUBCOMMAND_DOWNLOADER_JUMP          '0'

/* SubCommand - Read Status */
#define SUBCOMMNAD_READ_SENSORSTATUS        'T'  // Sensor Subcommand.
#define SUBCOMMAND_SET_BOXLIMIT			    'B'
#define SUBCOMMAND_READ_COUNT			    'C'

/* SubCommand - MovePlate */
#define SUBCOMMAND_MOVE_TOP_POSITION        'T'
#define SUBCOMMAND_MOVE_BOTTOM_POSITION     'B'
#define SUBCOMMAND_MOVE_READY_POSITION      'R'

/* SubCommand - Cash In Start  & CMD_ACTION */ /* SubCommand - CASH_ACTION */
#define SUBCOMMAND_CASH_IN_STANDBY          'B'
#define SUBCOMMAND_CASH_IN_READY            'R'
#define SUBCOMMAND_CASH_IN_START            'S'

/* SubCommand - Log */
#define SUBCOMMAND_CLEAR_LOG                'L'
#define SUBCOMMAND_READ_LOG                 'D'
#define SUBCOMMAND_READ_VERSION             'V'
#define SUBCOMMAND_READ_SENSOR              'S'
#define SUBCOMMAND_READ_COMPACTLOG		    'D'

/* SubCommand - Rest */
#define SUBCOMMAND_RESET_JAM_CASH_IN_READY  'R'
#define SUBCOMMAND_RESET_JAM_CASH_IN_START  'S'
#define SUBCOMMAND_RESET_JAM_CASH_IN        'J'

/* SubCommand - Write */
#define SUBCOMMAND_WRITE_DATA				'C'

/* SubCommand - Factory */
#define SUBCOMMAND_FACTORY_TEST				'I'

/* Test SubCommand*/
#define SUBCOMMAND_RJP_MOTOR_ON             '1'
#define SUBCOMMAND_RJP_MOTOR_OFF            '2'
#define SUBCOMMAND_RJP_DIVERTERUPDOWN       '3'


/* Command - UserCommand : Start */
#define CMD_USER_COMMAND					'U'

#define USER_COMMAND_SENSOR		            0x81
#define USER_COMMAND_DIVERTER	            0x82
#define USER_COMMAND_MOTOR		            0x83
#define USER_COMMAND_MEMORY		            0x84

#define USER_COMMAND_SENSOR_LEVELING		0x11
#define USER_COMMAND_SENSOR_SHORT_ON		0x12
#define USER_COMMAND_SENSOR_SHORT_OFF		0x13
#define USER_COMMAND_SENSOR_LONG_ON			0x14
#define USER_COMMAND_SENSOR_LONG_OFF		0x15
#define USER_COMMAND_SENSOR_INT_ON			0x16
#define USER_COMMAND_SENSOR_INT_OFF			0x17
#define USER_COMMAND_SENSOR_ALL_ON			0x18
#define USER_COMMAND_SENSOR_ALL_OFF			0x19

#define USER_COMMAND_MOTOR_STOP				0x31
#define USER_COMMAND_MOTOR_LOWSPEED_CW		0x32
#define USER_COMMAND_MOTOR_NORMALSPEED_CW	0x33
#define USER_COMMAND_MOTOR_FASTSPEED_CW		0x34
#define USER_COMMAND_MOTOR_JAMRESET_CW		0x35
#define USER_COMMAND_MOTOR_LOWSPEED_CCW		0x36
#define USER_COMMAND_MOTOR_NORMALSPEED_CCW	0x37
#define USER_COMMAND_MOTOR_FASTSPEED_CCW	0x38
#define USER_COMMAND_MOTOR_JAMRESET_CCW		0x39
#define USER_COMMAND_MOTOR_PLATE_MOVE_FULL	0x3a
#define USER_COMMAND_MOTOR_PLATE_MOVE_READY	0x3b
#define USER_COMMAND_MOTOR_PLATE_MOVE_TOP	0x3c
#define USER_COMMAND_MOTOR_PLATE_MOVE_COMPRESS	0x3d

#define USER_COMMAND_MEMORY_CLEAR			0x41
#define USER_COMMAND_MEMORY_TEST			0x42