/*
 *  PolySceneLine.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 10/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolySceneLine.h"

using namespace Polycode;

SceneLine::SceneLine(SceneEntity *ent1, SceneEntity *ent2) : SceneEntity() {
	this->ent1 = ent1;
	this->ent2 = ent2;	

	mesh = new Mesh(Mesh::LINE_MESH);	
	
	Polygon *poly = new Polygon();
	poly->addVertex(0,0,0);
	poly->addVertex(0,0,0);	
	mesh->addPolygon(poly);
	
	ignoreParentMatrix = true;
}

SceneLine::~SceneLine() {

}


void SceneLine::Render() {	
	
	Vector3 v1;
	v1 = ent1->getConcatenatedMatrix().getPosition();
	Vector3 v2;
	v2 = ent2->getConcatenatedMatrix().getPosition();

	
	mesh->getPolygon(0)->getVertex(0)->set(v1.x,v1.y,v1.z); 
	mesh->getPolygon(0)->getVertex(1)->set(v2.x,v2.y,v2.z); 	
	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
	
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	renderer->setTexture(NULL);	
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::VERTEX_DATA_ARRAY);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::NORMAL_DATA_ARRAY);		
	
	renderer->drawArrays(mesh->getMeshType());	
	
}
