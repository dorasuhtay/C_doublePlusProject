#include "StdAfx.h"
#include "isleep.h"
#include "classlogfile.h"



#define MAX_FILENAMEPATH__		1024
logfile::logfile()
{
    Filefp = 0;
    active = 0;
    lock = 0;
	filenamelen = MAX_FILENAMEPATH__;
	filename = new char [filenamelen];
	filename[0] = 0x0;
}
int sleeptime=10;
logfile::~logfile()
{
    stop();
	delete filename;
}

void logfile::Close()
{
	stop();
}

void logfile::stop()
{
	while(lock)
        isleep(sleeptime);
		//isleep(10);
    lock = 1;
    active = 0;
	if (Filefp)
  		fclose(Filefp);
   	Filefp = 0;
   	lock = 0;
}

int logfile::start(const char *file_name)
{
	if (active) return -2;
    strncpy(filename, file_name, filenamelen-1);
    filename[filenamelen-1] = 0x0;
	if (!filename[0]) return -3;
    stop();
	Filefp = fopen(filename, "w+b");
	if (Filefp)
	{
		active = 1;
      return 0;
    }
    return -4;
}

void logfile::flush()
{
	while(lock)
		isleep(sleeptime);
        //isleep(10);
    lock = 1;
	active = 0;
	if (Filefp)
		fclose(Filefp);
	Filefp = fopen(filename, "a+b");
	if (Filefp)
		active = 1;
	lock = 0;
}

int logfile::puts(const char *data, int size)
{
	int nn = 0;
	if (!active) return -2;
	while(lock)
		isleep(sleeptime);
		//isleep(10);//orginal 10
	lock = 1;
	if (Filefp)
		nn = fwrite(data, 1, size, Filefp);
	lock = 0;
	return nn;
}

int logfile::putc(char ch)
{
	if (!active) return -2;
	int nn = 0;
	while(lock)
		isleep(sleeptime);
        //isleep(10);//orginal 10
    lock = 1;
	if (Filefp)
	    nn = fputc(ch, Filefp);
    lock = 0;
	return nn;
}
