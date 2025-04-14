#ifndef ___SQL_appfunc__H
#define ___SQL_appfunc__H

#include <vcclr.h>  

#include "StationOperatorClass.h"
#include "stationSettingClass.h"
#include "DesignCodeSequenceClass.h"
#include "class_HostnameMRTonline.h"
#include "class_SQLfunc.h"

//#define SQLDBconnectionstring		"Initial Catalog=ONLINEBTREKDB;Data Source=localhost;Integrated Security=SSPI;"



#define SQLDBName					"ONLINEBTREKDB"

	using namespace System;
	using namespace System::Data::SqlClient;
	using namespace System::Data;
	using namespace common_ClassLib;
	/*
	using namespace System::Text;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;
	using namespace System::Timers;
	using namespace System::Windows::Forms;
	using namespace System::Resources;
	using namespace System::Globalization;
	using namespace System::Configuration;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO;		
	using namespace System::Data::Odbc;			
	using namespace System::IO::Ports;
	using namespace System::Xml;
	using namespace System::Runtime::InteropServices;
	*/


//extern class_processError *processErrorLog; 
//extern SqlConnection ^openDBConnection();
//extern int openDBConnection(SqlConnection ^%SQLmyConnection, String ^myConnectionString);
//extern int openDBConnection(SqlConnection ^%SQLmyConnection, String ^ipaddress, String ^dbname);
//extern int openDBConnection(SqlConnection ^%SQLmyConnection, String ^ipaddress, String ^dbname, String ^ID, String ^password, int timeout=0);
//extern bool SQLerrorExceptionLog(SqlException ^sqle, const char *file, int line, String ^remarks="");
extern String ^getfrom_STATION_DataValue(class_SQLfunc ^sqlfunc, String ^STNID, String ^fieldname, String ^IPaddress);
extern int getfrom_STATION_IntValue(class_SQLfunc ^sqlfunc, String ^STNID, String ^fieldname, String ^IPaddress);
extern bool getfrom_STATION_BoolValue(class_SQLfunc ^sqlfunc, String ^STNID, String ^fieldname, String ^IPaddress);
extern int reload_StationOperator(class_SQLfunc ^sqlfunc, StationOperatorClass *StationOperator, String^ dIPAddress, String ^Prodline);
extern int clearPusherMonitorSQLdb(class_SQLfunc ^sqlfunc);
extern int readfromPUSHERTIMEdb(class_SQLfunc ^sqlfunc, stationSettingClass *stationSetting, const wchar_t *folder, String ^%ErrorStr);
extern int writeToPUSHERTIMEdb(class_SQLfunc ^sqlfunc, stationSettingClass *stationSetting);
extern int reload_From_StatioAssignSQL(class_SQLfunc ^sqlfunc, DesignCodeSequenceClass *table, const wchar_t *folder);
//extern String ^getLoginNameFromStationSQL(class_SQLfunc ^sqlfunc, String ^STNID, String ^prodline);
//extern String ^getLoginStatusFromStationSQL(class_SQLfunc ^sqlfunc, String ^STNID, String ^prodline);
extern int CheckAdd_PUSHERMONITOR_PusherID(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int MaxNumberofPUSHER);
extern int CheckAdd_STATIONHANGER_(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int MaxNumberofStation);
extern int CheckAdd_HEADLINEMOTOR_(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine);
//extern int CheckAdd_PUSHERCOUNTER_(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int maxPusherounter);
extern int CheckAdd_PUSHERCOUNTER_(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int maxPushercounter, int interval, int chainLink);
extern int CheckAdd_LASTBUNDLE_(class_SQLfunc ^mastersql, class_SQLfunc ^localsql, String ^PRODUCTIONLine);
extern void TestBridgeFunction();
//extern int reload_HOSTNAME_MRT_db(class_HostnameMRTonline *classhost, String ^hostnameServerIpAddress);
//extern int reload_HOSTNAME_MRT_db(class_HostnameMRTonline *classhost, class_SQLfunc ^%SQLfunc);
extern int RetrieveProdline(class_SQLfunc ^sqlfunc, String ^dIPAddress, String ^%lineNumber);
extern String ^Retrieve_DataValue_FromBundleSeq(SqlCommand ^myCommand, String ^fieldName, String ^Prodline, int BundleNo, String ^PRODID);
extern String ^getSQLGoStation(SqlCommand ^my_Command, String ^PusherCount_STNID, String ^Timer_Prodline, String ^PusherCount_HangerID);

extern bool isLoadStation(class_SQLfunc ^sqlfunc, String ^Prodline, String ^STNID);
//extern int retrieve_PUSHERCOUNTER_values(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int *maxPushercounter, int *interval);
extern int retrieve_PUSHERCOUNTER_values(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int *maxPushercounter, int *interval, int *chainLink);
extern int Check_PUSHERTIMEdb(class_SQLfunc ^sqlfunc, String ^Prodline);


#endif