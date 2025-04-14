//StationOperatorClass.h

#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include "StationOperatorClass.h"
#ifdef _MSC_VER
    #include "stringconversion.h"
#endif

//---------------------------
//Macro definition
//---------------------------
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#ifdef _MSC_VER
    #define returnTag(a, b)                                             \
        {                                                               \
        	if ((a<0)||(a>=max_STATIONOPERATOR))                         \
                return NULLValue;                                       \
            return gcnew String(reinterpret_cast<const wchar_t*>(b));   \
        }

        #define SetSTRGValue(a, b, c, d)       \
        {                                   \
            if ((a<0)||(a>=count))          \
                return;                     \
            String2CharArray(c, b);    \
            if (flush)                          \
                writeDat();                     \
        }
		#define returnYNValue(a,b)	{if (b)	return "Y"; else return ""; }
	//#define Label_Yes		"Y"
	//#define Label_No		"N"
#else
    #define returnTag(a, b)                 \
        {                                   \
        	if ((a<0)||(a>=max_STATIONOPERATOR))  \
                return NULLValue;           \
            return (b);                     \
        }

    #define SetSTRGValue(a, b, c, d)       \
    {                                   \
        if ((a<0)||(a>=count))          \
            return;                     \
        _tcscpy(b, c);                  \
        if (flush)                          \
            writeDat();                     \
    }

	#define returnYNValue(a,b) {  if (b) return L"Y"; else return L""; }
	//#define Label_Yes		L"Y"
	//#define Label_No		L"N"
#endif

#define returnTAGValue(a,b) \
    {                                   \
	if ((a<0)||(a>=count))      \
		return 0;                       \
	return b;     \
    }


/*
#define SetTAG(a, b, c, d)      \
{                               \
	if ((a<0)||(a>=count))      \
		return;                 \
	b = c;                      \
	if (d)                      \
		writeDat();             \
}
*/
#define SetTAG(a, b, c, d)      \
{                               \
	if ((a>=0)&&(a<count))      \
	{				            \
		b = c;                  \
		if (d)                  \
			writeDat();         \
	}							\
}

#define SetINTValue(a, b, c, d)      \
{                               \
	if ((a>=0)&&(a<count))      \
	{				            \
		b = c;                  \
		if (d)                  \
			writeDat();         \
	}							\
}

#define IncrementTAG(a, b, d)      \
{                               \
	if ((a<0)||(a>=count))      \
		return;                 \
	b++;                      \
	if (d)                      \
		writeDat();             \
}

#define cfile_Name		"StationOp.DAT\0\0"
//const char *StationOperatorClass::getfile_Name(){if (filepathname) return (char *)filepathname->data(); else return cfile_Name;}
const wchar_t *StationOperatorClass::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
const char c_StationOperatorendheaderCheckId[]			= {0xE4,0x65,0x17};
const char c_StationOperatorFileHeader[]				= {0x05,0xC8,0x23};

StationOperatorClass::StationOperatorClass(const wchar_t *path)
{
	storeLock = 0;
	count = 0;
	for (int ii=0;ii<max_STATIONOPERATOR;ii++)
		memset(&StationOp[ii], 0x0, sizeof(StationOpType));

	//initialise file header
	memset(&StationOpFileHeader, 0x0, sizeof(StationOpFileHeaderType));
	StationOpFileHeader.Idstring[0] = c_StationOperatorFileHeader[0];
	StationOpFileHeader.Idstring[1] = c_StationOperatorFileHeader[1];
	StationOpFileHeader.Idstring[2] = c_StationOperatorFileHeader[2];
	StationOpFileHeader.versionMajor = 1;
	StationOpFileHeader.versionMinor = 0;
	StationOpFileHeader.reccount = max_STATIONOPERATOR;
	StationOpFileHeader.endheaderCheckId[0] = c_StationOperatorendheaderCheckId[0];
	StationOpFileHeader.endheaderCheckId[1] = c_StationOperatorendheaderCheckId[1];
	StationOpFileHeader.endheaderCheckId[2] = c_StationOperatorendheaderCheckId[2];

	filepath  = new wctString(path);
	filepathname  = new wctString(path);
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));


	//and finally... read the data from file
	readDat();
}

