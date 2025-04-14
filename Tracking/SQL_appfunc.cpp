#include "StdAfx.h"
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include "SQL_appfunc.h"
#include "stringconversion.h"





/*
SqlConnection ^kopenDBConnection()
{
	String ^myConnectionString = "Initial Catalog=ONLINEBTREKDB;Data Source=localhost;Integrated Security=SSPI;";
	SqlConnection ^SQLmyConnection = gcnew SqlConnection(); 
	if (SQLmyConnection->State == System::Data::ConnectionState::Open)
	{
		SQLmyConnection->Close();
		return nullptr;
	}
	SQLmyConnection->ConnectionString = myConnectionString; 
	//SqlCommand ^my_Command = gcnew SqlCommand();
	//my_Command->Connection = SQLmyConnection; 
	try{
	SQLmyConnection->Open();
	}
	catch (SqlException ^sqle)
	{
		SQLmyConnection->Close();
		return nullptr;
	}
	SQLmyConnection->Close();
	return SQLmyConnection;
}
*/







int clearPusherMonitorSQLdb(class_SQLfunc ^sqlfunc)
{
	int error = 0;
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result!=0) 
		return -1;
	SqlCommand ^my_Command = gcnew SqlCommand();
	my_Command->Connection = SQLmyConnection; 
	SQLmyConnection->Open();
	try
	{
		my_Command->CommandType = CommandType::Text;							
		my_Command->CommandText = " UPDATE PUSHERMONITOR SET PUSHERSTATUS = 'N',HANGERID = '',CURSTN = '',STNDEST = '',ROUND = '0'";
		int affected_UpdatePusherMonitor = my_Command->ExecuteNonQuery();								 							
	}
	catch (SqlException ^sqle)
	{
		SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "ClearPusherMonitor");
		error = -2;
	}
	SQLmyConnection->Close();
	return error;
}


int RetrieveProdline(class_SQLfunc ^sqlfunc, String ^dIPAddress, String ^%lineNumber)
{
	int error = 0;
	lineNumber = "";
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result!=0) 	
		return -1;
	try
	{
		SqlCommand ^myCommand=gcnew SqlCommand();
		myCommand->Connection=SQLmyConnection;
		SQLmyConnection->Open();
		myCommand->CommandType = CommandType::Text;								
		myCommand->CommandText =String::Format("SELECT PRODLINE FROM PRODUCTIONLINE WHERE IPADDRESS = '" + dIPAddress + "' ");					
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
			lineNumber = reader["PRODLINE"]->ToString();
//		__ASSERT_POSSIBLE_ERROR(reader->HasRows, catchERROR::SQLNOREAD, "PRODLINE FROM PRODUCTIONLINE", __FILE__, __LINE__);
		reader->Close();
	}
	catch (SqlException ^sqle)
	{
		SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "PRODLINE FROM PRODUCTIONLINE");
		error = -2;
	}			
	SQLmyConnection->Close();

	//------------------------------------------------------------
	//production line number must be a number from 1 onwards
	//------------------------------------------------------------
	if (convertToInt32(lineNumber)<=0)
		error = -3;

	return error;
}

//Get from STATION SQL Table
String ^getfrom_STATION_DataValue(class_SQLfunc ^sqlfunc, String ^STNID, String ^fieldname, String ^IPaddress)
{
	String ^LoadStn_Prodline = "";
	String ^str_value = "null";
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result!=0) 
		return str_value;	

    try
	{
		SqlCommand ^myCommand = gcnew SqlCommand();
		
		SQLmyConnection->Open();
		myCommand->Connection = SQLmyConnection;
		// Retrieve Prodline								
		myCommand->CommandType = CommandType::Text;								
		myCommand->CommandText =String::Format("SELECT PRODLINE FROM PRODUCTIONLINE WHERE IPADDRESS = '" + IPaddress + "' ");					
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
		{						
			LoadStn_Prodline = reader["PRODLINE"]->ToString();
		}					
		reader->Close();	
			
		// Retrieve ISASSIGNED Station								
		myCommand->CommandType = CommandType::Text;								
		myCommand->CommandText =String::Format("SELECT " + fieldname + " FROM STATION WHERE PRODLINE = '" + LoadStn_Prodline + "' AND STATIONID = '" + STNID + "' ");					
		SqlDataReader ^LoadStn_reader = myCommand->ExecuteReader();
		while(LoadStn_reader->Read())
			str_value = LoadStn_reader[fieldname]->ToString();
		LoadStn_reader->Close();	
	}catch (SqlException ^sqle)
	{	
		SQL_errorExceptionLog(sqle, __FILE__, __LINE__);
	}
	SQLmyConnection->Close();
	return str_value;
}

int getfrom_STATION_IntValue(class_SQLfunc ^sqlfunc, String ^STNID, String ^fieldname, String ^IPaddress)
{
	String ^str = getfrom_STATION_DataValue(sqlfunc, STNID, fieldname, IPaddress);
	if (str=="null")
		return 0;
	else
		return convertToInt32(str);
}

bool getfrom_STATION_BoolValue(class_SQLfunc ^sqlfunc, String ^STNID, String ^fieldname, String ^IPaddress)
{
	if (getfrom_STATION_DataValue(sqlfunc, STNID, fieldname, IPaddress)=="Y")
		return true;
	else
		return false;
}

