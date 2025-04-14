#include <vcclr.h>  
#include "class_processError.h"
#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;
using namespace System::Data::SqlClient;
using namespace System::Data;

extern int openDBConnection(SqlConnection ^%SQLmyConnection, String ^ipaddress, String ^dbname, String ^ID, String ^password, int timeout);
extern bool SQL_errorExceptionLog(SqlException ^sqle, const char *file, int line, String ^remarks="");

namespace common_ClassLib {

	/// <summary>
	/// Summary for class_SQLfunc
	/// </summary>
	public ref class class_SQLfunc :  public System::ComponentModel::Component
	{
	public:
		String ^SQLInstanceName;
		class_SQLfunc(String ^ipaddress, String ^dbname, String ^loginName, String ^loginPassword)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			ErrorLog = 0;
			SQLInstanceName = "";
			this->ipaddress = ipaddress;
			this->dbname = dbname;
			this->loginName = loginName;
			this->loginPassword = loginPassword;
			
		}
		
		void setSQLDB_Fail(int fail) {SQLDB_Fail = fail;}
		int isSQLConnectFail() { return SQLDB_Fail;}

		int openDBConnection_open(SqlConnection ^%SQLmyConnection)
		{
			int nn = 0;
			if (SQLDB_Fail) 
				return SQLDB_Fail;
			SQLmyConnection = gcnew SqlConnection(); 
			String ^myConnectionString =	"Data Source = "+ipaddress+
											";Network Library = DBMSSOCN;Initial Catalog="+dbname+
											";User ID="+loginName+";Password="+loginPassword + ";";
			//if (timeout>0)
			//	myConnectionString += "Connect Timeout="+timeout.ToString() + ";"; 

			SQLmyConnection->ConnectionString = myConnectionString; 
			try
			{
				SQLmyConnection->Open();
			}
			catch (SqlException ^sqle)
			{
				//SQLerrorExceptionLog(sqle, __FILE__, __LINE__, "openDBConnection");
				if (ErrorLog)
					ErrorLog->logError("SQL", sqle->Number, __FILE__, __LINE__, sqle->Message, "openDBConnection"); 
				nn = -1;
			}
			return nn;
		}


		int openDBConnection(SqlConnection ^%SQLmyConnection)
		{
			int nn = openDBConnection_open(SQLmyConnection);
			if (SQLmyConnection&&(SQLmyConnection!=nullptr))
				SQLmyConnection->Close();
			return nn;
		}

		class_processError *ErrorLog;

		String ^getipaddress() {return this->ipaddress;}
		String ^getdbname() { return this->dbname;}

		String ^getloginNames() {return this->loginName;}
		String ^getloginPassword() { return this->loginPassword;}

		String ^getDescription() {return getipaddress() + "(" +getdbname()+ ")";}

		const wchar_t *wgetloginNames()
		{
			pin_ptr<const wchar_t> wstr = PtrToStringChars(this->loginName);
			return wstr;
		}

		const wchar_t *wgetloginPassword()
		{
			pin_ptr<const wchar_t> wstr = PtrToStringChars(this->loginPassword);
			return wstr;
		}

		const wchar_t *wgetdbname()
		{
			pin_ptr<const wchar_t> wstr = PtrToStringChars(this->dbname);
			return wstr;
		}

		const wchar_t *wgetipaddress()
		{
			pin_ptr<const wchar_t> wstr = PtrToStringChars(this->ipaddress);
			return wstr;
		}
		
	//------------------------------------------------
	//Public variables
	//------------------------------------------------
	public:


		class_SQLfunc(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();

			SQLDB_Fail = 0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~class_SQLfunc()
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
		String ^ipaddress;
		String ^dbname;
		String ^loginName;
		String ^loginPassword;
		int SQLDB_Fail;

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
