#ifndef __class_processError__H
#define __class_processError__H

#include <stdio.h>
using namespace System;
class class_processError{
private:
	FILE *fp;
	char logfilename[1024];
public:
	class_processError();
	~class_processError();
	void logError(const char *errtype, int errorcode, const char *filename, int lineNumber, String ^errtext, String ^remarks="");
	void OpenLogFile(const char *filename);
	void CloselogFile();
	void FlushlogFile();
};

extern class_processError *processErrorLog; 

#endif