//isLoadStation(localSQL, MyproductlineNumber
bool isLoadStation(class_SQLfunc ^sqlfunc, String ^Prodline, String ^STNID)
		{
			String ^Loading_Loadstn = "";
			SqlConnection ^SQLmyConnection;
			int result = sqlfunc->openDBConnection(SQLmyConnection);
			if (result!=0) 	
				return 0;
            try
			{
				SqlCommand ^myCommand = gcnew SqlCommand();
				myCommand->Connection = SQLmyConnection;
				SQLmyConnection->Open();
				myCommand->CommandType = CommandType::Text;								
				//myCommand->CommandText =String::Format("SELECT CURLOADING FROM STATIONASSIGN WHERE PRODLINE = '" + MyproductlineNumber + "' AND STATIONID = '" + STNID + "' ");	
				myCommand->CommandText =String::Format("SELECT S.LOADSTATION AS LOADSTATION FROM STATION S, STATIONASSIGN SA WHERE S.PRODLINE = '" + Prodline + "' AND S.STATIONID = '" + STNID + 
																"' AND SA.SEQNO=1 AND S.PRODLINE = SA.PRODLINE AND S.STATIONID=SA.STATIONID AND SA.CURLOADING='Y' ");
				SqlDataReader ^LoadStn_reader = myCommand->ExecuteReader();
				while(LoadStn_reader->Read())
					//Loading_Loadstn = LoadStn_reader["CURLOADING"]->ToString();
					Loading_Loadstn = LoadStn_reader["LOADSTATION"]->ToString();
				//donot ASSERT here...__ASSERT_POSSIBLE_ERROR(LoadStn_reader->HasRows, catchERROR::SQLNOREAD, "ISLOADSTN LINE#"+MyproductlineNumber, __FILE__, __LINE__);
				LoadStn_reader->Close();
				SQLmyConnection->Close();
			}catch (SqlException ^sqle)
			{	
				SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "ISLOADSTN");
			}
			
			return (Loading_Loadstn == "Y");
		}

//---------------------------------------------------------------------------------
//Check and Add additional pusherID for Prodline, 
//  if pusherID for the Prodline is not found in "PUSHERMONITOR" SQL DB
//---------------------------------------------------------------------------------
int CheckAdd_PUSHERMONITOR_PusherID(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int MaxNumberofPUSHER)
{
	int changed = 0;
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result==0)
	{
		SQLmyConnection->Open();
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		myCommand->CommandType = CommandType::Text;	
		int pusherid;
		for (pusherid=0;pusherid<MaxNumberofPUSHER;pusherid++)
		{
			try
			{
				myCommand->CommandText = " INSERT INTO PUSHERMONITOR(PRODLINE,PUSHERID,PUSHERSTATUS,HANGERID,CURSTN,STNDEST,PUSHERSENSOR,ROUND) VALUES('" + 
																						PRODUCTIONLine + "','" +
																						pusherid + "','" + 
																						"N','"+
																						"','"+
																						"','"+
																						"','"+
																						"N','"+
																						"0')";
																					
				int affected = myCommand->ExecuteNonQuery();
				changed++;
			}
			catch (SqlException ^sqle)
			{	
				if (sqle->Number!=2627)		//Error:2627...Violation of PRIMARY KEY is intended here so as to avoid creating another duplicate record
				{
					SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "Warning:Updating STATIONHANGER");
				}
			}

		}

		myCommand->CommandText = " DELETE FROM PUSHERMONITOR WHERE PRODLINE <> '"+PRODUCTIONLine+"'";
		int affected = myCommand->ExecuteNonQuery();
		SQLmyConnection->Close();
	}
	return changed;
}

//---------------------------------------------------------------------------------
//Check and Add additional stationID for Prodline, 
//  if stationID for the Prodline is not found in "STATIONHANGER" SQL DB
//---------------------------------------------------------------------------------
int CheckAdd_STATIONHANGER_(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int MaxNumberofStation)
{
	int changed = 0;
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result==0)
	{
	
		SQLmyConnection->Open();
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		myCommand->CommandType = CommandType::Text;	
		//---------------------------
		//Add if not found
		//---------------------------
		int stationid;
		for (stationid=1;stationid<=MaxNumberofStation;stationid++)
		{
			try
			{
				myCommand->CommandText = " INSERT INTO STATIONHANGER(PRODLINE,STATIONID,HANGERID,HANGERWAIT) VALUES('" + 
																						PRODUCTIONLine + "','" +
																						stationid.ToString() + "','" + 
																						"','"+
																						"N')";
																					
				int affected = myCommand->ExecuteNonQuery();
				changed++;
			}
			catch (SqlException ^sqle)
			{	
				if (sqle->Number!=2627)		//Error:2627...Violation of PRIMARY KEY is intended here so as to avoid creating another duplicate record
				{
					SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "Warning:Updating STATIONHANGER");
				}
			}
		}
		SQLmyConnection->Close();
	}
	return changed;
}


//---------------------------------------------------------------------------------
//Check and Add additional status for Prodline, 
//  if status for the Prodline is not found in "HEADLINEMOTOR" SQL DB
//---------------------------------------------------------------------------------
int CheckAdd_HEADLINEMOTOR_(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine)
{
	String ^status = "123";
	int changed = 0;
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result==0)
	{
	
		SQLmyConnection->Open();
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		myCommand->CommandType = CommandType::Text;	

		myCommand->CommandText =String::Format("SELECT STATUS FROM HEADLINEMOTOR WHERE PRODLINE = '" + PRODUCTIONLine + "' ");					
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
		{	
			status = reader["STATUS"]->ToString();
		}		
		reader->Close();
		if (status=="123")
		{
			myCommand->CommandText = " INSERT INTO HEADLINEMOTOR(PRODLINE,STATUS) VALUES('" + 
																					PRODUCTIONLine + "','" +
																					"N')";
																					
			int affected = myCommand->ExecuteNonQuery();
			changed++;
		}
		SQLmyConnection->Close();
	}
	return changed;
}

