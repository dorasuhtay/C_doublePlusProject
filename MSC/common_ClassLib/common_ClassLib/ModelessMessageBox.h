
#pragma once

namespace common_ClassLib {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;



	/// <summary>
	/// Summary for ModelessMessageBox
	/// </summary>
	public ref class ModelessMessageBox : public System::Windows::Forms::Form
	{
	public:
		


		ModelessMessageBox(String ^msg)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			msg1 = msg;
			msg2 = "Please wait...";
			BackColor = Color::FromArgb( 255, 255, 183 );
			msg1Font = gcnew System::Drawing::Font( "Arial",16 );
			cancelButtonEnable = 0;
			preDelay=0;
		}

		void setMessage2(String ^msg)
		{
			msg2 = msg;
		}
		
		void setBackColor(Color color)
		{
			BackColor = color;
		}

		void setMessage1Font(System::Drawing::Font^ msgfnt)
		{
			msg1Font = msgfnt;
		}

		bool isCancelled()	{return (this->DialogResult==System::Windows::Forms::DialogResult::Cancel);	}
		void showCancelButton() {cancelButtonEnable = 1;}

	public: 
			System::Windows::Forms::ImageList^  waitIcon_imageList;
			int preDelay;	

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ModelessMessageBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


			String ^msg1;
			String ^msg2;
			ThreadStart^ threadDelegate; 
			Thread^ newThread; 
			int opacity;
			Color BackColor;
			bool cancelButtonEnable;
	private: int tcounter;

	

			 Control^ control;
	private: System::Windows::Forms::Button^  Cancelbutton;
	private: System::Windows::Forms::Timer^  timer1;


			System::Drawing::Font^ msg1Font;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->Cancelbutton = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// Cancelbutton
			// 
			this->Cancelbutton->Location = System::Drawing::Point(266, 92);
			this->Cancelbutton->Name = L"Cancelbutton";
			this->Cancelbutton->Size = System::Drawing::Size(56, 23);
			this->Cancelbutton->TabIndex = 0;
			this->Cancelbutton->Text = L"&Cancel";
			this->Cancelbutton->UseVisualStyleBackColor = true;
			this->Cancelbutton->UseWaitCursor = true;
			this->Cancelbutton->Click += gcnew System::EventHandler(this, &ModelessMessageBox::Cancelbutton_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &ModelessMessageBox::timer1_Tick);
			// 
			// ModelessMessageBox
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(334, 127);
			this->Controls->Add(this->Cancelbutton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"ModelessMessageBox";
			this->Opacity = 0;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ModelessMessageBox";
			this->TopMost = true;
			this->UseWaitCursor = true;
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ModelessMessageBox::ModelessMessageBox_FormClosed);
			this->Load += gcnew System::EventHandler(this, &ModelessMessageBox::ModelessMessageBox_Load);
			this->Shown += gcnew System::EventHandler(this, &ModelessMessageBox::ModelessMessageBox_Shown);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ModelessMessageBox::ModelessMessageBox_Paint);
			this->ResumeLayout(false);

		} 
#pragma endregion
	private: System::Void ModelessMessageBox_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				 tcounter = 1;
				this->timer1->Enabled = true;
				this->timer1->Start();
				 if (!cancelButtonEnable)
					Cancelbutton->Visible = false;

				 control = dynamic_cast<Control^>(sender);
				 //(dynamic_cast<Control^>(sender))->Hide();

				 //Control^ control
				 //Graphics^ g = control->CreateGraphics();
