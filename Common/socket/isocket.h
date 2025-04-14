#ifndef ISOCKET_H_INCLUDED
#define ISOCKET_H_INCLUDED

#include <windows.h>


/*
#ifndef in_addr
typedef struct in_addr {
  union {
    struct {
      u_char s_b1,s_b2,s_b3,s_b4;
    } S_un_b;
    struct {
      u_short s_w1,s_w2;
    } S_un_w;
    u_long S_addr;
  } S_un;
} IN_ADDR, *PIN_ADDR, FAR *LPIN_ADDR;
#endif

#ifndef sockaddr_in
struct sockaddr_in{
   short sin_family;
   unsigned short sin_port;
   struct in_addr sin_addr;
   char sin_zero[8];
};
#endif
*/

/*
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
*/


class iSocket{
public:
   enum SocketEnum {
     SOCKET_ERR     = -1,
     SETSOCKOPT_ERR = -2,
     LISTEN_ERR     = -3,
     ACCEPT_ERR     = -4,
     INET_ADDR_ERR  = -5,
     CONNECT_ERR    = -6,
     PORT_ERR       = -7
     };
   iSocket(const char *adr, int port, int active);
   //iSocket(int socket);
   ~iSocket();
   char *localName(char *name, int nsize);
   char *localIPAddr(char *localIP, int nsize);
   void setAdr(const char *adr);
   void setPort(int port);
   int getPort();
   const char *getAddress() {return adr;}
   void setActive(int active);
   int read(int len, int timeout=0);
   int read(void *buf, int len, int timeout=0);
   int readStr(char *buf, int len, int timeout=0);
   int write(const void *buf, int len);
   int sconnect();
   void disconnect();
   void OnClose();
   int select(int timeout=0);
   int isConnected();
	int createrawsocket();
   int getSOCKET() {return s_id;}
   //int clientconnect();
   bool clientconnect(char *host,int port, int timeout);
//   int printf(const char *format, ...);
   int s_id;
//	char *getremotedotAddr(char *out);
	sockaddr_in *getremoteAddr();
	inline unsigned char *getinbuf(){return inbuf;}
    inline int getinbufSize() {return inbufSize;}
	int sendPing(const char *lpdest);
	int retryCount;
	char *getipaddress() {return adr;}
private:
	 WSADATA wsadata;
	int clientRetryCounter;
	int clientRetry;	 
   char adr[132];
   int  port;
   int  active;
   int  os;
   int  first;
	struct sockaddr_in remoteAddr;
	unsigned char *inbuf;
	 int inbufSize;

/*
	int datasize;
	char *icmp_data;
	char *recvbuf;
	USHORT seq_no;
	struct sockaddr_in dest;
*/
};

#ifdef WIN32
//extern int init_wsa();
#endif

extern int sortout_ipaddress(const char *in, char *ipaddr, int ipaddrsize, int *port);
//extern bool isValidIpAddress(const char *ip_str);
//extern int string_is_ipv4(const char * s);
#endif // ISOCKET_H_INCLUDED
