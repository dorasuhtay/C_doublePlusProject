#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include "xplatform_define.h"
#include "HangerTagClass.h"


#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

#ifdef _MSC_VER
    #include "stringconversion.h"
    #define returnTag(a, b)                                             \
        {                                                               \
        	if ((a<0)||(a>=max_HANGERTAG))                              \
                return NULLValue;                                       \
            return gcnew String(reinterpret_cast<const wchar_t*>(b));   \
        }
#else
    #define USING_GCC
    #define returnTag(a, b)                 \
        {                                   \
        	if ((a<0)||(a>=max_HANGERTAG))  \
                return NULLValue;           \
            return (b);                     \
        }
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



#define cfile_Name		"HANGERTAG.DAT\0\0"

const unsigned char c_hangerTagendheaderCheckId[]		= {0xC5,0x78,0x23};  
const unsigned char c_hangerTagFileHeader[]				= {0xE7,0xA4,0xD6};
const wchar_t *HangerTagClass::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
const char    *HangerTagClass::cgetfile_Name(){if (filepathname) return (char *)filepathname->cdata(); else return cfile_Name;}
HangerTagClass::HangerTagClass(const wchar_t *path)
{
	count = 0;
	storeLock = 0;
	for (int ii=0;ii<max_HANGERTAG;ii++)
		memset(&HangerTag[ii], 0x0, sizeof(HangerTagType));

	//initialise file header
	memset(&HangerTagFileHeader, 0x0, sizeof(HangerTagFileHeaderType));
	HangerTagFileHeader.Idstring[0] = c_hangerTagFileHeader[0];
	HangerTagFileHeader.Idstring[1] = c_hangerTagFileHeader[1];
	HangerTagFileHeader.Idstring[2] = c_hangerTagFileHeader[2];
	HangerTagFileHeader.versionMajor = 1;
	HangerTagFileHeader.versionMinor = 0;
	HangerTagFileHeader.reccount = max_HANGERTAG;
	HangerTagFileHeader.endheaderCheckId[0] = c_hangerTagendheaderCheckId[0];
	HangerTagFileHeader.endheaderCheckId[1] = c_hangerTagendheaderCheckId[1];
	HangerTagFileHeader.endheaderCheckId[2] = c_hangerTagendheaderCheckId[2];

	filepath  = new wctString(path);
	filepathname  = new wctString(path);
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));


	//and finally... read the data from file
	readDat();
}

