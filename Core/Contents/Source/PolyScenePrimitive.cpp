/*
 *  PolyScenePrimitive.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 6/15/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
 
#include "PolyScenePrimitive.h"

using namespace Polycode;

ScenePrimitive::ScenePrimitive(int type, float v1, float v2, float v3) : SceneMesh(Mesh::QUAD_MESH) {

	switch(type) {
		case TYPE_PLANE:
			mesh->createPlane(v1,v2);
		break;
		case TYPE_BOX:
			mesh->createBox(v1,v2,v3);
			bBox.x = v1;
			bBox.y = v2;
			bBox.z = v3;			
		break;
		case TYPE_SPHERE:
			mesh->createSphere(v1,v2,v3);
		break;
	}
}

ScenePrimitive::~ScenePrimitive() {

}