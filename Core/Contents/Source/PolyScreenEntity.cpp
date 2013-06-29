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

#include "PolyScreenEntity.h"
#include "PolyInputEvent.h"
#include "PolyRectangle.h"
#include "PolyPolygon.h"
#include "PolyVertex.h"
#include "PolyRenderer.h"
#include "PolyCoreServices.h"
#include "PolyLogger.h"

inline double round(double x) { return floor(x + 0.5); }

using namespace Polycode;

ScreenEntity::ScreenEntity() : Entity() {
	color = Color(1.0f,1.0f,1.0f,1.0f);
	width = 0;
	height = 0;
	setHitbox(1, 1);
	backfaceCulled = false;
	positionMode = POSITION_TOPLEFT;
	mouseOver = false;
	dragged = false;

	dragOffsetX = 0;
	dragOffsetY = 0;
	parentEntity = NULL;
	
	depthWrite = false;
	depthTest = false;
	
	focusable = false;
	hasFocus = false;
	focusChildren = false;	
	blockMouseInput = false;
	
	snapToPixels = false;

	lastClickTicks = 0;
	dragLimits = NULL;

	xmouse = 0;
	ymouse = 0;

	processInputEvents = false;

}

Entity *ScreenEntity::Clone(bool deepClone, bool ignoreEditorOnly) {
	ScreenEntity *newEntity = new ScreenEntity();
	applyClone(newEntity, deepClone, ignoreEditorOnly);
	return newEntity;
}

void ScreenEntity::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) {
	Entity::applyClone(clone, deepClone, ignoreEditorOnly);

	ScreenEntity *_clone = (ScreenEntity*) clone;
	_clone->width = width;
	_clone->height = height;
	_clone->setHitbox(hit.x, hit.y, hit.w, hit.h);
	_clone->positionMode = positionMode;
	_clone->focusable = focusable;
	_clone->blockMouseInput = blockMouseInput;
	_clone->snapToPixels = snapToPixels;
	_clone->processInputEvents = processInputEvents;

}

void ScreenEntity::addEntity(Entity *newChild) {
	((ScreenEntity*)newChild)->setDefaultScreenOptions(snapToPixels);
	Entity::addEntity(newChild);
}

void ScreenEntity::setDefaultScreenOptions(bool snapToPixels) {
	this->snapToPixels = snapToPixels;
		for(int i=0; i < children.size(); i++) {
			((ScreenEntity*)children[i])->setDefaultScreenOptions(snapToPixels);
		}
}

void ScreenEntity::focusNextChild() {
	int j = 0;
	bool hasFocusedChild = false;
	if(CoreServices::getInstance()->focusedChild) {
		for(int i=0; i < children.size(); i++) {
			if(children[i] == CoreServices::getInstance()->focusedChild) {
				j = i;
				hasFocusedChild = true;
			}
		}
	}

	if(!hasFocusedChild)
		return;

	for(int i=0; i < children.size(); i++) {
		if(((ScreenEntity*)children[j])->isFocusable() && children[j] != CoreServices::getInstance()->focusedChild) {
			focusChild(((ScreenEntity*)children[j]));
			return;
		}

		j++;
		if(j == children.size())
			j = 0;
	}
}

Number ScreenEntity::getRotation() const {
	return this->getRoll();
}

void ScreenEntity::focusChild(ScreenEntity *child) {
	if(CoreServices::getInstance()->focusedChild != NULL) {
		((ScreenEntity*)CoreServices::getInstance()->focusedChild)->onLoseFocus();
		((ScreenEntity*)CoreServices::getInstance()->focusedChild)->hasFocus = false;
	}
	CoreServices::getInstance()->focusedChild = child;
	if(child) {
		((ScreenEntity*)CoreServices::getInstance()->focusedChild)->hasFocus = true;
		((ScreenEntity*)CoreServices::getInstance()->focusedChild)->onGainFocus();
	}
}

void ScreenEntity::moveChildUp(ScreenEntity *child) {
	for(int i=0; i < children.size(); i++) {
		if(children[i] == child && i < children.size()-1) {
			ScreenEntity *next = (ScreenEntity*)children[i+1];
			children[i+1] = child;
			children[i] = next;
			break;
		}
	}
}

void ScreenEntity::moveChildDown(ScreenEntity *child) {
	for(int i=0; i < children.size(); i++) {
		if(children[i] == child && i > 0) {
			ScreenEntity *prev = (ScreenEntity*)children[i-1];
			children[i-1] = child;
			children[i] = prev;
			break;
		}
	}
}

