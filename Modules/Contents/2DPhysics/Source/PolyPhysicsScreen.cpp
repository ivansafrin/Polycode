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
#include "PolyPhysicsScreenEntity.h"
#include "PolyCoreServices.h"
#include "PolyCore.h"

using namespace Polycode;

PhysicsScene2DEvent::PhysicsScene2DEvent() : Event() {

}

PhysicsScene2DEvent::~PhysicsScene2DEvent() {

}

Entity *PhysicsScene2DEvent::getFirstEntity() {
	return entity1;
}

Entity *PhysicsScene2DEvent::getSecondEntity() {
	return entity2;
}

void PhysicsScene2D::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    if(((PhysicsScene2DEntity*)contact->GetFixtureA()->GetBody()->GetUserData())->collisionOnly ||
       ((PhysicsScene2DEntity*)contact->GetFixtureB()->GetBody()->GetUserData())->collisionOnly) {
        contact->SetEnabled(false);
    }    
}

void PhysicsScene2D::BeginContact (b2Contact *contact) {

//	if(!contact->GetFixtureA()->IsSensor() && !contact->GetFixtureB()->IsSensor()) {
//		return;
//	}
	PhysicsScene2DEvent *newEvent = new PhysicsScene2DEvent();
	newEvent->entity1 = ((PhysicsScene2DEntity*)contact->GetFixtureA()->GetBody()->GetUserData())->getEntity();
	newEvent->entity2 = ((PhysicsScene2DEntity*)contact->GetFixtureB()->GetBody()->GetUserData())->getEntity();

    if(((PhysicsScene2DEntity*)contact->GetFixtureA()->GetBody()->GetUserData())->collisionOnly ||
        ((PhysicsScene2DEntity*)contact->GetFixtureB()->GetBody()->GetUserData())->collisionOnly) {
        contact->SetEnabled(false);
    }
       
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

    newEvent->contact = contact;
    
	newEvent->setEventCode(PhysicsScene2DEvent::EVENT_NEW_SHAPE_COLLISION);
	eventsToDispatch.push_back(newEvent);
	
	contacts.push_back(contact);
}

void PhysicsScene2D::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
	PhysicsScene2DEvent *newEvent = new PhysicsScene2DEvent();
	newEvent->entity1 = ((PhysicsScene2DEntity*)contact->GetFixtureA()->GetBody()->GetUserData())->getEntity();
	newEvent->entity2 = ((PhysicsScene2DEntity*)contact->GetFixtureB()->GetBody()->GetUserData())->getEntity();

    
    if(((PhysicsScene2DEntity*)contact->GetFixtureA()->GetBody()->GetUserData())->collisionOnly ||
       ((PhysicsScene2DEntity*)contact->GetFixtureB()->GetBody()->GetUserData())->collisionOnly) {
        contact->SetEnabled(false);
    }

    
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
    
    newEvent->contact = contact;
	for(int i=0; i < manifold->pointCount; i++) {
		if(impulse->normalImpulses[i] > newEvent->impactStrength)
			newEvent->impactStrength = impulse->normalImpulses[i];
			
		if(impulse->tangentImpulses[i] > newEvent->frictionStrength)
			newEvent->frictionStrength = impulse->tangentImpulses[i];		
	}

	newEvent->setEventCode(PhysicsScene2DEvent::EVENT_SOLVE_SHAPE_COLLISION);
	eventsToDispatch.push_back(newEvent);

}

void PhysicsScene2D::EndContact (b2Contact *contact) {
	PhysicsScene2DEvent *newEvent = new PhysicsScene2DEvent();
	newEvent->entity1 = ((PhysicsScene2DEntity*)contact->GetFixtureA()->GetBody()->GetUserData())->getEntity();
	newEvent->entity2 = ((PhysicsScene2DEntity*)contact->GetFixtureB()->GetBody()->GetUserData())->getEntity();
    newEvent->contact = contact;
    
	for(int i=0; i < contacts.size(); i++) {
		if(contacts[i] == contact) {
			contacts.erase(contacts.begin()+i);
			break;
		}
	}
	newEvent->setEventCode(PhysicsScene2DEvent::EVENT_END_SHAPE_COLLISION);
	eventsToDispatch.push_back(newEvent);

}

