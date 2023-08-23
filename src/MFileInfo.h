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


//v1.9 copyright Comine.com 20190316S0819
#ifndef MFileInfo_h
#define MFileInfo_h

//////////////////////////////////////////////
#include "MStdLib.h"
#include "TAutoPtr.h"

#if (defined(MSTDLIB_API_WINDOWS) )
#include <windows.h>

/////////////////////////////////////////////
class MFileInfo
	{
	TAutoPtr<BY_HANDLE_FILE_INFORMATION> mpInfo;

	/////////////////////////////////////////
	void ClearObject(void);

	/////////////////////////////////////////
	public:
	MFileInfo(void);
	explicit MFileInfo(const char *filename);
	~MFileInfo(void);
	bool Create(const char *filename);
	bool Destroy(void);
	const FILETIME *GetCreationTime(void);
	const FILETIME *GetLastAccessTime(void);
	const FILETIME *GetLastWriteTime(void);
	DWORD GetVolumeSerialNumber(void);
	DWORD GetFileSizeHigh(void);
	DWORD GetFileSizeLow(void);
	DWORD GetNumberOfLinks(void);
	DWORD GetFileIndexHigh(void);
	DWORD GetFileIndexLow(void);
	};

#endif // MSTDLIB_API_WINDOWS


#endif // MFileInfo_h
