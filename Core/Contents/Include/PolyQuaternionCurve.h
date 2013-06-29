/*
Copyright (C) 2011 by Ivan Safrin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once
#include "PolyGlobals.h"
#include "PolyQuaternion.h"
#include <vector>

namespace Polycode {

class BezierCurve;

class _PolyExport QuatTriple {
	public:
	Quaternion q1;
	Quaternion q2;
	Quaternion q3;
};

class _PolyExport QuaternionCurve : public PolyBase {
	public:
		QuaternionCurve(BezierCurve *wCurve, BezierCurve *xCurve, BezierCurve *yCurve, BezierCurve *zCurve);
		virtual ~QuaternionCurve();

		Quaternion interpolate(Number t, bool useShortestPath);
		Quaternion interpolate(unsigned int fromIndex, Number t, bool useShortestPath);

		void generatePointsFromCurves(BezierCurve *wCurve, BezierCurve *xCurve, BezierCurve *yCurve, BezierCurve *zCurve);
		void recalcTangents();

	protected:

		std::vector<QuatTriple> tPoints;
		std::vector<Quaternion> points;
		std::vector<Quaternion> tangents;
};

}
