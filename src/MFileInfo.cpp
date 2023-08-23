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
#include "MStdLib.h"
#include "TAutoPtr.h"
#include "MFileInfo.h"

#if ( defined(MSTDLIB_API_WINDOWS) )


//*******************************************************
//*	MFileInfo 
//*******************************************************
void MFileInfo::ClearObject(void)
	{
	// Nothing Here
	}


/////////////////////////////////////////////////////
MFileInfo::MFileInfo(void)
	{  ClearObject();  }


////////////////////////////////////////////////////
MFileInfo::MFileInfo(const char *filename)
	{
	ClearObject();
	if(Create(filename)==false)
		{
		return;
		}
	}


/////////////////////////////////////////////////////
MFileInfo::~MFileInfo(void)
	{  Destroy();  }


/////////////////////////////////////////////////////
bool MFileInfo::Create(const char *filename)
	{
	Destroy();

	//allocate space
	
	if(mpInfo.Create()==false)
		{
		Destroy();
		return false;
		}

	// Open File Info
	HANDLE hfile=CreateFileA(filename,0,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if(hfile==INVALID_HANDLE_VALUE)
		{
		Destroy();  return false;
		}

	if(GetFileInformationByHandle(hfile,mpInfo.Get() )==FALSE)
		{
		CloseHandle(hfile);
		Destroy();  
		return false;
		}

	CloseHandle(hfile);
	return true;
	}


/////////////////////////////////////////////////////
bool MFileInfo::Destroy(void)
	{
	mpInfo.Destroy();
	ClearObject();
	return true;
	}



/////////////////////////////////////////////////////
const FILETIME *MFileInfo::GetCreationTime(void)
	{
	return &(mpInfo->ftCreationTime);
	}


/////////////////////////////////////////////////////
const FILETIME *MFileInfo::GetLastAccessTime(void)
	{
	return &(mpInfo->ftLastAccessTime);
	}


/////////////////////////////////////////////////////
const FILETIME *MFileInfo::GetLastWriteTime(void)
	{
	return &(mpInfo->ftLastWriteTime);
	}


/////////////////////////////////////////////////////
DWORD MFileInfo::GetVolumeSerialNumber(void)
	{
	return mpInfo->dwVolumeSerialNumber;
	}


/////////////////////////////////////////////////////
DWORD MFileInfo::GetFileSizeHigh(void)
	{
	return mpInfo->nFileSizeHigh;
	}


/////////////////////////////////////////////////////
DWORD MFileInfo::GetFileSizeLow(void)
	{
	return mpInfo->nFileSizeLow;
	}


/////////////////////////////////////////////////////
DWORD MFileInfo::GetNumberOfLinks(void)
	{
	return mpInfo->nNumberOfLinks;
	}


/////////////////////////////////////////////////////
DWORD MFileInfo::GetFileIndexHigh(void)
	{
	return mpInfo->nFileIndexHigh;
	}


/////////////////////////////////////////////////////
DWORD MFileInfo::GetFileIndexLow(void)
	{
	return mpInfo->nFileIndexLow;
	}


#endif //MSTDLIB_API_WINDOWS

