
#include "polycode/core/PolyPhysFSFileProvider.h"
#include "polycode/core/PolyLogger.h"

using namespace Polycode;

PhysFSFileProvider::PhysFSFileProvider() {
	canListFiles = true;
	type = "archive";
	PHYSFS_init(NULL);
}

PhysFSFileProvider::~PhysFSFileProvider() {
	PHYSFS_deinit();	
}

bool PhysFSFileProvider::parseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector) {
	
	if(pathString != "/") {
		if(pathString.size() < 128) {
			if(PHYSFS_exists(pathString.c_str())) {
				if(PHYSFS_isDirectory(pathString.c_str())) {
					
					char **rc = PHYSFS_enumerateFiles(pathString.c_str());
					char **i;
					
					String fullPath;
					String fname;
					for (i = rc; *i != NULL; i++) {
						fname = std::string(*i);
						fullPath = pathString + "/" + fname;
						if((fname.c_str()[0] != '.' || (fname.c_str()[0] == '.'	 && showHidden)) && fname != "..") {
							if(PHYSFS_isDirectory(fullPath.c_str())) {
								targetVector.push_back(OSFileEntry(pathString, fname, OSFileEntry::TYPE_FOLDER));
							} else {
								targetVector.push_back(OSFileEntry(pathString, fname, OSFileEntry::TYPE_FILE));
							}
						}
					}
					PHYSFS_freeList(rc);	
					return true;;
					
				}
			}
		}
	}
	return false;
}

Polycode::CoreFile *PhysFSFileProvider::openFile(const String &fileName, const String &opts) {
	
	PhysFSFile *retFile = NULL;
	if(PHYSFS_exists(fileName.c_str())) {
		if(!PHYSFS_isDirectory(fileName.c_str())) {
			retFile = new PhysFSFile();
			
			if(opts.find("a") != -1) {
				retFile->physFSFile = PHYSFS_openAppend(fileName.c_str());
			} else if(opts.find("w") != -1) {
				retFile->physFSFile = PHYSFS_openWrite(fileName.c_str());
			} else {
				retFile->physFSFile = PHYSFS_openRead(fileName.c_str());
			}
			return retFile;
		}
	}
	return NULL;
}

void PhysFSFileProvider::addSource(const String &source) {
	if(PHYSFS_addToSearchPath(source.c_str(), 1) == 0) {
		Logger::log("Error adding physfs archive: %s [%s]\n", PHYSFS_getLastError(), source.c_str());
	} else {
		Logger::log("Added physfs archive: %s\n", source.c_str());
	}
}

void PhysFSFileProvider::removeSource(const String &source) {
	PHYSFS_removeFromSearchPath(source.c_str());
}

void PhysFSFileProvider::closeFile(Polycode::CoreFile *file) {
	PhysFSFile *physFSFile = (PhysFSFile*) file;
	PHYSFS_close(physFSFile->physFSFile);
	delete physFSFile;
}

long PhysFSFile::read( void * ptr, size_t size, size_t count) {
	return PHYSFS_read(physFSFile, ptr, size, count);
}

long PhysFSFile::write( const void * ptr, size_t size, size_t count) {
	return PHYSFS_write(physFSFile, ptr, size, count);
}

int PhysFSFile::seek(long int offset, int origin) {
	switch(origin) {
		case SEEK_SET:
			return PHYSFS_seek(physFSFile, offset);
			break;
		case SEEK_CUR: {
			PHYSFS_sint64 curoffset = PHYSFS_tell(physFSFile);
			return PHYSFS_seek(physFSFile, curoffset+offset);
		}
			break;
		case SEEK_END: {
			PHYSFS_sint64 fileLength =	PHYSFS_fileLength(physFSFile);
			return PHYSFS_seek(physFSFile, fileLength-offset);
		}
			break;
	}
	return 0;
}

long PhysFSFile::tell() {
	return PHYSFS_tell(physFSFile);	  
}

