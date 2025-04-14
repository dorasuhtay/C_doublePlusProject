
#ifndef __ManufactureOrder__H
#define __ManufactureOrder__H

	

#include "wctString.h"

#define max_MANUFACTUREORDER			1024
//#define max_OPCODESEQUENCE		512

#ifdef __GNUC__
    #define STRINGPTR   wchar_t *
 //   #define NULLValue   0
#else
    #define STRINGPTR   String ^
//    #define NULLValue   "null"
#endif

typedef struct{
	wchar_t MONO[32];
	int prodline;
	int maxbundleno;

	int day;
	int month;
	int year;

	//wchar_t STNID[16];
	//wchar_t HANGERID[16];
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
}MONO_Type;

typedef struct{
	char Idstring[3];
	int versionMajor;
	int versionMinor;
	int Productionline;		//4 bytes
	int highestmaxbundleno;
	char spare[64];
	int reccount;
	char endheaderCheckId[3];
}MONO_FileHeaderType;


#ifndef __GNUC__
using namespace System;
#endif

class ManufactureOrder{
private:
	bool storeLock;
	MONO_Type	*monoRec[max_MANUFACTUREORDER];
	MONO_FileHeaderType	monoRecFileHeader;

	int count;
	wctString *filepath;
	wctString *filepathname;
public:
	ManufactureOrder(const wchar_t *path);
	~ManufactureOrder();
	const wchar_t *wgetfile_Name();
	const char *cgetfile_Name();
	int getcount() {return count;}
    void Clear(bool flush=1);
	void setProdline(int Prodline);
#ifndef __GNUC__
	void add(STRINGPTR mono, int prodline, int maxbundleno, int Day, int Month, int Year);
	void clear(STRINGPTR mono, int prodline);
#endif
	STRINGPTR getMONO(int index);
	int getmaxbundleno(int index);
	int find(STRINGPTR mono, int prodline);
    //const char *getfile_Name();
    int readDat();
private:
	int findlargestBundleNo();
	void clearNot(int Prodline);
	void packarray();
	void writeDat();

};



#endif