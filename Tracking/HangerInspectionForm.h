#include <tchar.h>
#include<vcclr.h>
//#include "SQL_func.h"
#include "SQL_appfunc.h"
#pragma once

/*
enum {	form_LOAD=1,
		form_CLOSED,
};*/

namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for HangerInspectionForm
	/// </summary>
	public ref class HangerInspectionForm : public System::Windows::Forms::Form
	{
	//public: System::Int32 **status;
	public:
		HangerInspectionForm(class_SQLfunc ^sql, String ^ipaddress)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->sqlfunc = sql;
			IPAddress = ipaddress;
		}
		
		void setIndex_textBox(String ^str)
		{
			Index_textBox->Text = str;
		}

		void sethangerID(String^ HangerID)
		{
			HangerID_hex = HangerID;
			//----------------------------------
			//Convert the Hanger ID to decimal
			//----------------------------------
			wchar_t *endptr;
			pin_ptr<const wchar_t> wch = PtrToStringChars(HangerID_hex);
			long value = _tcstol(wch, &endptr, 16);		//convert Hex to long
			HangerID_dec = value.ToString()->PadLeft(10, '0'); //long to string

			//---------------------
			this->Text = "Hanger Inspection " + HangerID_hex +" (" + HangerID_dec + ")";
			HangerID_label->Text =  "Hanger:" + HangerID_hex +" (" + HangerID_dec + ")";
		}

	protected: 
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HangerInspectionForm()
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
	private: System::Windows::Forms::Label^  HangerID_label;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::TextBox^  MONO_textBox;
	private: System::Windows::Forms::Label^  Mono_label;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  BundleNo_textBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  Colorlabel;
	private: System::Windows::Forms::TextBox^  Color_textBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  DesignSize_textBox;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  LoadTimetextBox;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  PiecePerHangertextBox;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Station;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LoadingStation;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Offline;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  OPCODE;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Description;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  EmpID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  EMPF;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  settingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fontToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  Index_textBox;

	private: String^ HangerID_hex;
			 String^ HangerID_dec;
			 String^ IPAddress;
			 class_SQLfunc ^sqlfunc;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->HangerID_label = (gcnew System::Windows::Forms::Label());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Station = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LoadingStation = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Offline = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->OPCODE = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Description = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->EmpID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->EMPF = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MONO_textBox = (gcnew System::Windows::Forms::TextBox());
			this->Mono_label = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->BundleNo_textBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->Colorlabel = (gcnew System::Windows::Forms::Label());
			this->Color_textBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->DesignSize_textBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->LoadTimetextBox = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->PiecePerHangertextBox = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->settingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Index_textBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// HangerID_label
			// 
			this->HangerID_label->AutoSize = true;
			this->HangerID_label->Font = (gcnew System::Drawing::Font(L"Courier New", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->HangerID_label->Location = System::Drawing::Point(6, 24);
			this->HangerID_label->Name = L"HangerID_label";
			this->HangerID_label->Size = System::Drawing::Size(88, 18);
			this->HangerID_label->TabIndex = 0;
			this->HangerID_label->Text = L"HangerID";
			// 
			// dataGridView1
			// 
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::FloralWhite;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->dataGridView1->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {this->Station, 
				this->LoadingStation, this->Offline, this->OPCODE, this->Description, this->EmpID, this->EMPF});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->Location = System::Drawing::Point(12, 137);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 55;
			this->dataGridView1->Size = System::Drawing::Size(960, 212);
			this->dataGridView1->TabIndex = 36;
			// 
			// Station
			// 
			this->Station->HeaderText = L"Seq";
			this->Station->Name = L"Station";
			this->Station->Width = 40;
			// 
			// LoadingStation
			// 
			this->LoadingStation->HeaderText = L"Start Time";
			this->LoadingStation->Name = L"LoadingStation";
			this->LoadingStation->ToolTipText = L"Start Time";
			this->LoadingStation->Width = 150;
			// 
			// Offline
			// 
			this->Offline->HeaderText = L"Station";
			this->Offline->Name = L"Offline";
			this->Offline->Width = 50;
			// 
			// OPCODE
			// 
			this->OPCODE->HeaderText = L"OpCode";
			this->OPCODE->Name = L"OPCODE";
			this->OPCODE->Width = 120;
			// 
			// Description
			// 
			this->Description->HeaderText = L"Description";
			this->Description->Name = L"Description";
			this->Description->Width = 200;
			// 
			// EmpID
			// 
			this->EmpID->HeaderText = L"EmpID";
			this->EmpID->Name = L"EmpID";
			// 
			// EMPF
			// 
			this->EMPF->HeaderText = L"Name";
			this->EMPF->Name = L"EMPF";
			this->EMPF->Width = 200;
			// 
			// MONO_textBox
			// 
			this->MONO_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MONO_textBox->Location = System::Drawing::Point(85, 54);
			this->MONO_textBox->Name = L"MONO_textBox";
			this->MONO_textBox->ReadOnly = true;
			this->MONO_textBox->Size = System::Drawing::Size(100, 22);
			this->MONO_textBox->TabIndex = 37;
			// 
			// Mono_label
			// 
			this->Mono_label->AutoSize = true;
			this->Mono_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Mono_label->Location = System::Drawing::Point(38, 57);
			this->Mono_label->Name = L"Mono_label";
			this->Mono_label->Size = System::Drawing::Size(46, 15);
			this->Mono_label->TabIndex = 38;
			this->Mono_label->Text = L"MO No";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(216, 57);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 15);
			this->label1->TabIndex = 40;
			this->label1->Text = L"Design";
			// 
			// BundleNo_textBox
			// 
			this->BundleNo_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->BundleNo_textBox->Location = System::Drawing::Point(268, 54);
			this->BundleNo_textBox->Name = L"BundleNo_textBox";
			this->BundleNo_textBox->ReadOnly = true;
			this->BundleNo_textBox->Size = System::Drawing::Size(100, 22);
			this->BundleNo_textBox->TabIndex = 39;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(6, 84);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(73, 15);
			this->label2->TabIndex = 42;
			this->label2->Text = L"Next Station";
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(85, 81);
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(100, 22);
			this->textBox3->TabIndex = 41;
			// 
			// Colorlabel
			// 
			this->Colorlabel->AutoSize = true;
			this->Colorlabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Colorlabel->Location = System::Drawing::Point(393, 57);
			this->Colorlabel->Name = L"Colorlabel";
			this->Colorlabel->Size = System::Drawing::Size(36, 15);
			this->Colorlabel->TabIndex = 44;
			this->Colorlabel->Text = L"Color";
			// 
			// Color_textBox
			// 
			this->Color_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Color_textBox->Location = System::Drawing::Point(435, 54);
			this->Color_textBox->Name = L"Color_textBox";
			this->Color_textBox->ReadOnly = true;
			this->Color_textBox->Size = System::Drawing::Size(100, 22);
			this->Color_textBox->TabIndex = 43;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(550, 54);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(31, 15);
			this->label3->TabIndex = 46;
			this->label3->Text = L"Size";
			// 
			// DesignSize_textBox
			// 
			this->DesignSize_textBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->DesignSize_textBox->Location = System::Drawing::Point(587, 54);
			this->DesignSize_textBox->Name = L"DesignSize_textBox";
			this->DesignSize_textBox->ReadOnly = true;
			this->DesignSize_textBox->Size = System::Drawing::Size(44, 22);
			this->DesignSize_textBox->TabIndex = 45;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(17, 112);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(62, 15);
			this->label4->TabIndex = 48;
			this->label4->Text = L"Load time";
			// 
			// LoadTimetextBox
			// 
			this->LoadTimetextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->LoadTimetextBox->Location = System::Drawing::Point(85, 109);
			this->LoadTimetextBox->Name = L"LoadTimetextBox";
			this->LoadTimetextBox->ReadOnly = true;
			this->LoadTimetextBox->Size = System::Drawing::Size(148, 22);
			this->LoadTimetextBox->TabIndex = 47;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(236, 84);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(132, 15);
			this->label5->TabIndex = 50;
			this->label5->Text = L"Total Piece Per hanger";
			// 
			// PiecePerHangertextBox
			// 
			this->PiecePerHangertextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->PiecePerHangertextBox->Location = System::Drawing::Point(374, 82);
			this->PiecePerHangertextBox->Name = L"PiecePerHangertextBox";
			this->PiecePerHangertextBox->ReadOnly = true;
			this->PiecePerHangertextBox->Size = System::Drawing::Size(53, 22);
			this->PiecePerHangertextBox->TabIndex = 49;
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::GradientInactiveCaption;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->settingToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(984, 24);
			this->menuStrip1->TabIndex = 51;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// settingToolStripMenuItem
			// 
			this->settingToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->fontToolStripMenuItem});
			this->settingToolStripMenuItem->Name = L"settingToolStripMenuItem";
			this->settingToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->settingToolStripMenuItem->Text = L"&Setting";
			// 
			// fontToolStripMenuItem
			// 
			this->fontToolStripMenuItem->Name = L"fontToolStripMenuItem";
			this->fontToolStripMenuItem->Size = System::Drawing::Size(98, 22);
			this->fontToolStripMenuItem->Text = L"&Font";
			this->fontToolStripMenuItem->Click += gcnew System::EventHandler(this, &HangerInspectionForm::fontToolStripMenuItem_Click);
			// 
			// Index_textBox
			// 
			this->Index_textBox->Location = System::Drawing::Point(955, 27);
			this->Index_textBox->Name = L"Index_textBox";
			this->Index_textBox->ReadOnly = true;
			this->Index_textBox->Size = System::Drawing::Size(29, 20);
			this->Index_textBox->TabIndex = 52;
			this->Index_textBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// HangerInspectionForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(984, 361);
			this->Controls->Add(this->Index_textBox);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->PiecePerHangertextBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->LoadTimetextBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->DesignSize_textBox);
			this->Controls->Add(this->Colorlabel);
			this->Controls->Add(this->Color_textBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->BundleNo_textBox);
			this->Controls->Add(this->Mono_label);
			this->Controls->Add(this->MONO_textBox);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->HangerID_label);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"HangerInspectionForm";
			this->Text = L"HangerInspectionForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &HangerInspectionForm::HangerInspectionForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &HangerInspectionForm::HangerInspectionForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void HangerInspectionForm_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				//--------------------------------------
				//setup the Font for Data Grid
				//--------------------------------------
				dataGridView1->RowsDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0));
				dataGridView1->AlternatingRowsDefaultCellStyle->Font = dataGridView1->RowsDefaultCellStyle->Font;
				
				//--------------------------------------
				//setup the Font for Data Grid
				//--------------------------------------				
				Fill_In_Form();

			 }
	private: System::Void HangerInspectionForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
			 {

			 }

	private: Void Fill_In_Form()
		{
			SqlConnection ^SQLmyConnection;
			int result = sqlfunc->openDBConnection(SQLmyConnection);
			if (result!=0)
				return;
			String ^Prodline = "";
			String ^Mono = "";
			String ^BundleNo = "";
			String ^OPDesc = "";
			String ^SEQNo = "";
			String ^STNid = "";
			String ^OPcode = "";
			String ^BundleLogTime = "";
			String ^EMPid = "";
			String ^EMPfname = "";
			String ^DesignColor = "";
			String ^DesignSize = "";
			String ^LoadTime = "";
			String ^PiecePerHanger = "";
			
			
 		
			//SqlConnection ^SQLmyConnection = openDBConnection();
			SqlCommand ^myCommand = gcnew SqlCommand();
			myCommand->Connection = SQLmyConnection;
			SQLmyConnection->Open();
			myCommand->CommandType = CommandType::Text;								
			myCommand->CommandText =String::Format("SELECT PRODLINE FROM PRODUCTIONLINE WHERE IPADDRESS = '" + IPAddress + "' ");					
			SqlDataReader ^reader = myCommand->ExecuteReader();
			while(reader->Read())
			{		
				Prodline = reader["PRODLINE"]->ToString();
			}					
			reader->Close();

			myCommand->CommandType = CommandType::Text;								
			myCommand->CommandText =String::Format("SELECT * FROM BUNDLE WHERE BUNDLEID = '" + HangerID_hex + 
																			"' AND PRODLINE = '" + Prodline + "'");	
			//-----------------------
			reader = myCommand->ExecuteReader();
			while(reader->Read())
			{												
				Mono = reader["MONO"]->ToString();
				BundleNo = reader["BUNDLENO"]->ToString();
				DesignColor = reader["DESIGNCOLOR"]->ToString();
				DesignSize = reader["DESIGNSIZE"]->ToString();
				LoadTime = reader["LOADTIME"]->ToString();
				PiecePerHanger = reader["PPB"]->ToString();
			}					
			reader->Close();

			//-----------------------------
			//Insert Text into boxes
			//-----------------------------
			MONO_textBox->Text = Mono;
			BundleNo_textBox->Text = BundleNo;
			Color_textBox->Text = DesignColor;
			DesignSize_textBox->Text = DesignSize;
			LoadTimetextBox->Text = LoadTime;
			PiecePerHangertextBox->Text = PiecePerHanger;
		
			//-----------------------------------------
			//Update the Table (DataGrid)
			//-----------------------------------------
			myCommand->CommandType = CommandType::Text;								
			myCommand->CommandText =String::Format("SELECT * FROM ALLBUNDLESEQ WHERE BUNDLENO = '" + BundleNo +
																			"' AND PRODLINE = '" + Prodline + "'");	
			reader = myCommand->ExecuteReader();
			dataGridView1->Rows->Clear();
			while(reader->Read())
			{	
				SEQNo = reader["SEQNO"]->ToString();
				BundleLogTime = reader["BUNDLELOGTIME"]->ToString();
				STNid = reader["STATIONID"]->ToString();
				OPcode = reader["OPCODE"]->ToString();
				OPDesc = reader["OPDESC"]->ToString();
				EMPid = reader["EMPID"]->ToString();
				EMPfname = reader["EMPFNAME"]->ToString();
				//-------------------------------------
				//add a row to the DataGrid Table
				//-------------------------------------
				dataGridView1->Rows->Add(	SEQNo,
											BundleLogTime,
											STNid,
											OPcode,
											OPDesc,
											EMPid,
											EMPfname
											);
			}					
			reader->Close();

			SQLmyConnection->Close();
		}


private: System::Void fontToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			  FontDialog^ myFontDialog = gcnew FontDialog;
			  myFontDialog->Font = dataGridView1->RowsDefaultCellStyle->Font;
			  if ( myFontDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			  {
				 // Set the control's font.
				 dataGridView1->AlternatingRowsDefaultCellStyle->Font = myFontDialog->Font;
				 dataGridView1->RowsDefaultCellStyle->Font  = myFontDialog->Font;
			  }
		 }
};
}
