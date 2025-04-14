//DesignCodeSequenceClass

#include "StdAfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include "DesignCodeSequenceClass.h"
#include "stringconversion.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}
#define cfile_Name		"DesignCodeSequence.DAT\0\0"

const char c_DesignCodeSequenceendheaderCheckId[]		= {0x25,0xE8,0x13};
const char c_DesignCodeSequenceFileHeader[]				= {0x77,0x54,0x63};
const wchar_t *DesignCodeSequenceClass::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
 
DesignCodeSequenceClass::DesignCodeSequenceClass(const wchar_t *path)
{
	count = 0;
	storeLock = 0;
	for (int ii=0;ii<max_DesignCodeSequence;ii++)
		memset(&DesignCodeSequence[ii], 0x0, sizeof(DesignCodeSequenceType));

	//initialise file header
	memset(&DesignCodeSequenceFileHeader, 0x0, sizeof(DesignCodeSequenceFileHeaderType));
	DesignCodeSequenceFileHeader.Idstring[0] = c_DesignCodeSequenceFileHeader[0];
	DesignCodeSequenceFileHeader.Idstring[1] = c_DesignCodeSequenceFileHeader[1];
	DesignCodeSequenceFileHeader.Idstring[2] = c_DesignCodeSequenceFileHeader[2];
	DesignCodeSequenceFileHeader.versionMajor = 1;
	DesignCodeSequenceFileHeader.versionMinor = 0;
	DesignCodeSequenceFileHeader.reccount = max_DesignCodeSequence;
	DesignCodeSequenceFileHeader.endheaderCheckId[0] = c_DesignCodeSequenceendheaderCheckId[0];
	DesignCodeSequenceFileHeader.endheaderCheckId[1] = c_DesignCodeSequenceendheaderCheckId[1];
	DesignCodeSequenceFileHeader.endheaderCheckId[2] = c_DesignCodeSequenceendheaderCheckId[2];

	filepath  = new wctString(path);
	filepathname  = new wctString(path);
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));


	remove(filepathname->cdata());
	//and finally... read the data from file
	readDat();
}

DesignCodeSequenceClass::~DesignCodeSequenceClass()
{
	writeDat();
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

void DesignCodeSequenceClass::clear()
{
	count = 0;
	for (int ii=0;ii<max_DesignCodeSequence;ii++)
		memset(&DesignCodeSequence[ii], 0x0, sizeof(DesignCodeSequenceType));
}

void DesignCodeSequenceClass::exportToCSV(const char *filename)
{
	int ii;
	//char buf[128];
	FILE *fp = fopen(filename, "w+t");
	if(fp)
	{
		for (ii=0;ii<count;ii++)
		{
			//wchar_t2CharArray(DesignCodeSequence[ii].ProdID, buf);
			_ftprintf(fp, _T("%s, %s, %s, %d\r"),	DesignCodeSequence[ii].StnID,
								DesignCodeSequence[ii].ProdID,
								DesignCodeSequence[ii].OpCode,
								DesignCodeSequence[ii].seqno);
/*
			fprintf(fp, 
					String2CharArray(ProdID, DesignCodeSequence[count].ProdID);
		String2CharArray(OpCode, DesignCodeSequence[count].OpCode);
		String2CharArray(StnID, DesignCodeSequence[count].StnID);
	
		DesignCodeSequence[count].seqno = seqno;
			//fprintf(
			*/
		}
		fclose(fp);
	}
}

void DesignCodeSequenceClass::add(String ^prodID, String ^stnID, String ^opCode, String ^DesignCode, int seqno)
{
	if ((count<0)||(count>=max_DesignCodeSequence)) return;

	String2CharArray(prodID, DesignCodeSequence[count].ProdID);
	String2CharArray(opCode, DesignCodeSequence[count].OpCode);
	String2CharArray(stnID, DesignCodeSequence[count].StnID);
	String2CharArray(DesignCode, DesignCodeSequence[count].DesignCode);

	
	DesignCodeSequence[count].seqno = seqno;
	count++;
	writeDat();
}
/*
String ^DesignCodeSequenceClass::getOpCode(String ^STNID, String ^Prodid)
{
	int ii;
	String ^str = "";
	wchar_t stnid[64];
	wchar_t prodid[64];
	String2CharArray(STNID, stnid);
	String2CharArray(Prodid, prodid);
	for (ii=0;ii<count;ii++)
	{
		if((_tcscmp(stnid, DesignCodeSequence[ii].StnID)==0)&&
			(_tcscmp(prodid, DesignCodeSequence[ii].ProdID)==0))
		{
			str = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].OpCode));
		}
	}
	return str;
}
*/

int DesignCodeSequenceClass::getStationID(String ^OpCode, String ^Prodid, wctStringList *list)
{
	int ii;
	int found = 0;
	list->clear();
	for (ii=0;ii<count;ii++)
	{
		String ^opcode = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].OpCode));
		String ^prodid = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].ProdID));
		//*endindex = (ii+1)%count; 
		if ((opcode==OpCode)&&(prodid==Prodid))
		{
			list->add( DesignCodeSequence[ii].StnID);
			//memcpy(out[found], DesignCodeSequence[ii].StnID, 31);
			found++;
			//return gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].StnID));
		}
	}
	return found;
}

