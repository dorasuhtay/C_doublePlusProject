#include "StdAfx.h"
#include <stdlib.h>
#include <string.h>
#include "class_Keypad_Interface.h"
#include "hardware\command.h"
#include "hardware\keypad\EE_Key_Map.h"



class_Keypad_Interface::class_Keypad_Interface()
{
	int ii;
	SOT = 0x05;
	EOT = 0x0a;
	unsigned char count = 0;
	for (ii=0;ii<MAX_EEPROM_STATIONS;ii++)
	{
		eeprom[ii] = (unsigned char *)malloc(EEPROM_size);
		for (int jj=0;jj<2048;jj++)
		{
			if (jj==0)
				eeprom[ii][jj] = ii;
			else
				eeprom[ii][jj] = count; //0xFF;
			count++;
		}
	}


	//eeprom = (unsigned char *)malloc(EEPROM_size);

}

class_Keypad_Interface::~class_Keypad_Interface()
{
	int ii;
	for (ii=0;ii<MAX_EEPROM_STATIONS;ii++)
		free(eeprom[ii]);
}

const unsigned char class_Keypad_Interface::makeReadEEPROM(unsigned __int16 address, unsigned char *buf, int bytecount)
{
	memset(buf,'.', 8);
	buf[0] = (unsigned char)((address>>8)&0x00FF);		//EEAdd_Hi
	buf[1] = (unsigned char)(address&0x00FF);			//EEAdd_Low
	buf[2] = bytecount;
	buf[3] = 'E';
	buf[4] = 'E';
	buf[5] = 'R';
	buf[6] = 'D';
	buf[7] = '.';

	return READ_EEPROM_KEY;
}

void class_Keypad_Interface::storeBytes(int stn_id, unsigned char *data, int size)
{
	int ii;
	if ((stn_id<0)||(stn_id>=MAX_EEPROM_STATIONS)) return;
	unsigned __int16 address, addressHi, addressLo;
	addressHi = data[0];
	addressHi <<= 8;
	addressHi &= 0xFF00;
	addressLo = data[1];
	address = addressHi|addressLo;
	addressLo &= 0x00FF;
	int len =  data[2];
	unsigned char *ptr = data+3;
	for (ii=0;ii<len;ii++)
	{	
		if (address<0) continue;
		if (address>=EEPROM_size) continue;

		eeprom[stn_id][address] = *ptr++;
		address++;
	}
}

unsigned char *class_Keypad_Interface::geteepromLoc(int stn, int address)
{
	if ((stn<0)||(stn>=MAX_EEPROM_STATIONS)) return 0;
	if ((address<0)||(address>=EEPROM_size)) return 0;
	return &eeprom[stn][address];
}


unsigned char *class_Keypad_Interface::geteeprom(int stn)
{
	if ((stn<0)||(stn>=MAX_EEPROM_STATIONS)) return 0;
	return eeprom[stn];
}

void class_Keypad_Interface::setLCDlineLabel(int stn, unsigned __int16 address, const char *data, int len)
{
	if ((stn<0)||(stn>=MAX_EEPROM_STATIONS)) return;
	memcpy(eeprom[stn]+address, data, len);
}

void class_Keypad_Interface::setLCDlineLabel(int stn, unsigned __int16 address, const wchar_t *data, int len)
{
	if ((stn<0)||(stn>=MAX_EEPROM_STATIONS)) return;
	memcpy(eeprom[stn]+address, data, sizeof(wchar_t)*len);
}

String^ class_Keypad_Interface::getLCDlineLabel(int stn, unsigned __int16 address, int len)
{
	if ((stn<0)||(stn>=MAX_EEPROM_STATIONS)) return "";
	char buf[32];
	memcpy(buf, eeprom[stn]+address, len);
	return gcnew String(reinterpret_cast<const char*>(buf)); 
}

String^ class_Keypad_Interface::getPrayerLabel(int stn)	{return getLCDlineLabel(stn, Loc_Str_81, 16);}
String^ class_Keypad_Interface::getBreakLabel(int stn)	{return getLCDlineLabel(stn, Loc_Str_82, 16);}
String^ class_Keypad_Interface::getRepairLabel(int stn)	{return getLCDlineLabel(stn, Loc_Str_83, 16);}
String^ class_Keypad_Interface::getIdleLabel(int stn)	{return getLCDlineLabel(stn, Loc_Str_84, 16);}

void class_Keypad_Interface::setPrayerLabel_Default(int stn)	{setLCDlineLabel(stn, Loc_Str_81, Str_81, 16);}
void class_Keypad_Interface::setBreakLabel_Default(int stn)		{setLCDlineLabel(stn, Loc_Str_82, Str_82, 16);}
void class_Keypad_Interface::setRepairLabel_Default(int stn)	{setLCDlineLabel(stn, Loc_Str_83, Str_83, 16);}
void class_Keypad_Interface::setIdleLabel_Default(int stn)		{setLCDlineLabel(stn, Loc_Str_84, Str_84, 16);}

void class_Keypad_Interface::setLCDlineLabel(int stn, unsigned __int16 address, String ^textstr)
{
	String ^finalstr ="";
	int str_length = textstr->Length;
	if(str_length != 8)
		finalstr = textstr->ToString()->PadRight(8,' ');
	else
		finalstr = textstr->ToString()->PadLeft(4,' ');
	array<wchar_t> ^szChar1 = finalstr->ToCharArray();
	array<Byte> ^Bytecode = Encoding::GetEncoding(936)->GetBytes(szChar1) ;
	char buff[32];
	for (int ii=0;ii<str_length;ii++)
		buff[ii]=Bytecode[ii];
	setLCDlineLabel(stn, address, buff, str_length);

}