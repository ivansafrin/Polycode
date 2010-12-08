/*
 *  PolyScreenMesh.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 5/6/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */



#include "PolyScreenMesh.h"

using namespace Polycode;

ScreenMesh::ScreenMesh(string fileName) : ScreenEntity(), texture(NULL) {
	mesh = new Mesh(fileName);
}

ScreenMesh::ScreenMesh(int meshType) : ScreenEntity(), texture(NULL) {
	mesh = new Mesh(meshType);
}


ScreenMesh::~ScreenMesh() {

}

Mesh *ScreenMesh::getMesh() {
	return mesh;
}

Texture *ScreenMesh::getTexture() {
	return texture;
}

void ScreenMesh::setTexture(Texture *texture) {
	this->texture = texture;
}

void ScreenMesh::loadTexture(string fileName) {
	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(fileName);
}

void ScreenMesh::loadTexture(Image *image) {
	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromImage(image);
}

void ScreenMesh::Render() {	
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	renderer->setTexture(texture);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::COLOR_DATA_ARRAY);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::VERTEX_DATA_ARRAY);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
	renderer->drawArrays(mesh->getMeshType());
}