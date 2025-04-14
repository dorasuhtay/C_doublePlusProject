#include "stdafx.h"
#include <stdlib.h>
#ifdef __BCPLUSPLUS__
	#include <mem.h>
#endif

//#include "stdafx.h"
#include "lcircbuf.h"
#include <windows.h>
#include <stdlib.h>
#define ReleasecbufLock		cbuf.Lock = 0
//#define ReleasecbufLock(a)		a->Lock = 0

void WaitForLock(LCircBuffer *pBuf)
{
	if (!pBuf) return;
	while(pBuf->Lock)
		Sleep(10);
	pBuf->Lock = 1;
}


LCircularBuf::LCircularBuf()
{
	TotalChars = 0;
	age = 0;
  	ReleasecbufLock;
	databuf = NULL;
	#if defined(BI_PLAT_WIN32)
   hdatabuf = NULL;
   #endif
	memset(&cbuf, 0x0, sizeof(LCircBuffer));
//	Enable();
}

LCircularBuf::~LCircularBuf()
{
	WaitForLock(&cbuf);		//ensure nobody is using the circ buffer before we destroy it;
  	ReleasecbufLock;
	DestroyStorageBuffer();
}


void LCircularBuf::DestroyStorageBuffer()
{
   if (databuf)
		free(databuf);
   databuf = 0;

/*
	#if defined(BI_PLAT_WIN32)
   if (hdatabuf&&databuf){
		GlobalUnlock(hdatabuf);
		GlobalFree(hdatabuf);
		hdatabuf = NULL;
		databuf = NULL;
      }
	#else
	Avoid using this
	#ifdef _USE_MALLOC
	if (databuf){
		free(databuf);
      databuf = NULL;
      }
	#else
	if (databuf){
		delete databuf;
  		databuf = NULL;
      }
	#endif
	#endif
   return 0;
*/
}

void LCircularBuf::Clear()
{
   Reset();
   circbufReset(&cbuf);
}


void LCircularBuf::Reset()
{
   prevSerialPtr = 0;
   outSerialPtr = 0;
   //Lock = 0;
}

long LCircularBuf::bSize()
{
   return cbuf.Length;
}


/*
void LCircularBuf::WaitForLock()
{
	::WaitForLock(&cbuf);
	while(cbuf.Lock)
		Sleep(10);
	cbuf.Lock = 1;
}
*/
int LCircularBuf::PutBackSerialChar()
{
	if (cbuf.Where==NULL)
		return -1;
	WaitForLock(&cbuf);
//	while(Lock)
//	  Sleep(50);
//	Lock = 1;
	cbuf.QEnd = prevSerialPtr;
	cbuf.Lock = 0;
	return 0;
}

int LCircularBuf::RemoveSerialChar(long nCount)
{
	if (cbuf.Where==NULL)
		return -1;
	WaitForLock(&cbuf);
//	while(Lock)
//		Sleep(50);
//	Lock = 1;
	for (;nCount;nCount--)
		cbuf.QEnd = (cbuf.QEnd+1) % cbuf.Length;	//wrap around
	ReleasecbufLock;
	return 0;
}

//if succesful then return 0 otherwise return -1;
int LCircularBuf::Init(long nsize)
{
	DestroyStorageBuffer();
	databuf = (unsigned char *)malloc(nsize*sizeof(unsigned char));
   if (!databuf)
   	return -1;
	circbufInit(&cbuf, databuf, nsize);
	Reset();
   return 0;
/*
	#if defined(BI_PLAT_WIN32)
	hdatabuf = GlobalAlloc(GPTR,(DWORD)(nsize+1));
	if (hdatabuf==NULL)
   	return -1;
	databuf = (unsigned char *)GlobalLock(hdatabuf);
	if (databuf==NULL){
		GlobalFree(hdatabuf);
		hdatabuf = NULL;
   	return -1;
      }
	circbufInit(&cbuf, databuf, nsize);
	Reset();
   return 0;
	#else
	Avoid using this
	#ifdef _USE_MALLOC
	if ((databuf = (unsigned char *) malloc(nsize)) != NULL){
		circbufInit(&cbuf, databuf, nsize);
      Reset();
      return 0;
      }
   else
   	return -1;
	#else
	databuf = new unsigned char [nsize];
   if (databuf){
		circbufInit(&cbuf, databuf, nsize);
		Reset();
		return 0;
      }
   else
   	return -1;
	#endif
   #endif
*/
}




