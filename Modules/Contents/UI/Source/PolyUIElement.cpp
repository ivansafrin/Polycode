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

#include "PolyUIElement.h"
#include "PolyRenderer.h"
#include "PolyCoreServices.h"
#include "PolyTexture.h"
#include "PolyConfig.h"
#include "PolyCoreInput.h"
#include "PolyInputEvent.h"

using namespace Polycode;

UIElement *UIElement::globalFocusedChild = NULL;

UIMultilineLabel::UIMultilineLabel(const String& text, int size, int spacing, const String& fontName, int amode) : UIElement() {
    labelSize = size;
    labelFontName = fontName;
    labelAAMode = amode;
    this->spacing = spacing;
    setText(text);
}

void UIMultilineLabel::setText(const String& text) {
    clearLabels();
    
    std::vector<String> lines = text.split("\n");
	linesCount = lines.size();

	Number lineSize = spacing;
    Number yPos = 0.0;
    for(int i=0; i < lines.size(); i++) {
        if(lines[i] == "") {
            yPos += lineSize + spacing;
        } else {
            UILabel *label = new UILabel(lines[i], labelSize, labelFontName, labelAAMode);
            lineSize = label->getHeight();
            label->setPositionY(yPos);
            yPos += label->getHeight() + spacing;
            addChild(label);
			labels.push_back(label);
        }
    }
}

String UIMultilineLabel::getText() {
    String text;
    for(int i=0; i < labels.size(); i++) {
        if(i != 0) {
            text += "\n";
        }
        text += labels[i]->getText();
    }
    return text;
}

void UIMultilineLabel::setColor(Color color) {
	for (int i = 0; i < labels.size(); i++) {
		labels[i]->color.setColor(&color);
	}
}

void UIMultilineLabel::setColorInt(int r, int g, int b, int a) {
	for (int i = 0; i < labels.size(); i++) {
		labels[i]->color.setColorRGBA(r, g, b, a);
	}
}

void UIMultilineLabel::setColor(Number r, Number g, Number b, Number a) {
	for (int i = 0; i < labels.size(); i++) {
		labels[i]->color.setColor(r, g, b, a);
	}
}

void UIMultilineLabel::clearLabels() {
    for(int i=0; i < labels.size(); i++) {
        removeChild(labels[i]);
        delete labels[i];
    }
    labels.clear();
}

Number UIMultilineLabel::getWidth(){
	Number maxWidth = 0;
	for (int i = 0; i < labels.size(); i++) {
		if (labels[i]->getWidth() > maxWidth){
			maxWidth = labels[i]->getWidth();
		}
	}
	return maxWidth;
}

Number UIMultilineLabel::getHeight(){
	Number retHeight = 0;
	for (int i = 0; i < labels.size(); i++) {
		retHeight += labels[i]->getHeight() + spacing;
	}
	retHeight += (linesCount - labels.size()) * (labelSize + spacing);
	return retHeight;
}

UIMultilineLabel::~UIMultilineLabel() {
    if(!ownsChildren) {
        clearLabels();
    }
}

UILabel::UILabel(const String& text, int size, const String& fontName, int amode) : UIElement() {

	Config *conf = CoreServices::getInstance()->getConfig();	
	label = new SceneLabel(text, size, fontName, amode);
    label->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    label->positionAtBaseline = true;
    label->setAnchorPoint(-1.0, -1.0, 0.0);
	label->snapToPixels = true;
	
	color.setColorHexFromString(conf->getStringValue("Polycode", "uiDefaultFontColor"));
	addChild(label);
	setLocalBoundingBox(label->getLocalBoundingBox());
}

void UILabel::setText(const String& text) {
	label->setText(text);
    setLocalBoundingBox(label->getLocalBoundingBox());
}

String UILabel::getText() {
	return label->getText();
}

UILabel::~UILabel() {
    if(!ownsChildren) {
        delete label;
    }
}

Label *UILabel::getLabel() {
	return label->getLabel();
}

UIRect::UIRect(String fileName, Number width, Number height) : UIElement() {
	texture = NULL;
	loadTexture(fileName);
    initRect(width, height);
    imageWidth = width;
    imageHeight = height;
}

UIRect::UIRect(String fileName) : UIElement() {
	texture = NULL;
	loadTexture(fileName);
	if(texture) {	
		initRect(texture->getWidth(), texture->getHeight());
		imageWidth = texture->getWidth();
		imageHeight = texture->getHeight();	
	} else {
		initRect(1,  1);
		imageWidth = 0;
		imageHeight = 0;
	}
    setWidth(imageWidth);
    setHeight(imageHeight);
}

UIRect::UIRect(Number width, Number height) : UIElement() {
	texture = NULL;
	initRect(width, height);
	imageWidth = 0;
	imageHeight = 0;
}

