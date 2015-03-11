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
	Number pixelSizeX = 1 / imageWidth;
	Number pixelSizeY = 1 / imageHeight;

	if (realWidth == -1)
		realWidth = width;
	if (realHeight == -1)
		realHeight = height;

	setWidth(realWidth);
	setHeight(realHeight);

	Number whalf = realWidth / 2.0f;
	Number hhalf = realHeight / 2.0f;

	Number xFloat = x * pixelSizeX;
	Number yFloat = y * pixelSizeY;
	Number wFloat = width * pixelSizeX;
	Number hFloat = height * pixelSizeY;

	mesh->vertexPositionArray.data.clear();
	mesh->vertexTexCoordArray.data.clear();

	mesh->setMeshType(Mesh::QUAD_MESH);

	mesh->addVertex(0 - whalf, 0 - hhalf, 0);
	mesh->addTexCoord(xFloat, (1.0 - yFloat) - hFloat);

	mesh->addVertex(realWidth - whalf, 0 - hhalf, 0);
	mesh->addTexCoord(xFloat + wFloat, (1.0 - yFloat) - hFloat);

	mesh->addVertex(realWidth - whalf, realHeight - hhalf, 0);
	mesh->addTexCoord(xFloat + wFloat, 1.0 - yFloat);

	mesh->addVertex(0 - whalf, realHeight - hhalf, 0);
	mesh->addTexCoord(xFloat, 1.0 - yFloat);

	rebuildTransformMatrix();
	matrixDirty = true;
}

Number SceneImage::getImageWidth() const {
	return imageWidth;
}

Number SceneImage::getImageHeight() const {
	return imageHeight;	
}