int DesignCodeSequenceClass::getStationID(String ^OpCode, String ^Prodid,wchar_t out[32][64])
{
	int ii;
	int found = 0;
	for (ii=0;ii<count;ii++)
	{
		String ^opcode = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].OpCode));
		String ^prodid = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].ProdID));
		//*endindex = (ii+1)%count; 
		if ((opcode==OpCode)&&(prodid==Prodid))
		{
			memcpy(out[found], DesignCodeSequence[ii].StnID, 31);
			found++;
			//return gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].StnID));
		}
	}
	return found;
	/*
	int ii;
	String ^str = "";
	wchar_t opcode[64];
	wchar_t prodid[64];
	String2CharArray(OpCode, opcode);
	String2CharArray(Prodid, prodid);
	for (ii=index;ii<count;ii++)
	{
		if((_tcscmp(opcode, DesignCodeSequence[ii].OpCode)==0)&&
			(_tcscmp(prodid, DesignCodeSequence[ii].ProdID)==0))
		{
			str = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].StnID));
		}
	}
	*endindex = ii;
	*/
	//return "";
}



String ^DesignCodeSequenceClass::getDesignCode(int index)
{
	if ((index<0)||(index>=count)) return "null";
	return gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[index].DesignCode));
}


String ^DesignCodeSequenceClass::getOpCode(int index)
{
	if ((index<0)||(index>=count)) return "null";
	return gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[index].OpCode));
}



int DesignCodeSequenceClass::getOpCode(String ^STNID, String ^Prodid, int dummy)
{
	int ii;
	for (ii=0;ii<count;ii++)
	{
		String ^stnid = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].StnID));
		String ^prodid = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].ProdID));
		if ((stnid==STNID)&&(prodid==Prodid))
			return _tstoi(DesignCodeSequence[ii].OpCode);
	}
	return -1;
/*
	int ii;
	wchar_t stnid[64];
	wchar_t prodid[64];
	String2CharArray(STNID, stnid);
	String2CharArray(Prodid, prodid);
	for (int ii=0;ii<count;ii++)
	{
		if(_tcscmp(stnid, DesignCodeSequence[ii].StnID)==0)

			if(_tcscmp(prodid, DesignCodeSequence[ii].ProdID)==0)

		{
			 return _tstoi(DesignCodeSequence[ii].OpCode);
		}
	}
	return -2;
	*/
}

int DesignCodeSequenceClass::find_lastsequenceNo(String ^ProdID)
{
	int ii; 
	int last = 0;
	for (ii=0;ii<count;ii++)
	{
		String ^mprodID = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].ProdID));
		if (mprodID==ProdID)
		{
			if (DesignCodeSequence[ii].seqno>=last)
				last = DesignCodeSequence[ii].seqno;
		}
	}	
	return last;
}

