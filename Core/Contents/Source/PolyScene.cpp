/*
 *  PolyScene.cpp
 *  TAU
 *
 *  Created by Ivan Safrin on 3/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyScene.h"

using namespace Polycode;

Scene::Scene() : EventDispatcher() {
	defaultCamera = new Camera(this);
	CoreServices::getInstance()->getSceneManager()->addScene(this);
	fogEnabled = false;
	lightingEnabled = false;
	enabled = true;
	isSceneVirtual = false;
}

void Scene::setVirtual(bool val) {
	isSceneVirtual = val;
}

bool Scene::isVirtual() {
	return isSceneVirtual;
}

void Scene::setEnabled(bool enabled) {
	this->enabled = enabled;
}

bool Scene::isEnabled() {
	return enabled;
}

void Scene::Update() {

}

Scene::~Scene() {
	Logger::log("Cleaning scene...\n");
	for(int i=0; i < entities.size(); i++) {	
//		delete entities[i];
	}
	entities.clear();	
	CoreServices::getInstance()->getSceneManager()->removeScene(this);	
//	delete defaultCamera;
}

void Scene::enableLighting(bool enable) {
	lightingEnabled = enable;
	CoreServices::getInstance()->getRenderer()->enableLighting(enable);
}



void Scene::enableFog(bool enable) {
	fogEnabled = enable;
	if(enable)
		CoreServices::getInstance()->getRenderer()->setFogProperties(fogMode, fogColor, fogDensity, fogStartDepth, fogEndDepth);
	CoreServices::getInstance()->getRenderer()->enableFog(enable);
	
}

void Scene::setFogProperties(int fogMode, Color color, float density, float startDepth, float endDepth) {
	this->fogMode = fogMode;
	fogColor = color;
	fogDensity = density;
	fogStartDepth = startDepth;
	fogEndDepth = endDepth;
	if(fogEnabled)
		CoreServices::getInstance()->getRenderer()->setFogProperties(fogMode, fogColor, fogDensity, fogStartDepth, fogEndDepth);
	
}

SceneEntity *Scene::getEntityAtCursor(float x, float y) {
	for(int i =0; i< entities.size(); i++) {
		if(entities[i]->testMouseCollision(x,y)) {
			return entities[i];
		}
	}
	return NULL;
}

void Scene::addEntity(SceneEntity *entity) {
	entity->setRenderer(CoreServices::getInstance()->getRenderer());
	entities.push_back(entity);
}

void Scene::removeEntity(SceneEntity *entity) {
	for(int i=0; i < entities.size(); i++) {
		if(entities[i] == entity) {
			entities.erase(entities.begin()+i);
			return;
		}		
	}
}

Camera *Scene::getDefaultCamera() {
	return defaultCamera;
}