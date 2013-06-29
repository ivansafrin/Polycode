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

#include "PolyScreenManager.h"
#include "PolyCoreServices.h"
#include "PolyRenderer.h"
#include "PolyScreen.h"

using namespace Polycode;

ScreenManager::ScreenManager() : EventDispatcher() {

}

ScreenManager::~ScreenManager() {

}

void ScreenManager::removeScreen(Screen *screen) {
	for(int i=0;i<screens.size();i++) {
		if(screens[i] == screen) {
			screens.erase(screens.begin()+i);
		}
	}
}

void ScreenManager::addScreen(Screen *screen) {
	screen->setRenderer(CoreServices::getInstance()->getRenderer());
	screens.push_back(screen);
}

void ScreenManager::handleEvent(Event *event) {
//	if(event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput()) {
		InputEvent *inputEvent = (InputEvent*)event;
		for(int i=0;i<screens.size();i++) {
			screens[i]->handleInputEvent(inputEvent);
		}
//	}
}

void ScreenManager::Render() {
	Renderer *renderer = CoreServices::getInstance()->getRenderer();
	for(int i=0;i<screens.size();i++) {
		if(screens[i]->enabled) {
			if(!screens[i]->usesNormalizedCoordinates()) {
				renderer->setOrthoMode(renderer->getXRes(), renderer->getYRes(), false);
			} else {
				Number yCoordinateSize = screens[i]->getYCoordinateSize();
				Number ratio = ((Number)renderer->getXRes())/((Number)renderer->getYRes());
				renderer->setOrthoMode(ratio*yCoordinateSize, yCoordinateSize, true);
			}

			if(screens[i]->hasFilterShader()) {
				screens[i]->drawFilter();
			} else {
				screens[i]->Render();
			}
		}
	}
}

void ScreenManager::Update() {
	for(int i=0;i<screens.size();i++) {
		if(screens[i]->enabled) {
			screens[i]->Update();
		}
	}
}