int CheckAdd_LASTBUNDLE_(class_SQLfunc ^mastersql, class_SQLfunc ^localsql, String ^PRODUCTIONLine)
{
	int changed = 0;
	String ^master_empid;
	SqlConnection ^SQLmasterConnection;
	int result = mastersql->openDBConnection(SQLmasterConnection);
	if (result==0)
	{
		SqlConnection ^SQLlocalConnection;
		result = localsql->openDBConnection(SQLlocalConnection);
		if (result==0)
		{	
			SQLmasterConnection->Open();
			SqlCommand ^masterCommand = gcnew SqlCommand();
			masterCommand->Connection = SQLmasterConnection;
			masterCommand->CommandType = CommandType::Text;	

			SQLlocalConnection->Open();
			SqlCommand ^localCommand = gcnew SqlCommand();
			localCommand->Connection = SQLlocalConnection;
			localCommand->CommandType = CommandType::Text;	

			masterCommand->CommandText =String::Format("SELECT EMPID FROM EMP");					
			SqlDataReader ^reader = masterCommand->ExecuteReader();
			while(reader->Read())
			{	
				master_empid = reader["EMPID"]->ToString();
				localCommand->CommandText = String::Format("SELECT EMPID FROM LASTBUNDLE WHERE EMPID='" + master_empid + "'");					
				SqlDataReader ^localreader = localCommand->ExecuteReader();
				int exist = localreader->HasRows;
				localreader->Close();
				if (exist<=0)
				{
					localreader->Close();
					localCommand->CommandText = String::Format("INSERT INTO LASTBUNDLE (EMPID, COMPLETED, PRODLINE) VALUES('" +
																						master_empid + "','" +
																						"Y" + "','" +
																						PRODUCTIONLine + "'" + 
																						")");

					int affected = localCommand->ExecuteNonQuery();
					changed++;
				}
			}		
			reader->Close();
	/*
			if (PusherCount=="1234568")
			{
				myCommand->CommandText = " INSERT INTO PUSHERCOUNTER(Prodline,PusherCount,PusherLink,MaxPusherCount,Interval,NxtCkHour,MotorStatus,STNASSIGN_dirtyFlag) VALUES('" + 
																						PRODUCTIONLine + "','" +
																						"0" + "','" +
																						"0" + "','" +
																						maxPusherounter + "','" +
																						"10" + "','" +
																						"2012-05-24 12:16:11.000" + "','" +
																						"N" + "','" +
																						"N')";
																					
				int affected = myCommand->ExecuteNonQuery();
				changed++;
			}
			*/
		}
		if (SQLlocalConnection&&(SQLlocalConnection!=nullptr))
			SQLlocalConnection->Close();
	}
	if (SQLmasterConnection&&(SQLmasterConnection!=nullptr))
		SQLmasterConnection->Close();

	return changed;
}

//david20121120...
//---------------------------------------------------------------------------------
//Check and Add additional status for Prodline, 
//  if status for the Prodline is not found in "PUSHERCOUNTER" SQL DB
//---------------------------------------------------------------------------------
int retrieve_PUSHERCOUNTER_values(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int *maxPushercounter, int *interval, int *chainLink)
{
	int count = 0;
	*maxPushercounter = 0;
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result==0)
	{

		SQLmyConnection->Open();
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		myCommand->CommandType = CommandType::Text;	
		
		if (PRODUCTIONLine=="")
			myCommand->CommandText =String::Format("SELECT MaxPusherCount, Interval, MaxChainLink FROM PUSHERCOUNTER");
		else
			myCommand->CommandText =String::Format("SELECT MaxPusherCount, Interval, MaxChainLink FROM PUSHERCOUNTER WHERE PRODLINE = '" + PRODUCTIONLine + "' ");					
		
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
		{	
			*maxPushercounter = convertToInt32(reader["MaxPusherCount"]->ToString());
			*interval = convertToInt32(reader["Interval"]->ToString());
			*chainLink = convertToInt32(reader["MaxChainLink"]->ToString());
			count++;
		}		
		reader->Close();
		if (SQLmyConnection&&(SQLmyConnection!=nullptr))
			SQLmyConnection->Close();
		result = count;
	}
	return result;
}
//...david20121120

//---------------------------------------------------------------------------------
//Check and Add additional status for Prodline, 
//  if status for the Prodline is not found in "PUSHERCOUNTER" SQL DB
//---------------------------------------------------------------------------------
/*
int retrieve_PUSHERCOUNTER_values(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int *maxPushercounter, int *interval)
{
	//String ^PusherCount = "1234568";
	*maxPushercounter = 0;
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result==0)
	{
		SQLmyConnection->Open();
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		myCommand->CommandType = CommandType::Text;	

		myCommand->CommandText =String::Format("SELECT MaxPusherCount, Interval FROM PUSHERCOUNTER WHERE PRODLINE = '" + PRODUCTIONLine + "' ");					
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
		{	
			*maxPushercounter = convertToInt32(reader["MaxPusherCount"]->ToString());
			*interval = convertToInt32(reader["Interval"]->ToString());
		}		
		reader->Close();
		if (SQLmyConnection&&(SQLmyConnection!=nullptr))
			SQLmyConnection->Close();
	}
	return result;
}

//---------------------------------------------------------------------------------
//Check and Add additional status for Prodline, 
//  if status for the Prodline is not found in "PUSHERCOUNTER" SQL DB
//---------------------------------------------------------------------------------
int CheckAdd_PUSHERCOUNTER_(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int maxPusherounter)
{
	String ^PusherCount = "1234568";
	int changed = 0;
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result==0)
	{
	
		SQLmyConnection->Open();
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		myCommand->CommandType = CommandType::Text;	

		myCommand->CommandText =String::Format("SELECT PusherCount FROM PUSHERCOUNTER WHERE PRODLINE = '" + PRODUCTIONLine + "' ");					
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
		{	
			PusherCount = reader["PusherCount"]->ToString();
		}		
		reader->Close();

		if (PusherCount=="1234568")
		{
			myCommand->CommandText = " INSERT INTO PUSHERCOUNTER(Prodline,PusherCount,PusherLink,MaxPusherCount,Interval,NxtCkHour,MotorStatus,STNASSIGN_dirtyFlag) VALUES('" + 
																					PRODUCTIONLine + "','" +
																					"0" + "','" +
																					"0" + "','" +
																					maxPusherounter + "','" +
																					"10" + "','" +
																					"2012-05-24 12:16:11.000" + "','" +
																					"N" + "','" +
																					"N')";
																					
			int affected = myCommand->ExecuteNonQuery();
			changed++;
		}
		SQLmyConnection->Close();
	}
	return changed;
}
*/

