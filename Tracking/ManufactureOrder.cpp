#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include "xplatform_define.h"
#include "ManufactureOrder.h"
#include "idate.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#ifdef _MSC_VER
	#include < vcclr.h >
    #include "stringconversion.h"
    #define returnTag(a, b, c)                                             \
        {                                                               \
			if (!b) return NULLValue;				\
        	if ((a<0)||(a>=max_MANUFACTUREORDER))                              \
                return NULLValue;                                       \
            return gcnew String(reinterpret_cast<const wchar_t*>(c));   \
        }
#else
    #define USING_GCC
    #define returnTag(a, b, c)                 \
        {                                   \
			if (!b) return NULLValue;			\
        	if ((a<0)||(a>=max_MANUFACTUREORDER))  \
                return NULLValue;           \
            return (c);                     \
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



#define cfile_Name		"MANUFACTORDER.DAT\0\0"

const unsigned char c_mono_endheaderCheckId[]		= {0xE5,0x58,0x23};  
const unsigned char c_mono_FileHeader[]				= {0xC7,0xA3,0xD5};
const wchar_t *ManufactureOrder::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
const char    *ManufactureOrder::cgetfile_Name(){if (filepathname) return (char *)filepathname->cdata(); else return cfile_Name;}

ManufactureOrder::ManufactureOrder(const wchar_t *path)
{
	count = 0;
	storeLock = 0;
	for (int ii=0;ii<max_MANUFACTUREORDER;ii++)
		monoRec[ii] = 0;


	//initialise file header
	memset(&monoRecFileHeader, 0x0, sizeof(MONO_FileHeaderType));
	monoRecFileHeader.Idstring[0] = c_mono_FileHeader[0];
	monoRecFileHeader.Idstring[1] = c_mono_FileHeader[1];
	monoRecFileHeader.Idstring[2] = c_mono_FileHeader[2];
	monoRecFileHeader.versionMajor = 1;
	monoRecFileHeader.versionMinor = 0;
	monoRecFileHeader.reccount = max_MANUFACTUREORDER;
	monoRecFileHeader.endheaderCheckId[0] = c_mono_endheaderCheckId[0];
	monoRecFileHeader.endheaderCheckId[1] = c_mono_endheaderCheckId[1];
	monoRecFileHeader.endheaderCheckId[2] = c_mono_endheaderCheckId[2];

	filepath  = new wctString(path);
	filepathname  = new wctString(*filepath);
	//filepathname = filepath;
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));


	//and finally... read the data from file
	if (readDat())
		remove((char *)filepathname->cdata());
}

