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

#include "PolyCamera.h"
#include "PolyCore.h"
#include "PolyCoreServices.h"
#include "PolyMaterial.h"
#include "PolyRenderer.h"
#include "PolyResource.h"
#include "PolyResourceManager.h"
#include "PolyScene.h"
#include "PolyShader.h"
#include "PolyTexture.h"

using namespace Polycode;

Camera::Camera(Scene *parentScene) : SceneEntity() {
	setParentScene(parentScene);
	orthoMode = false;
	fov = 45.0f;
	filterShaderMaterial = NULL;
	originalSceneTexture = NULL;
	zBufferSceneTexture = NULL;
	exposureLevel = 1.0f;
	_hasFilterShader = false;
	fovSet = false;
	frustumCulling = true;
}

Camera::~Camera() {
	for(int i=0; i < localShaderOptions.size(); i++) {
		delete localShaderOptions[i];
	}

	delete originalSceneTexture;
	delete zBufferSceneTexture;
}

void Camera::setExposureLevel(Number level) {
	exposureLevel = level;
}

Number Camera::getExposureLevel() {
	return exposureLevel;
}


void Camera::setFOV(Number fov) {
	this->fov = fov;
	fovSet = true;
}

Number Camera::getFOV() {
	return fov;
}


bool Camera::isSphereInFrustum(Vector3 pos, Number fRadius) {
	if(!frustumCulling)
		return true;
	for( int i = 0; i < 6; ++i )
	{
		if( frustumPlanes[i][0] * pos.x +
			frustumPlanes[i][1] * pos.y +
			frustumPlanes[i][2] * pos.z +
			frustumPlanes[i][3] <= -fRadius )
			return false;
	}

	return true;
}

void Camera::setOrthoMode(bool mode, Number orthoSizeX, Number orthoSizeY) {
	this->orthoSizeX = orthoSizeX;
	this->orthoSizeY = orthoSizeY;
	orthoMode = mode;
}

bool Camera::getOrthoMode() {
	return orthoMode;
}

Number Camera::getOrthoSizeX() {
	return orthoSizeX;
}

Number Camera::getOrthoSizeY() {
	return orthoSizeY;
}


