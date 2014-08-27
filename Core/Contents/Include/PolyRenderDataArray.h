/*
 Copyright (C) 2014 by Ivan Safrin
 
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
#include <vector>

namespace Polycode {
    
    class RenderDataArray : public PolyBase {
    public:
        
        RenderDataArray(unsigned int type);
        unsigned int type;
        virtual void *getArrayData();
        virtual unsigned int getDataSize();
        
        /**
         * Vertex position array.
         */
        static const int VERTEX_DATA_ARRAY = 0;
        
        /**
         * Vertex color array.
         */
        static const int COLOR_DATA_ARRAY = 1;
        
        /**
         * Vertex normal array.
         */
        static const int NORMAL_DATA_ARRAY = 2;
        
        /**
         * Vertex texture coordinate array.
         */
        static const int TEXCOORD_DATA_ARRAY = 3;
        
        /**
         * Tangent array.
         */
        static const int TANGENT_DATA_ARRAY = 4;
        
        /**
         * Bone weight array.
         */
        static const int BONE_WEIGHT_DATA_ARRAY = 5;
        
        /**
         * Bone weight array.
         */
        static const int BONE_INDEX_DATA_ARRAY = 6;
        
        /**
         * Index data array.
         */
        static const int INDEX_DATA_ARRAY = 7;
        
        /**
         * Secondary texture coordinate array.
         */
        static const int TEXCOORD2_DATA_ARRAY = 8;
        
    };

    class VertexDataArray : public RenderDataArray {
    public:
        VertexDataArray(unsigned int type) : RenderDataArray(type) {
        }
        
        std::vector<PolyRendererVertexType> data;
        virtual void *getArrayData();
        virtual unsigned int getDataSize();
    };

    class IndexDataArray : public RenderDataArray {
    public:
        IndexDataArray(unsigned int type) : RenderDataArray(type) {
        }
        
        std::vector<PolyRendererIndexType> data;
        virtual void *getArrayData();
        virtual unsigned int getDataSize();
    };

}