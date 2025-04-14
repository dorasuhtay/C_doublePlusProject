#ifndef __A60735_fileType__H
#define __A60735_fileType__H



#include "stateM.h"
//------------------------------------------------------------------------------------
//MXComm is an internal defined wrapper
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
    unsigned short dlength;	  			//length of contained data in the packet plus the port Xnet_cmd and device number (i.e. n + plus 2bytes)
    int length;	  			            //length of contained data in the packet plus the port Xnet_cmd and device number (i.e. n + plus 2bytes)
    int status;								//is the decoding status (PKT_ACQUIRING, PKT_FOUND,... one of the enum or define types)
	unsigned char *databuffer;	//this is where the data packet the is acquired is stored
    int databuffersize;
    int error;
    unsigned char dtype;
    unsigned char port;
    unsigned char *dataptr;
	unsigned int seqno;
	unsigned int lapse;
	unsigned short ipv4_port;
	unsigned char deviceprefix;			
	unsigned char device;
	unsigned char pktseq;

	unsigned char spare1;
	unsigned char spare2;
	unsigned char spare3;
	unsigned char spare4;
	unsigned char spare5;
	unsigned char spare6;
	unsigned char spare7;
	unsigned char spare8;
	unsigned char spare9;
	unsigned char spare10;

	int payloadleft;
	//int lnoffset;
    //unsigned char *ptr;
}structA60735_fileType;

extern const unsigned char A60735_1sync;
extern const unsigned char A60735_2sync;
extern const unsigned char A60735_3sync;
extern int wrapmrt_A60735(const unsigned char *payload, unsigned short szsize, unsigned char *transport, unsigned char type, int lapse, unsigned short seqNo);
//extern int Findmrt_A60735Statement(char *data, int szsize, structA60735_fileType *uState, char **endstr);
extern void A60735StateMachine(unsigned char ch, structA60735_fileType *uState);
extern void A60735resetState(structA60735_fileType *uState, int state);



#endif