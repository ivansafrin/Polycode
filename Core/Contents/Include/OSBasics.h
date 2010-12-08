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

class _PolyExport OSFileEntry {
	public:
		OSFileEntry() {};
		OSFileEntry(string path, string name, int type);
		
		string name;
		string extension;
		string nameWithoutExtension;
		string basePath;
		string fullPath;
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
	
		static OSFILE *open(string filename, string opts);
		static int close(OSFILE *file);
		static size_t read( void * ptr, size_t size, size_t count, OSFILE * stream );	
		static size_t write( const void * ptr, size_t size, size_t count, OSFILE * stream );
		static int seek(OSFILE * stream, long int offset, int origin );
		static long tell(OSFILE * stream);
	
		static vector<OSFileEntry> parsePhysFSFolder(string pathString, bool showHidden);
		static vector<OSFileEntry> parseFolder(string pathString, bool showHidden);
		static bool isFolder(string pathString);
		static void createFolder(string pathString);
		
	private:
	
};