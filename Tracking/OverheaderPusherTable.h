#include "OverheadPusherClass.h"
#include "stringconversion.h"
//#include "applicationSetting.h"
#include "class_childWindow.h"

#include "SQL_appfunc.h"
#pragma once

namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace common_ClassLib;

	/// <summary>
	/// Summary for OverheaderPusherTable
	/// </summary>
	public ref class OverheaderPusherTable : public System::Windows::Forms::Form
	{
	public:


		OverheaderPusherTable(class_SQLfunc ^sql, childWindowType *configset)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			
			chldWndw = gcnew class_childWindow(configset);
			//applicationSetting = appset;
			//chldWndw = chldWndwSet;
			OverheadPusher = 0;
			pauseUpdate = 0;
			update_rate = 10;
			update_rate_counter = 0;
			blinkcounter = 0;
			blink = 0;
			sqlfunc = sql;
		}
		void setOverheadPusher(OverheadPusherClass *obj) {OverheadPusher = obj;}
		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~OverheaderPusherTable()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
			class_childWindow ^chldWndw;
			class_SQLfunc ^sqlfunc;
	//private:applicationSettingClass *applicationSetting;
	//private:childWindowType *chldWndw;
	private: OverheadPusherClass *OverheadPusher;
	private: bool pauseUpdate;
	private: Color pauseUpdateDefaultColor;
	private: int update_rate;
	private: int update_rate_counter;
	private: int blinkcounter;
	private: int blink;
	Color reminderColor;

	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::Timer^  timer100ms;
	protected: 










	private: System::Windows::Forms::Button^  PauseButton;
	private: System::Windows::Forms::Button^  ClearButton;



	private: System::Windows::Forms::TextBox^  Update_rateTextBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  InFeed;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  InFeedOffset;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  OutFeed;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Round;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  PusherCount;




































	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->timer100ms = (gcnew System::Windows::Forms::Timer(this->components));
			this->PauseButton = (gcnew System::Windows::Forms::Button());
			this->ClearButton = (gcnew System::Windows::Forms::Button());
			this->Update_rateTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->InFeed = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->InFeedOffset = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->OutFeed = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Round = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PusherCount = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			dataGridViewCellStyle1->BackColor = System::Drawing::Color::FloralWhite;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->dataGridView1->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->InFeed, 
				this->InFeedOffset, this->OutFeed, this->Round, this->PusherCount});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->Location = System::Drawing::Point(1, 1);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 55;
			this->dataGridView1->Size = System::Drawing::Size(342, 739);
			this->dataGridView1->TabIndex = 28;
			// 
			// timer100ms
			// 
			this->timer100ms->Tick += gcnew System::EventHandler(this, &OverheaderPusherTable::timer100ms_Tick);
			// 
			// PauseButton
			// 
			this->PauseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->PauseButton->Location = System::Drawing::Point(352, 50);
			this->PauseButton->Name = L"PauseButton";
			this->PauseButton->Size = System::Drawing::Size(75, 23);
			this->PauseButton->TabIndex = 29;
			this->PauseButton->Text = L"Pause";
			this->PauseButton->UseVisualStyleBackColor = true;
			this->PauseButton->Click += gcnew System::EventHandler(this, &OverheaderPusherTable::PauseButton_Click);
			// 
			// ClearButton
			// 
			this->ClearButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ClearButton->Location = System::Drawing::Point(349, 133);
			this->ClearButton->Name = L"ClearButton";
			this->ClearButton->Size = System::Drawing::Size(75, 23);
			this->ClearButton->TabIndex = 30;
			this->ClearButton->Text = L"Clear";
			this->ClearButton->UseVisualStyleBackColor = true;
			this->ClearButton->Click += gcnew System::EventHandler(this, &OverheaderPusherTable::ClearButton_Click);
			// 
			// Update_rateTextBox
			// 
			this->Update_rateTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Update_rateTextBox->Location = System::Drawing::Point(353, 24);
			this->Update_rateTextBox->Name = L"Update_rateTextBox";
			this->Update_rateTextBox->Size = System::Drawing::Size(73, 20);
			this->Update_rateTextBox->TabIndex = 44;
			this->Update_rateTextBox->TextChanged += gcnew System::EventHandler(this, &OverheaderPusherTable::Update_rateTextBox_TextChanged);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(349, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 12);
			this->label2->TabIndex = 43;
			this->label2->Text = L"Update rate (sec)";
			// 
			// InFeed
			// 
			this->InFeed->HeaderText = L"HangerID";
			this->InFeed->Name = L"InFeed";
			this->InFeed->Width = 80;
			// 
			// InFeedOffset
			// 
			this->InFeedOffset->HeaderText = L"Source";
			this->InFeedOffset->Name = L"InFeedOffset";
			this->InFeedOffset->Width = 45;
			// 
			// OutFeed
			// 
			this->OutFeed->HeaderText = L"Dest";
			this->OutFeed->Name = L"OutFeed";
			this->OutFeed->Width = 40;
			// 
			// Round
			// 
			this->Round->HeaderText = L"Round";
			this->Round->Name = L"Round";
			this->Round->Width = 45;
			// 
			// PusherCount
			// 
			this->PusherCount->HeaderText = L"Count Left";
			this->PusherCount->Name = L"PusherCount";
			this->PusherCount->Width = 40;
			// 
			// OverheaderPusherTable
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(436, 742);
			this->Controls->Add(this->Update_rateTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->ClearButton);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"OverheaderPusherTable";
			this->Text = L"OverheaderPusherTable";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &OverheaderPusherTable::OverheaderPusherTable_FormClosing);
			this->Load += gcnew System::EventHandler(this, &OverheaderPusherTable::OverheaderPusherTable_Load);
			this->ResizeEnd += gcnew System::EventHandler(this, &OverheaderPusherTable::OverheaderPusherTable_ResizeEnd);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void OverheaderPusherTable_Load(System::Object^  sender, System::EventArgs^  e) 
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


				FillTable();
				timer100ms->Start();
				timer100ms->Enabled = true;
				pauseUpdateDefaultColor = this->PauseButton->BackColor;
				int rate = update_rate*100;
				Update_rateTextBox->Text = rate.ToString();
				reminderColor = Color::FromArgb( 250, 125, 65 );
			 }

	private: System::Void OverheaderPusherTable_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
			 {
				 if (chldWndw&&(chldWndw!=nullptr))
					chldWndw->ChildWindowClosing(Location.X, Location.Y);
			 }

	private: System::Void FillTable()
			 {
				 if (OverheadPusher)
				 {
					 dataGridView1->Rows->Clear();
					 int ii;
					for (ii=0;ii<OverheadPusher->getcount();ii++)
					{

						dataGridView1->Rows->Add(	OverheadPusher->getHangerID(ii), 
													OverheadPusher->getHangerSrcStation(ii), 
													OverheadPusher->getHangerDestStation(ii),
													OverheadPusher->getRounds(ii),
													OverheadPusher->getRemainder(ii)
													
													);
					}
					int row;
					for (ii=0;ii<OverheadPusher->getcount();ii++)
					{
						row = ii;
						dataGridView1->Rows[ii]->HeaderCell->Value = row.ToString();
					}
					// Autosize the columns.
					//dataGridView1->AutoResizeColumns();
				 }
			 }

	private: Void UpdateTable()
			 {
				if (OverheadPusher)
				{
					int ii, col;
					String ^value = "";
					int ivalue = 0;
					try
					{
						for (ii=0;ii<OverheadPusher->getcount();ii++)
						{
							//class_TCPsocket ^sock = socklist->get(ii);
							Color prevcolor = dataGridView1->Rows[ii]->Cells[0]->Style->BackColor;
							for(col=0;col<dataGridView1->ColumnCount;col++)
							{
								switch(col)
								{
								case	0:  value = OverheadPusher->getHangerID(ii); break;
								case	1:  value = OverheadPusher->getHangerSrcStation(ii); break;
								case	2:  value = OverheadPusher->getHangerDestStation(ii); break;
								case	4:  ivalue = OverheadPusher->getRemainder(ii); 
											if (ivalue>0)
												dataGridView1->Rows[ii]->Cells[col]->Style->BackColor = Color::FromArgb( 225, 255, 213 );
											else
												dataGridView1->Rows[ii]->Cells[col]->Style->BackColor = prevcolor;
											value = ivalue.ToString();
											break;
								case	3:  ivalue = OverheadPusher->getRounds(ii); 
											value = ivalue.ToString();
											break;
										
									/*
											
											value = sock->getstateStr(); 
											break;
								case	4:  value = sock->getSocketTypeStr(); break;
								case	5:  value = sock->index.ToString(); break;
								default:	value = ""; break;
								*/
								}
								dataGridView1->Rows[ii]->Cells[col]->Value = value;
							}	
						}
					}
					catch (...)
					{
					}
				}
			}


