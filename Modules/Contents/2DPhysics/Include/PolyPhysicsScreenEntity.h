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
#include "PolyVector2.h"
#include "Box2D/Box2D.h"

namespace Polycode {

	class ScreenEntity;

	/**
	* A 2D Physics enabled screen entity. 
	*/	
	class _PolyExport PhysicsScreenEntity {
		public:
			PhysicsScreenEntity(ScreenEntity *entity, b2World *world, Number worldScale, int entType, bool isStatic, Number friction, Number density, Number restitution, bool isSensor, bool fixedRotation, int groupIndex = 0);
			~PhysicsScreenEntity();		
			
			/**
			* Returns the screen entity associated with this physics entity.
			*/
			ScreenEntity *getScreenEntity();
			
			/**
			* Applies torque to the physics entity		
			*/
			void applyTorque(Number torque);
			
			/**
			* Applies force to the physics entity		
			*/			
			void applyForce(Vector2 force);
		
			void setTransform(Vector2 pos, Number angle);
			
			void Update();
			
			void setVelocity(Number fx, Number fy);	
			void setVelocityX( Number fx);	
			void setVelocityY(Number fy);				
			
			void applyImpulse(Number fx, Number fy);
				
			/**
			* Rectangular physics entity
			*/ 
			static const int ENTITY_RECT = 1;
			/**
			* Circular physics entity
			*/ 			
			static const int ENTITY_CIRCLE = 2;	
			/**
			* Mesh entity.
			*/ 						
			static const int ENTITY_MESH = 3;
		
			b2Fixture *fixture;		
			b2Body* body;
			b2Shape *shape;
			
			bool collisionOnly;
		
		protected:
		
		Number worldScale;
		ScreenEntity *screenEntity;
	};

}
