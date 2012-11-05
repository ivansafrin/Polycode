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

#pragma once

#include "PolyGlobals.h"
#include "PolyString.h"
#include "PolyResource.h"
#include "PolyShader.h"

namespace Polycode {

class _PolyExport GLSLProgramParam : public ProgramParam {
	public:		
		static void createParamData(int *retType, const String& type, const String& value, const String& min, const String& max, void **valueRes, void **minRes, void **maxRes);	
	};

	class _PolyExport GLSLProgram : public Resource {
		public:
			GLSLProgram(int type);
			virtual ~GLSLProgram();
			
			GLSLProgramParam addParam(const String& name, const String& typeString, const String& valueString, bool isAuto, int autoID, int paramType, void *defaultData, void *minData, void *maxData);
		
			unsigned int program;
//			GLSLparameter modelViewProjection;
	
			static const int TYPE_VERT = 0;
			static const int TYPE_FRAG = 1;		
			
			int type;
			
			std::vector<GLSLProgramParam> params;
	};
}
