/*
 *  PolyCGShader.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyCGShader.h"

using namespace Polycode;

CGShaderBinding::CGShaderBinding(CGShader *shader) : ShaderBinding(shader) {
	cgShader = shader;
}

CGShaderBinding::~CGShaderBinding() {
	
}


void CGShaderBinding::addTexture(string name, Texture *texture) {
	CGTextureBinding binding;
	binding.name = name;
	binding.texture = texture;
	binding.vpParam = cgGetNamedParameter(cgShader->fp->program, name.c_str());
	textures.push_back(binding);
}

void CGShaderBinding::addCubemap(string name, Cubemap *cubemap) {
	CGCubemapBinding binding;
	binding.cubemap = cubemap;
	binding.name = name;
	binding.vpParam = cgGetNamedParameter(cgShader->fp->program, name.c_str());
	cubemaps.push_back(binding);
}

void CGShaderBinding::clearTexture(string name) {
	for(int i=0; i < textures.size(); i++) {
		if(textures[i].name == name) {
			textures.erase(textures.begin()+i);
			return;
		}
	}
}


void CGShaderBinding::addParam(string type, string name, string value) {
	int paramType;
	void *defaultData = CGProgramParam::createParamData(&paramType, type, value);
	LocalShaderParam *newParam = new LocalShaderParam;
	newParam->data = defaultData;
	newParam->name = name;
	localParams.push_back(newParam);
}

CGShader::CGShader(CGProgram *vp, CGProgram *fp) : Shader(Shader::CG_SHADER) {
	this->vp = vp;
	this->fp = fp;
}

CGShader::~CGShader() {

}

ShaderBinding *CGShader::createBinding() {
	return new CGShaderBinding(this);
}