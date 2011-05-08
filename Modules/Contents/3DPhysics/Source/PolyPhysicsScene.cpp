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
	
	btVector3 worldMin(-100,-100,-100);
	btVector3 worldMax(100,100,100);
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

PhysicsCharacter *PhysicsScene::addCharacterChild(SceneEntity *newEntity,float mass, float friction, float stepSize, int group) {
	addEntity(newEntity);	
	PhysicsCharacter *newPhysicsEntity = new PhysicsCharacter(newEntity, mass, friction, stepSize);
	
	physicsWorld->addCollisionObject(newPhysicsEntity->ghostObject,group, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
	physicsWorld->addAction(newPhysicsEntity->character);
	
	
	physicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(newPhysicsEntity->ghostObject->getBroadphaseHandle(),physicsWorld->getDispatcher());
	
	newPhysicsEntity->character->reset ();
	
	newPhysicsEntity->character->setUseGhostSweepTest(false);
	
	physicsChildren.push_back(newPhysicsEntity);
	return newPhysicsEntity;
	
}

PhysicsSceneEntity *PhysicsScene::trackPhysicsChild(SceneEntity *newEntity, int type, float mass, float friction, float restitution, int group) {
	PhysicsSceneEntity *newPhysicsEntity = new PhysicsSceneEntity(newEntity, type, mass, friction,restitution);
	physicsWorld->addRigidBody(newPhysicsEntity->rigidBody, group, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);	
	//	newPhysicsEntity->rigidBody->setActivationState(ISLAND_SLEEPING);	
	physicsChildren.push_back(newPhysicsEntity);
	return newPhysicsEntity;	
}

PhysicsSceneEntity *PhysicsScene::addPhysicsChild(SceneEntity *newEntity, int type, float mass, float friction, float restitution, int group) {
	addEntity(newEntity);	
	return trackPhysicsChild(newEntity, type, mass, friction, restitution, group);	
}