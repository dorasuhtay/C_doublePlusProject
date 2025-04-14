/*
 * command.h
 *
 * Created: 9th. Feb., 2012 10:00 AM
 * Author: Chaw CS
 */
#ifndef COMMAND_H_
#define COMMAND_H_

#define PUSHERCOUNT			0x01	//1		//(SM)	Pusher sensor from the master board
#define LOGIN_ID			0x0A	//10	//(SM)	For employee to login their id at terminal. By pressing keypad "0". After which lcd will display employee name
#define RFID_ID				0x0B	//11	//(SM)	The hanger RFID
#define LOGOUT_ID			0x0C	//12	//(SM)	For employee to login at terminal. By pressing "0" button  to login at keypad
#define TIME_ID				0x0D	//13	//(SM)	Time
#define ALOGON_ID			0x0E	//14	//(SM)	Auto login
#define ALOGOUT_ID			0x0F	//15	//(SM)	Auto Logout
#define SHIFTOVERMSG_ID		0x10	//16	//(SM)	Shift Over
#define LHANGER_ID			0x11	//17	//(SM)	Record Last Hanger Id
#define ALIVE_ID			0x12	//18	//(SM)	Tested With Machince
#define LOGIN_ERR			0x13	//19	//(WPI)	Login Error

#define NORMAL_STN_ID		0x38	//56	//(WPI) Set it to normal Station

#define EMPNAME_ID			0x46	//70	//(SM)	Employee Name
#define EMP_ID				0x47	//71	//(SM)	Employee Id
#define STATION_ID			0x48	//72	//(SM)	Station Id
#define DATE_ID				0x49	//73	//(SM)	Date
#define OPERATION_ID		0x4A	//74	//(SM)	Operation Id
#define HANGERNO_ID			0x4B	//75	//(SM)	Hanger id
#define QCFUNCTION_ID		0x4C	//76	//(SM)	Server inform the station to be QC station
#define QCHANGER_ID			0xBE 	//190	//(WPI)	Register the hanger at the qc station

#define BRIDGESTN_ID		0xBC 	//188	//(WPI)	Bridge Station id
#define BRIDGEHANGER_ID		0xBD	//189	//(WPI)	Register the hanger at the bridge station
#define BRIDGELCD_ID		0xBF	//191	//(WPI)	Info display on LCD moving to which IP

#define ISLOADING_ID		0x4D	//77	//(SM)	Whether station is load station
#define REMOVEHISTORY_ID	0x4E	//78	//(SM)	Remove history
#define LOADHANGER_ID		0x4F	//79	//(SM)	Register the hanger at the load station

#define UNLOADING_ID		0xE0	//224	//(WPI)	Unload station ID
#define UNLOAD_HANGER_ID	0xE1	//225	//(WPI)	Register the hanger at the unload station

#define ADDLOADCOUNT_ID		0x50	//80	//(SM)	Add total pieces count for the load station
#define ISLASTSTN_ID		0x51	//81	//(SM)	Whether its last station

#define INSPEC_STN_ID		0x52	//82	//(WPI) Set to Inspection Station
#define INSPECHANGER_ID		0x53	//83	//(WPI) Register the hanger at Inspection station

#define AUTOCOL_STN_ID		0x54	//84	//(WPI) Set to Auto Collection Station
#define AUTOCOLHANGER_ID	0x55	//85	//(WPI) Register the hanger at Auto Collection Station

#define CHECKSEQ_ID			0x56	//86	//(SM)	Whether its correct sequence
#define ISREWORK_ID			0x57	//87	//(SM)	Whether hanger is a rework or not for that station
#define ADDREWORK_ID		0x58	//88	//(SM)	Add total pieces count for hanger to rework on that station
#define ADDCOUNT_ID			0x59	//89	//(SM)	Add total pieces count for all station