void ScreenEntity::moveChildTop(ScreenEntity *child) {
	for(int i=0; i < children.size(); i++) {
		if(children[i] == child && i < children.size()-1) {
			children.erase(children.begin()+i);
			children.push_back(child);
			break;
		}
	}
}

void ScreenEntity::moveChildBottom(ScreenEntity *child) {
	for(int i=0; i < children.size(); i++) {
		if(children[i] == child && i > 0) {
			children.erase(children.begin()+i);
			children.insert(children.begin(), child);
			break;
		}
	}
}

bool ScreenEntity::isFocusable() const {
	return focusable;
}

void ScreenEntity::startDrag(Number xOffset, Number yOffset) {
	dragged = true;
	dragOffsetX = xOffset;
	dragOffsetY = yOffset;
}

void ScreenEntity::stopDrag() {
	dragged = false;
}

ScreenEntity::~ScreenEntity() {
	if(CoreServices::getInstance()->focusedChild == this) 
		CoreServices::getInstance()->focusedChild = NULL;
	if(dragLimits) 
		delete dragLimits;
}

void ScreenEntity::setBlendingMode(int newBlendingMode) {
	blendingMode = newBlendingMode;
}

void ScreenEntity::setPosition(Number x, Number y) {
	position.x  = x;
	position.y  = y;
	matrixDirty = true;
}

void ScreenEntity::setPosition(const Vector2 &v) {
	position.x  = v.x;
	position.y  = v.y;
	matrixDirty = true;
}

void ScreenEntity::setScale(Number x, Number y) {
	scale.x = x;
	scale.y = y;
	matrixDirty = true;
}

void ScreenEntity::setScale(const Vector2 &v) {
	scale.x = v.x;
	scale.y = v.y;
	matrixDirty = true;
}


Number ScreenEntity::getWidth() const {
	return width;
}

Number ScreenEntity::getHeight() const {
	return height;
}

bool isPointInsidePolygon2D(Polycode::Polygon *poly, const Vector2 &p) {
	Number angle = 0.0;
	Vector2 p1,p2;
/*	
	printf("PIP: %f,%f in [%f,%f], [%f,%f], [%f,%f], [%f,%f]\n", p.x, p.y, 
		poly->getVertex(0)->x, poly->getVertex(0)->y,
		poly->getVertex(1)->x, poly->getVertex(1)->y,
		poly->getVertex(2)->x, poly->getVertex(2)->y,
		poly->getVertex(3)->x, poly->getVertex(3)->y);
*/
	for (int i=0; i < poly->getVertexCount(); i++) {

		p1.x = poly->getVertex(i)->x - p.x;
		p1.y = poly->getVertex(i)->y - p.y;
		p2.x = poly->getVertex((i+1)%poly->getVertexCount())->x - p.x;
		p2.y = poly->getVertex((i+1)%poly->getVertexCount())->y - p.y;

		Vector2 vec(p1.x,p1.y);
		angle += vec.angle(Vector2(p2.x,p2.y));

	}

	return !(fabs(angle) < PI);
}


bool ScreenEntity::hitTest(const Number x, const Number y) {

	Vector3 v;
	Polygon testPoly;

	Matrix4 transformMatrix = getConcatenatedMatrix();
	v = Vector3(hit.x, hit.y, 0);
	v = transformMatrix * v;
	testPoly.addVertex(v.x, v.y, 0.0);

	v = Vector3(hit.x+hit.w, hit.y, 0);
	v = transformMatrix * v;
	testPoly.addVertex(v.x, v.y, 0.0);

	v = Vector3(hit.x+hit.w, hit.y+hit.h, 0);
	v = transformMatrix * v;
	testPoly.addVertex(v.x, v.y, 0.0);

	v = Vector3(hit.x,hit.y+hit.h, 0);
	v = transformMatrix * v;
	testPoly.addVertex(v.x, v.y, 0.0);

	return isPointInsidePolygon2D(&testPoly, Vector2(x,y));
}

void ScreenEntity::setPositionMode(int newPositionMode) {
	positionMode = newPositionMode;
}

void ScreenEntity::_onKeyDown(PolyKEY key, wchar_t charCode) {
	onKeyDown(key, charCode);
	for(int i=0;i<children.size();i++) {
		((ScreenEntity*)children[i])->_onKeyDown(key, charCode);
	}
}

