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
			
Camera::Camera(Scene *parentScene) : Entity() {
	projectionMode = PERSPECTIVE_FOV;
	renderer = CoreServices::getInstance()->getRenderer();
	setParentScene(parentScene);
	setFOV(45.0f);
	filterShaderMaterial = NULL;
	originalSceneTexture = NULL;
	zBufferSceneTexture = NULL;
	exposureLevel = 1.0f;
	_hasFilterShader = false;
	frustumCulling = true;
	nearClipPlane = 1.0;
	farClipPlane = 1000.0;
	topLeftOrtho = false;
    orthoSizeX = 1.0;
	orthoSizeY = 1.0;
}

Camera::~Camera() {	
	for(int i=0; i < localShaderOptions.size(); i++) {
		delete localShaderOptions[i];
	}

	delete originalSceneTexture;
	delete zBufferSceneTexture;
}

void Camera::setClippingPlanes(Number nearClipPlane, Number farClipPlane) {
	this->nearClipPlane = nearClipPlane;
	this->farClipPlane = farClipPlane;	
}

void Camera::setFOV(Number fov) {
	setProjectionMode(PERSPECTIVE_FOV);
	this->fov = fov;
}

bool Camera::isSphereInFrustum(const Vector3 &pos, Number fRadius) {
	if(!frustumCulling)
		return true;
    for( int i = 0; i < 6; ++i )
    {
        if( frustumPlanes[i].x * pos.x +
            frustumPlanes[i].y * pos.y +
            frustumPlanes[i].z * pos.z +
            frustumPlanes[i].w <= -fRadius )
            return false;
    }

    return true;
}


bool Camera::isAABBInFrustum(const AABB &aabb) {
    for( int i=0; i < 6; i++) {
        int out = 0;
        out += (frustumPlanes[i].dot(Vector4(aabb.min.x, aabb.min.y, aabb.min.z, 1.0)) < 0.0) ? 1 : 0;
        out += (frustumPlanes[i].dot(Vector4(aabb.max.x, aabb.min.y, aabb.min.z, 1.0)) < 0.0) ? 1 : 0;
        out += (frustumPlanes[i].dot(Vector4(aabb.min.x, aabb.max.y, aabb.min.z, 1.0)) < 0.0) ? 1 : 0;
        out += (frustumPlanes[i].dot(Vector4(aabb.max.x, aabb.max.y, aabb.min.z, 1.0)) < 0.0) ? 1 : 0;
        out += (frustumPlanes[i].dot(Vector4(aabb.min.x, aabb.min.y, aabb.max.z, 1.0)) < 0.0) ? 1 : 0;
        out += (frustumPlanes[i].dot(Vector4(aabb.max.x, aabb.min.y, aabb.max.z, 1.0)) < 0.0) ? 1 : 0;
        out += (frustumPlanes[i].dot(Vector4(aabb.min.x, aabb.max.y, aabb.max.z, 1.0)) < 0.0) ? 1 : 0;
        out += (frustumPlanes[i].dot(Vector4(aabb.max.x, aabb.max.y, aabb.max.z, 1.0)) < 0.0) ? 1 : 0;
        if( out==8 ) return false;
    }
    
    return true;
}

void Camera::setOrthoSize(Number orthoSizeX, Number orthoSizeY) {
	this->orthoSizeX = orthoSizeX;
	this->orthoSizeY = orthoSizeY;
}

void Camera::setOrthoMode(bool mode) {
	if (mode && !getOrthoMode()) {
		setProjectionMode(ORTHO_SIZE_LOCK_HEIGHT);
	}
	else if (!mode && getOrthoMode()) {
		setProjectionMode(PERSPECTIVE_FOV);
	}
}			


void Camera::setFrustumMode(Number left, Number right, Number bottom, Number top, Number front, Number back) {
	setProjectionMode(PERSPECTIVE_FRUSTUM);
	leftFrustum = left;
	rightFrustum = right;
	bottomFrustum = bottom;
	topFrustum = top;
	nearClipPlane = front;
	farClipPlane = back;
}

Number Camera::getOrthoSizeX() {
	return orthoSizeX;
}

