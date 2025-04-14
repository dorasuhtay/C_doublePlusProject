#ifndef LCIRCBUF_H_INCLUDED
#define LCIRCBUF_H_INCLUDED

typedef struct  {
	unsigned char *Where;
	long Length;
	long QHead;
	long QEnd;
	long Free;
	long Used;
	char Lock;
	}LCircBuffer;



class LCircularBuf {
private:
//	#if defined(BI_PLAT_WIN32)
//	HGLOBAL hdatabuf;
//   #endif
	unsigned char *databuf;
   LCircBuffer	cbuf;
   long prevSerialPtr;		//for Read			 intended for comms processing purpose
   long outSerialPtr;			//for ReadOut()    intended for console display purpose
public:
	int age;
	char DateSince[60];
	long TotalChars;
	LCircularBuf();
   ~LCircularBuf();
   int Init(long nsize);
   int Add(const unsigned char *lpChar, long CharNum);
	int Add(unsigned char ch);
	void Clear();
	int RemoveSerialChar(long nCount);
	int PutBackSerialChar();
	int ReadCh();
	long Read(unsigned char *buf, long nCount);			//for comms processing purpose
   long ReadOut(unsigned char *buf, long nCount); 	//for console readout raw data display purpose
	long circbufChkTerm(char TermChar);
   long bSize();
   double circbufPercentUsed();
	double circbufPercentUsedAsOf(long size);
   int bytesAvail();
   long samplesavailable();
   long used();
   void Backspace();
	unsigned ReadUptoTerm(char Term, unsigned char *buf, int bufsize);
   void OffsetTail(long offset);
private:
	void Reset();
	void circbufInit(LCircBuffer *pBuf, void *Storage, long size);
	void circbufReset(LCircBuffer *pBuf);
	void DestroyStorageBuffer();
	long _Read(unsigned char *buf, long nCount);
};


#endif // LCIRCBUF_H_INCLUDED
