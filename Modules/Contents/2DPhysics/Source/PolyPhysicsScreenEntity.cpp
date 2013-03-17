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

#define PI 3.14159265

#include "PolyPhysicsScreenEntity.h"
#include "PolyLogger.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolyScreenEntity.h"
#include "PolyScreenMesh.h"

using namespace Polycode;

PhysicsScreenEntity::PhysicsScreenEntity(ScreenEntity *entity, b2World *world, Number worldScale, int entType, bool isStatic, Number friction, Number density, Number restitution, bool isSensor, bool fixedRotation, int groupIndex) {
	
	this->worldScale = worldScale;
	
	Vector3 entityScale = entity->getCompoundScale();
	
    Vector3 entityAngle;
    
	screenEntity = entity;

    entity->ignoreParentMatrix = true;
    entity->scale = entityScale;
    
	shape = NULL;
		
	b2BodyDef *bodyDef = new b2BodyDef();
	
	Matrix4 compoundMatrix = screenEntity->getConcatenatedMatrix();	
				
	bodyDef->position.Set(compoundMatrix.getPosition().x/worldScale, compoundMatrix.getPosition().y/worldScale);
	bodyDef->angle = screenEntity->getCombinedRoll()*(PI/180.0f);	
	bodyDef->bullet = isSensor;	
	bodyDef->fixedRotation = fixedRotation;	
	
	if(isStatic) {
		bodyDef->type = b2_staticBody;		
	} else {
		bodyDef->type = b2_dynamicBody;	
	}
	body = world->CreateBody(bodyDef);
	delete bodyDef;
		
	b2FixtureDef fDef;
	fDef.friction = friction;
	fDef.restitution = restitution;
	fDef.density = density;
	fDef.isSensor = isSensor;
	fDef.filter.groupIndex = groupIndex;
    
	fDef.userData = screenEntity;

	switch(entType) {
		case ENTITY_MESH:
		{
			b2PolygonShape *b2shape = new b2PolygonShape;			
			
			ScreenMesh* screenMesh = dynamic_cast<ScreenMesh*>(entity);
			if(screenMesh != NULL) {
				b2Vec2 *vertices = (b2Vec2*)malloc(sizeof(b2Vec2) * screenMesh->getMesh()->getVertexCount());
	
				int index = 0;
				for(int i=0; i < screenMesh->getMesh()->getPolygonCount(); i++) {
					Polycode::Polygon *poly = screenMesh->getMesh()->getPolygon(i);
					for(int j = 0; j < poly->getVertexCount(); j++) {
						vertices[index].x = poly->getVertex(j)->x/worldScale;
						vertices[index].y = poly->getVertex(j)->y/worldScale;						
						index++;
					}
				}
				b2shape->Set(vertices, screenMesh->getMesh()->getVertexCount());	
				free(vertices);
			} else {
				Logger::log("Tried to make a mesh collision object from a non-mesh\n");							
			}

			fDef.shape = b2shape;				
			shape = b2shape;
		}
		break;
		case ENTITY_RECT: 
		{
			b2PolygonShape *b2shape = new b2PolygonShape;			
			b2shape->SetAsBox(screenEntity->getWidth()/(worldScale*2.0f) * entityScale.x, screenEntity->getHeight()/(worldScale*2.0f) * entityScale.y);
			fDef.shape = b2shape;						
			shape = b2shape;
		}
		break;
        case ENTITY_EDGE: 
        {
            b2PolygonShape *b2shape = new b2PolygonShape;	
            b2shape->SetAsEdge(b2Vec2(-screenEntity->getWidth()/(worldScale*2.0f),-screenEntity->getHeight()/(2.0*worldScale)),
                               b2Vec2(screenEntity->getWidth()/(worldScale*2.0f),-screenEntity->getHeight()/(2.0*worldScale)));
            fDef.shape = b2shape;						
            shape = b2shape;                                                                
        }
        break;
		case ENTITY_CIRCLE:
		{		
			b2CircleShape *b2shape = new b2CircleShape;
			b2shape->m_radius = screenEntity->getWidth()/(worldScale*2.0f);
			fDef.shape = b2shape;
			shape = b2shape;
		}
		break;
	}
	
	fixture = body->CreateFixture(&fDef);	
	
    body->SetUserData(this);
    
	collisionOnly = false;
	
}

void PhysicsScreenEntity::applyTorque(Number torque) {
	body->ApplyTorque(torque);
}

