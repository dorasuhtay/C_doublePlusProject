#include <string.h>
#include <windows.h>
#include "serialnetwork_func.h"
#include "logfile_timeStampClass.h"
#include "stringconversion.h"
#include "class_stationMsgFifo.h"
#include "hardware\command.h"
#include "applicationSetting.h"
#include "GlobalVariables.h"

#define MasterID		0x80
#define BroadcastID		0x00
//#define testing_status
enum{
	PRIORITY_EXHIGH = 1,
	PRIORITY_HIGH,
	PRIORITY_INFEED,
	PRIORITY_OUTFEED,
	PRIORITY_FULLHALFSENSOR,
	PRIORITY_COMMS,
	PRIORITY_SETUP_DATETIME,
	PRIORITY_SETUP_FUNC_KEY,
	PRIORITY_SETUP_PIECERATE,
	PRIORITY_SETUP_Totalpay,
	PRIORITY_SETUP_Efficiency,
	PRIORITY_SETUP_Totalpcs,
	PRIORITY_SETUP_paycat,
	PRIORITY_SETUP_OFFLINECMD,
	PRIORITY_SETUP,
	PRIORITY_MISC,
	PRIORITY_LOW,
	PRIORITY_TEST_LOW,
	PRIORITY_EXLOW
};

#define LCDKeypad_beep				true
#define LCDKeypad_nobeep			false
#define LCDKeypad_clearscreen		true
#define LCDKeypad_noclearscreen		false	

#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;
using namespace System::IO::Ports;
using namespace System::Threading;
using namespace System::Text;



#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

typedef struct
{
	serialfifoStatisticsType fifostatistics[4];
	int ACK_flag;
	int NAK_flag;
	int maxACK_flag;
	int maxNAK_flag;
	int ACK_count;
	int NAK_count;
	int priority_FireCounter;
	int sendlastCount;
}NetworkMasterCommsStatisticsType;


#define __USE_DEBUG___ASSERT_NETWORKSTATIONMASTER_ERROR

#ifdef __USE_DEBUG___ASSERT_NETWORKSTATIONMASTER_ERROR
	#define __ASSERT_NETWORKSTATIONMASTER_ERROR(a, b, c, d, e)	\
	{												\
			errorCatch(a, b, c, d, e);			\
	}
#else
#define __ASSERT_NETWORKSTATIONMASTER_ERROR(a, b, c, d, e)	
#endif


namespace BTREKCANDAEMONV1 {

		enum {
			PACKETLENGTH = 1
		};	

	/// <summary>
	/// Summary for NetworkStationMasterClass
	/// </summary>
	public ref class NetworkStationMasterClass :  public System::ComponentModel::Component
	{
	public:
		int noSerialEventTimeOut1;
		bool SeriallockFlag;
		int ACK_flag;
		bool stop_fifo;
		int NAK_flag;
		bool ACK_flagE7,Svr_ACK_flagE7;
		bool ACK_flagServer;
		logfile_timeStampClass *sMsgOutlogfile;
		System::IO::Ports::SerialPort^ sPort;
		NetworkMasterCommsStatisticsType *NetworkMasterCommsStatistics;
		NetworkStationMasterClass(applicationSettingClass *appconfig, String ^appdatapath)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			noSerialEventTimeOut1 = 2500;
			ACK_flagE7=false;
			ACK_flagServer=false;
			Svr_ACK_flagE7=false;
			stop_fifo=false;
			ACK_flag = 1; 
			NAK_flag = 0;
			SeriallockFlag = 0;
			sMsgOutlogfile = 0;
			MsgFifo_1 = 0;
			MsgFifo_2 = 0;
			MsgFifo_3 = 0;
			use_fifo = 1;
			maxACK_flag = 0; 
			maxNAK_flag = 0;
			ACK_NAK_handshake_enable = 0;
			ACK_NAK_DirectWrite_enable = 1;
			blockingCounter = 0;
			sendlast = 0;
			SendMsgPacket2SerialLock = 0;
			appcfg = appconfig;
			blocking = false;
			LockSleepMillsec = 5; //10-->130104
			threadSleepMillsec = 5; //10-->130104

			resend_databuffer = (unsigned char *)malloc(__MSG_stn___MAXSIZE+10);
			resend_datasize = 0;

			NetworkMasterCommsStatistics = new NetworkMasterCommsStatisticsType;
			memset(NetworkMasterCommsStatistics, 0x0, sizeof(NetworkMasterCommsStatisticsType));
			//-----------------------------------------
			//TransmitMsgFIFO
			//-----------------------------------------
			MsgFifo_1 = new class_stationMsgFifo();		
			MsgFifo_1->create(appcfg->data.txfifosize);	
			MsgFifo_2 = new class_stationMsgFifo();		
			MsgFifo_2->create(appcfg->data.txfifosize);	
			MsgFifo_3 = new class_stationMsgFifo();		
			MsgFifo_3->create(appcfg->data.txfifosize);	
			setACK_handshake_enable((appcfg->data.ACK_handshake_enable!=0));
			setACK_NAK_DirectWrite_enable((appcfg->data.ACK_NAK_DirectWrite_enable!=0));
			setTxFifo_enable((appcfg->data.TxFifo_enable!=0));
			setLockSleepMillsec(appcfg->data.txLockSleepMillsec);
			setthreadSleepMillsec(appcfg->data.txthreadSleepMillsec);


			String ^Headerlines = "**********UPSsysNW232 LOG ********** \r\n**********DATE TIME:" + DateTime::Now.ToString() + "**********\r\n";
			String ^logfile = appdatapath + "\\nw232_" + DateTime::Today.ToString("yyyy\M\d") + ".log";
			Log_file = gcnew System::IO::StreamWriter(logfile);
			Log_file->WriteLine(Headerlines);

			ClearSerialTx();
			ClearSerialRx();

			//start the thread
			threadDelegate = gcnew ThreadStart( this, &NetworkStationMasterClass::serialwriteThread);
			swritethread = gcnew Thread(threadDelegate);
			swritethread->Start();

			//start the thread
			threadmsecTimerDelegate = gcnew ThreadStart( this, &NetworkStationMasterClass::millsecThread);
			msecTimerthread = gcnew Thread(threadmsecTimerDelegate);
			msecTimerthread->Start();
		}


