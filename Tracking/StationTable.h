#include "StationOperatorClass.h"
//#include "GlobalVariables.h"
#include "stringconversion.h"
#include "applicationSetting.h"
#include "offlineCommandClass.h"
#include "class_processError.h"
#include "class_childWindow.h"


#include "SQL_appfunc.h"

#pragma once

//extern int reload_StationOperator(StationOperatorClass *StationOperator, String^ dIPAddress);

namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace common_ClassLib;

	/// <summary>
	/// Summary for StationTable
	/// </summary>
	public ref class StationTable : public System::Windows::Forms::Form
	{
	public:
		StationTable(class_SQLfunc ^sql, childWindowType *configset, applicationSettingClass *appset, offlineCommandClass *offline, String ^prodline)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			initAll();

			
			applicationSetting = appset;
			chldWndw = gcnew class_childWindow(configset);
			offlineCmd = offline;
			sqlfunc = sql;
			Prodline = prodline;
		}
		
		void defaultPos(int x, int y, int w, int h)
		{
			init_X = x;
			init_Y = y;
			init_W = w;
			init_H = h;
		}

	private: System::Windows::Forms::Timer^  timer100ms;
			 offlineCommandClass *offlineCmd;
			 class_SQLfunc ^sqlfunc;
			 String ^Prodline;
	public: 

	private: bool pauseUpdate;
	private: Color pauseUpdateDefaultColor;

















	private: System::Windows::Forms::Label^  label2;














	private: System::Windows::Forms::TextBox^  Update_rateTextBox;
















			 //private: System::Windows::Forms::Button^  PauseButton;
	public: 
	
	



























	private:applicationSettingClass *applicationSetting;
	private: class_childWindow ^chldWndw;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Station;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Offline;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  LoadingStation;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  LogIn;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  EmpID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  EMPF;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  EMPL;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  OPCODE;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  InStatus;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  StationStatus;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  GoStn;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  MoveStn;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  FindQCStn;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  OpreFunction;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  CmdID;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  IPaddress;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  BreakStatus;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  status;

































	private:StationOperatorClass *StationOperator;
	public: void setObj(StationOperatorClass *obj) {StationOperator = obj;}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~StationTable()
		{
			if (components)
			{
				delete components;
			}
		}
	private: int update_rate;
	private: int update_rate_counter;
			int init_X;
			int init_Y;
			int init_W;
			int init_H;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  ReloadAllButton;
	protected: 

	private: System::Windows::Forms::Button^  CopyAllButton;
	private: System::Windows::Forms::Button^  PauseButton;
	private: System::Windows::Forms::DataGridView^  dataGridView1;










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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ReloadAllButton = (gcnew System::Windows::Forms::Button());
			this->CopyAllButton = (gcnew System::Windows::Forms::Button());
			this->PauseButton = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->timer100ms = (gcnew System::Windows::Forms::Timer(this->components));
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Update_rateTextBox = (gcnew System::Windows::Forms::TextBox());
			this->Station = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Offline = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LoadingStation = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LogIn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->EmpID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->EMPF = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->EMPL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->OPCODE = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->InStatus = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->StationStatus = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->GoStn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->MoveStn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->FindQCStn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->OpreFunction = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->CmdID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->IPaddress = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->BreakStatus = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->status = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(753, 161);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 12);
			this->label1->TabIndex = 39;
			this->label1->Text = L"Copy to Clipboard";
			// 
			// ReloadAllButton
			// 
			this->ReloadAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ReloadAllButton->Location = System::Drawing::Point(753, 123);
			this->ReloadAllButton->Name = L"ReloadAllButton";
			this->ReloadAllButton->Size = System::Drawing::Size(75, 23);
			this->ReloadAllButton->TabIndex = 38;
			this->ReloadAllButton->Text = L"&Reload";
			this->ReloadAllButton->UseVisualStyleBackColor = true;
			this->ReloadAllButton->Click += gcnew System::EventHandler(this, &StationTable::ClearAllButton_Click);
			// 
			// CopyAllButton
			// 
			this->CopyAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->CopyAllButton->Location = System::Drawing::Point(753, 176);
			this->CopyAllButton->Name = L"CopyAllButton";
			this->CopyAllButton->Size = System::Drawing::Size(75, 23);
			this->CopyAllButton->TabIndex = 37;
			this->CopyAllButton->Text = L"Copy &All";
			this->CopyAllButton->UseVisualStyleBackColor = true;
			this->CopyAllButton->Click += gcnew System::EventHandler(this, &StationTable::CopyAllButton_Click);
			// 
			// PauseButton
			// 
			this->PauseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->PauseButton->Location = System::Drawing::Point(753, 48);
			this->PauseButton->Name = L"PauseButton";
			this->PauseButton->Size = System::Drawing::Size(75, 23);
			this->PauseButton->TabIndex = 36;
			this->PauseButton->Text = L"Pause";
			this->PauseButton->UseVisualStyleBackColor = true;
			this->PauseButton->Click += gcnew System::EventHandler(this, &StationTable::PauseButton_Click);
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
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(18) {this->Station, 
				this->Offline, this->LoadingStation, this->LogIn, this->EmpID, this->EMPF, this->EMPL, this->OPCODE, this->InStatus, this->StationStatus, 
				this->GoStn, this->MoveStn, this->FindQCStn, this->OpreFunction, this->CmdID, this->IPaddress, this->BreakStatus, this->status});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->Location = System::Drawing::Point(0, 0);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 55;
			this->dataGridView1->Size = System::Drawing::Size(747, 481);
			this->dataGridView1->TabIndex = 35;
			// 
			// timer100ms
			// 
			this->timer100ms->Tick += gcnew System::EventHandler(this, &StationTable::timer1_Tick);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(752, 7);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 12);
			this->label2->TabIndex = 41;
			this->label2->Text = L"Update rate (sec)";
			this->label2->Click += gcnew System::EventHandler(this, &StationTable::label2_Click);
			// 
			// Update_rateTextBox
			// 
			this->Update_rateTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Update_rateTextBox->Location = System::Drawing::Point(753, 22);
			this->Update_rateTextBox->Name = L"Update_rateTextBox";
			this->Update_rateTextBox->Size = System::Drawing::Size(73, 20);
			this->Update_rateTextBox->TabIndex = 42;
			this->Update_rateTextBox->TextChanged += gcnew System::EventHandler(this, &StationTable::Update_rateTextBox_TextChanged);
			// 
			// Station
			// 
			this->Station->HeaderText = L"Stn";
			this->Station->Name = L"Station";
			this->Station->Width = 40;
			// 
			// Offline
			// 
			this->Offline->HeaderText = L"Off line";
			this->Offline->Name = L"Offline";
			this->Offline->Width = 30;
			// 
			// LoadingStation
			// 
			this->LoadingStation->HeaderText = L"Loading Station";
			this->LoadingStation->Name = L"LoadingStation";
			this->LoadingStation->ToolTipText = L"Loading Station";
			this->LoadingStation->Width = 50;
			// 
			// LogIn
			// 
			this->LogIn->HeaderText = L"Log In";
			this->LogIn->Name = L"LogIn";
			this->LogIn->Width = 30;
			// 
			// EmpID
			// 
			this->EmpID->HeaderText = L"EmpID";
			this->EmpID->Name = L"EmpID";
			this->EmpID->Width = 70;
			// 
			// EMPF
			// 
			this->EMPF->HeaderText = L"EMPF";
			this->EMPF->Name = L"EMPF";
			this->EMPF->Width = 70;
			// 
			// EMPL
			// 
			this->EMPL->HeaderText = L"EMPL";
			this->EMPL->Name = L"EMPL";
			this->EMPL->Width = 70;
			// 
			// OPCODE
			// 
			this->OPCODE->HeaderText = L"OP CODE";
			this->OPCODE->Name = L"OPCODE";
			this->OPCODE->Width = 50;
			// 
			// InStatus
			// 
			this->InStatus->HeaderText = L"In Status";
			this->InStatus->Name = L"InStatus";
			this->InStatus->Width = 40;
			// 
			// StationStatus
			// 
			this->StationStatus->HeaderText = L"Stn Status";
			this->StationStatus->Name = L"StationStatus";
			this->StationStatus->Width = 35;
			// 
			// GoStn
			// 
			this->GoStn->HeaderText = L"Go Stn";
			this->GoStn->Name = L"GoStn";
			this->GoStn->Width = 30;
			// 
			// MoveStn
			// 
			this->MoveStn->HeaderText = L"Move Stn";
			this->MoveStn->Name = L"MoveStn";
			this->MoveStn->Width = 40;
			// 
			// FindQCStn
			// 
			this->FindQCStn->HeaderText = L"Find QCStn";
			this->FindQCStn->Name = L"FindQCStn";
			this->FindQCStn->Width = 40;
			// 
			// OpreFunction
			// 
			this->OpreFunction->HeaderText = L"Opre Func";
			this->OpreFunction->Name = L"OpreFunction";
			this->OpreFunction->Width = 40;
			// 
			// CmdID
			// 
			this->CmdID->HeaderText = L"Cmd ID";
			this->CmdID->Name = L"CmdID";
			this->CmdID->Width = 40;
			// 
			// IPaddress
			// 
			this->IPaddress->HeaderText = L"IP";
			this->IPaddress->Name = L"IPaddress";
			// 
			// BreakStatus
			// 
			this->BreakStatus->HeaderText = L"Break Status";
			this->BreakStatus->Name = L"BreakStatus";
			// 
			// status
			// 
			this->status->HeaderText = L"status";
			this->status->Name = L"status";
			// 
			// StationTable
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(840, 485);
			this->Controls->Add(this->Update_rateTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ReloadAllButton);
			this->Controls->Add(this->CopyAllButton);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"StationTable";
			this->Text = L"StationTable";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &StationTable::StationTable_FormClosing);
			this->Load += gcnew System::EventHandler(this, &StationTable::StationTable_Load);
			this->ResizeEnd += gcnew System::EventHandler(this, &StationTable::StationTable_ResizeEnd);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void StationTable_Load(System::Object^  sender, System::EventArgs^  e) 
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
				else
					Location = System::Drawing::Point(init_X, init_Y);
				if (chldWndw->ChildWindowGetSize(&W,  &H))
					Size = System::Drawing::Size(W, H);
				else
					Size = System::Drawing::Size(init_W, init_H);
				}

				FillTable();
				timer100ms->Start();
				timer100ms->Enabled = true;
				pauseUpdateDefaultColor = this->PauseButton->BackColor;
				int rate = update_rate*100;
				Update_rateTextBox->Text = rate.ToString();
			 }


	private:void initAll()
		{
			Prodline = "";
			StationOperator = 0;
			update_rate = 10;
			update_rate_counter = 0;
			//Button_Clear = true;
			//Button_Pause = true;
			init_X = 30;
			init_Y = 30;
			init_W = 600;
			init_H = 500;
			//StatusLabeltimeout = -1;
			//counter_tick = 0;
			//ScrollDownText = true;
		}

	private: System::Void FillTable()
			 {
				 String ^offlinestr = "";
				 if (StationOperator)
				 {
					 dataGridView1->Rows->Clear();
					 int ii;
					 for (ii=1;ii<StationOperator->getcount();ii++)
					 {
						 if (offlineCmd)
						 {
							 if(offlineCmd->isStationOffline(ii))
								 offlinestr = "X";
							 else
								 offlinestr = "";
						 }
						 dataGridView1->Rows->Add(	ii.ToString(),
														offlinestr, 
														StationOperator->getLoadingStation(ii), 
														StationOperator->getloggedIn(ii), 
														StationOperator->getEMPID(ii),
														StationOperator->getEMPFname(ii),
														StationOperator->getEMPLname(ii),
														StationOperator->getCurOpCode(ii),
														StationOperator->getIn_Status(ii),
														StationOperator->getStationStatus(ii),
														StationOperator->getGoStn(ii),
														StationOperator->getMoveStn(ii),
														StationOperator->getQCStn(ii),
														StationOperator->getOprefunction(ii),
														StationOperator->get_CMDID(ii).ToString(),
														StationOperator->getStationIPaddress(ii),
														StationOperator->getBreakName(ii),
														StationOperator->getBreakName(ii)
													);
						 				
					 }
					 int row;
					 for (ii=0;ii<StationOperator->getcount();ii++)
					 {
						row = ii+1;
						dataGridView1->Rows[ii]->HeaderCell->Value = row.ToString();
					 }
				 }
			 }

	private: Void setloginColor(int index, int row, int col, Color prevcolor)
			 {
				if (StationOperator->isloggedIn(index))
					dataGridView1->Rows[row]->Cells[col]->Style->BackColor = Color::FromArgb( 225, 255, 213 );
				else
					dataGridView1->Rows[row]->Cells[col]->Style->BackColor = prevcolor;
			 }

	private: Void UpdateTable()
			 {
				if (StationOperator)
				{
					Color normalBackcolor = Color::FromArgb( 255, 255, 255 );
					int ii, col;
					String ^value = "";
					int ivalue = 0;
					try
					{
						String ^offlinestr = "";
						int row = 0;
						for (ii=1;ii<StationOperator->getcount();ii++)
						{
							//class_TCPsocket ^sock = socklist->get(ii);
							if (offlineCmd)
							{
								if(offlineCmd->isStationOffline(ii))
									offlinestr = "X";
								else
									offlinestr = "";
							}
							//dataGridView1->Rows[row]->Cells[0]->Style->BackColor;
							//Color prevforecolor = dataGridView1->Rows[row]->Cells[0]->Style->ForeColor;
							for(col=0;col<dataGridView1->ColumnCount;col++)
							{
								switch(col)
								{
								case	0:  value = ii.ToString(); 
											if(StationOperator->getBreakStatus(ii)=="Y")
												dataGridView1->Rows[row]->Cells[col]->Style->BackColor = Color::FromArgb( 248, 115, 35 );
											else
												dataGridView1->Rows[row]->Cells[col]->Style->BackColor = normalBackcolor;
											break;
								case	1:  value = offlinestr; 	break;
								case	2:  value = StationOperator->getLoadingStation(ii); 
											if (StationOperator->isLoadingStation(ii))
												dataGridView1->Rows[row]->Cells[col]->Style->BackColor = Color::FromArgb( 255, 255, 0 );
											else
												dataGridView1->Rows[row]->Cells[col]->Style->BackColor = normalBackcolor;
											break;
								case	3:  value = StationOperator->getloggedIn(ii); 	setloginColor(ii, row, col, normalBackcolor);break;
								case	4:  value = StationOperator->getEMPID(ii);		setloginColor(ii, row, col, normalBackcolor);break;
								case	5:  value = StationOperator->getEMPFname(ii);	setloginColor(ii, row, col, normalBackcolor);break;
								case	6:  value = StationOperator->getEMPLname(ii);	setloginColor(ii, row, col, normalBackcolor);break;
								case	7:  value = StationOperator->getCurOpCode(ii); break;
								case	8:  value = StationOperator->getIn_Status(ii); break;
								case	9:  value = StationOperator->getStationStatus(ii); break;
								case	10: value = StationOperator->getGoStn(ii); break;
								case	11: value = StationOperator->getMoveStn(ii); break;
								case	12: value = StationOperator->getQCStn(ii); break;
								case	13: value = StationOperator->getOprefunction(ii); break;
								case	14: value = StationOperator->get_CMDID(ii).ToString(); break;
								case	15: value = StationOperator->getStationIPaddress(ii); break;
								case	16: value = StationOperator->getBreakName(ii);
											if(StationOperator->getBreakStatus(ii)=="Y")
												dataGridView1->Rows[row]->Cells[col]->Style->BackColor = Color::FromArgb( 248, 115, 35 );
											else
												dataGridView1->Rows[row]->Cells[col]->Style->BackColor = normalBackcolor;
											break;
								}

								if (offlineCmd->isStationOffline(ii))
									dataGridView1->Rows[row]->Cells[col]->Style->ForeColor = Color::FromArgb( 192, 192, 192 );
								else
									dataGridView1->Rows[row]->Cells[col]->Style->ForeColor = Color::FromArgb( 0, 0, 0 );
								dataGridView1->Rows[row]->Cells[col]->Value = value;
							}
							row++;
						}
					}
					catch (...)
					{
					}
				}
			}

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (!pauseUpdate)
			 {
				 if (update_rate>0)
				 {
					if ((update_rate_counter%update_rate)==0)
						UpdateTable();
				 }
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



private: System::Void Update_rateTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			update_rate = convertToInt32(Update_rateTextBox->Text);
			update_rate = update_rate/100;
			update_rate_counter = 0;
		 }