private: System::Void timer100ms_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (!pauseUpdate)
			 {
				 if (update_rate>0)
				 {
					if ((update_rate_counter%update_rate)==0)
						UpdateTable();
				 }
			 }
			 else
			 {
				 if ((blinkcounter%5)==0)
				 {
					if (blink)
					{
						blink = 0;
						this->PauseButton->BackColor = pauseUpdateDefaultColor;
					}
					else					
					{
						blink = 1;
						//this->PauseButton->BackColor = Color::Yellow;
						this->PauseButton->BackColor = reminderColor;
						
					}
				 }
				 blinkcounter++;
			 }
			 update_rate_counter++;
		 }


private: System::Void PauseButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (pauseUpdate)
				 pauseUpdate = 0;
			 else
				 pauseUpdate = 1;

			 if (pauseUpdate)
			 {
				 this->PauseButton->Text = L"Resume";
				 //this->PauseButton->BackColor = Color::Yellow;
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
				 //
				 this->PauseButton->Text = L"Pause";
				 this->PauseButton->BackColor = pauseUpdateDefaultColor;
			 }
		 }
		
private: System::Void ClearButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 	String^ message = "Clear \"Overhead Pusher\" monitoring information?";
				 String^ caption = Text;
				 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				 System::Windows::Forms::DialogResult result;
				 // Displays the MessageBox.
				 result = MessageBox::Show( this, message, caption, buttons, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2);
				 if ( result == System::Windows::Forms::DialogResult::Yes )
				 {
					 clearPusherMonitorSQLdb(sqlfunc);
					 OverheadPusher->Clear();
				 }
			
		 }




	private: System::Void Update_rateTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
			 {
				 update_rate = convertToInt32(Update_rateTextBox->Text);
				update_rate = update_rate/100;
				update_rate_counter = 0;
			 }

	private: System::Void OverheaderPusherTable_ResizeEnd(System::Object^  sender, System::EventArgs^  e) 
			 {
				Control^ control = dynamic_cast<Control^>(sender);
				if (chldWndw&&(chldWndw!=nullptr))
					chldWndw->ChildWindowResizeEnd( control->Size.Width, control->Size.Height);
			 }
};
}
