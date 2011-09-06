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

#include "PolyScreenCurve.h"
#include "PolyBezierCurve.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"

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
