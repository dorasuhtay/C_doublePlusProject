/*	CRC generator function function modified from
   http://www.modicon.com/techpubs/toc7.html
	Be certain that the memory reserved for pMsg is two
	bytes longer than MsgLength.

#ifndef CRC_CCITTH
#define CRC_CCITTH
extern void AddCRC_CCITTchksum(char *buf);
extern int CRC_CCITTchksumFail(char *buf);
#endif
*/
#include "StdAfx.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "CRCCCITT.h"
#include "numberConversion.h"
/* Table of CRC values for high-order byte */
/*
static unsigned char auchCRCHi[] = {
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;
*/
/* Table of CRC values for low-order byte */
/*
static char auchCRCLo[] = {
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
0x43, 0x83, 0x41, 0x81, 0x80, 0x40
} ;
*/
/*
void CRC_CCITT(unsigned char* pMsg,  int MsgLength, unsigned char *Hi, unsigned char *Lo)
{
	unsigned char CRCHi;
	unsigned char CRCLo;
	unsigned int Index;
	CRCHi=0xff;
	CRCLo =0xff;
	while(MsgLength--){
		Index =CRCHi^*pMsg++;
		CRCHi =CRCLo^auchCRCHi[Index];
		CRCLo =auchCRCLo[Index];
		}

//	*pMsg =CRCHi; pMsg++;
//	*pMsg =CRCLo;
	//If we are generating a CRC on a message that already includes a CRC,
	//and if the message was received without error, the new CRC will be 0x00
	//and this fuction will return '0'.
//	if((CRCHi ==0x00)&(CRCLo ==0x00))
//	  return 0;
//	else
//	  return -1;

	*Hi = CRCHi;
	*Lo = CRCLo;
}
*/




/*
//-------------------------------------------------------------------------------------
//void AddCRC_CCITTchksum(char *buf)
//Add the CRC_CCITT checksum to the string pointed by buf
//format: $xxxxx..xxxxxxxxxcccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//    where xxx..xx is the string pointed by buf
//          cccc is the ASCII hex 16 bit checksum
//          <CR><LF> terminates the string after the checksum
//
//    The following are reserve characters that should not be used within the data string
//    <CR><LF> is the termination characters
//    $ is the start character of the statement
//    The CRC_CCITT calculation begins from $ right to the last character before a
//    'CR' or 'LF' or to the last character of the string.
//
//   input buf                             resultant buf
// $xxxxxxxxxxxxxxxx               $xxxxxxxxxxxxxxxxcccc<CR><LF>
// $xxxxxxxxxxxxxxxx<CR>           $xxxxxxxxxxxxxxxxcccc<CR><LF>
// $xxxxxxxxxxxxxxxx<LF>           $xxxxxxxxxxxxxxxxcccc<CR><LF>
//-------------------------------------------------------------------------------------
void AddCRC_CCITTchksum(char *buf)
{
	unsigned char CRCHi;
	unsigned char CRCLo;
	char CRCstr[16];
	char *sptr;
	CRCHi=0xff;
	CRCLo =0xff;
	sptr = strchr(buf,'\r');
	if (sptr)
		*sptr = 0x0;
	sptr = strchr(buf,'\n');
	if (sptr)
		*sptr = 0x0;

//void CRC_CCITT(unsigned char* pMsg,  int MsgLength, unsigned char *Hi, unsigned char *Lo)
	CRC_CCITT((unsigned char* )buf,  strlen(buf), &CRCHi, &CRCLo);
	sprintf(CRCstr,"%02x%02x\r\n",CRCHi, CRCLo);
   strupr(CRCstr);
   strcat(buf,CRCstr);
}
*/


