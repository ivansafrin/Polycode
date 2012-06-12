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


#include "PolyPhysicsScreen.h"
#include "PolyScreenEntity.h"
#include "PolyPhysicsScreenEntity.h"

using namespace Polycode;

PhysicsScreenEvent::PhysicsScreenEvent() : Event() {

}

PhysicsScreenEvent::~PhysicsScreenEvent() {

}

ScreenEntity *PhysicsScreenEvent::getFirstEntity() {
	return entity1;
}

ScreenEntity *PhysicsScreenEvent::getSecondEntity() {
	return entity2;
}


void PhysicsScreen::BeginContact (b2Contact *contact) {

//	if(!contact->GetFixtureA()->IsSensor() && !contact->GetFixtureB()->IsSensor()) {
//		return;
//	}
	
	PhysicsScreenEvent *newEvent = new PhysicsScreenEvent();
	newEvent->entity1 = getPhysicsEntityByFixture(contact->GetFixtureA())->getScreenEntity();
	newEvent->entity2 = getPhysicsEntityByFixture(contact->GetFixtureB())->getScreenEntity();			

	b2Manifold *manifold = contact->GetManifold();
	b2Vec2 nor = manifold->localNormal;
	b2Vec2 point = manifold->localPoint;
	

	b2WorldManifold w_manifold;
	contact->GetWorldManifold(&w_manifold);
	b2Vec2 w_nor = w_manifold.normal;

	newEvent->localCollisionNormal.x = nor.x;
	newEvent->localCollisionNormal.y = nor.y;	
	newEvent->worldCollisionNormal.x = w_nor.x;
	newEvent->worldCollisionNormal.y = w_nor.y;	

	newEvent->localCollisionPoint.x = point.x * worldScale;
	newEvent->localCollisionPoint.y = point.y * worldScale;	
	
	newEvent->worldCollisionPoint.x = w_manifold.points[0].x * worldScale;
	newEvent->worldCollisionPoint.y = w_manifold.points[0].y * worldScale;
	
	newEvent->impactStrength = 0;
	newEvent->frictionStrength = 0;

	dispatchEvent(newEvent, PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION);
	
	contacts.push_back(contact);
}

void PhysicsScreen::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	PhysicsScreenEvent *newEvent = new PhysicsScreenEvent();
	newEvent->entity1 = getPhysicsEntityByFixture(contact->GetFixtureA())->getScreenEntity();
	newEvent->entity2 = getPhysicsEntityByFixture(contact->GetFixtureB())->getScreenEntity();			

	b2Manifold *manifold = contact->GetManifold();
	b2Vec2 nor = manifold->localNormal;
	b2Vec2 point = manifold->points[0].localPoint;
	

	b2WorldManifold w_manifold;
	contact->GetWorldManifold(&w_manifold);
	b2Vec2 w_nor = w_manifold.normal;

	newEvent->localCollisionNormal.x = nor.x;
	newEvent->localCollisionNormal.y = nor.y;	
	newEvent->worldCollisionNormal.x = w_nor.x;
	newEvent->worldCollisionNormal.y = w_nor.y;	

	newEvent->localCollisionPoint.x = point.x * worldScale;
	newEvent->localCollisionPoint.y = point.y * worldScale;	
	newEvent->worldCollisionPoint.x = w_manifold.points[0].x * worldScale;
	newEvent->worldCollisionPoint.y = w_manifold.points[0].y * worldScale;
	
	
	newEvent->impactStrength = 0;
	newEvent->frictionStrength = 0;

	for(int i=0; i < manifold->pointCount; i++) {
		if(impulse->normalImpulses[i] > newEvent->impactStrength)
			newEvent->impactStrength = impulse->normalImpulses[i];
			
		if(impulse->tangentImpulses[i] > newEvent->frictionStrength)
			newEvent->frictionStrength = impulse->tangentImpulses[i];		
	}

	dispatchEvent(newEvent, PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION);
}

void PhysicsScreen::EndContact (b2Contact *contact) {
	PhysicsScreenEvent *newEvent = new PhysicsScreenEvent();
	newEvent->entity1 = getPhysicsEntityByFixture(contact->GetFixtureA())->getScreenEntity();
	newEvent->entity2 = getPhysicsEntityByFixture(contact->GetFixtureB())->getScreenEntity();
	
	for(int i=0; i < contacts.size(); i++) {
		if(contacts[i] == contact) {
			contacts.erase(contacts.begin()+i);
			break;
		}
	}
	
	dispatchEvent(newEvent, PhysicsScreenEvent::EVENT_END_SHAPE_COLLISION);
}

