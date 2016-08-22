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


#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyVector4.h"
#include "polycode/core/PolyLogger.h"
#if PLATFORM == PLATFORM_ANDROID
	#include <unistd.h>
#endif


using namespace Polycode;

RenderFrame::RenderFrame(const Polycode::Rectangle &viewport) : viewport(viewport), customFrameFinalizer(NULL), customFrameFinalizerData(NULL) {
	
}

RenderFrame::~RenderFrame() {
	while(drawBuffers.size() > 0) {
		GPUDrawBuffer *buffer = drawBuffers.front();
		delete buffer;
		drawBuffers.pop();
	}
}

void RenderFrame::addDrawBuffer(GPUDrawBuffer *buffer) {
	drawBuffers.push(buffer);
}

GraphicsInterface::GraphicsInterface() {
}

RenderThread::RenderThread() : graphicsInterface(NULL) {
}

void RenderThread::initGlobals() {
	rendererShaderBinding = new ShaderBinding();
	
	projectionMatrixParam = rendererShaderBinding->addParam(ProgramParam::PARAM_MATRIX, "projectionMatrix");
	modelMatrixParam = rendererShaderBinding->addParam(ProgramParam::PARAM_MATRIX, "modelMatrix");
	viewMatrixParam = rendererShaderBinding->addParam(ProgramParam::PARAM_MATRIX, "viewMatrix");
	
	for(int i=0; i < RENDERER_MAX_LIGHTS; i++) {
		lights[i].position = rendererShaderBinding->addParam(ProgramParam::PARAM_VECTOR3, "lights["+String::IntToString(i)+"].position");
		lights[i].direction = rendererShaderBinding->addParam(ProgramParam::PARAM_VECTOR3, "lights["+String::IntToString(i)+"].direction");
		lights[i].specular = rendererShaderBinding->addParam(ProgramParam::PARAM_COLOR, "lights["+String::IntToString(i)+"].specular");
		lights[i].diffuse = rendererShaderBinding->addParam(ProgramParam::PARAM_COLOR, "lights["+String::IntToString(i)+"].diffuse");
		lights[i].spotExponent = rendererShaderBinding->addParam(ProgramParam::PARAM_NUMBER, "lights["+String::IntToString(i)+"].spotExponent");
		lights[i].spotCosCutoff = rendererShaderBinding->addParam(ProgramParam::PARAM_NUMBER, "lights["+String::IntToString(i)+"].spotCosCutoff");
		lights[i].constantAttenuation = rendererShaderBinding->addParam(ProgramParam::PARAM_NUMBER, "lights["+String::IntToString(i)+"].constantAttenuation");
		lights[i].linearAttenuation = rendererShaderBinding->addParam(ProgramParam::PARAM_NUMBER, "lights["+String::IntToString(i)+"].linearAttenuation");
		lights[i].quadraticAttenuation = rendererShaderBinding->addParam(ProgramParam::PARAM_NUMBER, "lights["+String::IntToString(i)+"].quadraticAttenuation");
		lights[i].shadowEnabled = rendererShaderBinding->addParam(ProgramParam::PARAM_NUMBER, "lights["+String::IntToString(i)+"].shadowEnabled");
		
	}
	
	for(int i=0; i < RENDERER_MAX_LIGHT_SHADOWS; i++) {
		lightShadows[i].shadowMatrix = rendererShaderBinding->addParam(ProgramParam::PARAM_MATRIX, "lightsShadows["+String::IntToString(i)+"].shadowMatrix");
		lightShadows[i].shadowBuffer = rendererShaderBinding->addParam(ProgramParam::PARAM_TEXTURE, "lightsShadows["+String::IntToString(i)+"].shadowBuffer");
		lightShadows[i].shadowBuffer->setTexture(NULL);
		
	}
}