//-------------------------------------------------------------------------------------
//void AddCRC_CCITTchksum(char *buf)
//Add the CRC_CCITT checksum to the string pointed by buf
//format: $xxxxx..xxxxxxxxxcccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//    where xxx..xx is the string pointed by buf
//          cccc is the ASCII hex 16 bit checksum
//          <CR><LF> terminates the string after the checksum
//
//    The following are reserve characters that should not be used within the data string
//    <CR><LF> is the termination characters
//    $ is the start character of the statement
//    The CRC_CCITT calculation begins from $ right to the last character before a
//    'CR' or 'LF' or to the last character of the string.
//
//   input buf                             resultant buf
// $xxxxxxxxxxxxxxxx               $xxxxxxxxxxxxxxxxcccc<CR><LF>
// $xxxxxxxxxxxxxxxx<CR>           $xxxxxxxxxxxxxxxxcccc<CR><LF>
// $xxxxxxxxxxxxxxxx<LF>           $xxxxxxxxxxxxxxxxcccc<CR><LF>
//-------------------------------------------------------------------------------------
void AddLnCRC_CCITTchksum(char *buf)
{
	unsigned char CRCHi;
	unsigned char CRCLo;
	char CRCstr[16];
	char *sptr;
	CRCHi=0xff;
	CRCLo =0xff;
	if (strlen(buf)==0)
	 	return;
	sptr = strchr(buf,'\r');
	if (sptr)
		*sptr = 0x0;
	sptr = strchr(buf,'\n');
	if (sptr)
		*sptr = 0x0;
	int len = strlen(buf);
   if (len<=0)
   	return;
	CRC_CCITT((unsigned char *)buf,  len, &CRCHi, &CRCLo);
	sprintf(CRCstr,"%02x%02x\r\n",CRCHi, CRCLo);
   strupr(CRCstr);
   strcat(buf,CRCstr);
}


//------------------------------------------------------------------------------
//format: $xxxxx..xxxxxxxxxcccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//return  0 if no error
//       -3 if no CRC fail check.
//------------------------------------------------------------------------------
int CRC_CCITTchksumNFail(char *buf, int szsize)
{
	unsigned char CRCHi=0xff;
	unsigned char CRCLo =0xff;
	char CRCstr[16];
	char *sptr;
	char *CRCptr;
	sptr = strchr(buf,'\r');
	if (sptr)
		*sptr = 0x0;
	sptr = strchr(buf,'\n');
	if (sptr)
		*sptr = 0x0;
	CRC_CCITT((unsigned char*)buf,  szsize, &CRCHi, &CRCLo);
	sprintf(CRCstr,"%02x%02x",CRCHi, CRCLo);
	CRCptr = (buf + szsize);
   strupr(CRCstr);
	if (strncmp(CRCstr,CRCptr,4)!=0)
		return -3;					//There is a CRC error
	return 0;						//There is no CRC error
}

/*
//------------------------------------------------------------------------------
//format: $xxxxx..xxxxxxxxxcccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//return  0 if no error
//       -3 if no CRC fail check.
//------------------------------------------------------------------------------
int CRC_CCITTchksumFail(char *buf)
{
	unsigned char CRCHi=0xff;
	unsigned char CRCLo =0xff;
	char CRCstr[16];
	char *sptr;
	char *CRCptr;
	if ((strlen(buf)-4)<=0)
	 	return -4;					//There is string error
	sptr = strchr(buf,'\r');
	if (sptr)
		*sptr = 0x0;
	sptr = strchr(buf,'\n');
	if (sptr)
		*sptr = 0x0;
	int len = strlen(buf)-4;
   if (len<=0)
   	return -4;
	CRC_CCITT((unsigned char *)buf,  len, &CRCHi, &CRCLo);
	sprintf(CRCstr,"%02x%02x",(unsigned char)(CRCHi&0xFF), (unsigned char)(CRCLo&0xFF));
	CRCptr = (buf + (strlen(buf)-4));
   strupr(CRCstr);
	if (strncmp(CRCstr,CRCptr,4)!=0)
		return -3;					//There is a CRC error
	return 0;						//There is no CRC error
}
*/

