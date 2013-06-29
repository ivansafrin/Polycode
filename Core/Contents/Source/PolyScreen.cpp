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

#include "PolyScreen.h"
#include "PolyCoreServices.h"
#include "PolyInputEvent.h"
#include "PolyScreenManager.h"
#include "PolyResourceManager.h"
#include "PolyCore.h"
#include "PolyMaterial.h"
#include "PolyRenderer.h"
#include "PolyScreenEntity.h"
#include "PolyScreenEvent.h"
#include "PolyShader.h"
#include "PolyTexture.h"

using namespace Polycode;

Screen::Screen() : EventDispatcher() {
	enabled = true;
	focusChild = NULL;
	originalSceneTexture = NULL;
	CoreServices::getInstance()->getScreenManager()->addScreen(this);
	filterShaderMaterial = NULL;
	_hasFilterShader = false;
	useNormalizedCoordinates = false;
	processTouchEventsAsMouse = false;
	ownsChildren = false;

	rootEntity.processInputEvents = true;
	rootEntity.setPositionMode(ScreenEntity::POSITION_CENTER);
	rootEntity.setRenderer(renderer);
	rootEntity.setDefaultScreenOptions(false);
}

Screen::~Screen() {
	CoreServices::getInstance()->getScreenManager()->removeScreen(this);

	for(int i=0; i < localShaderOptions.size(); i++) {
		delete localShaderOptions[i];
	}
	delete originalSceneTexture;
}

void Screen::setNormalizedCoordinates(bool newVal, Number yCoordinateSize) {
	useNormalizedCoordinates = newVal;
	this->yCoordinateSize = yCoordinateSize;
}

void Screen::handleInputEvent(InputEvent *inputEvent) {

	switch(inputEvent->getEventCode()) {
	
		case InputEvent::EVENT_TOUCHES_BEGAN:
			if(processTouchEventsAsMouse) {
				for(int j=0; j < inputEvent->touches.size(); j++) {
					rootEntity._onMouseDown(inputEvent->touches[j].position.x, inputEvent->touches[j].position.y, CoreInput::MOUSE_BUTTON1, inputEvent->timestamp);
				}
			}
		break;
		case InputEvent::EVENT_MOUSEDOWN:
			rootEntity._onMouseDown(inputEvent->mousePosition.x, inputEvent->mousePosition.y, inputEvent->mouseButton, inputEvent->timestamp);
		break;
		case InputEvent::EVENT_MOUSEMOVE:
			rootEntity._onMouseMove(inputEvent->mousePosition.x, inputEvent->mousePosition.y, inputEvent->timestamp);
		break;
		case InputEvent::EVENT_MOUSEUP:
			rootEntity._onMouseUp(inputEvent->mousePosition.x, inputEvent->mousePosition.y, inputEvent->mouseButton, inputEvent->timestamp);
		break;
		case InputEvent::EVENT_MOUSEWHEEL_UP:
			rootEntity._onMouseWheelUp(inputEvent->mousePosition.x, inputEvent->mousePosition.y, inputEvent->timestamp);
		break;
		case InputEvent::EVENT_MOUSEWHEEL_DOWN:
			rootEntity._onMouseWheelDown(inputEvent->mousePosition.x, inputEvent->mousePosition.y,inputEvent->timestamp);
		break;
		case InputEvent::EVENT_KEYDOWN:
			rootEntity._onKeyDown(inputEvent->key, inputEvent->charCode);
		break;
		case InputEvent::EVENT_KEYUP:
			rootEntity._onKeyUp(inputEvent->key, inputEvent->charCode);
		break;
	}
}

void Screen::setRenderer(Renderer *renderer) {
	this->renderer = renderer;
}

void Screen::setScreenShader(const String& shaderName) {
	filterShaderMaterial = (Material*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_MATERIAL, shaderName);
	if(!filterShaderMaterial || filterShaderMaterial->getNumShaders() == 0)
		return;

	if(!originalSceneTexture) {
		CoreServices::getInstance()->getRenderer()->createRenderTextures(&originalSceneTexture, NULL, CoreServices::getInstance()->getCore()->getXRes(), CoreServices::getInstance()->getCore()->getYRes(), filterShaderMaterial->fp16RenderTargets);
	}
	
	for(int i=0; i < filterShaderMaterial->getNumShaders(); i++) {
		ShaderBinding* binding = filterShaderMaterial->getShader(i)->createBinding();
		localShaderOptions.push_back(binding);
	}
	_hasFilterShader = true;

}

void Screen::clearScreenShader() {
	if(_hasFilterShader) {
		_hasFilterShader = false;
		filterShaderMaterial = NULL;
	}
}


void Screen::drawFilter() {

	if(!filterShaderMaterial)
		return;

	Renderer *renderer = CoreServices::getInstance()->getRenderer();

	renderer->bindFrameBufferTexture(originalSceneTexture);

	Render();
	renderer->unbindFramebuffers();

	ShaderBinding* materialBinding;
	for(int i=0; i < filterShaderMaterial->getNumShaders(); i++) {
		materialBinding = filterShaderMaterial->getShaderBinding(i);

		for(int j=0; j < materialBinding->getNumColorTargetBindings(); j++) {
			RenderTargetBinding *colorBinding = materialBinding->getColorTargetBinding(j);
			materialBinding->clearTexture(colorBinding->name);
			materialBinding->addTexture(colorBinding->name, originalSceneTexture);
		}

		renderer->applyMaterial(filterShaderMaterial, localShaderOptions[i], i);

		if(i==filterShaderMaterial->getNumShaders()-1) {
			renderer->loadIdentity();
			renderer->drawScreenQuad(renderer->getXRes(), renderer->getYRes());
		} else {
			for(int j=0; j < materialBinding->getNumOutTargetBindings(); j++) {
				renderer->bindFrameBufferTexture(materialBinding->getOutTargetBinding(j)->texture);

				renderer->drawScreenQuad(materialBinding->getOutTargetBinding(j)->width, materialBinding->getOutTargetBinding(j)->height);
				renderer->unbindFramebuffers();
			}
		}
		renderer->clearShader();
		renderer->loadIdentity();
		renderer->setOrthoMode();
	}

}

void Screen::setScreenOffset(Number x, Number y) {
	offset.x = x;
	offset.y = y;
}

bool Screen::hasFilterShader() const {
	return _hasFilterShader;
}

void Screen::addEntity(ScreenEntity *newEntity) {
	rootEntity.addChild(newEntity);
}

void Screen::addChild(ScreenEntity *newEntity) {
	addEntity(newEntity);
}

void Screen::removeChild(ScreenEntity *entityToRemove) {
	rootEntity.removeChild(entityToRemove);
}

void Screen::Shutdown() {

}

void Screen::Update() {
	rootEntity.doUpdates();
}

void Screen::Render() {
	renderer->loadIdentity();
	renderer->translate2D(offset.x, offset.y);
	rootEntity.updateEntityMatrix();
	rootEntity.transformAndRender();
}
