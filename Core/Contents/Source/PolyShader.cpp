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

ShaderProgram::ShaderProgram(int type) : Resource(Resource::RESOURCE_PROGRAM) {
	this->type = type;
}

ShaderProgram::~ShaderProgram() {

}

ProgramParam ShaderProgram::addParam(const String& name, const String& typeString, const String& valueString, bool isAuto, int autoID, int paramType, void *defaultData, void *minData, void *maxData) {
	ProgramParam newParam;
	newParam.name = name;
	newParam.typeString = typeString;
	newParam.valueString = valueString;	
	newParam.paramType = paramType;
	newParam.defaultData = defaultData;
	newParam.minValue = minData;
	newParam.maxValue = maxData;
	newParam.isAuto = isAuto;
	newParam.autoID = autoID;

	params.push_back(newParam);
	return newParam;
}

void ProgramParam::createParamData(int *retType, const String& type, const String& value, const String& min, const String& max, void **valueRes, void **minRes, void **maxRes) {
		
		(*valueRes) = NULL;
		(*minRes) = NULL;
		(*maxRes) = NULL;
						
		if(type == "Number") {
			*retType = ProgramParam::PARAM_Number;
			Number *val = new Number();
			*val = atof(value.c_str());
			(*valueRes) = (void*)val;
			
			val = new Number();
			*val = atof(min.c_str());
			(*minRes) = (void*)val;

			val = new Number();
			*val = atof(max.c_str());
			(*maxRes) = (void*)val;			
			
			return;		
		} else if(type == "Vector2") {
			*retType = ProgramParam::PARAM_Vector2;
			Vector2 *val = new Vector2();
			(*valueRes) = (void*)val;
			std::vector<String> values = value.split(" ");
			if(values.size() == 2) {
				val->set(atof(values[0].c_str()), atof(values[1].c_str()));
			} else {
				printf("Error: A Vector2 must have 2 values (%d provided)!\n", values.size());
			}
			return;				
		} else if(type == "Vector3") {
			*retType = ProgramParam::PARAM_Vector3;
			Vector3 *val = new Vector3();
			(*valueRes) = (void*)val;
			std::vector<String> values = value.split(" ");
			if(values.size() == 3) {
				val->set(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()));
			} else {
				printf("Error: A Vector3 must have 3 values (%d provided)!\n", values.size());
			}
			return;
		} else if(type == "Color") {
			*retType = ProgramParam::PARAM_Color;
			Color *val = new Color();
			(*valueRes) = (void*)val;
			std::vector<String> values = value.split(" ");
			if(values.size() == 4) {
				val->setColor(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()), atof(values[3].c_str()));
			} else {
				printf("Error: A Color must have 4 values (%d provided)!\n", values.size());
			}
			return;			
		} else {
			*retType = ProgramParam::PARAM_UNKNOWN;
			(*valueRes) =  NULL;
		}
}


ShaderBinding::ShaderBinding(Shader *shader) {
	this->shader = shader;
}

ShaderBinding::~ShaderBinding() {
	for(int i=0; i < localParams.size(); i++) {
		delete localParams[i];
	}	
	for(int i=0; i < renderTargetBindings.size(); i++) {
		delete renderTargetBindings[i];
	}	
	for(int i=0; i < inTargetBindings.size(); i++) {
		delete inTargetBindings[i];
	}	
	for(int i=0; i < outTargetBindings.size(); i++) {
		delete outTargetBindings[i];
	}	
}

unsigned int ShaderBinding::getNumLocalParams() {
	return localParams.size();
}

LocalShaderParam *ShaderBinding::getLocalParam(unsigned int index) {
	return localParams[index];
}

LocalShaderParam *ShaderBinding::getLocalParamByName(const String& name) {
	for(int i=0; i < localParams.size(); i++) {
		if(localParams[i]->name == name) {
			return localParams[i];
		}
	}
	return NULL;
}

LocalShaderParam *ShaderBinding::addLocalParam(const String& name, void *ptr) {
	LocalShaderParam *newParam = new LocalShaderParam();
	newParam->name = name;
	newParam->data = ptr;
	localParams.push_back(newParam);
	return newParam;
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
	vp = NULL;
	fp = NULL;
}

Shader::~Shader() {

}

int Shader::getType() const {
	return type;
}

void Shader::setName(const String& name) {
	this->name = name;
}

const String& Shader::getName() const {
	return name;
}
