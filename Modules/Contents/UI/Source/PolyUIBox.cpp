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

using namespace Polycode;

UIBox::UIBox(String imageFile, Number t, Number r, Number b, Number l, Number boxWidth, Number boxHeight) : UIElement() {
	
	setAnchorPoint(-1.0, -1.0, 0.0);	
	
	setWidth(boxWidth);
	setHeight(boxHeight);
	
	tlImage = new SceneImage(imageFile);
	tlImage->setAnchorPoint(-1.0, -1.0, 0.0);
	tlImage->setImageCoordinates(0,0,l,t);
	addChild(tlImage);
	tlImage->setPosition(0, 0);
	
	trImage = new SceneImage(imageFile);
	trImage->setAnchorPoint(-1.0, -1.0, 0.0);
	trImage->setImageCoordinates(trImage->getWidth()-r,0,r,t);
	addChild(trImage);	
	trImage->setPosition(boxWidth-r, 0);

	blImage = new SceneImage(imageFile);
	blImage->setAnchorPoint(-1.0, -1.0, 0.0);	
	blImage->setImageCoordinates(0,blImage->getHeight()-b,l,b);
	addChild(blImage);	
	blImage->setPosition(0, boxHeight-b);

	brImage = new SceneImage(imageFile);
	brImage->setAnchorPoint(-1.0, -1.0, 0.0);
	brImage->setImageCoordinates(brImage->getWidth()-r,brImage->getHeight()-b,r,b);
	addChild(brImage);	
	brImage->setPosition(boxWidth-r, boxHeight-b);	
	
	centerImage = new SceneImage(imageFile);
	centerImage->setAnchorPoint(-1.0, -1.0, 0.0);
	centerImage->setImageCoordinates(l,t,centerImage->getWidth()-l-r, centerImage->getHeight()-t-b, boxWidth-l-r, boxHeight-t-b);
	addChild(centerImage);	
	centerImage->setPosition(l,t);	
	
	tImage = new SceneImage(imageFile);
	tImage->setAnchorPoint(-1.0, -1.0, 0.0);
	tImage->setImageCoordinates(l,0,tImage->getWidth()-l-r,t, boxWidth-l-r, t);
	addChild(tImage);
	tImage->setPosition(l,0);	

	bImage = new SceneImage(imageFile);
	bImage->setAnchorPoint(-1.0, -1.0, 0.0);	
	bImage->setImageCoordinates(l,bImage->getHeight()-b,bImage->getWidth()-l-r,b, boxWidth-l-r, b);
	addChild(bImage);
	bImage->setPosition(l,boxHeight-b);	

	lImage = new SceneImage(imageFile);
	lImage->setAnchorPoint(-1.0, -1.0, 0.0);		
	lImage->setImageCoordinates(0,t,l,lImage->getHeight()-t-b, l, boxHeight-t-b);
	addChild(lImage);
	lImage->setPosition(0,t);	

	rImage = new SceneImage(imageFile);
	rImage->setAnchorPoint(-1.0, -1.0, 0.0);		
	rImage->setImageCoordinates(rImage->getWidth()-r,t,r,rImage->getHeight()-t-b, r, boxHeight-t-b);
	addChild(rImage);
	rImage->setPosition(boxWidth-r,t);	
	
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
	
	centerImage->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, newWidth-l-r, newHeight-t-b);
		
	lImage->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, l, newHeight-t-b);	
	rImage->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, r, newHeight-t-b);		
	bImage->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, newWidth-l-r, b);
	tImage->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, newWidth-l-r, t);	
	
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