void RenderThread::updateRenderThread() {
	jobQueueMutex.lock();
		
	while (jobQueue.size() > 0) {
		RendererThreadJob nextJob = jobQueue.front();
		jobQueue.pop();
#if PLATFORM == PLATFORM_ANDROID
		if (!core->isWindowInitialized() && nextJob.jobType != JOB_REQUEST_CONTEXT_CHANGE) {
			jobQueue.push(nextJob);
			for (int i = 0; i < jobQueue.size() - 1; i++) {
				RendererThreadJob fJob = jobQueue.front();
				if (fJob.jobType != JOB_REQUEST_CONTEXT_CHANGE) {
					jobQueue.push(fJob);
				} else {
					processJob(fJob);
					i--;
				}
				jobQueue.pop();
			}
			break;
		} else {
#endif
			processJob(nextJob);
#if PLATFORM == PLATFORM_ANDROID
		}
#endif
	}

	RenderFrame *nextFrame = NULL;
	if (frameQueue.size() > 0) {
		nextFrame = frameQueue.front();
		frameQueue.pop();
	}

	jobQueueMutex.unlock();

	if (nextFrame) {
		
		beginFrame();
		
		while (nextFrame->drawBuffers.size() > 0) {
			#if PLATFORM == PLATFORM_ANDROID
				if(!core->isWindowInitialized()){
					break;
				}
			#endif
			GPUDrawBuffer *drawBuffer = nextFrame->drawBuffers.front();
			nextFrame->drawBuffers.pop();
			processDrawBuffer(drawBuffer);
			delete drawBuffer;
		}
		
		endFrame();
		

		if (nextFrame->customFrameFinalizer) {
			nextFrame->customFrameFinalizer(nextFrame->customFrameFinalizerData);
		}


		delete nextFrame;
	}
	
	for(int i=0; i < framesToDelete.size(); i++) {
		delete framesToDelete[i];
	}
	framesToDelete.clear();
}

void RenderThread::runThread() {

	initGlobals();
	
	while(threadRunning) {
		updateRenderThread();
	}
}

ShaderBinding *RenderThread::getShaderBinding() {
	return rendererShaderBinding;
}

void RenderThread::processDrawBufferLights(GPUDrawBuffer *buffer) {
	int lightShadowIndex = 0;
	
	for(int i=0; i <RENDERER_MAX_LIGHTS; i++) {
		if(i < buffer->lights.size()) {
			lights[i].diffuse->setColor(buffer->lights[i].diffuseColor * buffer->lights[i].intensity);
			lights[i].specular->setColor(buffer->lights[i].specularColor  * buffer->lights[i].intensity);
			
			lights[i].position->setVector3(buffer->lights[i].position);
			lights[i].direction->setVector3(buffer->lights[i].direction);
			lights[i].spotExponent->setNumber(buffer->lights[i].spotlightExponent);
			if(buffer->lights[i].type == 0) {
				lights[i].spotCosCutoff->setNumber(180.0);
			} else {
				lights[i].spotCosCutoff->setNumber(cos((buffer->lights[i].spotlightCutoff) * TORADIANS));
			}
			
			lights[i].constantAttenuation->setNumber(buffer->lights[i].constantAttenuation);
			lights[i].linearAttenuation->setNumber(buffer->lights[i].linearAttenuation);
			lights[i].quadraticAttenuation->setNumber(buffer->lights[i].quadraticAttenuation);
			
			
			if(buffer->lights[i].shadowsEnabled) {
				lightShadows[lightShadowIndex].shadowMatrix->setMatrix4(buffer->lights[i].lightViewMatrix);
				lightShadows[lightShadowIndex].shadowBuffer->setTexture(buffer->lights[i].shadowMapTexture);
				
				lights[i].shadowEnabled->setNumber(1.0);
				
				if(lightShadowIndex < RENDERER_MAX_LIGHT_SHADOWS-1) {
					lightShadowIndex++;
				}
			} else {
				lights[i].shadowEnabled->setNumber(0.0);
                lightShadows[lightShadowIndex].shadowBuffer->setTexture(NULL);
			}
		} else {
			lights[i].diffuse->setColor(Color(0.0, 0.0, 0.0, 0.0));
			lights[i].specular->setColor(Color(0.0, 0.0, 0.0, 0.0));
			lights[i].spotCosCutoff->setNumber(180.0);
			lights[i].shadowEnabled->setNumber(0.0);
			lights[i].constantAttenuation->setNumber(1.0);
			lights[i].linearAttenuation->setNumber(1.0);
			lights[i].quadraticAttenuation->setNumber(1.0);
			
		}
	}
}

void RenderThread::clearFrameQueue() {
	jobQueueMutex.lock();
	while(frameQueue.size()) {
		frameQueue.pop();
	}
	jobQueueMutex.unlock();
}

