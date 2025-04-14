#include "StdAfx.h"
#ifdef WIN32
// #include <windows.h>
// #include <io.h>
// #include <direct.h>
 #define  MSG_NOSIGNAL 0
 #if __BORLANDC__ >0x520
	 #include "ws2tcpip.h"
 #endif
#else
 #include <sys/time.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <arpa/inet.h>
 #include <netdb.h>
 #include "unistd.h"
#endif

#ifdef __VMS
 #define  MSG_NOSIGNAL 0
#endif

#include <stdio.h>
//#include <stdarg.h>
//#include <string.h>
#include "isocket.h"
//#include "ithread.h"
#include "isleep.h"
//#include "icutil.h"

/*
#ifdef WIN32
bool isValidIpAddress(const char *ip_str)
{
	unsigned int n1,n2,n3,n4;

	if(sscanf(ip_str,"%u.%u.%u.%u", &n1, &n2, &n3, &n4) != 4) return 0;

	if((n1 <= 255) && (n2 <= 255) && (n3 <= 255) && (n4 <= 255)) return 1;
	return 0;
}


#else
bool isValidIpAddress(const char *ip_str)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ip_str, &(sa.sin_addr));
    return result != 0;
}
#endif
*/


#ifdef WIN32
//-------------------------------------------------------------
//RETURN:  0    successful
//         -1   there is an error in WSAStartup
//-------------------------------------------------------------
int init__wsa()
{
	
   static int first = 1;
   WORD wVersionRequested;
   WSADATA wsadata;
   int err;
   if(first == 1){
      wVersionRequested = MAKEWORD(1,1);
      err = WSAStartup(wVersionRequested, &wsadata);
      if(err != 0){
//         printf("Startup error=%d on windows\n",err);
         //exit(0);
         return -1;
         }
      first = 0;
      }
   return 0;
}
#endif



/*
// 
// Function: FillICMPData
//
// Description:
//    Helper function to fill in various fields for our ICMP request
//
#define ICMP_ECHO        8
void FillICMPData(char *icmp_data, int datasize)
{
    IcmpHeader *icmp_hdr = NULL;
    char       *datapart = NULL;

    icmp_hdr = (IcmpHeader*)icmp_data;
    icmp_hdr->i_type = ICMP_ECHO;        // Request an ICMP echo
    icmp_hdr->i_code = 0;
    icmp_hdr->i_id = (USHORT)GetCurrentProcessId();
    icmp_hdr->i_cksum = 0;
    icmp_hdr->i_seq = 0;
  
    datapart = icmp_data + sizeof(IcmpHeader);
    //
    // Place some junk in the buffer
    //
    memset(datapart,'E', datasize - sizeof(IcmpHeader));
}

// 
// Function: checksum
//
// Description:
//    This function calculates the 16-bit one's complement sum
//    of the supplied buffer (ICMP) header
//
USHORT checksum(USHORT *buffer, int size) 
{
    unsigned long cksum=0;

    while (size > 1) 
    {
        cksum += *buffer++;
        size -= sizeof(USHORT);
    }
    if (size) 
    {
        cksum += *(UCHAR*)buffer;
    }
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >>16);
    return (USHORT)(~cksum);
}


int iSocket::sendPing(const char *lpdest)
{
	struct hostent    *hp = NULL;
    memset(&dest, 0, sizeof(dest));
    //
    // Resolve the endpoint's name if necessary
    //
    dest.sin_family = AF_INET;
    if ((dest.sin_addr.s_addr = inet_addr(lpdest)) == INADDR_NONE)
    {
        if ((hp = gethostbyname(lpdest)) != NULL)
        {
            memcpy(&(dest.sin_addr), hp->h_addr, hp->h_length);
            dest.sin_family = hp->h_addrtype;
            //printf("dest.sin_addr = %s\n", inet_ntoa(dest.sin_addr));
        }
        else
        {
            //printf("gethostbyname() failed: %d\n", 
               // WSAGetLastError());
            return -1;
        }
    } 

	if(s_id == -1) return -1;
	((IcmpHeader*)icmp_data)->i_cksum = 0;
    ((IcmpHeader*)icmp_data)->timestamp = GetTickCount();
    ((IcmpHeader*)icmp_data)->i_seq = seq_no++;
    ((IcmpHeader*)icmp_data)->i_cksum = checksum((USHORT*)icmp_data, datasize);

	int bwrote = sendto(s_id, icmp_data, datasize, 0, 
                     (struct sockaddr*)&dest, sizeof(dest));

	return 0;

}
*/

