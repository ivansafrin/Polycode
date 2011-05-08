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

#include "PolyCGShader.h"

using namespace Polycode;

CGShaderBinding::CGShaderBinding(CGShader *shader) : ShaderBinding(shader) {
	cgShader = shader;
}

CGShaderBinding::~CGShaderBinding() {
	
}


void CGShaderBinding::addTexture(String name, Texture *texture) {
	CGTextureBinding binding;
	binding.name = name;
	binding.texture = texture;
	binding.vpParam = cgGetNamedParameter(cgShader->fp->program, name.c_str());
	textures.push_back(binding);
}

void CGShaderBinding::addCubemap(String name, Cubemap *cubemap) {
	CGCubemapBinding binding;
	binding.cubemap = cubemap;
	binding.name = name;
	binding.vpParam = cgGetNamedParameter(cgShader->fp->program, name.c_str());
	cubemaps.push_back(binding);
}

void CGShaderBinding::clearTexture(String name) {
	for(int i=0; i < textures.size(); i++) {
		if(textures[i].name == name) {
			textures.erase(textures.begin()+i);
			return;
		}
	}
}


void CGShaderBinding::addParam(String type, String name, String value) {
	int paramType;
	void *defaultData = CGProgramParam::createParamData(&paramType, type, value);
	LocalShaderParam *newParam = new LocalShaderParam;
	newParam->data = defaultData;
	newParam->name = name;
	localParams.push_back(newParam);
}

CGShader::CGShader(CGProgram *vp, CGProgram *fp) : Shader(Shader::MODULE_SHADER) {
	this->vp = vp;
	this->fp = fp;
}

CGShader::~CGShader() {

}

ShaderBinding *CGShader::createBinding() {
	return new CGShaderBinding(this);
}