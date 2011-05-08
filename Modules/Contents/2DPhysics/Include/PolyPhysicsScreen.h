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
	
class _PolyExport PhysicsScreen : public Screen, b2ContactListener {

public:
	PhysicsScreen();
	PhysicsScreen(float worldScale, float freq);

	~PhysicsScreen();
	
	void Update();
	PhysicsScreenEntity *addPhysicsChild(ScreenEntity *newEntity, int entType, float friction=0.1, float density=1, float restitution = 0, bool isSensor = false, bool fixedRotation = false);
	void removePhysicsChild(PhysicsScreenEntity *entityToRemove);
	
	PhysicsScreenEntity *addCollisionChild(ScreenEntity *newEntity, int entType);
	
	void destroyJoint(PhysicsJoint *joint);
	void createDistanceJoint(ScreenEntity *ent1, ScreenEntity *ent2, bool collideConnected);
	void createPrismaticJoint(ScreenEntity *ent1, ScreenEntity *ent2, bool collideConnected);
	PhysicsJoint *createRevoluteJoint(ScreenEntity *ent1, ScreenEntity *ent2, float ax, float ay, bool enableLimit, float lowerLimit, float upperLimit, bool motorEnabled, float motorSpeed, float maxTorque);
//	b2MouseJoint *createMouseJoint(ScreenEntity *ent1, Vector2 *mp);
	void applyForce(ScreenEntity *ent, float fx, float fy);
	void applyImpulse(ScreenEntity *ent, float fx, float fy);
	
	void setGravity(Vector2 newGravity);
	
	void setTransform(ScreenEntity *ent, Vector2 pos, float angle);
	
	PhysicsScreenEntity *getPhysicsEntityByShape(b2Shape *shape);
	PhysicsScreenEntity *getPhysicsEntityByFixture(b2Fixture *fixture);
	
	void setVelocity(ScreenEntity *ent, float fx, float fy);	
	void setVelocityX(ScreenEntity *ent, float fx);	
	void setVelocityY(ScreenEntity *ent, float fy);	
	void setSpin(ScreenEntity *ent, float spin);
	
	Vector2 getVelocity(ScreenEntity *ent);
			
	void BeginContact (b2Contact *contact);
	void EndContact (b2Contact *contact);	
	
	void wakeUp(ScreenEntity *ent);
	
	void handleEvent(Event *event);
	
	Vector2 getEntityCollisionNormal(ScreenEntity *ent1, ScreenEntity *ent2);
	
	bool areEntitiesColliding(ScreenEntity *ent1, ScreenEntity *ent2);
	ScreenEntity *getEntityAtPosition(float x, float y);
	bool testEntityAtPosition(ScreenEntity *ent, float x, float y);
	
	void Shutdown();
	
	PhysicsScreenEntity *getPhysicsByScreenEntity(ScreenEntity *ent);
	void destroyMouseJoint(b2MouseJoint *mJoint);


protected:
	
	
	float worldScale;
	
	void init(float worldScale, float physicsTimeStep, int physicsIterations, Vector2 physicsGravity);

	Timer *updateTimer;
	vector <PhysicsScreenEntity*> physicsChildren;
	
	ContactPoint m_points[MAX_B2DCONTACTPOINTS];
	int32 numContactPoints;
	
	b2World *world;
	float32 timeStep;
	int32 iterations;
};


}