
#include <stdio.h>
#include <string.h>
#include "isocket.h"
#include <vcclr.h>
#include "lcircbuf.h"
#include "wctStringFifo.h"
#include "tcpCommon.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;

using namespace System::Threading;
//using System;
//using System.Text;
using namespace System::Runtime::InteropServices;

//#using <mscorlib.dll>
//#define textline_SIZE			1024

typedef unsigned long uint32;
typedef void (*type_IPCallBack) (uint32 object, uint32 event);

namespace common_ClassLib {

	/// <summary>
	/// Summary for class_TCPsocket
	/// </summary>
	public ref class class_TCPsocket :  public System::ComponentModel::Component
	{
	public:
		int index;
		bool CRLF_on;
		class_TCPsocket(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			//ID = 0;
			//retryCount = 0;
			//closeclientConnection = 0;
			CRLF_on = 0;
			authorizationLevel = 0;
			tx1_circbuf = 0;
			rx_circbuf = 0;
			thread_callfunc = 0;
			//connectEnable = 1;
			rxEnable = 1;
			txEnable = 1;
			sock = 0;
			socktype = isock_SERVER;
			ipaddress = "";
			nPort = 0;
			state = tcpSocket_NULL;
			Name = "tcpSocket";
			mode = tcpPort_BINARY;			
			StartMsg = "";
			last_Status = -1;
			connect_timeout = 3;

			sockresult = iSocket::CONNECT_ERR;

			//init cbuf
			LCircularBuf *cbf;
			cbf = new LCircularBuf();
			if (cbf) cbf->Init(4096);
			rx_circbuf = (void *)cbf;
			cbf = new LCircularBuf();
			if (cbf) cbf->Init(4096);
			tx1_circbuf = (void *)cbf;
			
			//textline = new wctString();
			recvbytes = new char [textline_SIZE+1];
			recvbytesptr = 0;

			inTextLines = new wctStringFifo();
			inTextLines->create(512);


		}
		class_TCPsocket(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}

	public: 
		String ^Name;
		int connect_timeout;
		 int authorizationLevel;
		
		void setStartMessage(String ^msg)
		{
			StartMsg = msg;
		}
		void setmode(int mode_) { mode = mode_;}
		int getmode() {return mode;}
		String ^getmodeStr()
		{
			if ((mode<0)||(mode>=tcpPort____MAX))
				return "---";
			return gcnew String(reinterpret_cast<const wchar_t*>(sockModeMsgString[mode]));
		}
		int getstate(){return state;}
		String ^getstateStr() {			if ((state>=0)&&(state<tcpSocket____MAXCOUNT))	return gcnew String(reinterpret_cast<const wchar_t*>(stateMsgString[state])); else return "";}
		String ^getSocketTypeStr() {	if ((socktype>=0)&&(socktype<isock____MAX))		return gcnew String(reinterpret_cast<const wchar_t*>(socktypeMsgString[socktype])); else return "";}
		int getSocketType() {return socktype;}
		int getport() {return nPort;}
		String ^getipaddress() {return ipaddress;}
		//isock_CLIENT, isock_SERVER, etc...
		void Open(int type, String ^ipaddr, int port)
			{
				if (port<=0) 
				{
					SAFE_DELETE(sock);
					return;
				}
				socktype = type;
				ipaddress = ipaddr;
				nPort = port;
				char* addr = (char*)Marshal::StringToHGlobalAnsi(ipaddress).ToPointer();
				if (socktype==isock_CLIENT)
   					sock = new iSocket(addr, nPort, 1);
				else
   					sock = new iSocket(addr, nPort, 0);

				//start the thread
				threadDelegate = gcnew ThreadStart( this, &class_TCPsocket::ThreadProc);
				socketthread = gcnew Thread(threadDelegate);
				socketthread->Start();

			}
		
		void ClearBuffers()
		{
			LCircularBuf *cbf;
			cbf = (LCircularBuf *)rx_circbuf;
			cbf->Clear();
			cbf = (LCircularBuf *)tx1_circbuf;
			cbf->Clear();

			recvbytesptr = 0;
			if (inTextLines)
				inTextLines->Clear();
		}

		int sconnect()
		{
			sockresult = 0;
			if (sock)
				sockresult = sock->sconnect();
		   return sockresult;
		}

		void DisConnect()
		{
			threadstarted = 0;
			if (sock)
				sock->disconnect();
//			while(!threadstopped)
//				Sleep(10);
		}


		void reconnect(int type, String ^ipaddress, int portnumber, int mode)
		{
			DisConnect();
			if (socketthread&&(socketthread!=nullptr))
				socketthread->Abort();
			SAFE_DELETE(sock);
			setmode(mode);		
			Open(type, ipaddress, portnumber);
			ClearBuffers();
		}

		int connected() {return isconnected();}
		bool isconnected()
		{
			iSocket *sock = getSock();
			if (sock&&sock->isConnected())
				return true;
			return false;
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

		int rxBytes() 
		{
			LCircularBuf *rxcbf = (LCircularBuf *)rx_circbuf;
			if (rxcbf)
				return rxcbf->bytesAvail();
			return 0;
		}

		void *getrxBuf() {return rx_circbuf;}


		void setrxEnable(int enable) {rxEnable = enable;}
		void settxEnable(int enable) {txEnable = enable;}
		int getrxEnable() {return rxEnable;}
		int gettxEnable() {return txEnable;}

		void setthread_callfunc(type_IPCallBack thread_callfunc_arg)
		{
			thread_callfunc = thread_callfunc_arg;
		}

		iSocket *getSock() {return sock;}

		int writesock(const unsigned char *buf, int len)
		{
		   if (sock&&txEnable&&(len>0))
			  return sock->write(buf, len);
		   return 0;
		}

		void clientConnect(int retry)
		{
			if (sock&&txEnable)
				sock->retryCount=retry;
			state = tcpSocket_NULL;
		}

		void SendString(String ^str)
		{
			if (str&&(str!=nullptr))
			{
				char* data = (char*)Marshal::StringToHGlobalAnsi(str).ToPointer();
				if (data)
					writesock((unsigned char *)data, strlen(data));
			}
		}

		bool recv_TextAvailable()
		{
			if (inTextLines)
				return inTextLines->available();
			else
				return 0;
		}

		wctString *getrecv_TextLine()
		{
			return inTextLines->get();
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

		void putchar(unsigned char ch)
		{
			writeblock(&ch, 1);
		}

		int writeblock(const unsigned char *buf, int len)
		{
		   if (txEnable) {
			  LCircularBuf *cbf = (LCircularBuf *)tx1_circbuf;
			  if (cbf){
				 cbf->Add(buf,len);
				 return len;
				 }
			  }
		   return 0;
		}



		void Close()
		{
			DisConnect();
			
			if (socketthread&&(socketthread!=nullptr))
				socketthread->Abort();

			SAFE_DELETE(sock);
			LCircularBuf *cbf;
			cbf = (LCircularBuf *)rx_circbuf;
			SAFE_DELETE(cbf);
			rx_circbuf = 0;
			cbf = (LCircularBuf *)tx1_circbuf;
			SAFE_DELETE(cbf);
			tx1_circbuf = 0;

			SAFE_DELETE(inTextLines);


			SAFE_DELETE(recvbytes); 

		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~class_TCPsocket()
		{
			Close();
			
			if (components)
			{
				delete components;
			}
			
		}

/*
		int CloseSocket()
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
		*/
private: System::ComponentModel::IContainer^  components;
protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


		type_IPCallBack thread_callfunc;
		ThreadStart^ threadDelegate; 
		Thread^ socketthread; 
		iSocket *sock;
		bool threadstarted;
		bool threadstopped;
		//int closeclientConnection;
		//bool connectEnable;
		String ^ipaddress;
		int nPort;
		int socktype;                   //isock_CLIENT, isock_SERVER, etc...
		int sockresult;					//if <0 (error) one of the following
													 //iSocket::SOCKET_ERR,
													 //iSocket::SETSOCKOPT_ERR,
													 //iSocket::LISTEN_ERR,
													 //iSocket::ACCEPT_ERR,
													 //iSocket::INET_ADDR_ERR,
													 //iSocket::CONNECT_ERR,
													 //iSocket::PORT_ERR
		void *tx1_circbuf;
		void *rx_circbuf;
		int rxEnable;
		int txEnable;
		int last_Status;
		int state;
		int mode;		//tcpPort_COMMAND_TEXT, tcpPort_BINARY
		String ^StartMsg;
		//wctString	*textline;
		wctStringFifo *inTextLines;
		char *recvbytes;
		int recvbytesptr;
		//int retryCount;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{

		}
#pragma endregion

	//--------------------------------------------------------
	//handling of bytes that forms a line
	//  receive the bytes and store in recvbytes[] 
	//  until CR '\r'
	//--------------------------------------------------------
	void getline(const unsigned char *bytes, int byteCount)
		{
			char ch;
			for (int ii=0;ii<byteCount;ii++)
			{
				ch = bytes[ii];
				switch(ch)
				{
					case	'\r':		//line terminator
							{
								//pin_ptr<const wchar_t> wch = PtrToStringChars(textline);
								//wctString str;
								//str = recvbytes;
								inTextLines->put(recvbytes);
								if (CRLF_on)
									inTextLines->put("\r\n");
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

	void ThreadProc()
	{

		unsigned char out[2048];
		LCircularBuf *txcbf = (LCircularBuf *)tx1_circbuf;
		LCircularBuf *rxcbf = (LCircularBuf *)rx_circbuf;

		/*running = 1;
		thread_callfunc((uint32) this, IPNET_THREADSTARTED);
		*/


		threadstopped = 0;
		threadstarted = 1;
		while(threadstarted)
		{
			Thread::Sleep(10);
			iSocket *sock = getSock();
			if (sock)
			{
					if (!sock->isConnected())
					{
						if (socktype==isock_SERVER)
						{
							state = tcpSocket_NULL;
							sock->sconnect();
						}
						else
						{
							state = tcpSocket_CONNECTING;
							
							sock->clientconnect(sock->getipaddress(), nPort, connect_timeout);

				
							if (!sock->isConnected())
							{
								if (sock->retryCount<=0)
								{
									state = tcpSocket_CONNECTFAIL;
									while(state == tcpSocket_CONNECTFAIL)
									{
										Thread::Sleep(10);
									}
									if (sock->retryCount>-9)
										sock->retryCount--;
								}
							}
							
						}
						//thread_callfunc((uint32) this, IPNET_DISCONNECTED);
					}
					else
            		{
						if (StartMsg != "")
						{
							char* data = (char*)Marshal::StringToHGlobalAnsi(StartMsg).ToPointer();
							writesock((unsigned char *)data, strlen(data));
						}
						if (txcbf)
							txcbf->Clear();   //clears the buffer for a fresh new connection
						state = tcpSocket_CONNECTED;
						while (sock->isConnected())
						{
							//--- sends whatever data available ----------------------------------
							if (txcbf)
							{
								int result;
								while(txcbf->bytesAvail())
								{
									result = txcbf->Read(out, 2047);		//read from the circular buffer
									if (result>0)
									writesock(out, result);
									Thread::Sleep(10);                     //sleep for a while
								}
							}
							//----------
							//receive
							//-----------
							int result = sock->read(1, 100);       //reponse to 1 bytes or 100ms from client
							if(result > 0)
							{
								if (result>sock->getinbufSize())
									result=sock->getinbufSize();
								//--- stores up the incoming data ------------------------------------
								if (rxcbf&&(result>0)&&rxEnable)
								{
									switch(mode)
									{
										case	tcpPort_COMMAND_TEXT:getline(sock->getinbuf(), result);break;
										default:rxcbf->Add(sock->getinbuf(), result);break;
									}
								}
							}
							//thread_callfunc((uint32) this, IPNET_CONNECTED);
						}
					}
			}
/*			
			if (closeclientConnection)
			{
				CloseSocket();
				closeclientConnection = 0;
			}
			*/
		}
		threadstopped = 1;
	}



};


}
