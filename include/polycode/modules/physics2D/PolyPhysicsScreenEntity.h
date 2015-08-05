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

	class Entity;

	/**
	* A 2D Physics enabled screen entity. 
	*/	
	class _PolyExport PhysicsScene2DEntity {
		public:
        
            PhysicsScene2DEntity() { collisionOnly = false; }
        
			PhysicsScene2DEntity(Entity *entity, b2World *world, Number worldScale, int entType, bool isStatic, Number friction, Number density, Number restitution, bool isSensor, bool fixedRotation, int groupIndex = 0);
			virtual ~PhysicsScene2DEntity();

			virtual void Update();
			
			/**
			* Returns the screen entity associated with this physics entity.
			*/
			Entity *getEntity();
			
			/**
			* Applies torque to the physics entity		
			*/
			void applyTorque(Number torque);
			
			/**
			 * Applies force to the physics entity		
			 */			
			void applyForce(Vector2 force);

			/**
			 * Applies an impulse to the physics entity		
			 */
			void applyImpulse(Number fx, Number fy);
			
			/**
			 * Sets the position and rotation of entity
			 */
			void setTransform(Vector2 pos, Number angle);
			
			/**
             * Sets the velocity of the physics entity
             */
			void setVelocity(Number fx, Number fy);	
			void setVelocityX( Number fx);	
			void setVelocityY(Number fy);				
        
            /**
             * Sets the dampening of the physics entity
             */
            void setLinearDamping(Number damping);
            void setAngularDamping(Number damping);
            void setFriction(Number friction);
        
            /**
             * Returns dampening information
             */ 
            Number getLinearDamping();
            Number getAngularDamping();
            Number getFriction();

            /**
             * Sets physics entity density
             */
            void setDensity(Number density);
            Number getDensity();
        
            /**
             * Sets collision filtering
             * Collision category specifies which bits on a 16 bit field the physics entity belongs to. default is 1 (or "0000000000000001")
             * Collision mask specifies which bits the physics entity will collide with. default 65535 (or 0xFFFF, or "1111111111111111", or everything)
             * If a physics entity's mask bits don't line up with any of an overlapping entity's category bits, their collisions will be skipped
             */
            void setCollisionCategory(int categoryBits);
            void setCollisionMask(int maskBits);
            void setCollisionGroupIndex(int group);

			/**
			 * Gets a specific fixture based on it's index position
			 */
			b2Fixture* getFixture(unsigned short index);
			/**
			 * Gets the last fixture selected (automatically set to last added on creation)
			 */
			b2Fixture* getFixture();
        
            bool getFixedRotation() const;
            void setFixedRotation(bool val);

			/**
			* Rectangular physics entity
			*/
			static const int ENTITY_RECT = 1;
			/**
			* Circular physics entity
			*/ 			
			static const int ENTITY_CIRCLE = 2;	
			/**
			* Mesh physics entity.
			*/ 						
			static const int ENTITY_MESH = 3;
			/**
			* Edge phyiscs Entity
			*/ 
            static const int ENTITY_EDGE = 4;
			/**
			* Capsule entity. 
			*/ 
            static const int ENTITY_CAPSULE = 5;

			/**
			* Three vertical circles.
			*/ 
            static const int ENTITY_TRIPLE_CIRCLE = 6;


			b2Body *body;			
			b2Fixture *fixture;		
			
			bool collisionOnly;

		protected:
        
            bool fixedRotation;
			Number worldScale;
			Entity *entity;
	};
	
	typedef PhysicsScene2DEntity PhysicsScreenEntity;

}
