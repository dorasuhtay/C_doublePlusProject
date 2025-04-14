#include "class_childWindow.h"

#pragma once

namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for form_debugTerminal
	/// </summary>
	public ref class form_debugTerminal : public System::Windows::Forms::Form
	{
	public:

		form_debugTerminal(childWindowType *configset)
		{
			InitializeComponent();
			initAll();
			chldWndw = gcnew class_childWindow(configset);
		}

		form_debugTerminal(class_childWindow ^chldWindow)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			initAll();			
			chldWndw = chldWindow;
		}

	private:void initAll()
		{
			StatusLabeltimeout = -1;
			counter_tick = 0;
			ScrollDownText = true;
		}

	//--------------------------------------------
	//Public variables
	//--------------------------------------------
	public:	int ScrollDownText;

	//--------------------------------------------
	//Public functions
	//--------------------------------------------
	public:
		void appendText(String ^text)
		{
			if (!pauseUpdate)
			{
				textBox_text->Text += text;
				terminal_textbox_focus();
			}
		}
		void WriteStatusBar(String ^msg, Color color, int timeout)
		{
			Statuslabel->ForeColor = color;
			Statuslabel->Text = msg;
			StatusLabeltimeout = timeout;
		}

	//--------------------------------------------
	//Protected functions
	//--------------------------------------------
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~form_debugTerminal()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  PauseButton;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  ClearAllButton;
	private: System::Windows::Forms::Button^  CopyAllButton;
	private: System::Windows::Forms::TextBox^  textBox_text;
	private: System::ComponentModel::IContainer^  components;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

	private: bool pauseUpdate;
	private: Color pauseUpdateDefaultColor;
	private: System::Windows::Forms::Label^  Statuslabel;
	private: System::Windows::Forms::Timer^  timer1;
	private: class_childWindow ^chldWndw;
	private:
				int StatusLabeltimeout;
				int counter_tick;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->PauseButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ClearAllButton = (gcnew System::Windows::Forms::Button());
			this->CopyAllButton = (gcnew System::Windows::Forms::Button());
			this->textBox_text = (gcnew System::Windows::Forms::TextBox());
			this->Statuslabel = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// PauseButton
			// 
			this->PauseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->PauseButton->Location = System::Drawing::Point(359, 12);
			this->PauseButton->Name = L"PauseButton";
			this->PauseButton->Size = System::Drawing::Size(75, 23);
			this->PauseButton->TabIndex = 55;
			this->PauseButton->Text = L"Pause";
			this->PauseButton->UseVisualStyleBackColor = true;
			this->PauseButton->Click += gcnew System::EventHandler(this, &form_debugTerminal::PauseButton_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(356, 99);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 12);
			this->label1->TabIndex = 54;
			this->label1->Text = L"Copy to Clipboard";
			// 
			// ClearAllButton
			// 
			this->ClearAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ClearAllButton->Location = System::Drawing::Point(359, 51);
			this->ClearAllButton->Name = L"ClearAllButton";
			this->ClearAllButton->Size = System::Drawing::Size(75, 23);
			this->ClearAllButton->TabIndex = 53;
			this->ClearAllButton->Text = L"Clear &All";
			this->ClearAllButton->UseVisualStyleBackColor = true;
			this->ClearAllButton->Click += gcnew System::EventHandler(this, &form_debugTerminal::ClearAllButton_Click);
			// 
			// CopyAllButton
			// 
			this->CopyAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->CopyAllButton->Location = System::Drawing::Point(359, 114);
			this->CopyAllButton->Name = L"CopyAllButton";
			this->CopyAllButton->Size = System::Drawing::Size(75, 23);
			this->CopyAllButton->TabIndex = 52;
			this->CopyAllButton->Text = L"Copy &All";
			this->CopyAllButton->UseVisualStyleBackColor = true;
			this->CopyAllButton->Click += gcnew System::EventHandler(this, &form_debugTerminal::CopyAllButton_Click);
			// 
			// textBox_text
			// 
			this->textBox_text->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_text->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox_text->Location = System::Drawing::Point(1, 1);
			this->textBox_text->Multiline = true;
			this->textBox_text->Name = L"textBox_text";
			this->textBox_text->ReadOnly = true;
			this->textBox_text->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox_text->Size = System::Drawing::Size(349, 443);
			this->textBox_text->TabIndex = 51;
			// 
			// Statuslabel
			// 
			this->Statuslabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Statuslabel->AutoSize = true;
			this->Statuslabel->Location = System::Drawing::Point(-2, 447);
			this->Statuslabel->Name = L"Statuslabel";
			this->Statuslabel->Size = System::Drawing::Size(40, 13);
			this->Statuslabel->TabIndex = 56;
			this->Statuslabel->Text = L"Status:";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &form_debugTerminal::timer1_Tick);
			// 
			// form_debugTerminal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(446, 469);
			this->Controls->Add(this->Statuslabel);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ClearAllButton);
			this->Controls->Add(this->CopyAllButton);
			this->Controls->Add(this->textBox_text);
			this->Name = L"form_debugTerminal";
			this->Text = L"form_debugTerminal";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &form_debugTerminal::form_debugTerminal_FormClosing);
			this->Load += gcnew System::EventHandler(this, &form_debugTerminal::form_debugTerminal_Load);
			this->ResizeEnd += gcnew System::EventHandler(this, &form_debugTerminal::form_debugTerminal_ResizeEnd);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	//--------------------------------------------
	//Private functions
	//--------------------------------------------
	private: System::Void form_debugTerminal_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 pauseUpdateDefaultColor = this->PauseButton->BackColor;
			
				//-------------------------------------------------------------------------
				//update the location and size according to the last sved position in 
				//  "applicationSetting"
				//-------------------------------------------------------------------------
				 if (chldWndw&&(chldWndw!=nullptr))
				 {
					int X, Y, W, H;
					if (chldWndw->ChildWindowGetLocation(&X,  &Y))
						Location = System::Drawing::Point(X, Y);
					if (chldWndw->ChildWindowGetSize(&W,  &H))
						Size = System::Drawing::Size(W, H);
				 }
			
			 }

	private: System::Void terminal_textbox_focus()
		 {
			 if (ScrollDownText&&textBox_text&&(textBox_text!=nullptr))
			 {
				//textBox_text->Focus();
				textBox_text->Select(textBox_text->Text->Length, 0);
				textBox_text->ScrollToCaret();
			 }
		 }
	