int CRC16_ok(char *pMsg, int szsize)
{
	unsigned char CRCHi=0;
	unsigned char CRCLo=0;
	CRC_CCITT((unsigned char*)pMsg,  szsize, &CRCHi, &CRCLo);
   return ((*(pMsg+szsize)==CRCHi)&&(*(pMsg+szsize+1)==CRCLo));
//   return ((*(pMsg+szsize)==(crc>>8))&&(*(pMsg+szsize+1)==(crc&0xFF)));
}

//------------------------------------------------------------------------------------------
//Calculate the CRC polynomial 16 bit ascii checksum
//  123456789...HHLL
//  <---data--->
//  <--- szsize --->
//      where 123456789... is the data bytes
//            HH is the asciii hex representation of the hibyte of the 16 bit CRC
//            LL is the asciii hex representation of the lobyte of the 16 bit CRC
//PARAMETER: data is the pointer to the data
//           szsize is the packet size (including CRC)
//           hibyte is the pointer to the resultant calculated CRC high byte
//           lobyte is the pointer to the resultant calculated CRC low byte
//           readhibyte is the pointer CRC high byte (read)
//           readlobyte is the pointer CRC low byte  (read)
//------------------------------------------------------------------------------------------
int CRC16ascii_ok(unsigned char *data, int szsize, unsigned char *hibyte, unsigned char *lobyte, unsigned char *readhibyte, unsigned char *readlobyte)
{
	CRC_CCITT(data,  szsize-4, hibyte, lobyte);
	char temp[4];
	temp[2] = 0x0;
	temp[0] = data[szsize-4];
	temp[1] = data[szsize-3];
	*readhibyte = a2toh((unsigned char *)temp);
	temp[0] = data[szsize-2];
	temp[1] = data[szsize-1];
	*readlobyte = a2toh((unsigned char *)temp);
	return ((*lobyte==*readlobyte)&&(*hibyte==*readhibyte)) ;
}


void AddCRC16(char* pMsg, int szsize)
{
	unsigned char CRCHi=0;
	unsigned char CRCLo=0;
    CRC_CCITT((unsigned char*)pMsg,  szsize, &CRCHi, &CRCLo);
   *(pMsg+szsize) = CRCHi;
   *(pMsg+szsize+1) = CRCLo;
}



int crc_ccitt_ChksumNFail(char *buf, int szsize, unsigned char *crcHi, unsigned char *crcLo)
{
	unsigned char CRCHi;
	unsigned char CRCLo;
	char CRCstr[6];
	char *sptr;
 //	char *CRCptr;
	CRCHi=0xff;
	CRCLo=0xff;
	CRC_CCITT((unsigned char*)buf,  szsize, &CRCHi, &CRCLo);
	sprintf(CRCstr,"%02x%02x",CRCHi, CRCLo);
	CRCstr[0] = (char)toupper(CRCstr[0]);
	CRCstr[1] = (char)toupper(CRCstr[1]);
	CRCstr[2] = (char)toupper(CRCstr[2]);
	CRCstr[3] = (char)toupper(CRCstr[3]);
	sptr = buf+szsize;
	if (crcHi) *crcHi = CRCHi;
	if (crcLo) *crcLo = CRCLo;
	if (  (*sptr==CRCstr[0])&&
			(*(sptr+1)==CRCstr[1])&&
			(*(sptr+2)==CRCstr[2])&&
			(*(sptr+3)==CRCstr[3])
		)
		return 0;					//There is no CRC error
	return -3;						//There is CRC error
}


