/*
 *  PolySceneRenderTexture.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 8/6/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolySceneRenderTexture.h"


using namespace Polycode;

SceneRenderTexture::SceneRenderTexture(Scene *targetScene, Camera *targetCamera, int renderWidth,int renderHeight) {
	targetTexture = CoreServices::getInstance()->getMaterialManager()->createTexture(renderWidth, renderHeight, NULL,true);
	this->targetScene = targetScene;
	this->targetCamera = targetCamera;
	CoreServices::getInstance()->getSceneManager()->registerRenderTexture(this);
}

void SceneRenderTexture::drawScreen() {
	CoreServices::getInstance()->getRenderer()->renderToTexture(targetTexture);
}
	
Scene *SceneRenderTexture::getTargetScene() {
	return targetScene;
}

Camera *SceneRenderTexture::getTargetCamera() {
	return targetCamera;
}

Texture *SceneRenderTexture::getTargetTexture() {
	return targetTexture;
}

SceneRenderTexture::~SceneRenderTexture() {

}
