//logfile_timeStampClass.cpp
#include "StdAfx.h"
#include <string.h>
#include <time.h>
#include "logfile_timeStampClass.h"

logfile_timeStampClass::logfile_timeStampClass():logfile()
{
	strcpy(crlf, "\r\n");
}

logfile_timeStampClass::~logfile_timeStampClass()
{
}

const char *DateTimeStr(char *dstr)
{
	#ifdef use_LOCALTIME
//	const char daystr[7][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
//	const char monthstr[13][4] = {"   ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	SYSTEMTIME st;
	GetLocalTime(&st);
	sprintf(dstr,"%s %s %02d %02d:%02d:%02d.ff %04d\n",
                  daystr[st.wDayOfWeek],
                  monthStr[st.wMonth],
                  st.wDay,
                  st.wHour,
						st.wMinute,						
                  st.wSecond,
				  st.wMilliseconds,
                  st.wYear);
	dstr[24] = 0x0;
   #else
	time_t t;
	time(&t);
	sprintf(dstr,"%s", ctime(&t));
	dstr[24] = 0x0;
   #endif
   return dstr;
}
/*
void DateTimeStrFormatted(int Format, char *dstr)
{
	//#ifdef use_LOCALTIME
//	const char daystr[7][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
//	const char monthstr[13][4] = {"   ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	const char daystr[7][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
	const char daystr1[7][16] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	const char daystr2[7][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
//	const char monthstr[13][4] = {"   ","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
   char stemp[60];
	tm st;
	GetLocalTime(&st);
	switch (Format){
  	case 		1:
  	case 		101:
            sprintf(dstr,"%02d/%02d/%04d %02d:%02d:%02d",
                  st.wMonth,
                  st.wDay,
                  st.wYear,
                  st.wHour,
						st.wMinute,
                  st.wSecond
                  );
						dstr[24] = 0x0;
						break;
  	case 		2:
  	case 		102:
            sprintf(dstr,"%02d-%s-%04d, %02d:%02d:%02d",
                  st.wDay,
                  monthStr[st.wMonth],
                  st.wYear,
                  st.wHour,
									st.wMinute,
                  st.wSecond
                  );
						dstr[24] = 0x0;
						break;
  	case 		3:
  	case 		103:
            sprintf(dstr,"%04d/%02d/%02d, %02d:%02d:%02d",
                  st.wYear,
                  st.wMonth,
                  st.wDay,
                  st.wHour,
									st.wMinute,
                  st.wSecond
                  );
						dstr[24] = 0x0;
						break;
  	case 		4:
  	case 		104:
            sprintf(dstr,"%02d/%02d/%04d, %02d:%02d:%02d",
                  st.wDay,
                  st.wMonth,
                  st.wYear,
                  st.wHour,
						st.wMinute,
                  st.wSecond
                  );
						dstr[24] = 0x0;
						break;
  	case 		5:
  	case 		105:
   //        		strcpy(stemp, daystr[st.wDayOfWeek]);
    			sprintf(dstr,"%s, %s %02d %04d, %02d:%02d:%02d",
//						strlwr(stemp),
						daystr1[st.wDayOfWeek],
                  monthStr[st.wMonth],
                  st.wDay,
                  st.wYear,
                  st.wHour,
						st.wMinute,
                  st.wSecond
                  );
//						dstr[24] = 0x0;
            break;
  	case 		6:
  	case 		106:
            sprintf(dstr,"%02d %s %04d, %02d:%02d:%02d",
                  st.wDay,
                  monthStr[st.wMonth],
                  st.wYear,
                  st.wHour,
									st.wMinute,
                  st.wSecond
                  );
						dstr[24] = 0x0;
						break;
  	case 		7:
  	case 		107:
            sprintf(dstr,"%02d.%02d.%04d",
                  st.wDay,
                  st.wMonth,
                  st.wYear
                  );
						dstr[10] = 0x0;
						break;
  	case 		8:
            sprintf(dstr,"%02d:%02d:%02d",
                  st.wHour,
						st.wMinute,
                  st.wSecond
                  );
						dstr[24] = 0x0;
						break;
  	case 		9:
            sprintf(dstr,"%02d/%02d/%04d",
                  st.wDay,
                  st.wMonth,
                  st.wYear
                  );
						dstr[24] = 0x0;
						break;

    default:sprintf(dstr,"%s %s %02d %02d:%02d:%02d %04d\n",
                  daystr[st.wDayOfWeek],
                  monthStr[st.wMonth],
                  st.wDay,
                  st.wHour,
						st.wMinute,
                  st.wSecond,
                  st.wYear);
						dstr[24] = 0x0;
            break;
    }

}

*/

