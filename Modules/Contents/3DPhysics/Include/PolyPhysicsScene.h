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

	/**
	* A scene subclass that simulates physics for its children.
	*/
	class _PolyExport PhysicsScene : public CollisionScene {
	public:
		/**
		* Main constructor.
		*/
		PhysicsScene();
		virtual ~PhysicsScene();	
		
		void Update();		
		
			/** @name Physics scene
			*  Public methods
			*/
			//@{			
		
		void removePhysicsChild(SceneEntity *entity);
		PhysicsSceneEntity *getPhysicsEntityBySceneEntity(SceneEntity *entity);
		
		PhysicsSceneEntity *addPhysicsChild(SceneEntity *newEntity, int type=0, Number mass = 0.0f, Number friction=1, Number restitution=0, int group=1);		
		PhysicsSceneEntity *trackPhysicsChild(SceneEntity *newEntity, int type=0, Number mass = 0.0f, Number friction=1, Number restitution=0, int group=1);		
		
		PhysicsCharacter *addCharacterChild(SceneEntity *newEntity, Number mass, Number friction, Number stepSize, int group  = 1);
		
		PhysicsVehicle *addVehicleChild(SceneEntity *newEntity, Number mass, Number friction, int group  = 1);
			//@}
			// ----------------------------------------------------------------------------------------------------------------

		
	protected:
		
		void initPhysicsScene();		
		
		btDiscreteDynamicsWorld* physicsWorld;
		vector<PhysicsSceneEntity*> physicsChildren;		
		
	};
	
}

