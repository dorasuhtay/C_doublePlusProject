#ifndef pusherCounterClass___H
#define pusherCounterClass___H

#include "wctString.h"

typedef struct
{
	INT pushercount;
	INT pusherlink;
	INT sync;
	INT sync_max;
} pushercountDAT_Type;

//extern INT nPusherCount;
//extern INT pusherlink;

class pusherCounterClass
{
private:
	BOOL storeLock;
	pushercountDAT_Type pushercountDAT;

	INT numberof_CHAIN_LINKS_STOP_compensation;

	BOOL pusher_flag;

	wctString *filepath;
	wctString *filepathname;

public:
	INT pCount;
	INT pLink;				//this is the official pLink (pusher link used for infeed outfeed calculation
	INT internal_pLink;		//this is the "internal_pLink" for stopping motor in the middle between 2 pushers
	INT sync;
	bool flag_thread;
	INT sync_max;
	//INT counter120ms;
    bool enable;
	INT numberof_CHAIN_LINKS;
	INT numberof_CHAIN_LINKS_internalpLink;
	INT max_Number_of_PUSHER;
	bool flagged;
	INT linkInterval;
	INT ExceedError;
	bool hardwareSignalAvail;
	


public:
	pusherCounterClass(const wchar_t *path, int pusher_interval_millisec);
	~pusherCounterClass();
	const wchar_t *wgetfile_Name();
	const char *cgetfile_Name();
	//INT getPusherCount() {readDat(); nPusherCount=pCount;pusherlink = pLink;return pCount; }
	INT getPusherCount() {read_Dat(); return pCount; }
	//INT getPusherLink() {readDat(); nPusherCount=pCount;pusherlink = pLink;return pLink; }
	INT getPusherLink() {read_Dat(); return pLink; }
	//VOID setPusherCount(INT pC) {pCount = pC; writeDat(); nPusherCount=pCount;pusherlink = pLink;}
	VOID setPusherCount(INT pC) {pCount = pC; writeDat(); }
	//VOID setPusherLink(INT pL) {pLink = pL; writeDat(); nPusherCount=pCount;pusherlink = pLink;}
	VOID setPusherLink(INT pL) {pLink = pL; internal_pLink = pL; writeDat();}
	//void resetLink();
	//void resetPusherCounter();
	BOOL getpusher_flag() {/*return pusher_flag;*/ return flagged;}
	VOID read_Dat();
	VOID writeDat();

	VOID setnumberof_CHAIN_LINKS(INT links) {numberof_CHAIN_LINKS = links; numberof_CHAIN_LINKS_internalpLink = (numberof_CHAIN_LINKS*4);}//change pusherlink to stop motor if there is no signal incoming from pusher count
	VOID setnumberof_CHAIN_LINKS_STOP_compensation(INT links) {numberof_CHAIN_LINKS_STOP_compensation = links;}
	VOID setMax_Number_of_PUSHER(INT links) {max_Number_of_PUSHER = links;}
	VOID updateStop_compensationLink();

	VOID Start()
	{
		ExceedError = 0;
		internal_pLink = 0;
		hardwareSignalAvail = 1;
	}

	VOID Stop()
	{
		ExceedError = 0;
		hardwareSignalAvail = 0;
	}

	//INT incrementPusherCount(INT offset);
	VOID incrementPusherCount();
//	VOID decrementPusherCounter();
//	VOID updatePusherCount();
	VOID receivedPusherMsg();
	//VOID resetLink() {counter120ms = 1;pLink=0;nPusherCount=pCount;pusherlink = pLink;writeDat();}
	VOID resetLink() {pLink=0; internal_pLink=0; sync=0; ExceedError=0; writeDat();}
	VOID resetSync() {sync_max=0; sync=0;}
private:

	VOID setpusher_flag(bool flag) {/*pusher_flag = flag;*/ flagged = flag;}
/*
	VOID pLink__wrap_around();
		bool isPusher_LinkError();
*/
};




#endif