Number Camera::getOrthoSizeY() {
	return orthoSizeY;
}


void Camera::buildFrustumPlanes() {

	Matrix4 mv;
	Matrix4 mvp;
	Number t;

    mv = renderer->getModelviewMatrix();

    //
    // Concatenate the projection matrix and the model-view matrix to produce 
    // a combined model-view-projection matrix.
    //

    mvp.ml[ 0] = mv.ml[ 0] * projectionMatrix.ml[ 0] + mv.ml[ 1] * projectionMatrix.ml[ 4] + mv.ml[ 2] * projectionMatrix.ml[ 8] + mv.ml[ 3] * projectionMatrix.ml[12];

    mvp.ml[ 1] = mv.ml[ 0] * projectionMatrix.ml[ 1] + mv.ml[ 1] * projectionMatrix.ml[ 5] + mv.ml[ 2] * projectionMatrix.ml[ 9] + mv.ml[ 3] * projectionMatrix.ml[13];
    mvp.ml[ 2] = mv.ml[ 0] * projectionMatrix.ml[ 2] + mv.ml[ 1] * projectionMatrix.ml[ 6] + mv.ml[ 2] * projectionMatrix.ml[10] + mv.ml[ 3] * projectionMatrix.ml[14];
    mvp.ml[ 3] = mv.ml[ 0] * projectionMatrix.ml[ 3] + mv.ml[ 1] * projectionMatrix.ml[ 7] + mv.ml[ 2] * projectionMatrix.ml[11] + mv.ml[ 3] * projectionMatrix.ml[15];

    mvp.ml[ 4] = mv.ml[ 4] * projectionMatrix.ml[ 0] + mv.ml[ 5] * projectionMatrix.ml[ 4] + mv.ml[ 6] * projectionMatrix.ml[ 8] + mv.ml[ 7] * projectionMatrix.ml[12];
    mvp.ml[ 5] = mv.ml[ 4] * projectionMatrix.ml[ 1] + mv.ml[ 5] * projectionMatrix.ml[ 5] + mv.ml[ 6] * projectionMatrix.ml[ 9] + mv.ml[ 7] * projectionMatrix.ml[13];
    mvp.ml[ 6] = mv.ml[ 4] * projectionMatrix.ml[ 2] + mv.ml[ 5] * projectionMatrix.ml[ 6] + mv.ml[ 6] * projectionMatrix.ml[10] + mv.ml[ 7] * projectionMatrix.ml[14];
    mvp.ml[ 7] = mv.ml[ 4] * projectionMatrix.ml[ 3] + mv.ml[ 5] * projectionMatrix.ml[ 7] + mv.ml[ 6] * projectionMatrix.ml[11] + mv.ml[ 7] * projectionMatrix.ml[15];

    mvp.ml[ 8] = mv.ml[ 8] * projectionMatrix.ml[ 0] + mv.ml[ 9] * projectionMatrix.ml[ 4] + mv.ml[10] * projectionMatrix.ml[ 8] + mv.ml[11] * projectionMatrix.ml[12];
    mvp.ml[ 9] = mv.ml[ 8] * projectionMatrix.ml[ 1] + mv.ml[ 9] * projectionMatrix.ml[ 5] + mv.ml[10] * projectionMatrix.ml[ 9] + mv.ml[11] * projectionMatrix.ml[13];
    mvp.ml[10] = mv.ml[ 8] * projectionMatrix.ml[ 2] + mv.ml[ 9] * projectionMatrix.ml[ 6] + mv.ml[10] * projectionMatrix.ml[10] + mv.ml[11] * projectionMatrix.ml[14];
    mvp.ml[11] = mv.ml[ 8] * projectionMatrix.ml[ 3] + mv.ml[ 9] * projectionMatrix.ml[ 7] + mv.ml[10] * projectionMatrix.ml[11] + mv.ml[11] * projectionMatrix.ml[15];

    mvp.ml[12] = mv.ml[12] * projectionMatrix.ml[ 0] + mv.ml[13] * projectionMatrix.ml[ 4] + mv.ml[14] * projectionMatrix.ml[ 8] + mv.ml[15] * projectionMatrix.ml[12];
    mvp.ml[13] = mv.ml[12] * projectionMatrix.ml[ 1] + mv.ml[13] * projectionMatrix.ml[ 5] + mv.ml[14] * projectionMatrix.ml[ 9] + mv.ml[15] * projectionMatrix.ml[13];
    mvp.ml[14] = mv.ml[12] * projectionMatrix.ml[ 2] + mv.ml[13] * projectionMatrix.ml[ 6] + mv.ml[14] * projectionMatrix.ml[10] + mv.ml[15] * projectionMatrix.ml[14];
    mvp.ml[15] = mv.ml[12] * projectionMatrix.ml[ 3] + mv.ml[13] * projectionMatrix.ml[ 7] + mv.ml[14] * projectionMatrix.ml[11] + mv.ml[15] * projectionMatrix.ml[15];

    //
    // Extract the frustum's right clipping plane and normalize it.
    //

    frustumPlanes[0].x = mvp.ml[ 3] - mvp.ml[ 0];
    frustumPlanes[0].y = mvp.ml[ 7] - mvp.ml[ 4];
    frustumPlanes[0].z = mvp.ml[11] - mvp.ml[ 8];
    frustumPlanes[0].w = mvp.ml[15] - mvp.ml[12];

    t = (Number) sqrt( frustumPlanes[0].x * frustumPlanes[0].x + 
                      frustumPlanes[0].y * frustumPlanes[0].y + 
                      frustumPlanes[0].z * frustumPlanes[0].z );

    frustumPlanes[0].x /= t;
    frustumPlanes[0].y /= t;
    frustumPlanes[0].z /= t;
    frustumPlanes[0].w /= t;

    //
    // Extract the frustum's left clipping plane and normalize it.
    //

    frustumPlanes[1].x = mvp.ml[ 3] + mvp.ml[ 0];
    frustumPlanes[1].y = mvp.ml[ 7] + mvp.ml[ 4];
    frustumPlanes[1].z = mvp.ml[11] + mvp.ml[ 8];
    frustumPlanes[1].w = mvp.ml[15] + mvp.ml[12];

    t = (Number) sqrt( frustumPlanes[1].x * frustumPlanes[1].x + 
                      frustumPlanes[1].y * frustumPlanes[1].y + 
                      frustumPlanes[1].z * frustumPlanes[1].z );

    frustumPlanes[1].x /= t;
    frustumPlanes[1].y /= t;
    frustumPlanes[1].z /= t;
    frustumPlanes[1].w /= t;

    //
    // Extract the frustum's bottom clipping plane and normalize it.
    //

    frustumPlanes[2].x = mvp.ml[ 3] + mvp.ml[ 1];
    frustumPlanes[2].y = mvp.ml[ 7] + mvp.ml[ 5];
    frustumPlanes[2].z = mvp.ml[11] + mvp.ml[ 9];
    frustumPlanes[2].w = mvp.ml[15] + mvp.ml[13];

    t = (Number) sqrt( frustumPlanes[2].x * frustumPlanes[2].x + 
                      frustumPlanes[2].y * frustumPlanes[2].y + 
                      frustumPlanes[2].z * frustumPlanes[2].z );

    frustumPlanes[2].x /= t;
    frustumPlanes[2].y /= t;
    frustumPlanes[2].z /= t;
    frustumPlanes[2].w /= t;

    //
    // Extract the frustum's top clipping plane and normalize it.
    //

    frustumPlanes[3].x = mvp.ml[ 3] - mvp.ml[ 1];
    frustumPlanes[3].y = mvp.ml[ 7] - mvp.ml[ 5];
    frustumPlanes[3].z = mvp.ml[11] - mvp.ml[ 9];
    frustumPlanes[3].w = mvp.ml[15] - mvp.ml[13];

    t = (Number) sqrt( frustumPlanes[3].x * frustumPlanes[3].x + 
                      frustumPlanes[3].y * frustumPlanes[3].y + 
                      frustumPlanes[3].z * frustumPlanes[3].z );

    frustumPlanes[3].x /= t;
    frustumPlanes[3].y /= t;
    frustumPlanes[3].z /= t;
    frustumPlanes[3].w /= t;

    //
    // Extract the frustum's far clipping plane and normalize it.
    //

    frustumPlanes[4].x = mvp.ml[ 3] - mvp.ml[ 2];
    frustumPlanes[4].y = mvp.ml[ 7] - mvp.ml[ 6];
    frustumPlanes[4].z = mvp.ml[11] - mvp.ml[10];
    frustumPlanes[4].w = mvp.ml[15] - mvp.ml[14];

    t = (Number) sqrt( frustumPlanes[4].x * frustumPlanes[4].x +  
                      frustumPlanes[4].y * frustumPlanes[4].y + 
                      frustumPlanes[4].z * frustumPlanes[4].z );

    frustumPlanes[4].x /= t;
    frustumPlanes[4].y /= t;
    frustumPlanes[4].z /= t;
    frustumPlanes[4].w /= t;

    //
    // Extract the frustum's near clipping plane and normalize it.
    //

    frustumPlanes[5].x = mvp.ml[ 3] + mvp.ml[ 2];
    frustumPlanes[5].y = mvp.ml[ 7] + mvp.ml[ 6];
    frustumPlanes[5].z = mvp.ml[11] + mvp.ml[10];
    frustumPlanes[5].w = mvp.ml[15] + mvp.ml[14];

    t = (Number) sqrt( frustumPlanes[5].x * frustumPlanes[5].x + 
                      frustumPlanes[5].y * frustumPlanes[5].y + 
                      frustumPlanes[5].z * frustumPlanes[5].z );

    frustumPlanes[5].x /= t;
    frustumPlanes[5].y /= t;
    frustumPlanes[5].z /= t;
    frustumPlanes[5].w /= t;

}

