#include "StdAfx.h"
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include "csvStringClass.h"

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}

csvStringClass::csvStringClass(wchar_t *str)
{
	int ii;
	for (ii=0;ii<MAX_PARSED_ELEMENT;ii++)
		wstr[ii] = 0;
	count = 0;
	length = _tcslen(str);
	//inputstr = (wchar_t *)malloc((length+1)*sizeof(wchar_t));
	inputstr = new wchar_t[(length+2)*sizeof(wchar_t)];
	_tcscpy(inputstr, str);
	vbuflen = length;
	vbuf = new wchar_t[(vbuflen+2)*sizeof(wchar_t)];

	while((inputstr[_tcslen(inputstr)-1]=='\r')||(inputstr[_tcslen(inputstr)-1]=='\n'))
		inputstr[_tcslen(inputstr)-1] = 0x0;
}

csvStringClass::~csvStringClass()
{
	int ii;
	for (ii=0;ii<MAX_PARSED_ELEMENT;ii++)
	{
		SAFE_DELETE(wstr[ii]);
		//if (wstr[ii])
		//	free(wstr[ii]);
	}

	//if(inputstr)
	//	free(inputstr);
	SAFE_DELETE(inputstr);
	SAFE_DELETE(vbuf);
}

int csvStringClass::add(wchar_t *str)
{
	if (count<0) return -1;
	if (count>=MAX_PARSED_ELEMENT) return -1;
	int len = _tcslen(str);
	//wstr[count] = (wchar_t *)malloc((len+1)*sizeof(wchar_t));
	wstr[count] = new wchar_t[(len+2)*sizeof(wchar_t)];

	_tcscpy(wstr[count], str);

	count++;
	return 0;

}

int csvStringClass::get(int index, wchar_t *str, int len)
{
	if (index<0) return 0;
	if (index>=MAX_PARSED_ELEMENT) return 0;
	if (wstr[index])
	{
		_tcsncpy(str, wstr[index], len);
		str[len] = 0x0;
		return 1;
	}
	return 0;
}

void csvStringClass::parseCSV(wchar_t delimiter)
{
	wchar_t *sptr;
	int jj;
	int len = _tcslen(inputstr);
	sptr = inputstr;

	jj = 0;
	int skipcomma = 0;
	while(*sptr)
	{
		vbuf[jj] = *sptr;
		vbuf[jj+1] = 0;
		if (*sptr=='\"')
		{
			if (skipcomma)
			{
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
		if (jj>vbuflen) 
			jj = 0;
      	if ((!skipcomma)&&(*sptr==','))
		{
			vbuf[jj-1] = 0x0;
			add(vbuf);
			//arrayData(icol, vbuf, sPara);
            //icol++;
            jj=0;
			vbuf[jj] = 0x0;
         }
         sptr++;
	}
	//arrayData(icol, vbuf, sPara);
	add(vbuf);

	//delete(vbuf);
	//*width  = icol-col+1;
	//*height = irow-row+1;

}



void CSVformat2TableRow(int col, int row, char *linebuf, int *width, int *height, void(*func)(int icol, const char *vbuf, void *sPara), void *sPara)
{ 
	int icol = col;
	int irow = row;
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
        if (*sptr=='\"')
		{
	        if (skipcomma)
			{
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
			if(func)
				func(icol, vbuf, sPara);
            icol++;
            jj=0;
  			vbuf[jj] = 0x0;
         }
         sptr++;
	}
	if (func)
		func(icol, vbuf, sPara);
	*width  = icol-col+1;
	*height = irow-row+1;
}

