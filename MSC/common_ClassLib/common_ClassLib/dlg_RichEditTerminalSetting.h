#pragma once

namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for dlg_RichEditTerminalSetting
	/// </summary>
	public ref class dlg_RichEditTerminalSetting : public System::Windows::Forms::Form
	{
	public:
		dlg_RichEditTerminalSetting(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~dlg_RichEditTerminalSetting()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	protected: 
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::Button^  CancelButton;
	private: System::Windows::Forms::Button^  OKButton;
	private: System::Windows::Forms::DataGridView^  SyntaxColoringdataGridView;


	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Text2Highlight;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Color;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  WholeLine;

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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->OKButton = (gcnew System::Windows::Forms::Button());
			this->SyntaxColoringdataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->Text2Highlight = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Color = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->WholeLine = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabControl1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->SyntaxColoringdataGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(483, 232);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(475, 206);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"General";
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage2->Controls->Add(this->SyntaxColoringdataGridView);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(475, 206);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Syntax Coloring";
			// 
			// CancelButton
			// 
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Location = System::Drawing::Point(416, 259);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(75, 23);
			this->CancelButton->TabIndex = 5;
			this->CancelButton->Text = L"&Cancel";
			this->CancelButton->UseVisualStyleBackColor = true;
			// 
			// OKButton
			// 
			this->OKButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKButton->Location = System::Drawing::Point(307, 259);
			this->OKButton->Name = L"OKButton";
			this->OKButton->Size = System::Drawing::Size(75, 23);
			this->OKButton->TabIndex = 4;
			this->OKButton->Text = L"&OK";
			this->OKButton->UseVisualStyleBackColor = true;
			// 
			// SyntaxColoringdataGridView
			// 
			dataGridViewCellStyle5->BackColor = System::Drawing::Color::FloralWhite;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->SyntaxColoringdataGridView->AlternatingRowsDefaultCellStyle = dataGridViewCellStyle5;
			this->SyntaxColoringdataGridView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->SyntaxColoringdataGridView->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::DisplayedCells;
			this->SyntaxColoringdataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->SyntaxColoringdataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->Text2Highlight, 
				this->Color, this->WholeLine});
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle6->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle6->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle6->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->SyntaxColoringdataGridView->DefaultCellStyle = dataGridViewCellStyle6;
			this->SyntaxColoringdataGridView->Location = System::Drawing::Point(6, 6);
			this->SyntaxColoringdataGridView->Name = L"SyntaxColoringdataGridView";
			this->SyntaxColoringdataGridView->ReadOnly = true;
			this->SyntaxColoringdataGridView->RowHeadersWidth = 55;
			this->SyntaxColoringdataGridView->Size = System::Drawing::Size(387, 194);
			this->SyntaxColoringdataGridView->TabIndex = 49;
			// 
			// Text2Highlight
			// 
			this->Text2Highlight->HeaderText = L"Tex to Highlight";
			this->Text2Highlight->Name = L"Text2Highlight";
			this->Text2Highlight->ReadOnly = true;
			this->Text2Highlight->Width = 140;
			// 
			// Color
			// 
			this->Color->HeaderText = L"Color";
			this->Color->Name = L"Color";
			this->Color->ReadOnly = true;
			this->Color->Width = 60;
			// 
			// WholeLine
			// 
			this->WholeLine->HeaderText = L"Whole Line";
			this->WholeLine->Name = L"WholeLine";
			this->WholeLine->ReadOnly = true;
			// 
			// dlg_RichEditTerminalSetting
			// 
			this->AcceptButton = this->OKButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(507, 294);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->OKButton);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"dlg_RichEditTerminalSetting";
			this->Text = L"Terminal Setting";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &dlg_RichEditTerminalSetting::dlg_RichEditTerminalSetting_Load);
			this->tabControl1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->SyntaxColoringdataGridView))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void dlg_RichEditTerminalSetting_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
};
}