iSocket::iSocket(const char *a, int p, int act)
{
	retryCount = 0;
	clientRetryCounter = 0;
	clientRetry = 100;
   #ifdef WIN32
   init__wsa(); // init sockets on windows
   #endif
   
	inbuf = 0;
	adr[0] = 0x0;
	if(a) 
		strcpy(adr,a);
	port = p;
	active = act;
	s_id = -1;
	os = -1;
	first = 1;
	memset(&remoteAddr,0,sizeof(remoteAddr));
	inbufSize = 2047;
	inbuf = (unsigned char *)malloc(inbufSize+1);
	/*
	//----------------------------------
	WORD wVersionRequested;
	int err;
	wVersionRequested = MAKEWORD(1,1);
	err = WSAStartup(wVersionRequested, &wsadata);
	if(err != 0)
	{
		return;
	}*/
}


/*
iSocket::iSocket(int socket)
{
   adr[0] = '\0';
   port   = -1;
   active = 0;
   s_id   = socket;
   os     = -1;
   first  = 0;

}
*/
char *iSocket::localName(char *name, int nsize)
{
   gethostname(name, nsize-1);
   return name;
}


char *iSocket::localIPAddr(char *localIP, int nsize)
{
   hostent* localHost;
   char hname[80];
   gethostname(hname, 79);
   localHost = gethostbyname(hname);
   if (localHost){
	   strncpy(localIP, inet_ntoa (*(struct in_addr *)*localHost->h_addr_list), nsize-1);
	   localIP[nsize-1] = 0x0;
      }
    return localIP;
}


iSocket::~iSocket()
{
    disconnect();
    if(os != -1 && active == 0)
    {
		shutdown(os,2);
		#ifdef WIN32
		closesocket(os);
		#else
		close(os);
		#endif
    }

    free(inbuf);

	//WSACleanup();
}

void iSocket::setAdr(const char *a)
{
   strcpy(adr,a);
}

void iSocket::setPort(int p)
{
   port = p;
}

int iSocket::getPort()
{
   return port;
}

void iSocket::setActive(int act)
{
   active = act;
}

/*
int iSocket::readi(void *buf, int len)
{
   char *cbuf = (char *) buf;
   return recv(s,cbuf,len,0);
}
*/

int iSocket::read(int len, int timeout)
{
    if (len>inbufSize)
        len = inbufSize;
    return read(inbuf, len, timeout);
}

int iSocket::read(void *buf, int len, int timeout)
{
   int  ii,ret;
   char *cbuf;
   if(s_id == -1) return -1;
   if(select(timeout) == 0) return 0; // timeout
   cbuf = (char *) buf;
   ii = 0;
   while(ii < len){
     ret = recv(s_id,&cbuf[ii],len-ii,0);
     if(ret <= 0){
       disconnect();
       return -1;
       }
     ii += ret;
     }
   return ii;
 }

int iSocket::readStr(char *buf, int len, int timeout)
{
   int ret,i;
   if(s_id == -1) return -1;
   if(select(timeout) == 0) return 0; // timeout
   i = 0;
   while(1) {
     #ifdef WIN32
     tryagain:
     #endif
     ret = recv(s_id,&buf[i],1,0);
     if(ret <= 0){
       #ifdef WIN32
       if(WSAEWOULDBLOCK == WSAGetLastError()) goto tryagain;
       #endif
       disconnect();
       buf[i] = '\0';
       return -1;
       }
     if(buf[i] == '\n'){
       buf[i+1] = '\0';
       return i+1;
       }
     if(i >= len-1){
       buf[i+1] = '\0';
       return i+1;
       }
     i++;
     }
}

