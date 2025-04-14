#include "StdAfx.h"
#include <Windows.h>
#include "class_appPlayback.h"
//#include "CRCCCITT.h"


#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}	

class_appPlayback::class_appPlayback()
{
	sync1 = 0xA6;
	sync2 = 0x07;
	sync3 = 0x35;
	seqNo = 0;
	playfilefp = 0;
	playfilename[0] = 0x0;
	memset(&playState, 0x0, sizeof(structA60735_fileType));
	playState.delimiter0 = A60735_1sync;
	playState.delimiter1 = A60735_2sync;
	playState.delimiter2 = A60735_3sync;
	playState.databuffersize = 65536;
	playState.databuffer = (unsigned char *)malloc(playState.databuffersize+1);

	PlayBack_payload = (unsigned char *)malloc(65536);
	PlayBack_type = 0;
	PlayBack_delay = 0;
	playBackEvent = 0;

	delayfactor = 0.075;
	//delayfactor = 0.025;		//too fast can mess up the pusher thread sync... can later look at that in playback

	lfile = new logfile();


	wrkbuf = (unsigned char *)malloc(65536);

	timerFreq_ = new my_LARGE_INTEGER;
	counterAtStart_ = new my_LARGE_INTEGER;
	/*
	unsigned int lapse;

	Sleep(10);
	lapse = calculateElapsedTime();
	*/
}

class_appPlayback::~class_appPlayback()
{
	Close();
	free(playState.databuffer);
	free(PlayBack_payload);
	free(wrkbuf);
	SAFE_DELETE(lfile);
	delete timerFreq_;
	delete counterAtStart_;
}

const char *class_appPlayback::getRecordfilename()
{
	if (lfile)
		return lfile->getfile_Name();
	return "";
}

void class_appPlayback::Start(const char *file_name)
{
	seqNo = 1;
	lfile->start(file_name);
	QueryPerformanceFrequency((LARGE_INTEGER *)timerFreq_);
	QueryPerformanceCounter((LARGE_INTEGER *)counterAtStart_);
	//if(lfile) lfile->putc(ch);
}

void class_appPlayback::Close()
{
	close_play();
	/*
	if (playfilefp)
	{
		fclose(playfilefp);
		playfilefp = 0;
	}*/
}

void class_appPlayback::Open(const char *file_name)
{
	Close();
	strncpy(playfilename, file_name, sizeof(playfilename)-1);
	playfilename[sizeof(playfilename)-1] = 0x0;
	playfilefp = fopen(file_name, "rb");
	seqNo = 0;
}

void class_appPlayback::close_play()
{
	if (playfilefp)
		fclose(playfilefp);
	playfilefp = 0;
}

int class_appPlayback::Read(unsigned char *payload, unsigned char *type, int *delay)
{
	int size = 0;
	*type = 0;
	if (playfilefp)
	{
		bool done = 0;
		while(!done)
		{
			if (feof(playfilefp))
			{
				close_play();
				break;
			}
			int result = fgetc(playfilefp);
			if (result<0) 
			{
				size = result;
				close_play();
				break;
			}
			A60735StateMachine((unsigned char)result, &playState);
			switch (playState.status)
                {
                    case    PKT_FOUND:
							*type = playState.dtype;
							*delay = playState.lapse;
							size = playState.length;
							seqNo = playState.seqno;
							memcpy(payload, playState.dataptr, playState.length);
							payload[playState.length] = 0x0;
                            A60735resetState(&playState, 0);
							done = 1;
                            break;
                    case	PKT_CRCERROR:
                    case	PKT_ABORT:A60735resetState(&playState, 0);
                            break;
                    case	PKT_ACQUIRING:
                    default:break;
                }
		}
	}
	return size;
}


void class_appPlayback::continueRead()
{
	playBackEvent = 0;
	bytesAvail = Read(PlayBack_payload, &PlayBack_type, &PlayBack_delay);
	if (bytesAvail>0)
		playBackEvent = getPlayBack_delay();
}

int class_appPlayback::firstRead()
{
	bytesAvail = Read(PlayBack_payload, &PlayBack_type, &PlayBack_delay);
	if(bytesAvail>0)
		playBackEvent = getPlayBack_delay();
	
	if (playBackEvent>100)
		playBackEvent = 100;

	return bytesAvail;
}


unsigned int class_appPlayback::calculateElapsedTime()
{
  if (timerFreq_->QuadPart == 0)
  {
    return -1;
  }
  else
  {
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
    return static_cast<unsigned int>( (c.QuadPart - counterAtStart_->QuadPart) * 1000 / timerFreq_->QuadPart );
  }
}

void class_appPlayback::write(unsigned char type, const char *data, unsigned short size)
{
	if (!lfile->Active())
		return;
	unsigned int lapse = calculateElapsedTime();
	int ptr = wrapmrt_A60735((const unsigned char *)data, size, wrkbuf, type, lapse, seqNo++);
/*
	unsigned char crchi, crclo;
//	unsigned short uvalue;
	unsigned int lapse = calculateElapsedTime();
	//lapse = 3184438100;
	int ptr = 0;
	wrkbuf[ptr] = sync1;						ptr++;
	wrkbuf[ptr] = sync2;						ptr++;
	wrkbuf[ptr] = sync3;						ptr++;
	wrkbuf[ptr] = type;							ptr++;
	wrkbuf[ptr] = (unsigned char)(lapse>>24);	ptr++;
	wrkbuf[ptr] = (unsigned char)(lapse>>16);	ptr++;
	wrkbuf[ptr] = (unsigned char)(lapse>>8);	ptr++;
	wrkbuf[ptr] = (unsigned char)lapse;			ptr++;
	wrkbuf[ptr] = (unsigned char)(size>>8);		ptr++;
	wrkbuf[ptr] = (unsigned char)size;			ptr++;
	memcpy(wrkbuf+ptr, data, size);				ptr+=size;
	CRC_CCITT(wrkbuf,  ptr, &crchi, &crclo);	//calculate the CRC16 checksum
	wrkbuf[ptr] = crchi;						ptr++;
	wrkbuf[ptr] = crclo;						ptr++;
*/
	char *obuf = (char *)malloc(8192);
	listhex(wrkbuf, ptr, obuf);


	lfile->puts((const char *)wrkbuf, ptr);
	free(obuf);

	QueryPerformanceFrequency((LARGE_INTEGER *)timerFreq_);
	QueryPerformanceCounter((LARGE_INTEGER *)counterAtStart_);
}

void class_appPlayback::flush()
{
	if(lfile)
		lfile->flush();
}

void class_appPlayback::listhex(const unsigned char *wrkbuf, int size, char *obuf)
{
	int ii;
	char buf[32];
	obuf[0] = 0x0;
	for (ii=0;ii<size;ii++)
	{
		if (ii==0)
			sprintf(buf, "%02X", wrkbuf[ii]);
		else
			sprintf(buf, ",%02X", wrkbuf[ii]);
		strcat(obuf, buf);
	}

}



