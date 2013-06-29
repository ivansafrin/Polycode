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
 
#include "PolyScenePrimitive.h"
#include "PolyMesh.h"

using namespace Polycode;

ScenePrimitive::ScenePrimitive(int type, Number v1, Number v2, Number v3,Number v4,Number v5) : SceneMesh(Mesh::QUAD_MESH) {

	switch(type) {
		case TYPE_PLANE:
			mesh->createPlane(v1,v2);
			bBox.x = v1;
			bBox.y = 0;
			bBox.z = v2;
		break;
		case TYPE_VPLANE:
			mesh->createVPlane(v1,v2);
			bBox.x = v1;
			bBox.y = v2;
			bBox.z = 0;
		break;
		case TYPE_BOX:
			mesh->createBox(v1,v2,v3);
			bBox.x = v1;
			bBox.y = v2;
			bBox.z = v3;
		break;
		case TYPE_SPHERE:
			mesh->createSphere(v1,v2,v3);
			bBox.x = v1*2;
			bBox.y = v1*2;
			bBox.z = v1*2;
		break;
		case TYPE_CYLINDER:
			mesh->createCylinder(v1,v2,v3);
			bBox.x = v2*2;
			bBox.y = v1;
			bBox.z = v2*2;
		break;
		case TYPE_UNCAPPED_CYLINDER:
			mesh->createCylinder(v1,v2,v3, false);
			bBox.x = v2*2;
			bBox.y = v1;
			bBox.z = v2*2;
		break;
		case TYPE_CONE:
			mesh->createCone(v1,v2,v3);
			bBox.x = v2*2;
			bBox.y = v1;
			bBox.z = v2*2;
		break;
		case TYPE_TORUS:
			mesh->createTorus(v1,v2,v3,v4);
			bBox.x = v1*2;
			bBox.y = v2;
			bBox.z = v1*2;
		break;
	}
}

ScenePrimitive::~ScenePrimitive() {

}
