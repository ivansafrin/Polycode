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
#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyScenePrimitive.h"
#include "polycode/core/PolyTexture.h"
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
    
    shadowMapRenderBuffer = NULL;
    
	shadowMapFOV = 60.0f;
	lightInfo.shadowMapTexture = NULL;
	spotCamera = NULL;
	this->parentScene = parentScene;
	lightInfo.shadowsEnabled = false;
	lightInfo.diffuseColor.setColor(1.0f,1.0f,1.0f,1.0f);
	setSpotlightProperties(40,0.1);
	
    unlitMaterial = (Material*) Services()->getResourceManager()->getGlobalPool()->getResource(Resource::RESOURCE_MATERIAL, "Unlit");
    
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

	if(val) {
        if(shadowMapRenderBuffer) {
            Services()->getRenderer()->destroyRenderBuffer(shadowMapRenderBuffer);
        }
        
        shadowMapRenderBuffer = Services()->getRenderer()->createRenderBuffer(resolution, resolution, true, false);
        
		if(!spotCamera) {
			spotCamera = new Camera(parentScene);
            spotCamera->editorOnly = true;
            spotCamera->setClippingPlanes(0.01, 50.0);
			addChild(spotCamera);	
		}
        
		shadowMapRes = resolution;
		lightInfo.shadowsEnabled = true;
	} else {
		lightInfo.shadowsEnabled = false;
        if(shadowMapRenderBuffer) {
            Services()->getRenderer()->destroyRenderBuffer(shadowMapRenderBuffer);
        }
	}
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
    
    if(shadowMapRenderBuffer) {
        Services()->getRenderer()->destroyRenderBuffer(shadowMapRenderBuffer);
    }
    
    if(!ownsChildren) {
        delete spotCamera;
    }
    
    if(parentScene) {
        parentScene->removeLight(this);
    }
}

unsigned int SceneLight::getShadowMapResolution() const {
    return shadowMapRes;
}

void SceneLight::renderDepthMap(Scene *scene) {
    if(!unlitMaterial) {
        return;
    }
    spotCamera->setFOV(shadowMapFOV);
    spotCamera->setViewport(Polycode::Rectangle(0, 0, shadowMapRes, shadowMapRes));
    scene->Render(spotCamera, shadowMapRenderBuffer, unlitMaterial, false);
    
    Matrix4 matTexAdj(0.5f,	0.0f,	0.0f,	0.0f,
                      0.0f,	0.5f,	0.0f,	0.0f,
                      0.0f,	0.0f,	0.5f,	0.0f,
                      0.5f,	0.5f,	0.5f,	1.0f);
    
    lightInfo.lightViewMatrix = getConcatenatedMatrix().Inverse() *  spotCamera->getProjectionMatrix() * matTexAdj;
    lightInfo.shadowMapTexture = shadowMapRenderBuffer->depthTexture;
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

Texture *SceneLight::getZBufferTexture() const {
	return lightInfo.shadowMapTexture;
}

Number SceneLight::getIntensity() const {
	return lightInfo.intensity;
}

int SceneLight::getType() const {
	return lightInfo.type;
}
