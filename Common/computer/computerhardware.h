#ifndef __HARDWARE___H
#define __HARDWARE___H

typedef struct 
{
	int CPU_ProcessorBit;
	char OSname[64];
	char OSedition[64];
}COMPUTERHARDWAREINFO;


extern DWORD GetNumCPUs();
//extern int CPU_ProcessorBit();
//extern BOOL GetOSDisplayString( LPTSTR pszOS);
extern bool windowsVersionName(wchar_t* str, int bufferSize);
extern bool windowsVersionName(wchar_t* str, int bufferSize, COMPUTERHARDWAREINFO	*info);

#endif