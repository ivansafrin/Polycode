/*
 *  PolySceneLabel.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/31/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Scene
 
#pragma once
#include "PolyString.h"
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
			
			SceneLabel(String fontName, String text, int size, Number scale, int amode);
			~SceneLabel();			
		
			bool testMouseCollision(Number x, Number y);
		
			void setText(String newText);
			Label *getLabel();
			void Render();
			
		protected:
			
			Mesh *mesh;
			Texture *texture;		
		
			Number scale;
			Label *label;
	};
}