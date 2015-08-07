
#include "polycode/core/PolyBasicFileProvider.h"

using namespace Polycode;

Polycode::CoreFile *BasicFileProvider::openFile(const String &fileName, const String &opts) {
    FILE *file = fopen(fileName.c_str(), opts.c_str());
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
