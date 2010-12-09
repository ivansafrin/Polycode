/*
 *  PolyCGProgram.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Materials

#pragma once

#include "Polycode.h"

#include "PolyGlobals.h"

#include "PolyLogger.h"
#include "PolyResource.h"
#include "PolyVector3.h"
#include "PolyUtil.h"
#include <vector>
#include <CG/cg.h>

using std::vector;

namespace Polycode {

class _PolyExport CGProgramParam {
	public:
	
	CGparameter cgParam;
	String name;
	bool isAuto;
	int autoID;
	void *defaultData;
	int paramType;
	
	static void *createParamData(int *retType, String type, String value);
	
	static const int TAU_MODELVIEWPROJ_MATRIX = 0;
	static const int TAU_MODELVIEW_MATRIX = 2;
	static const int TAU_MODELVIEW_INVERSE_MATRIX = 3;
	static const int TAU_EXPOSURE_LEVEL = 7;
	static const int TAU_CLEARCOLOR = 10;
	static const int TAU_AMBIENTCOLOR = 11;	
	
	static const int TAU_AREA_LIGHT_POSITION_0 = 12;
	static const int TAU_AREA_LIGHT_COLOR_0 = 13;	
	static const int TAU_AREA_LIGHT_POSITION_1 = 14;
	static const int TAU_AREA_LIGHT_COLOR_1 = 15;	
	static const int TAU_AREA_LIGHT_POSITION_2 = 16;
	static const int TAU_AREA_LIGHT_COLOR_2 = 17;	
	static const int TAU_AREA_LIGHT_POSITION_3 = 18;
	static const int TAU_AREA_LIGHT_COLOR_3 = 19;	
	static const int TAU_AREA_LIGHT_POSITION_4 = 20;
	static const int TAU_AREA_LIGHT_COLOR_4 = 21;	
	static const int TAU_AREA_LIGHT_POSITION_5 = 22;
	static const int TAU_AREA_LIGHT_COLOR_5 = 23;	
	static const int TAU_AREA_LIGHT_POSITION_6 = 24;
	static const int TAU_AREA_LIGHT_COLOR_6 = 25;	
	static const int TAU_AREA_LIGHT_POSITION_7 = 26;
	static const int TAU_AREA_LIGHT_COLOR_7 = 27;	

	static const int TAU_SPOT_LIGHT_POSITION_0 = 30;
	static const int TAU_SPOT_LIGHT_COLOR_0 = 31;
	static const int TAU_SPOT_LIGHT_DIRECTION_0 = 32;
	static const int TAU_SPOT_LIGHT_POSITION_1 = 33;
	static const int TAU_SPOT_LIGHT_COLOR_1 = 34;
	static const int TAU_SPOT_LIGHT_DIRECTION_1 = 35;
	static const int TAU_SPOT_LIGHT_POSITION_2 = 36;
	static const int TAU_SPOT_LIGHT_COLOR_2 = 37;
	static const int TAU_SPOT_LIGHT_DIRECTION_2 = 38;
	static const int TAU_SPOT_LIGHT_POSITION_3 = 39;
	static const int TAU_SPOT_LIGHT_COLOR_3 = 40;
	static const int TAU_SPOT_LIGHT_DIRECTION_3 = 41;
	
	static const int TAU_SPOT_LIGHT_TEXTUREMATRIX_0 = 42;	
	static const int TAU_SPOT_LIGHT_TEXTUREMATRIX_1 = 43;
	static const int TAU_SPOT_LIGHT_TEXTUREMATRIX_2 = 44;
	static const int TAU_SPOT_LIGHT_TEXTUREMATRIX_3 = 45;
	
	static const int PARAM_UNKNOWN = 0;	
	static const int PARAM_FLOAT = 1;
	static const int PARAM_FLOAT3 = 2;
	static const int PARAM_FLOAT4 = 3;
	
	};

	class _PolyExport CGProgram : public Resource {
		public:
			CGProgram(int type);
			~CGProgram();
			
			void addParam(String name, bool isAuto, int autoID, int paramType, void *defaultData);
		
			CGprogram program;
			CGparameter modelViewProjection;
	
			static const int TYPE_VERT = 0;
			static const int TYPE_FRAG = 1;		
			
			int type;
			
			vector<CGProgramParam> params;
	};
}
