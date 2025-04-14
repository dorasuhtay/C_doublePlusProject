#ifndef __helpRequestClass__H
#define __helpRequestClass__H

#include "wctString.h"

#define max_HELPREQUEST			128
//#define max_OPCODESEQUENCE		512

#ifdef __GNUC__
    #define STRINGPTR   wchar_t *
 //   #define NULLValue   0
#else
    #define STRINGPTR   String ^
//    #define NULLValue   "null"
#endif

typedef struct{
	wchar_t helpMsg[32];
	wchar_t STNID[16];
	/*
	wchar_t OPCODE[32];
	wchar_t EmpId[32];
	wchar_t NxtSTNID[32];
	wchar_t dbgloc[32];

	int seqNo;
	int nextseqNo;

	int BundlSeqSeqNo;
	int source_stn;
	int dest_stn;
	int rounds;
	int OpCodeSeqPtr;		//0..max_OPCODESEQUENCE-1

	//initialization get from SQL at startup
	wchar_t DesignCode[64];
	int OpCodeSequence[max_OPCODESEQUENCE];		//2000, 5000, 600000,...

	//...
	bool skipCount;
	*/
}helpRequestType;

typedef struct{
	char Idstring[3];
	int versionMajor;
	int versionMinor;
	char spare[64];
	int reccount;
	char endheaderCheckId[3];
}helpRequestFileHeaderType;


#ifndef __GNUC__
using namespace System;
#endif

class helpRequestClass{
private:
	bool storeLock;
	helpRequestType	helpRequest[max_HELPREQUEST];
	helpRequestFileHeaderType	helpRequestFileHeader;

	int count;
	wctString *filepath;
	wctString *filepathname;
public:
	helpRequestClass(const wchar_t *path);
	~helpRequestClass();
	const wchar_t *wgetfile_Name();
	const char *cgetfile_Name();
	int getcount() {return count;}
    void Clear();
#ifndef __GNUC__
	void add(STRINGPTR helpMsg, STRINGPTR STNID);
	void clear(STRINGPTR STNID);
#endif
	STRINGPTR getMessage(int index);
	STRINGPTR getSTNID(int index);
    //const char *getfile_Name();
    void readDat();
private:

	int find(STRINGPTR STNID);
	void packarray();

	void writeDat();

};

#endif