void UIRect::setImageCoordinates(Number x, Number y, Number width, Number height, Number imageScale) {

	Number pixelSizeX = 1/imageWidth;
	Number pixelSizeY = 1/imageHeight;

	setWidth(width);
	setHeight(height);

	Number whalf = width/2.0f;
	Number hhalf = height/2.0f;
		
	Number xFloat = x * pixelSizeX * imageScale;
	Number yFloat = (y * pixelSizeY) * imageScale;
	Number wFloat = width * pixelSizeX * imageScale;
	Number hFloat = height * pixelSizeY * imageScale;

    rectMesh->vertexPositionArray.data.clear();
    rectMesh->vertexTexCoordArray.data.clear();
    
	rectMesh->addVertex(-whalf,-hhalf,0);
	rectMesh->addTexCoord(xFloat, (1.0-yFloat) - hFloat);

	rectMesh->addVertex(-whalf+width,-hhalf,0);
	rectMesh->addTexCoord(xFloat + wFloat, (1.0-yFloat) - hFloat);

	rectMesh->addVertex(-whalf+width,-hhalf+height,0);
	rectMesh->addTexCoord(xFloat + wFloat, 1.0-yFloat);

	rectMesh->addVertex(-whalf,-hhalf+height,0);
	rectMesh->addTexCoord(xFloat, 1.0-yFloat);

	rebuildTransformMatrix();
	matrixDirty = true;
}

Number UIRect::getImageWidth() const {
	return imageWidth;
}

Number UIRect::getImageHeight() const {
	return imageHeight;	
}

void UIRect::initRect(Number width, Number height) {
	rectMesh = new Mesh(Mesh::QUAD_MESH);
	processInputEvents = true;

	setAnchorPoint(-1.0, -1.0, 0.0);
	setWidth(width);	
	setHeight(height);
	
	Number whalf = width/2.0f;
	Number hhalf = height/2.0f;
				
	rectMesh->addVertexWithUV(-whalf,-hhalf,0,0,0);
	rectMesh->addVertexWithUV(-whalf+width,-hhalf,0, 1, 0);
	rectMesh->addVertexWithUV(-whalf+width,-hhalf+height,0, 1, 1);
	rectMesh->addVertexWithUV(-whalf,-hhalf+height,0,0,1);
}

UIRect::~UIRect() {
	delete rectMesh;
}

void UIRect::loadTexture(String fileName) {
	MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
	texture = materialManager->createTextureFromFile(fileName, materialManager->clampDefault, false);
}

void UIRect::setTexture(Texture *texture) {
	this->texture = texture;
}	

Texture *UIRect::getTexture() {
	return texture;
}

void UIRect::Render() {
	renderer->clearShader();
	renderer->setTexture(texture);
    
    renderer->pushRenderDataArray(&rectMesh->vertexPositionArray);
    renderer->pushRenderDataArray(&rectMesh->vertexTexCoordArray);

	renderer->drawArrays(Mesh::QUAD_MESH, NULL);
}

void UIRect::Resize(Number width, Number height) {

	setWidth(width);	
	setHeight(height);

	Number whalf = width/2.0f;
	Number hhalf = height/2.0f;

    rectMesh->vertexPositionArray.data.clear();

    rectMesh->addVertex(-whalf,-hhalf,0);
    rectMesh->addVertex(-whalf+width,-hhalf,0);
    rectMesh->addVertex(-whalf+width,-hhalf+height,0);
    rectMesh->addVertex(-whalf,-hhalf+height,0);
}

UIImage::UIImage(String imagePath, int width, int height) : UIRect(imagePath, width, height) {
    setBlendingMode(Renderer::BLEND_MODE_NORMAL);
}

UIImage::UIImage(String imagePath) : UIRect(imagePath) {
    setBlendingMode(Renderer::BLEND_MODE_NORMAL);
}

UIElement::UIElement() : Entity() {
	snapToPixels = true;
	setAnchorPoint(-1.0, -1.0, 0.0);
	processInputEvents = true;
	depthTest = false;	
	hasFocus = false;
	focusable = false;
	focusParent = NULL;
	hasDragLimits = false;
	dragged = false;
	depthTest = false;
	depthWrite = false;
    Services()->getInput()->addEventListenerUnique(this, InputEvent::EVENT_KEYDOWN);
}

