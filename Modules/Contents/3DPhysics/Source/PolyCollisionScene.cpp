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

#include "PolyCollisionScene.h"
#include "PolyCollisionSceneEntity.h"
#include "PolyEntity.h"

using namespace Polycode;

CollisionResult::CollisionResult() : collided(false),colNormal(),colDist(0),setOldPosition(false),newPos(){

}

CollisionResult::~CollisionResult() {

}

RayTestResult::RayTestResult() : entity(NULL),normal(),position(){

}

RayTestResult::~RayTestResult() {

}

RayTestResultMultiple::RayTestResultMultiple() {

}

RayTestResultMultiple::~RayTestResultMultiple() {
	clearResults();
}

void RayTestResultMultiple::addResult(RayTestResult *result){
	results.push_back(result);
}

RayTestResult *RayTestResultMultiple::getResult(int index) {
	if(index < results.size())
		return results[index];
	else
		return NULL;
}

unsigned int RayTestResultMultiple::getResultCount() {
	return results.size();
}

void RayTestResultMultiple::clearResults() {
	for(int i=0; i < results.size(); i++ )
		delete results[i];
	results.clear();
}

CollisionScene::CollisionScene(Vector3 size, bool virtualScene, bool deferInitCollision) : Scene(Scene::SCENE_3D, virtualScene), world(NULL), collisionConfiguration(NULL), dispatcher(NULL), axisSweep(NULL) {
	if(!deferInitCollision) {
		initCollisionScene(size);
	}
}

void CollisionScene::initCollisionScene(Vector3 size) {
	
	btVector3	worldAabbMin(-size.x * 0.5, -size.y * 0.5, -size.z * 0.5);
	btVector3	worldAabbMax(size.x * 0.5, size.y * 0.5, size.z * 0.5);
	
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	//	dispatcher->setNearCallback(customNearCallback);
	axisSweep = new btAxisSweep3(worldAabbMin,worldAabbMax);
	world = new btCollisionWorld(dispatcher,axisSweep,collisionConfiguration);	
}

void CollisionScene::fixedUpdate() {
	
	for(int i=0; i < collisionChildren.size(); i++) {
		if(collisionChildren[i]->enabled)
			collisionChildren[i]->Update();
	}
	
	world->performDiscreteCollisionDetection();	
	
	for(int i=0; i < collisionChildren.size(); i++) {
		if(collisionChildren[i]->enabled)		
			collisionChildren[i]->lastPosition = collisionChildren[i]->getEntity()->getPosition();
	}
	Scene::fixedUpdate();
}

void CollisionScene::enableCollision(Entity *entity, bool val) {
	CollisionEntity *cEnt = getCollisionByScreenEntity(entity);
	if(cEnt) {
		cEnt->enabled = val;
	}
}

void CollisionScene::adjustForCollision(CollisionEntity *collisionEntity) {
	CollisionResult result;
//	Number elapsed = CoreServices::getInstance()->getCore()->getElapsed();
	result.collided = false;
	for(int i=0; i < collisionChildren.size(); i++) {
		if(collisionChildren[i] != collisionEntity) {
			result = testCollisionOnCollisionChild(collisionEntity, collisionChildren[i]);
			if(result.collided) {
				if(result.setOldPosition) {
					collisionEntity->getEntity()->setPosition(result.newPos);
				} else {
					collisionEntity->getEntity()->Translate(result.colNormal.x*result.colDist, result.colNormal.y*result.colDist, result.colNormal.z*result.colDist);
				}
			}
		}
	}
}	

CollisionEntity *CollisionScene::getCollisionByScreenEntity(Entity *ent) {
	for(int i=0; i<collisionChildren.size();i++) {
		if(collisionChildren[i]->getEntity() == ent)
			return collisionChildren[i];
	}	
	return NULL;

}

bool CollisionScene::isColliding(Entity *ent1) {
    CollisionEntity *cEnt1 = getCollisionByScreenEntity(ent1);
    if(cEnt1) {
        int numManifolds = world->getDispatcher()->getNumManifolds();
        for (int i=0;i<numManifolds;i++)
        {
            btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
          
            btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
            btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
            
            if(obA == cEnt1->collisionObject || obB == cEnt1->collisionObject) {
                return true;
            }
        }
    } else {
        return false;
    }
    return false;
}

CollisionResult CollisionScene::testCollisionOnCollisionChild_Convex(CollisionEntity *cEnt1, CollisionEntity *cEnt2) {
	CollisionResult result;
	result.collided = false;
	result.setOldPosition = false;
	
	Vector3 collNormal;
	result.colNormal.set(0,0,0);									
	result.colDist = 0; 	
	
	int numAdds = 0;
	
	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
 		if((obA == cEnt1->collisionObject && obB == cEnt2->collisionObject) ||
		   (obA == cEnt2->collisionObject && obB == cEnt1->collisionObject)) {
//			contactManifold->refreshContactPoints(obA->getWorldTransform(), obB->getWorldTransform());
			if(contactManifold->getNumContacts() > 0) {
				for(int j=0; j < contactManifold->getNumContacts(); j++) {
					if(contactManifold->getContactPoint(j).getDistance() <= btScalar(0.0)) {
						btVector3 vec = contactManifold->getContactPoint(j).m_normalWorldOnB;
						result.colNormal += Vector3(vec.getX(), vec.getY(), vec.getZ());	
						result.colDist += contactManifold->getContactPoint(j).getDistance(); 
						numAdds++;
					}
				}
				
				//				btVector3 vec = contactManifold->getContactPoint(0).m_normalWorldOnB;
				//				result.colNormal.set(vec.getX(), vec.getY(), vec.getZ());
				//				result.colDist = contactManifold->getContactPoint(0).getDistance(); 
				
				result.collided = true;
			}
		}
	}
	
	if(numAdds > 0) {
		result.colNormal = result.colNormal / (Number)numAdds;
		//		result.colNormal = Vector3(0,1,0);
		//		result.colNormal.Normalize();
		result.colDist  = result.colDist / (Number)numAdds;
	}
	
	return result;
	//	return cEnt1->collisionObject->checkCollideWith(cEnt2->collisionObject);
}

