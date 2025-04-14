//StationMasterDataParser
#ifndef STATIONMASTERDATAPARSER_H_INCLUDED
#define STATIONMASTERDATAPARSER_H_INCLUDED




#define PKT_ABORT					1200			//packet is aborted due to some un explain errors
#define PKT_ACQUIRING				1201			//packet is in process being acquire or acquiring
#define PKT_FOUND					1202			//packet is found and process and acquire is complete
#define PKT_CRCERROR				1203
#define PKT_MAXLIMIT				1204			//packet is found to have exceed the limit packet buffer limit
#define PKT_FINDINGHDR				1205			//find of header
//#include "stateM.h"
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//This is a state machine structure to hold the packet decoding information during
//decoding. The structure also serves as the final decoded packet storage area
//(packet is stored in the element ".data")
//------------------------------------------------------------------------------------
typedef struct {
	unsigned char delimiter0;	 		//delimiter start of packet (id Sync)
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
}structMStationcommType;


extern int FindMStationcommStatement(char *data, int szsize, structMStationcommType *uState, char **endstr);
extern void MStationcommStateMachine(unsigned char ch, structMStationcommType *uState);
extern void MStationcommresetState(structMStationcommType *uState, int state);


extern unsigned char StationMdataBuffer[13];
extern structMStationcommType MStationcomm;



#endif // StationMASTERDATAPARSER_H_INCLUDED