/*
private: System::Void CopyAllButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			dataGridView1->SelectAll();
			DataObject ^dataObj = dataGridView1->GetClipboardContent();
			Clipboard ^clipb;
			clipb->SetDataObject(dataObj, true);
			dataGridView1->ClearSelection();
			Color copyColor = Color::FromArgb( 183, 185, 255 );
			this->CopyAllButton->BackColor = copyColor;
		 }

private: System::Void ClearAllButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 	String^ message = "Clear \"Hanger Tag\" monitoring information?";
				 String^ caption = Text;
				 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				 System::Windows::Forms::DialogResult result;
				 // Displays the MessageBox.
				 result = MessageBox::Show( this, message, caption, buttons, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2);
				 if ( result == System::Windows::Forms::DialogResult::Yes )
				 {
					HangerTag->Clear();
					Invalidate();
				 }
		 }
*/

private: System::Void ClearAllButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 	String^ message = "Reload \"Station\" monitoring information?";
				 String^ caption = Text;
				 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				 System::Windows::Forms::DialogResult result;
				 // Displays the MessageBox.
				 result = MessageBox::Show( this, message, caption, buttons, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2);
				 if ( result == System::Windows::Forms::DialogResult::Yes )
				 {
					String ^DefIPAddress = gcnew String(reinterpret_cast<const char*>(applicationSetting->data.DefIPAddress));
					int result;
					
					if (result=reload_StationOperator(sqlfunc, StationOperator, DefIPAddress, Prodline)!=0)
					{
						processErrorLog->logError("SQL", result, __FILE__, __LINE__, "");
					}
					Invalidate();
				 }
		 }
private: System::Void CopyAllButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			dataGridView1->SelectAll();
			DataObject ^dataObj = dataGridView1->GetClipboardContent();
			//Clipboard ^clipb;
			Clipboard::SetDataObject(dataObj, true);
			dataGridView1->ClearSelection();
			Color copyColor = Color::FromArgb( 183, 185, 255 );
			this->CopyAllButton->BackColor = copyColor;
		 }

private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
		 }

private: System::Void StationTable_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			 if (chldWndw&&(chldWndw!=nullptr))
				 chldWndw->ChildWindowClosing(Location.X, Location.Y);
		 }

private: System::Void StationTable_ResizeEnd(System::Object^  sender, System::EventArgs^  e) 
		 {
			Control^ control = dynamic_cast<Control^>(sender);
			if (chldWndw&&(chldWndw!=nullptr))
				chldWndw->ChildWindowResizeEnd(control->Size.Width, control->Size.Height);
		 }
};
}
