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
#include "PolyScreen.h"
#include "Box2D/Box2D.h"
//#include "PolyCoreServices.h"
#include "PolyScreenLine.h"
#include "PolyPhysicsScreenEntity.h"
#include "PolyTimer.h"
#include <vector>

#define MAX_B2DCONTACTPOINTS 2048

namespace Polycode {
	
class _PolyExport PhysicsScreenEvent : public Event {
	public:	
		
		PhysicsScreenEntity *entity1;	
		PhysicsScreenEntity *entity2;	
	
		static const int EVENT_NEW_SHAPE_COLLISION = 0;
		static const int EVENT_END_SHAPE_COLLISION = 1;
		static const int EVENT_PERSIST_SHAPE_COLLISION = 2;	
};		


enum ContactState
{
	e_contactAdded = 0,
	e_contactPersisted = 1,
	e_contactRemoved = 2,
};
	
struct ContactPoint
{
	b2Shape* shape1;
	b2Shape* shape2;
	b2Vec2 normal;
	b2Vec2 position;
	b2Vec2 velocity;
	b2ContactID id;
	ContactState state;
};
	

class _PolyExport PhysicsJoint {
public:
	PhysicsJoint() {}
	~PhysicsJoint() {}
	b2Joint *box2DJoint;
	
};

/**
* A 2D Physics enabled screen. 
*/	
class _PolyExport PhysicsScreen : public Screen, b2ContactListener {

public:

	/**
	*
	*/ 
	PhysicsScreen(Number worldScale, Number freq);
	
	/**
	* Default constructor.
	*/
	PhysicsScreen();
	
	~PhysicsScreen();
	
	void Update();
	
	/**
	* Adds a ScreenEntity as a physics enabled child. 
	* @param newEntity Screen entity to add.
	* @param entType Physics entity type to add as. Possible values are PhysicsScreenEntity::ENTITY_RECT, PhysicsScreenEntity::ENTITY_CIRCLE and PhysicsScreenEntity::ENTITY_STATICRECT
	* @return The physics entity wrapper.
	*/
	PhysicsScreenEntity *addPhysicsChild(ScreenEntity *newEntity, int entType, Number friction=0.1, Number density=1, Number restitution = 0, bool isSensor = false, bool fixedRotation = false);
	void removePhysicsChild(PhysicsScreenEntity *entityToRemove);
	
	PhysicsScreenEntity *addCollisionChild(ScreenEntity *newEntity, int entType);
	
	void destroyJoint(PhysicsJoint *joint);
	void createDistanceJoint(ScreenEntity *ent1, ScreenEntity *ent2, bool collideConnected);
	void createPrismaticJoint(ScreenEntity *ent1, ScreenEntity *ent2, bool collideConnected);
	PhysicsJoint *createRevoluteJoint(ScreenEntity *ent1, ScreenEntity *ent2, Number ax, Number ay, bool enableLimit, Number lowerLimit, Number upperLimit, bool motorEnabled, Number motorSpeed, Number maxTorque);
//	b2MouseJoint *createMouseJoint(ScreenEntity *ent1, Vector2 *mp);
	void applyForce(ScreenEntity *ent, Number fx, Number fy);
	void applyImpulse(ScreenEntity *ent, Number fx, Number fy);
	
	void setGravity(Vector2 newGravity);
	
	void setTransform(ScreenEntity *ent, Vector2 pos, Number angle);
	
	PhysicsScreenEntity *getPhysicsEntityByShape(b2Shape *shape);
	PhysicsScreenEntity *getPhysicsEntityByFixture(b2Fixture *fixture);
	
	void setVelocity(ScreenEntity *ent, Number fx, Number fy);	
	void setVelocityX(ScreenEntity *ent, Number fx);	
	void setVelocityY(ScreenEntity *ent, Number fy);	
	void setSpin(ScreenEntity *ent, Number spin);
	
	Vector2 getVelocity(ScreenEntity *ent);
			
	void BeginContact (b2Contact *contact);
	void EndContact (b2Contact *contact);	
	
	void wakeUp(ScreenEntity *ent);
	
	void handleEvent(Event *event);
	
	Vector2 getEntityCollisionNormal(ScreenEntity *ent1, ScreenEntity *ent2);
	
	bool areEntitiesColliding(ScreenEntity *ent1, ScreenEntity *ent2);
	ScreenEntity *getEntityAtPosition(Number x, Number y);
	bool testEntityAtPosition(ScreenEntity *ent, Number x, Number y);
	
	void Shutdown();
	
	PhysicsScreenEntity *getPhysicsByScreenEntity(ScreenEntity *ent);
	void destroyMouseJoint(b2MouseJoint *mJoint);


protected:
	
	
	Number worldScale;
	
	void init(Number worldScale, Number physicsTimeStep, int physicsIterations, Vector2 physicsGravity);

	Timer *updateTimer;
	vector <PhysicsScreenEntity*> physicsChildren;
	
	ContactPoint m_points[MAX_B2DCONTACTPOINTS];
	int32 numContactPoints;
	
	b2World *world;
	Number timeStep;
	int32 iterations;
};


}