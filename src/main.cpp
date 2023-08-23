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


//v1.0 copyright Comine.com 20060927W17
#include "MStdLib.h"
#include "MFileOps.h"
#include "MWatchDirectory.h"
#include "MPathNameList.h"
#include "MBuffer.h"
#include "MFileInfo.h"
#include "MCommandArg.h"
#include "MTime.h"
#include "MProcessJob.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MWatch";	// Used in Help
static const char *GApplicationVersion="1.1";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	///////////////////////////////////////////////
	if(args.GetArgCount()<3)
		{
		GDisplayHelp();
		return 0;
		}

	// Init MFileOps
	MFileOps fileops;
	if(fileops.Create()==false)
		{
		MStdPrintf("**Unable to init MFileOps\n");
		return 1;
		}

	// Find File path
	MString filepath;
	if(fileops.GetAbsolutePath(args.GetArg(1),filepath)==false)
		{
		MStdPrintf("**Unable to get file path\n");
		return 1;
		}

	// Check if file exists
	if(fileops.Exists(filepath.Get())==false)
		{
		MStdPrintf("**Unable to find watch file\n");
		return 1;
		}

	MPathNameList pathlist;
	if(pathlist.Create(filepath.Get())==false)
		{
		MStdPrintf("**Unable to init MPathNameList",__LINE__);
		return 1;
		}

	// Pop off file name and get directory
	if(pathlist.Pop()==false)
		{
		MStdPrintf("**Unable to pop off file name",__LINE__);
		return 1;
		}

	// Get the full path of the directory
	MBuffer dirpath;
	if(pathlist.GetFullPath(dirpath)==false)
		{
		MStdPrintf("**Unable to get path to directory\n");
		return 1;
		}

	MWatchDirectory watcher;
	if(watcher.Create(dirpath.GetBuffer())==false)
		{
		MStdPrintf("**Unable to start watching directory\n");
		return 1;
		}

	MFileInfo fileinfo;
	if(fileinfo.Create(args.GetArg(1))==false)
		{
		MStdPrintf("**Unable to int MFileInfo\n");
		return 1;
		}

	FILETIME ft;
	ft=*fileinfo.GetLastWriteTime();

	MTimeWatch clock;
	if(clock.Create()==false)
		{
		return 1;
		}
		

	MStdPrintf("Watching file %s\n",filepath.Get() );
	// Loop the file
	for(;;)
		{
		if(watcher.Watch()!=0)
			{
			MStdPrintf("**Unable to watch directory\n");
			return 1;
			}

		if(clock.GetCount()<1000)
			{
			continue;
			}

		if(fileinfo.Create(args.GetArg(1))==false)
			{
			MStdPrintf("**Unable to int MFileInfo\n");
			return 1;
			}

		FILETIME newtime;
		newtime=*fileinfo.GetLastWriteTime();
		if(newtime.dwLowDateTime != ft.dwLowDateTime 
				|| newtime.dwHighDateTime != ft.dwHighDateTime )
			{
			MStdPrintf("Executing %s\n",args.GetArg(2) );
			MProcessJob job;
			if(job.Create(args.GetArg(2))==false)
				{
				MStdPrintf("**Unable to init MProcessJob\n");
				return 1;
				}

			job.Wait();
			}

		clock.Create();

		ft=newtime;		

		MStdPrintf("Watching file %s\n",filepath.Get() );
		}

	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s <watchfile> <executeprogram>[-?]\n"
				"           v%s copyright Comine.com\n"
				"\n"
				"   Program will watch a file for changes.  If the file changes,\n"
				"   the execute program will be executed automatically.\n"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


