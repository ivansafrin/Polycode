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

#include "PolyCollisionSceneEntity.h"
#include "PolyLogger.h"
#include "PolyMesh.h"
#include "PolyEntity.h"
#include "PolySceneMesh.h"
#include "btBulletCollisionCommon.h"

using namespace Polycode;

CollisionEntity::CollisionEntity(Entity *entity, int type, bool compoundChildren) {
	this->entity = entity;
	shape = NULL;
	
	this->type = type;
	enabled = true;	
	lastPosition = entity->getPosition();	
	
	
	btMatrix3x3 basisA;
	basisA.setIdentity();
	
	collisionObject = new btCollisionObject();
	collisionObject->getWorldTransform().setBasis(basisA);	
	
	if(compoundChildren) {
		 btCompoundShape* compoundShape = new btCompoundShape();
		 
		 for(int i=0; i < entity->getNumChildren(); i++) {
			Entity *child = (Entity*)entity->getChildAtIndex(i);
			btCollisionShape *childShape = createCollisionShape(child, child->collisionShapeType);
			btTransform transform;
			
			child->rebuildTransformMatrix();

			btScalar mat[16];		
			Matrix4 ent_mat = child->getTransformMatrix();
	
			for(int i=0; i < 16; i++) {
				mat[i] = ent_mat.ml[i];
			}			
			
			transform.setFromOpenGLMatrix(mat);
			compoundShape->addChildShape(transform, childShape);			
		 }	
		 
		 shape = compoundShape;
	} else {
		shape = createCollisionShape(entity, type);	
	}
	
	if(shape) {
		collisionObject->setCollisionShape(shape);
	}
	
	collisionObject->setUserPointer((void*)this);
	
	if(type == SHAPE_MESH_CONCAVE) {		
		concaveShape = dynamic_cast<btConcaveShape*>(shape);
	} else {
		convexShape	= dynamic_cast<btConvexShape*>(shape);		
	}		
}

btCollisionShape *CollisionEntity::createCollisionShape(Entity *entity, int type) {
	
	btCollisionShape *collisionShape = NULL;	
	
    Vector3 scale = entity->getCompoundScale();
    Vector3 bBox = entity->getLocalBoundingBox() * scale;
	
    Number largestSize = bBox.x;
    if(bBox.y > largestSize) {
        largestSize = bBox.y;
    }
    if(bBox.z > largestSize) {
        largestSize = bBox.z;
    }
    
	switch(type) {
		case SHAPE_CAPSULE:
		case CHARACTER_CONTROLLER:
			collisionShape = new btCapsuleShape(bBox.x/2.0f, bBox.y/2.0f);
		break;
		case SHAPE_CONE: {
			Number largest = bBox.x;
			if(bBox.z > largest) {
				largest = bBox.z;
			}
			collisionShape = new btConeShape(largest/2.0f, bBox.y);
			}
		break;
		case SHAPE_CYLINDER:
		{
			collisionShape = new btCylinderShape(btVector3(bBox.x/2.0, bBox.y/2.0f,bBox.z/2.0));
		}
		break;
		case SHAPE_PLANE:
			collisionShape = new btBoxShape(btVector3(bBox.x/2.0f, 0.05,bBox.z/2.0f));
			break;
		case SHAPE_BOX:
			collisionShape = new btBoxShape(btVector3(bBox.x/2.0f, bBox.y/2.0f,bBox.z/2.0f));
			break;
		case SHAPE_SPHERE:
			collisionShape = new btSphereShape(largestSize/2.0f);
			break;
		case SHAPE_MESH:
		case SHAPE_MESH_COMPOUND:
		case SHAPE_MESH_CONCAVE:
		{
			SceneMesh* sceneMesh = dynamic_cast<SceneMesh*>(entity);
			Mesh *mesh = sceneMesh->getMesh();
			if(sceneMesh != NULL) {
				if(type == SHAPE_MESH) {
					btConvexHullShape *hullShape = new btConvexHullShape();
					for(int i=0; i < mesh->getActualVertexCount(); i++) {
						hullShape->addPoint(btVector3((btScalar)mesh->getActualVertex(i)->x, (btScalar)mesh->getActualVertex(i)->y,(btScalar)mesh->getActualVertex(i)->z));
					}				
					collisionShape = hullShape;
				} else if(type == SHAPE_MESH_COMPOUND) {
					collisionShape = createCompoundMeshShape(mesh);
				} else {
					btTriangleMesh *triMesh = new btTriangleMesh(true, false);
					btVector3 *vert0 = new btVector3(0,0,0);
					btVector3 *vert1 = new btVector3(0,0,0);
					btVector3 *vert2 = new btVector3(0,0,0);
					for( int i=0; i < mesh->getVertexCount(); i+=3) {
						vert0->setX(mesh->getVertex(i)->x);
						vert0->setY(mesh->getVertex(i)->y);
						vert0->setZ(mesh->getVertex(i)->z);

						vert1->setX(mesh->getVertex(i+1)->x);
						vert1->setY(mesh->getVertex(i+1)->y);
						vert1->setZ(mesh->getVertex(i+1)->z);

						vert2->setX(mesh->getVertex(i+2)->x);
						vert2->setY(mesh->getVertex(i+2)->y);
						vert2->setZ(mesh->getVertex(i+2)->z);

						triMesh->addTriangle(*vert0, *vert1, *vert2, false);
					}
					btBvhTriangleMeshShape *bvhMesh = new btBvhTriangleMeshShape(triMesh, true, true);
					delete vert0,vert1,vert2,triMesh;
					collisionShape = bvhMesh;
				}
			} else {
				Logger::log("Tried to make a mesh collision object from a non-mesh\n");
				collisionShape = new btBoxShape(btVector3(bBox.x/2.0f, bBox.y/2.0f,bBox.z/2.0f));
			}
		}
		break;
	}
    
   // collisionShape->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
    
	return collisionShape; 
}

