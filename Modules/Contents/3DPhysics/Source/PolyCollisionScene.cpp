/*
 *  PolyCollisionScene.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 6/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyCollisionScene.h"

using namespace Polycode;

CollisionScene::CollisionScene() : GenericScene() {
	initCollisionScene();
}

CollisionScene::CollisionScene(bool virtualScene) : GenericScene(virtualScene) { 
	initCollisionScene();
}

void CollisionScene::initCollisionScene() {
	
	btVector3	worldAabbMin(-1000,-1000,-1000);
	btVector3	worldAabbMax(1000,1000,1000);
	
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	//	dispatcher->setNearCallback(customNearCallback);
	btAxisSweep3*	broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax);
	world = new btCollisionWorld(dispatcher,broadphase,collisionConfiguration);	
}

void CollisionScene::Update() {
	
	for(int i=0; i < collisionChildren.size(); i++) {
		if(collisionChildren[i]->enabled)
			collisionChildren[i]->Update();
	}
	
	world->performDiscreteCollisionDetection();	
	for(int i=0; i < collisionChildren.size(); i++) {
		if(collisionChildren[i]->enabled) {		
			if(collisionChildren[i]->autoCollide) {
				adjustForCollision(collisionChildren[i]);
			}	
		}
	}
	
	for(int i=0; i < collisionChildren.size(); i++) {
		if(collisionChildren[i]->enabled)		
			collisionChildren[i]->lastPosition = *collisionChildren[i]->getSceneEntity()->getPosition();
	}	
}

void CollisionScene::enableCollision(SceneEntity *entity, bool val) {
	// what the fuck?? rename that
	CollisionSceneEntity *cEnt = getCollisionByScreenEntity(entity);
	if(cEnt) {
		cEnt->enabled = val;
	}
}

void CollisionScene::adjustForCollision(CollisionSceneEntity *collisionEntity) {
	CollisionResult result;
//	float elapsed = CoreServices::getInstance()->getCore()->getElapsed();
	result.collided = false;
	for(int i=0; i < collisionChildren.size(); i++) {
		if(collisionChildren[i] != collisionEntity) {
			result = testCollisionOnCollisionChild(collisionEntity, collisionChildren[i]);
			if(result.collided) {
				if(result.setOldPosition) {
					collisionEntity->getSceneEntity()->setPosition(result.newPos);
					collisionEntity->gVelocity.set(0,0,0);					
				} else {
//				printf("colnormal: %f %f %f %f\n", result.colNormal.x, result.colNormal.y, result.colNormal.z,result.colDist);
				collisionEntity->getSceneEntity()->Translate(result.colNormal.x*result.colDist, result.colNormal.y*result.colDist, result.colNormal.z*result.colDist);
//				Logger::log("colnormal: %f,%f,%f\n",result.colNormal.x,result.colNormal.y,result.colNormal.z);
				if(result.colNormal.x > 0 && collisionEntity->gVelocity.x > 0)
					collisionEntity->gVelocity.x = 0;
				if(result.colNormal.x < 0 && collisionEntity->gVelocity.x < 0)
					collisionEntity->gVelocity.x = 0;
				if(result.colNormal.y > 0 && collisionEntity->gVelocity.y > 0)
					collisionEntity->gVelocity.y = 0;
				if(result.colNormal.y < 0 && collisionEntity->gVelocity.y < 0)
					collisionEntity->gVelocity.y = 0;
				if(result.colNormal.z > 0 && collisionEntity->gVelocity.z > 0)
					collisionEntity->gVelocity.z = 0;
				if(result.colNormal.z < 0 && collisionEntity->gVelocity.z < 0)
					collisionEntity->gVelocity.z = 0;
				collisionEntity->gVelocity.set(0,0,0);
				}
			}
		}
	}
}	

CollisionSceneEntity *CollisionScene::getCollisionByScreenEntity(SceneEntity *ent) {
	for(int i=0; i<collisionChildren.size();i++) {
		if(collisionChildren[i]->getSceneEntity() == ent)
			return collisionChildren[i];
	}	
	return NULL;

}

void CollisionScene::applyVelocity(SceneEntity *entity, float x, float y, float z) {
	CollisionSceneEntity *cEnt1 = getCollisionByScreenEntity(entity);
	if(!cEnt1)
		return;
	cEnt1->gVelocity.x += x;
	cEnt1->gVelocity.y += y;
	cEnt1->gVelocity.z += z;	
}

Vector3 CollisionScene::getCollisionNormalFromCollisionEnts(CollisionSceneEntity *cEnt1, CollisionSceneEntity *cEnt2) {

	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
 		if((obA == cEnt1->collisionObject && obB == cEnt2->collisionObject) ||
		 (obA == cEnt2->collisionObject && obB == cEnt1->collisionObject)) {
			if(contactManifold->getNumContacts() > 0) {
				btVector3 vec = contactManifold->getContactPoint(0).m_normalWorldOnB;
				return Vector3(vec.getX(), vec.getY(), vec.getZ());
			}
		}
	}
	return Vector3(0,0,0);
}

Vector3 CollisionScene::getCollisionNormal(SceneEntity *ent1, SceneEntity *ent2) {
	CollisionSceneEntity *cEnt1 = getCollisionByScreenEntity(ent1);
	CollisionSceneEntity *cEnt2 = getCollisionByScreenEntity(ent2);
	if(cEnt1 == NULL || cEnt2 == NULL)
		return Vector3(0,0,0);

	return getCollisionNormalFromCollisionEnts(cEnt1, cEnt2);
}

CollisionResult CollisionScene::testCollisionOnCollisionChild_Convex(CollisionSceneEntity *cEnt1, CollisionSceneEntity *cEnt2) {
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
				//				return result;
			}
		}
	}
	
	if(numAdds > 0) {
		result.colNormal = result.colNormal / (float)numAdds;
		//		result.colNormal = Vector3(0,1,0);
		//		result.colNormal.Normalize();
		result.colDist  = result.colDist / (float)numAdds;
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
		CollisionSceneEntity *retEnt = getCollisionEntityByObject(cb.m_collisionObject);
		if(retEnt) {
			ret.entity = retEnt->getSceneEntity();
			ret.position = Vector3(cb.m_hitPointWorld.getX(), cb.m_hitPointWorld.getY(), cb.m_hitPointWorld.getZ());
			ret.normal = Vector3(cb.m_hitNormalWorld.getX(), cb.m_hitNormalWorld.getY(), cb.m_hitNormalWorld.getZ());			
			return ret;
		}
	}
	
	return ret;
}

CollisionSceneEntity *CollisionScene::getCollisionEntityByObject(btCollisionObject *collisionObject) {
	for(int i=0; i <collisionChildren.size(); i++) {
		if(collisionChildren[i]->collisionObject == collisionObject) {
			return collisionChildren[i];
		}
	}
	return NULL;
}

CollisionResult CollisionScene::testCollisionOnCollisionChild_RayTest(CollisionSceneEntity *cEnt1, CollisionSceneEntity *cEnt2) {
	CollisionResult result;
	result.collided = false;
	result.setOldPosition = false;
	btConvexShape *shape = cEnt1->getConvexShape();
	if(!shape)
		return result;
	
//	shape->setMargin(1.0f);
	
	// hack to not collide with itself
	world->removeCollisionObject(cEnt1->collisionObject);	

	btVector3 fVec(cEnt1->lastPosition.x, cEnt1->lastPosition.y, cEnt1->lastPosition.z);
	btVector3 toVec(cEnt1->getSceneEntity()->getPosition()->x, cEnt1->getSceneEntity()->getPosition()->y, cEnt1->getSceneEntity()->getPosition()->z);
	
	btCollisionWorld::ClosestConvexResultCallback cb(toVec, fVec);
	btQuaternion qFrom;	
	btQuaternion qTo;
	qFrom.setRotation (btVector3(1.0, 0.0, 0.0), 0.0);
	qTo.setRotation (btVector3(1.0, 0.0, 0.0), 0.0);
	btTransform from(qFrom, fVec);
	btTransform to(qTo, toVec);
		
	world->convexSweepTest(shape, from, to, cb);
	
	if (cb.hasHit()) {
		result.collided = true;
		
		btVector3 newVec = toVec;
		newVec.setInterpolate3(fVec, toVec, cb.m_closestHitFraction);		
		result.colDist = newVec.distance(toVec);// + 0.001f;

//		result.colDist = fVec.distance(toVec);// - cb.m_closestHitFraction;
//		cb.m_hitPointWorld
		
//		result.colDist = shape->
//		result.colDist = cb.m_hitPointWorld.distance(fVec) - shape->;

		/*
		btVector3 linVel, angVel;
		btTransformUtil::calculateVelocity (from, to, 1.0, linVel, angVel);
		btTransform T;
		btTransformUtil::integrateTransform (from, linVel, angVel, cb.m_closestHitFraction, T);
		btVector3 newVec;
		newVec = T.getOrigin(); // * newVec;
		result.colDist = toVec.distance(newVec);	
		
		Logger::log("dist: %f\n", result.colDist);
		*/
		
