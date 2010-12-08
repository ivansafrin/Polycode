/*
 *  PolyScreenLabel.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyScreenLabel.h"

using namespace Polycode;

ScreenLabel::ScreenLabel(string fontName, wstring text, int size, int amode) : ScreenShape(ScreenShape::SHAPE_RECT,1,1) {
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

void ScreenLabel::addDropShadow(Color color, float size, float offsetX, float offsetY) {
	Image *labelImage = new Image(label);
	labelImage->fastBlur(size);
	dropShadowImage = new ScreenImage(labelImage);	
	addChild(dropShadowImage);
	dropShadowImage->setColor(color);
	dropShadowImage->setPositionMode(POSITION_TOPLEFT);
	dropShadowImage->setPosition(offsetX, offsetY);
	dropShadowImage->getMesh()->getPolygon(0)->flipUVY();
}

wstring ScreenLabel::getText() {
	return label->getText();
}	

void ScreenLabel::setText(wstring newText) {		
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
