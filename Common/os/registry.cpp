#include "stdafx.h"
#include "registry.h"

#ifdef UNICODE
	#include <TCHAR.H>
	#define STRLEN		_tcslen
	#define CHAR_T		wchar_t
	#pragma comment(lib, "Advapi32.lib")

/*
		#pragma comment(lib, "User32.Lib")
		#pragma comment(lib, "Kernel32.Lib")
Urlmon.Lib
User32.Lib
UserEnv.Lib
USP10.Lib
Uuid.Lib
Uxtheme.lib
VdmDbg.Lib
vds_uuid.lib
Version.Lib
Vfw32.Lib
virtdisk.lib
vpccominterfaces.lib
vssapi.lib
vss_uuid.lib
vstorinterface.lib
WbemUuid.Lib
wcmguid.lib
wdsbp.lib
WdsClientApi.lib
wdsmc.lib
wdspxe.lib
wdstptc.lib
WebPost.Lib
WebServices.lib
wecapi.lib
WER.LIB
wevtapi.lib
#pragma comment(lib, "WiaGuid.Lib
#pragma comment(lib, "WinBio.lib
#pragma comment(lib, "windowscodecs.lib
#pragma comment(lib, "WindowsSideShowGuids.lib
#pragma comment(lib, "WinFax.Lib
#pragma comment(lib, "winhttp.lib
#pragma comment(lib, "WinInet.Lib

#pragma comment(lib, "WinMM.Lib")
#pragma comment(lib, "winsatapi.lib")
#pragma comment(lib, "WinSCard.Lib")
#pragma comment(lib, "WinSpool.Lib")
#pragma comment(lib, "WinStrm.Lib")
#pragma comment(lib, "WinTrust.Lib")
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "wlanui.lib")
#pragma comment(lib, "Wldap32.Lib")
#pragma comment(lib, "wmcodecdspuuid.lib")
#pragma comment(lib, "wmdrmsdk.lib")
#pragma comment(lib, "wmiutils.lib")
#pragma comment(lib, "wmvcore.lib")
#pragma comment(lib, "workspaceax.lib")
#pragma comment(lib, "Wow32.Lib")
#pragma comment(lib, "WS2_32.Lib")
#pragma comment(lib, "wsbapp_uuid.Lib")
#pragma comment(lib, "wscapi.lib")
#pragma comment(lib, "wsdapi.lib")
#pragma comment(lib, "wsmsvc.lib")
#pragma comment(lib, "WSnmp32.Lib")
#pragma comment(lib, "WSock32.Lib")
#pragma comment(lib, "Wst.Lib")
#pragma comment(lib, "WtsApi32.Lib")
#pragma comment(lib, "wuguid.lib")
#pragma comment(lib, "xaSwitch.Lib")
#pragma comment(lib, "Xinput.lib")
#pragma comment(lib, "xmllite.lib")
#pragma comment(lib, "xoleHlp.Lib")
#pragma comment(lib, "xpsprint.lib")
*/
/*
	#pragma comment(lib, "comsupp.lib")
	#pragma comment(lib, "comsuppd.lib")
	#pragma comment(lib, "comsuppw.lib")
	#pragma comment(lib, "comsuppwd.lib")
	#pragma comment(lib, "delayimp.lib")
	#pragma comment(lib, "libcmt.lib")
	#pragma comment(lib, "libcmtd.lib")
	#pragma comment(lib, "libcpmt.lib")
	#pragma comment(lib, "libcpmt1.lib")
	#pragma comment(lib, "libcpmtd.lib")
	#pragma comment(lib, "libcpmtd0.lib")
	#pragma comment(lib, "libcpmtd1.lib")
	#pragma comment(lib, "msvcmrt.lib")
	#pragma comment(lib, "msvcmrtd.lib")
	#pragma comment(lib, "msvcprt.lib")
	#pragma comment(lib, "msvcprtd.lib")
	#pragma comment(lib, "msvcrt.lib")
	#pragma comment(lib, "msvcrtd.lib")
	#pragma comment(lib, "msvcurt.lib")
	#pragma comment(lib, "msvcurtd.lib")
	#pragma comment(lib, "oldnames.lib")
	#pragma comment(lib, "ptrustm.lib")
	#pragma comment(lib, "ptrustmd.lib")
	#pragma comment(lib, "ptrustu.lib")
	#pragma comment(lib, "ptrustud.lib")
	#pragma comment(lib, "RunTmChk.lib")
	#pragma comment(lib, "wsetargv.obj")
*/
#else
	#define STRLEN		strlen
	#define CHAR_T		char