int xCRC_CCITTchksumNFail(char *buf, int szsize, unsigned char *crcHi, unsigned char *crcLo)
{
	unsigned char CRCHi;
	unsigned char CRCLo;
	char CRCstr[6];
	char *sptr;
 //	char *CRCptr;
	CRCHi=0xff;
	CRCLo=0xff;
	sptr = strchr(buf,'\r');
	if (sptr) *sptr = 0x0;
	sptr = strchr(buf,'\n');
	if (sptr) *sptr = 0x0;
	CRC_CCITT((unsigned char*)buf,  szsize, &CRCHi, &CRCLo);
	sprintf(CRCstr,"%02x%02x",CRCHi, CRCLo);
	CRCstr[0] = (char)toupper(CRCstr[0]);
	CRCstr[1] = (char)toupper(CRCstr[1]);
	CRCstr[2] = (char)toupper(CRCstr[2]);
	CRCstr[3] = (char)toupper(CRCstr[3]);
	sptr = buf+szsize;
	if (crcHi) *crcHi = CRCHi;
	if (crcLo) *crcLo = CRCLo;
	if (  (*sptr==CRCstr[0])&&
			(*(sptr+1)==CRCstr[1])&&
			(*(sptr+2)==CRCstr[2])&&
			(*(sptr+3)==CRCstr[3])
		)
		return 0;					//There is no CRC error
	return -3;						//There is CRC error
}

int x2CRC_CCITTchksumNFail(char *buf, int szsize, unsigned char *crcHi, unsigned char *crcLo)
{
	unsigned char CRCHi;
	unsigned char CRCLo;
	char CRCstr[6];
	char *sptr;
 //	char *CRCptr;
	CRCHi=0xff;
	CRCLo=0xff;
//	sptr = strchr(buf,'\r');
//	if (sptr) *sptr = 0x0;
//	sptr = strchr(buf,'\n');
//	if (sptr) *sptr = 0x0;
	CRC_CCITT((unsigned char*)buf,  szsize, &CRCHi, &CRCLo);
	sprintf(CRCstr,"%02x%02x",CRCHi, CRCLo);
	CRCstr[0] = (char)toupper(CRCstr[0]);
	CRCstr[1] = (char)toupper(CRCstr[1]);
	CRCstr[2] = (char)toupper(CRCstr[2]);
	CRCstr[3] = (char)toupper(CRCstr[3]);
	sptr = buf+szsize;
	if (crcHi) *crcHi = CRCHi;
	if (crcLo) *crcLo = CRCLo;
	if (  (*sptr==CRCstr[0])&&
			(*(sptr+1)==CRCstr[1])&&
			(*(sptr+2)==CRCstr[2])&&
			(*(sptr+3)==CRCstr[3])
		)
		return 0;					//There is no CRC error
	return -3;						//There is CRC error
}


//------------------------------------------------------------------------------
//format: $xxxxx..xxxxxxxxxcccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//return  0 if no error
//       -3 if no CRC fail check.
//------------------------------------------------------------------------------
int CRC_CCITTchksumFail(char *buf)
{
	return CRC_CCITTchksumNFail(buf, strlen(buf)-4);
}

/*
//------------------------------------------------------------------------------
//format: $xxxxx..xxxxxxxxxcccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//return  0 if no error
//       -3 if no CRC fail check.
//------------------------------------------------------------------------------
int CRC_CCITTchksumFail(char *buf)
{
	unsigned char CRCHi=0xff;
	unsigned char CRCLo =0xff;
//	unsigned long crc;
	char CRCstr[16];
	char *sptr;
	char *CRCptr;
	sptr = strchr(buf,'\r');
	if (sptr)
		*sptr = 0x0;
	sptr = strchr(buf,'\n');
	if (sptr)
		*sptr = 0x0;
	CRC_CCITT(buf,  strlen(buf)-4, &CRCHi, &CRCLo);
	sprintf(CRCstr,"%02x%02x",CRCHi, CRCLo);
	CRCptr = (buf + (strlen(buf)-4));
   strupr(CRCstr);
	if (strncmp(CRCstr,CRCptr,4)!=0)
		return -3;					//There is a CRC error
	return 0;						//There is no CRC error
}
*/

unsigned char calcChksum(unsigned char* pMsg,  int MsgLength)
{
	unsigned char crc;
	crc=0x0;
	while(MsgLength--)
		crc = crc+(unsigned char)(*pMsg++);
   return crc;
}


