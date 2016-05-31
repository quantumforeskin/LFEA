#include <iostream>
using namespace std;

#include "LRCtime.h"



//////////////////////////////////////////////////////////////////////////

LRCtime::LRCtime() {
  //  now = time(NULL);
  //  time_tm = localtime(&now);
  gettimeofday(&time_tv, NULL);
  time_tm = localtime(&time_tv.tv_sec);
}


LRCtime::~LRCtime() {}

int LRCtime::GetTime1970sec() { return time_tv.tv_sec; }

int LRCtime::GetTime1970usec() { return time_tv.tv_usec; }

//int LRCtime::GetTime1970sec() { return now; }

int LRCtime::GetTimeSeconds() { return time_tm->tm_sec; }
int LRCtime::GetTimeMinutes() { return time_tm->tm_min; }
int LRCtime::GetTimeHours()   { return time_tm->tm_hour; }
int LRCtime::GetTimeDay()     { return time_tm->tm_mday; }
int LRCtime::GetTimeMonth()   { return time_tm->tm_mon + 1; }
int LRCtime::GetTimeYear()    { return time_tm->tm_year + 1900; }

///////////////////////////////////////////////////////////////////
double LRCtime::GetTimefull() { 
   return (double)GetTime1970sec() + 1.0E-6*(double)GetTime1970usec();  
}


