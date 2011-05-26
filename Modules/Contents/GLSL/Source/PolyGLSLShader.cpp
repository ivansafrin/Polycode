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


#include "PolyGLSLShader.h"

#ifdef _WINDOWS
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocation;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
#endif

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