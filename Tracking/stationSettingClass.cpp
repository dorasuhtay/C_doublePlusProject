#include "StdAfx.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <TCHAR.H>
#include "fileIO.h"

#include "stationSettingClass.h"
#include "csvStringClass.h"
#include "wctString.h"
#include "unicodeStringFunction.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

#define cfile_Name		"InfeedOutfeed.DAT\0\0"
//const char *stationSettingClass::getfile_Name(){return file_Name;}
const char c_endheaderCheckId[]			= {0xE3,0x86,0x53};
const char c_FileHeader[]				= {0x02,0xC7,0x72};
const wchar_t *stationSettingClass::wgetfile_Name(){if (filepathname) return (wchar_t *)filepathname->wdata(); else return _T(cfile_Name);}
const char    *stationSettingClass::cgetfile_Name(){if (filepathname) return (char *)filepathname->cdata(); else return cfile_Name;}

stationSettingClass::stationSettingClass(const wchar_t *path, wchar_t *prodline)
{
	int ii;
	storeLock = 0;
	for (ii=0;ii<MAX_STATIONARRAY_SIZE;ii++)
		stationPara[ii] = 0;
	count = 0;
	int wsize = sizeof(wt_prodline)/sizeof(wchar_t);
	_tcsncpy(wt_prodline, prodline, wsize-1);
	wt_prodline[wsize-1] = 0x0;
	//initialise file header
	memset(&FileHeader, 0x0, sizeof(stationParameterFileHeaderType));
	FileHeader.Idstring[0] = c_FileHeader[0];
	FileHeader.Idstring[1] = c_FileHeader[1];
	FileHeader.Idstring[2] = c_FileHeader[2];
	FileHeader.versionMajor = 1;
	FileHeader.versionMinor = 0;
	FileHeader.reccount = MAX_STATIONARRAY_SIZE;
	FileHeader.endheaderCheckId[0] = c_endheaderCheckId[0];
	FileHeader.endheaderCheckId[1] = c_endheaderCheckId[1];
	FileHeader.endheaderCheckId[2] = c_endheaderCheckId[2];


	filepath  = new wctString(path);
	filepathname  = new wctString(path);
	filepathname->append(_T("\\"));
	filepathname->append(_T(cfile_Name));

	userfilepathname = 0;
}


stationSettingClass::~stationSettingClass()
{
	deleteAll();
	SAFE_DELETE(userfilepathname);
	SAFE_DELETE(filepath);
	SAFE_DELETE(filepathname);
}

void stationSettingClass::add(stationParameterType *sPara)
{
	if (count<0) return;
	if (count>MAX_STATIONARRAY_SIZE) return;
	if (stationPara[count]) return;
	stationPara[count] = new stationParameterType;
	memcpy(stationPara[count], sPara, sizeof(stationParameterType));
	count++;
}


void stationSettingClass::deleteAll()
{
	int ii;
	for (ii=0;ii<MAX_STATIONARRAY_SIZE;ii++)
		SAFE_DELETE(stationPara[ii]);
	count = 0;
}

int stationSettingClass::get(int ii, stationParameterType *sPara)
{
	if (ii<0) return 0;
	if (ii>MAX_STATIONARRAY_SIZE) return 0;
	if (stationPara[ii])
	{
		memcpy(sPara, stationPara[ii], sizeof(stationParameterType));
		return 1;
	}
	return 0;
}

int stationSettingClass::set(int ii, stationParameterType *sPara)
{
	if (ii<0) return 0;
	if (ii>MAX_STATIONARRAY_SIZE) return 0;
	if (stationPara[ii])
	{
		memcpy(stationPara[ii], sPara, sizeof(stationParameterType));
		return 1;
	}
	return 0;
}

//const char csvtitle[] = "\"StationID\", \"Infeed\", \"Infeed Offset\", \"Outfeed\", \"Outfeed Offset\", \"Prodline\"\r";
//const char csvtitle[] = "StationID, Infeed, Infeed Offset, Outfeed, Outfeed Offset, Prodline\r";
#define Num_Of_FIELDS_infeedoutfeed_CSV		5
wchar_t Fields_infeedoutfeed_CSV[Num_Of_FIELDS_infeedoutfeed_CSV][32] =
{
	L"STATIONID", 
	L"INFEED", 
	L"INFEED OFFSET", 
	L"OUTFEED", 
	L"OUTFEED OFFSET" 
//	L"PRODLINE"
};

wchar_t *stationSettingClass::getCSVtitleLine(wchar_t *csvtitle, int size)
{
	int ii;
	wctString *wctstr = new wctString();
	for (ii=0;ii<Num_Of_FIELDS_infeedoutfeed_CSV;ii++)
	{
		if (ii>0)
			wctstr->append(L", ");
		wctstr->append(Fields_infeedoutfeed_CSV[ii]);
	}
	_tcsncpy(csvtitle, wctstr->wdata(), size-1);
	csvtitle[size-1] = 0x0;
	delete wctstr;
	return csvtitle;
}

