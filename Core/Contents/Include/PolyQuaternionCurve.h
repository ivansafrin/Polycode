/*
 *  PolyQuaternionCurve.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/15/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Math

#pragma once
#include "PolyGlobals.h"
#include "PolyBezierCurve.h"
#include "PolyQuaternion.h"
#include <vector>

using std::vector;

namespace Polycode {

	class _PolyExport QuatTriple {
		public:
		Quaternion q1;
		Quaternion q2;
		Quaternion q3;		
	};	

	class _PolyExport QuaternionCurve {
		public:
			QuaternionCurve(BezierCurve *wCurve, BezierCurve *xCurve, BezierCurve *yCurve, BezierCurve *zCurve);
			~QuaternionCurve();
		
			Quaternion interpolate(float t, bool useShortestPath);
			Quaternion interpolate(unsigned int fromIndex, float t, bool useShortestPath);
						
			void generatePointsFromCurves(BezierCurve *wCurve, BezierCurve *xCurve, BezierCurve *yCurve, BezierCurve *zCurve);
			void recalcTangents(void);
		
		private:
		
			vector<QuatTriple> tPoints;
			vector<Quaternion> points;			
			vector<Quaternion> tangents;
	};
}