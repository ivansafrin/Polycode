/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#pragma once

#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyString.h"

#ifdef _WINDOWS
	#include <windows.h>
#else
	#include <dirent.h> 
	#include <sys/types.h>
	#include <sys/stat.h>
#endif

#include <vector>
#include <string>
#include "physfs.h"

using namespace std;
using namespace Polycode;

class _PolyExport OSFileEntry {
	public:
		OSFileEntry() {};
		OSFileEntry(const String& path, const String& name, int type);
		
		String name;
		String extension;
		String nameWithoutExtension;
		String basePath;
		String fullPath;
		int type;
		
		static const int TYPE_FILE = 0;
		static const int TYPE_FOLDER = 1;
};

class _PolyExport OSFILE {
public:
	OSFILE(){}
	
	void debugDump();
	
	int fileType;
	FILE *file;	
	PHYSFS_file *physFSFile;
	static const int TYPE_FILE = 0;
	static const int TYPE_ARCHIVE_FILE = 1;	
};

class _PolyExport OSBasics {
	public:
	
		static OSFILE *open(const String& filename, const String& opts);
		static int close(OSFILE *file);
		static size_t read( void * ptr, size_t size, size_t count, OSFILE * stream );	
		static size_t write( const void * ptr, size_t size, size_t count, OSFILE * stream );
		static int seek(OSFILE * stream, long int offset, int origin );
		static long tell(OSFILE * stream);
	
		static vector<OSFileEntry> parsePhysFSFolder(const String& pathString, bool showHidden);
		static vector<OSFileEntry> parseFolder(const String& pathString, bool showHidden);
		static bool isFolder(const String& pathString);
		static void createFolder(const String& pathString);
		static void removeItem(const String& pathString);
		
	private:
	
};
