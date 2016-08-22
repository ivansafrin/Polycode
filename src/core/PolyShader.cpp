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

#include "polycode/core/PolyShader.h"
#include "polycode/core/PolyMatrix4.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyCore.h"
#include <stdlib.h>
#include <sstream>

using namespace Polycode;

ShaderRenderTarget::ShaderRenderTarget() : PolyBase() {
	buffer = NULL;
}

ProgramParam::ProgramParam() : type(PARAM_UNKNOWN), platformData(NULL), globalParam(NULL) {
}

ProgramAttribute::ProgramAttribute() : platformData(NULL) {
	
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
			val->setColor(1.0, 1.0, 1.0, 1.0);
			return (void*)val;
		}
		break;		
		case PARAM_MATRIX:
		{
			Matrix4 *val = new Matrix4();
			return (void*)val;
		}
		break;
		case PARAM_TEXTURE:
		{
			Texture *val = NULL;
			return (void*)val;
		}
		break;
		case PARAM_CUBEMAP:
		{
			// RENDERER_TODO: default cubemap here?
			return NULL;
		}
		break;
		default:		
			return NULL;
		break;
	}
}

ShaderProgram::ShaderProgram(const String &fileName) : Resource(Resource::RESOURCE_PROGRAM) {
	setResourcePath(fileName);
	setResourceName(fileName);
}

ShaderProgram::ShaderProgram(const String &fileName, int type) : Resource(Resource::RESOURCE_PROGRAM), type(type) {
	setResourcePath(fileName);
	setResourceName(fileName);
}


ShaderProgram::~ShaderProgram() {
}

void ShaderProgram::reloadResource(Core *core) {
	reloadProgram();
	Resource::reloadResource(core);
}


ShaderBinding::ShaderBinding() : targetShader(NULL) {
}

ShaderBinding::~ShaderBinding() {
	accessMutex.lock();
	for(int i=0; i < renderTargetBindings.size(); i++) {
		delete renderTargetBindings[i];
	}
	accessMutex.unlock();
}

unsigned int ShaderBinding::getNumLocalParams() {
	return localParams.size();
}

unsigned int ShaderBinding::getNumAttributeBindings() {
	return attributes.size();
}

AttributeBinding *ShaderBinding::getAttributeBinding(unsigned int index) {
	return attributes[index];
}

std::shared_ptr<LocalShaderParam> ShaderBinding::getLocalParam(unsigned int index) {
	return localParams[index];
}

std::shared_ptr<LocalShaderParam> ShaderBinding::getLocalParamByName(const String& name) {
	accessMutex.lock();
	for(int i=0; i < localParams.size(); i++) {
		if(localParams[i]->name == name) {
			std::shared_ptr<LocalShaderParam> retParam = localParams[i];
			accessMutex.unlock();
			return retParam;
		}
	}
	accessMutex.unlock();
	return NULL;
}

AttributeBinding *ShaderBinding::getAttributeBindingByName(const String &name) {
	for(int i=0; i < attributes.size(); i++) {
		if(attributes[i]->name == name) {
			return attributes[i];
		}
	}
	return NULL;
}

std::shared_ptr<LocalShaderParam> ShaderBinding::addParam(int type, const String& name) {
	void *defaultData = ProgramParam::createParamData(type);
	std::shared_ptr<LocalShaderParam> newParam = std::make_shared<LocalShaderParam>();
	newParam->data = defaultData;
	newParam->name = name;
	newParam->type = type;
	newParam->param = NULL;
	
	if(type == ProgramParam::PARAM_TEXTURE || type == ProgramParam::PARAM_CUBEMAP) {
		newParam->ownsPointer = false;
	}
	
	accessMutex.lock();
	localParams.push_back(newParam);
	accessMutex.unlock();
	
	return newParam;
}

