/*
 *  PolyPhysicsScreen.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 5/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyPhysicsScreen.h"

using namespace Polycode;

/*
void PhysicsScreen::Add(const b2ContactPoint* point) {
	if (numContactPoints == MAX_B2DCONTACTPOINTS) {
		return;
	}
	
	ContactPoint* cp = m_points + numContactPoints;
	cp->shape1 = point->shape1;
	cp->shape2 = point->shape2;
	cp->position = point->position;
	cp->normal = point->normal;
	cp->id = point->id;
	cp->state = e_contactAdded;
	
	++numContactPoints;
}

void PhysicsScreen::Persist(const b2ContactPoint* point) {
	if (numContactPoints == MAX_B2DCONTACTPOINTS) {
		return;
	}
	
	ContactPoint* cp = m_points + numContactPoints;
	cp->shape1 = point->shape1;
	cp->shape2 = point->shape2;
	cp->position = point->position;
	cp->normal = point->normal;
	cp->id = point->id;
	cp->state = e_contactPersisted;
	
	++numContactPoints;
}

void PhysicsScreen::Remove(const b2ContactPoint* point) {
	if (numContactPoints == MAX_B2DCONTACTPOINTS) {
		return;
	}
	
	ContactPoint* cp = m_points + numContactPoints;
	cp->shape1 = point->shape1;
	cp->shape2 = point->shape2;
	cp->position = point->position;
	cp->normal = point->normal;
	cp->id = point->id;
	cp->state = e_contactRemoved;
	
	++numContactPoints;
}
*/

void PhysicsScreen::BeginContact (b2Contact *contact) {
	PhysicsScreenEvent *newEvent = new PhysicsScreenEvent();
	newEvent->entity1 = getPhysicsEntityByFixture(contact->GetFixtureA());
	newEvent->entity2 = getPhysicsEntityByFixture(contact->GetFixtureB());			
	dispatchEvent(newEvent, PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION);
}

void PhysicsScreen::EndContact (b2Contact *contact) {
	
}


PhysicsScreen::PhysicsScreen() : Screen() {
	init(10.0f, 1.0f/60.0f,10,Vector2(0.0f, 10.0f));
}

PhysicsScreen::PhysicsScreen(float worldScale, float freq) : Screen() {
	init(worldScale, 1.0f/freq,10,Vector2(0.0f, 10.0f));	
}

void PhysicsScreen::init(float worldScale, float physicsTimeStep, int physicsIterations, Vector2 physicsGravity) {
	
	this->worldScale = worldScale;
	
	numContactPoints = 0;	
	timeStep = physicsTimeStep;
	iterations = physicsIterations;
	
	b2Vec2 gravity(physicsGravity.x,physicsGravity.y);
	bool doSleep = true;
	world  = new b2World(gravity, doSleep);
	
	world->SetContactListener(this);

	updateTimer = new Timer(true, 3);
	updateTimer->addEventListener(this, Timer::EVENT_TRIGGER);
}

void PhysicsScreen::setGravity(Vector2 newGravity) {
	world->SetGravity(b2Vec2(newGravity.x, newGravity.y));
}

PhysicsScreenEntity *PhysicsScreen::getPhysicsByScreenEntity(ScreenEntity *ent) {
	for(int i=0; i<physicsChildren.size();i++) {
		if(physicsChildren[i]->getScreenEntity() == ent)
			return physicsChildren[i];
	}	
	return NULL;
}

void PhysicsScreen::destroyJoint(PhysicsJoint *joint) {
	world->DestroyJoint(joint->box2DJoint);
}


