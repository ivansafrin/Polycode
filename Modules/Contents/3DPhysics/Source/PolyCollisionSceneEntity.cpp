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

using namespace Polycode;

CollisionSceneEntity::CollisionSceneEntity(SceneEntity *entity, bool autoCollide, int type) {
	gravityEnabled = false;
	this->autoCollide = autoCollide;
	sceneEntity = entity;
	gravityVector.y = -1.0f;
	
	this->type = type;
	enabled = true;
	
	gravityStrength = 5.0f;
	lastPosition = entity->getPosition();	
	
	
	btMatrix3x3 basisA;
	basisA.setIdentity();
	
	collisionObject = new btCollisionObject();
	collisionObject->getWorldTransform().setBasis(basisA);
	

	shape = createCollisionShape(entity, type);;
	if(shape) {
		collisionObject->setCollisionShape(shape);
	}	
	
//	if(type == SHAPE_MESH) {		
//		concaveShape = dynamic_cast<btConcaveShape*>(shape);
//	} else {
		convexShape	= dynamic_cast<btConvexShape*>(shape);		
//	}
		
	gVelocity.set(0,0,0);
}

btCollisionShape *CollisionSceneEntity::createCollisionShape(SceneEntity *entity, int type) {
	
	btCollisionShape *collisionShape = NULL;	
	
	switch(type) {
		case SHAPE_CAPSULE:
		case CHARACTER_CONTROLLER:
			collisionShape = new btCapsuleShape(entity->bBox.x/2.0f, entity->bBox.y/2.0f);			
		break;
		case SHAPE_PLANE:
			collisionShape = new btBoxShape(btVector3(entity->bBox.x/2.0f, entity->bBox.y/2.0f,0.1f));			
			break;
		case SHAPE_BOX:
			collisionShape = new btBoxShape(btVector3(entity->bBox.x/2.0f, entity->bBox.y/2.0f,entity->bBox.z/2.0f));			
			break;
		case SHAPE_SPHERE:
			collisionShape = new btSphereShape(entity->bBox.x/2.0f);
			break;
		case SHAPE_MESH:
		{
			SceneMesh* sceneMesh = dynamic_cast<SceneMesh*>(entity);
			if(sceneMesh != NULL) {
				/*
				btTriangleMesh *btMesh = new btTriangleMesh();
				for(int i=0; i < sceneMesh->getMesh()->getPolygonCount(); i++) {
					Polygon *poly = sceneMesh->getMesh()->getPolygon(i);
					btVector3 v0 = btVector3(btScalar(poly->getVertex(0)->x),btScalar(poly->getVertex(0)->y),btScalar(poly->getVertex(0)->z));
					btVector3 v1= btVector3(btScalar(poly->getVertex(1)->x),btScalar(poly->getVertex(1)->y),btScalar(poly->getVertex(1)->z));
					btVector3 v2= btVector3(btScalar(poly->getVertex(2)->x),btScalar(poly->getVertex(2)->y),btScalar(poly->getVertex(2)->z));					
					btMesh->addTriangle(v2,v1,v0);
				}
				collisionShape = new btBvhTriangleMeshShape(btMesh, true);
				*/
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
	
//	lastPosition = *getSceneEntity()->getPosition();	
	if(gravityEnabled) {	
		float elapsed = CoreServices::getInstance()->getCore()->getElapsed();
		Vector3 elapsedGrav = gravityVector;
		elapsedGrav * elapsed * gravityStrength;
		gVelocity = gVelocity+(elapsedGrav);
		sceneEntity->Translate(gVelocity.x * elapsed, gVelocity.y * elapsed,gVelocity.z * elapsed);
		sceneEntity->rebuildTransformMatrix();
	}

	btQuaternion orn;
//	collisionObject->getCollisionShape()->setLocalScaling
	collisionObject->getWorldTransform().setFromOpenGLMatrix((float*)sceneEntity->getConcatenatedMatrix().ml);

/*	
	float rads = PI/180.0f;
	orn.setEuler(sceneEntity->getCombinedYaw()*rads,sceneEntity->getCombinedPitch()*rads,sceneEntity->getCombinedRoll()*rads);
	collisionObject->getWorldTransform().setRotation(orn);
	collisionObject->getWorldTransform().setOrigin(btVector3(sceneEntity->getCombinedPosition().x, sceneEntity->getCombinedPosition().y, sceneEntity->getCombinedPosition().z));
*/	
}

SceneEntity *CollisionSceneEntity::getSceneEntity() {
	return sceneEntity;
}

CollisionSceneEntity::~CollisionSceneEntity() {

}