#endif

bool GetRegKeyValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName, TCHAR * lpData, DWORD dwSize)
{
	DWORD dwType; HKEY hKey;
	if( RegOpenKeyEx(hRoot, lpszRegPath, 0, KEY_QUERY_VALUE, & hKey) != ERROR_SUCCESS ) return false;
	if( RegQueryValueEx(hKey, lpszValName, 0, & dwType, (BYTE *)lpData, & dwSize) != ERROR_SUCCESS ) return false;
	if( RegCloseKey(hKey) != ERROR_SUCCESS ) return false;
	return true;
}
/*
bool GetRegKeyValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName, xstring *szValue, DWORD *dwType)
{
//	DWORD dwType, dwSize = MAX_PATH; BYTE szBuf[MAX_PATH]; HKEY hKey;
	DWORD dwSize = MAX_PATH; BYTE szBuf[MAX_PATH]; HKEY hKey;
	if( RegOpenKeyEx(hRoot, lpszRegPath, 0, KEY_QUERY_VALUE, & hKey) != ERROR_SUCCESS ) return false;
	if( RegQueryValueEx(hKey, lpszValName, 0, dwType, szBuf, & dwSize) != ERROR_SUCCESS ) return false;
	if( RegCloseKey(hKey) != ERROR_SUCCESS ) return false;
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
	if (szValue) szValue->assign(szBuf);
	return true;
}
*/

/*
bool SetRegKeyValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName, LPCTSTR lpszValue)
{
	DWORD dwType, dwDisposition; TCHAR szBuf[MAX_PATH]; HKEY hKey;
	dwType = REG_SZ; szBuf[0] = '\0';
	if( RegCreateKeyEx(hRoot, lpszRegPath, 0, szBuf, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, & hKey, & dwDisposition) != ERROR_SUCCESS ) return false;
	//if( RegSetValueEx(hKey, lpszValName, 0, dwType, (const BYTE *)lpszValue, strlen(lpszValue)+1) != ERROR_SUCCESS ) return false;
	if( RegSetValueEx(hKey, lpszValName, 0, dwType, (const BYTE *)lpszValue, STRLEN(lpszValue)+1) != ERROR_SUCCESS ) return false;
	if( RegCloseKey(hKey) != ERROR_SUCCESS ) return false;
	return true;
}
*/

bool SetRegKeyValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName, LPCTSTR lpszValue, DWORD dwType, REGSAM samDesired)
{
//	DWORD dwType, dwDisposition; TCHAR szBuf[MAX_PATH]; HKEY hKey;
//	dwType = REG_SZ; szBuf[0] = '\0';
	int leng = (STRLEN(lpszValue)+1)*sizeof(CHAR_T);
	DWORD dwDisposition; TCHAR szBuf[MAX_PATH]; HKEY hKey;
//	dwType = REG_SZ;
	szBuf[0] = '\0';

	//security
	//--------------------------
	SECURITY_DESCRIPTOR SD;
    SECURITY_ATTRIBUTES SA;

    if(!InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION))
        return false;

    if(!SetSecurityDescriptorDacl(&SD, true, 0, false))
        return false;

    SA.nLength             = sizeof(SA);
    SA.lpSecurityDescriptor = &SD;
    SA.bInheritHandle      = false;

	//-------------------------------------------

	//if( RegCreateKeyEx(hRoot, lpszRegPath, 0, szBuf, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_WOW64_64KEY, NULL, & hKey, & dwDisposition) != ERROR_SUCCESS ) return false;
	if( RegCreateKeyEx(hRoot, lpszRegPath, 0, szBuf, REG_OPTION_NON_VOLATILE, KEY_WRITE|samDesired, &SA, &hKey, &dwDisposition) != ERROR_SUCCESS ) 
		return false;
	switch(dwType)
	{
		case	REG_DWORD:
				{
					DWORD value = _ttoi(lpszValue);
					if( RegSetValueEx(hKey, lpszValName, 0, dwType, reinterpret_cast<LPBYTE>(&value), (STRLEN(lpszValue)+1)*sizeof(CHAR_T)) != ERROR_SUCCESS ) 
						return false;
				}	
				break;
		default:
				if( RegSetValueEx(hKey, lpszValName, 0, dwType, (const BYTE *)lpszValue, (STRLEN(lpszValue)+1)*sizeof(CHAR_T)) != ERROR_SUCCESS ) 
					return false;
			break;
	}
	if( RegCloseKey(hKey) != ERROR_SUCCESS ) return false;
	return true;
}



