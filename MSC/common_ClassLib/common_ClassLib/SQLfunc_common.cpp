#include "StdAfx.h"
#include "registry.h"
#include "SQLfunc_common.h"
/*
BOOL sGetRegKeyValue(HKEY hRoot, LPCWSTR lpszRegPath, LPCWSTR lpszValName, String ^%szValue, DWORD *dwType)
{
	#define MAX_regVlaueSIZE		256
	DWORD dwSize = MAX_regVlaueSIZE; 
	BYTE szBuf[MAX_regVlaueSIZE]; 
	HKEY hKey;
	
	if( RegOpenKeyEx(hRoot, lpszRegPath, 0, KEY_QUERY_VALUE|KEY_WOW64_64KEY, & hKey) != ERROR_SUCCESS ) 
		return FALSE;
	if( RegQueryValueEx(hKey, lpszValName, 0, dwType, szBuf, & dwSize) != ERROR_SUCCESS ) 
		return FALSE;
	if( RegCloseKey(hKey) != ERROR_SUCCESS ) return FALSE;
   switch (*dwType){
		case REG_BINARY:		//Binary data in any form.
		case REG_DWORD:		//A 32-bit number.
//		case REG_DWORD_LITTLE_ENDIAN:		//A 32-bit number in little-endian format (same as REG_DWORD). In little-endian format, the most significant byte of a word is the high-order byte. This is the most common format for computers running Windows NT and Windows 95.
		case REG_DWORD_BIG_ENDIAN:		//A 32-bit number in big-endian format. In big-endian format, the most significant byte of a word is the low-order byte.
		case REG_EXPAND_SZ:		//A null-terminated string that contains unexpanded references to environment variables (for example, "%PATH%"). It will be a Unicode or ANSI string depending on whether you use the Unicode or ANSI functions.
		case REG_LINK:		//A Unicode symbolic link.
		case REG_MULTI_SZ:		//An array of null-terminated strings, terminated by two null characters.
		case REG_NONE:		//No defined value type.
		case REG_RESOURCE_LIST:		//A device-driver resource list.
		case REG_SZ:		//A null-terminated string. It will be a Unicode or ANSI string depending on whether you use the Unicode or ANSI functions.
            break;
		}
	szValue = gcnew String(reinterpret_cast<const wchar_t*>(szBuf));
	return TRUE;

}
*/

BOOL sGetRegKeyValue(HKEY hRoot, LPCWSTR lpszRegPath, LPCWSTR lpszValName, String ^%szValue, DWORD *dwType, DWORD *reg_dword)
{
	#define MAX_regVlaueSIZE		256
	//DWORD dwSize = MAX_regVlaueSIZE; 
	BYTE szBuf[MAX_regVlaueSIZE];
	DWORD dwSize = sizeof(szBuf);
	HKEY hKey = 0;
	DWORD nResult = 0;
	
	if( RegOpenKeyEx(hRoot, lpszRegPath, 0, KEY_QUERY_VALUE|KEY_WOW64_64KEY, & hKey) != ERROR_SUCCESS ) 
		return FALSE;
	//  RegQueryValueEx(hKey,"url1",NULL,NULL,(PBYTE)url1,&lin);
	//if( RegQueryValueEx(hKey, lpszValName, 0, dwType, szBuf, & dwSize) != ERROR_SUCCESS ) 
	if (*dwType==REG_DWORD)
	{
		if( RegQueryValueEx(hKey, lpszValName,   0,   NULL, reinterpret_cast<LPBYTE>(&nResult), &dwSize) != ERROR_SUCCESS ) 
		//( RegQueryValueEx(hKey, lpszValName, NULL, NULL, (BYTE*)szBuf, &dwSize) != ERROR_SUCCESS ) 
			return FALSE;
	}
	else
	{
		if( RegQueryValueEx(hKey, lpszValName, 0, dwType, szBuf, &dwSize) != ERROR_SUCCESS ) 
			return FALSE;
	}
	if( RegCloseKey(hKey) != ERROR_SUCCESS ) return FALSE;
   switch (*dwType){
		case REG_DWORD:		//A 32-bit number.
			*reg_dword = nResult;
			szValue = nResult.ToString();
			break;
		case REG_BINARY:		//Binary data in any form.
//		case REG_DWORD_LITTLE_ENDIAN:		//A 32-bit number in little-endian format (same as REG_DWORD). In little-endian format, the most significant byte of a word is the high-order byte. This is the most common format for computers running Windows NT and Windows 95.
		case REG_DWORD_BIG_ENDIAN:		//A 32-bit number in big-endian format. In big-endian format, the most significant byte of a word is the low-order byte.
		case REG_LINK:		//A Unicode symbolic link.
		case REG_NONE:		//No defined value type.
		case REG_RESOURCE_LIST:		//A device-driver resource list.
			/*{
				wchar_t = szBuf;
			for (int ii=0;ii<dwSize;ii++)
			{

			}
			}*/
            break;
		case REG_MULTI_SZ:		//An array of null-terminated strings, terminated by two null characters.
		case REG_EXPAND_SZ:		//A null-terminated string that contains unexpanded references to environment variables (for example, "%PATH%"). It will be a Unicode or ANSI string depending on whether you use the Unicode or ANSI functions.
		case REG_SZ:		//A null-terminated string. It will be a Unicode or ANSI string depending on whether you use the Unicode or ANSI functions.
		default:
			szValue = gcnew String(reinterpret_cast<const wchar_t*>(szBuf));
			break;
		}

	return TRUE;

}


