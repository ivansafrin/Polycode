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
	
	screenEntity = entity;

	Vector3 entityScale = entity->getCompoundScale();
	this->worldScale = worldScale;
	collisionOnly = false;

	
	// Create body definition---------------------------------------
	b2BodyDef bodyDef;
	bodyDef.position.Set(screenEntity->getPosition2D().x/worldScale, screenEntity->getPosition2D().y/worldScale);
	bodyDef.angle = screenEntity->getRotation()*(PI/180.0f);	
	bodyDef.bullet = isSensor;	
	bodyDef.fixedRotation = fixedRotation;	
	if(isStatic)
		bodyDef.type = b2_staticBody;
	else
		bodyDef.type = b2_dynamicBody;

		// Create the body
	body = world->CreateBody(&bodyDef);
	
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
			// Set fixture shape to shape definition
			fDef.shape = &Shape;
			// Create the shape
			Shape.m_radius = screenEntity->getWidth()/(worldScale*2.0f);
			// Create the fixture
			fixture = body->CreateFixture(&fDef);
			break;
		}
		case ENTITY_RECT: {
			b2PolygonShape Shape;
			// Set fixture shape to shape definition
			fDef.shape = &Shape;
			// Create the shape
			Shape.SetAsBox(screenEntity->getWidth()/(worldScale*2.0f) * entityScale.x, screenEntity->getHeight()/(worldScale*2.0f) * entityScale.y);
			// Create the fixture
			fixture = body->CreateFixture(&fDef);
			break;
		}
		case ENTITY_MESH: {
			b2PolygonShape Shape;
			// Set fixture shape to shape definition
			fDef.shape = &Shape;
			// Get the screenmesh of the entity
			ScreenMesh* screenMesh = dynamic_cast<ScreenMesh*>(entity);
		
			if(screenMesh) {
				for(short i=0, polycount=screenMesh->getMesh()->getPolygonCount(); i < polycount; i++) {
					// Get the next polygon
					Polygon* poly = screenMesh->getMesh()->getPolygon(i);
					// Get the vertex count of current polygon
					unsigned short vertexcount = poly->getVertexCount();

					if (vertexcount >= 3 && vertexcount <= 8) {
						// Create new vertices array based on vertexcount
						b2Vec2* vertices = new b2Vec2[vertexcount];
						// and copy from the screenmesh
						for(short index=0; index < vertexcount; index++) {
							vertices[index].x = poly->getVertex(index)->x/worldScale;
							vertices[index].y = poly->getVertex(index)->y/worldScale;						
						}
						// Create the shape
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
	}
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

void PhysicsScreenEntity::applyImpulse(Number fx, Number fy) {	
	body->SetAwake(true);
	b2Vec2 f =  b2Vec2(fx,fy);
	b2Vec2 p = body->GetWorldPoint(b2Vec2(0.0f, 0.0f));
	body->ApplyLinearImpulse(f, p);
}

void PhysicsScreenEntity::setTransform(Vector2 pos, Number angle) {
	body->SetTransform(b2Vec2(pos.x/worldScale, pos.y/worldScale), angle*(PI/180.0f));
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





//==============================================
//Add on functions to access the fixture library
//==============================================


// Gets the last fixture selected
b2Fixture* PhysicsScreenEntity::getFixture() { return fixture; }


// Returns specific fixture based on index starting from 0
b2Fixture* PhysicsScreenEntity::getFixture(unsigned short index) {
	if(fixture)	{
		short i = 0;
		for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
			if (i = index) {
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



// I believe that at runtime you are not supposed to edit Shapes; However you still can
// by getting a fixture(above) and then adding "->GetShape()" on the end to get the fixtures shape



// Slight change to the destructor
PhysicsScreenEntity::~PhysicsScreenEntity()
{
	if(body)
		body->GetWorld()->DestroyBody(body);	// DestroyBody deletes fixtures and shapes automaticaly according to box2d documentation
}