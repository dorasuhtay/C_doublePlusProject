#include "StdAfx.h"
#include <time.h>
#include <string.h>
#include "class_processError.h"
#include "stringconversion.h"

class_processError *processErrorLog = 0; 

class_processError::class_processError()
{
	fp = 0;
}

class_processError::~class_processError()
{
	CloselogFile();
}
//#include <dir.h>
void class_processError::logError(const char *errtype, int errorcode, const char *filename, int lineNumber, String ^errtext, String ^remarks)
{
	if (fp)
	{
		char filen[1024];
		strcpy(filen, filename);

		char tempbuf[512], remarkbuf[512];
		String2Char(errtext, tempbuf);
		String2Char(remarks, remarkbuf);
		
		char *sptr = strrchr((char *)filename, '\\');
		if (sptr)
		{
			strcpy(filen, sptr);
		}
		
		sptr = strstr(filen, ".CPP");
		if (sptr)
		{
			*sptr = 0x0;
			strcat(filen, ".CC");
		}
		sptr = strstr(filen, ".cpp");
		if (sptr)
		{
			*sptr = 0x0;
			strcat(filen, ".cc");
		}
		sptr = strstr(filen, ".h");
		if (sptr)
		{
			*sptr = 0x0;
			strcat(filen, ".hh");
		}
		sptr = strstr(filen, ".H");
		if (sptr)
		{
			*sptr = 0x0;
			strcat(filen, ".HH");
		}


		fprintf(fp, "Error:%s(%d), %s, %s, <%s, line#%d>\r\n", errtype, errorcode, tempbuf, remarkbuf, filen, lineNumber);
	}
}

void class_processError::OpenLogFile(const char *filename)
{
	struct tm * timeinfo;
	char buf[128];
	time_t timenow = time(0);
	timeinfo = localtime ( &timenow );
	
	strcpy(logfilename, filename);
	fp = fopen(logfilename, "a+t");
	if (fp)
	{
		strcpy(buf, asctime (timeinfo));
		
		char *sptr = strchr(buf,'\r');
		if (sptr) *sptr = 0x0;
		sptr = strchr(buf,'\n');
		if (sptr) *sptr = 0x0;
		
		fprintf(fp, "*******************************\r\n");
		fprintf(fp, "* %s\r\n", buf);
		fprintf(fp, "*******************************\r\n");
	}
}

void class_processError::CloselogFile()
{
	if (fp)
		fclose(fp);
}

void class_processError::FlushlogFile()
{
	if (fp)
		fclose(fp);
	fp = fopen(logfilename, "a+t");
}
