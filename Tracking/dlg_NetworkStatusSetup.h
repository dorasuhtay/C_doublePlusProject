//#include <vcclr.h>  
#include "applicationSetting.h"
#include "stringconversion.h"
//#include "socketfunction.h"
//#include "GlobalVariables.h"

#pragma once


typedef struct{
	int operationMode;
	applicationSettingType	appset;
}NetworkStatusSetupType;


namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for dlg_NetworkStatusSetup
	/// </summary>
	public ref class dlg_NetworkStatusSetup : public System::Windows::Forms::Form
	{
	public:
		dlg_NetworkStatusSetup(NetworkStatusSetupType *dlg_data)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			dlgdata = dlg_data;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~dlg_NetworkStatusSetup()
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
	private: System::Windows::Forms::Button^  CancelButton;
	private: System::Windows::Forms::Button^  OKButton;
	private: System::Windows::Forms::TextBox^  networkStatus_MaxAgingtextBox;
	private: System::Windows::Forms::Label^  label1;

		NetworkStatusSetupType *dlgdata;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->networkStatus_MaxAgingtextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// CancelButton
			// 
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Location = System::Drawing::Point(105, 53);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(75, 23);
			this->CancelButton->TabIndex = 15;
			this->CancelButton->Text = L"&Cancel";
			this->CancelButton->UseVisualStyleBackColor = true;
			this->CancelButton->Click += gcnew System::EventHandler(this, &dlg_NetworkStatusSetup::CancelButton_Click);
			// 
			// OKButton
			// 
			this->OKButton->Cursor = System::Windows::Forms::Cursors::Default;
			this->OKButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKButton->Location = System::Drawing::Point(24, 53);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(75, 23);
			this->OKButton->TabIndex = 14;
			this->OKButton->Text = L"&OK";
			this->OKButton->UseVisualStyleBackColor = true;
			this->OKButton->Click += gcnew System::EventHandler(this, &dlg_NetworkStatusSetup::OKButton_Click);
			// 
			// networkStatus_MaxAgingtextBox
			// 
			this->networkStatus_MaxAgingtextBox->Location = System::Drawing::Point(123, 11);
			this->networkStatus_MaxAgingtextBox->Name = L"networkStatus_MaxAgingtextBox";
			this->networkStatus_MaxAgingtextBox->Size = System::Drawing::Size(72, 20);
			this->networkStatus_MaxAgingtextBox->TabIndex = 16;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(8, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(109, 13);
			this->label1->TabIndex = 17;
			this->label1->Text = L"Max Aging (seconds):";
			// 
			// dlg_NetworkStatusSetup
			// 
			this->AcceptButton = this->OKButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(213, 97);
			this->ControlBox = false;
			this->Controls->Add(this->label1);
			this->Controls->Add(this->networkStatus_MaxAgingtextBox);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->OKButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"dlg_NetworkStatusSetup";
			this->Text = L"Network Status Setup";
			this->Load += gcnew System::EventHandler(this, &dlg_NetworkStatusSetup::dlg_NetworkStatusSetup_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void dlg_NetworkStatusSetup_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				networkStatus_MaxAgingtextBox->Text = dlgdata->appset.networkStatus_MaxAging.ToString();
			 }

	private: System::Void OKButton_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 dlgdata->appset.networkStatus_MaxAging = convertToInt32(networkStatus_MaxAgingtextBox->Text);

				 this->DialogResult = System::Windows::Forms::DialogResult::OK;
			 }

	private: System::Void CancelButton_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			 }
};
}
