#ifndef __OverheadPusherClass__h
#define __OverheadPusherClass__h

#include "xplatform_define.h"
#include "wctString.h"
#include "applicationSetting.h"
/*
#ifdef __GNUC__
    #define STRINGPTR   wchar_t *
    #define NULLValue   0
#else
    using namespace System;
    #define STRINGPTR   String ^
    #define NULLValue   "null"
#endif
*/
typedef struct{
	wchar_t Hanger_ID[16];		//in SQLdb fieldname is HANGERID
	wchar_t srcSTNID[16];		//in SQLdb fieldname is CURSTN
	wchar_t destSTNID[16];		//in SQLdb fieldname is STNDEST
	int pCount;					//for monitoring only
	int Pusher_Count;			//for monitoring only
	bool PUSHERSTATUS;			//in SQLdb fieldname is PUSHERSTATUS
	int ROUND;					//in SQLdb fieldname is ROUND
}overhdrPusherType;

typedef struct{
	char Idstring[3];
	int versionMajor;
	int versionMinor;
	char spare[64];
	int reccount;
	char endheaderCheckId[3];
}overhdrPusherFileHeaderType;
 
#define  max_OVERHEADPUSHER	200


class OverheadPusherClass{
private:
	int count;
	bool storeLock;
	//max_OVERHEADPUSHER=count;
	overhdrPusherType	overhdrPusher[max_OVERHEADPUSHER];
	overhdrPusherFileHeaderType	overhdrPusherFileHeader;
	wctString *filepath;
	wctString *filepathname;
public:
	OverheadPusherClass(const wchar_t *path);
	~OverheadPusherClass();
	const wchar_t *wgetfile_Name();
	const char *cgetfile_Name();
	void Clear();
	int getData(int index, overhdrPusherType *ovrhdrpsh);
	#ifdef _MSC_VER
	void LoadHanger(int pusher, String^ srcSTNID, String^ destSTNID, String^ HangerID, bool flush=1);
	void unLoadHanger(int pusher, bool flush=1);
	void updateHangerStatus(int pusher, int rounds, String^ destSTNID, bool flush=1);
	int findHanger(STRINGPTR HangerID, STRINGPTR Dest);
	void setPusherUnloadStatus(STRINGPTR HangerID, STRINGPTR STNDest, int pCount, int Pusher_Count);
	#endif
	int getPusher_Count(int pusher);
	int getpCount(int pusher);
	int getRemainder(int pusher);
	STRINGPTR getHangerID(int pusher);
	void setMax_Number_of_PUSHER(int pusher) {count = pusher; writeDat();}
	int getcount() {return count;}
	STRINGPTR getHangerSrcStation(int pusher);
	STRINGPTR getHangerDestStation(int pusher);
    bool isPusherLoaded(int index);
    int getRounds(int index);
	//const char *getfile_Name();
    void readDat();
private:
	void writeDat();

};

#endif
