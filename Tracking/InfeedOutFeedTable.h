#include <TCHAR.H>
#include <STRING.H>
#include <vcclr.h>
#include "stationSettingClass.h"
#include "stringconversion.h"
#include "SQL_appfunc.h"
#include "GlobalVariables.h"
#pragma once

namespace BTREKCANDAEMONV1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for InfeedOutFeedTable
	/// </summary>
	public ref class InfeedOutFeedTable : public System::Windows::Forms::Form
	{
	public:
		InfeedOutFeedTable(class_SQLfunc ^sql)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			stationSetting = 0;
			dirty = 0;
			StatusLabeltimeout = -1;
			counter_tick = 0;
			this->sqlfunc = sql;
		}
		
		void setstationSetting(stationSettingClass *stnSetting){stationSetting = stnSetting;}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~InfeedOutFeedTable()
		{
			if (components)
			{
				delete components;
			}
		}

	private: stationSettingClass *stationSetting;
	private: int dirty;
	private: int currentRowIndex;
			 int currentColIndex;
			 int StatusLabeltimeout;
			 int counter_tick;
			 class_SQLfunc ^sqlfunc;

	private: System::Windows::Forms::DataGridView^  dataGridView1;






	private: System::Windows::Forms::Button^  RefreshButton;
	private: System::Windows::Forms::Button^  SaveButton;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  STNID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  InFeed;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  InFeedOffset;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  OutFeed;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  OutFeedOffset;








	private: System::Windows::Forms::ToolStripMenuItem^  contentsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  indexToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  searchToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  customizeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  undoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  redoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  cutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pasteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::ToolStripMenuItem^  selectAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  printToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  printPreviewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip_Popup1;
	private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  pasteToolStripMenuItem1;


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  CopyAllButton;
	private: System::Windows::Forms::Button^  ExportToCSVbutton;
	private: System::Windows::Forms::Button^  ImportfromCSVbutton;
	private: System::Windows::Forms::Label^  Statuslabel;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  ProdLinelabel;



































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
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->STNID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->InFeed = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->InFeedOffset = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->OutFeed = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->OutFeedOffset = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->RefreshButton = (gcnew System::Windows::Forms::Button());
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->contentsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->indexToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->searchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->customizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->cutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pasteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->selectAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->printToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->printPreviewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip_Popup1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->copyToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pasteToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->CopyAllButton = (gcnew System::Windows::Forms::Button());
			this->ExportToCSVbutton = (gcnew System::Windows::Forms::Button());
			this->ImportfromCSVbutton = (gcnew System::Windows::Forms::Button());
			this->Statuslabel = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->ProdLinelabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->contextMenuStrip_Popup1->SuspendLayout();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->STNID, 
				this->InFeed, this->InFeedOffset, this->OutFeed, this->OutFeedOffset});
			this->dataGridView1->Location = System::Drawing::Point(12, 22);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 55;
			this->dataGridView1->Size = System::Drawing::Size(333, 397);
			this->dataGridView1->TabIndex = 27;
			this->dataGridView1->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &InfeedOutFeedTable::OnCellValueChanged);
			this->dataGridView1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &InfeedOutFeedTable::OnMouseClick);
			// 
			// STNID
			// 
			this->STNID->HeaderText = L"Station";
			this->STNID->Name = L"STNID";
			this->STNID->Width = 50;
			// 
			// InFeed
			// 
			this->InFeed->HeaderText = L"InFeed";
			this->InFeed->Name = L"InFeed";
			this->InFeed->Width = 50;
			// 
			// InFeedOffset
			// 
			this->InFeedOffset->HeaderText = L"InFeed Offset";
			this->InFeedOffset->Name = L"InFeedOffset";
			this->InFeedOffset->Width = 50;
			// 
			// OutFeed
			// 
			this->OutFeed->HeaderText = L"OutFeed";
			this->OutFeed->Name = L"OutFeed";
			this->OutFeed->Width = 50;
			// 
			// OutFeedOffset
			// 
			this->OutFeedOffset->HeaderText = L"OutFeed Offset";
			this->OutFeedOffset->Name = L"OutFeedOffset";
			this->OutFeedOffset->Width = 50;
			// 
			// RefreshButton
			// 
			this->RefreshButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->RefreshButton->Location = System::Drawing::Point(351, 22);
			this->RefreshButton->Name = L"RefreshButton";
			this->RefreshButton->Size = System::Drawing::Size(75, 23);
			this->RefreshButton->TabIndex = 28;
			this->RefreshButton->Text = L"&Refresh";
			this->RefreshButton->UseVisualStyleBackColor = true;
			// 
			// SaveButton
			// 
			this->SaveButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->SaveButton->Location = System::Drawing::Point(351, 53);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(75, 23);
			this->SaveButton->TabIndex = 29;
			this->SaveButton->Text = L"&Save";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &InfeedOutFeedTable::SaveButton_Click);
			// 
			// contentsToolStripMenuItem
			// 
			this->contentsToolStripMenuItem->Name = L"contentsToolStripMenuItem";
			this->contentsToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->contentsToolStripMenuItem->Text = L"&Contents";
			// 
			// indexToolStripMenuItem
			// 
			this->indexToolStripMenuItem->Name = L"indexToolStripMenuItem";
			this->indexToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->indexToolStripMenuItem->Text = L"&Index";
			// 
			// searchToolStripMenuItem
			// 
			this->searchToolStripMenuItem->Name = L"searchToolStripMenuItem";
			this->searchToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->searchToolStripMenuItem->Text = L"&Search";
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(119, 6);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(122, 22);
			this->aboutToolStripMenuItem->Text = L"&About...";
			// 
			// customizeToolStripMenuItem
			// 
			this->customizeToolStripMenuItem->Name = L"customizeToolStripMenuItem";
			this->customizeToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->customizeToolStripMenuItem->Text = L"&Customize";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->optionsToolStripMenuItem->Text = L"&Options";
			// 
			// undoToolStripMenuItem
			// 
			this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
			this->undoToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
			this->undoToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->undoToolStripMenuItem->Text = L"&Undo";
			// 
			// redoToolStripMenuItem
			// 
			this->redoToolStripMenuItem->Name = L"redoToolStripMenuItem";
			this->redoToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Y));
			this->redoToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->redoToolStripMenuItem->Text = L"&Redo";
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(141, 6);
			// 
			// cutToolStripMenuItem
			// 
			this->cutToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cutToolStripMenuItem->Name = L"cutToolStripMenuItem";
			this->cutToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
			this->cutToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->cutToolStripMenuItem->Text = L"Cu&t";
			// 
			// copyToolStripMenuItem
			// 
			this->copyToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
			this->copyToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
			this->copyToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->copyToolStripMenuItem->Text = L"&Copy";
			// 
			// pasteToolStripMenuItem
			// 
			this->pasteToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->pasteToolStripMenuItem->Name = L"pasteToolStripMenuItem";
			this->pasteToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::V));
			this->pasteToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->pasteToolStripMenuItem->Text = L"&Paste";
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(141, 6);
			// 
			// selectAllToolStripMenuItem
			// 
			this->selectAllToolStripMenuItem->Name = L"selectAllToolStripMenuItem";
			this->selectAllToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->selectAllToolStripMenuItem->Text = L"Select &All";
			// 
			// newToolStripMenuItem
			// 
			this->newToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->newToolStripMenuItem->Name = L"newToolStripMenuItem";
			this->newToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->newToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->newToolStripMenuItem->Text = L"&New";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->openToolStripMenuItem->Text = L"&Open";
			// 
			// toolStripSeparator
			// 
			this->toolStripSeparator->Name = L"toolStripSeparator";
			this->toolStripSeparator->Size = System::Drawing::Size(143, 6);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->saveToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->saveToolStripMenuItem->Text = L"&Save";
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->saveAsToolStripMenuItem->Text = L"Save &As";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(143, 6);
			// 
			// printToolStripMenuItem
			// 
			this->printToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->printToolStripMenuItem->Name = L"printToolStripMenuItem";
			this->printToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
			this->printToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->printToolStripMenuItem->Text = L"&Print";
			// 
			// printPreviewToolStripMenuItem
			// 
			this->printPreviewToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->printPreviewToolStripMenuItem->Name = L"printPreviewToolStripMenuItem";
			this->printPreviewToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->printPreviewToolStripMenuItem->Text = L"Print Pre&view";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(143, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->exitToolStripMenuItem->Text = L"E&xit";
			// 
			// contextMenuStrip_Popup1
			// 
			this->contextMenuStrip_Popup1->AccessibleRole = System::Windows::Forms::AccessibleRole::MenuBar;
			this->contextMenuStrip_Popup1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->copyToolStripMenuItem1, 
				this->pasteToolStripMenuItem1});
			this->contextMenuStrip_Popup1->Name = L"contextMenuStrip_Popup1";
			this->contextMenuStrip_Popup1->Size = System::Drawing::Size(103, 48);
			// 
			// copyToolStripMenuItem1
			// 
			this->copyToolStripMenuItem1->Name = L"copyToolStripMenuItem1";
			this->copyToolStripMenuItem1->Size = System::Drawing::Size(133, 22);
			this->copyToolStripMenuItem1->Text = L"&Copy";
			this->copyToolStripMenuItem1->Click += gcnew System::EventHandler(this, &InfeedOutFeedTable::copyToolStripMenuItem1_Click);
			// 
			// pasteToolStripMenuItem1
			// 
			this->pasteToolStripMenuItem1->Name = L"pasteToolStripMenuItem1";
			this->pasteToolStripMenuItem1->Size = System::Drawing::Size(133, 22);
			this->pasteToolStripMenuItem1->Text = L"&Paste";
			this->pasteToolStripMenuItem1->Click += gcnew System::EventHandler(this, &InfeedOutFeedTable::pasteToolStripMenuItem1_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(351, 156);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 12);
			this->label1->TabIndex = 36;
			this->label1->Text = L"Copy to Clipboard";
			// 
			// CopyAllButton
			// 
			this->CopyAllButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->CopyAllButton->Location = System::Drawing::Point(351, 171);
			this->CopyAllButton->Name = L"CopyAllButton";
			this->CopyAllButton->Size = System::Drawing::Size(75, 23);
			this->CopyAllButton->TabIndex = 35;
			this->CopyAllButton->Text = L"Copy &All";
			this->CopyAllButton->UseVisualStyleBackColor = true;
			this->CopyAllButton->Click += gcnew System::EventHandler(this, &InfeedOutFeedTable::CopyAllButton_Click);
			// 
			// ExportToCSVbutton
			// 
			this->ExportToCSVbutton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ExportToCSVbutton->Location = System::Drawing::Point(351, 218);
			this->ExportToCSVbutton->Name = L"ExportToCSVbutton";
			this->ExportToCSVbutton->Size = System::Drawing::Size(75, 37);
			this->ExportToCSVbutton->TabIndex = 37;
			this->ExportToCSVbutton->Text = L"&Export to CSV";
			this->ExportToCSVbutton->UseVisualStyleBackColor = true;
			this->ExportToCSVbutton->Click += gcnew System::EventHandler(this, &InfeedOutFeedTable::ExportToCSVbutton_Click);
			// 
			// ImportfromCSVbutton
			// 
			this->ImportfromCSVbutton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ImportfromCSVbutton->Location = System::Drawing::Point(351, 261);
			this->ImportfromCSVbutton->Name = L"ImportfromCSVbutton";
			this->ImportfromCSVbutton->Size = System::Drawing::Size(75, 37);
			this->ImportfromCSVbutton->TabIndex = 38;
			this->ImportfromCSVbutton->Text = L"&Import from CSV";
			this->ImportfromCSVbutton->UseVisualStyleBackColor = true;
			this->ImportfromCSVbutton->Click += gcnew System::EventHandler(this, &InfeedOutFeedTable::ImportfromCSVbutton_Click);
			// 
			// Statuslabel
			// 
			this->Statuslabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Statuslabel->AutoSize = true;
			this->Statuslabel->Location = System::Drawing::Point(12, 422);
			this->Statuslabel->Name = L"Statuslabel";
			this->Statuslabel->Size = System::Drawing::Size(40, 13);
			this->Statuslabel->TabIndex = 39;
			this->Statuslabel->Text = L"Status:";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &InfeedOutFeedTable::timer1_Tick);
			// 
			// ProdLinelabel
			// 
			this->ProdLinelabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->ProdLinelabel->AutoSize = true;
			this->ProdLinelabel->Location = System::Drawing::Point(9, 6);
			this->ProdLinelabel->Name = L"ProdLinelabel";
			this->ProdLinelabel->Size = System::Drawing::Size(84, 13);
			this->ProdLinelabel->TabIndex = 40;
			this->ProdLinelabel->Text = L"Production Line:";
			// 
			// InfeedOutFeedTable
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(436, 444);
			this->Controls->Add(this->ProdLinelabel);
			this->Controls->Add(this->ExportToCSVbutton);
			this->Controls->Add(this->ImportfromCSVbutton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->CopyAllButton);
			this->Controls->Add(this->Statuslabel);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->RefreshButton);
			this->Name = L"InfeedOutFeedTable";
			this->Text = L"InfeedOutFeedTable";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &InfeedOutFeedTable::InfeedOutFeedTable_FormClosing);
			this->Load += gcnew System::EventHandler(this, &InfeedOutFeedTable::InfeedOutFeedTable_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->contextMenuStrip_Popup1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: Void FillTable()
			 {
				 dataGridView1->Rows->Clear();
				 currentRowIndex = -1;
				 currentColIndex = -1;
				 if (stationSetting)
				 {
					 int ii;
					 stationParameterType sPara;
					 for (ii=1;ii<stationSetting->getcount();ii++)
					 {
						 if (stationSetting->get(ii, &sPara))
						 {
							 String ^STNID = gcnew String(reinterpret_cast<wchar_t*>(sPara.stnID));
							 //String ^PRODLINE = gcnew String(reinterpret_cast<wchar_t*>(sPara.prodlineID));
							 dataGridView1->Rows->Add(	STNID, 
														sPara.infeed.ToString(), 
														sPara.infeedoffset.ToString(),
														sPara.outfeed.ToString(),
														sPara.outfeedoffset.ToString()
														);
						 }				
					 }
					 int row;
					 //int ccount = stationSetting->getcount();
					 for (ii=0;ii<stationSetting->getcount();ii++)
					 {
						row = ii+1;
						dataGridView1->Rows[ii]->HeaderCell->Value = row.ToString();
					 }

				 }				
			 }

	private: System::Void InfeedOutFeedTable_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				ProdLinelabel->Text = "Production Line:"+gcnew String(reinterpret_cast<const wchar_t*>(stationSetting->getprodline()));
				FillTable();
				SaveButton->Enabled = false;
				timer1->Enabled = true;
				timer1->Start();
			 }

	private: Void SaveToSQL()
			 {
				int result = writeToPUSHERTIMEdb(sqlfunc, stationSetting);
				if (result<0)
				{
					String ^msg = "ERROR: Saving to Database, error[" + result.ToString() + "]";
					MessageBox::Show(this, msg, Text, MessageBoxButtons::OK,
					MessageBoxIcon::Error, MessageBoxDefaultButton::Button1);	
				}
			 }

	private: System::Void SaveButton_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				if(!stationSetting) 
					return;
				int row, col;
				stationParameterType sPara;
				stationSetting->deleteAll();
				memset(&sPara,0x0,sizeof(stationParameterType));
				stationSetting->add(&sPara);
				 for (row=0;row<dataGridView1->RowCount-1;row++)
				 {
					 memset(&sPara, 0x0, sizeof(stationParameterType));
					 //_tcscpy(sPara.prodlineID, L"1");
					 for (col=0;col<dataGridView1->ColumnCount;col++)
					 {
						dataGridView1->Rows[row]->Cells[col];

						String ^valueStr = dataGridView1->Rows[row]->Cells[col]->Value->ToString();
						switch(col)
						{
							case	0:
									{
										pin_ptr<const wchar_t> wch = PtrToStringChars(valueStr);
										_tcsncpy(sPara.stnID, wch, sizeof(sPara.stnID));
										sPara.stnID[sizeof(sPara.stnID)] = 0x0;
									}
									break;
							case	1:	sPara.infeed = convertToInt32(valueStr);break;
							case	2:	sPara.infeedoffset = convertToInt32(valueStr);break;
							case	3:	sPara.outfeed = convertToInt32(valueStr);break;				
							case	4:	sPara.outfeedoffset = convertToInt32(valueStr);break;
						}
					 }
					 stationSetting->add(&sPara);
				 }

