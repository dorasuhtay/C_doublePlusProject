#ifndef __isocketping__H
#define __isocketping__H

#include <windows.h>
//#include <WinSock2.h>
// 
// IP header structure
//
typedef struct _iphdr 
{
    unsigned int   h_len:4;        // Length of the header
    unsigned int   version:4;      // Version of IP
    unsigned char  tos;            // Type of service
    unsigned short total_len;      // Total length of the packet
    unsigned short ident;          // Unique identifier
    unsigned short frag_and_flags; // Flags
    unsigned char  ttl;            // Time to live
    unsigned char  proto;          // Protocol (TCP, UDP etc)
    unsigned short checksum;       // IP checksum

    unsigned int   sourceIP;
    unsigned int   destIP;
} IpHeader;


//
// ICMP header structure
//
typedef struct _icmphdr 
{
    BYTE   i_type;
    BYTE   i_code;                 // Type sub code
    USHORT i_cksum;
    USHORT i_id;
    USHORT i_seq;
    // This is not the standard header, but we reserve space for time
    ULONG  timestamp;
} IcmpHeader;

//
// IP option header - use with socket option IP_OPTIONS
//
typedef struct _ipoptionhdr
{
    unsigned char        code;        // Option type
    unsigned char        len;         // Length of option hdr
    unsigned char        ptr;         // Offset into options
    unsigned long        addr[9];     // List of IP addrs
} IpOptionHeader;

class isocketping {
   enum {
	 ping_PINGOK = 0,
     ping_COMPLETE     = -40,
	 ping_SENDERROR,
	 ping_SENDTIMEOUT,
	 ping_RECVTIMEOUT,
	 ping_RECVERROR,
	 

     };
private:
	//WSADATA   wsaData;
	SOCKET sockRaw;
	BOOL  bRecordRoute;
	int   datasize;
	char  lpdest[128];
    struct sockaddr_in dest;
    struct sockaddr_in from;
    int fromlen;
/*



    unsigned int       addr = 0;
    
    
	*/
	USHORT             seq_no;
	char              *icmp_data, *recvbuf;
	struct hostent    *hp;
	 int                bread;
	 int timeout;
	int ret;
    IpOptionHeader     ipopt;

public:
	isocketping();
	~isocketping();
	int Ping(const char *address, int packetsize);
	int sendPing(char *buf, int size);
	
	//void createrawsocket(const char *adr);

};

#endif