PhysicsJoint *PhysicsScreen::createRevoluteJoint(ScreenEntity *ent1, ScreenEntity *ent2, float ax, float ay, bool enableLimit, float lowerLimit, float upperLimit, bool motorEnabled, float motorSpeed, float maxTorque) {
	PhysicsScreenEntity *pEnt1 = getPhysicsByScreenEntity(ent1);
	PhysicsScreenEntity *pEnt2 = getPhysicsByScreenEntity(ent2);
	if(pEnt1 == NULL || pEnt2 == NULL)
		return NULL;
	
	b2Vec2 anchor((ent1->getPosition().x+ax)/worldScale, (ent1->getPosition().y+ay)/worldScale);
	b2RevoluteJointDef *jointDef = new b2RevoluteJointDef();
	jointDef->collideConnected = false;
	jointDef->lowerAngle = lowerLimit * (PI/180.0f);
	jointDef->upperAngle = upperLimit * (PI/180.0f);
	jointDef->enableLimit = enableLimit;
	jointDef->motorSpeed = motorSpeed;
	jointDef->maxMotorTorque = maxTorque;
	jointDef->enableMotor = motorEnabled;	
	jointDef->Initialize(pEnt1->body, pEnt2->body, anchor);
	
	PhysicsJoint *joint = new PhysicsJoint();
	
	joint->box2DJoint = world->CreateJoint(jointDef);
	return joint;
	
}

void PhysicsScreen::createPrismaticJoint(ScreenEntity *ent1, ScreenEntity *ent2, bool collideConnected) {

}

void PhysicsScreen::wakeUp(ScreenEntity *ent) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;
		
	pEnt->body->SetAwake(true);
}


Vector2 PhysicsScreen::getVelocity(ScreenEntity *ent) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return Vector2(0,0);
	
	b2Vec2 vec = pEnt->body->GetLinearVelocity();
	return Vector2(vec.x, vec.y);
}

void PhysicsScreen::setSpin(ScreenEntity *ent, float spin) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;

	pEnt->body->SetAngularVelocity(spin);
}

void PhysicsScreen::setVelocity(ScreenEntity *ent, float fx, float fy) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;
	
	pEnt->body->SetAwake(true);
	b2Vec2 f = pEnt->body->GetLinearVelocity();
	if(fx != 0)
		f.x = fx;
	if(fy != 0)
		f.y = fy;
	
	pEnt->body->SetLinearVelocity(f);
}

void PhysicsScreen::setVelocityX(ScreenEntity *ent, float fx) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;
	
	pEnt->body->SetAwake(true);
	b2Vec2 f = pEnt->body->GetLinearVelocity();
	f.x = fx;	
	pEnt->body->SetLinearVelocity(f);
	
}

void PhysicsScreen::setVelocityY(ScreenEntity *ent, float fy) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;
	
	pEnt->body->SetAwake(true);
	b2Vec2 f = pEnt->body->GetLinearVelocity();
	f.y = fy;	
	pEnt->body->SetLinearVelocity(f);	
}


PhysicsScreenEntity *PhysicsScreen::addCollisionChild(ScreenEntity *newEntity, int entType) {
	PhysicsScreenEntity *ret;
	ret = addPhysicsChild(newEntity, entType, 0,0.1,0, true);
	ret->collisionOnly = true; 
	return ret;
}

void PhysicsScreen::setTransform(ScreenEntity *ent, Vector2 pos, float angle) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;
	pEnt->setTransform(pos, angle);
}

void PhysicsScreen::applyForce(ScreenEntity *ent, float fx, float fy) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;

	pEnt->body->SetAwake(true);
	b2Vec2 f =  b2Vec2(fx,fy);
	b2Vec2 p = pEnt->body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
		
	pEnt->body->ApplyForce(f, p);
}

void PhysicsScreen::applyImpulse(ScreenEntity *ent, float fx, float fy) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;
	
	pEnt->body->SetAwake(true);
	b2Vec2 f =  b2Vec2(fx,fy);
	b2Vec2 p = pEnt->body->GetWorldPoint(b2Vec2(0.0f, 0.0f));	
	pEnt->body->ApplyLinearImpulse(f, p);	
}