		void ClearMsgFifoStatistics()
		{
				MsgFifo_1->clearStatistics();
				MsgFifo_2->clearStatistics();
				MsgFifo_3->clearStatistics();
				maxACK_flag = 0;
				maxNAK_flag = 0;
				
				if (NetworkMasterCommsStatistics)
					memset(NetworkMasterCommsStatistics, 0x0, sizeof(NetworkMasterCommsStatisticsType));
		}

		
		void setTxFifo_enable(bool enable)	{use_fifo = enable;}
		void setACK_handshake_enable(bool enable)	{ACK_NAK_handshake_enable = enable;}
		bool isUserFifo()	{return use_fifo;}
		bool isACK_handshake_enable()	{return ACK_NAK_handshake_enable;}
		bool is_DirectWrite_enable()	{return ACK_NAK_DirectWrite_enable;}
		void setACK_NAK_DirectWrite_enable(bool enable)	{ACK_NAK_DirectWrite_enable = enable;}
		int getmaxACK_flag() {return maxACK_flag;}
		int getmaxNAK_flag() {return maxNAK_flag;} 

		void setLockSleepMillsec(int ms) {LockSleepMillsec = ms;}
		int getLockSleepMillsec(int ms) {return LockSleepMillsec;}
		void setthreadSleepMillsec(int ms) {threadSleepMillsec = ms;}
		int getthreadSleepMillsec(int ms) {return threadSleepMillsec;}
		

		NetworkStationMasterClass(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}

		String^ SendDate(int stn_id, String^  date_Format, int priority)
		{
			String^ szTmp= DateTime::Today.ToString(date_Format)->PadLeft(8,'0 ');
		//	WriteToSerialx(stn_id,DATE_ID,szTmp);//directly send serial
			WriteToSerial(stn_id, DATE_ID, szTmp, priority);
			return szTmp;
		}

		String^ SendTime(int stn_id, String^  time_Format, int priority)
		{
			String^ szTmp=DateTime::Now.ToString(time_Format)->ToString()->PadLeft(8,'0 ');
			WriteToSerial(stn_id, TIME_ID, szTmp, priority);
		//	WriteToSerialx(stn_id,TIME_ID,szTmp);	//directly send serial
			return szTmp;
		}


		
	public: void test__fireInFeed(testFireRLxType *rlx)
			 {
				if (!rlx) return;
				if (rlx->RL1stations[0] == 0)
					Fireinfeed(BroadcastID);
				else
				{
					int jj = 0;
					while(rlx->RL1stations[jj])
						Fireinfeed(rlx->RL1stations[jj++]);
				}
				//not broadcast
				//for(int ii=1;ii<61;ii++){
				//	Fireinfeed(rlx->RL1stations[ii++]);
				//}
			 }
	public: void test__firehelp(testFireRLxType *rlx)
			 {
				//if (!rlx) return;
				//if (rlx->RL4stations[0] == 0)
					Firehelpfeed(BroadcastID);
			/*	else
				{
					int jj = 0;
					while(rlx->RL4stations[jj]==0)
					{
						Firehelpfeed(rlx->RL4stations[jj++]);
						if(jj==20)
						{	unFirehelpfeed(BroadcastID);
						break;}
					}
				}*/
			 }

		public: void ClearSerialRx()
			 {
				if (sPort&&(sPort!=nullptr)&&(sPort->IsOpen))
					sPort->DiscardInBuffer();
			 }

		public: void ClearSerialTx()
			 {
				if (sPort&&(sPort!=nullptr)&&(sPort->IsOpen))
					sPort->DiscardOutBuffer();
			 }
				

