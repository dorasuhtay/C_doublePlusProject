#include <vcclr.h>  
#include <stdio.h>
#include "class_TCPclient.h"
#include "stringconversion.h"
#include "iniprofile.h"
#include "socketfunction.h"
#include "ModelessMessageBox.h"


#using <mscorlib.dll>

//#pragma comment(lib, "Ws2_32.lib")
//#using <Ws2_32.dll>
//Ws2_32.lib

#pragma once

#define MAX_INBUFFSIZE		1024

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}




namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;


	/// <summary>
	/// Summary for tcpClientTerminal
	/// </summary>
	public ref class tcpClientTerminal : public System::Windows::Forms::Form
	{
	public:
		tcpClientTerminal(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			last_state = -1;
			tcpclientConnected = 0;
			port_Number = 0;
			ipaddressStr = "";
			inifilename = "";
			inisectionfilename = "";			
			inbuffptr = 0;
			inbuffptrMaxSize = MAX_INBUFFSIZE-1;
			inbuff = new unsigned char [MAX_INBUFFSIZE];
			inbuff[0] = 0;
		}

		void setinifilename(String ^filename)	{ inifilename = filename; }
		void setinisectionname(String ^name)	{ inisectionfilename = name; }
	//--------------------------------------------------------
	//public variables
	//--------------------------------------------------------
	public: 
			System::Windows::Forms::ImageList^  waitIcon_imageList;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~tcpClientTerminal()
		{
			if (components)
			{
				delete components;
			}
			SAFE_DELETE(inbuff);
		}
	private: System::Windows::Forms::TextBox^  terminal_textBox;
	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  ClearAllButton;
	private: System::Windows::Forms::Button^  CopyAllButton;



	private: System::Windows::Forms::Button^  Connectbutton;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


		int port_Number;
		String ^ipaddressStr;
		class_TCPclient ^termPort;
		unsigned char *inbuff;
		int inbuffptr;
		int inbuffptrMaxSize;
		bool tcpclientConnected;
		Color ConnectButtonBackColor;
		String ^inifilename;
		String ^inisectionfilename;
		int last_state;
		ModelessMessageBox ^progressBox;

	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ComboBox^  IPaddresscomboBox;
	private: System::Windows::Forms::ComboBox^  IPportcomboBox;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearHistoryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  copyAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  connectToolStripMenuItem;
	private: System::Windows::Forms::ComboBox^  SendCommandcomboBox;
	private: System::Windows::Forms::Button^  SendCommandbutton;
			 

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->terminal_textBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ClearAllButton = (gcnew System::Windows::Forms::Button());
			this->CopyAllButton = (gcnew System::Windows::Forms::Button());
			this->Connectbutton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->IPaddresscomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->IPportcomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->connectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->copyAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearHistoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->SendCommandcomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->SendCommandbutton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// terminal_textBox
			// 
			this->terminal_textBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->terminal_textBox->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->terminal_textBox->Location = System::Drawing::Point(12, 70);
			this->terminal_textBox->Multiline = true;
			this->terminal_textBox->Name = L"terminal_textBox";
			this->terminal_textBox->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->terminal_textBox->Size = System::Drawing::Size(600, 412);
			this->terminal_textBox->TabIndex = 22;
			this->terminal_textBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &tcpClientTerminal::terminal_textBox_KeyDown);
			this->terminal_textBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &tcpClientTerminal::terminal_textBox_KeyPress);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(454, 52);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 12);
			this->label1->TabIndex = 42;
			this->label1->Text = L"Copy to Clipboard";
			// 
			// ClearAllButton
			// 
			this->ClearAllButton->Location = System::Drawing::Point(537, 26);
			this->ClearAllButton->Name = L"ClearAllButton";
			this->ClearAllButton->Size = System::Drawing::Size(75, 23);
			this->ClearAllButton->TabIndex = 41;
			this->ClearAllButton->Text = L"Clear &All";
			this->ClearAllButton->UseVisualStyleBackColor = true;
			this->ClearAllButton->Click += gcnew System::EventHandler(this, &tcpClientTerminal::ClearAllButton_Click);
			// 
			// CopyAllButton
			// 
			this->CopyAllButton->Location = System::Drawing::Point(456, 26);
			this->CopyAllButton->Name = L"CopyAllButton";
			this->CopyAllButton->Size = System::Drawing::Size(75, 23);
			this->CopyAllButton->TabIndex = 40;
			this->CopyAllButton->Text = L"Copy &All";
			this->CopyAllButton->UseVisualStyleBackColor = true;
			this->CopyAllButton->Click += gcnew System::EventHandler(this, &tcpClientTerminal::CopyAllButton_Click);
			// 
			// Connectbutton
			// 
			this->Connectbutton->Location = System::Drawing::Point(297, 26);
			this->Connectbutton->Name = L"Connectbutton";
			this->Connectbutton->Size = System::Drawing::Size(77, 25);
			this->Connectbutton->TabIndex = 47;
			this->Connectbutton->Text = L"&Connect";
			this->Connectbutton->UseVisualStyleBackColor = true;
			this->Connectbutton->Click += gcnew System::EventHandler(this, &tcpClientTerminal::Connectbutton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(182, 54);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(57, 12);
			this->label2->TabIndex = 48;
			this->label2->Text = L"Port Number";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(12, 54);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(98, 12);
			this->label3->TabIndex = 49;
			this->label3->Text = L"IP Address (127.0.0.1)";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &tcpClientTerminal::timer1_Tick);
			// 
			// IPaddresscomboBox
			// 
			this->IPaddresscomboBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->IPaddresscomboBox->FormattingEnabled = true;
			this->IPaddresscomboBox->Location = System::Drawing::Point(12, 27);
			this->IPaddresscomboBox->Name = L"IPaddresscomboBox";
			this->IPaddresscomboBox->Size = System::Drawing::Size(166, 24);
			this->IPaddresscomboBox->TabIndex = 50;
			// 
			// IPportcomboBox
			// 
			this->IPportcomboBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->IPportcomboBox->FormattingEnabled = true;
			this->IPportcomboBox->Location = System::Drawing::Point(184, 27);
			this->IPportcomboBox->Name = L"IPportcomboBox";
			this->IPportcomboBox->Size = System::Drawing::Size(107, 24);
			this->IPportcomboBox->TabIndex = 51;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->optionToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(624, 24);
			this->menuStrip1->TabIndex = 52;
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
			this->connectToolStripMenuItem->Click += gcnew System::EventHandler(this, &tcpClientTerminal::connectToolStripMenuItem_Click);
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
			this->copyAllToolStripMenuItem->Click += gcnew System::EventHandler(this, &tcpClientTerminal::copyAllToolStripMenuItem_Click);
			// 
			// clearAllToolStripMenuItem
			// 
			this->clearAllToolStripMenuItem->Name = L"clearAllToolStripMenuItem";
			this->clearAllToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->clearAllToolStripMenuItem->Text = L"Clea&r All";
			this->clearAllToolStripMenuItem->Click += gcnew System::EventHandler(this, &tcpClientTerminal::clearAllToolStripMenuItem_Click);
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
			this->clearHistoryToolStripMenuItem->Click += gcnew System::EventHandler(this, &tcpClientTerminal::clearHistoryToolStripMenuItem_Click);
			// 
			// SendCommandcomboBox
			// 
			this->SendCommandcomboBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->SendCommandcomboBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->SendCommandcomboBox->FormattingEnabled = true;
			this->SendCommandcomboBox->Location = System::Drawing::Point(69, 488);
			this->SendCommandcomboBox->Name = L"SendCommandcomboBox";
			this->SendCommandcomboBox->Size = System::Drawing::Size(543, 24);
			this->SendCommandcomboBox->TabIndex = 53;
			// 
			// SendCommandbutton
			// 
			this->SendCommandbutton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->SendCommandbutton->Location = System::Drawing::Point(14, 487);
			this->SendCommandbutton->Name = L"SendCommandbutton";
			this->SendCommandbutton->Size = System::Drawing::Size(49, 23);
			this->SendCommandbutton->TabIndex = 54;
			this->SendCommandbutton->Text = L"&Send";
			this->SendCommandbutton->UseVisualStyleBackColor = true;
			this->SendCommandbutton->Click += gcnew System::EventHandler(this, &tcpClientTerminal::SendCommandbutton_Click);
			// 
			// tcpClientTerminal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 536);
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
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"tcpClientTerminal";
			this->Text = L"tcpClientTerminal";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &tcpClientTerminal::tcpClientTerminal_FormClosed);
			this->Load += gcnew System::EventHandler(this, &tcpClientTerminal::tcpClientTerminal_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void tcpClientTerminal_Load(System::Object^  sender, System::EventArgs^  e) 
			 {

				timer1->Enabled = true;
				timer1->Start();

				 //port_Number = 7000;
				//ipaddressStr = "127.0.0.1";
				//IPaddresstextBox->Text = ipaddressStr;
				//IPportTextBox->Text = port_Number.ToString();

				ConnectButtonBackColor = this->Connectbutton->BackColor;


				IPaddresscomboBox->Items->Add("127.0.0.1");
				//IPaddresscomboBox->Items->Add("192.168.1.9");
				//IPaddresscomboBox->Items->Add("192.168.1.2");
				if ((inifilename != "")&&(inisectionfilename != ""))
					LoadFromINI();

				setconnected(false);
					
			 }
/*
	private: System::Void IPaddresstextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
			 {
				 ipaddressStr = IPaddresstextBox->Text;
			 }
			 */
			 /*
private: System::Void IPportTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
				port_Number = convertToInt32(IPportTextBox->Text);
		 }
		 */
		 

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


	private: void ConnectCommand() 
		 {
			 //CallbackFuncDelegate(0);
			 CloseProgessBox();

			 if (termPort&&(termPort!=nullptr))
			 {
				 switch(termPort->getstate())
				 {
					 case	tcpClient_CONNECTED:
					 case	tcpClient_CONNECTING:
					 //case	tcpClient_CONNECTFAIL:
							termPort->Close();
							setconnected(false);
							return;
				 }
			 }

			 if (!tcpclientConnected)
			 {
				 ipaddressStr = IPaddresscomboBox->Text;
				 port_Number = convertToInt32(IPportcomboBox->Text);
				 Add2_IPAddressComboBox(ipaddressStr);
				 Add2_IPportComboBox(port_Number);

				 if ((port_Number>0)&&(ipaddressStr!=""))
				 {
					//----------------------------------------			
					//Open a TCP server port As command Port
					//(Text port)
					//----------------------------------------	
					termPort = gcnew class_TCPclient();
					
					//termPort->Callback += gcnew class_TCPclient::CallbackEventHandler(&BTREKCANDAEMONV1::tcpClientTerminal::sr_Callback);
					/*
            ServerRequest sr = new ServerRequest();
            sr.Callback += new ServerRequest.CallbackEventHandler(sr_Callback);
            sr.DoRequest("myrequest");
			*/

//					termPort->Callback = &BTREKCANDAEMONV1::tcpClientTerminal::sr_Callback;
					//termPort->Callback += gcnew class_TCPclient::CallbackEventHandler(sr_Callback);
            //sr.DoRequest("myrequest");

					//termPort->funcP = &BTREKCANDAEMONV1::tcpClientTerminal::testbb;
					//termPort->connectionCallBackfunction = &BTREKCANDAEMONV1::tcpClientTerminal::Work::tcpclientconnectionCallBack;
					termPort->Name = "Client Terminal";
					termPort->setmode(tcpPort_COMMAND_TEXT);		//Text port
					int result = termPort->Open_IP_port(ipaddressStr, port_Number);
					terminal_textBox->Focus();
				 }
			 }
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
				 terminal_textBox->Enabled = connect;
				 SendCommandbutton->Enabled = connect;
				 SendCommandcomboBox->Enabled = connect;
				 if (!connect)
				 {
						this->Connectbutton->BackColor = ConnectButtonBackColor;
						this->Connectbutton->Text = "&Connect";
				 }
				 else
				 {
						Color cColor = Color::FromArgb( 169, 223, 237 );
						this->Connectbutton->BackColor = cColor;
						this->Connectbutton->Text = "Dis&connect";
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
				//progressBox->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
				progressBox->setMessage2("Connecting...");
				progressBox->Opacity = 0.85;
				progressBox->setBackColor(Color::FromArgb( 255, 255, 183 ));
				progressBox->setMessage1Font(gcnew System::Drawing::Font( "Arial",14 ));
				progressBox->showCancelButton();
				progressBox->waitIcon_imageList = this->waitIcon_imageList;
				progressBox->Show();
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
						case	tcpClient_CONNECTING:
								this->Connectbutton->Text = "&Connecting...";
								OpenProgessBox();
								break;
						case	tcpClient_CONNECTED:
								setconnected(true);
								CloseProgessBox();
								break;
						case	tcpClient_CONNECTFAIL:
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
						//terminal_textbox_focus();
						terminal_textBox->Text += commandstr;
						terminal_textbox_append();
						//terminal_textbox_focus();
					}
			}
		 }


