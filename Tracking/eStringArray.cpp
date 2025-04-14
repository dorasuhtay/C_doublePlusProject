#include "StdAfx.h"
#include "eStringArray.h"

eStringArray::eStringArray()
{
//	int ii;
//	for (ii=0;ii<MAX_ESTRINGARRAY;ii++)
//		sstr[ii] = "";
	count = 0;
}

eStringArray::~eStringArray()
{
}

void eStringArray::add(String ^str)
{
	if (count<0) return;
	if (count>=MAX_ESTRINGARRAY) return;
//	sstr[count] = str;
	count++;

}

/*
String ^eStringArray::get(int index)
{
	if (index<0) return;
	if (index>=MAX_ESTRINGARRAY) "";
	return sstr[index];
}
*/