void RenderThread::processDrawBuffer(GPUDrawBuffer *buffer) {
	
	++currentDebugFrameInfo.buffersProcessed;
	
	if(buffer->targetFramebuffer) {
		graphicsInterface->bindRenderBuffer(&*buffer->targetFramebuffer);
	}
	
	graphicsInterface->setViewport(buffer->viewport.x, buffer->viewport.y, buffer->viewport.w, buffer->viewport.h);
	graphicsInterface->clearBuffers(buffer->clearColor, buffer->clearColorBuffer, buffer->clearDepthBuffer, true);
	
	projectionMatrixParam->setMatrix4(buffer->projectionMatrix);
	viewMatrixParam->setMatrix4(buffer->viewMatrix);

	processDrawBufferLights(buffer);
	
	for(int i=0; i < buffer->drawCalls.size(); i++) {
		
		if(!buffer->drawCalls[i].submesh) {
			continue;
		}
		
		if(buffer->drawCalls[i].options.enableScissor) {
			graphicsInterface->enableScissor(true);
			Polycode::Rectangle scissorBox = buffer->drawCalls[i].options.scissorBox;
						
			scissorBox.x *= buffer->backingResolutionScale.x;
			scissorBox.w *= buffer->backingResolutionScale.x;
			scissorBox.h *= buffer->backingResolutionScale.y;
			scissorBox.y = ((buffer->viewport.h-(scissorBox.y*buffer->backingResolutionScale.y)))-scissorBox.h;
			
			graphicsInterface->setScissorBox(scissorBox);
		} else {
			graphicsInterface->enableScissor(false);
		}
		
		graphicsInterface->enableDepthTest(buffer->drawCalls[i].options.depthTest);
		graphicsInterface->enableDepthWrite(buffer->drawCalls[i].options.depthWrite);
		graphicsInterface->enableBackfaceCulling(buffer->drawCalls[i].options.backfaceCull);
		graphicsInterface->setLineSize(buffer->drawCalls[i].options.linePointSize);
		
		modelMatrixParam->setMatrix4(buffer->drawCalls[i].modelMatrix);
		
		Material *material = &*buffer->drawCalls[i].material;
		if(buffer->globalMaterial && !buffer->drawCalls[i].options.forceMaterial) {
			material = &*buffer->globalMaterial;
		}
		
		if(material) {
			
			if(buffer->drawCalls[i].options.blendingMode == Renderer::BLEND_MODE_MATERIAL || buffer->globalMaterial) {
				graphicsInterface->setBlendingMode(material->blendingMode);
			} else {
				graphicsInterface->setBlendingMode(buffer->drawCalls[i].options.blendingMode);
			}
			
			
			for(int s=0; s < buffer->drawCalls[i].shaderPasses.size(); s++) {
		
				++currentDebugFrameInfo.drawCallsProcessed;
				graphicsInterface->beginDrawCall();
				
				ShaderPass shaderPass;

				shaderPass = buffer->drawCalls[i].shaderPasses[s];
				
				std::shared_ptr<ShaderBinding> localShaderBinding = buffer->drawCalls[i].shaderPasses[s].shaderBinding;
				std::shared_ptr<ShaderBinding> materialShaderBinding = shaderPass.materialShaderBinding;
				
				
				if(buffer->globalMaterial && !buffer->drawCalls[i].options.forceMaterial) {
					if(s < buffer->globalMaterial->getNumShaderPasses()) {
						shaderPass = buffer->globalMaterial->getShaderPass(s);
						localShaderBinding = shaderPass.shaderBinding;
					}
				}
				
				if(!shaderPass.shader || !localShaderBinding) {
					continue;
				}
				
				
				if(shaderPass.shader) {
					if(!shaderPass.shader->platformData.data) {
						graphicsInterface->createShader(&*shaderPass.shader);
						// set renderer global params
						for(int p=0; p < rendererShaderBinding->getNumLocalParams(); p++) {
							LocalShaderParam *localParam = &*rendererShaderBinding->getLocalParam(p);
							if(localParam) {
								ProgramParam *paramPtr = shaderPass.shader->getParamPointer(localParam->name);
								if(paramPtr) {
									paramPtr->globalParam = localParam;
								}
							}
						}
						shaderPass.shader->reloadResource(core);
					}
				}
				
				graphicsInterface->useShader(&*shaderPass.shader);
				graphicsInterface->setWireframeMode(shaderPass.wireframe);

				// set global params
				for(int p=0; p < shaderPass.shader->expectedParams.size(); p++) {
					if(shaderPass.shader->expectedParams[p].globalParam) {
						graphicsInterface->setParamInShader(&*shaderPass.shader, &shaderPass.shader->expectedParams[p], shaderPass.shader->expectedParams[p].globalParam);
					}
				}
				
				
				if(materialShaderBinding && materialShaderBinding != localShaderBinding) {
					materialShaderBinding->accessMutex.lock();
				}
				if(materialShaderBinding) {
					for(int p=0; p < materialShaderBinding->getNumLocalParams(); p++) {						   
						std::shared_ptr<LocalShaderParam> localParam = materialShaderBinding->getLocalParam(p);
						if(localParam) {
							if(!localParam->param) {
								localParam->param = shaderPass.shader->getParamPointer(localParam->name);
							}
							if(localParam->param) {
								graphicsInterface->setParamInShader(&*shaderPass.shader, localParam->param, &*localParam);
								Color c = localParam->getColor();
								
							}
						}
					}
				}
				if(materialShaderBinding  && materialShaderBinding != localShaderBinding) {
					materialShaderBinding->accessMutex.unlock();
				}
				
				localShaderBinding->accessMutex.lock();
				for(int p=0; p < localShaderBinding->getNumLocalParams(); p++) {
					std::shared_ptr<LocalShaderParam> localParam = localShaderBinding->getLocalParam(p);
					if(localParam) {
						if(!localParam->param) {
							localParam->param = shaderPass.shader->getParamPointer(localParam->name);
						}
						if(localParam->param) {
							graphicsInterface->setParamInShader(&*shaderPass.shader, localParam->param, &*localParam);
						}
					}
				}
				localShaderBinding->accessMutex.unlock();
				
				if(buffer->drawCalls[i].submesh->dataChanged) {
					graphicsInterface->createSubmeshBuffers(&*buffer->drawCalls[i].submesh);
					buffer->drawCalls[i].submesh->dataChanged = false;
				}
				graphicsInterface->drawSubmeshBuffers(&*buffer->drawCalls[i].submesh, &*shaderPass.shader);
				graphicsInterface->endDrawCall();
			}
		}
	}
	
	if(buffer->targetFramebuffer) {
		graphicsInterface->bindRenderBuffer(NULL);
	}
	
}