/*
HKEY hKey;
LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Perl", 0, KEY_READ, &hKey);
bool bExistsAndSuccess (lRes == ERROR_SUCCESS);
bool bDoesNotExistsSpecifically (lRes == ERROR_FILE_NOT_FOUND);
std::wstring strValueOfBinDir;
std::wstring strKeyDefaultValue;
GetStringRegKey(hKey, L"BinDir", strValueOfBinDir, L"bad");
GetStringRegKey(hKey, L"", strKeyDefaultValue, L"bad");

LONG GetDWORDRegKey(HKEY hKey, const std::wstring &strValueName, DWORD &nValue, DWORD nDefaultValue)
{
    nValue = nDefaultValue;
    DWORD dwBufferSize(sizeof(DWORD));
    DWORD nResult(0);
    LONG nError = ::RegQueryValueExW(hKey,
        strValueName.c_str(),
        0,
        NULL,
        reinterpret_cast<LPBYTE>(&nResult),
        &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        nValue = nResult;
    }
    return nError;
}


LONG GetBoolRegKey(HKEY hKey, const std::wstring &strValueName, bool &bValue, bool bDefaultValue)
{
    DWORD nDefValue((bDefaultValue) ? 1 : 0);
    DWORD nResult(nDefValue);
    LONG nError = GetDWORDRegKey(hKey, strValueName.c_str(), nResult, nDefValue);
    if (ERROR_SUCCESS == nError)
    {
        bValue = (nResult != 0) ? true : false;
    }
    return nError;
}


LONG GetStringRegKey(HKEY hKey, const std::wstring &strValueName, std::wstring &strValue, const std::wstring &strDefaultValue)
{
    strValue = strDefaultValue;
    WCHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;
    nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        strValue = szBuffer;
    }
    return nError;
}
*/

String ^GetDotNetVersionInformation(String ^%InstanceName, String ^%SQLRootpath)
			 {
				InstanceName = "";
				wchar_t regKeypath[] = L"SOFTWARE\\Microsoft\\.NETFramework\\\0";
				wchar_t regKeyParameter[] = L"InstallRoot\0";
				String ^valueStr = "";
				DWORD dwtype = REG_SZ;
				DWORD dwvalue = 0;
				sGetRegKeyValue(HKEY_LOCAL_MACHINE, regKeypath,  regKeyParameter, SQLRootpath, &dwtype, &dwvalue);
				return valueStr;
			 }

String ^GetSQLVersionInformation(String ^%InstanceName, String ^%SQLRootpath)
			 {
				InstanceName = "";
				//HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Microsoft SQL Server\SQLEXPRESS\MSSQLServer\CurrentVersion\CurrentVersion
				wchar_t regKeypath[] = L"SOFTWARE\\Microsoft\\Microsoft SQL Server\\SQLEXPRESS\\MSSQLServer\\CurrentVersion\\\0";
				wchar_t regKeyParameter[] = L"CurrentVersion\0";
				//date_FormatKEYPAD = gcnew String(reinterpret_cast<const char*>(applicationSetting->data.mdate_FormatKEYPAD));
				//-------------------------------------------------------------------------
				String ^valueStr = "";
				DWORD dwtype = REG_SZ;
				DWORD dwvalue = 0;
				sGetRegKeyValue(HKEY_LOCAL_MACHINE, regKeypath,  regKeyParameter, valueStr, &dwtype, &dwvalue);

				sGetRegKeyValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Microsoft SQL Server\\Instance Names\\SQL\\\0",  
													L"SQLEXPRESS\0", InstanceName, &dwtype, &dwvalue);

			
				String ^pPath = "SOFTWARE\\Microsoft\\Microsoft SQL Server\\"+InstanceName+"\\Setup\0";
				pin_ptr<const wchar_t> wpath = PtrToStringChars(pPath);
				SQLRootpath = "";
				sGetRegKeyValue(HKEY_LOCAL_MACHINE, wpath,  L"SQLPath\0", SQLRootpath, &dwtype, &dwvalue);

				//HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Microsoft SQL Server\MSSQL10_50.SQLEXPRESS\Setup
				if (!InstanceName)
					InstanceName = "";
				if (InstanceName==nullptr)
					InstanceName = "";

				return valueStr;
			 }

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