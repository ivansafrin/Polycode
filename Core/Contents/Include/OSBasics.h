/*
 *  OSBasics.h
 *  PolyStudio
 *
 *  Created by Ivan Safrin on 8/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package System

#pragma once

#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyString.h"

#ifdef _WINDOWS
	#include <windows.h>
#else
	#include <dirent.h> 
	#include <sys/types.h>s
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
		OSFileEntry(String path, String name, int type);
		
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
	
		static OSFILE *open(String filename, String opts);
		static int close(OSFILE *file);
		static size_t read( void * ptr, size_t size, size_t count, OSFILE * stream );	
		static size_t write( const void * ptr, size_t size, size_t count, OSFILE * stream );
		static int seek(OSFILE * stream, long int offset, int origin );
		static long tell(OSFILE * stream);
	
		static vector<OSFileEntry> parsePhysFSFolder(String pathString, bool showHidden);
		static vector<OSFileEntry> parseFolder(String pathString, bool showHidden);
		static bool isFolder(String pathString);
		static void createFolder(String pathString);
		
	private:
	
};