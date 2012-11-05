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


#include "PolyGLSLProgram.h"
#include "PolyVector3.h"
#include "PolyVector2.h"
#include "PolyColor.h"
#include "PolyLogger.h"

#ifdef _WINDOWS
#include <windows.h>
#endif

#include "PolyGLHeaders.h"

using std::vector;

#ifdef _WINDOWS
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUNIFORM1IPROC glUniform1i;
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
#ifndef _MINGW
extern PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocation;
#endif
#endif

using namespace Polycode;

GLSLProgram::GLSLProgram(int type) : Resource(Resource::RESOURCE_PROGRAM) {
	this->type = type;
}

GLSLProgram::~GLSLProgram() {
	glDeleteShader(program);
}

GLSLProgramParam GLSLProgram::addParam(const String& name, const String& typeString, const String& valueString, bool isAuto, int autoID, int paramType, void *defaultData, void *minData, void *maxData) {
	GLSLProgramParam newParam;
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

void GLSLProgramParam::createParamData(int *retType, const String& type, const String& value, const String& min, const String& max, void **valueRes, void **minRes, void **maxRes) {
		
		(*valueRes) = NULL;
		(*minRes) = NULL;
		(*maxRes) = NULL;
						
		if(type == "Number") {
			*retType = GLSLProgramParam::PARAM_Number;
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
			*retType = GLSLProgramParam::PARAM_Vector2;
			Vector2 *val = new Vector2();
			(*valueRes) = (void*)val;
			vector<String> values = value.split(" ");
			if(values.size() == 2) {
				val->set(atof(values[0].c_str()), atof(values[1].c_str()));
			} else {
				Logger::log("Error: A Vector2 must have 2 values (%d provided)!\n", values.size());
			}
			return;				
		} else if(type == "Vector3") {
			*retType = GLSLProgramParam::PARAM_Vector3;
			Vector3 *val = new Vector3();
			(*valueRes) = (void*)val;
			vector<String> values = value.split(" ");
			if(values.size() == 3) {
				val->set(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()));
			} else {
				Logger::log("Error: A Vector3 must have 3 values (%d provided)!\n", values.size());
			}
			return;
		} else if(type == "Color") {
			*retType = GLSLProgramParam::PARAM_Color;
			Color *val = new Color();
			(*valueRes) = (void*)val;
			vector<String> values = value.split(" ");
			if(values.size() == 4) {
				val->setColor(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()), atof(values[3].c_str()));
			} else {
				Logger::log("Error: A Color must have 4 values (%d provided)!\n", values.size());
			}
			return;			
		} else {
			*retType = GLSLProgramParam::PARAM_UNKNOWN;
			(*valueRes) =  NULL;
		}
}
