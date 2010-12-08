/*
 *  PolyScenePrimitive.h
 *  Poly
 *
 *  Created by Ivan Safrin on 6/15/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Scene

#pragma once
#include "PolyGlobals.h"
#include "PolySceneMesh.h"
#include "PolyCoreServices.h"

#include <string>
using std::string;

namespace Polycode {

	class _PolyExport ScenePrimitive : public SceneMesh {
		public:
		
			ScenePrimitive(int type, float v1=1.0f, float v2=1.0f, float v3=1.0f);
			virtual ~ScenePrimitive();

			static const int TYPE_BOX = 0;		
			static const int TYPE_PLANE = 1;
			static const int TYPE_SPHERE = 2;
		
		private:
		
	};
	
}