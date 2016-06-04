
#include "polycode/core/PolyBasicFileProvider.h"

using namespace Polycode;

BasicFileProvider::BasicFileProvider() : CoreFileProvider() {
	type = "folder";
}

void BasicFileProvider::addSource(const String &source) {
	sourceFolders.push_back(source);
}

void BasicFileProvider::removeSource(const String &source) {
	for(int i=0; i < sourceFolders.size(); i++) {
		if(sourceFolders[i] == source) {
			sourceFolders.erase(sourceFolders.begin()+i);
			return;
		}
	}
}

Polycode::CoreFile *BasicFileProvider::openFile(const String &fileName, const String &opts) {
	
	FILE *file = NULL;
	for(int i=0; i < sourceFolders.size(); i++) {
		file = fopen((sourceFolders[i]+"/"+fileName).c_str(), opts.c_str());
		if(file) {
			break;
		}
	}
	
	if(!file) {
		file = fopen(fileName.c_str(), opts.c_str());
	}
	
	if(file) {
		BasicFile *retFile = NULL;
		retFile = new BasicFile();
		retFile->file = file;
		return retFile;
	}
	
	return NULL;
}

void BasicFileProvider::closeFile(Polycode::CoreFile *file) {
	BasicFile *basicFile = (BasicFile*) file;
	fclose(basicFile->file);
	delete basicFile;
}

long BasicFile::read( void * ptr, size_t size, size_t count) {
	return fread(ptr, size, count, file);
}

long BasicFile::write( const void * ptr, size_t size, size_t count) {
	return fwrite(ptr, size, count, file);
}

int BasicFile::seek(long int offset, int origin) {
	return fseek(file, offset, origin);
}

long BasicFile::tell() {
	return ftell(file);
}
