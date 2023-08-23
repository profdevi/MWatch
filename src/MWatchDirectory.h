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
#ifndef MWatchDirectory_h
#define MWatchDirectory_h

/////////////////////////////////////////////
#include <windows.h>

/////////////////////////////////////////////
class MWatchDirectory
	{
	HANDLE mhDirectory;

	//////////////////////////////////////////////
	void ClearObject(void);

	//////////////////////////////////////////////
	public:
	MWatchDirectory(void);
	MWatchDirectory(const char *dirname,bool recursesubdir=false
			,DWORD filter=FILE_NOTIFY_CHANGE_LAST_WRITE);
	~MWatchDirectory(void);
	bool Create(const char *dirname,bool recursesubdir=false
			,DWORD filter=FILE_NOTIFY_CHANGE_LAST_WRITE);
	bool Destroy(void);
	int Watch(DWORD waittime=INFINITE); //=0 (success),=1(time out),=-1(Failed)
	};


#endif // MWatchDirectory_h