void ScreenEntity::_onKeyUp(PolyKEY key, wchar_t charCode) {
	onKeyUp(key, charCode);
	for(int i=0;i<children.size();i++) {
		((ScreenEntity*)children[i])->_onKeyUp(key, charCode);
	}
}

int ScreenEntity::getPositionMode() {
	return positionMode;
}

void ScreenEntity::setDragLimits(Polycode::Rectangle rect) {
	if(!dragLimits)
		dragLimits = new Polycode::Rectangle();
	dragLimits->x = rect.x;
	dragLimits->y = rect.y;
	dragLimits->w = rect.w;
	dragLimits->h = rect.h;
}

void ScreenEntity::clearDragLimits() {
	delete dragLimits;
	dragLimits = NULL;
}

Rectangle ScreenEntity::getHitbox() {
	return hit;
}

void ScreenEntity::setHitbox(Number width, Number height) {
	hit.w = width;
	hit.h = height;
	hit.x = -width/2;
	hit.y = -height/2;
}
void ScreenEntity::setHitbox(Number width, Number height, Number left, Number top) {
	hit.w = width;
	hit.h = height;
	hit.x = left;
	hit.y = top;
}

bool ScreenEntity::isDragged() {
	return dragged;
}

Matrix4 ScreenEntity::getScreenConcatenatedMatrix() {
	Matrix4 retMatrix = transformMatrix;
	if(positionMode == POSITION_TOPLEFT) {
		Vector3 pos = retMatrix.getPosition();
		retMatrix.setPosition(pos.x + width/2.0, pos.y + height/2.0, 0);
	}

	if(parentEntity) {
		return retMatrix * ((ScreenEntity*)parentEntity)->getScreenConcatenatedMatrix();
	} else {
		return retMatrix;
	}
}

MouseEventResult ScreenEntity::_onMouseMove(Number x, Number y, int timestamp, Vector2 parentAdjust) {

	if(dragged) {
		Vector3 localCoordinate = Vector3(x+(parentAdjust.x*2.0),y+(parentAdjust.y*2.0),0);

		if(parentEntity) {
			Matrix4 inverse = ((ScreenEntity*)parentEntity)->getScreenConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;
		}

		setPosition(localCoordinate.x-dragOffsetX,localCoordinate.y-dragOffsetY);
		if(dragLimits) {
			if(position.x < dragLimits->x)
				position.x = dragLimits->x;
			if(position.x > dragLimits->x + dragLimits->w)
				position.x = dragLimits->x + dragLimits->w;
			if(position.y < dragLimits->y)
				position.y = dragLimits->y;
			if(position.y > dragLimits->y + dragLimits->h)
				position.y = dragLimits->y + dragLimits->h;
		}
	}


	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;


	if(processInputEvents && enabled) {
		if(hitTest(x+parentAdjust.x,y+parentAdjust.y)) {
			Vector3 localCoordinate = Vector3(x+(parentAdjust.x*2.0),y+(parentAdjust.y*2.0),0);
			Matrix4 inverse = getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.x += hit.w/2.0;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.y += hit.h/2.0;

			onMouseMove(localCoordinate.x,localCoordinate.y);
			xmouse = localCoordinate.x;
			ymouse = localCoordinate.y;

			dispatchEvent(new InputEvent(Vector2(localCoordinate.x,localCoordinate.y)-parentAdjust, timestamp), InputEvent::EVENT_MOUSEMOVE);
			
			if(!mouseOver) {
				dispatchEvent(new InputEvent(Vector2(localCoordinate.x,localCoordinate.y)-parentAdjust, timestamp), InputEvent::EVENT_MOUSEOVER);
				mouseOver = true;
			}
			ret.hit = true;
			if(blockMouseInput) {
				ret.blocked = true;
			}

		} else if(mouseOver) {

			Vector3 localCoordinate = Vector3(x+(parentAdjust.x*2.0),y+(parentAdjust.y*2.0),0);
			Matrix4 inverse = getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.x += hit.w/2.0;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.y += hit.h/2.0;

			dispatchEvent(new InputEvent(Vector2(localCoordinate.x,localCoordinate.y)-parentAdjust, timestamp), InputEvent::EVENT_MOUSEOUT);
			mouseOver = false;
		}

		for(int i=children.size()-1;i>=0;i--) {
			Vector2 adjust = parentAdjust;
			if(positionMode == POSITION_TOPLEFT)
				adjust += Vector2(floor(width/2.0), floor(height/2.0));

			MouseEventResult childRes = ((ScreenEntity*)children[i])->_onMouseMove(x,y, timestamp, adjust);
			if(childRes.hit)
				ret.hit = true;
			if(childRes.blocked)
				ret.blocked = true;
			if(childRes.blocked)
				break;
		}
	}

	return ret;
}

