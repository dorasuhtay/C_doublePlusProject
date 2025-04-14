#include "HangerTagClass.h"
#pragma once

namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for HangerTagTable
	/// </summary>
	public ref class HangerTagTable : public System::Windows::Forms::Form
	{
	public:
		HangerTagTable(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			HangerTag = 0;
		}

		void setObj(HangerTagClass *obj) {HangerTag = obj;}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~HangerTagTable()
		{
			if (components)
			{
				delete components;
			}
		}

	private: HangerTagClass	*HangerTag;
	private: bool pauseUpdate;
	private: Color pauseUpdateDefaultColor;
	private: System::Windows::Forms::Button^  PauseButton;


	protected: 
	private: System::Windows::Forms::DataGridView^  dataGridView1;











	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  HangerID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DesignCode;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Station;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  OPCODE;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Seq;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  EmpID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  NextStation;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  SeqNo;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  NextSeq;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dbgloc;
	private: System::Windows::Forms::Button^  CopyAllButton;
	private: System::Windows::Forms::Button^  ClearAllButton;
	private: System::Windows::Forms::Label^  label1;










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
			this->PauseButton = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->HangerID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DesignCode = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Station = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->OPCODE = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Seq = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->EmpID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->NextStation = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SeqNo = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->NextSeq = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dbgloc = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->CopyAllButton = (gcnew System::Windows::Forms::Button());
			this->ClearAllButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// PauseButton
			// 
			this->PauseButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->PauseButton->Location = System::Drawing::Point(754, 12);
			this->PauseButton->Name = L"PauseButton";
			this->PauseButton->Size = System::Drawing::Size(75, 23);
			this->PauseButton->TabIndex = 31;
			this->PauseButton->Text = L"Pause";
			this->PauseButton->UseVisualStyleBackColor = true;
			this->PauseButton->Click += gcnew System::EventHandler(this, &HangerTagTable::PauseButton_Click);
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
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(10) {this->HangerID, 
				this->DesignCode, this->Station, this->OPCODE, this->Seq, this->EmpID, this->NextStation, this->SeqNo, this->NextSeq, this->dbgloc});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->Location = System::Drawing::Point(2, 1);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 55;
			this->dataGridView1->Size = System::Drawing::Size(746, 523);
			this->dataGridView1->TabIndex = 30;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &HangerTagTable::dataGridView1_CellContentClick);
			// 
			// HangerID
			// 
			this->HangerID->HeaderText = L"HangerID";
			this->HangerID->Name = L"HangerID";
			// 
			// DesignCode
			// 
			this->DesignCode->HeaderText = L"DesignCode";
			this->DesignCode->Name = L"DesignCode";
			// 
			// Station
			// 
			this->Station->HeaderText = L"Station";
			this->Station->Name = L"Station";
			this->Station->Width = 50;
			// 
			// OPCODE
			// 
			this->OPCODE->HeaderText = L"OPCODE";
			this->OPCODE->Name = L"OPCODE";
			this->OPCODE->Width = 70;
			// 
			// Seq
			// 
			this->Seq->HeaderText = L"Seq";
			this->Seq->Name = L"Seq";
			this->Seq->Width = 50;
			// 
			// EmpID
			// 
			this->EmpID->HeaderText = L"EmpID";
			this->EmpID->Name = L"EmpID";
			// 
			// NextStation
			// 
			this->NextStation->HeaderText = L"NextStation";
			this->NextStation->Name = L"NextStation";
			this->NextStation->Width = 50;
			// 
			// SeqNo
			// 
			this->SeqNo->HeaderText = L"SeqNo";
			this->SeqNo->Name = L"SeqNo";
			this->SeqNo->Width = 50;
			// 
			// NextSeq
			// 
			this->NextSeq->HeaderText = L"NextSeq";
			this->NextSeq->Name = L"NextSeq";
			this->NextSeq->Width = 50;
			// 
			// dbgloc
			// 
			this->dbgloc->HeaderText = L"dbgloc";
			this->dbgloc->Name = L"dbgloc";
			this->dbgloc->Width = 50;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &HangerTagTable::timer1_Tick);
			// 
			// CopyAllButton
			// 
			this->CopyAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->CopyAllButton->Location = System::Drawing::Point(754, 129);
			this->CopyAllButton->Name = L"CopyAllButton";
			this->CopyAllButton->Size = System::Drawing::Size(75, 23);
			this->CopyAllButton->TabIndex = 32;
			this->CopyAllButton->Text = L"Copy &All";
			this->CopyAllButton->UseVisualStyleBackColor = true;
			this->CopyAllButton->Click += gcnew System::EventHandler(this, &HangerTagTable::CopyAllButton_Click);
			// 
			// ClearAllButton
			// 
			this->ClearAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ClearAllButton->Location = System::Drawing::Point(754, 54);
			this->ClearAllButton->Name = L"ClearAllButton";
			this->ClearAllButton->Size = System::Drawing::Size(75, 23);
			this->ClearAllButton->TabIndex = 33;
			this->ClearAllButton->Text = L"Clear &All";
			this->ClearAllButton->UseVisualStyleBackColor = true;
			this->ClearAllButton->Click += gcnew System::EventHandler(this, &HangerTagTable::ClearAllButton_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(754, 114);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 12);
			this->label1->TabIndex = 34;
			this->label1->Text = L"Copy to Clipboard";
			this->label1->Click += gcnew System::EventHandler(this, &HangerTagTable::label1_Click);
			// 
			// HangerTagTable
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(837, 518);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ClearAllButton);
			this->Controls->Add(this->CopyAllButton);
			this->Controls->Add(this->PauseButton);
			this->Controls->Add(this->dataGridView1);
			this->Name = L"HangerTagTable";
			this->Text = L"HangerTagTable";
			this->Load += gcnew System::EventHandler(this, &HangerTagTable::HangerTagTable_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void dataGridView1_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 }
	private: System::Void HangerTagTable_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			 	FillTable();
				timer1->Start();
				timer1->Enabled = true;
				pauseUpdateDefaultColor = this->PauseButton->BackColor;

					


		 }

	private: System::Void FillTable()
			 {
				 if (HangerTag)
				 {
					 dataGridView1->Rows->Clear();
					 int ii;
					 //stationParameterType sPara;

					 /*
					         // Add columns to the DataGridView.
        dataGridView1.ColumnCount = 3;

        // Set the properties of the DataGridView columns.
        dataGridView1.Columns[0].Name = "ID";
        dataGridView1.Columns[1].Name = "Name";
        dataGridView1.Columns[2].Name = "City";
        dataGridView1.Columns["ID"].HeaderText = "ID";
        dataGridView1.Columns["Name"].HeaderText = "Name";
        dataGridView1.Columns["City"].HeaderText = "City";

        // Add rows of data to the DataGridView.
        dataGridView1.Rows.Add(new string[] { "1", "Parker", "Seattle" });
        dataGridView1.Rows.Add(new string[] { "2", "Parker", "New York" });
        dataGridView1.Rows.Add(new string[] { "3", "Watson", "Seattle" });
        dataGridView1.Rows.Add(new string[] { "4", "Jameson", "New Jersey" });
        dataGridView1.Rows.Add(new string[] { "5", "Brock", "New York" });
        dataGridView1.Rows.Add(new string[] { "6", "Conner", "Portland" });

        // Autosize the columns.
        dataGridView1.AutoResizeColumns();

					 */
					 for (ii=0;ii<HangerTag->getcount();ii++)
					 {
						 //if (OverheadPusher->get(ii, &sPara))
						 {/*
							 //String ^STNID = gcnew String(reinterpret_cast<wchar_t*>(sPara.stnID));
							 String ^HangerID = OverheadPusher->getHangerID(ii);
							 String ^Src = gcnew String(reinterpret_cast<wchar_t*>(OverheadPusher->getHangerSrcStation(ii)));
							 String ^dest = gcnew String(reinterpret_cast<wchar_t*>(OverheadPusher->getHangerDestStation(ii)));
							 */
							 /*
							 debugMsgtextBox->Text += ii.ToString() + "\t" + 
													STNID + "\t" + 
													sPara.infeed.ToString() + "\t" + 
													sPara.infeedoffset.ToString() + "\t" + 
													sPara.outfeed.ToString() + "\t" + 
													sPara.outfeedoffset.ToString() + "\t" + 
													PRODLINE + "\r\n";
*/
							 dataGridView1->Rows->Add(	
														HangerTag->getHangerID(ii), 
														HangerTag->getDesignCode(ii),
														HangerTag->getHangerSTNID(ii),
														HangerTag->getHangerOPCODE(ii),
														HangerTag->getBundlSeqSeqNo(ii),
														HangerTag->getHangerEmpId(ii),
														HangerTag->getNextStation(ii),
														HangerTag->getSeqNo(ii).ToString(),
														HangerTag->getNextSeqNo(ii).ToString(),
														HangerTag->getdbgloc(ii)
														);




						 }				
					 }
					 int row;
					 for (ii=0;ii<HangerTag->getcount();ii++)
					 {
						row = ii+1;
						dataGridView1->Rows[ii]->HeaderCell->Value = row.ToString();
					 }
				 }
			 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if (!pauseUpdate)
				FillTable();
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




private: System::Void CopyAllButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			dataGridView1->SelectAll();
			DataObject ^dataObj = dataGridView1->GetClipboardContent();
//			Clipboard ^clipb;
//			clipb->SetDataObject(dataObj, true);
			Clipboard::SetDataObject(dataObj, true);
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
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};



}