#define FINDNXTSTN_ID		0x5B	//91	//(SM)	Find next station based on operation
#define FINDLOADINGSTN_ID	0x5C	//92	//(SM)	Find loading station
#define FINDOVERLOADSTN_ID	0x5D	//95	//(SM)	Find overload station
//F1
#define GOSTN_ID			0x3C	//60	//(SM)	Activate request for Go Station function (send station no destination)
#define GOSTN_ID_RFID		0x2C	//44	//(WPI)	RFID code after Go Station Cmd.
#define RETURN_GOSTN_ID		0x40	//64	//(SM)	Activate outfeed Go station function based on the GOSTN_ID (by sending hanger id)
//F2
#define FINDQCSTN_ID		0x60	//96	//(SM)	Activate request for finding QC station function
#define FINDQC_ID_RFID		0x63	//99	//(WPI)	RFID code after FIND_QCSTN command.
#define RETURN_FINDQCSTN_ID	0x41	//65	//(SM)	Activate outfeed find qc station function based on the FINDQCSTN_ID (by sending hanger id)
//F3
#define MOVETO_ID			0x3D	//61	//(SM)	Activate request for Move station function (send station no destination)
#define MOVTO_ID_RFID		0x37	//55	//(WPI)	RFID code after Move to station Cmd.
#define RETURN_MOVETO_ID	0x42	//66	//(SM)	Activate outfeed Move station function based on the station destination (by sending hanger id)
#define CANCEL_MOVETO_ID	0x3F	//63	//(SM)	Cancel the MoveStn command
#define RET_CANCEL_MOVETO	0x44	//68	//(SM)	To stop "MoveStn"
//F4
#define GO_OPER_ID			0x34	//52	//(WPI)	Activate request for Go function using operation ID (Station fix by server)
#define GO_OPER_ID_RFID		0x35	//53	//(WPI)	RFID code after Go Operation CMD
#define RETURN_GO_OPER_ID	0x36	//54	//(WPI)	Acti
// 4
#define QCREPORT_ID			0x3E	//62	//(SM)	Activate request for display QC report description
#define RETURN_QCREPORT_ID	0x43	//67	//(SM)	Display at the Lcd the QC report description
// 5
#define PIECERATE_ID		0x14	//20	//(SM)	LCD display piecerate
#define EFFICIENCY_ID		0x15	//21	//(SM)	LCD display efficiency
#define TOTALPIECES_ID		0x16	//22	//(SM)	LCD display total piece count
#define TOTALPAY_ID			0x17	//23	//(SM)	LCD display total pay
#define PAYCAT_ID			0x18	//24	//(SM)	LCD display pay catagory
// 8
#define PRAYER_ID			0x1E	//30	//(SM)	Prayer
#define BREAK_ID			0x1F	//31	//(SM)	Break
#define REPAIR_ID			0x20	//32	//(SM)	Repair
#define IDLE_ID				0x21	//33	//(SM)	Idle
#define RETURN_ID			0x22	//34	//(SM)	Return from Break RFID
#define RETURN_PRAYER		0x23	//35	//(SM)	Return from Prayer
#define RETURN_BREAK		0x24	//36	//(SM)	Return from Break
#define RETURN_REPAIR		0x25	//37	//(SM)	Return from Repair
#define RETURN_IDLE			0x26	//38	//(SM)	Return from Idle
#define RETURN_EMP_ID		0x2E	//46	//(WPI)	Return from break with emp. id
// 9
#define CHECK_DESIGN_ID		0x32	//50	//(WPI)	Check the Design code
#define DSNCODE_ID			0x28	//40	//(SM)	Show Design Code
#define COLOR_ID			0x29	//41	//(SM)	Show Color
#define SIZE_ID				0x2A	//42	//(SM)	Show Size
#define PPB_ID				0x2B	//43	//(SM)	Show piece per hanger
// H
#define HELP_ID				0x27	//39	//(SM)	To show the HELP notification
#define CANCEL_HELP_ID		0x2D	//45	//(WPI)	Cancel the help command

