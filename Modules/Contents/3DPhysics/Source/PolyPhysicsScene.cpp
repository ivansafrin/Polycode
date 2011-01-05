/*
 *  PolyPhysicsScene.cpp
 *  Modules
 *
 *  Created by Ivan Safrin on 12/22/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */

#include "PolyPhysicsScene.h"

PhysicsScene::PhysicsScene() : CollisionScene() {
	initPhysicsScene();	
}

PhysicsScene::~PhysicsScene() {
	
}

void PhysicsScene::initPhysicsScene() {
		
	
 btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
//	btDbvtBroadphase* broadphase = new btDbvtBroadphase();
	
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);	
	
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
	
	btVector3 worldMin(-1000,-1000,-1000);
	btVector3 worldMax(1000,1000,1000);
	btAxisSweep3* sweepBP = new btAxisSweep3(worldMin,worldMax);	
	
	physicsWorld = new btDiscreteDynamicsWorld(dispatcher,sweepBP,solver,collisionConfiguration);
	
	physicsWorld->getSolverInfo().m_solverMode |= SOLVER_RANDMIZE_ORDER;
	physicsWorld->setGravity(btVector3(0,-10,0));
	
	
	sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	
	world = physicsWorld;
}

void PhysicsScene::Update() {
	
	for(int i=0; i < physicsChildren.size(); i++) {
//		if(physicsChildren[i]->enabled)
			physicsChildren[i]->Update();
	}
	
	
	float elapsed = CoreServices::getInstance()->getCore()->getElapsed();
	physicsWorld->stepSimulation(elapsed);	

	
	CollisionScene::Update();
	
}

PhysicsCharacter *PhysicsScene::addCharacterChild(SceneEntity *newEntity,float mass, float friction, float stepSize) {
	addEntity(newEntity);	
	PhysicsCharacter *newPhysicsEntity = new PhysicsCharacter(newEntity, mass, friction, stepSize);
	
	physicsWorld->addCollisionObject(newPhysicsEntity->ghostObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
	physicsWorld->addAction(newPhysicsEntity->character);
	
	
	physicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(newPhysicsEntity->ghostObject->getBroadphaseHandle(),physicsWorld->getDispatcher());
	
	newPhysicsEntity->character->reset ();
	
	newPhysicsEntity->character->setUseGhostSweepTest(false);
	
	physicsChildren.push_back(newPhysicsEntity);
	return newPhysicsEntity;
	
}

PhysicsSceneEntity *PhysicsScene::addPhysicsChild(SceneEntity *newEntity, int type, float mass, float friction, float restitution) {
	addEntity(newEntity);	
	PhysicsSceneEntity *newPhysicsEntity = new PhysicsSceneEntity(newEntity, type, mass, friction,restitution);
	physicsWorld->addRigidBody(newPhysicsEntity->rigidBody);	
	newPhysicsEntity->rigidBody->setActivationState(ISLAND_SLEEPING);	
	physicsChildren.push_back(newPhysicsEntity);
	return newPhysicsEntity;
	
}