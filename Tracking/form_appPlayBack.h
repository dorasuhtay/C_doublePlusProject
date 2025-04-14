#include <stdlib.h>
#include "stringconversion.h"
#include "GlobalVariables.h"
//#include "applicationSetting.h"
#include "class_childWindow.h"
#include "class_appPlayback.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

#pragma once


namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;		

	using namespace common_ClassLib;

	/// <summary>
	/// Summary for form_appPlayBack
	/// </summary>
	public ref class form_appPlayBack : public System::Windows::Forms::Form
	{
	public:
		form_appPlayBack(childWindowType *configset, String ^datapath)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			playbackdelayfactor=0.075F;
			seqnumber = 0;
			secondEventCounter = 0;
			application_PlayBack_is_ON = 0;
			appPlaybackPlay = 0;
			chldWndw = gcnew class_childWindow(configset);
			data_path = datapath;

			playdata = (unsigned char *)malloc(65536);
		}

		int onEventPlayBack(unsigned char *ptrplaydata, unsigned char *playbackType)
		{
			if (!appPlaybackPlay)
				 return 0;
			int size = 0;
			*ptrplaydata = 0;
			//------------------------
			//PLAY_BACK_EVENT
			//------------------------
			if (appPlaybackPlay->IsEvent())
			{
				size = appPlaybackPlay->getbytesAvail();
				*playbackType = appPlaybackPlay->getPlayBack_type();
				memcpy(ptrplaydata, appPlaybackPlay->getPlayBack_payload(), size);		//retrieve the data to be played back
				appPlaybackPlay->continueRead();	//assign the next PLAY_BACK_EVENT
			}
			appPlaybackPlay->advanceEvent();
			return size;
		}

		bool Playing()
		{
			if (appPlaybackPlay)
				return appPlaybackPlay->Playing();
			return 0;
		}

		//---------------------------------------
		//Public variables
		//---------------------------------------
	public:
		float playbackdelayfactor;


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~form_appPlayBack()
		{
			if (components)
			{
				delete components;
			}
			SAFE_DELETE(appPlaybackPlay);
			free(playdata);
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


	private: System::Windows::Forms::Button^  PlayBackbutton;
			 class_childWindow ^chldWndw;

	private: System::Windows::Forms::Timer^  secondeventtimer;
			 String ^data_path;
			 unsigned char *playdata;
			 int secondEventCounter;
			 int seqnumber;
			 
	private: System::Windows::Forms::Label^  playbacklabel;
	private: System::Windows::Forms::TextBox^  playbackfilenametextBox;
	private: System::Windows::Forms::Button^  StopPlaybutton;
			 class_appPlayback *appPlaybackPlay;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->PlayBackbutton = (gcnew System::Windows::Forms::Button());
			this->secondeventtimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->playbacklabel = (gcnew System::Windows::Forms::Label());
			this->playbackfilenametextBox = (gcnew System::Windows::Forms::TextBox());
			this->StopPlaybutton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// PlayBackbutton
			// 
			this->PlayBackbutton->Location = System::Drawing::Point(12, 12);
			this->PlayBackbutton->Name = L"PlayBackbutton";
			this->PlayBackbutton->Size = System::Drawing::Size(75, 23);
			this->PlayBackbutton->TabIndex = 0;
			this->PlayBackbutton->Text = L"Play Back";
			this->PlayBackbutton->UseVisualStyleBackColor = true;
			this->PlayBackbutton->Click += gcnew System::EventHandler(this, &form_appPlayBack::PlayBackbutton_Click);
			// 
			// secondeventtimer
			// 
			this->secondeventtimer->Interval = 1000;
			this->secondeventtimer->Tick += gcnew System::EventHandler(this, &form_appPlayBack::secondeventtimer_Tick);
			// 
			// playbacklabel
			// 
			this->playbacklabel->AutoSize = true;
			this->playbacklabel->Location = System::Drawing::Point(12, 106);
			this->playbacklabel->Name = L"playbacklabel";
			this->playbacklabel->Size = System::Drawing::Size(40, 13);
			this->playbacklabel->TabIndex = 1;
			this->playbacklabel->Text = L"Status:";
			// 
			// playbackfilenametextBox
			// 
			this->playbackfilenametextBox->Location = System::Drawing::Point(12, 55);
			this->playbackfilenametextBox->Name = L"playbackfilenametextBox";
			this->playbackfilenametextBox->Size = System::Drawing::Size(247, 20);
			this->playbackfilenametextBox->TabIndex = 2;
			// 
			// StopPlaybutton
			// 
			this->StopPlaybutton->Location = System::Drawing::Point(93, 12);
			this->StopPlaybutton->Name = L"StopPlaybutton";
			this->StopPlaybutton->Size = System::Drawing::Size(75, 23);
			this->StopPlaybutton->TabIndex = 3;
			this->StopPlaybutton->Text = L"Stop";
			this->StopPlaybutton->UseVisualStyleBackColor = true;
			this->StopPlaybutton->Click += gcnew System::EventHandler(this, &form_appPlayBack::StopPlaybutton_Click);
			// 
			// form_appPlayBack
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(296, 151);
			this->Controls->Add(this->StopPlaybutton);
			this->Controls->Add(this->playbackfilenametextBox);
			this->Controls->Add(this->playbacklabel);
			this->Controls->Add(this->PlayBackbutton);
			this->Name = L"form_appPlayBack";
			this->Text = L"form_appPlayBack";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &form_appPlayBack::form_appPlayBack_FormClosing);
			this->Load += gcnew System::EventHandler(this, &form_appPlayBack::form_appPlayBack_Load);
			this->ResizeEnd += gcnew System::EventHandler(this, &form_appPlayBack::form_appPlayBack_ResizeEnd);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void form_appPlayBack_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
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
				 setplayBack(false);
				 this->secondeventtimer->Enabled = true;
				 this->secondeventtimer->Start();
			 }

	private: System::Void form_appPlayBack_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
			 {
				  if (chldWndw&&(chldWndw!=nullptr))
					chldWndw->ChildWindowClosing(Location.X, Location.Y);
			 }

	private: System::Void form_appPlayBack_ResizeEnd(System::Object^  sender, System::EventArgs^  e) 
			 {
				Control^ control = dynamic_cast<Control^>(sender);
				if (chldWndw&&(chldWndw!=nullptr))
					chldWndw->ChildWindowResizeEnd( control->Size.Width, control->Size.Height);
			 }
			 
	private: System::Void PlayBackbutton_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				if (appPlaybackPlay)
				{
					StopPlayBack();
					/*
					application_PlayBack_is_ON = 0;
					appPlaybackPlay->Close();
					SAFE_DELETE(appPlaybackPlay);
					setplayBack(false);
					*/
				}
				else
				{
					char logfilename[1024];
					logfilename[0] = 0x0;
					OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
					openFileDialog1->InitialDirectory = data_path;
					openFileDialog1->Filter = "rec files (*.rec)|*.rec|All files (*.*)|*.*";
					openFileDialog1->FilterIndex = 1;
					openFileDialog1->RestoreDirectory = true;

					if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
					{
						if (openFileDialog1->OpenFile() != nullptr )
						{
							appPlaybackPlay = new class_appPlayback();
							appPlaybackPlay->setplaybackdelayfactor(playbackdelayfactor);
							String2Char_n(openFileDialog1->FileName , logfilename, sizeof(logfilename)-1);
							appPlaybackPlay->Open(logfilename);
							appPlaybackPlay->firstRead();
							playbackfilenametextBox->Text = gcnew String(reinterpret_cast<const char*>(appPlaybackPlay->getplayfilename()));
							setplayBack(true);
							playbacklabel->ForeColor = Color::FromArgb( 0, 128, 0 );
						}
					}
				}
			 }

