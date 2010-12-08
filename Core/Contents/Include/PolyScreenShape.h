/*
 *  PolyScreenShape.h
 *  Poly
 *
 *  Created by Ivan Safrin on 5/6/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Screen

#pragma once
#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyScreenEntity.h"
#include "PolyScreenMesh.h"
#include "PolyPolygon.h"
#include "PolyMesh.h"

#include <string>
using std::string;

namespace Polycode {

	class _PolyExport ScreenShape : public ScreenMesh {
		public:
			
			ScreenShape(int shapeType, float option1=0, float option2=0, float option3=0, float option4=0);
			~ScreenShape();
			void Render();
					
			void setStrokeColor(float r, float g, float b, float a);
			void setStrokeWidth(float width);
			
			void setGradient(float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2);
			void clearGradient();
		
			void setShapeSize(float newWidth, float newHeight);
		
			void addShapePoint(float x, float y);
			
			static const int SHAPE_RECT = 1;
			static const int SHAPE_CIRCLE = 2;
			static const int SHAPE_CIRCLE_OUTLINE = 3;
			static const int SHAPE_CUSTOM = 4;
			
			bool strokeEnabled;
			Color strokeColor;
			bool lineSmooth;
			
		protected:
		
			float option1;
			float option2;
			float option3;
			float option4;
									
			Polygon *customShapePoly;
			float strokeWidth;
			int shapeType;
			
	};
}