int LCircularBuf::Add(const unsigned char *lpChar, long CharNum)
{
	if (cbuf.Where==NULL)
		return -1;

	WaitForLock(&cbuf);

   if (cbuf.QEnd<0){
   	ReleasecbufLock;
      return -1;
      }
   if (cbuf.QHead<0){
   	ReleasecbufLock;
      return -1;
      }

	for (long ii=0;ii<CharNum;ii++) {
		cbuf.Where[cbuf.QHead] = *lpChar++;
		cbuf.QHead = (cbuf.QHead+1) % cbuf.Length;	//Increment wrap around
      cbuf.Used++;
      if (cbuf.Used>cbuf.Length) cbuf.Used = cbuf.Length;
		}
	TotalChars += CharNum;
  	ReleasecbufLock;
   return 0;
}

int LCircularBuf::Add(unsigned char ch)
{
	if (cbuf.Where==NULL)
		return -1;

	WaitForLock(&cbuf);

   if (cbuf.QEnd<0){
   	ReleasecbufLock;
      return -1;
      }
   if (cbuf.QHead<0){
   	ReleasecbufLock;
      return -1;
      }

	cbuf.Where[cbuf.QHead] = ch;
	cbuf.QHead = (cbuf.QHead+1) % cbuf.Length;	//Increment wrap around
	cbuf.Used++;
	if (cbuf.Used>cbuf.Length) cbuf.Used = cbuf.Length;
	TotalChars ++;
  	ReleasecbufLock;
   return 0;
}

int LCircularBuf::ReadCh()
{
	unsigned char ch;
	if (cbuf.Where==NULL)
		return -1;

	WaitForLock(&cbuf);
//	while(Lock)
//	  Sleep(50);
//	Lock = 1;

   if (cbuf.QEnd<0){
   	ReleasecbufLock;
      return -1;
      }
   if (cbuf.QHead<0){
   	ReleasecbufLock;
      return -1;
      }

//	long ii;
   if (cbuf.QEnd==cbuf.QHead){
   	ReleasecbufLock;
		return -1;
   	}
	prevSerialPtr = cbuf.QEnd;
	ch = cbuf.Where[cbuf.QEnd];
	cbuf.QEnd = (cbuf.QEnd+1) % cbuf.Length;	//Increment wrap around
	cbuf.Used--;
   if (cbuf.Used<-10) cbuf.Used = -10;
  	ReleasecbufLock;
	return (int)(ch&0xFF);
}


void LCircularBuf::OffsetTail(long offset)
{
	if (offset==0) return;
	if (cbuf.Where==NULL)
		return ;

	WaitForLock(&cbuf);
//	while(Lock)
//	  Sleep(50);
//	Lock = 1;

   if (cbuf.QEnd<0){
   	ReleasecbufLock;
      return;
      }
   if (cbuf.QHead<0){
   	ReleasecbufLock;
      return;
      }

   if (offset<0){
		cbuf.QEnd = cbuf.QEnd + offset;
      if (cbuf.QEnd<0)
      	cbuf.QEnd = cbuf.Length + cbuf.QEnd;
   	}

   if (cbuf.QEnd<0)
      cbuf.QEnd = 0;

  	ReleasecbufLock;
}

long LCircularBuf::_Read(unsigned char *buf, long nCount)
{
	long ii;
	prevSerialPtr = cbuf.QEnd;
	for (ii=0;ii<nCount;ii++){
		buf[ii] = cbuf.Where[cbuf.QEnd];
		cbuf.QEnd = (cbuf.QEnd+1) % cbuf.Length;	//Increment wrap around
		cbuf.Used--;
      if (cbuf.Used<-10) cbuf.Used = -10;
		if (cbuf.QEnd==cbuf.QHead){					//reach the last char available
			ii++;											//number of char read would be one plus
			break;
			}
		}
	return ii;
}


//formerly known as int TCommView::xReadSerialComm(unsigned char *buf, int nCount)
//------------------------------------------------------------
//Read nCount or whatever available in the Ring Buffer
//Return the number of chars available in the Ring Buffer
//------------------------------------------------------------
long LCircularBuf::Read(unsigned char *buf, long nCount)
{
	if (cbuf.Where==NULL)
		return -1;

	WaitForLock(&cbuf);

   if (cbuf.QEnd<0){
   	ReleasecbufLock;
      return -2;
      }
   if (cbuf.QHead<0){
   	ReleasecbufLock;
      return -2;
      }

	long ii;
   if (cbuf.QEnd==cbuf.QHead){
   	ReleasecbufLock;
		return 0;
   	}
	ii = _Read(buf, nCount);
/*
	prevSerialPtr = cbuf.QEnd;
	for (ii=0;ii<nCount;ii++)
	{
		buf[ii] = cbuf.Where[cbuf.QEnd];
		cbuf.QEnd = (cbuf.QEnd+1) % cbuf.Length;	//Increment wrap around
		cbuf.Used--;
      if (cbuf.Used<-10) cbuf.Used = -10;
		if (cbuf.QEnd==cbuf.QHead)					//reach the last char available
		{
			ii++;											//number of char read would be one plus
			break;
		}
	}
*/
  	ReleasecbufLock;
	return ii;
}

