//#include "class_MRT_Online_Bridges.h"


//class_MRT_Online_Bridges.h

#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include "class_MRT_Online_Bridges.h"
#ifdef _MSC_VER
    #include "stringconversion.h"
#endif

//---------------------------
//Macro definition
//---------------------------
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#ifdef _MSC_VER
    #define returnTag(a, b, c)                                             \
        {				\
			if (!b)		\
				return NULLValue;                                       \
        	if ((a<0)||(a>=count))                         \
                return NULLValue;                                       \
            return gcnew String(reinterpret_cast<const wchar_t*>(c));   \
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
    #define returnTag(a, b`, c)                 \
        {                                   \
			if (!b)		\
				return NULLValue;           \
        	if ((a<0)||(a>=count))  \
                return NULLValue;           \
            return (c);                     \
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

#define returnTAGValue(a, b, c) \
    {						\
	if (!b)\
		return 0;                       \
	if ((a<0)||(a>=count))      \
		return 0;                       \
	return c;     \
    }



#define SetTAG(a, e, b, c, d)      \
{                               \
	if (e&&(a>=0)&&(a<count))      \
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

#define cfile_Name		"OnlineBridges.DAT\0\0"
//const char *class_MRT_Online_Bridges::getfile_Name(){if (filepathname) return (char *)filepathname->data(); else return cfile_Name;}
const wchar_t *class_MRT_Online_Bridges::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
const char c_MRT_OnlineBridgesendheaderCheckId[]			= {0xE4,0x65,0x17};
const char c_MRT_OnlineBridgesFileHeader[]				= {0x05,0xC8,0x23};

class_MRT_Online_Bridges::class_MRT_Online_Bridges(const wchar_t *path)
{
	storeLock = 0;
	count = 0;
	for (int ii=0;ii<max_MRT_OnlineBridges;ii++)
		OnlineBridges[ii] = 0x0;

	//initialise file header
	memset(&OnlineBridgesFileHeader, 0x0, sizeof(MRT_OnlineBridgesFileHeaderType));
	OnlineBridgesFileHeader.Idstring[0] = c_MRT_OnlineBridgesFileHeader[0];
	OnlineBridgesFileHeader.Idstring[1] = c_MRT_OnlineBridgesFileHeader[1];
	OnlineBridgesFileHeader.Idstring[2] = c_MRT_OnlineBridgesFileHeader[2];
	OnlineBridgesFileHeader.versionMajor = 1;
	OnlineBridgesFileHeader.versionMinor = 0;
	OnlineBridgesFileHeader.reccount = max_MRT_OnlineBridges;
	OnlineBridgesFileHeader.endheaderCheckId[0] = c_MRT_OnlineBridgesendheaderCheckId[0];
	OnlineBridgesFileHeader.endheaderCheckId[1] = c_MRT_OnlineBridgesendheaderCheckId[1];
	OnlineBridgesFileHeader.endheaderCheckId[2] = c_MRT_OnlineBridgesendheaderCheckId[2];

	filepath  = new wctString(path);
	filepathname  = new wctString(path);
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));


	//and finally... read the data from file
	//readDat();
}

class_MRT_Online_Bridges::~class_MRT_Online_Bridges()
{
	writeDat();
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

void class_MRT_Online_Bridges::Clear()
{
	for (int ii=0;ii<max_MRT_OnlineBridges;ii++)
	{
		SAFE_DELETE(OnlineBridges[ii]);
	}
	count = 0;
}

void class_MRT_Online_Bridges::Add(const wchar_t *Type, const wchar_t *bridgeName, int bridgeID, const wchar_t *hostname1, int stationID1, const wchar_t *hostname2, int stationID2, const wchar_t *Remarks)
{
	if (count>=max_MRT_OnlineBridges) return;
	OnlineBridges[count] = new MRT_OnlineBridgesType;

	OnlineBridges[count]->bridgeID = bridgeID;
	OnlineBridges[count]->stationID1 = stationID1;
	OnlineBridges[count]->stationID2 = stationID2;
	_tcsncpy(OnlineBridges[count]->Type, Type, MAX_bridgename_STRING_SIZE-1);				OnlineBridges[count]->Type[MAX_bridgename_STRING_SIZE-1] = 0x0;
	_tcsncpy(OnlineBridges[count]->bridgeName, bridgeName, MAX_bridgename_STRING_SIZE-1);	OnlineBridges[count]->bridgeName[MAX_bridgename_STRING_SIZE-1] = 0x0;
	_tcsncpy(OnlineBridges[count]->hostname1, hostname1, MAX_bridgename_STRING_SIZE-1);		OnlineBridges[count]->hostname1[MAX_bridgename_STRING_SIZE-1] = 0x0;
	_tcsncpy(OnlineBridges[count]->hostname2, hostname2, MAX_bridgename_STRING_SIZE-1);		OnlineBridges[count]->hostname2[MAX_bridgename_STRING_SIZE-1] = 0x0;
	_tcsncpy(OnlineBridges[count]->Remarks, Remarks, MAX_bridgename_STRING_SIZE-1);			OnlineBridges[count]->Remarks[MAX_bridgename_STRING_SIZE-1] = 0x0;
	count++;
}

/*
void class_MRT_Online_Bridges::cancelFindQCStn(int index)
{
	setQCStn(index, false);
	setstationID2(index, 0);
}

void class_MRT_Online_Bridges::cancelMoveStn(int index)
{
	setMoveStn(index, false);
	setstationID2(index, 0);
}

void class_MRT_Online_Bridges::cancelGoStn(int index)
{
	setbridgeID(index, false);
	setstationID2(index, 0);
}


void class_MRT_Online_Bridges::cancelOprefunction(int index)
{
	setOprefunction(index, false);
	setstationID2(index, 0);
}

void class_MRT_Online_Bridges::OutFeedUnFire(int index, bool flush)
{
	setFireOutFeed(index, false);
	ClearHangerReadCounter(index, flush);
}
*/



/*
STRINGPTR class_MRT_Online_Bridges::getFireOutFeed(int index){		returnYNValue(index, isFireOutFeed(index));}
STRINGPTR class_MRT_Online_Bridges::getxFullLoad(int index){			returnYNValue(index, isxFullLoad(index));}
STRINGPTR class_MRT_Online_Bridges::getxHalfLoad(int index){			returnYNValue(index, isxHalfLoad(index));}
STRINGPTR class_MRT_Online_Bridges::getloggedIn(int index){			returnYNValue(index, isloggedIn(index));}
STRINGPTR class_MRT_Online_Bridges::getLoadingStation(int index){	returnYNValue(index, isLoadingStation(index));}
STRINGPTR class_MRT_Online_Bridges::getGoStn(int index){			returnYNValue(index, isGoStn(index));}
STRINGPTR class_MRT_Online_Bridges::getMoveStn(int index){			returnYNValue(index, isMoveStn(index));}
STRINGPTR class_MRT_Online_Bridges::getQCStn(int index){			returnYNValue(index, isQCStn(index));}
STRINGPTR class_MRT_Online_Bridges::getOprefunction(int index){		returnYNValue(index, isOprefunction(index));}


bool class_MRT_Online_Bridges::isFireOutFeed(int index){    returnTAGValue(index, OnlineBridges[index].FireOutFeed);}
bool class_MRT_Online_Bridges::isxHalfLoad(int index){    returnTAGValue(index, OnlineBridges[index].xhalfload);}
bool class_MRT_Online_Bridges::isxFullLoad(int index){    returnTAGValue(index, OnlineBridges[index].xfullload);}
bool class_MRT_Online_Bridges::isOutFeedReady(int index){    returnTAGValue(index, OnlineBridges[index].OutFeedReady);}
bool class_MRT_Online_Bridges::isOutFeedBusy(int index){ returnTAGValue(index, OnlineBridges[index].OutFeedBusy);}
bool class_MRT_Online_Bridges::isOutAlive(int index){    returnTAGValue(index, OnlineBridges[index].alive);}
bool class_MRT_Online_Bridges::isloggedIn(int index){    returnTAGValue(index, OnlineBridges[index].loggedIn);}
bool class_MRT_Online_Bridges::isStationAssigned(int index){    returnTAGValue(index, OnlineBridges[index].assigned);}
bool class_MRT_Online_Bridges::isLoadingStation(int index){    returnTAGValue(index, OnlineBridges[index].loadingStation);}


bool class_MRT_Online_Bridges::isGoStn(int index){    returnTAGValue(index, OnlineBridges[index].bundle_Flag);}
bool class_MRT_Online_Bridges::isMoveStn(int index){    returnTAGValue(index, OnlineBridges[index].bundle_Flag1);}
bool class_MRT_Online_Bridges::isQCStn(int index){    returnTAGValue(index, OnlineBridges[index].bundle_Flag2);}
bool class_MRT_Online_Bridges::isOprefunction(int index){    returnTAGValue(index, OnlineBridges[index].bundle_Flag3);}
bool class_MRT_Online_Bridges::isofflineState(int index){    returnTAGValue(index, OnlineBridges[index].offlineState);}
*/
int class_MRT_Online_Bridges::getbridgeID(int index){		returnTAGValue(index, OnlineBridges[index], OnlineBridges[index]->bridgeID);}
int class_MRT_Online_Bridges::getstationID1(int index){		returnTAGValue(index, OnlineBridges[index], OnlineBridges[index]->stationID1);}
int class_MRT_Online_Bridges::getstationID2(int index){		returnTAGValue(index, OnlineBridges[index], OnlineBridges[index]->stationID2);}

STRINGPTR class_MRT_Online_Bridges::getbridgeName(int index){	returnTag(index, OnlineBridges[index], OnlineBridges[index]->bridgeName) ;}
STRINGPTR class_MRT_Online_Bridges::gethostname1(int index){	returnTag(index, OnlineBridges[index], OnlineBridges[index]->hostname1) ;}
STRINGPTR class_MRT_Online_Bridges::gethostname2(int index){	returnTag(index, OnlineBridges[index], OnlineBridges[index]->hostname2) ;}
STRINGPTR class_MRT_Online_Bridges::getRemarks(int index){		returnTag(index, OnlineBridges[index], OnlineBridges[index]->Remarks) ;}
STRINGPTR class_MRT_Online_Bridges::getType(int index){			returnTag(index, OnlineBridges[index], OnlineBridges[index]->Type) ;}

void class_MRT_Online_Bridges::setstationID1(int index, int value, bool flush){		SetTAG(index, OnlineBridges[index], OnlineBridges[index]->stationID1, value, flush);}
void class_MRT_Online_Bridges::setstationID2(int index, int value, bool flush){		SetTAG(index, OnlineBridges[index], OnlineBridges[index]->stationID2, value, flush);}
void class_MRT_Online_Bridges::setbridgeID(int index, bool value, bool flush){		SetTAG(index, OnlineBridges[index], OnlineBridges[index]->bridgeID, value, flush);}
/*
int class_MRT_Online_Bridges::getHangerReadCounter(int index){    returnTAGValue(index, OnlineBridges[index].HangerReadCounter);}
int class_MRT_Online_Bridges::getOutFeedCMDID(int index){    returnTAGValue(index, OnlineBridges[index].OutFeedCMDID);}

STRINGPTR class_MRT_Online_Bridges::getStationStatus(int index){    returnTag(index, OnlineBridges[index].stationStatus);}

STRINGPTR class_MRT_Online_Bridges::getCurOpCode(int index){	returnTag(index, OnlineBridges[index].CurOpCode) ;}
STRINGPTR class_MRT_Online_Bridges::getOutFeedHangerID(int index){	returnTag(index, OnlineBridges[index].OutFeedHangerID) ;}


STRINGPTR class_MRT_Online_Bridges::getoperator_ID(int index){	returnTag(index, OnlineBridges[index].operator_ID) ;}
STRINGPTR class_MRT_Online_Bridges::getEMPLname(int index){	returnTag(index, OnlineBridges[index].EMPL_name) ;}
STRINGPTR class_MRT_Online_Bridges::getLEDName(int index){	returnTag(index, OnlineBridges[index].LEDName) ;}
STRINGPTR class_MRT_Online_Bridges::getEMPID(int index){	returnTag(index, OnlineBridges[index].EMPID) ;}
STRINGPTR class_MRT_Online_Bridges::getCurdesignCode(int index){	returnTag(index, OnlineBridges[index].CurdesignCode) ;}
STRINGPTR class_MRT_Online_Bridges::getLastBundleID(int index){	returnTag(index, OnlineBridges[index].LastBundleID) ;}
*/



/*
void class_MRT_Online_Bridges::setxHalfLoad(int index, bool state, bool flush){					SetTAG(index, OnlineBridges[index].xhalfload, state, flush);}
void class_MRT_Online_Bridges::setxFullLoad(int index, bool state, bool flush){					SetTAG(index, OnlineBridges[index].xfullload, state, flush);}
void class_MRT_Online_Bridges::setFireOutFeed(int index, bool state, bool flush) {				SetTAG(index, OnlineBridges[index].FireOutFeed, state, flush);}
void class_MRT_Online_Bridges::setloggedIn(int index, bool state, bool flush){					SetTAG(index, OnlineBridges[index].loggedIn, state, flush);}
void class_MRT_Online_Bridges::setStationAssigned(int index, bool state, bool flush){			SetTAG(index, OnlineBridges[index].assigned, state, flush);}
void class_MRT_Online_Bridges::setOutFeedReady(int index, bool state, bool flush){				SetTAG(index, OnlineBridges[index].OutFeedReady, state, flush);}
void class_MRT_Online_Bridges::setOutFeedCMDID(int index, int cmdid, bool flush){				SetTAG(index, OnlineBridges[index].OutFeedCMDID, cmdid, flush);}
void class_MRT_Online_Bridges::setMoveStn(int index, bool value, bool flush){					SetTAG(index, OnlineBridges[index].bundle_Flag1, value, flush);}
void class_MRT_Online_Bridges::setQCStn(int index, bool value, bool flush){						SetTAG(index, OnlineBridges[index].bundle_Flag2, value, flush);}
void class_MRT_Online_Bridges::setOprefunction(int index, bool value, bool flush){				SetTAG(index, OnlineBridges[index].bundle_Flag3, value, flush);}
void class_MRT_Online_Bridges::setAlive(int index, bool state, bool flush){						SetTAG(index, OnlineBridges[index].alive, state, flush);}
void class_MRT_Online_Bridges::setOutFeedBusy(int index, bool state, bool flush){				SetTAG(index, OnlineBridges[index].OutFeedBusy, state, flush);}
void class_MRT_Online_Bridges::setStationAsLoadingStation(int index, bool state, bool flush){	SetTAG(index, OnlineBridges[index].loadingStation, state, flush);}
void class_MRT_Online_Bridges::setStationStatus(int index, STRINGPTR name, bool flush){				SetSTRGValue(index, OnlineBridges[index].stationStatus, name, flush);}


void class_MRT_Online_Bridges::setofflineState(int index, bool value, bool flush){				SetTAG(index, OnlineBridges[index].offlineState, value, flush);}
void class_MRT_Online_Bridges::ClearHangerReadCounter(int index, bool flush){					SetTAG(index, OnlineBridges[index].HangerReadCounter, 0, flush);}
void class_MRT_Online_Bridges::IncrementHangerReadCounter(int index, bool flush){				IncrementTAG(index, OnlineBridges[index].HangerReadCounter, flush);}

void class_MRT_Online_Bridges::loggedIn(int index, bool state, bool flush)
{
    setloggedIn(index, state, 0);
	setStationAssigned( index, state, 0);
	setAlive(index, state, flush);
}
 */


#ifdef _MSC_VER
void class_MRT_Online_Bridges::setRemarks(int index, STRINGPTR name, bool flush){		SetSTRGValue(index, OnlineBridges[index]->Remarks, name, flush);}
void class_MRT_Online_Bridges::sethostname1(int index, STRINGPTR name, bool flush){		SetSTRGValue(index, OnlineBridges[index]->hostname1, name, flush);}
void class_MRT_Online_Bridges::sethostname2(int index, STRINGPTR name, bool flush){		SetSTRGValue(index, OnlineBridges[index]->hostname2, name, flush);}
void class_MRT_Online_Bridges::setbridgeName(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, OnlineBridges[index]->bridgeName, name, flush);}
#endif

/*
#ifdef _MSC_VER
void class_MRT_Online_Bridges::setRemarks(STRINGPTR CurOpCode, STRINGPTR CurdesignCode, STRINGPTR name, bool flush)
{
	int ii;
	for (ii=0;ii<count;ii++)
	{
		STRINGPTR mCurOpCode = gcnew String(reinterpret_cast<const wchar_t*>(OnlineBridges[ii].CurOpCode));
		STRINGPTR mCurdesignCode = gcnew String(reinterpret_cast<const wchar_t*>(OnlineBridges[ii].CurdesignCode));
	}

}
#endif


void class_MRT_Online_Bridges::setoperator_ID(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, OnlineBridges[index].operator_ID, name, flush);}
void class_MRT_Online_Bridges::setEMPLname(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, OnlineBridges[index].EMPL_name, name, flush);}
void class_MRT_Online_Bridges::setLEDName(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, OnlineBridges[index].LEDName, name, flush);}
void class_MRT_Online_Bridges::setEMPID(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, OnlineBridges[index].EMPID, name, flush);}
void class_MRT_Online_Bridges::setCurdesignCode(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, OnlineBridges[index].CurdesignCode, name, flush);}
void class_MRT_Online_Bridges::setLastBundleID(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, OnlineBridges[index].LastBundleID, name, flush);}
void class_MRT_Online_Bridges::setOutFeedHangerID(int index, STRINGPTR HangerID, bool flush){	SetSTRGValue(index, OnlineBridges[index].OutFeedHangerID, HangerID, flush);}
void class_MRT_Online_Bridges::setbridgeName(int index, STRINGPTR name, bool flush){	SetSTRGValue(index, OnlineBridges[index].CurOpCode, name, flush);}
*/


/*
void class_MRT_Online_Bridges::LoadHanger(String^ ID, String^ HangerID, bool flush)
{
	int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_MRT_OnlineBridges))
		return;
	String2CharArray(HangerID, OnlineBridges[stnid].Hanger_ID);
	if (flush)
		writeDat();
}

void class_MRT_Online_Bridges::unLoadHanger(String^ ID, bool flush)
{
		int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_MRT_OnlineBridges))
		return;
	memset(&OnlineBridges[stnid].Hanger_ID, 0x0, sizeof(OnlineBridges[stnid].Hanger_ID));
	if (flush)
		writeDat();
}

String^ class_MRT_Online_Bridges::getHangerID(String^ ID)
{
	int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_MRT_OnlineBridges))
		return "";
	String ^temp = gcnew String(reinterpret_cast<const char*>(OnlineBridges[stnid].Hanger_ID));
	return temp;
}

*/
void class_MRT_Online_Bridges::readDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&OnlineBridgesFileHeader, sizeof(MRT_OnlineBridgesFileHeaderType), 1, fp);
		count = OnlineBridgesFileHeader.reccount;
		for (int ii=0;ii<OnlineBridgesFileHeader.reccount;ii++)
		{
			fread(&OnlineBridges[ii], sizeof(MRT_OnlineBridgesType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}

void class_MRT_Online_Bridges::writeDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
		OnlineBridgesFileHeader.reccount = count;
		fwrite(&OnlineBridgesFileHeader, sizeof(MRT_OnlineBridgesFileHeaderType), 1, fp);
		for (int ii=0;ii<OnlineBridgesFileHeader.reccount;ii++)
		{
			fwrite(&OnlineBridges[ii], sizeof(MRT_OnlineBridgesType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}
