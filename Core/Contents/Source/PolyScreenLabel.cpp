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
#include "PolyRenderer.h"

using namespace Polycode;

ScreenLabel::ScreenLabel(const String& text, int size, const String& fontName, int amode, bool premultiplyAlpha) : ScreenShape(ScreenShape::SHAPE_RECT,1,1) {
	label = new Label(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), text, size, amode, premultiplyAlpha);
	texture = NULL;
	updateTexture();
	positionMode = POSITION_TOPLEFT;
	colorAffectsChildren = false;
	positionAtBaseline = true;
}

ScreenLabel::~ScreenLabel() {
	delete label;
}

Label *ScreenLabel::getLabel() const {
	return label;
}

Entity *ScreenLabel::Clone(bool deepClone, bool ignoreEditorOnly) {
	ScreenLabel *newLabel = new ScreenLabel(getText(), label->getSize(), label->getFont()->getFontName(), label->getAntialiasMode());
	applyClone(newLabel, deepClone, ignoreEditorOnly);
	return newLabel;
}

void ScreenLabel::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) {
	ScreenShape::applyClone(clone, deepClone, ignoreEditorOnly);
	ScreenLabel *_clone = (ScreenLabel*) clone;
	_clone->positionAtBaseline = positionAtBaseline;
}

const String& ScreenLabel::getText() const {
	return label->getText();
}

void ScreenLabel::updateTexture() {

	if(texture) {
		CoreServices::getInstance()->getMaterialManager()->deleteTexture(texture);
	}

	texture = NULL;
	if(!label->getFont() || !label->getFont()->isValid())
		return;

	texture = CoreServices::getInstance()->getMaterialManager()->createTextureFromImage(label, true, false);
	setWidth(label->getWidth());
	setHeight(label->getHeight());
	setShapeSize(width, height);

}

void ScreenLabel::Render() {
	if(positionAtBaseline) {
		CoreServices::getInstance()->getRenderer()->translate2D(0.0, -label->getBaselineAdjust() + label->getSize());
	}
	ScreenShape::Render();
}

void ScreenLabel::setText(const String& newText) {
	if(newText != label->getText() || label->optionsChanged()) {
		label->setText(newText);
		updateTexture();
	}
}
