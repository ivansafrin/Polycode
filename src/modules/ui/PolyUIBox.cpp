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

#include "PolyUIBox.h"
#include "PolyCoreServices.h"
#include "PolyConfig.h"
#include "PolyRenderer.h"

using namespace Polycode;

UIBox::UIBox(String imageFile, Number t, Number r, Number b, Number l, Number boxWidth, Number boxHeight) : UIElement() {

    Config *conf = CoreServices::getInstance()->getConfig();
    Number uiScale = conf->getNumericValue("Polycode", "uiScale");
    
	setAnchorPoint(-1.0, -1.0, 0.0);
	
	setWidth(boxWidth);
	setHeight(boxHeight);
	
	tlImage = new UIRect(imageFile);
	tlImage->setImageCoordinates(0,0,l,t, uiScale);
	addChild(tlImage);
	tlImage->setPosition(0, 0);
    tlImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	trImage = new UIRect(imageFile);
	trImage->setImageCoordinates((trImage->getWidth()/uiScale)-r,0,r,t, uiScale);
	addChild(trImage);	
	trImage->setPosition(boxWidth-r, 0);
    trImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	blImage = new UIRect(imageFile);
	blImage->setImageCoordinates(0,(blImage->getHeight()/uiScale)-b,l,b, uiScale);
	addChild(blImage);	
	blImage->setPosition(0, boxHeight-b);
    blImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	brImage = new UIRect(imageFile);
	brImage->setImageCoordinates((brImage->getWidth()/uiScale)-r,(brImage->getHeight()/uiScale)-b,r,b, uiScale);
	addChild(brImage);	
	brImage->setPosition(boxWidth-r, boxHeight-b);	
    brImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	centerImage = new UIRect(imageFile);
	centerImage->setImageCoordinates(l,t,(centerImage->getWidth()/uiScale)-l-r, (centerImage->getHeight()/uiScale)-t-b, uiScale);
	addChild(centerImage);	
	centerImage->setPosition(l,t);	
	centerImage->Resize(boxWidth-l-r, boxHeight-t-b);
    centerImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	tImage = new UIRect(imageFile);
	tImage->setImageCoordinates(l,0,(tImage->getWidth()/uiScale)-l-r,t, uiScale);
	addChild(tImage);
	tImage->setPosition(l,0);	
	tImage->Resize(boxWidth-l-r, t);
    tImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	bImage = new UIRect(imageFile);
	bImage->setImageCoordinates(l,(bImage->getHeight()/uiScale)-b,(bImage->getWidth()/uiScale)-l-r,b, uiScale);
	addChild(bImage);
	bImage->setPosition(l,boxHeight-b);	
	bImage->Resize(boxWidth-l-r, b);
    bImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	lImage = new UIRect(imageFile);
	lImage->setImageCoordinates(0,t,l,(lImage->getHeight()/uiScale)-t-b, uiScale);
	addChild(lImage);
	lImage->setPosition(0,t);	
	lImage->Resize(l, boxHeight-t-b);
    lImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    
	rImage = new UIRect(imageFile);
	rImage->setImageCoordinates((rImage->getWidth()/uiScale)-r,t,r,(rImage->getHeight()/uiScale)-t-b, uiScale);
	addChild(rImage);
	rImage->setPosition(boxWidth-r,t);	
	rImage->Resize(r, boxHeight-t-b);	
    rImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	
	this->t = t;
	this->r = r;
	this->b = b;
	this->l = l;

	ownsChildren = true;	
}

void UIBox::resizeBox(Number newWidth, Number newHeight) {

	brImage->setPosition(newWidth-brImage->getWidth(), newHeight-brImage->getHeight());
	trImage->setPosition(newWidth-trImage->getWidth(), 0);
	blImage->setPosition(0, newHeight-blImage->getHeight());

	centerImage->Resize(ceil(newWidth-l-r), ceil(newHeight-t-b));

	lImage->Resize(l, newHeight-t-b);	
	rImage->Resize(r, newHeight-t-b);		
	bImage->Resize(ceil(newWidth-l-r), b);
	tImage->Resize(ceil(newWidth-l-r), t);

	bImage->setPosition(bImage->getPosition().x, newHeight-bImage->getHeight());	
	rImage->setPosition(newWidth-rImage->getWidth(),rImage->getPosition().y);

	setWidth(newWidth);
	setHeight(newHeight);

	this->rebuildTransformMatrix();
}

UIBox::~UIBox() {
	if(!ownsChildren) {
		delete tlImage;
		delete trImage;		
		delete blImage;		
		delete brImage;					
		delete centerImage;		
		delete tImage;
		delete rImage;
		delete bImage;
		delete lImage;		
	}
}
