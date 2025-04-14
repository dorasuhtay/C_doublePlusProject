#include <vcclr.h>  
#include <stdio.h>
#include <tchar.h>
#include "class_TCPsocket.h"
#include "stringconversion.h"
#include "iniprofile.h"
#include "socketfunction.h"
#include "ModelessMessageBox.h"
#include "wctStringList.h"
#include "mrt_X01netc.h"



#using <mscorlib.dll>

#pragma once


#define MAX_SOCKINBUFFSIZE		1024

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

/*
wchar_t connectButtonMsg[tcpSocket____MAXCOUNT][32] ={
	L"--",
	L"Connecting",
	L"CONNECTED",
	L"FAIL"
	};
*/


namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for tcpSocketTerminal
	/// </summary>
	public ref class tcpSocketTerminal : public System::Windows::Forms::Form
	{
	public:
		tcpSocketTerminal(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			porttype = 0;
			last_state = -1;
			tcpclientConnected = 0;
			port_Number = 0;
			ipaddressStr = "";
			inifilename = "";
			inisectionfilename = "";			
			inbuffptr = 0;
			inbuffptrMaxSize = MAX_SOCKINBUFFSIZE-1;
			inbuff = new unsigned char [MAX_SOCKINBUFFSIZE];
			inbuff[0] = 0;
			enableCRLF = 1;

			
			clientbuttonName = new wctStringList();
			serverbuttonName = new wctStringList();
			buttonName = serverbuttonName;

			clientbuttonName->add(L"Connect");
			clientbuttonName->add(L"Connecting");
			clientbuttonName->add(L"Disconnect");

			serverbuttonName->add(L"Start");
			serverbuttonName->add(L"Stop");
			serverbuttonName->add(L"Disconnect");

		}

		void setinifilename(String ^filename)	{ inifilename = filename; }
		void setinisectionname(String ^name)	{ inisectionfilename = name; }

	//--------------------------------------------------------
	//public variables
	//--------------------------------------------------------
	public: 
			System::Windows::Forms::ImageList^  waitIcon_imageList;
			bool enableCRLF;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~tcpSocketTerminal()
		{
			if (termPort&&termPort!=nullptr)
				termPort->Close();
			if (components)
			{
				delete components;
			}
			SAFE_DELETE(inbuff);
			SAFE_DELETE(clientbuttonName);
			SAFE_DELETE(serverbuttonName);
		
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected: 
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  connectToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  copyAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearHistoryToolStripMenuItem;
	private: System::Windows::Forms::ComboBox^  IPportcomboBox;
	private: System::Windows::Forms::ComboBox^  IPaddresscomboBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  Connectbutton;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  ClearAllButton;
	private: System::Windows::Forms::Button^  CopyAllButton;
	private: System::Windows::Forms::TextBox^  terminal_textBox;
	private: System::Windows::Forms::Button^  SendCommandbutton;
	private: System::Windows::Forms::ComboBox^  SendCommandcomboBox;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
			 
		
		int port_Number;
		String ^ipaddressStr;
		class_TCPsocket ^termPort;
		unsigned char *inbuff;
		int inbuffptr;
		int inbuffptrMaxSize;
		bool tcpclientConnected;
		Color ConnectButtonBackColor;
		String ^inifilename;
		String ^inisectionfilename;
		int last_state;
		int porttype;
		wctStringList *clientbuttonName;
		wctStringList *serverbuttonName;
		wctStringList *buttonName;
		int connectionstate;
		ModelessMessageBox ^progressBox;

	private: System::Windows::Forms::ComboBox^  PortTypecomboBox;
	private: System::Windows::Forms::Label^  label4;
			 


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->connectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->copyAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearHistoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->IPportcomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->IPaddresscomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Connectbutton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ClearAllButton = (gcnew System::Windows::Forms::Button());
			this->CopyAllButton = (gcnew System::Windows::Forms::Button());
			this->terminal_textBox = (gcnew System::Windows::Forms::TextBox());
			this->SendCommandbutton = (gcnew System::Windows::Forms::Button());
			this->SendCommandcomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->PortTypecomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->optionToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(724, 24);
			this->menuStrip1->TabIndex = 53;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->connectToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// connectToolStripMenuItem
			// 
			this->connectToolStripMenuItem->Name = L"connectToolStripMenuItem";
			this->connectToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->connectToolStripMenuItem->Text = L"&Connect";
			this->connectToolStripMenuItem->Click += gcnew System::EventHandler(this, &tcpSocketTerminal::connectToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->copyAllToolStripMenuItem, 
				this->clearAllToolStripMenuItem});
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->editToolStripMenuItem->Text = L"&Edit";
			// 
			// copyAllToolStripMenuItem
			// 
			this->copyAllToolStripMenuItem->Name = L"copyAllToolStripMenuItem";
			this->copyAllToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->copyAllToolStripMenuItem->Text = L"Copy A&ll";
			// 
			// clearAllToolStripMenuItem
			// 
			this->clearAllToolStripMenuItem->Name = L"clearAllToolStripMenuItem";
			this->clearAllToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->clearAllToolStripMenuItem->Text = L"Clea&r All";
			// 
			// optionToolStripMenuItem
			// 
			this->optionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->clearHistoryToolStripMenuItem});
			this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
			this->optionToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->optionToolStripMenuItem->Text = L"&Option";
			// 
			// clearHistoryToolStripMenuItem
			// 
			this->clearHistoryToolStripMenuItem->Name = L"clearHistoryToolStripMenuItem";
			this->clearHistoryToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->clearHistoryToolStripMenuItem->Text = L"&Clear History";
			// 
			// IPportcomboBox
			// 
			this->IPportcomboBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->IPportcomboBox->FormattingEnabled = true;
			this->IPportcomboBox->Location = System::Drawing::Point(288, 27);
			this->IPportcomboBox->Name = L"IPportcomboBox";
			this->IPportcomboBox->Size = System::Drawing::Size(107, 24);
			this->IPportcomboBox->TabIndex = 62;
			// 
			// IPaddresscomboBox
			// 
			this->IPaddresscomboBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->IPaddresscomboBox->FormattingEnabled = true;
			this->IPaddresscomboBox->Location = System::Drawing::Point(116, 27);
			this->IPaddresscomboBox->Name = L"IPaddresscomboBox";
			this->IPaddresscomboBox->Size = System::Drawing::Size(166, 24);
			this->IPaddresscomboBox->TabIndex = 61;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(116, 54);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(98, 12);
			this->label3->TabIndex = 60;
			this->label3->Text = L"IP Address (127.0.0.1)";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(286, 54);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(57, 12);
			this->label2->TabIndex = 59;
			this->label2->Text = L"Port Number";
			// 
			// Connectbutton
			// 
			this->Connectbutton->Location = System::Drawing::Point(401, 26);
			this->Connectbutton->Name = L"Connectbutton";
			this->Connectbutton->Size = System::Drawing::Size(77, 25);
			this->Connectbutton->TabIndex = 58;
			this->Connectbutton->Text = L"&Connect";
			this->Connectbutton->UseVisualStyleBackColor = true;
			this->Connectbutton->Click += gcnew System::EventHandler(this, &tcpSocketTerminal::Connectbutton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(558, 52);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 12);
			this->label1->TabIndex = 57;
			this->label1->Text = L"Copy to Clipboard";
			// 
			// ClearAllButton
			// 
			this->ClearAllButton->Location = System::Drawing::Point(641, 26);
			this->ClearAllButton->Name = L"ClearAllButton";
			this->ClearAllButton->Size = System::Drawing::Size(75, 23);
			this->ClearAllButton->TabIndex = 56;
			this->ClearAllButton->Text = L"Clear &All";
			this->ClearAllButton->UseVisualStyleBackColor = true;
			this->ClearAllButton->Click += gcnew System::EventHandler(this, &tcpSocketTerminal::ClearAllButton_Click);
			// 
			// CopyAllButton
			// 
			this->CopyAllButton->Location = System::Drawing::Point(560, 26);
			this->CopyAllButton->Name = L"CopyAllButton";
			this->CopyAllButton->Size = System::Drawing::Size(75, 23);
			this->CopyAllButton->TabIndex = 55;
			this->CopyAllButton->Text = L"Copy &All";
			this->CopyAllButton->UseVisualStyleBackColor = true;
			this->CopyAllButton->Click += gcnew System::EventHandler(this, &tcpSocketTerminal::CopyAllButton_Click);
			// 
			// terminal_textBox
			// 
			this->terminal_textBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->terminal_textBox->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->terminal_textBox->Location = System::Drawing::Point(12, 69);
			this->terminal_textBox->Multiline = true;
			this->terminal_textBox->Name = L"terminal_textBox";
			this->terminal_textBox->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->terminal_textBox->Size = System::Drawing::Size(700, 423);
			this->terminal_textBox->TabIndex = 54;
			this->terminal_textBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &tcpSocketTerminal::terminal_textBox_KeyPress);
			// 
			// SendCommandbutton
			// 
			this->SendCommandbutton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->SendCommandbutton->Location = System::Drawing::Point(13, 497);
			this->SendCommandbutton->Name = L"SendCommandbutton";
			this->SendCommandbutton->Size = System::Drawing::Size(49, 23);
			this->SendCommandbutton->TabIndex = 64;
			this->SendCommandbutton->Text = L"&Send";
			this->SendCommandbutton->UseVisualStyleBackColor = true;
			this->SendCommandbutton->Click += gcnew System::EventHandler(this, &tcpSocketTerminal::SendCommandbutton_Click);
			// 
			// SendCommandcomboBox
			// 
			this->SendCommandcomboBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->SendCommandcomboBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->SendCommandcomboBox->FormattingEnabled = true;
			this->SendCommandcomboBox->Location = System::Drawing::Point(68, 498);
			this->SendCommandcomboBox->Name = L"SendCommandcomboBox";
			this->SendCommandcomboBox->Size = System::Drawing::Size(643, 24);
			this->SendCommandcomboBox->TabIndex = 63;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &tcpSocketTerminal::timer1_Tick);
			// 
			// PortTypecomboBox
			// 
			this->PortTypecomboBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->PortTypecomboBox->FormattingEnabled = true;
			this->PortTypecomboBox->Location = System::Drawing::Point(13, 28);
			this->PortTypecomboBox->Name = L"PortTypecomboBox";
			this->PortTypecomboBox->Size = System::Drawing::Size(98, 24);
			this->PortTypecomboBox->TabIndex = 66;
			this->PortTypecomboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &tcpSocketTerminal::PortTypecomboBox_SelectedIndexChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(12, 55);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(25, 12);
			this->label4->TabIndex = 65;
			this->label4->Text = L"Type";
			// 
			// tcpSocketTerminal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(724, 557);
			this->Controls->Add(this->PortTypecomboBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->SendCommandbutton);
			this->Controls->Add(this->SendCommandcomboBox);
			this->Controls->Add(this->IPportcomboBox);
			this->Controls->Add(this->IPaddresscomboBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Connectbutton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ClearAllButton);
			this->Controls->Add(this->CopyAllButton);
			this->Controls->Add(this->terminal_textBox);
			this->Controls->Add(this->menuStrip1);
			this->Name = L"tcpSocketTerminal";
			this->Text = L"tcpSocketTerminal";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &tcpSocketTerminal::tcpSocketTerminal_FormClosed);
			this->Load += gcnew System::EventHandler(this, &tcpSocketTerminal::tcpSocketTerminal_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}