StationOperatorClass::~StationOperatorClass()
{
	writeDat();
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

void StationOperatorClass::Clear()
{
	for (int ii=0;ii<max_STATIONOPERATOR;ii++)
	{
		
		int HangerReadCounter = StationOp[ii].HangerReadCounter;
		int OutFeedCMDID = StationOp[ii].OutFeedCMDID;
		wchar_t OutFeedHangerID[32];
		_tcscpy(OutFeedHangerID, StationOp[ii].OutFeedHangerID);

		memset(&StationOp[ii], 0x0, sizeof(StationOpType));

		StationOp[ii].HangerReadCounter = HangerReadCounter;
		StationOp[ii].OutFeedCMDID = OutFeedCMDID;
		_tcscpy(StationOp[ii].OutFeedHangerID, OutFeedHangerID);
	}
}



void StationOperatorClass::cancelFindQCStn(int index)
{
	setQCStn(index, false);
	set_CMDID(index, 0);
}

void StationOperatorClass::cancel88Stn(int index)
{
	set88Stn(index, false);
	set_CMDID(index, 0);
}

void StationOperatorClass::cancelMoveStn(int index)
{
	setMoveStn(index, false);
	set_CMDID(index, 0);
}

void StationOperatorClass::cancelGoStn(int index)
{
	setGoStn(index, false);
	set_CMDID(index, 0);
}


void StationOperatorClass::cancelOprefunction(int index)
{
	setOprefunction(index, false);
	set_CMDID(index, 0);
}

void StationOperatorClass::OutFeedUnFire(int index, bool flush)
{
	setFireOutFeed(index, false);
	ClearHangerReadCounter(index, flush);
}





STRINGPTR StationOperatorClass::getFireOutFeed(int index){		returnYNValue(index, isFireOutFeed(index));}
STRINGPTR StationOperatorClass::getxFullLoad(int index){			returnYNValue(index, isxFullLoad(index));}
STRINGPTR StationOperatorClass::getxHalfLoad(int index){			returnYNValue(index, isxHalfLoad(index));}
STRINGPTR StationOperatorClass::getloggedIn(int index){			returnYNValue(index, isloggedIn(index));}
STRINGPTR StationOperatorClass::getLoadingStation(int index){	returnYNValue(index, isLoadingStation(index));}
STRINGPTR StationOperatorClass::getGoStn(int index){			returnYNValue(index, isGoStn(index));}
STRINGPTR StationOperatorClass::getMoveStn(int index){			returnYNValue(index, isMoveStn(index));}
STRINGPTR StationOperatorClass::getQCStn(int index){			returnYNValue(index, isQCStn(index));}
STRINGPTR StationOperatorClass::getOprefunction(int index){		returnYNValue(index, isOprefunction(index));}
//STRINGPTR StationOperatorClass::getOprefunction(int index){		returnYNValue(index, isOprefunction(index));}


bool StationOperatorClass::isFireOutFeed(int index){    returnTAGValue(index, StationOp[index].FireOutFeed);}
bool StationOperatorClass::isxHalfLoad(int index){    returnTAGValue(index, StationOp[index].xhalfload);}
bool StationOperatorClass::isxFullLoad(int index){    returnTAGValue(index, StationOp[index].xfullload);}
bool StationOperatorClass::isOutFeedReady(int index){    returnTAGValue(index, StationOp[index].OutFeedReady);}
bool StationOperatorClass::isOutFeedBusy(int index){ returnTAGValue(index, StationOp[index].OutFeedBusy);}
bool StationOperatorClass::isOutAlive(int index){    returnTAGValue(index, StationOp[index].alive);}
bool StationOperatorClass::isloggedIn(int index){    returnTAGValue(index, StationOp[index].loggedIn);}
bool StationOperatorClass::isStationAssigned(int index){    returnTAGValue(index, StationOp[index].assigned);}
bool StationOperatorClass::isLoadingStation(int index){    returnTAGValue(index, StationOp[index].loadingStation);}

int StationOperatorClass::get_CMDID(int index){    returnTAGValue(index, StationOp[index].bundle_CMDID);}
bool StationOperatorClass::isGoStn(int index){    returnTAGValue(index, StationOp[index].bundle_Flag);}
bool StationOperatorClass::isMoveStn(int index){    returnTAGValue(index, StationOp[index].bundle_Flag1);}
bool StationOperatorClass::isQCStn(int index){    returnTAGValue(index, StationOp[index].bundle_Flag2);}
bool StationOperatorClass::isOprefunction(int index){    returnTAGValue(index, StationOp[index].bundle_Flag3);}
bool StationOperatorClass::isofflineState(int index){    returnTAGValue(index, StationOp[index].offlineState);}
bool StationOperatorClass::is88Stn(int index){    returnTAGValue(index, StationOp[index].bundle_Flag4);}


int StationOperatorClass::getHangerReadCounter(int index){    returnTAGValue(index, StationOp[index].HangerReadCounter);}
int StationOperatorClass::getOutFeedCMDID(int index){    returnTAGValue(index, StationOp[index].OutFeedCMDID);}


STRINGPTR StationOperatorClass::getStationStatus(int index){    returnTag(index, StationOp[index].stationStatus);}
STRINGPTR StationOperatorClass::getBreakStatus(int index){    returnTag(index, StationOp[index].BreakStatus);}
STRINGPTR StationOperatorClass::getBreakName(int index){    returnTag(index, StationOp[index].BreakName);}
STRINGPTR StationOperatorClass::getIn_Status(int index){	returnTag(index, StationOp[index].In_Status) ;}
STRINGPTR StationOperatorClass::getCurOpCode(int index){	returnTag(index, StationOp[index].CurOpCode) ;}
STRINGPTR StationOperatorClass::getOutFeedHangerID(int index){	returnTag(index, StationOp[index].OutFeedHangerID) ;}
STRINGPTR StationOperatorClass::getStationIPaddress(int index){	returnTag(index, StationOp[index].ipaddress) ;}

STRINGPTR StationOperatorClass::getEMPFname(int index){	returnTag(index, StationOp[index].EMPF_name) ;}
STRINGPTR StationOperatorClass::getProdLine(int index){	returnTag(index, StationOp[index].ProdLine) ;}
STRINGPTR StationOperatorClass::getoperator_ID(int index){	returnTag(index, StationOp[index].operator_ID) ;}
STRINGPTR StationOperatorClass::getEMPLname(int index){	returnTag(index, StationOp[index].EMPL_name) ;}
STRINGPTR StationOperatorClass::getLEDName(int index){	returnTag(index, StationOp[index].LEDName) ;}
STRINGPTR StationOperatorClass::getEMPID(int index){	returnTag(index, StationOp[index].EMPID) ;}
STRINGPTR StationOperatorClass::getCurdesignCode(int index){	returnTag(index, StationOp[index].CurdesignCode) ;}
STRINGPTR StationOperatorClass::getLastBundleID(int index){	returnTag(index, StationOp[index].LastBundleID) ;}


bool StationOperatorClass::validArray(int index)
{
	if ((index>=0)&&(index<count)) 
	{
		return true;
	}
	return false;
}

int StationOperatorClass::getShift(int index){    returnTAGValue(index, StationOp[index].shift);}

void StationOperatorClass::setxHalfLoad(int index, bool state, bool flush){					SetTAG(index, StationOp[index].xhalfload, state, flush);}
void StationOperatorClass::setxFullLoad(int index, bool state, bool flush){					SetTAG(index, StationOp[index].xfullload, state, flush);}
void StationOperatorClass::setFireOutFeed(int index, bool state, bool flush) {				SetTAG(index, StationOp[index].FireOutFeed, state, flush);}
void StationOperatorClass::setloggedIn(int index, bool state, bool flush){					SetTAG(index, StationOp[index].loggedIn, state, flush);}
void StationOperatorClass::setStationAssigned(int index, bool state, bool flush){			SetTAG(index, StationOp[index].assigned, state, flush);}
void StationOperatorClass::setOutFeedReady(int index, bool state, bool flush){				SetTAG(index, StationOp[index].OutFeedReady, state, flush);}
void StationOperatorClass::setOutFeedCMDID(int index, int cmdid, bool flush){				SetTAG(index, StationOp[index].OutFeedCMDID, cmdid, flush);}
void StationOperatorClass::set_CMDID(int index, int value, bool flush){						SetTAG(index, StationOp[index].bundle_CMDID, value, flush);}
void StationOperatorClass::setGoStn(int index, bool value, bool flush){						SetTAG(index, StationOp[index].bundle_Flag, value, flush);}
void StationOperatorClass::setMoveStn(int index, bool value, bool flush){					SetTAG(index, StationOp[index].bundle_Flag1, value, flush);}				

void StationOperatorClass::setDestinationStation(int index, int value, bool flush){			SetINTValue(index, StationOp[index].destStn, value, flush);}


void StationOperatorClass::set88Stn(int index, bool value, bool flush){						SetTAG(index, StationOp[index].bundle_Flag4, value, flush);}
void StationOperatorClass::setQCStn(int index, bool value, bool flush){						SetTAG(index, StationOp[index].bundle_Flag2, value, flush);}
void StationOperatorClass::setOprefunction(int index, bool value, bool flush){				SetTAG(index, StationOp[index].bundle_Flag3, value, flush);}
void StationOperatorClass::setAlive(int index, bool state, bool flush){						SetTAG(index, StationOp[index].alive, state, flush);}
void StationOperatorClass::setShift(int index, int value, bool flush){						SetTAG(index, StationOp[index].shift, value, flush);}
void StationOperatorClass::setOutFeedBusy(int index, bool state, bool flush){				SetTAG(index, StationOp[index].OutFeedBusy, state, flush);}
void StationOperatorClass::setStationAsLoadingStation(int index, bool state, bool flush){	SetTAG(index, StationOp[index].loadingStation, state, flush);}
void StationOperatorClass::setEMPFname(int index, STRINGPTR name, bool flush){				SetSTRGValue(index, StationOp[index].EMPF_name, name, flush);}
void StationOperatorClass::setIn_Status(int index, STRINGPTR name, bool flush){				SetSTRGValue(index, StationOp[index].In_Status, name, flush);}
void StationOperatorClass::setStationStatus(int index, STRINGPTR name, bool flush){				SetSTRGValue(index, StationOp[index].stationStatus, name, flush);}

void StationOperatorClass::setBreakStatus(int index, STRINGPTR name, bool flush){			SetSTRGValue(index, StationOp[index].BreakStatus, name, flush);}
void StationOperatorClass::setBreakName(int index, STRINGPTR name, bool flush){				SetSTRGValue(index, StationOp[index].BreakName, name, flush);}

void StationOperatorClass::setofflineState(int index, bool value, bool flush){				SetTAG(index, StationOp[index].offlineState, value, flush);}
void StationOperatorClass::ClearHangerReadCounter(int index, bool flush){					SetTAG(index, StationOp[index].HangerReadCounter, 0, flush);}
void StationOperatorClass::IncrementHangerReadCounter(int index, bool flush){				IncrementTAG(index, StationOp[index].HangerReadCounter, flush);}

void StationOperatorClass::loggedIn(int index, bool state, bool flush)
{
    setloggedIn(index, state, 0);
	setStationAssigned( index, state, 0);
	setAlive(index, state, flush);
}
 




void StationOperatorClass::setloggedInMsg(int index, STRINGPTR name, bool flush)
{
}




#ifdef _MSC_VER
void StationOperatorClass::setIn_Status(STRINGPTR CurOpCode, STRINGPTR CurdesignCode, STRINGPTR name, bool flush)
{
	int ii;
	for (ii=0;ii<count;ii++)
	{
		STRINGPTR mCurOpCode = gcnew String(reinterpret_cast<const wchar_t*>(StationOp[ii].CurOpCode));
		STRINGPTR mCurdesignCode = gcnew String(reinterpret_cast<const wchar_t*>(StationOp[ii].CurdesignCode));
	}

}
#endif

void StationOperatorClass::setProdLine(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, StationOp[index].ProdLine, name, flush);}
void StationOperatorClass::setoperator_ID(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, StationOp[index].operator_ID, name, flush);}
void StationOperatorClass::setEMPLname(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, StationOp[index].EMPL_name, name, flush);}
void StationOperatorClass::setLEDName(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, StationOp[index].LEDName, name, flush);}
void StationOperatorClass::setEMPID(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, StationOp[index].EMPID, name, flush);}
void StationOperatorClass::setCurdesignCode(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, StationOp[index].CurdesignCode, name, flush);}
void StationOperatorClass::setLastBundleID(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, StationOp[index].LastBundleID, name, flush);}
void StationOperatorClass::setOutFeedHangerID(int index, STRINGPTR HangerID, bool flush){	SetSTRGValue(index, StationOp[index].OutFeedHangerID, HangerID, flush);}
void StationOperatorClass::setStationIPaddress(int index, STRINGPTR ipaddress, bool flush){	SetSTRGValue(index, StationOp[index].ipaddress, ipaddress, flush);}
void StationOperatorClass::setCurOpCode(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, StationOp[index].CurOpCode, name, flush);}



