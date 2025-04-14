#include "StdAfx.h"
#include "motorClass.h"

motorClass::motorClass()
{
	motorON = 0;
	offMotorFlag = 0;
	WriteToSerialfunction = 0;
}

motorClass::~motorClass()
{
}