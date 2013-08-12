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

using namespace Polycode;

UIImage::UIImage(String imagePath) : UIElement() {
	image = new SceneImage(imagePath);
	addChild(image);
	setWidth(image->bBox.x);
	setHeight(image->bBox.y);	
}

UIElement::UIElement() : Entity() {
	setAnchorPoint(-1.0, -1.0, 0.0);
	processInputEvents = true;
	depthTest = false;	
	hasFocus = false;
	focusable = false;
	focusParent = NULL;
	hasDragLimits = false;
	dragged = false;	
}

UIElement::UIElement(Number width, Number height) : Entity() {
	setAnchorPoint(-1.0, -1.0, 0.0);
	processInputEvents = true;
	focusParent = NULL;
	hasDragLimits = false;	
	dragged = false;	
	setWidth(width);
	setHeight(height);
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
		setPosition(localCoordinate.x-dragOffsetX,-localCoordinate.y+dragOffsetY);
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
