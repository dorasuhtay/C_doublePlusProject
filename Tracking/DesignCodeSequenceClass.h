

#ifndef __DesignCodeSequenceClass__h
#define __DesignCodeSequenceClass__h

#include "wctStringList.h"

#define max_DesignCodeSequence			128
#define max_OPCODESEQUENCE		512



typedef struct{
	wchar_t StnID[8];
	wchar_t ProdID[64];//was 32
	wchar_t OpCode[12];
	wchar_t DesignCode[32];
	int seqno;
	//wchar_t Description[128];


	//double piece_rate;
	//double SAM;
}DesignCodeSequenceType;

typedef struct{
	char Idstring[3];
	int versionMajor;
	int versionMinor;
	char spare[64];
	int reccount;
	char endheaderCheckId[3];
}DesignCodeSequenceFileHeaderType;



using namespace System;

class DesignCodeSequenceClass{
private:
	bool storeLock;
	DesignCodeSequenceType	DesignCodeSequence[max_DesignCodeSequence];
	DesignCodeSequenceFileHeaderType	DesignCodeSequenceFileHeader;

	int count;

	wctString *filepath;
	wctString *filepathname;

public:
	DesignCodeSequenceClass(const wchar_t *path);
	~DesignCodeSequenceClass();
	const wchar_t *wgetfile_Name();
	void clear();
	//void add(String ^DesignCodeID, String ^StnID, String ^Description, int OpCode);
	void add(String ^prodID, String ^stnID, String ^opCode, String ^DesignCode, int seqno);
	//String ^getOpCode(String ^STNID, String ^Prodid);
	int getOpCode(String ^STNID, String ^Prodid, int dummy);
	String ^getOpCode(int index);
	String ^getDesignCode(int index);
	int getStationID(String ^OpCode, String ^Prodid, wctStringList *list);
	int getStationID(String ^OpCode, String ^Prodid,wchar_t out[32][64]);
	int getcount() {return count;}

	//int get(String ^DesignCodeID, int StnID, int SequenceNo[], int sizeof_SequenceNo);

	void clear(String ^DesignCodeID);
	//void LoadHanger(String^ ID, String^ HangerID, bool flush=1);
	//void unLoadHanger(String^ ID, bool flush=1);
	//String^ getHangerID(String^ ID);
	void exportToCSV(const char *filename);
	int find(String ^DesignCodeID, int seqno, int offset);
	int find_lastsequenceNo(String ^ProdID);
private:
	//int find(String ^DesignCodeID, int offset);
	void writeDat();
	void readDat();
};

#endif