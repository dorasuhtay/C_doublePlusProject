#ifndef LOGFILE_H_INCLUDED
#define LOGFILE_H_INCLUDED

#include <stdio.h>

class logfile{
private:
	int active;
    FILE *Filefp;
	char *filename;
	int filenamelen;
	bool lock;
/*
	char *title;
   char last_Title[128];

	char fileExtension[8];
   char startTimeStr[32];
   int in_Progress;
   int sync;
   long totalsize;
   int overwriteFile;

   int timeRate;			//playback rate in milleseconds
   int ByteSize;			//read size from file for playback
   int MaxByteSize;		//max allowable file read size per read operation for playback
   char *rbuf;				//read buffer pointer

   //---GPStime seek--------------
	int timeformat;		//timeformat_HHMMSS, timeformat_SECONDS
   long startTime;		//start time (GPSTime) for playback begin
   long beginTime;
   long endTime;
   int NumOfRecordFound;
   unsigned short beginweek;
   unsigned short endweek;
	bool repeat;

	long seekoffset;
*/
public:
    logfile();
    ~logfile();
    void stop();
	void Close();
    int start(const char *file_name);
    int puts(const char *data, int size);
    int putc(char ch);
	void flush();
	bool Active() {return (active!=0);}
	const char * getfile_Name() {if (filename) return filename; else return "";}
};


#endif // LOGFILE_H_INCLUDED