void stationSettingClass::export2CSV(const char *filename)
{
	int ii;
	FILE *fp = fopen(filename, "w+t");
	if(fp)
	{
		//_ftprintf(fp, _T("StationID, Infeed, Infeed Offset, Outfeed, Outfeed Offset, Prodline\r"));
		for (ii=0;ii<Num_Of_FIELDS_infeedoutfeed_CSV;ii++)
		{
			if (ii>0)
				_ftprintf(fp, L", ");
			_ftprintf(fp, Fields_infeedoutfeed_CSV[ii]);
		}
		_ftprintf(fp, L"\r");
		for (ii=1;ii<getcount();ii++)
		{
			_ftprintf(fp, _T("%s, %d, %d, %d, %d\r"),	
												stationPara[ii]->stnID,
												stationPara[ii]->infeed,
												stationPara[ii]->infeedoffset,
												stationPara[ii]->outfeed,
												stationPara[ii]->outfeedoffset
												);
/*
			_ftprintf(fp, _T("%s, %d, %d, %d, %d, %s\r"),	
												stationPara[ii]->stnID,
												stationPara[ii]->infeed,
												stationPara[ii]->infeedoffset,
												stationPara[ii]->outfeed,
												stationPara[ii]->outfeedoffset,
												stationPara[ii]->prodlineID
												);
												*/
		}
		fclose(fp);
	}
}
/*
int Readln(FILE *fp, char *buf, int bufsize)
{
 int ch;
 char *bufptr = buf;
 int count = 0;
 int done = 0;
 while (!done) {
		ch = fgetc(fp);
		*bufptr  = (char)ch;
		bufptr++;
		count++;
		if (ch==EOF) {
			count = -1;
			break;
			}
		if (count>=bufsize) {
			count = -2;		// exceeded buf size
			break;
			}
	  if (ch==13) {			//CRLF
			//ch = fgetc(fp);
			//*bufptr  = (char)ch;
			//bufptr++;
			//count++;
			// (ch==10) {
				break;
				//
         }
	  if (ch==10) {			//LF
		  break;
	     }
	  }
 *bufptr = 0x00;
 return count;
}
*/

void stationSettingClass::arrayData(int icol, const char *vbuf, stationParameterType *sPara)
{
	const char *sptr = vbuf;
	int ii;
	if (!sPara) return;
	switch (icol)
	{
		case	0:	ii = 0;
					while(*sptr)
					{
						if (*sptr!='\"')
							sPara->stnID[ii++] = (wchar_t)(*sptr++);
					}
					sPara->stnID[ii] = 0x0;
					break;
		case	1:	sPara->infeed = atoi(vbuf);
					break;
		case	2:	sPara->infeedoffset = atoi(vbuf);
					break;
		case	3:	sPara->outfeed = atoi(vbuf);
					break;					
		case	4:	sPara->outfeedoffset = atoi(vbuf);
					break;	
					/*
		case	5:	ii = 0;
					while(*sptr)
					{
						if (*sptr!='\"')
							sPara->prodlineID[ii++] = *sptr++;
					}
					sPara->prodlineID[ii] = 0x0;
				
					break;
					*/

	}
}

void sarrayData(int icol, const char *vbuf, void *sPara)
{
}

void sCSVformat2TableRow(int col, int row, char *linebuf, int *width, int *height, void(*func)(int icol, const char *vbuf, void *sPara), void *sPara)
{ 
	int icol = col;
   int irow = row;
//   int result;
   char *sptr;
   int jj;
   char vbuf[512];

		int kk = strlen(linebuf)-1;
      if (linebuf[kk]=='\r') linebuf[kk] = 0x0;
      if (linebuf[kk]=='\n') linebuf[kk] = 0x0;

		kk = strlen(linebuf)-1;
      if (linebuf[kk]=='\r') linebuf[kk] = 0x0;
      if (linebuf[kk]=='\n') linebuf[kk] = 0x0;

      sptr = linebuf;
	   jj = 0;
      int skipcomma = 0;
	while(*sptr)
	{
        	vbuf[jj] = *sptr;
        	vbuf[jj+1] = 0;
         if (*sptr=='\"'){
	         if (skipcomma){
					skipcomma = 0;
         		vbuf[jj] = 0x0;
               }
            else
            	{
					skipcomma = 1;
               jj = 0;
               }
            }
         else
	  			jj++;
         if (jj>sizeof(vbuf)-1) jj = 0;
      	if ((!skipcomma)&&(*sptr==','))
		{
				vbuf[jj-1] = 0x0;
				sarrayData(icol, vbuf, sPara);
            icol++;
            jj=0;
  				vbuf[jj] = 0x0;
         }
         sptr++;
	}
	sarrayData(icol, vbuf, sPara);
	*width  = icol-col+1;
	*height = irow-row+1;
}

