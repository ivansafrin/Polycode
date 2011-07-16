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

using namespace Polycode;

ShaderBinding::ShaderBinding(Shader *shader) {
	this->shader = shader;
}

ShaderBinding::~ShaderBinding() {

}

unsigned int ShaderBinding::getNumLocalParams() {
	return localParams.size();
}

LocalShaderParam *ShaderBinding::getLocalParam(unsigned int index) {
	return localParams[index];
}

LocalShaderParam *ShaderBinding::getLocalParamByName(String name) {
	for(int i=0; i < localParams.size(); i++) {
		if(localParams[i]->name == name) {
			return localParams[i];
		}
	}
	return NULL;
}

void ShaderBinding::addLocalParam(String name, void *ptr) {
	LocalShaderParam *newParam = new LocalShaderParam();
	newParam->name = name;
	newParam->data = ptr;
	localParams.push_back(newParam);
}

void ShaderBinding::addRenderTargetBinding(RenderTargetBinding *binding) {
	renderTargetBindings.push_back(binding);
	if(binding->mode == RenderTargetBinding::MODE_IN) {
		inTargetBindings.push_back(binding);
		printf("Adding in target binding [%s] [%s]\n", binding->id.c_str(), binding->name.c_str());
	} else {
		outTargetBindings.push_back(binding);	
		printf("Adding out target binding [%s]\n", binding->id.c_str());		
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


Shader::Shader(int type) : Resource(Resource::RESOURCE_SHADER) {
	numSpotLights = 0;
	numAreaLights = 0;
	this->type = type;
}

Shader::~Shader() {

}

int Shader::getType() {
	return type;
}

void Shader::setName(String name) {
	this->name = name;
}

String Shader::getName() {
	return name;
}