btCollisionShape *CollisionEntity::createCompoundMeshShape(Mesh *mesh) {
	unsigned int vertexCount = mesh->getVertexCount();
	unsigned int actualVertexCount = mesh->getActualVertexCount();

	Vertex*** hullArray = new Vertex**[vertexCount/3];
	for(int p=0; p < (vertexCount/3); p++)
		hullArray[p] = NULL;
				
	int hullArraySize = 0;
	int hullSize = 0;
	int maxHullVerts = 1000;
				
	bool foundVert0 = false;
	bool foundVert1 = false;
	bool foundVert2 = false;
	bool foundHull = false;
	
	for(int i=0; i < vertexCount; i+=3) {
		Vertex* vert0 = mesh->getVertex(i);
		Vertex* vert1 = mesh->getVertex(i+1);
		Vertex* vert2 = mesh->getVertex(i+2);
		if(i == 0) {
				Vertex** newHull = new Vertex*[maxHullVerts];
				for(int p=0; p < maxHullVerts; p++)
					newHull[p] = NULL;
				newHull[0] = vert0;
				newHull[1] = vert1;
				newHull[2] = vert2;
				hullArray[i] = newHull;
		} else {
			foundHull = false;
			for(int j=(vertexCount/3-1); j > -1; j--) {
				if(hullArray[j] == NULL){
					hullArraySize = j;
					continue;
				}
				if(j < (hullArraySize - 2))
					break;
				foundVert0 = false;
				foundVert1 = false;
				foundVert2 = false;
				for(int k = 0; k < maxHullVerts; k++) {
					if(hullArray[j][k] == NULL) {
						hullSize = k;
						break;
					}
					if(hullArray[j][k] == vert0){
						foundVert0 = true;
					} else if(hullArray[j][k] == vert1){
						foundVert1 = true;
					} else if(hullArray[j][k] == vert2){
						foundVert2 = true;
					}
				}
				if(foundVert0 || foundVert1 || foundVert2){
					foundHull = true;
					if(!foundVert0){
						hullArray[j][hullSize] = vert0;
					}
					if(!foundVert1){
						hullArray[j][hullSize+foundVert0] = vert1;
					}
					if(!foundVert2){
						hullArray[j][hullSize+foundVert0+foundVert1] = vert2;
					}
				}
			}
			if(!foundHull) {
				Vertex** newHull = new Vertex*[maxHullVerts];
				for(int p=0; p < maxHullVerts; p++)
					newHull[p] = NULL;
				newHull[0] = vert0;
				newHull[1] = vert1;
				newHull[2] = vert2;
				hullArray[hullArraySize] = newHull;
			}
		}
	}
	btTransform transform;	

	transform.setOrigin(btVector3(0,0,0));
	transform.setRotation(btQuaternion(0,0,0));
	
	btCompoundShape* meshShape = new btCompoundShape();
	for(int i=0; i < (vertexCount/3); i++) {
		if(hullArray[i] == NULL)
			break;
		btConvexHullShape *hullShape = new btConvexHullShape();
		for(int j=0; j < maxHullVerts; j++) {
			if(hullArray[i][j] == NULL)
				break;
			btScalar x,y,z;
			x = hullArray[i][j]->x;
			y = hullArray[i][j]->y;
			z = hullArray[i][j]->z;
			hullShape->addPoint(btVector3(x, y, z));
		}
		delete[] hullArray[i];
		meshShape->addChildShape(transform, hullShape);
	}
	delete[] hullArray;
	
	return meshShape;
}

void CollisionEntity::Update() {	
	entity->rebuildTransformMatrix();

	btScalar mat[16];		
	Matrix4 ent_mat = entity->getConcatenatedMatrix();
	
	for(int i=0; i < 16; i++) {
			mat[i] = ent_mat.ml[i];
	}			

	collisionObject->getWorldTransform().setFromOpenGLMatrix(mat);
}

Entity *CollisionEntity::getEntity() {
	return entity;
}

CollisionEntity::~CollisionEntity() {
	delete shape;
	delete collisionObject;
}