bool PhysicsScene2D::isEntityColliding(Entity *ent1) {
	PhysicsScene2DEntity *pEnt1 = getPhysicsByEntity(ent1);
	if(pEnt1 == NULL)
		return false;

	for(int i=0; i < contacts.size(); i++) {
		Entity *cEnt1 = ((PhysicsScene2DEntity*)contacts[i]->GetFixtureA()->GetBody()->GetUserData())->getEntity();
		Entity *cEnt2 = ((PhysicsScene2DEntity*)contacts[i]->GetFixtureB()->GetBody()->GetUserData())->getEntity();
		if(cEnt1 == ent1 || cEnt2 == ent1) {
			return true;
		}
	}
	return false;
}

bool PhysicsScene2D::testEntityCollision(Entity *ent1, Entity *ent2) {
	PhysicsScene2DEntity *pEnt1 = getPhysicsByEntity(ent1);
	PhysicsScene2DEntity *pEnt2 = getPhysicsByEntity(ent2);	
	if(pEnt1 == NULL || pEnt2 == NULL)
		return false;
	
	for(int i=0; i < contacts.size(); i++) {
		Entity *cEnt1 = ((PhysicsScene2DEntity*)contacts[i]->GetFixtureA()->GetBody()->GetUserData())->getEntity();
		Entity *cEnt2 = ((PhysicsScene2DEntity*)contacts[i]->GetFixtureB()->GetBody()->GetUserData())->getEntity();
		
	        
		if((cEnt1 == ent1 && cEnt2 == ent2) || (cEnt1 == ent2 && cEnt2 == ent1)) {
			return true;
		}
	}
	return false;
}

PhysicsScene2D::PhysicsScene2D() : Scene(Scene::SCENE_2D) {
	init(10.0f,10,10,Vector2(0.0f, -10.0f));
}

PhysicsScene2D::PhysicsScene2D(Number worldScale, int velIterations, int posIterations): Scene(Scene::SCENE_2D) {
	init(worldScale, velIterations, posIterations, Vector2(0.0f, -10.0f));
}

void PhysicsScene2D::init(Number worldScale, int velIterations, int posIterations, Vector2 physicsGravity) {
	
	this->worldScale = worldScale;
	
	velocityIterations = velIterations;
    positionIterations = posIterations;
	
	b2Vec2 gravity(physicsGravity.x,physicsGravity.y);
	bool doSleep = true;
	world  = new b2World(gravity, doSleep);
    
	world->SetContactListener(this);
}

void PhysicsScene2D::setGravity(Vector2 newGravity) {
	world->SetGravity(b2Vec2(newGravity.x, newGravity.y));
}
                                
PhysicsScene2DEntity *PhysicsScene2D::getPhysicsByEntity(Entity *ent) {
	for(int i=0; i<physicsChildren.size();i++) {
		if(physicsChildren[i]->getEntity() == ent)
			return physicsChildren[i];
	}	
	return NULL;
}

void PhysicsScene2D::destroyJoint(PhysicsJoint *joint) {
	world->DestroyJoint(joint->box2DJoint);
}


PhysicsJoint *PhysicsScene2D::createRevoluteJoint(Entity *ent1, Entity *ent2, Number ax, Number ay, bool collideConnected, bool enableLimit, Number lowerLimit, Number upperLimit, bool motorEnabled, Number motorSpeed, Number maxTorque) {
	PhysicsScene2DEntity *pEnt1 = getPhysicsByEntity(ent1);
	PhysicsScene2DEntity *pEnt2 = getPhysicsByEntity(ent2);
	if(pEnt1 == NULL || pEnt2 == NULL)
    {
		return NULL;
	}
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

PhysicsJoint *PhysicsScene2D::createPrismaticJoint(Entity *ent1, Entity *ent2, Vector2 worldAxis, Number ax, Number ay, bool collideConnected, Number lowerTranslation, Number upperTranslation, bool enableLimit, Number motorSpeed, Number motorForce, bool motorEnabled) {
	PhysicsScene2DEntity *pEnt1 = getPhysicsByEntity(ent1);
	PhysicsScene2DEntity *pEnt2 = getPhysicsByEntity(ent2);
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

void PhysicsScene2D::wakeUp(Entity *ent) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);
	if(pEnt == NULL)
		return;
		
	pEnt->body->SetAwake(true);
}