//david20121120...
//---------------------------------------------------------------------------------
//Check and Add additional status for Prodline, 
//  if status for the Prodline is not found in "PUSHERCOUNTER" SQL DB
//---------------------------------------------------------------------------------
int CheckAdd_PUSHERCOUNTER_(class_SQLfunc ^sqlfunc, String ^PRODUCTIONLine, int maxPushercounter, int interval, int chainLink)
{
	String ^PusherCount = "1234568";
	int changed = 0;
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result==0)
	{
	
		SQLmyConnection->Open();
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		myCommand->CommandType = CommandType::Text;	

		myCommand->CommandText =String::Format("SELECT PusherCount FROM PUSHERCOUNTER WHERE PRODLINE = '" + PRODUCTIONLine + "' ");					
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
		{	
			PusherCount = reader["PusherCount"]->ToString();
		}		
		reader->Close();

		if (PusherCount=="1234568")
		{
			myCommand->CommandText = " INSERT INTO PUSHERCOUNTER(Prodline,PusherCount,PusherLink,MaxPusherCount,Interval,NxtCkHour,MotorStatus,STNASSIGN_dirtyFlag,MaxChainLink) VALUES('" + 
																					PRODUCTIONLine + "','" +
																					"0" + "','" +
																					"0" + "'," +
																					maxPushercounter + "," +
																					interval + ",'" +
																					"2012-05-24 12:16:11.000" + "','" +
																					"N" + "','" +
																					"N" + "'," +
																					chainLink + 
																					")";
			
																					
			int affected = myCommand->ExecuteNonQuery();
			myCommand->CommandText =String::Format("DELETE FROM PUSHERCOUNTER WHERE PRODLINE <> '" + PRODUCTIONLine + "' ");	//david20121120 added
			affected = myCommand->ExecuteNonQuery();
			changed++;
		}
		SQLmyConnection->Close();
	}
	return changed;
}
//...david20121120


int reload_StationOperator(class_SQLfunc ^sqlfunc, StationOperatorClass *StationOperator, String^ dIPAddress, String ^Prodline)
{
	int ii;

	StationOperator->Clear();
	for (ii=0;ii<StationOperator->getcount();ii++)
	{
		StationOperator->setloggedIn(ii,				getfrom_STATION_BoolValue(sqlfunc, ii.ToString(), "LOGINSTATUS", dIPAddress),0);
		//StationOperator->setStationAsLoadingStation(ii, getfrom_STATION_BoolValue(sqlfunc, ii.ToString(), "LOADSTATION", dIPAddress),0);
		StationOperator->setStationAssigned(ii,			getfrom_STATION_BoolValue(sqlfunc, ii.ToString(), "ISASSIGNED", dIPAddress),0);
		StationOperator->setAlive(ii,					getfrom_STATION_BoolValue(sqlfunc, ii.ToString(), "ALIVE", dIPAddress),0);
		StationOperator->setEMPFname(ii,				getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "EMPFNAME", dIPAddress),0);
		StationOperator->setCurOpCode(ii,				getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "CUROPCODE", dIPAddress),0);
		StationOperator->setIn_Status(ii,				getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "IN_STATUS", dIPAddress),0);
		StationOperator->setoperator_ID(ii,				getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "EMPID", dIPAddress),0);
		StationOperator->setEMPID(ii,					getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "EMPID", dIPAddress),0);			
		StationOperator->setEMPFname(ii,				getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "EMPFNAME", dIPAddress),0);							
		StationOperator->setEMPLname(ii,				getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "EMPLNAME", dIPAddress),0);													
		StationOperator->setProdLine(ii,				getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "PRODLINE", dIPAddress),0);							
		StationOperator->setCurdesignCode(ii,			getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "CURDESIGNCODE", dIPAddress),0);							
		StationOperator->setLastBundleID(ii,			getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "LASTBUNDLEID", dIPAddress),0);							
		StationOperator->setLEDName(ii,					getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "LEDNAME", dIPAddress),0);		
		StationOperator->setShift(ii,					getfrom_STATION_IntValue (sqlfunc, ii.ToString(), "SHIFT", dIPAddress),0);	

		StationOperator->setBreakStatus(ii,				getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "Break_Status", dIPAddress),0);	
		StationOperator->setBreakName(ii,				getfrom_STATION_DataValue(sqlfunc, ii.ToString(), "ALLSTNSTATUS", dIPAddress),0);	

		StationOperator->setStationAsLoadingStation(ii, isLoadStation(sqlfunc, Prodline, ii.ToString()), 0);
	}
	StationOperator->writeDat();
	return 0;
}	

