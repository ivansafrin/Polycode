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

#include "PolySceneLight.h"
#include "PolyCamera.h"
#include "PolyCore.h"
#include "PolyCoreServices.h"
#include "PolyMesh.h"
#include "PolyRenderer.h"
#include "PolyScenePrimitive.h"
#include "PolyScene.h"

using namespace Polycode;

SceneLight::SceneLight(int type, Scene *parentScene, Number intensity, Number constantAttenuation, Number linearAttenuation, Number quadraticAttenuation) : Entity() {
	this->type = type;
	this->intensity = intensity;
	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
	
	spotlightCutoff = 40;
	spotlightExponent = 10;
		
    shadowMapRes = 256;
	this->depthWrite = false;
	lightMesh = new Mesh(Mesh::QUAD_MESH);
	lightMesh->createBox(0.1,0.1,0.1);
	setLocalBoundingBox(lightMesh->calculateBBox());
	shadowMapFOV = 60.0f;
	zBufferTexture = NULL;
	spotCamera = NULL;
	this->parentScene = parentScene;
	shadowsEnabled = false;
	lightColor.setColor(1.0f,1.0f,1.0f,1.0f);
	setSpotlightProperties(40,0.1);
	
	lightImportance = 0;
}

void SceneLight::setLightType(int lightType) {
    this->type = lightType;
}

void SceneLight::setLightImportance(int newImportance) {
	lightImportance = newImportance;
}

int SceneLight::getLightImportance() const {
	return lightImportance;
}

void SceneLight::enableShadows(bool val, unsigned int resolution) {
	if(val) {
        delete zBufferTexture;
        CoreServices::getInstance()->getRenderer()->createRenderTextures(NULL, &zBufferTexture, resolution, resolution, false);
		if(!spotCamera) {
			spotCamera = new Camera(parentScene);
            /*
            spotCamera->setProjectionMode(Camera::ORTHO_SIZE_MANUAL);
            spotCamera->setOrthoSize(5.0, 5.0);
             */
            spotCamera->editorOnly = true;
            spotCamera->setClippingPlanes(0.01, 100.0);
//            spotCamera->setPitch(90.0);
			addChild(spotCamera);	
		}
		shadowMapRes = resolution;
		shadowsEnabled = true;
	} else {
		shadowsEnabled = false;
	}
}

bool SceneLight::areShadowsEnabled() const {
	return shadowsEnabled;
}

void SceneLight::setAttenuation(Number constantAttenuation, Number linearAttenuation, Number quadraticAttenuation) {
	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
}			


void SceneLight::setIntensity(Number newIntensity) {
	intensity = newIntensity;
}

void SceneLight::setShadowMapFOV(Number fov) {
	shadowMapFOV = fov;
}

Number SceneLight::getShadowMapFOV() const {
    return shadowMapFOV;
}

SceneLight::~SceneLight() {
    if(parentScene) {
        parentScene->removeLight(this);
    }
	printf("Destroying scene light...\n");
}

unsigned int SceneLight::getShadowMapResolution() const {
    return shadowMapRes;
}

void SceneLight::renderDepthMap(Scene *scene) {
    spotCamera->setFOV(shadowMapFOV);
	Renderer* renderer = CoreServices::getInstance()->getRenderer();
	renderer->pushMatrix();
	renderer->loadIdentity();

    Number vpW = renderer->getViewportWidth();
    Number vpH = renderer->getViewportHeight();
    
	renderer->setViewportSize(shadowMapRes, shadowMapRes);
	renderer->bindFrameBufferTexture(zBufferTexture);

	scene->RenderDepthOnly(spotCamera);
		
	lightViewMatrix = getConcatenatedMatrix().Inverse() *  renderer->getProjectionMatrix();
	renderer->unbindFramebuffers();
	renderer->popMatrix();
	renderer->setViewportSize(vpW , vpH);
}

Entity *SceneLight::Clone(bool deepClone, bool ignoreEditorOnly) const {
    SceneLight *newLight = new SceneLight(type, NULL, intensity, constantAttenuation, linearAttenuation, quadraticAttenuation);
    applyClone(newLight, deepClone, ignoreEditorOnly);
    return newLight;
}

void SceneLight::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    Entity::applyClone(clone, deepClone, ignoreEditorOnly);
    SceneLight *cloneLight = (SceneLight*) clone;
    
    cloneLight->setAttenuation(constantAttenuation, linearAttenuation, quadraticAttenuation);
    cloneLight->setIntensity(intensity);
    cloneLight->lightColor = lightColor;
    cloneLight->specularLightColor = specularLightColor;
    cloneLight->enableShadows(shadowsEnabled, shadowMapRes);
    cloneLight->setShadowMapFOV(shadowMapFOV);
    cloneLight->setSpotlightProperties(spotlightCutoff, spotlightExponent);
    cloneLight->setLightType(type);
}

Scene *SceneLight::getParentScene() const {
    return parentScene;
}

void SceneLight::setParentScene(Scene *scene) {
    parentScene = scene;
    if(spotCamera) {
        spotCamera->setParentScene(scene);
    }
}

Camera *SceneLight::getSpotlightCamera() {
    return spotCamera;
}

const Matrix4& SceneLight::getLightViewMatrix() const {
	return lightViewMatrix;
}

Texture *SceneLight::getZBufferTexture() const {
	return zBufferTexture;
}

Number SceneLight::getIntensity() const {
	return intensity;
}

void SceneLight::Render() {
    
}

int SceneLight::getType() const {
	return type;
}