private: System::Void setplayBack(bool play)
		 {
			StopPlaybutton->Enabled = play;
			PlayBackbutton->Enabled = !play;
		 }

private: System::Void StopPlayBack()
		 {
			application_PlayBack_is_ON = 0;
			if (appPlaybackPlay)
				appPlaybackPlay->Close();
			SAFE_DELETE(appPlaybackPlay);
			setplayBack(false);
			playbacklabel->ForeColor = Color::FromArgb( 0, 0, 0 );
			playbacklabel->Text = "Status:Stop "+seqnumber.ToString();
		 }

private: System::Void secondeventtimer_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			//---------------------------------------
			// 1 seconds event STATUS reporting
			 // global playing flag
			//----------------------------------------
			if (appPlaybackPlay)
			{
				if (appPlaybackPlay->Playing())
					application_PlayBack_is_ON = 1;
				else
					application_PlayBack_is_ON = 0;
			}
			else
				application_PlayBack_is_ON = 0;

			//---------------------------------------
			// 2 seconds event STATUS reporting
			//----------------------------------------
			if ((secondEventCounter%2)==0)
			{
				if (appPlaybackPlay)
				{
					seqnumber = appPlaybackPlay->getseqNo();
					if (appPlaybackPlay->Playing())
					{
						playbacklabel->Text = "Status:Playing "+seqnumber.ToString();
					}
					else
						StopPlayBack();
				}
			}

			//--------------------------------
			secondEventCounter++;
		 }



private: System::Void StopPlaybutton_Click(System::Object^  sender, System::EventArgs^  e) 	 {	StopPlayBack();	 }



};
}
