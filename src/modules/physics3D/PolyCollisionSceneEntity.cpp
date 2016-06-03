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

#include "polycode/modules/physics3D/PolyCollisionSceneEntity.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyEntity.h"
#include "polycode/core/PolySceneMesh.h"
#include "btBulletCollisionCommon.h"

using namespace Polycode;

CollisionEntity::CollisionEntity(Entity *entity, int type, bool compoundChildren, MeshGeometry *collisionGeometry) {
	this->entity = entity;
	shape = NULL;
	
	this->type = type;
	enabled = true; 
	lastPosition = entity->getPosition();	
	
	
	btMatrix3x3 basisA;
	basisA.setIdentity();
	
	collisionObject = new btCollisionObject();
	collisionObject->getWorldTransform().setBasis(basisA);	
	
	if(compoundChildren) {
		 btCompoundShape* compoundShape = new btCompoundShape();
		 
		 for(int i=0; i < entity->getNumChildren(); i++) {
			Entity *child = (Entity*)entity->getChildAtIndex(i);
			btCollisionShape *childShape = createCollisionShape(child, child->collisionShapeType, collisionGeometry);
			btTransform transform;
			
			child->rebuildTransformMatrix();

			btScalar mat[16];		
			Matrix4 ent_mat = child->getTransformMatrix();
	
			for(int i=0; i < 16; i++) {
				mat[i] = ent_mat.ml[i];
			}			
			
			transform.setFromOpenGLMatrix(mat);
			compoundShape->addChildShape(transform, childShape);			
		 }	
		 
		 shape = compoundShape;
	} else {
		shape = createCollisionShape(entity, type, collisionGeometry);
	}
	
	if(shape) {
		collisionObject->setCollisionShape(shape);
	}
	
	collisionObject->setUserPointer((void*)this);
}

btCollisionShape *CollisionEntity::createCollisionShape(Entity *entity, int type, MeshGeometry *collisionGeometry) {
	
	btCollisionShape *collisionShape = NULL;	
	
	Vector3 scale = entity->getCompoundScale();
	Vector3 bBox = entity->getLocalBoundingBox();// * scale;
	
	Number largestSize = bBox.x;
	if(bBox.y > largestSize) {
		largestSize = bBox.y;
	}
	if(bBox.z > largestSize) {
		largestSize = bBox.z;
	}
	
	switch(type) {
		case SHAPE_CAPSULE:
		case CHARACTER_CONTROLLER:
			collisionShape = new btCapsuleShape(bBox.x/2.0f, bBox.y/2.0f);
		break;
		case SHAPE_CONE: {
			Number largest = bBox.x;
			if(bBox.z > largest) {
				largest = bBox.z;
			}
			collisionShape = new btConeShape(largest/2.0f, bBox.y);
			}
		break;
		case SHAPE_CYLINDER:
		{
			collisionShape = new btCylinderShape(btVector3(bBox.x/2.0, bBox.y/2.0f,bBox.z/2.0));
		}
		break;
		case SHAPE_PLANE:
			collisionShape = new btBoxShape(btVector3(bBox.x/2.0f, 0.05,bBox.z/2.0f));
			break;
		case SHAPE_BOX:
			collisionShape = new btBoxShape(btVector3(bBox.x/2.0f, bBox.y/2.0f,bBox.z/2.0f));
			break;
		case SHAPE_SPHERE:
			collisionShape = new btSphereShape(largestSize/2.0f);
			break;
		case SHAPE_MESH:
		{
			if(collisionGeometry) {
				btConvexHullShape *hullShape = new btConvexHullShape();
				for(int i=0; i < collisionGeometry->vertexPositionArray.data.size()-2; i += 3) {
					
					hullShape->addPoint(btVector3((btScalar)collisionGeometry->vertexPositionArray.data[i], (btScalar)collisionGeometry->vertexPositionArray.data[i+1],collisionGeometry->vertexPositionArray.data[i+2]));
				}
				collisionShape = hullShape;
				
			} else {
				Logger::log("Warning: Mesh collision data not supplied to SHAPE_MESH collision entity.\n");
				collisionShape = new btBoxShape(btVector3(bBox.x/2.0f, bBox.y/2.0f,bBox.z/2.0f));
			}
		}
		break;
	}
	
	
	collisionShape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
	
	return collisionShape; 
}

void CollisionEntity::Update() {

	Vector3 pos = entity->getConcatenatedMatrix().getPosition();
	Quaternion quat = entity->getConcatenatedQuat();
	
	btVector3 btPos(pos.x, pos.y, pos.z);
	btQuaternion btQuat(quat.x, quat.y, quat.z, quat.w);
	
	collisionObject->getWorldTransform().setOrigin(btPos);
	collisionObject->getWorldTransform().setRotation(btQuat);
}

Entity *CollisionEntity::getEntity() {
	return entity;
}

CollisionEntity::~CollisionEntity() {
	delete shape;
	delete collisionObject;
}
