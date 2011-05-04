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

#include "PolyScreenLabel.h"

using namespace Polycode;

ScreenLabel::ScreenLabel(String fontName, String text, int size, int amode) : ScreenShape(ScreenShape::SHAPE_RECT,1,1) {
	label = new Label(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), text, size, amode);
	texture = NULL;
	setText(text);		
	mesh->getPolygon(0)->flipUVY();	
	positionMode = POSITION_TOPLEFT;	
	dropShadowImage = NULL;
	colorAffectsChildren = false;
}

ScreenLabel::~ScreenLabel() {
}

Label *ScreenLabel::getLabel() {
	return label;
}

void ScreenLabel::addDropShadow(Color color, Number size, Number offsetX, Number offsetY) {
	Image *labelImage = new Image(label);
	labelImage->fastBlur(size);
	dropShadowImage = new ScreenImage(labelImage);	
	addChild(dropShadowImage);
	dropShadowImage->setColor(color);
	dropShadowImage->setPositionMode(POSITION_TOPLEFT);
	dropShadowImage->setPosition(offsetX, offsetY);
	dropShadowImage->getMesh()->getPolygon(0)->flipUVY();
}

String ScreenLabel::getText() {
	return label->getText();
}	

void ScreenLabel::setText(String newText) {		
	label->setText(newText);
	
	if(texture) {
		CoreServices::getInstance()->getMaterialManager()->deleteTexture(texture);
	}
	
	texture = NULL;
	if(!label->getFont())
		return;
	if(!label->getFont()->isValid())
		return;				
	
	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromImage(label);
	width = label->getWidth();
	height = label->getHeight();
	setShapeSize(width, height);
}
