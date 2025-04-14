//StationOperatorClass.h

#ifndef __StationOperatorClass__h
#define __StationOperatorClass__h

#include "xplatform_define.h"
#include "wctString.h"


#define stn_status_OK			1000
#define stn_status_PRAYER		1001
#define stn_status_TEABREAK		1002
#define stn_status_REPAIR		1003

typedef struct{

	//login status
	wchar_t ProdLine[8];	//ProductionLine
	wchar_t operator_ID[32];	//operator name
	wchar_t EMPF_name[64];	//operator name
	wchar_t EMPL_name[64];	//operator name
	wchar_t LEDName[64];	//operator name
	wchar_t EMPID[64];	//operator name
	wchar_t CurOpCode[64];
	wchar_t CurdesignCode[64];
	wchar_t In_Status[32];
	wchar_t OutFeedHangerID[32];
	wchar_t LastBundleID[64];
	wchar_t loggedInMsg[32];
	wchar_t stationStatus[2];			//SQL STATIONSTATUS   //H-HALF, F-FULL, X-NULL, L-LOCK
	wchar_t BreakStatus[2];			//"Y" "N" "X" 
	wchar_t BreakName[32];			//Prayer, etc...
	char RFID_tag[12];			//operator login
	int shift;

	//station ....
	double piece_rate;
	double efficiency;
	int total_pieces;
	double total_pay;
	char pay_cat[3];

	//station status
	//required for INFEED and OUTFEED
	//int stn_status;		//H-HALF, F-FULL, X-NULL, L-LOCK
	//stn_status_OK, stn_status_PRAYER, stn_status_TEABREAK, stn_status_REPAIR,
	bool loggedIn;
	bool assigned;
	bool loadingStation;
	bool xhalfload;
	bool xfullload;
	bool OutFeedReady;
	bool OutFeedBusy;
	bool alive;
	bool FireOutFeed;
	int HangerReadCounter;
	int OutFeedCMDID;

	int bundle_CMDID;
	bool bundle_Flag;       //gostn
	bool bundle_Flag1;        //movestn
	bool bundle_Flag2;           //QCstn
	bool bundle_Flag3;           //oprefunction
	bool bundle_Flag4;           //88

	int destStn;

	bool offlineState;
	wchar_t ipaddress[20];
	//char spare[23];
	char spare[64];

}StationOpType;




typedef struct{
	char Idstring[3];
	int versionMajor;
	int versionMinor;
	char spare[64];
	int reccount;
	char endheaderCheckId[3];
}StationOpFileHeaderType;

#define max_STATIONOPERATOR		4096

//using namespace System;

class StationOperatorClass{
private:
	bool storeLock;
	StationOpType	StationOp[max_STATIONOPERATOR];
	StationOpFileHeaderType	StationOpFileHeader;
	int count;
	wctString *filepath;
	wctString *filepathname;
public:
	StationOperatorClass(const wchar_t *path);
	~StationOperatorClass();
	const wchar_t *wgetfile_Name();
	const char *cgetfile_Name();
    int getcount() {return count;}
	int getLastStationNumber() {return count-1;}
	void Clear();
	void loggedIn(int index, bool state, bool flush=1);
	void setMax_Number_of_Stations(int stations) {count = stations; writeDat();}
	void setxHalfLoad(int index, bool state, bool flush=1);
	void setxFullLoad(int index, bool state, bool flush=1);
	void setloggedIn(int index, bool state, bool flush=1);
	void setFireOutFeed(int index, bool state, bool flush=1);

	bool StationValid(int stn_id)	
	{
		return ((stn_id>0)&&(stn_id<=getLastStationNumber()));
	}

	bool StationOutOfRange(int stn_id)	{return !StationValid(stn_id);}

	void setloggedInMsg(int index, STRINGPTR name, bool flush=1);
	void setStationAssigned(int index, bool state, bool flush=1);
	void setStationAsLoadingStation(int index, bool state, bool flush=1);
	void setEMPFname(int index, STRINGPTR name, bool flush=1);
	void setCurOpCode(int index, STRINGPTR name, bool flush=1);
	void setIn_Status(int index, STRINGPTR name, bool flush=1);
	//void setIn_Status(STRINGPTR stn, STRINGPTR name, bool flush=1);
	void setIn_Status(STRINGPTR CurOpCode, STRINGPTR CurdesignCode, STRINGPTR name, bool flush=1);
	void OutFeedUnFire(int index, bool flush=1);
	
