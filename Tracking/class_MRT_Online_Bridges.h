

//class_MRT_Online_Bridges.h

#ifndef __class_MRT_Online_Bridges__h
#define __class_MRT_Online_Bridges__h

#include "xplatform_define.h"
#include "wctString.h"


#define stn_status_OK			1000
#define stn_status_PRAYER		1001
#define stn_status_TEABREAK		1002
#define stn_status_REPAIR		1003

#define MAX_bridgename_STRING_SIZE	64
typedef struct{
	wchar_t Type[MAX_bridgename_STRING_SIZE];
	int typeID;
	int bridgeID;
	wchar_t bridgeName[MAX_bridgename_STRING_SIZE];
	wchar_t hostname1[MAX_bridgename_STRING_SIZE];
	wchar_t hostname2[MAX_bridgename_STRING_SIZE];
	int stationID1;
	int stationID2;
	wchar_t Remarks[MAX_bridgename_STRING_SIZE];
	char spare[64];

}MRT_OnlineBridgesType;

typedef struct{
	char Idstring[3];
	int versionMajor;
	int versionMinor;
	char spare[64];
	int reccount;
	char endheaderCheckId[3];
}MRT_OnlineBridgesFileHeaderType;

#define max_MRT_OnlineBridges		1024


class class_MRT_Online_Bridges{
private:
	bool storeLock;
	MRT_OnlineBridgesType	*OnlineBridges[max_MRT_OnlineBridges];
	MRT_OnlineBridgesFileHeaderType	OnlineBridgesFileHeader;
	int count;
	wctString *filepath;
	wctString *filepathname;
public:
	class_MRT_Online_Bridges(const wchar_t *path);
	~class_MRT_Online_Bridges();
	const wchar_t *wgetfile_Name();
	const char *cgetfile_Name();
    int getcount() {return count;}
	void Clear();
	void Add(const wchar_t *Type, const wchar_t *bridgeName, int bridgeID, const wchar_t *hostname1, int stationID1, const wchar_t *hostname2, int stationID2, const wchar_t *Remarks);

	void sethostname1(int index, STRINGPTR name, bool flush=1);
	void sethostname2(int index, STRINGPTR name, bool flush=1);
	void setbridgeName(int index, STRINGPTR name, bool flush=1);
	void setRemarks(int index, STRINGPTR name, bool flush=1);
    void setbridgeID(int index, bool value, bool flush=1);
    void setstationID1(int index, int value, bool flush=1);
    void setstationID2(int index, int value, bool flush=1);


	STRINGPTR gethostname1(int index);
	STRINGPTR gethostname2(int index);
	STRINGPTR getbridgeName(int index);
	STRINGPTR getRemarks(int index);
	STRINGPTR getType(int index);
	

	int getbridgeID(int index);
    int getstationID1(int index);
    int getstationID2(int index);

/*
    STRINGPTR getoperator_ID(int index);
    STRINGPTR getEMPLname(int index);
    STRINGPTR getLEDName(int index);

    int getHangerReadCounter(int index);
    int getOutFeedCMDID(int index);

	STRINGPTR getFireOutFeed(int index);
	STRINGPTR getxFullLoad(int index);
	STRINGPTR getxHalfLoad(int index);
	STRINGPTR getloggedIn(int index);
	STRINGPTR getLoadingStation(int index);*/
/*
	void loggedIn(int index, bool state, bool flush=1);
	//void setMax_Number_of_Stations(int stations) {count = stations; writeDat();}
	void setxHalfLoad(int index, bool state, bool flush=1);
	void setxFullLoad(int index, bool state, bool flush=1);
	void setloggedIn(int index, bool state, bool flush=1);
	void setFireOutFeed(int index, bool state, bool flush=1);



	//void setRemarks(STRINGPTR stn, STRINGPTR name, bool flush=1);
	void setRemarks(STRINGPTR CurOpCode, STRINGPTR CurdesignCode, STRINGPTR name, bool flush=1);
	void OutFeedUnFire(int index, bool flush=1);
	void setOutFeedHangerID(int index, STRINGPTR HangerID, bool flush=1);
	void setOutFeedReady(int index, bool ready, bool flush=1);
	void setOutFeedBusy(int index, bool ready, bool flush=1);
	void setAlive(int index, bool ready, bool flush=1);

	void setOutFeedCMDID(int index, int cmdid, bool flush=1);


    void setMoveStn(int index, bool value, bool flush=1);
    void setQCStn(int index, bool value, bool flush=1);
    void setOprefunction(int index, bool value, bool flush=1);
    void setofflineState(int index, bool value, bool flush=1);


    void setProdLine(int index, STRINGPTR name, bool flush=1);
    void setoperator_ID(int index, STRINGPTR name, bool flush=1);
    void setEMPLname(int index, STRINGPTR name, bool flush=1);
    void setLEDName(int index, STRINGPTR name, bool flush=1);
    void setEMPID(int index, STRINGPTR name, bool flush=1);
    void setCurdesignCode(int index, STRINGPTR name, bool flush=1);
    void setLastBundleID(int index, STRINGPTR name, bool flush=1);

	void ClearHangerReadCounter(int index, bool flush=1);
	void IncrementHangerReadCounter(int index, bool flush=1);
	*/

/*
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

	STRINGPTR getStationStatus(int index);

	bool isGoStn(int index);
	bool isMoveStn(int index);
	bool isQCStn(int index);
 	bool isOprefunction(int index);


	STRINGPTR getOutFeedHangerID(int index);
	STRINGPTR gethostname1(int index);
	STRINGPTR gethostname2(int index);
	STRINGPTR getbridgeName(int index);
	STRINGPTR getRemarks(int index);
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
*/
	void flush() {writeDat();}
	//void LoadHanger(String^ ID, String^ HangerID, bool flush=1);
	//void unLoadHanger(String^ ID, bool flush=1);
	//String^ getHangerID(String^ ID);
	void writeDat();
	void readDat();
private:

};

#endif
