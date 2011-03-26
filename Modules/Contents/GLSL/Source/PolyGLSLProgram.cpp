/*
 *  PolyGLSLProgram.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyGLSLProgram.h"

using namespace Polycode;

GLSLProgram::GLSLProgram(int type) : Resource(Resource::RESOURCE_PROGRAM) {
	this->type = type;
}

GLSLProgram::~GLSLProgram() {
	glDeleteShader(program);
}

void GLSLProgram::addParam(String name, bool isAuto, int autoID, int paramType, void *defaultData) {
	GLSLProgramParam newParam;
	newParam.name = name;
	newParam.paramType = paramType;
	newParam.defaultData = defaultData;
	newParam.isAuto = isAuto;
	newParam.autoID = autoID;
//	newParam.cgParam = cgGetNamedParameter(program, name.c_str());
	params.push_back(newParam);
}

void *GLSLProgramParam::createParamData(int *retType, String type, String value) {
		void *defaultData;
		if(type == "float") {
			*retType = GLSLProgramParam::PARAM_FLOAT;
			float *val = new float();
			*val = atof(value.c_str());
			defaultData = (void*)val;
			return defaultData;			
		} else if(type == "float3") {
			*retType = GLSLProgramParam::PARAM_FLOAT3;
			Vector3 *val = new Vector3();
			defaultData = (void*)val;
			vector<String> values = value.split(" ");
			if(values.size() == 3) {
				val->set(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()));
			} else {
				Logger::log("Error: A float3 must have 3 values (%d provided)!\n", values.size());
			}
			return defaultData;
		} else {
			*retType = GLSLProgramParam::PARAM_UNKNOWN;
			return NULL;
		}

}