RayTestResult CollisionScene::getFirstEntityInRay(const Vector3 &origin,  const Vector3 &dest) {

	RayTestResult ret;
	ret.entity = NULL;
	
	btVector3 fromVec(origin.x, origin.y, origin.z);
	btVector3 toVec(dest.x, dest.y, dest.z);
	
	btCollisionWorld::ClosestRayResultCallback cb(fromVec, toVec);
	world->rayTest (fromVec, toVec, cb);	
	
	if (cb.hasHit ()) {
		CollisionEntity *retEnt = getCollisionEntityByObject(cb.m_collisionObject);
		if(retEnt) {
			ret.entity = retEnt->getEntity();
			ret.position = Vector3(cb.m_hitPointWorld.getX(), cb.m_hitPointWorld.getY(), cb.m_hitPointWorld.getZ());
			ret.normal = Vector3(cb.m_hitNormalWorld.getX(), cb.m_hitNormalWorld.getY(), cb.m_hitNormalWorld.getZ());
			ret.fraction = cb.m_closestHitFraction;
			return ret;
		}
	}
	
	return ret;
}

RayTestResultMultiple *CollisionScene::getAllEntitiesInRay(const Vector3 &origin,  const Vector3 &dest, int group, int mask) {
	RayTestResultMultiple *ret = new RayTestResultMultiple();
	ret->clearResults();

	btVector3 fromVec(origin.x, origin.y, origin.z);
	btVector3 toVec(dest.x, dest.y, dest.z);

	btCollisionWorld::AllHitsRayResultCallback cb(fromVec, toVec);
	cb.m_collisionFilterGroup = group;
	cb.m_collisionFilterMask = mask;

	world->rayTest(fromVec, toVec, cb);

	if(cb.hasHit()) {
		for(int i=0; i < cb.m_collisionObjects.size(); i++) {
			CollisionEntity *retEnt = getCollisionEntityByObject(cb.m_collisionObjects[i]);
			if(retEnt) {
				RayTestResult *ray = new RayTestResult;
				ray->entity = retEnt->getEntity();
				ray->fraction = cb.m_hitFractions[i];
				ray->normal= Vector3(cb.m_hitNormalWorld[i].getX(), cb.m_hitNormalWorld[i].getY(), cb.m_hitNormalWorld[i].getZ());
				ray->position= Vector3(cb.m_hitPointWorld[i].getX(), cb.m_hitPointWorld[i].getY(), cb.m_hitPointWorld[i].getZ());
				ret->addResult(ray);
			}
		}
	}
	return ret;
}

CollisionEntity *CollisionScene::getCollisionEntityByObject(btCollisionObject *collisionObject) {
	return (CollisionEntity*)collisionObject->getUserPointer();
}


CollisionResult CollisionScene::testCollisionOnCollisionChild(CollisionEntity *cEnt1, CollisionEntity *cEnt2) {
		return testCollisionOnCollisionChild_Convex(cEnt1, cEnt2);
}

CollisionResult CollisionScene::testCollision(Entity *ent1, Entity *ent2) {
	CollisionEntity *cEnt1 = getCollisionByScreenEntity(ent1);
	CollisionEntity *cEnt2 = getCollisionByScreenEntity(ent2);
	CollisionResult result;
	result.collided = false;
	if(cEnt1 == NULL || cEnt2 == NULL)
		return result;
	return testCollisionOnCollisionChild(cEnt1, cEnt2);
}

CollisionScene::~CollisionScene() {
	for(int i=0; i < collisionChildren.size(); i++) {
		delete collisionChildren[i];
	}
	delete world;
	delete axisSweep;
	delete dispatcher;
	delete collisionConfiguration;
}

void CollisionScene::removeCollision(Entity *entity) {
	CollisionEntity *cEnt = getCollisionByScreenEntity(entity);
	if(cEnt) {
		world->removeCollisionObject(cEnt->collisionObject);
		for(int i=0; i < collisionChildren.size(); i++) {
			if(collisionChildren[i] == cEnt) {
				std::vector<CollisionEntity*>::iterator target = collisionChildren.begin()+i;
				delete *target;
				collisionChildren.erase(target);
			}
		}
	}

}

void CollisionScene::removeEntity(Entity *entity) {
	if(getCollisionByScreenEntity(entity)) {
		removeCollision(entity);	
	}
	Scene::removeEntity(entity);
}

CollisionEntity *CollisionScene::trackCollision(Entity *newEntity, int type, int group, int mask) {
	CollisionEntity *newCollisionEntity = new CollisionEntity(newEntity, type);

//	if(type == CollisionEntity::CHARACTER_CONTROLLER) {
//		world->addCollisionObject(newCollisionEntity->collisionObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);		
//	} else {
//		newCollisionEntity->collisionObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
		world->addCollisionObject(newCollisionEntity->collisionObject, group, mask);
//	}
	
	collisionChildren.push_back(newCollisionEntity);
	return newCollisionEntity;
}

CollisionEntity *CollisionScene::addCollisionChild(Entity *newEntity, int type, int group, int mask) {
	addEntity(newEntity);
	return trackCollision(newEntity, type, group, mask);

}