#pragma endregion
	private: System::Void tcpSocketTerminal_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				timer1->Enabled = true;
				timer1->Start();
				connectionstate = 0;
				this->Connectbutton->Text = gcnew String(reinterpret_cast<const wchar_t*>(buttonName->get(connectionstate)->wdata()));
				ConnectButtonBackColor = this->Connectbutton->BackColor;
				

				IPaddresscomboBox->Items->Add("127.0.0.1");
				//IPaddresscomboBox->Items->Add("192.168.1.9");
				//IPaddresscomboBox->Items->Add("192.168.1.2");
				PortTypecomboBox->Items->Add("Client");
				PortTypecomboBox->Items->Add("Server");
				if ((inifilename != "")&&(inisectionfilename != ""))
					LoadFromINI();
				setPortInterfaceMode(isock_CLIENT);
				setconnected(false);
			 }

	private: void Add2_IPAddressComboBox(String ^addr)
		 {
			if (addr!="")
			{
				int index = IPaddresscomboBox->FindString(addr);
				if (index<0)
					IPaddresscomboBox->Items->Add(addr);
			}
		 }
		
	private: void Add2_IPportComboBox(int port)
		 {
			if (port>0)
			{
				String ^portstr = port.ToString();
				int index = IPportcomboBox->FindString(portstr);
				if (index<0)
					IPportcomboBox->Items->Add(portstr);
			}
		 }