//				if(stationSetting)
//					stationSetting->writeDat();
				SaveToSQL();

				WriteStatusBar("Saved to Data Base", Color::FromArgb( 188, 84, 14 ), 2);

				SaveButton->Enabled = false;
				dirty=0;
			 }

	private: System::Void OnCellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) 
		 {
			 if (e->RowIndex<0) return;
			 if (e->ColumnIndex<0) return;

			 dirty++;
			 SaveButton->Enabled = true;

			 /*
			 //String^ recipeName = dynamic_cast<String^>(dataGridView1->CurrentCell->Value);
			 String ^valueStr = dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString();
			 int value = convertToInt32(valueStr); 
			 pin_ptr<const wchar_t> wct = PtrToStringChars(valueStr);
			 stationParameterType sPara;
			 int row = e->RowIndex+1;
			 if (stationSetting->get(row, &sPara))
			 {
				 //_tcscpy(sPara.prodlineID, L"1");
				 switch (e->ColumnIndex)
				 {
					case	0:_tcscpy(sPara.stnID, wct);break;
					case	1:sPara.infeed = value; break;
					case	2:sPara.infeedoffset = value; break;
					case	3:sPara.outfeed = value; break;
					case	4:sPara.outfeedoffset = value; break;
				 }
				 stationSetting->set(row, &sPara);
			 }*/
		 }
	private: System::Void OnMouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
			
			 if ( e->Button == System::Windows::Forms::MouseButtons::Right )
			 {
				System::Windows::Forms::DataGridView::HitTestInfo^ hitTestInfo = dataGridView1->HitTest(e->X, e->Y);
				int rowIndex = hitTestInfo->RowIndex;
				int colIndex = hitTestInfo->ColumnIndex;
				if (hitTestInfo->Type == DataGridViewHitTestType::Cell)
				{
					DataGridViewCell ^clickedCell;
					clickedCell = dataGridView1->Rows[rowIndex]->Cells[colIndex];
					clickedCell->Selected = true;
					currentRowIndex = rowIndex;
					currentColIndex = colIndex;

					Control^ control = dynamic_cast<Control^>(sender);
					contextMenuStrip_Popup1->Show(control, rowIndex, colIndex);
					
				}
			 }
	
					/*
{
    Control c = sender as Control;
    if (e.Button == MouseButtons.Right)
    {
        this.contextMenuStrip1.Show(c, e.Location, this.dropDownDirection);
    }
				}
			 }

*/

