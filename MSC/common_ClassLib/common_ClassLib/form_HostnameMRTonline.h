#include "class_HostnameMRTonline.h"
#include "stringconversion.h"
#pragma once

namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for form_HostnameMRTonline
	/// </summary>
	public ref class form_HostnameMRTonline : public System::Windows::Forms::Form
	{
	public:
		form_HostnameMRTonline(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			objectList = 0;
			update_rate = 0;
			update_rate_counter = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~form_HostnameMRTonline()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  Update_rateTextBox;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  PauseButton;
	private: System::Windows::Forms::DataGridView^  dataGridView1;















	private: System::Windows::Forms::Timer^  timer100ms;

	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
	public: class_HostnameMRTonline	*objectList;
	private: int update_rate;
	private: int update_rate_counter;
	private: bool pauseUpdate;







	private: System::Windows::Forms::Label^  RemarksTitlelabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nameLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Line;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  AddressLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Status;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Database;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LoginName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Password;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Remarks;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ServerPort;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Mail;





































	private: Color pauseUpdateDefaultColor;








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
			this->Update_rateTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->PauseButton = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->nameLabel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Line = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->AddressLabel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Status = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Database = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LoginName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Password = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Remarks = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ServerPort = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Mail = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->timer100ms = (gcnew System::Windows::Forms::Timer(this->components));
			this->RemarksTitlelabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// Update_rateTextBox
			// 
			this->Update_rateTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Update_rateTextBox->Location = System::Drawing::Point(888, 45);
			this->Update_rateTextBox->Name = L"Update_rateTextBox";
			this->Update_rateTextBox->Size = System::Drawing::Size(73, 20);
			this->Update_rateTextBox->TabIndex = 51;
			this->Update_rateTextBox->TextChanged += gcnew System::EventHandler(this, &form_HostnameMRTonline::Update_rateTextBox_TextChanged);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(887, 30);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 12);
			this->label2->TabIndex = 50;
			this->label2->Text = L"Update rate (sec)";
			// 
			// PauseButton
			// 
			this->PauseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->PauseButton->Location = System::Drawing::Point(888, 71);
			this->PauseButton->Name = L"PauseButton";
			this->PauseButton->Size = System::Drawing::Size(75, 23);
			this->PauseButton->TabIndex = 49;
			this->PauseButton->Text = L"Pause";
			this->PauseButton->UseVisualStyleBackColor = true;
			this->PauseButton->Click += gcnew System::EventHandler(this, &form_HostnameMRTonline::PauseButton_Click);
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
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(10) {this->nameLabel, 
				this->Line, this->AddressLabel, this->Status, this->Database, this->LoginName, this->Password, this->Remarks, this->ServerPort, 
				this->Mail});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->Location = System::Drawing::Point(4, 30);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersWidth = 55;
			this->dataGridView1->Size = System::Drawing::Size(878, 261);
			this->dataGridView1->TabIndex = 48;
			// 
			// nameLabel
			// 
			this->nameLabel->HeaderText = L"Host Name (Alias)";
			this->nameLabel->Name = L"nameLabel";
			this->nameLabel->ReadOnly = true;
			this->nameLabel->Width = 140;
			// 
			// Line
			// 
			this->Line->HeaderText = L"Line";
			this->Line->Name = L"Line";
			this->Line->ReadOnly = true;
			this->Line->Width = 60;
			// 
			// AddressLabel
			// 
			this->AddressLabel->HeaderText = L"Address";
			this->AddressLabel->Name = L"AddressLabel";
			this->AddressLabel->ReadOnly = true;
			// 
			// Status
			// 
			this->Status->HeaderText = L"Status";
			this->Status->Name = L"Status";
			this->Status->ReadOnly = true;
			// 
			// Database
			// 
			this->Database->HeaderText = L"Database";
			this->Database->Name = L"Database";
			this->Database->ReadOnly = true;
			this->Database->Width = 120;
			// 
			// LoginName
			// 
			this->LoginName->HeaderText = L"Login Name";
			this->LoginName->Name = L"LoginName";
			this->LoginName->ReadOnly = true;
			// 
			// Password
			// 
			this->Password->HeaderText = L"Password";
			this->Password->Name = L"Password";
			this->Password->ReadOnly = true;
			this->Password->Width = 80;
			// 
			// Remarks
			// 
			this->Remarks->HeaderText = L"Remarks";
			this->Remarks->Name = L"Remarks";
			this->Remarks->ReadOnly = true;
			this->Remarks->ToolTipText = L"Common Name";
			this->Remarks->Width = 160;
			// 
			// ServerPort
			// 
			this->ServerPort->HeaderText = L"Server Port";
			this->ServerPort->Name = L"ServerPort";
			this->ServerPort->ReadOnly = true;
			// 
			// Mail
			// 
			this->Mail->HeaderText = L"Mail";
			this->Mail->Name = L"Mail";
			this->Mail->ReadOnly = true;
			this->Mail->Width = 40;
			// 
			// timer100ms
			// 
			this->timer100ms->Tick += gcnew System::EventHandler(this, &form_HostnameMRTonline::timer1_Tick);
			// 
			// RemarksTitlelabel
			// 
			this->RemarksTitlelabel->AutoSize = true;
			this->RemarksTitlelabel->Location = System::Drawing::Point(13, 11);
			this->RemarksTitlelabel->Name = L"RemarksTitlelabel";
			this->RemarksTitlelabel->Size = System::Drawing::Size(35, 13);
			this->RemarksTitlelabel->TabIndex = 52;
			this->RemarksTitlelabel->Text = L"label1";
			// 
			// form_HostnameMRTonline
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(973, 303);
			this->Controls->Add(this->RemarksTitlelabel);
			this->Controls->Add(this->Update_rateTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"form_HostnameMRTonline";
			this->Text = L"form_HostnameMRTonline";
			this->Load += gcnew System::EventHandler(this, &form_HostnameMRTonline::form_HostnameMRTonline_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void form_HostnameMRTonline_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				RemarksTitlelabel->Text = "Hostname Table:" + gcnew String(reinterpret_cast<const wchar_t *>(objectList->getIPaddress()));
				this->PauseButton->Enabled = false;
				FillTable();
				timer100ms->Start();
				timer100ms->Enabled = true;
				pauseUpdateDefaultColor = this->PauseButton->BackColor;
				int rate = update_rate*100;
				Update_rateTextBox->Text = rate.ToString();
			 }

	private: Void FillTable()
			 {
				 if (!objectList) return;

					 dataGridView1->Rows->Clear();
					 int ii;
					 for (ii=0;ii<objectList->getcount();ii++)
					 {
						 dataGridView1->Rows->Add(	objectList->getName(ii),
													objectList->getProdline(ii).ToString(),
													objectList->getIpaddress(ii),
													objectList->getconnectionstatus(ii),
													objectList->getdbname(ii), 
													objectList->getloginname(ii),
													objectList->getloginpassword(ii),
													objectList->getremarks(ii),
													objectList->getlineserverPortnumber(ii),
													objectList->mailAvailable(ii).ToString()
													);
					 }
					 int row;
					 for (ii=0;ii<objectList->getcount();ii++)
					 {
						row = ii+1;
						dataGridView1->Rows[ii]->HeaderCell->Value = row.ToString();
					 }
			}

	private: Void UpdateTable()
			 {
				if (!objectList) return;
				int ii, col;
				String ^value;
				try
				{
					for (ii=0;ii<objectList->getcount();ii++)
					{
						//class_TCPsocket ^sock = socklist->get(ii);
						Color prevcolor = dataGridView1->Rows[ii]->Cells[0]->Style->BackColor;
						for(col=0;col<dataGridView1->ColumnCount;col++)
						{
							switch(col)
							{
							case	0:  value = objectList->getName(ii); break;
							case	1:  value = objectList->getProdline(ii).ToString(); break;
							case	2:  value = objectList->getIpaddress(ii); break;
							case	3:  value = objectList->getconnectionstatus(ii); break;
							case	4:  value = objectList->getdbname(ii); break;
							case	5:  value = objectList->getloginname(ii); break;
							case	6:  value = objectList->getloginpassword(ii); break;
							case	7:  value = objectList->getremarks(ii); break;
							case	8:  value = objectList->getlineserverPortnumber(ii).ToString(); break;
							case	9:  value = objectList->mailAvailable(ii).ToString(); break;
							
/*
							case	1:  value = sock->getipaddress(); break;
							case	2:  value = sock->getport().ToString(); break;
							case	3:  if (sock->getstate()==tcpSocket_CONNECTED)
											dataGridView1->Rows[ii]->Cells[col]->Style->BackColor = Color::FromArgb( 225, 255, 213 );
										else
											dataGridView1->Rows[ii]->Cells[col]->Style->BackColor = prevcolor;
										value = sock->getstateStr(); 
										break;
							case	4:  value = sock->getSocketTypeStr(); break;
							case	5:  value = sock->index.ToString(); break;
							*/
							default:	value = ""; break;
							}
							dataGridView1->Rows[ii]->Cells[col]->Value = value;
						}	
					}
				}
				catch (...)
				{
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
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (!pauseUpdate)
			 {
				 if (update_rate>0)
				 {
					if ((update_rate_counter%update_rate)==0)
						UpdateTable();
					update_rate_counter++;
				 }
			 }
		 }
private: System::Void Update_rateTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) 
		 {
			 update_rate = convertToInt32(Update_rateTextBox->Text);
			update_rate = update_rate/100;
			update_rate_counter = 0;
			if (update_rate>0)
				this->PauseButton->Enabled = true;
			else
				this->PauseButton->Enabled = false;
		 }




};
}
