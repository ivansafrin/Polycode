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


#include "PolyRenderer.h"
#include "PolyCoreServices.h"
#include "PolyCore.h"
#include "PolyTexture.h"

using namespace Polycode;

GPUDrawBuffer::GPUDrawBuffer() {
    
}

GPUDrawBuffer::~GPUDrawBuffer() {
    
}

GraphicsInterface::GraphicsInterface() {
}

RenderThread::RenderThread() : interface(NULL) {
    
    options.filteringMode = Renderer::TEX_FILTERING_LINEAR;
    options.anisotropy = 0;
    options.createMipmaps = true;
    
    rendererShaderBinding = new ShaderBinding();
    
    projectionMatrixParam = rendererShaderBinding->addParam(ProgramParam::PARAM_MATRIX, "projectionMatrix");
    modelMatrixParam = rendererShaderBinding->addParam(ProgramParam::PARAM_MATRIX, "modelMatrix");
    viewMatrixParam = rendererShaderBinding->addParam(ProgramParam::PARAM_MATRIX, "viewMatrix");
    
    jobQueueMutex = Services()->getCore()->createMutex();
}

void RenderThread::runThread() {
    while(threadRunning) {
        
        Services()->getCore()->lockMutex(jobQueueMutex);
        if(jobQueue.size() > 0) {
            RendererThreadJob nextJob = jobQueue.front();
            jobQueue.pop();
            processJob(nextJob);
        }
        Services()->getCore()->unlockMutex(jobQueueMutex);
    }
}

ShaderBinding *RenderThread::getShaderBinding() {
    return rendererShaderBinding;
}

void RenderThread::processDrawBuffer(GPUDrawBuffer *buffer) {
    
    ++currentDebugFrameInfo.buffersProcessed;
    
    interface->setViewport(buffer->viewport.x, buffer->viewport.y, buffer->viewport.w, buffer->viewport.h);
    interface->clearBuffers(buffer->clearColor, buffer->clearColorBuffer, buffer->clearDepthBuffer, true);
    
    projectionMatrixParam->setMatrix4(buffer->projectionMatrix);
    viewMatrixParam->setMatrix4(buffer->viewMatrix);
    
    for(int i=0; i < buffer->drawCalls.size(); i++) {
        
        interface->beginDrawCall();
        
        interface->setBlendingMode(buffer->drawCalls[i].options.blendingMode);
        interface->enableDepthTest(buffer->drawCalls[i].options.depthTest);
        interface->enableDepthWrite(buffer->drawCalls[i].options.depthWrite);
        
        modelMatrixParam->setMatrix4(buffer->drawCalls[i].modelMatrix);
        
        if(buffer->drawCalls[i].material) {
            
            for(int s=0; s < buffer->drawCalls[i].material->getNumShaders(); s++) {
        
                ++currentDebugFrameInfo.drawCallsProcessed;
                
                Shader *shader = buffer->drawCalls[i].material->getShader(s);
                interface->useShader(shader);
                
                // set shader uniforms
   
                for(int p=0; p < buffer->drawCalls[i].shaderParams.size(); p++) {
                    interface->setParamInShader(shader, buffer->drawCalls[i].shaderParams[p].programParam, buffer->drawCalls[i].shaderParams[p].localParam);
                    
                }
                
                 for(int a=0; a < buffer->drawCalls[i].shaderAttributes.size(); a++) {
                        interface->setAttributeInShader(shader, buffer->drawCalls[i].shaderAttributes[a].programAttribute,  buffer->drawCalls[i].shaderAttributes[a].attributeBinding);
                 }
                
                if(buffer->drawCalls[i].indexed) {
                    interface->drawIndices(buffer->drawCalls[i].mode, buffer->drawCalls[i].indexArray);
                } else {
                    interface->drawArrays(buffer->drawCalls[i].mode, buffer->drawCalls[i].numVertices);
                }
                
                
                for(int a=0; a < shader->expectedAttributes.size(); a++) {
                    ProgramAttribute attribute = shader->expectedAttributes[a];
                    interface->disableAttribute(shader, attribute);
                }
                

            }
        }
    }
}

