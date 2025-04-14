#include <vcclr.h>  
#include "applicationSetting.h"
#include "stringconversion.h"
#include "socketfunction.h"
#include "GlobalVariables.h"


#pragma once

typedef struct{
	int operationMode;
	applicationSettingType	appset;
}ApplicationConfigurationDialogDataType;


namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for dlg_ApplicationConfiguration
	/// </summary>
	public ref class dlg_ApplicationConfiguration : public System::Windows::Forms::Form
	{
	public:
		dlg_ApplicationConfiguration(ApplicationConfigurationDialogDataType *dlg_data)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			dlgdata = dlg_data;
		}

	public: 

	public: 

	public: 

	public: 













	
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~dlg_ApplicationConfiguration()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  CancelButton;
	protected: 
	private: System::Windows::Forms::Button^  OKButton;
	private: System::Windows::Forms::Label^  MRThostnameServerIPaddresslabel;


	private: System::Windows::Forms::TextBox^  MRT_hostnameServer;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  Network_radioButton;

	private: System::Windows::Forms::RadioButton^  StandAlone_radioButton;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Label^  ProductionLineNamelabel;


	private: System::Windows::Forms::ComboBox^  ProductionLineNamecomboBox;
	private: System::Windows::Forms::Label^  Standalone_label;
	private: System::Windows::Forms::Label^  NetworkModelabel;
	private: System::Windows::Forms::TabControl^  tabControl1;


	private: System::Windows::Forms::TabPage^  OperationModetabPage;
	private: System::Windows::Forms::TabPage^  InspectiontabPage;


	private: System::Windows::Forms::CheckBox^  ShowInspectionPopupcheckBox;


	private: System::Windows::Forms::TabPage^  GeneraltabPage;
	private: System::Windows::Forms::CheckBox^  Send2TCPcheckBox;
	private: System::Windows::Forms::TabPage^  TCPPorttabPage;









	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  MasterDataServerIPaddresslabeltextBox;
	private: System::Windows::Forms::Label^  LocalDataServerNamelabel;
	private: System::Windows::Forms::TextBox^  LocalDataServerIPaddresslabeltextBox;
	private: System::Windows::Forms::GroupBox^  DataServerTableNamegroupBox;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  LocalDataServerNamelabeltextBox;
	private: System::Windows::Forms::TextBox^  MasterDataServerNamelabeltextBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  HostnameDataServerNamelabeltextBox;
private: System::Windows::Forms::GroupBox^  TCP_hiddensetgroupBox;