	public: void test__fireElevator(testFireRLxType *rlx)
			 {
#ifdef testing_status
				 test__fireInFeed(rlx);
				 test__fireOutfeed(rlx);
				 test__firehelp(rlx);
#endif
			//	 if (!rlx) return;
			if (rlx->RL3stations[0] == 0)
					FireElevator(BroadcastID);
				else
				{
					int jj = 0;
					while(rlx->RL3stations[jj])
						FireElevator(rlx->RL3stations[jj++]);
				}
			//	test__fireOutfeed
			 }

	public: void test__fireOutfeed(testFireRLxType *rlx)
			 {
				 if (!rlx) return;
				if (rlx->RL2stations[0] == 0)
					Fireoutfeed(BroadcastID);
				else
				{
					int jj = 0;
					while(rlx->RL3stations[jj])
						Fireoutfeed(rlx->RL2stations[jj++]);
				}
			 }

	public: void Close()
		{
			if (swritethread&&(swritethread!=nullptr))
				swritethread->Abort();
			if (msecTimerthread&&(msecTimerthread!=nullptr))
				msecTimerthread->Abort();


			SAFE_DELETE(MsgFifo_1);
			SAFE_DELETE(MsgFifo_2);
			SAFE_DELETE(MsgFifo_3);
			SAFE_DELETE(NetworkMasterCommsStatistics);
			free(resend_databuffer);
			if (Log_file&&(Log_file!=nullptr))
				Log_file->Close();
		}
/*
int WriteToSerialx(SerialPort ^%serial_port, int STNID,int command,String ^Msg)
{
	if (serial_port&&(serial_port!=nullptr)&&(serial_port->IsOpen))
	{
		String ^szTmp = Msg->ToString()->PadLeft(8, ' '); //ensure the data is 7 bytes
		int ii;
		unsigned char ubuf[__MSG_stn___MAXSIZE+1];
		memset(ubuf, 0x0, sizeof(ubuf));
		unsigned char *sptr = ubuf;
		*sptr++ = 0x05;							//packet header SYNC
		*sptr++ = (unsigned char)STNID;			//packet Station ID number
		*sptr++ = (unsigned char)command;		//packet Command number
		for (ii=0;ii<8;ii++)					//data message 8 bytes
			*sptr++ = (unsigned char)szTmp[ii];	
		//--------------------------------------------
		//calculate checksum and send out packet
		//--------------------------------------------
		int chks = calculate_StationPacketChecksum(ubuf+1, MSG_stnChksum+1);		//calculate chksum
		*sptr++ = chks;																//packet checksum
		*sptr = 0x0a;																//EOT character
		writeNetworkSerial(serial_port, MakeManagedArray(ubuf, __MSG_stn___MAXSIZE+1), 0, __MSG_stn___MAXSIZE+1); 
		//----------------------------------
		//log to a debug test file
		//----------------------------------
		if(sMsgOutlogfile)
		{
			sMsgOutlogfile->putMsg("svr_out",ubuf, 13);
			sMsgOutlogfile->flush();
		}
	}
	return 0;
}
*/






/*
int WriteUCharToSerial(int STNID,int command, unsigned char *data)
{
	if (sPort&&(sPort!=nullptr)&&(sPort->IsOpen))
	{
		int ii;
		unsigned char ubuf[__MSG_stn___MAXSIZE+1];
		memset(ubuf, 0x0, sizeof(ubuf));
		unsigned char *sptr = ubuf;
		*sptr++ = 0x05;							//packet header SYNC
		*sptr++ = (unsigned char)STNID;			//packet Station ID number
		*sptr++ = (unsigned char)command;		//packet Command number
		for (ii=0;ii<8;ii++)					//data message 8 bytes
			*sptr++ = data[ii];	
		//--------------------------------------------
		//calculate checksum and send out packet
		//--------------------------------------------
		int chks = calculate_StationPacketChecksum(ubuf+1, MSG_stnChksum+1);		//calculate chksum
		*sptr++ = chks;																//packet checksum
		*sptr = 0x0a;																//EOT character
		writeNetworkSerial(sPort, MakeManagedArray(ubuf, __MSG_stn___MAXSIZE+1), 0, __MSG_stn___MAXSIZE+1); 
		//----------------------------------
		//log to a debug test file
		//----------------------------------
		if(sMsgOutlogfile)
		{
			sMsgOutlogfile->putMsg("svr_out",ubuf, 13);
			sMsgOutlogfile->flush();
		}
	}
	return 0;
}
*/

