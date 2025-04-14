
#include "stdafx.h"
#include <windows.h>
#include <vcclr.h>
#include "lcircbuf.h"
#include "wctStringFifo.h"
#include "tcpCommon.h"


#pragma once

using namespace System;
using namespace System::IO;	
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;
using namespace System::Threading;
using namespace System::Net::Sockets;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

/*
enum{
	tcpPort_BINARY=0,
	tcpPort_COMMAND_TEXT
};
enum{
	tcpStatus_NULL=0,
	tcpStatus_NOTCONNECTED,
	tcpStatus_CONNECTED
};
*/

			
				
#define SAFE_CLOSE(p)	{ if (p&&(p!=nullptr))p->Close();}
#define SAFE_STOP(p)	{ if (p&&(p!=nullptr))p->Stop();}

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
//#define textline_SIZE			128

namespace common_ClassLib {

	/// <summary>
	/// Summary for class_TCPserver
	/// </summary>
	public ref class class_TCPserver :  public System::ComponentModel::Component
	{
	public:
		class_TCPserver(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			//---------------------------------------
			//Create a Pusher Link counter thread
			//---------------------------------------
			/*
			Work^ w = gcnew Work;		    
			threadDelegate = gcnew ThreadStart( w, &Work::tcpServiceThread);
			newThread = gcnew Thread(threadDelegate);
			newThread->Start();
			*/
			Name = "tcpServer";
			mode = tcpPort_BINARY;
			tcpListenerStarted = 0;
			tcpServerConnected = 0;
			last_Status = -1;
			//textlineptr = 0;
			recvbytes = gcnew array<Byte>(textline_SIZE);
			recvbytesptr = 0;

			inbuf = new LCircularBuf();
			inbuf->Init(2048);
			
			outbuf = new LCircularBuf();
			outbuf->Init(2048);
			inTextLines = new wctStringFifo();
			inTextLines->create(512);
			//outTextLines = new wctStringFifo();
			
			StartMsg = "";

			threadDelegate = gcnew ThreadStart( this, &class_TCPserver::tcpServiceThread);
			newThread = gcnew Thread(threadDelegate);
			newThread->Start();
		}
		class_TCPserver(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}
		void setmode(int mode_) { mode = mode_;}
		int getmode() { return mode;}
		String ^getmodeStr()
		{
			if ((mode<0)||(mode>=tcpPort____MAX))
				return "---";
			return gcnew String(reinterpret_cast<const wchar_t*>(sockModeMsgString[mode]));
			
			/*
			switch(mode)
			{
				case	tcpPort_BINARY: return "BINARY";
				case	tcpPort_COMMAND_TEXT: return "TEXT";
			}
			return "---";
			*/
		}
		bool isconnected(){ return tcpServerConnected;}
		int connected(){ return tcpServerConnected;}
		String ^Name;
		int getStatus()
		{
			int nn;
			if (last_Status==connected())
				return 0;
			if (connected())
				nn = tcpStatus_CONNECTED;
			else
				nn = tcpStatus_NOTCONNECTED;

			last_Status=connected();
			return nn;
		}

		bool getChangedStatus(int *status)
		{
			if (last_Status==connected())
				return 0;
			if (connected())
				*status = tcpStatus_CONNECTED;
			else
				*status = tcpStatus_NOTCONNECTED;
			last_Status=connected();
			return 1;
		}
		void setStartMessage(String ^msg)
		{
			StartMsg = msg;
		}
		wctString *getrecv_TextLine()
		{
			return inTextLines->get();
		}

		int getport(){return ipport;}
		void Open_IP_port(int port)
		{
			if (port<=0) 
				return;
			try{
				ipport = port;
				//ipAddress = IPAddress::Parse(ipaddr);
				//ipAddress = Dns::Resolve("localhost");
				tcpListener = gcnew TcpListener( IPAddress::Any,ipport );
				tcpListener->Start();
				tcpListenerStarted = 1;
			}
			//catch(System::Exception^ ex)
			catch(System::Exception^)
			{

			}

		}
		//String ^getipaddress() {return IPAddress::Any;}

		void putchar(unsigned char ch)
		{
			if(outbuf)
				outbuf->Add(ch);
			//outbuf->bytesAvail();

		}



		void SendString(String ^str)
		{
			if (serverSocket&&serverSocket->Connected)
			{
				//open network stream on accepted socket
				
				array<Byte>^ msg = Encoding::UTF8->GetBytes(str);
				serverSocket->Send( msg );
			}
		}
		
		String ^recv_String()
		{
			if(recv_TextAvailable())
			{
				wctString *wstr = getrecv_TextLine();
				if(wstr)
					return gcnew String(reinterpret_cast<const wchar_t*>(wstr->wdata()));
			}
			return "";
		}

		bool recv_Available(){ if (inbuf) return inbuf->bytesAvail(); else return 0;}
		LCircularBuf *getinBuf() {return inbuf;}
		
		
		bool recv_TextAvailable()
		{
			if (inTextLines)
				return inTextLines->available();
			else
				return 0;
		}
		
		void Close()
		{
			newThread->Abort();

			SAFE_STOP(tcpListener);
			SAFE_CLOSE(serverSocket);

			SAFE_DELETE(inbuf);
			SAFE_DELETE(outbuf);
			SAFE_DELETE(inTextLines);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~class_TCPserver()
		{
			SAFE_DELETE(inbuf);
			SAFE_DELETE(outbuf);
			SAFE_DELETE(inTextLines);
			//SAFE_DELETE(outTextLines);
			
			if (components)
			{
				delete components;
			}
		}

	//--------------------------------------------------------
	//handling of bytes that forms a line
	//  receive the bytes and store in recvbytes[] 
	//  until CR '\r'
	//--------------------------------------------------------
	void getline(array<Byte>^ bytes, int byteCount)
		{
			char ch;
			for (int ii=0;ii<byteCount;ii++)
			{
				ch = bytes[ii];
				switch(ch)
				{
					case	'\r':		//line terminator
							{
								textline = Encoding::UTF8->GetString( recvbytes );
								pin_ptr<const wchar_t> wch = PtrToStringChars(textline);
								inTextLines->put(wch);
								recvbytesptr = 0;
							}
							break;
					case	'\0':
					case	'\n':		//ignore these
							break;
					case	'\b':		//backspace
							if (recvbytesptr>0) 
								recvbytesptr--;
							break;
					default:
						recvbytes[recvbytesptr] = ch;
						recvbytesptr = (recvbytesptr+1)%textline_SIZE;	//wrap around
						recvbytes[recvbytesptr] = 0x0;
						break;
				}
			}
		}

		//--------------------------------------------------------
		//thread. The service thread is constantly running
		//  Checking for Accepting of connection 
		//  In text mode:
		//    Checking of received characters from client side (inTextLines)
		//  In binary mode:
		//    Checking of received characters from client side (inbuf)
		//    Checking of characters to send out (outbuf)
	
		//--------------------------------------------------------
		void tcpServiceThread()
		{
			int byteCount, ii, result;
			//array<Byte>^ msg;
			array<Byte>^ bytes = gcnew array<Byte>(512);
			
			while(true)
			{
				Thread::Sleep(10);

				if (tcpListener&&(tcpListener!=nullptr)&&tcpListenerStarted)
				{
					if ( tcpListener->Pending() )
					{
						//Accept the pending client connection and return a TcpClient object^ initialized for communication.
						serverSocket = tcpListener->AcceptSocket();
						if (serverSocket->Connected)
						{
							//open network stream on accepted socket
							serverSocket->Send(Encoding::UTF8->GetBytes( StartMsg ));
							tcpServerConnected = 1;
						}
					}
					

					// On connected... perform the read using non-blocking method
					//   "serverSocket->Available" & "serverSocket->Receive()"
					if (serverSocket&&serverSocket->Connected)
					{
						switch(mode)
						{
							case	tcpPort_COMMAND_TEXT:
									//--------------------------------------------
									//In text mode, read a line terminated by '\r'
									//--------------------------------------------
									result = serverSocket->Available;
									if (result>0)
									{
										byteCount = serverSocket->Receive( bytes );
										if (byteCount>0)
											getline(bytes, byteCount);
									}
									break;
							default:
									//-----------------------------------------------
									//In binary mode, read bytes and store in "inbuf"
									//-----------------------------------------------
									//array<Byte>^ bytes = gcnew array<Byte>(256);
									result = serverSocket->Available;
									if (result>0)
									{
										byteCount = serverSocket->Receive( bytes );
										for (ii=0;ii<byteCount;ii++)
											inbuf->Add(bytes[ii]);
									}
									//-----------------------------------------------
									//In binary mode, "outbuf"
									//outbuf FIFO if there is bytes available to be send.. 
									//perform the send here
									//--------------------------------------------------------
									if (outbuf->bytesAvail())
									{
										unsigned char buf[256];
										int result = outbuf->Read(buf, 255);
										if (result>0)
										{
											array<Byte>^ msg = gcnew array<Byte>(result);
											for (ii=0;ii<result;ii++)
												msg[ii] = buf[ii];
											serverSocket->Send( msg );
										}
									}
									break;
						}
						//--------------------------------------------
						//check if socket is still connected or
						//Disconnected by Client side
						//--------------------------------------------
						if(serverSocket->Poll(0, SelectMode::SelectRead) && serverSocket->Available == 0)
						{
							tcpServerConnected = 0;
							serverSocket->Shutdown( SocketShutdown::Both );
							serverSocket->Disconnect( true );
						}
					}
				}
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	
	private:
		ThreadStart^ threadDelegate; 
		Thread^ newThread; 
		String ^StartMsg;
		int ipport;
		TcpListener ^tcpListener;
		Socket^ serverSocket;
		LCircularBuf *inbuf;
		LCircularBuf *outbuf;
		wctStringFifo *inTextLines;
		int tcpServerConnected;
		bool tcpListenerStarted;
		String ^textline;
		array<Byte>^ recvbytes;
		int recvbytesptr;
		int mode;		//tcpPort_COMMAND_TEXT, tcpPort_BINARY
		int last_Status;

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
