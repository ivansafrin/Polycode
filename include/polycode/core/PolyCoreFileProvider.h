/*
 Copyright (C) 2015 by Ivan Safrin
 
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

namespace Polycode {
    
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
    
    class CoreFileProvider;
    
    class _PolyExport CoreFile : public PolyBase {
    public:
        CoreFile(){}
        
        virtual long read( void * ptr, size_t size, size_t count) = 0;
        virtual long write( const void * ptr, size_t size, size_t count) = 0;
        virtual int seek(long int offset, int origin) = 0;
        virtual long tell() = 0;
        
        CoreFileProvider *provider;
    };
    
    class _PolyExport CoreFileProvider {
    public:
        CoreFileProvider();
        
        virtual CoreFile *openFile(const String &fileName, const String &opts) = 0;
        virtual void closeFile(CoreFile *file) = 0;
        virtual bool parseFolder(const Polycode::String& pathString, bool showHidden, std::vector<OSFileEntry> &targetVector);
        
        bool canListFiles;
    };

    
}