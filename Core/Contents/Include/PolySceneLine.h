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
#include "PolyMesh.h"

namespace Polycode {
	class _PolyExport SceneLine : public SceneEntity {
		public:
			SceneLine(SceneEntity *ent1, SceneEntity *ent2);
			~SceneLine();
			
			void Render();
			
		private:		
		
			Mesh *mesh;
		
			SceneEntity *ent1;
			SceneEntity *ent2;
	};

}