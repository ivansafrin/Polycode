/*
 *  PolySceneLight.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/21/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolySceneLight.h"

using namespace Polycode;

SceneLight::SceneLight(int type, float intensity, float distance, Scene *parentScene) : SceneEntity() {
	this->type = type;
	this->intensity = intensity;
	this->distance = distance;
	this->depthWrite = false;
	lightMesh = new Mesh(Mesh::QUAD_MESH);
	lightMesh->createBox(0.1,0.1,0.1);
	bBoxRadius = lightMesh->getRadius();
	bBox = lightMesh->calculateBBox();
	shadowMapFOV = 70.0f;
	zBufferTexture = NULL;
	spotCamera = NULL;
	this->parentScene = parentScene;
	shadowsEnabled = false;
}

void SceneLight::enableShadows(bool val, float resolution) {
	if(val) {
		if(!zBufferTexture) {
			CoreServices::getInstance()->getRenderer()->createRenderTextures(NULL, &zBufferTexture, resolution, resolution);
		}
		if(!spotCamera) {
			spotCamera = new Camera(parentScene);
			spotCamera->setPitch(-90.0f);
			addEntity(spotCamera);	
		}
		shadowMapRes = resolution;
		shadowsEnabled = true;
	} else {
		shadowsEnabled = false;
	}
}

bool SceneLight::areShadowsEnabled() {
	return shadowsEnabled;
}

void SceneLight::setShadowMapFOV(float fov) {
	
}

SceneLight::~SceneLight() {
	printf("Destroying scene light...\n");
}

void SceneLight::renderDepthMap(Scene *scene) {
	CoreServices::getInstance()->getRenderer()->clearScreen();
	CoreServices::getInstance()->getRenderer()->pushMatrix();
	CoreServices::getInstance()->getRenderer()->loadIdentity();

	CoreServices::getInstance()->getRenderer()->setViewportSize(shadowMapRes, shadowMapRes, shadowMapFOV);	
	CoreServices::getInstance()->getRenderer()->bindFrameBufferTexture(zBufferTexture);	

	scene->RenderDepthOnly(spotCamera);
	
	lightViewMatrix = CoreServices::getInstance()->getRenderer()->getModelviewMatrix() *  CoreServices::getInstance()->getRenderer()->getProjectionMatrix();
	CoreServices::getInstance()->getRenderer()->unbindFramebuffers();
	CoreServices::getInstance()->getRenderer()->popMatrix();
	CoreServices::getInstance()->getRenderer()->setViewportSize(CoreServices::getInstance()->getCore()->getXRes(), CoreServices::getInstance()->getCore()->getYRes(), 45.0f);
}

Matrix4 SceneLight::getLightViewMatrix() {
	return lightViewMatrix;
}

Texture *SceneLight::getZBufferTexture() {
	return zBufferTexture;
}

float SceneLight::getIntensity() {
	return intensity;
}

float SceneLight::getDistance() {
	return distance;
}

void SceneLight::Render() {
/*
	CoreServices::getInstance()->getRenderer()->setTexture(NULL);
	CoreServices::getInstance()->getRenderer()->beginRenderOperation(lightMesh->getMeshType());
	for(int i=0; i < lightMesh->getPolygonCount(); i++) {
			CoreServices::getInstance()->getRenderer()->draw3DPolygon(lightMesh->getPolygon(i));
	}
	CoreServices::getInstance()->getRenderer()->endRenderOperation();	
	*/
}

int SceneLight::getType() {
	return type;
}
