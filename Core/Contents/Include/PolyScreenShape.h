/*
 *  PolyScreenShape.h
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
#include "PolyScreenMesh.h"
#include "PolyPolygon.h"
#include "PolyMesh.h"

#include <string>
using std::string;

namespace Polycode {

	class _PolyExport ScreenShape : public ScreenMesh {
		public:
			
			ScreenShape(int shapeType, Number option1=0, Number option2=0, Number option3=0, Number option4=0);
			~ScreenShape();
			void Render();
					
			void setStrokeColor(Number r, Number g, Number b, Number a);
			void setStrokeWidth(Number width);
			
			void setGradient(Number r1, Number g1, Number b1, Number a1, Number r2, Number g2, Number b2, Number a2);
			void clearGradient();
		
			void setShapeSize(Number newWidth, Number newHeight);
		
			void addShapePoint(Number x, Number y);
			
			static const int SHAPE_RECT = 1;
			static const int SHAPE_CIRCLE = 2;
			static const int SHAPE_CIRCLE_OUTLINE = 3;
			static const int SHAPE_CUSTOM = 4;
			
			bool strokeEnabled;
			Color strokeColor;
			bool lineSmooth;
			
		protected:
		
			Number option1;
			Number option2;
			Number option3;
			Number option4;
									
			Polygon *customShapePoly;
			Number strokeWidth;
			int shapeType;
			
	};
}