int iSocket::write(const void *buf, int len)
{
   int ret,bytes_left,first_byte;
   const char *cbuf;
   if(s_id == -1) return -1;
   cbuf = (char *) buf;
   bytes_left = len;
   first_byte = 0;
   while(bytes_left > 0){
     ret = send(s_id,&cbuf[first_byte],bytes_left,MSG_NOSIGNAL);
     if(ret <= 0){
       disconnect();
       return -1;
       }
     bytes_left -= ret;
     first_byte += ret;
     }
   return first_byte;
}

int iSocket::createrawsocket()
{
	struct hostent     *host;
	struct in_addr     RemoteIpAddress;
	os = socket(AF_INET,SOCK_RAW, IPPROTO_ICMP);
	if(os == -1)
		return SOCKET_ERR;
	host = gethostbyname(adr);
	if(host == NULL){
		// See if the host is specified in "dot address" form
		RemoteIpAddress.s_addr = inet_addr(adr);
		if(RemoteIpAddress.s_addr == INADDR_NONE){
			closesocket(os);
			return INET_ADDR_ERR; // -1
			}
		}
	else
		memcpy(&RemoteIpAddress,host->h_addr,host->h_length);
	memset(&remoteAddr,0,sizeof(remoteAddr));
	remoteAddr.sin_family = AF_INET;
	remoteAddr.sin_port = 0;
	remoteAddr.sin_addr = RemoteIpAddress;
	s_id = os;
   return s_id;
}


bool is_ipv4adr(const char *ip_str)
{
	unsigned int n1,n2,n3,n4;
	if(sscanf(ip_str,"%u.%u.%u.%u", &n1, &n2, &n3, &n4) != 4) return 0;
	if((n1 <= 255) && (n2 <= 255) && (n3 <= 255) && (n4 <= 255)) return 1;
	return 0;
}
/*
int iSocket::clientconnect()
{
	int option;
	struct sockaddr_in localAddr;
	
	struct in_addr     RemoteIpAddress;
	if(port < 0)       return PORT_ERR;
	if(port >  256*256) return PORT_ERR;

		//---------------------------
		//Client connect
		//---------------------------
	if (clientRetryCounter>0)
	{
		clientRetryCounter--;
		int ret = ::connect(os, (struct sockaddr *) &remoteAddr, sizeof(remoteAddr));
		if(ret != -1) 
			s_id = os;
		return -2542;
	}
	else
	{
		clientRetryCounter = clientRetry;
			disconnect();
			os = socket(AF_INET,SOCK_STREAM,0);
			if(os == -1)
       			return SOCKET_ERR;


			memset(&remoteAddr,0,sizeof(remoteAddr));
			remoteAddr.sin_family = AF_INET;
			remoteAddr.sin_port = htons((short) port);
			//-------------------------------------------------------------------------------
			// If the user input is an alpha name for the host, use gethostbyname()
			// If not, get host by addr (assume IPv4, specified in "dot address" form)
			// e.g. adr = "www.this.com"
			//-------------------------------------------------------------------------------
			if (isalpha(adr[0]))         // host address is a name
			{
				struct hostent     *host;
				host = gethostbyname(adr);
				if(host == NULL)
				{
					closesocket(os);
					return INET_ADDR_ERR; // -1
				}
         		int ii;
				ii = 0;
				while (host->h_addr_list[ii] != 0) 
				{
					RemoteIpAddress.s_addr = *(u_long *) host->h_addr_list[ii++];
		        }
				remoteAddr.sin_family = host->h_addrtype;
			}
			else
         	{
				RemoteIpAddress.s_addr = inet_addr(adr);
				if(RemoteIpAddress.s_addr == INADDR_NONE)
				{
					closesocket(os);
					return INET_ADDR_ERR; // -1
				}
            }

			remoteAddr.sin_addr = RemoteIpAddress;
			u_long iMode=1;
			ioctlsocket(os,FIONBIO,&iMode);
			int ret = ::connect(os, (struct sockaddr *) &remoteAddr, sizeof(remoteAddr));
			if(ret == -1) 
			{
				closesocket(os);
				return CONNECT_ERR;
			}

			s_id = os;
	}	
	
	return s_id;
}
*/