HangerTagClass::~HangerTagClass()
{
	writeDat();
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

void HangerTagClass::Clear()
{
	for (int ii=0;ii<max_HANGERTAG;ii++)
		memset(&HangerTag[ii], 0x0, sizeof(HangerTagType));
	count=0;
	writeDat();
}

#ifndef __GNUC__
void HangerTagClass::add(String ^Hanger_ID, String ^DesignCode, String ^OPCODE, String ^STNID, int BundlSeqSeqNo,  String ^EmpId)
{
	if ((count<0)||(count>=max_HANGERTAG)) return;

	int index = find(Hanger_ID);
	if(index<0)
	{
		index = count;
		count++;
	}


	String2CharArray(Hanger_ID, HangerTag[index].Hanger_ID);
	String2CharArray(DesignCode, HangerTag[index].DesignCode);
	String2CharArray(OPCODE, HangerTag[index].OPCODE);
	String2CharArray(STNID, HangerTag[index].STNID);
	String2CharArray(EmpId, HangerTag[index].EmpId);
	HangerTag[index].BundlSeqSeqNo = BundlSeqSeqNo;
	//HangerTag[index].CMDID = CMDID;

	
/*
	int numof_OpCodeSequence_t = min(max_OPCODESEQUENCE, numof_OpCodeSequence);
	for (int ii=0;ii<numof_OpCodeSequence_t;ii++)
	{
		HangerTag[index].OpCodeSequence[ii] = OpCodeSequence[ii];
	}
*/
//	HangerTag[index].valid = 1;

}
#endif



STRINGPTR HangerTagClass::getDesignCode(int index)
{
	//if ((index<0)||(index>=max_HANGERTAG))
	//	return NULLValue;
    returnTag(index, HangerTag[index].DesignCode);
/*
    #ifndef __GNUC__
	return gcnew String(reinterpret_cast<const wchar_t*>(HangerTag[index].DesignCode));
	#else
    return HangerTag[index].DesignCode;
	#endif
	*/
}

STRINGPTR HangerTagClass::getHangerOPCODE(int index)
{
	//if ((index<0)||(index>=max_HANGERTAG))
		//return NULLValue;
    returnTag(index, HangerTag[index].OPCODE);
	//String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(HangerTag[index].OPCODE));
	//return temp;
}

STRINGPTR HangerTagClass::getHangerSTNID(int index)
{
    returnTag(index, HangerTag[index].STNID);
    /*
	if ((index<0)||(index>=max_HANGERTAG))
		return NULLValue;
	String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(HangerTag[index].STNID));
	return temp;*/
}

STRINGPTR HangerTagClass::getHangerEmpId(int index)
{
    returnTag(index, HangerTag[index].EmpId);
    /*
	if ((index<0)||(index>=max_HANGERTAG))
		return "";
	String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(HangerTag[index].EmpId));
	return temp;*/
}
int HangerTagClass::getBundlSeqSeqNo(int index)
{
    //returnTag(index, HangerTag[index].BundlSeqSeqNo);
	if ((index<0)||(index>=max_HANGERTAG))
		return -1;
	return HangerTag[index].BundlSeqSeqNo;
}

#ifndef __GNUC__
 void HangerTagClass::setNextStation(String ^Hanger_ID, String ^NxtSTNID, String ^dbgloc)
 {
	int index = find(Hanger_ID);
	if(index>=0)
	{
		if (NxtSTNID==nullptr)
			NxtSTNID = "NULL";
		String2CharArray(NxtSTNID, HangerTag[index].NxtSTNID);
		String2CharArray(dbgloc, HangerTag[index].dbgloc);
	}
    writeDat();
 }
#endif

 /*
void HangerTagClass::setSkipCount(STRINGPTR Hanger_ID, bool state)
 {
	int index = find(Hanger_ID);
	if(index>=0)
		HangerTag[index].skipCount=state;
    writeDat();
 }

bool HangerTagClass::getSkipCount(STRINGPTR Hanger_ID)
 {
	int index = find(Hanger_ID);
	if(index>=0)
		return HangerTag[index].skipCount;
    return 0;
 }
 */

#ifndef __GNUC__
void HangerTagClass::updateSequence(String ^Hanger_ID, int seqNo, int nextseqNo)
{
	int index = find(Hanger_ID);
	if ((index>=0)&&(index<max_HANGERTAG))
	{
		HangerTag[index].seqNo = seqNo;
		HangerTag[index].nextseqNo = nextseqNo;
	}
}
#endif
/*
#ifndef __GNUC__
void HangerTagClass::updateNextSequenceNo(String ^Hanger_ID, int seqNo, int nextseqNo)
{
	int index = find(Hanger_ID);
	if ((index>=0)&&(index<max_HANGERTAG))
	{
		HangerTag[index].seqNo = seqNo;
		HangerTag[index].nextseqNo = nextseqNo;
	}
}
#endif
*/
int HangerTagClass::find(STRINGPTR Hanger_ID)
{
	for (int ii=0;ii<count;ii++)
	{
        #ifndef __GNUC__
		String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(HangerTag[ii].Hanger_ID));
		if (temp==Hanger_ID)
			return ii;
        #else
        if (_tcscmp(Hanger_ID, HangerTag[ii].Hanger_ID)==0)
            return ii;
        #endif
	}
	return -1;
}




int HangerTagClass::getBundlSeqSeqNo(STRINGPTR Hanger_ID)
{
	int index = find(Hanger_ID);
	if ((index>=0)&&(index<count))
		return HangerTag[index].BundlSeqSeqNo;
	else
		return 0;
}

STRINGPTR HangerTagClass::getOpCode(STRINGPTR Hanger_ID)
{
	int index = find(Hanger_ID);
	returnTag(index, HangerTag[index].OPCODE);
	/*
	if ((index>=0)&&(index<max_HANGERTAG))
		return gcnew String(reinterpret_cast<const wchar_t*>(HangerTag[index].OPCODE));
	return "null";
	*/
}