//-------------------------------------------------------------------------------------
//void AddCRC_CCITTchksum(char *buf)
//Add the CRC_CCITT checksum to the string pointed by buf
//format: $xxxxx..xxxxxxxxxcccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//    where xxx..xx is the string pointed by buf
//          cccc is the ASCII hex 16 bit checksum
//          <CR><LF> terminates the string after the checksum
//
//    The following are reserve characters that should not be used within the data string
//    <CR><LF> is the termination characters
//    $ is the start character of the statement
//    The CRC_CCITT calculation begins from $ right to the last character before a
//    'CR' or 'LF' or to the last character of the string.
//
//   input buf                             resultant buf
// $xxxxxxxxxxxxxxxx               $xxxxxxxxxxxxxxxxcccc<CR><LF>
// $xxxxxxxxxxxxxxxx<CR>           $xxxxxxxxxxxxxxxxcccc<CR><LF>
// $xxxxxxxxxxxxxxxx<LF>           $xxxxxxxxxxxxxxxxcccc<CR><LF>
//-------------------------------------------------------------------------------------
void AddCRC_SUM8chksum(char *buf)
{
	unsigned char crc;
	char CRCstr[16];
	char *sptr;
//	crc=0x0;
	sptr = strchr(buf,'\r');
	if (sptr)
		*sptr = 0x0;
	sptr = strchr(buf,'\n');
	if (sptr)
		*sptr = 0x0;
	crc = calcChksum((unsigned char *)buf, strlen(buf));
	sprintf(CRCstr,"%02x\r\n",crc);
   strupr(CRCstr);
   strcat(buf,CRCstr);
}


//------------------------------------------------------------------------------
//format: $xxxxx..xxxxxxxxxcccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//return  0 if no error
//       -3 if no CRC fail check.
//------------------------------------------------------------------------------
int CRC_SUM8chksumFail(char *buf)
{
	unsigned char crc;
	char CRCstr[16];
	char *sptr;
	char *CRCptr;
//	crc = 0x0;
	sptr = strchr(buf,'\r');
	if (sptr)
		*sptr = 0x0;
	sptr = strchr(buf,'\n');
	if (sptr)
		*sptr = 0x0;
	crc = calcChksum((unsigned char *)buf, strlen(buf)-2);
	sprintf(CRCstr,"%02x",crc);
	CRCptr = (buf + (strlen(buf)-2));
   strupr(CRCstr);
	if (strncmp(CRCstr,CRCptr,2)!=0)
		return -3;					//There is a CRC error
	return 0;						//There is no CRC error
}


