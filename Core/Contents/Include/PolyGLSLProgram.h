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

#include "Polycode.h"

#include "PolyGlobals.h"

#include "PolyLogger.h"
#include "PolyResource.h"
#include "PolyVector3.h"
#include <vector>


#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <GL/glext.h>
#endif



using std::vector;

namespace Polycode {

class _PolyExport GLSLProgramParam {
	public:
	
	String name;
	bool isAuto;
	int autoID;
	void *defaultData;
	int paramType;
	
	static void *createParamData(int *retType, String type, String value);
	
	static const int POLY_MODELVIEWPROJ_MATRIX = 0;
	static const int POLY_MODELVIEW_MATRIX = 2;
	static const int POLY_MODELVIEW_INVERSE_MATRIX = 3;
	static const int POLY_EXPOSURE_LEVEL = 7;
	static const int POLY_CLEARCOLOR = 10;
	static const int POLY_AMBIENTCOLOR = 11;	
	
	static const int POLY_AREA_LIGHT_POSITION_0 = 12;
	static const int POLY_AREA_LIGHT_COLOR_0 = 13;	
	static const int POLY_AREA_LIGHT_POSITION_1 = 14;
	static const int POLY_AREA_LIGHT_COLOR_1 = 15;	
	static const int POLY_AREA_LIGHT_POSITION_2 = 16;
	static const int POLY_AREA_LIGHT_COLOR_2 = 17;	
	static const int POLY_AREA_LIGHT_POSITION_3 = 18;
	static const int POLY_AREA_LIGHT_COLOR_3 = 19;	
	static const int POLY_AREA_LIGHT_POSITION_4 = 20;
	static const int POLY_AREA_LIGHT_COLOR_4 = 21;	
	static const int POLY_AREA_LIGHT_POSITION_5 = 22;
	static const int POLY_AREA_LIGHT_COLOR_5 = 23;	
	static const int POLY_AREA_LIGHT_POSITION_6 = 24;
	static const int POLY_AREA_LIGHT_COLOR_6 = 25;	
	static const int POLY_AREA_LIGHT_POSITION_7 = 26;
	static const int POLY_AREA_LIGHT_COLOR_7 = 27;	

	static const int POLY_SPOT_LIGHT_POSITION_0 = 30;
	static const int POLY_SPOT_LIGHT_COLOR_0 = 31;
	static const int POLY_SPOT_LIGHT_DIRECTION_0 = 32;
	static const int POLY_SPOT_LIGHT_POSITION_1 = 33;
	static const int POLY_SPOT_LIGHT_COLOR_1 = 34;
	static const int POLY_SPOT_LIGHT_DIRECTION_1 = 35;
	static const int POLY_SPOT_LIGHT_POSITION_2 = 36;
	static const int POLY_SPOT_LIGHT_COLOR_2 = 37;
	static const int POLY_SPOT_LIGHT_DIRECTION_2 = 38;
	static const int POLY_SPOT_LIGHT_POSITION_3 = 39;
	static const int POLY_SPOT_LIGHT_COLOR_3 = 40;
	static const int POLY_SPOT_LIGHT_DIRECTION_3 = 41;
	
	static const int POLY_SPOT_LIGHT_TEXTUREMATRIX_0 = 42;	
	static const int POLY_SPOT_LIGHT_TEXTUREMATRIX_1 = 43;
	static const int POLY_SPOT_LIGHT_TEXTUREMATRIX_2 = 44;
	static const int POLY_SPOT_LIGHT_TEXTUREMATRIX_3 = 45;
	
	static const int PARAM_UNKNOWN = 0;	
	static const int PARAM_Number = 1;
	static const int PARAM_Number3 = 2;
	static const int PARAM_Number4 = 3;
	
	};

	class _PolyExport GLSLProgram : public Resource {
		public:
			GLSLProgram(int type);
			~GLSLProgram();
			
			void addParam(String name, bool isAuto, int autoID, int paramType, void *defaultData);
		
			unsigned int program;
//			GLSLparameter modelViewProjection;
	
			static const int TYPE_VERT = 0;
			static const int TYPE_FRAG = 1;		
			
			int type;
			
			vector<GLSLProgramParam> params;
	};
}
