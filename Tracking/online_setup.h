//#define OLD_STYLE_WRITE
//----------------------------------------------------------------------------------------
// The default setting are stored in an application INI file (similar to the windows.ini format)
// If changed 
//   delete the file (before delete if you have important previous settings, mae a copy)
//   const char applicationINIfile[] = "applicationSetting.ini\0";
//   see "applicationSetting.h" and "applicationSetting.cpp"
// let it automatically re-create
//----------------------------------------------------------------------------------------
#define FULL_RELEASE

#define Application_TITLENAME			L"MRT-Online Server "// U_S(woSTwACK)"
#define Application_VERSION				"V2.7.6(long13*4)wlongStop(Total) unlimit"
#define Application_BUILDNUMBER			"Build  2013.10.02 6:19"
#define Application_TRAYTITLENAME		Application_TITLENAME
//-----------------------------------------------------------------------------------------
//Factory default values... to have these values effective the application.ini should be 
//deleted and automatically re-created by these values.
//defines the number of Chain links. Physically count the chain links and change this value
//for installation to installation
//-----------------------------------------------------------------------------------------
#define NumberofCHAINLINKS__						14		
#define Max_NumberofPUSHER__						35
#define Max_NumberofSTATIONS__						100
#define MAX_OVERLOAD_ROUNDS__						3		//rounds
#define MaxBundleNo__								9999
//-----------------------------------------------------------------------------------------
//Factory default values... to have these values effective the application.ini should be 
//deleted and automatically re-created by these values.
//to adjust for mechanical error number depends on the motor stop delays. Some motor need a value of 8 and some need 4
//depending on motor this must be adjusted by trial and error. Stop the motor and count the remaining link.
//-----------------------------------------------------------------------------------------
#define Numberof_CHAIN_LINKS_STOPcompensation__		0//8//4//6
#define CHAIN_LINKS_STOPnumber__					3
#define Pusher_millsec_interval__					120			//in millisec... this is the pusher thread timing.

//-----------------------------------------------------------------------------------------
//Factory default values... to have these values effective the application.ini should be 
//deleted and automatically re-created by these values.
//defines the Serial port. change this value
//for installation to installation
//-----------------------------------------------------------------------------------------
#define PUSHER_port_Name		"COM2\0"
#define STATIONNetwork_Name		"COM1\0"
#define DATE_FormatKEYPAD		"yy-MM-dd\0"

#define UPDATENETWORKDATETIME_period			900		//this is the regular periodic intervl in milliseconds to update the Network's date and Time from Server.
#define OFFLINEPOLLSECONDS_Period				60
#define REQUESTHELPSECONDS_Period				2
#define FLUSHSERIALCOMMLOGFILESECONDS_Period	5

//----------------------------------------
//Compilation defines
//----------------------------------------
#define USE_NEW_PUSHER_PORT			//defines that the code is compiled with the 9600bps Pusher Master

#define USE_PUSHERTIME_MEMORY_ARRAY

//#define USE_PUSHERCOUNTINSERIAL


/*

In the SQL db PusherCounter
Pusher Count  ... This is the number of the pusher that has just passed the pusher_sensor
Pusher Link  .... The number of chain links after the last pusher count (between the "Pusher Count" and sensor)
MaxPusherCount .. This is Constant for a particular installation.Depending on the number of pushers=22 (enter pushers-1 which is a 0..21)

   *
|-|-|-|-|-|-|-|-|
                ^
				20


*///terrence