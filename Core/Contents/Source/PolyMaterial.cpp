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

#include "PolyMaterial.h"
#include "PolyLogger.h"
#include "PolyShader.h"
#include "PolyRenderer.h"
#include "PolyCoreServices.h"
#include "PolyCore.h"
#include "PolyTexture.h"

using namespace Polycode;

Material::Material(const String& name) : Resource(Resource::RESOURCE_MATERIAL) {
	this->name = name;
	fp16RenderTargets = false;
	shaderModule = NULL;
	blendingMode = Renderer::BLEND_MODE_NORMAL;
	screenMaterial = false;
}

Material::~Material() {

	Logger::log("deleting material (%s)\n", name.c_str());

	clearShaders();
}

void Material::setName(const String &name) {
	this->name = name;
}

void Material::clearShaders() {
	// do not delete shaders here, they're shared
/*	
	for(int i=0; i < materialShaders.size(); i++) {
		delete materialShaders[i];
	}
	*/

	for(int i=0; i < materialShaders.size(); i++) {
		materialShaders[i]->removeAllHandlersForListener(this);
	}
	materialShaders.clear();

	for(int i=0; i < shaderBindings.size(); i++) {
		delete shaderBindings[i];
	}
	shaderBindings.clear();

	for(int i=0; i < renderTargets.size(); i++) {
		delete renderTargets[i];
	}
	renderTargets.clear();
}

void Material::recreateRenderTargets() {
	for(int i=0; i < renderTargets.size(); i++) {
		recreateRenderTarget(renderTargets[i]);
	}
}

void Material::recreateRenderTarget(ShaderRenderTarget *renderTarget) {
	int textureWidth;
	int textureHeight;
	Texture *newTexture;

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
			textureWidth = (int) (CoreServices::getInstance()->getCore()->getXRes() * safeWidth);
			textureHeight = (int) (CoreServices::getInstance()->getCore()->getYRes() * safeHeight);
		}
	} else {
		textureWidth = (int)renderTarget->width;
		textureHeight = (int)renderTarget->height;
	}

	CoreServices::getInstance()->getRenderer()->createRenderTextures(&newTexture, NULL, textureWidth, textureHeight, fp16RenderTargets);
	newTexture->setResourceName(renderTarget->id);

	Texture *oldTexture = renderTarget->texture;
	renderTarget->texture = newTexture;

	if(oldTexture) {
		for(int i=0; i < shaderBindings.size(); i++) {
	
			for(int j=0; j < shaderBindings[i]->getNumRenderTargetBindings(); j++) {
				if(shaderBindings[i]->getRenderTargetBinding(j)->texture == oldTexture) {
					shaderBindings[i]->getRenderTargetBinding(j)->texture = newTexture;
					shaderBindings[i]->getRenderTargetBinding(j)->width = newTexture->getWidth();
					shaderBindings[i]->getRenderTargetBinding(j)->height = newTexture->getHeight();
					shaderBindings[i]->clearTexture(shaderBindings[i]->getRenderTargetBinding(j)->name);
					shaderBindings[i]->addTexture(shaderBindings[i]->getRenderTargetBinding(j)->name, newTexture);
				}
			}
		}

		CoreServices::getInstance()->getRenderer()->destroyTexture(oldTexture);
	}
}

void Material::handleEvent(Event *event) {
	std::vector<Shader*> _materialShaders = materialShaders;
	clearShaders();
	for(int i=0; i < _materialShaders.size(); i++)	{
		ShaderBinding *newShaderBinding = _materialShaders[i]->createBinding();
		addShader(_materialShaders[i], newShaderBinding);
	}
	dispatchEvent(new Event(), Event::RESOURCE_RELOAD_EVENT);
}

void Material::removeShader(int shaderIndex) {
	if(shaderIndex >= 0 && shaderIndex < materialShaders.size()) {
		materialShaders.erase(materialShaders.begin() + shaderIndex);
		shaderBindings.erase(shaderBindings.begin() + shaderIndex);
	}
}

void Material::addShaderAtIndex(Shader *shader,ShaderBinding *shaderBinding, int shaderIndex) {
	materialShaders.insert(materialShaders.begin()+shaderIndex, shader);
	shaderBindings.insert(shaderBindings.begin()+shaderIndex, shaderBinding);

	shader->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
	CoreServices::getInstance()->getRenderer()->setRendererShaderParams(shader, shaderBinding);

	for(int i=0; i < shader->expectedParams.size(); i++) {
		if(!shaderBinding->getLocalParamByName(shader->expectedParams[i].name)) {
			shaderBinding->addParam(shader->expectedParams[i].type, shader->expectedParams[i].name);
		}
	}
}

void Material::addShader(Shader *shader,ShaderBinding *shaderBinding) {
	materialShaders.push_back(shader);
	shaderBindings.push_back(shaderBinding);

	shader->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);	
	CoreServices::getInstance()->getRenderer()->setRendererShaderParams(shader, shaderBinding);

	for(int i=0; i < shader->expectedParams.size(); i++) {
		if(!shaderBinding->getLocalParamByName(shader->expectedParams[i].name)) {
			shaderBinding->addParam(shader->expectedParams[i].type, shader->expectedParams[i].name);
		}
	}
}


unsigned int Material::getNumShaders() const {
	return materialShaders.size();
}

const String& Material::getName() const {
	return name;
}

Shader *Material::getShader(unsigned int index) const {
	if(index < materialShaders.size()) { 
		return materialShaders[index];
	} else {
		return NULL;
	}
}

ShaderBinding *Material::getShaderBinding(unsigned int index) const {
	if(index < shaderBindings.size()) {
		return shaderBindings[index]; 
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
