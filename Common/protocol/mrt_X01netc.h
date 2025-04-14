#if !defined(__mrt_X01netc_h)              // Sentry, use file only if it's not already included.
#define __mrt_X01netc_h

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
    unsigned char portXnet_cmd;
    unsigned char port;
    unsigned char *dataptr;
	unsigned char ipv4_1;
	unsigned char ipv4_2;
	unsigned char ipv4_3;
	unsigned char ipv4_4;
	unsigned short ipv4_port;
	unsigned char deviceprefix;			
	unsigned char device;
	unsigned char pktseq;

	int payloadleft;
	//int lnoffset;
    //unsigned char *ptr;
}structmrt_X01netcType;

extern const unsigned char netc16_1sync;
extern const unsigned char netc16_2sync;
extern const unsigned char netc16_3sync;
extern int wrapmrt_Xnetc(const unsigned char *data, unsigned short szsize, unsigned char *netcdata, unsigned char pktseq);
//extern int Findmrt_XnetcStatement(char *data, int szsize, structmrt_X01netcType *uState, char **endstr);
extern void mrt_XnetcStateMachine(unsigned char ch, structmrt_X01netcType *uState);
extern void mrt_XnetcresetState(structmrt_X01netcType *uState, int state);

#endif


