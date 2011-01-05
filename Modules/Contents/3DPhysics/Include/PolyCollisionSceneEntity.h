/*
 *  PolyCollisionSceneEntity.h
 *  Poly
 *
 *  Created by Ivan Safrin on 6/17/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package SceneDynamics

#pragma once
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolySceneEntity.h"
#include "btBulletCollisionCommon.h"
#include "PolyCoreServices.h"
#include "PolySceneMesh.h"

namespace Polycode {

	class _PolyExport CollisionSceneEntity {
		public:
			CollisionSceneEntity(SceneEntity *entity, bool autoCollide, int type);
			~CollisionSceneEntity();
			
			SceneEntity *getSceneEntity();
			virtual void Update();
			int getType() { return type; }
		
			btConvexShape *getConvexShape(){ return convexShape; }
					
			btCollisionShape *createCollisionShape(SceneEntity *entity, int type);
		
			btCollisionObject *collisionObject;
			bool gravityEnabled;
			bool autoCollide;
			Vector3 gravityVector;
			Vector3 gVelocity;
			float gravityStrength;
		
			Vector3 lastPosition;
		
		static const int SHAPE_BOX = 0;
		static const int SHAPE_TERRAIN = 1;
		static const int SHAPE_SPHERE = 2;	
		static const int SHAPE_MESH = 3;			
		static const int CHARACTER_CONTROLLER = 4;
		static const int SHAPE_CAPSULE = 5;		
		
			bool enabled;
			btCollisionShape *shape;
		
		protected:
		

			btConvexShape *convexShape;
			btConcaveShape *concaveShape;
		
			int type;
			SceneEntity *sceneEntity;
	
	};
}