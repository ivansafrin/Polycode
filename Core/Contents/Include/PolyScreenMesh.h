/*
 *  PolyScreenMesh.h
 *  Poly
 *
 *  Created by Ivan Safrin on 5/6/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

// @package Screen

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyScreenEntity.h"
#include "PolyMesh.h"
#include "PolyTexture.h"
#include "PolyPolygon.h"

#include <string>
using std::string;

namespace Polycode {

	class _PolyExport ScreenMesh : public ScreenEntity {
		public:
			ScreenMesh(String fileName);
			ScreenMesh(int meshType);
			~ScreenMesh();
			
			void Render();
			
			Mesh *getMesh();
			Texture *getTexture();
			void loadTexture(String fileName);
			void loadTexture(Image *image);	
			void setTexture(Texture *texture);
			
		protected:
		
			Mesh *mesh;
			Texture *texture;
	};
}