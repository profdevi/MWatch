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
#ifndef MTime_h
#define MTime_h

#include <windows.h>
#include <time.h>

//************************************************************
//** class MTimeDataLocal 
//************************************************************
class MTimeDateLocal
	{
	time_t mUniversalTime;								// Universal Time in s since 1970
	struct tm mTime;									// Holds the time struct of local time

	/////////////////////////////////////////////////
	void ClearObject(void);
	
	/////////////////////////////////////////////////
	public:
	MTimeDateLocal(bool init=false);					// Constructor
	~MTimeDateLocal(void);								// Destructor
	bool Create(bool gmt=false,int secoffset=0);		// Construct Local Time
	bool Create(int universaltime,bool gmt,int secoffset);		// Construct using universal time
	bool Destroy(void);									// Destroy the object
	int GetYear(void);									// Get Year>=1970
	int GetMonth(void);									// Get Month 0-11
	int GetDay(void);									// Get Day of Month 1-31
	int GetWeekDay(void);								// Get Week Day 0-Sunday 1-Monday...6-Saturday
	int GetYearDay(void);								// Get 1-365
	int GetHour(void);									// Get 0-23
	int GetMinute(void);								// Get 0-59
	int GetSecond(void);								// Get 0-59
	char GetDayLetter(void);							// M-Monday T-Tuesday W-Wednesday...
	const char *GetDayWord(void);						// ="MONDAY","TUESDAY",...
	const char *GetDayPrefix(void);						// ="MON","TUE","WED",
	const char *GetMonthWord(void);						// ="JANUARY",...
	const char *GetMonthPrefix(void);					// ="JAN","FEB"...
	int GetUTime(void);									// Get Universal time
	};


//************************************************************
//** class MTimeWatch
//************************************************************
class MTimeWatch
	{
	unsigned int mTickStart;		// Holds the Start Counter Object
	unsigned int mMarkedTime;		// Marked Time	
	bool mPaused;					// Clock is Paused
	
	/////////////////////////////////////////////////
	void ClearObject(void);

	/////////////////////////////////////////////////
	public:
	MTimeWatch(bool init=false);		// Defaults Starts Off the mTickCount
	~MTimeWatch(void);					// Destructor
	bool Create(void);					// Starts Off the mTickCount
	bool Destroy(void);					// Destroy State of object
	unsigned int GetCount(void);		// Returns total Number of MS since start	
	bool Pause(void);					// Pause the watch
	bool Continue(void);				// Continue the watch
	bool MarkCount(void);				// Mark Current Time
	unsigned int GetMarkedCount(void);	// Get Marked Time
	bool IsPaused(void);				// Check if clock is paused
	};


//************************************************************
//** class MTimeSystem
//************************************************************
class MTimeSystem
	{
	SYSTEMTIME mSysTime;								// System Time

	/////////////////////////////////////////////////
	void ClearObject(void);
	
	/////////////////////////////////////////////////
	public:
	MTimeSystem(void);									// Constructor
	~MTimeSystem(void);									// Destructor
	bool Create(const SYSTEMTIME *ref);					// Construct System Time
	bool Create(const FILETIME *ref);					// Construct using FILETYPE
	bool Create(bool gmt=false);						// Construct System Time from current
	bool Create(int year,int month=1,int day=1,int hour=0,int min=0,int sec=0
				,int msec=0);
	bool Create(const char *datetime);					// Construct time from string "200812252359123"
	bool Destroy(void);									// Destroy the object
	int GetYear(void);									// Get Year>=1970
	int GetMonth(void);									// Get Month 0-11
	int GetDay(void);									// Get Day of Month 1-31
	int GetWeekDay(void);								// Get Week Day 0-Sunday 1-Monday...6-Saturday
	int GetYearDay(void);								// Get 1-365
	int GetHour(void);									// Get 0-23
	int GetMinute(void);								// Get 0-59
	int GetSecond(void);								// Get 0-59
	int GetMilliSecond(void);							// Get 0-59
	char GetDayLetter(void);							// M-Monday T-Tuesday W-Wednesday...
	const char *GetDayWord(void);						// ="MONDAY","TUESDAY",...
	const char *GetDayPrefix(void);						// ="MON","TUE","WED",
	const char *GetMonthWord(void);						// ="JANUARY",...
	const char *GetMonthPrefix(void);					// ="JAN","FEB"...
	int GetUTime(void);									// Get Universal time
	const SYSTEMTIME *GetSysTime(void);					// Reference to SYSTEMTIME
	bool GetDateTime(char buf[],int size,int fieldcount=7);		// Build up a time date string
	};



#endif // MTime_h
