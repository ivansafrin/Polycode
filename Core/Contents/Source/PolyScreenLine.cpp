/*
 *  PolyScreenLine.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 5/8/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyScreenLine.h"

using namespace Polycode;

ScreenLine::ScreenLine(Vector2* start, Vector2* end) {
	target1 = NULL;
	startVertex.x = start->x;
	startVertex.y = start->y;
	endVertex.x = end->x;
	endVertex.y = end->y;
	
	vertexDataArray = CoreServices::getInstance()->getRenderer()->createRenderDataArray(RenderDataArray::VERTEX_DATA_ARRAY);	
}

ScreenLine::ScreenLine(ScreenEntity* target1, ScreenEntity* target2) : ScreenEntity() {
	this->target1 = target1;
	this->target2 = target2;
	lineWidth = 1.0f;
	vertexDataArray = CoreServices::getInstance()->getRenderer()->createRenderDataArray(RenderDataArray::VERTEX_DATA_ARRAY);
}

ScreenLine::~ScreenLine() {

}


void ScreenLine::setLineWidth(Number width) {
	lineWidth = width;
}

void ScreenLine::Update() {
	if(!target1)
		return;
	Vector3 pos1 = target1->getPosition();
	Vector3 pos2 = target2->getPosition();
	
	setPosition(pos1.x, pos1.y);
	endVertex.x = pos2.x-pos1.x;
	endVertex.y = pos2.y-pos1.y;
}


void ScreenLine::Render() {
	Renderer *renderer = CoreServices::getInstance()->getRenderer();	
	int rmode = renderer->getRenderMode();

	renderer->setRenderMode(Renderer::RENDER_MODE_WIREFRAME);
	renderer->setLineSize(lineWidth);
	renderer->setTexture(NULL);
	
//	renderer->draw2DVertex(&startVertex);
//	renderer->draw2DVertex(&endVertex);		
	renderer->pushRenderDataArray(vertexDataArray);
	renderer->drawArrays(Mesh::TRIFAN_MESH);
	
	
	renderer->setRenderMode(rmode);
}
