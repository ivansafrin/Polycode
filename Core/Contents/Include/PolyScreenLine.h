/*
 *  PolyScreenLine.h
 *  Poly
 *
 *  Created by Ivan Safrin on 5/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Screen

#pragma once
#include "PolyGlobals.h"
#include "PolyScreenEntity.h"
#include "PolyCoreServices.h"
#include "PolyMesh.h"

#include <string>
using std::string;

namespace Polycode {

	class _PolyExport ScreenLine : public ScreenEntity {
		public:
			
			ScreenLine(Vector2* start, Vector2* end);
			ScreenLine(ScreenEntity* target1, ScreenEntity* target2);
			~ScreenLine();

			void Update();
			void Render();
			void setLineWidth(float width);
			
		protected:
		
			float lineWidth;
			
			Vertex startVertex;
			Vertex endVertex;
		
			RenderDataArray *vertexDataArray;

			ScreenEntity *target1;
			ScreenEntity *target2;
			
	};
}