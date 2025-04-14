#include <windows.h>
#include <vcclr.h>
#include "lcircbuf.h"
#include "wctStringFifo.h"
#include "tcpCommon.h"

#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;


using namespace System::IO;	
using namespace System::Threading;
using namespace System::Net::Sockets;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

enum{
	tcpClient_NULL=0,
	tcpClient_CONNECTING,
	tcpClient_CONNECTED,
	tcpClient_CONNECTFAIL
};

//#define ISCONNECTED(p)	{ (p&&(p!=nullptr)&&p->Connected)}
#define SAFE_CLOSE(p)		{ if (p&&(p!=nullptr))p->Close();}
#define SAFE_STOP(p)		{ if (p&&(p!=nullptr))p->Stop();}
#define SAFE_DELETE(p)		{ if(p) { delete (p);     (p)=0; }}
//#define textline_SIZE		128



namespace common_ClassLib {

	/// <summary>
	/// Summary for class_TCPclient
	/// </summary>
	public ref class class_TCPclient :  public System::ComponentModel::Component
	{
	public:
		class_TCPclient(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			state = tcpClient_NULL;
			Name = "tcpClient";
			mode = tcpPort_BINARY;

			//opened = 1;
			
			//tcpListenerStarted = 0;
			tcpclientConnected = 0;
			beginconnect = 0;
			last_Status = -1;
			//textlineptr = 0;
			//connectionCallBackfunction = nullptr;
			recvbytes = gcnew array<Byte>(textline_SIZE);
			recvbytesptr = 0;
			inbuf = new LCircularBuf();
			inbuf->Init(2048);
			outbuf = new LCircularBuf();
			outbuf->Init(2048);
			inTextLines = new wctStringFifo();
			inTextLines->create(128);
			//outTextLines = new wctStringFifo();
			//StartMsg = "";
			threadDelegate = gcnew ThreadStart( this, &class_TCPclient::tcpclientThread);
			newThread = gcnew Thread(threadDelegate);
			newThread->Start();
	
			tcpClient = gcnew TcpClient();
		}

		//int (*class_TCPclient::funcP)(int state);
//		void ^%obj;
		//int (*connectionCallBackfunction)(int state);
		//void (*callback)(void);
		//void cbfunc()
		//{
		//}
	//public: delegate void CallbackEventHandler(int state);
	//public: event CallbackEventHandler ^Callback; 
	//public: delegate void CallbackEventHandler(int state);
	//public: event CallbackEventHandler ^Callback; 



		//bool isOpened() {return opened;}

		class_TCPclient(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}

		int getstate(){return state;}
		int getportnumber(){return ipport;}
		int Open_IP_port(String ^address, int port)
		{
			if (port<=0)
				return -1;
			//callback=(void *)cbfunc;
			int error = 0;
			ipport = port;
			ipaddress = address;
			//ipAddress = IPAddress::Parse(ipaddress);
			//ipAddress = Dns::Resolve("localhost");
			beginconnect = 1;
			/*
			try
			{
				//tcpClient = gcnew TcpClient( ipaddress, ipport );
				
				if (tcpClient&&(tcpClient!=nullptr))
				{
					tcpClient->Connect(ipaddress, ipport);
					//tcpClient->BeginConnect(ipaddress, ipport, &BTREKCANDAEMONV1::class_TCPclient::OnSocketConnected, nullptr);
					clientSocket = tcpClient->Client; 
					if (clientSocket)
						tcpclientConnected = 1;
				}
				
			}catch (Exception ^e)
			{
				error = 1;
			}
*/
			return error;	
		}

		void setmode(int mode_) { mode = mode_;}
		bool connected(){ return tcpclientConnected;}
		void putchar(unsigned char ch)
		{
			if(outbuf)
				outbuf->Add(ch);
			//outbuf->bytesAvail();

		}

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
		/*
		void setStartMessage(String ^msg)
		{
			StartMsg = msg;
		}
		*/
		wctString *getrecv_TextLine()
		{
			return inTextLines->get();
		}

		void SendString(String ^str)
		{
			if (clientSocket&&(clientSocket!=nullptr)&&clientSocket->Connected)
			{
				//open network stream on accepted socket
				array<Byte>^ msg = Encoding::UTF8->GetBytes(str);
				clientSocket->Send( msg );
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
			//opened = 0;

			newThread->Abort();
			state = 0;
			/*
			if (serverSocket&&serverSocket->Connected)
			{
				serverSocket->Shutdown( SocketShutdown::Both );
				serverSocket->Disconnect( true );
			}*/


			/*if (clientSocket&&(clientSocket!=nullptr))
				clientSocket->Close();
			if (tcpClient&&(tcpClient!=nullptr))
				tcpClient->Close();
				*/

			SAFE_CLOSE(clientSocket);
			SAFE_CLOSE(tcpClient);

			SAFE_DELETE(inbuf);
			SAFE_DELETE(outbuf);
			SAFE_DELETE(inTextLines);

		}
		String ^Name;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~class_TCPclient()
		{
			if (components)
			{
				delete components;
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
		TcpClient ^tcpClient;
		int ipport;
		String ^ipaddress;
		Socket^ clientSocket;
		int mode;	
		int last_Status;
		bool tcpclientConnected;
		String ^textline;
		array<Byte>^ recvbytes;
		int recvbytesptr;
		wctStringFifo *inTextLines;
		LCircularBuf *inbuf;
		LCircularBuf *outbuf;
		bool beginconnect;
		int state;
		//bool opened;
/*
private: void OnSocketConnected (IAsyncResult ^asynchronousResult)
{
  try
  {
    tcpClient->EndConnect(asynchronousResult);
  }
  catch { }
}
		 */

	void addByte(char ch)
	{
		recvbytes[recvbytesptr] = ch;
		recvbytesptr = (recvbytesptr+1)%textline_SIZE;	//wrap around
		recvbytes[recvbytesptr] = 0x0;
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
								addByte(ch);
								if (bytes[ii+1]=='\n')
								{
									addByte(bytes[ii+1]);
									/*
									recvbytes[recvbytesptr] = '\n';
									recvbytesptr = (recvbytesptr+1)%textline_SIZE;	//wrap around
									recvbytes[recvbytesptr] = 0x0;*/
								}
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
		void tcpclientThread()
		{
			int byteCount, ii, result;
			//array<Byte>^ msg;
			array<Byte>^ bytes = gcnew array<Byte>(512);
			
			while(true)
			{
				Thread::Sleep(10);
				if(beginconnect)
				{
					if (tcpClient&&(tcpClient!=nullptr))
					{
						try
						{
							//if (Callback) 
								//Callback(state);
							state = tcpClient_CONNECTING;
							//if (connectionCallBackfunction)
								//connectionCallBackfunction(state);
							tcpClient->Connect(ipaddress, ipport);
							clientSocket = tcpClient->Client; 
							if (clientSocket)
							{
								tcpclientConnected = 1;
								state = tcpClient_CONNECTED;
							}
						}
						catch (Exception ^)
						{
							state = tcpClient_CONNECTFAIL;
							//if (connectionCallBackfunction)
								//connectionCallBackfunction(state);
							tcpclientConnected = 0;
						}
						beginconnect = 0;
					}
					continue;
				}
				//if (ISCONNECTED(clientSocket))
				if (clientSocket&&(clientSocket!=nullptr)&&clientSocket->Connected)
				{
					switch(mode)
						{
							case	tcpPort_COMMAND_TEXT:
									//--------------------------------------------
									//In text mode, read a line terminated by '\r'
									//--------------------------------------------
									result = clientSocket->Available;
									if (result>0)
									{
										byteCount = clientSocket->Receive( bytes );
										if (byteCount>0)
											getline(bytes, byteCount);
									}
									break;
							default:
									//-----------------------------------------------
									//In binary mode, read bytes and store in "inbuf"
									//-----------------------------------------------
									//array<Byte>^ bytes = gcnew array<Byte>(256);
									result = clientSocket->Available;
									if (result>0)
									{
										byteCount = clientSocket->Receive( bytes );
										for (ii=0;ii<byteCount;ii++)
											inbuf->Add(bytes[ii]);
									}

									break;
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
								clientSocket->Send( msg );
							}
						}
				}


				/*
				//TcpClient ^client = tcpListener->AcceptTcpClient();
				if (tcpListener&&tcpListenerStarted)
				{
					//serverSocket = tcpListener->AcceptSocket();
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
				*/
			}
		}

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
