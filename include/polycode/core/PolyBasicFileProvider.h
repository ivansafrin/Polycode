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

#include "polycode/core/PolyCoreFileProvider.h"

namespace Polycode {
    
    class _PolyExport BasicFile : public CoreFile {
    public:
        
        long read( void * ptr, size_t size, size_t count);
        long write( const void * ptr, size_t size, size_t count);
        int seek(long int offset, int origin);
        long tell();
        
        FILE *file;
    };
    
    class _PolyExport BasicFileProvider : public CoreFileProvider {
        public:
            BasicFileProvider();
            Polycode::CoreFile *openFile(const String &fileName, const String &opts);
            void closeFile(Polycode::CoreFile *file);
            void addSource(const String &source);
            void removeSource(const String &source);
      
            std::vector<String> sourceFolders;
        
    };
    
}