	//-----------------------------------------------------------------------
	//write UPSsys formatted data packet "Msg" String type data to 
	//Serialport directly or via FIFO depending on priority
	//This function write UPSsys formatted data packet.
	//stn_id  --- Station ID (remote unit address)
	//command --- UPSsysNW232 PROTOCOL command
	//payload --- the 8 byte of payload data (MUST ALWAYS BE 8 bytes)
	//priority -- specifies the writing to serialport priority
	//-----------------------------------------------------------------------
	public:int WriteToSerial(int STNID,int command, String ^Msg, int priority)
		   {
				int nn = 0;
				switch(priority)
				{
			   		case	PRIORITY_EXHIGH:
					case	PRIORITY_HIGH:
					//case	PRIORITY_INFEED:
					//case	PRIORITY_OUTFEED:
					case	PRIORITY_FULLHALFSENSOR:
							/*if (ACK_NAK_DirectWrite_enable)
							{
								WriteToSerialx(STNID, command, Msg);
								NetworkMasterCommsStatistics->priority_FireCounter++;
							}
							else
								WriteStrToSerialNetworkFifo(getFifoPriority(priority),  STNID, command, Msg);
							
							break;*/

					case	PRIORITY_COMMS:
					case	PRIORITY_SETUP_DATETIME:
					case	PRIORITY_SETUP_FUNC_KEY:
					case	PRIORITY_SETUP_PIECERATE:
					case	PRIORITY_SETUP_Totalpay:
					case	PRIORITY_SETUP_Efficiency:
					case	PRIORITY_SETUP_Totalpcs:
					case	PRIORITY_SETUP_paycat:
					case	PRIORITY_SETUP_OFFLINECMD:
					case	PRIORITY_SETUP:
					case	PRIORITY_MISC:
					case	PRIORITY_LOW:
					case	PRIORITY_TEST_LOW:
					case	PRIORITY_EXLOW:
					default:
							if (use_fifo){
#ifdef testing_status
								nn = WriteStrToSerialNetworkFifo(getFifoPriority(priority),  STNID, command, Msg);
#else
								if(Svr_ACK_flagE7.Equals(false)){
									nn = WriteStrToSerialNetworkFifo(getFifoPriority(priority),  STNID, command, Msg);
								}else{
									if(command!=101){
										if(command!=102){
										nn = WriteToSerialx(STNID, command, Msg);
										Svr_ACK_flagE7=false;
										}//nn = WriteStrToSerialNetworkFifo(getFifoPriority(priority),  STNID, command, Msg);
									}//nn = WriteStrToSerialNetworkFifo(getFifoPriority(priority),  STNID, command, Msg);
								}
								
#endif
							}
							else{
								nn = WriteToSerialx(STNID, command, Msg);} 
							break;
				}
				return nn;
		   }



	//-----------------------------------------------------------------------
	//write UPSsys formatted data packet "payload" array<Byte> type data to 
	//Serialport directly or via FIFO depending on priority
	//This function write UPSsys formatted data packet.
	//stn_id  --- Station ID (remote unit address)
	//command --- UPSsysNW232 PROTOCOL command
	//payload --- the 8 byte of payload data (MUST ALWAYS BE 8 bytes)
	//priority -- specifies the writing to serialport priority
	//-----------------------------------------------------------------------
	public:int WriteArryByte_Payload(int stn_id,int command, array<Byte> ^payload, int priority)
		   {
				__ASSERT_NETWORKSTATIONMASTER_ERROR(BTREKCANDAEMONV1::PACKETLENGTH, payload->Length, "payloadLength!=8",  __FILE__, __LINE__);
				if (use_fifo)
					return WriteArryByte_Payload(getFifoPriority(priority),  stn_id, command, payload);
				else
					return WriteArryByteToSerialx(stn_id, command, payload);
		   }

	//-----------------------------------------------------------------------
	//write directly to the serial port the data "ubuf" of size "dsize"
	//This function write any data size. It treats the "ubuf" as bytes
	//-----------------------------------------------------------------------
	public:int putUnsignedCharToSerialPort(unsigned char *ubuf, int dsize)
		   {
				if (sPort&&(sPort!=nullptr)&&(sPort->IsOpen))
					return writeSerial(MakeManagedArray(ubuf, dsize), dsize); 
				else
					return 0;
		   }

		   		
/*

	private:String^ SendDateDir(int stn_id, String^  date_Format)
			{
				return SendDate(stn_id, date_Format, PRIORITY_EXHIGH);
			}

	private:String^ SendTimeDir(int stn_id, String^  time_Format)
			{
				return SendTime(stn_id, time_Format, PRIORITY_EXHIGH);
			}
			*/

	public:void WriteKeyPadLCD(int stn_id, unsigned char X, unsigned char Y, String ^msg, bool beep, bool clearscr, unsigned char delay)
{
	int ii;
	unsigned char ubuf[128];
	unsigned char *sptr;
	int offset = 0;
	int length = msg->Length;
	unsigned char cntrl = 0x0F|delay;
	if (beep)
		cntrl |= 0x80;
	if (clearscr)
		cntrl |= 0x40;

	while(length>0)
	{
		memset(ubuf, 0x0, sizeof(ubuf));
		sptr = ubuf;
		*sptr++ = cntrl;							//packet control
		*sptr++ = X;			//packet Station ID number
		*sptr++ = Y;		//packet Command number
		for (ii=0;ii<6;ii++)					//data message 8 bytes
		{
			*sptr++ = (unsigned char)msg[ii+offset];
			length--;
			X++;
			if (X>16)		//greater than LCD columns
			{
				X=1;
				Y++;
				if (Y>4)	//greater than LCD rows
					Y=1;
			}

			if (length==0)
				break;
		}
		offset+=6;
		WriteToSerial(stn_id,0xEE,gcnew String(reinterpret_cast<const char*>(ubuf)), PRIORITY_SETUP);				//davidmod#
		cntrl &= 0x0F;		//after 1st round remove the clear scr and beep
	}
}