//public: delegate void CallbackFuncDelegate(DWORD ddStatus);

	private: void setPortInterfaceMode(int port_type)
			 {
				 if (port_type==isock_CLIENT)
				 {
					 buttonName = clientbuttonName;
				 }
				 else
				 {
					 buttonName = serverbuttonName;
				 }
			 }

	private: void ConnectCommand() 
		 {
			 CloseProgessBox();

			 switch(connectionstate)
			 {
				 case	0:
						ipaddressStr = IPaddresscomboBox->Text;
						port_Number = convertToInt32(IPportcomboBox->Text);
						Add2_IPAddressComboBox(ipaddressStr);
						Add2_IPportComboBox(port_Number);
						//String ^porttypeStr = PortTypecomboBox->Text;
						if (PortTypecomboBox->Text=="Client")
							porttype = isock_CLIENT;
						else
							porttype = isock_SERVER;

						setPortInterfaceMode(porttype);

						if ((port_Number>0)&&(ipaddressStr!=""))
						{
						//----------------------------------------			
						//Open a TCP server port As command Port
						//(Text port)
						//----------------------------------------	
						if (termPort&&(termPort!=nullptr))
							termPort->Close();
						termPort = gcnew class_TCPsocket();
						//termPort->setthread_callfunc(tcpSocketcallback);
						termPort->Name = "socket Terminal";
						termPort->setmode(tcpPort_COMMAND_TEXT);		//Text port
						termPort->Open(porttype, ipaddressStr, port_Number);
						//termPort->Open(isock_CLIENT, ipaddressStr, port_Number);
						termPort->setStartMessage("connected...\r\n");
						connectionstate++;
						}
						
						break;
				 case	1:
						if (termPort&&(termPort!=nullptr))
						{
							termPort->Close();
							connectionstate = 0;
							setconnected(false);
						}
						return;
				 case	2:
						connectionstate = 0;
						if (termPort&&(termPort!=nullptr))
						{
							termPort->Close();
							 //if (termPort->isconnected())
									
									//this->Connectbutton->Text = gcnew String(reinterpret_cast<const wchar_t*>(buttonName->get(connectionstate)->wdata()));
						}
						if (termPort->getSocketType()==isock_SERVER)
							connectionstate++;
						setconnected(false);
						break;
			 }
			 this->Connectbutton->Text = gcnew String(reinterpret_cast<const wchar_t*>(buttonName->get(connectionstate)->wdata()));
			 terminal_textBox->Focus();

			 //return;

/*
			 if (termPort&&(termPort!=nullptr))
			 {
				 if (termPort->getSocketType()==isock_SERVER)
				 {
					 if (termPort->isconnected())
					 {
						termPort->Close();
						connectionstate = 0;
						//this->Connectbutton->Text = gcnew String(reinterpret_cast<const wchar_t*>(buttonName->get(connectionstate)->wdata()));
						setconnected(false);
						return;
					 }
				 }
				 else
				 {
					 switch(termPort->getstate())
					 {
						
						 case	tcpSocket_CONNECTED:
						 case	tcpSocket_CONNECTING:
						 //case	tcpClient_CONNECTFAIL:
								termPort->Close();
								connectionstate = 0;
								this->Connectbutton->Text = gcnew String(reinterpret_cast<const wchar_t*>(buttonName->get(connectionstate)->wdata()));
								setconnected(false);
								return;
					 }
				 }
			 }

			 if (!tcpclientConnected)
			 {
				
				 ipaddressStr = IPaddresscomboBox->Text;
				 port_Number = convertToInt32(IPportcomboBox->Text);
				 Add2_IPAddressComboBox(ipaddressStr);
				 Add2_IPportComboBox(port_Number);
				 String ^porttypeStr = PortTypecomboBox->Text;
				 if (porttypeStr=="Client")
					 porttype = isock_CLIENT;
				 else
					 porttype = isock_SERVER;

				setPortInterfaceMode(porttype);

				 if ((port_Number>0)&&(ipaddressStr!=""))
				 {
					//----------------------------------------			
					//Open a TCP server port As command Port
					//(Text port)
					//----------------------------------------	
					 if (termPort&&termPort!=nullptr)
					 {
						termPort->Close();
						//connectionstate = 0;
						//this->Connectbutton->Text = gcnew String(reinterpret_cast<const wchar_t*>(buttonName->get(connectionstate)->wdata()));
					 }
					termPort = gcnew class_TCPsocket();
					//termPort->setthread_callfunc(tcpSocketcallback);
					termPort->Name = "socket Terminal";
					termPort->setmode(tcpPort_COMMAND_TEXT);		//Text port
					termPort->Open(porttype, ipaddressStr, port_Number);
					//termPort->Open(isock_CLIENT, ipaddressStr, port_Number);
					termPort->setStartMessage("connected...\r\n");
					connectionstate++;
					this->Connectbutton->Text = gcnew String(reinterpret_cast<const wchar_t*>(buttonName->get(connectionstate)->wdata()));


					
				 }
			 }
			 */
		 }
			 /*
	     void sr_Callback(int state)
        {

        }

	private: int testbb(int state)
			 {
				 return 1;
			 }*/

	private: void setconnected(bool connect)
			 {
				 tcpclientConnected = connect;
				 IPaddresscomboBox->Enabled = !connect;
				 IPportcomboBox->Enabled = !connect;
				 PortTypecomboBox->Enabled = !connect;
				 terminal_textBox->Enabled = connect;
				 SendCommandbutton->Enabled = connect;
				 SendCommandcomboBox->Enabled = connect;

				 this->Connectbutton->Text = gcnew String(reinterpret_cast<const wchar_t*>(buttonName->get(connectionstate)->wdata()));

				 if (!connect)
				 {
						this->Connectbutton->BackColor = ConnectButtonBackColor;
						
						
				 }
				 else
				 {
					 //this->Connectbutton->Text = gcnew String(reinterpret_cast<const wchar_t*>(buttonName->get(connectionstate)->wdata()));
					 if (termPort->getSocketType()==isock_SERVER)
					 {
						Color cColor = Color::FromArgb( 255, 255, 0 );
						this->Connectbutton->BackColor = cColor;
						
						//this->Connectbutton->Text = "&Stop";
					 }
					 else
					 {
						Color cColor = Color::FromArgb( 169, 223, 237 );
						this->Connectbutton->BackColor = cColor;
						//this->Connectbutton->Text = "Dis&connect";
					 }
				 }
			 }

	private: void CloseProgessBox()
			 {
				 if (progressBox&&(progressBox!=nullptr)&&progressBox->Created)
					progressBox->Close();
			 }

	private: bool isProgessBoxCancelled()
			 {
				if (progressBox&&(progressBox!=nullptr)&&progressBox->Created)
				{
					return progressBox->isCancelled();
				}
				return 0;
			 }

	private: void OpenProgessBox()
			 {
				String ^msg = "Connecting to " + ipaddressStr + " " + port_Number.ToString();
				if (progressBox&&(progressBox!=nullptr)&&progressBox->Created)
					progressBox->Close();
				progressBox = gcnew ModelessMessageBox(msg);
				progressBox->showCancelButton();
				//progressBox->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
				progressBox->setMessage2("Connecting...");
				progressBox->Opacity = 0.85;
				progressBox->setBackColor(Color::FromArgb( 255, 255, 183 ));
				progressBox->setMessage1Font(gcnew System::Drawing::Font( "Arial",14 ));
				progressBox->waitIcon_imageList = this->waitIcon_imageList;
				
				progressBox->Show();  

				//for (int ii=0;ii<5;ii++) 
					//Sleep(1000);
			 }






