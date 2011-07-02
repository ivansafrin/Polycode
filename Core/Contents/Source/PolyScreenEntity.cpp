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

inline double round(double x) { return floor(x + 0.5); }

using namespace Polycode;

ScreenEntity::ScreenEntity() : Entity(), EventDispatcher() {
	color = new Color(1.0f,1.0f,1.0f,1.0f);
	width = 1;
	height = 1;
	hitwidth = 1;
	hitheight = 1;
	backfaceCulled = false;
	positionMode = POSITION_TOPLEFT;
	mouseOver = false;
	isDragged = false;

	dragOffsetX = 0;
	dragOffsetY = 0;
	parentEntity = NULL;
	zindex = 0;
	
	depthWrite = false;
	depthTest = false;
	
	focusable = false;
	hasFocus = false;
	focusChildren = false;	
	focusedChild = NULL;
	blockMouseInput = false;
	
	snapToPixels = false;

	lastClickTicks = 0;
	dragLimits = NULL;
	
	xmouse = 0;
	ymouse = 0;
	
}

void ScreenEntity::focusNextChild() {
	int j = 0;
	if(focusedChild) {
		for(int i=0; i < children.size(); i++) {
			if(children[i] == focusedChild)
				j = i;
		}
	}
	
	for(int i=0; i < children.size(); i++) {
		if(((ScreenEntity*)children[j])->isFocusable() && children[j] != focusedChild) {
			focusChild(((ScreenEntity*)children[j]));
			return;
		}
		
		j++;
		if(j == children.size())
			j = 0;
	}
}

Number ScreenEntity::getRotation() {
	return this->getRoll();
}

void ScreenEntity::focusChild(ScreenEntity *child) {
	if(focusedChild != NULL) {
		focusedChild->onLoseFocus();
		focusedChild->hasFocus = false;
	}
	focusedChild = child;
	focusedChild->hasFocus = true;
	focusedChild->onGainFocus();
}

bool ScreenEntity::isFocusable() {
	return focusable;
}

void ScreenEntity::startDrag(Number xOffset, Number yOffset) {
	isDragged = true;
	dragOffsetX = xOffset;
	dragOffsetY = yOffset;
}

void ScreenEntity::stopDrag() {
	isDragged = false;
}

ScreenEntity::~ScreenEntity() {

}

void ScreenEntity::setBlendingMode(int newBlendingMode) {
	blendingMode = newBlendingMode;
}

void ScreenEntity::setPosition(Number x, Number y) {
	position.x  = x;
	position.y  = y;
	matrixDirty = true;
}

void ScreenEntity::setScale(Number x, Number y) {
	scale.x = x;
	scale.y = y;
	matrixDirty = true;	
}

Number ScreenEntity::getWidth() {
	return width;
}

Number ScreenEntity::getHeight() {
	return height;
}

