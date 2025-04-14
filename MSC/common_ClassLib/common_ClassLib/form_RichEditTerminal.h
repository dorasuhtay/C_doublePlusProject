#include <stdio.h>
#include <stdlib.h>
#include "class_childWindow.h"
#include "dlg_RichEditTerminalSetting.h"

#pragma once

#define MAXBUFFERPTR_SIZE		512

namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::Timers;
	using namespace System::Windows::Forms;
	using namespace System::Data::SqlClient;
	using namespace System::Resources;
	using namespace System::Globalization;
	using namespace System::Configuration;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO;		
	using namespace System::Data::Odbc;			
	using namespace System::IO::Ports;
	using namespace System::Xml;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for form_RichEditTerminal
	/// </summary>
	public ref class form_RichEditTerminal : public System::Windows::Forms::Form
	{
	public:

		form_RichEditTerminal(childWindowType *configset)
		{
			InitializeComponent();
			initAll();
			chldWndw = gcnew class_childWindow(configset);
		}


		void setTextColorColor(Color color)
		{
			this->textBox_text->SelectionColor = color;
		}

		void setFont(System::Drawing::Font^ font)
		{
			this->textBox_text->SelectionFont = font;
		}

		
		form_RichEditTerminal(class_childWindow ^chldWindow)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			initAll();			
			chldWndw = chldWindow;
		}

		void defaultPos(int x, int y, int w, int h)
		{
			init_X = x;
			init_Y = y;
			init_W = w;
			init_H = h;
		}

		//--------------------------------------------
		//Public variables
		//--------------------------------------------
		bool Button_Clear;
	private: System::Windows::Forms::Button^  Settingbutton;
	public: 
		bool Button_Pause;






	private:void initAll()
		{
			Button_Clear = true;
			Button_Pause = true;
			init_X = 30;
			init_Y = 30;
			init_W = 600;
			init_H = 500;
			StatusLabeltimeout = -1;
			counter_tick = 0;
			ScrollDownText = true;
			msgFp = 0;
			nextFpptr = 0L;

			msgbuffer = (char *)malloc(MAXBUFFERPTR_SIZE);
			msgbufptr = 0;
		}


	private: System::Windows::Forms::RichTextBox^  textBox_text;




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
				this->textBox_text->SelectedText = text;
				//textBox_text->Text += text;
				terminal_textbox_focus();
			}
		}

		void appendText(String ^text, System::Drawing::Font^ font, Color color)
		{
			if (!pauseUpdate)
			{
				setTextColorColor(color);
				setFont(font);
				appendText(text);
			}
		}

		void appendText(const char *text, System::Drawing::Font^ font, Color color)
		{
			appendText(gcnew String(reinterpret_cast<const char*>(text)), font, color);
		}

		void WriteStatusBar(String ^msg, Color color, int timeout)
		{
			Statuslabel->ForeColor = color;
			Statuslabel->Text = msg;
			StatusLabeltimeout = timeout;
		}

		void setFile(const char *file)
		{
			if (File::Exists(gcnew String(reinterpret_cast<const char*>(file))))
			{
				int result;
				if (msgFp)
					fclose(msgFp);
				msgFp = fopen(file, "r+t");

				fseek( msgFp, 0, SEEK_END );
				int Size = ftell( msgFp );		// get the file size
				nextFpptr = Size - 256-8;
				if (nextFpptr<0L) 
					nextFpptr = 0L;
				if (nextFpptr>0L)
				{
					appendText("...<partial file>...\r\n", courier8font, color_NORMAL);
				}

				fseek ( msgFp , nextFpptr , SEEK_SET );
				nextFpptr = ftell(msgFp);

			}
		}
	//--------------------------------------------
	//Protected functions
	//--------------------------------------------
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~form_RichEditTerminal()
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
				int init_X;
				int init_Y;
				int init_W;
				int init_H;
	private: FILE *msgFp;
	private: char *msgbuffer;
	private: int msgbufptr;
	private: unsigned long nextFpptr;
	private: System::Drawing::Font^ courier8font;
	private: Color color_NORMAL;
	private: Color color_FIFOOUT;
	private: Color color_RESEND;



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
			this->Statuslabel = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->textBox_text = (gcnew System::Windows::Forms::RichTextBox());
			this->Settingbutton = (gcnew System::Windows::Forms::Button());
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
			this->PauseButton->Click += gcnew System::EventHandler(this, &form_RichEditTerminal::PauseButton_Click);
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
			this->ClearAllButton->Click += gcnew System::EventHandler(this, &form_RichEditTerminal::ClearAllButton_Click);
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
			this->CopyAllButton->Click += gcnew System::EventHandler(this, &form_RichEditTerminal::CopyAllButton_Click);
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
			this->timer1->Tick += gcnew System::EventHandler(this, &form_RichEditTerminal::timer1_Tick);
			// 
			// textBox_text
			// 
			this->textBox_text->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_text->Location = System::Drawing::Point(1, 2);
			this->textBox_text->Name = L"textBox_text";
			this->textBox_text->ReadOnly = true;
			this->textBox_text->Size = System::Drawing::Size(349, 442);
			this->textBox_text->TabIndex = 57;
			this->textBox_text->Text = L"";
			// 
			// Settingbutton
			// 
			this->Settingbutton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Settingbutton->Location = System::Drawing::Point(359, 207);
			this->Settingbutton->Name = L"Settingbutton";
			this->Settingbutton->Size = System::Drawing::Size(75, 23);
			this->Settingbutton->TabIndex = 58;
			this->Settingbutton->Text = L"&Setting";
			this->Settingbutton->UseVisualStyleBackColor = true;
			this->Settingbutton->Click += gcnew System::EventHandler(this, &form_RichEditTerminal::Settingbutton_Click);
			// 
			// form_RichEditTerminal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(446, 469);
			this->Controls->Add(this->Settingbutton);
			this->Controls->Add(this->textBox_text);
			this->Controls->Add(this->Statuslabel);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ClearAllButton);
			this->Controls->Add(this->CopyAllButton);
			this->Name = L"form_RichEditTerminal";
			this->Text = L"form_RichEditTerminal";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &form_RichEditTerminal::form_RichEditTerminal_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &form_RichEditTerminal::form_RichEditTerminal_FormClosed);
			this->Load += gcnew System::EventHandler(this, &form_RichEditTerminal::form_RichEditTerminal_Load);
			this->ResizeEnd += gcnew System::EventHandler(this, &form_RichEditTerminal::form_RichEditTerminal_ResizeEnd);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	//--------------------------------------------
	//Private functions
	//--------------------------------------------
	private: System::Void form_RichEditTerminal_Load(System::Object^  sender, System::EventArgs^  e) 
			 {

				courier8font = gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular);

				color_NORMAL = Color::FromArgb( 0, 0, 0 );
				color_FIFOOUT = Color::FromArgb( 252, 153, 18 );
				color_RESEND =  Color::FromArgb( 0, 92, 255 ); 
			
				/*color_FIFOOUT = Color::FromArgb( 255, 0, 0 );
			color_RESEND = Color::FromArgb( 255, 0, 0 ); 
			color_ACK = Color::FromArgb( 0, 92, 255 );
			color_SVROUT = Color::FromArgb( 252, 153, 18 );
			*/
				 pauseUpdateDefaultColor = this->PauseButton->BackColor;

				if(!Button_Clear)
					this->ClearAllButton->Hide();
				if(!Button_Pause)
					this->PauseButton->Hide();
			
				//-------------------------------------------------------------------------
				//update the location and size according to the last sved position in 
				//  "applicationSetting"
				//-------------------------------------------------------------------------
				 if (chldWndw&&(chldWndw!=nullptr))
				 {
					int X, Y, W, H;
					if (chldWndw->ChildWindowGetLocation(&X,  &Y))
						Location = System::Drawing::Point(X, Y);
					else
						Location = System::Drawing::Point(init_X, init_Y);
					if (chldWndw->ChildWindowGetSize(&W,  &H))
						Size = System::Drawing::Size(W, H);
					else
						Size = System::Drawing::Size(init_W, init_H);
				 }
				this->timer1->Enabled = true;
				this->timer1->Start();
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
private: System::Void form_RichEditTerminal_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			 if (chldWndw&&(chldWndw!=nullptr))
				 chldWndw->ChildWindowClosing(Location.X, Location.Y);
		 }
