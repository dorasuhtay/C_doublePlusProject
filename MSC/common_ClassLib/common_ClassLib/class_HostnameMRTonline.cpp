#include "StdAfx.h"
#include <tchar.h>
#include <string.h>
#include "class_HostnameMRTonline.h"
#ifdef _MSC_VER
    #include "stringconversion.h"
#endif

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#ifdef _MSC_VER
    #define returnTag(a, b)                                             \
        {                                                               \
        	if ((a<0)||(a>=count))                         \
                return NULLValue;                                       \
            return gcnew String(reinterpret_cast<const wchar_t*>(b));   \
        }

        #define SetSTRGValue(a, b, c, d, e)       \
        {                                   \
            if ((a<0)||(a>=count))          \
                return;                     \
			if (!b) return;			\
            String2CharArray(d, c);    \
            if (e)                          \
                writeDat();                     \
        }

		#define returnYNValue(a,b)	{if (b)	return "Y"; else return ""; }
	//#define Label_Yes		"Y"
	//#define Label_No		"N"
#else
    #define returnTag(a, b)                 \
        {                                   \
        	if ((a<0)||(a>=count))  \
                return NULLValue;           \
            return (b);                     \
        }

    #define SetSTRGValue(a, b, c, d, e)       \
    {                                   \
        if ((a<0)||(a>=count))          \
            return;                     \
		if (!b) return;			\
        _tcscpy(c, d);                  \
        if (e)                          \
            writeDat();                     \
    }

	#define returnYNValue(a,b) {  if (b) return L"Y"; else return L""; }
	//#define Label_Yes		L"Y"
	//#define Label_No		L"N"
#endif
/*
#define returnTAGValue(a,b) \
    {                                   \
	if ((a<0)||(a>=count))      \
		return 0;                       \
	return b;     \
    }
*/
#define returnTAGValue(a,b,c) \
    {							\
		if (!b)					\
			return 0;                       \
		if ((a<0)||(a>=count))      \
			return 0;                       \
		return c;     \
    }

/*
#define SetTAG(a, b, c, d)      \
{                               \
	if ((a<0)||(a>=count))      \
		return;                 \
	b = c;                      \
	if (d)                      \
		writeDat();             \
}
*/
#define SetTAG(a, b, c, d, e)   \
{                               \
	if (b)						\
	{							\
		if ((a>=0)&&(a<count))  \
		{				        \
			c = d;              \
			if (e)              \
				writeDat();     \
		}						\
	}							\
}

#define IncrementTAG(a, b, d)      \
{                               \
	if ((a<0)||(a>=count))      \
		return;                 \
	b++;                      \
	if (d)                      \
		writeDat();             \
}

void class_HostnameMRTonline::Add(const wchar_t *name, const wchar_t *ipaddr, const wchar_t *dbname, const wchar_t *loginname, const wchar_t *loginpassword, const wchar_t *remarks, const wchar_t *prodline)
{
	if (count>=MAX_HOSTNAME_MRTONLINE) return;

	Hostname[count] = new HostnameMRTonlineType;
	memset(Hostname[count], 0x0, sizeof(HostnameMRTonlineType));
	TCSNCPY(Hostname[count]->Name, name, MAX_hostname_STRING_SIZE-1);					Hostname[count]->Name[MAX_hostname_STRING_SIZE-1] = 0x0;
	TCSNCPY(Hostname[count]->Ipaddress, ipaddr, MAX_hostname_STRING_SIZE-1);			Hostname[count]->Ipaddress[MAX_hostname_STRING_SIZE-1] = 0x0;
	TCSNCPY(Hostname[count]->dbname, dbname, MAX_hostname_STRING_SIZE-1);				Hostname[count]->dbname[MAX_hostname_STRING_SIZE-1] = 0x0;
	TCSNCPY(Hostname[count]->loginname, loginname, MAX_hostname_STRING_SIZE-1);			Hostname[count]->loginname[MAX_hostname_STRING_SIZE-1] = 0x0;
	TCSNCPY(Hostname[count]->loginpassword, loginpassword, MAX_hostname_STRING_SIZE-1);	Hostname[count]->loginpassword[MAX_hostname_STRING_SIZE-1] = 0x0;
	TCSNCPY(Hostname[count]->remarks, remarks, MAX_hostname_STRING_SIZE-1);				Hostname[count]->remarks[MAX_hostname_STRING_SIZE-1] = 0x0;
	TCSNCPY(Hostname[count]->Prodline, prodline, 7);									Hostname[count]->Prodline[7] = 0x0;

	//create a mailbox
	mailbox[count] = new wctStringFifo();

	count++;
}



