/*
 Copyright (C) 2011 by Ivan Safrin
 
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

#include "polycode/core/PolyMaterial.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyShader.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyMesh.h"

using namespace Polycode;


ShaderPass::ShaderPass() :
	shader(NULL),
	wireframe(false),
	shaderBinding(NULL),
	materialShaderBinding(NULL),
	blendingMode(Renderer::BLEND_MODE_NONE) {

}

ShaderPass::ShaderPass(Shader *shader) :
	shader(shader),
	wireframe(false),
	shaderBinding(NULL),
	materialShaderBinding(NULL),
	blendingMode(Renderer::BLEND_MODE_NONE) {

}

ShaderPass::ShaderPass(const ShaderPass &other) {
	shader = other.shader;
	wireframe = other.wireframe;
	blendingMode = other.blendingMode;
	shaderBinding = other.shaderBinding;
	materialShaderBinding = other.materialShaderBinding;
}

ShaderPass::~ShaderPass() {
}

std::shared_ptr<ShaderBinding> ShaderPass::getShaderBinding() {
	return shaderBinding;
}


Material::Material(const String& name) : Resource(Resource::RESOURCE_MATERIAL) {
	this->name = name;
	fp16RenderTargets = false;
	blendingMode = Renderer::BLEND_MODE_NORMAL;
	screenMaterial = false;
}

Material::~Material() {
	
	Logger::log("deleting material (%s)\n", name.c_str());
	
	clearShaders();
}

void Material::setName(const String &name) {
	this->name = name;
	setResourceName(name);
	dispatchEvent(new Event(), Event::RESOURCE_CHANGE_EVENT);
}

void Material::clearShaders() {
	for(int i=0; i < shaderPasses.size(); i++)	{
		shaderPasses[i].shader->removeAllHandlersForListener(this);
	}	
	shaderPasses.clear();
	
	for(int i=0; i < renderTargets.size(); i++) {
		delete renderTargets[i];
	}
	renderTargets.clear();		
}

void Material::recreateRenderTargets(const Vector2 &screenSize) {
	for(int i=0; i < renderTargets.size(); i++) {
		recreateRenderTarget(renderTargets[i], screenSize);
	}
}

void Material::recreateRenderTarget(ShaderRenderTarget *renderTarget, const Vector2 &screenSize) {
	int textureWidth;
	int textureHeight;
	std::shared_ptr<RenderBuffer> newBuffer;
	
	if(renderTarget->sizeMode == ShaderRenderTarget::SIZE_MODE_NORMALIZED) {
		Number safeWidth = renderTarget->width;
		Number safeHeight = renderTarget->height;		
		if(safeWidth > 1.0)
			safeWidth = 1.0;
		if(safeHeight > 1.0)
			safeHeight = 1.0;
			
		if(safeWidth < 0.0)
			safeWidth = 0.0;
		if(safeHeight < 0.0)
			safeHeight = 0.0;
		
		if(renderTarget->normalizedWidth > 0 && renderTarget->normalizedHeight > 0) {
			textureWidth = (int) (renderTarget->normalizedWidth * safeWidth);
			textureHeight = (int) (renderTarget->normalizedHeight * safeHeight);		
		} else {
			textureWidth = (int) (safeWidth * screenSize.x);
			textureHeight = (int) (safeHeight * screenSize.y);
		}
	} else {
		textureWidth = (int)renderTarget->width;
		textureHeight = (int)renderTarget->height;		
	}
	
	newBuffer = std::make_shared<RenderBuffer>(textureWidth, textureHeight, false, fp16RenderTargets);
//	newBuffer->setResourceName(renderTarget->id);
	
	std::shared_ptr<RenderBuffer> oldBuffer = renderTarget->buffer;
	renderTarget->buffer = newBuffer;

	/*
	if(oldBuffer) {
		for(int i=0; i < shaderBindings.size(); i++) {
			for(int j=0; j < shaderBindings[i]->getNumRenderTargetBindings(); j++) {
				if(shaderBindings[i]->getRenderTargetBinding(j)->texture == oldTexture) {
					shaderBindings[i]->getRenderTargetBinding(j)->texture = newTexture;
					shaderBindings[i]->clearTexture(shaderBindings[i]->getRenderTargetBinding(j)->name);
					shaderBindings[i]->addTexture(shaderBindings[i]->getRenderTargetBinding(j)->name, newTexture);					
				}
			}			
		}
		
		CoreServices::getInstance()->getRenderer()->destroyTexture(oldTexture);
	}
*/
}

void Material::removeShaderPass(int shaderIndex) {
	if(shaderIndex >= 0 && shaderIndex < shaderPasses.size()) {
		shaderPasses.erase(shaderPasses.begin() + shaderIndex);
	}
}

void Material::addShaderPass(const ShaderPass &pass) {
	shaderPasses.push_back(pass);
	pass.shader->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
}

void Material::addShaderPassAtIndex(const ShaderPass &pass, unsigned int shaderIndex) {
	shaderPasses.insert(shaderPasses.begin()+shaderIndex, pass);
	pass.shader->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
}

unsigned int Material::getNumShaderPasses() const {
	return shaderPasses.size();
}

const String& Material::getName() const {
	return name;
}

ShaderPass Material::getShaderPass(unsigned int index) const {
	if(index < shaderPasses.size()) {
		return shaderPasses[index];
	} else {
		return ShaderPass();
	}
}

std::shared_ptr<Shader> Material::getShader(unsigned int index) const {
	if(index < shaderPasses.size()) {
		return shaderPasses[index].shader;
	} else {
		return NULL;
	}
}

std::shared_ptr<ShaderBinding> Material::getShaderBinding(unsigned int index) const {
	if(index < shaderPasses.size()) {
		return shaderPasses[index].shaderBinding;
	} else {
		return NULL;
	}
}

void Material::loadMaterial(const String& fileName) {

}

void Material::addShaderRenderTarget(ShaderRenderTarget *newTarget) {
	renderTargets.push_back(newTarget);
}

int Material::getNumShaderRenderTargets() {
	return renderTargets.size();
}

ShaderRenderTarget *Material::getShaderRenderTarget(unsigned int index) {
	return renderTargets[index];
}

void Material::removeShaderRenderTarget(int index) {
	if(index >= 0 && index < renderTargets.size()) {
		ShaderRenderTarget *renderTarget = renderTargets[index];
		renderTargets.erase(renderTargets.begin() + index);
		delete renderTarget;
	}
}
