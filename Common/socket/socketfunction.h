#ifndef __socketfunction__H
#define __socketfunction__H



typedef struct 
{
    unsigned char b1, b2, b3, b4;
}IPv4Type;

extern bool getMyIP(IPv4Type & myIP);
extern bool isValid_ipv4_IpAddress(const char *ip_str);

class class_localMachine
{
private:
	int error;
    char szBuffer[1024];
	struct hostent *host;
	int ipcount;
public:
	class_localMachine();
	~class_localMachine();
	const char *getIpAddress();
	const char *getName() {return szBuffer;}
};

#endif