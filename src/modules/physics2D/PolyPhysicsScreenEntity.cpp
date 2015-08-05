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
#include "PolyEntity.h"

using namespace Polycode;

PhysicsScene2DEntity::PhysicsScene2DEntity(Entity *entity, b2World *world, Number worldScale, int entType, bool isStatic, Number friction, Number density, Number restitution, bool isSensor, bool fixedRotation, int groupIndex) {
	
    this->fixedRotation =  fixedRotation;
	this->entity = entity;

	Vector3 entityScale = entity->getCompoundScale();
	Matrix4 compoundMatrix = entity->getConcatenatedMatrix();
	entity->ignoreParentMatrix = true;
	entity->setScale(entityScale);
	entityScale.x = fabs(entityScale.x);
	entityScale.y = fabs(entityScale.y);
	this->worldScale = worldScale;
	collisionOnly = false;

	
	// Create body definition---------------------------------------
	b2BodyDef bodyDef;
	bodyDef.position.Set(compoundMatrix.getPosition().x/worldScale, compoundMatrix.getPosition().y/worldScale);
    
    Number ax,ay,az;
    compoundMatrix.getEulerAngles(&ax, &ay, &az);
    
	bodyDef.angle = az*(PI/180.0f);
	bodyDef.bullet = isSensor;	
	bodyDef.fixedRotation = fixedRotation;	
	if(isStatic)
		bodyDef.type = b2_staticBody;
	else
		bodyDef.type = b2_dynamicBody;

	// Create the body
	body = world->CreateBody(&bodyDef);
	body->SetUserData(this);
	
	// Create fixture definition---------------------------------------------
	b2FixtureDef fDef;
	fDef.friction = friction;
	fDef.restitution = restitution;
	fDef.density = density;
	fDef.isSensor = isSensor;
	fDef.filter.groupIndex = groupIndex;

	// Create Shape definition (Circle/Rectangle/Polygon)---------------------------
	switch(entType) {
		case ENTITY_CIRCLE: {
			b2CircleShape Shape;
			fDef.shape = &Shape;
			// Set the shape
			Shape.m_radius = entity->getWidth()/(worldScale*2.0f);
			// Create the fixture
			fixture = body->CreateFixture(&fDef);
			break;
		}
		case ENTITY_RECT: {
			b2PolygonShape Shape;
			fDef.shape = &Shape;
			// Set the shape
			Shape.SetAsBox(entity->getWidth()/(worldScale*2.0f) * entityScale.x, entity->getHeight()/(worldScale*2.0f) * entityScale.y);
			// Create the fixture
			fixture = body->CreateFixture(&fDef);
			break;
		}
		case ENTITY_EDGE: {
			b2PolygonShape Shape;	
			Shape.SetAsEdge(b2Vec2(-entity->getWidth()/(worldScale*2.0f),-entity->getHeight()/(2.0*worldScale)),
							b2Vec2(entity->getWidth()/(worldScale*2.0f),-entity->getHeight()/(2.0*worldScale)));
			fDef.shape = &Shape;
			fixture = body->CreateFixture(&fDef);
			break;
        }
		case ENTITY_CAPSULE: {
		
			Number rectSize = (entity->getHeight()/(worldScale*2.0f) * entityScale.y) - (entity->getWidth()/(worldScale*2.0f * entityScale.y));
					
			b2CircleShape Shape;
			fDef.shape = &Shape;
			Shape.m_radius = entity->getWidth()/(worldScale*2.0f);			
			Shape.m_p.y = rectSize;
			fixture = body->CreateFixture(&fDef);
			Shape.m_p.y = -rectSize;
			fixture = body->CreateFixture(&fDef);
			
			b2PolygonShape Shape2;
			fDef.shape = &Shape2;
			Shape2.SetAsBox(entity->getWidth()/(worldScale*2.0f) * entityScale.x, rectSize);
			fixture = body->CreateFixture(&fDef);
			break;						
		}
		break;
		case ENTITY_TRIPLE_CIRCLE: {
		
			Number rectSize = (entity->getHeight()/(worldScale*2.0f) * entityScale.y) - (entity->getWidth()/(worldScale*2.0f * entityScale.y));
					
			b2CircleShape Shape;
			fDef.shape = &Shape;
			Shape.m_radius = entity->getWidth()/(worldScale*2.0f);			
			Shape.m_p.y = rectSize;
			fixture = body->CreateFixture(&fDef);
			Shape.m_p.y = -rectSize;
			fixture = body->CreateFixture(&fDef);
			Shape.m_p.y = 0;
			fixture = body->CreateFixture(&fDef);
			break;						
		}
		break;	
		case ENTITY_MESH:
		/*		
		{
			b2PolygonShape Shape;
			fDef.shape = &Shape;
			ScreenMesh* screenMesh = dynamic_cast<ScreenMesh*>(entity);
		
			if(screenMesh) {
				for(short i=0, polycount=screenMesh->getMesh()->getPolygonCount(); i < polycount; i++) {
					Polygon* poly = screenMesh->getMesh()->getPolygon(i);
					unsigned short vertexcount = poly->getVertexCount();
					if (vertexcount >= 3 && vertexcount <= 8) {
						b2Vec2* vertices = new b2Vec2[vertexcount];
						for(short index=0; index < vertexcount; index++) {
							vertices[index].x = poly->getVertex(index)->x/worldScale;
							vertices[index].y = poly->getVertex(index)->y/worldScale;						
						}
						// Set the shape
						Shape.Set(vertices, vertexcount);
						// Create the fixture
						fixture = body->CreateFixture(&fDef);
						delete []vertices;
					}
					else { Logger::log("Between 3 and 8 vertices allowed per polygon\n"); }
				}
			}
			else { Logger::log("Tried to make a mesh collision object from a non-mesh\n"); }
		}
		*/
		break;		
	}
}