void PhysicsScreenEntity::applyForce(Vector2 force){
	body->SetAwake(true);
	body->ApplyForce(b2Vec2(force.x,force.y), b2Vec2(body->GetPosition().x,body->GetPosition().y));
}

ScreenEntity *PhysicsScreenEntity::getScreenEntity() {
	return screenEntity;
}

void PhysicsScreenEntity::setVelocity(Number fx, Number fy) {
	body->SetAwake(true);
	b2Vec2 f = body->GetLinearVelocity();
	if(fx != 0)
		f.x = fx;
	if(fy != 0)
		f.y = fy;
	body->SetLinearVelocity(f);
}

void PhysicsScreenEntity::setVelocityX( Number fx) {
	body->SetAwake(true);
	b2Vec2 f = body->GetLinearVelocity();
	f.x = fx;	
	body->SetLinearVelocity(f);
}

void PhysicsScreenEntity::setVelocityY(Number fy) {
	body->SetAwake(true);
	b2Vec2 f = body->GetLinearVelocity();
	f.y = fy;	
	body->SetLinearVelocity(f);	
}


void PhysicsScreenEntity::setCollisionCategory(int categoryBits) {
        b2Filter filter=fixture->GetFilterData();
        filter.categoryBits = categoryBits;
        fixture->SetFilterData(filter);
}

void PhysicsScreenEntity::setCollisionMask(int maskBits) {
        b2Filter filter=fixture->GetFilterData();
        filter.maskBits = maskBits;
        fixture->SetFilterData(filter);
}

void PhysicsScreenEntity::setCollisionGroupIndex(int group) {
    b2Filter filter=fixture->GetFilterData();
    filter.groupIndex = group;
    fixture->SetFilterData(filter);    
}

void PhysicsScreenEntity::setLinearDamping(Number damping) {
    body->SetLinearDamping(damping);
}

void PhysicsScreenEntity::setAngularDamping(Number damping) {
    body->SetAngularDamping(damping);
}

void PhysicsScreenEntity::setFriction(Number friction) {
    if(fixture) {
        fixture->SetFriction(friction);
    }
}

void PhysicsScreenEntity::setDensity(Number density){
    if(fixture) {
        fixture->SetDensity(density);
    }
}

Number PhysicsScreenEntity::getLinearDamping() {
    return body->GetLinearDamping();
}

Number PhysicsScreenEntity::getAngularDamping() {
    return body->GetAngularDamping();
}

Number PhysicsScreenEntity::getFriction() {
    return fixture->GetFriction();
}

Number PhysicsScreenEntity::getDensity() {
    return fixture->GetDensity();
}

void PhysicsScreenEntity::applyImpulse(Number fx, Number fy) {
	body->SetAwake(true);
	b2Vec2 f =  b2Vec2(fx,fy);
	b2Vec2 p = body->GetWorldPoint(b2Vec2(0.0f, 0.0f));	
	body->ApplyLinearImpulse(f, p);	
}
			
void PhysicsScreenEntity::setTransform(Vector2 pos, Number angle) {
	body->SetTransform(b2Vec2(pos.x/worldScale, pos.y/worldScale), angle*(PI/180.0f));
    screenEntity->setPosition(pos);
}

void PhysicsScreenEntity::Update() {
	if(collisionOnly) {
		Matrix4 matrix = screenEntity->getConcatenatedMatrix();
		b2Vec2 newPos;
		Number newRotation;
		
		Vector3 pos = matrix.getPosition();
		newPos.x = pos.x/worldScale;
		newPos.y = pos.y/worldScale;		

		Number rx,ry,rz;

		matrix.getEulerAngles(&rx, &ry, &rz);
		newRotation = rz;

		body->SetAwake(true);
		body->SetTransform(newPos, newRotation * TORADIANS);
	} else {
		b2Vec2 position = body->GetPosition();
		Number angle = body->GetAngle();	
		screenEntity->setRotation(angle*(180.0f/PI));	
		screenEntity->setPosition(position.x*worldScale, position.y*worldScale);
		screenEntity->rebuildTransformMatrix();		
	}	
}

PhysicsScreenEntity::~PhysicsScreenEntity() {
	if (body) {
		if (fixture) {	
			body->DestroyFixture(fixture);
		}	
		body->GetWorld()->DestroyBody(body);	
	}
	delete shape;
}
