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

#include "polycode/core/PolySceneRenderTexture.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyScene.h"
#include "polycode/core/PolyCamera.h"

using namespace Polycode;

SceneRenderTexture::SceneRenderTexture(int renderWidth,int renderHeight, bool floatingPoint) : floatingPoint(floatingPoint) {
	targetFramebuffer = std::make_shared<RenderBuffer>(renderWidth, renderHeight, true, floatingPoint);
	enabled = true;
}

void SceneRenderTexture::resizeRenderTexture(int newWidth, int newHeight) {

	if(newWidth > 0 && newHeight > 0) {
		targetFramebuffer = nullptr;
		targetFramebuffer = std::make_shared<RenderBuffer>(newWidth, newHeight, true, floatingPoint);
	}
}

void SceneRenderTexture::Render(RenderFrame *frame, Scene *targetScene, Camera* targetCamera) {
	if(targetCamera->hasFilterShader()) {
		targetCamera->drawFilter(frame, targetFramebuffer, targetScene);
	} else {
		targetScene->Render(frame, targetCamera, targetFramebuffer, NULL);
	}
}

Image *SceneRenderTexture::saveToImage() {
	//RENDERER_TODO
	//return renderer->renderBufferToImage(targetTexture);
	return NULL;
}

std::shared_ptr<Texture> SceneRenderTexture::getTargetTexture() {
	return targetFramebuffer->colorTexture;
}

SceneRenderTexture::~SceneRenderTexture() {
}