private: System::Void form_RichEditTerminal_ResizeEnd(System::Object^  sender, System::EventArgs^  e) 
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

				
				if (msgFp)
				{
					fseek ( msgFp , nextFpptr , SEEK_SET );
					
					//int counter = 0;
					while(!feof(msgFp))
					{
						int result=fgetc(msgFp);
						if(result>=0)
						{
							switch((char)result)
							{
								case	'\r':
										break;
								case	'\n':
										msgbuffer[msgbufptr++] =  (char)result;
										msgbuffer[msgbufptr] = 0x0;
										msgbufptr = 0;
										{
											char *sptr;
											char temp[128];
											Color color = color_NORMAL;
											char text[128];
											strcpy(text, "_hw_ACK");
											sptr = strstr(msgbuffer, text);
											if (sptr)
											{
												color = color_RESEND;
												strncpy(temp, sptr, strlen(text));
												temp[strlen(text)] = 0x0;
												appendText(temp, courier8font, color);
												sptr = sptr + strlen(text);
												color = color_NORMAL;
											}
											else
												sptr = msgbuffer;
											
											//if (strstr(msgbuffer, "_hw_ACK")==0)
											//	color = color_RESEND;
											
											appendText(sptr, courier8font, color);
										}
										break;
								default:msgbuffer[msgbufptr++] =  (char)result;
										if (msgbufptr>MAXBUFFERPTR_SIZE)
											msgbufptr = 0;
										msgbuffer[msgbufptr]  = 0x0;
										break;

							}
						}
						//if ((counter%10)==0)
						//	Sleep(10);
						//counter++;
					}
					nextFpptr = ftell(msgFp);
					
				}
			}
			counter_tick++;
		 }

private: System::Void form_RichEditTerminal_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
		 {
			 if (msgFp)
				fclose(msgFp);
			 //free(msgbuffer);

		 }

private: System::Void Settingbutton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 /*
			 	System::Windows::Forms::DialogResult result;
				 //testFireRLx.RL1rate = convertToInt32(RL1_CycleRatetextBox->Text);
				 //FireInfeedDialogDataType dlgdata;
				 //dlgdata.interval = testFireRLx.RL1rate;
				 dlg_RichEditTerminalSetting^ dlg = gcnew dlg_RichEditTerminalSetting(&dlgdata);
				 result = dlg->ShowDialog();
				 if ( result == System::Windows::Forms::DialogResult::OK )
				 {
					 //testFireRLx.RL1rate = dlgdata.interval;
					 //RL1_CycleRatetextBox->Text = testFireRLx.RL1rate.ToString();
					//testFire_InFeed();  
				 }
				 //if (form_testFireRelayView&&form_testFireRelayView->Created)
					 //form_testFireRelayView->update();
			 */
		 }
};
}
