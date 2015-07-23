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
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyMatrix4.h"
#include "PolyVector2.h"
#include "PolyShader.h"
#include "PolyImage.h"
#include "PolyRectangle.h"
#include "PolyShader.h"
#include "PolyRenderDataArray.h"
#include "PolyThreaded.h"
#include "PolyGPUDrawBuffer.h"
#include <stack>
#include <queue>  

namespace Polycode {
    
    class _PolyExport GraphicsInterface : public PolyBase {
        public:
            GraphicsInterface();
            virtual void setParamInShader(Shader *shader, const ProgramParam &param, LocalShaderParam *localParam) = 0;
            virtual void setAttributeInShader(Shader *shader, const ProgramAttribute &attribute, AttributeBinding *attributeBinding) = 0;
            virtual void disableAttribute(Shader *shader, const ProgramAttribute &attribute) = 0;
            virtual void createTexture(Texture *texture, int filteringMode, int anisotropy, bool createMipmaps) = 0;
            virtual void setViewport(unsigned int x,unsigned  int y,unsigned  int width, unsigned height) = 0;
            virtual void clearBuffers(bool colorBuffer, bool depthBuffer, bool stencilBuffer) = 0;
            virtual void createProgram(ShaderProgram *program) = 0;
            virtual void createShader(Shader *shader) = 0;
            virtual void useShader(Shader *shader) = 0;
        
            virtual void drawIndices(int type, IndexDataArray *indexArray) = 0;
            virtual void drawArrays(int type, unsigned int vertexCount) = 0;
        
            virtual void enableDepthTest(bool val) = 0;
            virtual void enableDepthWrite(bool val) = 0;
        
    };
    
    class _PolyExport RendererThreadJob {
        public:
            int jobType;
            void *data;
    };
    
    class _PolyExport RendererOptions {
        public:
        
        int filteringMode;
        int anisotropy;
        bool createMipmaps;
    };
    
    class _PolyExport RenderThread : public Threaded {
        public:
            RenderThread();
            void setGraphicsInterface(Core *core, GraphicsInterface *interface);
            virtual void runThread();
            void enqueueJob(int jobType, void *data);
            void processJob(const RendererThreadJob &job);
        
            void processDrawBuffer(GPUDrawBuffer *buffer);
        
            static const int JOB_REQUEST_CONTEXT_CHANGE = 0;
            static const int JOB_CREATE_TEXTURE = 1;
            static const int JOB_PROCESS_DRAW_BUFFER = 2;
            static const int JOB_FLUSH_CONTEXT = 3;
            static const int JOB_CREATE_PROGRAM = 4;
            static const int JOB_CREATE_SHADER = 5;
        
        protected:
            Core *core;
            RendererOptions options;
            CoreMutex *jobQueueMutex;
            std::queue<RendererThreadJob> jobQueue;
            GraphicsInterface *interface;
        
            ShaderBinding *rendererShaderBinding;
            LocalShaderParam *projectionMatrixParam;
            LocalShaderParam *viewMatrixParam;
            LocalShaderParam *modelMatrixParam;
    };
    
    class _PolyExport Renderer : public PolyBase {
	public:
        
		Renderer();
		virtual ~Renderer();
        void setGraphicsInterface(Core *core, GraphicsInterface *interface);
        
        RenderThread *getRenderThread();

        Cubemap *createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5);
        Texture *createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, bool createMipmaps, int type=Image::IMAGE_RGBA);
        void destroyTexture(Texture *texture);
        void createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height, bool floatingPointBuffer);
        
        void processDrawBuffer(GPUDrawBuffer *buffer);
        
        void setBackingResolutionScale(Number xScale, Number yScale);
        Number getBackingResolutionScaleX();
        Number getBackingResolutionScaleY();
        ShaderProgram *createProgram(const String &fileName);
        Shader *createShader(ShaderProgram *vertexProgram, ShaderProgram *fragmentProgram);
        
        void setAnisotropyAmount(Number amount);
        Number getAnisotropyAmount();
        
        void flushContext();
        
        static const int BLEND_MODE_NONE = 0;
        static const int BLEND_MODE_NORMAL = 1;
        static const int BLEND_MODE_LIGHTEN = 2;
        static const int BLEND_MODE_COLOR = 3;
        static const int BLEND_MODE_PREMULTIPLIED = 4;
        static const int BLEND_MODE_MULTIPLY = 5;
        
        static const int DEPTH_FUNCTION_GREATER = 0;
        static const int DEPTH_FUNCTION_LEQUAL = 1;
        
        static const int TEX_FILTERING_NEAREST = 0;
        static const int TEX_FILTERING_LINEAR = 1;
        
        
	protected:
        
      
        Number backingResolutionScaleX;
        Number backingResolutionScaleY;
        
		Number anisotropy;
        
        int cpuBufferIndex;
        int gpuBufferIndex;
        RenderThread *renderThread;

	};
}
