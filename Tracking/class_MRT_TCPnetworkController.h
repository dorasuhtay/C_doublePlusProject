#include <vcclr.h>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include "class_TCPsocket.h"
#include "class_HostnameMRTonline.h"
#include "stringconversion.h"
#include "mrt_X01netc.h"
#pragma once

//#using <System.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::NetworkInformation;
using namespace System::Text;

using namespace common_ClassLib;

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

namespace BTREKCANDAEMONV1 {

	/// <summary>
	/// Summary for class_MRT_TCPnetworkController
	/// </summary>
	public ref class class_MRT_TCPnetworkController :  public System::ComponentModel::Component
	{
	public:
		class_MRT_TCPnetworkController(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			connectionstate = 0;
			clientSocket_lock = 0;
			last_state = -1;
			hostname_table = 0;
			counter = 0;
			hostnameIndex = 0;
			mrt_X01 = new structmrt_X01netcType;
			memset(mrt_X01, 0x0, sizeof(structmrt_X01netcType));
			mrt_X01->delimiter0 = netc16_1sync;
			mrt_X01->delimiter1 = netc16_2sync;
			mrt_X01->delimiter2 = netc16_3sync;
			mrt_X01->databuffersize = 128;
			mrt_X01->databuffer = (unsigned char *)malloc(mrt_X01->databuffersize+1);
    
			testData = new char [1024];
			payload = new unsigned char[1024];

			threadDelegate = gcnew ThreadStart( this, &class_MRT_TCPnetworkController::ServiceThread);
			newThread = gcnew Thread(threadDelegate);
			//newThread->Start();
		}
		class_MRT_TCPnetworkController(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}


	void ConnectCommand(String ^ipaddressStr, int port_Number) 
		 {
			 switch(connectionstate)
			 {
				 case	0:
						if ((port_Number>0)&&(ipaddressStr!=""))
						{
						//----------------------------------------			
						//Open a TCP server port As command Port
						//(Text port)
						//----------------------------------------	
						if (clientSocket&&(clientSocket!=nullptr))
							clientSocket->Close();
						clientSocket = gcnew class_TCPsocket();
						clientSocket->Name = "socket Terminal";
						clientSocket->setmode(tcpPort_BINARY);		//Text port
						clientSocket->Open(isock_CLIENT, ipaddressStr, port_Number);
						connectionstate++;
						}
						break;
				 default:
						if (CloseclientSocket())
							connectionstate = 0;
						break;
			 }
		 }


		int parsePacket(unsigned char ch)
		{
			int nn = 0;
			//char testbuf[128];
				mrt_XnetcStateMachine(ch, mrt_X01);
                switch (mrt_X01->status)
                {
                    case    PKT_FOUND:
                            //sprintf(buf, "Psh:%03d\r\n",mrt_X01->databuffer[9]);
							memcpy(payload, mrt_X01->dataptr, mrt_X01->length);
							payload[mrt_X01->length] = 0x0;
							sprintf(testData, "%s  [%c][%d][%d.%d.%d.%d %d][%c%d]\r\n", 
												payload, mrt_X01->portXnet_cmd, mrt_X01->port,
												mrt_X01->ipv4_1,
												mrt_X01->ipv4_2,
												mrt_X01->ipv4_3,
												mrt_X01->ipv4_4,
												mrt_X01->ipv4_port,
												mrt_X01->deviceprefix,			
												mrt_X01->device
												);

							mrt_X01->dataptr[mrt_X01->length] = 0x0;
							if (strcmp((char *)mrt_X01->dataptr, "status")==0)
							{
								if (hostname_table)
									hostname_table->setconnectionstatus(hostnameIndex, "ok", 0);
								CloseclientSocket();
							}
							if (strcmp((char *)mrt_X01->dataptr, "verifed")==0)
							{
								if (hostname_table)
									hostname_table->setconnectionstatus(hostnameIndex, "OK", 0);
							}

							//testData[mrt_X01->length] = 0x0;
							nn = 1;
                            mrt_XnetcresetState(mrt_X01, 0);
                            break;
                    case	PKT_CRCERROR:
                    case	PKT_ABORT:mrt_XnetcresetState(mrt_X01, 0);
                            break;
                    case	PKT_ACQUIRING:
                    default:break;
                }
				return nn;
		}

		char *testData;
		unsigned char *payload;


		void Close()
		{
			threadstarted = 0;
			newThread->Abort();

			if (clientSocket&&(clientSocket!=nullptr))
				clientSocket->Close();
			if (mrt_X01)
			{
				if (mrt_X01->databuffer)
					free(mrt_X01->databuffer);
				SAFE_DELETE(mrt_X01);
			}

			//if (clientSocket&&(clientSocket!=nullptr))
			//	clientSocket->Close();
			
			SAFE_DELETE(testData);
			SAFE_DELETE(payload);
			
		}

		void Start()
		{
			newThread->Start();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~class_MRT_TCPnetworkController()
		{
			if (components)
			{
				delete components;
			}

		
		}

		int CloseclientSocket()
		{
			connectionstate = 0;
			if (clientSocket&&(clientSocket!=nullptr))
			{
				clientSocket->Close();
				delete clientSocket;
				clientSocket = nullptr;
				return 1;
			}
			return 0;
		}

		void ServiceThread()
		{
			threadstarted = 1;
			while(threadstarted)
			{
				Thread::Sleep(10);
				//10 second event
				//--------------------

				if (clientSocket&&(clientSocket!=nullptr))
				{
					int cstate = clientSocket->getstate();
					if (last_state!=cstate)
					{
						//Color cColor;
						switch(cstate)
						{
							case	tcpSocket_NULL:
									if (clientSocket->getSocketType()==isock_SERVER)
										connectionstate = 1;
									else
										connectionstate = 0;
									//setconnected(false);
									break;
							case	tcpSocket_CONNECTING:
									connectionstate=1;
									//setconnected(false);
									//OpenProgessBox();
									break;
							case	tcpSocket_CONNECTED:
									connectionstate++;
									//setconnected(true);
									//CloseProgessBox();
									if (hostname_table)
										hostname_table->setconnectionstatus(hostnameIndex, "CONNECTED", 0);
									if(clientSocket_lock==0)
									{
									
										clientSocket_lock = 1;
										unsigned char buf[512];
										int result = wrapmrt_Xnetc((unsigned char *)"status", 6, buf, 0);
										if (result>0)
										{
											if (hostname_table)
												hostname_table->setconnectionstatus(hostnameIndex, "verify...", 0);
											clientSocket->writeblock(buf, result);
										}
										clientSocket_lock = 0;
									}

									break;
							case	tcpSocket_CONNECTFAIL:
									//connectionstate = 0;
									if (hostname_table)
										hostname_table->setconnectionstatus(hostnameIndex, "fail", 0);
									CloseclientSocket();

									//setconnected(false);
									//CloseProgessBox();
									//terminal_textBox->Text += "\r\n***Connection to " + ipaddressStr + " " + port_Number.ToString() + " FAILED\r\n";
									break;
						}
						last_state = cstate;
					}
				 }

				if ((counter&100)==0)
				{
					if (clientSocket==nullptr)
					{
						if (hostname_table)
						{
							hostnameIndex++;
							if(hostnameIndex>=hostname_table->getcount())
								hostnameIndex = 0;
							String^ ipaddr = hostname_table->getIpaddress(hostnameIndex);
							if (ipaddr!="")
							{
								ConnectCommand(ipaddr, 12000);
								hostname_table->setconnectionstatus(hostnameIndex, "connecting...", 0);
							}
						}
					}
				}



				counter++;
			}

			/*//int byteCount, ii, result;
			//array<Byte>^ msg;
			//array<Byte>^ bytes = gcnew array<Byte>(512);
			Ping ^ pingSender = gcnew Ping;
			PingOptions ^ options = gcnew PingOptions;
			// Create a buffer of 32 bytes of data to be transmitted.
			String^ data = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
			array<Byte>^buffer = Encoding::ASCII->GetBytes( data );
			int timeout = 120;
			String ^replyTest="";


			int ii;
			HostnameMRTonlineType hst_online;
			HostnameMRTonlineType *hst_ptr;
			FILE *fp = fopen("tcptest.txt", "w+t");
			while(true)
			{
				Thread::Sleep(10);
				if ((counter%1000)==0)
				{
					if(hostname_table)
					{
						for (ii=0;ii<hostname_table->getcount();ii++)
						{
							if (hostname_table->isMyName(ii)) continue;
							if (hostname_table->isName(ii, L"-LOCAL-")) continue;
							hst_ptr = hostname_table->get(ii);
							if (!hst_ptr) continue;
							memcpy(&hst_online, hst_ptr, sizeof(HostnameMRTonlineType));
							String ^str = hostname_table->getName(ii);
							if (str=="") continue;

							String ^ip = hostname_table->getIpaddress(ii);

							replyTest = "";
							if (pingSender&&pingSender!=nullptr())
							{
							// Use the default Ttl value which is 128, 
							// but change the fragmentation behavior.
							options->DontFragment = true;
							PingReply ^ reply = pingSender->Send( ip, timeout, buffer, options );
							
							if ( reply->Status == IPStatus::Success )
							{
								replyTest = "OK ";
								replyTest += reply->Address->ToString() + ", ";
								replyTest += reply->RoundtripTime + ", ";
								replyTest += reply->Options->Ttl + ", ";
								replyTest += reply->Options->DontFragment + ", ";
								replyTest += reply->Buffer->Length;

							}
							}

							if (fp)
							{
								char buf[128], buf1[128], buf2[1024];
								String2Char_n(ip, buf1, sizeof(buf1)-1);
								String2Char_n(str, buf, sizeof(buf)-1);
								String2Char_n(replyTest, buf2, sizeof(buf2)-1);
								
								fprintf(fp, "%s %s\r\n", buf, buf1, buf2);
							}
						}
					}
				}
				counter++;
			}
			fclose(fp);
			*/
		}

	public:
		class_HostnameMRTonline *hostname_table;

	private:
		ThreadStart^ threadDelegate; 
		Thread^ newThread; 
		bool threadstarted;
		int counter;
		int connectionstate;
		bool clientSocket_lock;
		int last_state;
		int hostnameIndex;
		structmrt_X01netcType *mrt_X01;
		class_TCPsocket ^clientSocket;
		
		//mrt_X01netc *mrt_X01;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
			
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			components = gcnew System::ComponentModel::Container();
		}
#pragma endregion
	};
}
