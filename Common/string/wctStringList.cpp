#include "StdAfx.h"

#include "wctStringList.h"

#define NULL	0

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; }}

wctStringList::wctStringList()
{
    int ii;
    for (ii=0;ii<MAX_wctStringList;ii++)
        wctstr[ii] = 0;
    count = 0;
}

wctStringList::~wctStringList()
{
    clear();
}

void wctStringList::clear()
{
    int ii;
    for (ii=0;ii<MAX_wctStringList;ii++)
        SAFE_DELETE(wctstr[ii]);
    count = 0;
}

void wctStringList::add(const wchar_t *wstr)
{
    if((count<0)||(count>=MAX_wctStringList)) return;
    SAFE_DELETE(wctstr[count])
    wctstr[count] = new wctString(wstr);
    count++;
}



const wctString *wctStringList::get(int index)
{
    if((index<0)||(index>=MAX_wctStringList)) return 0;
    if (!wctstr[index]) return 0;
    return  wctstr[index];
}


