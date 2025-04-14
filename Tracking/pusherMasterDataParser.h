#ifndef PUSHERMASTERDATAPARSER_H_INCLUDED
#define PUSHERMASTERDATAPARSER_H_INCLUDED
#include "stateM.h"
enum{
		MSGpshID = 0,
		MSGpshCMD,
		MSGpshMSG0,
		MSGpshMSG1,
		MSGpshMSG2,
		MSGpshMSG3,
		MSGpshMSG4,
		MSGpshMSG5,
		MSGpshMSG6,
		MSGpshMSG7,
		MSGpshChksum,
		MSGpshEOD,
		__MSGpsh___MAXSIZE
};
/*
*/
//#include "stateM.h"
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//This is a state machine structure to hold the packet decoding information during
//decoding. The structure also serves as the final decoded packet storage area
//(packet is stored in the element ".data")
//------------------------------------------------------------------------------------
typedef struct {
	unsigned char delimiter0;	 		//delimiter start of packet (id Sync)
	unsigned char delimiter1;	 		//delimiter start of packet (id Sync)
    unsigned char delimiter2;	 		//delimiter start of packet (id Sync)
	int state;								//state of the decoding 0,1,2,3.... starting at delimiter (also indicates the char position)
    int pktSize;							//size of packet from delimiter to end
    unsigned short dlength;	  			//length of contained data in the packet plus the port prefix and device number (i.e. n + plus 2bytes)
    int length;	  			            //length of contained data in the packet plus the port prefix and device number (i.e. n + plus 2bytes)
    int status;								//is the decoding status (PKT_ACQUIRING, PKT_FOUND,... one of the enum or define types)
	unsigned char *databuffer;	//this is where the data packet the is acquired is stored
    int databuffersize;
    int error;
    unsigned char portprefix;
    unsigned char port;
    unsigned char *dataptr;
    int lnoffset;
    //unsigned char *ptr;
}structMPushercommType;

//extern const unsigned char mPsh_1sync;
//extern const unsigned char mPsh_2sync;

extern int FindMPushercommStatement(char *data, int szsize, structMPushercommType *uState, char **endstr);
extern void MPushercommStateMachine(unsigned char ch, structMPushercommType *uState);
extern void MPushercommresetState(structMPushercommType *uState, int state);


extern unsigned char pusherMdataBuffer[16];
extern structMPushercommType MPushercomm;
#endif // PUSHERMASTERDATAPARSER_H_INCLUDED