/*
int reload_HOSTNAME_MRT_db(class_HostnameMRTonline *classhost, class_SQLfunc ^%SQLfunc)
{
	int nn = 0;
	if (!classhost) return -1;
	if (SQLfunc->getipaddress()=="") return -2;
	SqlConnection ^SQLmyConnection;
	String ^hostnameTable = "HostName_MRT";
    try
	{
		int result = SQLfunc->openDBConnection(SQLmyConnection);
		nn = result;
		if (result==0) 
		{
			//-----------------------------------------------------
			// Read from SQL data table
			//-----------------------------------------------------
			SqlCommand ^myCommand = gcnew SqlCommand();
			myCommand->Connection = SQLmyConnection;
			SQLmyConnection->Open();
			myCommand->CommandType = CommandType::Text;		
			myCommand->CommandText =String::Format("SELECT * FROM "+hostnameTable);					
			SqlDataReader ^reader = myCommand->ExecuteReader();
			//-----------------------------------------------------------------------
			// Clear array table default for refresh of data from hostname server
			//-----------------------------------------------------------------------
			classhost->Clear();
			while(reader->Read())
			{	
				//------------------------------------------
				//read SQL and fill the memory aray table
				//------------------------------------------
				String ^mHostname = reader["Hostname"]->ToString();
				String ^mIPAddress = reader["IPAddress"]->ToString();
				String ^mDBName = reader["DBName"]->ToString();
				String ^mLoginName = reader["LoginName"]->ToString();
				String ^mPassword = reader["Password"]->ToString();
				String ^mReMark = reader["ReMark"]->ToString();
				String ^mProdline = reader["Prodline"]->ToString();

				pin_ptr<const wchar_t> wHostname = PtrToStringChars(mHostname);
				pin_ptr<const wchar_t> wIPAddress = PtrToStringChars(mIPAddress);
				pin_ptr<const wchar_t> wDBName = PtrToStringChars(mDBName);
				pin_ptr<const wchar_t> wLoginName = PtrToStringChars(mLoginName);
				pin_ptr<const wchar_t> wPassword = PtrToStringChars(mPassword);
				pin_ptr<const wchar_t> wReMark = PtrToStringChars(mReMark);
				pin_ptr<const wchar_t> wProdline = PtrToStringChars(mProdline);
				

				classhost->Add(wHostname,	wIPAddress,	wDBName, wLoginName, wPassword, wReMark, wProdline); 
			}					
			reader->Close();
		}
	}catch (SqlException ^sqle)
	{	
		SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "Warning:Locating HostName_Server<"+SQLfunc->getipaddress()+">");
		nn = -4;
	}
	SQLmyConnection->Close();
		
	return nn;

}
*/
/*
int reload_HOSTNAME_MRT_db(class_HostnameMRTonline *classhost, String ^hostnameServerIpAddress)
{
//	int ii;
	int nn = 0;
	if (!classhost) return -1;
	if (hostnameServerIpAddress=="") return -2;
	SqlConnection ^SQLmyConnection;
	String ^hostnameTable = "HostName_MRT";
    try
	{
		int result = openDBConnection(SQLmyConnection, hostnameServerIpAddress, "ONLINEBTREKDB", "sa", "1234");
		nn = result;
		if (result==0) 
		{
			//-----------------------------------------------------
			// Read from SQL data table
			//-----------------------------------------------------
			SqlCommand ^myCommand = gcnew SqlCommand();
			myCommand->Connection = SQLmyConnection;
			SQLmyConnection->Open();
			myCommand->CommandType = CommandType::Text;		
			myCommand->CommandText =String::Format("SELECT * FROM "+hostnameTable);					
			SqlDataReader ^reader = myCommand->ExecuteReader();
			//-----------------------------------------------------------------------
			// Clear array table default for refresh of data from hostname server
			//-----------------------------------------------------------------------
			classhost->Clear();
			while(reader->Read())
			{	
				//------------------------------------------
				//read SQL and fill the memory aray table
				//------------------------------------------
				String ^mHostname = reader["Hostname"]->ToString();
				String ^mIPAddress = reader["IPAddress"]->ToString();
				String ^mDBName = reader["DBName"]->ToString();
				String ^mLoginName = reader["LoginName"]->ToString();
				String ^mPassword = reader["Password"]->ToString();
				String ^mReMark = reader["ReMark"]->ToString();

				pin_ptr<const wchar_t> wHostname = PtrToStringChars(mHostname);
				pin_ptr<const wchar_t> wIPAddress = PtrToStringChars(mIPAddress);
				pin_ptr<const wchar_t> wDBName = PtrToStringChars(mDBName);
				pin_ptr<const wchar_t> wLoginName = PtrToStringChars(mLoginName);
				pin_ptr<const wchar_t> wPassword = PtrToStringChars(mPassword);
				pin_ptr<const wchar_t> wReMark = PtrToStringChars(mReMark);

				classhost->Add(wHostname,	wIPAddress,	wDBName, wLoginName, wPassword, wReMark); 
			}					
			reader->Close();
		}
	}catch (SqlException ^sqle)
	{	
		SQLerrorExceptionLog(sqle, __FILE__, __LINE__, "Warning:Locating HostName_Server<"+hostnameServerIpAddress+">");
		nn = -4;
	}
	SQLmyConnection->Close();
		
	return nn;

}
*/
int Check_PUSHERTIMEdb(class_SQLfunc ^sqlfunc, String ^Prodline)
{
	//ErrorStr = "";
	//if (!stationSetting) return 0;

	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result!=0) 
		return 0;
	
	//-----------------------------------------------------
	// Read from SQL data table
	//-----------------------------------------------------
	int stnID;
	//SqlConnection ^SQLmyConnection = openDBConnection();
	
	SqlCommand ^myCommand = gcnew SqlCommand();
	myCommand->Connection = SQLmyConnection;
	SQLmyConnection->Open();
	/*
	myCommand->CommandType = CommandType::Text;								
	myCommand->CommandText =String::Format("SELECT PRODLINE FROM PRODUCTIONLINE WHERE IPADDRESS = '127.0.0.1' ");					
	SqlDataReader ^reader = myCommand->ExecuteReader();
	while(reader->Read())
	{												
		Prodline = reader["PRODLINE"]->ToString();
	}		
	reader->Close();
	*/
	//wchar_t wt_buff[64];
	//String2CharArray(Prodline, stationSetting->wt_prodline);
	myCommand->CommandType = CommandType::Text;		
	myCommand->CommandText =String::Format("DELETE FROM PUSHERTIME WHERE PRODLINE <> '" + Prodline + "' ");
	myCommand->ExecuteNonQuery();
	SQLmyConnection->Close();

