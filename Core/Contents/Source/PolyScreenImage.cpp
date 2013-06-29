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

#include "PolyScreenImage.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolyTexture.h"
#include "PolyVertex.h"

using namespace Polycode;

ScreenImage* ScreenImage::ScreenImageWithImage(Image *image) {
	return new ScreenImage(image);
}

ScreenImage* ScreenImage::ScreenImageWithTexture(Texture *texture) {
	return new ScreenImage(texture);
}

ScreenImage::ScreenImage(const String& fileName) : ScreenShape(ScreenShape::SHAPE_RECT,1,1) {
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

ScreenImage::ScreenImage(Texture *texture) : ScreenShape(ScreenShape::SHAPE_RECT,1,1) {
	setTexture(texture);

	imageWidth = texture->getWidth();
	imageHeight = texture->getHeight();

	width = texture->getWidth();
	height = texture->getHeight();
	setShapeSize(width, height);

	positionMode = POSITION_TOPLEFT;
}

ScreenImage::~ScreenImage() {

}

Entity *ScreenImage::Clone(bool deepClone, bool ignoreEditorOnly) {
	ScreenImage *newImage = new ScreenImage(getTexture()->getResourcePath());
	applyClone(newImage, deepClone, ignoreEditorOnly);
	return newImage;
}

void ScreenImage::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) {
	ScreenShape::applyClone(clone, deepClone, ignoreEditorOnly);
}

void ScreenImage::setImageCoordinates(Number x, Number y, Number width, Number height) {
	Vertex *vertex;
	Number pixelSizeX = 1/imageWidth;
	Number pixelSizeY = 1/imageHeight;

	this->width = width;
	this->height = height;
	setHitbox(width, height);
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

Number ScreenImage::getImageWidth() const {
	return imageWidth;
}

Number ScreenImage::getImageHeight() const {
	return imageHeight;
}
