#include "class_Keypad_Interface.h"
#include "stringconversion.h"
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
	/// Summary for StationMemoryForm
	/// </summary>
	public ref class StationMemoryForm : public System::Windows::Forms::Form
	{
	public:
		StationMemoryForm(class_Keypad_Interface *station_memory)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			stationid=0;
			addressloc=0;
			stationMemory = station_memory;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~StationMemoryForm()
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
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  ClearAllButton;
	private: System::Windows::Forms::Button^  CopyAllButton;
	private: System::Windows::Forms::Label^  LabelTitle;

	private: System::Windows::Forms::TextBox^  MemorytextBox;

	private: System::Windows::Forms::Button^  Updatebutton;
	private: System::Windows::Forms::TextBox^  StationIDtextBox;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
			 class_Keypad_Interface *stationMemory;
			 int stationid;
	private: System::Windows::Forms::NumericUpDown^  PageNo_numericUpDown;
			 int addressloc;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ClearAllButton = (gcnew System::Windows::Forms::Button());
			this->CopyAllButton = (gcnew System::Windows::Forms::Button());
			this->LabelTitle = (gcnew System::Windows::Forms::Label());
			this->MemorytextBox = (gcnew System::Windows::Forms::TextBox());
			this->Updatebutton = (gcnew System::Windows::Forms::Button());
			this->StationIDtextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->PageNo_numericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PageNo_numericUpDown))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(388, 101);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 12);
			this->label1->TabIndex = 54;
			this->label1->Text = L"Copy to Clipboard";
			// 
			// ClearAllButton
			// 
			this->ClearAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ClearAllButton->Location = System::Drawing::Point(388, 27);
			this->ClearAllButton->Name = L"ClearAllButton";
			this->ClearAllButton->Size = System::Drawing::Size(75, 23);
			this->ClearAllButton->TabIndex = 53;
			this->ClearAllButton->Text = L"Clear &All";
			this->ClearAllButton->UseVisualStyleBackColor = true;
			// 
			// CopyAllButton
			// 
			this->CopyAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->CopyAllButton->Location = System::Drawing::Point(390, 116);
			this->CopyAllButton->Name = L"CopyAllButton";
			this->CopyAllButton->Size = System::Drawing::Size(75, 23);
			this->CopyAllButton->TabIndex = 52;
			this->CopyAllButton->Text = L"Copy &All";
			this->CopyAllButton->UseVisualStyleBackColor = true;
			// 
			// LabelTitle
			// 
			this->LabelTitle->AutoSize = true;
			this->LabelTitle->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->LabelTitle->Location = System::Drawing::Point(12, 9);
			this->LabelTitle->Name = L"LabelTitle";
			this->LabelTitle->Size = System::Drawing::Size(88, 16);
			this->LabelTitle->TabIndex = 51;
			this->LabelTitle->Text = L"Memory Map";
			// 
			// MemorytextBox
			// 
			this->MemorytextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->MemorytextBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->MemorytextBox->Location = System::Drawing::Point(12, 28);
			this->MemorytextBox->Multiline = true;
			this->MemorytextBox->Name = L"MemorytextBox";
			this->MemorytextBox->ReadOnly = true;
			this->MemorytextBox->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->MemorytextBox->Size = System::Drawing::Size(370, 460);
			this->MemorytextBox->TabIndex = 50;
			// 
			// Updatebutton
			// 
			this->Updatebutton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Updatebutton->Location = System::Drawing::Point(388, 56);
			this->Updatebutton->Name = L"Updatebutton";
			this->Updatebutton->Size = System::Drawing::Size(75, 23);
			this->Updatebutton->TabIndex = 55;
			this->Updatebutton->Text = L"&Update";
			this->Updatebutton->UseVisualStyleBackColor = true;
			this->Updatebutton->Click += gcnew System::EventHandler(this, &StationMemoryForm::Updatebutton_Click);
			// 
			// StationIDtextBox
			// 
			this->StationIDtextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->StationIDtextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->StationIDtextBox->Location = System::Drawing::Point(393, 178);
			this->StationIDtextBox->Name = L"StationIDtextBox";
			this->StationIDtextBox->Size = System::Drawing::Size(70, 35);
			this->StationIDtextBox->TabIndex = 56;
			this->StationIDtextBox->TextChanged += gcnew System::EventHandler(this, &StationMemoryForm::StationIDtextBox_TextChanged);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(391, 163);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 12);
			this->label2->TabIndex = 58;
			this->label2->Text = L"Station ID";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(391, 224);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 12);
			this->label3->TabIndex = 59;
			this->label3->Text = L"Page [0..7]";
			// 
			// PageNo_numericUpDown
			// 
			this->PageNo_numericUpDown->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->PageNo_numericUpDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->PageNo_numericUpDown->Location = System::Drawing::Point(393, 239);
			this->PageNo_numericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {7, 0, 0, 0});
			this->PageNo_numericUpDown->Name = L"PageNo_numericUpDown";
			this->PageNo_numericUpDown->Size = System::Drawing::Size(70, 35);
			this->PageNo_numericUpDown->TabIndex = 60;
			this->PageNo_numericUpDown->Click += gcnew System::EventHandler(this, &StationMemoryForm::PageNo_numericUpDown_Click);
			// 
			// StationMemoryForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(475, 500);
			this->Controls->Add(this->PageNo_numericUpDown);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->StationIDtextBox);
			this->Controls->Add(this->Updatebutton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ClearAllButton);
			this->Controls->Add(this->CopyAllButton);
			this->Controls->Add(this->LabelTitle);
			this->Controls->Add(this->MemorytextBox);
			this->Name = L"StationMemoryForm";
			this->Text = L"StationMemoryForm";
			this->Load += gcnew System::EventHandler(this, &StationMemoryForm::StationMemoryForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PageNo_numericUpDown))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void StationMemoryForm_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 

				 StationIDtextBox->Text = stationid.ToString();
				  refill();

			 }

	private: System::Void StationIDtextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
			 {
				 stationid = convertToInt32(StationIDtextBox->Text);
				 refill();
			 }
			 
			 /*
private: System::Void AddresstextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 
			 int page = convertToInt32(AddresstextBox->Text);
			 if (page<0)
				 page = 0;
			 if (page>7)
				 page = 7;
			 AddresstextBox->Text = page.ToString();	 
			 addressloc = page*256;
			 
		 }
*/
		 private: Void refill()
		 {
		 	int ii, kk;
			int pagesize = 32;
			char buf[32];
			char value[32];
			char temp[32];
			LabelTitle->Text = "Station:" + stationid.ToString() + " Page:" + (addressloc/256).ToString();

			//unsigned char *address = stationMemory->geteepromLoc(stationid, addressloc);
			unsigned char *address = stationMemory->geteeprom(stationid)+addressloc;
			int pageadress = addressloc;
			if (address)
			{
				MemorytextBox->Text = "";
				for (ii=0;ii<pagesize;ii++)
				{				
					 sprintf(buf, "0x%04X ", pageadress);
					 for(kk=0;kk<8;kk++)
					 {
						 if (((*address)<0x20)||((*address)>=0x80))
							value[kk] = '.';
						 else
							value[kk] = *address;
						
						 sprintf(temp, "%02X ", *address);
						 strcat(buf, temp);
						 address++;
						 pageadress++;
					 }
					 value[kk] = 0x0;
					 String ^line = gcnew String(reinterpret_cast<const char*>(buf));
					 String ^valuestr = gcnew String(reinterpret_cast<const char*>(value));
					 MemorytextBox->Text += line + " " + valuestr + "\r\n";

				 }
				MemorytextBox->SelectionStart  = 0;
				MemorytextBox->SelectionLength = 0;
			 }
		}

private: System::Void Updatebutton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 refill();
		 }

private: System::Void PageNo_numericUpDown_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		 {

		 }
private: System::Void PageNo_numericUpDown_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 int page = convertToInt32(PageNo_numericUpDown->Text);
			  addressloc = page*256;
			  refill();
			  
		 }
};
}
