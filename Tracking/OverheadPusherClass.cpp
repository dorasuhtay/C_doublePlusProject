
#include "StdAfx.h"

#include "tchar.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include "OverheadPusherClass.h"
#ifdef _MSC_VER
    #include "stringconversion.h"
#endif

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#ifdef _MSC_VER
	#define SSTRCPY	wcscpy_s
    #define returnTag(a, b)                                             \
        {                                                               \
        	if ((a<0)||(a>=max_OVERHEADPUSHER))                         \
                return NULLValue;                                       \
            return gcnew String(reinterpret_cast<const wchar_t*>(b));   \
        }
#else
	#define SSTRCPY	_tcscpy
    #define USING_GCC
    #define returnTag(a, b)                 \
        {                                   \
        	if ((a<0)||(a>=max_OVERHEADPUSHER))  \
                return NULLValue;           \
            return (b);                     \
        }
#endif

#define returnTAGValue(a,b) \
    {                                   \
	if ((a<0)||(a>=count))      \
		return 0;                       \
	return b;     \
    }

#define cfile_Name		"OVERHEADPUSHER.DAT\0\0"

const char c_endheaderCheckId[]			= {0xC5, 0x78, 0x23};
const char c_overhdrPusherFileHeader[]	= {0xE7, 0xA4, 0xD6};
const wchar_t *OverheadPusherClass::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
const char    *OverheadPusherClass::cgetfile_Name(){if (filepathname) return (char *)filepathname->cdata(); else return cfile_Name;}

OverheadPusherClass::OverheadPusherClass(const wchar_t *path)
{
	storeLock = 0;
	for (int ii=0;ii<max_OVERHEADPUSHER;ii++)
		memset(&overhdrPusher[ii], 0x0, sizeof(overhdrPusherType));

	//initialise file header
	memset(&overhdrPusherFileHeader, 0x0, sizeof(overhdrPusherFileHeaderType));
	overhdrPusherFileHeader.Idstring[0] = c_overhdrPusherFileHeader[0];
	overhdrPusherFileHeader.Idstring[1] = c_overhdrPusherFileHeader[1];
	overhdrPusherFileHeader.Idstring[2] = c_overhdrPusherFileHeader[2];
	overhdrPusherFileHeader.versionMajor = 1;
	overhdrPusherFileHeader.versionMinor = 0;
	overhdrPusherFileHeader.reccount = max_OVERHEADPUSHER;
	overhdrPusherFileHeader.endheaderCheckId[0] = c_endheaderCheckId[0];
	overhdrPusherFileHeader.endheaderCheckId[1] = c_endheaderCheckId[1];
	overhdrPusherFileHeader.endheaderCheckId[2] = c_endheaderCheckId[2];

	filepath  = new wctString(path);
	filepathname  = new wctString(path);
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));

	//and finally... read the data from file
	readDat();
}