std::shared_ptr<LocalShaderParam> ShaderBinding::addParamFromData(ResourcePool *pool, const String &name, const Polycode::String &data) {
	std::shared_ptr<LocalShaderParam> param = std::make_shared<LocalShaderParam>();
	std::istringstream stream(data.contents);
	
	Number n1 ,n2,n3,n4;
	int type = ProgramParam::PARAM_UNKNOWN;
	
	if (stream >> n1) {
		if (stream >> n2) {
			if (stream >> n3) {
				if (stream >> n4) {
					type = ProgramParam::PARAM_COLOR;
				} else {
					type = ProgramParam::PARAM_VECTOR3;
				}
			} else {
				type = ProgramParam::PARAM_VECTOR2;
			}
		} else {
			type = ProgramParam::PARAM_NUMBER;
		}
	} else {
		type = ProgramParam::PARAM_TEXTURE;
	}
	
	void *defaultData = ProgramParam::createParamData(type);
	std::shared_ptr<LocalShaderParam> newParam = std::make_shared<LocalShaderParam>();
	newParam->data = defaultData;
	newParam->name = name;
	newParam->type = type;
	newParam->param = NULL;
	
	if(type == ProgramParam::PARAM_TEXTURE || type == ProgramParam::PARAM_CUBEMAP) {
		newParam->ownsPointer = false;
	}
	
	newParam->setParamValueFromString(pool, type, data);
	
	accessMutex.lock();
	localParams.push_back(newParam);
	accessMutex.unlock();
	
	return newParam;
}

