#ifndef ___wctStringFifo__H
#define ___wctStringFifo__H




#include "wctString.h"


#define MAX_WCTSTRINGFIFO_SIZE		1024

class wctStringFifo{
private:
	int count;
	int headptr;
	int tailptr;
	int overrunCount;
	wctString *wctStr[MAX_WCTSTRINGFIFO_SIZE];

public:
	wctStringFifo();
	~wctStringFifo();
	//void add(unsigned char *data);
	int	getcount() {return count;}
	int getHeadptr() {return headptr;}
	int getTailptr() {return tailptr;}
	void create(int size);
	void Clear();
	void put(const wchar_t *data);
	void put(const char *data);
	int get(wchar_t *data);
	wctString *get();
	long used();
	//int getLength();
	bool available();
	int getoverrunCount() {return overrunCount;}
	void clear() {overrunCount=0; headptr=0; tailptr=0;}

};


#endif