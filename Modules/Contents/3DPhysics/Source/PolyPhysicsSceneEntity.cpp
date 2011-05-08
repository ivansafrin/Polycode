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

#include "PolyPhysicsSceneEntity.h"

using namespace Polycode;

PhysicsCharacter::PhysicsCharacter(SceneEntity *entity, float mass, float friction, float stepSize) : PhysicsSceneEntity(entity, PhysicsSceneEntity::CHARACTER_CONTROLLER, mass, friction, 1) {	
	ghostObject = new btPairCachingGhostObject();
	
	Vector3 pos = entity->getPosition();	
	btTransform transform;
	transform.setIdentity();		
	transform.setOrigin(btVector3(pos.x,pos.y,pos.z));	
	
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
	Vector3 pos = entity->getPosition();	
	btTransform transform;
	transform.setIdentity();		
	transform.setOrigin(btVector3(pos.x,pos.y,pos.z));
	
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