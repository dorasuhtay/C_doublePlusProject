#ifndef __tcpCommon__H
#define __tcpCommon__H

#define textline_SIZE			1024

enum{
	tcpPort_BINARY=0,
	tcpPort_COMMAND_TEXT,
    tcpPort____MAX,
};

enum{
	tcpStatus_NULL=0,
	tcpStatus_NOTCONNECTED,
	tcpStatus_CONNECTED
};

enum{
    isock_CLIENT=0,
    isock_SERVER,
    isock____MAX,
};

enum{
	tcpSocket_NULL=0,
	tcpSocket_CONNECTING,
	tcpSocket_CONNECTED,
	tcpSocket_CONNECTFAIL,
	tcpSocket____MAXCOUNT
};

enum{
	LOG_null=0,
	LOG_pusherCounter,
	LOG_dateTime,
	LOG____TOTAL_MAX
};

extern wchar_t stateMsgString[tcpSocket____MAXCOUNT][32];
extern wchar_t socktypeMsgString[isock____MAX][16];
extern wchar_t sockModeMsgString[tcpPort____MAX][16];

#endif