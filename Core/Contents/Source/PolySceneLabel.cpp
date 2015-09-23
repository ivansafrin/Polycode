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

#include "PolySceneLabel.h"
#include "PolyCoreServices.h"
#include "PolyFontManager.h"
#include "PolyLabel.h"
#include "PolyMesh.h"
#include "PolyRenderer.h"
#include "PolyMaterialManager.h"

using namespace Polycode;

Vector3 SceneLabel::defaultAnchor = Vector3();
bool SceneLabel::defaultPositionAtBaseline = false;
bool SceneLabel::defaultSnapToPixels = false;
bool SceneLabel::createMipmapsForLabels = true;

SceneLabel::SceneLabel(const String& text, int size, const String& fontName, int amode, Number actualHeight, bool premultiplyAlpha, const Color &backgroundColor, const Color &foregroundColor) : ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1, 1){

	label = new Label(CoreServices::getInstance()->getFontManager()->getFontByName(fontName), text, size * CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX(), amode, premultiplyAlpha, backgroundColor, foregroundColor);
    
	positionAtBaseline = SceneLabel::defaultPositionAtBaseline;
	setAnchorPoint(SceneLabel::defaultAnchor);	
	snapToPixels = SceneLabel::defaultSnapToPixels;	
	setLabelActualHeight(actualHeight);
}

Entity *SceneLabel::Clone(bool deepClone, bool ignoreEditorOnly) const {
	SceneLabel *newLabel = new SceneLabel(label->getText(), label->getSize(), label->getFont()->getFontName(), label->getAntialiasMode(), actualHeight, label->getPremultiplyAlpha(), label->getBackgroundColor(), label->getForegroundColor());
    applyClone(newLabel, deepClone, ignoreEditorOnly);
    return newLabel;
}

void SceneLabel::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    
    SceneLabel* cloneLabel = (SceneLabel*) clone;
    

    cloneLabel->getLabel()->setSize(label->getSize());
    cloneLabel->getLabel()->setAntialiasMode(label->getAntialiasMode());
    cloneLabel->getLabel()->setFont(label->getFont());
    cloneLabel->getLabel()->setPremultiplyAlpha(label->getPremultiplyAlpha());
    cloneLabel->setLabelActualHeight(actualHeight);
    cloneLabel->getLabel()->setBackgroundColor(label->getBackgroundColor());
    cloneLabel->getLabel()->setForegroundColor(label->getForegroundColor());
    cloneLabel->positionAtBaseline = positionAtBaseline;
    cloneLabel->setText(label->getText());
    
    ScenePrimitive::applyClone(clone, deepClone, ignoreEditorOnly);
}


SceneLabel::~SceneLabel() {
    delete label;
}

Label *SceneLabel::getLabel() {
	return label;
}

String SceneLabel::getText() {
	return label->getText();
}

void SceneLabel::setLabelActualHeight(Number actualHeight) {
    this->actualHeight = actualHeight;
    
    if(actualHeight > 0.0) {
        labelScale = actualHeight/((Number)label->getSize()) * CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX();
    } else {
        labelScale = 1.0;
    }
    updateFromLabel();
}

Number SceneLabel::getLabelActualHeight() {
    return actualHeight;
}

void SceneLabel::updateFromLabel() {

	MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();

    Services()->getRenderer()->destroyTexture(texture);
    
	if(SceneLabel::createMipmapsForLabels) {
		texture = materialManager->createTextureFromImage(label, materialManager->clampDefault, materialManager->mipmapsDefault);	
	} else {
		texture = materialManager->createTextureFromImage(label, materialManager->clampDefault, false);		
	}

	if(material) {
		localShaderOptions->clearTexture("diffuse");
		localShaderOptions->addTexture("diffuse", texture);	
	}


	setPrimitiveOptions(type, label->getWidth()*labelScale/CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX(),label->getHeight()*labelScale/CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
	
    setLocalBoundingBox(label->getWidth()*labelScale / CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX(), label->getHeight()*labelScale/ CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX(), 0.001);
    
	if(useVertexBuffer)
		CoreServices::getInstance()->getRenderer()->createVertexBufferForMesh(mesh);
	
}

void SceneLabel::Render() {
	if(positionAtBaseline) {
		CoreServices::getInstance()->getRenderer()->translate2D(0.0, (((Number)label->getSize()*labelScale) * -1.0 / CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleY()) + (((Number)label->getBaselineAdjust())*labelScale/CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleY()));
	}
	ScenePrimitive::Render();
}

int SceneLabel::getTextWidthForString(String text) {
    return label->getTextWidthForString(text) / CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX();
}

void SceneLabel::setText(const String& newText) {
	
	if(newText == label->getText() && !label->optionsChanged()) {
		return;
	}		
	label->setText(newText);	
	updateFromLabel();
}
