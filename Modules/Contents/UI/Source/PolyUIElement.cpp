/*
 Copyright (C) 2012 by Ivan Safrin
 
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

#include "PolyUIElement.h"
#include "PolyRenderer.h"
#include "PolyCoreServices.h"
#include "PolyTexture.h"
#include "PolyConfig.h"

using namespace Polycode;

UIElement *UIElement::globalFocusedChild = NULL;

UILabel::UILabel(const String& text, int size, const String& fontName, int amode) : UIElement() {

	Config *conf = CoreServices::getInstance()->getConfig();	
	label = new SceneLabel(text, size, fontName, amode);
    label->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	label->snapToPixels = true;
	
	color.setColorHexFromString(conf->getStringValue("Polycode", "uiDefaultFontColor"));
	addChild(label);
	bBox = label->bBox;
}

void UILabel::setText(const String& text) {
	label->setText(text);
	bBox = label->bBox;	
}

String UILabel::getText() {
	return label->getText();
}

UILabel::~UILabel() {
	delete label;
}

Label *UILabel::getLabel() {
	return label->getLabel();
}

UIRect::UIRect(String fileName, Number width, Number height) : UIElement() {
	texture = NULL;
	loadTexture(fileName);
    initRect(width, height);
    imageWidth = width;
    imageHeight = height;
}

UIRect::UIRect(String fileName) : UIElement() {
	texture = NULL;
	loadTexture(fileName);
	if(texture) {	
		initRect(texture->getWidth(), texture->getHeight());
		imageWidth = texture->getWidth();
		imageHeight = texture->getHeight();	
	} else {
		initRect(1,  1);
		imageWidth = 0;
		imageHeight = 0;
	}
    setWidth(imageWidth);
    setHeight(imageHeight);
}

UIRect::UIRect(Number width, Number height) : UIElement() {
	texture = NULL;
	initRect(width, height);
	imageWidth = 0;
	imageHeight = 0;
}

void UIRect::setImageCoordinates(Number x, Number y, Number width, Number height, Number imageScale) {
    Vertex *vertex;
	Number pixelSizeX = 1/imageWidth;
	Number pixelSizeY = 1/imageHeight;

	setWidth(width);
	setHeight(height);

	Number whalf = width/2.0f;
	Number hhalf = height/2.0f;
		
	Number xFloat = x * pixelSizeX * imageScale;
	Number yFloat = (y * pixelSizeY) * imageScale;
	Number wFloat = width * pixelSizeX * imageScale;
	Number hFloat = height * pixelSizeY * imageScale;

	vertex = rectMesh->getVertex(0);
	vertex->set(-whalf,-hhalf,0);
	vertex->setTexCoord(xFloat, (1.0-yFloat) - hFloat);

	vertex = rectMesh->getVertex(1);
	vertex->set(-whalf+width,-hhalf,0);
	vertex->setTexCoord(xFloat + wFloat, (1.0-yFloat) - hFloat);

	vertex = rectMesh->getVertex(2);
	vertex->set(-whalf+width,-hhalf+height,0);
	vertex->setTexCoord(xFloat + wFloat, 1.0-yFloat);

	vertex = rectMesh->getVertex(3);
	vertex->set(-whalf,-hhalf+height,0);	
	vertex->setTexCoord(xFloat, 1.0-yFloat);

	rectMesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
	rectMesh->arrayDirtyMap[RenderDataArray::TEXCOORD_DATA_ARRAY] = true;	
	rebuildTransformMatrix();
	matrixDirty = true;
}

Number UIRect::getImageWidth() const {
	return imageWidth;
}

Number UIRect::getImageHeight() const {
	return imageHeight;	
}

void UIRect::initRect(Number width, Number height) {
	rectMesh = new Mesh(Mesh::QUAD_MESH);
	processInputEvents = true;

	setAnchorPoint(-1.0, -1.0, 0.0);
	setWidth(width);	
	setHeight(height);
	
	Number whalf = width/2.0f;
	Number hhalf = height/2.0f;
				
	rectMesh->addVertex(-whalf,-hhalf,0,0,0);
	rectMesh->addVertex(-whalf+width,-hhalf,0, 1, 0);
	rectMesh->addVertex(-whalf+width,-hhalf+height,0, 1, 1);
	rectMesh->addVertex(-whalf,-hhalf+height,0,0,1);
}

UIRect::~UIRect() {
	delete rectMesh;
}

void UIRect::loadTexture(String fileName) {
	MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
	texture = materialManager->createTextureFromFile(fileName, materialManager->clampDefault, false);
}

void UIRect::setTexture(Texture *texture) {
	this->texture = texture;
}	

Texture *UIRect::getTexture() {
	return texture;
}

void UIRect::Render() {
	renderer->clearShader();
	renderer->setTexture(texture);
	renderer->pushDataArrayForMesh(rectMesh, RenderDataArray::VERTEX_DATA_ARRAY);
	renderer->pushDataArrayForMesh(rectMesh, RenderDataArray::TEXCOORD_DATA_ARRAY);	
	renderer->drawArrays(Mesh::QUAD_MESH);
}

void UIRect::Resize(Number width, Number height) {

	setWidth(width);	
	setHeight(height);

	Number whalf = width/2.0f;
	Number hhalf = height/2.0f;
	Vertex *vertex;

	vertex = rectMesh->getVertex(0);
	vertex->set(-whalf,-hhalf,0);			
	vertex = rectMesh->getVertex(1);
	vertex->set(-whalf+width,-hhalf,0);			
	vertex = rectMesh->getVertex(2);
	vertex->set(-whalf+width,-hhalf+height,0);			
	vertex = rectMesh->getVertex(3);
	vertex->set(-whalf,-hhalf+height,0);				
	rectMesh->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;	
}

UIImage::UIImage(String imagePath, int width, int height) : UIRect(imagePath, width, height) {
    setBlendingMode(Renderer::BLEND_MODE_NORMAL);
}

UIImage::UIImage(String imagePath) : UIRect(imagePath) {
    setBlendingMode(Renderer::BLEND_MODE_NORMAL);
}

UIElement::UIElement() : Entity() {
	snapToPixels = true;
	setAnchorPoint(-1.0, -1.0, 0.0);
	processInputEvents = true;
	depthTest = false;	
	hasFocus = false;
	focusable = false;
	focusParent = NULL;
	hasDragLimits = false;
	dragged = false;
	depthTest = false;
	depthWrite = false;			
}

UIElement::UIElement(Number width, Number height) : Entity() {
	setAnchorPoint(-1.0, -1.0, 0.0);
	processInputEvents = true;
	focusParent = NULL;
	hasFocus = false;
	hasDragLimits = false;	
	dragged = false;	
	depthTest = false;
	depthWrite = false;		
	setWidth(width);
	setHeight(height);
}

void UIElement::addChild(Entity *child) {
	UIElement* uiChild = dynamic_cast<UIElement*>(child);
	if(uiChild) {
		addFocusChild(uiChild);
	}
	Entity::addChild(child);
}

void UIElement::setDragLimits(Rectangle rect) {
	dragLimits.x = rect.x;
	dragLimits.y = rect.y;
	dragLimits.w = rect.w;
	dragLimits.h = rect.h;
	hasDragLimits = true;
}

void UIElement::clearDragLimits() {
	hasDragLimits = false;
}

bool UIElement::isDragged() {
	return dragged;
}

void UIElement::startDrag(Number xOffset, Number yOffset) {
	dragged = true;
	dragOffsetX = xOffset;
	dragOffsetY = yOffset;
}

void UIElement::stopDrag() {
	dragged = false;
}

bool UIElement::isFocusable() {
	return focusable;
}

MouseEventResult UIElement::onMouseMove(const Ray &ray, int timestamp) {
	if(dragged) {	
		Vector3 localCoordinate = Vector3(ray.origin.x, ray.origin.y,0);

		if(parentEntity) {
			Matrix4 inverse = parentEntity->getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;		
		}
		setPosition(localCoordinate.x-dragOffsetX,-localCoordinate.y-dragOffsetY);
		if(hasDragLimits) {
			if(position.x < dragLimits.x)
				position.x = dragLimits.x;
			if(position.x > dragLimits.x + dragLimits.w)
				position.x = dragLimits.x + dragLimits.w;
			if(position.y < dragLimits.y)
				position.y = dragLimits.y;
			if(position.y > dragLimits.y + dragLimits.h)
				position.y = dragLimits.y + dragLimits.h;
		}		
		
	}
	return Entity::onMouseMove(ray, timestamp);
}

UIElement::~UIElement() {
	if(UIElement::globalFocusedChild == this) {
		UIElement::globalFocusedChild = NULL;
	}
}

void UIElement::focusNextChild() {

	int j = 0;
	bool hasFocusedChild = false;
	if(UIElement::globalFocusedChild) {
		for(int i=0; i < focusChildren.size(); i++) {
			if(focusChildren[i] == UIElement::globalFocusedChild) {
				j = i;
				hasFocusedChild = true;
			}
		}
	}

	if(!hasFocusedChild)
		return;

	for(int i=0; i < focusChildren.size(); i++) {
		if(focusChildren[j]->isFocusable() && focusChildren[j] != UIElement::globalFocusedChild) {
			focusChild(focusChildren[j]);
			return;
		}

		j++;
		if(j == focusChildren.size())
			j = 0;
	}
}

void UIElement::focusSelf() {
	if(UIElement::globalFocusedChild) {
		UIElement::globalFocusedChild->onLoseFocus();
		UIElement::globalFocusedChild->hasFocus = false;
	}

	UIElement::globalFocusedChild = this;
	
	onGainFocus();
	hasFocus = true;
}

void UIElement::focusChild(UIElement *child) {

	if(UIElement::globalFocusedChild) {
		UIElement::globalFocusedChild->onLoseFocus();
		UIElement::globalFocusedChild->hasFocus = false;
	}

	UIElement::globalFocusedChild = child;
	
	if(child) {
		UIElement::globalFocusedChild->onGainFocus();
		UIElement::globalFocusedChild->hasFocus = true;
	}	
}

void UIElement::addFocusChild(UIElement *element) {
	element->setFocusParent(element);
	focusChildren.push_back(element);
}

void UIElement::setFocusParent(UIElement *element) {
	focusParent = element;	
}

void UIElement::Resize(Number width, Number height) {
	setWidth(width);
	setHeight(height);
	dirtyMatrix(true);	
}
