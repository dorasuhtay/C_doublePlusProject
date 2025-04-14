/********************************************************************
 * Filename : EE_Key_Map.h
 *
 * Function : Header setting for EEprom Mapping for KeyPad
 *
 * Company : World Peace International (South Asia) Pte. Ltd.
 *
 * Author : Chaw Chen Song
 *
 ********************************************************************/

#ifndef EE_Key_Map_H
#define EE_Key_Map_H
/*----------------------------------------------------------------------------
					EEPROM Location Mapping
----------------------------------------------------------------------------*/
#define EE_Page0	0x0000
#define EE_Page1	0x0100
#define EE_Page2	0x0200
#define EE_Page3	0x0300
#define EE_Page4	0x0400
#define EE_Page5	0x0500
#define EE_Page6	0x0600
#define EE_Page7	0x0700

// Page 0
#define Loc_Firm_Ver		EE_Page0+0x10

#define Loc_Font_BIG5		EE_Page0+0x20
#define Loc_Contrast		EE_Page0+0x21

#define Loc_Scan_TimeOut	EE_Page0+0x28
#define Loc_Sta_Ret_Time	EE_Page0+0x29
#define Loc_Time_Spc		EE_Page0+0x2E
#define Loc_Date_Spc		EE_Page0+0x2F

#define Loc_Refresh_Default	EE_Page0+0x30
#define Loc_Break_Refresh	EE_Page0+0x31
#define Loc_EmpName_Delay	EE_Page0+0x32
#define Loc_PayOut_Refresh	EE_Page0+0x33
#define Loc_PayOper_Refresh	EE_Page0+0x34

// Station range
#define Loc_Min_Sta			EE_Page0+0x40
#define Loc_Max_Sta			EE_Page0+0x41
// Operation_ID range
#define Loc_Min_OperDigit	EE_Page0+0x42
#define Loc_Max_OperDigit	EE_Page0+0x43
// Emp_ID Digit range
#define Loc_Min_EmpDigit	EE_Page0+0x44
#define Loc_Max_EmpDigit	EE_Page0+0x45

// Sensor Threshold
#define Loc_QThreshold		EE_Page0+0x80
#define Loc_QThreshold_Step	EE_Page0+0x81
#define Loc_QThreshold_Min	EE_Page0+0x82
#define Loc_QThreshold_Max	EE_Page0+0x83
// #define Loc_QThres_Persen	EE_Page0+0x81

// Use for EM chip only
#define Loc_EM_Tset			EE_Page0+0xE0

#define Loc_EM_M_Short_L	EE_Page0+0xE2
#define Loc_EM_M_Short_H	EE_Page0+0xE3
#define Loc_EM_M_Long_L		EE_Page0+0xE4
#define Loc_EM_M_Long_H		EE_Page0+0xE5
//#define Loc_EM_Clk_Low		EE_Page0+0xEE
//#define Loc_EM_Clk_High		EE_Page0+0xEF

//location for PassPin
#define Loc_Pass_Pin	EE_Page0+0xF0

// Page 1
// save default string legend/label
#define Loc_Str_ID		EE_Page1+0x10	//"Station ID: "
//#define 	EE_Page1+0x20
#define Loc_Str_Load	EE_Page1+0x30	//"Loading Station"
#define Loc_Str_UnLoad	EE_Page1+0x40	//"UnLoad Station"
#define Loc_Str_QC		EE_Page1+0x50	//"QC Station"
#define Loc_Str_Bridge	EE_Page1+0x60	//"Bridge Station"
#define Loc_Str_Inspec	EE_Page1+0x70	//"Inspection Stn"
#define Loc_Str_AutoCol	EE_Page1+0x80	//"Auto Collect"

#define Loc_Str_Time	EE_Page1+0xC0	//"Time: "
#define Loc_Str_Date	EE_Page1+0xD0	//"Date: "
#define Loc_Str_AM		EE_Page1+0xE0	// "am"
#define Loc_Str_PM		EE_Page1+0xE8	// "pm"
//#define Loc_Str_TD		EE_Page1+0xF0	// ?? parameter for time ex. 24hour format? ddmmyy?

// Page 2
// String Mode 8
#define Loc_Str_81		EE_Page2+0x10	//"1. Prayer"
#define Loc_Str_82		EE_Page2+0x20	//"2. Break"
#define Loc_Str_83		EE_Page2+0x30	//"3. Repair"
#define Loc_Str_84		EE_Page2+0x40	//"4. Idle"
#define Loc_Str_85		EE_Page2+0x50	//"Re-Scan Card"

// String Mode 9
#define Loc_Str_90		EE_Page2+0x80	//"Check Design Code"
#define Loc_Str_91		EE_Page2+0x90	//"Design Code :"
#define Loc_Str_92		EE_Page2+0xA0	//"Color :"
#define Loc_Str_93		EE_Page2+0xB0	//"Size :"
#define Loc_Str_94		EE_Page2+0xC0	//"PPB :"
#define Loc_Str_95		EE_Page2+0xD0	//"Scan Tag Here"

