#ifdef __GNUC__
    #define STRINGPTR   wchar_t *
    #define NULLValue   0
	#define SPRINTF		snprintf
	#define STRCPY		strcpy_s
	#define STRNCPY(a, b, c)		strncpy(a, b, c)
	#define STRREV		_strrev
	#define TCSCPY		_tcscpy
	#define TCSNCPY		_tcsncpy
#else
    using namespace System;
    #define STRINGPTR   String ^
    #define NULLValue   ""
	#define SPRINTF		sprintf_s
	#define STRCPY		strcpy_s
	#define STRNCPY(a, b, c)		strcpy_s(a, c, b)
	#define STRREV		_strrev
	#define TCSCPY		wcscpy_s
	#define TCSNCPY		wcsncpy_s
#endif