std::shared_ptr<LocalShaderParam> ShaderBinding::addParamPointer(int type, const String& name, void *ptr) {
	std::shared_ptr<LocalShaderParam> newParam = std::make_shared<LocalShaderParam>();
	newParam->name = name;
	newParam->data = ptr;
	newParam->type = type;
	newParam->param = NULL;
	newParam->ownsPointer = false;
	accessMutex.lock();
	localParams.push_back(newParam);
	accessMutex.unlock();
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

void ShaderBinding::copyTo(ShaderBinding *targetBinding) {
	targetBinding->accessMutex.lock();
	for(int i=0; i < localParams.size(); i++) {
		std::shared_ptr<LocalShaderParam> copyParam = localParams[i]->Copy();
		targetBinding->localParams.push_back(copyParam);
	}
   targetBinding->accessMutex.unlock();
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


void ShaderBinding::setTextureForParam(const String &paramName, std::shared_ptr<Texture> texture) {
	if(!texture) {
		removeParam(paramName);
		return;
	}
	std::shared_ptr<LocalShaderParam> textureParam = getLocalParamByName(paramName);
	if(!textureParam) {
		textureParam = addParam(ProgramParam::PARAM_TEXTURE, paramName);
	}
	textureParam->setTexture(texture);
}

void ShaderBinding::setCubemapForParam(const String &paramName, std::shared_ptr<Cubemap> cubemap) {
	std::shared_ptr<LocalShaderParam> textureParam = getLocalParamByName(paramName);
	if(!textureParam) {
		textureParam = addParam(ProgramParam::PARAM_CUBEMAP, paramName);
	}
	textureParam->setCubemap(cubemap);
}

void ShaderBinding::removeParam(const String &name) {
	for(int i=0; i < localParams.size(); i++) {
		if(localParams[i]->name == name) {
			accessMutex.lock();
			localParams.erase(localParams.begin()+i);
			accessMutex.unlock();
			return;
		}
	}
}

Shader::Shader(std::shared_ptr<ShaderProgram> vp, std::shared_ptr<ShaderProgram> fp) : Resource(Resource::RESOURCE_SHADER) {
	numSpotLights = 0;
	numPointLights = 0;
	vertexProgram = vp;
	fragmentProgram = fp;
}

Shader::Shader() : Resource(Resource::RESOURCE_SHADER) {
	numSpotLights = 0;
	numPointLights = 0;
	vertexProgram = NULL;
	fragmentProgram = NULL;
}

ProgramParam *Shader::getParamPointer(const String &name) {
	for(int i=0; i < expectedParams.size(); i++) {
		if(expectedParams[i].name == name) {
			return &expectedParams[i];
		}
	}
	return NULL;
}

ProgramAttribute *Shader::getAttribPointer(const String &name) {
	for(int i=0; i < expectedAttributes.size(); i++) {
		if(expectedAttributes[i].name == name) {
			return &expectedAttributes[i];
		}
	}
	return NULL;
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

Number LocalShaderParam::getNumber() {
	if(type != ProgramParam::PARAM_NUMBER) {
		return 0.0;
	}
	return *((Number *)data);
}

Vector2 LocalShaderParam::getVector2() {
	if(type != ProgramParam::PARAM_VECTOR2) {
		return Vector2();
	}
	return *((Vector2 *)data);
}

Vector3 LocalShaderParam::getVector3() {
	if(type != ProgramParam::PARAM_VECTOR3) {
		return Vector3();
	}
	return *((Vector3 *)data);
}

Matrix4 LocalShaderParam::getMatrix4() {
	if(type != ProgramParam::PARAM_MATRIX) {
		return Matrix4();
	}
	return *((Matrix4 *)data);
}

Color LocalShaderParam::getColor() {
	if(type != ProgramParam::PARAM_COLOR) {
		return Color(0.0, 0.0, 0.0, 0.0);
	}
	return *((Color *)data);
}

void LocalShaderParam::setNumber(Number x) {
	if(type != ProgramParam::PARAM_NUMBER) {
		return;
	}
    accessMutex.lock();
	memcpy(data, &x, sizeof(x));
    accessMutex.unlock();
}

void LocalShaderParam::setVector2(Vector2 x) {
	if(type != ProgramParam::PARAM_VECTOR2) {
		return;
	}
    accessMutex.lock();
	memcpy(data, &x, sizeof(x));
    accessMutex.unlock();
}

void LocalShaderParam::setVector3(Vector3 x) {
	if(type != ProgramParam::PARAM_VECTOR3) {
		return;
	}
    accessMutex.lock();
	memcpy(data, &x, sizeof(x));
    accessMutex.unlock();
}

void LocalShaderParam::setMatrix4(Matrix4 x) {
	if(type != ProgramParam::PARAM_MATRIX) {
		return;
	}
    accessMutex.lock();
	memcpy(data, &x, sizeof(x));
    accessMutex.unlock();
}

void LocalShaderParam::setMatrix4Array(std::vector<Matrix4> &x) {
    if(type != ProgramParam::PARAM_MATRIX) {
        return;
    }
    accessMutex.lock();
    if(arraySize > 0) {
        delete[] ((Matrix4*) data);
    } else {
        delete ((Matrix4*) data);
    }
    arraySize = x.size();
    data = new Matrix4[arraySize];
    for(int i=0; i < x.size(); i++) {
        ((Matrix4*)data)[i] = x[i];
    }
//    memcpy(data, &x[0], sizeof(x));
    accessMutex.unlock();
}

void LocalShaderParam::setColor(Color x) {
	if(type != ProgramParam::PARAM_COLOR) {
		return;
	}
    accessMutex.lock();
	static_cast<Color*>(data)->setColor(&x);
    accessMutex.unlock();
}

const String& Shader::getName() const {
	return name;
}

LocalShaderParam::LocalShaderParam() {
	data = NULL;
	arraySize = 0;
	ownsPointer = true;
}

void LocalShaderParam::setTexture(std::shared_ptr<Texture> texture) {
    accessMutex.lock();
	texturePtr = texture;
    accessMutex.unlock();
}

std::shared_ptr<Texture> LocalShaderParam::getTexture() {
	return texturePtr;
}

void LocalShaderParam::setCubemap(std::shared_ptr<Cubemap> cubemap) {
    accessMutex.lock();
	cubemapPtr = cubemap;
    accessMutex.unlock();
}

std::shared_ptr<Cubemap> LocalShaderParam::getCubemap() {
	return cubemapPtr;
}

LocalShaderParam::~LocalShaderParam() {
    accessMutex.lock();
	if(ownsPointer) {
		switch(type) {
			case ProgramParam::PARAM_NUMBER:
				delete ((Number*) data);
			break;
			case ProgramParam::PARAM_VECTOR2:
				delete ((Vector2*) data);
			break;
			case ProgramParam::PARAM_VECTOR3:
				delete ((Vector3*) data);
			break;
			case ProgramParam::PARAM_COLOR:
				delete ((Color*) data);
			break;
			case ProgramParam::PARAM_MATRIX:
                if(arraySize > 0) {
                    delete[] ((Matrix4*) data);
                } else {
                    delete ((Matrix4*) data);
                }
			break;
		}
	}
    accessMutex.unlock();
}

std::shared_ptr<LocalShaderParam> LocalShaderParam::Copy() {
	std::shared_ptr<LocalShaderParam> copyParam = std::make_shared<LocalShaderParam>();
	copyParam->name = name;
	copyParam->type = type;
	copyParam->data = ProgramParam::createParamData(type);
	copyParam->ownsPointer = ownsPointer;
	
	switch(type) {
		case ProgramParam::PARAM_NUMBER:
		{
			copyParam->setNumber(getNumber());
		}
		break;
		case ProgramParam::PARAM_VECTOR2:
		{
			copyParam->setVector2(getVector2());
		}
		break;
		case ProgramParam::PARAM_VECTOR3:
		{
			copyParam->setVector3(getVector3());
		}
		break;
		case ProgramParam::PARAM_COLOR:
		{
			copyParam->setColor(getColor());
		}
		break;
		case ProgramParam::PARAM_MATRIX:
		{
			copyParam->setMatrix4(getMatrix4());
		}
		break;
	}
	return copyParam;
}

AttributeBinding::AttributeBinding() : enabled(true), vertexData(NULL), attribute(NULL) {
	
}

AttributeBinding *ShaderBinding::addAttributeBinding(const String &name, VertexDataArray *dataArray) {
	AttributeBinding *binding = new AttributeBinding();
	binding->name = name;
	binding->attribute = NULL;
	binding->vertexData = dataArray;
	attributes.push_back(binding);
	return binding;
}

void LocalShaderParam::setParamValueFromString(ResourcePool *pool, int type, String pvalue) {
		switch(type) {
			case ProgramParam::PARAM_NUMBER:
			{
				setNumber(atof(pvalue.c_str()));
			}
				break;
			case ProgramParam::PARAM_VECTOR2:
			{
				std::vector<String> values = pvalue.split(" ");
				if(values.size() == 2) {
					setVector2(Vector2(atof(values[0].c_str()), atof(values[1].c_str())));
				} else {
					printf("Material parameter error: Vector2 %s must have 2 values (%d provided)!\n", name.c_str(), (int)values.size());
				}
			}
				break;
			case ProgramParam::PARAM_VECTOR3:
			{
				std::vector<String> values = pvalue.split(" ");
				if(values.size() == 3) {
					setVector3(Vector3(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str())));
				} else {
					printf("Material parameter error: Vector3 %s must have 3 values (%d provided)!\n", name.c_str(), (int)values.size());
				}
			}
				break;
			case ProgramParam::PARAM_COLOR:
			{
				std::vector<String> values = pvalue.split(" ");
				if(values.size() == 4) {
					setColor(Color(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()), atof(values[3].c_str())));
				} else {
					printf("Material parameter error: Color %s must have 4 values (%d provided)!\n", name.c_str(), (int)values.size());
				}
			}
			break;
			case ProgramParam::PARAM_TEXTURE:
				std::shared_ptr<Texture> texture = std::static_pointer_cast<Texture>(pool->loadResource(pvalue));
				setTexture(texture);
			break;
		}
}
