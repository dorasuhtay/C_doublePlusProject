#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include "xplatform_define.h"
#include "helpRequestClass.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#ifdef _MSC_VER
	#include < vcclr.h >
    #include "stringconversion.h"
    #define returnTag(a, b)                                             \
        {                                                               \
        	if ((a<0)||(a>=max_HELPREQUEST))                              \
                return NULLValue;                                       \
            return gcnew String(reinterpret_cast<const wchar_t*>(b));   \
        }
#else
    #define USING_GCC
    #define returnTag(a, b)                 \
        {                                   \
        	if ((a<0)||(a>=max_HELPREQUEST))  \
                return NULLValue;           \
            return (b);                     \
        }
#endif

#if defined(__WINDOWS__)

#endif
/*
//#ifndef WINVER
    // the only exception to the above is MSVC 6 which has a time bomb in its
    // headers: they warn against using them with WINVER >= 0x0500 as they
    // contain only part of the declarations and they're not always correct, so
    // don't define WINVER for it at all as this allows everything to work as
    // expected both with standard VC6 headers (which define WINVER as 0x0400
    // by default) and headers from a newer SDK (which may define it as 0x0500)
    #if !defined(__VISUALC__) || (__VISUALC__ >= 1300)
        //#define WINVER 0x0600

    #endif
//#endif
*/



#define cfile_Name		"HELPREQUEST.DAT\0\0"

const unsigned char c_helprequestendheaderCheckId[]		= {0xC5,0x78,0x23};  
const unsigned char c_helprequestFileHeader[]				= {0xE7,0xA4,0xD6};
const wchar_t *helpRequestClass::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
const char    *helpRequestClass::cgetfile_Name(){if (filepathname) return (char *)filepathname->cdata(); else return cfile_Name;}

helpRequestClass::helpRequestClass(const wchar_t *path)
{
	count = 0;
	storeLock = 0;
	for (int ii=0;ii<max_HELPREQUEST;ii++)
		memset(&helpRequest[ii], 0x0, sizeof(helpRequestType));

	//initialise file header
	memset(&helpRequestFileHeader, 0x0, sizeof(helpRequestFileHeaderType));
	helpRequestFileHeader.Idstring[0] = c_helprequestFileHeader[0];
	helpRequestFileHeader.Idstring[1] = c_helprequestFileHeader[1];
	helpRequestFileHeader.Idstring[2] = c_helprequestFileHeader[2];
	helpRequestFileHeader.versionMajor = 1;
	helpRequestFileHeader.versionMinor = 0;
	helpRequestFileHeader.reccount = max_HELPREQUEST;
	helpRequestFileHeader.endheaderCheckId[0] = c_helprequestendheaderCheckId[0];
	helpRequestFileHeader.endheaderCheckId[1] = c_helprequestendheaderCheckId[1];
	helpRequestFileHeader.endheaderCheckId[2] = c_helprequestendheaderCheckId[2];

	filepath  = new wctString(path);
	filepathname  = new wctString(*filepath);
	//filepathname = filepath;
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));


	//and finally... read the data from file
	readDat();
}

helpRequestClass::~helpRequestClass()
{
	writeDat();
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

void helpRequestClass::Clear()
{
	count=0;
	for (int ii=0;ii<max_HELPREQUEST;ii++)
		memset(&helpRequest[ii], 0x0, sizeof(helpRequestType));
	writeDat();
}

#ifndef __GNUC__
void helpRequestClass::add(STRINGPTR STNID, STRINGPTR helpMsg)
{
	if ((count<0)||(count>=max_HELPREQUEST)) return;

	int index = find(STNID);
	if(index<0)
	{
		index = count;
		count++;
	}
	#ifdef _MSC_VER
		pin_ptr<const wchar_t> wch_helpMsg = PtrToStringChars(helpMsg);
		pin_ptr<const wchar_t> wch_STNID = PtrToStringChars(STNID);
		_tcscpy_s(helpRequest[index].helpMsg, wch_helpMsg);
		_tcscpy_s(helpRequest[index].STNID, wch_STNID);
	#else
		String2CharArray(helpMsg, helpRequest[index].helpMsg);
		String2CharArray(STNID, helpRequest[index].STNID);
	#endif
	writeDat();
}
#endif


STRINGPTR helpRequestClass::getSTNID(int index)
{
    returnTag(index, helpRequest[index].STNID);
}


STRINGPTR helpRequestClass::getMessage(int index)
{
    returnTag(index, helpRequest[index].helpMsg);
}







#ifndef __GNUC__

#endif


int helpRequestClass::find(STRINGPTR STNID)
{
	for (int ii=0;ii<count;ii++)
	{
		/*
        #ifndef __GNUC__
		String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(helpRequest[ii].STNID));
		temp->Trim();
		STNID->Trim();
		if (temp==STNID)
			return ii;
        #else
		*/
		#ifndef __GNUC__
		pin_ptr<const wchar_t> wch = PtrToStringChars(STNID);
        if (_tcscmp(wch, helpRequest[ii].STNID)==0)
            return ii;
		#else
        if (_tcscmp(STNID, helpRequest[ii].STNID)==0)
            return ii;
		#endif
        //#endif
	}
	return -1;
}








void helpRequestClass::clear(STRINGPTR STNID)
{
	int index = find(STNID);
	if ((index>=0)&&(index<max_HELPREQUEST))
	{
		_tcscpy_s(helpRequest[index].STNID, L"");
		_tcscpy_s(helpRequest[index].helpMsg, L"");
	}
	packarray();
	writeDat();
}



void helpRequestClass::packarray()
{
	int ii, jj;
	if (count<=0) return;
	for (ii=0;ii<count;ii++)
	{
		if (_tcscmp(helpRequest[ii].STNID,L"")==0)
		{
			for (jj=ii;jj<count-1;jj++)
			{
				memcpy(&helpRequest[jj], &helpRequest[jj+1], sizeof(helpRequestType));
			}
			if (count==0) 
				break;
			count--;
		}
	}

}




void helpRequestClass::readDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&helpRequestFileHeader, sizeof(helpRequestFileHeaderType), 1, fp);
		count = helpRequestFileHeader.reccount;
		for (int ii=0;ii<helpRequestFileHeader.reccount;ii++)
		{
			fread(&helpRequest[ii], sizeof(helpRequestType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}

void helpRequestClass::writeDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
	    helpRequestFileHeader.reccount = count;
		fwrite(&helpRequestFileHeader, sizeof(helpRequestFileHeaderType), 1, fp);
		for (int ii=0;ii<helpRequestFileHeader.reccount;ii++)
		{
			fwrite(&helpRequest[ii], sizeof(helpRequestType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}
