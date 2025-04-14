#include "StdAfx.h"
//#include <vcclr.h>
//#include <stdio.h>
//#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include "mrt_X01PayloadParser.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

mrt_X01PayloadParser::mrt_X01PayloadParser()
{
	mrt_X01 = new structmrt_X01netcType;
	memset(mrt_X01, 0x0, sizeof(structmrt_X01netcType));
	mrt_X01->delimiter0 = netc16_1sync;
	mrt_X01->delimiter1 = netc16_2sync;
	mrt_X01->delimiter2 = netc16_3sync;
	mrt_X01->databuffersize = 128;
	mrt_X01->databuffer = (unsigned char *)malloc(mrt_X01->databuffersize+1);
	payload = 0;
}

mrt_X01PayloadParser::~mrt_X01PayloadParser()
{
	if (mrt_X01)
	{
		if (mrt_X01->databuffer)
			free(mrt_X01->databuffer);
		SAFE_DELETE(mrt_X01);
	}
	SAFE_DELETE(payload);
}

int mrt_X01PayloadParser::parsePacket(unsigned char ch)
{
			int nn = 0;
			//char testbuf[128];
				mrt_XnetcStateMachine(ch, mrt_X01);
                switch (mrt_X01->status)
                {
                    case    PKT_FOUND:
							SAFE_DELETE(payload);
							payload = new unsigned char[mrt_X01->length+2];
							memcpy(payload, mrt_X01->dataptr, mrt_X01->length);
							payload[mrt_X01->length] = 0x0;
							/*
							sprintf(testData, "%s  [%c][%d][%d.%d.%d.%d %d][%c%d]\r\n", 
												payload, mrt_X01->portXnet_cmd, mrt_X01->port,
												mrt_X01->ipv4_1,
												mrt_X01->ipv4_2,
												mrt_X01->ipv4_3,
												mrt_X01->ipv4_4,
												mrt_X01->ipv4_port,
												mrt_X01->deviceprefix,			
												mrt_X01->device
												);

							mrt_X01->dataptr[mrt_X01->length] = 0x0;
							if (strcmp((char *)mrt_X01->dataptr, "status")==0)
							{
								if (hostname_table)
									hostname_table->setconnectionstatus(hostnameIndex, "ok", 0);
								CloseclientSocket();
							}
							if (strcmp((char *)mrt_X01->dataptr, "verifed")==0)
							{
								if (hostname_table)
									hostname_table->setconnectionstatus(hostnameIndex, "OK", 0);
							}
							*/
							//testData[mrt_X01->length] = 0x0;
							nn = 1;
                            mrt_XnetcresetState(mrt_X01, 0);
                            break;
                    case	PKT_CRCERROR:
                    case	PKT_ABORT:mrt_XnetcresetState(mrt_X01, 0);
                            break;
                    case	PKT_ACQUIRING:
                    default:break;
                }
				return nn;
		}
