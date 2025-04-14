#include "class_stationMsgFifo.h"
#include "NetworkStationMasterClass.h"
#include "applicationSetting.h"


#pragma once

using namespace System::IO::Ports;

namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FIFO_debugForm
	/// </summary>
	public ref class FIFO_debugForm : public System::Windows::Forms::Form
	{
	public:
		FIFO_debugForm(applicationSettingClass *appconfig, class_stationMsgFifo	*stnMsgFifo, SerialPort^  Psher_port, SerialPort^  stnNetwork_port, NetworkStationMasterClass ^NetworkStationMaster)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			stationMsgFifo = stnMsgFifo;
			Pusher_port =  Psher_port;
			stationNetwork_port = stnNetwork_port;
			tickcounter_timer1=0;
			nStationMaster = NetworkStationMaster;
			appcfg = appconfig;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FIFO_debugForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
	private: applicationSettingClass *appcfg;
	private: NetworkStationMasterClass	^nStationMaster;
	private: class_stationMsgFifo		*stationMsgFifo;
	private: System::IO::Ports::SerialPort^  Pusher_port;
	private: int tickcounter_timer1;

	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  PsherRxByteslabel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  PsherTxByteslabel;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  StnTxByteslabel;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  StnRxByteslabel;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label4;



	private: System::Windows::Forms::Label^  txFIFO_1label;
	private: System::Windows::Forms::Label^  txFIFO_2label;
	private: System::Windows::Forms::Label^  txFIFO_3label;
	private: System::Windows::Forms::Label^  txFIFO_3MAX_label;
	private: System::Windows::Forms::Label^  txFIFO_2MAX_label;
	private: System::Windows::Forms::Label^  txFIFO_1MAX_label;
	private: System::Windows::Forms::Label^  txFIFO_3chksum_label;
	private: System::Windows::Forms::Label^  txFIFO_2chksum_label;
	private: System::Windows::Forms::Label^  txFIFO_1chksum_label;
	private: System::Windows::Forms::Label^  txFIFO_3Ovrr_label;
	private: System::Windows::Forms::Label^  txFIFO_2Ovrr_label;
	private: System::Windows::Forms::Label^  txFIFO_1Ovrr_label;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  MsgPktRxOverrunlabel;
	private: System::Windows::Forms::Label^  MsgPktRxBuflabel;
	private: System::Windows::Forms::Label^  rxFIFO_MAX_label;
	private: System::Windows::Forms::Label^  rxFIFO_chksum_label;
	private: System::Windows::Forms::CheckBox^  TxFifoEnablecheckBox;
	private: System::Windows::Forms::CheckBox^  TxACKEnablecheckBox;
	private: System::Windows::Forms::Label^  rxFIFO_Usage_label;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  txFIFO_3Usage_label;
	private: System::Windows::Forms::Label^  txFIFO_2Usage_label;
	private: System::Windows::Forms::Label^  txFIFO_1Usage_label;


	private: System::Windows::Forms::Button^  ClearStatbutton;
	private: System::Windows::Forms::Label^  StatusACKlabel;
	private: System::Windows::Forms::Label^  txFIFO_0Usage_label;

	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  txFIFO_0Ovrr_label;
	private: System::Windows::Forms::Label^  txFIFO_0chksum_label;
	private: System::Windows::Forms::Label^  txFIFO_0MAX_label;
	private: System::Windows::Forms::Label^  txFIFO_0label;
	private: System::Windows::Forms::CheckBox^  UseDirectcheckBox;
	private: System::Windows::Forms::TextBox^  txThreadPeriodMillisectextBox;
	private: System::Windows::Forms::Label^  txthreadMilliseclabel;
	private: System::Windows::Forms::TextBox^  txLockMillisectextBox;
	private: System::Windows::Forms::Label^  txLockMilliseclabel;


			 System::IO::Ports::SerialPort^  stationNetwork_port;
			

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->PsherRxByteslabel = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->PsherTxByteslabel = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->StnTxByteslabel = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->StnRxByteslabel = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txFIFO_1label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_2label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_3label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_3MAX_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_2MAX_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_1MAX_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_3chksum_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_2chksum_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_1chksum_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_3Ovrr_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_2Ovrr_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_1Ovrr_label = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->txThreadPeriodMillisectextBox = (gcnew System::Windows::Forms::TextBox());
			this->txthreadMilliseclabel = (gcnew System::Windows::Forms::Label());
			this->txLockMillisectextBox = (gcnew System::Windows::Forms::TextBox());
			this->txLockMilliseclabel = (gcnew System::Windows::Forms::Label());
			this->UseDirectcheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->StatusACKlabel = (gcnew System::Windows::Forms::Label());
			this->ClearStatbutton = (gcnew System::Windows::Forms::Button());
			this->TxFifoEnablecheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->TxACKEnablecheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->MsgPktRxOverrunlabel = (gcnew System::Windows::Forms::Label());
			this->MsgPktRxBuflabel = (gcnew System::Windows::Forms::Label());
			this->rxFIFO_MAX_label = (gcnew System::Windows::Forms::Label());
			this->rxFIFO_chksum_label = (gcnew System::Windows::Forms::Label());
			this->rxFIFO_Usage_label = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->txFIFO_3Usage_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_2Usage_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_1Usage_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_0Usage_label = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->txFIFO_0Ovrr_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_0chksum_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_0MAX_label = (gcnew System::Windows::Forms::Label());
			this->txFIFO_0label = (gcnew System::Windows::Forms::Label());
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 10;
			this->timer1->Tick += gcnew System::EventHandler(this, &FIFO_debugForm::timer1_Tick);
			// 
			// PsherRxByteslabel
			// 
			this->PsherRxByteslabel->AutoSize = true;
			this->PsherRxByteslabel->Location = System::Drawing::Point(100, 41);
			this->PsherRxByteslabel->Name = L"PsherRxByteslabel";
			this->PsherRxByteslabel->Size = System::Drawing::Size(67, 13);
			this->PsherRxByteslabel->TabIndex = 0;
			this->PsherRxByteslabel->Text = L"not available";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(19, 41);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Pusher RxBuf:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(19, 63);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(74, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Pusher TxBuf:";
			// 
			// PsherTxByteslabel
			// 
			this->PsherTxByteslabel->AutoSize = true;
			this->PsherTxByteslabel->Location = System::Drawing::Point(100, 63);
			this->PsherTxByteslabel->Name = L"PsherTxByteslabel";
			this->PsherTxByteslabel->Size = System::Drawing::Size(67, 13);
			this->PsherTxByteslabel->TabIndex = 2;
			this->PsherTxByteslabel->Text = L"not available";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(20, 146);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(74, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Station TxBuf:";
			// 
			// StnTxByteslabel
			// 
			this->StnTxByteslabel->AutoSize = true;
			this->StnTxByteslabel->Location = System::Drawing::Point(101, 146);
			this->StnTxByteslabel->Name = L"StnTxByteslabel";
			this->StnTxByteslabel->Size = System::Drawing::Size(67, 13);
			this->StnTxByteslabel->TabIndex = 6;
			this->StnTxByteslabel->Text = L"not available";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(19, 124);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(75, 13);
			this->label5->TabIndex = 5;
			this->label5->Text = L"Station RxBuf:";
			// 
			// StnRxByteslabel
			// 
			this->StnRxByteslabel->AutoSize = true;
			this->StnRxByteslabel->Location = System::Drawing::Point(100, 124);
			this->StnRxByteslabel->Name = L"StnRxByteslabel";
			this->StnRxByteslabel->Size = System::Drawing::Size(67, 13);
			this->StnRxByteslabel->TabIndex = 4;
			this->StnRxByteslabel->Text = L"not available";
			// 
			// groupBox1
			// 
			this->groupBox1->Location = System::Drawing::Point(12, 24);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(210, 62);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Pusher Serial Comms";
			// 
			// groupBox2
			// 
			this->groupBox2->Location = System::Drawing::Point(12, 106);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(210, 67);
			this->groupBox2->TabIndex = 9;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Station Network Serial Comms";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(244, 131);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(29, 13);
			this->label4->TabIndex = 11;
			this->label4->Text = L"rxfifo";
			// 
			// txFIFO_1label
			// 
			this->txFIFO_1label->Location = System::Drawing::Point(279, 77);
			this->txFIFO_1label->Name = L"txFIFO_1label";
			this->txFIFO_1label->Size = System::Drawing::Size(42, 13);
			this->txFIFO_1label->TabIndex = 10;
			this->txFIFO_1label->Text = L"1_used";
			this->txFIFO_1label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_2label
			// 
			this->txFIFO_2label->Location = System::Drawing::Point(279, 95);
			this->txFIFO_2label->Name = L"txFIFO_2label";
			this->txFIFO_2label->Size = System::Drawing::Size(42, 13);
			this->txFIFO_2label->TabIndex = 11;
			this->txFIFO_2label->Text = L"2_used";
			this->txFIFO_2label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_3label
			// 
			this->txFIFO_3label->Location = System::Drawing::Point(279, 113);
			this->txFIFO_3label->Name = L"txFIFO_3label";
			this->txFIFO_3label->Size = System::Drawing::Size(42, 13);
			this->txFIFO_3label->TabIndex = 12;
			this->txFIFO_3label->Text = L"3_used";
			this->txFIFO_3label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_3MAX_label
			// 
			this->txFIFO_3MAX_label->Location = System::Drawing::Point(327, 113);
			this->txFIFO_3MAX_label->Name = L"txFIFO_3MAX_label";
			this->txFIFO_3MAX_label->Size = System::Drawing::Size(75, 13);
			this->txFIFO_3MAX_label->TabIndex = 15;
			this->txFIFO_3MAX_label->Text = L"fifo3_usedMax";
			this->txFIFO_3MAX_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_2MAX_label
			// 
			this->txFIFO_2MAX_label->Location = System::Drawing::Point(327, 95);
			this->txFIFO_2MAX_label->Name = L"txFIFO_2MAX_label";
			this->txFIFO_2MAX_label->Size = System::Drawing::Size(75, 13);
			this->txFIFO_2MAX_label->TabIndex = 14;
			this->txFIFO_2MAX_label->Text = L"fifo2_usedMax";
			this->txFIFO_2MAX_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_1MAX_label
			// 
			this->txFIFO_1MAX_label->Location = System::Drawing::Point(327, 77);
			this->txFIFO_1MAX_label->Name = L"txFIFO_1MAX_label";
			this->txFIFO_1MAX_label->Size = System::Drawing::Size(75, 13);
			this->txFIFO_1MAX_label->TabIndex = 13;
			this->txFIFO_1MAX_label->Text = L"fifo1_usedMax";
			this->txFIFO_1MAX_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_3chksum_label
			// 
			this->txFIFO_3chksum_label->Location = System::Drawing::Point(408, 113);
			this->txFIFO_3chksum_label->Name = L"txFIFO_3chksum_label";
			this->txFIFO_3chksum_label->Size = System::Drawing::Size(56, 13);
			this->txFIFO_3chksum_label->TabIndex = 18;
			this->txFIFO_3chksum_label->Text = L"3_chksum";
			this->txFIFO_3chksum_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_2chksum_label
			// 
			this->txFIFO_2chksum_label->Location = System::Drawing::Point(408, 95);
			this->txFIFO_2chksum_label->Name = L"txFIFO_2chksum_label";
			this->txFIFO_2chksum_label->Size = System::Drawing::Size(56, 13);
			this->txFIFO_2chksum_label->TabIndex = 17;
			this->txFIFO_2chksum_label->Text = L"2_chksum";
			this->txFIFO_2chksum_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_1chksum_label
			// 
			this->txFIFO_1chksum_label->Location = System::Drawing::Point(408, 77);
			this->txFIFO_1chksum_label->Name = L"txFIFO_1chksum_label";
			this->txFIFO_1chksum_label->Size = System::Drawing::Size(56, 13);
			this->txFIFO_1chksum_label->TabIndex = 16;
			this->txFIFO_1chksum_label->Text = L"1_chksum";
			this->txFIFO_1chksum_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_3Ovrr_label
			// 
			this->txFIFO_3Ovrr_label->Location = System::Drawing::Point(473, 113);
			this->txFIFO_3Ovrr_label->Name = L"txFIFO_3Ovrr_label";
			this->txFIFO_3Ovrr_label->Size = System::Drawing::Size(51, 13);
			this->txFIFO_3Ovrr_label->TabIndex = 21;
			this->txFIFO_3Ovrr_label->Text = L"fifo3_ovrr";
			this->txFIFO_3Ovrr_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_2Ovrr_label
			// 
			this->txFIFO_2Ovrr_label->Location = System::Drawing::Point(473, 95);
			this->txFIFO_2Ovrr_label->Name = L"txFIFO_2Ovrr_label";
			this->txFIFO_2Ovrr_label->Size = System::Drawing::Size(51, 13);
			this->txFIFO_2Ovrr_label->TabIndex = 20;
			this->txFIFO_2Ovrr_label->Text = L"fifo2_ovrr";
			this->txFIFO_2Ovrr_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_1Ovrr_label
			// 
			this->txFIFO_1Ovrr_label->Location = System::Drawing::Point(473, 77);
			this->txFIFO_1Ovrr_label->Name = L"txFIFO_1Ovrr_label";
			this->txFIFO_1Ovrr_label->Size = System::Drawing::Size(51, 13);
			this->txFIFO_1Ovrr_label->TabIndex = 19;
			this->txFIFO_1Ovrr_label->Text = L"fifo1_ovrr";
			this->txFIFO_1Ovrr_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(478, 41);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(45, 13);
			this->label7->TabIndex = 25;
			this->label7->Text = L"Overrun";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(418, 41);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(45, 13);
			this->label8->TabIndex = 24;
			this->label8->Text = L"Chksum";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(340, 41);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(61, 13);
			this->label9->TabIndex = 23;
			this->label9->Text = L"Max Usage";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(288, 41);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(32, 13);
			this->label10->TabIndex = 22;
			this->label10->Text = L"Used";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->txThreadPeriodMillisectextBox);
			this->groupBox3->Controls->Add(this->txthreadMilliseclabel);
			this->groupBox3->Controls->Add(this->txLockMillisectextBox);
			this->groupBox3->Controls->Add(this->txLockMilliseclabel);
			this->groupBox3->Controls->Add(this->UseDirectcheckBox);
			this->groupBox3->Controls->Add(this->StatusACKlabel);
			this->groupBox3->Controls->Add(this->ClearStatbutton);
			this->groupBox3->Controls->Add(this->TxFifoEnablecheckBox);
			this->groupBox3->Controls->Add(this->TxACKEnablecheckBox);
			this->groupBox3->Location = System::Drawing::Point(236, 23);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(444, 223);
			this->groupBox3->TabIndex = 26;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Tx/Rx Fifo Statistics";
			// 
			// txThreadPeriodMillisectextBox
			// 
			this->txThreadPeriodMillisectextBox->Location = System::Drawing::Point(234, 185);
			this->txThreadPeriodMillisectextBox->Name = L"txThreadPeriodMillisectextBox";
			this->txThreadPeriodMillisectextBox->Size = System::Drawing::Size(32, 20);
			this->txThreadPeriodMillisectextBox->TabIndex = 42;
			this->txThreadPeriodMillisectextBox->TextChanged += gcnew System::EventHandler(this, &FIFO_debugForm::txThreadPeriodMillisectextBox_TextChanged);
			// 
			// txthreadMilliseclabel
			// 
			this->txthreadMilliseclabel->AutoSize = true;
			this->txthreadMilliseclabel->Location = System::Drawing::Point(156, 188);
			this->txthreadMilliseclabel->Name = L"txthreadMilliseclabel";
			this->txthreadMilliseclabel->Size = System::Drawing::Size(72, 13);
			this->txthreadMilliseclabel->TabIndex = 41;
			this->txthreadMilliseclabel->Text = L"tx period (ms):";
			// 
			// txLockMillisectextBox
			// 
			this->txLockMillisectextBox->Location = System::Drawing::Point(94, 185);
			this->txLockMillisectextBox->Name = L"txLockMillisectextBox";
			this->txLockMillisectextBox->Size = System::Drawing::Size(32, 20);
			this->txLockMillisectextBox->TabIndex = 40;
			this->txLockMillisectextBox->TextChanged += gcnew System::EventHandler(this, &FIFO_debugForm::txLockMillisectextBox_TextChanged);
			// 
			// txLockMilliseclabel
			// 
			this->txLockMilliseclabel->AutoSize = true;
			this->txLockMilliseclabel->Location = System::Drawing::Point(23, 188);
			this->txLockMilliseclabel->Name = L"txLockMilliseclabel";
			this->txLockMilliseclabel->Size = System::Drawing::Size(67, 13);
			this->txLockMilliseclabel->TabIndex = 39;
			this->txLockMilliseclabel->Text = L"tx Lock (ms):";
			// 
			// UseDirectcheckBox
			// 
			this->UseDirectcheckBox->AutoSize = true;
			this->UseDirectcheckBox->Location = System::Drawing::Point(351, 36);
			this->UseDirectcheckBox->Name = L"UseDirectcheckBox";
			this->UseDirectcheckBox->Size = System::Drawing::Size(88, 17);
			this->UseDirectcheckBox->TabIndex = 38;
			this->UseDirectcheckBox->Text = L"direct Enable";
			this->UseDirectcheckBox->UseVisualStyleBackColor = true;
			this->UseDirectcheckBox->CheckedChanged += gcnew System::EventHandler(this, &FIFO_debugForm::UseDirectcheckBox_CheckedChanged);
			// 
			// StatusACKlabel
			// 
			this->StatusACKlabel->Location = System::Drawing::Point(13, 155);
			this->StatusACKlabel->Name = L"StatusACKlabel";
			this->StatusACKlabel->Size = System::Drawing::Size(334, 13);
			this->StatusACKlabel->TabIndex = 37;
			this->StatusACKlabel->Text = L"ACK";
			this->StatusACKlabel->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// ClearStatbutton
			// 
			this->ClearStatbutton->Location = System::Drawing::Point(256, 129);
			this->ClearStatbutton->Name = L"ClearStatbutton";
			this->ClearStatbutton->Size = System::Drawing::Size(91, 23);
			this->ClearStatbutton->TabIndex = 36;
			this->ClearStatbutton->Text = L"Reset Statistics";
			this->ClearStatbutton->UseVisualStyleBackColor = true;
			this->ClearStatbutton->Click += gcnew System::EventHandler(this, &FIFO_debugForm::ClearStatbutton_Click);
			// 
			// TxFifoEnablecheckBox
			// 
			this->TxFifoEnablecheckBox->AutoSize = true;
			this->TxFifoEnablecheckBox->Location = System::Drawing::Point(15, 135);
			this->TxFifoEnablecheckBox->Name = L"TxFifoEnablecheckBox";
			this->TxFifoEnablecheckBox->Size = System::Drawing::Size(94, 17);
			this->TxFifoEnablecheckBox->TabIndex = 34;
			this->TxFifoEnablecheckBox->Text = L"Tx Fifo Enable";
			this->TxFifoEnablecheckBox->UseVisualStyleBackColor = true;
			this->TxFifoEnablecheckBox->CheckedChanged += gcnew System::EventHandler(this, &FIFO_debugForm::TxFifoEnablecheckBox_CheckedChanged);
			// 
			// TxACKEnablecheckBox
			// 
			this->TxACKEnablecheckBox->AutoSize = true;
			this->TxACKEnablecheckBox->Location = System::Drawing::Point(122, 135);
			this->TxACKEnablecheckBox->Name = L"TxACKEnablecheckBox";
			this->TxACKEnablecheckBox->Size = System::Drawing::Size(97, 17);
			this->TxACKEnablecheckBox->TabIndex = 35;
			this->TxACKEnablecheckBox->Text = L"Tx ACK enable";
			this->TxACKEnablecheckBox->UseVisualStyleBackColor = true;
			this->TxACKEnablecheckBox->CheckedChanged += gcnew System::EventHandler(this, &FIFO_debugForm::TxACKEnablecheckBox_CheckedChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(246, 113);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(27, 13);
			this->label11->TabIndex = 29;
			this->label11->Text = L"fifo3";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(246, 95);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(27, 13);
			this->label12->TabIndex = 28;
			this->label12->Text = L"fifo2";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(246, 77);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(27, 13);
			this->label13->TabIndex = 27;
			this->label13->Text = L"fifo1";
			// 
			// MsgPktRxOverrunlabel
			// 
			this->MsgPktRxOverrunlabel->Location = System::Drawing::Point(473, 131);
			this->MsgPktRxOverrunlabel->Name = L"MsgPktRxOverrunlabel";
			this->MsgPktRxOverrunlabel->Size = System::Drawing::Size(51, 13);
			this->MsgPktRxOverrunlabel->TabIndex = 30;
			this->MsgPktRxOverrunlabel->Text = L"rx_ovrr";
			this->MsgPktRxOverrunlabel->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// MsgPktRxBuflabel
			// 
			this->MsgPktRxBuflabel->Location = System::Drawing::Point(279, 131);
			this->MsgPktRxBuflabel->Name = L"MsgPktRxBuflabel";
			this->MsgPktRxBuflabel->Size = System::Drawing::Size(42, 13);
			this->MsgPktRxBuflabel->TabIndex = 31;
			this->MsgPktRxBuflabel->Text = L"rx_used";
			this->MsgPktRxBuflabel->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// rxFIFO_MAX_label
			// 
			this->rxFIFO_MAX_label->Location = System::Drawing::Point(327, 131);
			this->rxFIFO_MAX_label->Name = L"rxFIFO_MAX_label";
			this->rxFIFO_MAX_label->Size = System::Drawing::Size(75, 13);
			this->rxFIFO_MAX_label->TabIndex = 32;
			this->rxFIFO_MAX_label->Text = L"fifo3_usedMax";
			this->rxFIFO_MAX_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// rxFIFO_chksum_label
			// 
			this->rxFIFO_chksum_label->Location = System::Drawing::Point(408, 131);
			this->rxFIFO_chksum_label->Name = L"rxFIFO_chksum_label";
			this->rxFIFO_chksum_label->Size = System::Drawing::Size(56, 13);
			this->rxFIFO_chksum_label->TabIndex = 33;
			this->rxFIFO_chksum_label->Text = L"3_chksum";
			this->rxFIFO_chksum_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// rxFIFO_Usage_label
			// 
			this->rxFIFO_Usage_label->Location = System::Drawing::Point(530, 131);
			this->rxFIFO_Usage_label->Name = L"rxFIFO_Usage_label";
			this->rxFIFO_Usage_label->Size = System::Drawing::Size(51, 13);
			this->rxFIFO_Usage_label->TabIndex = 40;
			this->rxFIFO_Usage_label->Text = L"rx_usage";
			this->rxFIFO_Usage_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(535, 41);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(38, 13);
			this->label14->TabIndex = 39;
			this->label14->Text = L"Usage";
			// 
			// txFIFO_3Usage_label
			// 
			this->txFIFO_3Usage_label->Location = System::Drawing::Point(530, 113);
			this->txFIFO_3Usage_label->Name = L"txFIFO_3Usage_label";
			this->txFIFO_3Usage_label->Size = System::Drawing::Size(51, 13);
			this->txFIFO_3Usage_label->TabIndex = 38;
			this->txFIFO_3Usage_label->Text = L"fifo3_usage";
			this->txFIFO_3Usage_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_2Usage_label
			// 
			this->txFIFO_2Usage_label->Location = System::Drawing::Point(530, 95);
			this->txFIFO_2Usage_label->Name = L"txFIFO_2Usage_label";
			this->txFIFO_2Usage_label->Size = System::Drawing::Size(51, 13);
			this->txFIFO_2Usage_label->TabIndex = 37;
			this->txFIFO_2Usage_label->Text = L"fifo2_usage";
			this->txFIFO_2Usage_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_1Usage_label
			// 
			this->txFIFO_1Usage_label->Location = System::Drawing::Point(530, 77);
			this->txFIFO_1Usage_label->Name = L"txFIFO_1Usage_label";
			this->txFIFO_1Usage_label->Size = System::Drawing::Size(51, 13);
			this->txFIFO_1Usage_label->TabIndex = 36;
			this->txFIFO_1Usage_label->Text = L"fifo1_usage";
			this->txFIFO_1Usage_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_0Usage_label
			// 
			this->txFIFO_0Usage_label->Location = System::Drawing::Point(530, 59);
			this->txFIFO_0Usage_label->Name = L"txFIFO_0Usage_label";
			this->txFIFO_0Usage_label->Size = System::Drawing::Size(51, 13);
			this->txFIFO_0Usage_label->TabIndex = 46;
			this->txFIFO_0Usage_label->Text = L"fifo1_usage";
			this->txFIFO_0Usage_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(246, 59);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(33, 13);
			this->label15->TabIndex = 45;
			this->label15->Text = L"direct";
			// 
			// txFIFO_0Ovrr_label
			// 
			this->txFIFO_0Ovrr_label->Location = System::Drawing::Point(473, 59);
			this->txFIFO_0Ovrr_label->Name = L"txFIFO_0Ovrr_label";
			this->txFIFO_0Ovrr_label->Size = System::Drawing::Size(51, 13);
			this->txFIFO_0Ovrr_label->TabIndex = 44;
			this->txFIFO_0Ovrr_label->Text = L"fifo1_ovrr";
			this->txFIFO_0Ovrr_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_0chksum_label
			// 
			this->txFIFO_0chksum_label->Location = System::Drawing::Point(408, 59);
			this->txFIFO_0chksum_label->Name = L"txFIFO_0chksum_label";
			this->txFIFO_0chksum_label->Size = System::Drawing::Size(56, 13);
			this->txFIFO_0chksum_label->TabIndex = 43;
			this->txFIFO_0chksum_label->Text = L"1_chksum";
			this->txFIFO_0chksum_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_0MAX_label
			// 
			this->txFIFO_0MAX_label->Location = System::Drawing::Point(327, 59);
			this->txFIFO_0MAX_label->Name = L"txFIFO_0MAX_label";
			this->txFIFO_0MAX_label->Size = System::Drawing::Size(75, 13);
			this->txFIFO_0MAX_label->TabIndex = 42;
			this->txFIFO_0MAX_label->Text = L"fifo1_usedMax";
			this->txFIFO_0MAX_label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// txFIFO_0label
			// 
			this->txFIFO_0label->Location = System::Drawing::Point(279, 59);
			this->txFIFO_0label->Name = L"txFIFO_0label";
			this->txFIFO_0label->Size = System::Drawing::Size(42, 13);
			this->txFIFO_0label->TabIndex = 41;
			this->txFIFO_0label->Text = L"1_used";
			this->txFIFO_0label->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// FIFO_debugForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(697, 258);
			this->Controls->Add(this->txFIFO_0Usage_label);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->txFIFO_0Ovrr_label);
			this->Controls->Add(this->txFIFO_0chksum_label);
			this->Controls->Add(this->txFIFO_0MAX_label);
			this->Controls->Add(this->txFIFO_0label);
			this->Controls->Add(this->rxFIFO_Usage_label);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->txFIFO_3Usage_label);
			this->Controls->Add(this->txFIFO_2Usage_label);
			this->Controls->Add(this->txFIFO_1Usage_label);
			this->Controls->Add(this->rxFIFO_chksum_label);
			this->Controls->Add(this->rxFIFO_MAX_label);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->MsgPktRxBuflabel);
			this->Controls->Add(this->MsgPktRxOverrunlabel);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->txFIFO_3Ovrr_label);
			this->Controls->Add(this->txFIFO_2Ovrr_label);
			this->Controls->Add(this->txFIFO_1Ovrr_label);
			this->Controls->Add(this->txFIFO_3chksum_label);
			this->Controls->Add(this->txFIFO_2chksum_label);
			this->Controls->Add(this->txFIFO_1chksum_label);
			this->Controls->Add(this->txFIFO_3MAX_label);
			this->Controls->Add(this->txFIFO_2MAX_label);
			this->Controls->Add(this->txFIFO_1MAX_label);
			this->Controls->Add(this->txFIFO_3label);
			this->Controls->Add(this->txFIFO_2label);
			this->Controls->Add(this->txFIFO_1label);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->StnTxByteslabel);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->StnRxByteslabel);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->PsherTxByteslabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->PsherRxByteslabel);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox3);
			this->Name = L"FIFO_debugForm";
			this->Text = L"FIFO_debugForm";
			this->Load += gcnew System::EventHandler(this, &FIFO_debugForm::FIFO_debugForm_Load);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void FIFO_debugForm_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				//-------------------------
				 
				if (nStationMaster->isUserFifo())
					TxFifoEnablecheckBox->Checked = true;
				else
					TxFifoEnablecheckBox->Checked = false;
				//-------------------------
				if (nStationMaster->isACK_handshake_enable())
					TxACKEnablecheckBox->Checked = true;
				else
					TxACKEnablecheckBox->Checked = false;
				//-------------------------
				if (nStationMaster->is_DirectWrite_enable())
					UseDirectcheckBox->Checked = true;
				else
					UseDirectcheckBox->Checked = false;

				txThreadPeriodMillisectextBox->Text = appcfg->data.txthreadSleepMillsec.ToString();
				txLockMillisectextBox->Text = appcfg->data.txLockSleepMillsec.ToString();

				//------------------------- 
				setTxFifoMode(nStationMaster->isUserFifo());

				//------------------------- 
				 timer1->Enabled = true;
				 timer1->Start();
			 }

	private: void setTxFifoMode(bool enable)
			 {
				txFIFO_1label->Enabled = enable; 
				txFIFO_1MAX_label->Enabled = enable; 
				txFIFO_1chksum_label->Enabled = enable; 
				txFIFO_1Ovrr_label->Enabled = enable; 
				txFIFO_1Usage_label->Enabled = enable; 

				txFIFO_2label->Enabled = enable; 
				txFIFO_2MAX_label->Enabled = enable; 
				txFIFO_2chksum_label->Enabled = enable; 
				txFIFO_2Ovrr_label->Enabled = enable; 
				txFIFO_2Usage_label->Enabled = enable; 

				txFIFO_3label->Enabled = enable; 
				txFIFO_3MAX_label->Enabled = enable; 
				txFIFO_3chksum_label->Enabled = enable; 
				txFIFO_3Ovrr_label->Enabled = enable; 
				txFIFO_3Usage_label->Enabled = enable; 

				TxACKEnablecheckBox->Enabled = enable; 
			 }
			 
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
			 {
				 if ((tickcounter_timer1%100)==0)
				 {
					 if (Pusher_port->IsOpen)
					 {
						PsherRxByteslabel->Text = Pusher_port->BytesToRead.ToString();
						PsherTxByteslabel->Text = Pusher_port->BytesToWrite.ToString();
					 }

					 if (stationNetwork_port->IsOpen)
					 {
						StnRxByteslabel->Text = stationNetwork_port->BytesToRead.ToString();
						StnTxByteslabel->Text = stationNetwork_port->BytesToWrite.ToString();
					 }
				 



				 }



				 if ((tickcounter_timer1%10)==0)
				 {
				 	int ii;
					class_stationMsgFifo *fifo;
					serialfifoStatisticsType *fifostatistic;
					NetworkMasterCommsStatisticsType *statistics = nStationMaster->NetworkMasterCommsStatistics;
					String ^usage = "";
					String ^usage_Max = "";
					String ^BufferSize = "";
					String ^chksumCount = "";
					String ^overrunCount = "";
					String ^totalusageCount = "";
					int totalusage_iCount = 0;
					for (ii=1;ii<=3;ii++)
					{
						fifo = nStationMaster->getFifo(ii);
						if (fifo)
						{
							fifostatistic = &statistics->fifostatistics[ii-1];
							fifo->getserialfifoStatistics(fifostatistic);
							usage = fifostatistic->usage.ToString();
							usage_Max = fifostatistic->usage_Max.ToString();
							BufferSize = fifostatistic->BufferSize.ToString();
							chksumCount = fifostatistic->chksumCount.ToString();
							overrunCount = fifostatistic->overrunCount.ToString();
							totalusage_iCount = fifostatistic->totalusageCount;
							if (totalusage_iCount>99999)
								totalusage_iCount = 99999;
							totalusageCount = totalusage_iCount.ToString();
							switch(ii)
							{
								/*
								case	0:
										txFIFO_0label->Text = usage; 
										txFIFO_0MAX_label->Text = usage_Max+"/"+BufferSize;
										txFIFO_0chksum_label->Text = chksumCount;
										txFIFO_0Ovrr_label->Text = overrunCount;
										txFIFO_0Usage_label->Text = totalusageCount;
										break;
										*/
								case	1:
										txFIFO_1label->Text = usage; 
										txFIFO_1MAX_label->Text = usage_Max+"/"+BufferSize;
										txFIFO_1chksum_label->Text = chksumCount;
										txFIFO_1Ovrr_label->Text = overrunCount;
										txFIFO_1Usage_label->Text = totalusageCount;
										break;
								case	2:
										txFIFO_2label->Text = usage; 
										txFIFO_2MAX_label->Text = usage_Max+"/"+BufferSize;
										txFIFO_2chksum_label->Text = chksumCount;
										txFIFO_2Ovrr_label->Text = overrunCount;
										txFIFO_2Usage_label->Text = totalusageCount;
										break;
								case	3:
										txFIFO_3label->Text = usage; 
										txFIFO_3MAX_label->Text = usage_Max+"/"+BufferSize;
										txFIFO_3chksum_label->Text = chksumCount;
										txFIFO_3Ovrr_label->Text = overrunCount;
										txFIFO_3Usage_label->Text = totalusageCount;
										break;
							}
						}
					}

					fifo = stationMsgFifo;
					fifostatistic = &statistics->fifostatistics[4];
					fifo->getserialfifoStatistics(fifostatistic);
					MsgPktRxBuflabel->Text = fifostatistic->usage.ToString();
					MsgPktRxOverrunlabel->Text = fifostatistic->overrunCount.ToString();
					rxFIFO_MAX_label->Text = fifostatistic->usage_Max.ToString()+"/"+fifostatistic->BufferSize.ToString();
					rxFIFO_chksum_label->Text = fifostatistic->chksumCount.ToString();
					totalusage_iCount = fifostatistic->totalusageCount;
					if (totalusage_iCount>99999)
						totalusage_iCount = 99999;
					totalusageCount = totalusage_iCount.ToString();
					rxFIFO_Usage_label->Text = totalusageCount;

					

					StatusACKlabel->Text =	"Errcount:"+nStationMaster->NetworkMasterCommsStatistics->sendlastCount.ToString()+"    "+
											"ACKcount:"+nStationMaster->NetworkMasterCommsStatistics->ACK_count.ToString()+"    "+
											"NAKcount:"+nStationMaster->NetworkMasterCommsStatistics->NAK_count.ToString()+"    "+
											"ACK:"+nStationMaster->ACK_flag.ToString()+"/"+nStationMaster->getmaxACK_flag()+"  "+
											"NAK:"+nStationMaster->NAK_flag.ToString()+"/"+nStationMaster->getmaxNAK_flag();
			 

					totalusageCount = nStationMaster->NetworkMasterCommsStatistics->priority_FireCounter.ToString();
					txFIFO_0label->Text = "0"; 
					txFIFO_0MAX_label->Text = "0"; 
					txFIFO_0chksum_label->Text = "0"; 
					txFIFO_0Ovrr_label->Text = "0"; 
					txFIFO_0Usage_label->Text = totalusageCount;

				 }

				tickcounter_timer1++;
			 }

