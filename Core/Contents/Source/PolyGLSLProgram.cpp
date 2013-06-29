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
#include "PolyCoreServices.h"
#include "PolyLogger.h"
#include "PolyGLHeaders.h"

#ifdef _WINDOWS
#include <windows.h>

// Some shader functions that aren't defined in glext/wglext
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

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

GLSLProgram::GLSLProgram(String fileName, int type) : ShaderProgram(type) {
	program = -1;
	this->fileName = fileName;
	reloadProgram();
}

GLSLProgram::~GLSLProgram() {
	glDeleteShader(program);
}

void GLSLProgram::reloadProgram() {
	if(program != -1)
		glDeleteShader(program);

	OSFILE *file = OSBasics::open(fileName, "r");
	OSBasics::seek(file, 0, SEEK_END);
	long progsize = OSBasics::tell(file);
	OSBasics::seek(file, 0, SEEK_SET);
	char *buffer = (char*)malloc(progsize+1);
	memset(buffer, 0, progsize+1);
	OSBasics::read(buffer, progsize, 1, file);
	OSBasics::close(file);

	if(type == GLSLProgram::TYPE_VERT) {
		program =  glCreateShader(GL_VERTEX_SHADER);
	} else {
		program =  glCreateShader(GL_FRAGMENT_SHADER);
	}

	glShaderSource(program, 1, (const GLchar**)&buffer, 0);
	glCompileShader(program);

	GLint compiled = true;
	glGetShaderiv(program, GL_COMPILE_STATUS, &compiled);
	if(!compiled) {
		GLint length;
		GLchar* log;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);
		log = (GLchar*)malloc(length);
		glGetShaderInfoLog(program, length, &length, log);
		printf("GLSL ERROR: %s\n", log);
		CoreServices::getInstance()->getLogger()->logBroadcast("GLSL ERROR:" + String(log));
		free(log);
	}
	free(buffer);
}
