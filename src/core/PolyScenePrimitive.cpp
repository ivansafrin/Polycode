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
 
#include "polycode/core/PolyScenePrimitive.h"
#include "polycode/core/PolyMesh.h"

using namespace Polycode;

ScenePrimitive::ScenePrimitive(int type, Number v1, Number v2, Number v3,Number v4,Number v5) : SceneMesh() {

	this->type = type;
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->v4 = v4;
	this->v5 = v5;

	recreatePrimitive();
}

int ScenePrimitive::getPrimitiveType() const {
    return type;
}

Number ScenePrimitive::getPrimitiveParameter1() const {
    return v1;
}

Number ScenePrimitive::getPrimitiveParameter2() const {
    return v2;
}
    
Number ScenePrimitive::getPrimitiveParameter3() const {
    return v3;
}

Number ScenePrimitive::getPrimitiveParameter4() const {
    return v4;
}

Number ScenePrimitive::getPrimitiveParameter5() const {
    return v5;
}

void ScenePrimitive::recreatePrimitive() {
	mesh->clearMesh();
    MeshGeometry geometry;

	switch(type) {
		case TYPE_PLANE:
			geometry.createPlane(v1, v2, v3);
            setLocalBoundingBox(v1, 0.001, v2);
		break;
		case TYPE_VPLANE:
			geometry.createVPlane(v1, v2, v3);
            setLocalBoundingBox(v1, v2, 0.001);
		break;
		case TYPE_BOX:
			geometry.createBox(v1, v2, v3, v4);
            setLocalBoundingBox(v1, v2, v3);
		break;
		case TYPE_SPHERE:
			geometry.createSphere(v1, v2, v3, v4);
            setLocalBoundingBox(v1*2, v1*2, v1*2);
		break;
		case TYPE_CYLINDER:
			geometry.createCylinder(v1, v2, v3, true, v4);
            setLocalBoundingBox(v2*2, v1, v2*2);
		break;
		case TYPE_UNCAPPED_CYLINDER:
			geometry.createCylinder(v1, v2, v3, false, v5);
            setLocalBoundingBox(v2*2, v1, v2*2);
		break;
		case TYPE_CONE:
			geometry.createCone(v1, v2, v3, v4);
            setLocalBoundingBox(v2*2, v1, v2*2);
		break;
		case TYPE_TORUS:
			geometry.createTorus(v1, v2, v3, v4, v5);
            setLocalBoundingBox((v1*2) + (v2*2), v2 * 2, (v1*2) + (v2*2));
		break;
		case TYPE_CIRCLE:
			geometry.createCircle(v1, v2, v3, v4);
            setLocalBoundingBox(v1, v2, 0.001);
		break;
		case TYPE_LINE_CIRCLE:
			geometry.createLineCircle(v1, v2, v3, v4);
            geometry.meshType = MeshGeometry::LINE_LOOP_MESH;
            setLocalBoundingBox(v1, v2, 0.001);
        break;
		case TYPE_ICOSPHERE:
			geometry.createIcosphere(v1, v2);
            setLocalBoundingBox(v1*2, v1*2, v1*2);
        break;
		case TYPE_OCTOSPHERE:
			geometry.createOctosphere(v1, v2);
            setLocalBoundingBox(v1*2, v1*2, v1*2);
        break;
	}
    
    mesh->addSubmesh(geometry);
}

Entity *ScenePrimitive::Clone(bool deepClone, bool ignoreEditorOnly) const {
    ScenePrimitive *newEntity = new ScenePrimitive(type, v1, v2, v3, v4, v5);
    applyClone(newEntity, deepClone, ignoreEditorOnly);
    return newEntity;
}

void ScenePrimitive::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    SceneMesh::applyClone(clone, deepClone, ignoreEditorOnly);    
    ((ScenePrimitive*)clone)->setPrimitiveOptions(type, v1, v2, v3, v4, v5);
}

void ScenePrimitive::setPrimitiveOptions(int type, Number v1, Number v2, Number v3,Number v4,Number v5) {

	this->type = type;
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->v4 = v4;
	this->v5 = v5;

	recreatePrimitive();
}

ScenePrimitive::~ScenePrimitive() {

}