/*
	myCommand->CommandText =String::Format("SELECT * FROM PUSHERTIME WHERE PRODLINE = '" + Prodline + "' ");					
	SqlDataReader ^PusherTime_reader = myCommand->ExecuteReader();
	int count = 0;
	while(PusherTime_reader->Read())
	{	
		//------------------------------------------
		//read SQL and fill the memory aray table
		//------------------------------------------
		String ^STNID = PusherTime_reader["STATIONID"]->ToString();
		stnID = convertToInt32(STNID);
		if ((stnID>=0)&&(stnID<MAX_STATIONARRAY_SIZE))
		{
			stationPara.infeed = convertToInt32(PusherTime_reader["INFEED"]->ToString());		
			stationPara.outfeed = convertToInt32(PusherTime_reader["OUTFEED"]->ToString());
			stationPara.outfeedoffset =  convertToInt32(PusherTime_reader["OUTFEEDOFFSET"]->ToString());
			stationPara.infeedoffset = convertToInt32(PusherTime_reader["INFEEDOFFSET"]->ToString());
			String2CharArray(STNID, wt_buff);
			wcscpy_s(stationPara.stnID, wt_buff);
			stationSetting->set(stnID, &stationPara);
			count++;		//count the number of record read
		}
	}					
	PusherTime_reader->Close();
	SQLmyConnection->Close();
	if (count<=0)
	{
		ErrorStr = "No Infeed/Outfeed offset defined in PUSHERTIME for production line "+Prodline;
	}
	//------------------------------------------
	//Display write to file for test debug
	//write to file for view
	//------------------------------------------
	char csvfile[1024];
	unsigned int ln;
	for (ln=0;ln<_tcslen(folder);ln++)
		csvfile[ln] = (char)folder[ln];
	csvfile[ln] = 0;
	strcat(csvfile, "\\pushertime.txt");

	FILE *fp=fopen(csvfile, "w+t");
	if (fp)
	{
		int ii;
		for (ii=1;ii<stationSetting->getcount();ii++)
		{
			
			if (stationSetting->get(ii, &stationPara))
			{

				fprintf(fp, "%d\t %d\t %d\t %d\t %d\r\n", ii, 
							stationPara.infeed,
							stationPara.infeedoffset,
							stationPara.outfeed,
							stationPara.outfeedoffset);
			}
		}
	fclose(fp);		
	}
	*/
	return result;
}


int readfromPUSHERTIMEdb(class_SQLfunc ^sqlfunc, stationSettingClass *stationSetting, const wchar_t *folder, String ^%ErrorStr)
{
	ErrorStr = "";
	if (!stationSetting) return 0;

	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	//int result = openDBConnection(SQLmyConnection, SQLDBconnectionstring);
	if (result!=0) 
		return 0;

	int ii;
	//-----------------------------------------------------
	// Clear array table. set all array to default -1
	//-----------------------------------------------------
	stationSetting->deleteAll();
	stationParameterType stationPara;
	for (ii=0;ii<MAX_STATIONARRAY_SIZE;ii++)
	{
		memset(&stationPara, 0x0, sizeof(stationParameterType));
		stationPara.infeed = -1;		
		stationPara.outfeed = -1;
		stationPara.outfeedoffset = -1;
		stationPara.infeedoffset = -1;
//		wcscpy_s(stationPara.prodlineID, L"");
	//	wcscpy_s(stationPara.prodlineID, L"");
		wcscpy_s(stationPara.stnID, L"");
		stationSetting->add(&stationPara);
	}

	//-----------------------------------------------------
	// Read from SQL data table
	//-----------------------------------------------------
	int stnID;
	//SqlConnection ^SQLmyConnection = openDBConnection();
	String ^Prodline="";
	SqlCommand ^myCommand = gcnew SqlCommand();
	myCommand->Connection = SQLmyConnection;
	SQLmyConnection->Open();
	myCommand->CommandType = CommandType::Text;								
	myCommand->CommandText =String::Format("SELECT PRODLINE FROM PRODUCTIONLINE WHERE IPADDRESS = '127.0.0.1' ");					
	SqlDataReader ^reader = myCommand->ExecuteReader();
	while(reader->Read())
	{												
		Prodline = reader["PRODLINE"]->ToString();
	}		
	reader->Close();
	wchar_t wt_buff[64];
	//String2CharArray(Prodline, stationSetting->wt_prodline);
	myCommand->CommandType = CommandType::Text;		
	//myCommand->CommandText =String::Format("DELETE FROM PUSHERTIME WHERE PRODLINE <> '" + Prodline + "' ");
	//myCommand->ExecuteNonQuery();


	myCommand->CommandText =String::Format("SELECT * FROM PUSHERTIME WHERE PRODLINE = '" + Prodline + "' ");					
	SqlDataReader ^PusherTime_reader = myCommand->ExecuteReader();
	int count = 0;
	while(PusherTime_reader->Read())
	{	
		//------------------------------------------
		//read SQL and fill the memory aray table
		//------------------------------------------
		String ^STNID = PusherTime_reader["STATIONID"]->ToString();
		stnID = convertToInt32(STNID);
		if ((stnID>=0)&&(stnID<MAX_STATIONARRAY_SIZE))
		{
			stationPara.infeed = convertToInt32(PusherTime_reader["INFEED"]->ToString());		
			stationPara.outfeed = convertToInt32(PusherTime_reader["OUTFEED"]->ToString());
			stationPara.outfeedoffset =  convertToInt32(PusherTime_reader["OUTFEEDOFFSET"]->ToString());
			stationPara.infeedoffset = convertToInt32(PusherTime_reader["INFEEDOFFSET"]->ToString());
			String2CharArray(STNID, wt_buff);
			wcscpy_s(stationPara.stnID, wt_buff);
			stationSetting->set(stnID, &stationPara);
			count++;		//count the number of record read
		}
	}					
	PusherTime_reader->Close();
	SQLmyConnection->Close();
	if (count<=0)
	{
		ErrorStr = "No Infeed/Outfeed offset defined in PUSHERTIME for production line "+Prodline;
	}
	//------------------------------------------
	//Display write to file for test debug
	//write to file for view
	//------------------------------------------
	char csvfile[1024];
	unsigned int ln;
	for (ln=0;ln<_tcslen(folder);ln++)
		csvfile[ln] = (char)folder[ln];
	csvfile[ln] = 0;
	strcat(csvfile, "\\pushertime.txt");

	FILE *fp=fopen(csvfile, "w+t");
	if (fp)
	{
		int ii;
		for (ii=1;ii<stationSetting->getcount();ii++)
		{
			
			if (stationSetting->get(ii, &stationPara))
			{

				fprintf(fp, "%d\t %d\t %d\t %d\t %d\r\n", ii, 
							stationPara.infeed,
							stationPara.infeedoffset,
							stationPara.outfeed,
							stationPara.outfeedoffset);
			}
		}
	fclose(fp);		
	}
	return count;
}


