#include <Windows.h>
#include <stdio.h>
#include "online_setup.h"
#include "socketfunction.h"
#pragma once



namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for HelpAbout
	/// </summary>
	public ref class HelpAbout : public System::Windows::Forms::Form
	{
	public:
		HelpAbout(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HelpAbout()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  TitleLabel;

	private: System::Windows::Forms::Label^  CopyRightLabel;


	private: System::Windows::Forms::Label^  labelIPAddress;

	private: System::Windows::Forms::Label^  ComputerName_Label;
	private: System::Windows::Forms::Button^  Closebutton;
	private: System::Windows::Forms::ListBox^  ComputerIPAddresslistBox;
	private: System::Windows::Forms::TextBox^  VersiontextBox;
	private: System::Windows::Forms::TextBox^  webURL_textBox;
	private: System::Windows::Forms::TextBox^  support_textBox;

	protected: 


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(HelpAbout::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->TitleLabel = (gcnew System::Windows::Forms::Label());
			this->CopyRightLabel = (gcnew System::Windows::Forms::Label());
			this->labelIPAddress = (gcnew System::Windows::Forms::Label());
			this->ComputerName_Label = (gcnew System::Windows::Forms::Label());
			this->Closebutton = (gcnew System::Windows::Forms::Button());
			this->ComputerIPAddresslistBox = (gcnew System::Windows::Forms::ListBox());
			this->VersiontextBox = (gcnew System::Windows::Forms::TextBox());
			this->webURL_textBox = (gcnew System::Windows::Forms::TextBox());
			this->support_textBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->InitialImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.InitialImage")));
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(511, 125);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// TitleLabel
			// 
			this->TitleLabel->AutoSize = true;
			this->TitleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->TitleLabel->ForeColor = System::Drawing::Color::Blue;
			this->TitleLabel->Location = System::Drawing::Point(7, 140);
			this->TitleLabel->Name = L"TitleLabel";
			this->TitleLabel->Size = System::Drawing::Size(179, 25);
			this->TitleLabel->TabIndex = 1;
			this->TitleLabel->Text = L"Online smartMRT";
			// 
			// CopyRightLabel
			// 
			this->CopyRightLabel->AutoSize = true;
			this->CopyRightLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->CopyRightLabel->Location = System::Drawing::Point(9, 186);
			this->CopyRightLabel->Name = L"CopyRightLabel";
			this->CopyRightLabel->Size = System::Drawing::Size(65, 16);
			this->CopyRightLabel->TabIndex = 3;
			this->CopyRightLabel->Text = L"Copyright";
			// 
			// labelIPAddress
			// 
			this->labelIPAddress->AutoSize = true;
			this->labelIPAddress->Location = System::Drawing::Point(9, 281);
			this->labelIPAddress->Name = L"labelIPAddress";
			this->labelIPAddress->Size = System::Drawing::Size(58, 13);
			this->labelIPAddress->TabIndex = 6;
			this->labelIPAddress->Text = L"IPAddress:";
			// 
			// ComputerName_Label
			// 
			this->ComputerName_Label->AutoSize = true;
			this->ComputerName_Label->Location = System::Drawing::Point(9, 263);
			this->ComputerName_Label->Name = L"ComputerName_Label";
			this->ComputerName_Label->Size = System::Drawing::Size(80, 13);
			this->ComputerName_Label->TabIndex = 7;
			this->ComputerName_Label->Text = L"ComputerName";
			// 
			// Closebutton
			// 
			this->Closebutton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->Closebutton->Location = System::Drawing::Point(452, 325);
			this->Closebutton->Name = L"Closebutton";
			this->Closebutton->Size = System::Drawing::Size(75, 23);
			this->Closebutton->TabIndex = 8;
			this->Closebutton->Text = L"&Close";
			this->Closebutton->UseVisualStyleBackColor = true;
			// 
			// ComputerIPAddresslistBox
			// 
			this->ComputerIPAddresslistBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ComputerIPAddresslistBox->FormattingEnabled = true;
			this->ComputerIPAddresslistBox->ItemHeight = 16;
			this->ComputerIPAddresslistBox->Location = System::Drawing::Point(12, 297);
			this->ComputerIPAddresslistBox->Name = L"ComputerIPAddresslistBox";
			this->ComputerIPAddresslistBox->Size = System::Drawing::Size(144, 52);
			this->ComputerIPAddresslistBox->TabIndex = 9;
			// 
			// VersiontextBox
			// 
			this->VersiontextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->VersiontextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->VersiontextBox->Location = System::Drawing::Point(12, 168);
			this->VersiontextBox->Name = L"VersiontextBox";
			this->VersiontextBox->ReadOnly = true;
			this->VersiontextBox->Size = System::Drawing::Size(511, 15);
			this->VersiontextBox->TabIndex = 10;
			this->VersiontextBox->Text = L"VersiontextBox";
			// 
			// webURL_textBox
			// 
			this->webURL_textBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->webURL_textBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->webURL_textBox->Location = System::Drawing::Point(12, 205);
			this->webURL_textBox->Name = L"webURL_textBox";
			this->webURL_textBox->ReadOnly = true;
			this->webURL_textBox->Size = System::Drawing::Size(511, 15);
			this->webURL_textBox->TabIndex = 11;
			this->webURL_textBox->Text = L"http://www.smartmrt.com";
			// 
			// support_textBox
			// 
			this->support_textBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->support_textBox->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->support_textBox->Location = System::Drawing::Point(12, 226);
			this->support_textBox->Name = L"support_textBox";
			this->support_textBox->ReadOnly = true;
			this->support_textBox->Size = System::Drawing::Size(511, 15);
			this->support_textBox->TabIndex = 12;
			this->support_textBox->Text = L"support@smartmrt.com";
			// 
			// HelpAbout
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->Closebutton;
			this->ClientSize = System::Drawing::Size(539, 361);
			this->Controls->Add(this->support_textBox);
			this->Controls->Add(this->webURL_textBox);
			this->Controls->Add(this->VersiontextBox);
			this->Controls->Add(this->ComputerIPAddresslistBox);
			this->Controls->Add(this->Closebutton);
			this->Controls->Add(this->ComputerName_Label);
			this->Controls->Add(this->labelIPAddress);
			this->Controls->Add(this->CopyRightLabel);
			this->Controls->Add(this->TitleLabel);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"HelpAbout";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"About";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &HelpAbout::HelpAbout_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void HelpAbout_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 this->TitleLabel->Text = Application_TITLENAME;
				 this->VersiontextBox->Text = Application_TITLENAME + " " + Application_VERSION + " " + Application_BUILDNUMBER;
				 this->CopyRightLabel->Text = (wchar_t) 0x00A9 + " 2012 SINGAPORE MACHINERY CO PTE LTD.\r\nAll rights reserved.";
				
				 wchar_t buffer[128];
				 DWORD dwLen = sizeof(buffer);
				 GetComputerName(buffer, &dwLen);
				 this->ComputerName_Label->Text = "Computer name: " + gcnew String(reinterpret_cast<wchar_t*>(buffer));
				 
				 /*
				 IPv4Type myIPaddress;
				 //----------------------------------------
				 getMyIP(myIPaddress);
				 char buf[32];
				 sprintf_s(buf, "%d.%d.%d.%d", myIPaddress.b1, myIPaddress.b2, myIPaddress.b3, myIPaddress.b4);
				 this->ComputerIPAddress->Text = "IPv4 Address: " + gcnew String(reinterpret_cast<char*>(buf));
				 */
				 	const char *ipn;
					class_localMachine *machine = new class_localMachine();
					ipn = machine->getName();
					if (ipn)
					{
						//this->ComputerName_Label->Text = "Computer name: " + gcnew String(reinterpret_cast<const char*>(ipn));
					}
					while((ipn = machine->getIpAddress())!=0)
						ComputerIPAddresslistBox->Items->Add(gcnew String(reinterpret_cast<const char*>(ipn)));

					delete machine;
				 
			 }



};
}
