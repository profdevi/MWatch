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


//v1.3 copyright Comine.com 20060927W09
#include <windows.h>
#include "MStdLib.h"
#include "MWatchDirectory.h"


//********************************************************
//*** MWatchDirectory
//********************************************************
void MWatchDirectory::ClearObject(void)
	{
	mhDirectory=INVALID_HANDLE_VALUE;
	}


///////////////////////////////////////////////////////////
MWatchDirectory::MWatchDirectory(void)
	{  ClearObject();  }


///////////////////////////////////////////////////////////
MWatchDirectory::MWatchDirectory(const char *dirname,bool recursesubdir
			,DWORD filter)
	{
	ClearObject();
	if(Create(dirname,recursesubdir,filter)==false)
		{
		return;
		}
	}
	

//////////////////////////////////////////////////////////
MWatchDirectory::~MWatchDirectory(void)
	{  Destroy();  }


//////////////////////////////////////////////////////////
bool MWatchDirectory::Create(const char *dirname,bool recursesubdir
			,DWORD filter)
	{
	Destroy();

	BOOL recurs;
	if(recursesubdir==true) { recurs=TRUE; } else { recurs=FALSE; }

	mhDirectory=FindFirstChangeNotification(dirname,recurs,filter);
	if(mhDirectory==INVALID_HANDLE_VALUE)
		{
		Destroy();  return false;
		}

	return true;
	}


//////////////////////////////////////////////////////////
bool MWatchDirectory::Destroy(void)
	{
	if(mhDirectory!=INVALID_HANDLE_VALUE){ CloseHandle(mhDirectory); }
	ClearObject();  return true;
	}





//////////////////////////////////////////////////////////
int MWatchDirectory::Watch(DWORD waittime) //=0 (success),=1(time out),=-1(Failed)
	{
	DWORD ret=WaitForSingleObject(mhDirectory,waittime);
	if(ret==WAIT_ABANDONED)
		{
		return -1;
		}
	else if(ret==WAIT_OBJECT_0)
		{
		if(FindNextChangeNotification(mhDirectory)==FALSE)
			{
			return -1;
			}

		return 0;
		}
	else
		{  return 1; } //timed out
	}


