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

#include "PolyUIScrollContainer.h"
#include "PolyConfig.h"
#include "PolyInputEvent.h"
#include "PolyLabel.h"
#include "PolyCoreServices.h"
#include <math.h>

using namespace Polycode;

UIScrollContainer::UIScrollContainer(Entity *scrolledEntity, bool hScroll, bool vScroll, Number width, Number height) : UIElement() {
	
	scrolledEntity->setAnchorPoint(-1.0, -1.0, 0.0);
	
	scrolledEntity->rebuildTransformMatrix();
	Config *conf = CoreServices::getInstance()->getConfig();
	
	hasHScroll = hScroll;
	hasVScroll = vScroll;	
	
	
	setWidth(width);
	setHeight(height);
	
	Number uiScrollPanePadding = conf->getNumericValue("Polycode", "uiScrollPanePadding");			
	
	defaultScrollSize = conf->getNumericValue("Polycode", "uiScrollDefaultSize");			
		
	scrollChild = scrolledEntity;
	addChild(scrollChild);
	
	enableScissor = true;
	
	vScrollBar = new UIVScrollBar(defaultScrollSize, height, height / scrolledEntity->getHeight());
	addChild(vScrollBar);
	vScrollBar->setPosition(width+uiScrollPanePadding,0);	
	vScrollBar->addEventListener(this, Event::CHANGE_EVENT);
	vScrollBar->blockMouseInput = true;
	vScrollBar->processInputEvents = true;
	
	if(!vScroll)
		vScrollBar->enabled = false;
	
	hScrollBar = new UIHScrollBar(width, defaultScrollSize, width / scrolledEntity->getWidth());
	addChild(hScrollBar);
	hScrollBar->setPosition(0,height+uiScrollPanePadding);	
	hScrollBar->addEventListener(this, Event::CHANGE_EVENT);
	if(!hScroll)
		hScrollBar->enabled = false;
			
	setContentSize(scrollChild->getWidth()*scrollChild->getScale().x, scrollChild->getHeight()*scrollChild->getScale().y);
	Resize(width, height);	
	
	processInputEvents = true;
	
	addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);
	addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);	
}

void UIScrollContainer::Resize(Number width, Number height) {
	setWidth(width);
	setHeight(height);
	
	hScrollBar->Resize(width);	
	vScrollBar->Resize(height);

	setContentSize(contentWidth, contentHeight);
	vScrollBar->setPosition(width-vScrollBar->getWidth(), 0);
	hScrollBar->setPosition(0, height-hScrollBar->getHeight());
	
	matrixDirty = true;
	
}

void UIScrollContainer::_onMouseWheelUp() {
	if(vScrollBar->enabled)
		vScrollBar->scrollUpOneTick();
}

void UIScrollContainer::_onMouseWheelDown() {
	if(vScrollBar->enabled)
		vScrollBar->scrollDownOneTick();
}

Vector2 UIScrollContainer::getContentSize() {
	return Vector2(contentWidth, contentHeight);
}

Number UIScrollContainer::getVScrollWidth() {
	if(vScrollBar->enabled) {
		return vScrollBar->getWidth();
	} else {
		return 0;
	}
}

UIVScrollBar *UIScrollContainer::getVScrollBar() { return vScrollBar; }

UIHScrollBar *UIScrollContainer::getHScrollBar() { return hScrollBar; }

void UIScrollContainer::setContentSize(Number newContentWidth, Number newContentHeight) {
    
    if(newContentWidth < 1.0)
        newContentWidth = 1.0;
    if(newContentHeight < 1.0)
        newContentHeight = 1.0;


	contentHeight = newContentHeight;
	contentWidth = newContentWidth;
	
	vScrollBar->setHandleRatio(getHeight() / newContentHeight);	
	hScrollBar->setHandleRatio(getWidth() / newContentWidth);	
	
	if(hasVScroll) {
		if((getHeight() / newContentHeight) >= 1) {
			vScrollBar->enabled = false;
			vScrollBar->scrollTo(0);
            scrollChild->setPositionY(0.0);
		} else {
			vScrollBar->enabled = true;		
		}
	}
	
	if(hasHScroll) {
		if((getWidth() / newContentWidth) >= 1) {
			hScrollBar->enabled = false;
			hScrollBar->scrollTo(0);
            scrollChild->setPositionX(0.0);
		} else {
			hScrollBar->enabled = true;		
		}
	}	
}

void UIScrollContainer::setScrollValue(Number xScroll, Number yScroll) {
	if(xScroll < 0)
		xScroll = 0;
	if(xScroll > 1)
		xScroll = 1;
		
	if(yScroll < 0)
		yScroll = 0;
	if(yScroll > 1)
		yScroll = 1;

		
	hScrollBar->scrollTo(xScroll);
	vScrollBar->scrollTo(yScroll);
    
    vScrollBar->dispatchEvent(new Event(), Event::CHANGE_EVENT);
    hScrollBar->dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void UIScrollContainer::scrollVertical(Number amount) {
	vScrollBar->Scroll(amount);		
}

void UIScrollContainer::scrollHorizontal(Number amount) {
	hScrollBar->Scroll(amount);
}


void UIScrollContainer::Update() {
	Vector2 pos = getScreenPositionForMainCamera();
	scissorBox.setRect(pos.x, pos.y, getWidth(), getHeight());
}

void UIScrollContainer::handleEvent(Event *event) {

	if(event->getDispatcher() == this) {
		if(event->getEventCode() == InputEvent::EVENT_MOUSEWHEEL_UP) {
			_onMouseWheelUp();
		} else if(event->getEventCode() == InputEvent::EVENT_MOUSEWHEEL_DOWN) {
			_onMouseWheelDown();		
		}
	}
	
	if(event->getDispatcher() == vScrollBar) {
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			scrollChild->setPositionY(floor(((-contentHeight+getHeight()) )*vScrollBar->getScrollValue()));
            if(scrollChild->getPosition().y > 0) {
				scrollChild->setPositionY(0);
            }
            dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
	
	if(event->getDispatcher() == hScrollBar) {
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			scrollChild->setPositionX(floor(((-contentWidth+getWidth()) )*hScrollBar->getScrollValue()));
            if(scrollChild->getPosition().x > 0) {
				scrollChild->setPositionX(0);
            }
            dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
	
}

UIScrollContainer::~UIScrollContainer() {
	if(!ownsChildren) {
		delete vScrollBar;
		delete hScrollBar;
	}
}