bool ScreenEntity::hitTest(Number x, Number y) {
	bool retVal = false;
    // apply compound scale to test hit against
    Vector3 compScale = getCompoundScale();
    Number hx = position.x * compScale.x;
    Number hy = position.y * compScale.y;
    Number hw = hitwidth * compScale.x;
    Number hh = hitheight * compScale.y;
    //        Logger::log("hittest %f,%f in %f %f %f %f\n",x, y, hx, hy, hw, hh);
	switch(positionMode) {
		case ScreenEntity::POSITION_TOPLEFT:
						
            if(x > hx && x < (hx + hw)
                && y > hy && y < (hy + hh))
				retVal = true;			
		break;
		case ScreenEntity::POSITION_CENTER:
            if(x > (hx - hw/2.0f) && x < (hx + hw/2.0f)
                && y > (hy - hh/2.0f) && y < (hy + hh/2.0f))
				retVal = true;	
		break;
	}

	return retVal;
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

void ScreenEntity::_onMouseMove(Number x, Number y, int timestamp) {

	if(isDragged) {
		setPosition(x-dragOffsetX,y-dragOffsetY);
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
	
	xmouse = x-position.x;
	ymouse = y-position.y;

	onMouseMove(x,y);
	if(enabled) {
		if(hitTest(x,y)) {
			dispatchEvent(new InputEvent(Vector2(x,y), timestamp), InputEvent::EVENT_MOUSEMOVE);
			if(!mouseOver) {
				dispatchEvent(new InputEvent(Vector2(x,y), timestamp), InputEvent::EVENT_MOUSEOVER);
				mouseOver = true;
			}
		} else {
			if(mouseOver) {
				dispatchEvent(new InputEvent(Vector2(x,y), timestamp), InputEvent::EVENT_MOUSEOUT);
				mouseOver = false;
			}
		}
	}
	
	if(enabled) {
		for(int i=0;i<children.size();i++) {
			((ScreenEntity*)children[i])->_onMouseMove(x-position.x,y-position.y, timestamp);
		}
	}
}

bool ScreenEntity::_onMouseUp(Number x, Number y, int mouseButton, int timestamp) {
	bool retVal = false;
	if(hitTest(x,y) && enabled) {
		onMouseUp(x,y);
		
		InputEvent *inputEvent = new InputEvent(Vector2(x,y), timestamp);		
		inputEvent->mouseButton = mouseButton;		
		dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEUP);
		retVal = true;		
	} else {
		
		InputEvent *inputEvent = new InputEvent(Vector2(x,y), timestamp);		
		inputEvent->mouseButton = mouseButton;
		
		dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	}
	
	if(enabled) {
		for(int i=0;i<children.size();i++) {
			((ScreenEntity*)children[i])->_onMouseUp(x-position.x,y-position.y, mouseButton, timestamp);
		}
	}
	return retVal;
}

void ScreenEntity::_onMouseWheelUp(Number x, Number y, int timestamp) {
	bool doTest = true;
	
	if(hasMask) {
		if(!((ScreenEntity*)maskEntity)->hitTest(x-position.x,y-position.y)) {
			doTest = false;
		}	
	}
	
	if(doTest) {
		if(hitTest(x,y) && enabled) {
			onMouseWheelUp(x,y);
			dispatchEvent(new InputEvent(Vector2(x,y), timestamp), InputEvent::EVENT_MOUSEWHEEL_UP);
		}
		if(enabled) {
			for(int i=children.size()-1;i>=0;i--) {				
				((ScreenEntity*)children[i])->_onMouseWheelUp(x-position.x,y-position.y, timestamp);
				if(((ScreenEntity*)children[i])->blockMouseInput && ((ScreenEntity*)children[i])->enabled) {
					if(((ScreenEntity*)children[i])->hitTest(x-position.x,y-position.y))
						break;
				}
			}
		}
	}	
}

void ScreenEntity::_onMouseWheelDown(Number x, Number y, int timestamp) {
	bool doTest = true;
	
	if(hasMask) {
		if(!((ScreenEntity*)maskEntity)->hitTest(x-position.x,y-position.y)) {
			doTest = false;
		}	
	}
	
	if(doTest) {
		if(hitTest(x,y) && enabled) {
			onMouseWheelDown(x,y);
			dispatchEvent(new InputEvent(Vector2(x,y), timestamp), InputEvent::EVENT_MOUSEWHEEL_DOWN);
		}
		if(enabled) {
			for(int i=children.size()-1;i>=0;i--) {				
				((ScreenEntity*)children[i])->_onMouseWheelDown(x-position.x,y-position.y, timestamp);
				if(((ScreenEntity*)children[i])->blockMouseInput && ((ScreenEntity*)children[i])->enabled) {
					if(((ScreenEntity*)children[i])->hitTest(x-position.x,y-position.y))
						break;
				}
			}
		}
	}	
}


bool ScreenEntity::_onMouseDown(Number x, Number y, int mouseButton, int timestamp) {
	bool retVal = false;
	
	bool doTest = true;
	
	if(hasMask) {
		if(!((ScreenEntity*)maskEntity)->hitTest(x,y)) {
			doTest = false;
		}	
	}
	
	if(doTest) {
	if(hitTest(x,y) && enabled) {
		onMouseDown(x,y);
		
		InputEvent *inputEvent = new InputEvent(Vector2(x,y), timestamp);		
		inputEvent->mouseButton = mouseButton;
		dispatchEvent(inputEvent, InputEvent::EVENT_MOUSEDOWN);
		
		if(timestamp - lastClickTicks < 400) {
			InputEvent *inputEvent = new InputEvent(Vector2(x,y), timestamp);
			inputEvent->mouseButton = mouseButton;			
			dispatchEvent(inputEvent, InputEvent::EVENT_DOUBLECLICK);
		}
		lastClickTicks = timestamp;		
		retVal = true;
	}
	if(enabled) {
		for(int i=children.size()-1;i>=0;i--) {
			
			((ScreenEntity*)children[i])->_onMouseDown(x-position.x,y-position.y, mouseButton, timestamp);
			if(((ScreenEntity*)children[i])->blockMouseInput && ((ScreenEntity*)children[i])->enabled) {
				if(((ScreenEntity*)children[i])->hitTest(x-position.x,y-position.y))
				   break;
			}
		}
	}
	}		
	
	return retVal;
}

void ScreenEntity::setRotation(Number rotation) {
	setRoll(rotation);
}

Vector2 ScreenEntity::getPosition2D() {
	return Vector2(position.x, position.y);
}

Matrix4 ScreenEntity::buildPositionMatrix() {
	Matrix4 posMatrix;
	switch(positionMode) {
		case POSITION_TOPLEFT:
//			renderer->translate2D(position.x+ceil(width/2.0f)*scale->x, position.y+ceil(height/2.0f)*scale->y);
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
	if(positionMode == POSITION_TOPLEFT)
		renderer->translate2D(-floor(width/2.0f), -floor(height/2.0f));	
}

/*
void ScreenEntity::transformAndRender() {

	Update();

	if(!renderer || !visible)
		return;

	renderer->pushMatrix();
	switch(positionMode) {
		case POSITION_TOPLEFT:
			renderer->translate2D(position.x+ceil(width/2.0f)*scale->x, position.y+ceil(height/2.0f)*scale->y);
		break;
		case POSITION_CENTER:
			renderer->translate2D(position.x, position.y);
		break;
	}
	renderer->scale2D(scale);
	renderer->rotate2D(rotation);
	if(parentEntity) {
		Color combined = getCombinedColor();
		renderer->setVertexColor(combined.r,combined.g,combined.b,combined.a);
	} else {
		renderer->setVertexColor(color.r,color.g,color.b,color.a);
	}
	
	renderer->setBlendingMode(blendingMode);
	Render();
	if(positionMode == POSITION_TOPLEFT)
		renderer->translate2D(-ceil(width/2.0f)*scale->x, -ceil(height/2.0f)*scale->y);
	renderChildren();
	renderer->popMatrix();
}
*/
