#include <TCHAR.H>
#include < vcclr.h >
#pragma once


	typedef struct{
		wchar_t password[32];
		wchar_t confirmPassword[32];
		int passwordlength;
	}stationPasswordType;

	
namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for stationPasswordDialog
	/// </summary>
	public ref class stationPasswordDialog : public System::Windows::Forms::Form
	{
	public:
		stationPasswordDialog(stationPasswordType *password)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			passwd = password;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~stationPasswordDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  helplabel1;
	protected: 

	protected: 
	private: System::Windows::Forms::Button^  CancelButton;
	private: System::Windows::Forms::Button^  OKButton;
	private: System::Windows::Forms::TextBox^  passwordEdit;
	private: System::Windows::Forms::Label^  label1;

	private: stationPasswordType *passwd;
	private: System::Windows::Forms::TextBox^  ConfirmPasswordtextBox;

	private: System::Windows::Forms::Label^  label3;
			bool cancelclosing;		
	private: System::Windows::Forms::Label^  label2;
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
			this->helplabel1 = (gcnew System::Windows::Forms::Label());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->passwordEdit = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ConfirmPasswordtextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// helplabel1
			// 
			this->helplabel1->AutoSize = true;
			this->helplabel1->ForeColor = System::Drawing::SystemColors::WindowText;
			this->helplabel1->Location = System::Drawing::Point(12, 9);
			this->helplabel1->Name = L"helplabel1";
			this->helplabel1->Size = System::Drawing::Size(89, 13);
			this->helplabel1->TabIndex = 9;
			this->helplabel1->Text = L"Station Password";
			// 
			// CancelButton
			// 
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Location = System::Drawing::Point(121, 155);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(75, 23);
			this->CancelButton->TabIndex = 8;
			this->CancelButton->Text = L"&Cancel";
			this->CancelButton->UseVisualStyleBackColor = true;
			this->CancelButton->Click += gcnew System::EventHandler(this, &stationPasswordDialog::CancelButton_Click);
			// 
			// OKButton
			// 
			this->OKButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKButton->Location = System::Drawing::Point(15, 155);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(75, 23);
			this->OKButton->TabIndex = 7;
			this->OKButton->Text = L"&OK";
			this->OKButton->UseVisualStyleBackColor = true;
			this->OKButton->Click += gcnew System::EventHandler(this, &stationPasswordDialog::OKButton_Click);
			// 
			// passwordEdit
			// 
			this->passwordEdit->Location = System::Drawing::Point(112, 36);
			this->passwordEdit->Name = L"passwordEdit";
			this->passwordEdit->PasswordChar = '*';
			this->passwordEdit->Size = System::Drawing::Size(84, 20);
			this->passwordEdit->TabIndex = 6;
			this->passwordEdit->TextChanged += gcnew System::EventHandler(this, &stationPasswordDialog::passwordEdit_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Enter Password:";
			// 
			// ConfirmPasswordtextBox
			// 
			this->ConfirmPasswordtextBox->Location = System::Drawing::Point(112, 62);
			this->ConfirmPasswordtextBox->Name = L"ConfirmPasswordtextBox";
			this->ConfirmPasswordtextBox->PasswordChar = '*';
			this->ConfirmPasswordtextBox->Size = System::Drawing::Size(84, 20);
			this->ConfirmPasswordtextBox->TabIndex = 11;
			this->ConfirmPasswordtextBox->TextChanged += gcnew System::EventHandler(this, &stationPasswordDialog::ConfirmPasswordtextBox_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 65);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(94, 13);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Confirm Password:";
			this->label3->Click += gcnew System::EventHandler(this, &stationPasswordDialog::label3_Click);
			// 
			// label2
			// 
			this->label2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label2->ForeColor = System::Drawing::SystemColors::WindowText;
			this->label2->Location = System::Drawing::Point(15, 95);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(181, 48);
			this->label2->TabIndex = 12;
			this->label2->Text = L"The option allows the administrator to change ALL stations utility, setup and tes" 
				L"t functions Password.";
			// 
			// stationPasswordDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(212, 197);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->ConfirmPasswordtextBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->helplabel1);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->OKButton);
			this->Controls->Add(this->passwordEdit);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"stationPasswordDialog";
			this->Text = L"Station Password Dialog";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &stationPasswordDialog::stationPasswordDialog_FormClosing);
			this->Load += gcnew System::EventHandler(this, &stationPasswordDialog::stationPasswordDialog_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void stationPasswordDialog_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 cancelclosing = false;
				 helplabel1->Text = "Enter Station Password ("+passwd->passwordlength.ToString()+") characters";
			 }

private: System::Void OKButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (passwordEdit->Text->Length==passwd->passwordlength)
			 {
				 if (passwordEdit->Text == ConfirmPasswordtextBox->Text)
				 {
					pin_ptr<const wchar_t> wch = PtrToStringChars(passwordEdit->Text);
					_tcscpy_s(passwd->password, wch);
					pin_ptr<const wchar_t> wch1 = PtrToStringChars(ConfirmPasswordtextBox->Text);
					_tcscpy_s(passwd->confirmPassword, wch1);
				 }
				 else
				 {
					 	String ^errormsg = "Error: Entered and Confirmation of password not the same\r\nPlease Re-Enter again the password";
						MessageBox::Show(this, errormsg, Text, MessageBoxButtons::OK,
						MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);	
						passwordEdit->Text = "";
						ConfirmPasswordtextBox->Text = "";
						cancelclosing = true;
						return;
				 }
			 }
			 else
			 {
					String ^errormsg = "Error: Password must be "+passwd->passwordlength.ToString()+" characters.\r\nPlease Re-Enter";
					MessageBox::Show(this, errormsg, Text, MessageBoxButtons::OK,
					MessageBoxIcon::Exclamation, MessageBoxDefaultButton::Button1);	
					passwordEdit->Text = "";
					ConfirmPasswordtextBox->Text = "";
					cancelclosing = true;
					return;
			 }

			 cancelclosing = false;
			 //pin_ptr<const wchar_t> wch = PtrToStringChars(passwordEdit->Text);
			 //_tcscpy_s(passwd->password, wch);

			 this->DialogResult = System::Windows::Forms::DialogResult::OK;
		 }

private: System::Void CancelButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 cancelclosing = false;
			 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		 }

private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
		 /*
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }*/

private: System::Void ConfirmPasswordtextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 
		 }
private: System::Void passwordEdit_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 
		 }
private: System::Void stationPasswordDialog_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			e->Cancel = cancelclosing;
		 }


};
}
