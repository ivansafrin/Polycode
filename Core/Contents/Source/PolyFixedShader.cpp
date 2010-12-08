/*
 *  PolyFixedShader.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyFixedShader.h"

using namespace Polycode;

FixedShaderBinding::FixedShaderBinding(FixedShader *shader) : ShaderBinding(shader) {
	fixedShader = shader;
}

FixedShaderBinding::~FixedShaderBinding() {

}


void FixedShaderBinding::addCubemap(string name, Cubemap *cubemap) {
	cubemaps.push_back(cubemap);
}

void FixedShaderBinding::addTexture(string name, Texture *texture) {
	textures.push_back(texture);
}

Texture *FixedShaderBinding::getDiffuseTexture() {
	return textures[0];
}

void FixedShaderBinding::addParam(string type, string name, string value) {

}


FixedShader::FixedShader() : Shader(Shader::FIXED_SHADER) {
}

FixedShader::~FixedShader() {
}

ShaderBinding *FixedShader::createBinding() {
	return new FixedShaderBinding(this);
}