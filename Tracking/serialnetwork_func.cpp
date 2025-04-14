#include "StdAfx.h"
#include <string.h>
#include "serialnetwork_func.h"
#include "class_stationMsgFifo.h"


int calculate_StationPacketChecksum(const unsigned char *data, int size)
{
	int ii, checksum_temp ;
	unsigned char sum = 0;
	for (ii=0;ii<size;ii++)
		sum += data[ii];
	checksum_temp = 2550 - sum;	
	return checksum_temp&0xFF;
}

//#david20121029-00...
int MakeStrSerialNetworkHardwarePacket(int STNID,int command, String ^Msg, unsigned char *out)
{
	int ii;
	memset(out, 0x0, __MSG_stn___MAXSIZE+1);
	String ^szTmp = Msg->ToString()->PadLeft(8, ' '); //ensure the data is 7 bytes
	unsigned char *sptr = out;
	*sptr++ = 0x05;							//packet header SYNC
	*sptr++ = (unsigned char)STNID;			//packet Station ID number
	*sptr++ = (unsigned char)command;		//packet Command number
	for (ii=0;ii<8;ii++)					//data message 8 bytes
		*sptr++ = (unsigned char)szTmp[ii];	
	//--------------------------------------------
	//calculate checksum and send out packet
	//--------------------------------------------
	int chks = calculate_StationPacketChecksum(out+1, MSG_stnChksum+1);		//calculate chksum
	*sptr++ = chks;																//packet checksum
	*sptr = 0x0a;	//EOT character
	return __MSG_stn___MAXSIZE+1;
}

//-----------------------------------------------------------------------
//write UPSsys formatted data packet "payload" array<Byte> type data to 
//Serialport directly or via FIFO
//This function write UPSsys formatted data packet.
//stn_id  --- Station ID (remote unit address)
//command --- UPSsysNW232 PROTOCOL command
//payload --- the 8 byte of payload data (MUST ALWAYS BE 8 bytes)
//out ------- pointer to an output buffer
//-----------------------------------------------------------------------
void MakeStrSerialNetworkHardwarePacket(int stn_id,int command, array<Byte> ^payload, unsigned char *out)
{
	int ii;
	memset(out, 0x0, __MSG_stn___MAXSIZE+1);
	unsigned char *sptr = out;
	*sptr++ = 0x05;							//packet header SYNC
	*sptr++ = (unsigned char)stn_id;			//packet Station ID number
	*sptr++ = (unsigned char)command;		//packet Command number
	for (ii=0;ii<8;ii++)					//data message 8 bytes
	{
		if (ii>=payload->Length)
			*sptr = 'X';
		else
			*sptr = (unsigned char)payload[ii];	
		sptr++;
	}
	//--------------------------------------------
	//calculate checksum and send out packet
	//--------------------------------------------
	int chks = calculate_StationPacketChecksum(out+1, MSG_stnChksum+1);		//calculate chksum
	*sptr++ = chks;																//packet checksum
	*sptr = 0x0a;	//EOT character
}
//...#david20121029-00


//#david20121029-00...
int WriteStrToSerialNetworkFifo(class_stationMsgFifo *fifo, int STNID,int command, String ^data)
{
	if (fifo)
	{
		unsigned char obuf[__MSG_stn___MAXSIZE+1];
		MakeStrSerialNetworkHardwarePacket(STNID, command, data, obuf);
		return fifo->put(obuf);
	}
	return 0;
}
/*
int WriteArryByteToSerialNetworkFifo(class_stationMsgFifo *fifo, int STNID,int command, array<Byte> ^Bytecode)
{
	if (fifo)
	{
		unsigned char obuf[__MSG_stn___MAXSIZE+1];
		MakeStrSerialNetworkHardwarePacket(STNID, command, Bytecode, obuf);
		return fifo->put(obuf);
	}
	return 0;
}
*/


 
//...#david20121029-00