#ifdef TESTING_ONLY			
			{
			 if ( e->Button == System::Windows::Forms::MouseButtons::Right )
			 {
				 Char tempChar = 'a';
				 MessageBox::Show( String::Format( "The character at the specified position is {0}.", tempChar ) );
				 System::Windows::Forms::DataGridView::HitTestInfo^ hitTestInfo = dataGridView1->HitTest(e->X, e->Y);

				int rowIndex = hitTestInfo->RowIndex;
				int colIndex = hitTestInfo->ColumnIndex;
				//int type = hitTestInfo->Type;
				if (hitTestInfo->Type == DataGridViewHitTestType::Cell)
				{
					DataGridViewCell ^clickedCell;
					clickedCell = dataGridView1->Rows[rowIndex]->Cells[colIndex];
					clickedCell->Selected = true; 
					
				}
				/*
				DataGridViewHitTestType ^type;
				if(type==System::Windows::Forms::DataGridView::DataGridViewHitTestType->Cell)
				{
				}*/
				dataGridView1->Rows->Insert(rowIndex, 2);
				dataGridView1->ClearSelection();
				//dataGridView1->Rows->RemoveAt(rowIndex);

				//Clipboard::SetDataObject(dataGridView1->GetClipboardContent());
				//Clipboard::GetText();
				
				if ((rowIndex>=0)&&(colIndex>=0))
					dataGridView1->Rows[rowIndex]->Cells[colIndex]->Value = Clipboard::GetData(dataGridView1->GetClipboardContent());
			 /*
			 dataGridView1.Rows[e.RowIndex].Selected = true;

Rectangle r = dataGridView1.GetCellDisplayRectangle(e.ColumnIndex, e.RowIndex, true);

contextMenu.Show((Control)sender, r.Left + e.X, r.Top + e.Y);



if (e.RowIndex >= 0 && e.ColumnIndex >= 0 && e.Button == MouseButtons.Right)
{
dgvBookmarks.Rows[e.RowIndex].Selected = true;
Rectangle r = dgvBookmarks.GetCellDisplayRectangle(e.ColumnIndex, e.RowIndex, true);

contextMenu.Show((Control)sender, r.Left + e.X, r.Top + e.Y);
}
			 */
			 }
			}
