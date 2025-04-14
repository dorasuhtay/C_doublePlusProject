//Program tested on Microsoft Visual Studio 2008 - Zahid Ghadialy
//This program shows example of Getting Elapsed Time
#include "StdAfx.h"
#include <iostream>
#include <Windows.h>
#include "cputime_measurement.h"

//using namespace std;

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Kernel32.Lib")


LARGE_INTEGER timerFreq_;
LARGE_INTEGER counterAtStart_;

void performance_startTime()
{
  QueryPerformanceFrequency(&timerFreq_);
  QueryPerformanceCounter(&counterAtStart_);
  //cout<<"timerFreq_ = "<<timerFreq_.QuadPart<<endl;
  //cout<<"counterAtStart_ = "<<counterAtStart_.QuadPart<<endl;
  TIMECAPS ptc;
  UINT cbtc = 8;
  MMRESULT result = timeGetDevCaps(&ptc, cbtc);
  if (result == TIMERR_NOERROR)
  {
    //cout<<"Minimum resolution = "<<ptc.wPeriodMin<<endl;
    //cout<<"Maximum resolution = "<<ptc.wPeriodMax<<endl;
  }
  else
  {
    //cout<<"result = TIMER ERROR"<<endl;
  }
}

unsigned int performance_calculateElapsedTime()
{
  if (timerFreq_.QuadPart == 0)
  {
    return -1;
  }
  else
  {
    LARGE_INTEGER c;
    QueryPerformanceCounter(&c);
    return static_cast<unsigned int>( (c.QuadPart - counterAtStart_.QuadPart) * 1000 / timerFreq_.QuadPart );
  }
}
/*
int main()
{
  //Increasing the accuracy of Sleep to 1ms using timeBeginPeriod
  timeBeginPeriod(1); //Add Winmm.lib in Project
  unsigned int diffTime = 0, lastTime = 0, newTime = 0;
  startTime();
  lastTime = calculateElapsedTime();
  cout<<"Start Time = "<<lastTime<<endl;

  Sleep(100);
  newTime = calculateElapsedTime();
  diffTime = newTime - lastTime;
  cout<<"Time after 100ms Sleep = "<<newTime<<", Difference = "<<diffTime<<endl;
  lastTime = newTime;

  Sleep(100);
  newTime = calculateElapsedTime();
  diffTime = newTime - lastTime;
  cout<<"Time after 100ms Sleep = "<<newTime<<", Difference = "<<diffTime<<endl;
  lastTime = newTime;

  Sleep(5);
  newTime = calculateElapsedTime();
  diffTime = newTime - lastTime;
  cout<<"Time after   5ms Sleep = "<<newTime<<", Difference = "<<diffTime<<endl;
  lastTime = newTime;

  Sleep(50);
  newTime = calculateElapsedTime();
  diffTime = newTime - lastTime;
  cout<<"Time after  50ms Sleep = "<<newTime<<", Difference = "<<diffTime<<endl;

  timeEndPeriod(1); //Must be called if timeBeginPeriod() was called
  return 0;
}*/


 