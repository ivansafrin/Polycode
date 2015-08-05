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

#include "PolyQuaternionCurve.h"
#include "PolyBezierCurve.h"
#include "PolyLogger.h"

using namespace Polycode;

QuaternionCurve::QuaternionCurve(BezierCurve *wCurve, BezierCurve *xCurve, BezierCurve *yCurve, BezierCurve *zCurve) {
	generatePointsFromCurves(wCurve, xCurve, yCurve, zCurve);
}

QuaternionCurve::~QuaternionCurve() {

}

void QuaternionCurve::generatePointsFromCurves(BezierCurve *wCurve, BezierCurve *xCurve, BezierCurve *yCurve, BezierCurve *zCurve) {
	for(int i=0; i < wCurve->getNumControlPoints(); i++) {
		Quaternion quat1(wCurve->getControlPoint(i)->p1.y,
							xCurve->getControlPoint(i)->p1.y,
							yCurve->getControlPoint(i)->p1.y,
							zCurve->getControlPoint(i)->p1.y);

		Quaternion quat2(wCurve->getControlPoint(i)->p2.y,
							xCurve->getControlPoint(i)->p2.y,
							yCurve->getControlPoint(i)->p2.y,
							zCurve->getControlPoint(i)->p2.y);

		Quaternion quat3(wCurve->getControlPoint(i)->p3.y,
							xCurve->getControlPoint(i)->p3.y,
							yCurve->getControlPoint(i)->p3.y,
							zCurve->getControlPoint(i)->p3.y);

		
		QuatTriple newTriple;
		newTriple.q1 = quat1;
		newTriple.q2 = quat2;
		newTriple.q3 = quat3;
		tPoints.push_back(newTriple);
	}
}

Quaternion QuaternionCurve::interpolate(Number t, bool useShortestPath)
{
	t = std::min(std::max(t, Number(0.0)), Number(1.0));
    Number fSeg = t * (tPoints.size() - 1);
    unsigned int segIdx = (unsigned int)fSeg;
    t = fSeg - segIdx;

    return interpolate(segIdx, t, useShortestPath);
}

Quaternion QuaternionCurve::interpolate(unsigned int fromIndex, Number t, bool useShortestPath) {
    if ((fromIndex + 1) == tPoints.size() && tPoints[fromIndex].q2 != tPoints[0].q2) {
        return  tPoints[fromIndex].q2;

    }
    if (t == 0.0f) {
        return tPoints[fromIndex].q2;
    }
    else if(t == 1.0f) {
        return tPoints[fromIndex + 1].q2;
    }
    
    Quaternion &p = tPoints[fromIndex].q2;
    Quaternion &q = tPoints[fromIndex+1].q2;
    Quaternion &a = tPoints[fromIndex].q3;
    Quaternion &b = tPoints[fromIndex+1].q1;		
    
    if ((fromIndex + 1) == tPoints.size() && tPoints[fromIndex].q2 == tPoints[0].q2) {
        q = tPoints[1].q2;
        b = tPoints[1].q1;					
    } 

    return Quaternion::Squad(t, p, a, b, q, useShortestPath);
}