#endif

}


/*
private void DeleteRow_Click(object sender, EventArgs e)
{
    Int32 rowToDelete = MyrDataGridView.Rows.GetFirstRow(DataGridViewElementStates.Selected);
    MyDataGridView.Rows.RemoveAt(rowToDelete);
    MyDataGridView.ClearSelection();
}

Private cell_clicked As Boolean = False

    Private Sub DataGridView1_CellMouseClick(ByVal sender As Object, ByVal e As System.Windows.Forms.DataGridViewCellMouseEventArgs) Handles DataGridView1.CellMouseClick
        If e.RowIndex >= 0 And e.ColumnIndex >= 0 And e.Button = Windows.Forms.MouseButtons.Right Then
            DataGridView1.CurrentCell = DataGridView1.Rows(e.RowIndex).Cells(e.ColumnIndex)
            cell_clicked = True
        End If
    End Sub

    Private Sub DataGridView1_MouseUp(ByVal sender As Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles DataGridView1.MouseUp
        If e.Button = Windows.Forms.MouseButtons.Right Then
            If Not cell_clicked Then
                item_menu_charts.Enabled = False
                item_menu_web.Enabled = False
                item_menu_edit.Enabled = False
                item_menu_delete.Enabled = False
            Else
                item_menu_charts.Enabled = True
                item_menu_web.Enabled = True
                item_menu_edit.Enabled = True
                item_menu_delete.Enabled = True
            End If
            item_menu.Show(DataGridView1, e.X, e.Y)
            cell_clicked = False
        End If
    End Sub
*/
private: System::Void AddRowbutton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 dataGridView1->Rows->Add("", "-1", "-1", "-1", "-1");
		 }



