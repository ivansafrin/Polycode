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
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyMesh.h"

using namespace Polycode;

ShaderPass::ShaderPass() :
    shader(NULL),
    wireframe(false),
    shaderBinding(NULL),
    blendingMode(Renderer::BLEND_MODE_NONE)
{
    
}

ShaderPass::ShaderPass(Shader *shader) :
    shader(shader),
    wireframe(false),
    shaderBinding(NULL),
    blendingMode(Renderer::BLEND_MODE_NONE)
{
    
}

void ShaderPass::setExpectedAttributes(Mesh *mesh) {
    if(!shader || !shaderBinding) {
        return;
    }
    
    shaderBinding->attributes.clear();
    
    for(int i=0; i < shader->expectedAttributes.size(); i++) {
        
        VertexDataArray *targetArray = NULL;
        
        if(shader->expectedAttributes[i].name == "position") {
            targetArray = &mesh->vertexPositionArray;
        } else if(shader->expectedAttributes[i].name == "texCoord"){
            targetArray = &mesh->vertexTexCoordArray;
        } else if(shader->expectedAttributes[i].name == "normal") {
            targetArray = &mesh->vertexNormalArray;
        } else if(shader->expectedAttributes[i].name == "color") {
            targetArray = &mesh->vertexColorArray;
        } else if(shader->expectedAttributes[i].name == "tangent") {
            targetArray = &mesh->vertexTangentArray;
        } else if(shader->expectedAttributes[i].name == "texCoord2") {
            targetArray = &mesh->vertexTexCoord2Array;
        } else if(shader->expectedAttributes[i].name == "boneWeights") {
            targetArray = &mesh->vertexBoneWeightArray;
        } else if(shader->expectedAttributes[i].name == "boneIndices") {
            targetArray = &mesh->vertexBoneIndexArray;
        }
        
        AttributeBinding *attributeBinding = shaderBinding->getAttributeBindingByName(shader->expectedAttributes[i].name);
        if(attributeBinding) {
            attributeBinding->vertexData = targetArray;
        } else {
            shaderBinding->addAttributeBinding(shader->expectedAttributes[i].name, targetArray);
        }
    }
}

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
    setResourceName(name);
	dispatchEvent(new Event(), Event::RESOURCE_CHANGE_EVENT);
}

void Material::clearShaders() {
    
    // SMARTPTR_TODO: add here
	// do not delete shaders here, they're shared
/*	
	for(int i=0; i < materialShaders.size(); i++)	{
		delete materialShaders[i];
	}
	*/
	
	for(int i=0; i < shaderPasses.size(); i++)	{
		shaderPasses[i].shader->removeAllHandlersForListener(this);
        delete shaderPasses[i].shaderBinding;
	}	
	shaderPasses.clear();
	
	for(int i=0; i < renderTargets.size(); i++)	{
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
    
    // RENDERER_TODO
    /*
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
					shaderBindings[i]->clearTexture(shaderBindings[i]->getRenderTargetBinding(j)->name);
					shaderBindings[i]->addTexture(shaderBindings[i]->getRenderTargetBinding(j)->name, newTexture);					
				}
			}			
		}
		
		CoreServices::getInstance()->getRenderer()->destroyTexture(oldTexture);
	}
    */
}

void Material::handleEvent(Event *event) {
    recreateExpectedShaderParams();
}

void Material::recreateExpectedShaderParams() {
    for (int i = 0; i < shaderPasses.size(); i++) {
        
        Shader* shader = shaderPasses[i].shader;
        ShaderBinding* shaderBinding = shaderPasses[i].shaderBinding;
        
        for(int i=0; i < shader->expectedParams.size(); i++) {
            if(!shaderBinding->getLocalParamByName(shader->expectedParams[i].name)) {
                if(!shader->expectedParams[i].globalParam) {
                    shaderBinding->addParam(shader->expectedParams[i].type, shader->expectedParams[i].name);
                }
            }
        }
    }
    dispatchEvent(new Event(), Event::RESOURCE_RELOAD_EVENT);
}

void Material::removeShaderPass(int shaderIndex) {
	if(shaderIndex >= 0 && shaderIndex < shaderPasses.size()) {
        delete shaderPasses[shaderIndex].shaderBinding;
		shaderPasses.erase(shaderPasses.begin() + shaderIndex);
	}
}

void Material::addShaderAtIndex(Shader *shader,ShaderBinding *shaderBinding, int shaderIndex) {
    ShaderPass newPass;
    newPass.shader = shader;
    newPass.shaderBinding = shaderBinding;
	shaderPasses.insert(shaderPasses.begin()+shaderIndex, newPass);
	shader->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
}

void Material::addShaderPass(const ShaderPass &pass) {
    shaderPasses.push_back(pass);
    pass.shader->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
    recreateExpectedShaderParams();
}

void Material::addShaderPassAtIndex(const ShaderPass &pass, unsigned int shaderIndex) {
    shaderPasses.insert(shaderPasses.begin()+shaderIndex, pass);
    pass.shader->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
}


void Material::addShader(Shader *shader,ShaderBinding *shaderBinding) {
    ShaderPass newPass;
    newPass.shader = shader;
    newPass.shaderBinding = shaderBinding;
    addShaderPass(newPass);
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

Shader *Material::getShader(unsigned int index) const {
    if(index < shaderPasses.size()) {
        return shaderPasses[index].shader;
    } else {
        return NULL;
    }
}

ShaderBinding *Material::getShaderBinding(unsigned int index) const {
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
