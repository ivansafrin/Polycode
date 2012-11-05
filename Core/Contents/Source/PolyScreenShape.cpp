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

#include "PolyScreenShape.h"
#include "PolyCoreServices.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolyRenderer.h"

using namespace Polycode;

ScreenShape::ScreenShape(int shapeType, Number option1, Number option2, Number option3, Number option4) : ScreenMesh(Mesh::QUAD_MESH) {
	Number DEG2RAD = 3.14159/180;
	strokeWidth = 1.0f;
	this->shapeType = shapeType;
	width = option1;
	height = option2;
	
	setHitbox(width, height);

	this->option1 = option1;
	this->option2 = option2;
	this->option3 = option3;
	this->option4 = option4;
	lineSmooth = false;
		
	switch(shapeType) {
		case SHAPE_RECT: {
			mesh->setMeshType(Mesh::QUAD_MESH);
			Polygon *poly = new Polygon();
			poly->addVertex(-width/2.0f,-height/2.0f,0,0,1);
			poly->addVertex(width/2.0f,-height/2.0f,0, 1, 1);
			poly->addVertex(width/2.0f,height/2.0f,0, 1, 0);
			poly->addVertex(-width/2.0f,height/2.0f,0,0,0);
						
			mesh->addPolygon(poly);
			}
		break;
		case SHAPE_CIRCLE: {
			mesh->setMeshType(Mesh::TRIFAN_MESH);
			Polygon *poly = new Polygon();
			int step;
			if(option3 > 0)
				step = ceil(360/option3);
			else
				step = 1;
			if(shapeType == SHAPE_CIRCLE)
				poly->addVertex(0,0,0,0.5,0.5);
			else
				poly->addVertex(cosf(0)*(width/2),sinf(0)*(height/2), 0, (cosf(0)*0.5) + 0.5,(sinf(0) * 0.5)+ 0.5);
			
			for (int i=0; i < 361; i+= step) {
				Number degInRad = i*DEG2RAD;
				poly->addVertex(cos(degInRad)*(width/2),sin(degInRad)*(height/2), 0, (cos(degInRad) * 0.5)+ 0.5 ,(sin(degInRad) * 0.5)+ 0.5);
			}
			mesh->addPolygon(poly);
			}
		break;
		case SHAPE_CUSTOM:
			mesh->setMeshType(Mesh::TRIFAN_MESH);
			customShapePoly = new Polygon();
			mesh->addPolygon(customShapePoly);
		break;	
		default:
		break;
	}
	
	positionMode = POSITION_CENTER;
	strokeEnabled = false;
}

void ScreenShape::setShapeSize(Number newWidth, Number newHeight) {

	setWidth(newWidth);
	setHeight(newHeight);

	
	Number whalf = floor(width/2.0f);
	Number hhalf = floor(height/2.0f);
	Polygon *polygon;
	Vertex *vertex;
	
	switch(shapeType) {
		case SHAPE_RECT: {	
			polygon = mesh->getPolygon(0);	
			vertex = polygon->getVertex(0);
			vertex->set(-whalf,-hhalf,0);			
			vertex = polygon->getVertex(1);
			vertex->set(-whalf+width,-hhalf,0);			
			vertex = polygon->getVertex(2);
			vertex->set(-whalf+width,-hhalf+height,0);			
			vertex = polygon->getVertex(3);	
			vertex->set(-whalf,-hhalf+height,0);				
		}			
		break;
		default:
		break;
	}
	
		
	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
	rebuildTransformMatrix();
	matrixDirty = true;
}

void ScreenShape::addShapePoint(Number x, Number y) {
	customShapePoly->addVertex(x,y,0,0,0);
}

void ScreenShape::setGradient(Number r1, Number g1, Number b1, Number a1, Number r2, Number g2, Number b2, Number a2) {

	mesh->useVertexColors = true;
	for(int i=0; i < mesh->getPolygon(0)->getVertexCount(); i++) {
		mesh->getPolygon(0)->getVertex(i)->useVertexColor = true;
	}
	
	switch(shapeType) {
		case SHAPE_RECT:
				mesh->getPolygon(0)->getVertex(0)->vertexColor.setColor(r1,g1,b1,a1);
				mesh->getPolygon(0)->getVertex(1)->vertexColor.setColor(r1,g1,b1,a1);
				mesh->getPolygon(0)->getVertex(2)->vertexColor.setColor(r2,g2,b2,a2);
				mesh->getPolygon(0)->getVertex(3)->vertexColor.setColor(r2,g2,b2,a2);
		break;
		case SHAPE_CIRCLE:	
			mesh->getPolygon(0)->getVertex(0)->vertexColor.setColor(r1,g1,b1,a1);
			for(int i=1; i < mesh->getPolygon(0)->getVertexCount(); i++) {
				mesh->getPolygon(0)->getVertex(i)->vertexColor.setColor(r2,g2,b2,a2);
			}
		break;
	}
}

void ScreenShape::clearGradient() {
	for(int i=0; i < mesh->getPolygon(0)->getVertexCount(); i++) {
		mesh->getPolygon(0)->getVertex(i)->useVertexColor = false;
	}
	mesh->useVertexColors = false;
}

void ScreenShape::setStrokeWidth(Number width) {
	strokeWidth = width;
}

void ScreenShape::setStrokeColor(Number r, Number g, Number b, Number a) {
	strokeColor.setColor(r,g,b,a);
}

void ScreenShape::Render() {
	Renderer *renderer = CoreServices::getInstance()->getRenderer();

	ScreenMesh::Render();

	if(strokeEnabled) {
		renderer->setTexture(NULL);
		if(lineSmooth) {
				renderer->setLineSmooth(true);
		}
		
		renderer->setLineSize(strokeWidth);
		renderer->setVertexColor(strokeColor.r,strokeColor.g,strokeColor.b,strokeColor.a);
		int rmode = renderer->getRenderMode();
		renderer->setRenderMode(Renderer::RENDER_MODE_WIREFRAME);

//		renderer->pushDataArrayForMesh(mesh, RenderDataArray::COLOR_DATA_ARRAY);
		renderer->pushDataArrayForMesh(mesh, RenderDataArray::VERTEX_DATA_ARRAY);
//		renderer->pushDataArrayForMesh(mesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
		renderer->drawArrays(mesh->getMeshType());		
		
		renderer->setRenderMode(rmode);
		renderer->setLineSize(1.0f);
		renderer->setLineSmooth(false);
	}

}


ScreenShape::~ScreenShape() {

}