	void setStationIPaddress(int index, STRINGPTR ipaddress, bool flush=1);
	void setOutFeedHangerID(int index, STRINGPTR HangerID, bool flush=1);
	void setOutFeedReady(int index, bool ready, bool flush=1);
	void setOutFeedBusy(int index, bool ready, bool flush=1);
	void setAlive(int index, bool ready, bool flush=1);
    void setShift(int index, int value, bool flush=1);

	void setOutFeedCMDID(int index, int cmdid, bool flush=1);
    void set_CMDID(int index, int value, bool flush=1);
    void setGoStn(int index, bool value, bool flush=1);
    void setMoveStn(int index, bool value, bool flush=1);
    void setQCStn(int index, bool value, bool flush=1);
    void setOprefunction(int index, bool value, bool flush=1);
    void setofflineState(int index, bool value, bool flush=1);
	void set88Stn(int index, bool value, bool flush=1);

	void setDestinationStation(int index, int value, bool flush=1);

    void setStationStatus(int index, STRINGPTR name, bool flush=1);
	void setBreakStatus(int index, STRINGPTR name, bool flush=1);
	void setBreakName(int index, STRINGPTR name, bool flush=1);


    void setProdLine(int index, STRINGPTR name, bool flush=1);
    void setoperator_ID(int index, STRINGPTR name, bool flush=1);
    void setEMPLname(int index, STRINGPTR name, bool flush=1);
    void setLEDName(int index, STRINGPTR name, bool flush=1);
    void setEMPID(int index, STRINGPTR name, bool flush=1);
    void setCurdesignCode(int index, STRINGPTR name, bool flush=1);
    void setLastBundleID(int index, STRINGPTR name, bool flush=1);

	void ClearHangerReadCounter(int index, bool flush=1);
	void IncrementHangerReadCounter(int index, bool flush=1);
    int getHangerReadCounter(int index);
    int getOutFeedCMDID(int index);
	



	STRINGPTR getFireOutFeed(int index);
	STRINGPTR getxFullLoad(int index);
	STRINGPTR getxHalfLoad(int index);
	STRINGPTR getloggedIn(int index);
	STRINGPTR getLoadingStation(int index);

	STRINGPTR getGoStn(int index);
	STRINGPTR getMoveStn(int index);
	STRINGPTR getQCStn(int index);
	STRINGPTR getOprefunction(int index);

	bool isFireOutFeed(int index);
    bool isloggedIn(int index);
    bool isStationAssigned(int index);
    bool isLoadingStation(int index);
    bool isxFullLoad(int index);
    bool isxHalfLoad(int index);
	bool isofflineState(int index);
	bool isOutFeedReady(int index);
	bool isOutFeedBusy(int index);
	bool isOutAlive(int index);
	int getShift(int index);
	STRINGPTR getStationStatus(int index);
	STRINGPTR getBreakStatus(int index);
	STRINGPTR getBreakName(int index);

    int get_CMDID(int index);
	bool isGoStn(int index);
	bool isMoveStn(int index);
	bool isQCStn(int index);
 	bool isOprefunction(int index);
	bool is88Stn(int index);

	STRINGPTR getStationIPaddress(int index);
	STRINGPTR getOutFeedHangerID(int index);
	STRINGPTR getEMPFname(int index);
	STRINGPTR getCurOpCode(int index);
	STRINGPTR getIn_Status(int index);
	STRINGPTR getProdLine(int index);
    STRINGPTR getoperator_ID(int index);
    STRINGPTR getEMPLname(int index);
    STRINGPTR getLEDName(int index);
    STRINGPTR getEMPID(int index);
    STRINGPTR getCurdesignCode(int index);
    STRINGPTR getLastBundleID(int index);

	void cancelFindQCStn(int index);
	void cancelMoveStn(int index);
	void cancelGoStn(int index);
	void cancelOprefunction(int index);
	void cancel88Stn(int index);

	void flush() {writeDat();}
	//void LoadHanger(String^ ID, String^ HangerID, bool flush=1);
	//void unLoadHanger(String^ ID, bool flush=1);
	//String^ getHangerID(String^ ID);
	void writeDat();
	void readDat();
private:
	bool validArray(int index);

};

#endif
