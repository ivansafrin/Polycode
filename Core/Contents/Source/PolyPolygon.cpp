/*
 *  PolyPolygon.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/14/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyPolygon.h"

namespace Polycode {

Polygon::Polygon()  : useVertexNormals(false), vertexCount(0), useFaceUV(false) {
	normal = new Vector3();
	hasSecUVs = false;
	useVertexNormals = true;
}

Polygon::~Polygon() {
	for(int i=0; i < texCoords.size(); i++) {	
		delete texCoords[i];
	}
	texCoords.clear();

	for(int i=0; i < texCoords2.size(); i++) {	
		delete texCoords2[i];
	}
	texCoords2.clear();
}
	
void Polygon::flipUVY() {
	for(int i=0; i < vertices.size(); i++) {
		Vector2 *coord = vertices[i]->getTexCoord();
		vertices[i]->setTexCoord(coord->x, 1-coord->y);
	}
}

void Polygon::setUseFaceUV(bool val) {
	useFaceUV = val;
}

bool Polygon::usesFaceUV() {
	return useFaceUV;
}

Vector2 *Polygon::getTexCoord(int index) {
	return texCoords[index];
}

Vector2 *Polygon::getTexCoord2(int index) {
	return texCoords2[index];
}

unsigned int Polygon::getVertexCount() {
	return vertices.size();
}

Vertex *Polygon::getVertex(unsigned int index) {
	return vertices[index];
}

Vector3 Polygon::getFaceNormal() {
/*
	Vector3 fNormal;
	fNormal.x = (vertices[2]->z-vertices[1]->z)*(vertices[2]->y-vertices[1]->y)-(vertices[0]->y-vertices[1]->y)*(vertices[2]->z-vertices[1]->z);
	fNormal.y = (vertices[0]->x-vertices[1]->x)*(vertices[2]->z-vertices[1]->z)-(vertices[0]->z-vertices[1]->z)*(vertices[2]->x-vertices[1]->x);
	fNormal.z = (vertices[0]->y-vertices[1]->y)*(vertices[2]->x-vertices[1]->x)-(vertices[0]->x-vertices[1]->x)*(vertices[2]->y-vertices[1]->y);
	fNormal.Normalize();	
	return fNormal;
	*/
	return *normal;
}

Rectangle Polygon::getBounds2D() {
	Rectangle retBox;
	retBox.x = 1000000000;
	retBox.y = 1000000000;
	for(int i=0; i < vertices.size(); i++) {
			retBox.x = min(retBox.x,vertices[i]->x);
			retBox.y = min(retBox.y,vertices[i]->y);
	}
	for(int i=0; i < vertices.size(); i++) {
			retBox.w = max(retBox.w, vertices[i]->x - retBox.x);
			retBox.h = max(retBox.h, vertices[i]->y - retBox.y);
	}
	
	return retBox;
}

void Polygon::setNormal(Vector3 normal) {
	*this->normal = normal;
}	

void Polygon::calculateNormal() {
	if(vertices.size() < 3)
		return;

//	normal->x = (vertices[2]->z-vertices[1]->z)*(vertices[2]->y-vertices[1]->y)-(vertices[0]->y-vertices[1]->y)*(vertices[2]->z-vertices[1]->z);
//	normal->y = (vertices[0]->x-vertices[1]->x)*(vertices[2]->z-vertices[1]->z)-(vertices[0]->z-vertices[1]->z)*(vertices[2]->x-vertices[1]->x);
//	normal->z = (vertices[0]->y-vertices[1]->y)*(vertices[2]->x-vertices[1]->x)-(vertices[0]->x-vertices[1]->x)*(vertices[2]->y-vertices[1]->y);

	*normal = (*vertices[0] - *vertices[1]).crossProduct((*vertices[1] - *vertices[2]));
	
	normal->Normalize();
	
	for(int i=0; i < vertices.size(); i++) {
		vertices[i]->normal->x = normal->x;
		vertices[i]->normal->y = normal->y;
		vertices[i]->normal->z = normal->z;		
	}
}

Vertex *Polygon::addVertex(float x, float y, float z) {
	Vertex *vertex = new Vertex(x,y,z);
	vertices.push_back(vertex);
	return vertex;
}

void Polygon::addTexCoord2(float u, float v) {
	Vector2 *newCoord = new Vector2(u,v);
	texCoords2.push_back(newCoord);
	hasSecUVs =true;
}

void Polygon::addTexCoord(float u, float v) {
	Vector2 *newCoord = new Vector2(u,v);
	texCoords.push_back(newCoord);
}

void Polygon::addVertex(Vertex *vertex) {
	vertices.push_back(vertex);
}

Vertex *Polygon::addVertex(float x, float y, float z, float u, float v) {
	Vertex *vertex = new Vertex(x,y,z,u,v);
	vertices.push_back(vertex);
	return vertex;
}

}