/*
 *  PolyMaterial.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/19/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */


#include "PolyMaterial.h"

using namespace Polycode;

Material::Material(String name) : Resource(Resource::RESOURCE_MATERIAL) {
	this->name = name;
}

Material::~Material() {
	
	Logger::log("deleting material (%s)\n", name.c_str());
	vector<Shader*> materialShaders;
	vector<ShaderBinding*> shaderBindings;
	vector<ShaderRenderTarget*> renderTargets;	
	
	for(int i=0; i < materialShaders.size(); i++)	{
		delete materialShaders[i];
	}
	materialShaders.clear();

	for(int i=0; i < shaderBindings.size(); i++)	{
		delete shaderBindings[i];
	}
	shaderBindings.clear();
	
	for(int i=0; i < renderTargets.size(); i++)	{
		delete renderTargets[i];
	}
	renderTargets.clear();	
}

void Material::addShader(Shader *shader,ShaderBinding *shaderBinding) {
	materialShaders.push_back(shader);
	shaderBindings.push_back(shaderBinding);
}


unsigned int Material::getNumShaders() {
	return materialShaders.size();
}

String Material::getName() {
	return name;
}

Shader *Material::getShader(unsigned int index) {
	return materialShaders[index];
}

ShaderBinding *Material::getShaderBinding(unsigned int index) {
	return shaderBindings[index];
}

void Material::loadMaterial(String fileName) {

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