int writeToPUSHERTIMEdb(class_SQLfunc ^sqlfunc, stationSettingClass *stationSetting)
{
	SqlConnection ^SQLmyConnection;
	//int result = openDBConnection(SQLmyConnection, "localhost", "ONLINEBTREKDB");
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	//int result = openDBConnection(SQLmyConnection, SQLDBconnectionstring);
	if (result!=0) 
		return -1;

	int ii;
	int error = 0;
	stationParameterType sPara;

	String ^Prodline="";
	SqlCommand ^myCommand = gcnew SqlCommand();
	myCommand->Connection = SQLmyConnection;
	SQLmyConnection->Open();
	myCommand->CommandType = CommandType::Text;								
	myCommand->CommandText =String::Format("SELECT PRODLINE FROM PRODUCTIONLINE WHERE IPADDRESS = '127.0.0.1' ");					
	SqlDataReader ^reader = myCommand->ExecuteReader();
	while(reader->Read())
	{												
		Prodline = reader["PRODLINE"]->ToString();
	}		
	reader->Close();

	//delete all records
	myCommand->CommandType = CommandType::Text;							
	myCommand->CommandText = "DELETE PUSHERTIME WHERE PRODLINE = '" + Prodline +"'";
	myCommand->ExecuteNonQuery();

	//-----------------------------------------------------
	// Write to SQL data table
	//-----------------------------------------------------
	String ^PRODLINE = gcnew String(reinterpret_cast<const wchar_t*>(stationSetting->getprodline()));
	int iprodline = convertToInt32(PRODLINE);
	if (iprodline>0)
	{
		for (ii=1;ii<stationSetting->getcount();ii++)
		{
			if (stationSetting->get(ii, &sPara))
			{
				String ^STNID = gcnew String(reinterpret_cast<wchar_t*>(sPara.stnID));
				if (STNID=="") continue;
				try
				{
				//String ^PRODLINE = gcnew String(reinterpret_cast<wchar_t*>(sPara.prodlineID));
				myCommand->CommandText = " INSERT INTO PUSHERTIME(STATIONID,INFEED,INFEEDOFFSET,OUTFEED,OUTFEEDOFFSET,PRODLINE) VALUES('" + 
																						STNID + "','" +
																						sPara.infeed.ToString() + "','" + 
																						sPara.infeedoffset.ToString() + "','"+
																						sPara.outfeed.ToString() + "','"+
																						sPara.outfeedoffset.ToString() + "','"+ 
																						PRODLINE + "')";
				myCommand->ExecuteNonQuery();
				}
				catch (SqlException ^sqle)
				{
					SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "save_to_PUSHERTIME");
					error = -3;
					break;
				}
			}
		}
	}
	else
		error = -2;

	SQLmyConnection->Close();
	return error;
}


int reload_From_StatioAssignSQL(class_SQLfunc ^sqlfunc, DesignCodeSequenceClass *table, const wchar_t *folder)
{
	int error = 0;
	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result!=0) 
		return -1;


	table->clear();
	//SqlConnection ^SQLmyConnection = openDBConnection();
    try
	{
		String ^m_ProdID = "";
		String ^m_OpCode = "";
		String ^m_StnID = "";
		String ^m_DesignCode = "";
		int m_SeqNo = 0;

		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		SQLmyConnection->Open();
	
		myCommand->CommandType = CommandType::Text;								
		myCommand->CommandText =String::Format("SELECT * FROM STATIONASSIGN");					
		SqlDataReader ^reader = myCommand->ExecuteReader();

		while(reader->Read())
		{												
			m_ProdID = reader["PRODID"]->ToString();
			m_OpCode = reader["OPCODE"]->ToString();
			m_SeqNo  = convertToInt32(reader["SEQNO"]->ToString());
			m_StnID = reader["STATIONID"]->ToString();
			m_DesignCode = reader["DESIGNCODE"]->ToString();
			table->add(m_ProdID, m_StnID, m_OpCode, m_DesignCode, m_SeqNo);
		}		
		reader->Close();
	}catch (SqlException ^sqle)
	{	
		SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "reload_From_StatioAssignSQL");
		error = -2;
	}	
	SQLmyConnection->Close();

	unsigned int ln;
	//char csvfile[3000000000];
	char csvfile[111024];
	for (ln=0;ln<_tcslen(folder);ln++)
		csvfile[ln] = (char)folder[ln];
	csvfile[ln] = 0;
	strcat(csvfile, "\\test-stationassign.csv");
	table->exportToCSV(csvfile);

	return error;
}

/*
String ^getLoginNameFromStationSQL(class_SQLfunc ^sqlfunc, String ^STNID, String ^prodline)
{
	String ^empl_name = "";

	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result!=0) 
		return empl_name;
    try
	{
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		SQLmyConnection->Open();
		myCommand->CommandType = CommandType::Text;								
		myCommand->CommandText =String::Format("SELECT EMPFNAME FROM STATION WHERE PRODLINE = '" + prodline + "' AND STATIONID = '" + STNID + "' ");					
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
		{												
			empl_name = reader["EMPFNAME"]->ToString();
		}		
		reader->Close();
	}catch (SqlException ^sqle)
	{	
		SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "getLoginNameFromStationSQL");
	}	
	SQLmyConnection->Close();
	return empl_name;
}
*/
/*
String ^getLoginStatusFromStationSQL(class_SQLfunc ^sqlfunc, String ^STNID, String ^prodline)
{
	String ^valueStr = "";

	SqlConnection ^SQLmyConnection;
	int result = sqlfunc->openDBConnection(SQLmyConnection);
	if (result!=0) 
		return valueStr;

    try
	{
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		SQLmyConnection->Open();
		myCommand->CommandType = CommandType::Text;								
		myCommand->CommandText =String::Format("SELECT LOGINSTATUS FROM STATION WHERE PRODLINE = '" + prodline + "' AND STATIONID = '" + STNID + "' ");					
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
		{												
			valueStr = reader["LOGINSTATUS"]->ToString();
		}		
		reader->Close();
	}catch (SqlException ^sqle)
	{	
		SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "getLoginStatusFromStationSQL");
	}	
	SQLmyConnection->Close();
	return valueStr;
}
*/