private: System::Windows::Forms::TextBox^  ServerNetworkControlPorttextBox;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Label^  motor_on_delaylabel;
private: System::Windows::Forms::TextBox^  motor_on_delaytextBox;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::TextBox^  noSerialEventTimeOuttextBox;



		ApplicationConfigurationDialogDataType *dlgdata;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->MRThostnameServerIPaddresslabel = (gcnew System::Windows::Forms::Label());
			this->MRT_hostnameServer = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Network_radioButton = (gcnew System::Windows::Forms::RadioButton());
			this->StandAlone_radioButton = (gcnew System::Windows::Forms::RadioButton());
			this->ProductionLineNamelabel = (gcnew System::Windows::Forms::Label());
			this->ProductionLineNamecomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->Standalone_label = (gcnew System::Windows::Forms::Label());
			this->NetworkModelabel = (gcnew System::Windows::Forms::Label());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->GeneraltabPage = (gcnew System::Windows::Forms::TabPage());
			this->motor_on_delaylabel = (gcnew System::Windows::Forms::Label());
			this->motor_on_delaytextBox = (gcnew System::Windows::Forms::TextBox());
			this->OperationModetabPage = (gcnew System::Windows::Forms::TabPage());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->MasterDataServerIPaddresslabeltextBox = (gcnew System::Windows::Forms::TextBox());
			this->LocalDataServerNamelabel = (gcnew System::Windows::Forms::Label());
			this->LocalDataServerIPaddresslabeltextBox = (gcnew System::Windows::Forms::TextBox());
			this->DataServerTableNamegroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->HostnameDataServerNamelabeltextBox = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->LocalDataServerNamelabeltextBox = (gcnew System::Windows::Forms::TextBox());
			this->MasterDataServerNamelabeltextBox = (gcnew System::Windows::Forms::TextBox());
			this->InspectiontabPage = (gcnew System::Windows::Forms::TabPage());
			this->Send2TCPcheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->ShowInspectionPopupcheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->TCPPorttabPage = (gcnew System::Windows::Forms::TabPage());
			this->TCP_hiddensetgroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->ServerNetworkControlPorttextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->noSerialEventTimeOuttextBox = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->GeneraltabPage->SuspendLayout();
			this->OperationModetabPage->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->DataServerTableNamegroupBox->SuspendLayout();
			this->InspectiontabPage->SuspendLayout();
			this->TCPPorttabPage->SuspendLayout();
			this->TCP_hiddensetgroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// CancelButton
			// 
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Location = System::Drawing::Point(251, 339);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(75, 23);
			this->CancelButton->TabIndex = 13;
			this->CancelButton->Text = L"&Cancel";
			this->CancelButton->UseVisualStyleBackColor = true;
			this->CancelButton->Click += gcnew System::EventHandler(this, &dlg_ApplicationConfiguration::CancelButton_Click);
			// 
			// OKButton
			// 
			this->OKButton->Cursor = System::Windows::Forms::Cursors::Default;
			this->OKButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKButton->Location = System::Drawing::Point(122, 339);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(75, 23);
			this->OKButton->TabIndex = 12;
			this->OKButton->Text = L"&OK";
			this->OKButton->UseVisualStyleBackColor = true;
			this->OKButton->Click += gcnew System::EventHandler(this, &dlg_ApplicationConfiguration::OKButton_Click);
			// 
			// MRThostnameServerIPaddresslabel
			// 
			this->MRThostnameServerIPaddresslabel->AutoSize = true;
			this->MRThostnameServerIPaddresslabel->Location = System::Drawing::Point(14, 103);
			this->MRThostnameServerIPaddresslabel->Name = L"MRThostnameServerIPaddresslabel";
			this->MRThostnameServerIPaddresslabel->Size = System::Drawing::Size(154, 13);
			this->MRThostnameServerIPaddresslabel->TabIndex = 10;
			this->MRThostnameServerIPaddresslabel->Text = L"Hostname Server IPv4 address";
			// 
			// MRT_hostnameServer
			// 
			this->MRT_hostnameServer->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F));
			this->MRT_hostnameServer->Location = System::Drawing::Point(17, 118);
			this->MRT_hostnameServer->Name = L"MRT_hostnameServer";
			this->MRT_hostnameServer->Size = System::Drawing::Size(148, 20);
			this->MRT_hostnameServer->TabIndex = 9;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->Network_radioButton);
			this->groupBox1->Controls->Add(this->StandAlone_radioButton);
			this->groupBox1->Location = System::Drawing::Point(6, 13);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(166, 69);
			this->groupBox1->TabIndex = 14;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Operation Mode Configuration";
			// 
			// Network_radioButton
			// 
			this->Network_radioButton->AutoSize = true;
			this->Network_radioButton->Location = System::Drawing::Point(18, 42);
			this->Network_radioButton->Name = L"Network_radioButton";
			this->Network_radioButton->Size = System::Drawing::Size(65, 17);
			this->Network_radioButton->TabIndex = 1;
			this->Network_radioButton->TabStop = true;
			this->Network_radioButton->Text = L"&Network";
			this->Network_radioButton->UseVisualStyleBackColor = true;
			this->Network_radioButton->CheckedChanged += gcnew System::EventHandler(this, &dlg_ApplicationConfiguration::Network_radioButton_CheckedChanged);
			// 
			// StandAlone_radioButton
			// 
			this->StandAlone_radioButton->AutoSize = true;
			this->StandAlone_radioButton->Location = System::Drawing::Point(18, 19);
			this->StandAlone_radioButton->Name = L"StandAlone_radioButton";
			this->StandAlone_radioButton->Size = System::Drawing::Size(82, 17);
			this->StandAlone_radioButton->TabIndex = 0;
			this->StandAlone_radioButton->TabStop = true;
			this->StandAlone_radioButton->Text = L"&Stand-alone";
			this->StandAlone_radioButton->UseVisualStyleBackColor = true;
			this->StandAlone_radioButton->CheckedChanged += gcnew System::EventHandler(this, &dlg_ApplicationConfiguration::StandAlone_radioButton_CheckedChanged);
			// 
			// ProductionLineNamelabel
			// 
			this->ProductionLineNamelabel->AutoSize = true;
			this->ProductionLineNamelabel->Location = System::Drawing::Point(219, 36);
			this->ProductionLineNamelabel->Name = L"ProductionLineNamelabel";
			this->ProductionLineNamelabel->Size = System::Drawing::Size(112, 13);
			this->ProductionLineNamelabel->TabIndex = 16;
			this->ProductionLineNamelabel->Text = L"Production Line Name";
			// 
			// ProductionLineNamecomboBox
			// 
			this->ProductionLineNamecomboBox->FormattingEnabled = true;
			this->ProductionLineNamecomboBox->Location = System::Drawing::Point(221, 51);
			this->ProductionLineNamecomboBox->Name = L"ProductionLineNamecomboBox";
			this->ProductionLineNamecomboBox->Size = System::Drawing::Size(176, 21);
			this->ProductionLineNamecomboBox->TabIndex = 17;
			// 
			// Standalone_label
			// 
			this->Standalone_label->Location = System::Drawing::Point(6, 241);
			this->Standalone_label->Name = L"Standalone_label";
			this->Standalone_label->Size = System::Drawing::Size(325, 21);
			this->Standalone_label->TabIndex = 18;
			this->Standalone_label->Text = L"Stand-alone: Non-Network version of the Online MRT system. ";
			// 
			// NetworkModelabel
			// 
			this->NetworkModelabel->Location = System::Drawing::Point(6, 267);
			this->NetworkModelabel->Name = L"NetworkModelabel";
			this->NetworkModelabel->Size = System::Drawing::Size(325, 22);
			this->NetworkModelabel->TabIndex = 19;
			this->NetworkModelabel->Text = L"Network: MRT online network system with bridge";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->GeneraltabPage);
			this->tabControl1->Controls->Add(this->OperationModetabPage);
			this->tabControl1->Controls->Add(this->InspectiontabPage);
			this->tabControl1->Controls->Add(this->TCPPorttabPage);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(465, 321);
			this->tabControl1->TabIndex = 20;
			// 
			// GeneraltabPage
			// 
			this->GeneraltabPage->BackColor = System::Drawing::SystemColors::Control;
			this->GeneraltabPage->Controls->Add(this->label1);
			this->GeneraltabPage->Controls->Add(this->noSerialEventTimeOuttextBox);
			this->GeneraltabPage->Controls->Add(this->motor_on_delaylabel);
			this->GeneraltabPage->Controls->Add(this->motor_on_delaytextBox);
			this->GeneraltabPage->Location = System::Drawing::Point(4, 22);
			this->GeneraltabPage->Name = L"GeneraltabPage";
			this->GeneraltabPage->Size = System::Drawing::Size(457, 295);
			this->GeneraltabPage->TabIndex = 2;
			this->GeneraltabPage->Text = L"General";
			// 
			// motor_on_delaylabel
			// 
			this->motor_on_delaylabel->AutoSize = true;
			this->motor_on_delaylabel->Location = System::Drawing::Point(15, 30);
			this->motor_on_delaylabel->Name = L"motor_on_delaylabel";
			this->motor_on_delaylabel->Size = System::Drawing::Size(158, 13);
			this->motor_on_delaylabel->TabIndex = 1;
			this->motor_on_delaylabel->Text = L"Head line Motor On Delay (sec):";
			// 
			// motor_on_delaytextBox
			// 
			this->motor_on_delaytextBox->Location = System::Drawing::Point(179, 27);
			this->motor_on_delaytextBox->Name = L"motor_on_delaytextBox";
			this->motor_on_delaytextBox->Size = System::Drawing::Size(50, 20);
			this->motor_on_delaytextBox->TabIndex = 0;
			// 
			// OperationModetabPage
			// 
			this->OperationModetabPage->BackColor = System::Drawing::SystemColors::Control;
			this->OperationModetabPage->Controls->Add(this->groupBox4);
			this->OperationModetabPage->Controls->Add(this->DataServerTableNamegroupBox);
			this->OperationModetabPage->Controls->Add(this->ProductionLineNamelabel);
			this->OperationModetabPage->Controls->Add(this->groupBox1);
			this->OperationModetabPage->Controls->Add(this->ProductionLineNamecomboBox);
			this->OperationModetabPage->Controls->Add(this->NetworkModelabel);
			this->OperationModetabPage->Controls->Add(this->Standalone_label);
			this->OperationModetabPage->Location = System::Drawing::Point(4, 22);
			this->OperationModetabPage->Name = L"OperationModetabPage";
			this->OperationModetabPage->Padding = System::Windows::Forms::Padding(3);
			this->OperationModetabPage->Size = System::Drawing::Size(457, 295);
			this->OperationModetabPage->TabIndex = 0;
			this->OperationModetabPage->Text = L"Operation Mode";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->label4);
			this->groupBox4->Controls->Add(this->MasterDataServerIPaddresslabeltextBox);
			this->groupBox4->Controls->Add(this->LocalDataServerNamelabel);
			this->groupBox4->Controls->Add(this->LocalDataServerIPaddresslabeltextBox);
			this->groupBox4->Controls->Add(this->MRT_hostnameServer);
			this->groupBox4->Controls->Add(this->MRThostnameServerIPaddresslabel);
			this->groupBox4->Location = System::Drawing::Point(7, 94);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(174, 144);
			this->groupBox4->TabIndex = 33;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Data Server IP Address";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(14, 64);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(133, 13);
			this->label4->TabIndex = 29;
			this->label4->Text = L"Local (Client) IPv4 address";
			// 
			// MasterDataServerIPaddresslabeltextBox
			// 
			this->MasterDataServerIPaddresslabeltextBox->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->MasterDataServerIPaddresslabeltextBox->Location = System::Drawing::Point(17, 41);
			this->MasterDataServerIPaddresslabeltextBox->Name = L"MasterDataServerIPaddresslabeltextBox";
			this->MasterDataServerIPaddresslabeltextBox->Size = System::Drawing::Size(148, 20);
			this->MasterDataServerIPaddresslabeltextBox->TabIndex = 26;
			// 
			// LocalDataServerNamelabel
			// 
			this->LocalDataServerNamelabel->AutoSize = true;
			this->LocalDataServerNamelabel->Location = System::Drawing::Point(14, 25);
			this->LocalDataServerNamelabel->Name = L"LocalDataServerNamelabel";
			this->LocalDataServerNamelabel->Size = System::Drawing::Size(104, 13);
			this->LocalDataServerNamelabel->TabIndex = 29;
			this->LocalDataServerNamelabel->Text = L"Master IPv4 address";
			// 
			// LocalDataServerIPaddresslabeltextBox
			// 
			this->LocalDataServerIPaddresslabeltextBox->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F));
			this->LocalDataServerIPaddresslabeltextBox->Location = System::Drawing::Point(17, 80);
			this->LocalDataServerIPaddresslabeltextBox->Name = L"LocalDataServerIPaddresslabeltextBox";
			this->LocalDataServerIPaddresslabeltextBox->Size = System::Drawing::Size(148, 20);
			this->LocalDataServerIPaddresslabeltextBox->TabIndex = 26;
			// 
			// DataServerTableNamegroupBox
			// 
			this->DataServerTableNamegroupBox->Controls->Add(this->label2);
			this->DataServerTableNamegroupBox->Controls->Add(this->HostnameDataServerNamelabeltextBox);
			this->DataServerTableNamegroupBox->Controls->Add(this->label6);
			this->DataServerTableNamegroupBox->Controls->Add(this->label5);
			this->DataServerTableNamegroupBox->Controls->Add(this->LocalDataServerNamelabeltextBox);
			this->DataServerTableNamegroupBox->Controls->Add(this->MasterDataServerNamelabeltextBox);
			this->DataServerTableNamegroupBox->Location = System::Drawing::Point(194, 94);
			this->DataServerTableNamegroupBox->Name = L"DataServerTableNamegroupBox";
			this->DataServerTableNamegroupBox->Size = System::Drawing::Size(165, 144);
			this->DataServerTableNamegroupBox->TabIndex = 32;
			this->DataServerTableNamegroupBox->TabStop = false;
			this->DataServerTableNamegroupBox->Text = L"Data Server Table Name";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(24, 103);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 13);
			this->label2->TabIndex = 32;
			this->label2->Text = L"Hostname";
			// 
			// HostnameDataServerNamelabeltextBox
			// 
			this->HostnameDataServerNamelabeltextBox->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F));
			this->HostnameDataServerNamelabeltextBox->Location = System::Drawing::Point(28, 119);
			this->HostnameDataServerNamelabeltextBox->Name = L"HostnameDataServerNamelabeltextBox";
			this->HostnameDataServerNamelabeltextBox->Size = System::Drawing::Size(125, 20);
			this->HostnameDataServerNamelabeltextBox->TabIndex = 31;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(24, 25);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(39, 13);
			this->label6->TabIndex = 30;
			this->label6->Text = L"Master";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(24, 64);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(68, 13);
			this->label5->TabIndex = 29;
			this->label5->Text = L"Local (Client)";
			// 
			// LocalDataServerNamelabeltextBox
			// 
			this->LocalDataServerNamelabeltextBox->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F));
			this->LocalDataServerNamelabeltextBox->Location = System::Drawing::Point(28, 80);
			this->LocalDataServerNamelabeltextBox->Name = L"LocalDataServerNamelabeltextBox";
			this->LocalDataServerNamelabeltextBox->Size = System::Drawing::Size(125, 20);
			this->LocalDataServerNamelabeltextBox->TabIndex = 28;
			// 
			// MasterDataServerNamelabeltextBox
			// 
			this->MasterDataServerNamelabeltextBox->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F));
			this->MasterDataServerNamelabeltextBox->Location = System::Drawing::Point(27, 41);
			this->MasterDataServerNamelabeltextBox->Name = L"MasterDataServerNamelabeltextBox";
			this->MasterDataServerNamelabeltextBox->Size = System::Drawing::Size(125, 20);
			this->MasterDataServerNamelabeltextBox->TabIndex = 28;
			// 
			// InspectiontabPage
			// 
			this->InspectiontabPage->BackColor = System::Drawing::SystemColors::Control;
			this->InspectiontabPage->Controls->Add(this->Send2TCPcheckBox);
			this->InspectiontabPage->Controls->Add(this->ShowInspectionPopupcheckBox);
			this->InspectiontabPage->Location = System::Drawing::Point(4, 22);
			this->InspectiontabPage->Name = L"InspectiontabPage";
			this->InspectiontabPage->Padding = System::Windows::Forms::Padding(3);
			this->InspectiontabPage->Size = System::Drawing::Size(457, 295);
			this->InspectiontabPage->TabIndex = 1;
			this->InspectiontabPage->Text = L"Inspection";
			// 
			// Send2TCPcheckBox
			// 
			this->Send2TCPcheckBox->AutoSize = true;
			this->Send2TCPcheckBox->Location = System::Drawing::Point(18, 82);
			this->Send2TCPcheckBox->Name = L"Send2TCPcheckBox";
			this->Send2TCPcheckBox->Size = System::Drawing::Size(275, 17);
			this->Send2TCPcheckBox->TabIndex = 3;
			this->Send2TCPcheckBox->Text = L"Send Inspection Message to ONLINE software (GUI)";
			this->Send2TCPcheckBox->UseVisualStyleBackColor = true;
			// 
			// ShowInspectionPopupcheckBox
			// 
			this->ShowInspectionPopupcheckBox->AutoSize = true;
			this->ShowInspectionPopupcheckBox->Location = System::Drawing::Point(18, 59);
			this->ShowInspectionPopupcheckBox->Name = L"ShowInspectionPopupcheckBox";
			this->ShowInspectionPopupcheckBox->Size = System::Drawing::Size(139, 17);
			this->ShowInspectionPopupcheckBox->TabIndex = 0;
			this->ShowInspectionPopupcheckBox->Text = L"Show Inspection Popup";
			this->ShowInspectionPopupcheckBox->UseVisualStyleBackColor = true;
			// 
			// TCPPorttabPage
			// 
			this->TCPPorttabPage->BackColor = System::Drawing::SystemColors::Control;
			this->TCPPorttabPage->Controls->Add(this->TCP_hiddensetgroupBox);
			this->TCPPorttabPage->Location = System::Drawing::Point(4, 22);
			this->TCPPorttabPage->Name = L"TCPPorttabPage";
			this->TCPPorttabPage->Padding = System::Windows::Forms::Padding(3);
			this->TCPPorttabPage->Size = System::Drawing::Size(457, 295);
			this->TCPPorttabPage->TabIndex = 3;
			this->TCPPorttabPage->Text = L"TCP Ports";
			// 
			// TCP_hiddensetgroupBox
			// 
			this->TCP_hiddensetgroupBox->Controls->Add(this->ServerNetworkControlPorttextBox);
			this->TCP_hiddensetgroupBox->Controls->Add(this->label3);
			this->TCP_hiddensetgroupBox->Location = System::Drawing::Point(186, 33);
			this->TCP_hiddensetgroupBox->Name = L"TCP_hiddensetgroupBox";
			this->TCP_hiddensetgroupBox->Size = System::Drawing::Size(244, 83);
			this->TCP_hiddensetgroupBox->TabIndex = 79;
			this->TCP_hiddensetgroupBox->TabStop = false;
			this->TCP_hiddensetgroupBox->Text = L"Server Port (System)";
			// 
			// ServerNetworkControlPorttextBox
			// 
			this->ServerNetworkControlPorttextBox->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F));
			this->ServerNetworkControlPorttextBox->Location = System::Drawing::Point(126, 33);
			this->ServerNetworkControlPorttextBox->Name = L"ServerNetworkControlPorttextBox";
			this->ServerNetworkControlPorttextBox->Size = System::Drawing::Size(72, 20);
			this->ServerNetworkControlPorttextBox->TabIndex = 77;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(15, 36);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(105, 13);
			this->label3->TabIndex = 78;
			this->label3->Text = L"Network Control Port";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 57);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(160, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"NoSerialEventTimeOut (millisec):";
			// 
			// noSerialEventTimeOuttextBox
			// 
			this->noSerialEventTimeOuttextBox->Location = System::Drawing::Point(179, 54);
			this->noSerialEventTimeOuttextBox->Name = L"noSerialEventTimeOuttextBox";
			this->noSerialEventTimeOuttextBox->Size = System::Drawing::Size(50, 20);
			this->noSerialEventTimeOuttextBox->TabIndex = 2;
			// 
			// dlg_ApplicationConfiguration
			// 
			this->AcceptButton = this->OKButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(501, 374);
			this->ControlBox = false;
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->OKButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"dlg_ApplicationConfiguration";
			this->Text = L"Application Configuration";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &dlg_ApplicationConfiguration::dlg_ApplicationConfiguration_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &dlg_ApplicationConfiguration::dlg_ApplicationConfiguration_FormClosed);
			this->Load += gcnew System::EventHandler(this, &dlg_ApplicationConfiguration::dlg_ApplicationConfiguration_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->GeneraltabPage->ResumeLayout(false);
			this->GeneraltabPage->PerformLayout();
			this->OperationModetabPage->ResumeLayout(false);
			this->OperationModetabPage->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->DataServerTableNamegroupBox->ResumeLayout(false);
			this->DataServerTableNamegroupBox->PerformLayout();
			this->InspectiontabPage->ResumeLayout(false);
			this->InspectiontabPage->PerformLayout();
			this->TCPPorttabPage->ResumeLayout(false);
			this->TCP_hiddensetgroupBox->ResumeLayout(false);
			this->TCP_hiddensetgroupBox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void dlg_ApplicationConfiguration_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 int ii;
		/*
				 if ((dlgdata->operationMode & operationMode_PASSWORD_OK)==operationMode_PASSWORD_OK)
					DataBasetabPage->Hide();
				 else
					DataBasetabPage->Hide();
		*/

				 ProductionLineNamecomboBox->Items->Add("---");
				 for (ii=1;ii<=32;ii++)
				 {
					ProductionLineNamecomboBox->Items->Add("-LINE"+ii.ToString()+"-");
				 }
				 ProductionLineNamecomboBox->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.ProdLineName));
				
				 //-------------------------------------------------------
