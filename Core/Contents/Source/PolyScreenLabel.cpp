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
#include "PolyCoreServices.h"
#include "PolyFontManager.h"
#include "PolyFont.h"
#include "PolyLabel.h"
#include "PolyMaterialManager.h"
#include "PolyMesh.h"
#include "PolyPolygon.h"
#include "PolyScreenImage.h"

using namespace Polycode;

ScreenLabel::ScreenLabel(const String& text, int size, const String& fontName, int amode, bool premultiplyAlpha) : ScreenShape(ScreenShape::SHAPE_RECT,1,1) {
	label = new Label(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), text, size, amode, premultiplyAlpha);
	dropShadowImage = NULL;
	texture = NULL;
	setText(text);		
	mesh->getPolygon(0)->flipUVY();	
	positionMode = POSITION_TOPLEFT;	
	dropShadowImage = NULL;
	colorAffectsChildren = false;
}

ScreenLabel::~ScreenLabel() {
	delete label;
	delete dropShadowImage;
}

Label *ScreenLabel::getLabel() const {
	return label;
}

void ScreenLabel::addDropShadow(Color color, Number size, Number offsetX, Number offsetY) {
	delete dropShadowImage;
	Image *labelImage = new Image(label);
	labelImage->fastBlur(size);
	dropShadowImage = new ScreenImage(labelImage);	
	delete labelImage;
	addChild(dropShadowImage);
	dropShadowImage->setColor(color);
	dropShadowImage->setPositionMode(POSITION_TOPLEFT);
	dropShadowImage->setPosition(offsetX, offsetY);
	dropShadowImage->getMesh()->getPolygon(0)->flipUVY();
}

const String& ScreenLabel::getText() const {
	return label->getText();
}	

void ScreenLabel::setText(const String& newText) {
	label->setText(newText);
	
	if(texture) {
		CoreServices::getInstance()->getMaterialManager()->deleteTexture(texture);
	}
	
	texture = NULL;
	if(!label->getFont())
		return;
	if(!label->getFont()->isValid())
		return;				
	
	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromImage(label, true, false);
	width = label->getWidth();
	height = label->getHeight();
	setShapeSize(width, height);
}