void Camera::buildFrustumPlanes() {

	Matrix4 p; 
	Matrix4 mv;
	Matrix4 mvp;
	Number t;

	p = CoreServices::getInstance()->getRenderer()->getProjectionMatrix();
	mv = CoreServices::getInstance()->getRenderer()->getModelviewMatrix();

	//
	// Concatenate the projection matrix and the model-view matrix to produce 
	// a combined model-view-projection matrix.
	//

	mvp.ml[ 0] = mv.ml[ 0] * p.ml[ 0] + mv.ml[ 1] * p.ml[ 4] + mv.ml[ 2] * p.ml[ 8] + mv.ml[ 3] * p.ml[12];

	mvp.ml[ 1] = mv.ml[ 0] * p.ml[ 1] + mv.ml[ 1] * p.ml[ 5] + mv.ml[ 2] * p.ml[ 9] + mv.ml[ 3] * p.ml[13];
	mvp.ml[ 2] = mv.ml[ 0] * p.ml[ 2] + mv.ml[ 1] * p.ml[ 6] + mv.ml[ 2] * p.ml[10] + mv.ml[ 3] * p.ml[14];
	mvp.ml[ 3] = mv.ml[ 0] * p.ml[ 3] + mv.ml[ 1] * p.ml[ 7] + mv.ml[ 2] * p.ml[11] + mv.ml[ 3] * p.ml[15];

	mvp.ml[ 4] = mv.ml[ 4] * p.ml[ 0] + mv.ml[ 5] * p.ml[ 4] + mv.ml[ 6] * p.ml[ 8] + mv.ml[ 7] * p.ml[12];
	mvp.ml[ 5] = mv.ml[ 4] * p.ml[ 1] + mv.ml[ 5] * p.ml[ 5] + mv.ml[ 6] * p.ml[ 9] + mv.ml[ 7] * p.ml[13];
	mvp.ml[ 6] = mv.ml[ 4] * p.ml[ 2] + mv.ml[ 5] * p.ml[ 6] + mv.ml[ 6] * p.ml[10] + mv.ml[ 7] * p.ml[14];
	mvp.ml[ 7] = mv.ml[ 4] * p.ml[ 3] + mv.ml[ 5] * p.ml[ 7] + mv.ml[ 6] * p.ml[11] + mv.ml[ 7] * p.ml[15];

	mvp.ml[ 8] = mv.ml[ 8] * p.ml[ 0] + mv.ml[ 9] * p.ml[ 4] + mv.ml[10] * p.ml[ 8] + mv.ml[11] * p.ml[12];
	mvp.ml[ 9] = mv.ml[ 8] * p.ml[ 1] + mv.ml[ 9] * p.ml[ 5] + mv.ml[10] * p.ml[ 9] + mv.ml[11] * p.ml[13];
	mvp.ml[10] = mv.ml[ 8] * p.ml[ 2] + mv.ml[ 9] * p.ml[ 6] + mv.ml[10] * p.ml[10] + mv.ml[11] * p.ml[14];
	mvp.ml[11] = mv.ml[ 8] * p.ml[ 3] + mv.ml[ 9] * p.ml[ 7] + mv.ml[10] * p.ml[11] + mv.ml[11] * p.ml[15];

	mvp.ml[12] = mv.ml[12] * p.ml[ 0] + mv.ml[13] * p.ml[ 4] + mv.ml[14] * p.ml[ 8] + mv.ml[15] * p.ml[12];
	mvp.ml[13] = mv.ml[12] * p.ml[ 1] + mv.ml[13] * p.ml[ 5] + mv.ml[14] * p.ml[ 9] + mv.ml[15] * p.ml[13];
	mvp.ml[14] = mv.ml[12] * p.ml[ 2] + mv.ml[13] * p.ml[ 6] + mv.ml[14] * p.ml[10] + mv.ml[15] * p.ml[14];
	mvp.ml[15] = mv.ml[12] * p.ml[ 3] + mv.ml[13] * p.ml[ 7] + mv.ml[14] * p.ml[11] + mv.ml[15] * p.ml[15];

	//
	// Extract the frustum's right clipping plane and normalize it.
	//

	frustumPlanes[0][0] = mvp.ml[ 3] - mvp.ml[ 0];
	frustumPlanes[0][1] = mvp.ml[ 7] - mvp.ml[ 4];
	frustumPlanes[0][2] = mvp.ml[11] - mvp.ml[ 8];
	frustumPlanes[0][3] = mvp.ml[15] - mvp.ml[12];

	t = (Number) sqrt( frustumPlanes[0][0] * frustumPlanes[0][0] + 
			frustumPlanes[0][1] * frustumPlanes[0][1] + 
			frustumPlanes[0][2] * frustumPlanes[0][2] );

	frustumPlanes[0][0] /= t;
	frustumPlanes[0][1] /= t;
	frustumPlanes[0][2] /= t;
	frustumPlanes[0][3] /= t;

	//
	// Extract the frustum's left clipping plane and normalize it.
	//

	frustumPlanes[1][0] = mvp.ml[ 3] + mvp.ml[ 0];
	frustumPlanes[1][1] = mvp.ml[ 7] + mvp.ml[ 4];
	frustumPlanes[1][2] = mvp.ml[11] + mvp.ml[ 8];
	frustumPlanes[1][3] = mvp.ml[15] + mvp.ml[12];

	t = (Number) sqrt( frustumPlanes[1][0] * frustumPlanes[1][0] + 
			frustumPlanes[1][1] * frustumPlanes[1][1] + 
			frustumPlanes[1][2] * frustumPlanes[1][2] );

	frustumPlanes[1][0] /= t;
	frustumPlanes[1][1] /= t;
	frustumPlanes[1][2] /= t;
	frustumPlanes[1][3] /= t;

	//
	// Extract the frustum's bottom clipping plane and normalize it.
	//

	frustumPlanes[2][0] = mvp.ml[ 3] + mvp.ml[ 1];
	frustumPlanes[2][1] = mvp.ml[ 7] + mvp.ml[ 5];
	frustumPlanes[2][2] = mvp.ml[11] + mvp.ml[ 9];
	frustumPlanes[2][3] = mvp.ml[15] + mvp.ml[13];

	t = (Number) sqrt( frustumPlanes[2][0] * frustumPlanes[2][0] + 
			frustumPlanes[2][1] * frustumPlanes[2][1] + 
			frustumPlanes[2][2] * frustumPlanes[2][2] );

	frustumPlanes[2][0] /= t;
	frustumPlanes[2][1] /= t;
	frustumPlanes[2][2] /= t;
	frustumPlanes[2][3] /= t;

	//
	// Extract the frustum's top clipping plane and normalize it.
	//

	frustumPlanes[3][0] = mvp.ml[ 3] - mvp.ml[ 1];
	frustumPlanes[3][1] = mvp.ml[ 7] - mvp.ml[ 5];
	frustumPlanes[3][2] = mvp.ml[11] - mvp.ml[ 9];
	frustumPlanes[3][3] = mvp.ml[15] - mvp.ml[13];

	t = (Number) sqrt( frustumPlanes[3][0] * frustumPlanes[3][0] + 
			frustumPlanes[3][1] * frustumPlanes[3][1] + 
			frustumPlanes[3][2] * frustumPlanes[3][2] );

	frustumPlanes[3][0] /= t;
	frustumPlanes[3][1] /= t;
	frustumPlanes[3][2] /= t;
	frustumPlanes[3][3] /= t;

	//
	// Extract the frustum's far clipping plane and normalize it.
	//

	frustumPlanes[4][0] = mvp.ml[ 3] - mvp.ml[ 2];
	frustumPlanes[4][1] = mvp.ml[ 7] - mvp.ml[ 6];
	frustumPlanes[4][2] = mvp.ml[11] - mvp.ml[10];
	frustumPlanes[4][3] = mvp.ml[15] - mvp.ml[14];

	t = (Number) sqrt( frustumPlanes[4][0] * frustumPlanes[4][0] +  
			frustumPlanes[4][1] * frustumPlanes[4][1] + 
			frustumPlanes[4][2] * frustumPlanes[4][2] );

	frustumPlanes[4][0] /= t;
	frustumPlanes[4][1] /= t;
	frustumPlanes[4][2] /= t;
	frustumPlanes[4][3] /= t;

	//
	// Extract the frustum's near clipping plane and normalize it.
	//

	frustumPlanes[5][0] = mvp.ml[ 3] + mvp.ml[ 2];
	frustumPlanes[5][1] = mvp.ml[ 7] + mvp.ml[ 6];
	frustumPlanes[5][2] = mvp.ml[11] + mvp.ml[10];
	frustumPlanes[5][3] = mvp.ml[15] + mvp.ml[14];

	t = (Number) sqrt( frustumPlanes[5][0] * frustumPlanes[5][0] + 
			frustumPlanes[5][1] * frustumPlanes[5][1] + 
			frustumPlanes[5][2] * frustumPlanes[5][2] );

	frustumPlanes[5][0] /= t;
	frustumPlanes[5][1] /= t;
	frustumPlanes[5][2] /= t;
	frustumPlanes[5][3] /= t;

}