Vector2 PhysicsScene2D::getVelocity(Entity *ent) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);
	if(pEnt == NULL)
		return Vector2(0,0);
	
	b2Vec2 vec = pEnt->body->GetLinearVelocity();
	return Vector2(vec.x, vec.y);
}

void PhysicsScene2D::setAngularVelocity(Entity *ent, Number spin) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);
	if(pEnt == NULL)
		return;

	pEnt->body->SetAngularVelocity(spin);
}

void PhysicsScene2D::setVelocity(Entity *ent, Number fx, Number fy) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);
	if(pEnt == NULL)
		return;
	pEnt->setVelocity(fx, fy);	
}

void PhysicsScene2D::setVelocityX(Entity *ent, Number fx) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);
	if(pEnt == NULL)
		return;
	pEnt->setVelocityX(fx);
}

void PhysicsScene2D::setVelocityY(Entity *ent, Number fy) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);
	if(pEnt == NULL)
		return;
	pEnt->setVelocityY(fy);
}


PhysicsScene2DEntity *PhysicsScene2D::addCollisionChild(Entity *newEntity, int entType, int groupIndex, bool sensorOnly) {
	PhysicsScene2DEntity *ret;
	ret = addPhysicsChild(newEntity, entType, false, 0,0,0, sensorOnly, false, groupIndex);
	newEntity->ignoreParentMatrix = false;    
	ret->collisionOnly = true; 
	return ret;
}

PhysicsScene2DEntity *PhysicsScene2D::trackCollisionChild(Entity *newEntity, int entType, int groupIndex) {
	PhysicsScene2DEntity *ret;
	ret = trackPhysicsChild(newEntity, entType, false, 0,0.0,0, true, false, groupIndex);
	ret->collisionOnly = true;
	newEntity->ignoreParentMatrix = false;
	return ret;
}

void PhysicsScene2D::setTransform(Entity *ent, Vector2 pos, Number angle) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);
	if(pEnt == NULL)
		return;
	pEnt->setTransform(pos, angle);
}

void PhysicsScene2D::applyForce(Entity *ent, Number fx, Number fy) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);
	if(pEnt == NULL)
		return;

	pEnt->body->SetAwake(true);
	b2Vec2 f =  b2Vec2(fx,fy);
	b2Vec2 p = pEnt->body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
		
	pEnt->body->ApplyForce(f, p);
}

void PhysicsScene2D::applyImpulse(Entity *ent, Number fx, Number fy) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);
	if(pEnt == NULL)
		return;
	pEnt->applyImpulse(fx, fy);
}