void stationSettingClass::CSVformat2TableRow(int col, int row, char *linebuf, int *width, int *height, stationParameterType *sPara)
{ 
	int icol = col;
   int irow = row;
//   int result;
   char *sptr;
   int jj;
   char vbuf[512];

		int kk = strlen(linebuf)-1;
      if (linebuf[kk]=='\r') linebuf[kk] = 0x0;
      if (linebuf[kk]=='\n') linebuf[kk] = 0x0;

		kk = strlen(linebuf)-1;
      if (linebuf[kk]=='\r') linebuf[kk] = 0x0;
      if (linebuf[kk]=='\n') linebuf[kk] = 0x0;

      sptr = linebuf;
	   jj = 0;
      int skipcomma = 0;
	while(*sptr)
	{
        	vbuf[jj] = *sptr;
        	vbuf[jj+1] = 0;
         if (*sptr=='\"'){
	         if (skipcomma){
					skipcomma = 0;
         		vbuf[jj] = 0x0;
               }
            else
            	{
					skipcomma = 1;
               jj = 0;
               }
            }
         else
	  			jj++;
         if (jj>sizeof(vbuf)-1) jj = 0;
      	if ((!skipcomma)&&(*sptr==','))
		{
				vbuf[jj-1] = 0x0;
				arrayData(icol, vbuf, sPara);
            icol++;
            jj=0;
  				vbuf[jj] = 0x0;
         }
         sptr++;
	}
	arrayData(icol, vbuf, sPara);
	*width  = icol-col+1;
	*height = irow-row+1;
}



int stationSettingClass::importFromCSV(const char *filename)
{

	int width, height;
	int row;
	int result;
	char linebuf[1024];
	stationParameterType sPara;
	int found = 0;
	FILE *fp;
	fp = fopen(filename, "r+b");
	if (fp)
	{
		while(!feof(fp))
		{
			result = Readln(fp, linebuf, sizeof(linebuf)-1);
			if (result>0)
			{

				wchar_t teststr[128];
				wchar_t teststr1[128];
				int ii;
				for (ii=0;ii<strlen(linebuf);ii++)
					teststr[ii] = (wchar_t)linebuf[ii];
				teststr[ii] = 0x0;
				csvStringClass *csvstr = new csvStringClass(teststr);
				csvstr->parseCSV(',');
				if (csvstr->getcount()==Num_Of_FIELDS_infeedoutfeed_CSV)
				{
					for (int ii=0;ii<csvstr->getcount();ii++)
					{
						csvstr->get(ii, teststr1, 100);
						trim(teststr1);
						if(_tcscmp(teststr1,Fields_infeedoutfeed_CSV[ii])==0)
							found++;
					}
				}
				delete csvstr;
				if (found==Num_Of_FIELDS_infeedoutfeed_CSV)
				{
					deleteAll();
					memset(&sPara,0x0,sizeof(stationParameterType));
					add(&sPara);
					break;
				}
				else
					found=0;
				break;
			}
		}
		if (found==Num_Of_FIELDS_infeedoutfeed_CSV)
		{
			row = 1;
			while(!feof(fp))
			{
				result = Readln(fp, linebuf, sizeof(linebuf)-1);
				if (result<=0) break;
				memset(&sPara,0x0,sizeof(stationParameterType));
				CSVformat2TableRow(0, row, linebuf, &width, &height, &sPara); 
				add(&sPara);
				row++;
			}
		}
		fclose(fp);
	}
	return found;
}




void stationSettingClass::readDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp= fopen((char *)filepathname->cdata(), "r+b");
	if (fp)
	{
		fread(&FileHeader, sizeof(stationParameterFileHeaderType), 1, fp);
		count = FileHeader.reccount;
		for (int ii=0;ii<FileHeader.reccount;ii++)
		{
			fread(&stationPara[ii], sizeof(stationParameterType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}

void stationSettingClass::writeDat()
{
	while(storeLock)
		Sleep(1);
	storeLock = 1;

	FILE *fp = fopen((char *)filepathname->cdata(), "w+b");
	if (fp)
	{
		FileHeader.reccount = count;
		fwrite(&FileHeader, sizeof(stationParameterFileHeaderType), 1, fp);
		for (int ii=0;ii<FileHeader.reccount;ii++)
		{
			fwrite(&stationPara[ii], sizeof(stationParameterType), 1, fp);
		}
		fclose(fp);
	}
	storeLock = 0;
}