int logfile_timeStampClass::arryputMsg(const char *portid, array<unsigned char> ^data, int size)
{
	unsigned char buf[128];
	for (int ii=0;ii<size;ii++)
		buf[ii] = data[ii];
	return putMsg(portid,  buf, size);
}

int logfile_timeStampClass::putMsg(const char *portid,  unsigned char *data, int size)
{
	int ii;
	char buf[128];
	char buf1[32];
	char tempb[32];
	strcpy(buf,portid);
	strcat(buf, ":");
	strcat(buf,DateTimeStr(buf1));
	strcat(buf, " ");
	for (ii=0;ii<size;ii++)
	{
		if (ii==0)
			sprintf(tempb, "%02X", data[ii]);
		else
			sprintf(tempb, ",%02X", data[ii]);
		strcat(buf, tempb);
	}
	strcat(buf, ", ");
	char *sptr = buf+strlen(buf);
	for (ii=0;ii<size;ii++)
	{
		unsigned char ch = data[ii];
		//if (isalpha(ch)||isalnum(ch)||isdigit(ch)||isspace(ch))
		if((ch>=32)&&(ch<128))
			*sptr = ch;
		else
			*sptr = '.';
		sptr++;
	}
	*sptr = 0;

	strcat(buf, crlf);
	return puts(buf, strlen(buf));
}

//putSerialEventMsg(" EVENT ","SerialError:"+eventMsg);	
int logfile_timeStampClass::putSerialEventMsg(const char *portid,  const char *msg)
{
	//int ii;
	char buf[128];
	char buf1[32];
//	char tempb[32];
	
	strcpy(buf,portid);
	strcat(buf, ":");
	strcat(buf,DateTimeStr(buf1));
	strcat(buf, " ");
	/*
	for (ii=0;ii<strlen(msg);ii++)
	{
		if (ii==0)
			sprintf(tempb, "%02X", data[ii]);
		else
			sprintf(tempb, ",%02X", data[ii]);
		strcat(buf, tempb);
	}
	strcat(buf, ", ");
	*/
	char *sptr = buf+strlen(buf);
	for (size_t ii=0;ii<strlen(msg);ii++)
	{
		char ch = msg[ii];
		if((ch>=0)&&(ch<=13))
			*sptr = '.';
		else
		{
			*sptr = ch;
		}
		sptr++;
	}
	*sptr = 0;

	strcat(buf, crlf);

	return puts(buf, strlen(buf));
}
/*
int logfile_timeStampClass::putMsg(const char *portid, array<unsigned char> ^data, int size)
{
	int ii;
	char buf[128];
	char buf1[32];
	char tempb[32];
	strcpy(buf,portid);
	strcat(buf, ":");
	strcat(buf,DateTimeStr(buf1));
	strcat(buf, " ");
	for (ii=0;ii<size;ii++)
	{
		if (ii==0)
			sprintf(tempb, "%02X", data[ii]);
		else
			sprintf(tempb, ",%02X", data[ii]);
		strcat(buf, tempb);
	}
	strcat(buf, ", ");
	char *sptr = buf+strlen(buf);
	for (ii=0;ii<size;ii++)
	{
		char ch = data[ii];
		if((ch>=0)&&(ch<=13))
			*sptr = '.';
		else
		{
			*sptr = ch;
		}
		sptr++;
	}
	*sptr = 0;

	strcat(buf, crlf);
	return puts(buf, strlen(buf));
}
*/