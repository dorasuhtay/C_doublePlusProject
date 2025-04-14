#ifndef __serialnetwork_func__H
#define __serialnetwork_func__H

#include "class_stationMsgFifo.h"

using namespace System;

enum{
		MSG_stnID = 0,
		MSG_stnCMD,
		MSG_stnMSG0,
		MSG_stnMSG1,
		MSG_stnMSG2,
		MSG_stnMSG3,
		MSG_stnMSG4,
		MSG_stnMSG5,
		MSG_stnMSG6,
		MSG_stnMSG7,
		MSG_stnChksum,
		MSG_stnEOD,
		__MSG_stn___MAXSIZE
};

extern int calculate_StationPacketChecksum(const unsigned char *data, int size);
extern int MakeStrSerialNetworkHardwarePacket(int STNID,int command, String ^Msg, unsigned char *out);
extern void MakeStrSerialNetworkHardwarePacket(int STNID,int command, array<Byte> ^Bytecode, unsigned char *out);
extern int WriteStrToSerialNetworkFifo(class_stationMsgFifo *fifo, int STNID,int command, String ^data);
extern int WriteArryByteToSerialNetworkFifo(class_stationMsgFifo *fifo, int STNID,int command, array<Byte> ^Bytecode);

#endif