//				 InspectionStationNumbertextBox->Text = dlgdata->appset.InpectionstationNo.ToString();
				 if (dlgdata->appset.ShowInspectionPopup)
					ShowInspectionPopupcheckBox->Checked = true;
				 else
					ShowInspectionPopupcheckBox->Checked = false;
					
				 //-------------------------------------------------------
				 if (dlgdata->appset.sendInspection2GUI)
					Send2TCPcheckBox->Checked = true;
				 else
					Send2TCPcheckBox->Checked = false;	

				 noSerialEventTimeOuttextBox->Text = dlgdata->appset.noSerialEventTimeOut.ToString();

				ServerNetworkControlPorttextBox->Text = dlgdata->appset.serverID_NETWORKCONTROL_PORT.ToString();

				motor_on_delaytextBox->Text = dlgdata->appset.motor_on_delay.ToString();
				LocalDataServerIPaddresslabeltextBox->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.DataServer_local_IPaddress));
				LocalDataServerNamelabeltextBox->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.DataServer_local_Name));
				MasterDataServerIPaddresslabeltextBox->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.DataServer_Master_IPaddress));
				MasterDataServerNamelabeltextBox->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.DataServer_Master_Name));

				 if ((dlgdata->operationMode & operationMode_PASSWORD_OK)!=operationMode_PASSWORD_OK)
				 {
					 DataServerTableNamegroupBox->Visible = false;
					 TCP_hiddensetgroupBox->Visible = false;
					 /*
					 LocalDataServerIPaddresslabeltextBox->Visible = false;
					 LocalDataServerNamelabeltextBox->Visible = false;
					 MasterDataServerIPaddresslabeltextBox->Visible = false;
					 MasterDataServerNamelabeltextBox->Visible = false;
					 */
				 }

				 //MRT_MasterServer->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.MRT_masterSQLServer));
				 MRT_hostnameServer->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.MRT_hostnameServer));
				 HostnameDataServerNamelabeltextBox->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.MRT_hostnameServerName));
				if (dlgdata->appset.StandaloneMode)
				{
					//StandAlone_radioButton->PerformClick();
					StandAlone_radioButton->Checked = true;
					Network_radioButton->Checked = false;
					HostnameDataServerNamelabeltextBox->Enabled = false;
					
				}
				else
				{
					StandAlone_radioButton->Checked = false;
					Network_radioButton->Checked = true;
					HostnameDataServerNamelabeltextBox->Enabled = true;
					
					
				}

				
				/*
				 String ^str = gcnew String(reinterpret_cast<char*>(dlgdata->appset.MRT_hostnameServer));
				 if (str=="")
				 {
					 StandAlone_radioButton->PerformClick();
					 MRT_hostnameServer->Enabled = false;
				 }
				 else
				 {
					 Network_radioButton->PerformClick();
					 MRT_hostnameServer->Enabled = true;
				 }
				 
				 MRT_hostnameServer->Text = str;
				 */
			 }