bool Camera::canSee(SceneEntity *entity) {
	return isSphereInFrustum(entity->getPosition(), entity->getBBoxRadius());
}

void Camera::setParentScene(Scene *parentScene) {
	this->parentScene = parentScene;
}

void Camera::setPostFilterByName(const String& materialName) {
	Material *shaderMaterial = (Material*) CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_MATERIAL, materialName);
	if(shaderMaterial)
		setPostFilter(shaderMaterial);
}

void Camera::removePostFilter() {
	if(_hasFilterShader) {
		filterShaderMaterial = NULL;
		_hasFilterShader = false;
	}
}

void Camera::setPostFilter(Material *shaderMaterial) {
	if(!shaderMaterial || shaderMaterial->getNumShaders() == 0)
		return;

	this->filterShaderMaterial = shaderMaterial;
	if(!originalSceneTexture) {
		CoreServices::getInstance()->getRenderer()->createRenderTextures(&originalSceneTexture, &zBufferSceneTexture, CoreServices::getInstance()->getCore()->getXRes(), CoreServices::getInstance()->getCore()->getYRes(), shaderMaterial->fp16RenderTargets);
	}

	for(int i=0; i < shaderMaterial->getNumShaders(); i++) {
		ShaderBinding* binding = shaderMaterial->getShader(i)->createBinding();
		localShaderOptions.push_back(binding);
		binding->addLocalParam("exposure", (void*)&exposureLevel);
	}

	_hasFilterShader = true;
}

bool Camera::hasFilterShader() {
	return _hasFilterShader;
}

void Camera::setLightDepthTexture(Texture *texture) {
	for(int i=0; i < localShaderOptions.size(); i++) {
		localShaderOptions[i]->clearTexture("PolyLight0ZBuffer");
		localShaderOptions[i]->addTexture("PolyLight0ZBuffer", texture);
	}

}

