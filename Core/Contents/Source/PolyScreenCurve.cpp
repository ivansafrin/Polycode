/*
 *  PolyScreenCurve.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/5/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyScreenCurve.h"

using namespace Polycode;

ScreenCurve::ScreenCurve(BezierCurve *curve, int numVertices) : ScreenShape(ScreenShape::SHAPE_CUSTOM) {
	this->curve = curve;
	this->numVertices = numVertices;
	
	mesh->setMeshType(Mesh::TRIFAN_MESH);
	
	Polygon *poly = new Polygon();

	Color c;
	Number interval = 1.0f/numVertices;
	Vector3 vec;
	Number offset = 1.0f;
	Vertex *v;
	for(int i=0; i < numVertices; i++) {
		vec = curve->getPointAt(offset);
		v = poly->addVertex(vec.x, vec.y, 0);
		offset -= interval;
	}	
	mesh->addPolygon(poly);
}

ScreenCurve::~ScreenCurve() {
}