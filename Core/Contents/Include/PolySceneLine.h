/*
 *  PolySceneLine.h
 *  Poly
 *
 *  Created by Ivan Safrin on 10/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Scene
 
#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolySceneEntity.h"
#include "PolyCoreServices.h"

namespace Polycode {
	class _PolyExport SceneLine : public SceneEntity {
		public:
			SceneLine(Vector3 p1, Vector3 p2);
			~SceneLine();
			
			void Render();
			
		private:
			Vertex v1;
			Vertex v2;
	};

}