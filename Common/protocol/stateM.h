#if !defined(__stateM_h)              // Sentry, use file only if it's not already included.
#define __stateM_h

#define PKT_ABORT					1200			//packet is aborted due to some un explain errors
#define PKT_ACQUIRING				1201			//packet is in process being acquire or acquiring
#define PKT_FOUND					1202			//packet is found and process and acquire is complete
#define PKT_CRCERROR				1203
#define PKT_MAXLIMIT				1204			//packet is found to have exceed the limit packet buffer limit
#define PKT_FINDINGHDR				1205			//find of header
/*
#define PKT_ABORT					1500			//packet is aborted due to some un explain errors
#define PKT_ACQUIRING			1501			//packet is in process being acquire or acquiring
#define PKT_FOUND					1502			//packet is found and process and acquire is complete
#define PKT_CRCERROR				1503
#define PKT_MAXLIMIT				1504			//packet is found to have exceed the limit packet buffer limit
#define PKT_FINDINGHDR			1505			//find of header

//#define MAXSTATEDATAPACKETSIZE	79
#define MAXSTATEDATAPACKETSIZE	300
struct structPacketState{
	int state;
   int error;
   char data[MAXSTATEDATAPACKETSIZE+1];
   char *dataptr;
   char *CRCstr;
//   long id;
   int status;								//is the decoding status (PKT_ACQUIRING, PKT_FOUND,...)
   int channel;
   char PktNum;
   char length;
   char length_inv;
	int finalState;
   int pktSize;
   int tempPtr;
   unsigned char crchi, crclo;
   char SrcDest;
   char SrcDest_inv;
   int src;
   int dst;
	};

extern void resetState(struct structPacketState *uState);
*/
#endif
