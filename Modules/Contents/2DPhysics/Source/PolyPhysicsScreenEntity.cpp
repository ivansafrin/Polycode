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

PhysicsScreenEntity::PhysicsScreenEntity(ScreenEntity *entity, b2World *world, int entType, float friction, float density, float restitution, bool isSensor) {
	screenEntity = entity;
	
	bodyDef = new b2BodyDef();
	bodyDef->position.Set(screenEntity->getPosition()->x/10.0f, screenEntity->getPosition()->y/10.0f);
	bodyDef->angle = screenEntity->getRotation()*(PI/180.0f);
	body = world->CreateBody(bodyDef);
	bodyDef->isBullet = isSensor;
	
	switch(entType) {
		case ENTITY_STATICRECT:{
			b2PolygonDef *groundShapeDef = new b2PolygonDef();
			groundShapeDef->isSensor = isSensor;
			groundShapeDef->SetAsBox(screenEntity->getWidth()/20.0f, screenEntity->getHeight()/20.0f);
			shape = body->CreateShape(groundShapeDef);
		}
		break;
		case ENTITY_RECT: {
			b2PolygonDef *shapeDef;
			shapeDef = new b2PolygonDef();
			shapeDef->SetAsBox(screenEntity->getWidth()/20.0f, screenEntity->getHeight()/20.0f);
			shapeDef->density = density;
			shapeDef->friction = friction;
			shapeDef->restitution = restitution;
			shapeDef->isSensor = isSensor;			
			shape = body->CreateShape(shapeDef);
			}
		break;			
		case ENTITY_CIRCLE: {
			b2CircleDef *shapeDef = new b2CircleDef();
			shapeDef->radius = screenEntity->getWidth()/20.0f;
			shapeDef->density = density;
//			shapeDef->SetAsBox(screenEntity->getWidth()/20.0f, screenEntity->getHeight()/20.0f);
			shapeDef->friction = friction;
			shapeDef->restitution = restitution;
			shapeDef->isSensor = isSensor;				
			shape = body->CreateShape(shapeDef);
			}
		break;
	}
	
	lastPosition.x = screenEntity->getPosition2D().x;
	lastPosition.y = screenEntity->getPosition2D().y;

	body->SetMassFromShapes();

	collisionOnly = false;
}

void PhysicsScreenEntity::applyTorque(float torque) {
	body->ApplyTorque(torque);
}

void PhysicsScreenEntity::applyForce(Vector2 force){
	body->WakeUp();
	body->ApplyForce(b2Vec2(force.x,force.y), b2Vec2(body->GetPosition().x,body->GetPosition().y));
}

ScreenEntity *PhysicsScreenEntity::getScreenEntity() {
	return screenEntity;
}
			
void PhysicsScreenEntity::Update() {
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	if(lastRotation != screenEntity->getRotation() || collisionOnly) {
		body->SetXForm(position, screenEntity->getRotation()*(PI/180.0f));		
	} else {
		screenEntity->setRotation(angle*(180.0f/PI));	
	}
	
	if(lastPosition != screenEntity->getPosition2D() || collisionOnly) {
		b2Vec2 newPos;
		newPos.x = screenEntity->getPosition2D().x/10.0f; 
		newPos.y = screenEntity->getPosition2D().y/10.0f;				
		body->SetXForm(newPos, screenEntity->getRotation()*(PI/180.0f));
		position.x = screenEntity->getPosition2D().x/10.0f; 
		position.y = screenEntity->getPosition2D().y/10.0f; 				
	} else {
		screenEntity->setPosition(position.x*10.0f, position.y*10.0f);
	}
	
	lastPosition.x = position.x*10.0f;
	lastPosition.y = position.y*10.0f;	
	
	lastRotation = angle * (180.0f/PI);
}

PhysicsScreenEntity::~PhysicsScreenEntity() {

}