bool DeleteRegKey(HKEY hRoot, LPCTSTR lpszRegPath)
{
	if( RegDeleteKey(hRoot, lpszRegPath) != ERROR_SUCCESS ) true; // return false;
	return true;
}

bool DeleteRegValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName)
{
	HKEY hKey;
	if( RegOpenKeyEx(hRoot, lpszRegPath, 0, KEY_WRITE, & hKey) != ERROR_SUCCESS ) return false;
	if( RegDeleteValue(hKey, lpszValName) != ERROR_SUCCESS ) true; //return false;
	if( RegCloseKey(hKey) != ERROR_SUCCESS ) return false;
	return true;
}

bool RegisterInProcServer(LPCTSTR lpszClsID, LPCTSTR lpszProgID, LPCTSTR lpszServerPath)
{
/*
	xstring szRegPath;
	szRegPath.Format("CLSID\\%s", lpszClsID);
	if( ! SetRegKeyValue(HKEY_CLASSES_ROOT, szRegPath, "", lpszProgID) ) return false;
	szRegPath.Format("CLSID\\%s\\InProcServer32", lpszClsID);
	if( ! SetRegKeyValue(HKEY_CLASSES_ROOT, szRegPath, "", lpszServerPath) ) return false;
	if( ! SetRegKeyValue(HKEY_CLASSES_ROOT, szRegPath, "ThreadingModel", "Apartment") ) return false;
	szRegPath.Format("CLSID\\%s\\ProgID", lpszClsID);
	if( ! SetRegKeyValue(HKEY_CLASSES_ROOT, szRegPath, "", lpszProgID) ) return false;
	szRegPath.Format("%s", lpszProgID);
	if( ! SetRegKeyValue(HKEY_CLASSES_ROOT, szRegPath, "", lpszProgID) ) return false;
	szRegPath.Format("%s\\CLSID", lpszProgID);
	if( ! SetRegKeyValue(HKEY_CLASSES_ROOT, szRegPath, "", lpszClsID) ) return false;
*/
	return true;
}

bool UnregisterInProcServer(LPCTSTR lpszClsID, LPCTSTR lpszProgID)
{
/*
	CString szRegPath;
	szRegPath.Format("%s\\CLSID", lpszProgID);
	if( ! DeleteRegKey(HKEY_CLASSES_ROOT, szRegPath) ) return false;
	szRegPath.Format("%s", lpszProgID);
	if( ! DeleteRegKey(HKEY_CLASSES_ROOT, szRegPath) ) return false;
	szRegPath.Format("CLSID\\%s\\ProgID", lpszClsID);
	if( ! DeleteRegKey(HKEY_CLASSES_ROOT, szRegPath) ) return false;
	szRegPath.Format("CLSID\\%s\\InProcServer32", lpszClsID);
	if( ! DeleteRegKey(HKEY_CLASSES_ROOT, szRegPath) ) return false;
	szRegPath.Format("CLSID\\%s", lpszClsID);
	if( ! DeleteRegKey(HKEY_CLASSES_ROOT, szRegPath) ) return false;
*/   
	return true;
}


#include <windows.h>
#include <stdio.h>
#include <lmcons.h>
/*-------------------------------------------------------------------------

-
IsCurrentUserLocalAdministrator ()

This function checks the token of the calling thread to see if the caller
belongs to the Administrators group.

Return Value:
   TRUE if the caller is an administrator on the local machine.
   Otherwise, FALSE.
--------------------------------------------------------------------------*/