RenderThread::~RenderThread() {
	clearFrameQueue();
	renderMutex.unlock();
	jobQueueMutex.unlock();
}

void RenderThread::lockRenderMutex() {
    renderMutex.lock();
}

void RenderThread::unlockRenderMutex() {
    renderMutex.unlock();
}

void RenderThread::processJob(const RendererThreadJob &job) {
	lockRenderMutex();

	switch(job.jobType) {
		case JOB_REQUEST_CONTEXT_CHANGE:
		{
			VideoModeChangeInfo *modeInfo = (VideoModeChangeInfo*) job.data;
			core->handleVideoModeChange(modeInfo);
			delete modeInfo;
		}
		break;
		case JOB_DESTROY_TEXTURE:
		{
			graphicsInterface->destroyTextureData(job.data);
		}
		break;
		case JOB_DESTROY_RENDER_BUFFER:
		{
			graphicsInterface->destroyRenderBufferData(job.data);
		}
		break;
		case JOB_DESTROY_SHADER:
		{
			graphicsInterface->destroyShaderData(job.data);
		}
		break;
		case JOB_DESTROY_PROGRAM:
		{
			graphicsInterface->destroyProgramData(job.data);
		}
		break;
		case JOB_DESTROY_SUBMESH_BUFFER:
		{
			graphicsInterface->destroySubmeshBufferData(job.data);
		}
		break;
			
	}
	unlockRenderMutex();
}

void RenderThread::beginFrame() {
	currentDebugFrameInfo.buffersProcessed = 0;
	currentDebugFrameInfo.drawCallsProcessed = 0;
	currentDebugFrameInfo.timeTaken = 0;
	frameStart = core->getTicks();
	core->prepareRenderContext();
}

void RenderThread::endFrame() {
	core->flushRenderContext();
	currentDebugFrameInfo.timeTaken = core->getTicks() - frameStart;
	lastFrameDebugInfo = currentDebugFrameInfo;
}