	//-------------------------------------------
	//write function to SerialDirect or MsgFifo
	//-------------------------------------------
	public:void SendOfflineCmd()					{								WriteToSerial(MasterID, 185,"offline",	PRIORITY_SETUP_OFFLINECMD);	}
	public:void Firehelpfeed(int stn_id)			{if ((stn_id>=0)&&(stn_id<128))	WriteToSerial(stn_id, 104,"help",	PRIORITY_OUTFEED);	}
	public:void unFirehelpfeed(int stn_id)			{if ((stn_id>=0)&&(stn_id<128))	WriteToSerial(stn_id, 109,"nonhelp",	PRIORITY_OUTFEED);	}
	public:void Fireoutfeed(int stn_id)				{if ((stn_id>=0)&&(stn_id<128))	WriteToSerialx(stn_id, 102,"outfeed"/*,	PRIORITY_OUTFEED*/);	}
	public:void Fireinfeed(int stn_id)				{if ((stn_id>=0)&&(stn_id<128))	WriteToSerialx(stn_id, 101,"infeed");/*,		PRIORITY_INFEED);	*/}
	public:void FireElevator(int stn_id)			{if ((stn_id>=0)&&(stn_id<128))	WriteToSerial(stn_id, 103,"elevator",PRIORITY_TEST_LOW);	}
	public:void SetInpectionStation(int stn_id)		{if ((stn_id>0)&&(stn_id<128))	WriteToSerial(stn_id, 0x52, "InspStn",	PRIORITY_EXLOW);	}
	public:void SetBridgeStation(int stn_id)		{if ((stn_id>0)&&(stn_id<128))	WriteToSerial(stn_id, 0xBC, "Bridge",	PRIORITY_SETUP);	}
	public:void SetLoadStation(int stn_id)			{if ((stn_id>0)&&(stn_id<128))	WriteToSerial(stn_id, 77, "loadstn",	PRIORITY_SETUP);	}
	public:void SetAutocollectStation(int stn_id)	{if ((stn_id>0)&&(stn_id<128))	WriteToSerial(stn_id, 84,"AutoCol",		PRIORITY_SETUP);	}
	public:void SetNormalStation(int stn_id)		{if ((stn_id>0)&&(stn_id<128))	WriteToSerial(stn_id, 56,"normstn",		PRIORITY_SETUP);	
		   }

	public:void ChangePassword(int stn_id, String ^password)		//change password	
	{
		if ((stn_id>0)&&(stn_id<128))	
			WriteToSerial(stn_id, 0x8F, password->PadRight(8, '.'), PRIORITY_SETUP);
	}	

	void SendDesignInfo(int stn_id, String ^Designcode, String ^color, String ^size, String ^qty)
	{
		WriteToSerial(stn_id,40,Designcode, PRIORITY_SETUP);
		WriteToSerial(stn_id,41,color,		PRIORITY_SETUP);
		WriteToSerial(stn_id,42,size,		PRIORITY_SETUP);
		WriteToSerial(stn_id,43,qty,		PRIORITY_SETUP);
	}


	void station_reLogin(int stn_id, String ^login_ledname,String ^login_empid)
	{
		String ^szLedname ="";
		int str_length = login_ledname->Length;
		if(str_length != 8)
			szLedname = login_ledname->ToString()->PadRight(8,' ');
		else
			szLedname = login_ledname->ToString()->PadLeft(4,' ');
		array<wchar_t> ^szChar1 = szLedname->ToCharArray();
		array<Byte> ^Bytecode = Encoding::GetEncoding(936)->GetBytes(szChar1) ;
		WriteArryByte_Payload(stn_id, 70, Bytecode, PRIORITY_SETUP);
		WriteToSerial(stn_id, 47, login_empid, PRIORITY_SETUP);
	}

	void Infeed_Fire(int stn_id, bool fire)
	{
		if (fire)
			WriteToSerial(stn_id, RL1FIRE,	"autocol1", PRIORITY_INFEED);	//101
		else
			WriteToSerial(stn_id, RL1UNFIRE,"autocol0", PRIORITY_INFEED);	//106
	}