Entity *Camera::Clone(bool deepClone, bool ignoreEditorOnly) const {
    Camera *newCamera = new Camera(NULL);
    applyClone(newCamera, deepClone, ignoreEditorOnly);
    return newCamera;
}

void Camera::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    Entity::applyClone(clone, deepClone, ignoreEditorOnly);
    
    Camera *cloneCamera = (Camera*) clone;
	cloneCamera->projectionMatrix = Matrix4(projectionMatrix.ml);
	cloneCamera->fov = fov;
	cloneCamera->viewport = viewport;
	cloneCamera->setOrthoSize(orthoSizeX, orthoSizeY);
	cloneCamera->projectionMode = projectionMode;
	cloneCamera->setClippingPlanes(nearClipPlane, farClipPlane);
    cloneCamera->setExposureLevel(exposureLevel);
}

Scene *Camera::getParentScene() const {
    return parentScene;
}

void Camera::setParentScene(Scene *parentScene) {
	this->parentScene = parentScene;
}

void Camera::setPostFilterByName(const String& materialName) {
	Material *shaderMaterial = (Material*) CoreServices::getInstance()->getResourceManager()->getGlobalPool()->getResource(Resource::RESOURCE_MATERIAL, materialName);
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
	if(!shaderMaterial)
		return;
	if(shaderMaterial->getNumShaders() == 0)
		return;
		
	this->filterShaderMaterial = shaderMaterial;
	if(!originalSceneTexture) {
        CoreServices::getInstance()->getRenderer()->createRenderTextures(&originalSceneTexture, &zBufferSceneTexture, CoreServices::getInstance()->getCore()->getXRes(), CoreServices::getInstance()->getCore()->getYRes(), shaderMaterial->fp16RenderTargets);
	}
	
	for(int i=0; i < shaderMaterial->getNumShaders(); i++) {
		ShaderBinding* binding = shaderMaterial->getShader(i)->createBinding();		
		localShaderOptions.push_back(binding);
		binding->addParamPointer(ProgramParam::PARAM_NUMBER, "exposure", (void*)&exposureLevel);
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
		renderer->setViewportSize(targetTextureWidth, targetTextureHeight);		
	} else {
		finalTargetColorTexture = originalSceneTexture;
		finalTargetZTexture = zBufferSceneTexture;	
		renderer->setViewportSize(renderer->getXRes(), renderer->getYRes());
	}
	renderer->bindFrameBufferTexture(finalTargetColorTexture);
	renderer->bindFrameBufferTextureDepth(finalTargetZTexture);
	parentScene->Render(this);
	renderer->unbindFramebuffers();


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
		
		renderer->applyMaterial(filterShaderMaterial, localShaderOptions[i], i, true);
		if(i==filterShaderMaterial->getNumShaders()-1) {
				if(targetTexture) {
					renderer->setViewportSize(targetTextureWidth, targetTextureHeight);	
					renderer->bindFrameBufferTexture(targetTexture);								
					renderer->clearScreen();
					renderer->loadIdentity();

					renderer->drawScreenQuad(targetTextureWidth, targetTextureHeight);
					renderer->unbindFramebuffers();									
				} else {
					renderer->setViewportSize(renderer->getXRes(), renderer->getYRes());
					renderer->clearScreen();
					renderer->loadIdentity();
					renderer->drawScreenQuad(renderer->getXRes(), renderer->getYRes());
				}
		} else {
			for(int j=0; j < materialBinding->getNumOutTargetBindings(); j++) {
				Texture *bindingTexture = materialBinding->getOutTargetBinding(j)->texture;
				if(bindingTexture) {
					renderer->setViewportSize(bindingTexture->getWidth(), bindingTexture->getHeight());
					renderer->bindFrameBufferTexture(bindingTexture);				
					renderer->drawScreenQuad(bindingTexture->getWidth(), bindingTexture->getHeight());
					renderer->unbindFramebuffers();
				}
			}		
		}
		renderer->clearShader();
		renderer->loadIdentity();
	}
}