private: System::Void terminal_textBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
		 {
			 /*
			 return;
			       // Initialize the flag to false.
     // nonNumberEntered = false;
			 if ( e->KeyCode == Keys::ShiftKey)
				 return;
		// if ( e->KeyCode < Keys::D0 || e->KeyCode > Keys::D9 )
		//	 return;
			 //if ( e->KeyCode == Keys::F1 && (e->Alt || e->Control || e->Shift) )
			 //if ( e->KeyCode == Keys::F2 && e->Modifiers == Keys::Alt )
		 if ( e->KeyCode == Keys::Back )// Determine whether the keystroke is a backspace.
		 {
			 if (inbuffptr>0)
				 inbuffptr--;
			 return;
		 }
		 if ( e->KeyCode == Keys::Enter )// Determine whether the keystroke is a Enter.
		 {
			 inbuff[inbuffptr++] = (unsigned char)e->KeyCode;
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
			 return;
		 }


      // Determine whether the keystroke is a number from the top of the keyboard.
      if ( e->KeyCode < Keys::D0 || e->KeyCode > Keys::D9 )
      {
         // Determine whether the keystroke is a number from the keypad.
         if ( e->KeyCode < Keys::NumPad0 || e->KeyCode > Keys::NumPad9 )
         {
            // Determine whether the keystroke is a backspace.
            if ( e->KeyCode != Keys::Back )
            {
               // A non-numerical keystroke was pressed.
               // Set the flag to true and evaluate in KeyPress event.
               nonNumberEntered = true;
            }
         }
      }*/
      //If shift key was pressed, it's not a number.
      //if (Control::ModifierKeys == Keys::Shift) {
         //nonNumberEntered = true;
   
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



	private: System::Void terminal_textbox_append()
		 {
			 if (terminal_textBox&&(terminal_textBox!=nullptr))
			 {
				//terminal_textBox->Focus();
				terminal_textBox->Select(terminal_textBox->Text->Length, 0);
				terminal_textBox->ScrollToCaret();
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

	private: System::Void CopyAllButton_Click(System::Object^  sender, System::EventArgs^  e)  				{ CopyAll(); }
	private: System::Void copyAllToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)	{ CopyAll(); }
	private: System::Void ClearAllButton_Click(System::Object^  sender, System::EventArgs^  e)				{ ClearAll(); } 
	private: System::Void clearAllToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)	{ ClearAll(); }
	private: System::Void connectToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)	{ ConnectCommand();	}
	private: System::Void Connectbutton_Click(System::Object^  sender, System::EventArgs^  e)				{ ConnectCommand();	} 

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