BOOL IsCurrentUserLocalAdministrator(void)
{
   BOOL   fReturn         = FALSE;
   DWORD  dwStatus;
   DWORD  dwAccessMask;
   DWORD  dwAccessDesired;
   DWORD  dwACLSize;
   DWORD  dwStructureSize = sizeof(PRIVILEGE_SET);
   PACL   pACL            = NULL;
   PSID   psidAdmin       = NULL;

   HANDLE hToken              = NULL;
   HANDLE hImpersonationToken = NULL;

   PRIVILEGE_SET   ps;
   GENERIC_MAPPING GenericMapping;

   PSECURITY_DESCRIPTOR     psdAdmin           = NULL;
   SID_IDENTIFIER_AUTHORITY SystemSidAuthority = SECURITY_NT_AUTHORITY;


   /*
      Determine if the current thread is running as a user that is a member 

of
      the local admins group.  To do this, create a security descriptor 

that
      has a DACL which has an ACE that allows only local aministrators 

access.
      Then, call AccessCheck with the current thread's token and the 

security
      descriptor.  It will say whether the user could access an object if 

it
      had that security descriptor.  Note: you do not need to actually 

create
      the object.  Just checking access against the security descriptor 

alone
      will be sufficient.
   */
   const DWORD ACCESS_READ  = 1;
   const DWORD ACCESS_WRITE = 2;


   __try
   {

      /*
         AccessCheck() requires an impersonation token.  We first get a 

primary
         token and then create a duplicate impersonation token.  The
         impersonation token is not actually assigned to the thread, but is
         used in the call to AccessCheck.  Thus, this function itself never
         impersonates, but does use the identity of the thread.  If the 

thread
         was impersonating already, this function uses that impersonation 

context.
      */
      if (!OpenThreadToken(GetCurrentThread(), TOKEN_DUPLICATE|TOKEN_QUERY, 

TRUE, &hToken))
      {
         if (GetLastError() != ERROR_NO_TOKEN)
            __leave;

         if (!OpenProcessToken(GetCurrentProcess(), 

TOKEN_DUPLICATE|TOKEN_QUERY, &hToken))
            __leave;
      }

      if (!DuplicateToken (hToken, SecurityImpersonation, 

&hImpersonationToken))
          __leave;


      /*
        Create the binary representation of the well-known SID that
        represents the local administrators group.  Then create the 

security
        descriptor and DACL with an ACE that allows only local admins 

access.
        After that, perform the access check.  This will determine whether
        the current user is a local admin.
      */
      if (!AllocateAndInitializeSid(&SystemSidAuthority, 2,
                                    SECURITY_BUILTIN_DOMAIN_RID,
                                    DOMAIN_ALIAS_RID_ADMINS,
                                    0, 0, 0, 0, 0, 0, &psidAdmin))
         __leave;

      psdAdmin = LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
      if (psdAdmin == NULL)
         __leave;

      if (!InitializeSecurityDescriptor(psdAdmin, 

SECURITY_DESCRIPTOR_REVISION))
         __leave;

      // Compute size needed for the ACL.
      dwACLSize = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) +
                  GetLengthSid(psidAdmin) - sizeof(DWORD);

      pACL = (PACL)LocalAlloc(LPTR, dwACLSize);
      if (pACL == NULL)
         __leave;

      if (!InitializeAcl(pACL, dwACLSize, ACL_REVISION2))
         __leave;

      dwAccessMask= ACCESS_READ | ACCESS_WRITE;

      if (!AddAccessAllowedAce(pACL, ACL_REVISION2, dwAccessMask, 

psidAdmin))
         __leave;

      if (!SetSecurityDescriptorDacl(psdAdmin, TRUE, pACL, FALSE))
         __leave;

      /*
         AccessCheck validates a security descriptor somewhat; set the 

group
         and owner so that enough of the security descriptor is filled out 

to
         make AccessCheck happy.
      */
      SetSecurityDescriptorGroup(psdAdmin, psidAdmin, FALSE);
      SetSecurityDescriptorOwner(psdAdmin, psidAdmin, FALSE);

      if (!IsValidSecurityDescriptor(psdAdmin))
         __leave;

      dwAccessDesired = ACCESS_READ;

      /*
         Initialize GenericMapping structure even though you
         do not use generic rights.
      */
      GenericMapping.GenericRead    = ACCESS_READ;
      GenericMapping.GenericWrite   = ACCESS_WRITE;
      GenericMapping.GenericExecute = 0;
      GenericMapping.GenericAll     = ACCESS_READ | ACCESS_WRITE;

      if (!AccessCheck(psdAdmin, hImpersonationToken, dwAccessDesired,
                       &GenericMapping, &ps, &dwStructureSize, &dwStatus,
                       &fReturn))
      {
         fReturn = FALSE;
         __leave;
      }
   }
   __finally
   {
      // Clean up.
      if (pACL) LocalFree(pACL);
      if (psdAdmin) LocalFree(psdAdmin);
      if (psidAdmin) FreeSid(psidAdmin);
      if (hImpersonationToken) CloseHandle (hImpersonationToken);
      if (hToken) CloseHandle (hToken);
   }

   return fReturn;
}