#include "StdAfx.h"
#include "tcpCommon.h"

wchar_t stateMsgString[tcpSocket____MAXCOUNT][32] =
{
	L"--\0",
	L"Connecting\0",
	L"Connected\0",
	L"Connect fail\0"
};

wchar_t socktypeMsgString[isock____MAX][16] =
{
	L"CLIENT\0",
    L"SERVER\0"
};

wchar_t sockModeMsgString[tcpPort____MAX][16] =
{
	L"BINARY\0",
    L"TEXT\0"
};
