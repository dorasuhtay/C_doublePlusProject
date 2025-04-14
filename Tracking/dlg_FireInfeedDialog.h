#include "GlobalVariables.h"
#include "stringconversion.h"
#pragma once

typedef struct{
	int interval;
}FireInfeedDialogDataType;

namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FireInfeedDialog
	/// </summary>
	public ref class FireInfeedDialog : public System::Windows::Forms::Form
	{
	public:
		FireInfeedDialog(FireInfeedDialogDataType *data)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			dlgdata = data;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FireInfeedDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  IntervalSecond;
	protected: 

	protected: 
	private: System::Windows::Forms::Label^  label1;




	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  OKButton;
	private: System::Windows::Forms::Button^  CancelButton;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: FireInfeedDialogDataType *dlgdata;


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
			this->IntervalSecond = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// IntervalSecond
			// 
			this->IntervalSecond->Location = System::Drawing::Point(73, 48);
			this->IntervalSecond->Name = L"IntervalSecond";
			this->IntervalSecond->Size = System::Drawing::Size(41, 20);
			this->IntervalSecond->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(24, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(195, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Enter in Seconds the activation interval.";
			this->label1->Click += gcnew System::EventHandler(this, &FireInfeedDialog::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(24, 28);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(207, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Enter 0 or blank to stop or to fire once only";
			this->label2->Click += gcnew System::EventHandler(this, &FireInfeedDialog::label2_Click);
			// 
			// OKButton
			// 
			this->OKButton->Cursor = System::Windows::Forms::Cursors::Default;
			this->OKButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKButton->Location = System::Drawing::Point(39, 87);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(75, 23);
			this->OKButton->TabIndex = 5;
			this->OKButton->Text = L"&OK";
			this->OKButton->UseVisualStyleBackColor = true;
			this->OKButton->Click += gcnew System::EventHandler(this, &FireInfeedDialog::OKbutton_Click);
			// 
			// CancelButton
			// 
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Location = System::Drawing::Point(146, 87);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(75, 23);
			this->CancelButton->TabIndex = 6;
			this->CancelButton->Text = L"&Cancel";
			this->CancelButton->UseVisualStyleBackColor = true;
			this->CancelButton->Click += gcnew System::EventHandler(this, &FireInfeedDialog::CancelButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(120, 51);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(86, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Seconds interval";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(50, 51);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(16, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"at";
			// 
			// FireInfeedDialog
			// 
			this->AcceptButton = this->OKButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->CancelButton;
			this->ClientSize = System::Drawing::Size(265, 122);
			this->ControlBox = false;
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->OKButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->IntervalSecond);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"FireInfeedDialog";
			this->Text = L"Activation Interval";
			this->Load += gcnew System::EventHandler(this, &FireInfeedDialog::FireInfeedDialog_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }

private: System::Void OKbutton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 dlgdata->interval = convertToInt32(IntervalSecond->Text);
			 this->DialogResult = System::Windows::Forms::DialogResult::OK;
		 }

private: System::Void FireInfeedDialog_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			IntervalSecond->Text = dlgdata->interval.ToString();
		 }

private: System::Void CancelButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		 }
};

}