MouseEventResult ScreenEntity::_onMouseUp(Number x, Number y, int mouseButton, int timestamp, Vector2 parentAdjust) {
	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;


	if(processInputEvents && enabled) {
		if(hitTest(x+parentAdjust.x,y+parentAdjust.y)) {
			Vector3 localCoordinate = Vector3(x+(parentAdjust.x*2.0),y+(parentAdjust.y*2.0),0);

			Matrix4 inverse = getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.x += hit.w/2.0;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.y += hit.h/2.0;

			onMouseUp(localCoordinate.x,localCoordinate.y);
			InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x,localCoordinate.y)-parentAdjust, timestamp);
			inputEvent->mouseButton = mouseButton;
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEUP);

			ret.hit = true;
			if(blockMouseInput) {
				ret.blocked = true;
			}

		} else {
			Vector3 localCoordinate = Vector3(x+(parentAdjust.x*2.0),y+(parentAdjust.y*2.0),0);

			Matrix4 inverse = getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.x += hit.w/2.0;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.y += hit.h/2.0;

			InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x,localCoordinate.y)-parentAdjust, timestamp);
			inputEvent->mouseButton = mouseButton;
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEUP_OUTSIDE);
		}

		for(int i=children.size()-1;i>=0;i--) {
			Vector2 adjust = parentAdjust;
			if(positionMode == POSITION_TOPLEFT)
				adjust += Vector2(floor(width/2.0), floor(height/2.0));
			MouseEventResult childRes = ((ScreenEntity*)children[i])->_onMouseUp(x,y, mouseButton, timestamp, adjust);
			if(childRes.hit)
				ret.hit = true;
			if(childRes.blocked)
				ret.blocked = true;
			if(childRes.blocked)
				break;

		}
	}

	return ret;
}

MouseEventResult ScreenEntity::_onMouseWheelUp(Number x, Number y, int timestamp, Vector2 parentAdjust) {

	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;

	if(processInputEvents && enabled) {
		if(hitTest(x+parentAdjust.x,y+parentAdjust.y)) {
			Vector3 localCoordinate = Vector3(x+(parentAdjust.x*2.0),y+(parentAdjust.y*2.0),0);

			Matrix4 inverse = getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.x += hit.w/2.0;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.y += hit.h/2.0;

			onMouseWheelUp(localCoordinate.x,localCoordinate.y);

			InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x,localCoordinate.y)-parentAdjust, timestamp);
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEWHEEL_UP);

			ret.hit = true;
			if(blockMouseInput) {
				ret.blocked = true;
			}

		}

		for(int i=children.size()-1;i>=0;i--) {
			Vector2 adjust = parentAdjust;
			if(positionMode == POSITION_TOPLEFT)
				adjust += Vector2(floor(width/2.0), floor(height/2.0));
			MouseEventResult childRes = ((ScreenEntity*)children[i])->_onMouseWheelUp(x,y, timestamp, adjust);
			if(childRes.hit)
				ret.hit = true;
			if(childRes.blocked)
				ret.blocked = true;
			if(childRes.blocked)
				break;
		}
	}
	return ret;
}

MouseEventResult ScreenEntity::_onMouseWheelDown(Number x, Number y, int timestamp, Vector2 parentAdjust) {
	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;

	if(processInputEvents && enabled) {
		if(hitTest(x+parentAdjust.x,y+parentAdjust.y)) {
			Vector3 localCoordinate = Vector3(x+(parentAdjust.x*2.0),y+(parentAdjust.y*2.0),0);

			Matrix4 inverse = getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.x += hit.w/2.0;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.y += hit.h/2.0;

			onMouseWheelDown(localCoordinate.x,localCoordinate.y);

			InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x,localCoordinate.y)-parentAdjust, timestamp);
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEWHEEL_DOWN);

			ret.hit = true;
			if(blockMouseInput) {
				ret.blocked = true;
			}
		}

		for(int i=children.size()-1;i>=0;i--) {
			Vector2 adjust = parentAdjust;
			if(positionMode == POSITION_TOPLEFT)
				adjust += Vector2(floor(width/2.0), floor(height/2.0));

			MouseEventResult childRes = ((ScreenEntity*)children[i])->_onMouseWheelDown(x,y, timestamp, adjust);
			if(childRes.hit)
				ret.hit = true;
			if(childRes.blocked)
				ret.blocked = true;
			if(childRes.blocked)
				break;

		}
	}

	return ret;
}


