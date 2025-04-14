#ifndef __GlobalVariables__H
#define __GlobalVariables__H

using namespace System;

#define MAX_TEST_RLX_STATIONS		128
typedef struct
{
	int RL1rate;
	int RL2rate;
	int RL3rate;
	int RL4rate;
	int RL1stations[MAX_TEST_RLX_STATIONS];
	int RL2stations[MAX_TEST_RLX_STATIONS];
	int RL3stations[MAX_TEST_RLX_STATIONS];
	int RL4stations[MAX_TEST_RLX_STATIONS];
}testFireRLxType;

extern testFireRLxType testFireRLx;

//extern int RL1Fire_rate;		//in seconds
//extern int RL2Fire_rate;		//in seconds
//extern int RL3Fire_rate;		//in seconds
extern int resetFire_rate;		//in seconds
extern wchar_t application_DataPath[1024];
extern wchar_t application_MyDocumentsPath[1024];
extern char userlistDatafilenamePath[1024];

extern bool application_PlayBack_is_ON;


#define operationMode_ADVANCESCREEN		0x00000001
#define operationMode_PASSWORD_OK		0x00000002

#endif