private: System::Void tcpClientTerminal_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
		 {
			 if (progressBox&&(progressBox!=nullptr)&&progressBox->Created)
				progressBox->Close();

			 if ((inifilename != "")&&(inisectionfilename != ""))
				 Save2INI();


			 if (termPort&&(termPort!=nullptr))
				termPort->Close();
		 }
/*
private: System::Void IPaddresscomboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			// int selectedIndex = IPaddresscomboBox->SelectedIndex;
			// Object^ selectedItem = IPaddresscomboBox->SelectedItem;
			/// MessageBox::Show( "Selected Item Text: " + selectedItem->ToString() + "\n" +
			//"Index: " + selectedIndex.ToString() );
		 }
		
private: System::Void IPaddresscomboBox_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //int selectedIndex = IPaddresscomboBox->SelectedIndex;
			// MessageBox::Show( "Item Text: " + IPaddresscomboBox->Text + "\n" +
			//"Index: " + selectedIndex.ToString() );
		 }
		
private: System::Void IPaddresscomboBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			// int selectedIndex = IPaddresscomboBox->SelectedIndex;
			// MessageBox::Show( "Item changedText: " + IPaddresscomboBox->Text + "\n" +
			//"Index: " + selectedIndex.ToString() );
		 }
		
private: System::Void IPaddresscomboBox_TextUpdate(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //int index = comboBox1->FindString( textBox2->Text );
			// int selectedIndex = IPaddresscomboBox->SelectedIndex;
			// MessageBox::Show( "Item uodateText: " + IPaddresscomboBox->Text + "\n" +
			//"Index: " + selectedIndex.ToString() );
		 }
		 */

private: System::Void clearHistoryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
				 String^ message = "Clear All History?";
				 String^ caption = Text;
				 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				 System::Windows::Forms::DialogResult result;
				 // Displays the MessageBox.
				 result = MessageBox::Show( this, message, caption, buttons, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2);
				 if ( result == System::Windows::Forms::DialogResult::Yes )
				 {
					IPportcomboBox->Items->Clear();
					IPaddresscomboBox->Items->Clear();
					SendCommandcomboBox->Items->Clear();
					Invalidate();
				 }

		 }



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
					/*if (sendstr=="TestX01")
					{
						sendstr=MakeTestX01();
						termPort->SensdString(sendstr + "\r\n");
					}
					else*/
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


/*
	ref class Work
	{	
		public:
		Work(void)	
		{
		}	
		int tcpclientconnectionCallBack(int state)
		{
			return 0;
		}
	};
*/	


};

}