//		result.colNormal = cEnt1->getSceneEntity()->getPosition()->(cEnt1->lastPosition);		
		result.colNormal = Vector3(cb.m_hitNormalWorld.getX(), cb.m_hitNormalWorld.getY(), cb.m_hitNormalWorld.getZ());
		result.colNormal.Normalize();
	}
	
	world->addCollisionObject(cEnt1->collisionObject);
	
	return result;
}

CollisionResult CollisionScene::testCollisionOnCollisionChild(CollisionSceneEntity *cEnt1, CollisionSceneEntity *cEnt2) {
	if(cEnt2->getType() == CollisionSceneEntity::SHAPE_MESH) {
		return testCollisionOnCollisionChild_RayTest(cEnt1, cEnt2);		
	} else {
		return testCollisionOnCollisionChild_Convex(cEnt1, cEnt2);
	}
}

CollisionResult CollisionScene::testCollision(SceneEntity *ent1, SceneEntity *ent2) {
	CollisionSceneEntity *cEnt1 = getCollisionByScreenEntity(ent1);
	CollisionSceneEntity *cEnt2 = getCollisionByScreenEntity(ent2);
	CollisionResult result;
	result.collided = false;
	if(cEnt1 == NULL || cEnt2 == NULL)
		return result;
	return testCollisionOnCollisionChild(cEnt1, cEnt2);
}

