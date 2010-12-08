/*
 *  PolySceneLabel.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/31/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Scene
 
#pragma once
#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyFont.h"
#include "PolyLabel.h"
#include "PolyMesh.h"
#include "PolyTexture.h"
#include "PolyPolygon.h"
#include "PolySceneEntity.h"

#include <string>
using std::string;

namespace Polycode {
	
	class _PolyExport SceneLabel : public SceneEntity {
		public:
			
			SceneLabel(string fontName, wstring text, int size, float scale, int amode);
			~SceneLabel();			
		
			bool testMouseCollision(float x, float y);
		
			void setText(wstring newText);
			Label *getLabel();
			void Render();
			
		protected:
			
			Mesh *mesh;
			Texture *texture;		
		
			float scale;
			Label *label;
	};
}