private: System::Void TxFifoEnablecheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			if (TxFifoEnablecheckBox->Checked)
				appcfg->data.TxFifo_enable = 1;
			else
				appcfg->data.TxFifo_enable = 0;
			nStationMaster->setTxFifo_enable(appcfg->data.TxFifo_enable);
			appcfg->SaveConfigINI();
			setTxFifoMode(appcfg->data.TxFifo_enable);
		 }

private: System::Void TxACKEnablecheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			if (TxACKEnablecheckBox->Checked)
				appcfg->data.ACK_handshake_enable = 1;
			else
				appcfg->data.ACK_handshake_enable = 0;
			nStationMaster->setACK_handshake_enable(appcfg->data.ACK_handshake_enable);
			appcfg->SaveConfigINI();
		 }

private: System::Void ClearStatbutton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 nStationMaster->ClearMsgFifoStatistics();
			 stationMsgFifo->clearStatistics();
		 }

private: System::Void UseDirectcheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			if (UseDirectcheckBox->Checked)
				appcfg->data.ACK_NAK_DirectWrite_enable = 1;
			else
				appcfg->data.ACK_NAK_DirectWrite_enable = 0;
			nStationMaster->setACK_NAK_DirectWrite_enable(appcfg->data.ACK_NAK_DirectWrite_enable);
			appcfg->SaveConfigINI();
		 }

private: System::Void txThreadPeriodMillisectextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			int value = convertToInt32(txThreadPeriodMillisectextBox->Text);
			if (value<=2) 
				value = 2;
			appcfg->data.txthreadSleepMillsec = value;
			nStationMaster->setthreadSleepMillsec(appcfg->data.txthreadSleepMillsec);
			appcfg->SaveConfigINI();

		 }


private: System::Void txLockMillisectextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			int value = convertToInt32(txLockMillisectextBox->Text);
			if (value<=2) 
				value = 2;
			appcfg->data.txLockSleepMillsec = value;
			nStationMaster->setLockSleepMillsec(appcfg->data.txLockSleepMillsec);
			appcfg->SaveConfigINI();
		 }
};
}