void Camera::drawFilter(Texture *targetTexture, Number targetTextureWidth, Number targetTextureHeight, Texture *targetColorTexture, Texture *targetZTexture) {

	if(!filterShaderMaterial)
		return;

	Texture *finalTargetColorTexture;
	Texture *finalTargetZTexture;

	if(targetTexture) {
		finalTargetColorTexture = targetColorTexture;
		finalTargetZTexture = targetZTexture;
		CoreServices::getInstance()->getRenderer()->setViewportSize(targetTextureWidth, targetTextureHeight);
	} else {
		finalTargetColorTexture = originalSceneTexture;
		finalTargetZTexture = zBufferSceneTexture;
		CoreServices::getInstance()->getRenderer()->setViewportSize(CoreServices::getInstance()->getRenderer()->getXRes(), CoreServices::getInstance()->getRenderer()->getYRes());
	}
	CoreServices::getInstance()->getRenderer()->bindFrameBufferTexture(finalTargetColorTexture);
	CoreServices::getInstance()->getRenderer()->bindFrameBufferTextureDepth(finalTargetZTexture);
	parentScene->Render(this);
	CoreServices::getInstance()->getRenderer()->unbindFramebuffers();


	ShaderBinding* materialBinding;
	for(int i=0; i < filterShaderMaterial->getNumShaders(); i++) {
		materialBinding = filterShaderMaterial->getShaderBinding(i);

		for(int j=0; j < materialBinding->getNumColorTargetBindings(); j++) {
			RenderTargetBinding *colorBinding = materialBinding->getColorTargetBinding(j);
			materialBinding->clearTexture(colorBinding->name);
			materialBinding->addTexture(colorBinding->name, finalTargetColorTexture);
		}

		for(int j=0; j < materialBinding->getNumDepthTargetBindings(); j++) {
			RenderTargetBinding *depthBinding = materialBinding->getDepthTargetBinding(j);
			materialBinding->clearTexture(depthBinding->name);
			materialBinding->addTexture(depthBinding->name, finalTargetZTexture);
		}

		CoreServices::getInstance()->getRenderer()->applyMaterial(filterShaderMaterial, localShaderOptions[i], i);
		if(i==filterShaderMaterial->getNumShaders()-1) {
			if(targetTexture) {
				CoreServices::getInstance()->getRenderer()->setViewportSize(targetTextureWidth, targetTextureHeight);	
				CoreServices::getInstance()->getRenderer()->bindFrameBufferTexture(targetTexture);
				CoreServices::getInstance()->getRenderer()->clearScreen();
				CoreServices::getInstance()->getRenderer()->loadIdentity();

				CoreServices::getInstance()->getRenderer()->drawScreenQuad(targetTextureWidth, targetTextureHeight);
				CoreServices::getInstance()->getRenderer()->unbindFramebuffers();
			} else {
				CoreServices::getInstance()->getRenderer()->setViewportSize(CoreServices::getInstance()->getRenderer()->getXRes(), CoreServices::getInstance()->getRenderer()->getYRes());
				CoreServices::getInstance()->getRenderer()->clearScreen();
				CoreServices::getInstance()->getRenderer()->loadIdentity();
				CoreServices::getInstance()->getRenderer()->drawScreenQuad(CoreServices::getInstance()->getRenderer()->getXRes(), CoreServices::getInstance()->getRenderer()->getYRes());
			}
		} else {
			for(int j=0; j < materialBinding->getNumOutTargetBindings(); j++) {
				CoreServices::getInstance()->getRenderer()->setViewportSize(materialBinding->getOutTargetBinding(j)->width, materialBinding->getOutTargetBinding(j)->height);
				CoreServices::getInstance()->getRenderer()->bindFrameBufferTexture(materialBinding->getOutTargetBinding(j)->texture);
				CoreServices::getInstance()->getRenderer()->drawScreenQuad(materialBinding->getOutTargetBinding(j)->width, materialBinding->getOutTargetBinding(j)->height);
				CoreServices::getInstance()->getRenderer()->unbindFramebuffers();
			}
		}
		CoreServices::getInstance()->getRenderer()->clearShader();
		CoreServices::getInstance()->getRenderer()->loadIdentity();
	}

}

void Camera::doCameraTransform() {

	if(fovSet)
		CoreServices::getInstance()->getRenderer()->setFOV(fov);
	CoreServices::getInstance()->getRenderer()->setExposureLevel(exposureLevel);

	if(matrixDirty) {
		rebuildTransformMatrix();
	}

	Matrix4 camMatrix = getConcatenatedMatrix();
	CoreServices::getInstance()->getRenderer()->setCameraMatrix(camMatrix);
	camMatrix = camMatrix.Inverse();
	CoreServices::getInstance()->getRenderer()->multModelviewMatrix(camMatrix);
}
