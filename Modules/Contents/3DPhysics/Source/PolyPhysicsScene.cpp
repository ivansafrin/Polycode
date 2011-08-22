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
	
	btDbvtBroadphase *broadPhase = new btDbvtBroadphase();
	
	physicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadPhase,solver,collisionConfiguration);
	
//	physicsWorld->getSolverInfo().m_solverMode |= SOLVER_RANDMIZE_ORDER;
	physicsWorld->setGravity(btVector3(0,-10,0));
	
	
	sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	
	world = physicsWorld;
}

void PhysicsScene::Update() {
	
	for(int i=0; i < physicsChildren.size(); i++) {
//		if(physicsChildren[i]->enabled)
			physicsChildren[i]->Update();
	}
	
	
	Number elapsed = CoreServices::getInstance()->getCore()->getElapsed();
	physicsWorld->stepSimulation(elapsed);	
	CollisionScene::Update();
	
}

PhysicsCharacter *PhysicsScene::addCharacterChild(SceneEntity *newEntity,Number mass, Number friction, Number stepSize, int group) {
	addEntity(newEntity);	
	PhysicsCharacter *newPhysicsEntity = new PhysicsCharacter(newEntity, mass, friction, stepSize);
	
	physicsWorld->addCollisionObject(newPhysicsEntity->ghostObject,group, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
	physicsWorld->addAction(newPhysicsEntity->character);
	
	
	physicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(newPhysicsEntity->ghostObject->getBroadphaseHandle(),physicsWorld->getDispatcher());
	
	newPhysicsEntity->character->reset ();
	
	newPhysicsEntity->character->setUseGhostSweepTest(false);
	
	physicsChildren.push_back(newPhysicsEntity);
	collisionChildren.push_back(newPhysicsEntity);
	return newPhysicsEntity;
	
}

void PhysicsScene::removeCharacterChild(PhysicsCharacter *character) {
	physicsWorld->removeAction(character->character);

	physicsWorld->removeCollisionObject(character->ghostObject);


		for(int i=0; i < physicsChildren.size(); i++) {
			if(physicsChildren[i] == character) {
				physicsChildren.erase(physicsChildren.begin()+i);
			}
		}
		for(int i=0; i < collisionChildren.size(); i++) {
			if(collisionChildren[i] == character) {
				collisionChildren.erase(collisionChildren.begin()+i);
			}
		}		
	
}


PhysicsVehicle *PhysicsScene::addVehicleChild(SceneEntity *newEntity, Number mass, Number friction, int group) {
	addEntity(newEntity);		
	
	btDefaultVehicleRaycaster *m_vehicleRayCaster = new btDefaultVehicleRaycaster(physicsWorld);
	
	PhysicsVehicle *newPhysicsEntity = new PhysicsVehicle(newEntity, mass, friction,m_vehicleRayCaster);		
	physicsWorld->addRigidBody(newPhysicsEntity->rigidBody, group, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);	
		
	newPhysicsEntity->vehicle = new btRaycastVehicle(newPhysicsEntity->tuning,newPhysicsEntity->rigidBody,m_vehicleRayCaster);	
	
	newPhysicsEntity->rigidBody->setActivationState(DISABLE_DEACTIVATION);
	
		
	int rightIndex = 0; 
		int upIndex = 1; 
		int forwardIndex = 2;
			
	physicsWorld->addVehicle(newPhysicsEntity->vehicle);
	
	newPhysicsEntity->vehicle->setCoordinateSystem(rightIndex,upIndex,forwardIndex);

	newPhysicsEntity->vehicle->resetSuspension();

	physicsChildren.push_back(newPhysicsEntity);
	collisionChildren.push_back(newPhysicsEntity);
		
	return newPhysicsEntity;
}

void PhysicsScene::removePhysicsChild(SceneEntity *entity) {
	PhysicsSceneEntity *ent = getPhysicsEntityBySceneEntity(entity);
	if(ent) {
		physicsWorld->removeRigidBody(ent->rigidBody);
		physicsWorld->removeCollisionObject(ent->collisionObject);
		for(int i=0; i < physicsChildren.size(); i++) {
			if(physicsChildren[i] == ent) {
				physicsChildren.erase(physicsChildren.begin()+i);
			}
		}
		for(int i=0; i < collisionChildren.size(); i++) {
			if(collisionChildren[i] == ent) {
				collisionChildren.erase(collisionChildren.begin()+i);
			}
		}		
	}
	delete ent;
}

PhysicsSceneEntity *PhysicsScene::getPhysicsEntityBySceneEntity(SceneEntity *entity) {
	PhysicsSceneEntity *retEntity = NULL;
	for(int i=0; i < physicsChildren.size(); i++) {
		if(physicsChildren[i]->getSceneEntity() == entity) {
			retEntity = physicsChildren[i];
		}	
	}
	return retEntity;
}

PhysicsSceneEntity *PhysicsScene::trackPhysicsChild(SceneEntity *newEntity, int type, Number mass, Number friction, Number restitution, int group) {
	PhysicsSceneEntity *newPhysicsEntity = new PhysicsSceneEntity(newEntity, type, mass, friction,restitution);
	physicsWorld->addRigidBody(newPhysicsEntity->rigidBody, group,  btBroadphaseProxy::AllFilter); //btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);	
	world->addCollisionObject(newPhysicsEntity->collisionObject, group);	
	//	newPhysicsEntity->rigidBody->setActivationState(ISLAND_SLEEPING);	
	physicsChildren.push_back(newPhysicsEntity);
	collisionChildren.push_back(newPhysicsEntity);	
	return newPhysicsEntity;	
}

PhysicsSceneEntity *PhysicsScene::addPhysicsChild(SceneEntity *newEntity, int type, Number mass, Number friction, Number restitution, int group) {
	addEntity(newEntity);	
	return trackPhysicsChild(newEntity, type, mass, friction, restitution, group);	
}