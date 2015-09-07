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
#include "PolyVector3.h"

class btConvexShape;
class btConcaveShape;
class btCollisionShape;
class btCollisionObject;

namespace Polycode {

	class Entity;

	/**
	* A wrapped around Entity that provides collision information.
	*/
	class _PolyExport CollisionEntity {
		public:
			/**
			* Main constructor.
			*/ 
			CollisionEntity(Entity *entity, int type, bool compoundChildren = false);
			virtual ~CollisionEntity();
			
			/** @name Collision scene entity
			*  Public methods
			*/
			//@{			
			
			Entity *getEntity();			
			
			int getType() { return type; }
						
			//@}
			// ----------------------------------------------------------------------------------------------------------------
			
			virtual void Update();
		
			btConvexShape *getConvexShape(){ return convexShape; }					
			btCollisionShape *createCollisionShape(Entity *entity, int type);		
			btCollisionObject *collisionObject;		
			Vector3 lastPosition;
		
		/**
		* Box shape
		*/
		static const int SHAPE_BOX = 0;		
		/**
		* Terrain shape
		*/		
		static const int SHAPE_TERRAIN = 1;
		
		/**
		* Sphere shape
		*/		
		static const int SHAPE_SPHERE = 2;	
		
		/**
		* Mesh shape
		*/		
		static const int SHAPE_MESH = 3;			
		
		/**
		* Character controller shape
		*/				
		static const int CHARACTER_CONTROLLER = 4;
		
		/**
		* Capsule shape
		*/						
		static const int SHAPE_CAPSULE = 5;		
		
		/**
		* Plane shape
		*/								
		static const int SHAPE_PLANE = 6;
		
		/**
		* Cone shape
		*/										
		static const int SHAPE_CONE = 7;
		
		/**
		* Cylinder shape
		*/												
		static const int SHAPE_CYLINDER = 8;
						
			bool enabled;
			btCollisionShape *shape;
		
		protected:
		

			btConvexShape *convexShape;
			btConcaveShape *concaveShape;
		
			int type;
			Entity *entity;
	
	};
}
