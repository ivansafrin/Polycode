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

#include "PolyGlobals.h"
#include "PolyString.h"

struct PHYSFS_File;

class _PolyExport OSFileEntry : public PolyBase {

	public:
		OSFileEntry() {};
		OSFileEntry(const Polycode::String& fullPath, int type);
		OSFileEntry(const Polycode::String& path, const Polycode::String& name, int type);
		
		void init(const Polycode::String& path, const Polycode::String& name, int type);
		
		Polycode::String name;
		Polycode::String extension;
		Polycode::String nameWithoutExtension;
		Polycode::String basePath;
		Polycode::String fullPath;
		int type;
		
		static const int TYPE_FILE = 0;
		static const int TYPE_FOLDER = 1;
};

class _PolyExport OSFILE : public PolyBase {
public:
	OSFILE(){}
	
	void debugDump();
	
	int fileType;
	FILE *file;	
	PHYSFS_File *physFSFile;
	static const int TYPE_FILE = 0;
	static const int TYPE_ARCHIVE_FILE = 1;	
};

class _PolyExport OSBasics : public PolyBase {
	public:
	
		static OSFILE *open(const Polycode::String& filename, const Polycode::String& opts);
		static int close(OSFILE *file);
		static size_t read( void * ptr, size_t size, size_t count, OSFILE * stream );	
		static size_t write( const void * ptr, size_t size, size_t count, OSFILE * stream );
		static int seek(OSFILE * stream, long int offset, int origin );
		static long tell(OSFILE * stream);
	
		static std::vector<OSFileEntry> parsePhysFSFolder(const Polycode::String& pathString, bool showHidden);
		static std::vector<OSFileEntry> parseFolder(const Polycode::String& pathString, bool showHidden);
		static bool fileExists(const Polycode::String& pathString);
		static bool isFolder(const Polycode::String& pathString);
		static void createFolder(const Polycode::String& pathString);
		static void removeItem(const Polycode::String& pathString);
		static time_t getFileTime(const Polycode::String& pathString);
		
	private:
	
};
