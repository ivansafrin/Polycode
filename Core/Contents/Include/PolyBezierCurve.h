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
		BezierPoint(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z);
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
			
		void addControlPoint(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z);

		void addControlPoint3dWithHandles(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z);
		void addControlPoint3d(float x, float y, float z);		
		void addControlPoint2dWithHandles(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y);
		void addControlPoint2d(float x, float y);
		
		float getHeightAt(float a);
		
		Vector3 getPointAt(float a);
		inline Vector3 getPointBetween(float a, BezierPoint *bp1, BezierPoint *bp2);
			
		void rebuildBuffers();
		
		protected:
		
			bool buffersDirty;
		
			float heightBuffer[BUFFER_CACHE_PRECISION];
		
			void recalculateDistances();
	
			vector<BezierPoint*> controlPoints;
			vector<float> distances;
			
	};

}