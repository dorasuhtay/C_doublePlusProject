#ifndef __HangerTagClass__h
#define __HangerTagClass__h

#include "wctString.h"

#define max_HANGERTAG			4096
#define max_OPCODESEQUENCE		512

#ifdef __GNUC__
    #define STRINGPTR   wchar_t *
 //   #define NULLValue   0
#else
    #define STRINGPTR   String ^
//    #define NULLValue   "null"
#endif

typedef struct{
	wchar_t Hanger_ID[16];
	wchar_t STNID[16];
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

}HangerTagType;

typedef struct{
	char Idstring[3];
	int versionMajor;
	int versionMinor;
	char spare[64];
	int reccount;
	char endheaderCheckId[3];
}HangerTagFileHeaderType;


#ifndef __GNUC__
using namespace System;
#endif

class HangerTagClass{
private:
	bool storeLock;
	HangerTagType	HangerTag[max_HANGERTAG];
	HangerTagFileHeaderType	HangerTagFileHeader;

	int count;
	wctString *filepath;
	wctString *filepathname;
public:
	HangerTagClass(const wchar_t *path);
	~HangerTagClass();
	const wchar_t *wgetfile_Name();
	const char *cgetfile_Name();
	int getcount() {return count;}
    void Clear();
#ifndef __GNUC__
	void add(String ^Hanger_ID, String ^DesignCode, String ^OPCODE, String ^STNID, int BundlSeqSeqNo,  String ^EmpId);
	void setNextStation(String ^Hanger_ID, String ^NxtSTNID, String ^dbgloc);
	void clear(String ^Hanger_ID);
	void updateSequence(String ^Hanger_ID, int seqNo, int nextseqNo);
#endif
	STRINGPTR getDesignCode(int index);
	STRINGPTR getHangerID(int index);
	STRINGPTR getHangerOPCODE(int index);
	STRINGPTR getHangerSTNID(int index);
	STRINGPTR getHangerEmpId(int index);
    STRINGPTR getdbgloc(int index);
	int getBundlSeqSeqNo(int index);
	int getBundlSeqSeqNo(STRINGPTR Hanger_ID);
	STRINGPTR getNextStation(int index);
	STRINGPTR getOpCode(STRINGPTR Hanger_ID);
    int getSeqNo(int index);
	int getSeqNo(STRINGPTR Hanger_ID);
	int getNextSeqNo(int index);
	int getNextSeqNo(STRINGPTR Hanger_ID);
   //const char *getfile_Name();

	//void setSkipCount(STRINGPTR Hanger_ID, bool state);
	//bool getSkipCount(STRINGPTR Hanger_ID);


    void readDat();
private:

	int find(STRINGPTR Hanger_ID);

	void writeDat();

};

#endif

