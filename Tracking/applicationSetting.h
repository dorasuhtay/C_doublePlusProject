#ifndef  _applicationSetting___H
#define  _applicationSetting___H

#include "wctString.h"
#include "class_childWindow.h"
/*
typedef struct{
	int X;
	int Y;
	int W;
	int H;
	int Opened;
	char name[32];
}childWindowType;
*/
typedef struct{
	int mNumberof_CHAIN_LINKS;
	int mMax_Number_of_PUSHER;
	int mNumberof_CHAIN_LINKS_STOP_compensation;
	int mCHAIN_LINKS_STOP_number;
	int mPusher_millsec_interval;
	//int UpdateNetworkDateTime_period;
	//int mMax_Number_of_STATIONS;
	char mPusher_port_Name[12];	//		"COM2\0"
	char mstationNetwork_Name[12];		//		"COM1\0"
	int mstationNetwork_Baud;
	int mstationNetwork_WriteBufferSize;
	char mdate_FormatKEYPAD[16];		//"yy-MM-dd";
	char serialComm_pusherlogFile[512];
	char serialComm_StationlogFile[512];
	char serialMsg_StationlogFile[512];
	char serverLogfileFolder[512];
	char DefIPAddress[64];
	int maxBunNo;
	char app_startupMode[32];				// startup as visible, or not visible

	int motor_on_delay;
	int noSerialEventTimeOut;

	int updateDataTimeSecond;				//second interval to send Date and Time command to updae all station's Date and Time
	int offlinepollseconds;					//second interval to send offline command to check station status (offline)
	int requesthelpseconds;					//second interval to check and display Station help request.
	int flushserialcommlogfileSeconds;		//second interval to flush to disk the serial comm log file (if log file is enabled).
	int OverLoadMaxRounds;					//the maximum rounds (count) around overhead pusher before going to overload or QC station

	int networkStatus_MaxAging;

	//int InpectionstationNo;
	//int BridgeStnNo;

	int AlwaysHide;

	int commandportnumber;
	int nwportnumber;
	int detailseqportnumber;
	char testoption[32];

	int ACK_handshake_enable;
	int ACK_NAK_DirectWrite_enable;
	int TxFifo_enable;

	int NewFeatureReleaseLevel;
	char ProdLineName[32];
	char MRT_hostnameServer[512];			//"192.168.2.70"
	char MRT_hostnameServerName[512];			//"ONLINEBTREKDB"
	int StandaloneMode;

	char DataServer_local_IPaddress[64];			//"127.0.0.1"
	char DataServer_local_Name[64];					//"CLIENTDB"
	char DataServer_Master_IPaddress[64];			//"127.0.0.1"
	char DataServer_Master_Name[64];				//"ONLINEBTREKDB"

	int serverID_NETWORKCONTROL_PORT;	
	int TCPserverBasePort;					//base port number

	int ShowInspectionPopup;
	int sendInspection2GUI;

	int txfifosize;
	int txLockSleepMillsec;
	int txthreadSleepMillsec;

	int reminderMessageCount;

	int updateremoteDBbmethod;

	float playbackdelayfactor;

	char recordplaybackfilename[1024];

	char GUIshellcommandFolder[1024];	// = "C:\\Users\\X3990\\Desktop\\client\\"
	char GUIshellcommandProgram[128];	// = "Online_Client.jar"

	childWindowType	NetworkSerialInMessageView;
	childWindowType	OperationDebugView;
	childWindowType	OverheaderPusherView;
	childWindowType	DetailSequencingView;
	childWindowType	setupInformationView;
	childWindowType	form_appPlayBackView;
	childWindowType	stationTableView;
	childWindowType	form_testFireRelayView;

}applicationSettingType;


class applicationSettingClass{
	private:
	//char inifile[1024];
	int dirty;
	wctString *filepath;
	wctString *filepathname;
public:
	applicationSettingType	data;
	applicationSettingClass(const wchar_t *path);
	~applicationSettingClass();
	const wchar_t *wgetfile_Name();
	const char *cgetfile_Name();
	void InitConfigINI();
	void LoadConfigINI();
	void SaveConfigINI();
	const char *getINIfile() {if (filepathname) return filepathname->cdata();else return "";}
	int isDirty() {return dirty;}
	void setDirty() {dirty++;}
	//void ChildWindowClosing(childWindowType *chldWndw, int X, int Y);
	//void ChildWindowResizeEnd(childWindowType *chldWndw, int Width,  int Height);
	//int ChildWindowGetLocation(childWindowType *chldWndw, int *X,  int *Y);
	//int ChildWindowGetSize(childWindowType *chldWndw, int *W,  int *H);
};
//extern applicationSettingType	application_Setting;

/*
extern int ChildWindowGetSize(childWindowType *chldWndw, int *W,  int *H);
extern int ChildWindowGetLocation(childWindowType *chldWndw, int *X,  int *Y);
extern void ChildWindowClosing(childWindowType *chldWndw, int X, int Y);
extern void ChildWindowResizeEnd(childWindowType *chldWndw, int Width,  int Height);
*/
#endif