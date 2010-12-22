/*
 *  PolyCollisionSceneEntity.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 6/17/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
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
	
	btMatrix3x3 basisA;
	basisA.setIdentity();
	collisionObject = new btCollisionObject();
	collisionObject->getWorldTransform().setBasis(basisA);
	
	lastPosition = *entity->getPosition();
	
	shape = NULL;
	
	btBoxShape* box;
	btSphereShape* sphere;	
	SceneMesh *sceneMesh;

	switch(type) {
		case SHAPE_BOX:
			box = new btBoxShape(btVector3(entity->bBox.x/2.0f, entity->bBox.y/2.0f,entity->bBox.z/2.0f));
			collisionObject->setCollisionShape(box);
			shape = box;
		break;
		case SHAPE_SPHERE:
			sphere = new btSphereShape(entity->bBox.x/2.0f);
			collisionObject->setCollisionShape(sphere);
			shape = sphere;			
		break;
		case SHAPE_MESH:
			sceneMesh = dynamic_cast<SceneMesh*>(entity);
			if(sceneMesh != NULL) {
				btTriangleMesh *btMesh = new btTriangleMesh();
				for(int i=0; i < sceneMesh->getMesh()->getPolygonCount(); i++) {
					Polygon *poly = sceneMesh->getMesh()->getPolygon(i);
					btVector3 v0 = btVector3(btScalar(poly->getVertex(0)->x),btScalar(poly->getVertex(0)->y),btScalar(poly->getVertex(0)->z));
					btVector3 v1= btVector3(btScalar(poly->getVertex(1)->x),btScalar(poly->getVertex(1)->y),btScalar(poly->getVertex(1)->z));
					btVector3 v2= btVector3(btScalar(poly->getVertex(2)->x),btScalar(poly->getVertex(2)->y),btScalar(poly->getVertex(2)->z));					
					btMesh->addTriangle(v2,v1,v0);
				}
				btBvhTriangleMeshShape *concaveShape = new btBvhTriangleMeshShape(btMesh, true);
				collisionObject->setCollisionShape(concaveShape);
			} else {
				Logger::log("Tried to make a mesh collision object from a non-mesh\n");
				box = new btBoxShape(btVector3(entity->bBox.x/2.0f, entity->bBox.y/2.0f,entity->bBox.z/2.0f));			
				collisionObject->setCollisionShape(box);	
				shape = box;				
			}			
		break;
		case SHAPE_TERRAIN:			
			/*
			Terrain *terrain = dynamic_cast<Terrain*>(entity);
			if(terrain != NULL) {
//				btHeightfieldTerrainShape *hf = new btHeightfieldTerrainShape(ter
				btTriangleMesh *btMesh = new btTriangleMesh();
				for(int i=0; i < terrain->getMesh()->getPolygonCount(); i++) {
					Polygon *poly = terrain->getMesh()->getPolygon(i);
					btVector3 v0 = btVector3(btScalar(poly->getVertex(0)->x),btScalar(poly->getVertex(0)->y),btScalar(poly->getVertex(0)->z));
					btVector3 v1= btVector3(btScalar(poly->getVertex(1)->x),btScalar(poly->getVertex(1)->y),btScalar(poly->getVertex(1)->z));
					btVector3 v2= btVector3(btScalar(poly->getVertex(2)->x),btScalar(poly->getVertex(2)->y),btScalar(poly->getVertex(2)->z));					
					btMesh->addTriangle(v2,v1,v0);
				}
				btBvhTriangleMeshShape *concaveShape = new btBvhTriangleMeshShape(btMesh, true);
				collisionObject->setCollisionShape(concaveShape);
			} else {
				Logger::log("Tried to make a terrain collision object from a non-terrain\n");
				box = new btBoxShape(btVector3(entity->bBox.x/2.0f, entity->bBox.y/2.0f,entity->bBox.z/2.0f));			
				collisionObject->setCollisionShape(box);	
				shape = box;				
			}
			 */
		break;
	}
	gVelocity.set(0,0,0);
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
	collisionObject->getWorldTransform().setFromOpenGLMatrix(sceneEntity->getConcatenatedMatrix().ml);

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