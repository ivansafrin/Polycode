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
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolySceneMesh.h"
#include "PolyCoreServices.h"

#include <string>
using std::string;

namespace Polycode {

	class _PolyExport ScenePrimitive : public SceneMesh {
		public:
		
			ScenePrimitive(int type, Number v1=1.0f, Number v2=1.0f, Number v3=1.0f);
			virtual ~ScenePrimitive();

			static const int TYPE_BOX = 0;		
			static const int TYPE_PLANE = 1;
			static const int TYPE_SPHERE = 2;
		
		private:
		
	};
	
}