private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (termPort&&(termPort!=nullptr))
			{
				int cstate = termPort->getstate();
				if (last_state!=cstate)
				{
					Color cColor;
					switch(cstate)
					{
						case	tcpSocket_NULL:
								if (termPort->getSocketType()==isock_SERVER)
									connectionstate = 1;
								else
									connectionstate = 0;
								setconnected(false);
								break;
						case	tcpSocket_CONNECTING:
								//this->Connectbutton->Text = "&Connecting...";
								connectionstate=1;
								setconnected(false);
								OpenProgessBox();
								break;
						case	tcpSocket_CONNECTED:
								connectionstate++;
								setconnected(true);
								CloseProgessBox();
								break;
						case	tcpSocket_CONNECTFAIL:
								connectionstate = 0;
								setconnected(false);
								CloseProgessBox();
								terminal_textBox->Text += "\r\n***Connection to " + ipaddressStr + " " + port_Number.ToString() + " FAILED\r\n";
								break;
					}
					last_state = cstate;
				}

				//-----------------------------------------
				//if the user cancel the connection
				// while connection is in progress
				//-----------------------------------------
				if (isProgessBoxCancelled())
					ConnectCommand();

				//-----------------------------------------
				//if a connection is successful
				// check for available text response
				//-----------------------------------------
				if (termPort->connected())
					if (termPort->recv_TextAvailable())
					{
						//if available then place into textbox for display
						//-------------------------------------------------
						String ^commandstr = termPort->recv_String();
						if (enableCRLF)
							commandstr += "\r\n";
						terminal_textBox->Text += commandstr;
						terminal_textbox_append();
						//terminal_textbox_focus();
					}
			}
		 }


	private: System::Void terminal_textbox_append()
		 {
			 if (terminal_textBox&&(terminal_textBox!=nullptr))
			 {
				//terminal_textBox->Focus();
				terminal_textBox->Select(terminal_textBox->Text->Length, 0);
				terminal_textBox->ScrollToCaret();
			 }
		 }



