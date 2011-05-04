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
