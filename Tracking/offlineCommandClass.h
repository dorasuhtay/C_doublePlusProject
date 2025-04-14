#ifndef __offlineCommandClass__h
#define __offlineCommandClass__h

#include <string.h>
#include <stdio.h>
#include "xplatform_define.h"

class offlineCommandClass{
private:
	unsigned char pkt1[8];
	unsigned char pkt2[8];
	int byteCounter;
	char offlintext[256];
public:
	offlineCommandClass();
	/*
	{
		int ii;
		byteCounter = 0;
		memset(&offlintext, '0', sizeof(offlintext));
		offlintext[sizeof(offlintext)-1] = 0x0;
		for (ii=0;ii<8;ii++)
		{
			pkt1[ii] = 0x0;
			pkt2[ii] = 0x0;
		}
	}*/
	~offlineCommandClass()
	{
	}
	void reset(){byteCounter=0;}
	void byteNo(int index){byteCounter=index;}
	void next(){byteCounter++; byteCounter=byteCounter%2;}
	int isComplete() {return byteCounter;}
	void setbyte(unsigned char *pkt)
	{
		if (byteCounter==0)
			memcpy(pkt1, pkt, 8);
		else
			memcpy(pkt2, pkt, 8);
	}

	const char *getofflineBytesinHex(char *buf, int size)
	{
		int ii;
		char temp[16];
		buf[0] = 0x0;
		for (ii=0;ii<8;ii++)
		{
			if (ii==0)
				SPRINTF(temp, "%02X",pkt1[ii]);
			else
				SPRINTF(temp, ",%02X",pkt1[ii]);
			strcat_s(buf, size-1, temp);
		}
		strcat_s(buf, size-1, " ");
		for (ii=0;ii<8;ii++)
		{
			if (ii==0)
				SPRINTF(temp, "%02X",pkt2[ii]);
			else
				SPRINTF(temp, ",%02X",pkt2[ii]);
			strcat_s(buf, size-1, temp);
		}
		return buf;
	}

	const char *getofflineText();
		/*
	{
		int ii;
		char bytetext[9];
		offlintext[0] = 0x0;
		for (ii=0;ii<8;ii++)
		{
			byte2Binary(pkt1[ii], bytetext);
			strrev(bytetext);
			strcat(offlintext, bytetext);
		}
		for (ii=0;ii<8;ii++)
		{
			byte2Binary(pkt2[ii], bytetext);
			strrev(bytetext);
			strcat(offlintext, bytetext);
		}
		return offlintext;
	}*/
	bool isStationOffline(int stnid)
	{
		if ((stnid>=0)&&(stnid<=128))
			return (offlintext[stnid]=='0');
		return 1;
	}
};




#endif