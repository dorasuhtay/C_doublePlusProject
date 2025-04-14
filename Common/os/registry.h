#ifndef __REGISTRY_H_
#define __REGISTRY_H_

#include <windows.h>


bool GetRegKeyValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName, TCHAR * lpData, DWORD dwSize);
//BOOL GetRegKeyValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName, xstring *szValue, DWORD *dwType);
bool SetRegKeyValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName, LPCTSTR lpszValue, DWORD dwType, REGSAM samDesired = 0);
//BOOL SetRegKeyValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName, LPCTSTR lpszValue, DWORD dwType);


bool DeleteRegKey(HKEY hRoot, LPCTSTR lpszRegPath);
bool DeleteRegValue(HKEY hRoot, LPCTSTR lpszRegPath, LPCTSTR lpszValName);

bool RegisterInProcServer(LPCTSTR lpszClsID, LPCTSTR lpszProgID, LPCTSTR lpszServerPath);
bool UnregisterInProcServer(LPCTSTR lpszClsID, LPCTSTR lpszProgID);
extern BOOL IsCurrentUserLocalAdministrator(void);




#endif // __REGISTRY_H_