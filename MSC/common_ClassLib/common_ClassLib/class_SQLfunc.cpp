#include "StdAfx.h"
#include "class_SQLfunc.h"

bool SQL_errorExceptionLog(SqlException ^sqle, const char *file, int line, String ^remarks)
{
	if (processErrorLog)
		processErrorLog->logError("SQL", sqle->Number, file, line, sqle->Message, remarks); 
		return 1;
}

int openDBConnection(SqlConnection ^%SQLmyConnection, String ^myConnectionString)
{
	int nn = 0;
	SQLmyConnection = gcnew SqlConnection(); 
	try
	{
		SQLmyConnection->ConnectionString = myConnectionString; 
		SQLmyConnection->Open();
	}
	catch (SqlException ^sqle)
	{
		SQL_errorExceptionLog(sqle, __FILE__, __LINE__, "openDBConnection");
		nn = -1;
	}
	SQLmyConnection->Close();
	return nn;
}

//e.g. openDBConnection(SqlConnection ^%SQLmyConnection, "127.0.0.1", "ONLINEBTREKDB", "sa", "1234");
int openDBConnection(SqlConnection ^%SQLmyConnection, String ^ipaddress, String ^dbname, String ^ID, String ^password, int timeout)
{
	//String ^myConnectionString = "Initial Catalog="+dbname+";Data Source="+address+";Integrated Security=SSPI;";
	String ^myConnectionString =	"Data Source = "+ipaddress+
									";Network Library = DBMSSOCN;Initial Catalog="+dbname+
									";User ID="+ID+";Password="+password + ";";
	if (timeout>0)
		myConnectionString += "Connect Timeout="+timeout.ToString() + ";"; 
	
	return openDBConnection(SQLmyConnection, myConnectionString);
}

