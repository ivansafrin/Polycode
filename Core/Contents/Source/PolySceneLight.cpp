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
	bBoxRadius = lightMesh->getRadius();
	bBox = lightMesh->calculateBBox();
	shadowMapFOV = 60.0f;
	zBufferTexture = NULL;
	spotCamera = NULL;
	this->parentScene = parentScene;
	shadowsEnabled = false;
	lightColor.setColor(1.0f,1.0f,1.0f,1.0f);
	setSpotlightProperties(40,0.1);
	
	lightImportance = 0;
    
    debugDraw = false;
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

void SceneLight::enableDebugDraw(bool val) {
    debugDraw = val;
}

void SceneLight::enableShadows(bool val, unsigned int resolution) {
	if(val) {
        if(zBufferTexture) {
            CoreServices::getInstance()->getMaterialManager()->deleteTexture(zBufferTexture);
        }
        
        CoreServices::getInstance()->getRenderer()->createRenderTextures(NULL, &zBufferTexture, resolution, resolution, false);
		if(!spotCamera) {
			spotCamera = new Camera(parentScene);
//			spotCamera->setPitch(-45.0f);
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
	printf("Destroying scene light...\n");
}

unsigned int SceneLight::getShadowMapResolution() const {
    return shadowMapRes;
}

void SceneLight::renderDepthMap(Scene *scene) {
	CoreServices::getInstance()->getRenderer()->clearScreen();
	CoreServices::getInstance()->getRenderer()->pushMatrix();
	CoreServices::getInstance()->getRenderer()->loadIdentity();

	CoreServices::getInstance()->getRenderer()->setViewportSizeAndFOV(shadowMapRes, shadowMapRes, shadowMapFOV);	
	CoreServices::getInstance()->getRenderer()->bindFrameBufferTexture(zBufferTexture);	

	scene->RenderDepthOnly(spotCamera);
		
	lightViewMatrix = CoreServices::getInstance()->getRenderer()->getModelviewMatrix() *  CoreServices::getInstance()->getRenderer()->getProjectionMatrix();
	CoreServices::getInstance()->getRenderer()->unbindFramebuffers();
	CoreServices::getInstance()->getRenderer()->popMatrix();
	CoreServices::getInstance()->getRenderer()->setViewportSizeAndFOV(CoreServices::getInstance()->getCore()->getXRes(), CoreServices::getInstance()->getCore()->getYRes(), 45.0f);
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
