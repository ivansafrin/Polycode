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

#include "PolyVertex.h"

using namespace Polycode;

Vertex::Vertex() : Vector3(0,0,0) {
	texCoord = Vector2(0,0);
	normal = Vector3(0,0,0);
	useVertexColor = false;
}

Vertex::Vertex(Number pos_x, Number pos_y, Number pos_z, Number nor_x, Number nor_y, Number nor_z) : Vector3(pos_x, pos_y, pos_z) {
	normal = Vector3(nor_x, nor_y, nor_z);
	texCoord = Vector2(0,0);
	useVertexColor = false;
	restPosition.set(pos_x, pos_y, pos_z);
}

Vertex::Vertex(Number pos_x, Number pos_y, Number pos_z, Number nor_x, Number nor_y, Number nor_z, Number u, Number v): Vector3(pos_x, pos_y, pos_z) {
	normal = Vector3(nor_x, nor_y, nor_z);
	texCoord = Vector2(u,v);
	useVertexColor = false;
	restPosition.set(pos_x, pos_y, pos_z);
}

Vertex::Vertex(Number x, Number y, Number z) : Vector3(x,y,z) {
	useVertexColor = false;
	restPosition.set(x, y, z);
}

Vertex::Vertex(Number x, Number y, Number z, Number u, Number v) : Vector3(x,y,z) {
	texCoord = Vector2(u,v);
	useVertexColor = false;
	restPosition.set(x, y, z);
}

void Vertex::addBoneAssignment(unsigned int boneID, Number boneWeight) {
	BoneAssignment *newBas = new BoneAssignment();
	newBas->boneID = boneID;
	if(boneWeight > 1)
		boneWeight = 1;
	if(boneWeight < 0)
		boneWeight = 0;

	newBas->weight = boneWeight;
	boneAssignments.push_back(newBas);
}

void Vertex::setNormal(Number x, Number y, Number z) {
	normal.x = x;
	normal.y = y;
	normal.z = z;
}

void Vertex::normalizeWeights() {
	Number allWeights = 0;
//	if(boneAssignments.size() == 1)
//		if(boneAssignments[0]->weight < 1)
//			return;

	for(int i =0 ;i < boneAssignments.size(); i++) {
		allWeights += boneAssignments[i]->weight;
	}

	for(int i =0 ;i < boneAssignments.size(); i++) {
		boneAssignments[i]->weight *= 1.0f/allWeights;
	}
}

int Vertex::getNumBoneAssignments() {
	return boneAssignments.size();
}

BoneAssignment *Vertex::getBoneAssignment(unsigned int index) {
	return boneAssignments[index];
}

Vertex::~Vertex() {
//	delete normal;
//	delete texCoord;
}

Vector2 Vertex::getTexCoord() {
	return texCoord;
}

void Vertex::setTexCoord(Number u, Number v) {
	texCoord.x = u;
	texCoord.y = v;
}
