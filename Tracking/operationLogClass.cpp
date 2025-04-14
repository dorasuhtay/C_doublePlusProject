#include "StdAfx.h"
#include <string.h>
#include "operationLogClass.h"
#include "stringconversion.h"

operationLogClass::operationLogClass()
{
}

operationLogClass::~operationLogClass()
{
}

void operationLogClass::setPusherCount_HangerID(String^ ID){	String2CharArray(ID, data.PusherCount_HangerID);}
void operationLogClass::setSTN_DEST(String^ ID){	String2CharArray(ID, data.STN_DEST);}
void operationLogClass::setSTN_CURENT(String^ ID){	String2CharArray(ID, data.STN_CURENT);}
void operationLogClass::setOutfeed_PusherId(int id){	data.Outfeed_PusherId = id;}


String ^operationLogClass::getPusherCount_HangerID(){String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(data.PusherCount_HangerID));	return temp;}
String ^operationLogClass::getSTN_DEST(){String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(data.STN_DEST));	return temp;}
String ^operationLogClass::getSTN_CURENT(){String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(data.STN_CURENT));	return temp;}
int operationLogClass::getOutfeed_PusherId(){return data.Outfeed_PusherId;}


void operationLogClass::clear()
{
	memset(&data, 0x0, sizeof(opLogDataType));
}