bool PhysicsScreen::testEntityCollision(ScreenEntity *ent1, ScreenEntity *ent2) {
	PhysicsScreenEntity *pEnt1 = getPhysicsByScreenEntity(ent1);
	PhysicsScreenEntity *pEnt2 = getPhysicsByScreenEntity(ent2);	
	if(pEnt1 == NULL || pEnt2 == NULL)
		return false;
	
	for(int i=0; i < contacts.size(); i++) {
		ScreenEntity *cEnt1 = getPhysicsEntityByFixture(contacts[i]->GetFixtureA())->getScreenEntity();
		ScreenEntity *cEnt2 = getPhysicsEntityByFixture(contacts[i]->GetFixtureB())->getScreenEntity();
		
		if((cEnt1 == ent1 && cEnt2 == ent2) || (cEnt1 == ent2 && cEnt2 == ent1)) {
			return true;
		}
	}
	return false;
}

PhysicsScreen::PhysicsScreen() : Screen() {
	init(10.0f, 1.0f/60.0f,10,Vector2(0.0f, 10.0f));
}

PhysicsScreen::PhysicsScreen(Number worldScale, Number freq) : Screen() {
	init(worldScale, 1.0f/freq,10,Vector2(0.0f, 10.0f));	
}

void PhysicsScreen::init(Number worldScale, Number physicsTimeStep, int physicsIterations, Vector2 physicsGravity) {
	
	this->worldScale = worldScale;
	
	timeStep = physicsTimeStep;
	iterations = physicsIterations;
	
	b2Vec2 gravity(physicsGravity.x,physicsGravity.y);
	bool doSleep = true;
	world  = new b2World(gravity, doSleep);
	
	world->SetContactListener(this);

//	updateTimer = new Timer(true, 3);
//	updateTimer->addEventListener(this, Timer::EVENT_TRIGGER);
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


PhysicsJoint *PhysicsScreen::createRevoluteJoint(ScreenEntity *ent1, ScreenEntity *ent2, Number ax, Number ay, bool collideConnected, bool enableLimit, Number lowerLimit, Number upperLimit, bool motorEnabled, Number motorSpeed, Number maxTorque) {
	PhysicsScreenEntity *pEnt1 = getPhysicsByScreenEntity(ent1);
	PhysicsScreenEntity *pEnt2 = getPhysicsByScreenEntity(ent2);
	if(pEnt1 == NULL || pEnt2 == NULL)
		return NULL;
	
	b2Vec2 anchor((ent1->getPosition().x+ax)/worldScale, (ent1->getPosition().y+ay)/worldScale);
	b2RevoluteJointDef *jointDef = new b2RevoluteJointDef();
	jointDef->collideConnected = collideConnected;
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

PhysicsJoint *PhysicsScreen::createPrismaticJoint(ScreenEntity *ent1, ScreenEntity *ent2, Vector2 worldAxis, Number ax, Number ay, bool collideConnected, Number lowerTranslation, Number upperTranslation, bool enableLimit, Number motorSpeed, Number motorForce, bool motorEnabled) {
	PhysicsScreenEntity *pEnt1 = getPhysicsByScreenEntity(ent1);
	PhysicsScreenEntity *pEnt2 = getPhysicsByScreenEntity(ent2);
	if(pEnt1 == NULL || pEnt2 == NULL)
		return NULL;
	
	b2Vec2 anchor((ent1->getPosition().x+ax)/worldScale, (ent1->getPosition().y+ay)/worldScale);
	
	b2PrismaticJointDef *jointDef = new b2PrismaticJointDef();
	jointDef->collideConnected = collideConnected;
	
	jointDef->lowerTranslation = lowerTranslation/worldScale;
	jointDef->upperTranslation = upperTranslation/worldScale;
	jointDef->enableLimit = enableLimit;
	
	jointDef->motorSpeed = motorSpeed;
	jointDef->maxMotorForce = motorForce;
	jointDef->enableMotor = motorEnabled;	
	
	b2Vec2 _worldAxis(worldAxis.x, worldAxis.y);
	
	jointDef->Initialize(pEnt1->body, pEnt2->body, anchor, _worldAxis);
	
	PhysicsJoint *joint = new PhysicsJoint();	
	joint->box2DJoint = world->CreateJoint(jointDef);
	return joint;

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

void PhysicsScreen::setSpin(ScreenEntity *ent, Number spin) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;

	pEnt->body->SetAngularVelocity(spin);
}

void PhysicsScreen::setVelocity(ScreenEntity *ent, Number fx, Number fy) {
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

void PhysicsScreen::setVelocityX(ScreenEntity *ent, Number fx) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;
	
	pEnt->body->SetAwake(true);
	b2Vec2 f = pEnt->body->GetLinearVelocity();
	f.x = fx;	
	pEnt->body->SetLinearVelocity(f);
	
}

void PhysicsScreen::setVelocityY(ScreenEntity *ent, Number fy) {
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
	ret = addPhysicsChild(newEntity, entType, false, 0,0.1,0, true);
	ret->collisionOnly = true; 
	return ret;
}

void PhysicsScreen::setTransform(ScreenEntity *ent, Vector2 pos, Number angle) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;
	pEnt->setTransform(pos, angle);
}

void PhysicsScreen::applyForce(ScreenEntity *ent, Number fx, Number fy) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;

	pEnt->body->SetAwake(true);
	b2Vec2 f =  b2Vec2(fx,fy);
	b2Vec2 p = pEnt->body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
		
	pEnt->body->ApplyForce(f, p);
}