MouseEventResult ScreenEntity::_onMouseDown(Number x, Number y, int mouseButton, int timestamp, Vector2 parentAdjust) {
	MouseEventResult ret;
	ret.hit = false;
	ret.blocked = false;

	if(processInputEvents && enabled) {
		if(hitTest(x+parentAdjust.x,y+parentAdjust.y)) {
			Vector3 localCoordinate = Vector3(x+(parentAdjust.x*2.0),y+(parentAdjust.y*2.0),0);

			Matrix4 inverse = getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.x += hit.w/2.0;
			if(positionMode == POSITION_TOPLEFT)
				localCoordinate.y += hit.h/2.0;

			onMouseDown(localCoordinate.x,localCoordinate.y);

			InputEvent *inputEvent = new InputEvent(Vector2(localCoordinate.x,localCoordinate.y)-parentAdjust, timestamp);

			inputEvent->mouseButton = mouseButton;
			dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEDOWN);

			if(timestamp - lastClickTicks < 400) {
				InputEvent *inputEvent = new InputEvent(Vector2(x,y), timestamp);
				inputEvent->mouseButton = mouseButton;
				dispatchEvent(inputEvent, InputEvent::EVENT_DOUBLECLICK);
			}
			lastClickTicks = timestamp;
			ret.hit = true;
			if(blockMouseInput) {
				ret.blocked = true;
			}
		}

		for(int i=children.size()-1;i>=0;i--) {
				Vector2 adjust = parentAdjust;
				if(positionMode == POSITION_TOPLEFT)
					adjust += Vector2(floor(width/2.0), floor(height/2.0));
				MouseEventResult childRes = ((ScreenEntity*)children[i])->_onMouseDown(x,y, mouseButton, timestamp, adjust);
				if(childRes.hit)
					ret.hit = true;
				if(childRes.blocked)
					ret.blocked = true;
				if(childRes.blocked)
					break;
			}
	}

	return ret;
}

Vector2 ScreenEntity::getScreenPosition() const {
	Vector2 ret = getPosition2D();

	if(parentEntity) {
		return ret + ((ScreenEntity*)parentEntity)->getScreenPosition();
	} else {
		return ret;
	}
}

void ScreenEntity::setRotation(Number rotation) {
	setRoll(rotation);
}

Vector2 ScreenEntity::getPosition2D() const {
	return Vector2(position.x, position.y);
}

Vector2 ScreenEntity::getScale2D() const {
	return Vector2(scale.x, scale.y);
}

Matrix4 ScreenEntity::buildPositionMatrix() {

	Matrix4 posMatrix;
	switch(positionMode) {
		case POSITION_TOPLEFT:
			posMatrix.m[3][0] = (position.x+floor(width/2.0f)*scale.x)*matrixAdj;
			posMatrix.m[3][1] = (position.y+floor(height/2.0f)*scale.y)*matrixAdj;
			posMatrix.m[3][2] = position.z*matrixAdj;
		break;
		case POSITION_CENTER:
			posMatrix.m[3][0] = position.x*matrixAdj;
			posMatrix.m[3][1] = position.y*matrixAdj;
			posMatrix.m[3][2] = position.z*matrixAdj;
		break;
	}


	if(snapToPixels) {
		posMatrix.m[3][0] = round(posMatrix.m[3][0]);
		posMatrix.m[3][1] = round(posMatrix.m[3][1]);
		posMatrix.m[3][2] = round(posMatrix.m[3][2]);
	}

	return posMatrix;
}

void ScreenEntity::adjustMatrixForChildren() {
	if(positionMode == POSITION_TOPLEFT) {
		if(snapToPixels) {
			renderer->translate2D(-floor(width/2.0f), -floor(height/2.0f));
		} else {
			renderer->translate2D(-width/2.0f, -height/2.0f);
		}
	}
}

ScreenEntity *ScreenEntity::getScreenEntityById(String id, bool recursive) {
	return (ScreenEntity*)getEntityById(id, recursive);
}

std::vector<ScreenEntity*> ScreenEntity::getScreenEntitiesByTag(String tag, bool recursive) {
	std::vector<Entity*> entities = getEntitiesByTag(tag, recursive);
	std::vector<ScreenEntity*> retEntities;
	for(int i=0; i < entities.size(); i++) {
		retEntities.push_back((ScreenEntity*)entities[i]);
	}
	return retEntities;
}