RenderThreadDebugInfo RenderThread::getFrameInfo() {
	RenderThreadDebugInfo info;
    jobQueueMutex.lock();
	info = lastFrameDebugInfo;
    jobQueueMutex.unlock();
	return info;
}

void RenderThread::enqueueFrame(RenderFrame *frame) {
    jobQueueMutex.lock();
	frameQueue.push(frame);
	while(frameQueue.size() > MAX_QUEUED_FRAMES) {
		RenderFrame *nextFrame = frameQueue.front();
		framesToDelete.push_back(nextFrame);
		frameQueue.pop();
	}
    jobQueueMutex.unlock();
}

void RenderThread::enqueueJob(int jobType, void *data, void *data2) {
    jobQueueMutex.lock();
	RendererThreadJob job;
	job.jobType = jobType;
	job.data = data;
	job.data2 = data2;
	jobQueue.push(job);
    jobQueueMutex.unlock();
}

void RenderThread::setGraphicsInterface(Core *core, GraphicsInterface *graphicsInterface) {
	this->graphicsInterface = graphicsInterface;
	this->core = core;
}

Renderer::Renderer(Core *core, RenderThread *customThread) :
	backingResolutionScaleX(1.0),
	backingResolutionScaleY(1.0),
	cpuBufferIndex(0),
	gpuBufferIndex(1)
{
	   
	if(!customThread) {
		renderThread = new RenderThread();
		core->createThread(renderThread);
	} else {
		renderThread = customThread;
	}
}

Renderer::~Renderer() {
	renderThread->threadRunning = false;
	while(!renderThread->scheduledForRemoval) {}
	delete renderThread;
}

void Renderer::setGraphicsInterface(Core *core, GraphicsInterface *graphicsInterface) {
	renderThread->setGraphicsInterface(core, graphicsInterface);
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

void Renderer::submitRenderFrame(RenderFrame *newFrame) {
	renderThread->enqueueFrame(newFrame);
}

void Renderer::destroyRenderBufferPlatformData(void *platformData) {
	renderThread->enqueueJob(RenderThread::JOB_DESTROY_RENDER_BUFFER, platformData);
}

void Renderer::destroyTexturePlatformData(void *platformData) {
	renderThread->enqueueJob(RenderThread::JOB_DESTROY_TEXTURE, platformData);
}

void Renderer::destroyProgramPlatformData(void *platformData) {
	renderThread->enqueueJob(RenderThread::JOB_DESTROY_PROGRAM, platformData);
}


void Renderer::destroyShaderPlatformData(void *platformData) {
	renderThread->enqueueJob(RenderThread::JOB_DESTROY_SHADER, platformData);
}

void Renderer::destroySubmeshPlatformData(void *platformData) {
	 renderThread->enqueueJob(RenderThread::JOB_DESTROY_SUBMESH_BUFFER, platformData);
}

Vector3 Renderer::project(const Vector3 &position, const Matrix4 &modelMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport) {
	
	Vector4 in(position);
	Vector4 out = modelMatrix * in;
	in = projectionMatrix * out;
	
	if (in.w == 0.0) return Vector3();
	
	in.x /= in.w;
	in.y /= in.w;
	in.z /= in.w;
	
	in.x = in.x * 0.5 + 0.5;
	in.y = in.y * 0.5 + 0.5;
	in.z = in.z * 0.5 + 0.5;
	
	in.x = in.x * (viewport.w) + viewport.x;
	in.y = in.y * (viewport.h) + viewport.y;
	
	return Vector3(in.x, in.y, in.z);
}

Vector3 Renderer::unProject(const Vector3 &position, const Matrix4 &modelMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport) {

	Matrix4 finalMatrix = modelMatrix * projectionMatrix;
	finalMatrix = finalMatrix.Inverse();
	
	Vector4 in(position);
	
	in.x = (in.x - viewport.x) / (viewport.w);
	in.y = (in.y - viewport.y) / (viewport.h);
	
	in.y = 1.0 - in.y;
	
	in.x = in.x * 2.0 - 1.0;
	in.y = in.y * 2.0 - 1.0;
	in.z = in.z * 2.0 - 1.0;
	
	Vector4 out = finalMatrix * in;
	
	if(out.w == 0.0) return Vector3();
	
	out.x /= out.w;
	out.y /= out.w;
	out.z /= out.w;
	
	return Vector3(out.x, out.y, out.z);
}