void TestBridgeFunction()
{
	String ^valueStr="";
	//String ^myConnectionString = "Initial Catalog=ONLINEBTREKDB;Data Source=192.168.1.14;Integrated Security=SSPI;";
	//String ^myConnectionString = "Initial Catalog=ONLINEBTREKDB;Data Source=localhost;Integrated Security=SSPI;";
	String ^myConnectionString = "Data Source = 192.168.1.14,1433;Network Library = DBMSSOCN;Initial Catalog=ONLINEBTREKDB;User ID=sa;Password=1234;";
	SqlConnection ^SQLmyConnection = gcnew SqlConnection(); 
	if (SQLmyConnection->State == System::Data::ConnectionState::Open)
	{
		SQLmyConnection->Close();
	}
	SQLmyConnection->ConnectionString = myConnectionString; 
	//SqlCommand ^my_Command = gcnew SqlCommand();
	//my_Command->Connection = SQLmyConnection; 
	try{
	
		SQLmyConnection->Open();
		SqlCommand ^myCommand = gcnew SqlCommand();
		myCommand->Connection = SQLmyConnection;
		
		myCommand->CommandType = CommandType::Text;								
		myCommand->CommandText =String::Format("SELECT EMPFNAME FROM STATION WHERE PRODLINE = '1' AND STATIONID = '1' ");					
		SqlDataReader ^reader = myCommand->ExecuteReader();
		while(reader->Read())
		{												
			valueStr = reader["EMPFNAME"]->ToString();
		}		
		reader->Close();

	}
	catch (SqlException ^sqle)
	{
		int errornumber = sqle->Number;
		SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "TestBridge");
	}
	SQLmyConnection->Close();
	
}


String ^Retrieve_DataValue_FromBundleSeq(SqlCommand ^myCommand, String ^fieldName, String ^Prodline, int BundleNo, String ^PRODID)
{
	String ^str = "";
	myCommand->CommandType = CommandType::Text;								
	/*myCommand->CommandText =String::Format("SELECT "+ fieldName +" FROM BUNDLESEQ WHERE \
													PRODLINE = '"+ Prodline +"' \
													AND BUNDLENO = " + BundleNo + " \
													AND MONO = '" + Mono + "'");	*/
	myCommand->CommandText =String::Format("SELECT "+ fieldName +" FROM BUNDLESEQ1 WHERE PRODLINE = '"+ Prodline + "' " +
																						"AND BUNDLENO = " + BundleNo + " " +
																						"AND PRODID = '" + PRODID + "'");				
	SqlDataReader ^reader = myCommand->ExecuteReader();
	while(reader->Read())
		str = reader[fieldName]->ToString();
	reader->Close();
	return str;
}


String ^getSQLGoStation(SqlCommand ^my_Command, String ^PusherCount_STNID, String ^Timer_Prodline, String ^PusherCount_HangerID)
{
	String ^str="";
	my_Command->CommandType = CommandType::Text;								
	my_Command->CommandText =String::Format("SELECT INSTNID FROM GOSTN WHERE PRODLINE = '" + Timer_Prodline + "' AND OUTSTNID = '" + PusherCount_STNID +"' AND HANGERID = '"+ PusherCount_HangerID +"'");
	SqlDataReader ^reader = my_Command->ExecuteReader();
	while(reader->Read())
	{
		str = reader["INSTNID"]->ToString();
	}
	reader->Close();
	return str;
}

String ^getSQLGoStationLoad(SqlCommand ^my_Command, String ^PusherCount_STNID, String ^Timer_Prodline)
{
	String ^str="";
	my_Command->CommandType = CommandType::Text;								
	my_Command->CommandText =String::Format("SELECT INSTNID FROM GOSTN WHERE PRODLINE = '" + Timer_Prodline + "' AND OUTSTNID = '" + PusherCount_STNID +"' ");
	SqlDataReader ^reader = my_Command->ExecuteReader();
	while(reader->Read())
	{
		str = reader["INSTNID"]->ToString();
	}
	reader->Close();
	return str;
}
/*
using namespace System;
	using namespace System::Threading;
	using namespace System::Diagnostics;
//public static class SqlExtensions
	#pragma comment(lib, "mscorlib.lib")

class SqlExtensions
{
	public: static void QuickOpen(SqlConnection ^conn, int timeout)
    {
        // We'll use a Stopwatch here for simplicity. A comparison to a stored DateTime.Now value could also be used
        Stopwatch ^sw = gcnew Stopwatch();
        bool connectSuccess = false;
 
        // Try to open the connection, if anything goes wrong, make sure we set connectSuccess = false
        Thread ^t = gcnew Thread(delegate()
        {
            try
            {
                sw->Start();
                conn->Open();
                connectSuccess = true;
            }
            catch { }
        });
 
        // Make sure it's marked as a background thread so it'll get cleaned up automatically
        t->IsBackground = true;
        t->Start();
 
        // Keep trying to join the thread until we either succeed or the timeout value has been exceeded
        while (timeout > sw->ElapsedMilliseconds)
            if (t->Join(1))
                break;
 
        // If we didn't connect successfully, throw an exception
        if (!connectSuccess)
            throw new Exception("Timed out while trying to connect.");
    }
};
*/