int LCircularBuf::bytesAvail()
{
	int nn;
	WaitForLock(&cbuf);
//	while(Lock)
//		Sleep(50);
//	Lock = 1;

   if (cbuf.QEnd<0){
   	ReleasecbufLock;
      return 0;
      }
   if (cbuf.QHead<0){
   	ReleasecbufLock;
      return 0;
      }

	nn = (cbuf.QHead!=cbuf.QEnd);
  	ReleasecbufLock;
	return nn;
}

void LCircularBuf::Backspace()
{
	WaitForLock(&cbuf);

	if (cbuf.QHead!=cbuf.QEnd){
		if (cbuf.QHead==0)
			cbuf.QHead = cbuf.Length-1;
		else
			cbuf.QHead--;
      }

  	ReleasecbufLock;
}


long LCircularBuf::used()
{
	long count = 0L;
	WaitForLock(&cbuf);

	if ((cbuf.QEnd>=0)&&(cbuf.QHead>=0)&&(cbuf.QHead!=cbuf.QEnd)) {
		if (cbuf.QHead>cbuf.QEnd)
   		count = cbuf.QHead-cbuf.QEnd;
	   else
   		{
			if (cbuf.QHead<cbuf.QEnd)
   			count = (cbuf.Length-cbuf.QEnd)+cbuf.QHead;
	      }
      }

  	ReleasecbufLock;
	return count;
}



long LCircularBuf::samplesavailable()
{
	WaitForLock(&cbuf);
//	while(Lock)
//		Sleep(50);
//	Lock = 1;

   if (cbuf.QEnd<0){
   	ReleasecbufLock;
      return 0;
      }
   if (cbuf.QHead<0){
   	ReleasecbufLock;
      return 0;
      }

	int head = cbuf.QHead;
	int end = cbuf.QEnd;
	int count = 0;
	while(head!=end)
	{
		end = (end+1) % cbuf.Length;	//Increment wrap around
		count++;
	}
  	ReleasecbufLock;
	return count;
}

long LCircularBuf::ReadOut(unsigned char *buf, long nCount)
{
	if (cbuf.Where==NULL)
		return -1;

	WaitForLock(&cbuf);
//	while(Lock)
//	  Sleep(50);
//	Lock = 1;


   if (cbuf.QEnd<0){
   	ReleasecbufLock;
      return -2;
      }
   if (cbuf.QHead<0){
   	ReleasecbufLock;
      return -2;
      }

	long ii = 0L;
   while(outSerialPtr!=cbuf.QHead) {
		buf[ii++] = cbuf.Where[outSerialPtr];
		outSerialPtr = (outSerialPtr+1) % cbuf.Length;	//Increment wrap around
		cbuf.Used--;
      if (cbuf.Used<-10) cbuf.Used = -10;
      if (ii>nCount)
      	break;
      }
  	ReleasecbufLock;
   return ii;
}

/*
long LCircularBuf::Used()
{
   return cbuf.Used;
}
*/

double LCircularBuf::circbufPercentUsed()
{
/*
	if (cbuf.Where==NULL)
		return -1;
	double value = ((double)cbuf.Used/(double)cbuf.Length)*(double)100.0;
	return value;
*/
	return circbufPercentUsedAsOf(cbuf.Length);
}

double LCircularBuf::circbufPercentUsedAsOf(long size)
{
	if (cbuf.Where==NULL)
		return -1;
	double value = ((double)cbuf.Used/(double)size)*(double)100.0;
	return value;
}


//---------------------------------------------------------------------
//circbufInit
//SYNTAX:			void circbufInit(LCircBuffer *pBuf, void *Storage,
//										  unsigned size);
//DESCRIPTION:	Initializes a circular buffer structure.  "pBuf" points to
//the circular buffer to initialize, "Storage" points to a location where
//the circular buffer will hold information, and "size" specifies the number
//of bytes allocated at "Storage". Should be contained in critical section
//wrt other access the the same circular buffer. The buffer has nothing in
//the buffer after the call and all "size" many bytes should be free, non
//is used.
//RETURN VALUE:	None.
//---------------------------------------------------------------------
void LCircularBuf::circbufInit(LCircBuffer *pBuf, void *Storage, long size)
{
	pBuf->Where = (unsigned char *)Storage;
	pBuf->Length = size;
	pBuf->Lock = 0;
	circbufReset(pBuf);
}