void RenderThread::processJob(const RendererThreadJob &job) {
    switch(job.jobType) {
        case JOB_REQUEST_CONTEXT_CHANGE:
        {
            VideoModeChangeInfo *modeInfo = (VideoModeChangeInfo*) job.data;
            core->handleVideoModeChange(modeInfo);
            delete modeInfo;
        }
        break;
        case JOB_CREATE_TEXTURE:
        {
            Texture *texture = (Texture*) job.data;
            interface->createTexture(texture, options.filteringMode, options.anisotropy, options.createMipmaps);
        }
        break;
        case JOB_PROCESS_DRAW_BUFFER:
        {
            GPUDrawBuffer *buffer = (GPUDrawBuffer*) job.data;
            processDrawBuffer(buffer);
            delete buffer;
        }
        break;
        case JOB_FLUSH_CONTEXT:
        {
            core->flushRenderContext();
            
            currentDebugFrameInfo.timeTaken = Services()->getCore()->getTicks() - frameStart;
            lastFrameDebugInfo = currentDebugFrameInfo;
            currentDebugFrameInfo.buffersProcessed = 0;
            currentDebugFrameInfo.drawCallsProcessed = 0;
            currentDebugFrameInfo.timeTaken = 0;
            frameStart = Services()->getCore()->getTicks();
        }
        break;
        case JOB_CREATE_PROGRAM:
        {
            ShaderProgram *program = (ShaderProgram*) job.data;
            interface->createProgram(program);
        }
        break;
        case JOB_CREATE_SHADER:
        {
            Shader *shader = (Shader*) job.data;
            interface->createShader(shader);
        }
        break;
    }
}

RenderThreadDebugInfo RenderThread::getFrameInfo() {
    return lastFrameDebugInfo;
}

void RenderThread::enqueueJob(int jobType, void *data) {
    Services()->getCore()->lockMutex(jobQueueMutex);
    RendererThreadJob job;
    job.jobType = jobType;
    job.data = data;
    jobQueue.push(job);
    Services()->getCore()->unlockMutex(jobQueueMutex);
}

void RenderThread::setGraphicsInterface(Core *core, GraphicsInterface *interface) {
    this->interface = interface;
    this->core = core;
}

Renderer::Renderer() {
    renderThread = new RenderThread();
    Services()->getCore()->createThread(renderThread);
    
    cpuBufferIndex = 0;
    gpuBufferIndex = 1;
}

Renderer::~Renderer() {
    
}

void Renderer::setGraphicsInterface(Core *core, GraphicsInterface *interface) {
    renderThread->setGraphicsInterface(core, interface);
}

RenderThread *Renderer::getRenderThread() {
    return renderThread;
}

void Renderer::setBackingResolutionScale(Number xScale, Number yScale) {
    backingResolutionScaleX = xScale;
    backingResolutionScaleY = yScale;
}

Number Renderer::getBackingResolutionScaleX() {
    return backingResolutionScaleX;
}

Number Renderer::getBackingResolutionScaleY() {
    return backingResolutionScaleY;
}

Number Renderer::getAnisotropyAmount() {
    return anisotropy;
}

void Renderer::setAnisotropyAmount(Number amount) {
    anisotropy = amount;
}

Cubemap *Renderer::createCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5) {
    return NULL;
}

void Renderer::processDrawBuffer(GPUDrawBuffer *buffer) {
    renderThread->enqueueJob(RenderThread::JOB_PROCESS_DRAW_BUFFER, buffer);
}

void Renderer::flushContext() {
    renderThread->enqueueJob(RenderThread::JOB_FLUSH_CONTEXT, NULL);
}

Texture *Renderer::createTexture(unsigned int width, unsigned int height, char *textureData, bool clamp, bool createMipmaps, int type) {
    Texture *texture = new Texture(width, height, textureData, clamp, createMipmaps, type);
    renderThread->enqueueJob(RenderThread::JOB_CREATE_TEXTURE, (void*)texture);
    return texture;
}

Shader *Renderer::createShader(ShaderProgram *vertexProgram, ShaderProgram *fragmentProgram) {
    Shader *shader = new Shader();
    shader->vertexProgram = vertexProgram;
    shader->fragmentProgram = fragmentProgram;
    renderThread->enqueueJob(RenderThread::JOB_CREATE_SHADER, (void*)shader);
    return shader;
}

ShaderProgram *Renderer::createProgram(const String &fileName) {
    ShaderProgram *program = new ShaderProgram(fileName);
    
    OSFileEntry fileEntry(program->getResourcePath(), OSFileEntry::TYPE_FILE);
    
    if(fileEntry.extension == "vert" ) {
        program->type = ShaderProgram::TYPE_VERT;
    } else {
        program->type = ShaderProgram::TYPE_FRAG;
    }
    
    renderThread->enqueueJob(RenderThread::JOB_CREATE_PROGRAM, (void*)program);
    return program;
}

void Renderer::destroyTexture(Texture *texture) {
    
}
void createRenderTextures(Texture **colorBuffer, Texture **depthBuffer, int width, int height, bool floatingPointBuffer) {
    
}

