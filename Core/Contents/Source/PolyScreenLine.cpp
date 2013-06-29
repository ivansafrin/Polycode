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

#include "PolyScreenLine.h"
#include "PolyCoreServices.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolyRenderer.h"

using namespace Polycode;

ScreenLine::ScreenLine(Vector2 start, Vector2 end) : ScreenMesh(Mesh::LINE_MESH) {
	target1 = NULL;
	initMesh();

	startVertex->x = start.x;
	startVertex->y = start.y;
	endVertex->x = end.x;
	endVertex->y = end.y;
	lineWidth = 1.0f;
	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;	
}

ScreenLine *ScreenLine::ScreenLineBetweenEntities(ScreenEntity* target1, ScreenEntity* target2) {
	return new ScreenLine(target1, target2);
}


ScreenLine::ScreenLine(ScreenEntity* target1, ScreenEntity* target2) : ScreenMesh(Mesh::LINE_MESH) {
	initMesh();
	this->target1 = target1;
	this->target2 = target2;
	lineWidth = 1.0f;

}

void ScreenLine::setStart(Vector2 point) {
	startVertex->x = point.x;
	startVertex->y = point.y;
	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
}

void ScreenLine::setEnd(Vector2 point) {
	endVertex->x = point.x;
	endVertex->y = point.y;
	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
}

void ScreenLine::initMesh() {
	Polygon *poly = new Polygon();
	startVertex = poly->addVertex(0, 0, 0, 0,0);
	endVertex = poly->addVertex(0,0,0,1,0);	
	mesh->addPolygon(poly);
	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
	mesh->arrayDirtyMap[RenderDataArray::COLOR_DATA_ARRAY] = true;
	mesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
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
	endVertex->x = pos2.x-pos1.x;
	endVertex->y = pos2.y-pos1.y;

	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
}


void ScreenLine::Render() {
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	renderer->setLineSize(lineWidth);
	if(lineSmooth) {
		renderer->setLineSmooth(true);
	}

	renderer->setTexture(texture);
	if(mesh->useVertexColors) {
		renderer->pushDataArrayForMesh(mesh, RenderDataArray::COLOR_DATA_ARRAY);
	}
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::VERTEX_DATA_ARRAY);
	renderer->pushDataArrayForMesh(mesh, RenderDataArray::TEXCOORD_DATA_ARRAY);
	renderer->drawArrays(mesh->getMeshType());

	renderer->setLineSmooth(false);
}