/*
      // Create string to draw.
      String^ drawString = "Sample Text";
      // Create font and brush.
      System::Drawing::Font^ drawFont = gcnew System::Drawing::Font( "Arial",16 );
      SolidBrush^ drawBrush = gcnew SolidBrush( Color::Black );
      // Create point for upper-left corner of drawing.
      //PointF drawPoint = PointF(150.0F,150.0F);
	  PointF drawPoint = PointF(10.0F,10.0F);
      // Draw string to screen.
	  
      g->DrawString( drawString, drawFont, drawBrush, drawPoint );
	  */


				threadDelegate = gcnew ThreadStart( this, &ModelessMessageBox::ServiceThread);
			newThread = gcnew Thread(threadDelegate);
			newThread->Start();
			 }


		void ServiceThread()
		{
			int counter = 0;
			//---------------------------------------------------
			//perform a 1 second delay to hold off the popup
			// if the popup takes more than 1 seconds than popup
			//---------------------------------------------------
			if(preDelay>0)
			{
				while(preDelay)
				{
					Thread::Sleep(100);
					counter++;
					if((counter%10)==0)
						preDelay--;
				}
				if (preDelay!=0)
					return;
			}
			
			//----------------------------------------------------
			int imageptr = 0;
			//int byteCount, ii, result;
			//array<Byte>^ msg;
			//array<Byte>^ bytes = gcnew array<Byte>(512);
			Graphics^ g = control->CreateGraphics();
			Pen^ blackPen = gcnew Pen( Color::Black,1.0f );
			System::Drawing::Rectangle clientRect = this->ClientRectangle;
			SolidBrush^ blueBrush = gcnew SolidBrush(BackColor);
			clientRect.Inflate(  -1, -1 );
			g->DrawRectangle(blackPen, clientRect);
			clientRect.Inflate(  -1, -1 );
			//clientRect.Offset( -1, -1);
			g->FillRectangle( blueBrush, clientRect );
			counter = 0;
			// loop while animate variable is true 
			while(true)
			{
				if((counter%10)==0)
				{

      // Create pen.
      //Pen^ blackPen = gcnew Pen( Color::Black,3.0f );

      // Create coordinates of points that define line.
      int x1 = 100;
      int y1 = 100;
      int x2 = 500;
      int y2 = 200;

      // Draw line to screen.
      //g->DrawLine( blackPen, x1, y1, x2, y2 );


      // Create string to draw.
      //String^ drawString = "Sample Text";
      // Create font and brush.
      //System::Drawing::Font^ msg1Font = gcnew System::Drawing::Font( "Arial",16 );
      SolidBrush^ drawBrush = gcnew SolidBrush( Color::Black );
      // Create point for upper-left corner ofSystem::Drawing::Font^ msg1Font = gcnew System::Drawing::Font( "Arial",16 ); drawing.
      //PointF drawPoint = PointF(150.0F,150.0F);
	  PointF drawPoint = PointF(10.0F,10.0F);
      // Draw string to screen.
	  
      g->DrawString( msg1, msg1Font, drawBrush, drawPoint );
				// we need to delete the line that already exists on the screen so

	        // Create image.
      //Image^ newImage = Image::FromFile( "user-online.png" );
	
	  //Draw the animated images for "waiting"
	  float xx = 50.0F;
      float yy = 100.0F;
      float width = 200.0F;
      float height = 50.0F;
      RectangleF drawRect = RectangleF(xx,yy,width,height);
	  if (waitIcon_imageList&&(waitIcon_imageList!=nullptr))
	  {
		  Image^ newImage = waitIcon_imageList->Images[imageptr];
		  imageptr= (imageptr+1)%waitIcon_imageList->Images->Count;
		  int x = 10;
		  int y = 90;
		  g->DrawImage( newImage, x, y );
	  }
	  System::Drawing::Font^ arial10Font = gcnew System::Drawing::Font( "Arial",10 );
	  g->DrawString( msg2, arial10Font, drawBrush, drawRect );


// we draw another line of the background color
	  /*
g.DrawLine(penBack, startPoint, endPoint);

// offset the line points

startPoint.Offset(1, 1);

endPoint.Offset(1, 1);

// draw the line at the new position

g.DrawLine(penLine, startPoint, endPoint);
*/
				}

//				if (Opacity<1.0)
//					control->Opacity = 0.75;
				//if(this->DialogResult==System::Windows::Forms::DialogResult::Cancel)
				//{

				//}
				Thread::Sleep(100);
				counter++;
			}
		}

	private: System::Void ModelessMessageBox_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
			 {
//				 label1->Text = msg1;
			 }
	private: System::Void ModelessMessageBox_Shown(System::Object^  sender, System::EventArgs^  e) 
			 {
//				 label1->Text = msg1;
			 }

	private: System::Void ModelessMessageBox_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) 
			 {
				 newThread->Abort();
			 }

	private: System::Void Cancelbutton_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
				 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
			 
			// if ((tcounter%10)==0)
				//this->Opacity = 1.00;
			 tcounter++;
		 }
};
}