//Output Relay
#define RL1FIRE				0x65	//101	//(SM)	Outfeed
#define RL2FIRE				0x66	//102	//(SM)	Infeed A
#define RL3FIRE				0x67	//103	//(SM)	Infeed B
#define RL4FIRE				0x68	//104	//(SM)	1/2 CAM
#define RL5FIRE				0x69	//105	//(SM)	Motor
//#define RL6FIRE         //???

#define RL1UNFIRE			0x6A	//106	//(SM)	Outfeed
#define RL2UNFIRE			0x6B	//107	//(SM)	Infeed A
#define RL3UNFIRE			0x6C	//108	//(SM)	Infeed B
#define RL4UNFIRE			0x6D	//109	//(SM)	1/2 CAM
#define RL5UNFIRE			0x6E	//110	//(SM)	Motor
//#define RL6UNFIRE       //???
// Sensor Input
#define OP1FIRE				0xC9	//201	//(SM)	Half Full A
#define OP2FIRE				0xCA	//202	//(SM)	Half Full B
#define OP3FIRE				0xCB	//203	//(SM)	Full A
#define OP4FIRE				0xCC	//204	//(SM)	Full B
#define OP5FIRE				0xCD	//205	//(SM)	Elevator ON switch
#define OP6FIRE				0xCE	//206	//(SM)	Counter Sensor Switch
#define OP7FIRE				0xCF	//207	//(SM)	Operator ON Switch
#define OP8FIRE				0xD0	//208	//(SM)	OverLoad Sensor
#define OP9FIRE				0xD1	//209	//(SM)	Select Sensor Infeed A
#define OP10FIRE			0xD2	//210	//(SM)	Select Sensor Infeed A

#define OP1UNFIRE			0xD3	//211	//(SM)	Half Full A
#define OP2UNFIRE			0xD4	//212	//(SM)	Half Full B
#define OP3UNFIRE			0xD5	//213	//(SM)	Full A
#define OP4UNFIRE			0xD6	//214	//(SM)	Full B
#define OP5UNFIRE			0xD7	//215	//(SM)	Elevator ON switch
#define OP6UNFIRE			0xD8	//216	//(SM)	Counter Sensor Switch
#define OP7UNFIRE			0xD9	//217	//(SM)	Operator ON Switch
#define OP8UNFIRE			0xDA	//218	//(SM)	OverLoad Sensor
#define OP9UNFIRE			0xDB	//219	//(SM)	Select Sensor Infeed A
#define OP10UNFIRE			0xDC	//220	//(SM)	Select Sensor Infeed A

#define STATION_ACK			0x45	//69	//(SM)	Station's acknowledge for poll cmd.
#define MASTER_POLL			0xBB	//187	//(WPI)	Master poll for sensor input data.
#define REQ_OFFLINE_DEV		0xB9	//185	//(WPI)	Server request Master to send Off_Line devices.
#define RET_OFFLINE_DEV		0xBA	//186	//(WPI)	Master reply Off_Line devices.

#define ERROR_ID			0x6F	//111	//(WPI)	Error Code if Station is off_line.
#define TIME_OUT_ID			0x70	//112	//(WPI) Error code if Message from server is time out.
#define BAD_CRC_ID			0xE6	//228	//(WPI)
#define PC_MSG_ACK			0xE7 	//231 	//(WPI) Acknowledge from Server to Master Message sent.

#define POLL_RANGE_ID		0xB7	//183 	//(WPI)	Command ID to update poll range for master unit.
#define SOFT_RST_ID			0xB8	//184	//(WPI)	Command to do Software Reset to stations.

#define REQ_TIME_ID			0x78	//120	//(WPI)	Request time
#define REQ_DATE_ID			0x79	//121	//(WPI)	Request Date
#define OPR_START_CMD_ID	0xE3	//227	//(WPI) Command to Master for operation startup.
#define REQ_OPR_START_ID	0xE4	//228 	//(WPI) Command to Server for operation startup.
#define SHUTDOWN_ID			0xE5	//229	//(WPI) Command to Master to shutdown.