STRINGPTR class_HostnameMRTonline::getName(int index)				{    returnTag(index, Hostname[index]->Name);}
STRINGPTR class_HostnameMRTonline::getIpaddress(int index)			{    returnTag(index, Hostname[index]->Ipaddress);}
STRINGPTR class_HostnameMRTonline::getdbname(int index)				{    returnTag(index, Hostname[index]->dbname);}
STRINGPTR class_HostnameMRTonline::getloginname(int index)			{    returnTag(index, Hostname[index]->loginname);}
STRINGPTR class_HostnameMRTonline::getloginpassword(int index)		{    returnTag(index, Hostname[index]->loginpassword);}
STRINGPTR class_HostnameMRTonline::getremarks(int index)			{    returnTag(index, Hostname[index]->remarks);}
STRINGPTR class_HostnameMRTonline::getconnectionstatus(int index)	{    returnTag(index, Hostname[index]->connectionstatus);}
STRINGPTR class_HostnameMRTonline::getProdline_s(int index)			{    returnTag(index, Hostname[index]->Prodline);}

STRINGPTR class_HostnameMRTonline::getSQLServerstatus(int index)	{    returnTag(index, Hostname[index]->SQLServerstatus);}
STRINGPTR class_HostnameMRTonline::getPingStatus(int index)			{    returnTag(index, Hostname[index]->pingstatus);}


void class_HostnameMRTonline::setconnectionstatus(int index, STRINGPTR name, bool flush)	{SetSTRGValue(index, Hostname[index], Hostname[index]->connectionstatus, name, flush);}
void class_HostnameMRTonline::setSQLServerstatus(int index, STRINGPTR name, bool flush)		{SetSTRGValue(index, Hostname[index], Hostname[index]->SQLServerstatus, name, flush);}
void class_HostnameMRTonline::setPingStatus(int index, STRINGPTR name, bool flush)			{SetSTRGValue(index, Hostname[index], Hostname[index]->pingstatus, name, flush);}



//void class_HostnameMRTonline::setconnectionstatus(int index, STRINGPTR name, bool flush){if (Hostname[index])	SetSTRGValue(index, Hostname[index]->connectionstatus, name, flush);}

void class_HostnameMRTonline::setlineserverPortnumber(int index, int portnumber, bool flush)
{
	if ((index<0)||(index>=count)) return;
	if (!Hostname[index]) return;
	Hostname[index]->lineserverPortnumber = portnumber;
}

int class_HostnameMRTonline::getlineserverPortnumber(int index)
{
	if ((index<0)||(index>=count)) return 0;
	if (!Hostname[index]) return 0;
	return Hostname[index]->lineserverPortnumber;
}

int class_HostnameMRTonline::getProdline(int index)
{
	if ((index<0)||(index>=count)) return -1;
	if (!Hostname[index]) return -1;
	return _ttoi(Hostname[index]->Prodline);
}



HostnameMRTonlineType *class_HostnameMRTonline::get(int index)			
{    
	if ((index<0)||(index>=count)) return 0;
	return Hostname[index];
}

void class_HostnameMRTonline::setIPaddress(const wchar_t *ipa) {TCSNCPY(my_ipaddress, ipa, 63);my_ipaddress[63]=0x0;}

