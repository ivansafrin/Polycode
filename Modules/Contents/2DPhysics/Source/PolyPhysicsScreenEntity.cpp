/*
 *  PolyPhysicsScreenEntity.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 5/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#define PI 3.14159265

#include "PolyPhysicsScreenEntity.h"

using namespace Polycode;

PhysicsScreenEntity::PhysicsScreenEntity(ScreenEntity *entity, b2World *world, float worldScale, int entType, float friction, float density, float restitution, bool isSensor, bool fixedRotation) {
	
	this->worldScale = worldScale;
	
	screenEntity = entity;
	
	bodyDef = new b2BodyDef();
	bodyDef->position.Set(screenEntity->getPosition()->x/worldScale, screenEntity->getPosition()->y/worldScale);
	bodyDef->angle = screenEntity->getRotation()*(PI/180.0f);	
	bodyDef->bullet = isSensor;	
	bodyDef->fixedRotation = fixedRotation;
	
	if(entType != ENTITY_STATICRECT)
		bodyDef->type = b2_dynamicBody;	
	
	body = world->CreateBody(bodyDef);
	
	b2FixtureDef fDef;
	fDef.friction = friction;
	fDef.restitution = restitution;
	fDef.density = density;
	fDef.isSensor = isSensor;
		
	switch(entType) {
		case ENTITY_STATICRECT:
		{
			b2PolygonShape b2shape;			
			b2shape.SetAsBox(screenEntity->getWidth()/(worldScale*2.0f), screenEntity->getHeight()/(worldScale*2.0f));
			fDef.shape = &b2shape;			
		}
		break;
		case ENTITY_RECT: 
		{
			b2PolygonShape b2shape;			
			b2shape.SetAsBox(screenEntity->getWidth()/(worldScale*2.0f), screenEntity->getHeight()/(worldScale*2.0f));
			fDef.shape = &b2shape;						
		}
		break;			
		case ENTITY_CIRCLE:
		{			
			b2CircleShape b2shape;
			b2shape.m_radius = screenEntity->getWidth()/(worldScale*2.0f);
			fDef.shape = &b2shape;
		}
		break;
	}
	
	body->CreateFixture(&fDef);	
	
	lastPosition.x = screenEntity->getPosition2D().x;
	lastPosition.y = screenEntity->getPosition2D().y;

	collisionOnly = false;
}

void PhysicsScreenEntity::applyTorque(float torque) {
	body->ApplyTorque(torque);
}

void PhysicsScreenEntity::applyForce(Vector2 force){
	body->SetAwake(true);
	body->ApplyForce(b2Vec2(force.x,force.y), b2Vec2(body->GetPosition().x,body->GetPosition().y));
}

ScreenEntity *PhysicsScreenEntity::getScreenEntity() {
	return screenEntity;
}
			
void PhysicsScreenEntity::Update() {
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	
	if(lastRotation != screenEntity->getRotation() || collisionOnly) {
		body->SetTransform(position, screenEntity->getRotation()*(PI/180.0f));		
	} else {
		screenEntity->setRotation(angle*(180.0f/PI));	
	}
	
	if(lastPosition != screenEntity->getPosition2D() || collisionOnly) {
		b2Vec2 newPos;
		newPos.x = screenEntity->getPosition2D().x/worldScale; 
		newPos.y = screenEntity->getPosition2D().y/worldScale;				
		body->SetTransform(newPos, screenEntity->getRotation()*(PI/180.0f));
		position.x = screenEntity->getPosition2D().x/worldScale; 
		position.y = screenEntity->getPosition2D().y/worldScale; 				
	} else {
		screenEntity->setPosition(position.x*worldScale, position.y*worldScale);
	}
	
	lastPosition.x = position.x*worldScale;
	lastPosition.y = position.y*worldScale;	
	
	lastRotation = angle * (180.0f/PI);
}

PhysicsScreenEntity::~PhysicsScreenEntity() {

}