CollisionScene::~CollisionScene() {

}

void CollisionScene::enableGravity(SceneEntity *entity) {
	CollisionSceneEntity *cEnt1 = getCollisionByScreenEntity(entity);
	if(!cEnt1)
		return;
	cEnt1->gravityEnabled = true;
}

void CollisionScene::loadCollisionChild(SceneEntity *entity, bool autoCollide, int type) {
	addCollisionChild(entity, autoCollide, type);
}

void CollisionScene::stopTrackingCollision(SceneEntity *entity) {
	CollisionSceneEntity *cEnt = getCollisionByScreenEntity(entity);	
	world->removeCollisionObject(cEnt->collisionObject);
	for(int i=0; i < collisionChildren.size(); i++) {
		if(collisionChildren[i] == cEnt) {
			collisionChildren.erase(collisionChildren.begin() + i);
			delete cEnt;
			
			return;
		}
	}
}

CollisionSceneEntity *CollisionScene::trackCollision(SceneEntity *newEntity, bool autoCollide, int type, int group) {
	CollisionSceneEntity *newCollisionEntity = new CollisionSceneEntity(newEntity,autoCollide, type);

//	if(type == CollisionSceneEntity::CHARACTER_CONTROLLER) {
//		world->addCollisionObject(newCollisionEntity->collisionObject,btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);		
//	} else {
		world->addCollisionObject(newCollisionEntity->collisionObject, group);
//	}
	
	collisionChildren.push_back(newCollisionEntity);
//	newCollisionEntity->Update();
	return newCollisionEntity;
}

CollisionSceneEntity *CollisionScene::addCollisionChild(SceneEntity *newEntity, bool autoCollide, int type, int group) {
	addEntity(newEntity);
	return trackCollision(newEntity, autoCollide, type);

}