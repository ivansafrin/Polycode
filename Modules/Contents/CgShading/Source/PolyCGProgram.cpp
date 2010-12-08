/*
 *  PolyCGProgram.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyCGProgram.h"

using namespace Polycode;

CGProgram::CGProgram(int type) : Resource(Resource::RESOURCE_PROGRAM) {
	this->type = type;
}

CGProgram::~CGProgram() {

}

void CGProgram::addParam(string name, bool isAuto, int autoID, int paramType, void *defaultData) {
	CGProgramParam newParam;
	newParam.name = name;
	newParam.paramType = paramType;
	newParam.defaultData = defaultData;
	newParam.isAuto = isAuto;
	newParam.autoID = autoID;
	newParam.cgParam = cgGetNamedParameter(program, name.c_str());
	params.push_back(newParam);
}

void *CGProgramParam::createParamData(int *retType, string type, string value) {
		void *defaultData;
		if(type == "float") {
			*retType = CGProgramParam::PARAM_FLOAT;
			float *val = new float();
			*val = atof(value.c_str());
			defaultData = (void*)val;
			return defaultData;			
		} else if(type == "float3") {
			*retType = CGProgramParam::PARAM_FLOAT3;
			Vector3 *val = new Vector3();
			defaultData = (void*)val;
			vector<string> values = StringUtil::split(value, " ");
			if(values.size() == 3) {
				val->set(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()));
			} else {
				Logger::log("Error: A float3 must have 3 values (%d provided)!\n", values.size());
			}
			return defaultData;
		} else {
			*retType = CGProgramParam::PARAM_UNKNOWN;
			return NULL;
		}

}