private: System::Void insertRowToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			if (currentRowIndex>=0)
			{
				dataGridView1->Rows->Insert(currentRowIndex, 1);
			}
		 }

private: System::Void copyToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			DataObject ^dataObj = dataGridView1->GetClipboardContent();
			Clipboard::SetDataObject(dataObj, true);
		 }

private: System::Void deleteRowToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(currentRowIndex>=0)
				dataGridView1->Rows->RemoveAt(currentRowIndex);
		 }

private: System::Void pasteToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //char[2] rowSplitter = { '\r', '\n' };
            //char[1] columnSplitter = { '\t' };
			// Clipboard::GetDataObject()->GetData(DataFormats.Text);
/*
            // Get the text from clipboard
            IDataObject ^dataInClipboard = Clipboard->GetDataObject();
            string stringInClipboard = (string)dataInClipboard.GetData(DataFormats.Text);

            // Split it into lines
            string[] rowsInClipboard = stringInClipboard.Split(rowSplitter, StringSplitOptions.RemoveEmptyEntries);

            // Get the row and column of selected cell in grid
            int r = grid.SelectedCells[0].RowIndex;
            int c = grid.SelectedCells[0].ColumnIndex;

            // Add rows into grid to fit clipboard lines
            if (grid.Rows.Count < (r + rowsInClipboard.Length))
            {
                grid.Rows.Add(r + rowsInClipboard.Length - grid.Rows.Count);
            }

            // Loop through the lines, split them into cells and place the values in the corresponding cell.
            for (int iRow = 0; iRow < rowsInClipboard.Length; iRow++)
            {
                // Split row into cell values
                string[] valuesInRow = rowsInClipboard[iRow].Split(columnSplitter);

                // Cycle through cell values
                for (int iCol = 0; iCol < valuesInRow.Length; iCol++)
                {

                    // Assign cell value, only if it within columns of the grid
                    if (grid.ColumnCount - 1 >= c + iCol)
                    {
                        DataGridViewCell cell = grid.Rows[r + iRow].Cells[c + iCol];

                        if (!cell.ReadOnly)
                        {
                            cell.Value = valuesInRow[iCol];
                        }
                    }
                }
            }
        }
    }*/
		 }
