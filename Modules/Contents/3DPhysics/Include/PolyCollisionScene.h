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

#pragma once
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyScene.h"
#include "PolyCollisionSceneEntity.h"
#include "btBulletCollisionCommon.h"
#include "PolyVector3.h"
#include <vector>

using std::vector;

namespace Polycode {

struct CollisionResult {
	bool collided;
	Vector3 colNormal;
	Number colDist;
	bool setOldPosition;
	Vector3 newPos;
};

	struct RayTestResult {
		SceneEntity *entity;
		Vector3 normal;
		Vector3 position;
	};

	
	class _PolyExport CollisionScene : public Scene {
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
			void applyVelocity(SceneEntity *entity, Number x, Number y, Number z);			
			void loadCollisionChild(SceneEntity *entity, bool autoCollide=false, int type=0);
			void enableGravity(SceneEntity *entity);
			
			void stopTrackingCollision(SceneEntity *entity);
		
			virtual CollisionSceneEntity *addCollisionChild(SceneEntity *newEntity, bool autoCollide=false, int type=0, int group=0);
			CollisionSceneEntity *trackCollision(SceneEntity *newEntity, bool autoCollide, int type=0, int group=0);
			void adjustForCollision(CollisionSceneEntity *collisionEntity);
		protected:
		
			vector<CollisionSceneEntity*> collisionChildren;
			btCollisionWorld *world;
	};

}