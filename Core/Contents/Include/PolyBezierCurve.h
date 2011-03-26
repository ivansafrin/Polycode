/*
 *  PolyBezierCurve.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/5/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Math

#pragma once 

#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyString.h"
#include "PolyVector3.h"
#include <vector>

using std::vector;

#define BUFFER_CACHE_PRECISION 100

namespace Polycode {

	class _PolyExport BezierPoint {
		public:
		BezierPoint(Number p1x, Number p1y, Number p1z, Number p2x, Number p2y, Number p2z, Number p3x, Number p3y, Number p3z);
		Vector3 p1;
		Vector3 p2;
		Vector3 p3;
	};
	
	class _PolyExport BezierCurve {
		public:
			BezierCurve();
			~BezierCurve();

		BezierPoint *getControlPoint(unsigned int index);
		unsigned int getNumControlPoints();
			
		void addControlPoint(Number p1x, Number p1y, Number p1z, Number p2x, Number p2y, Number p2z, Number p3x, Number p3y, Number p3z);

		void addControlPoint3dWithHandles(Number p1x, Number p1y, Number p1z, Number p2x, Number p2y, Number p2z, Number p3x, Number p3y, Number p3z);
		void addControlPoint3d(Number x, Number y, Number z);		
		void addControlPoint2dWithHandles(Number p1x, Number p1y, Number p2x, Number p2y, Number p3x, Number p3y);
		void addControlPoint2d(Number x, Number y);
		
		Number getHeightAt(Number a);
		
		Vector3 getPointAt(Number a);
		inline Vector3 getPointBetween(Number a, BezierPoint *bp1, BezierPoint *bp2);
			
		void rebuildBuffers();
		
		Number heightBuffer[BUFFER_CACHE_PRECISION];

		vector<BezierPoint*> controlPoints;
		vector<Number> distances;
		
		
		protected:
		
			bool buffersDirty;
		
			void recalculateDistances();
	
			
	};

}