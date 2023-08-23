/*
Copyright (C) 2011-2023, Comine.com ( profdevi@ymail.com )
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
- The the names of the contributors of this project may not be used to 
  endorse or promote products derived from this software without specific 
  prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
`AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


//v1.17 copyright Comine.com 20230823W1230
#undef UNICODE
#include <windows.h>
#include <time.h>
#include "MStdLib.h"
#include "MTime.h"


//*****************************************************************
//** Module Elements
//*****************************************************************
static const char *GDayLetters="UMTWRFS";
static const char *GDayNames[]={"SUNDAY","MONDAY","TUESDAY","WEDNESDAY"
			,"THURSDAY","FRIDAY","SATURDAY" };
static const char *GDayPrefixes[]={"SUN","MON","TUE","WED"
			,"THU","FRI","SAT" };
static const char  *GMonthNames[]={"JANUARY","FEBRUARY","MARCH","APRIL"
			,"MAY","JUNE","JULY","AUGUST","SEPTEMBER","OCTOBER"
			,"NOVEMBER","DECEMBER"};
static const char  *GMonthPrefixes[]={"JAN","FEB","MAR","APR"
			,"MAY","JUN","JUL","AUG","SEP","OCT"
			,"NOV","DEC"};


//*****************************************************************
//** MTimeDateLocal Class
//*****************************************************************
void MTimeDateLocal::ClearObject(void)
	{
	mUniversalTime=0;
	MStdMemSet(&mTime,0,sizeof(mTime) );
	}

////////////////////////////////////////////////////////////////
MTimeDateLocal::MTimeDateLocal(bool init)
	{
	ClearObject();
	if(init==true && Create()==false)
		{
		return;
		}
	}


////////////////////////////////////////////////////////////
MTimeDateLocal::~MTimeDateLocal(void)
	{  Destroy();  }


////////////////////////////////////////////////////////////
bool MTimeDateLocal::Create(bool gmt,int secoffset) // Get Local Current Time
	{
	Destroy();
	time(&mUniversalTime);
	mUniversalTime = mUniversalTime + secoffset;

	if(gmt==false)
		{
		#if _MSC_VER>=1300
		localtime_s(&mTime,&mUniversalTime);
		#else
		mTime=*localtime(&mUniversalTime);
		#endif
		}
	else
		{
		#if _MSC_VER>=1300
		gmtime_s(&mTime,&mUniversalTime);
		#else
		mTime=*gmtime(&mUniversalTime);
		#endif
		}

	return true;
	}


////////////////////////////////////////////////////////////
bool MTimeDateLocal::Create(int universaltime,bool gmt,int secoffset)
	{
	Destroy();
	mUniversalTime = universaltime + secoffset;

	if(gmt==false)
		{
		#if _MSC_VER>=1300
		localtime_s(&mTime,&mUniversalTime);
		#else
		mTime=*localtime(&mUniversalTime);
		#endif
		}
	else
		{
		#if _MSC_VER>=1300
		gmtime_s(&mTime,&mUniversalTime);
		#else
		mTime=*gmtime(&mUniversalTime);
		#endif
		}

	return true;
	}
	

////////////////////////////////////////////////////////////
bool MTimeDateLocal::Destroy(void)
	{
	ClearObject();
	return true;
	}


////////////////////////////////////////////////////////////
int MTimeDateLocal::GetYear(void)
	{
	return 1900+mTime.tm_year;
	}


////////////////////////////////////////////////////////////
int MTimeDateLocal::GetMonth(void)
	{
	return mTime.tm_mon;
	}


////////////////////////////////////////////////////////////
int MTimeDateLocal::GetDay(void)
	{
	return mTime.tm_mday;
	}


////////////////////////////////////////////////////////////
int MTimeDateLocal::GetWeekDay(void) //0-Sunday 1-Monday...
	{
	return mTime.tm_wday;
	}


////////////////////////////////////////////////////////////
int MTimeDateLocal::GetYearDay(void)
	{
	return mTime.tm_yday;
	}


////////////////////////////////////////////////////////////
int MTimeDateLocal::GetHour(void)
	{
	return mTime.tm_hour;
	}


////////////////////////////////////////////////////////////
int MTimeDateLocal::GetMinute(void)
	{
	return mTime.tm_min;
	}

////////////////////////////////////////////////////////////
int MTimeDateLocal::GetSecond(void)
	{
	return mTime.tm_sec;
	}


////////////////////////////////////////////////////////////
const char *MTimeDateLocal::GetDayWord(void)
	{
	return GDayNames[GetWeekDay()%7];
	}


///////////////////////////////////////////////////////////
const char *MTimeDateLocal::GetDayPrefix(void)
	{
	return GDayPrefixes[GetWeekDay()%7];
	}


////////////////////////////////////////////////////////////
char MTimeDateLocal::GetDayLetter(void) //M-Monday
	{
	return GDayLetters[GetWeekDay()%7];
	}


////////////////////////////////////////////////////////////
const char *MTimeDateLocal::GetMonthWord(void)
	{
	return GMonthNames[GetMonth()%12];
	}


////////////////////////////////////////////////////////////
const char *MTimeDateLocal::GetMonthPrefix(void)
	{
	return GMonthPrefixes[GetMonth()%12];
	}


////////////////////////////////////////////////////////////
int MTimeDateLocal::GetUTime(void)
	{
	return (int)mUniversalTime;
	}


//*****************************************************************
//** MTimeWatch Class
//*****************************************************************
void MTimeWatch::ClearObject(void)
	{
	mTickStart=0;
	mMarkedTime=0;
	mPaused=false;
	}

///////////////////////////////////////////////////////////////////
MTimeWatch::MTimeWatch(bool init)
	{
	ClearObject();  
	if(init==true && Create()==false)
		{
		return;
		}
	}


///////////////////////////////////////////////////////////////////
MTimeWatch::~MTimeWatch(void)
	{  Destroy();  }



///////////////////////////////////////////////////////////////////
bool MTimeWatch::Create(void)
	{
	Destroy();
	mTickStart=GetTickCount();
	mMarkedTime=mTickStart;
	return true;
	}


///////////////////////////////////////////////////////////////////
bool MTimeWatch::Destroy(void)
	{  ClearObject();  return true;  }


///////////////////////////////////////////////////////////////////
unsigned int MTimeWatch::GetCount(void)
	{  
	if(mPaused==true){  return mMarkedTime-mTickStart; }

	// Calculate time
	unsigned int tickcount=::GetTickCount();
	if(tickcount<mTickStart)
		{
		mTickStart=0;
		}

	return tickcount-mTickStart;
	}


///////////////////////////////////////////////////////////////////
bool MTimeWatch::Pause(void)				// Pause the watch
	{
	if(mPaused==true) { return true; }
	mPaused=true;
	mMarkedTime=::GetTickCount();
	return true;
	}



///////////////////////////////////////////////////////////////////
bool MTimeWatch::Continue(void)			// Continue the watch
	{
	if(mPaused==false) { return true; }
	mPaused=false;
	mTickStart = mTickStart + (GetTickCount()-mMarkedTime);
	return true;
	}


//////////////////////////////////////////////////////////////////
bool MTimeWatch::MarkCount(void)					// Mark Current Time
	{
	if(mPaused==true) { return true; }
	mMarkedTime=GetTickCount();
	return true;
	}


//////////////////////////////////////////////////////////////////
unsigned int MTimeWatch::GetMarkedCount()	// Get Marked Time
	{
	return mMarkedTime-mTickStart;
	}


/////////////////////////////////////////////////////////////////
bool MTimeWatch::IsPaused(void)
	{
	return mPaused;
	}


//*****************************************************************
//** MSystemTime Class
//*****************************************************************
void MTimeSystem::ClearObject(void)
	{
	}


////////////////////////////////////////////////////////////
MTimeSystem::MTimeSystem(void)
	{  ClearObject();  }


////////////////////////////////////////////////////////////
MTimeSystem::~MTimeSystem(void)
	{  Destroy();  }


////////////////////////////////////////////////////////////
bool MTimeSystem::Create(const SYSTEMTIME *tm)
	{
	Destroy();

	if(tm==NULL)
		{
		Destroy();
		return false;
		}

	mSysTime=*tm;
	return true;
	}


/////////////////////////////////////////////////////////////
bool MTimeSystem::Create(const FILETIME *ref)
	{
	Destroy();
	if(ref==NULL)
		{
		Destroy();
		return false;
		}

	if(FileTimeToSystemTime(ref,&mSysTime)==FALSE)
		{
		Destroy();
		return false;
		}

	return true;
	}


////////////////////////////////////////////////////////////
bool MTimeSystem::Create(bool gmt)
	{
	Destroy();
	if(gmt==true)
		{  GetSystemTime(&mSysTime);  }
	else
		{  GetLocalTime(&mSysTime);  }

	return true;
	}


////////////////////////////////////////////////////////////
bool MTimeSystem::Create(int year,int month,int day,int hour,int min,int sec,int msec)
	{
	Destroy();

	// Init Memory
	MStdMemZero(&mSysTime,sizeof(mSysTime) );

	mSysTime.wYear=(WORD)year;
	mSysTime.wMonth=(WORD)month;
	mSysTime.wDay=(WORD)day;
	mSysTime.wHour=(WORD)hour;
	mSysTime.wMinute=(WORD)min;
	mSysTime.wSecond=(WORD)sec;
	mSysTime.wMilliseconds=msec;
	return true;
	}


/////////////////////////////////////////////////////////////
bool MTimeSystem::Create(const char *datetime)
	{
	Destroy();
	
	MStdAssert(datetime!=0 && *datetime!=0);

	// Init Memory
	MStdMemZero(&mSysTime,sizeof(mSysTime) );

	int length=MStdStrLen(datetime);
	if(length<8)
		{
		Destroy();
		return false;
		}

	int year=0;
	year=10*year+(datetime[0]-'0');
	year=10*year+(datetime[1]-'0');
	year=10*year+(datetime[2]-'0');
	year=10*year+(datetime[3]-'0');

	int month=0;
	month=10*month+(datetime[4]-'0');
	month=10*month+(datetime[5]-'0');

	int day=0;
	day=10*day+(datetime[6]-'0');
	day=10*day+(datetime[7]-'0');

	int hours=0;
	int mins=0;
	int secs=0;
	int msecs=0;

	if(length>=10)
		{
		hours=10*hours+(datetime[8]-'0');
		hours=10*hours+(datetime[9]-'0');
		}

	if(length>=12)
		{
		mins=10*mins+(datetime[10]-'0');
		mins=10*mins+(datetime[11]-'0');
		}

	if(length>=14)
		{
		secs=10*secs+(datetime[12]-'0');
		secs=10*secs+(datetime[13]-'0');
		}

	if(length>=17)
		{
		msecs=10*msecs+(datetime[14]-'0');
		msecs=10*msecs+(datetime[15]-'0');
		}

	return Create(year,month,day,hours,mins,secs,msecs);
	}


////////////////////////////////////////////////////////////
bool MTimeSystem::Destroy(void)
	{
	ClearObject();
	return true;
	}


////////////////////////////////////////////////////////////
int MTimeSystem::GetYear(void)
	{
	return mSysTime.wYear;
	}


////////////////////////////////////////////////////////////
int MTimeSystem::GetMonth(void)
	{
	return mSysTime.wMonth-1;
	}


////////////////////////////////////////////////////////////
int MTimeSystem::GetDay(void)
	{
	return mSysTime.wDay;
	}


////////////////////////////////////////////////////////////
int MTimeSystem::GetWeekDay(void)
	{
	return mSysTime.wDayOfWeek;
	}


////////////////////////////////////////////////////////////
int MTimeSystem::GetHour(void)
	{
	return mSysTime.wHour;
	}


////////////////////////////////////////////////////////////
int MTimeSystem::GetMinute(void)
	{
	return mSysTime.wMinute;
	}


////////////////////////////////////////////////////////////
int MTimeSystem::GetSecond(void)
	{
	return mSysTime.wSecond;
	}


////////////////////////////////////////////////////////////
int MTimeSystem::GetMilliSecond(void)
	{
	return mSysTime.wMilliseconds;	
	}


////////////////////////////////////////////////////////////
char MTimeSystem::GetDayLetter(void)
	{
	return GDayLetters[GetWeekDay()%7];
	}


////////////////////////////////////////////////////////////
const char *MTimeSystem::GetDayWord(void)
	{
	return GDayNames[GetWeekDay()%7];
	}


////////////////////////////////////////////////////////////
const char *MTimeSystem::GetDayPrefix(void)
	{
	return GDayPrefixes[GetWeekDay()%7];
	}


////////////////////////////////////////////////////////////
const char *MTimeSystem::GetMonthWord(void)
	{
	return GMonthNames[GetMonth()%12];
	}


////////////////////////////////////////////////////////////
const char *MTimeSystem::GetMonthPrefix(void)
	{
	return GMonthPrefixes[GetMonth()%12];
	}


////////////////////////////////////////////////////////////
int MTimeSystem::GetUTime(void)
	{
	struct tm timeinfo;
	MStdMemZero(&timeinfo,sizeof(timeinfo) );
	timeinfo.tm_year=GetYear()-1900;
	timeinfo.tm_mon=GetMonth();
	timeinfo.tm_mday=GetDay();
	timeinfo.tm_hour=GetHour();
	timeinfo.tm_min=GetMinute();
	timeinfo.tm_sec = GetSecond();

	return (int)mktime(&timeinfo);
	}


/////////////////////////////////////////////////////////////
const SYSTEMTIME *MTimeSystem::GetSysTime(void)
	{
	return &mSysTime;
	}


bool MTimeSystem::GetDateTime(char outbuf[],int size,int fieldcount)
	{
	char buf[100];
	if(fieldcount==7)
		{
		MStdSPrintf(buf,sizeof(buf),
			"%04d%02d%02d%02d%02d%02d%03d",GetYear(),GetMonth()+1
			,GetDay(),GetHour(),GetMinute(),GetSecond(),GetMilliSecond());
		}
	else if(fieldcount==6)
		{
		MStdSPrintf(buf,sizeof(buf),
			"%04d%02d%02d%02d%02d%02d",GetYear(),GetMonth()+1
			,GetDay(),GetHour(),GetMinute(),GetSecond() );
		}
	else if(fieldcount==5)
		{
		MStdSPrintf(buf,sizeof(buf),
			"%04d%02d%02d%02d%02d",GetYear(),GetMonth()+1
			,GetDay(),GetHour(),GetMinute());		
		}
	else if(fieldcount==4)
		{
		MStdSPrintf(buf,sizeof(buf),
			"%04d%02d%02d%02d",GetYear(),GetMonth()+1
			,GetDay(),GetHour());
		}
	else if(fieldcount==3)
		{
		MStdSPrintf(buf,sizeof(buf),
			"%04d%02d%02d",GetYear(),GetMonth()+1,GetDay());
		}
	else if(fieldcount==2)
		{
		MStdSPrintf(buf,sizeof(buf),
			"%04d%02d",GetYear(),GetMonth()+1);
		}
	else if(fieldcount==1)
		{
		MStdSPrintf(buf,sizeof(buf),"%04d",GetYear());
		}
	else
		{
		// Assume all six fields
		MStdSPrintf(buf,sizeof(buf),
			"%04d%02d%02d%02d%02d%02d",GetYear(),GetMonth()+1
			,GetDay(),GetHour(),GetMinute(),GetSecond() );		
		}	

	int length=MStdStrLen(buf);
	if(length>=size)
		{
		outbuf[0]=0;
		return false;
		}

	MStdStrCpy(outbuf,buf);
	return true;
	}