	//--------------------------------------
	//Direct Serial Port write function
	//--------------------------------------
	void StartOperation(){	WriteToSerialx(MasterID, 0xE3, "startOp");	}
	void ShutDown(){		WriteToSerialx(MasterID, 0xE5,"ShutDown");	}
	void Kickpupy(){		WriteToSerialx(MasterID, 0x33,"Kickpupy");	}
	void SendACK(){			WriteToSerialx(MasterID, 0xE7,"ACK");		}
	void Init_System(String^  date_Format, String^  time_Format)
	{
		StartOperation();
		if (ACK_NAK_handshake_enable)
		{
			SendDate(BroadcastID, date_Format, PRIORITY_SETUP_DATETIME);
			SendTime(BroadcastID, time_Format, PRIORITY_SETUP_DATETIME);
		}
	}


	public:class_stationMsgFifo *getFifo(int fifoNo)
			{
				switch(fifoNo)
				{
					case	1://return MsgFifo_1;
					case	2://return MsgFifo_2;
					case	3:
					default:return MsgFifo_3;
				}
			}


	public:void NAK()
		   {
			   ACK_flagE7=false;
				if (ACK_NAK_handshake_enable)
					sendlast = 1;
				else
					NAK_flag++;
				if (NetworkMasterCommsStatistics)
				{
					NetworkMasterCommsStatistics->NAK_flag = NAK_flag;
					NetworkMasterCommsStatistics->NAK_count++;
				}
		   }

	//public:void ACK_flag(){
	//		  ACK_flagServer=true;
			  //ACK_flagE7=true;
	//	   }

	public:void ACK()
		   {	
			   ACK_flagE7=true;
				if (ACK_NAK_handshake_enable)
				{
					//if(stop_fifo.Equals(false))
					//{ACK_flagE7=true;
						SendMsgPacket2Serial();					
						blockingCounter = 0;
						blocking = true;
					//}
				}
				else
					ACK_flag++;

				if(NetworkMasterCommsStatistics)
				{
					NetworkMasterCommsStatistics->ACK_flag = ACK_flag;
					NetworkMasterCommsStatistics->ACK_count++;
				}
		   }

	public:int SendMsgPacket2Serial()
		   {
				int ii;
				int nn = 0;
				//ACK_flagE7=false;
				while(SendMsgPacket2SerialLock)
					Sleep(LockSleepMillsec);
				SendMsgPacket2SerialLock = 1;
				if (sPort&&(sPort!=nullptr)&&(sPort->IsOpen))
				{
					class_stationMsgFifo *fifo = 0;
					ii=3;
					fifo = getFifo(ii);
					if(fifo&&fifo->available())	//if there is messages to send (available==True)
						nn += sendfifo2Serial(fifo);
					/*else
					{
						ii=2;
						fifo = getFifo(ii);
						if(fifo&&fifo->available())	//if there is messages to send (available==True)
							nn += sendfifo2Serial(fifo);
						else
						{
							ii=3;
							fifo = getFifo(ii);
							if(fifo&&fifo->available())	//if there is messages to send (available==True)
								nn += sendfifo2Serial(fifo);							
						}
					}*/
				}
				SendMsgPacket2SerialLock = 0;
				return nn;
		
		   }



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NetworkStationMasterClass()
		{
			Close();
			SAFE_DELETE(MsgFifo_1);		
			SAFE_DELETE(MsgFifo_2);	
			SAFE_DELETE(MsgFifo_3);	
			if (components)
			{
				delete components;
			}
		}

	protected: 

	protected: 
	private: System::ComponentModel::IContainer^  components;
			 applicationSettingClass *appcfg;
			class_stationMsgFifo	*MsgFifo_1;
			class_stationMsgFifo	*MsgFifo_2;
			class_stationMsgFifo	*MsgFifo_3;
			ThreadStart^ threadDelegate; 
			Thread^ swritethread;

			ThreadStart^ threadmsecTimerDelegate; 
			Thread^ msecTimerthread;


