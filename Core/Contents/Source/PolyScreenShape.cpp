/*
 *  PolyScreenShape.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 5/6/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyScreenShape.h"

using namespace Polycode;

ScreenShape::ScreenShape(int shapeType, float option1, float option2, float option3, float option4) : ScreenMesh(Mesh::QUAD_MESH) {
	float DEG2RAD = 3.14159/180;
	strokeWidth = 1.0f;
	this->shapeType = shapeType;
	width = option1;
	height = option2;

	hitwidth = width;
	hitheight = height;

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
		case SHAPE_CIRCLE_OUTLINE:
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
				float degInRad = i*DEG2RAD;
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

void ScreenShape::setShapeSize(float newWidth, float newHeight) {
	width = newWidth;
	height = newHeight;
	
	hitwidth = width;
	hitheight = height;	
	
	float whalf = floor(width/2.0f);
	float hhalf = floor(height/2.0f);
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

void ScreenShape::addShapePoint(float x, float y) {
	customShapePoly->addVertex(x,y,0,0,0);
}

void ScreenShape::setGradient(float r1, float g1, float b1, float a1, float r2, float g2, float b2, float a2) {

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
		case SHAPE_CIRCLE_OUTLINE:			
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
}

void ScreenShape::setStrokeWidth(float width) {
	strokeWidth = width;
}

void ScreenShape::setStrokeColor(float r, float g, float b, float a) {
	strokeColor.setColor(r,g,b,a);
}

void ScreenShape::Render() {
	Renderer *renderer = CoreServices::getInstance()->getRenderer();

	ScreenMesh::Render();

	if(strokeEnabled) {
		if(lineSmooth) {
				renderer->setLineSmooth(true);
		}
		
		renderer->setLineSize(strokeWidth);
		renderer->setVertexColor(strokeColor.r,strokeColor.g,strokeColor.b,strokeColor.a);
		int rmode = renderer->getRenderMode();
		renderer->setRenderMode(Renderer::RENDER_MODE_WIREFRAME);

		renderer->pushDataArrayForMesh(mesh, RenderDataArray::COLOR_DATA_ARRAY);
		renderer->pushDataArrayForMesh(mesh, RenderDataArray::VERTEX_DATA_ARRAY);
		renderer->pushDataArrayForMesh(mesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
		renderer->drawArrays(mesh->getMeshType());		
		
		renderer->setRenderMode(rmode);
		renderer->setLineSize(1.0f);
		renderer->setLineSmooth(false);
	}

}


ScreenShape::~ScreenShape() {

}