void PhysicsScreen::applyImpulse(ScreenEntity *ent, Number fx, Number fy) {
	PhysicsScreenEntity *pEnt = getPhysicsByScreenEntity(ent);
	if(pEnt == NULL)
		return;
	
	pEnt->body->SetAwake(true);
	b2Vec2 f =  b2Vec2(fx,fy);
	b2Vec2 p = pEnt->body->GetWorldPoint(b2Vec2(0.0f, 0.0f));	
	pEnt->body->ApplyLinearImpulse(f, p);	
}



PhysicsJoint *PhysicsScreen::createDistanceJoint(ScreenEntity *ent1, ScreenEntity *ent2, bool collideConnected) {
	PhysicsScreenEntity *pEnt1 = getPhysicsByScreenEntity(ent1);
	PhysicsScreenEntity *pEnt2 = getPhysicsByScreenEntity(ent2);
	if(pEnt1 == NULL || pEnt2 == NULL)
		return NULL;
	
	b2Vec2 a1(ent1->getPosition().x/worldScale, ent1->getPosition().y/worldScale);
	b2Vec2 a2(ent2->getPosition().x/worldScale, ent2->getPosition().y/worldScale);
	b2DistanceJointDef *jointDef = new b2DistanceJointDef();
	jointDef->Initialize(pEnt1->body, pEnt2->body, a1, a2);
	jointDef->collideConnected = collideConnected;
	
	PhysicsJoint *joint = new PhysicsJoint();	
	joint->box2DJoint = world->CreateJoint(jointDef);
	return joint;	
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
#ifdef TARGET_Number_IS_FIXED
	mj->maxForce = (pEnt1->body->GetMass() < 16.0)? (1000.0f * pEnt1->body->GetMass()) : Number(16000.0);
#else
	mj->maxForce = 1000.0f * pEnt1->body->GetMass();
#endif
	b2MouseJoint *m_mouseJoint = (b2MouseJoint*)world->CreateJoint(mj);
	pEnt1->body->SetAwake(true);
	Logger::log("OK %d!\n", m_mouseJoint);
	return m_mouseJoint;
}
*/

ScreenEntity *PhysicsScreen::getEntityAtPosition(Number x, Number y) {
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

bool PhysicsScreen::testEntityAtPosition(ScreenEntity *ent, Number x, Number y) {
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

PhysicsScreenEntity *PhysicsScreen::addPhysicsChild(ScreenEntity *newEntity, int entType, bool isStatic, Number friction, Number density, Number restitution, bool isSensor, bool fixedRotation) {
	addChild(newEntity);
	newEntity->setPositionMode(ScreenEntity::POSITION_CENTER);
	PhysicsScreenEntity *newPhysicsEntity = new PhysicsScreenEntity(newEntity, world, worldScale, entType, isStatic, friction, density, restitution, isSensor,fixedRotation);
	physicsChildren.push_back(newPhysicsEntity);
	newPhysicsEntity->body->SetAwake(true);
	return newPhysicsEntity;
}

void PhysicsScreen::removePhysicsChild(ScreenEntity *entityToRemove) {
	PhysicsScreenEntity *physicsEntityToRemove = getPhysicsByScreenEntity(entityToRemove);
	if(!physicsEntityToRemove) {
		return;
	}
	world->DestroyBody(physicsEntityToRemove->body);
	for(int i=0;i<physicsChildren.size();i++) {
		if(physicsChildren[i] == physicsEntityToRemove) {
			physicsChildren.erase(physicsChildren.begin()+i);
		}
	}
	Screen::removeChild(entityToRemove);	
}

ScreenEntity* PhysicsScreen::removeChild(ScreenEntity *entityToRemove) {
	if(getPhysicsByScreenEntity(entityToRemove)) {
		removePhysicsChild(entityToRemove);
	} else {
		Screen::removeChild(entityToRemove);	
	}
	return entityToRemove;
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
	Screen::handleEvent(event);
}

void PhysicsScreen::Update() {
	for(int i=0; i<physicsChildren.size();i++) {
		physicsChildren[i]->Update();
	}
	world->Step(timeStep, iterations,iterations);	
}