unsigned long crc32tab[256] = {
  0x00000000U, 0x77073096U, 0xee0e612cU, 0x990951baU, 0x076dc419U,
  0x706af48fU, 0xe963a535U, 0x9e6495a3U, 0x0edb8832U, 0x79dcb8a4U,
  0xe0d5e91eU, 0x97d2d988U, 0x09b64c2bU, 0x7eb17cbdU, 0xe7b82d07U,
  0x90bf1d91U, 0x1db71064U, 0x6ab020f2U, 0xf3b97148U, 0x84be41deU,
  0x1adad47dU, 0x6ddde4ebU, 0xf4d4b551U, 0x83d385c7U, 0x136c9856U,
  0x646ba8c0U, 0xfd62f97aU, 0x8a65c9ecU, 0x14015c4fU, 0x63066cd9U,
  0xfa0f3d63U, 0x8d080df5U, 0x3b6e20c8U, 0x4c69105eU, 0xd56041e4U,
  0xa2677172U, 0x3c03e4d1U, 0x4b04d447U, 0xd20d85fdU, 0xa50ab56bU,
  0x35b5a8faU, 0x42b2986cU, 0xdbbbc9d6U, 0xacbcf940U, 0x32d86ce3U,
  0x45df5c75U, 0xdcd60dcfU, 0xabd13d59U, 0x26d930acU, 0x51de003aU,
  0xc8d75180U, 0xbfd06116U, 0x21b4f4b5U, 0x56b3c423U, 0xcfba9599U,
  0xb8bda50fU, 0x2802b89eU, 0x5f058808U, 0xc60cd9b2U, 0xb10be924U,
  0x2f6f7c87U, 0x58684c11U, 0xc1611dabU, 0xb6662d3dU, 0x76dc4190U,
  0x01db7106U, 0x98d220bcU, 0xefd5102aU, 0x71b18589U, 0x06b6b51fU,
  0x9fbfe4a5U, 0xe8b8d433U, 0x7807c9a2U, 0x0f00f934U, 0x9609a88eU,
  0xe10e9818U, 0x7f6a0dbbU, 0x086d3d2dU, 0x91646c97U, 0xe6635c01U,
  0x6b6b51f4U, 0x1c6c6162U, 0x856530d8U, 0xf262004eU, 0x6c0695edU,
  0x1b01a57bU, 0x8208f4c1U, 0xf50fc457U, 0x65b0d9c6U, 0x12b7e950U,
  0x8bbeb8eaU, 0xfcb9887cU, 0x62dd1ddfU, 0x15da2d49U, 0x8cd37cf3U,
  0xfbd44c65U, 0x4db26158U, 0x3ab551ceU, 0xa3bc0074U, 0xd4bb30e2U,
  0x4adfa541U, 0x3dd895d7U, 0xa4d1c46dU, 0xd3d6f4fbU, 0x4369e96aU,
  0x346ed9fcU, 0xad678846U, 0xda60b8d0U, 0x44042d73U, 0x33031de5U,
  0xaa0a4c5fU, 0xdd0d7cc9U, 0x5005713cU, 0x270241aaU, 0xbe0b1010U,
  0xc90c2086U, 0x5768b525U, 0x206f85b3U, 0xb966d409U, 0xce61e49fU,
  0x5edef90eU, 0x29d9c998U, 0xb0d09822U, 0xc7d7a8b4U, 0x59b33d17U,
  0x2eb40d81U, 0xb7bd5c3bU, 0xc0ba6cadU, 0xedb88320U, 0x9abfb3b6U,
  0x03b6e20cU, 0x74b1d29aU, 0xead54739U, 0x9dd277afU, 0x04db2615U,
  0x73dc1683U, 0xe3630b12U, 0x94643b84U, 0x0d6d6a3eU, 0x7a6a5aa8U,
  0xe40ecf0bU, 0x9309ff9dU, 0x0a00ae27U, 0x7d079eb1U, 0xf00f9344U,
  0x8708a3d2U, 0x1e01f268U, 0x6906c2feU, 0xf762575dU, 0x806567cbU,
  0x196c3671U, 0x6e6b06e7U, 0xfed41b76U, 0x89d32be0U, 0x10da7a5aU,
  0x67dd4accU, 0xf9b9df6fU, 0x8ebeeff9U, 0x17b7be43U, 0x60b08ed5U,
  0xd6d6a3e8U, 0xa1d1937eU, 0x38d8c2c4U, 0x4fdff252U, 0xd1bb67f1U,
  0xa6bc5767U, 0x3fb506ddU, 0x48b2364bU, 0xd80d2bdaU, 0xaf0a1b4cU,
  0x36034af6U, 0x41047a60U, 0xdf60efc3U, 0xa867df55U, 0x316e8eefU,
  0x4669be79U, 0xcb61b38cU, 0xbc66831aU, 0x256fd2a0U, 0x5268e236U,
  0xcc0c7795U, 0xbb0b4703U, 0x220216b9U, 0x5505262fU, 0xc5ba3bbeU,
  0xb2bd0b28U, 0x2bb45a92U, 0x5cb36a04U, 0xc2d7ffa7U, 0xb5d0cf31U,
  0x2cd99e8bU, 0x5bdeae1dU, 0x9b64c2b0U, 0xec63f226U, 0x756aa39cU,
  0x026d930aU, 0x9c0906a9U, 0xeb0e363fU, 0x72076785U, 0x05005713U,
  0x95bf4a82U, 0xe2b87a14U, 0x7bb12baeU, 0x0cb61b38U, 0x92d28e9bU,
  0xe5d5be0dU, 0x7cdcefb7U, 0x0bdbdf21U, 0x86d3d2d4U, 0xf1d4e242U,
  0x68ddb3f8U, 0x1fda836eU, 0x81be16cdU, 0xf6b9265bU, 0x6fb077e1U,
  0x18b74777U, 0x88085ae6U, 0xff0f6a70U, 0x66063bcaU, 0x11010b5cU,
  0x8f659effU, 0xf862ae69U, 0x616bffd3U, 0x166ccf45U, 0xa00ae278U,
  0xd70dd2eeU, 0x4e048354U, 0x3903b3c2U, 0xa7672661U, 0xd06016f7U,
  0x4969474dU, 0x3e6e77dbU, 0xaed16a4aU, 0xd9d65adcU, 0x40df0b66U,
  0x37d83bf0U, 0xa9bcae53U, 0xdebb9ec5U, 0x47b2cf7fU, 0x30b5ffe9U,
  0xbdbdf21cU, 0xcabac28aU, 0x53b39330U, 0x24b4a3a6U, 0xbad03605U,
  0xcdd70693U, 0x54de5729U, 0x23d967bfU, 0xb3667a2eU, 0xc4614ab8U,
  0x5d681b02U, 0x2a6f2b94U, 0xb40bbe37U, 0xc30c8ea1U, 0x5a05df1bU,
  0x2d02ef8dU
};

