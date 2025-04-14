#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include "pusherCounterClass.h"

//int nPusherCount = 0;
//int pusherlink = 0;
//int tempCount = 0;
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#define cfile_Name		"PUSHERCOUNTTRACK.DAT\0\0"

//const char *pusherCounterClass::getfile_Name(){return file_PUSHERCOUNTTRACK;}
const wchar_t *pusherCounterClass::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
const char    *pusherCounterClass::cgetfile_Name(){if (filepathname) return (char *)filepathname->cdata(); else return cfile_Name;}
pusherCounterClass::pusherCounterClass(const wchar_t *path, int pusher_interval_millisec)
{
	sync = 0;
	sync_max = 0;
	pCount = 0;
	pLink = 0;
	storeLock = 0;
//	counter120ms = 1;
	enable = 0;
	flagged = 0;
	ExceedError=0;
	hardwareSignalAvail = 0;
	linkInterval = pusher_interval_millisec;
	

	filepath  = new wctString(path);
	filepathname  = new wctString(path);
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));

	resetLink();
}

pusherCounterClass::~pusherCounterClass()
{
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

/*
void pusherCounterClass::resetPusherCounter()
{
    pLink = 0;
    pCount = 0;
	sync_max = 0;
	sync = 0;
	linkInterval = 120;
	internal_pLink = 0;

//    counter120ms = 1;
}
*/
void pusherCounterClass::read_Dat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&pushercountDAT, sizeof(pushercountDAT), 1, fp);
		pCount = pushercountDAT.pushercount;
		pLink = pushercountDAT.pusherlink;
		sync = pushercountDAT.sync;
		sync_max = pushercountDAT.sync_max;

		fclose(fp);
	}
	storeLock = 0;
	//nPusherCount=pCount;pusherlink = pLink;	//not needed
}

void pusherCounterClass::writeDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	pushercountDAT.pushercount = pCount;
	pushercountDAT.pusherlink = pLink;
	pushercountDAT.sync = sync;
	pushercountDAT.sync_max = sync_max;

	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
		fwrite(&pushercountDAT, sizeof(pushercountDAT), 1, fp);
		fclose(fp);
	}
	storeLock = 0;
}

/*
void pusherCounterClass::pLink__wrap_around()
{
	if ((pLink>(numberof_CHAIN_LINKS-1))||(pLink<0))
		pLink = 0;
	//pusherlink = pLink;		//not needed
}
*/
/*
bool pusherCounterClass::isPusher_LinkError()
{
	return (pLink>=(numberof_CHAIN_LINKS+3));
}
*/
void pusherCounterClass::updateStop_compensationLink()
{

	pLink += numberof_CHAIN_LINKS_STOP_compensation;

	if(pLink > (numberof_CHAIN_LINKS-1) ){
		pLink = (pLink - (numberof_CHAIN_LINKS-1));
		pCount += 1;
		//if((nPusherCount >= maxPusherCount) && (pusherlink >= (Numberof_CHAIN_LINKS-1)))
		if((pCount >= (max_Number_of_PUSHER-1)) && (pLink >= (numberof_CHAIN_LINKS-1)))

		{
			pLink = 0;
			pCount = 0;
		}
	}
	writeDat();
	//nPusherCount=pCount;pusherlink = pLink;	//not needed
}

/*
int pusherCounterClass::incrementPusherCount(int offset)
{
	return (pCount+offset)%max_Number_of_PUSHER;
}
*/
void pusherCounterClass::incrementPusherCount()
{

	pCount = (pCount+1)%max_Number_of_PUSHER;
	writeDat();
	//nPusherCount=pCount;	//not needed
}
/*
void pusherCounterClass::updatePusherCount()
{
	if (getpusher_flag())
	{
		incrementPusherCount();
		resetLink();
		setpusher_flag(false);
		//nPusherCount=pCount;pusherlink = pLink;	//not needed
	}
}
*/
/*
void pusherCounterClass::decrementPusherCounter()
{
	pCount = (pCount-1)%max_Number_of_PUSHER;
	writeDat();
	//nPusherCount=pCount;	//not needed
}*/

void pusherCounterClass::receivedPusherMsg()
{
	//setpusher_flag(true);
	flag_thread=false;
	incrementPusherCount();
	resetLink();
	writeDat();
}

