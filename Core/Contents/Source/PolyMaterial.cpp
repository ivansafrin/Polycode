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

using namespace Polycode;

Material::Material(const String& name) : Resource(Resource::RESOURCE_MATERIAL) {
	this->name = name;
	specularValue = 75.0;
}

Material::~Material() {
	
	Logger::log("deleting material (%s)\n", name.c_str());
	
	// do not delete shaders here, they're shared
/*	
	for(int i=0; i < materialShaders.size(); i++)	{
		delete materialShaders[i];
	}
	*/
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


unsigned int Material::getNumShaders() const {
	return materialShaders.size();
}

const String& Material::getName() const {
	return name;
}

Shader *Material::getShader(unsigned int index) const {
	return materialShaders[index];
}

ShaderBinding *Material::getShaderBinding(unsigned int index) const {
	return shaderBindings[index];
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
