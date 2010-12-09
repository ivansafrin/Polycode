/*
 *  PolyShader.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
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

void ShaderBinding::addRenderTargetBinding(RenderTargetBinding *binding) {
	renderTargetBindings.push_back(binding);
	if(binding->mode == RenderTargetBinding::MODE_IN) {
		inTargetBindings.push_back(binding);
	} else {
		outTargetBindings.push_back(binding);	
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