int DesignCodeSequenceClass::find(String ^ProdID, int seqno, int offset)
{
	int ii;
	for (ii=offset;ii<count;ii++)
	{
		String ^mprodID = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].ProdID));
		if ((mprodID==ProdID)&&(seqno==DesignCodeSequence[ii].seqno))
		{
			//String ^mOpCode = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].OpCode));
			//if (mOpCode==OPCODE)
				return ii;
		}
	}	

	/*char hangerID[128];

	for (int ii=offset;ii<count;ii++)
	{
		String ^designcodeID = gcnew String(reinterpret_cast<const wchar_t*>(DesignCodeSequence[ii].DesignCodeID));
		if (designcodeID==DesignCodeID)
			return ii;
	}	
	*/
	/*
	String2CharArray(DesignCodeID, hangerID);
	for (int ii=0;ii<count;ii++)
	{
		if (_tcscmp(DesignCodeSequence[ii].DesignCodeID, hangerID)==0)
			return ii;
	}
	*/
	return -1;
}

void DesignCodeSequenceClass::clear(String ^DesignCodeID)
{
	/*
	int index = find(DesignCodeID, 0);
	if (index>=0)
	{
		memset(&DesignCodeSequence[index], 0x0, sizeof(DesignCodeSequenceType));
	}
	*/
}

/*
int DesignCodeSequenceClass::get(String ^DesignCodeID, int StnID, int SequenceNo[], int sizeof_SequenceNo)
{
	
	int ii;
	
	int index = 0;
	int offset = 0;
	while(index>=0)
	{
		index = find(DesignCodeID, offset);
		if (index>=0)
		{
			SequenceNo[ii] = DesignCodeSequence[ii].seqno;
			StnID
			ii++;
			if (ii>=sizeof_OpCodeSequence)
				break;
		}
	}
	return ii;
}
*/

/*
void DesignCodeSequenceClass::LoadHanger(String^ ID, String^ HangerID, bool flush)
{
	int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_DesignCodeSequence)) 
		return;
	String2CharArray(HangerID, DesignCodeSequence[stnid].DesignCodeID);
	if (flush)
		writeDat();
}

void DesignCodeSequenceClass::unLoadHanger(String^ ID, bool flush)
{
		int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_DesignCodeSequence)) 
		return;
	memset(&DesignCodeSequence[stnid].DesignCodeID, 0x0, sizeof(DesignCodeSequence[stnid].DesignCodeID));
	if (flush)
		writeDat();
}

String^ DesignCodeSequenceClass::getHangerID(String^ ID)
{
	int stnid;
	stnid = Convert::ToInt32(ID);
	if ((stnid<0)||(stnid>=max_DesignCodeSequence)) 
		return "";
	String ^temp = gcnew String(reinterpret_cast<const char*>(DesignCodeSequence[stnid].DesignCodeID));	
	return temp;
}

*/
void DesignCodeSequenceClass::readDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&DesignCodeSequenceFileHeader, sizeof(DesignCodeSequenceFileHeaderType), 1, fp);
		count = DesignCodeSequenceFileHeader.reccount;
		for (int ii=0;ii<DesignCodeSequenceFileHeader.reccount;ii++)
		{
			fread(&DesignCodeSequence[ii], sizeof(DesignCodeSequenceType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}

void DesignCodeSequenceClass::writeDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;
	
	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
		fwrite(&DesignCodeSequenceFileHeader, sizeof(DesignCodeSequenceFileHeaderType), 1, fp);
		DesignCodeSequenceFileHeader.reccount = count;
		for (int ii=0;ii<DesignCodeSequenceFileHeader.reccount;ii++)
		{
			fwrite(&DesignCodeSequence[ii], sizeof(DesignCodeSequenceType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}
