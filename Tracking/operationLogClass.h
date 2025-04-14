#ifndef __operationLogClass__H
#define __operationLogClass__H

typedef struct {
	wchar_t PusherCount_HangerID[16];
	wchar_t STN_DEST[8];
	wchar_t STN_CURENT[8];
	int Outfeed_PusherId;
}opLogDataType;

using namespace System;

class operationLogClass{
public:
	opLogDataType data;
public:
	operationLogClass();
	~operationLogClass();
	void setPusherCount_HangerID(String^ ID);
	void setSTN_DEST(String^ ID);
	void setSTN_CURENT(String^ ID);
	void setOutfeed_PusherId(int id);
	String ^getPusherCount_HangerID();
	String ^getSTN_DEST();
	String ^getSTN_CURENT();
	int getOutfeed_PusherId();
	void clear();
};

#endif