// Page 3
// String F
#define Loc_Str_F1		EE_Page3+0x10	//"Dest. ID: "
#define Loc_Str_F2		EE_Page3+0x20	//"Find QC. "
#define Loc_Str_F3		EE_Page3+0x30	//"Move to Station"
#define Loc_Str_F1A		EE_Page3+0x50	//"Operation ID: "
#define Loc_Str_4		EE_Page3+0x40	//"QC. Report"
// String Station ID Update
#define Loc_Str_PLogIn	EE_Page3+0x60	//"Pls. LogIn First"
#define Loc_Str_SCard	EE_Page3+0x70	//"Scan Card"
#define Loc_Str_RFIDNo	EE_Page3+0x80	//"RFID Number"
#define Loc_Str_Oper	EE_Page3+0x90	//"Oper. Name"
#define Loc_Str_EmpID	EE_Page3+0xA0	//"Emp. ID"
#define Loc_Str_PLogOut	EE_Page3+0xB0	//"Pls. LogOut"
#define Loc_Str_LogOut	EE_Page3+0xC0	//"Log Out?"
#define Loc_Str_SOver	EE_Page3+0xD0	//"Shift Over"
#define Loc_Str_Help1	EE_Page3+0xE0	//"Requesting"
#define Loc_Str_Help2	EE_Page3+0xF0	//"Help"

// Page 4
// Testing/Configuration
#define Loc_Str_Pass	EE_Page4+0x10	//"PassKey"
#define Loc_Str_CMode	EE_Page4+0x20	//"Mode Selection"
#define Loc_Str_N_Sta	EE_Page4+0x30	//"New Sta. No.: "
#define Loc_Str_Test	EE_Page4+0x40	//"Testing Mode"
#define Loc_Str_DRel00	EE_Page4+0x50	//"Select the Relay"
#define Loc_Str_DRel01	EE_Page4+0x60	//"Relay Dly Fire"
#define Loc_Str_DRel02	EE_Page4+0x70	//"ms"
#define Loc_Str_DRel03	EE_Page4+0x80	//"Relay Dly UnFire"
#define Loc_Str_DMotor	EE_Page4+0x90	//"Motor Delay"
#define Loc_Str_QThres	EE_Page4+0xA0	//"Sensor Threshold"
#define Loc_Str_Contras	EE_Page4+0xB0	//"LCD Contrast"
#define Loc_Str_AutoTim	EE_Page4+0xC0	//"Auto Test Delay"
#define Loc_Str_StaVer	EE_Page4+0xD0	//"Sta. Version".
#define Loc_Str_KeyVer	EE_Page4+0xE0	//'Key Version"
#define Loc_Auto_Pat	EE_Page4+0xF0	//Parameter for testing Auto Relay

//Page 5
// Error Page
#define Loc_Str_Err0	EE_Page5+0x10	//"     ERROR     "
#define Loc_Str_Err1	EE_Page5+0x20	//" Communication "
//#define Loc_Str_Range	EE_Page5+0x30	//"Station"
//#define Loc_Str_OpErr	EE_Page5+0x40	//"Operation Digit"
#define Loc_Str_QF3		EE_Page5+0x50	//"Quit Move 1st"
#define Loc_Str_Err2	EE_Page5+0x60	//"   Com Error   "
#define Loc_Str_ORange	EE_Page5+0x70	//"Out of Range"

#define Loc_Str_Range	EE_Page5+0x80	//"Station"
#define Loc_Str_OpErr	EE_Page5+0x90	//"Operation Digit"
#define Loc_Str_EmpErr	EE_Page5+0xA0	//"Emp. ID Digit"

#define Loc_Str_TimOut	EE_Page5+0xB0	//"Time Out"
#define Loc_Str_STOut	EE_Page5+0xC0	//"Server TimeOut"
#define Loc_Str_LogErr	EE_Page5+0xD0	//" Log In Error "
#define Loc_Str_HRst	EE_Page5+0xE0	//"Hardware Reset"
#define Loc_Str_Emer	EE_Page5+0xF0	//"EMERGENCY STOP"

//Page 6
// Network Testing
#define Loc_Net_Time		EE_Page6+0x10
#define Loc_Net_Time_Step	EE_Page6+0x11
#define Loc_Net_Time_Min	EE_Page6+0x12
#define Loc_Net_Time_Max	EE_Page6+0x13

#define Loc_Auto_Time		EE_Page6+0x18	//Timing
#define Loc_Auto_Time_Step	EE_Page6+0x19
#define Loc_Auto_Time_Min	EE_Page6+0x1A
#define Loc_Auto_Time_Max	EE_Page6+0x1B

#define Loc_Str_StaTst		EE_Page6+0x20	//"Network Test"
#define Loc_Str_NT_Time		EE_Page6+0x30	//"Network Delay"

#define Loc_Str_POSw		EE_Page6+0x80	//"Press Oper. Sw."
#define Loc_Str_MovHang		EE_Page6+0x90	//"Moving Hanger to"

