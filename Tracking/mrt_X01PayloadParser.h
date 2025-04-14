#ifndef ___mrt_X01PayloadParser__H
#define ___mrt_X01PayloadParser__H

#include "mrt_X01netc.h"

class mrt_X01PayloadParser{
private:
	unsigned char *payload;
	structmrt_X01netcType *mrt_X01;
public:
	mrt_X01PayloadParser();
	~mrt_X01PayloadParser();
	int parsePacket(unsigned char ch);
	const unsigned char *getpayload() {return payload;}
	int getpayloadlength() {return mrt_X01->length;}
};

#endif