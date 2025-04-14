//class_Keypad_Interface

#ifndef ___class_Keypad_Interface__H
#define ___class_Keypad_Interface__H

#define EEPROM_size					2048		//0x0000~0x07FF
#define MAX_EEPROM_STATIONS			128

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::Timers;
	using namespace System::Windows::Forms;
	using namespace System::Data::SqlClient;
	using namespace System::Resources;
	using namespace System::Globalization;
	using namespace System::Configuration;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO;		
	using namespace System::Data::Odbc;			
	using namespace System::IO::Ports;
	using namespace System::Xml;
	using namespace System::Runtime::InteropServices;

class class_Keypad_Interface{
private:
	unsigned char *eeprom[MAX_EEPROM_STATIONS];
	unsigned char SOT;
	unsigned char EOT;

public:
	class_Keypad_Interface();
	~class_Keypad_Interface();

	const unsigned char makeReadEEPROM(unsigned __int16 address, unsigned char *buf, int bytecount);
	void storeBytes(int stn_id, unsigned char *data, int size);
	unsigned char *geteepromLoc(int stn, int address);
	unsigned char *geteeprom(int stn);
	int getcount() {return MAX_EEPROM_STATIONS;}
	String^ getLCDlineLabel(int stn, unsigned __int16 address, int len);
	String^ getPrayerLabel(int stn);
	String^ getBreakLabel(int stn);
	String^ getRepairLabel(int stn);
	String^ getIdleLabel(int stn);

	void setLCDlineLabel(int stn, unsigned __int16 address, const char *data, int len);

	void setPrayerLabel_Default(int stn);
	void setBreakLabel_Default(int stn);	
	void setRepairLabel_Default(int stn);
	void setIdleLabel_Default(int stn);

	void setLCDlineLabel(int stn, unsigned __int16 address, const wchar_t *data, int len);

	void setLCDlineLabel(int stn,  unsigned __int16 address, String ^textstr);
};



#endif