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
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "PolyMatrix4.h"
#include "PolyEntity.h"

using namespace Polycode;


PhysicsVehicle::PhysicsVehicle(Entity *entity, Number mass, Number friction,btDefaultVehicleRaycaster *_rayCaster): PhysicsEntity(entity, PhysicsEntity::SHAPE_BOX, mass, friction, 1), rayCaster(_rayCaster), vehicle(NULL) {
	
}

void PhysicsVehicle::warpVehicle(Vector3 position) {
	btTransform transform;
	transform.setIdentity();		
	transform.setOrigin(btVector3(position.x,position.y,position.z));	
	
	vehicle->getRigidBody()->setCenterOfMassTransform(transform);
	vehicle->getRigidBody()->setLinearVelocity(btVector3(0,0,0));
	vehicle->getRigidBody()->setAngularVelocity(btVector3(0,0,0));

}

void PhysicsVehicle::addWheel(Entity *entity, Vector3 connection, Vector3 direction, Vector3 axle, Number suspentionRestLength, Number wheelRadius, bool isFrontWheel,Number  suspensionStiffness, Number  suspensionDamping, Number suspensionCompression, Number  wheelFriction, Number rollInfluence) {
    entity->ignoreParentMatrix = true;
    entity->setScale(entity->getCompoundScale());
    
    Vector3 vehicleScale = getEntity()->getScale();
    btVector3 conn = btVector3(connection.x * vehicleScale.x, connection.y  * vehicleScale.y, connection.z * vehicleScale.z);
    
	vehicle->addWheel(conn,
					btVector3(direction.x, direction.y, direction.z),
					btVector3(axle.x, axle.y, axle.z),	
					suspentionRestLength,
					wheelRadius, 
					tuning, 
					isFrontWheel);
					
					
					
	PhysicsVehicleWheelInfo wheel_info;
	wheel_info.wheelEntity = entity;
	wheel_info.wheelIndex = wheels.size();
	
			btWheelInfo& wheel = vehicle->getWheelInfo(wheel_info.wheelIndex);
			wheel.m_suspensionStiffness = suspensionStiffness;
			wheel.m_wheelsDampingRelaxation = suspensionDamping;
			wheel.m_wheelsDampingCompression = suspensionCompression;
			wheel.m_frictionSlip = wheelFriction;
			wheel.m_rollInfluence = rollInfluence;
	
	wheels.push_back(wheel_info);
	
}

void PhysicsVehicle::setBrake(Number value, unsigned int wheelIndex) {
	if ( wheelIndex < wheels.size()) {
		vehicle->setBrake(value, wheelIndex);
	}
}

void PhysicsVehicle::setSteeringValue(Number value, unsigned int wheelIndex) {
	if ( wheelIndex < wheels.size()) {
		vehicle->setSteeringValue(value, wheelIndex);
	}
}

void PhysicsVehicle::applyEngineForce(Number force, unsigned int wheelIndex) {
	if ( wheelIndex < wheels.size()) {
		vehicle->applyEngineForce(force, wheelIndex);
	}
}

void PhysicsVehicle::Update() {
	Matrix4 m;
	
	for(int i=0; i < wheels.size(); i++) {	
		PhysicsVehicleWheelInfo wheel_info = wheels[i];
		vehicle->updateWheelTransform(i,true);        
        btVector3 t = vehicle->getWheelInfo(i).m_worldTransform.getOrigin();
        btQuaternion q = vehicle->getWheelInfo(i).m_worldTransform.getRotation();
        wheel_info.wheelEntity->setRotationQuat(q.getW(), q.getX(), q.getY(), q.getZ());
        wheel_info.wheelEntity->setPosition(t.getX(), t.getY(), t.getZ());
	}
	
	PhysicsEntity::Update();
}

PhysicsVehicle::~PhysicsVehicle() {
	delete rayCaster;
	delete vehicle;
	for(int i = 0; i < wheels.size(); i++) {
		delete wheels[i].wheelEntity;
	}
}