#define SCR_DISPLAY			0xEE	//238	//(WPI) Display the message on Screen. [SOT,CMD,Len,X-col(ASCII),Y-row(ASCII),Data(ASCII) ... ,EOT]

#define NEW_RFID			0xE2	//226	//(WPI) Command to LCD to display New RFID read.

#define HANGER_ERROR		0x88	//136	//(WPI) Hanger error

#define ACCEPT_IN_RANGE		0x75	//117	//(WPI) Station/Operation send to server in range
#define ERROR_OUT_RANGE		0x76	//118	//(WPI) Station/Operation send to server OUT of range
#define ABORT_COMMAND		0x77	//119	//(WPI) Abort the current command

//Command definitions for communication between Keypad and Station/Slave

#define PROG_STATION_ID		0x80	//128	//(WPI)	Command to ask the slave to save the id
#define REQ_STATION_ID		0x81	//129	//(WPI)	Ask the slave for ID
#define RET_REQ_STATION_ID	0x82	//130	//(WPI)	Return from the slave with ID

#define QUERY_FIRM_VER_ID	0x9A	//154	//(WPI)	Ask Firmware version of Station/Master from Keypad.
#define RET_FIRM_VER_ID		0x9B	//155	//(WPI)	Return Station/Master Firmware Version to display on LCD.

#define PROG_EEPROM_KEY		0xA0	//160	//(WPI)	Programming the EEPROM, format [SOT,CMD,Len,EEAdd_Hi,EEAdd_Lo,EEDATA,EOT]
#define READ_EEPROM_KEY		0xA1	//161	//(WPI)	Read the EEPROM data, [SOT,CMD,Len,EEAdd_Hi,EEAdd_Low,No_Data,EOT]
#define RET_EEPROM_KEY		0xA2	//162	//(WPI)	Return the request (Read) EEPROM data

#define TEST_MODE_START		0xA6	//166	//(WPI)	Go to Test_Mode
#define TEST_MODE_END		0xA7	//167	//(WPI)	End Test_Mode
#define TEST_RELAY_ID		0xA8	//168	//(WPI)	Key to station testing the relay, [SOT,Test_Relay,Len,Data,EOT]
#define TEST_SENSOR_ID		0xA9	//169	//(WPI)	Station to Key testing the switch/sensor [SOT,Test_Sensor,Len,Data1,Data2,EOT]
#define TEST_RFID_ID		0xAA	//170	//(WPI)	Station to Key testing the RFID on Station [SOT,Test_RFID,Len,RFID_No,RFID_Data(10)/i-Button(8),EOT]

#define PROG_EEPROM_STN		0xB0	//176	//(WPI)	Programming the EEPROM, format [SOT,CMD,Len,EEAdd_Hi,EEAdd_Lo,EEDATA,EOT]
#define READ_EEPROM_STN		0xB1	//177	//(WPI)	Read the EEPROM data, [SOT,CMD,Len,EEAdd_Hi,EEAdd_Low,No_Data,EOT]
#define RET_EEPROM_STN		0xB2	//178	//(WPI)	Return the request (Read) EEPROM data

#define PROG_RDELAY_ID		0xB4	//180	//(WPI)	Delay for Relay
#define REQ_RDELAY_ID		0xB5	//181	//(WPI)	Request for Relay Delay parameter (0x0D for motor delay)
#define RET_REQ_RDELAY_ID	0xB6	//182	//(WPI)	Reply to Request

#define CHANGE_PASSWORD		0x8F	//143	//(WPI)	Command to change the KeyPad Password, stored in EEPROM

//#define STN_STATUS			0xF0	//240	//(WPI) Command to query station whether need to ask TIME or not.

#define EMERGENCY_STOP		0x99	//153	//(WPI) Emergency Stop the whole line.

#endif /* COMMAND_H_ */

