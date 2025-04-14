#ifndef ___logfile_timeStampClass__H
#define ___logfile_timeStampClass__H

#include "classlogfile.h"


class logfile_timeStampClass : public logfile{
private:
	char crlf[8];
public:
	logfile_timeStampClass();
	~logfile_timeStampClass();

	int arryputMsg(const char *portid, array<unsigned char> ^data, int size);
	int putSerialEventMsg(const char *portid,  const char *msg);
	int putMsg(const char *portid,  unsigned char *data, int size);

};


#endif