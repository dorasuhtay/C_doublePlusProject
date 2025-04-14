#include "StdAfx.h"
#include <stdio.h>
#include <string.h>
#include "debug_test_function.h"
#include "StationMasterDataParser.h"
#include "wctString.h"
#include "offlineCommandClass.h"
#include "xplatform_define.h"
#include "serialnetwork_func.h"

using namespace System;
/*
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
}*/
/*
class offlineCommandClass{
private:
	unsigned char pkt1[8];
	unsigned char pkt2[8];
	int byteCounter;
	char offlintext[256];
public:
	offlineCommandClass()
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
	~offlineCommandClass()
	{
	}
	void reset(){byteCounter=0;}
	void next(){byteCounter++; byteCounter=byteCounter%2;}
	int isComplete(); {return byteCounter;}
	void setbyte(unsigned char *pkt)
	{
		if (byteCounter==0)
			memcpy(pkt1, pkt, 8);
		else
			memcpy(pkt2, pkt, 8);
	}
	const char *getofflineText()
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
	}
	bool isStationOffline(int stnid)
	{
		if ((stnid>=0)&&(stnid<=128))
			return (offlintext[stnid]=='0');
		return 1;
	}
};
*/


void debug_run_offline_decode_Test()
{
	int ii;
	char out[256];
	unsigned char offline_byte1[8] = {0x9E,0x07,0x00,0x00,0x00,0x00,0x00,0x00};
	unsigned char offline_byte2[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	offlineCommandClass *offlineCommand = new offlineCommandClass();
	offlineCommand->reset();
	offlineCommand->setbyte(offline_byte1);
	offlineCommand->next();
	offlineCommand->setbyte(offline_byte2);
	SPRINTF(out, "%s", offlineCommand->getofflineText());
	FILE *fp=fopen("station.txt", "w+t");
	for(ii=0;ii<16;ii++)
	{
		if(offlineCommand->isStationOffline(ii))
			SPRINTF(out, "station#%02d:OFF\r\n", ii);
		else
			SPRINTF(out, "station#%02d:ON\r\n", ii);
		fprintf(fp, "%s", out);
	}
	fclose(fp);
	delete offlineCommand;


/*
	char bytetext[9];
	out[0] = 0x0;
	for (ii=0;ii<8;ii++)
	{
		byte2Binary(offline_byte1[ii], bytetext);
		strrev(bytetext);
		strcat(out, bytetext);
	}
	for (ii=0;ii<8;ii++)
	{
		byte2Binary(offline_byte2[ii], bytetext);
		strrev(bytetext);
		strcat(out, bytetext);
	}

	unsigned char val = offline_byte1[0];
	*/
	/*
	int len = 8;
	char *str = out;
	*(str + len) = 0;
	while(len--)
	{
	    if (0x01 & val)
            *(str + len) = '1';
        else
            *(str + len) = '0';
		val >>= 1;
	}


	char buf[64];
	wctString wstr;
	wstr = L"";
	ii = 0;
	wstr.appendBinary(offline_byte1[ii]);
	memcpy(out, wstr.data(buf, 8), 8);
	out[8] = 0x00;
	*/
}


void debug_run_StationDataParserTest()
{
	const unsigned char testStationData1[] = {0x05, 0x0a, 0x37, 0x30, 0x30, 0x45, 0x32, 0x34, 0x39, 0x45, 0x46, 0xe6, 0x0a};
	unsigned char StationPacket[16];
	for(int ii=0;ii<13;ii++)
	{
			//-------------------------------------
			//Checking of Master Data packet
			//-------------------------------------
			MStationcommStateMachine(testStationData1[ii], &MStationcomm);
			switch (MStationcomm.status)
			{
				case    PKT_FOUND:
						if (MStationcomm.pktSize==13)
						{
							memcpy(StationPacket, MStationcomm.dataptr, (MStationcomm.dlength));
							StationPacket[MStationcomm.dlength] = 0x0;
						}
						MStationcommresetState(&MStationcomm, 0);
						break;
				case	PKT_CRCERROR:
				case	PKT_ABORT:MStationcommresetState(&MStationcomm, 0);
						break;
				case	PKT_ACQUIRING:
				default:break;
			}
	}
}

/*
int calculate_Checksum(const unsigned char *data, int size)
{
	int ii, checksum_temp ;
	unsigned char sum = 0;
	for (ii=0;ii<size;ii++)
		sum += data[ii];
	checksum_temp = 2550 - sum;	
	return checksum_temp&0xFF;

#ifdef USING_OLD_CHECKSUM
	int ii, checksum_temp ;
	unsigned char sum = 0;
	for (ii=0;ii<size;ii++)
		sum += data[ii];
	checksum_temp = Convert::ToInt32(2550 - sum);	
	String ^chking = checksum_temp.ToString("X");
	String ^str = chking->Substring(chking->Length-2);
	return Int32::Parse(str, System::Globalization::NumberStyles::HexNumber);
#endif
}
*/

void debug_run_calculate_CheckSum_Test()
{
	const unsigned char testStationData[] = {0x0a, 0x37, 0x30, 0x30, 0x45, 0x32, 0x34, 0x39, 0x45, 0x46, 0xe6, 0x0a};
	int chks = calculate_StationPacketChecksum(testStationData, 10);
	if(chks == testStationData[MSG_stnChksum])
	{
		unsigned char cmd = testStationData[MSG_stnCMD];
		if((cmd != 0x6F)&&(cmd != 0x70)&&(cmd != 0xE7)&&(cmd != 0x49)&&(cmd != 0x0D))
		{
			char testDatstr[16];
			memcpy(testDatstr, testStationData+MSG_stnMSG0, 8);
			testDatstr[8] = 0x0;
			String ^HangerID = gcnew String(reinterpret_cast<const char*>(testDatstr));
			int decValue1 = testStationData[MSG_stnMSG0];
/*
							int decValue1 = testStationData[MSGstnMSG0];
							int decValue2 = testStationData[MSGstnMSG1];
							int decValue3 = testStationData[MSGstnMSG2];
							int decValue4 = testStationData[MSGstnMSG3];
							int decValue5 = testStationData[MSGstnMSG4];
							int decValue6 = testStationData[MSGstnMSG5];
							int decValue7 = testStationData[MSGstnMSG6];
							int decValue8 = testStationData[MSGstnMSG7];
							int decValue9 = testStationData[MSGstnChksum];

							String ^hexValue1 = decValue1.ToString("X");
							String ^hexValue2 = decValue2.ToString("X");
							String ^hexValue3 = decValue3.ToString("X");
							String ^hexValue4 = decValue4.ToString("X");
							String ^hexValue5 = decValue5.ToString("X");
							String ^hexValue6 = decValue6.ToString("X");
							String ^hexValue7 = decValue7.ToString("X");
							String ^hexValue8 = decValue8.ToString("X");
							String ^hexValue9 = decValue9.ToString("X");

							//HangerID = Convert::ToChar(hexValue1->Substring(0,1)).ToString();// + Convert::ToChar(hexValue2->Substring(0,1)).ToString()+Convert::ToChar(hexValue3->Substring(0,1)).ToString()+Convert::ToChar(hexValue4->Substring(0,1)).ToString()+
									//Convert::ToChar(hexValue5->Substring(0,1)).ToString() + Convert::ToChar(hexValue6->Substring(0,1)).ToString() + Convert::ToChar(hexValue7->Substring(0,1)).ToString()+Convert::ToChar(hexValue8->Substring(0,1)).ToString(); 
							StringBuilder ^sb1 = gcnew StringBuilder();
							StringBuilder ^sb2 = gcnew StringBuilder();
							StringBuilder ^sb3 = gcnew StringBuilder();
							StringBuilder ^sb4 = gcnew StringBuilder();
							StringBuilder ^sb5 = gcnew StringBuilder();
							StringBuilder ^sb6 = gcnew StringBuilder();
							StringBuilder ^sb7 = gcnew StringBuilder();
							StringBuilder ^sb8 = gcnew StringBuilder();
							StringBuilder ^sb9 = gcnew StringBuilder();
						
							for (int i = 0; i <= hexValue1->Length - 2; i += 2)
								sb1->Append(Convert::ToString(Convert::ToChar(Int32::Parse(hexValue1->Substring(i, 2), System::Globalization::NumberStyles::HexNumber))));

							for (int i = 0; i <= hexValue2->Length - 2; i += 2)
								sb2->Append(Convert::ToString(Convert::ToChar(Int32::Parse(hexValue2->Substring(i, 2), System::Globalization::NumberStyles::HexNumber))));

							for (int i = 0; i <= hexValue3->Length - 2; i += 2)
								sb3->Append(Convert::ToString(Convert::ToChar(Int32::Parse(hexValue3->Substring(i, 2), System::Globalization::NumberStyles::HexNumber))));

							for (int i = 0; i <= hexValue4->Length - 2; i += 2)
								sb4->Append(Convert::ToString(Convert::ToChar(Int32::Parse(hexValue4->Substring(i, 2), System::Globalization::NumberStyles::HexNumber))));

							for (int i = 0; i <= hexValue5->Length - 2; i += 2)
								sb5->Append(Convert::ToString(Convert::ToChar(Int32::Parse(hexValue5->Substring(i, 2), System::Globalization::NumberStyles::HexNumber))));

							for (int i = 0; i <= hexValue6->Length - 2; i += 2)
								sb6->Append(Convert::ToString(Convert::ToChar(Int32::Parse(hexValue6->Substring(i, 2), System::Globalization::NumberStyles::HexNumber))));

							for (int i = 0; i <= hexValue7->Length - 2; i += 2)
								sb7->Append(Convert::ToString(Convert::ToChar(Int32::Parse(hexValue7->Substring(i, 2), System::Globalization::NumberStyles::HexNumber))));

							for (int i = 0; i <= hexValue8->Length - 2; i += 2)
								sb8->Append(Convert::ToString(Convert::ToChar(Int32::Parse(hexValue8->Substring(i, 2), System::Globalization::NumberStyles::HexNumber))));
								

							HangerID = sb1->ToString() + sb2->ToString() + sb3->ToString() + sb4->ToString() + sb5->ToString() + sb6->ToString() + sb7->ToString() + sb8->ToString(); 
							printf("");
							*/
									//WriteToSerial(stationNetwork_port, MasterID,0xE7,"Valid"); // reply ack 
		}
	}
	else
	{
		//WriteToSerial(stationNetwork_port, MasterID,0xE6,"CS_Error");
	}
}