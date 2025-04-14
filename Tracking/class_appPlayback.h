#ifndef ___class_appPlayback__H
#define ___class_appPlayback__H

//#include <Windows.h>
#include <stdlib.h>
#include <string.h>
//#include <wtypes.h>
//#include <winbase.h>
#include "classlogfile.h"
#include "A60735_fileType.h"

//#pragma comment(lib, "Coredll.lib")
typedef __int64 my_LONGLONG;
typedef struct _my_LARGE_INTEGER
{
	my_LONGLONG QuadPart;
} my_LARGE_INTEGER;

class class_appPlayback
{
public:
	enum{
		_apbNULL = 0,
		_apbSVR_IN,
		_apbSVR_OUT,
		_apbPSH_IN,
		_apbPSH_OUT,
		_apbCMD_startMotor,
		_apbCMD_stopMotor,
		_apbCMD_StnAssign
	};
private:
	unsigned char sync1, sync2, sync3;
	logfile	*lfile;
	my_LARGE_INTEGER *timerFreq_;
	my_LARGE_INTEGER *counterAtStart_;
	unsigned char *wrkbuf;
	
	char playfilename[1024];
	FILE *playfilefp;
	structA60735_fileType playState;
	unsigned char *PlayBack_payload;
	unsigned char PlayBack_type;
	int PlayBack_delay;
	int bytesAvail;
	int seqNo;
	float delayfactor;
	int playBackEvent;

public:
	
	class_appPlayback();
	~class_appPlayback();
	void Start(const char *file_name);
	void Open(const char *file_name);
	void write(unsigned char type, const char *data, unsigned short size);
	void listhex(const unsigned char *wrkbuf, int size, char *obuf);
	void flush();
	void Close();
	int firstRead();
	void continueRead();
	unsigned char getPlayBack_type(){return PlayBack_type;}
	int getbytesAvail(){return bytesAvail;}
	void resetbytesAvail(){bytesAvail=0;}
	int getseqNo(){return seqNo;}
	const char *getRecordfilename();
	const char *getplayfilename() {return playfilename;}
	int getPlayBack_delay()
	{
		int nn = (int)((float)PlayBack_delay*delayfactor);
		if (nn<=0)
			nn = 1;
		return nn;
	}
	void setplaybackdelayfactor(float value) {delayfactor = value;}
	const unsigned char *getPlayBack_payload() {return PlayBack_payload;}
	bool Playing() {return (playfilefp!=0);}

	void advanceEvent() {if(playBackEvent>-1) playBackEvent--;}
	bool IsEvent() {return (playBackEvent==0);}

private:
	unsigned int calculateElapsedTime();
	int Read(unsigned char *payload, unsigned char *type, int *delay);
	void close_play();

};

#endif