// Station function Display
#define Loc_Sta_Nor			EE_Page6+0xE0	//Normal Station
#define Loc_Sta_Nor_Stat	EE_Page6+0xE1
#define Loc_Sta_Load		EE_Page6+0xE2	//Loading Station
#define Loc_Sta_Load_Stat	EE_Page6+0xE3
#define Loc_Sta_UnLoad		EE_Page6+0xE4	//UnLoading Station
#define Loc_Sta_UnLoad_Stat	EE_Page6+0xE5
#define Loc_Sta_QC			EE_Page6+0xE6	//QC Station
#define Loc_Sta_QC_Stat		EE_Page6+0xE7

#define Loc_Sta_Brid		EE_Page6+0xE8	//Bridge Station
#define Loc_Sta_Brid_Stat	EE_Page6+0xE9
#define Loc_Sta_Inspec		EE_Page6+0xEA	//Inspcetion Station
#define Loc_Sta_Inspec_Stat	EE_Page6+0xEB
#define Loc_Sta_AutoCo		EE_Page6+0xEC	//Auto-Collection Station
#define Loc_Sta_AutoCo_Stat	EE_Page6+0xED
//#define Loc_Sta_??			EE_Page6+0xEE	//?? Station
//#define Loc_Sta_??_Stat		EE_Page6+0xEF

/*----------------------------------------------------------------------------
			String display on the LCD
----------------------------------------------------------------------------*/
// ---- Page 1
// save default string legend/label
//                 //1234567890123456
#define Str_ID		"Station ID:"
#define Str_Load	"Loading Station"
#define Str_UnLoad	" UnLoad Station"
#define Str_QC		" Q. C. Station"
#define Str_Bridge	" Bridge Station"
#define Str_Inspec	"Inspection Stn."
#define Str_AutoCol	"Auto Collection"

#define Str_Time	" Time: "
#define Str_Date	" Date: "
#define Str_AM		"am"
#define Str_PM		"pm"

// #define Str_Time	"时间 :"	//0xCA 0xB1 0xBC 0xE4
// #define Str_Date	"日期 :"	//0xC8 0xD5 0xC6 0xDA
// #define Str_AM	"上午"		//0xC9 0xCF 0xCE 0xE7
// #define Str_PM	"下午"		//0xCF 0xC2 0xCE 0xE7
//#define Str_TD

// ---- Page 2
// String Mode 8   //1234567890123456
#define Str_81		"   1. Prayer"
#define Str_82		"   2. Break"
#define Str_83		"   3. Repair"
#define Str_84		"   4. Idle"
#define Str_85		"Re-Scan Card"

// String Mode 9   //1234567890123456
#define Str_90		"Check DSN Code"
#define Str_91		"Design:"
#define Str_92		"Color:"
#define Str_93		"Size:"
#define Str_94		"PPB:"
#define Str_95		"Scan Tag Here"

// ---- Page 3
// String F   	   //1234567890123456
#define Str_F1		"Go Dest. ID: "
#define Str_F2		"Find Q. C."
#define Str_F3		"Move to Station"
#define Str_F1A		"Go Oper. ID: "
#define Str_4		"Q. C. Report"

// String Station ID Update
//                 //1234567890123456
#define Str_PLogIn	"  Log In First"
#define Str_SCard	"Scan Card"
#define Str_RFIDNo	"RFID Number"
#define Str_Oper	"Operator Name"
#define Str_EmpID	"Emp. ID"
#define Str_PLogOut	" Please Log Out"

#define Str_LogOut	"Log Out???"

#define Str_SOver	"   Shift Over"
#define Str_Help1	"   Requesting"
#define Str_Help2	"      Help"

// Testing/Configuration
// ---- Page 4     //1234567890123456
#define Str_Pass	"PassKey"
#define Str_CMode	"Mode Selection"

#define Str_N_Sta	"New Sta. No.: "
#define Str_Test	"Testing Mode"
#define Str_DRel00	"Select the Relay"
#define Str_DRel01	"Delay Fire: "
#define Str_DRel02	"ms"
#define Str_DRel03	"Delay Unfire: "
#define Str_DMotor	"Motor Delay"
#define Str_QThres	"Sensor Threshold"
#define Str_Contras	"LCD Contrast"
#define Str_AutoTim	"Auto Test Delay"
#define Str_StaVer	"Sta. Version"
#define Str_KeyVer	"Key Version"

// ERROR Message
// ---- Page 5	   //1234567890123456
#define Str_Err0	"     ERROR"
#define Str_Err1	" Communication"
#define Str_QF3		"  Quit Move 1st"
#define Str_Err2	"   Com. Error"
#define Str_ORange	"  Out of Range "
#define Str_Range	"   Station No."
#define Str_OpErr	" Oper. ID Digit"
#define Str_EmpErr	" Emp. ID Digit"
#define Str_TimOut	"    Time Out"
#define Str_STOut	" Server TimeOut"
#define Str_LogErr	"  Log In Error"
#define Str_HRst	" Reset Hardware"
#define Str_Emer	" EMERGENCY STOP"

// Network Test
// ---- Page 6	   //1234567890123456
#define Str_StaTst	"Network Test"
#define Str_NT_Time	"Network Delay"

#define Str_POSw	"Press Oper. Sw."
#define Str_MovHang	"Moving Hanger"
//---------------------------------
#endif // EE_Key_Map_H
