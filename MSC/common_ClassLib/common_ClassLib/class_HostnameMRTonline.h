#ifndef ___class_HostnameMRTonline__H
#define ___class_HostnameMRTonline__H

#include "xplatform_define.h"
#include "wctStringFifo.h"

#define MAX_hostname_STRING_SIZE	64

typedef struct {
	wchar_t Name[MAX_hostname_STRING_SIZE];
	wchar_t Ipaddress[MAX_hostname_STRING_SIZE];
	wchar_t dbname[MAX_hostname_STRING_SIZE];
	wchar_t loginname[MAX_hostname_STRING_SIZE];
	wchar_t loginpassword[MAX_hostname_STRING_SIZE];
	wchar_t remarks[MAX_hostname_STRING_SIZE];
	wchar_t Prodline[8];
	wchar_t connectionstatus[MAX_hostname_STRING_SIZE];


	wchar_t SQLServerstatus[MAX_hostname_STRING_SIZE];
	wchar_t pingstatus[MAX_hostname_STRING_SIZE];
	

	bool	ServerEnablePoll; 
	bool	DatabaseEnablePoll;

	bool	Serveronline;
	bool	SQLonline;
	bool	pingOK;

	int		lineserverPortnumber;
}HostnameMRTonlineType;

typedef struct {
	wchar_t Name[MAX_hostname_STRING_SIZE];
	wchar_t Ipaddress[MAX_hostname_STRING_SIZE];
	wchar_t dbname[MAX_hostname_STRING_SIZE];
	wchar_t loginname[MAX_hostname_STRING_SIZE];
	wchar_t loginpassword[MAX_hostname_STRING_SIZE];
	wchar_t remarks[MAX_hostname_STRING_SIZE];
	wchar_t Prodline[8];
	wchar_t spare01[MAX_hostname_STRING_SIZE];
	wchar_t spare02[MAX_hostname_STRING_SIZE];
	wchar_t spare03[MAX_hostname_STRING_SIZE];
}HostnameMRTonlineFileType;

#define MAX_HOSTNAME_MRTONLINE		512

class class_HostnameMRTonline{
	int count;
	wchar_t my_name[64];
	wchar_t my_ipaddress[64];
	HostnameMRTonlineType *Hostname[MAX_HOSTNAME_MRTONLINE];
	wctStringFifo *mailbox[MAX_HOSTNAME_MRTONLINE];
	int SQLdb_index;
	int Ping_index;
public:
	class_HostnameMRTonline();
	~class_HostnameMRTonline();
	void setIPaddress(const wchar_t *ipa);
	const wchar_t *getIPaddress() {return my_ipaddress;}
	int getcount() {return count;}
	void Add(const wchar_t *name, const wchar_t *ipaddr, const wchar_t *dbname, const wchar_t *loginname, const wchar_t *loginpassword, const wchar_t *remarks, const wchar_t *prodline); 
	void Clear();
	HostnameMRTonlineType *get(int index);
	STRINGPTR getName(int index);
	STRINGPTR getIpaddress(int index);
	STRINGPTR getdbname(int index);
	STRINGPTR getloginname(int index);
	STRINGPTR getloginpassword(int index);
	STRINGPTR getremarks(int index);
	STRINGPTR getProdline_s(int index);
	int getProdline(int index);
	STRINGPTR getconnectionstatus(int index);
	STRINGPTR getSQLServerstatus(int index);
	STRINGPTR getPingStatus(int index);
	
	void setconnectionstatus(int index, STRINGPTR name, bool flush=1);
	void setSQLServerstatus(int index, STRINGPTR name, bool flush=1);
	void setPingStatus(int index, STRINGPTR name, bool flush=1);
	

	void setlineserverPortnumber(int index, int portnumber, bool flush=1);
	int getlineserverPortnumber(int index);

	int mailAvailable(int index)
	{
		if((index<0)||(index>=count)) return -1;
		if(!mailbox[index]) return -1;
		return mailbox[index]->used();
	}

	void addMail(int index, const wchar_t *data)
	{
		if((index<0)||(index>=count)) return;
		if(!mailbox[index]) return;
		mailbox[index]->put(data);
	}

	void addMail(int index, const char *data)
	{
		if((index<0)||(index>=count)) return;
		if(!mailbox[index]) return;
		mailbox[index]->put(data);
	}

	int getMail(int index, wchar_t *data)
	{
		if((index<0)||(index>=count)) return 0;
		if(!mailbox[index]) return 0;
		return mailbox[index]->get(data);
	}
	
	
	bool isPingOK(int index);
	void setPingOK(int index, bool state, bool flush=1);
	bool isServeronline(int index);
	void setServeronline(int index, bool state, bool flush=1);
	bool isSQLonline(int index);
	void setSQLonline(int index, bool state, bool flush=1);
	bool isonline(int index) {return (isSQLonline(index)&&isServeronline(index)&&isPingOK(index));}
	void incrementSQLdb_index() 
	{
		SQLdb_index++;
		SQLdb_index = SQLdb_index % count;
	}
	void incrementPing_index() 
	{
		Ping_index++;
		Ping_index = SQLdb_index % count;
	}
	void clearPing_index() {Ping_index=0;}
	int getPing_index() {return Ping_index;}
	
	
	void clearSQLdb_index() {SQLdb_index=0;}
	int getSQLdb_index() {return SQLdb_index;}

	int findIpAddress(const char *ipaddress);
	void setMyName(wchar_t *myname);
	wchar_t *getMyName();
	bool isMyName(int index);
	bool isName(int index, wchar_t *name);
	void writeDat();
	void readDat();


};

#endif




