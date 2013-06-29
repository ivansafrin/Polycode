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

#include "PolyShader.h"
#include "PolyMatrix4.h"

using namespace Polycode;

ShaderRenderTarget::ShaderRenderTarget() : PolyBase() {
	texture = NULL;
}

void *ProgramParam::createParamData(int type) {
	switch (type) {
		case PARAM_NUMBER:
		{
			Number *val = new Number();
			return (void*)val;
		}
		break;
		case PARAM_VECTOR2:
		{
			Vector2 *val = new Vector2();
			return (void*)val;
		}
		break;
		case PARAM_VECTOR3:
		{
			Vector3 *val = new Vector3();
			return (void*)val;
		}
		break;
		case PARAM_COLOR:
		{
			Color *val = new Color();
			return (void*)val;
		}
		break;
		case PARAM_MATRIX:
		{
			Matrix4 *val = new Matrix4();
			return (void*)val;
		}
		break;
		default:
			return NULL;
		break;
	}
}

ShaderProgram::ShaderProgram(int type) : Resource(Resource::RESOURCE_PROGRAM) {
	this->type = type;
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::reloadResource() {
	reloadProgram();
	Resource::reloadResource();
}


ShaderBinding::ShaderBinding(Shader *shader) {
	this->shader = shader;
}

ShaderBinding::~ShaderBinding() {
	for(int i=0; i < localParams.size(); i++) {
		delete localParams[i];
	}
	for(int i=0; i < renderTargetBindings.size(); i++) {
		delete renderTargetBindings[i];
	}
	for(int i=0; i < inTargetBindings.size(); i++) {
		delete inTargetBindings[i];
	}
	for(int i=0; i < outTargetBindings.size(); i++) {
		delete outTargetBindings[i];
	}
}

unsigned int ShaderBinding::getNumLocalParams() {
	return localParams.size();
}

LocalShaderParam *ShaderBinding::getLocalParam(unsigned int index) {
	return localParams[index];
}

LocalShaderParam *ShaderBinding::getLocalParamByName(const String& name) {
	for(int i=0; i < localParams.size(); i++) {
		if(localParams[i]->name == name) {
			return localParams[i];
		}
	}
	return NULL;
}

LocalShaderParam *ShaderBinding::addLocalParam(const String& name, void *ptr) {
	LocalShaderParam *newParam = new LocalShaderParam();
	newParam->name = name;
	newParam->data = ptr;
	localParams.push_back(newParam);
	return newParam;
}

LocalShaderParam * ShaderBinding::addParam(int type, const String& name) {
	void *defaultData = ProgramParam::createParamData(type);
	LocalShaderParam *newParam = new LocalShaderParam();
	newParam->data = defaultData;
	newParam->name = name;
	localParams.push_back(newParam);
	return newParam;
}

void ShaderBinding::addRenderTargetBinding(RenderTargetBinding *binding) {
	renderTargetBindings.push_back(binding);
	switch (binding->mode) {
		case RenderTargetBinding::MODE_IN:
			inTargetBindings.push_back(binding);
		break;
		case RenderTargetBinding::MODE_OUT:
			outTargetBindings.push_back(binding);
		break;
		case RenderTargetBinding::MODE_COLOR:
			colorTargetBindings.push_back(binding);
		break;
		case RenderTargetBinding::MODE_DEPTH:
			depthTargetBindings.push_back(binding);
		break;
	}
}

void ShaderBinding::removeRenderTargetBinding(RenderTargetBinding *binding) {
	for(int i=0; i < renderTargetBindings.size(); i++) {
		if(renderTargetBindings[i] == binding) {
			renderTargetBindings.erase(renderTargetBindings.begin() + i);
		}
	}

	for(int i=0; i < inTargetBindings.size(); i++) {
		if(inTargetBindings[i] == binding) {
			inTargetBindings.erase(inTargetBindings.begin() + i);
			return;
		}
	}
	for(int i=0; i < outTargetBindings.size(); i++) {
		if(outTargetBindings[i] == binding) {
			outTargetBindings.erase(outTargetBindings.begin() + i);
			return;
		}
	}

	for(int i=0; i < colorTargetBindings.size(); i++) {
		if(colorTargetBindings[i] == binding) {
			colorTargetBindings.erase(colorTargetBindings.begin() + i);
			return;
		}
	}

	for(int i=0; i < depthTargetBindings.size(); i++) {
		if(depthTargetBindings[i] == binding) {
			depthTargetBindings.erase(depthTargetBindings.begin() + i);
			return;
		}
	}

}

unsigned int ShaderBinding::getNumRenderTargetBindings() {
	return renderTargetBindings.size();
}

RenderTargetBinding *ShaderBinding::getRenderTargetBinding(unsigned int index) {
	return renderTargetBindings[index];
}

unsigned int ShaderBinding::getNumInTargetBindings() {
	return inTargetBindings.size();
}

RenderTargetBinding *ShaderBinding::getInTargetBinding(unsigned int index) {
	return inTargetBindings[index];
}

unsigned int ShaderBinding::getNumOutTargetBindings() {
	return outTargetBindings.size();
}

RenderTargetBinding *ShaderBinding::getOutTargetBinding(unsigned int index) {
	return outTargetBindings[index];
}

unsigned int ShaderBinding::getNumColorTargetBindings() {
	return colorTargetBindings.size();
}

RenderTargetBinding *ShaderBinding::getColorTargetBinding(unsigned int index) {
	return colorTargetBindings[index];
}

unsigned int ShaderBinding::getNumDepthTargetBindings() {
	return depthTargetBindings.size();
}

RenderTargetBinding *ShaderBinding::getDepthTargetBinding(unsigned int index) {
	return depthTargetBindings[index];
}


Shader::Shader(int type) : Resource(Resource::RESOURCE_SHADER) {
	numSpotLights = 0;
	numAreaLights = 0;
	this->type = type;
	vp = NULL;
	fp = NULL;
}

int Shader::getExpectedParamType(String name) {
	for(int i=0; i < expectedParams.size(); i++) {
		if(expectedParams[i].name == name) {
			return expectedParams[i].type;
		}
	}
	return ProgramParam::PARAM_UNKNOWN;
}

Shader::~Shader() {

}

int Shader::getType() const {
	return type;
}

void Shader::setName(const String& name) {
	this->name = name;
}

const String& Shader::getName() const {
	return name;
}
