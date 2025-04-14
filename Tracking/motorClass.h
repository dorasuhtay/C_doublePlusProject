#ifndef __motorClass___H
#define __motorClass___H

#include "stdafx.cpp"
//#include "CANRev.h"
#include <iostream>
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <ios>
#include <string.h>
#include <wchar.h>
#include "lcircbuf.h"
#include "motorClass.h"
#include "online_setup.h"
#include "pusherCounterClass.h"
#include "applicationSetting.h"

	using namespace System;
	using namespace System::IO::Ports;



class motorClass{
private:
	bool motorON;
	bool offMotorFlag;
public:
	int (*WriteToSerialfunction)(SerialPort^%  serial_port, int command, int pusher_Count);
	motorClass();
	~motorClass();
	bool ismotorON() {return motorON;}
	void TurnOn(SerialPort^%  serial_port, int pusher_Count) {if (WriteToSerialfunction) {offMotorFlag=false; WriteToSerialfunction(serial_port, 103, pusher_Count);motorON=1;}}
	void TurnOff(SerialPort^%  serial_port, int pusher_Count) {if (WriteToSerialfunction) {offMotorFlag=false; WriteToSerialfunction(serial_port, 108, pusher_Count);motorON=0;}}
	void ACK_MSG(SerialPort^%  serial_port, int pusher_Count) {if (WriteToSerialfunction) { WriteToSerialfunction(serial_port, 231, pusher_Count);}}
	void ResendMSG(SerialPort^%  serial_port,int cmdID, int pusher_Count) {if (WriteToSerialfunction) { WriteToSerialfunction(serial_port, cmdID, pusher_Count);}}
	void setoffMotorFlag(bool state) {offMotorFlag = state;}
	bool getoffMotorFlag() {return offMotorFlag;}
	void sendpreviouscmd(SerialPort^%  serial_port, int pusher_Count, int cmdid) 
	{
		if (WriteToSerialfunction) 
		{
			offMotorFlag=false; 
			WriteToSerialfunction(serial_port, cmdid, pusher_Count);
			if(cmdid=103)
				motorON=1;
			if(cmdid=108)
				motorON=0;
		}
	}
};

#endif