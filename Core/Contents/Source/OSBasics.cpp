/*
 *  OSBasics.cpp
 *  PolyStudio
 *
 *  Created by Ivan Safrin on 8/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "OSBasics.h"


#ifdef _WINDOWS

void wtoc(char* Dest, const WCHAR* Source)
{
	int i = 0;
	while(Source[i] != '\0') {
		Dest[i] = (char)Source[i];
		++i;
	}
}
void ctow(WCHAR* Dest, const char* Source)
{
	int i = 0;
	while(Source[i] != '\0') {
		Dest[i] = (WCHAR)Source[i];
		++i;
	}
}

#endif

OSFileEntry::OSFileEntry(String path, String name, int type) {
	this->basePath = path;
	this->fullPath = path + "/" + name;
	this->name = name;
	this->type = type;

	size_t found;
	found=this->name.rfind(".");
	if (found!=string::npos) {
		extension = this->name.substr(found+1);
		nameWithoutExtension = this->name.substr(0, found);
	} else {
		extension = "";
		nameWithoutExtension = name;
	}
}

void OSFILE::debugDump() {
	long tellval = OSBasics::tell(this);
	OSBasics::seek(this, 0, SEEK_SET);
	
	char buffer;
	while(OSBasics::read(&buffer, 1, 1, this)) {
		printf("%c", buffer);
	}
	
	OSBasics::seek(this, tellval, SEEK_SET);
}

OSFILE *OSBasics::open(String filename, String opts) {
	OSFILE *retFile = NULL;
	if(PHYSFS_exists(filename.c_str())) {
		if(!PHYSFS_isDirectory(filename.c_str())) {
			retFile = new OSFILE;
			retFile->fileType = OSFILE::TYPE_ARCHIVE_FILE;
			if(opts.find("a") !=string::npos) {
				retFile->physFSFile = PHYSFS_openAppend(filename.c_str());				
				if(!retFile->physFSFile){
					printf("Error opening file from archive (%s)\n", filename.c_str());
					return NULL;		
				}
			} else if(opts.find("w") !=string::npos) {
				retFile->physFSFile = PHYSFS_openWrite(filename.c_str());				
				if(!retFile->physFSFile){
					printf("Error opening file from archive (%s)\n", filename.c_str());
					return NULL;		
				}
			} else {
				retFile->physFSFile = PHYSFS_openRead(filename.c_str());				
				if(!retFile->physFSFile){
					printf("Error opening file from archive (%s)\n", filename.c_str());
					return NULL;		
				}
			}
			return retFile;
		}
	} else {
	//	Logger::log("File doesn't exist in archive\n");
	}
	
	FILE *file = fopen(filename.c_str(), opts.c_str());
	if(file) {
		retFile = new OSFILE;
		retFile->fileType = OSFILE::TYPE_FILE;
		retFile->file = file;		
		return retFile;
	}
	
	return NULL;
}

int OSBasics::close(OSFILE *file) {
	switch(file->fileType) {
		case OSFILE::TYPE_FILE:
			return fclose(file->file);
			break;
		case OSFILE::TYPE_ARCHIVE_FILE:
			return PHYSFS_close(file->physFSFile);
			break;			
	}
	return 0;
}

long OSBasics::tell(OSFILE * stream) {
	switch(stream->fileType) {
		case OSFILE::TYPE_FILE:
			return ftell(stream->file);
			break;
		case OSFILE::TYPE_ARCHIVE_FILE:
			return PHYSFS_tell(stream->physFSFile);
			break;			
	}
	return 0;
}

size_t OSBasics::read( void * ptr, size_t size, size_t count, OSFILE * stream ) {
	switch(stream->fileType) {
		case OSFILE::TYPE_FILE:
			return fread(ptr, size, count, stream->file);
		break;
		case OSFILE::TYPE_ARCHIVE_FILE:
			return PHYSFS_read(stream->physFSFile, ptr, size, count);
		break;			
	}
	return 0;
}

size_t OSBasics::write( const void * ptr, size_t size, size_t count, OSFILE * stream ) {
	switch(stream->fileType) {
		case OSFILE::TYPE_FILE:
			fwrite(ptr, size, count, stream->file);
			break;
		case OSFILE::TYPE_ARCHIVE_FILE:
			PHYSFS_write(stream->physFSFile, ptr, size, count);
		break;			
	}
	return 0;
}

int OSBasics::seek(OSFILE * stream, long int offset, int origin ) {
	switch(stream->fileType) {
		case OSFILE::TYPE_FILE:
			return fseek(stream->file, offset, origin);
			break;
		case OSFILE::TYPE_ARCHIVE_FILE:
			switch(origin) {
				case SEEK_SET:
					return PHYSFS_seek(stream->physFSFile, offset);
				break;
				case SEEK_CUR: {
					PHYSFS_sint64 curoffset = PHYSFS_tell(stream->physFSFile);					
					return PHYSFS_seek(stream->physFSFile, curoffset+offset);				
				}
				break;
				case SEEK_END: {
					PHYSFS_sint64 fileLength =  PHYSFS_fileLength(stream->physFSFile);
					return PHYSFS_seek(stream->physFSFile, fileLength-offset);
				}
				break;
			}
			break;			
	}
	return 0;	
}

vector<OSFileEntry> OSBasics::parsePhysFSFolder(String pathString, bool showHidden) {
	vector<OSFileEntry> returnVector;
	
	char **rc = PHYSFS_enumerateFiles(pathString.c_str());
	char **i;
	
	String fullPath;
	String fname;
	for (i = rc; *i != NULL; i++) {
		fname = string(*i);
		fullPath = pathString + "/" + fname;
		printf("parsing in %s\n", *i);
		if((fname.c_str()[0] != '.' || (fname.c_str()[0] == '.'  && showHidden)) && fname != "..") {
			if(PHYSFS_isDirectory(fullPath.c_str())) {
				returnVector.push_back(OSFileEntry(pathString, fname, OSFileEntry::TYPE_FOLDER));
			} else { 
				returnVector.push_back(OSFileEntry(pathString, fname, OSFileEntry::TYPE_FILE));		
			}
		}
	}
	PHYSFS_freeList(rc);	
	return returnVector;
}

vector<OSFileEntry> OSBasics::parseFolder(String pathString, bool showHidden) {
	vector<OSFileEntry> returnVector;
	
	if(pathString.size() < 128) {
		if(PHYSFS_exists(pathString.c_str())) {
			if(PHYSFS_isDirectory(pathString.c_str())) {
				return parsePhysFSFolder(pathString, showHidden);
			}
		}
	}
	
	
#ifdef _WINDOWS

	WIN32_FIND_DATA findFileData;

	WCHAR curDir[4096];
	GetCurrentDirectory(4096, curDir);

	WCHAR tmp[4096];
	memset(tmp, 0, sizeof(WCHAR)*4096);
	ctow(tmp, pathString.c_str());
	SetCurrentDirectory(tmp);

	HANDLE hFind = FindFirstFile((LPCWSTR)"*", &findFileData);
	if(hFind  == INVALID_HANDLE_VALUE) {
		SetCurrentDirectory(curDir);
		return returnVector;
	}

	char fileName[260];
	do {		
		memset(fileName, 0, 260);
		wtoc(fileName, findFileData.cFileName);
		String fname = string(fileName);
		
		if((fname.c_str()[0] != '.' || (fname.c_str()[0] == '.'  && showHidden)) && fname != "..") {
			if( findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
				returnVector.push_back(OSFileEntry(pathString, fname, OSFileEntry::TYPE_FOLDER));
			} else {
				returnVector.push_back(OSFileEntry(pathString, fname, OSFileEntry::TYPE_FILE));
			}
		}
    } while(FindNextFile(hFind, &findFileData));	
	FindClose(hFind);
	SetCurrentDirectory(curDir);
#else
	DIR           *d;
	struct dirent *dir;
	
	d = opendir(pathString.c_str());
	if(d) {
		while ((dir = readdir(d)) != NULL) {
			if(dir->d_name[0] != '.' || (dir->d_name[0] == '.'  && showHidden)) {
				if(dir->d_type == DT_DIR) {
					returnVector.push_back(OSFileEntry(pathString, dir->d_name, OSFileEntry::TYPE_FOLDER));
				} else {
					returnVector.push_back(OSFileEntry(pathString, dir->d_name, OSFileEntry::TYPE_FILE));
				}
			}
		}
		closedir(d);
	}
	
#endif
		
	return returnVector;
}

void OSBasics::createFolder(String pathString) {
#ifdef _WINDOWS
#else
	mkdir(pathString.c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
}

bool OSBasics::isFolder(String pathString) {	
	bool retVal = false;
#ifdef _WINDOWS
#else
	DIR           *d;
	
	d = opendir(pathString.c_str());
	if(d) {
		retVal = true;
		closedir(d);
	}
#endif
	return retVal;
}