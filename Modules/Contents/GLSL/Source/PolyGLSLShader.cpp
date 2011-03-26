/*
 *  PolyGLSLShader.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyGLSLShader.h"

using namespace Polycode;

GLSLShaderBinding::GLSLShaderBinding(GLSLShader *shader) : ShaderBinding(shader) {
	glslShader = shader;
}

GLSLShaderBinding::~GLSLShaderBinding() {
	
}


void GLSLShaderBinding::addTexture(String name, Texture *texture) {
	GLSLTextureBinding binding;
	binding.name = name;
	binding.texture = texture;
//	binding.vpParam = GLSLGetNamedParameter(glslShader->fp->program, name.c_str());
	textures.push_back(binding);
}

void GLSLShaderBinding::addCubemap(String name, Cubemap *cubemap) {
	GLSLCubemapBinding binding;
	binding.cubemap = cubemap;
	binding.name = name;
//	binding.vpParam = GLSLGetNamedParameter(GLSLShader->fp->program, name.c_str());
	cubemaps.push_back(binding);
}

void GLSLShaderBinding::clearTexture(String name) {
	for(int i=0; i < textures.size(); i++) {
		if(textures[i].name == name) {
			textures.erase(textures.begin()+i);
			return;
		}
	}
}


void GLSLShaderBinding::addParam(String type, String name, String value) {
	int paramType;
	void *defaultData = GLSLProgramParam::createParamData(&paramType, type, value);
	LocalShaderParam *newParam = new LocalShaderParam;
	newParam->data = defaultData;
	newParam->name = name;
	localParams.push_back(newParam);
}

GLSLShader::GLSLShader(GLSLProgram *vp, GLSLProgram *fp) : Shader(Shader::MODULE_SHADER) {
	this->vp = vp;
	this->fp = fp;
	
	shader_id = glCreateProgram();
    glAttachShader(shader_id, fp->program);
    glAttachShader(shader_id, vp->program);
    glLinkProgram(shader_id);	
}

GLSLShader::~GLSLShader() {
	glDetachShader(shader_id, fp->program);
    glDetachShader(shader_id, vp->program);
	glDeleteProgram(shader_id);	
}

ShaderBinding *GLSLShader::createBinding() {
	return new GLSLShaderBinding(this);
}