class_HostnameMRTonline::class_HostnameMRTonline()
{
	int ii;
	for (ii=0;ii<MAX_HOSTNAME_MRTONLINE;ii++)
	{
		Hostname[ii] = 0;
		mailbox[ii] = 0;
	}
	count = 0;
	SQLdb_index = 0;
	Ping_index = 0;
	TCSCPY(my_name, L"");
	TCSCPY(my_ipaddress, L"");
}
 

 
int class_HostnameMRTonline::findIpAddress(const char *ipaddress)
{
	unsigned int ii;
	wchar_t ipaddr[64];
	for (ii=0;ii<strlen(ipaddress);ii++)
		ipaddr[ii] = ipaddress[ii];
	ipaddr[ii] = 0x0;
	for (int ii=0;ii<count;ii++)
	{
		if (!Hostname[ii]) continue;
		if(_tcscmp(Hostname[ii]->Ipaddress, ipaddr)==0)
			return ii;
	}
	return -1;
}


class_HostnameMRTonline::~class_HostnameMRTonline()
{
	Clear();
	/*
	int ii;
	for (ii=0;ii<MAX_HOSTNAME_MRTONLINE;ii++)
	{
		SAFE_DELETE(Hostname[ii]);
	}*/
}

void class_HostnameMRTonline::Clear()
{
	int ii;
	for (ii=0;ii<MAX_HOSTNAME_MRTONLINE;ii++)
	{
		SAFE_DELETE(Hostname[ii]);
		SAFE_DELETE(mailbox[ii]);
	}
	count = 0;
}

void class_HostnameMRTonline::setMyName(wchar_t *myname)
{
	//int len = _tcslen(myname);
	TCSNCPY(my_name, myname, 63);
	my_name[63] = 0x0;
}

wchar_t *class_HostnameMRTonline::getMyName()
{
	return my_name;
}

bool class_HostnameMRTonline::isMyName(int index)
{
	if (index<0) return 0;
	if (index>=count) return 0;
	return (_tcscmp(Hostname[index]->Name, my_name)==0);
	/*
	if(_tcscmp(Hostname[index]->Name, my_name)==0)
		return 1;
	else
		return 0;*/
}

bool class_HostnameMRTonline::isName(int index, wchar_t *name)
{
	if (index<0) return 0;
	if (index>=count) return 0;
	return (_tcscmp(Hostname[index]->Name, name)==0);
	/*
	if(_tcscmp(Hostname[index]->Name, name)==0)
		return 1;
	else
		return 0;
		*/
}

bool class_HostnameMRTonline::isPingOK(int index){			returnTAGValue(index, Hostname[index], Hostname[index]->pingOK);}
bool class_HostnameMRTonline::isSQLonline(int index){		returnTAGValue(index, Hostname[index], Hostname[index]->SQLonline);}
bool class_HostnameMRTonline::isServeronline(int index){    returnTAGValue(index, Hostname[index], Hostname[index]->Serveronline);}

void class_HostnameMRTonline::setPingOK(int index, bool state, bool flush){			SetTAG(index, Hostname[index], Hostname[index]->pingOK, state, flush);}
void class_HostnameMRTonline::setSQLonline(int index, bool state, bool flush){		SetTAG(index, Hostname[index], Hostname[index]->SQLonline, state, flush);}
void class_HostnameMRTonline::setServeronline(int index, bool state, bool flush){	SetTAG(index, Hostname[index], Hostname[index]->Serveronline, state, flush);}





void class_HostnameMRTonline::readDat()
{
	/*
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&StationOpFileHeader, sizeof(StationOpFileHeaderType), 1, fp);
		count = StationOpFileHeader.reccount;
		for (int ii=0;ii<StationOpFileHeader.reccount;ii++)
		{
			fread(&StationOp[ii], sizeof(StationOpType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
	*/
}

void class_HostnameMRTonline::writeDat()
{
	/*
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
		StationOpFileHeader.reccount = count;
		fwrite(&StationOpFileHeader, sizeof(StationOpFileHeaderType), 1, fp);
		for (int ii=0;ii<StationOpFileHeader.reccount;ii++)
		{
			fwrite(&StationOp[ii], sizeof(StationOpType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
	*/
}