PhysicsCharacter::PhysicsCharacter(Entity *entity, Number mass, Number friction, Number stepSize) : PhysicsEntity(entity, PhysicsEntity::CHARACTER_CONTROLLER, mass, friction, 1) {	
	ghostObject = new btPairCachingGhostObject();
	
	Vector3 pos = entity->getPosition();	
	btTransform transform;
	transform.setIdentity();		
	transform.setOrigin(btVector3(pos.x,pos.y,pos.z));	
	
	Quaternion q = entity->getRotationQuat();
	transform.setRotation(btQuaternion(q.x,q.y,q.z,q.w));
	
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

void PhysicsCharacter::warpCharacter(Vector3 position) {
	character->warp(btVector3(position.x, position.y, position.z));
	Update();
}

void PhysicsCharacter::setJumpSpeed(Number jumpSpeed) {
	character->setJumpSpeed(jumpSpeed);
}

void PhysicsCharacter::setFallSpeed(Number fallSpeed) {
	character->setFallSpeed(fallSpeed);
}

void PhysicsCharacter::setMaxJumpHeight(Number maxJumpHeight) {
	character->setMaxJumpHeight(maxJumpHeight);
}

bool PhysicsCharacter::onGround() {
	return character->onGround();
}


void PhysicsCharacter::Update() {
	btVector3 pos = ghostObject->getWorldTransform().getOrigin();
	entity->setPosition(pos.x(), pos.y(), pos.z());
	entity->rebuildTransformMatrix();
	entity->dirtyMatrix(true);
}

PhysicsCharacter::~PhysicsCharacter() {
	delete character;
	delete ghostObject;	
}

PhysicsEntity::PhysicsEntity(Entity *entity, int type, Number mass, Number friction, Number restitution, bool compoundChildren) : CollisionEntity(entity, type, compoundChildren) {

	this->mass = mass;
	btVector3 localInertia(0,0,0);
	Vector3 pos = entity->getPosition();	
	btTransform transform;
	transform.setIdentity();		
	/*
	transform.setOrigin(btVector3(pos.x,pos.y,pos.z));
	Quaternion q = entity->getRotationQuat();
	transform.setRotation(btQuaternion(q.x,q.y,q.z,q.w));
	*/
	entity->rebuildTransformMatrix();
	Matrix4 ent_mat = entity->getConcatenatedMatrix();
	
	btScalar mat[16];
	for(int i=0; i < 16; i++) {
		mat[i] = ent_mat.ml[i];
	}	
	transform.setFromOpenGLMatrix(mat);	
	
	if(mass != 0.0f) {
		shape->calculateLocalInertia(mass,localInertia);
	}	
	
	if(type == CHARACTER_CONTROLLER) {
		rigidBody = NULL;
		myMotionState = NULL;
	} else {	
		myMotionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,shape,localInertia);
		rigidBody = new btRigidBody(rbInfo);
//		rigidBody->setActivationState(ISLAND_SLEEPING);		
		rigidBody->setFriction(friction);
		rigidBody->setRestitution(restitution);
		rigidBody->setUserPointer((void*)this);
	}
}

void PhysicsEntity::setFriction(Number friction) {
		rigidBody->setFriction(friction);
}

void PhysicsEntity::setMass(Number mass) {
	rigidBody->setMassProps(mass, btVector3(0.0, 0.0, 0.0));
}

void PhysicsEntity::Update() {		
	btVector3 t = rigidBody->getWorldTransform().getOrigin();
	btQuaternion q = rigidBody->getOrientation();
	entity->setRotationQuat(q.getW(), q.getX(), q.getY(), q.getZ());
	entity->setPosition(t.getX(), t.getY(), t.getZ());
}

void PhysicsEntity::setRotation(Quaternion quat) {
	btTransform t = rigidBody->getWorldTransform();
	btQuaternion q;
	q.setValue(quat.x, quat.y, quat.z, quat.w);
	t.setRotation(q);
	rigidBody->setWorldTransform(t);
}

void PhysicsEntity::setVelocity(Vector3 velocity) {
	rigidBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}


void PhysicsEntity::setSpin(Vector3 spin) {
	btVector3 angularVel = btVector3(spin.x, spin.y, spin.z);	
	rigidBody->setAngularVelocity(angularVel);
}

Vector3 PhysicsEntity::getVelocity() {
	btVector3 retVec = rigidBody->getLinearVelocity();
	return Vector3(retVec.getX(), retVec.getY(), retVec.getZ());
}

Vector3 PhysicsEntity::getSpin() {
	btVector3 retVec = rigidBody->getAngularVelocity();
	return Vector3(retVec.getX(), retVec.getY(), retVec.getZ());
}

void PhysicsEntity::wakeUp() {
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
}

void PhysicsEntity::applyImpulse(Vector3 direction, Vector3 point) {
	btVector3 imp = btVector3(direction.x, direction.y, direction.z);
	btVector3 pos = btVector3(point.x, point.y, point.z);
		 
	rigidBody->applyImpulse(imp, pos);
}

void PhysicsEntity::warpTo(Vector3 position, bool resetRotation) {
	btTransform transform;
	transform.setIdentity();
	
	if(!resetRotation) {
		Matrix4 ent_mat = entity->getConcatenatedMatrix();	
		btScalar mat[16];
		for(int i=0; i < 16; i++) {
			mat[i] = ent_mat.ml[i];
		}	
		transform.setFromOpenGLMatrix(mat);	
	} else {
        rigidBody->setAngularVelocity(btVector3());
    }
	
	transform.setOrigin(btVector3(position.x,position.y,position.z));
    
	rigidBody->setCenterOfMassTransform(transform);
    
    
}

PhysicsEntity::~PhysicsEntity() {
	delete rigidBody;
	delete myMotionState;	
}
