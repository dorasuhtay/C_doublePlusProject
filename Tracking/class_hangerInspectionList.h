//#include <tchar.h>
//#include <vcclr.h>

#include "HangerInspectionForm.h"
#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;

#using <mscorlib.dll>

#define MAX_HANGERINSPECTIONFORMS		16



namespace BTREKCANDAEMONV1 {

/*
typedef struct {
	wchar_t hangerID[32];

	
	//HangerInspectionForm ^p;
	//HangerInspectionForm ^iform;
	//gcroot<HangerInspectionForm ^>    _managedObject;	
	//gcroot<HangerInspectionForm^> msg;
	//HangerInspectionForm ^form;
}hangerInpectionListType;
*/



	/// <summary>
	/// Summary for class_hangerInspectionList
	/// </summary>
	public ref class class_hangerInspectionList :  public System::ComponentModel::Component
	{
	public:
		class_hangerInspectionList(class_SQLfunc ^sql, String ^ipaddress)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			int ii;
			count = 0;
			pform = gcnew array<HangerInspectionForm^>(MAX_HANGERINSPECTIONFORMS);
			hangerID = gcnew array<String^>(MAX_HANGERINSPECTIONFORMS);
			//pform_status = gcnew array<int>(MAX_HANGERINSPECTIONFORMS);
			pform_status = gcnew array<int^>(MAX_HANGERINSPECTIONFORMS);
			for (ii=0;ii<MAX_HANGERINSPECTIONFORMS;ii++)
			{
				pform[ii] = nullptr;
				hangerID[ii] = "";
				//pform_status[ii] = 0;
			}
			IPAddress = ipaddress;
			sqlfunc = sql;
		}
		class_hangerInspectionList(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();

			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~class_hangerInspectionList()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: int count;
	private: array<HangerInspectionForm^>^ pform;
	//private: hangerInpectionListType hIList[10];
	private: array<String ^> ^hangerID;
	private: array<int^> ^pform_status;
			 String ^IPAddress;
			 class_SQLfunc ^sqlfunc;

	private: int findHangerID(String ^HangerID)
			 {
				 int ii;
				 for (ii=0;ii<count;ii++)
				 {
					 if (pform[ii]!=nullptr)
						if(!pform[ii]->Created)
							hangerID[ii] = "";
					 if (hangerID[ii] == HangerID)
						return ii;
				 }
				 return -1;
			 }

	private: int findEmpty()
			 {
				 int ii;
				 for (ii=0;ii<count;ii++)
				 {
					 if (pform[ii]!=nullptr)
						if(!pform[ii]->Created)
							return ii;
				 }
				 return -1;
			 }

			 
	public:void add(String ^HangerID)
	{
		if (count>=MAX_HANGERINSPECTIONFORMS) return;
		if(pform[count]!=nullptr) return;
		int index = findHangerID(HangerID);
		if (index>=0) 
		{
			if (pform[index])
				pform[index]->BringToFront();
			return;
		}
		index = findEmpty();
		if (index<0)
			index = count;
		pform[index] = gcnew HangerInspectionForm(sqlfunc, IPAddress);
		//pform[index]->Text = "index "+index;
		pform[index]->Text = "Inspect Hanger " + HangerID;
		
		pform[index]->sethangerID(HangerID);
		pform[index]->Focus();
		pform[index]->BringToFront();
		pform[index]->Show();
		pform[index]->setIndex_textBox(index.ToString());
		hangerID[index] = HangerID;
		if (index==count)
			count++;
		

	}


	public:void Close()
		   {
				int ii;
				for(ii=0;ii<MAX_HANGERINSPECTIONFORMS;ii++)
				{
					if (pform[ii]&&(pform[ii]->Created))
						pform[ii]->Close();
				}
		   }

	int get(int index, HangerInspectionForm^% ppfor)
	{
		if ((index>=0)&&(index<MAX_HANGERINSPECTIONFORMS))
		{
			ppfor = pform[index];
			return 1;
		}
		return 0;
	}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			components = gcnew System::ComponentModel::Container();
		}
#pragma endregion
	};
}