ManufactureOrder::~ManufactureOrder()
{
	writeDat();
	for (int ii=0;ii<max_MANUFACTUREORDER;ii++)
		SAFE_DELETE(monoRec[ii]);
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

void ManufactureOrder::setProdline(int Prodline)
{
	monoRecFileHeader.Productionline = Prodline;
	clearNot(monoRecFileHeader.Productionline);

	monoRecFileHeader.highestmaxbundleno = findlargestBundleNo();

	/*
	TIntlDate date1(1, 9, 2012);
	TIntlDate date2(19, 9, 2012);

	unsigned long diff = date2-date1;

	*/
}



void ManufactureOrder::Clear(bool flush)
{
	for (int ii=0;ii<max_MANUFACTUREORDER;ii++)
		SAFE_DELETE(monoRec[ii]);
	count = 0;
	if (flush)
		writeDat();
}

#ifndef __GNUC__
void ManufactureOrder::add(STRINGPTR mono, int prodline, int maxbundleno, int Day, int Month, int Year)
{
	if ((count<0)||(count>=max_MANUFACTUREORDER)) return;

	int index = find(mono, prodline);
	if(index<0)
	{
		index = count;
		count++;
	}
	monoRec[index] = new MONO_Type;
	memset(monoRec[index], 0x0, sizeof(MONO_Type));
	#ifdef _MSC_VER
		pin_ptr<const wchar_t> wch_mono = PtrToStringChars(mono);
		_tcscpy_s(monoRec[index]->MONO, wch_mono);
	#else
		String2CharArray(mono, monoRec[index]->MONO);
	#endif
	monoRec[index]->prodline = prodline;
	monoRec[index]->maxbundleno  = maxbundleno;
	monoRec[index]->day = Day;
	monoRec[index]->month = Month;
	monoRec[index]->year = Year;
	writeDat();
}
#endif


int ManufactureOrder::getmaxbundleno(int index)
{
	if (index<0) return 0;
	if (index>=count) return 0;
	if (!monoRec[index]) return 0;
    return monoRec[index]->maxbundleno;
}


STRINGPTR ManufactureOrder::getMONO(int index)
{
    returnTag(index, monoRec[index], monoRec[index]->MONO);
}







#ifndef __GNUC__

#endif


int ManufactureOrder::find(STRINGPTR mono, int prodline)
{
	for (int ii=0;ii<count;ii++)
	{
		if (!monoRec[ii]) continue;
		#ifndef __GNUC__
		pin_ptr<const wchar_t> wch = PtrToStringChars(mono);
        if ((_tcscmp(wch, monoRec[ii]->MONO)==0)&&(prodline==monoRec[ii]->prodline))
            return ii;
		#else
        if ((_tcscmp(mono, monoRec[ii]->MONO)==0)&&(prodline==monoRec[ii]->prodline))
            return ii;
		#endif
        //#endif
	}
	return -1;
}








void ManufactureOrder::clear(STRINGPTR mono, int Prodline)
{
	int index = find(mono, Prodline);
	if ((monoRec[index])&&(index>=0)&&(index<max_MANUFACTUREORDER))
	{
		_tcscpy_s(monoRec[index]->MONO, L"");
		monoRec[index]->maxbundleno = 0;
		monoRec[index]->prodline = 0;
		packarray();
		writeDat();
	}
}



int ManufactureOrder::findlargestBundleNo()
{
	int ii;
	int maxnum = 0;
	for (ii=0;ii<count;ii++)
	{
		if (!monoRec[ii]) continue;
		if (monoRec[ii]->maxbundleno>maxnum)
			maxnum = monoRec[ii]->maxbundleno;
	}
	return maxnum;
}

void ManufactureOrder::clearNot(int Prodline)
{
	int ii;
	int counter = 0;
	for (ii=0;ii<count;ii++)
	{
		if (!monoRec[ii]) continue;
		if (monoRec[ii]->prodline!=Prodline)
		{
			_tcscpy_s(monoRec[ii]->MONO, L"");
			counter++;
		}
	}
	if (counter>0)
	{
		packarray();
		writeDat();
	}
}


void ManufactureOrder::packarray()
{
	int ii, jj;
	if (count<=0) return;
	for (ii=0;ii<count;ii++)
	{
		if (!monoRec[ii]) continue;
		if (_tcscmp(monoRec[ii]->MONO,L"")==0)
		{
			for (jj=ii;jj<count-1;jj++)
			{
				if (!monoRec[jj]) continue;
				if (!monoRec[jj+1]) continue;
				memcpy(monoRec[jj], monoRec[jj+1], sizeof(MONO_Type));
			}
			if (count==0) 
				break;
			count--;
		}
	}

}




int ManufactureOrder::readDat()
{
	int error = 0;
	while(storeLock)
		Sleep(1);
	storeLock = 1;
	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&monoRecFileHeader, sizeof(MONO_FileHeaderType), 1, fp);
		if (monoRecFileHeader.endheaderCheckId[0] != c_mono_endheaderCheckId[0])	error = 1;
		if (monoRecFileHeader.endheaderCheckId[1] != c_mono_endheaderCheckId[1])	error = 1;
		if (monoRecFileHeader.endheaderCheckId[2] != c_mono_endheaderCheckId[2])	error = 1;
		if (monoRecFileHeader.Idstring[0] != c_mono_FileHeader[0])	error = 1;
		if (monoRecFileHeader.Idstring[1] != c_mono_FileHeader[1])	error = 1;
		if (monoRecFileHeader.Idstring[2] != c_mono_FileHeader[2])	error = 1;
		if (monoRecFileHeader.reccount>=max_MANUFACTUREORDER)	error = 1;
		if (!error)
		{
			count = 0;
			int ii;
			for (ii=0;ii<monoRecFileHeader.reccount;ii++)
			{
				if (!monoRec[ii])
					monoRec[ii] = new MONO_Type;
				fread(monoRec[ii], sizeof(MONO_Type), 1, fp);
				count++;
			}

			//to prevent holes...
			for (int jj=ii; jj<max_MANUFACTUREORDER;jj++)
				SAFE_DELETE(monoRec[jj]);
		}
		fclose(fp);
	}
	storeLock = 0;
	return error;
}

void ManufactureOrder::writeDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
	    monoRecFileHeader.reccount = count;
		fwrite(&monoRecFileHeader, sizeof(MONO_FileHeaderType), 1, fp);
		for (int ii=0;ii<monoRecFileHeader.reccount;ii++)
		{
			if (monoRec[ii])
				fwrite(monoRec[ii], sizeof(MONO_Type), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}
