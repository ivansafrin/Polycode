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
#include "PolyGlobals.h"
#include "PolyScene.h"
#include "PolyVector3.h"
#include "btBulletCollisionCommon.h"
#include <vector>

class btCollisionObject;
class btCollisionWorld;

namespace Polycode {

class Entity;
class CollisionEntity;

/**
* Result of a collision test.
*/
class _PolyExport CollisionResult {
	public:
		/**
		* Default constructor.
		*/
		CollisionResult();
		virtual ~CollisionResult();

		/**
		* True if collided.
		*/ 
		bool collided;
	
		/**
		* Collision normal.
		*/ 	
		Vector3 colNormal;
	
		/**
		* Collision distance.
		*/ 		
		Number colDist;
		
		bool setOldPosition;
		Vector3 newPos;
};
	
	/**
	* Result of a ray test.
	*/
	class _PolyExport RayTestResult {
		public:
			/**
			* Default constructor.
			*/
			RayTestResult();
			virtual ~RayTestResult();
			
			/**
			* Entity returned.
			*/
			Entity *entity;

			/**
			* Ray fraction.
			*/
			Number fraction;
		
			/**
			* Ray normal.
			*/		
			Vector3 normal;
		
			/**
			* Ray position.
			*/				
			Vector3 position;
	};

	/**
	* Result of a ray test with multiple hits.
	*/
	class _PolyExport RayTestResultMultiple {
		public:
			/**
			* Default constructor.
			*/
			RayTestResultMultiple();
			virtual ~RayTestResultMultiple();

			/**
			* Adds a single RayTestResult.
			*/
			void addResult(RayTestResult *result);

			/**
			* Gets a result.
			*/
			RayTestResult *getResult(int index);

			/**
			* Gets the total number of results held.
			*/
			unsigned int getResultCount();

			/**
			* clears all results. 
			*/
			void clearResults();

		protected:
			std::vector<RayTestResult*> results;
	};

	/**
	* A scene that tracks collisions between entities. The collision scene acts like a regular scene, only it automatically tracks collisions between its child entities.
	*/
	class _PolyExport CollisionScene : public Scene {
		public:
			/**
			* Creates a collision scene.
			*/
			CollisionScene(Vector3 size = Vector3(2000), bool virtualScene = false, bool deferInitCollision = false);		
			virtual ~CollisionScene();
		
			void initCollisionScene(Vector3 size);
		
			virtual void Update();
			
			virtual void removeEntity(Entity *entity);
						
			CollisionEntity *getCollisionEntityByObject(btCollisionObject *collisionObject);		

			
			/** @name Collision scene
			*  Public methods
			*/
			//@{			
			
			RayTestResult getFirstEntityInRay(const Vector3 &origin,  const Vector3 &dest);	
			RayTestResultMultiple getAllEntitiesInRay(const Vector3 &origin,  const Vector3 &dest, int group=1, int mask=-1);
			void enableCollision(Entity *entity, bool val);											
			CollisionEntity *getCollisionByScreenEntity(Entity *ent);
			CollisionResult testCollision(Entity *ent1, Entity *ent2);
			CollisionResult testCollisionOnCollisionChild(CollisionEntity *cEnt1, CollisionEntity *cEnt2);				
			CollisionResult testCollisionOnCollisionChild_Convex(CollisionEntity *cEnt1, CollisionEntity *cEnt2);	
		
			virtual CollisionEntity *addCollisionChild(Entity *newEntity, int type=0, int group=1, int mask=-1);
			CollisionEntity *trackCollision(Entity *newEntity, int type=0, int group=1, int mask=-1);
			void removeCollision(Entity *entity);
			void adjustForCollision(CollisionEntity *collisionEntity);
			
			//@}
			// ----------------------------------------------------------------------------------------------------------------
			
		protected:
		
			std::vector<CollisionEntity*> collisionChildren;
			btCollisionWorld *world;
			
			btDefaultCollisionConfiguration *collisionConfiguration;
			btCollisionDispatcher *dispatcher;
			btAxisSweep3*  axisSweep;
	};

}