#ifndef __GNUC__
void HangerTagClass::clear(String ^Hanger_ID)
{
	int index = find(Hanger_ID);
	if ((index>=0)&&(index<max_HANGERTAG))
	{
		HangerTag[index].seqNo = 0;
		HangerTag[index].nextseqNo = 0;
	}
}
#endif

int HangerTagClass::getSeqNo(int index)
{
	if ((index<0)||(index>=max_HANGERTAG))
		return 0;
	return HangerTag[index].seqNo;
}

int HangerTagClass::getNextSeqNo(int index)
{
	if ((index<0)||(index>=max_HANGERTAG))
		return 0;
	return HangerTag[index].nextseqNo;
}

int HangerTagClass::getNextSeqNo(STRINGPTR Hanger_ID)
{
	int index = find(Hanger_ID);
	if ((index>=0)&&(index<max_HANGERTAG))
		return HangerTag[index].nextseqNo;
	return 0;
}

int HangerTagClass::getSeqNo(STRINGPTR Hanger_ID)
{
	int index = find(Hanger_ID);
	if ((index>=0)&&(index<max_HANGERTAG))
		return HangerTag[index].seqNo;
	return 0;
}

/*
void HangerTagClass::clear(String ^Hanger_ID)
{
	int index = find(Hanger_ID);
	if (index>=0)
	{
		memset(&HangerTag[index], 0x0, sizeof(HangerTagType));
		HangerTag[count].valid = 0;
	}
}
*/
/*
void HangerTagClass::LoadHanger(String^ ID, String^ HangerID, bool flush)
{
	int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_HANGERTAG))
		return;
	String2CharArray(HangerID, HangerTag[stnid].Hanger_ID);
	if (flush)
		writeDat();
}

void HangerTagClass::unLoadHanger(String^ ID, bool flush)
{
		int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_HANGERTAG))
		return;
	memset(&HangerTag[stnid].Hanger_ID, 0x0, sizeof(HangerTag[stnid].Hanger_ID));
	if (flush)
		writeDat();
}

String^ HangerTagClass::getHangerID(String^ ID)
{
	int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_HANGERTAG))
		return "";
	String ^temp = gcnew String(reinterpret_cast<const char*>(HangerTag[stnid].Hanger_ID));
	return temp;
}

*/
STRINGPTR HangerTagClass::getHangerID(int index)
{
    returnTag(index, HangerTag[index].Hanger_ID);
    /*
	if ((index<0)||(index>=max_HANGERTAG))
		return "";
	String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(HangerTag[index].Hanger_ID));
	return temp;
	*/
}
STRINGPTR HangerTagClass::getNextStation(int index)
{
    returnTag(index, HangerTag[index].NxtSTNID);
/*
	if ((index<0)||(index>=max_HANGERTAG))
		return "";
	String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(HangerTag[index].NxtSTNID));
	return temp;
	*/
}

STRINGPTR HangerTagClass::getdbgloc(int index)
{
    returnTag(index, HangerTag[index].dbgloc);
    /*
	if ((index<0)||(index>=max_HANGERTAG))dbgloc
		return "";
	String ^temp = gcnew String(reinterpret_cast<const wchar_t*>(HangerTag[index].dbgloc));
	return temp;
	*/
}

//const char *HangerTagClass::getfile_Name(){return file_HANGERTAG;}

void HangerTagClass::readDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&HangerTagFileHeader, sizeof(HangerTagFileHeaderType), 1, fp);
		count = HangerTagFileHeader.reccount;
		for (int ii=0;ii<HangerTagFileHeader.reccount;ii++)
		{
			fread(&HangerTag[ii], sizeof(HangerTagType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}

void HangerTagClass::writeDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
	    HangerTagFileHeader.reccount = count;
		fwrite(&HangerTagFileHeader, sizeof(HangerTagFileHeaderType), 1, fp);
		for (int ii=0;ii<HangerTagFileHeader.reccount;ii++)
		{
			fwrite(&HangerTag[ii], sizeof(HangerTagType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}