private: System::Void terminal_textBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
		 {
			switch ( e->KeyChar )
			{
				// backspaces.
				case	'\b':
						if (inbuffptr>0)
							inbuffptr--;
						break;

				// ENTER keys.
				case	'\r':
						inbuff[inbuffptr++] = (unsigned char)e->KeyChar;
						inbuff[inbuffptr] = 0x0;
						char testbuf[128];
						strcpy(testbuf,(char *)inbuff);
						if (inbuffptr>1)
						{
							if(termPort&&(termPort!=nullptr)&&termPort->connected())
							for (int ii=0;ii<inbuffptr;ii++)
								termPort->putchar(inbuff[ii]);
						}
						inbuffptr = 0;
						break;

				// ESC key.  
				case	(char)27:
						
						break;

				default:
						inbuff[inbuffptr] = (unsigned char)e->KeyChar;
						inbuffptr = (inbuffptr+1)%inbuffptrMaxSize;
						inbuff[inbuffptr] = 0x0;
						break;
			}

		 }

	private: void LoadFromINI()
		{
			int ii;
			char* inifile = (char*)Marshal::StringToHGlobalAnsi(inifilename).ToPointer();
			char* inisection = (char*)Marshal::StringToHGlobalAnsi(inisectionfilename).ToPointer();
			char sectionHistory[128];
			strcpy(sectionHistory, inisection);
			strcat(sectionHistory,"_History");

			pIniFile *ini = new pIniFile();
			if (ini){
				ini->read(inifile);

				char value[512];
				char buf[128];
				//---------------------------------------
				//update IP address combo box
				//---------------------------------------
				ii = 0;
				while(1)
				{
					sprintf(buf, "ipaddr%03d",ii++); 
					ini->getText(sectionHistory, buf, value, sizeof(value), "");
					if (value[0]==0)
						break;
					if (isValid_ipv4_IpAddress(value))
					{
						String ^addr = gcnew String(reinterpret_cast<char*>(value));
						int index = IPaddresscomboBox->FindString(addr);
						if (index<0)
							IPaddresscomboBox->Items->Add(addr);
					}
				}
				//---------------------------------------
				//update IP port number combo box
				//---------------------------------------
				ii = 0;
				while(1)
				{
					sprintf(buf, "ipport%03d",ii++); 
					ini->getText(sectionHistory, buf, value, sizeof(value), "");
					if (value[0]==0)
						break;
					if (atoi(value)>0)
					{
						String ^portstr = gcnew String(reinterpret_cast<char*>(value));
						int index = IPportcomboBox->FindString(portstr);
						if (index<0)
							IPportcomboBox->Items->Add(portstr);
					}
				}

				//---------------------------------------
				//update sendcommand combo box
				//---------------------------------------
				ii = 0;
				while(1)
				{
					sprintf(buf, "sndcmd%03d",ii++); 
					ini->getText(sectionHistory, buf, value, sizeof(value), "");
					if (value[0]==0)
						break;
					//if (atoi(value)>0)
					//{
						String ^portstr = gcnew String(reinterpret_cast<char*>(value));
						int index = SendCommandcomboBox->FindString(portstr);
						if (index<0)
							SendCommandcomboBox->Items->Add(portstr);
					//}
				}
	
				
				//ini->setInt(inisection, "Numberof_CHAIN_LINKS", data.mNumberof_CHAIN_LINKS);
				//ini->setInt(inisection, "Max_Number_of_PUSHER", data.mMax_Number_of_PUSHER);
				//setINIchildWindowValues(ini, &data.setupInformationView);
  				//ini->setdouble("MBECoperationSet", "lostdataCountthreshold", "%8.2f", cnf->lostdataCountthreshold);

				delete ini;
				}
			
			Marshal::FreeHGlobal((IntPtr)inisection);
			Marshal::FreeHGlobal((IntPtr)inifile);
		}


	private: void Save2INI()
		{
			int ii;
			char buf[128];
			char* inifile = (char*)Marshal::StringToHGlobalAnsi(inifilename).ToPointer();
			char* inisection = (char*)Marshal::StringToHGlobalAnsi(inisectionfilename).ToPointer();
			char sectionHistory[128];
			strcpy(sectionHistory, inisection);
			strcat(sectionHistory,"_History");

			pIniFile *ini = new pIniFile();
			if (ini){
				ini->read(inifile);

				//---------------------------------------
				//remove sections from INI file
				//---------------------------------------
				ini->remove(sectionHistory);

				//---------------------------------------
				//save IP address from combo box
				//---------------------------------------
				for (ii=0;ii<IPaddresscomboBox->Items->Count;ii++)
				{
					String ^valuestr = IPaddresscomboBox->Items[ii]->ToString();
					char* value = (char*)Marshal::StringToHGlobalAnsi(valuestr).ToPointer();
					sprintf(buf, "ipaddr%03d",ii); 
					ini->setText(sectionHistory, buf, value);
					Marshal::FreeHGlobal((IntPtr)value);
				}

				//---------------------------------------
				//save IP port number from combo box
				//---------------------------------------								
				for (ii=0;ii<IPportcomboBox->Items->Count;ii++)
				{
					String ^valuestr = IPportcomboBox->Items[ii]->ToString();
					char* value = (char*)Marshal::StringToHGlobalAnsi(valuestr).ToPointer();
					sprintf(buf, "ipport%03d",ii); 
					ini->setText(sectionHistory, buf, value);
					Marshal::FreeHGlobal((IntPtr)value);
				}

				
				//---------------------------------------
				//save sendcommand from combo box
				//---------------------------------------								
				for (ii=0;ii<SendCommandcomboBox->Items->Count;ii++)
				{
					String ^valuestr = SendCommandcomboBox->Items[ii]->ToString();
					char* value = (char*)Marshal::StringToHGlobalAnsi(valuestr).ToPointer();
					sprintf(buf, "sndcmd%03d",ii); 
					ini->setText(sectionHistory, buf, value);
					Marshal::FreeHGlobal((IntPtr)value);
				}			

				//ini->setInt(inisection, "Numberof_CHAIN_LINKS", data.mNumberof_CHAIN_LINKS);
				//ini->setInt(inisection, "Max_Number_of_PUSHER", data.mMax_Number_of_PUSHER);

				//setINIchildWindowValues(ini, &data.setupInformationView);
				//
  				//ini->setdouble("MBECoperationSet", "lostdataCountthreshold", "%8.2f", cnf->lostdataCountthreshold);

				ini->write(inifile);

				delete ini;
				}
			
			Marshal::FreeHGlobal((IntPtr)inisection);
			Marshal::FreeHGlobal((IntPtr)inifile);
		}



