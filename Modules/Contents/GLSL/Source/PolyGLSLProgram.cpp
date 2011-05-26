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
		if(type == "Number") {
			*retType = GLSLProgramParam::PARAM_Number;
			Number *val = new Number();
			*val = atof(value.c_str());
			defaultData = (void*)val;
			return defaultData;			
		} else if(type == "Number3") {
			*retType = GLSLProgramParam::PARAM_Number3;
			Vector3 *val = new Vector3();
			defaultData = (void*)val;
			vector<String> values = value.split(" ");
			if(values.size() == 3) {
				val->set(atof(values[0].c_str()), atof(values[1].c_str()), atof(values[2].c_str()));
			} else {
				Logger::log("Error: A Number3 must have 3 values (%d provided)!\n", values.size());
			}
			return defaultData;
		} else {
			*retType = GLSLProgramParam::PARAM_UNKNOWN;
			return NULL;
		}

}