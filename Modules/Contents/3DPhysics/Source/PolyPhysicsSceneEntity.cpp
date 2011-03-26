
/*
 *  PolyPhysicsSceneEntity.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 6/17/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyPhysicsSceneEntity.h"

using namespace Polycode;

PhysicsCharacter::PhysicsCharacter(SceneEntity *entity, float mass, float friction, float stepSize) : PhysicsSceneEntity(entity, PhysicsSceneEntity::CHARACTER_CONTROLLER, mass, friction, 1) {	
	ghostObject = new btPairCachingGhostObject();
	
	Vector3 *pos = entity->getPosition();	
	btTransform transform;
	transform.setIdentity();		
	transform.setOrigin(btVector3(pos->x,pos->y,pos->z));	
	
	ghostObject->setWorldTransform(transform);	
	ghostObject->setCollisionShape (shape);
	
	ghostObject->setFriction(friction);	
	
	ghostObject->setCollisionFlags (btCollisionObject::CF_CHARACTER_OBJECT);	
	character = new btKinematicCharacterController (ghostObject,convexShape,btScalar(stepSize));			
	
}


void PhysicsCharacter::setWalkDirection(Vector3 direction) {
	character->setWalkDirection(btVector3(direction.x, direction.y, direction.z));	
}

void PhysicsCharacter::jump() {
	character->jump();	
}

void PhysicsCharacter::Update() {
	btVector3 pos = ghostObject->getWorldTransform().getOrigin();
	sceneEntity->setPosition(pos.x(), pos.y(), pos.z());
//	sceneEntity->rebuildTransformMatrix();
	sceneEntity->dirtyMatrix(true);
}

PhysicsCharacter::~PhysicsCharacter() {
	
}

PhysicsSceneEntity::PhysicsSceneEntity(SceneEntity *entity, int type, float mass, float friction, float restitution) : CollisionSceneEntity(entity, false, type) {

	this->mass = mass;
	btVector3 localInertia(0,0,0);
	Vector3 *pos = entity->getPosition();	
	btTransform transform;
	transform.setIdentity();		
	transform.setOrigin(btVector3(pos->x,pos->y,pos->z));
	
	if(mass != 0.0f) {
		shape->calculateLocalInertia(mass,localInertia);
	}	
	
	if(type == CHARACTER_CONTROLLER) {
		
	} else {	
		btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		rigidBody = new btRigidBody(rbInfo);
//		rigidBody->setActivationState(ISLAND_SLEEPING);		
		rigidBody->setFriction(friction);
		rigidBody->setRestitution(restitution);
	}
}

void PhysicsSceneEntity::Update() {		
	Matrix4 m;
		
	btScalar* mat = (btScalar*) malloc(sizeof(btScalar) * 16);				
		
	rigidBody->getWorldTransform().getOpenGLMatrix(mat);
	for(int i=0; i < 16; i++) {
		m.ml[i] = mat[i];
	}
	
	free(mat);
		
	sceneEntity->setTransformByMatrixPure(m);			
}

SceneEntity *PhysicsSceneEntity::getSceneEntity() {
	return sceneEntity;
}

PhysicsSceneEntity::~PhysicsSceneEntity() {
	
}