bool PhysicsScene2DEntity::getFixedRotation() const {
    return fixedRotation;
}

void PhysicsScene2DEntity::setFixedRotation(bool val) {
    fixedRotation = val;
    
}

void PhysicsScene2DEntity::applyTorque(Number torque) {
	body->ApplyTorque(torque);
}

void PhysicsScene2DEntity::applyForce(Vector2 force){
	body->SetAwake(true);
	body->ApplyForce(b2Vec2(force.x,force.y), b2Vec2(body->GetPosition().x,body->GetPosition().y));
}

Entity *PhysicsScene2DEntity::getEntity() {
	return entity;
}

void PhysicsScene2DEntity::setVelocity(Number fx, Number fy) {
	body->SetAwake(true);
	b2Vec2 f = body->GetLinearVelocity();
	if(fx != 0)
		f.x = fx;
	if(fy != 0)
		f.y = fy;
	body->SetLinearVelocity(f);
}

void PhysicsScene2DEntity::setVelocityX( Number fx) {
	body->SetAwake(true);
	b2Vec2 f = body->GetLinearVelocity();
	f.x = fx;	
	body->SetLinearVelocity(f);
}

void PhysicsScene2DEntity::setVelocityY(Number fy) {
	body->SetAwake(true);
	b2Vec2 f = body->GetLinearVelocity();
	f.y = fy;	
	body->SetLinearVelocity(f);	
}


void PhysicsScene2DEntity::setCollisionCategory(int categoryBits) {
        b2Filter filter=fixture->GetFilterData();
        filter.categoryBits = categoryBits;
        fixture->SetFilterData(filter);
}

void PhysicsScene2DEntity::setCollisionMask(int maskBits) {
        b2Filter filter=fixture->GetFilterData();
        filter.maskBits = maskBits;
        fixture->SetFilterData(filter);
}

void PhysicsScene2DEntity::setCollisionGroupIndex(int group) {
    b2Filter filter=fixture->GetFilterData();
    filter.groupIndex = group;
    fixture->SetFilterData(filter);    
}

void PhysicsScene2DEntity::setLinearDamping(Number damping) {
    body->SetLinearDamping(damping);
}

void PhysicsScene2DEntity::setAngularDamping(Number damping) {
    body->SetAngularDamping(damping);
}

void PhysicsScene2DEntity::setFriction(Number friction) {
    if(fixture) {
        fixture->SetFriction(friction);
    }
}

void PhysicsScene2DEntity::setDensity(Number density) {
    if(fixture) {
        fixture->SetDensity(density);
    }
}

Number PhysicsScene2DEntity::getLinearDamping() {
    return body->GetLinearDamping();
}

Number PhysicsScene2DEntity::getAngularDamping() {
    return body->GetAngularDamping();
}

Number PhysicsScene2DEntity::getFriction() {
    return fixture->GetFriction();
}

Number PhysicsScene2DEntity::getDensity() {
    return fixture->GetDensity();
}

void PhysicsScene2DEntity::applyImpulse(Number fx, Number fy) {
	body->SetAwake(true);
	b2Vec2 f =  b2Vec2(fx,fy);
	b2Vec2 p = body->GetWorldPoint(b2Vec2(0.0f, 0.0f));	
	body->ApplyLinearImpulse(f, p);	
}
			
void PhysicsScene2DEntity::setTransform(Vector2 pos, Number angle) {
	if(entity->getParentEntity()) {
		Matrix4 matrix = entity->getParentEntity()->getConcatenatedMatrix();
		Vector3 parentPos = matrix.getPosition();		
		pos.x = parentPos.x + pos.x;
		pos.y = parentPos.y + pos.y;		
	}

	body->SetTransform(b2Vec2(pos.x/worldScale, pos.y/worldScale), angle*(PI/180.0f));
	Update();
}

void PhysicsScene2DEntity::Update() {
	if(collisionOnly) {
		Matrix4 matrix = entity->getConcatenatedMatrix();
		Vector3 pos = matrix.getPosition();		
		b2Vec2 newPos;
		newPos.x = pos.x/worldScale;
		newPos.y = pos.y/worldScale;   
		
		Number rx,ry,rz;
		matrix.getEulerAngles(&rx, &ry, &rz);
		
		body->SetAwake(true);
		body->SetTransform(newPos, rz * TORADIANS);
	} else {
		b2Vec2 position = body->GetPosition();
		Number angle = body->GetAngle();	
		entity->setRoll(angle*(180.0f/PI));	
		entity->setPosition(position.x*worldScale, position.y*worldScale, 0.0);
	}	
}

b2Fixture* PhysicsScene2DEntity::getFixture(unsigned short index) {
	if(fixture)	{
		short i = 0;
		for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
			if (i == index) {
				fixture = f;
				return fixture;
			}
			else {i++;}
		}
		
		Logger::log("That fixture index does not exist\n");	
		return fixture = NULL;
	}

	Logger::log("Fixturelist is for mesh only\n");
	return fixture = NULL;	
}

b2Fixture* PhysicsScene2DEntity::getFixture() { return fixture; }


// I believe that at runtime you are not supposed to edit Shapes; However you still can
// by getting a fixture(above) and then adding "->GetShape()" on the end to get the fixtures shape

PhysicsScene2DEntity::~PhysicsScene2DEntity() {
	if(body)
		body->GetWorld()->DestroyBody(body);	// DestroyBody deletes fixtures and shapes automaticaly according to box2d documentation
}