OverheadPusherClass::~OverheadPusherClass()
{
	writeDat();
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

void OverheadPusherClass::Clear()
{
	for (int ii=0;ii<max_OVERHEADPUSHER;ii++)
		memset(&overhdrPusher[ii], 0x0, sizeof(overhdrPusherType));
	writeDat();
}

bool OverheadPusherClass::isPusherLoaded(int index){    returnTAGValue(index, overhdrPusher[index].PUSHERSTATUS);}
int OverheadPusherClass::getRounds(int index){    returnTAGValue(index, overhdrPusher[index].ROUND);}



/*
int OverheadPusherClass::getLoadedPusher(wctStringList *list)
{
	int ii;
	int found = 0;
	list->clear();
	for (ii=0;ii<count;ii++)
	{
		if(overhdrPusher[ii].PUSHERSTATUS)
		{
		}
		String ^opcode = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].OpCode));
		String ^prodid = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].ProdID));
		//*endindex = (ii+1)%count;
		if ((opcode==OpCode)&&(prodid==Prodid))
		{
			list->add( DesignCodeSequence[ii].PUSHERSTATUS);
			//memcpy(out[found], DesignCodeSequence[ii].StnID, 31);
			found++;
			//return gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].StnID));
		}
	}
	return found;
}
*/
int OverheadPusherClass::getData(int index, overhdrPusherType *ovrhdrpsh)
{
	if ((index<0)||(index>=max_OVERHEADPUSHER))
		return 0;
	memcpy(ovrhdrpsh, &overhdrPusher[index], sizeof(overhdrPusherType));
	return 1;
}

#ifdef _MSC_VER
void OverheadPusherClass::updateHangerStatus(int pusher, int rounds, String^ destSTNID, bool flush)
{
	if ((pusher<0)||(pusher>=max_OVERHEADPUSHER))
		return;
	String2CharArray(destSTNID, overhdrPusher[pusher].destSTNID);
	overhdrPusher[pusher].ROUND = rounds;		//set to number of runds
	if (flush)
		writeDat();
}
#endif
#ifdef _MSC_VER
void OverheadPusherClass::LoadHanger(int pusher, String^ srcSTNID, String^ destSTNID, String^ HangerID, bool flush)
{
	//int stnid;
	//stnid = Convert::ToInt32(ID);
	//pusher = (pusher-1)%count;
	if ((pusher<0)||(pusher>=max_OVERHEADPUSHER))
		return;
	String2CharArray(srcSTNID, overhdrPusher[pusher].srcSTNID);
	String2CharArray(destSTNID, overhdrPusher[pusher].destSTNID);
	String2CharArray(HangerID, overhdrPusher[pusher].Hanger_ID);
	overhdrPusher[pusher].PUSHERSTATUS = 1;		//set to loaded hanger
	if (flush)
		writeDat();
}
#endif


#ifdef _MSC_VER
void OverheadPusherClass::unLoadHanger(int pusher, bool flush)
{
	if ((pusher<0)||(pusher>=max_OVERHEADPUSHER))
		return;
	overhdrPusher[pusher].Hanger_ID[0]=0x0;
	overhdrPusher[pusher].srcSTNID[0]=0x0;
	overhdrPusher[pusher].destSTNID[0]=0x0;
	overhdrPusher[pusher].PUSHERSTATUS=0;
	overhdrPusher[pusher].ROUND = 0;
	/*
	memset(&overhdrPusher[pusher].Hanger_ID, 0x0, sizeof(overhdrPusher[pusher].Hanger_ID));
	SSTRCPY(overhdrPusher[pusher].Hanger_ID,L"");
	SSTRCPY(overhdrPusher[pusher].srcSTNID,L"");
	SSTRCPY(overhdrPusher[pusher].destSTNID,L"");
	overhdrPusher[pusher].ROUND = 0;
	*/
	if (flush)
		writeDat();
}
#endif

//const char *OverheadPusherClass::getfile_Name(){return file_OVERHEADPUSHER;}

STRINGPTR OverheadPusherClass::getHangerID(int pusher)
{
    returnTag(pusher, overhdrPusher[pusher].Hanger_ID);
    /*
	if ((pusher<0)||(pusher>=max_OVERHEADPUSHER))
		return "";
	String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(overhdrPusher[pusher].Hanger_ID));
	return temp;
	*/
}


STRINGPTR OverheadPusherClass::getHangerSrcStation(int pusher)
{
    returnTag(pusher, overhdrPusher[pusher].srcSTNID);
    /*
	if ((pusher<0)||(pusher>=max_OVERHEADPUSHER))
		return "";
	String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(overhdrPusher[pusher].srcSTNID));
	return temp;*/
}

STRINGPTR OverheadPusherClass::getHangerDestStation(int pusher)
{
    returnTag(pusher, overhdrPusher[pusher].destSTNID);
    /*
	if ((pusher<0)||(pusher>=max_OVERHEADPUSHER))
		return "";
	String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(overhdrPusher[pusher].destSTNID));
	return temp;*/
}

int OverheadPusherClass::getpCount(int pusher)
{
	if ((pusher>=0)||(pusher<max_OVERHEADPUSHER))
	{
		return overhdrPusher[pusher].pCount;
	}
	return -1;
}

int OverheadPusherClass::getPusher_Count(int pusher)
{
	if ((pusher>=0)||(pusher<max_OVERHEADPUSHER))
	{
		return overhdrPusher[pusher].Pusher_Count;
	}
	return -1;
}

int OverheadPusherClass::getRemainder(int pusher)
{
	int remainder = 0;
	if ((pusher>=0)||(pusher<max_OVERHEADPUSHER))
	{
		int Pusher_Count = overhdrPusher[pusher].Pusher_Count;
		int pCount = overhdrPusher[pusher].pCount;
		remainder = Pusher_Count-pCount;
		if (remainder<0)
			remainder = (count - pCount)+Pusher_Count;
	}
	return remainder;
}


#ifdef _MSC_VER
int OverheadPusherClass::findHanger(STRINGPTR HangerID, STRINGPTR Dest)
{
	int ii;
	for (ii=0;ii<count;ii++)
	{
		STRINGPTR hangerID = gcnew String(reinterpret_cast<const wchar_t*>(overhdrPusher[ii].Hanger_ID));
		STRINGPTR dest = gcnew String(reinterpret_cast<const wchar_t*>(overhdrPusher[ii].destSTNID));
		if ((dest==Dest)&&(hangerID==HangerID))
			return ii;
	}
	return -1;
}
#endif
#ifdef _MSC_VER
void OverheadPusherClass::setPusherUnloadStatus(STRINGPTR HangerID, STRINGPTR STNDest, int pCount, int Pusher_Count)
{
	int index = findHanger(HangerID, STNDest);
	if ((index>=0)&&(index<count))
	{
		overhdrPusher[index].pCount = pCount;
		overhdrPusher[index].Pusher_Count = Pusher_Count;
	}
}
#endif

void OverheadPusherClass::readDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&overhdrPusherFileHeader, sizeof(overhdrPusherFileHeaderType), 1, fp);
		count = overhdrPusherFileHeader.reccount;
		for (int ii=0;ii<overhdrPusherFileHeader.reccount;ii++)
		{
			fread(&overhdrPusher[ii], sizeof(overhdrPusherType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}

void OverheadPusherClass::writeDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
		overhdrPusherFileHeader.reccount = count;
		fwrite(&overhdrPusherFileHeader, sizeof(overhdrPusherFileHeaderType), 1, fp);
		for (int ii=0;ii<overhdrPusherFileHeader.reccount;ii++)
		{
			fwrite(&overhdrPusher[ii], sizeof(overhdrPusherType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}
