#include "class_TCPsocket.h"
#include "class_cmdLogList.h"
#pragma once

#define MAX_TCPSOCKET_ARRAY_SIZE		128

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;

enum{
	sckLOG_null=0,
	sckLOG_pusherCounter,
	sckLOG_dateTime,
	sckLOG____TOTAL_MAX
};

namespace common_ClassLib {

	/// <summary>
	/// Summary for class_TCPsocketList
	/// </summary>
	public ref class class_TCPsocketList :  public System::ComponentModel::Component
	{
	public:
		class_TCPsocketList(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			//tcpsock = tcpsocket();
			cmdLogList = new class_cmdLogList();
			tcpsock = gcnew array<class_TCPsocket ^>(MAX_TCPSOCKET_ARRAY_SIZE);

			secondcounter = 0;
			//log_rate = new int [sckLOG____TOTAL_MAX];
			unlogall();
		}
		class_TCPsocketList(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~class_TCPsocketList()
		{
			Close();
			//delete log_rate;
			delete cmdLogList;
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

		int count;
		
		
		//Array
		array<class_TCPsocket ^>^ tcpsock;
		/*
		array<class_TCPsocket ^>^ tcpsocket(){
			int ii;
			array<class_TCPsocket ^>^ local = gcnew array<class_TCPsocket ^>(MAX_TCPSOCKET_ARRAY_SIZE);
			
			for (ii=0;ii<MAX_TCPSOCKET_ARRAY_SIZE;ii++)
			{
				local[ii] = gcnew class_TCPsocket;
				local[ii]->index = ii;
			}
		
			return local;
		}
		*/
	private: class_cmdLogList *cmdLogList;

	//private: int *log_rate;
	private: int secondcounter;
	public: int OnsecondEvent()
			{
				if(!cmdLogList) return 0;
				secondcounter++;
				int ii;
				int ref, cmd_enum, second;
				for (ii=0;ii<cmdLogList->getcount();ii++)
				{
					if (cmdLogList->get(ii, &ref, &cmd_enum, &second))
					{
						if (ref<0) continue;
						if (ref>=MAX_TCPSOCKET_ARRAY_SIZE) continue;
						if (cmd_enum>=sckLOG____TOTAL_MAX) continue;
						if (cmd_enum<0) continue;
						if (second<=0) continue;
						if ((secondcounter%second)==0)
							return 1;
					}
				}
				return 0;
			}

	public: void unlogall()
			{
				if(cmdLogList)
					cmdLogList->Clear();
				/*
				int ii;
				for (ii=0;ii<sckLOG____TOTAL_MAX;ii++)
					log_rate[ii] = 0;
					*/
			}
			
	public: int getLogcmdCount()
			{
				if (!cmdLogList) return 0;
				return cmdLogList->getcount();
			}

	public: int onEventLogcmd(int index, int *ref, int *cmd_enum)
			{
				if (!cmdLogList) return 0;
				int sec;
				if (cmdLogList->get(index, ref, cmd_enum, &sec))
				{
					if (sec>0)
					{
						if ((secondcounter%sec)==0)
							return 1;
					}
				}
				return 0;
			}
/*
	public: int LOG_cmd(int LOGcmd_index)
			{
				if (!cmdLogList) return 0;

				int ref, cmd_enum, second;
				for (ii=0;ii<cmdLogList->getcount();ii++)
				{
					if (cmdLogList->get(ii, &ref, &cmd_enum, &second))


				if (log_rate[LOGcmd_index]>0)
				{
					if ((secondcounter%log_rate[LOGcmd_index])==0)
						return 1;
				}
				return 0;
			}
*/
	public: void AddLogCmd(int portindex, int cmd_enum, int second)
			{
				if(cmdLogList)
				{
					int foundindex = -1;
					if (count>1)
						foundindex = cmdLogList->find(portindex, cmd_enum);
					if (foundindex>=0)
						cmdLogList->Set(foundindex, portindex, cmd_enum, second);
					else
						cmdLogList->Add(portindex, cmd_enum, second);
				}
			}
	/*public: void setlog_rate(int index, int cmdindex, int time_second)
			{
				if (cmdindex<0) return;
				if (cmdindex>=sckLOG____TOTAL_MAX) return;
				log_rate[cmdindex] = time_second;
			}
			*/


	//Add(isock_SERVER, "127.0.0.1", 12101, tcpPort_COMMAND_TEXT)
	public: int Add(int type, String ^ipaddress, int portnumber, int mode)
			{
				if (portnumber<=0) 
					return -1;
				int nn = count;
				if (count>=MAX_TCPSOCKET_ARRAY_SIZE) return -1;
				tcpsock[count] = gcnew class_TCPsocket;
				if (tcpsock[count]==nullptr) return -2;

				tcpsock[count]->index = count;
				tcpsock[count]->Name = "Aux Command Port";
				tcpsock[count]->setmode(mode);		
				tcpsock[count]->Open(type, ipaddress, portnumber);
				tcpsock[count]->setStartMessage("connected <"+portnumber+">...\r\n");
				count++;

				return nn;
			}

	public: void reconnect(int index, int type, String ^ipaddress, int portnumber, int mode)
			{
				if (index<0) return;
				if (index>count) return;
				tcpsock[index]->reconnect(type, ipaddress, portnumber, mode);
				//tcpsock[index]->Close();
				//tcpsock[index]->setmode(mode);	
				//tcpsock[index]->Open(type, ipaddress, portnumber);
			}

	public: void setStartMessage(int index, String ^msg)
			{
				if ((index>=0)&&(index<count))
				{
					if (tcpsock[index]&&(tcpsock[index]!=nullptr))
						tcpsock[index]->setStartMessage(msg);
				}
			}

	public: class_TCPsocket ^get(int index)
			{
				if ((index>=0)&&(index<count))
				{
					if (tcpsock[index]&&(tcpsock[index]!=nullptr))
						return tcpsock[index];
				}
				return nullptr;
			}

	public: int findPort(int portnumber, int startfrom)
			{
				int ii;
				
				for (ii=startfrom;ii<count;ii++)
				{
					if (tcpsock[ii]&&(tcpsock[ii]!=nullptr))
						if (tcpsock[ii]->getport()==portnumber)
							return ii;
				}
				return -1;
			}

	public: int findPort(String ^ipaddress, int portnumber, int startfrom)
			{
				int ii;
				for (ii=startfrom;ii<count;ii++)
				{
					if (tcpsock[ii]&&(tcpsock[ii]!=nullptr))
						if (tcpsock[ii]->getport()==portnumber)
							if (tcpsock[ii]->getipaddress()==ipaddress)
								return ii;
				}
				return -1;
			}

	public: int isconnected(String ^ipaddress, int portnumber, int startfrom)
			{
				int ii;
				for (ii=startfrom;ii<count;ii++)
				{
					if (tcpsock[ii]&&(tcpsock[ii]!=nullptr))
						if (tcpsock[ii]->getport()==portnumber)
							if (tcpsock[ii]->getipaddress()==ipaddress)
								return tcpsock[ii]->connected();
				}
				return 0;
			}




	public: int findSocketType(int type, int startfrom)
			{
				int ii;
				for (ii=startfrom;ii<count;ii++)
				{
					if (tcpsock[ii]&&(tcpsock[ii]!=nullptr))
						if (tcpsock[ii]->getSocketType()==type)
							return ii;
				}
				return -1;
			}

	public: int findmode(int mode, int startfrom)
			{
				int ii;
				
				for (ii=startfrom;ii<count;ii++)
				{
					if (tcpsock[ii]&&(tcpsock[ii]!=nullptr))
						if (tcpsock[ii]->getmode()==mode)
							return ii;
				}
				return -1;
			}
		
			

	public: int getcount()	{return count;}
	public: void Close()
			{
				int ii;
				for (ii=0;ii<count;ii++)
				{
					if (tcpsock[ii]&&(tcpsock[ii]!=nullptr))
						tcpsock[ii]->Close();
				}
			}



	private: void Testfunc()
			{
				int ii;
				for (ii=0;ii<MAX_TCPSOCKET_ARRAY_SIZE;ii++)
				{
					if (tcpsock[ii]&&(tcpsock[ii]!=nullptr))
						tcpsock[ii]->index;
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
