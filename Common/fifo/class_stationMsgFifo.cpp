#include "StdAfx.h"
#include <string.h>
#include <windows.h>
#include "class_stationMsgFifo.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#define SETBUFFERLOCK			{while(Lock) Sleep(10);Lock = 1;/*orginal Sleep(10)*/}
#define RELEASEBUFFERLOCK		{Lock = 0;}

class_stationMsgFifo::class_stationMsgFifo()
{
	int ii;
	for (ii=0;ii<MAX_MsgBuffer_SIZE;ii++)
		msgbuf[ii] = 0x0;;
	count = 0;
	headptr = 0;
	tailptr = 0;
	overrunCount = 0;
	Lock = 0;
	checksumerror = 0;
	maxUsage = 0;
	totalusage = 0;
	memset(&statistics, 0x0, sizeof(serialfifoStatisticsType));
}



class_stationMsgFifo::~class_stationMsgFifo()
{
	int ii;
	for (ii=0;ii<MAX_MsgBuffer_SIZE;ii++)
		SAFE_DELETE(msgbuf[ii]);
}



int class_stationMsgFifo::put(const unsigned char *data)
{
	int nn = 0;
	SETBUFFERLOCK;

	if (msgbuf[headptr])
	{
		memcpy(msgbuf[headptr]->buf, data, sizeof(msgbuf[headptr]->buf));
		headptr = (headptr + 1) % count;
		if (headptr==tailptr)
			overrunCount++;
		nn = sizeof(msgbuf[headptr]->buf);
		totalusage++;
	}

	RELEASEBUFFERLOCK;	
	updateStatistics();
	return nn;
}

int class_stationMsgFifo::get(unsigned char *data)
{
	SETBUFFERLOCK;

	int nn = 0;
	if (msgbuf[tailptr])
	{
		memcpy(data, msgbuf[tailptr]->buf, sizeof(msgbuf[tailptr]->buf));
		tailptr = (tailptr + 1) % count;
		nn = 1;
	}

	RELEASEBUFFERLOCK;	
	updateStatistics();
	return nn;
}

bool class_stationMsgFifo::available()
{
	return (tailptr!=headptr);
}



long class_stationMsgFifo::used()
{
	SETBUFFERLOCK;

	long use = 0L;
	if ((tailptr>=0)&&(headptr>=0)&&(headptr!=tailptr)) {
		if (headptr>tailptr)
   		use = headptr-tailptr;
	   else
   		{
			if (headptr<tailptr)
   			use = (count-tailptr)+headptr;
	      }
      }
	if (use>maxUsage)
		maxUsage = use;

  	RELEASEBUFFERLOCK;

	return use;
}

void class_stationMsgFifo::create(int size)
{
	int ii;
	if (size<0) return;
	if (size>MAX_MsgBuffer_SIZE) size = MAX_MsgBuffer_SIZE;
	for (ii = 0;ii<size;ii++)
	{
		msgbuf[ii] = new MsgBuffer;
		memset(msgbuf[ii], 0x0, sizeof(MsgBuffer));
		count++;
	}
	updateStatistics();
}

void class_stationMsgFifo::updateStatistics()
{
	statistics.usage = used();
	statistics.usage_Max = maxUsage;
	statistics.BufferSize = count;
	statistics.chksumCount = checksumerror;
	statistics.overrunCount = overrunCount;
	statistics.totalusageCount = totalusage;
}

void class_stationMsgFifo::getserialfifoStatistics(serialfifoStatisticsType *stat)
{
	memcpy(stat, &statistics, sizeof(serialfifoStatisticsType));
}