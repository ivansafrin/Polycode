/*
 *  PolyPhysicsScreenEntity.h
 *  Poly
 *
 *  Created by Ivan Safrin on 5/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
 
// @package ScreenPhysics

#pragma once
#include "PolyGlobals.h"
#include "PolyScreenEntity.h"
#include "Box2D.h"

namespace Polycode {

	class _PolyExport PhysicsScreenEntity {
		public:
			PhysicsScreenEntity(ScreenEntity *entity, b2World *world, int entType, float friction, float density, float restitution, bool isSensor);
			~PhysicsScreenEntity();		
			
			ScreenEntity *getScreenEntity();
			
			void applyTorque(float torque);
			void applyForce(Vector2 force);
			
			void Update();
			
			static const int ENTITY_RECT = 1;
			static const int ENTITY_CIRCLE = 2;	
			static const int ENTITY_STATICRECT = 3;
		
			b2Body* body;
			b2BodyDef *bodyDef;
			b2Shape *shape;
			
			bool collisionOnly;
		
		protected:
		
		Vector2 lastPosition;
		float lastRotation;
			
		ScreenEntity *screenEntity;
	};

}