unsigned long calcCRC32(char *buf, unsigned len)
// Calculate a 32-bit CRC for a raw pattern of bytes.
// Returns a 32-bit checksum.
{
	unsigned long CRC;
	unsigned int n;
	n = len;
	CRC=0xffffffffL;
	while(n--)
   	CRC=crc32tab[(int)(CRC ^ (*buf++)) & 0xFF] ^ ((CRC>>8) & 0x00ffffffL);
	return CRC ^ 0xffffffffL;
}


//-------------------------------------------------------------------------------------
//void AddCRC32chksum(char *buf)
//Add the CRC32 checksum to the string pointed by buf
//format: $xxxxx..xxxxxxxxx*cccccccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//    where xxx..xx is the string pointed by buf
//          * is the indentifier preceeding the checksum
//          cccccccc is the ASCII hex 32 bit checksum
//          <CR><LF> terminates the string after the checksum
//
//    The following are reserve characters that should not be used within the data string
//    * is a reserve character for indication that the statement has a checksum
//    and the preceding 4 bytes is the checksum.
//    <CR><LF> is the termination characters
//    $ is the start character of the statement
//    The CRC32 calculation begins from $ right to the last character before a
//    '*', 'CR' or 'LF' or to the last character of the string.
//
//   input buf                             resultant buf
// $xxxxxxxxxxxxxxxx*              $xxxxxxxxxxxxxxxx*cccccccc<CR><LF>
// $xxxxxxxxxxxxxxxx<CR>           $xxxxxxxxxxxxxxxx*cccccccc<CR><LF>
// $xxxxxxxxxxxxxxxx<LF>           $xxxxxxxxxxxxxxxx*cccccccc<CR><LF>
// $xxxxxxxxxxxxxxxx               $xxxxxxxxxxxxxxxx*cccccccc<CR><LF>
//-------------------------------------------------------------------------------------
void AddCRC32chksum(char *buf)
{
	unsigned long crc;
	char CRCstr[16];
	char *sptr;
	sptr = strchr(buf,'*');
	if (sptr)
		*sptr = 0x0;
	sptr = strchr(buf,'\r');
	if (sptr)
		*sptr = 0x0;
	sptr = strchr(buf,'\n');
	if (sptr)
		*sptr = 0x0;
	crc = calcCRC32(buf, strlen(buf));
//	sprintf(CRCstr,"*%04x%04x",(int)(crc>>16), (int)(crc&0xFFFF));
	sprintf(CRCstr,"*%08lx\r\n",crc);
//	sprintf(CRCstr,"*%08x\r\n",(unsigned long)crc);
	strupr(CRCstr);
	strcat(buf,CRCstr);
}


