
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
		PhysicsSceneEntity(SceneEntity *entity, int type, float mass, float friction, float restitution);
		virtual ~PhysicsSceneEntity();
		
		SceneEntity *getSceneEntity();
		virtual void Update();
		void setFriction(float friction);
		
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
	
		float mass;
	};
	
	
	class _PolyExport PhysicsCharacter : public PhysicsSceneEntity {
		public:
			PhysicsCharacter(SceneEntity *entity, float mass, float friction, float stepSize);
			virtual ~PhysicsCharacter();
	
			void setWalkDirection(Vector3 direction);
			void jump();
			virtual void Update();
		
			btKinematicCharacterController *character;
			btPairCachingGhostObject *ghostObject;
				
		
		protected:
	};
}