/*
 *  PolyScreenCurve.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/5/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Screen

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyScreenEntity.h"
#include "PolyBezierCurve.h"
#include "PolyPolygon.h"
#include "PolyScreenShape.h"

namespace Polycode {

	class _PolyExport ScreenCurve : public ScreenShape {
		public:
			ScreenCurve(BezierCurve *curve, int numVertices);
			~ScreenCurve();
			
		protected:
		
			float numVertices;
			BezierCurve *curve;
	};
}