//------------------------------------------------------------------------------
//format: $xxxxx..xxxxxxxxx*cccccccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//return  0 if no error
//       -1 if no '*'
//       -2 if no <CR>
//       -3 if no CRC fail check.
//------------------------------------------------------------------------------
int CRC32chksumFail(char *buf)
{
	unsigned long crc;
	char CRCstr[16];
	char *sptr;
	char *CRCptr;
	sptr = strchr(buf,'*');
	if (!sptr)
		return -1;					//no need to check further. There is an error
	if (*(sptr+9)!='\r')
		return -2;					//no need to check further. There is an error
	CRCptr = sptr+1;
	*sptr = 0x0;
	crc = calcCRC32(buf, strlen(buf));
//	sprintf(CRCstr,"%04x%04x",(int)(crc>>16), (int)(crc&0xFFFF));
	sprintf(CRCstr,"%08lx",crc);
   strupr(CRCstr);
	if (strncmp(CRCstr,CRCptr,8)!=0)
		return -3;					//There is a CRC error
	return 0;						//There is no CRC error
}

//-------------------------------------------------------------------------------------
//void AddCRC_CCITTchksum(char *buf)
//Add the CRC_CCITT checksum to the string pointed by buf
//format: $xxxxx..xxxxxxxxxcccc<CR><LF>
//        |<------------->| inclusive are characters used to calc the checksum
//    where xxx..xx is the string pointed by buf
//          cccc is the ASCII hex 16 bit checksum
//          <CR><LF> terminates the string after the checksum
//
//    The following are reserve characters that should not be used within the data string
//    <CR><LF> is the termination characters
//    $ is the start character of the statement
//    The CRC_CCITT calculation begins from $ right to the last character before a
//    'CR' or 'LF' or to the last character of the string.
//
//   input buf                             resultant buf
// $xxxxxxxxxxxxxxxx               $xxxxxxxxxxxxxxxxcccc<CR><LF>
// $xxxxxxxxxxxxxxxx<CR>           $xxxxxxxxxxxxxxxxcccc<CR><LF>
// $xxxxxxxxxxxxxxxx<LF>           $xxxxxxxxxxxxxxxxcccc<CR><LF>
//-------------------------------------------------------------------------------------
/*** BeginHeader x1AddCRC_CCITTchksum */
//void x1AddCRC_CCITTchksum(char *buf, int szsize);
/*** EndHeader */
//xmem nodebug speed nouseix
void x1AddCRC_CCITTchksum(char *buf, int szsize)
{
	unsigned char CRCHi=0;
	unsigned char CRCLo=0;
	char CRCstr[16];
	CRC_CCITT((unsigned char *)buf,  szsize, &CRCHi, &CRCLo);
	sprintf(CRCstr,"%02x%02x", CRCHi, CRCLo);
	*(buf+szsize)   = toupper(CRCstr[0]);
	*(buf+szsize+1) = toupper(CRCstr[1]);
	*(buf+szsize+2) = toupper(CRCstr[2]);
	*(buf+szsize+3) = toupper(CRCstr[3]);
	*(buf+szsize+4) = 0;
}

void CRC_CCITT(unsigned char* pMsg,  int MsgLength, unsigned char *Hi, unsigned char *Lo)
{
	unsigned char CRCHi;
	unsigned char CRCLo;
	unsigned int Index;
   int ii;
	CRCHi=0xff;
	CRCLo =0xff;
   if (MsgLength<=0)
   	return;
	for (ii=0;ii<MsgLength;ii++){
		Index =CRCHi^*pMsg++;
		CRCHi =CRCLo^auchCRCHi[Index];
		CRCLo =auchCRCLo[Index];
		}
	*Hi = CRCHi;
	*Lo = CRCLo;
}