UIElement::UIElement(Number width, Number height) : Entity() {
	setAnchorPoint(-1.0, -1.0, 0.0);
	processInputEvents = true;
	focusParent = NULL;
	hasFocus = false;
	hasDragLimits = false;
	focusable = false;
	dragged = false;	
	depthTest = false;
	depthWrite = false;		
	setWidth(width);
	setHeight(height);
    Services()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

void UIElement::handleEvent(Event *event) {
    if(event->getDispatcher() == Services()->getInput() && event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
        if(hasFocus && focusParent) {
            InputEvent *inputEvent = (InputEvent*) event;
            if(inputEvent->key == KEY_TAB) {
                if(Services()->getInput()->getKeyState(KEY_RSHIFT) || Services()->getInput()->getKeyState(KEY_LSHIFT)) {
                    focusParent->focusPreviousChild();
                } else {
                    focusParent->focusNextChild();
                }
                inputEvent->cancelEvent();
            }
        }
    }
}

void UIElement::setDragLimits(Rectangle rect) {
	dragLimits.x = rect.x;
	dragLimits.y = rect.y;
	dragLimits.w = rect.w;
	dragLimits.h = rect.h;
	hasDragLimits = true;
}

void UIElement::clearDragLimits() {
	hasDragLimits = false;
}

bool UIElement::isDragged() {
	return dragged;
}

void UIElement::startDrag(Number xOffset, Number yOffset) {
	dragged = true;
	dragOffsetX = xOffset;
	dragOffsetY = yOffset;
}

void UIElement::stopDrag() {
	dragged = false;
}

bool UIElement::isFocusable() {
	return focusable;
}

MouseEventResult UIElement::onMouseMove(const Ray &ray, int timestamp) {
	if(dragged) {	
		Vector3 localCoordinate = Vector3(ray.origin.x, ray.origin.y,0);

		if(parentEntity) {
			Matrix4 inverse = parentEntity->getConcatenatedMatrix().Inverse();
			localCoordinate = inverse * localCoordinate;		
		}
		setPosition(localCoordinate.x-dragOffsetX,-localCoordinate.y-dragOffsetY);
		if(hasDragLimits) {
			if(position.x < dragLimits.x)
				position.x = dragLimits.x;
			if(position.x > dragLimits.x + dragLimits.w)
				position.x = dragLimits.x + dragLimits.w;
			if(position.y < dragLimits.y)
				position.y = dragLimits.y;
			if(position.y > dragLimits.y + dragLimits.h)
				position.y = dragLimits.y + dragLimits.h;
		}		
		
	}
	return Entity::onMouseMove(ray, timestamp);
}

UIElement::~UIElement() {
    
    Services()->getInput()->removeAllHandlersForListener(this);

    if(focusParent) {
        focusParent->unregisterFocusChild(this);
    }
    
	if(UIElement::globalFocusedChild == this) {
		UIElement::globalFocusedChild = NULL;
	}
}

void UIElement::focusPreviousChild() {
    
    int j = 0;
    bool hasFocusedChild = false;
    if(UIElement::globalFocusedChild) {
        for(int i=0; i < focusChildren.size(); i++) {
            if(focusChildren[i] == UIElement::globalFocusedChild) {
                j = i;
                hasFocusedChild = true;
            }
        }
    }
    
    if(!hasFocusedChild) {
        return;
    }
    
    for(int i=0; i < focusChildren.size(); i++) {
        if(focusChildren[j]->isFocusable() && focusChildren[j] != UIElement::globalFocusedChild && focusChildren[j]->enabled && focusChildren[j]->visible) {
            focusChild(focusChildren[j]);
            return;
        }
        
        j--;
        if(j == -1) {
            j = focusChildren.size()-1;
        }
    }
}


void UIElement::focusNextChild() {

	int j = 0;
	bool hasFocusedChild = false;
	if(UIElement::globalFocusedChild) {
		for(int i=0; i < focusChildren.size(); i++) {
			if(focusChildren[i] == UIElement::globalFocusedChild) {
				j = i;
				hasFocusedChild = true;
			}
		}
	}

    if(!hasFocusedChild) {
		return;
    }

	for(int i=0; i < focusChildren.size(); i++) {
		if(focusChildren[j]->isFocusable() && focusChildren[j] != UIElement::globalFocusedChild && focusChildren[j]->enabled && focusChildren[j]->visible) {
			focusChild(focusChildren[j]);
			return;
		}

		j++;
        if(j == focusChildren.size()) {
			j = 0;
        }
	}
}

void UIElement::focusSelf() {
	if(UIElement::globalFocusedChild) {
		UIElement::globalFocusedChild->onLoseFocus();
		UIElement::globalFocusedChild->hasFocus = false;
	}

	UIElement::globalFocusedChild = this;
	
	onGainFocus();
	hasFocus = true;
}

void UIElement::focusChild(UIElement *child) {

	if(UIElement::globalFocusedChild) {
		UIElement::globalFocusedChild->onLoseFocus();
		UIElement::globalFocusedChild->hasFocus = false;
	}

	UIElement::globalFocusedChild = child;
	
	if(child) {
		UIElement::globalFocusedChild->onGainFocus();
		UIElement::globalFocusedChild->hasFocus = true;
	}	
}

void UIElement::registerFocusChild(UIElement *element) {
    if(element->isFocusable()) {
        element->setFocusParent(this);
        focusChildren.push_back(element);
    }
}

void UIElement::unregisterFocusChild(UIElement *element) {
    for(int i=0; i < focusChildren.size(); i++) {
        if(focusChildren[i] == element) {
            focusChildren.erase(focusChildren.begin()+i);
            return;
        }
    }
}

void UIElement::addFocusChild(UIElement *element) {
    registerFocusChild(element);
    addChild(element);
}

void UIElement::setFocusParent(UIElement *element) {
	focusParent = element;	
}

void UIElement::Resize(Number width, Number height) {
	setWidth(width);
	setHeight(height);
	dirtyMatrix(true);	
}
