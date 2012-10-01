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

PhysicsScreenEntity::PhysicsScreenEntity(ScreenEntity *entity, b2World *world, Number worldScale, int entType, bool isStatic, Number friction, Number density, Number restitution, bool isSensor, bool fixedRotation)
{
	screenEntity = entity;

	Vector3 entityScale = entity->getCompoundScale();
	this->worldScale = worldScale;
	collisionOnly = false;
	fixturelist = NULL;

	
	// Create body definition---------------------------------------
	b2BodyDef bodyDef;
	bodyDef.position.Set(screenEntity->getPosition().x/worldScale, screenEntity->getPosition().y/worldScale);
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

	// Create Shape definition (Circle or Polygon)---------------------------
	switch(entType)
	{
		case ENTITY_CIRCLE:
		{
			b2CircleShape shape;
			// Set fixture shape to shape definition
			fDef.shape = &shape;
			// Create the shape
			shape.m_radius = screenEntity->getWidth()/(worldScale*2.0f);
			// Create the fixture
			fixture = body->CreateFixture(&fDef);
			break;
		}
		case ENTITY_RECT: 
		{
			b2PolygonShape shape;
			// Set fixture shape to shape definition
			fDef.shape = &shape;
			// Create the shape
			shape.SetAsBox(screenEntity->getWidth()/(worldScale*2.0f) * entityScale.x, screenEntity->getHeight()/(worldScale*2.0f) * entityScale.y);
			// Create the fixture
			fixture = body->CreateFixture(&fDef);
			break;
		}
		case ENTITY_MESH:
		{
			b2PolygonShape shape;
			// Set fixture shape to shape definition
			fDef.shape = &shape;
			// Get the screenmesh of the entity
			ScreenMesh* screenMesh = dynamic_cast<ScreenMesh*>(entity);
		
			if(screenMesh)
			{
				// Get number of polygons
				unsigned short polycount = screenMesh->getMesh()->getPolygonCount();
				// Create a fixturelist just for meshes (that is why it is dynamic mem)
				fixturelist = new vector <b2Fixture*>;
			
				for(int i=0; i < polycount; i++)
				{
					// Get the vertex count of current polygon
					unsigned short vertexcount = screenMesh->getMesh()->getPolygon(i)->getVertexCount();
					if (vertexcount >= 3 && vertexcount <= 8)
					{
						// Create verticies array based on vertexcount size
						b2Vec2* vertices = new b2Vec2[vertexcount];
						
						for(int index = 0; index < vertexcount; index++)
						{
							vertices[index].x = screenMesh->getMesh()->getPolygon(i)->getVertex(index)->x/worldScale;
							vertices[index].y = screenMesh->getMesh()->getPolygon(i)->getVertex(index)->y/worldScale;						
						}
						// Create the shape
						shape.Set(vertices, vertexcount);
						// Create the fixture
						fixture = body->CreateFixture(&fDef);
						// Save fixture to the vector
						fixturelist->push_back(fixture);

						delete []vertices;
					}
					else
					{
						Logger::log("Number of vertices allowed must be between 3 and 8\n");
					}
				}
			}
			else
			{
				Logger::log("Tried to make a mesh collision object from a non-mesh\n");							
			}
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



//Add on functions for the fixture library
//========================================

// Gets last fixture selected
b2Fixture* PhysicsScreenEntity::getfixture()
{
	return fixture;
}

// Returns specific Fixture based on index starting from 0
b2Fixture* PhysicsScreenEntity::getfixture(unsigned int index)
{
	if(fixturelist)
	{
		if (index < fixturelist->size())
		{
			fixture = fixturelist->at(index);
			return fixture;
		}
		else
			Logger::log("That fixture index does not exist\n");							
	}
	else
		Logger::log("Fixturelist is for mesh only\n");
	
	return fixture = NULL;	
}

// Slight change to the destructor
PhysicsScreenEntity::~PhysicsScreenEntity()
{
	if(body)
		body->GetWorld()->DestroyBody(body);	// Destroy body deletes fixtures on it's own according to box2d documentation

	if(fixturelist)
		delete fixturelist;	//<--------------------I'm not really sure if this will cause a crash??? Needs testing
												// If so try: fixturelist->clear(); instead or just leave out.
}