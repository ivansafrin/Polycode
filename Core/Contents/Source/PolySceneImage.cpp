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

#include "PolySceneImage.h"
#include "PolyMesh.h"
#include "PolyTexture.h"
#include "PolyVertex.h"

using namespace Polycode;

SceneImage* SceneImage::SceneImageWithImage(Image *image) {
	return new SceneImage(image);
}

SceneImage* SceneImage::SceneImageWithTexture(Texture *texture) {
	return new SceneImage(texture);	
}

SceneImage::SceneImage(const String& fileName) : ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1, 1) {
	loadTexture(fileName);

	imageWidth = texture->getWidth();
	imageHeight = texture->getHeight();

	setWidth(texture->getWidth());
	setHeight(texture->getHeight());
	setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, getWidth(), getHeight());
}

SceneImage::SceneImage(Image *image) : ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1, 1) {
	loadTextureFromImage(image);

	imageWidth = texture->getWidth();
	imageHeight = texture->getHeight();

	setWidth(texture->getWidth());
	setHeight(texture->getHeight());	
	setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, getWidth(), getHeight());
}

SceneImage::SceneImage(Texture *texture) : ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1, 1)  {
	setTexture(texture);

	imageWidth = texture->getWidth();
	imageHeight = texture->getHeight();

	setWidth(texture->getWidth());
	setHeight(texture->getHeight());	
	setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, getWidth(), getHeight());
}

SceneImage::~SceneImage() {

}

Entity *SceneImage::Clone(bool deepClone, bool ignoreEditorOnly) const {
	SceneImage *newImage = new SceneImage(getTexture()->getResourcePath());
	applyClone(newImage, deepClone, ignoreEditorOnly);
	return newImage;
}

void SceneImage::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
	ScenePrimitive::applyClone(clone, deepClone, ignoreEditorOnly);
}

void SceneImage::setImageCoordinates(Number x, Number y, Number width, Number height, Number realWidth, Number realHeight) {
	
	Number pixelSizeX = 1/imageWidth;
	Number pixelSizeY = 1/imageHeight;

	if(realWidth == -1)
		realWidth = width;
	if(realHeight == -1)
		realHeight = height;


	setWidth(realWidth);
	setHeight(realHeight);	
	setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, getWidth(), getHeight());	
		
	Number xFloat = x * pixelSizeX;
	Number yFloat = 1 - (y * pixelSizeY);
	Number wFloat = width * pixelSizeX;
	Number hFloat = height * pixelSizeY;

    mesh->getVertex(0)->setTexCoord(xFloat, yFloat - hFloat);
    mesh->getVertex(1)->setTexCoord(xFloat + wFloat, yFloat - hFloat);
    mesh->getVertex(2)->setTexCoord(xFloat + wFloat, yFloat);
    mesh->getVertex(3)->setTexCoord(xFloat, yFloat);

	mesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
	mesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;
	
	rebuildTransformMatrix();
	matrixDirty = true;
}

Number SceneImage::getImageWidth() const {
	return imageWidth;
}

Number SceneImage::getImageHeight() const {
	return imageHeight;	
}