/*
private: void SetOperationModeToNetwork(bool network)
		 {
				 if (!network)
				 {
					 StandAlone_radioButton->Checked = true;
					 Network_radioButton->Checked = false;
				 }
				 else
				 {
					 StandAlone_radioButton->Checked = false;
					 Network_radioButton->Checked = true;
				}
		 }*/
		 /*
private: System::Void MRT_hostnameServer_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //String ^str = MRT_hostnameServer->Text;
			 //String2Char_n(MRT_hostnameServer->Text, dlgdata->appset.MRT_hostnameServer, sizeof(dlgdata->appset.MRT_hostnameServer)-1);
			 //pin_ptr<const char> name = PtrToStringChars(str);
			 //strcpy(dlgdata->appset.MRT_hostnameServer, name);
		 }
		 */
private: void setStandaloneMode(bool stndalone)
		 {
			 dlgdata->appset.StandaloneMode = stndalone;
			 MRT_hostnameServer->Enabled = !stndalone;
			 //HostnameDataServerNamelabeltextBox->Enabled = !stndalone;

			 MRThostnameServerIPaddresslabel->Enabled = !stndalone;
			 ProductionLineNamelabel->Enabled = stndalone;
			 ProductionLineNamecomboBox->Enabled = stndalone;


			 MasterDataServerIPaddresslabeltextBox->Enabled = !stndalone;
			 LocalDataServerIPaddresslabeltextBox->Enabled = !stndalone;
			 HostnameDataServerNamelabeltextBox->Enabled = !stndalone;

			 if (stndalone)
			 {
				Standalone_label->ForeColor = Color::FromArgb( 0, 84, 240 );
				NetworkModelabel->ForeColor = Color::FromArgb( 192, 192, 192 );
				LocalDataServerIPaddresslabeltextBox->Text = "127.0.0.1";
				MasterDataServerIPaddresslabeltextBox->Text = "127.0.0.1";
			 }
			 else
			 {
				Standalone_label->ForeColor = Color::FromArgb( 192, 192, 192 );
				NetworkModelabel->ForeColor = Color::FromArgb( 0, 84, 240 );
				LocalDataServerIPaddresslabeltextBox->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.DataServer_local_IPaddress));
				MasterDataServerIPaddresslabeltextBox->Text = gcnew String(reinterpret_cast<char*>(dlgdata->appset.DataServer_Master_IPaddress));
			 }
			 NetworkModelabel->Invalidate();
			 Standalone_label->Invalidate();
		 }

