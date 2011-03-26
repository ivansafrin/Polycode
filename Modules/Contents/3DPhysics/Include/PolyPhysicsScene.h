/*
 *  PolyPhysicsScene.h
 *  Modules
 *
 *  Created by Ivan Safrin on 12/22/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */

// @package SceneDynamics

#pragma once
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyCollisionScene.h"
#include "PolyVector3.h"
#include "PolyPhysicsSceneEntity.h"
#include <vector>

using std::vector;

namespace Polycode {

	class _PolyExport PhysicsScene : public CollisionScene {
	public:
		PhysicsScene();
		virtual ~PhysicsScene();	
		
		void Update();		
		
		PhysicsSceneEntity *addPhysicsChild(SceneEntity *newEntity, int type=0, float mass = 0.0f, float friction=1, float restitution=0, int group=1);		
		PhysicsSceneEntity *trackPhysicsChild(SceneEntity *newEntity, int type=0, float mass = 0.0f, float friction=1, float restitution=0, int group=1);		
		
		PhysicsCharacter *addCharacterChild(SceneEntity *newEntity, float mass, float friction, float stepSize, int group  = 1);

		
	protected:
		
		void initPhysicsScene();		
		
		btDiscreteDynamicsWorld* physicsWorld;
		vector<PhysicsSceneEntity*> physicsChildren;		
		
	};
	
}

