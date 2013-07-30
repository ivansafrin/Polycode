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

#include "PolyCollisionSceneEntity.h"
#include "PolyLogger.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolySceneEntity.h"
#include "PolySceneMesh.h"
#include "btBulletCollisionCommon.h"

using namespace Polycode;

CollisionSceneEntity::CollisionSceneEntity(SceneEntity *entity, int type, bool compoundChildren) {
	sceneEntity = entity;
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
			SceneEntity *child = (SceneEntity*)entity->getChildAtIndex(i);
			btCollisionShape *childShape = createCollisionShape(child, child->collisionShapeType);
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
		shape = createCollisionShape(entity, type);	
	}
	
	if(shape) {
		collisionObject->setCollisionShape(shape);
	}
	
	collisionObject->setUserPointer((void*)this);
	
//	if(type == SHAPE_MESH) {		
//		concaveShape = dynamic_cast<btConcaveShape*>(shape);
//	} else {
		convexShape	= dynamic_cast<btConvexShape*>(shape);		
//	}		
}

btCollisionShape *CollisionSceneEntity::createCollisionShape(SceneEntity *entity, int type) {
	
	btCollisionShape *collisionShape = NULL;	
	
	Vector3 entityScale = entity->getScale();
	Number largestScale = entityScale.x;
	if(entityScale.y > largestScale)
		largestScale = entityScale.y;
	if(entityScale.z > largestScale)
		largestScale = entityScale.z;

	
	switch(type) {
		case SHAPE_CAPSULE:
		case CHARACTER_CONTROLLER:
			collisionShape = new btCapsuleShape(entity->bBox.x/2.0f, entity->bBox.y/2.0f);			
		break;
		case SHAPE_CONE: {
			Number largest = entity->bBox.x;
			if(entity->bBox.z > largest) {
				largest = entity->bBox.z;
			}
			collisionShape = new btConeShape(largest/2.0f, entity->bBox.y);					
			}
		break;
		case SHAPE_CYLINDER:
		{
			collisionShape = new btCylinderShape(btVector3(entity->bBox.x/2.0, entity->bBox.y/2.0f,entity->bBox.z/2.0));
		}
		break;
		case SHAPE_PLANE:
			collisionShape = new btBoxShape(btVector3(entity->bBox.x/2.0f, 0.05,entity->bBox.z/2.0f));			
			break;
		case SHAPE_BOX:
			collisionShape = new btBoxShape(btVector3(entity->bBox.x/2.0f*entityScale.x, entity->bBox.y/2.0f*entityScale.y,entity->bBox.z/2.0f*entityScale.z));			
			break;
		case SHAPE_SPHERE:
			collisionShape = new btSphereShape(entity->bBox.x/2.0f*largestScale);
			break;
		case SHAPE_MESH:
		{
			SceneMesh* sceneMesh = dynamic_cast<SceneMesh*>(entity);
			if(sceneMesh != NULL) {
				btConvexHullShape *hullShape = new btConvexHullShape();
				for(int i=0; i < sceneMesh->getMesh()->getPolygonCount(); i++) {
					Polygon *poly = sceneMesh->getMesh()->getPolygon(i);
					for(int j=0; j < poly->getVertexCount(); j++) {					
						hullShape->addPoint(btVector3((btScalar)poly->getVertex(j)->x, (btScalar)poly->getVertex(j)->y,(btScalar)poly->getVertex(j)->z));
					}
				}				
				collisionShape = hullShape;
				
			} else {
				Logger::log("Tried to make a mesh collision object from a non-mesh\n");
				collisionShape = new btBoxShape(btVector3(entity->bBox.x/2.0f, entity->bBox.y/2.0f,entity->bBox.z/2.0f));			
			}
		}
		break;
	}	
	return collisionShape; 
}

void CollisionSceneEntity::Update() {	
	sceneEntity->rebuildTransformMatrix();

	btScalar mat[16];		
	Matrix4 ent_mat = sceneEntity->getConcatenatedMatrix();
	
	for(int i=0; i < 16; i++) {
			mat[i] = ent_mat.ml[i];
	}			

	collisionObject->getWorldTransform().setFromOpenGLMatrix(mat);
}

SceneEntity *CollisionSceneEntity::getSceneEntity() {
	return sceneEntity;
}

CollisionSceneEntity::~CollisionSceneEntity() {
	delete shape;
	delete collisionObject;
}
