/*
 *  PolyCollisionScene.h
 *  Poly
 *
 *  Created by Ivan Safrin on 6/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package SceneDynamics

#pragma once
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyGenericScene.h"
#include "PolyCollisionSceneEntity.h"
#include "btBulletCollisionCommon.h"
#include "PolyVector3.h"
#include <vector>

using std::vector;

namespace Polycode {

struct CollisionResult {
	bool collided;
	Vector3 colNormal;
	float colDist;
	bool setOldPosition;
	Vector3 newPos;
};

	struct RayTestResult {
		SceneEntity *entity;
		Vector3 normal;
		Vector3 position;
	};

	
	class _PolyExport CollisionScene : public GenericScene {
		public:
			CollisionScene();
			CollisionScene(bool virtualScene);		
			virtual ~CollisionScene();
		
			void initCollisionScene();
		
			virtual void Update();		
			void enableCollision(SceneEntity *entity, bool val);		
			CollisionSceneEntity *getCollisionEntityByObject(btCollisionObject *collisionObject);		
			RayTestResult getFirstEntityInRay(const Vector3 &origin,  const Vector3 &dest);
			
			CollisionSceneEntity *getCollisionByScreenEntity(SceneEntity *ent);
			CollisionResult testCollision(SceneEntity *ent1, SceneEntity *ent2);
			CollisionResult testCollisionOnCollisionChild(CollisionSceneEntity *cEnt1, CollisionSceneEntity *cEnt2);				
			CollisionResult testCollisionOnCollisionChild_Convex(CollisionSceneEntity *cEnt1, CollisionSceneEntity *cEnt2);		
			CollisionResult testCollisionOnCollisionChild_RayTest(CollisionSceneEntity *cEnt1, CollisionSceneEntity *cEnt2);					
			Vector3 getCollisionNormalFromCollisionEnts(CollisionSceneEntity *cEnt1, CollisionSceneEntity *cEnt2);			
			Vector3 getCollisionNormal(SceneEntity *ent1, SceneEntity *ent2);			
			void applyVelocity(SceneEntity *entity, float x, float y, float z);			
			void loadCollisionChild(SceneEntity *entity, bool autoCollide=false, int type=0);
			void enableGravity(SceneEntity *entity);
			
			virtual CollisionSceneEntity *addCollisionChild(SceneEntity *newEntity, bool autoCollide=false, int type=0);
			CollisionSceneEntity *trackCollision(SceneEntity *newEntity, bool autoCollide, int type=0);
			void adjustForCollision(CollisionSceneEntity *collisionEntity);
		protected:
		
			vector<CollisionSceneEntity*> collisionChildren;
			btCollisionWorld *world;
	};

}