void PhysicsScreen::createDistanceJoint(ScreenEntity *ent1, ScreenEntity *ent2, bool collideConnected) {
	PhysicsScreenEntity *pEnt1 = getPhysicsByScreenEntity(ent1);
	PhysicsScreenEntity *pEnt2 = getPhysicsByScreenEntity(ent2);
	if(pEnt1 == NULL || pEnt2 == NULL)
		return;
	
	b2Vec2 a1(ent1->getPosition().x/worldScale, ent1->getPosition().y/worldScale);
	b2Vec2 a2(ent2->getPosition().x/worldScale, ent2->getPosition().y/worldScale);
	b2DistanceJointDef *jointDef = new b2DistanceJointDef();
	jointDef->Initialize(pEnt1->body, pEnt2->body, a1, a2);
	jointDef->collideConnected = collideConnected;
	world->CreateJoint(jointDef);
}
/*
b2MouseJoint *PhysicsScreen::createMouseJoint(ScreenEntity *ent1, Vector2 *mp) {
	
	PhysicsScreenEntity *pEnt1 = getPhysicsByScreenEntity(ent1);
	if(pEnt1 == NULL)
		return NULL;

	b2MouseJointDef *mj = new b2MouseJointDef();	
	mj->bodyA = world->GetGroundBody();
	mj->bodyB = pEnt1->body;
	
	b2Vec2 mpos(mp->x/10.0f, mp->y/10.0f);
	mj->target = mpos;
#ifdef TARGET_FLOAT32_IS_FIXED
	mj->maxForce = (pEnt1->body->GetMass() < 16.0)? (1000.0f * pEnt1->body->GetMass()) : float32(16000.0);
#else
	mj->maxForce = 1000.0f * pEnt1->body->GetMass();
#endif
	b2MouseJoint *m_mouseJoint = (b2MouseJoint*)world->CreateJoint(mj);
	pEnt1->body->SetAwake(true);
	Logger::log("OK %d!\n", m_mouseJoint);
	return m_mouseJoint;
}
*/

Vector2 PhysicsScreen::getEntityCollisionNormal(ScreenEntity *ent1, ScreenEntity *ent2) {
	PhysicsScreenEntity *pEnt1 = getPhysicsByScreenEntity(ent1);
	PhysicsScreenEntity *pEnt2 = getPhysicsByScreenEntity(ent2);	
	if(pEnt1 == NULL || pEnt2 == NULL)
		return Vector2(0,0);	
	
	PhysicsScreenEntity *rEnt1;
	PhysicsScreenEntity *rEnt2;
	for (int32 i = 0; i < numContactPoints; ++i)
	{
		ContactPoint* point = m_points + i;		
		if (point->state == 0 || point->state == 1) {	
			rEnt1= getPhysicsEntityByShape(point->shape1);
			rEnt2 = getPhysicsEntityByShape(point->shape2);						
			if((rEnt1 == pEnt1 && rEnt2 == pEnt2) || 
			   (rEnt1 == pEnt2 && rEnt2 == pEnt1)) {
				return Vector2(point->normal.x,point->normal.y);
			}
		}
	}
	return Vector2(0,0);	
}

bool PhysicsScreen::areEntitiesColliding(ScreenEntity *ent1, ScreenEntity *ent2) {
	PhysicsScreenEntity *pEnt1 = getPhysicsByScreenEntity(ent1);
	PhysicsScreenEntity *pEnt2 = getPhysicsByScreenEntity(ent2);	
	if(pEnt1 == NULL || pEnt2 == NULL)
		return false;
	
	PhysicsScreenEntity *rEnt1;
	PhysicsScreenEntity *rEnt2;
	for (int32 i = 0; i < numContactPoints; ++i)
	{
		ContactPoint* point = m_points + i;		
		if (point->state == 0 || point->state == 1) {	
			rEnt1= getPhysicsEntityByShape(point->shape1);
			rEnt2 = getPhysicsEntityByShape(point->shape2);						
			if((rEnt1 == pEnt1 && rEnt2 == pEnt2) || 
			   (rEnt1 == pEnt2 && rEnt2 == pEnt1)) {
				return true;
			}
		}
	}
	return false;
}

ScreenEntity *PhysicsScreen::getEntityAtPosition(float x, float y) {
	ScreenEntity *ret = NULL;
	
	b2Vec2 mousePosition;
	mousePosition.x = x/worldScale;
	mousePosition.y = y/worldScale;
	
	for(int i=0;i<physicsChildren.size();i++) {
		PhysicsScreenEntity *ent = physicsChildren[i];
		if(ent->shape->TestPoint(ent->body->GetTransform(), mousePosition))
			return ent->getScreenEntity();
	}	
	return ret;
}

