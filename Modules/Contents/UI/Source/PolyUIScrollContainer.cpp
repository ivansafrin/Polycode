/*
 *  PolyUIScrollContainer.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/25/10.
 *  Copyright 2010 Ivan Safrin. All rights reserved.
 *
 */

#include "PolyUIScrollContainer.h"

using namespace Polycode;

UIScrollContainer::UIScrollContainer(ScreenEntity *scrolledEntity, bool hScroll, bool vScroll, float width, float height) : ScreenEntity() {
	
	scrolledEntity->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	
	scrolledEntity->rebuildTransformMatrix();
	Config *conf = CoreServices::getInstance()->getConfig();
	
	hasHScroll = hScroll;
	hasVScroll = vScroll;	
	
	
	this->width = width;
	this->height = height;
	this->hitwidth = width;
	this->hitheight = height;
	
	float uiScrollPanePadding = conf->getNumericValue("Polycode", "uiScrollPanePadding");			
	
	defaultScrollSize = conf->getNumericValue("Polycode", "uiScrollDefaultSize");			
	
	maskShape = new ScreenShape(ScreenShape::SHAPE_RECT, width, height);
	maskShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(maskShape);
	maskShape->setColor(1.0f,0,0,0.8f);
	
	scrollChild = scrolledEntity;
	addChild(scrollChild);
	
	scrollChild->setMask(maskShape);
	
	
	vScrollBar = new UIVScrollBar(defaultScrollSize, height, height / scrolledEntity->getHeight());
	addChild(vScrollBar);
	vScrollBar->setPosition(width+uiScrollPanePadding,0);	
	vScrollBar->addEventListener(this, Event::CHANGE_EVENT);
	
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
}

void UIScrollContainer::Resize(int x, int y) {
	width = x;
	height = y;
	hitwidth = width;
	hitheight = height;
	
	maskShape->setShapeSize(x, y);
	vScrollBar->Resize(y);
	setContentSize(contentWidth, contentHeight);
	vScrollBar->setPositionY(0);
}

void UIScrollContainer::onMouseWheelUp(float x, float y) {
	if(vScrollBar->enabled)
		vScrollBar->scrollUpOneTick();
}

void UIScrollContainer::onMouseWheelDown(float x, float y) {
	if(vScrollBar->enabled)
		vScrollBar->scrollDownOneTick();
}


void UIScrollContainer::setContentSize(float newContentWidth, float newContentHeight) {
	
	contentHeight = newContentHeight;
	contentWidth = newContentWidth;
	
	vScrollBar->setHandleRatio(height / newContentHeight);	
	hScrollBar->setHandleRatio(width / newContentWidth);	
	
	if(hasVScroll) {
		if((height / newContentHeight) >= 1) {
			vScrollBar->enabled = false;
		} else {
			vScrollBar->enabled = true;		
		}
	}
	
	if(hasHScroll) {
		if((width / newContentWidth) >= 1) {
			hScrollBar->enabled = false;
		} else {
			hScrollBar->enabled = true;		
		}
	}	
}

void UIScrollContainer::handleEvent(Event *event) {
	if(event->getDispatcher() == vScrollBar) {
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			scrollChild->setPositionY(round(-((contentHeight-height) )*vScrollBar->getScrollValue()));
		}
	}
	
	if(event->getDispatcher() == hScrollBar) {
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			scrollChild->setPositionX(round(-((contentWidth-width) )*hScrollBar->getScrollValue()));
		}
	}
	
}

UIScrollContainer::~UIScrollContainer() {
	
}
