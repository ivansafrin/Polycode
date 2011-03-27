/*
 *  PolyScreenImage.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyScreenImage.h"

using namespace Polycode;

ScreenImage::ScreenImage(String fileName) : ScreenShape(ScreenShape::SHAPE_RECT,1,1) {
	loadTexture(fileName);
	
	imageWidth = texture->getWidth();
	imageHeight = texture->getHeight();
	
	width = texture->getWidth();
	height = texture->getHeight();	
	setShapeSize(width, height);	
	
	positionMode = POSITION_TOPLEFT;
}

ScreenImage::ScreenImage(Image *image) : ScreenShape(ScreenShape::SHAPE_RECT,1,1) {
	loadTexture(image);
	
	imageWidth = texture->getWidth();
	imageHeight = texture->getHeight();
	
	width = texture->getWidth();
	height = texture->getHeight();	
	setShapeSize(width, height);	
	
	positionMode = POSITION_TOPLEFT;	
}

ScreenImage::~ScreenImage() {

}

void ScreenImage::setImageCoordinates(Number x, Number y, Number width, Number height) {
	Vertex *vertex;
	Number pixelSizeX = 1/imageWidth;
	Number pixelSizeY = 1/imageHeight;
	
	this->width = width;
	this->height = height;
	hitwidth = width;
	hitheight = height;
	Number whalf = floor(width/2.0f);
	Number hhalf = floor(height/2.0f);	
		
	Number xFloat = x * pixelSizeX;
	Number yFloat = 1 - (y * pixelSizeY);
	Number wFloat = width * pixelSizeX;
	Number hFloat = height * pixelSizeY;
	
	Polygon *imagePolygon = mesh->getPolygon(0);	
	vertex = imagePolygon->getVertex(0);
	vertex->set(-whalf,-hhalf,0);
	vertex->setTexCoord(xFloat, yFloat);
	
	vertex = imagePolygon->getVertex(1);
	vertex->set(-whalf+width,-hhalf,0);
	vertex->setTexCoord(xFloat + wFloat, yFloat);
	
	vertex = imagePolygon->getVertex(2);
	vertex->set(-whalf+width,-hhalf+height,0);
	vertex->setTexCoord(xFloat + wFloat, yFloat - hFloat);
	
	vertex = imagePolygon->getVertex(3);	
	vertex->set(-whalf,-hhalf+height,0);	
	vertex->setTexCoord(xFloat, yFloat - hFloat);
	
	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
	mesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;	
	rebuildTransformMatrix();
	matrixDirty = true;
	
}

Number ScreenImage::getImageWidth() {
	return imageWidth;
}

Number ScreenImage::getImageHeight() {
	return imageHeight;	
}