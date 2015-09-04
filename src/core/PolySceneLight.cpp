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

#include "polycode/core/PolySceneLight.h"
#include "polycode/core/PolyCamera.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyScenePrimitive.h"
#include "polycode/core/PolyScene.h"

using namespace Polycode;

SceneLight::SceneLight(int type, Scene *parentScene, Number intensity, Number constantAttenuation, Number linearAttenuation, Number quadraticAttenuation) : Entity() {
	lightInfo.type = type;
	lightInfo.intensity = intensity;
	lightInfo.constantAttenuation = constantAttenuation;
	lightInfo.linearAttenuation = linearAttenuation;
	lightInfo.quadraticAttenuation = quadraticAttenuation;
	
	lightInfo.spotlightCutoff = 40;
	lightInfo.spotlightExponent = 10;
		
    shadowMapRes = 256;
	this->depthWrite = false;
	    
	shadowMapFOV = 60.0f;
	lightInfo.shadowMapTexture = NULL;
	spotCamera = NULL;
	this->parentScene = parentScene;
	lightInfo.shadowsEnabled = false;
	lightInfo.diffuseColor.setColor(1.0f,1.0f,1.0f,1.0f);
	setSpotlightProperties(40,0.1);
	
	lightInfo.importance = 0;
}

void SceneLight::setLightType(int lightType) {
    lightInfo.type = lightType;
}

void SceneLight::setLightImportance(int newImportance) {
	lightInfo.importance = newImportance;
}

int SceneLight::getLightImportance() const {
	return lightInfo.importance;
}

void SceneLight::enableShadows(bool val, unsigned int resolution) {
        // RENDERER_TODO
    /*
	if(val) {
        if(zBufferTexture) {
            CoreServices::getInstance()->getMaterialManager()->deleteTexture(zBufferTexture);
        }
        CoreServices::getInstance()->getRenderer()->createRenderTextures(NULL, &zBufferTexture, resolution, resolution, false);
		if(!spotCamera) {
			spotCamera = new Camera(parentScene);
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
*/
}

bool SceneLight::areShadowsEnabled() const {
	return lightInfo.shadowsEnabled;
}

void SceneLight::setAttenuation(Number constantAttenuation, Number linearAttenuation, Number quadraticAttenuation) {
	lightInfo.constantAttenuation = constantAttenuation;
	lightInfo.linearAttenuation = linearAttenuation;
	lightInfo.quadraticAttenuation = quadraticAttenuation;
}			


void SceneLight::setIntensity(Number newIntensity) {
	lightInfo.intensity = newIntensity;
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
        // RENDERER_TODO
    /*
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
     */
}

LightInfo SceneLight::getLightInfo() const {
    return lightInfo;
}

Entity *SceneLight::Clone(bool deepClone, bool ignoreEditorOnly) const {
    SceneLight *newLight = new SceneLight(lightInfo.type, NULL, lightInfo.intensity, lightInfo.constantAttenuation, lightInfo.linearAttenuation, lightInfo.quadraticAttenuation);
    applyClone(newLight, deepClone, ignoreEditorOnly);
    return newLight;
}

void SceneLight::applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const {
    Entity::applyClone(clone, deepClone, ignoreEditorOnly);
    SceneLight *cloneLight = (SceneLight*) clone;
    
    cloneLight->setAttenuation(lightInfo.constantAttenuation, lightInfo.linearAttenuation, lightInfo.quadraticAttenuation);
    cloneLight->setIntensity(lightInfo.intensity);
    cloneLight->setDiffuseLightColor(lightInfo.diffuseColor.r, lightInfo.diffuseColor.g, lightInfo.diffuseColor.b);
    cloneLight->setSpecularLightColor(lightInfo.specularColor.r, lightInfo.specularColor.g, lightInfo.specularColor.b, lightInfo.specularColor.a);
    cloneLight->enableShadows(lightInfo.shadowsEnabled, shadowMapRes);
    cloneLight->setShadowMapFOV(shadowMapFOV);
    cloneLight->setSpotlightProperties(lightInfo.spotlightCutoff, lightInfo.spotlightExponent);
    cloneLight->setLightType(lightInfo.type);
}

Number SceneLight::getConstantAttenuation() const {
    return lightInfo.constantAttenuation;
}

Number SceneLight::getLinearAttenuation() const {
    return lightInfo.linearAttenuation;
}

Number SceneLight::getQuadraticAttenuation() const {
    return lightInfo.quadraticAttenuation;
}

void SceneLight::setSpotlightProperties(Number spotlightCutoff, Number spotlightExponent) {
    lightInfo.spotlightCutoff = spotlightCutoff;
    lightInfo.spotlightExponent = spotlightExponent;
}

Number SceneLight::getSpotlightCutoff() const {
    return lightInfo.spotlightCutoff;
}

Number SceneLight::getSpotlightExponent() const{
    return lightInfo.spotlightExponent;
}

Scene *SceneLight::getParentScene() const {
    return parentScene;
}

int SceneLight::getLightType() const {
    return lightInfo.type;
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
	return lightInfo.lightViewMatrix;
}

Texture *SceneLight::getZBufferTexture() const {
	return lightInfo.shadowMapTexture;
}

Number SceneLight::getIntensity() const {
	return lightInfo.intensity;
}

int SceneLight::getType() const {
	return lightInfo.type;
}
