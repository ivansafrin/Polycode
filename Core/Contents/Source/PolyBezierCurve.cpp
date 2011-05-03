/*
 *  PolyBezierCurve.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/5/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */


#include "PolyBezierCurve.h"

using namespace Polycode;


BezierPoint::BezierPoint(Number p1x, Number p1y, Number p1z, Number p2x, Number p2y, Number p2z, Number p3x, Number p3y, Number p3z) {
	p1.x = p1x;
	p1.y = p1y;
	p1.z = p1z;		
	p2.x = p2x;
	p2.y = p2y;
	p2.z = p2z;		
	p3.x = p3x;
	p3.y = p3y;
	p3.z = p3z;	
}

BezierCurve::BezierCurve(){
	for(int i=0; i < BUFFER_CACHE_PRECISION; i++) {
		heightBuffer[i] = 0;
	}
	
	buffersDirty = false;	
}

BezierCurve::~BezierCurve() {

}

void BezierCurve::addControlPoint(Number p1x, Number p1y, Number p1z, Number p2x, Number p2y, Number p2z, Number p3x, Number p3y, Number p3z) {
	BezierPoint* newPoint = new BezierPoint(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z);
	controlPoints.push_back(newPoint);
	distances.push_back(0);
	recalculateDistances();
	buffersDirty = true;	
}

void BezierCurve::addControlPoint3dWithHandles(Number p1x, Number p1y, Number p1z, Number p2x, Number p2y, Number p2z, Number p3x, Number p3y, Number p3z) {
	addControlPoint(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z);
}

void BezierCurve::addControlPoint3d(Number x, Number y, Number z) {
	addControlPoint(x, y, z, x, y, z, x, y, z);
}

void BezierCurve::addControlPoint2dWithHandles(Number p1x, Number p1y, Number p2x, Number p2y, Number p3x, Number p3y) {
	addControlPoint(p1x, p1y, 0, p2x, p2y, 0, p3x, p3y, 0);
}

void BezierCurve::addControlPoint2d(Number x, Number y) {
	addControlPoint(x, y, 0, x, y, 0, x, y, 0);
}


void BezierCurve::recalculateDistances() {
	if(controlPoints.size() < 2)
		return;
		
	Number dist, lastDist = 0;
	distances[0] = 0;
	Number totalDistance = 0;
		
	Vector3 point, lastPoint;
	for(int i=0; i < controlPoints.size()-1; i++) {
		lastPoint = getPointBetween(0, controlPoints[i], controlPoints[i+1]);
		dist = 0;
		for(Number a=0.0f; a < 1.0f; a += 0.01) {
			point = getPointBetween(a, controlPoints[i], controlPoints[i+1]);
			dist += point.distance(lastPoint);
			lastPoint = point;
		}
		lastDist += dist;
		distances[i+1] = lastDist;
		totalDistance += dist;
	}
	
	// normalize distances to total distance
	for(int i=0; i < controlPoints.size(); i++) {
		distances[i] = distances[i]/totalDistance;
	}
}

Vector3 BezierCurve::getPointBetween(Number a, BezierPoint *bp1, BezierPoint *bp2) {
	Vector3 retVector;
	Number b = 1.0f - a;
	
	retVector.x = bp1->p2.x*a*a*a + bp1->p3.x*3*a*a*b + bp2->p1.x*3*a*b*b + bp2->p2.x*b*b*b;
	retVector.y = bp1->p2.y*a*a*a + bp1->p3.y*3*a*a*b + bp2->p1.y*3*a*b*b + bp2->p2.y*b*b*b;
	retVector.z = bp1->p2.z*a*a*a + bp1->p3.z*3*a*a*b + bp2->p1.z*3*a*b*b + bp2->p2.z*b*b*b;	

	return retVector;
}

BezierPoint *BezierCurve::getControlPoint(unsigned int index) {
	return controlPoints[index];
} 

unsigned int BezierCurve::getNumControlPoints() {
	return controlPoints.size();
}

Number BezierCurve::getHeightAt(Number a) {
	if( a< 0) a = 0;
	if(a > 1) a = 1;
	
	if (buffersDirty) 
		rebuildBuffers();
	
	int index = ((Number)(BUFFER_CACHE_PRECISION)) * a;	
	return heightBuffer[index];
	
//	return getPointAt(a).y;
}

void BezierCurve::rebuildBuffers() {
	for(int i=0; i < BUFFER_CACHE_PRECISION; i++) {
		heightBuffer[i]	= getPointAt(((Number)i)/((Number)BUFFER_CACHE_PRECISION)).y;
	}
	buffersDirty = false;
}

Vector3 BezierCurve::getPointAt(Number a) {
	if(a < 0)
		a = 0;
	if(a > 1)
		a = 1;
		
		
	if(controlPoints.size() < 2)
		return Vector3(0,0,0);
	
	Vector3 retVector;
	for(int i=0; i < controlPoints.size()-1; i++) {
		if(a >= distances[i] && a <= distances[i+1]) {
			retVector = getPointBetween(1.0f-((a-distances[i])/(distances[i+1]-distances[i])), controlPoints[i], controlPoints[i+1]);
		}
	}
	return retVector;
}
