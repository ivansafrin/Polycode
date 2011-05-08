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
#include "PolyScreenEntity.h"
#include "Box2D/Box2D.h"

namespace Polycode {

	class _PolyExport PhysicsScreenEntity {
		public:
			PhysicsScreenEntity(ScreenEntity *entity, b2World *world, float worldScale, int entType, float friction, float density, float restitution, bool isSensor, bool fixedRotation);
			~PhysicsScreenEntity();		
			
			ScreenEntity *getScreenEntity();
			
			void applyTorque(float torque);
			void applyForce(Vector2 force);
		
			void setTransform(Vector2 pos, float angle);
			
			void Update();
			
			static const int ENTITY_RECT = 1;
			static const int ENTITY_CIRCLE = 2;	
			static const int ENTITY_STATICRECT = 3;
		
			b2Fixture *fixture;		
			b2Body* body;
			b2BodyDef *bodyDef;
			b2Shape *shape;
			
			bool collisionOnly;
		
		protected:
		
		float worldScale;
		Vector2 lastPosition;
		float lastRotation;
			
		ScreenEntity *screenEntity;
	};

}