bool PhysicsScreen::testEntityAtPosition(ScreenEntity *ent, float x, float y) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);	
	
	if(pEnt == NULL)
		return false;
	
	b2Vec2 mousePosition;
	mousePosition.x = x/worldScale;
	mousePosition.y = y/worldScale;
	
	if(pEnt->shape->TestPoint(pEnt->body->GetTransform(), mousePosition))
		return true;
	else
		return false;
	
}

void PhysicsScreen::destroyMouseJoint(b2MouseJoint *mJoint) {
		world->DestroyJoint(mJoint);
		mJoint = NULL;
}

PhysicsScreenEntity *PhysicsScreen::addPhysicsChild(ScreenEntity *newEntity, int entType, float friction, float density, float restitution, bool isSensor, bool fixedRotation) {
	addChild(newEntity);
	newEntity->setPositionMode(ScreenEntity::POSITION_CENTER);
	PhysicsScreenEntity *newPhysicsEntity = new PhysicsScreenEntity(newEntity, world, worldScale, entType, friction, density, restitution, isSensor,fixedRotation);
	physicsChildren.push_back(newPhysicsEntity);
	newPhysicsEntity->body->SetAwake(true);
	return newPhysicsEntity;
}

void PhysicsScreen::removePhysicsChild(PhysicsScreenEntity *entityToRemove) {
	world->DestroyBody(entityToRemove->body);
	removeChild(entityToRemove->getScreenEntity());
	for(int i=0;i<physicsChildren.size();i++) {
		if(physicsChildren[i] == entityToRemove) {
			physicsChildren.erase(physicsChildren.begin()+i);
		}
	}
}


void PhysicsScreen::Shutdown() {

}

PhysicsScreen::~PhysicsScreen() {
	delete world;
	for(int i=0; i<physicsChildren.size();i++) {
			delete physicsChildren[i];
	}
}

PhysicsScreenEntity *PhysicsScreen::getPhysicsEntityByFixture(b2Fixture *fixture) {
	for(int i=0; i < physicsChildren.size(); i++) {
		if(physicsChildren[i]->fixture == fixture)
			return physicsChildren[i];
	}
	return NULL;	
}

PhysicsScreenEntity *PhysicsScreen::getPhysicsEntityByShape(b2Shape *shape) {
	for(int i=0; i < physicsChildren.size(); i++) {
		if(physicsChildren[i]->shape == shape)
			return physicsChildren[i];
	}
	return NULL;
}
	
void PhysicsScreen::handleEvent(Event *event) {
	
	numContactPoints = 0;
	
	if(event->getDispatcher() == updateTimer) {		
		world->Step(timeStep, iterations,iterations);
	}
	/*
	for (int32 i = 0; i < numContactPoints; ++i)
	{
		ContactPoint* point = m_points + i;		
		if (point->state == 0) {	
			PhysicsScreenEvent *newEvent = new PhysicsScreenEvent();
			newEvent->entity1 = getPhysicsEntityByShape(point->shape1);
			newEvent->entity2 = getPhysicsEntityByShape(point->shape2);			
	
			dispatchEvent(newEvent, PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION);
		} else if (point->state == 1) {
			// Persist
//			DrawPoint(point->position, 5.0f, b2Color(0.3f, 0.3f, 0.95f));
		} else {
			// Remove
//			DrawPoint(point->position, 10.0f, b2Color(0.95f, 0.3f, 0.3f));
			dispatchEvent(new PhysicsScreenEvent(), PhysicsScreenEvent::EVENT_END_SHAPE_COLLISION);			
		}
	}
	*/
	Screen::handleEvent(event);
}

void PhysicsScreen::Update() {
//	unsigned int elapsed = updateTimer->getTicks();	
//	if(updateTimer->hasElapsed()) {
//		world->Step(timeStep, iterations);
		for(int i=0; i<physicsChildren.size();i++) {
			physicsChildren[i]->Update();
		}
//	}
}