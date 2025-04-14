#include "StdAfx.h"
#include <stdio.h>
#include <string.h>
#include "offlineCommandClass.h"


const char *byte2Binary(const unsigned char value, char *buf)
{
	unsigned char val = value;
	int len = 8;
	char *str = buf;
	*(str + len) = 0;
	while(len--)
	{
	    if (0x01 & val)
            *(str + len) = '1';
        else
            *(str + len) = '0';
		val >>= 1;
	}
	return buf;
}

offlineCommandClass::offlineCommandClass()
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
}

const char *offlineCommandClass::getofflineText()
{
		int ii;
		char bytetext[9];
		offlintext[0] = 0x0;
		for (ii=0;ii<8;ii++)
		{
			byte2Binary(pkt1[ii], bytetext);
			STRREV(bytetext);
			strcat_s(offlintext, sizeof(offlintext)-1, bytetext);
		}
		for (ii=0;ii<8;ii++)
		{
			byte2Binary(pkt2[ii], bytetext);
			STRREV(bytetext);
			strcat_s(offlintext, sizeof(offlintext)-1, bytetext);
		}
		return offlintext;
}