bool iSocket::clientconnect(char *host,int port, int timeout)
{
    TIMEVAL Timeout;
    Timeout.tv_sec = timeout;
    Timeout.tv_usec = 0;
    struct sockaddr_in address;  /* the libc network address data structure */   
 
    os = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 
    address.sin_addr.s_addr = inet_addr(host); /* assign the address */
    address.sin_port = htons(port);            /* translate int2port num */	
    address.sin_family = AF_INET;
 
    //set the socket in non-blocking
    unsigned long iMode = 1;
    int iResult = ioctlsocket(os, FIONBIO, &iMode);
    if (iResult != NO_ERROR)
    {	
        //printf("ioctlsocket failed with error: %ld\n", iResult);
    }
	    
    if(connect(os,(struct sockaddr *)&address,sizeof(address))==false)
    {	
        return false;
    }	
 
    // restart the socket mode
    iMode = 0;
    iResult = ioctlsocket(os, FIONBIO, &iMode);
    if (iResult != NO_ERROR)
    {	
        //printf("ioctlsocket failed with error: %ld\n", iResult);
    }
 
    fd_set Write, Err;
    FD_ZERO(&Write);
    FD_ZERO(&Err);
    FD_SET(os, &Write);
    FD_SET(os, &Err);
 
    // check if the socket is ready
    ::select(0,NULL,&Write,&Err,&Timeout);			
    if(FD_ISSET(os, &Write)) 
    {	
		s_id = os;
        return true;
    }
 
    return false;
}