PhysicsJoint *PhysicsScene2D::createDistanceJoint(Entity *ent1, Entity *ent2, bool collideConnected) {
	PhysicsScene2DEntity *pEnt1 = getPhysicsByEntity(ent1);
	PhysicsScene2DEntity *pEnt2 = getPhysicsByEntity(ent2);
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
b2MouseJoint *PhysicsScene2D::createMouseJoint(Entity *ent1, Vector2 *mp) {
	
	PhysicsScene2DEntity *pEnt1 = getPhysicsByEntity(ent1);
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

Entity *PhysicsScene2D::getEntityAtPosition(Number x, Number y) {
	Entity *ret = NULL;
	
	b2Vec2 mousePosition;
	mousePosition.x = x/worldScale;
	mousePosition.y = y/worldScale;
	
	for(int i=0;i<physicsChildren.size();i++) {
		PhysicsScene2DEntity *ent = physicsChildren[i];
		if(ent->fixture) {
			for (b2Fixture* f = ent->body->GetFixtureList(); f; f = f->GetNext()) {
				if(f->TestPoint(mousePosition)) {
					return ent->getEntity();
				}
			}
		}
	}	
	return ret;
}

bool PhysicsScene2D::testEntityAtPosition(Entity *ent, Number x, Number y) {
	PhysicsScene2DEntity *pEnt = getPhysicsByEntity(ent);	
	
	if(pEnt == NULL)
		return false;
	
	b2Vec2 mousePosition;
	mousePosition.x = x/worldScale;
	mousePosition.y = y/worldScale;
	
	if(pEnt->fixture) {
		for (b2Fixture* f = pEnt->body->GetFixtureList(); f; f = f->GetNext()) {
			if(f->TestPoint(mousePosition))
				return true;
			else
				return false;
		}
	}
	return false;
}

void PhysicsScene2D::destroyMouseJoint(b2MouseJoint *mJoint) {
		world->DestroyJoint(mJoint);
		mJoint = NULL;
}

PhysicsScene2DEntity *PhysicsScene2D::addPhysicsChild(Entity *newEntity, int entType, bool isStatic, Number friction, Number density, Number restitution, bool isSensor, bool fixedRotation, int groupIndex) {
	addChild(newEntity);
	return trackPhysicsChild(newEntity, entType, isStatic, friction, density, restitution, isSensor, fixedRotation, groupIndex);

}

PhysicsScene2DEntity *PhysicsScene2D::trackPhysicsChild(Entity *newEntity, int entType, bool isStatic, Number friction, Number density, Number restitution, bool isSensor, bool fixedRotation, int groupIndex) {

	PhysicsScene2DEntity *newPhysicsEntity = new PhysicsScene2DEntity(newEntity, world, worldScale, entType, isStatic, friction, density, restitution, isSensor,fixedRotation, groupIndex);
	physicsChildren.push_back(newPhysicsEntity);
	newPhysicsEntity->body->SetAwake(true);
	return newPhysicsEntity;
}

void PhysicsScene2D::stopTrackingChild(Entity *entity) {
	PhysicsScene2DEntity *physicsEntityToRemove = getPhysicsByEntity(entity);
	if(!physicsEntityToRemove) {
		return;
	}
	
	world->DestroyBody(physicsEntityToRemove->body);
	physicsEntityToRemove->body = NULL;	
				
	for(int i=0;i<physicsChildren.size();i++) {
		if(physicsChildren[i] == physicsEntityToRemove) {
			physicsChildren.erase(physicsChildren.begin()+i);
		}
	}
	
	delete physicsEntityToRemove;
}

void PhysicsScene2D::removePhysicsChild(Entity *entityToRemove) {
	stopTrackingChild(entityToRemove);
	Scene::removeEntity(entityToRemove);	
}

void PhysicsScene2D::removeChild(Entity *entityToRemove) {
	if(getPhysicsByEntity(entityToRemove)) {
		removePhysicsChild(entityToRemove);
	} else {
		Scene::removeEntity(entityToRemove);	
	}
}

void PhysicsScene2D::Shutdown() {

}

PhysicsScene2D::~PhysicsScene2D() {
	for(int i=0; i<physicsChildren.size();i++) {
			delete physicsChildren[i];
	}
	delete world;	
}

PhysicsScene2DEntity *PhysicsScene2D::getPhysicsEntityByFixture(b2Fixture *fixture) {
	for(int i=0; i < physicsChildren.size(); i++) {											
		for (b2Fixture* f = physicsChildren[i]->body->GetFixtureList(); f; f = f->GetNext()) {
			if(f == fixture)
				return physicsChildren[i];
		}
	}
	return NULL;	
}

PhysicsScene2DEntity *PhysicsScene2D::getPhysicsEntityByShape(b2Shape *shape) {
	for(int i=0; i < physicsChildren.size(); i++) {
		for (b2Fixture *f = physicsChildren[i]->body->GetFixtureList(); f; f = f->GetNext()) {
			if(f->GetShape() == shape)
				return physicsChildren[i];
		}
	}
	return NULL;
}
	
void PhysicsScene2D::handleEvent(Event *event) {	
	Scene::handleEvent(event);
}

void PhysicsScene2D::fixedUpdate() {
    
    for(int i=0; i<physicsChildren.size();i++) {
        if(physicsChildren[i]->collisionOnly) {
            physicsChildren[i]->Update();
        }
    }
    world->Step(core->getFixedTimestep(), velocityIterations,positionIterations);
    
    for(int i=0; i<physicsChildren.size();i++) {
        if(!physicsChildren[i]->collisionOnly) {
            physicsChildren[i]->Update();
        }
    }
		
    for(int i=0; i < eventsToDispatch.size(); i++) {
        dispatchEvent(eventsToDispatch[i], eventsToDispatch[i]->getEventCode());
    }
    eventsToDispatch.clear();
	Scene::fixedUpdate();
}