private: System::Void tcpSocketTerminal_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
		 {
			 if (progressBox&&(progressBox!=nullptr)&&progressBox->Created)
				progressBox->Close();

			 if ((inifilename != "")&&(inisectionfilename != ""))
				 Save2INI();


			 if (termPort&&(termPort!=nullptr))
			 {
				termPort->Close();
				connectionstate = 0;
				//termPort->Dispose();
			}
		 }
		  
private: System::Void Connectbutton_Click(System::Object^  sender, System::EventArgs^  e) { ConnectCommand();	}
		
private: System::Void connectToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) { ConnectCommand();	}
	
private: System::Void PortTypecomboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			String ^porttypeStr = PortTypecomboBox->Text;
			if (porttypeStr=="Client")
				this->Connectbutton->Text = "&Connect";
			else
			{
				this->Connectbutton->Text = "&Start";
				IPaddresscomboBox->Text = "127.0.0.1";
			}
		 }
/*
private: int MakeTestX01(unsigned char *buf, unsigned char prefix, int node, const unsigned char *data)
		 {
			return 
		 }
*/
private: System::Void SendCommandbutton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			String ^sendstr = SendCommandcomboBox->Text;		//get the command from combobox
			if (sendstr!="")
			{
				//---------------------------------
				//send the command from combox box
				//---------------------------------
				if (termPort&&(termPort!=nullptr))
				{
					if (sendstr=="TestX01")
					{
						unsigned char buf[512];
						int result = wrapmrt_Xnetc((unsigned char *)"testdata", 8, buf, 0);
						//int result = MakeTestX01(buf, 'P', 4, (unsigned char *)"testdata");
						if (result>0)
							termPort->writeblock(buf, result);
					}
					else
						termPort->SendString(sendstr + "\r\n");
				}
				//---------------------------------
				//memorise into combobox
				//---------------------------------
				int index = SendCommandcomboBox->FindString(sendstr);
				if (index<0)
				{
					SendCommandcomboBox->Items->Add(sendstr);
				}
			}
		 }
	private: void CopyAll()
			{
			 	terminal_textBox->SelectAll();
				//textBox_OpStatus->SelectionLength();
				terminal_textBox->Copy();
				/*
				Clipboard::SetDataObject(dataObj, true);
				*/
				//textBox_OpStatus->ClearSelection();
				Color copyColor = Color::FromArgb( 183, 185, 255 );
				this->CopyAllButton->BackColor = copyColor;
				
				//terminal_textbox_focus();
			}

	private: void ClearAll() 
		 {
			terminal_textBox->Clear();
			Invalidate();
			//terminal_textbox_focus();
		 }


private: System::Void ClearAllButton_Click(System::Object^  sender, System::EventArgs^  e)	{ ClearAll(); }

private: System::Void CopyAllButton_Click(System::Object^  sender, System::EventArgs^  e)	{ CopyAll(); }
		 
};
}
