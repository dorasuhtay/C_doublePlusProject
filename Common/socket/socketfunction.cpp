#include "StdAfx.h"
#include <windows.h>
#include <stdio.h>
#include "socketfunction.h"

struct IPv4
{
    unsigned char b1, b2, b3, b4;
};
#pragma comment(lib, "ws2_32.lib")
bool getMyIP(IPv4Type & myIP)
{
    char szBuffer[1024];

    #ifdef WIN32
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);
    if(::WSAStartup(wVersionRequested, &wsaData) != 0)
        return false;
    #endif


    if(gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)
    {
      #ifdef WIN32
      WSACleanup();
      #endif
      return false;
    }

    struct hostent *host = gethostbyname(szBuffer);
    if(host == NULL)
    {
      #ifdef WIN32
      WSACleanup();
      #endif
      return false;
    }

			
	char buf[128];
    for (int i = 0; host->h_addr_list[i] != 0; ++i) {
		char *ip = inet_ntoa(*(struct in_addr *)host->h_addr_list[i]);  
        struct in_addr addr;
        memcpy(&addr, host->h_addr_list[i], sizeof(struct in_addr));
		strcpy(buf, inet_ntoa(addr));
        
    }

    //Obtain the computer's IP
    myIP.b1 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b1;
    myIP.b2 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b2;
    myIP.b3 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b3;
    myIP.b4 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b4;

    #ifdef WIN32
    WSACleanup();
    #endif
    return true;
}

class_localMachine::~class_localMachine() {WSACleanup();}

class_localMachine::class_localMachine()
{
	ipcount = 0;
	error = 0;
	szBuffer[0] = 0x0;
    #ifdef WIN32
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);
    if(::WSAStartup(wVersionRequested, &wsaData) != 0)
        error++;
	else
	{
		if(gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)
		{
		  WSACleanup();
		  error++;
		}
		else
		{
			host = gethostbyname(szBuffer);
			if(host == NULL)
			{
			  WSACleanup();
			  error++;
			}
		}
	}
    #endif
}

const char *class_localMachine::getIpAddress()
{
	if (host == NULL) 
	{
		ipcount = 0;
		return 0;
	}
	if (host->h_addr_list[ipcount])
	{
		char *Ip = inet_ntoa(*(struct in_addr *)host->h_addr_list[ipcount]); 
		if (Ip)
		{
			ipcount++;
			return Ip;
		}
	}
	ipcount = 0;
	return 0;
}




bool isValid_ipv4_IpAddress(const char *ip_str)
{
	unsigned int n1,n2,n3,n4;
	if(sscanf(ip_str,"%u.%u.%u.%u", &n1, &n2, &n3, &n4) != 4) return 0;
	if((n1 <= 255) && (n2 <= 255) && (n3 <= 255) && (n4 <= 255)) return 1;
	return 0;
}

/*
bool validateIpAddress(const char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}
*/

int isInvalidIPaddress(const char *vbuf)
{
    const char *sptr;
	int coloncount = 0;
    int count = 0;
    int jj=0;
    int num;
    char databuf[6];
    sptr = strchr(vbuf, ':');
    if (!sptr)
        sptr = strchr(vbuf, ' ');
    if (!sptr)
        return -4;
    sptr = vbuf;
	while(*sptr){
   	databuf[jj] = *sptr;
	   jj++;
		if (*sptr=='.'){
      	count++;
			databuf[jj] = 0x0;
         jj = 0;
			if (coloncount==0){
            num = atoi(databuf);
   	   	if ((num<0)||(num>255))
	   	   	return -6;
            }
         }
		if ((*sptr==':')||(*sptr==' ')){
         jj = 0;
      	coloncount++;
      	if (count!=3)
         	return -1;
         }
      if (jj>4)
      	jj = 0;
   	sptr++;
	   }
   if (coloncount!=1)
   	return -4;
   if (count!=3)
   	return count;
   return 0;
}