private: System::Void StandAlone_radioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //MRT_hostnameServer->Enabled = false;
			 //MRThostnameServerIPaddresslabel->Enabled = false;
			 //ProductionLineNamelabel->Enabled = true;
			 //ProductionLineNamecomboBox->Enabled = true;
			 setStandaloneMode(true);
			 //MRT_hostnameServer->Text = "";
		 }

private: System::Void Network_radioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //MRT_hostnameServer->Enabled = true;
			 //MRThostnameServerIPaddresslabel->Enabled = true;
			 //ProductionLineNamelabel->Enabled = false;
			 //ProductionLineNamecomboBox->Enabled = false;
			 setStandaloneMode(false);
			 //String ^str = gcnew String(reinterpret_cast<char*>(dlgdata->appset.MRT_hostnameServer));
			 //MRT_hostnameServer->Text = str;
		 }



	private: System::Void OKButton_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				String2Char_n(MRT_hostnameServer->Text, dlgdata->appset.MRT_hostnameServer, sizeof(dlgdata->appset.MRT_hostnameServer)-1);
				String2Char_n(HostnameDataServerNamelabeltextBox->Text, dlgdata->appset.MRT_hostnameServerName, sizeof(dlgdata->appset.MRT_hostnameServerName)-1);
				String2Char_n(ProductionLineNamecomboBox->Text, dlgdata->appset.ProdLineName, sizeof(dlgdata->appset.ProdLineName)-1);
				//String2Char_n(MRT_MasterServer->Text, dlgdata->appset.MRT_masterSQLServer, sizeof(dlgdata->appset.MRT_masterSQLServer)-1);
				
				String2Char_n(LocalDataServerIPaddresslabeltextBox->Text, dlgdata->appset.DataServer_local_IPaddress, sizeof(dlgdata->appset.DataServer_local_IPaddress)-1);
				String2Char_n(LocalDataServerNamelabeltextBox->Text, dlgdata->appset.DataServer_local_Name, sizeof(dlgdata->appset.DataServer_local_Name)-1);
				String2Char_n(MasterDataServerIPaddresslabeltextBox->Text, dlgdata->appset.DataServer_Master_IPaddress, sizeof(dlgdata->appset.DataServer_Master_IPaddress)-1);
				String2Char_n(MasterDataServerNamelabeltextBox->Text, dlgdata->appset.DataServer_Master_Name, sizeof(dlgdata->appset.DataServer_Master_Name)-1);


				dlgdata->appset.noSerialEventTimeOut= convertToInt32(noSerialEventTimeOuttextBox->Text);

				dlgdata->appset.serverID_NETWORKCONTROL_PORT = convertToInt32(ServerNetworkControlPorttextBox->Text);

				dlgdata->appset.motor_on_delay = convertToInt32(motor_on_delaytextBox->Text);


				if (StandAlone_radioButton->Checked)
					dlgdata->appset.MRT_hostnameServer[0] = 0x0;

				//------------------------------------------------------------------
				//dlgdata->appset.InpectionstationNo = convertToInt32(InspectionStationNumbertextBox->Text);
				if (ShowInspectionPopupcheckBox->Checked)
					dlgdata->appset.ShowInspectionPopup = 1;
				else
					dlgdata->appset.ShowInspectionPopup = 0;

				//-------------------------------------------------------
				if (Send2TCPcheckBox->Checked)
					dlgdata->appset.sendInspection2GUI = 1;
				else
					dlgdata->appset.sendInspection2GUI = 0;
				

				this->DialogResult = System::Windows::Forms::DialogResult::OK;
		 }

private: System::Void CancelButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		 }

private: System::Void dlg_ApplicationConfiguration_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			 if (Network_radioButton->Checked)
			 {
				 char buf[128];
				 String2Char_n(MRT_hostnameServer->Text, buf, sizeof(buf)-1);
				 if (!isValid_ipv4_IpAddress(buf))
				 {
					String ^standalonemode = StandAlone_radioButton->Text->Replace("&", "");
					String ^errormsg = "Error: Entry \""+ MRThostnameServerIPaddresslabel->Text + 
						"\" is blank or is not a valid IPV4 address. Enter a valid -MASTER- host address e.g. 192.168.2.70\r\n\r\n Or switch to \""+standalonemode+"\" mode";
					MessageBox::Show(this, errormsg, Name, MessageBoxButtons::OK,
					MessageBoxIcon::Information, MessageBoxDefaultButton::Button1);	
					e->Cancel = true;
					return;
				 }
			 }
		 }

private: System::Void dlg_ApplicationConfiguration_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
		 {
		 }

};
}
