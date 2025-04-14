#include "StdAfx.h"
//#include <stdlib.h>
#include <string.h>
#include "class_StationBoardTest.h"


#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=0; }}




class_StationBoardTest::class_StationBoardTest()
{
	int ii;
	for (ii=0;ii<MAX_STATIONBOARDTEST_SIZE;ii++)
	{
		stn[ii] = 0x0;
	}
	count = 0;
}

class_StationBoardTest::~class_StationBoardTest()
{
	int ii;
	for (ii=0;ii<MAX_STATIONBOARDTEST_SIZE;ii++)
	{
		SAFE_DELETE(stn[ii]);
	}
}

void class_StationBoardTest::Reset()
{
	int ii;
	for (ii=0;ii<count;ii++)
	{
		if (!stn[ii]) continue;
		stn[ii]->state = 0;
		stn[ii]->counter = 0;
	}
}

void class_StationBoardTest::add(stationtestType *data)
{
	if (count>=MAX_STATIONBOARDTEST_SIZE) return;
	stn[count] = new stationtestType;
	memcpy(stn[count], data, sizeof(stationtestType));
	count++;
}

int class_StationBoardTest::get(int index,	stationtestType *data)
{
	if ((index<0)||(index>=MAX_STATIONBOARDTEST_SIZE)) 
		return 0;
	if (!stn[index]) return 0;
	memcpy(data, stn[index], sizeof(stationtestType));
	return 1;
}

void class_StationBoardTest::incrementstate(int index)
{
	if ((index<0)||(index>=MAX_STATIONBOARDTEST_SIZE)) 
		return;

	if (stn[index])
		stn[index]->state++;
}

int class_StationBoardTest::deccrementcounter(int index)
{
	int nn = 0;
	if ((index<0)||(index>=MAX_STATIONBOARDTEST_SIZE)) 
		return 0;

	if (stn[index])
	{
		if (stn[index]->counter>-1)
			stn[index]->counter--;
		nn = stn[index]->counter;
	}
	return nn;
}

void class_StationBoardTest::setcounter(int index, int value)
{
	int nn = 0;
	if ((index<0)||(index>=MAX_STATIONBOARDTEST_SIZE)) 
		return;

	if (stn[index])
		stn[index]->counter = value;
}


void class_StationBoardTest::resetstate(int index)
{
	int nn = 0;
	if ((index<0)||(index>=MAX_STATIONBOARDTEST_SIZE)) 
		return;

	if (stn[index])
		stn[index]->state = 0;
}