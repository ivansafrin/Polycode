/*
 *  PolySceneManager.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolySceneManager.h"

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
	Logger::log("Removing scene\n");
	for(int i=0;i<scenes.size();i++) {
		if(scenes[i] == scene) {
			scenes.erase(scenes.begin()+i);
//			delete scene;
		}
	}
}

void SceneManager::registerRenderTexture(SceneRenderTexture *renderTexture) {
	renderTextures.push_back(renderTexture);
}

void SceneManager::addScene(Scene *newScene) {
	scenes.push_back(newScene);
}

void SceneManager::updateRenderTextures(Scene *scene) {
}

void SceneManager::UpdateVirtual() {
	for(int i=0;i<renderTextures.size();i++) {
		CoreServices::getInstance()->getRenderer()->setViewportSize(renderTextures[i]->getTargetTexture()->getWidth(), renderTextures[i]->getTargetTexture()->getHeight());
		CoreServices::getInstance()->getRenderer()->loadIdentity();
		renderTextures[i]->getTargetScene()->Update();
		renderTextures[i]->getTargetScene()->Render();
		renderTextures[i]->drawScreen();
		CoreServices::getInstance()->getRenderer()->clearScreen();
		CoreServices::getInstance()->getRenderer()->loadIdentity();
	}
	CoreServices::getInstance()->getRenderer()->setViewportSize(CoreServices::getInstance()->getRenderer()->getXRes(), CoreServices::getInstance()->getRenderer()->getYRes());

}

void SceneManager::Update() {
	for(int i=0;i<scenes.size();i++) {
		if(scenes[i]->isEnabled() && !scenes[i]->isVirtual()) {
			CoreServices::getInstance()->getRenderer()->loadIdentity();
			Scene *scene = scenes[i];
			scene->Update();
			if(scene->getDefaultCamera()->hasFilterShader()) {
				scene->getDefaultCamera()->drawFilter();
			} else {
				scene->Render();
			}
		}
	}
}