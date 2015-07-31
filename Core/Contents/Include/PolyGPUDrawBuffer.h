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

#include "PolyMesh.h"
#include "PolyShader.h"
#include "PolyRectangle.h"
#include "PolyMaterial.h"
#include "PolyColor.h"

namespace Polycode {
    
    class _PolyExport GPUDrawOptions {
    public:
        bool depthTest;
        bool depthWrite;
        float linePointSize;
        bool alphaTest;
        bool backfaceCull;
        bool depthOnly;
        unsigned int blendingMode;
        Color drawColor;
    };
    
    
    class _PolyExport GPUDrawCall {
    public:
        unsigned int numVertices;
        unsigned char mode;
        bool indexed;
        
        GPUDrawOptions options;
        Matrix4 modelMatrix;
        Material *material;
        ShaderBinding *shaderBinding;
        IndexDataArray *indexArray;
    };
    
    class _PolyExport GPUDrawBuffer {
    public:
        GPUDrawBuffer();
        ~GPUDrawBuffer();
        
        Texture *targetFramebuffer;
        Matrix4 projectionMatrix;
        Matrix4 viewMatrix;
        Color clearColor;
        bool clearDepthBuffer;
        bool clearColorBuffer;
        
        Polycode::Rectangle viewport;
        std::vector<GPUDrawCall> drawCalls;
    };
}