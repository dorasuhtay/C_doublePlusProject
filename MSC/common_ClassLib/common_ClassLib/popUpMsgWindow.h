#pragma once

//davidmod#20120716
enum{
	form_CONSTRUCTOR=1,
	form_LOAD,
	form_CLOSED
};

namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	/// <summary>
	/// Summary for popUpMsgWindow
	/// </summary>
	public ref class popUpMsgWindow : public System::Windows::Forms::Form
	{
	
	public:
		popUpMsgWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			X = 20;
			Y = 20;
		}
		/*
		void appendText(String ^text)
		{
			LabelText->Text += text;
		}*/
		void appendMsgText(String ^text)
		{
			this->MsgBox->SelectedText = text;
			//MsgBox->Text += text;
		}
		
		void clearText()
		{
			this->MsgBox->Clear();
		}
		
		void Clear()
		{
			clearText();
		}

		void setSize(int width, int height)
		{
			Size = System::Drawing::Size(width, height);
		}

		void SetBackColors(Color color)
		{
			BackColor = color;
			this->MsgBox->BackColor = color;
		}
		void SetForeColors(Color color)
		{
			ForeColor = color;
			this->MsgBox->ForeColor = color;
		}
		void setTextColorColor(Color color)
		{
			this->MsgBox->SelectionColor = color;
		}
		void setBorderStyle(BorderStyle value)
		{
			this->MsgBox->BorderStyle = value;
		}

		/*
		void setFontsize(int fontsize)
		{
			this->LabelText->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", fontsize, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
			static_cast<System::Byte>(0)));
		}*/
		void GoHome()
		{
			this->MsgBox->SelectionStart = 0;
		}

		void setFontHeight(float fontheight)
		{
			//this->MsgBox->SetFontHeight(fontheight);
			//this->MsgBox->Font::Height = fontheight;
			/*
			this->MsgBox->SelectionFont =
					 gcnew System::Drawing::Font("Tahoma", fontheight, FontStyle::Bold);
			this->MsgBox->SelectionColor = System::Drawing::Color::Red;
			*/
			
			this->MsgBox->SelectionFont =
				gcnew System::Drawing::Font(L"Microsoft Sans Serif", fontheight, System::Drawing::FontStyle::Regular);
			//this->MsgBox->SelectionColor = System::Drawing::Color::Red;
			//this->MsgBox->SelectedText = "T";

		}
		
		//davidmod#20120716
		void setcallback_function(void (*callback)(int))
		{
			callback_function = callback;
		}
		
		void setLocation(int x, int y)
		{
			X = x;
			Y = y;
		}
				

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~popUpMsgWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private: 
			int X;
			int Y;

	private: System::Windows::Forms::RichTextBox^  MsgBox;
	private:void (*callback_function)(int state);			//davidmod#20120716
	
	

	protected: 

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
			this->MsgBox = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// MsgBox
			// 
			this->MsgBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->MsgBox->BackColor = System::Drawing::Color::Red;
			this->MsgBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->MsgBox->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->MsgBox->ForeColor = System::Drawing::Color::Yellow;
			this->MsgBox->Location = System::Drawing::Point(12, 12);
			this->MsgBox->Name = L"MsgBox";
			this->MsgBox->ReadOnly = true;
			this->MsgBox->Size = System::Drawing::Size(284, 272);
			this->MsgBox->TabIndex = 1;
			this->MsgBox->Text = L"";
			this->MsgBox->TextChanged += gcnew System::EventHandler(this, &popUpMsgWindow::MsgBox_TextChanged);
			// 
			// popUpMsgWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Red;
			this->ClientSize = System::Drawing::Size(308, 296);
			this->Controls->Add(this->MsgBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"popUpMsgWindow";
			this->Opacity = 0.8;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"popUpMsgWindow";
			this->TopMost = true;
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &popUpMsgWindow::popUpMsgWindow_FormClosed);
			this->Load += gcnew System::EventHandler(this, &popUpMsgWindow::popUpMsgWindow_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void popUpMsgWindow_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 Location = System::Drawing::Point(X, Y);
				 clearText();
			 }


//davidmod#20120716
	private: System::Void popUpMsgWindow_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
			 {
				 if (callback_function)
				 {
					callback_function(form_CLOSED);
				 }
			 }
private: System::Void MsgBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