private: System::Void PauseButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (pauseUpdate)
				 pauseUpdate = 0;
			 else
				 pauseUpdate = 1;

			 if (pauseUpdate)
			 {
				//this->PauseButton->Text = L"Pause";
				//this->PauseButton->BackColor = Color::Yellow;
				Color reminderColor = Color::FromArgb( 255, 255, 0 );
				this->PauseButton->BackColor = reminderColor;
							 

				 /*
				 Color slateBlue = Color::FromName( "SlateBlue" );
   Byte g = slateBlue.G;
   Byte b = slateBlue.B;
   Byte r = slateBlue.R;
   Byte a = slateBlue.A;
   array<Object^>^temp0 = {a,r,g,b};
   String^ text = String::Format( "Slate Blue has these ARGB values: Alpha:{0}, "
   "red:{1}, green: {2}, blue {3}", temp0 );
   e->Graphics->DrawString( text, gcnew System::Drawing::Font( this->Font,FontStyle::Italic ), gcnew SolidBrush( slateBlue ), RectangleF(PointF(0.0F,0.0F),this->Size) );
				 */
			 }
			 else
			 {
				 //this->PauseButton->Text = L"Resume";
				 this->PauseButton->BackColor = pauseUpdateDefaultColor;
			 }
		 }
private: System::Void form_debugTerminal_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			 if (chldWndw&&(chldWndw!=nullptr))
				 chldWndw->ChildWindowClosing(Location.X, Location.Y);
		 }
private: System::Void form_debugTerminal_ResizeEnd(System::Object^  sender, System::EventArgs^  e) 
		 {
			Control^ control = dynamic_cast<Control^>(sender);
			if (chldWndw&&(chldWndw!=nullptr))
				chldWndw->ChildWindowResizeEnd(control->Size.Width, control->Size.Height);
		 }
private: System::Void ClearAllButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			String^ message = "Clear All?";
			String^ caption = Text;
			MessageBoxButtons buttons = MessageBoxButtons::YesNo;
			System::Windows::Forms::DialogResult result;
			// Displays the MessageBox.
			result = MessageBox::Show( this, message, caption, buttons, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2);
			if ( result == System::Windows::Forms::DialogResult::Yes )
			{
			textBox_text->Clear();
			Invalidate();
			}
		 }
private: System::Void CopyAllButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			textBox_text->SelectAll();
			//textBox_OpStatus->SelectionLength();
			textBox_text->Copy();
			/*
			Clipboard::SetDataObject(dataObj, true);
			*/
			//textBox_OpStatus->ClearSelection();
			Color copyColor = Color::FromArgb( 183, 185, 255 );
			this->CopyAllButton->BackColor = copyColor;

			WriteStatusBar("Copied ALL to Clipboard. You may paste into your preferred document",Color::FromArgb( 188, 84, 14 ), -1); 
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			if ((counter_tick%10)==0)		//second event tick
			{
				if (StatusLabeltimeout>-1)
				{
					StatusLabeltimeout--;
					if (StatusLabeltimeout==0)
					{
						//Clear the statusbar
						WriteStatusBar("",Color::FromArgb( 188, 84, 14 ), -1); 
					}
				}
			}
			counter_tick++;
		 }
};
}
