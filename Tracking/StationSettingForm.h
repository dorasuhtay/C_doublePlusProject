#include "class_Keypad_Interface.h"
#include "stringconversion.h"
#include "hardware\keypad\EE_Key_Map.h"
#include <stdio.h>
#include <string.h>

#pragma once

namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for StationSettingForm
	/// </summary>
	public ref class StationSettingForm : public System::Windows::Forms::Form
	{
	public:
		StationSettingForm(class_Keypad_Interface *station_memory)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			stationMemory = station_memory;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~StationSettingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private: class_Keypad_Interface *stationMemory;
	private: System::Windows::Forms::TextBox^  Update_rateTextBox;
	
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  Prayer17Button;

	private: System::Windows::Forms::Button^  CopyAllButton;
	private: System::Windows::Forms::Button^  PauseButton;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Station;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  StnID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LoadingStation;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LogIn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  PrayerLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  BreakLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  RepairLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  IdleLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  InStatus;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  StationStatus;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  GoStn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  MoveStn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  FindQCStn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  FirmVer;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Contrast;





























































	private:
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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->Update_rateTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Prayer17Button = (gcnew System::Windows::Forms::Button());
			this->CopyAllButton = (gcnew System::Windows::Forms::Button());
			this->PauseButton = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Station = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StnID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LoadingStation = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LogIn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PrayerLabel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->BreakLabel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->RepairLabel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->IdleLabel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->InStatus = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StationStatus = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GoStn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MoveStn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->FindQCStn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->FirmVer = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Contrast = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// Update_rateTextBox
			// 
			this->Update_rateTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Update_rateTextBox->Location = System::Drawing::Point(847, 25);
			this->Update_rateTextBox->Name = L"Update_rateTextBox";
			this->Update_rateTextBox->Size = System::Drawing::Size(73, 20);
			this->Update_rateTextBox->TabIndex = 49;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(846, 10);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 12);
			this->label2->TabIndex = 48;
			this->label2->Text = L"Update rate (sec)";
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(847, 164);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 12);
			this->label1->TabIndex = 47;
			this->label1->Text = L"Copy to Clipboard";
			// 
			// Prayer17Button
			// 
			this->Prayer17Button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Prayer17Button->Location = System::Drawing::Point(848, 274);
			this->Prayer17Button->Name = L"Prayer17Button";
			this->Prayer17Button->Size = System::Drawing::Size(75, 23);
			this->Prayer17Button->TabIndex = 46;
			this->Prayer17Button->Text = L"&Prayer17";
			this->Prayer17Button->UseVisualStyleBackColor = true;
			this->Prayer17Button->Click += gcnew System::EventHandler(this, &StationSettingForm::Prayer17Button_Click);
			// 
			// CopyAllButton
			// 
			this->CopyAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->CopyAllButton->Location = System::Drawing::Point(847, 179);
			this->CopyAllButton->Name = L"CopyAllButton";
			this->CopyAllButton->Size = System::Drawing::Size(75, 23);
			this->CopyAllButton->TabIndex = 45;
			this->CopyAllButton->Text = L"Copy &All";
			this->CopyAllButton->UseVisualStyleBackColor = true;
			// 
			// PauseButton
			// 
			this->PauseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->PauseButton->Location = System::Drawing::Point(847, 51);
			this->PauseButton->Name = L"PauseButton";
			this->PauseButton->Size = System::Drawing::Size(75, 23);
			this->PauseButton->TabIndex = 44;
			this->PauseButton->Text = L"Pause";
			this->PauseButton->UseVisualStyleBackColor = true;
			// 
			// dataGridView1
			// 
			dataGridViewCellStyle3->BackColor = System::Drawing::Color::FloralWhite;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->dataGridView1->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle3;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(15) {this->Station, 
				this->StnID, this->LoadingStation, this->LogIn, this->PrayerLabel, this->BreakLabel, this->RepairLabel, this->IdleLabel, this->InStatus, 
				this->StationStatus, this->GoStn, this->MoveStn, this->FindQCStn, this->FirmVer, this->Contrast});
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle4->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle4->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle4;
			this->dataGridView1->Location = System::Drawing::Point(2, 0);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 55;
			this->dataGridView1->Size = System::Drawing::Size(839, 387);
			this->dataGridView1->TabIndex = 43;
			// 
			// Station
			// 
			this->Station->HeaderText = L"Stn";
			this->Station->Name = L"Station";
			this->Station->Width = 40;
			// 
			// StnID
			// 
			this->StnID->HeaderText = L"Stn ID";
			this->StnID->Name = L"StnID";
			this->StnID->Width = 30;
			// 
			// LoadingStation
			// 
			this->LoadingStation->HeaderText = L"Loading Station";
			this->LoadingStation->Name = L"LoadingStation";
			this->LoadingStation->ToolTipText = L"Loading Station";
			this->LoadingStation->Width = 50;
			// 
			// LogIn
			// 
			this->LogIn->HeaderText = L"Log In";
			this->LogIn->Name = L"LogIn";
			this->LogIn->Width = 30;
			// 
			// PrayerLabel
			// 
			this->PrayerLabel->HeaderText = L"Prayer Label";
			this->PrayerLabel->Name = L"PrayerLabel";
			this->PrayerLabel->Width = 70;
			// 
			// BreakLabel
			// 
			this->BreakLabel->HeaderText = L"Break Label";
			this->BreakLabel->Name = L"BreakLabel";
			this->BreakLabel->Width = 70;
			// 
			// RepairLabel
			// 
			this->RepairLabel->HeaderText = L"Repair Label";
			this->RepairLabel->Name = L"RepairLabel";
			this->RepairLabel->Width = 70;
			// 
			// IdleLabel
			// 
			this->IdleLabel->HeaderText = L"Idle Label";
			this->IdleLabel->Name = L"IdleLabel";
			this->IdleLabel->Width = 50;
			// 
			// InStatus
			// 
			this->InStatus->HeaderText = L"In Status";
			this->InStatus->Name = L"InStatus";
			this->InStatus->Width = 40;
			// 
			// StationStatus
			// 
			this->StationStatus->HeaderText = L"Stn Status";
			this->StationStatus->Name = L"StationStatus";
			this->StationStatus->Width = 35;
			// 
			// GoStn
			// 
			this->GoStn->HeaderText = L"Go Stn";
			this->GoStn->Name = L"GoStn";
			this->GoStn->Width = 30;
			// 
			// MoveStn
			// 
			this->MoveStn->HeaderText = L"Move Stn";
			this->MoveStn->Name = L"MoveStn";
			this->MoveStn->Width = 40;
			// 
			// FindQCStn
			// 
			this->FindQCStn->HeaderText = L"Find QCStn";
			this->FindQCStn->Name = L"FindQCStn";
			this->FindQCStn->Width = 40;
			// 
			// FirmVer
			// 
			this->FirmVer->HeaderText = L"Firm Ver";
			this->FirmVer->Name = L"FirmVer";
			this->FirmVer->Width = 60;
			// 
			// Contrast
			// 
			this->Contrast->HeaderText = L"Contrast";
			this->Contrast->Name = L"Contrast";
			this->Contrast->Width = 40;
			// 
			// StationSettingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(934, 392);
			this->Controls->Add(this->Update_rateTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Prayer17Button);
			this->Controls->Add(this->CopyAllButton);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"StationSettingForm";
			this->Text = L"StationSettingForm";
			this->Load += gcnew System::EventHandler(this, &StationSettingForm::StationSettingForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void StationSettingForm_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 int stn = 13;
				 stationMemory->setPrayerLabel_Default(stn);
				 stationMemory->setBreakLabel_Default(stn);	
				 stationMemory->setRepairLabel_Default(stn);
				 stationMemory->setIdleLabel_Default(stn);
				 stationMemory->setLCDlineLabel(14, Loc_Str_81, L"安装新才可以使用", 8);
				 stationMemory->setLCDlineLabel(15, Loc_Str_81, "安装新才可以使用");
				 stationMemory->setLCDlineLabel(16, Loc_Str_81, "1234567890abcdef");

				 FillTable();
			 }

	private: Void FillTable()
			 {
				 //String ^offlinestr = "";
				 if (stationMemory)
				 {
					 dataGridView1->Rows->Clear();
					 int ii;
					 for (ii=1;ii<stationMemory->getcount();ii++)
					 {
						 /*
						 if (offlineCmd)
						 {
							 if(offlineCmd->isStationOffline(ii))
								 offlinestr = "X";
							 else
								 offlinestr = "";
						 }
						 */
						 dataGridView1->Rows->Add(	ii.ToString(),
														"?", 
														"?",  
														"?", 
														stationMemory->getPrayerLabel(ii),
														stationMemory->getBreakLabel(ii),
														stationMemory->getRepairLabel(ii),
														stationMemory->getIdleLabel(ii),
														"?",
														"?",
														"?",
														"?",
														"?",
														"?",
														"?"
													);
						 				
					 }
					 int row;
					 for (ii=0;ii<stationMemory->getcount();ii++)
					 {
						row = ii+1;
						dataGridView1->Rows[ii]->HeaderCell->Value = row.ToString();
					 }
				 }
			 }
private: System::Void Prayer17Button_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //Prayer17Button

			 stationMemory->setLCDlineLabel(17, Loc_Str_81, "17f");
			 FillTable();
		 }
};
}
