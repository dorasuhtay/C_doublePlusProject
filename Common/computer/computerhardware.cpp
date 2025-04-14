#include "StdAfx.h"
#include <windows.h>
#include <stdio.h>
#include <string>
#include <sstream>
#pragma comment(lib, "user32.lib")
#include "computerhardware.h"

DWORD GetNumCPUs() 
{
	SYSTEM_INFO m_si = {0, };
	//GetSystemInfo(&m_si);
	GetNativeSystemInfo(&m_si);
	return m_si.dwNumberOfProcessors;
}
/*
int CPU_ProcessorBit()
{
	if(sizeof(void*) == 4 )
		return 32;	// 32 bit
	else
		if (sizeof(void*) == 8 )
			return 64;	// 64 bit
	return 0;
}
*/

//#include <windows.h>



typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);
#define PRODUCT_PROFESSIONAL	0x00000030
#define VER_SUITE_WH_SERVER	0x00008000



bool windowsVersionName(wchar_t* str, int bufferSize, COMPUTERHARDWAREINFO	*info)
{
	memset(info, 0x0, sizeof(COMPUTERHARDWAREINFO));
	OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;
	BOOL bOsVersionInfoEx;
	DWORD dwType; ZeroMemory(&si, sizeof(SYSTEM_INFO));
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX)); osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*) &osvi); 
	if(bOsVersionInfoEx == 0)
		return false; // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
	PGNSI pGNSI = (PGNSI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
	if(NULL != pGNSI)
		pGNSI(&si);
	else 
		GetSystemInfo(&si); // Check for unsupported OS
	if (VER_PLATFORM_WIN32_NT != osvi.dwPlatformId || osvi.dwMajorVersion <= 4 ) 
	{
		return false;
	} 
	std::wstringstream os;
	os << L"Microsoft "; // Test for the specific product. if ( osvi.dwMajorVersion == 6 )
 
	{
		if( osvi.dwMinorVersion == 0 )
		{
			if( osvi.wProductType == VER_NT_WORKSTATION )
			{
				strcpy(info->OSname, "Windows Vista");
				os << "Windows Vista ";
			}
			else 
			{
				strcpy(info->OSname, "Windows Server 2008");
				os << "Windows Server 2008 ";
			}
		}  
		if ( osvi.dwMinorVersion == 1 )
		{
			if( osvi.wProductType == VER_NT_WORKSTATION )
			{
				strcpy(info->OSname, "Windows 7");
				os << "Windows 7 ";
			}
			else 
			{
				strcpy(info->OSname, "Windows Server 2008 R2");
				os << "Windows Server 2008 R2 ";
			}
		}  
		PGPI pGPI = (PGPI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetProductInfo");
		pGPI( osvi.dwMajorVersion, osvi.dwMinorVersion, 0, 0, &dwType);  
		switch( dwType )
		{
			case PRODUCT_ULTIMATE:
					os << "Ultimate Edition";
					break;
			case PRODUCT_PROFESSIONAL:
					os << "Professional";
					break;
			case PRODUCT_HOME_PREMIUM:
					os << "Home Premium Edition";
					break;
			case PRODUCT_HOME_BASIC:
					os << "Home Basic Edition";
					break;
			case PRODUCT_ENTERPRISE:
					os << "Enterprise Edition";
					break;
			case PRODUCT_BUSINESS:
					os << "Business Edition";
					break;
			case PRODUCT_STARTER:
					os << "Starter Edition";
					break;
			case PRODUCT_CLUSTER_SERVER:
					os << "Cluster Server Edition";
					break;
			case PRODUCT_DATACENTER_SERVER:
					os << "Datacenter Edition";
					break;
			case PRODUCT_DATACENTER_SERVER_CORE:
					os << "Datacenter Edition (core installation)";
					break;
			case PRODUCT_ENTERPRISE_SERVER:
					os << "Enterprise Edition";
					break;
			case PRODUCT_ENTERPRISE_SERVER_CORE:
					os << "Enterprise Edition (core installation)";
					break;
			case PRODUCT_ENTERPRISE_SERVER_IA64:
					os << "Enterprise Edition for Itanium-based Systems";
					break;
			case PRODUCT_SMALLBUSINESS_SERVER:
					os << "Small Business Server";
					break;
			case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
					os << "Small Business Server Premium Edition";
					break;
			case PRODUCT_STANDARD_SERVER:
					os << "Standard Edition";
					break;
			case PRODUCT_STANDARD_SERVER_CORE:
					os << "Standard Edition (core installation)";
					break;
			case PRODUCT_WEB_SERVER:
					os << "Web Server Edition";
					break;
		}
	} 
	if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
	{
		if( GetSystemMetrics(SM_SERVERR2) )
			os <<  "Windows Server 2003 R2, ";
		else 
			if ( osvi.wSuiteMask & VER_SUITE_STORAGE_SERVER )
				os <<  "Windows Storage Server 2003";
			else 
				if ( osvi.wSuiteMask & VER_SUITE_WH_SERVER )
					os <<  "Windows Home Server";
				else 
					if( osvi.wProductType == VER_NT_WORKSTATION &&
							si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
					{
						os <<  "Windows XP Professional x64 Edition";
					}
					else 
						os << "Windows Server 2003, ";  // Test for the server type.
					if ( osvi.wProductType != VER_NT_WORKSTATION )
					{
						if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_IA64 )
						{
							if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
								os <<  "Datacenter Edition for Itanium-based Systems";
							else 
								if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
									os <<  "Enterprise Edition for Itanium-based Systems";
						}   
						else 
							if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
							{
								if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
									os <<  "Datacenter x64 Edition";
								else 
									if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
										os <<  "Enterprise x64 Edition";
									else 
										os <<  "Standard x64 Edition";
							}   
							else
							{
								if ( osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER )
									os <<  "Compute Cluster Edition";
								else 
									if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
										os <<  "Datacenter Edition";
									else 
										if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
											os <<  "Enterprise Edition";
										else 
											if ( osvi.wSuiteMask & VER_SUITE_BLADE )
												os <<  "Web Edition";
											else 
												os <<  "Standard Edition";
							}
					}
	} 
	if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
	{
		os << "Windows XP ";
		if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
			os <<  "Home Edition";
		else 
			os <<  "Professional";
	} 
	if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
	{
		os << "Windows 2000 ";  
		if ( osvi.wProductType == VER_NT_WORKSTATION )
		{
			os <<  "Professional";
		}
		else 
		{
			if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
				os <<  "Datacenter Server";
			else 
				if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
					os <<  "Advanced Server";
				else 
					os <<  "Server";
		}
	} // Include service pack (if any) and build number. 
	if(wcslen(osvi.szCSDVersion) > 0) 
	{
		os << " " << osvi.szCSDVersion;
	} 
		os << L" (build " << osvi.dwBuildNumber << L")"; 
	if ( osvi.dwMajorVersion >= 6 ) 
	{
		if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
		{
			info->CPU_ProcessorBit = 64;
			os <<  ", 64-bit";
		}
		else 
			if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
			{
				info->CPU_ProcessorBit = 32;
				os << ", 32-bit";
			}
	} 
	wcscpy_s(str, bufferSize, os.str().c_str());
 return true; 
}


#include <windows.h>
#include <stdio.h>
#include <tchar.h>

// Use to convert bytes to KB
#define DIV 1024

// Specify the width of the field in which to print the numbers. 
// The asterisk in the format specifier "%*I64d" takes an integer 
// argument and uses it to pad and right justify the number.
#define WIDTH 7

void _tmain()
{
  MEMORYSTATUSEX statex;
  statex.dwLength = sizeof (statex);
  GlobalMemoryStatusEx (&statex);
  /*
  _tprintf (TEXT("There is  %*ld percent of memory in use.\n"),
            WIDTH, statex.dwMemoryLoad);
  _tprintf (TEXT("There are %*I64d total KB of physical memory.\n"),
            WIDTH, statex.ullTotalPhys/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of physical memory.\n"),
            WIDTH, statex.ullAvailPhys/DIV);
  _tprintf (TEXT("There are %*I64d total KB of paging file.\n"),
            WIDTH, statex.ullTotalPageFile/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of paging file.\n"),
            WIDTH, statex.ullAvailPageFile/DIV);
  _tprintf (TEXT("There are %*I64d total KB of virtual memory.\n"),
            WIDTH, statex.ullTotalVirtual/DIV);
  _tprintf (TEXT("There are %*I64d free  KB of virtual memory.\n"),
            WIDTH, statex.ullAvailVirtual/DIV);

  // Show the amount of extended memory available.

  _tprintf (TEXT("There are %*I64d free  KB of extended memory.\n"),
            WIDTH, statex.ullAvailExtendedVirtual/DIV);
  */
}