			bool ACK_NAK_handshake_enable;
			bool ACK_NAK_DirectWrite_enable;
			bool use_fifo;
			int maxACK_flag;
			int maxNAK_flag;
			unsigned char *resend_databuffer;
			int resend_datasize;
			bool blocking;
			bool sendlast;
			int blockingCounter;
			bool SendMsgPacket2SerialLock;
			int LockSleepMillsec;
			int threadSleepMillsec;
			System::IO::StreamWriter ^Log_file;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
/*
		int writeSerialDirect(unsigned char *buf, int dsize)
		{
			int nn = writeSerial(MakeManagedArray(buf, dsize), dsize);
			//----------------------------------
			//log to a debug test file
			//----------------------------------
			if(sMsgOutlogfile)
			{
				sMsgOutlogfile->putMsg("svr_OuT",buf, dsize);
				sMsgOutlogfile->flush();
			}
			return nn;
		}
*/
		int sendfifo2Serial(class_stationMsgFifo *fifo)
		{
			int nn = 0;
			unsigned char ubuf[__MSG_stn___MAXSIZE+2];
			{
				int result = fifo->get(ubuf);	//read out the FIFO last entry for process
				if(result)
				{
#ifdef testing_status
				1	{
#else
					if(ubuf[2]!=102)	//testing
					{
						if(ubuf[2]!=101)//testing
#endif
						{
							nn = writeSerial(MakeManagedArray(ubuf, __MSG_stn___MAXSIZE+1),  __MSG_stn___MAXSIZE+1);
							if(sMsgOutlogfile)	//log to a debug test file
								{
									sMsgOutlogfile->putMsg("fifoOUT",ubuf, __MSG_stn___MAXSIZE+1);	//temporary
									sMsgOutlogfile->flush();
								}
								ACK_flag = 0;
							}
						}
						/*if(sMsgOutlogfile)	//log to a debug test file
						{
							sMsgOutlogfile->putMsg("fifoOUT",ubuf, __MSG_stn___MAXSIZE+1);
							sMsgOutlogfile->flush();
						}
						ACK_flag = 0;*/
				}
			}
			return nn;
		}

		int sendlast2Serial()
		{
			ACK_flagE7=false;
			int nn = 0;
			if (resend_datasize>0)
			{
				nn += writeSerial(MakeManagedArray(resend_databuffer, resend_datasize), resend_datasize);
				//datasize = __MSG_stn___MAXSIZE+1;
				//----------------------------------
				//log to a debug test file
				//----------------------------------
				if(sMsgOutlogfile)
				{
					sMsgOutlogfile->putMsg("svr_RPT",resend_databuffer, __MSG_stn___MAXSIZE+1);
					sMsgOutlogfile->flush();
				}
				NAK_flag = 0;
				NetworkMasterCommsStatistics->sendlastCount++;
			}
			return nn;
		}


		void millsecThread()
		{
			while(true)
			{
				Thread::Sleep(15);
				blockingCounter+=5;
				//millSecCounter++;
			}
		}


		void serialwriteThread()
		{
			bool writeEnable;
			int count3time=0;
			int i=0;
			//int ii;
			class_stationMsgFifo *fifo = 0;
			blockingCounter = 0;
			while(true)
			{
				Thread::Sleep(threadSleepMillsec);//10-->130104

				if (ACK_NAK_handshake_enable)
				{
					writeEnable = 0;
					if (sendlast)
					{
						sendlast2Serial();
						blockingCounter = 0;
						sendlast = 0;
					}
					else
					{
						
						while(count3time<=3){
							for(int i=0; i<500;){
								Sleep(1);
								if(ACK_flagE7.Equals(false)){
									i++;
									writeEnable=0;
									
								}else{
									//ACK_flagE7=true;
									writeEnable=1;
									break;
								}
							}
							sendlast2Serial();
							count3time++;
							if(count3time==3){
								//count3time=0;
								writeEnable=1;
							//	break;
							}
						}
						/*if (blocking)
						{
							//if((blockingCounter>appcfg->data.noSerialEventTimeOut)&&(ACK_flag==0)&&(NAK_flag==0))
							if((blockingCounter>noSerialEventTimeOut1)&&(ACK_flag==0)&&(NAK_flag==0))
							{
								blockingCounter = 0;
								noSerialEventTimeOut1 = 1;
								if(ACK_flagE7==false){
									//noSerialEventTimeOut1 += 1;
									if(noSerialEventTimeOut1 >100)
										sendlast2Serial();
									//ACK_flagE7=false;
								}
								//writeEnable=1;
							}*
						}
						else
							writeEnable=1;*/
					}
				}
				else
					writeEnable=1;

				if((writeEnable)&&(ACK_flag.Equals(true)))
				{
					ACK_flagE7=false;
					SendMsgPacket2Serial();
					blockingCounter = 0;
					//writeEnable = 0;
				}
				blocking = true;


				//-------------------------------------
				//debug get/set/update statistics
				//-------------------------------------
				//MsgFifo_1->updateStatistics();
				//MsgFifo_2->updateStatistics();
				//MsgFifo_3->updateStatistics();
				if (ACK_flag>maxACK_flag)
					maxACK_flag = ACK_flag;
				if (NAK_flag>maxNAK_flag)
					maxNAK_flag = NAK_flag;

				if (NetworkMasterCommsStatistics)
				{
					NetworkMasterCommsStatistics->ACK_flag = ACK_flag;
					NetworkMasterCommsStatistics->NAK_flag = NAK_flag;
					NetworkMasterCommsStatistics->maxACK_flag = maxACK_flag;
					NetworkMasterCommsStatistics->maxNAK_flag = maxNAK_flag;
				}

				//blockingCounter++;
			}
		}
		

	//-----------------------------------------------------------------------
	//write UPSsys formatted data packet "payload" array<Byte> type data to 
	//FIFO
	//This function write UPSsys formatted data packet.
	//fifo ------ specifies the FIFO to write to
	//stn_id  --- Station ID (remote unit address)
	//command --- UPSsysNW232 PROTOCOL command
	//payload --- the 8 byte of payload data
	//-----------------------------------------------------------------------
	private:int WriteArryByte_Payload(class_stationMsgFifo *fifo, int stn_id, int command, array<Byte> ^payload)
		 {
			if (fifo)
			{
				unsigned char outbuf[__MSG_stn___MAXSIZE+1];
				MakeStrSerialNetworkHardwarePacket(stn_id, command, payload, outbuf);
				fifo->put(outbuf);
				return 1;
			}
			return 0;
		 }

	private:class_stationMsgFifo *getFifoPriority(int priority)
			{
				switch(priority)
				{
					case	PRIORITY_EXHIGH:
					case	PRIORITY_HIGH:
					case	PRIORITY_INFEED:
					case	PRIORITY_OUTFEED:
					case	PRIORITY_FULLHALFSENSOR:
							//return MsgFifo_1;

					case	PRIORITY_COMMS:
					case	PRIORITY_SETUP_DATETIME:
					case	PRIORITY_SETUP_FUNC_KEY:
					case	PRIORITY_SETUP_PIECERATE:
					case	PRIORITY_SETUP_Totalpay:
					case	PRIORITY_SETUP_Efficiency:
					case	PRIORITY_SETUP_Totalpcs:
					case	PRIORITY_SETUP_paycat:
					case	PRIORITY_SETUP_OFFLINECMD:
					case	PRIORITY_SETUP:
					case	PRIORITY_MISC:
							//return MsgFifo_2;

					case	PRIORITY_LOW:
					case	PRIORITY_TEST_LOW:
					case	PRIORITY_EXLOW:
					default:
							return MsgFifo_3;
				}
			}

	private:int writeSerial(array<unsigned char>^ buffer, int count)
			{
				int nn = 0;
				resend_datasize = 0;
				while(SeriallockFlag)
					Sleep(LockSleepMillsec);
				SeriallockFlag = 1;
				if (sPort&&(sPort!=nullptr)&&(sPort->IsOpen))
				{
					//try{
						sPort->Write(buffer, 0, count);
					//}catch (TimeoutException ^) {
					//}
					nn = count;
					for (int ii=0;ii<nn; ii++)
						resend_databuffer[ii] = buffer[ii];
					resend_datasize = nn;
				}
				SeriallockFlag = 0;

				return nn;
			}

		//Send to serial port directly
	//private change to public for testing
	public:int WriteToSerialx(int stn_id,int command,String ^Msg)
			{
				/*if(command==0xE7){
					ACK_flagE7=true;
					SendMsgPacket2Serial();	
					blockingCounter = 0;
						blocking = true;			
				}*/
				int count = 0;
				if ((stn_id>=0)&&(stn_id<=128))
				{
					if (sPort&&(sPort!=nullptr)&&(sPort->IsOpen))
					{
						unsigned char ubuf[__MSG_stn___MAXSIZE+2];
						count = MakeStrSerialNetworkHardwarePacket(stn_id, command, Msg, ubuf);
						if (count==__MSG_stn___MAXSIZE+1)
						{
							count = writeSerial(MakeManagedArray(ubuf, count),  count); 
							//----------------------------------
							//log to a debug test file
							//----------------------------------
							if(sMsgOutlogfile)
							{
								if (command==0xE7){
									Svr_ACK_flagE7=true;
									sMsgOutlogfile->putMsg("svr_ACK",ubuf, count);	//temporary
								}
								else{
									sMsgOutlogfile->putMsg("svr_out",ubuf, count);	//temporary
								}
								sMsgOutlogfile->flush();
							}
						}
					}
				}
				return count;
			}

	private:int WriteArryByteToSerialx(int stn_id,int command, array<Byte> ^Bytecode)
			{
				int count = 0;
				if ((stn_id>=0)&&(stn_id<=128))
				{
					if (sPort&&(sPort!=nullptr)&&(sPort->IsOpen))
					{
						unsigned char ubuf[__MSG_stn___MAXSIZE+2];
						MakeStrSerialNetworkHardwarePacket(stn_id, command, Bytecode, ubuf);
						count += writeSerial(MakeManagedArray(ubuf, __MSG_stn___MAXSIZE+1), __MSG_stn___MAXSIZE+1); 
						//----------------------------------
						//log to a debug test file
						//----------------------------------
						if(sMsgOutlogfile)
						{
							sMsgOutlogfile->putMsg("svr_out",ubuf, 13);	//temporary
							sMsgOutlogfile->flush();
						}
					}
				}
				return count;
			}

	private:void errorCatch(int catchERROR_No, int value, String ^errRemark, const char *file, int line)
			{
				switch(catchERROR_No)
				{
					case	BTREKCANDAEMONV1::PACKETLENGTH:
							if (value!=8)
							{
								//String ^str = "Err:" + catchERROR_No.ToString() + "," + errRemark +","+ gcnew String(reinterpret_cast<const char*>(file)) + "," + line.ToString() +  "\r\n";
								String ^str = "Err:" + catchERROR_No.ToString() + "," + errRemark +","+ line.ToString() +  "\r\n";
								Log_file->WriteLine(str);
								Log_file->Flush();
							}
							break;
				}
			}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{

		}


#pragma endregion
	};



}