private: System::Void CopyAllButton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			dataGridView1->SelectAll();
			DataObject ^dataObj = dataGridView1->GetClipboardContent();
			Clipboard::SetDataObject(dataObj, true);
			dataGridView1->ClearSelection();
			//Color copyColor = Color::FromArgb( 183, 185, 255 );

			String ^msg = "Copied ALL to Clipboard.\nYou may paste into your preferred spreadsheet";
			MessageBox::Show(this, msg, Text, MessageBoxButtons::OK,
			MessageBoxIcon::Information, MessageBoxDefaultButton::Button1);				//this->CopyAllButton->BackColor = copyColor;

		 }
/*
private: System::Void ExportToCSVbutton_Click(System::Object^  sender, System::EventArgs^  e)
		 {
		 }
*/


private: System::Void ExportToCSVbutton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 WriteStatusBar("Please wait...", Color::FromArgb( 188, 84, 14 ), 2);
			//const char cfilename[] = "InfeedOutfeedTable.csv\0";
			
			//String ^filepathStr = gcnew String(reinterpret_cast<const wchar_t*>(application_MyDocumentsPath));
			//filepathStr += "\\InfeedOutfeedTable.csv";
			

			char filename[1024];
			SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
			saveFileDialog1->InitialDirectory = gcnew String(reinterpret_cast<const wchar_t*>(application_MyDocumentsPath));
			saveFileDialog1->Filter = "csv files (*.csv)|*.csv|All files (*.*)|*.*";
			saveFileDialog1->FilterIndex = 1;
			saveFileDialog1->RestoreDirectory = true;
			//saveFileDialog1->FileName = gcnew String(reinterpret_cast<const char*>(cfilename));
			saveFileDialog1->FileName = "InfeedOutfeedTable.csv";
			
			if ( saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			{
				String2Char(saveFileDialog1->FileName, filename);
				if(stationSetting)
				{
					stationSetting->export2CSV(filename);
					String ^filenamestr = gcnew String(reinterpret_cast<const char*>(filename));
					//String ^msg = "Exported to:<"+ System::IO::Directory::GetCurrentDirectory() + "\\" + filenamestr + ">";
					String ^msg = "Exported to:<" + filenamestr + ">";
					MessageBox::Show(this, msg, Text, MessageBoxButtons::OK,
					MessageBoxIcon::Information, MessageBoxDefaultButton::Button1);	
				}
			}
		 }

