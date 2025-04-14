#include "class_TCPsocketList.h"
#pragma once

namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for form_TCPsocketStatus
	/// </summary>
	public ref class form_TCPsocketStatus : public System::Windows::Forms::Form
	{
	public:
		form_TCPsocketStatus(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			socklist = nullptr;
			update_rate = 10;
			update_rate_counter = 0;
		}

	public: 














	private: System::Windows::Forms::TextBox^  Update_rateTextBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  PauseButton;
	private: System::Windows::Forms::Timer^  timer100ms;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nameLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  AddressLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Portnumber;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ConnectionStateLabel;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  SocketType;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LoadingStation;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  LogIn;































	private: System::Windows::Forms::DataGridView^  dataGridView1;

















	

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~form_TCPsocketStatus()
		{
			if (components)
			{
				delete components;
			}
		}
	public: class_TCPsocketList	^socklist;
	private: System::ComponentModel::IContainer^  components;
	public: 
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
	private: int update_rate;
	private: int update_rate_counter;
	private: bool pauseUpdate;
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
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->nameLabel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->AddressLabel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Portnumber = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ConnectionStateLabel = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SocketType = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LoadingStation = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->LogIn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Update_rateTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->PauseButton = (gcnew System::Windows::Forms::Button());
			this->timer100ms = (gcnew System::Windows::Forms::Timer(this->components));
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
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(7) {this->nameLabel, 
				this->AddressLabel, this->Portnumber, this->ConnectionStateLabel, this->SocketType, this->LoadingStation, this->LogIn});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->Location = System::Drawing::Point(3, 31);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 55;
			this->dataGridView1->Size = System::Drawing::Size(652, 238);
			this->dataGridView1->TabIndex = 44;
			// 
			// nameLabel
			// 
			this->nameLabel->HeaderText = L"Name";
			this->nameLabel->Name = L"nameLabel";
			this->nameLabel->Width = 140;
			// 
			// AddressLabel
			// 
			this->AddressLabel->HeaderText = L"Address";
			this->AddressLabel->Name = L"AddressLabel";
			// 
			// Portnumber
			// 
			this->Portnumber->HeaderText = L"Port";
			this->Portnumber->Name = L"Portnumber";
			this->Portnumber->Width = 70;
			// 
			// ConnectionStateLabel
			// 
			this->ConnectionStateLabel->HeaderText = L"Connection State";
			this->ConnectionStateLabel->Name = L"ConnectionStateLabel";
			// 
			// SocketType
			// 
			this->SocketType->HeaderText = L"Socket Type";
			this->SocketType->Name = L"SocketType";
			this->SocketType->Width = 80;
			// 
			// LoadingStation
			// 
			this->LoadingStation->HeaderText = L"Number";
			this->LoadingStation->Name = L"LoadingStation";
			this->LoadingStation->ToolTipText = L"Number";
			this->LoadingStation->Width = 50;
			// 
			// LogIn
			// 
			this->LogIn->HeaderText = L"Log In";
			this->LogIn->Name = L"LogIn";
			this->LogIn->Width = 30;
			// 
			// Update_rateTextBox
			// 
			this->Update_rateTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Update_rateTextBox->Location = System::Drawing::Point(662, 46);
			this->Update_rateTextBox->Name = L"Update_rateTextBox";
			this->Update_rateTextBox->Size = System::Drawing::Size(73, 20);
			this->Update_rateTextBox->TabIndex = 47;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(661, 31);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 12);
			this->label2->TabIndex = 46;
			this->label2->Text = L"Update rate (sec)";
			// 
			// PauseButton
			// 
			this->PauseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->PauseButton->Location = System::Drawing::Point(662, 72);
			this->PauseButton->Name = L"PauseButton";
			this->PauseButton->Size = System::Drawing::Size(75, 23);
			this->PauseButton->TabIndex = 45;
			this->PauseButton->Text = L"Pause";
			this->PauseButton->UseVisualStyleBackColor = true;
			this->PauseButton->Click += gcnew System::EventHandler(this, &form_TCPsocketStatus::PauseButton_Click);
			// 
			// timer100ms
			// 
			this->timer100ms->Tick += gcnew System::EventHandler(this, &form_TCPsocketStatus::timer100ms_Tick);
			// 
			// form_TCPsocketStatus
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(746, 294);
			this->Controls->Add(this->Update_rateTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"form_TCPsocketStatus";
			this->Text = L"form_TCPsocketStatus";
			this->Load += gcnew System::EventHandler(this, &form_TCPsocketStatus::form_TCPsocketStatus_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void form_TCPsocketStatus_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 FillTable();
				 timer100ms->Start();
				timer100ms->Enabled = true;
				pauseUpdateDefaultColor = this->PauseButton->BackColor;
				int rate = update_rate*100;
				Update_rateTextBox->Text = rate.ToString();
			 }

	private: Void FillTable()
			 {
				 if (socklist==nullptr) return;

					 dataGridView1->Rows->Clear();
					 int ii;
					 for (ii=0;ii<socklist->getcount();ii++)
					 {
						 class_TCPsocket ^sock = socklist->get(ii);
						 dataGridView1->Rows->Add(	sock->Name,
													sock->getipaddress(),
													sock->getport().ToString(), 
													sock->getstateStr(),
													sock->getSocketTypeStr(),
													sock->index.ToString()
													);
						 				
					 }
					 int row;
					 for (ii=0;ii<socklist->getcount();ii++)
					 {
						row = ii+1;
						dataGridView1->Rows[ii]->HeaderCell->Value = row.ToString();
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


private: System::Void timer100ms_Tick(System::Object^  sender, System::EventArgs^  e) 
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



	private: Void UpdateTable()
			 {
				if (socklist==nullptr) return;
				int ii, col;
				String ^value;
				try
				{
					for (ii=0;ii<socklist->getcount();ii++)
					{
						class_TCPsocket ^sock = socklist->get(ii);
						Color prevcolor = dataGridView1->Rows[ii]->Cells[0]->Style->BackColor;
						for(col=0;col<dataGridView1->ColumnCount;col++)
						{
							switch(col)
							{
							case	0:  value = sock->Name; break;
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

};





}