//---------------------------------------------------------------------
//circbufReset
//SYNTAX:			void circbufReset(LCircBuffer *pBuf);
//DESCRIPTION:	Resets the circular buffer pointed to by "pBuf".
//There should no used bytes, and the free bytes should equal the size of
//the buffer passed in circbufInit. Any call to this function should be
//contained in a critical section wrt other accesses to this buffer.
//RETURN VALUE:	None.
//---------------------------------------------------------------------
void LCircularBuf::circbufReset(LCircBuffer *pBuf) {
	pBuf->QHead = pBuf->QEnd = pBuf->Used = 0;
	pBuf->Free = pBuf->Length;
	pBuf->Lock = 0;
	pBuf->Used = 0;
	}



/* START FUNCTION DESCRIPTION ********************************************
circbufChkTerm               <CIRCBUF.LIB>

SYNTAX:			unsignd circbufChkTerm(
						LCircBuffer *pBuf,
						char TermChar);

DESCRIPTION:	Tries to determine if a terminal-character delimited
package is available in the buffer.  Does not remove any information
from the buffer.  Should call circbufGet[Byte] to remove information.
Call to this function should be
in a critical section w.r.t. the rest of circbuf access to this buffer
except all write functions and scan functions.

RETURN VALUE:	The size of the packet terminating with the specified
character "TermChar" (including the terminator character).

END DESCRIPTION **********************************************************/
long circbufChkTerm(LCircBuffer *pBuf,	char TermChar)
{
	if (!pBuf) return 0;
	if (!pBuf->Where) return 0;
	long size = 0;
	WaitForLock(pBuf);

	int head = pBuf->QHead;
	int end = pBuf->QEnd;
   if (end<0) {
	  	pBuf->Lock = 0;
   	return 0;
      }
   if (head<0){
	  	pBuf->Lock = 0;
   	return 0;
      }
	if (head==end){
	  	pBuf->Lock = 0;
   	return 0;
      }

	int count = 0;
	while(head!=end){
		count++;
		if (pBuf->Where[end]==TermChar){
			size = count;
			break;
			}
		end = (end+1) % pBuf->Length;	//Increment wrap around
		}
  	pBuf->Lock = 0;
	return size;
	}

unsigned LCircularBuf::ReadUptoTerm(char Term, unsigned char *buf, int bufsize)
{
	long size = 0;
	WaitForLock(&cbuf);

	int head = cbuf.QHead;
	int end = cbuf.QEnd;
   if (cbuf.QEnd<0) {
	  	ReleasecbufLock;
   	return 0;
      }
   if (cbuf.QHead<0){
	  	ReleasecbufLock;
   	return 0;
      }
	if (head==end) {
	  	ReleasecbufLock;
   	return 0;
      }

	//Scan for Term
   //--------------------
	int count = 0;
	while(head!=end){
		count++;
		if (cbuf.Where[end]==Term){
			size = count;
			break;
			}
		end = (end+1) % cbuf.Length;	//Increment wrap around
		}
	//Read up to Term or the bufsize
   //-------------------------------
	if (size>0){
   	if (size>bufsize) size=bufsize;
		size = _Read(buf, size);
   	}
  	ReleasecbufLock;
	return size;
}

/*
long LCircularBuf::circbufChkTerm(LCircBuffer *pBuf,	char TermChar)
{
	if (!pBuf) return 0;
	if (!pBuf->Where) return 0;


	char *pContent;
	long BufSize;
	long Ptr;
	long SegSize;
	long size;
	char *Occur;

	while(Lock)
		Sleep(50);
	Lock = 1;


	BufSize = pBuf->Length;
	size = pBuf->Used;			//	number of filled characters
	Ptr = pBuf->QEnd;
	if (!size) goto End;

	SegSize=(((Ptr+size)>BufSize)?BufSize-Ptr:size);
	pContent = (char *)pBuf->Where;
	Occur = (char *)memchr(pContent+Ptr,TermChar,SegSize);
	if (!Occur && (Ptr+size>BufSize)) {
		Occur = (char *)memchr(pContent,TermChar,size-SegSize);
		if (!Occur) {
			size = 0;
			}
		else {
			size = (BufSize - Ptr) + (long)(Occur - pContent) + 1;
			}
		}
	else if (Occur) {
		size = (long)(Occur - pContent) - Ptr + 1;
		}
	else {
		size = 0;
		}
End:
	Lock = 0;
	return size;
	}
*/

/*
long LCircularBuf::samplesavailable()
{
   return (cbuf.QHead-cbuf.QEnd);
}

long LCircularBuf::avail()
{
   return (cbuf.QHead-cbuf.QEnd);
}
*/
long LCircularBuf::circbufChkTerm(char TermChar)
{
   return ::circbufChkTerm(&cbuf, TermChar);
}
