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

#include "PolySceneLine.h"
#include "PolyRenderer.h"

using namespace Polycode;

using std::min;
using std::max;

SceneCurve::SceneCurve() : SceneMesh(Mesh::LINE_STRIP_MESH) {
    curveResolution = 256;
    renderCurve = true;
    curve = new BezierCurve();
}

SceneCurve::SceneCurve(BezierCurve *curve) : SceneMesh(Mesh::LINE_STRIP_MESH) {
    curveResolution = 256;
    renderCurve = true;
    this->curve = curve;
}

SceneCurve *SceneCurve::SceneCurveWithCurve(BezierCurve *curve) {
    return new SceneCurve(curve);
}

Vector3 SceneCurve::getWorldPointAt(Number t) {
    return getConcatenatedMatrix() * curve->getPointAt(t);
}

Entity *SceneCurve::Clone(bool deepClone, bool ignoreEditorOnly) const {
	SceneCurve *newCurve = new SceneCurve();
	applyClone(newCurve, deepClone, ignoreEditorOnly);
	return newCurve;
}

void SceneCurve::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    SceneMesh::applyClone(clone, deepClone, ignoreEditorOnly);
    
    SceneCurve *cloneCurve = (SceneCurve*)clone;
    cloneCurve->renderCurve = renderCurve;
    cloneCurve->curveResolution = curveResolution;
    
    for(int i=0; i < curve->getNumControlPoints(); i++) {
        BezierPoint *pt = curve->getControlPoint(i);
        cloneCurve->getCurve()->addControlPoint(
            pt->p1.x, pt->p1.y, pt->p1.z,
            pt->p2.x, pt->p2.y, pt->p2.z,
            pt->p3.x, pt->p3.y, pt->p3.z);
    }
}


SceneCurve::~SceneCurve() {
    delete curve;
}

BezierCurve *SceneCurve::getCurve() {
    return curve;
}

void SceneCurve::Update() {
    mesh->clearMesh();
    Vector3 bBox;
    
    if(renderCurve) {

        Number step = (1.0 / ((Number)curveResolution));
        
        for(Number offset=0.0; offset <= 1.0; offset += step) {
            Vector3 pt = curve->getPointAt(offset);
            mesh->addVertexWithUV(pt.x, pt.y, pt.z, offset, 0.0);
            
            bBox.x = max(bBox.x,(Number)fabs(pt.x));
            bBox.y = max(bBox.y,(Number)fabs(pt.y));
            bBox.z = max(bBox.z,(Number)fabs(pt.z));

        }
    }
    
    setLocalBoundingBox(bBox * 2.0);
}

SceneLine::SceneLine(Vector3 start, Vector3 end) : SceneMesh(Mesh::LINE_MESH) {
	this->ent1 = NULL;
	this->ent2 = NULL;
	this->start = start;
	this->end = end;	
	initLine();
	ignoreParentMatrix = false;
}

SceneLine::SceneLine(Entity *ent1, Entity *ent2) : SceneMesh(Mesh::LINE_MESH) {
	this->ent1 = ent1;
	this->ent2 = ent2;	
	initLine();
	ignoreParentMatrix = true;

}

void SceneLine::initLine() {
	mesh->addVertexWithUV(0,0,0,0,0);
	mesh->addVertexWithUV(0,0,0,1,0);
}

SceneLine *SceneLine::SceneLineWithPositions(Vector3 start, Vector3 end) {
	return new SceneLine(start, end);
}

SceneLine::~SceneLine() {
}

void SceneLine::setStart(Vector3 start) {
	this->start = start;
}

void SceneLine::setEnd(Vector3 end) {
	this->end = end;
}

void SceneLine::Update(){

	Vector3 v1;
	Vector3 v2;

    mesh->vertexPositionArray.data.clear();
	
	if(ent1 != NULL && ent2 != NULL) {
		v1 = ent1->getConcatenatedMatrix().getPosition();
		v2 = ent2->getConcatenatedMatrix().getPosition();
        
        mesh->addVertex(v1.x,v1.y,v1.z);
        mesh->addVertex(v2.x,v2.y,v2.z);
	} else {
		v1 = start;
		v2 = end;
        mesh->addVertex(v1.x,v1.y*yAdjust,v1.z);
        mesh->addVertex(v2.x,v2.y*yAdjust,v2.z);

	}
}