private:Void WriteStatusBar(String ^msg, Color color, int timeout)
		{
			Statuslabel->ForeColor = color;
			Statuslabel->Text = msg;
			StatusLabeltimeout = timeout;
		}

private: System::Void ImportfromCSVbutton_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 WriteStatusBar("Please wait...", Color::FromArgb( 188, 84, 14 ), 2);

			 //const char cfilename[] = "InfeedOutfeedTable.csv\0";


			char filename[1024];
			OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
			openFileDialog1->InitialDirectory = gcnew String(reinterpret_cast<const wchar_t*>(application_MyDocumentsPath));
			//openFileDialog1->InitialDirectory = System::IO::Directory::GetCurrentDirectory();
			openFileDialog1->Filter = "csv files (*.csv)|*.csv|All files (*.*)|*.*";
			openFileDialog1->FilterIndex = 1;
			openFileDialog1->RestoreDirectory = true;
			//openFileDialog1->FileName = gcnew String(reinterpret_cast<const char*>(cfilename));
			openFileDialog1->FileName = "InfeedOutfeedTable.csv";
			
			if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			{
				String2Char(openFileDialog1->FileName, filename);
				 if(stationSetting)
				 {
					if (stationSetting->importFromCSV(filename)>0)
					{
						FillTable();
						SaveButton->Enabled = true;
						dirty++;
						WriteStatusBar("Import Successful", Color::FromArgb( 13, 118, 10 ), 2);
						//Statuslabel->ForeColor = Color::FromArgb( 28, 65, 213 );
						//Statuslabel->Text = "Import Successful";
					}
					else
					{
						wchar_t wtitle[128];
						int ssize = sizeof(wtitle);
						stationSetting->getCSVtitleLine(wtitle, 127);
						String ^formatstr = gcnew String(reinterpret_cast<const wchar_t*>(wtitle));			
						String ^filenamestr = gcnew String(reinterpret_cast<const char*>(filename));
						String ^errormsg = "Import CSV file FAILURE!\r\n\r\nFile <" + filenamestr + ">\r\n\r\nis not a valid compatible file type.\r\nThe CSV file first line should have the header title:\r\n\""+formatstr+"\"\r";
						MessageBox::Show(this, errormsg, Text, MessageBoxButtons::OK,
						MessageBoxIcon::Information, MessageBoxDefaultButton::Button1);
					}

				 }
			}
		 }
		 

private: System::Void InfeedOutFeedTable_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		 {
			 if (dirty>0)
			 {
				 String^ message = "Changes were made. Are you sure you want quit without saving?";
				 String^ caption = Text;
				 MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				 System::Windows::Forms::DialogResult result;
				 // Displays the MessageBox.
				 result = MessageBox::Show( this, message, caption, buttons, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2);
				 if ( result != System::Windows::Forms::DialogResult::Yes )
					 e->Cancel = true;
			 }
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