int iSocket::sconnect()
{
	int option;
	struct sockaddr_in localAddr;
	
	struct in_addr     RemoteIpAddress;
	if(port < 0)       return PORT_ERR;
	if(port >  256*256) return PORT_ERR;
	disconnect();
	if(active == 0)
	{ // accept calls Server socket
		if(first == 1)
		{
			// create a socket
			os = socket(AF_INET,SOCK_STREAM,0);
			if(os == -1)
				return SOCKET_ERR;
			// set socket options
			#ifdef __VMS
			option = 1;
			if(setsockopt(os,SOL_SOCKET,SO_KEEPALIVE,&option,sizeof(option)) < 0)
			{
				closesocket(os);
				return SETSOCKOPT_ERR;
			}
			#endif
			option = 1;
			#ifdef WIN32
			setsockopt(os,SOL_SOCKET,SO_REUSEADDR,(const char *) &option,sizeof(option));
			#else
			setsockopt(os,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
			#endif
			// Bind our server to the agreed upon port number.
			memset(&localAddr,0,sizeof(localAddr));
			localAddr.sin_port = htons((short) port);
			localAddr.sin_addr.s_addr = INADDR_ANY;  //because servers are 127.0.0.1
			localAddr.sin_family = AF_INET;
	bind:
			int ret = bind(os, (struct sockaddr *) &localAddr, sizeof(localAddr));
			if(ret == -1) 
			{
				isleep(1000);
				goto bind;
			}
			// Prepare to accept client connections.  Allow up to 5 pending
			// connections.
			ret = listen(os, 5);
			if(ret == -1) 
			{
				closesocket(os);
				return LISTEN_ERR;
			}
		}
		first = 0;

		// accept connections
		//returns INVALID_SOCKET is error
		s_id = accept(os, NULL, NULL);
		if(s_id == -1)
		{
			closesocket(os);
			return ACCEPT_ERR;
        }
	} // end active == 0
	else
		//---------------------------
		//Client connect
		//---------------------------
		if(active == 1)
		{
			os = socket(AF_INET,SOCK_STREAM,0);
			if(os == -1)
       			return SOCKET_ERR;


			memset(&remoteAddr,0,sizeof(remoteAddr));
			remoteAddr.sin_family = AF_INET;
			remoteAddr.sin_port = htons((short) port);
			//-------------------------------------------------------------------------------
			// If the user input is an alpha name for the host, use gethostbyname()
			// If not, get host by addr (assume IPv4, specified in "dot address" form)
			// e.g. adr = "www.this.com"
			//-------------------------------------------------------------------------------
			if (isalpha(adr[0]))         // host address is a name
			{
				struct hostent     *host;
				host = gethostbyname(adr);
				if(host == NULL)
				{
					closesocket(os);
					return INET_ADDR_ERR; // -1
				}
         		int ii;
				ii = 0;
				while (host->h_addr_list[ii] != 0) 
				{
					RemoteIpAddress.s_addr = *(u_long *) host->h_addr_list[ii++];
					//  printf("\tIP Address #%d: %s\n", i, inet_ntoa(addr));
		        }
				remoteAddr.sin_family = host->h_addrtype;
				/*
				//host->h_length;
				//host->h_name;		//printf("\tOfficial name: %s\n", host->h_name);
				char **pAlias;
				for (pAlias = host->h_aliases; *pAlias != 0; pAlias++) 
				{
					//	printf("\tAlternate name #%d: %s\n", ++ii, *pAlias);
				}
				*/
			}
			else
         	{
				RemoteIpAddress.s_addr = inet_addr(adr);
				if(RemoteIpAddress.s_addr == INADDR_NONE)
				{
					closesocket(os);
					return INET_ADDR_ERR; // -1
				}
            }

			remoteAddr.sin_addr = RemoteIpAddress;
			//u_long iMode=1;
			//ioctlsocket(os,FIONBIO,&iMode);
			int ret = ::connect(os, (struct sockaddr *) &remoteAddr, sizeof(remoteAddr));
			if(ret == -1) 
			{
				closesocket(os);
				return CONNECT_ERR;
			}

			s_id = os;
			}
	return s_id;
}
/*
char *iSocket::getremoteAddr(char *out)
{
	sprintf(out, "%s", inet_ntoa(remoteAddr.sin_addr));
   return out;
}
*/
sockaddr_in *iSocket::getremoteAddr()
{
	return &remoteAddr;
}




/*
int iSocket::sconnect()
{
	int option;
	int ret = -1;
	struct sockaddr_in localAddr;
	struct sockaddr_in remoteAddr;
	struct hostent     *host;
	struct in_addr     RemoteIpAddress;
	if(port <= 0)       return PORT_ERR;
	if(port >  256*256) return PORT_ERR;
	disconnect();
	if(active == 0){ // accept calls
		if(first == 1){
			// create a socket
		os = socket(AF_INET,SOCK_STREAM,0);
			if(os == -1){
				return SOCKET_ERR;
				}
			// set socket options
			#ifdef __VMS
			option = 1;
			if(setsockopt(os,SOL_SOCKET,SO_KEEPALIVE,&option,sizeof(option)) < 0){
				closesocket(os);
				return SETSOCKOPT_ERR;
				}
			#endif
			option = 1;
			#ifdef WIN32
			setsockopt(os,SOL_SOCKET,SO_REUSEADDR,(const char *) &option,sizeof(option));
			#else
			setsockopt(os,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
			#endif
			// Bind our server to the agreed upon port number.
			memset(&localAddr,0,sizeof(localAddr));
			localAddr.sin_port = htons((short) port);
			localAddr.sin_family = AF_INET;
	bind:
			ret = bind(os, (struct sockaddr *) &localAddr, sizeof(localAddr));
			if(ret == -1) {
				iw_sleep(1000);
				goto bind;
				}
			// Prepare to accept client connections.  Allow up to 5 pending
			// connections.
			ret = listen(os, 5);
			if(ret == -1) {
				closesocket(os);
				return LISTEN_ERR;
				}
			}
		first = 0;

		// accept connections
		//returns INVALID_SOCKET is error
		s_id = accept(os, NULL, NULL);

//		printf("");
//		if(s_id == -1){
//			closesocket(os);
//         s_id = -1;
//     		return ACCEPT_ERR;
//         }
//		else
//	     	return s_id;
		} // end active == 0
	else
		if(active == 1){
			//::printf("debug: adr=%s port=%d\n",adr,port);
			//s_id = -1;
			os = socket(AF_INET,SOCK_STREAM,0);
			if(os == -1)
       		return SOCKET_ERR;
			s_id = os;
			//::printf("debug: gethostbyname\n");
			// fill destblk structure
			host = gethostbyname(adr);
			if(host == NULL){
				// See if the host is specified in "dot address" form
				RemoteIpAddress.s_addr = inet_addr(adr);
				if(RemoteIpAddress.s_addr == INADDR_NONE){
					s_id = -1;
					closesocket(os);
					return INET_ADDR_ERR; // -1
					}
				}
			else
				memcpy(&RemoteIpAddress,host->h_addr,host->h_length);
			memset(&remoteAddr,0,sizeof(remoteAddr));
			remoteAddr.sin_family = AF_INET;
			remoteAddr.sin_port = htons((short) port);
			remoteAddr.sin_addr = RemoteIpAddress;
			//::printf("debug: connect\n");
			ret = ::connect(s_id, (struct sockaddr *) &remoteAddr, sizeof(remoteAddr));
			//::printf("debug: connect ret=%d\n",ret);
			if(ret == -1) {
				s_id = -1;
				closesocket(os);
				return CONNECT_ERR;
				}
//			s_id = os;
			}
	return s_id;
}
*/
void iSocket::disconnect()
{
   if(s_id != -1) {
     #ifdef WIN32
     closesocket(s_id);
     #else
     close(s_id);
     #endif
     }
   s_id = -1;
}

void iSocket::OnClose()
{
     #ifdef WIN32
    closesocket(os);
     #else
     close(os);
     #endif

}


int iSocket::isConnected()
{
    if(s_id == -1)
        return 0;
    else
        return 1;
}

int iSocket::select(int timeout)
{
   struct timeval timout;
   fd_set wset,rset,eset;
   int    ret,maxfdp1;

   if(timeout == 0) return 1;
   /* setup sockets to read */
   maxfdp1 = s_id+1;
   FD_ZERO(&rset);
   FD_SET (s_id,&rset);
   FD_ZERO(&wset);
   FD_ZERO(&eset);
   timout.tv_sec  = timeout / 1000;
   timout.tv_usec = timeout % 1000;

   ret = ::select(maxfdp1,&rset,&wset,&eset,&timout);
   if(ret == 0) return 0; /* timeout */
   return 1;
}

/*
int iSocket::printf(const char *format, ...)
{
   int ret;
   char message[iw_PRINTF_LENGTH]; // should be big enough
   va_list ap;
   va_start(ap,format);
   ret = iw_vsnprintf(message, iw_PRINTF_LENGTH - 1, format, ap);
   va_end(ap);
   if(ret < 0) return ret;
   return write(message,strlen(message));
}
*/

/*
-------------------------------------------------------------
gethostname()
-------------------------------------------------------------
			int  rc;
			int  server_sock;
			char hostname[50];
			rc = gethostname((char *)&hostname,sizeof(hostname));
         if (rc==0){
	         sprintf(buf, "Hostname: %s\r\n", hostname);
   	      writeErrorMsg(buf);
            }

-------------------------------------------------------------
getpeername()
-------------------------------------------------------------
#include <sys/socket.h>
?
int addrlen;
int rc,
int newclient_sock;
int server_sock;
struct sockaddr_in client_addr;
?
newclient_sock = accept(server_sock, (struct sockaddr *) 0, (int) 0);
?
addrlen = sizeof(client_addr);
rc = getpeername(newclient_sock, (struct sockaddr *)&client_addr,
                &addrlen);

-------------------------------------------------------------
getsockname()
-------------------------------------------------------------
#include <sys/socket.h>
?
int addrlen;
int rc;
int server_sock;
struct sockaddr_in server_addr;
?
addrlen = sizeof(server_addr);
rc = getsockname(server_sock,(struct sockaddr *)&server_addr, &addrlen);

*/



/*
typedef enum {
  WZD_INET_NONE = 0,
  WZD_INET4     = 2,  // AF_INET
  WZD_INET6     = 10, // AF_INET6
} net_family_t;

// \brief Return our own ip
//
// \a buffer must be at least 16 bytes long
///
unsigned char * getmyip(int sock, net_family_t family, unsigned char * buffer)
{
  struct sockaddr_in sa;
  int size;

#if defined(IPV6_SUPPORT)
  if (family == WZD_INET6) {
    struct sockaddr_in6 sa6;

    size = sizeof(struct sockaddr_in6);
    memset(buffer,0,16);
    if (getsockname(sock,(struct sockaddr *)&sa6,&size)!=-1)
    {
      memcpy(buffer,&sa6.sin6_addr,16);
    } else { // failed, using localhost
      out_log(LEVEL_CRITICAL,"getmyip: could not get my own ip !\n");
      return NULL;
    }

    return buffer;
  }
#endif // IPV6_SUPPORT
  size = sizeof(struct sockaddr_in);
  memset(buffer,0,16);
  if (getsockname(sock,(struct sockaddr *)&sa,&size)!=-1)
  {
    memcpy(buffer,&sa.sin_addr,4);
  } else { // failed, using localhost
//    out_log(LEVEL_CRITICAL,"getmyip: could not get my own ip !\n");
    return NULL;
  }

  return buffer;
}
*/


/*
    ip = ip_parse_host("[123]");
    ip_free(ip);
    ip = ip_parse_host("1.2.3.4");
    ip_free(ip);
    ip = ip_parse_host("localhost.localdomain");
    ip_free(ip);
    ip = ip_parse_host("1.2.3.4/24");
    ip_free(ip);
    // tests which should fail properly
    ip = ip_parse_host("1:2");
    ip = ip_parse_host("1.2.3.4/");
    ip = ip_parse_host("1.2.3.4/a");
    ip = ip_parse_host("localhost.localdomain/22");
*/
/** \brief Check if string is a numeric IPv4 address
 * \return 1 if assertion is true
 *
 * \note actually, this is a very limited check
 */
int string_is_ipv4(const char * s)
{
  while (*s != '\0') {
    if (*s != '.' && !isdigit(*s)) return 0;
    s++;
  }

  return 1;
}

/** \brief Check if string is a numeric IPv6 address
 * \return 1 if assertion is true
 *
 * \note actually, this is a very limited check
 */
int string_is_ipv6(const char * s)
{
  while (*s != '\0') {
    if (*s != ':' && !isxdigit(*s)) return 0;
    s++;
  }

  return 1;
}

/** \brief Check if string is a host name
 * \return 1 if assertion is true
 *
 * Accepted host names are:
 * [:alnum:] ([alnum] | . | -)*
 */
static int string_is_hostname(const char * s)
{
  if (*s == '\0' || !isalnum(*s)) return 0;
  s++;

  while (*s != '\0') {
    if (!isalnum(*s) && *s != '-' && *s != '.') return 0;
    s++;
  }

  return 1;
}



int isCommandCaseMatch(const char *in, const char *match, int msize)
{
	int kk;
    char buf1[80];
	for (kk=0;kk<msize;kk++)
		buf1[kk] = toupper(in[kk]);
	if (strncmp(buf1, match, msize)==0)
		return 1;
  	return 0;
}

/*
sort out the text in "data"
	ip address specification can be
   	192.168.10.30:6123 or       with a colon separator
		192.168.10.30 6123 or       with a space separator
		192.168.10.30 6123+10       additional Consecutive port
      the spearator can be a colon or space between address and port
      the additional port e.g. 6123+10 would mean that ports 6123..6133 is defined
   text begins with "thisPC:" is replaced with the IP address allocated by the network DHCP (e.g. 192.168.10.123)
   text begins with "local:" is replaced with the IP address 127.0.0.1
   text begins with "localhost:" is replaced with the IP address 127.0.0.1

	Alias names of
     ipaddr, gun and tail are also valid and will be translated with a cross reference table
RETURNS: numberofconsecutiveports
*/
int sortout_ipaddress(const char *in, char *ipaddr, int ipaddrsize, int *port)
{
    int numberofconsecutiveports = 0;
	if (!in) return numberofconsecutiveports;
	if (!ipaddr) return numberofconsecutiveports;
    char *sptr;
    char *buffer = (char *)malloc(strlen(in)+16);
    strcpy(buffer, in);
	*port = 0;
	sptr = strchr(buffer, ':');		//search for an ip address port separator (e.g. 192.168.10.30:6123)
	if (!sptr)
		sptr = strchr(buffer, ' ');	//search for an ip address port separator (e.g. 192.168.10.30 6123)
   //---------------------------------------------------------------------------------------------------------
	//if cannot find separator of a space or colon... this text in "data" is not a valid IP address and port
   //---------------------------------------------------------------------------------------------------------
	if (!sptr)
	{
		if (isCommandCaseMatch(in, "NONE",4))
		{
		    strncpy(ipaddr, "NONE", ipaddrsize);
		    ipaddr[ipaddrsize] = 0x0;
		    *port = 0;
		}
        return numberofconsecutiveports;
    }

	//get additional consecutive port number
	numberofconsecutiveports = 1;       //make assumption that there is only one port specified
	char *sptra = strchr(sptr+1, '+');
	if (sptra)
	{
		*sptra = 0x0;
		sptra++;
		numberofconsecutiveports = atoi(sptra);		//additional Consecutive out ports.
	}

	//get port number
	//TCHAR t_buf[128];
	*port = atol(sptr+1);
	*sptr = 0x0;
	strncpy(ipaddr, buffer, ipaddrsize);
	ipaddr[ipaddrsize] = 0x0;
/*
	if (strcmp(ipaddr, "local")==0)
		strcpy(ipaddr, "127.0.0.1");
	if (strcmp(ipaddr, "localhost")==0)
		strcpy(ipaddr, "127.0.0.1");
	if (strcmp(ipaddr, "thisPC")==0)
		strcpy(ipaddr, myaddr);
*/
/*
	//Alias names
	if (strcmp(ipaddr, "ipaddr")==0)
		strcpy(ipaddr, rl->hostname.userSpecifiedIPaddr);
	if (strcmp(ipaddr, "gun")==0)
		strcpy(ipaddr, rl->hostname.userSpecifiedGunIPaddr);
	if (strcmp(ipaddr, "tail")==0)
		strcpy(ipaddr, rl->hostname.userSpecifiedTailIPaddr);
*/
    free(buffer);
    return numberofconsecutiveports;
}








#ifdef Kill
char     dir[DIRSIZE];  /* used for incomming dir name, and
					outgoing data */
	int 	 sd, sd_current, cc, fromlen, tolen;
	int 	 addrlen;
	struct   sockaddr_in sin;
	struct   sockaddr_in pin;

	/* get an internet domain socket */
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	/* complete the socket structure */
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(PORT);

	/* bind the socket to the port number */
	if (bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
		perror("bind");
		exit(1);
	}

	/* show that we are willing to listen */
	if (listen(sd, 5) == -1) {
		perror("listen");
		exit(1);
	}
	/* wait for a client to talk to us */
        addrlen = sizeof(pin);
	if ((sd_current = accept(sd, (struct sockaddr *)  &pin, &addrlen)) == -1) {
		perror("accept");
		exit(1);
	}
/* if you want to see the ip address and port of the client, uncomment the
    next two lines */

       /*
printf("Hi there, from  %s#\n",inet_ntoa(pin.sin_addr));
printf("Coming from port %d\n",ntohs(pin.sin_port));
        */

	/* get a message from the client */
	if (recv(sd_current, dir, sizeof(dir), 0) == -1) {
		perror("recv");
		exit(1);
	}

        /* get the directory contents */
         read_dir(dir);

      /* strcat (dir," DUDE");
       */
	/* acknowledge the message, reply w/ the file names */
	if (send(sd_current, dir, strlen(dir), 0) == -1) {
		perror("send");
		exit(1);
	}

        /* close up both sockets */
	close(sd_current); close(sd);

        /* give client a chance to properly shutdown */
        sleep(1);

#endif
