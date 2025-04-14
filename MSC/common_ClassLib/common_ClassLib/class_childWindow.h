#include <string.h>
#pragma once

typedef struct{
	int X;
	int Y;
	int W;
	int H;
	int Opened;
	char name[32];
}childWindowType;


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;


namespace common_ClassLib {

	/// <summary>
	/// Summary for class_childWindow
	/// </summary>
	public ref class class_childWindow :  public System::ComponentModel::Component
	{
	public:
		class_childWindow(childWindowType *configset)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			//cset = new childWindowType;
			//memset(cset, 0x0, sizeof(childWindowType));
			/*
			cset->X=0;
			cset->Y=0;
			cset->W=0;
			cset->H=0;
			*/
			cset = configset;
		}
		class_childWindow(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}

		int ChildWindowGetLocation( int *X,  int *Y)
		{
			if ((cset->X>0)&&(cset->Y>0))
			{
				*X = cset->X;
				*Y = cset->Y;
				return 1;
			}
			return 0;
		}

		int ChildWindowGetSize(int *W,  int *H)
		{
			if ((cset->W>40)&&(cset->H>40))
			{
				*W = cset->W;
				*H = cset->H;
				return 1;
			}
			return 0;
		}

		void ChildWindowClosing(int X, int Y)
		{
			cset->X = X;
			cset->Y = Y;
		}
		void ChildWindowResizeEnd(int Width,  int Height)
		{
			cset->W = Width;
			cset->H = Height;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~class_childWindow()
		{
			if (components)
			{
				delete components;
			}
			//delete cset;
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		childWindowType *cset;
/*
	private:int cset->X;
	private:int cset->Y;
	private:int cset->W;
	private:int cset->H;
	*/
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
