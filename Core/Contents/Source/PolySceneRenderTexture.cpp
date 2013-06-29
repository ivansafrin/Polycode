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

#include "PolySceneRenderTexture.h"
#include "PolyCoreServices.h"
#include "PolyRenderer.h"
#include "PolySceneManager.h"


using namespace Polycode;

SceneRenderTexture::SceneRenderTexture(Scene *targetScene, Camera *targetCamera, int renderWidth,int renderHeight, bool floatingPoint) {
	this->floatingPoint = floatingPoint;
	CoreServices::getInstance()->getRenderer()->createRenderTextures(&targetTexture, &depthTexture, renderWidth, renderHeight, floatingPoint);
	this->targetScene = targetScene;
	this->targetCamera = targetCamera;

	CoreServices::getInstance()->getRenderer()->createRenderTextures(&filterColorBufferTexture, &filterZBufferTexture, renderWidth, renderHeight, floatingPoint);
	CoreServices::getInstance()->getSceneManager()->registerRenderTexture(this);
}

void SceneRenderTexture::resizeRenderTexture(int newWidth, int newHeight) {

	if(newWidth > 0 && newHeight > 0) {
		CoreServices::getInstance()->getRenderer()->destroyTexture(targetTexture);
		CoreServices::getInstance()->getRenderer()->destroyTexture(depthTexture);
		CoreServices::getInstance()->getRenderer()->destroyTexture(filterColorBufferTexture);
		CoreServices::getInstance()->getRenderer()->destroyTexture(filterZBufferTexture);

		CoreServices::getInstance()->getRenderer()->createRenderTextures(&targetTexture, &depthTexture, newWidth, newHeight, floatingPoint);
		CoreServices::getInstance()->getRenderer()->createRenderTextures(&filterColorBufferTexture, &filterZBufferTexture, newWidth, newHeight, floatingPoint);
	}
}

Scene *SceneRenderTexture::getTargetScene() {
	return targetScene;
}

Texture *SceneRenderTexture::getFilterColorBufferTexture() {
	return filterColorBufferTexture;
}

Texture *SceneRenderTexture::getFilterZBufferTexture() {
	return filterZBufferTexture;
}

Camera *SceneRenderTexture::getTargetCamera() {
	return targetCamera;
}

Texture *SceneRenderTexture::getTargetTexture() {
	return targetTexture;
}

SceneRenderTexture::~SceneRenderTexture() {
	CoreServices::getInstance()->getSceneManager()->unregisterRenderTexture(this);
	CoreServices::getInstance()->getRenderer()->destroyTexture(targetTexture);
	CoreServices::getInstance()->getRenderer()->destroyTexture(depthTexture);
	CoreServices::getInstance()->getRenderer()->destroyTexture(filterColorBufferTexture);
	CoreServices::getInstance()->getRenderer()->destroyTexture(filterZBufferTexture);
}
