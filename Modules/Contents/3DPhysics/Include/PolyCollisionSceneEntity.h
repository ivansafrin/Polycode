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
			Number gravityStrength;
		
			Vector3 lastPosition;
		
		static const int SHAPE_BOX = 0;
		static const int SHAPE_TERRAIN = 1;
		static const int SHAPE_SPHERE = 2;	
		static const int SHAPE_MESH = 3;			
		static const int CHARACTER_CONTROLLER = 4;
		static const int SHAPE_CAPSULE = 5;		
		static const int SHAPE_PLANE = 6;
		static const int SHAPE_CONE = 7;
		static const int SHAPE_CYLINDER = 8;
						
			bool enabled;
			btCollisionShape *shape;
		
		protected:
		

			btConvexShape *convexShape;
			btConcaveShape *concaveShape;
		
			int type;
			SceneEntity *sceneEntity;
	
	};
}