/*
void StationOperatorClass::LoadHanger(String^ ID, String^ HangerID, bool flush)
{
	int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_STATIONOPERATOR))
		return;
	String2CharArray(HangerID, StationOp[stnid].Hanger_ID);
	if (flush)
		writeDat();
}

void StationOperatorClass::unLoadHanger(String^ ID, bool flush)
{
		int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_STATIONOPERATOR))
		return;
	memset(&StationOp[stnid].Hanger_ID, 0x0, sizeof(StationOp[stnid].Hanger_ID));
	if (flush)
		writeDat();
}

String^ StationOperatorClass::getHangerID(String^ ID)
{
	int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_STATIONOPERATOR))
		return "";
	String ^temp = gcnew String(reinterpret_cast<const char*>(StationOp[stnid].Hanger_ID));
	return temp;
}

*/
void StationOperatorClass::readDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&StationOpFileHeader, sizeof(StationOpFileHeaderType), 1, fp);
		count = StationOpFileHeader.reccount;
		for (int ii=0;ii<StationOpFileHeader.reccount;ii++)
		{
			fread(&StationOp[ii], sizeof(StationOpType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}

void StationOperatorClass::writeDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
		StationOpFileHeader.reccount = count;
		fwrite(&StationOpFileHeader, sizeof(StationOpFileHeaderType), 1, fp);
		for (int ii=0;ii<StationOpFileHeader.reccount;ii++)
		{
			fwrite(&StationOp[ii], sizeof(StationOpType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}
