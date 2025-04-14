//#include "StdAfx.h"
//

#include "StdAfx.h"
#include <string.h>
#include <tchar.h>
#include "wctStringFifo.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

wctStringFifo::wctStringFifo()
{
	int ii;
	for (ii=0;ii<MAX_WCTSTRINGFIFO_SIZE;ii++)
	{
		wctStr[ii] = 0x0;;
	}
	count = 0;
	headptr = 0;
	tailptr = 0;
	overrunCount = 0;
}

wctStringFifo::~wctStringFifo()
{
	int ii;
	for (ii=0;ii<MAX_WCTSTRINGFIFO_SIZE;ii++)
	{
		SAFE_DELETE(wctStr[ii]);
	}
}

void wctStringFifo::Clear()
{
	tailptr=headptr=0;
}

void wctStringFifo::put(const wchar_t *data)
{
	if (wctStr[headptr])
	{
		wctStr[headptr]->clear();
		wctStr[headptr]->append(data);
		//memcpy(wctStr[headptr]->buf, data, sizeof(wctStr[headptr]->buf));
		headptr = (headptr + 1) % count;
		if (headptr==tailptr)
			overrunCount++;
	}
}

void wctStringFifo::put(const char *data)
{
	if (wctStr[headptr])
	{
		wctStr[headptr]->clear();
		wctString str;
		str = data;
		wctStr[headptr]->append(str);
		//memcpy(wctStr[headptr]->buf, data, sizeof(wctStr[headptr]->buf));
		headptr = (headptr + 1) % count;
		if (headptr==tailptr)
			overrunCount++;
	}
}

int wctStringFifo::get(wchar_t *data)
{
	if (wctStr[tailptr]&&data)
	{
		_tcscpy(data, wctStr[tailptr]->wdata());
		//_tcscpy(data, wctStr[tailptr]->data(), wctStr[tailptr]->Length());
		tailptr = (tailptr + 1) % count;
		return 1;
	}
	return 0;
}


wctString *wctStringFifo::get()
{
	int ptr;
	if (wctStr[tailptr])
	{
		ptr = tailptr;
		tailptr = (tailptr + 1) % count;
		return wctStr[ptr];
	}
	return 0;
}

long wctStringFifo::used()
{
	long count = 0L;
	//WaitForLock(&cbuf);

	if ((tailptr>=0)&&(headptr>=0)&&(headptr!=tailptr)) {
		if (headptr>tailptr)
   		count = headptr-tailptr;
	   else
   		{
			if (headptr<tailptr)
   			count = (count-tailptr)+headptr;
	      }
      }

  	//ReleasecbufLock;
	return count;
}

bool wctStringFifo::available()
{
	return (tailptr!=headptr);
}

/*
int wctStringFifo::getLength()
{
	if (wctStr[tailptr])
		return wctStr[tailptr]->Length();
	else
		return 0;
}*/

void wctStringFifo::create(int size)
{
	int ii;
	if (size<0) return;
	if (size>=MAX_WCTSTRINGFIFO_SIZE) size = MAX_WCTSTRINGFIFO_SIZE-1;
	for (ii = 0;ii<size;ii++)
	{
		wctStr[ii] = new wctString();
		count++;
	}
}
