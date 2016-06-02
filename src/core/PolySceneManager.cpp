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

#include "polycode/core/PolySceneManager.h"
#include "polycode/core/PolyCamera.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyScene.h"
#include "polycode/core/PolySceneRenderTexture.h"
#include "polycode/core/PolyTexture.h"

using namespace Polycode;

SceneManager::SceneManager() {
}

SceneManager::~SceneManager() {
	for(int i=0; i < scenes.size(); i++) {	
		delete scenes[i];
	}
	scenes.clear(); 
}

void SceneManager::removeScene(Scene *scene) {
	for(int i=0;i<scenes.size();i++) {
		if(scenes[i] == scene) {
			scenes.erase(scenes.begin()+i);
			return;
		}
	}
}

void SceneManager::registerRenderTexture(SceneRenderTexture *renderTexture) {
	renderTextures.push_back(renderTexture);
}
	
void SceneManager::unregisterRenderTexture(SceneRenderTexture *renderTexture) {
	for(int i=0;i<renderTextures.size();i++) {
		if(renderTextures[i] == renderTexture) {
			renderTextures.erase(renderTextures.begin()+i);
		}
	}	
}
		
void SceneManager::addScene(Scene *newScene) {
	scenes.push_back(newScene);
}

void SceneManager::updateRenderTextures(Scene *scene) {
}

void SceneManager::setRenderer(Renderer *renderer) {
	this->renderer = renderer;
}

void SceneManager::renderVirtual() {
	for(int i=0;i<renderTextures.size();i++) {
		if(renderTextures[i]->enabled) {
			renderTextures[i]->Render();
		}			
	}
}

void SceneManager::Render(const Polycode::Rectangle &viewport) {	
	for(int i=0;i<scenes.size();i++) {
		if(scenes[i]->isEnabled() && !scenes[i]->isVirtual()) {
			Scene *scene = scenes[i];
			if(scene->getActiveCamera()->hasFilterShader()) {
				scene->getActiveCamera()->setViewport(viewport);				
				scene->getActiveCamera()->drawFilter(NULL);
			} else {
				scene->getActiveCamera()->setViewport(viewport);
				scene->Render(NULL, NULL, NULL, true);
			}
		}
	}

}

void SceneManager::fixedUpdate() {
	for(int i=0;i<scenes.size();i++) {
		if(scenes[i]->isEnabled()) {
			scenes[i]->fixedUpdate();
		}
	}
}

void SceneManager::Update() {
	for(int i=0;i<scenes.size();i++) {
		if(scenes[i]->isEnabled()) {
			scenes[i]->Update();
		}
	}
}
