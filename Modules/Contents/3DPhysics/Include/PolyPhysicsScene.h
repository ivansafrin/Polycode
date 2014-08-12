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
#include "PolyCollisionScene.h"
#include <vector>

class btDiscreteDynamicsWorld;
struct btDbvtBroadphase;
class btSequentialImpulseConstraintSolver;
class btGhostPairCallback;
class btTypedConstraint;
class btHingeConstraint;
class btGeneric6DofConstraint;

namespace Polycode {

	class Entity;
	class PhysicsEntity;
	class PhysicsCharacter;
	class PhysicsVehicle;
	
	class _PolyExport PhysicsSceneEvent : public Event {
		public:
			PhysicsSceneEvent();
			~PhysicsSceneEvent();
			
			static const int EVENTBASE_PHYSICSSCENEEVENT = 0x900;
			static const int COLLISION_EVENT = EVENTBASE_PHYSICSSCENEEVENT+0;
			
			PhysicsEntity *entityA;
			PhysicsEntity *entityB;
            CollisionEntity *collisionEntityA;
            CollisionEntity *collisionEntityB;
        

			Number appliedImpulse;
						
			Vector3 positionOnA;
			Vector3 positionOnB;
			Vector3 worldNormalOnB;				
	};
	
	class _PolyExport PhysicsGenericConstraint {
		public:
			
			void setLinearLowerLimit(Vector3 limit);
			void setLinearUpperLimit(Vector3 limit);
						
			void setAngularLowerLimit(Vector3 limit);
			void setAngularUpperLimit(Vector3 limit);
					
			btGeneric6DofConstraint *btConstraint;
	};

	class _PolyExport PhysicsHingeConstraint  {
		public:
			~PhysicsHingeConstraint();
			void setLimits(Number minLimit, Number maxLimit);
			Number getAngle();
			
			btHingeConstraint *btConstraint;
	};

	/**
	* A scene subclass that simulates physics for its children.
	*/
	class _PolyExport PhysicsScene : public CollisionScene {
	public:
		/**
		* Main constructor.
		*/
		PhysicsScene(int maxSubSteps = 0, Vector3 size = Vector3(200), bool virtualScene = false);
		virtual ~PhysicsScene();	
		
		void fixedUpdate();
		
		void removeEntity(Entity *entity);
		
		void processWorldCollisions();
		
		PhysicsEntity *getPhysicsEntityByCollisionObject(btCollisionObject *object);
		
			/** @name Physics scene
			*  Public methods
			*/
			//@{			
		
		void removePhysicsChild(Entity *entity);
		PhysicsEntity *getPhysicsEntityByEntity(Entity *entity);
		
		PhysicsEntity *addPhysicsChild(Entity *newEntity, int type=0, Number mass = 0.0f, Number friction=1, Number restitution=0, int group=1, bool compoundChildren = false);		
		PhysicsEntity *trackPhysicsChild(Entity *newEntity, int type=0, Number mass = 0.0f, Number friction=1, Number restitution=0, int group=1, bool compoundChildren = false);		
		
		PhysicsCharacter *addCharacterChild(Entity *newEntity, Number mass, Number friction, Number stepSize, int group  = 1);
		PhysicsCharacter *trackCharacterChild(Entity *newEntity, Number mass, Number friction, Number stepSize, int group  = 1);
        
		void removeCharacterChild(PhysicsCharacter *character);
		
		PhysicsHingeConstraint *createHingeConstraint(Entity *entity, Vector3 pivot, Vector3 axis, Number minLimit, Number maxLimit);

		PhysicsHingeConstraint *createHingeJoint(Entity *entity1, Entity *entity2, Vector3 pivot1, Vector3 axis1, Vector3 pivot2, Vector3 axis2, Number minLimit, Number maxLimit);
		
		PhysicsGenericConstraint *createGenericConstraint(Entity *entity);
				
		void setVelocity(Entity *entity, Vector3 velocity);
		void setSpin(Entity *entity, Vector3 spin);
				
		void warpEntity(Entity *entity, Vector3 position, bool resetRotation = false);
		
		void removeConstraint(PhysicsHingeConstraint *constraint);
		
		void applyImpulse(Entity *entity, Vector3 force, Vector3 point);
		
		PhysicsVehicle *addVehicleChild(Entity *newEntity, Number mass, Number friction, int group  = 1);

		PhysicsVehicle *trackVehicleChild(Entity *newEntity, Number mass, Number friction, int group  = 1);
		
		void setGravity(Vector3 gravity);
		
		void wakeUp(Entity *entity);
			//@}
			// ----------------------------------------------------------------------------------------------------------------

		bool pausePhysics;
		
	protected:
		
		bool paused;
		int maxSubSteps;
		void initPhysicsScene(Vector3 size);		
		
		btDiscreteDynamicsWorld* physicsWorld;
		btSequentialImpulseConstraintSolver *solver;		
		btDbvtBroadphase *broadphase;
		btGhostPairCallback *ghostPairCallback;
		
		std::vector<PhysicsEntity*> physicsChildren;
		
	};
	
}

