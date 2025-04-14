#include "StdAfx.h"
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include "applicationSetting.h"
#include "iniprofile.h"
#include "online_setup.h"
//#include "applicationdefine.h"
#include "xplatform_define.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#define cfile_Name		"applicationSetting.ini\0"

const wchar_t *applicationSettingClass::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
const char    *applicationSettingClass::cgetfile_Name(){if (filepathname) return (char *)filepathname->cdata(); else return cfile_Name;}

applicationSettingClass::applicationSettingClass(const wchar_t *path)
{
	filepath  = new wctString(path);
	filepathname  = new wctString(path);
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));

	//STRCPY(inifile, filepathname->cdata());
	dirty = 0;
}

applicationSettingClass::~applicationSettingClass()
{
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

void applicationSettingClass::InitConfigINI()
{
	memset(&data, 0x0, sizeof(applicationSettingType));
	data.mNumberof_CHAIN_LINKS = NumberofCHAINLINKS__;
	data.mMax_Number_of_PUSHER = Max_NumberofPUSHER__;
	data.mNumberof_CHAIN_LINKS_STOP_compensation = Numberof_CHAIN_LINKS_STOPcompensation__;
	data.mCHAIN_LINKS_STOP_number = CHAIN_LINKS_STOPnumber__;
	data.mPusher_millsec_interval = Pusher_millsec_interval__;
	//data.mMax_Number_of_STATIONS = Max_NumberofSTATIONS__;
	data.maxBunNo = MaxBundleNo__;
	data.OverLoadMaxRounds = MAX_OVERLOAD_ROUNDS__;

	data.networkStatus_MaxAging = 60;		//60 seconds

	data.updateDataTimeSecond = UPDATENETWORKDATETIME_period;
	data.offlinepollseconds = OFFLINEPOLLSECONDS_Period;
	data.requesthelpseconds = REQUESTHELPSECONDS_Period;
	data.flushserialcommlogfileSeconds = FLUSHSERIALCOMMLOGFILESECONDS_Period;

	data.motor_on_delay = 8;
	data.noSerialEventTimeOut = 800;
	

	//data.InpectionstationNo = 0;
	//data.BridgeStnNo = 0;

	data.AlwaysHide = 0;
	
	data.serverID_NETWORKCONTROL_PORT = 13000;
	data.TCPserverBasePort = 7100;
	
	int portn = 7000;
	data.commandportnumber = portn;		portn++;
	data.nwportnumber = portn;			portn++;
	data.detailseqportnumber = portn;	portn++;


	data.NewFeatureReleaseLevel = 255;		//release and make available all new features that are under test and debug

	data.ACK_handshake_enable = 0;
	data.ACK_NAK_DirectWrite_enable = 1;
	data.TxFifo_enable = 1;

	data.ShowInspectionPopup = 1;
	data.sendInspection2GUI = 1;
	data.StandaloneMode = 1;

	data.playbackdelayfactor = 0.075;

	data.reminderMessageCount = 6;

	data.txfifosize = 1024;

	data.txLockSleepMillsec = 10;
	data.txthreadSleepMillsec = 10;

	data.updateremoteDBbmethod = 0;

	


	memset(&data.NetworkSerialInMessageView, 0x0, sizeof(childWindowType));
	STRCPY(data.NetworkSerialInMessageView.name, "NetworkSerialInMessageView");
	memset(&data.OperationDebugView, 0x0, sizeof(childWindowType));
	STRCPY(data.OperationDebugView.name, "OperationDebugView");
	memset(&data.OverheaderPusherView, 0x0, sizeof(childWindowType));
	STRCPY(data.OverheaderPusherView.name, "OverheaderPusherView");	
	memset(&data.DetailSequencingView, 0x0, sizeof(childWindowType));
	STRCPY(data.DetailSequencingView.name, "DetailSequencingView");	
	memset(&data.setupInformationView, 0x0, sizeof(childWindowType));
	STRCPY(data.setupInformationView.name, "setupInformationView");	
	memset(&data.form_appPlayBackView, 0x0, sizeof(childWindowType));
	STRCPY(data.form_appPlayBackView.name, "form_appPlayBackView");	
	memset(&data.stationTableView, 0x0, sizeof(childWindowType));
	STRCPY(data.stationTableView.name, "stationTableView");	
	memset(&data.form_testFireRelayView, 0x0, sizeof(childWindowType));
	STRCPY(data.form_testFireRelayView.name, "form_testFireRelayView");	
	
	
	
	
	

	STRCPY(data.DefIPAddress, "127.0.0.1");
	//STRCPY(data.serverLogfileFolder, "d:\\Serverfile\\");
	
	STRCPY(data.MRT_hostnameServer, "");
	STRCPY(data.MRT_hostnameServerName, "ONLINEBTREKDB");
	STRCPY(data.DataServer_local_IPaddress, "127.0.0.1");
	STRCPY(data.DataServer_local_Name, "CLIENTDB");
	STRCPY(data.DataServer_Master_IPaddress, "127.0.0.1");
	STRCPY(data.DataServer_Master_Name, "ONLINEBTREKDB");


	
	STRCPY(data.ProdLineName, "---");
	
	STRCPY(data.serialComm_pusherlogFile, "serialPusherCOM.log");
	STRCPY(data.serialComm_StationlogFile, "serialStationCOM.log");
	STRCPY(data.serialMsg_StationlogFile, "serialStationMsg.log");
	
	STRCPY(data.app_startupMode, "VISIBLE");
	STRCPY(data.testoption, "MEM_INFEED");
	STRCPY(data.recordplaybackfilename, "");

	//STRCPY(data.GUIshellcommandFolder, "C:\\Users\\X3990\\Desktop\\client\\");
	//STRCPY(data.GUIshellcommandProgram, "Online_Client.jar");
	STRCPY(data.GUIshellcommandFolder, "C:\\Program Files (x86)\\SMC\\MRT-ONLINE\\dist");
	STRCPY(data.GUIshellcommandProgram, "run.bat");

	//data.testoption,"MEM_INFEED"
	
	
	STRCPY(data.mPusher_port_Name, PUSHER_port_Name);
	STRCPY(data.mstationNetwork_Name, STATIONNetwork_Name);
	data.mstationNetwork_Baud = 38400;
	data.mstationNetwork_WriteBufferSize = 2048;
	STRCPY(data.mdate_FormatKEYPAD, DATE_FormatKEYPAD);
}
  
		//-------------------------------------------


void getINIchildWindowValues(pIniFile *ini, childWindowType *chldWndw)
{
	if (!ini) return;
	chldWndw->X = ini->getInt(chldWndw->name, "X", chldWndw->X);
	chldWndw->Y = ini->getInt(chldWndw->name, "Y", chldWndw->Y);
	chldWndw->W = ini->getInt(chldWndw->name, "W", chldWndw->W);
	chldWndw->H = ini->getInt(chldWndw->name, "H", chldWndw->H);
	chldWndw->Opened = ini->getInt(chldWndw->name, "Opened", chldWndw->Opened);
}

void setINIchildWindowValues(pIniFile *ini, childWindowType *chldWndw)
{
	if (!ini) return;
	ini->setInt(chldWndw->name, "X", chldWndw->X);
	ini->setInt(chldWndw->name, "Y", chldWndw->Y);
	ini->setInt(chldWndw->name, "W", chldWndw->W);
	ini->setInt(chldWndw->name, "H", chldWndw->H);
	ini->setInt(chldWndw->name, "Opened", chldWndw->Opened);
}



void applicationSettingClass::LoadConfigINI()
{
	pIniFile *ini = new pIniFile(); 
	if (ini){
		ini->read(filepathname->cdata());
		data.mNumberof_CHAIN_LINKS = ini->getInt("Setting Option", "Numberof_CHAIN_LINKS", data.mNumberof_CHAIN_LINKS);
		data.mMax_Number_of_PUSHER = ini->getInt("Setting Option", "Max_Number_of_PUSHER", data.mMax_Number_of_PUSHER);
		data.mNumberof_CHAIN_LINKS_STOP_compensation = ini->getInt("Setting Option", "Numberof_CHAIN_LINKS_STOP_compensation", data.mNumberof_CHAIN_LINKS_STOP_compensation);
		data.mCHAIN_LINKS_STOP_number = ini->getInt("Setting Option", "CHAIN_LINKS_STOP_number", data.mCHAIN_LINKS_STOP_number);
		data.mPusher_millsec_interval = ini->getInt("Setting Option", "Pusher_millsec_interval", data.mPusher_millsec_interval);

		
		//data.UpdateNetworkDateTime_period = ini->getInt("Setting Option", "UpdateNetworkDateTime_period", data.UpdateNetworkDateTime_period);
		//data.mMax_Number_of_STATIONS = ini->getInt("Setting Option", "Max_Number_of_STATIONS", data.mMax_Number_of_STATIONS);
		data.maxBunNo = ini->getInt("Setting Option", "maxBunNo", data.maxBunNo);
		
		data.noSerialEventTimeOut = ini->getInt("Setting Option", "noSerialEventTimeOut", data.noSerialEventTimeOut);
		data.motor_on_delay = ini->getInt("Setting Option", "motor_on_delay", data.motor_on_delay);
		data.updateDataTimeSecond = ini->getInt("Setting Option", "updateDataTimeSecond", data.updateDataTimeSecond);
		data.offlinepollseconds = ini->getInt("Setting Option", "offlinepollseconds", data.offlinepollseconds);
		data.requesthelpseconds = ini->getInt("Setting Option", "requesthelpseconds", data.requesthelpseconds);
		data.flushserialcommlogfileSeconds = ini->getInt("Setting Option", "flushserialcommlogfileSeconds", data.flushserialcommlogfileSeconds);
		
		//data.flushserialcommlogfileSeconds = ini->getInt("Setting Option", "flushserialcommlogfileSecond", data.flushserialcommlogfileSecond);
		
		
		
		
		data.OverLoadMaxRounds = ini->getInt("Setting Option", "OverLoadMaxRounds", data.OverLoadMaxRounds);
		data.networkStatus_MaxAging = ini->getInt("Setting Option", "networkStatus_MaxAging", data.networkStatus_MaxAging);
		

		data.serverID_NETWORKCONTROL_PORT = ini->getInt("Setting Option", "serverID_NETWORKCONTROL_PORT", data.serverID_NETWORKCONTROL_PORT);
		data.TCPserverBasePort = ini->getInt("Setting Option", "TCPserverBasePort", data.TCPserverBasePort);
		data.commandportnumber = ini->getInt("Setting Option", "commandportnumber", data.commandportnumber);
		data.nwportnumber = ini->getInt("Setting Option", "nwportnumber", data.nwportnumber);
		data.detailseqportnumber = ini->getInt("Setting Option", "detailseqportnumber", data.detailseqportnumber);

		//data.InpectionstationNo = ini->getInt("Setting Option", "InpectionstationNo", data.InpectionstationNo);
		//data.BridgeStnNo = ini->getInt("Setting Option", "BridgeStnNo", data.BridgeStnNo);	
		data.AlwaysHide = ini->getInt("Setting Option", "AlwaysHide", data.AlwaysHide);
		

		data.NewFeatureReleaseLevel = ini->getInt("Setting Option", "NewFeatureReleaseLevel", data.NewFeatureReleaseLevel);	
		data.ACK_handshake_enable = ini->getInt("Setting Option", "ACK_handshake_enable", data.ACK_handshake_enable);
		data.ACK_NAK_DirectWrite_enable = ini->getInt("Setting Option", "ACK_NAK_DirectWrite_enable", data.ACK_NAK_DirectWrite_enable);	
		
		data.TxFifo_enable = ini->getInt("Setting Option", "TxFifo_enable", data.TxFifo_enable);
		
		
		
		data.ShowInspectionPopup = ini->getInt("Setting Option", "ShowInspectionPopup", data.ShowInspectionPopup);
		data.sendInspection2GUI = ini->getInt("Setting Option", "sendInspection2GUI", data.sendInspection2GUI);
		data.StandaloneMode = ini->getInt("Setting Option", "StandaloneMode", data.StandaloneMode);

		data.reminderMessageCount = ini->getInt("Setting Option", "reminderMessageCount", data.reminderMessageCount);
		data.updateremoteDBbmethod = ini->getInt("Setting Option", "updateremoteDBbmethod", data.updateremoteDBbmethod);
		data.txfifosize = ini->getInt("Setting Option", "txfifosize", data.txfifosize);
		data.txLockSleepMillsec = ini->getInt("Setting Option", "txLockSleepMillsec", data.txLockSleepMillsec);
		data.txthreadSleepMillsec = ini->getInt("Setting Option", "txthreadSleepMillsec", data.txthreadSleepMillsec);

		data.mstationNetwork_Baud = ini->getInt("Setting Option", "mstationNetwork_Baud", data.mstationNetwork_Baud);
		data.mstationNetwork_WriteBufferSize = ini->getInt("Setting Option", "mstationNetwork_WriteBufferSize", data.mstationNetwork_WriteBufferSize);
		
		
				
		data.playbackdelayfactor = (float)ini->getdouble("PlayBackOption", "playbackdelayfactor", "%12.5f", (double)data.playbackdelayfactor);
		
		
		

		getINIchildWindowValues(ini, &data.NetworkSerialInMessageView);
		getINIchildWindowValues(ini, &data.OperationDebugView);
		getINIchildWindowValues(ini, &data.OverheaderPusherView);
		getINIchildWindowValues(ini, &data.DetailSequencingView);
		getINIchildWindowValues(ini, &data.setupInformationView);
		getINIchildWindowValues(ini, &data.form_appPlayBackView);
		getINIchildWindowValues(ini, &data.stationTableView);
		getINIchildWindowValues(ini, &data.form_testFireRelayView);
		
		
		
		
		

		ini->getText("Setting Option", "testoption", data.testoption, sizeof(data.testoption), data.testoption);
		ini->getText("Setting Option", "recordplaybackfilename", data.recordplaybackfilename, sizeof(data.recordplaybackfilename), data.recordplaybackfilename);
		ini->getText("Setting Option", "GUIshellcommandFolder", data.GUIshellcommandFolder, sizeof(data.GUIshellcommandFolder), data.GUIshellcommandFolder);
		ini->getText("Setting Option", "GUIshellcommandProgram", data.GUIshellcommandProgram, sizeof(data.GUIshellcommandProgram), data.GUIshellcommandProgram);
		//ini->getText("Setting Option", "serverLogfileFolder", data.serverLogfileFolder, sizeof(data.serverLogfileFolder), data.serverLogfileFolder);

		
		ini->getText("Setting Option", "app_startupMode", data.app_startupMode, sizeof(data.app_startupMode), data.app_startupMode);
		ini->getText("Setting Option", "DefIPAddress", data.DefIPAddress, sizeof(data.DefIPAddress), data.DefIPAddress);
		ini->getText("Setting Option", "serverLogfileFolder", data.serverLogfileFolder, sizeof(data.serverLogfileFolder), data.serverLogfileFolder);
		ini->getText("Setting Option", "MRT_hostnameServer", data.MRT_hostnameServer, sizeof(data.MRT_hostnameServer), data.MRT_hostnameServer);
		ini->getText("Setting Option", "MRT_hostnameServerName", data.MRT_hostnameServerName, sizeof(data.MRT_hostnameServerName), data.MRT_hostnameServerName);

		ini->getText("Setting Option", "DataServer_local_IPaddress", data.DataServer_local_IPaddress, sizeof(data.DataServer_local_IPaddress), data.DataServer_local_IPaddress);
		ini->getText("Setting Option", "DataServer_local_Name", data.DataServer_local_Name, sizeof(data.DataServer_local_Name), data.DataServer_local_Name);
		ini->getText("Setting Option", "DataServer_Master_IPaddress", data.DataServer_Master_IPaddress, sizeof(data.DataServer_Master_IPaddress), data.DataServer_local_IPaddress);
		ini->getText("Setting Option", "DataServer_Master_Name", data.DataServer_Master_Name, sizeof(data.DataServer_Master_Name), data.DataServer_Master_Name);

		ini->getText("Setting Option", "ProdLineName", data.ProdLineName, sizeof(data.ProdLineName), data.ProdLineName);

		
		ini->getText("Setting Option", "serialComm_pusherlogFile", data.serialComm_pusherlogFile, sizeof(data.serialComm_pusherlogFile), data.serialComm_pusherlogFile);
		ini->getText("Setting Option", "serialComm_StationlogFile", data.serialComm_StationlogFile, sizeof(data.serialComm_StationlogFile), data.serialComm_StationlogFile);
		ini->getText("Setting Option", "serialMsg_StationlogFile", data.serialMsg_StationlogFile, sizeof(data.serialMsg_StationlogFile), data.serialMsg_StationlogFile);

		ini->getText("Setting Option", "Pusher_port_Name", data.mPusher_port_Name, sizeof(data.mPusher_port_Name), data.mPusher_port_Name);
		ini->getText("Setting Option", "stationNetwork_Name", data.mstationNetwork_Name, sizeof(data.mstationNetwork_Name), data.mstationNetwork_Name);
		ini->getText("Setting Option", "date_FormatKEYPAD", data.mdate_FormatKEYPAD, sizeof(data.mdate_FormatKEYPAD), data.mdate_FormatKEYPAD);

  		
		
		delete ini;
		strupr(data.mPusher_port_Name);
		strupr(data.mstationNetwork_Name);
		dirty = 0;
		}

	int length = strlen(data.serverLogfileFolder);
	if(data.serverLogfileFolder[length-1]!='\\')
		strcat_s(data.serverLogfileFolder, "\\");
}


void applicationSettingClass::SaveConfigINI()
{
	pIniFile *ini = new pIniFile();
	if (ini){
		ini->read(filepathname->cdata());

		ini->setInt("Setting Option", "Numberof_CHAIN_LINKS", data.mNumberof_CHAIN_LINKS);
		ini->setInt("Setting Option", "Max_Number_of_PUSHER", data.mMax_Number_of_PUSHER);
		ini->setInt("Setting Option", "Numberof_CHAIN_LINKS_STOP_compensation", data.mNumberof_CHAIN_LINKS_STOP_compensation);
		ini->setInt("Setting Option", "CHAIN_LINKS_STOP_number", data.mCHAIN_LINKS_STOP_number);
		ini->setInt("Setting Option", "Pusher_millsec_interval", data.mPusher_millsec_interval);
		
		//ini->setInt("Setting Option", "UpdateNetworkDateTime_period", data.UpdateNetworkDateTime_period);
		//ini->setInt("Setting Option", "Max_Number_of_STATIONS", data.mMax_Number_of_STATIONS);
		ini->setInt("Setting Option", "maxBunNo", data.maxBunNo);
		

		
		ini->setInt("Setting Option", "noSerialEventTimeOut", data.noSerialEventTimeOut);
		ini->setInt("Setting Option", "motor_on_delay", data.motor_on_delay);
		ini->setInt("Setting Option", "updateDataTimeSecond", data.updateDataTimeSecond);
		ini->setInt("Setting Option", "offlinepollseconds", data.offlinepollseconds);
		ini->setInt("Setting Option", "requesthelpseconds", data.requesthelpseconds);
		ini->setInt("Setting Option", "flushserialcommlogfileSeconds", data.flushserialcommlogfileSeconds);
		
		
		ini->setInt("Setting Option", "OverLoadMaxRounds", data.OverLoadMaxRounds);
		ini->setInt("Setting Option", "networkStatus_MaxAging", data.networkStatus_MaxAging);
		
		ini->setInt("Setting Option", "serverID_NETWORKCONTROL_PORT", data.serverID_NETWORKCONTROL_PORT);
		ini->setInt("Setting Option", "TCPserverBasePort", data.TCPserverBasePort);

		ini->setInt("Setting Option", "commandportnumber", data.commandportnumber);
		ini->setInt("Setting Option", "nwportnumber", data.nwportnumber);
		ini->setInt("Setting Option", "detailseqportnumber", data.detailseqportnumber);

		//ini->setInt("Setting Option", "InpectionstationNo", data.InpectionstationNo);
		//ini->setInt("Setting Option", "BridgeStnNo", data.BridgeStnNo);
		ini->setInt("Setting Option", "AlwaysHide", data.AlwaysHide);
		

		ini->setInt("Setting Option", "NewFeatureReleaseLevel", data.NewFeatureReleaseLevel);
		ini->setInt("Setting Option", "ACK_handshake_enable", data.ACK_handshake_enable);
		ini->setInt("Setting Option", "ACK_NAK_DirectWrite_enable", data.ACK_NAK_DirectWrite_enable);
		ini->setInt("Setting Option", "TxFifo_enable", data.TxFifo_enable);

		
		
		
		
		ini->setInt("Setting Option", "ShowInspectionPopup", data.ShowInspectionPopup);
		ini->setInt("Setting Option", "sendInspection2GUI", data.sendInspection2GUI);
		ini->setInt("Setting Option", "StandaloneMode", data.StandaloneMode);
		
		
		ini->setInt("Setting Option", "reminderMessageCount", data.reminderMessageCount);
		ini->setInt("Setting Option", "updateremoteDBbmethod", data.updateremoteDBbmethod);
		ini->setInt("Setting Option", "txfifosize", data.txfifosize);

		ini->setInt("Setting Option", "txLockSleepMillsec", data.txLockSleepMillsec);
		ini->setInt("Setting Option", "txthreadSleepMillsec", data.txthreadSleepMillsec);


		ini->setInt("Setting Option", "mstationNetwork_Baud", data.mstationNetwork_Baud);
		ini->setInt("Setting Option", "mstationNetwork_WriteBufferSize", data.mstationNetwork_WriteBufferSize);
		

		
		
		
		
		setINIchildWindowValues(ini, &data.NetworkSerialInMessageView);
		setINIchildWindowValues(ini, &data.OperationDebugView);
		setINIchildWindowValues(ini, &data.OverheaderPusherView);
		setINIchildWindowValues(ini, &data.DetailSequencingView);
		setINIchildWindowValues(ini, &data.setupInformationView);
		setINIchildWindowValues(ini, &data.form_appPlayBackView);
		setINIchildWindowValues(ini, &data.stationTableView);
		setINIchildWindowValues(ini, &data.form_testFireRelayView);
		
		
		
		
		


		ini->setText("Setting Option", "testoption", data.testoption);
		ini->setText("Setting Option", "recordplaybackfilename", data.recordplaybackfilename);

		ini->setText("Setting Option", "GUIshellcommandFolder", data.GUIshellcommandFolder);
		ini->setText("Setting Option", "GUIshellcommandProgram", data.GUIshellcommandProgram);
		
		ini->setText("Setting Option", "app_startupMode", data.app_startupMode);
		ini->setText("Setting Option", "DefIPAddress", data.DefIPAddress);
		ini->setText("Setting Option", "serverLogfileFolder", data.serverLogfileFolder);
		ini->setText("Setting Option", "MRT_hostnameServer", data.MRT_hostnameServer);
		ini->setText("Setting Option", "MRT_hostnameServerName", data.MRT_hostnameServerName);

		ini->setText("Setting Option", "DataServer_local_IPaddress", data.DataServer_local_IPaddress);
		ini->setText("Setting Option", "DataServer_local_Name", data.DataServer_local_Name);
		ini->setText("Setting Option", "DataServer_Master_IPaddress", data.DataServer_Master_IPaddress);
		ini->setText("Setting Option", "DataServer_Master_Name", data.DataServer_Master_Name);

		ini->setText("Setting Option", "ProdLineName", data.ProdLineName);

		
		ini->setText("Setting Option", "serialComm_pusherlogFile", data.serialComm_pusherlogFile);
		ini->setText("Setting Option", "serialComm_StationlogFile", data.serialComm_StationlogFile);
		ini->setText("Setting Option", "serialMsg_StationlogFile", data.serialMsg_StationlogFile);
	
		
		ini->setText("Setting Option", "Pusher_port_Name", data.mPusher_port_Name);
		ini->setText("Setting Option", "stationNetwork_Name", data.mstationNetwork_Name);
		ini->setText("Setting Option", "date_FormatKEYPAD", data.mdate_FormatKEYPAD);


		ini->setdouble("PlayBackOption", "playbackdelayfactor", "%12.5f", (double)data.playbackdelayfactor);



		ini->write(filepathname->cdata());

		dirty = 0;
	
		delete ini;
		}
}

/*
void ChildWindowClosing(childWindowType *chldWndw, int X, int Y)
{
	chldWndw->X = X;
	chldWndw->Y = Y;
	//SaveConfigINI();
}
			
void ChildWindowResizeEnd(childWindowType *chldWndw, int Width,  int Height)
{
	chldWndw->W = Width;
	chldWndw->H = Height;
	//SaveConfigINI();
}

int ChildWindowGetLocation(childWindowType *chldWndw, int *X,  int *Y)
{
	if ((chldWndw->X>0)&&(chldWndw->Y>0))
	{
		*X = chldWndw->X;
		*Y = chldWndw->Y;
		return 1;
	}
	return 0;
}
int ChildWindowGetSize(childWindowType *chldWndw, int *W,  int *H)
{
	if ((chldWndw->W>40)&&(chldWndw->H>40))
	{
		*W = chldWndw->W;
		*H = chldWndw->H;
		return 1;
	}
	return 0;
}
*/