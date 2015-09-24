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
class SceneMesh;
class CollisionEntity;

/**
* Result of a collision test.
*/
struct CollisionResult {

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
	struct RayTestResult {
		/**
		* Entity returned.
		*/
		Entity *entity;
		
		/**
		* Ray normal
		*/		
		Vector3 normal;
		
		/**
		* Ray position.
		*/				
		Vector3 position;
	};

	class CollisionSceneDebugDraw : public btIDebugDraw {
	public:
		CollisionSceneDebugDraw();

		void Update(btCollisionWorld *world);
		Entity* getDebugEntity();

		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
		void drawSphere(btScalar radius, const btTransform& transform, const btVector3& color);
		void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color){};
		void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar alpha);

		void reportErrorWarning(const char* warningString);
		void draw3dText(const btVector3& location, const char* textString);
		void setDebugMode(int debugMode);
		int  getDebugMode() const;

	protected:
		Entity *debugEntity;
		DebugDrawModes mode;
		SceneMesh *lineMesh;
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
		
			virtual void fixedUpdate();
			void Update();
			
			virtual void removeEntity(Entity *entity);
						
			CollisionEntity *getCollisionEntityByObject(btCollisionObject *collisionObject);		

			
			/** @name Collision scene
			*  Public methods
			*/
			//@{			
			
			RayTestResult getFirstEntityInRay(const Vector3 &origin,  const Vector3 &dest);			
			void enableCollision(Entity *entity, bool val);											
			CollisionEntity *getCollisionByScreenEntity(Entity *ent);
			CollisionResult testCollision(Entity *ent1, Entity *ent2);
			CollisionResult testCollisionOnCollisionChild(CollisionEntity *cEnt1, CollisionEntity *cEnt2);				
			CollisionResult testCollisionOnCollisionChild_Convex(CollisionEntity *cEnt1, CollisionEntity *cEnt2);
		
            bool isColliding(Entity *ent1);
        
			virtual CollisionEntity *addCollisionChild(Entity *newEntity, int type=0, int group=1);
			virtual CollisionEntity *trackCollision(Entity *newEntity, int type=0, int group=1);
			void removeCollision(Entity *entity);
			void adjustForCollision(CollisionEntity *collisionEntity);
			
			/**
			 * Sets whether you are visually debugging the CollsionShapes
			 * @param val If true you are debugging. Initially set to false.
			 * @param mode Debug mode as int. Defaults to wireframe visualisation. For available values see "btIDebugDraw.h"
			 */
			void setDebug(bool val, int mode = 1);

			//@}
			// ----------------------------------------------------------------------------------------------------------------
			
		protected:
		
			std::vector<CollisionEntity*> collisionChildren;
			btCollisionWorld *world;
			
			btDefaultCollisionConfiguration *collisionConfiguration;
			btCollisionDispatcher *dispatcher;
			btAxisSweep3*  axisSweep;

			CollisionSceneDebugDraw* debugDrawer;
	};

}
