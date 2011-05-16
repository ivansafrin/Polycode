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
#include "PolySceneEntity.h"
#include "PolyCollisionSceneEntity.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "PolyCoreServices.h"
#include "PolySceneMesh.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"


//class btKinematicCharacterController;

namespace Polycode {
	
	class _PolyExport PhysicsSceneEntity : public CollisionSceneEntity {
	public:
		PhysicsSceneEntity(SceneEntity *entity, int type, Number mass, Number friction, Number restitution);
		virtual ~PhysicsSceneEntity();
		
		SceneEntity *getSceneEntity();
		virtual void Update();
		void setFriction(Number friction);
		
		int getType() { return type; }	
		
		static const int SHAPE_BOX = 0;
		static const int SHAPE_TERRAIN = 1;
		static const int SHAPE_SPHERE = 2;	
		static const int SHAPE_MESH = 3;			
		static const int CHARACTER_CONTROLLER = 4;
		static const int SHAPE_CAPSULE = 5;		
		static const int SHAPE_PLANE = 6;		
		
		bool enabled;
		
		btRigidBody* rigidBody;
		
	protected:
	
		Number mass;
	};
	
	
	class _PolyExport PhysicsCharacter : public PhysicsSceneEntity {
		public:
			PhysicsCharacter(SceneEntity *entity, Number mass, Number friction, Number stepSize);
			virtual ~PhysicsCharacter();
	
			void setWalkDirection(Vector3 direction);
			void jump();
			virtual void Update();
		
			btKinematicCharacterController *character;
			btPairCachingGhostObject *ghostObject;
				
		
		protected:
	};
}