Matrix4 Camera::getProjectionMatrix() {
	return projectionMatrix;
}

Polycode::Rectangle Camera::getViewport() {
	return viewport;
}

Number Camera::getNearClippingPlane() {
    return nearClipPlane;
}

Number Camera::getFarClippingPlane() {
    return farClipPlane;
}

void Camera::setProjectionMode(int mode) {
	projectionMode = mode;
}

void Camera::setProjectionMatrix(Matrix4 matrix) {
    projectionMatrix = matrix;
}

void Camera::doCameraTransform() {
	
    viewport = renderer->getViewport();

	switch (projectionMode) {
		case PERSPECTIVE_FOV:
			renderer->setViewportShift(cameraShift.x, cameraShift.y);
			renderer->setProjectionFromFoV(fov, nearClipPlane, farClipPlane);
			renderer->setPerspectiveDefaults();
		break;
		case PERSPECTIVE_FRUSTUM:
			renderer->setProjectionFromFrustum(leftFrustum, rightFrustum, bottomFrustum, topFrustum, nearClipPlane, farClipPlane);
			renderer->setPerspectiveDefaults();
		break;
		case ORTHO_SIZE_MANUAL:
			renderer->setProjectionOrtho(orthoSizeX, orthoSizeY, nearClipPlane, farClipPlane, !topLeftOrtho);
		break;
		case ORTHO_SIZE_LOCK_HEIGHT:
			renderer->setProjectionOrtho(orthoSizeY * (viewport.w/viewport.h), orthoSizeY, nearClipPlane, farClipPlane, !topLeftOrtho);
		break;
		case ORTHO_SIZE_LOCK_WIDTH:
			renderer->setProjectionOrtho(orthoSizeX, orthoSizeX * (viewport.h/viewport.w), nearClipPlane, farClipPlane, !topLeftOrtho);
		break;
		case ORTHO_SIZE_VIEWPORT:
			renderer->setProjectionOrtho(viewport.w / renderer->getBackingResolutionScaleX(), viewport.h / renderer->getBackingResolutionScaleY(), !topLeftOrtho);
		break;
		case MANUAL_MATRIX:
            renderer->setProjectionMatrix(projectionMatrix);
        break;
	}
	renderer->setExposureLevel(exposureLevel);

    if(projectionMode != MANUAL_MATRIX) {
        projectionMatrix = renderer->getProjectionMatrix();
    }

	if(matrixDirty) {
		rebuildTransformMatrix();
	}

	Matrix4 camMatrix = getConcatenatedMatrix();
	renderer->setCameraMatrix(camMatrix);	
	camMatrix = camMatrix.Inverse();
	renderer->multModelviewMatrix(camMatrix);		
}
