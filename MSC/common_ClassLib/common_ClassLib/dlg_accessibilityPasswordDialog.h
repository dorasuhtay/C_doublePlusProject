
#include <TCHAR.H>
#include < vcclr.h >
//#include "classUserList.h"
#include "stringconversion.h"

#pragma once

namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	typedef struct{
		wchar_t username[64];
		wchar_t password[32];
	}accessibilityPasswordType;

	/// <summary>
	/// Summary for dlg_accessibilityPasswordDialog
	/// </summary>
	public ref class dlg_accessibilityPasswordDialog : public System::Windows::Forms::Form
	{
	public:
		dlg_accessibilityPasswordDialog(accessibilityPasswordType *password)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			passwd = password;
			setInstruction("");
			//userList = user_List;
		}

	void setInstruction(String ^str)
	{
		InstructionLabel->Text = str;
	}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~dlg_accessibilityPasswordDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  passwordEdit;
	protected: 

	private: System::Windows::Forms::Button^  OKButton;
	private: System::Windows::Forms::Button^  CancelButton;

	private: accessibilityPasswordType *passwd;
	private: System::Windows::Forms::Label^  InstructionLabel;	



	private: System::Windows::Forms::Label^  label3;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::TextBox^  usernameEdit;
			 //UserListType *userList;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->passwordEdit = (gcnew System::Windows::Forms::TextBox());
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->InstructionLabel = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->usernameEdit = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 41);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Enter Password:";
			// 
			// passwordEdit
			// 
			this->passwordEdit->Location = System::Drawing::Point(109, 38);
			this->passwordEdit->Name = L"passwordEdit";
			this->passwordEdit->PasswordChar = '*';
			this->passwordEdit->Size = System::Drawing::Size(150, 20);
			this->passwordEdit->TabIndex = 1;
			// 
			// OKButton
			// 
			this->OKButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKButton->Location = System::Drawing::Point(75, 84);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(75, 23);
			this->OKButton->TabIndex = 2;
			this->OKButton->Text = L"&OK";
			this->OKButton->UseVisualStyleBackColor = true;
			this->OKButton->Click += gcnew System::EventHandler(this, &dlg_accessibilityPasswordDialog::OKButton_Click);
			// 
			// CancelButton
			// 
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Location = System::Drawing::Point(184, 84);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(75, 23);
			this->CancelButton->TabIndex = 3;
			this->CancelButton->Text = L"&Cancel";
			this->CancelButton->UseVisualStyleBackColor = true;
			this->CancelButton->Click += gcnew System::EventHandler(this, &dlg_accessibilityPasswordDialog::CancelButton_Click);
			// 
			// InstructionLabel
			// 
			this->InstructionLabel->AutoSize = true;
			this->InstructionLabel->ForeColor = System::Drawing::Color::Red;
			this->InstructionLabel->Location = System::Drawing::Point(12, 61);
			this->InstructionLabel->Name = L"InstructionLabel";
			this->InstructionLabel->Size = System::Drawing::Size(120, 13);
			this->InstructionLabel->TabIndex = 4;
			this->InstructionLabel->Text = L"for now use \"password\"";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 15);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Enter User Name:";
			// 
			// usernameEdit
			// 
			this->usernameEdit->Location = System::Drawing::Point(109, 12);
			this->usernameEdit->Name = L"usernameEdit";
			this->usernameEdit->Size = System::Drawing::Size(150, 20);
			this->usernameEdit->TabIndex = 6;
			// 
			// dlg_accessibilityPasswordDialog
			// 
			this->AcceptButton = this->OKButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(283, 119);
			this->Controls->Add(this->usernameEdit);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->InstructionLabel);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->OKButton);
			this->Controls->Add(this->passwordEdit);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"dlg_accessibilityPasswordDialog";
			this->Text = L"Password";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &dlg_accessibilityPasswordDialog::dlg_accessibilityPasswordDialog_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void dlg_accessibilityPasswordDialog_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 usernameEdit->Text = gcnew String(reinterpret_cast<wchar_t*>(passwd->username));
				 passwordEdit->Text = gcnew String(reinterpret_cast<wchar_t*>(passwd->password));
				 /*
				 if (userList&&userList->name[0])
				 {
					usernameEdit->Text = gcnew String(reinterpret_cast<const char*>(userList->name));
				 }
				 //passwd  passwordEdit
				 */
			 }
			 
private: System::Void OKButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			//String2Char_n(passwordEdit->Text, userList->password, sizeof(userList->password)-1);
			 //String2Char_n(passwordEdit->Text, userList->password, sizeof(userList->password)-1);

			 pin_ptr<const wchar_t> wusername = PtrToStringChars(usernameEdit->Text);
			 _tcscpy_s(passwd->username, wusername);
			 pin_ptr<const wchar_t> wpassword = PtrToStringChars(passwordEdit->Text);
			 _tcscpy_s(passwd->password, wpassword);
			 this->DialogResult = System::Windows::Forms::DialogResult::OK;
		 }
private: System::Void CancelButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		 }
};
}
