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

using namespace Polycode;

SceneLight::SceneLight(int type, Scene *parentScene, Number intensity, Number constantAttenuation, Number linearAttenuation, Number quadraticAttenuation) : SceneEntity() {
	this->type = type;
	this->intensity = intensity;
	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
	
	spotlightCutoff = 40;
	spotlightExponent = 10;
		
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
	
	/*
	if(type == SceneLight::SPOT_LIGHT) {
		lightShape = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 3, 1.0, 8);
		lightShape->Translate(0,0,-1.5);
		lightShape->setPitch(90.0);
		lightShape->setColor(1.0,1.0,0.0, 0.75);
		lightShape->renderWireframe = true;
		addChild(lightShape);		
	} else {
		lightShape = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.5, 0.5, 0.5);
		lightShape->setColor(1.0,1.0,0.0, 0.75);
		lightShape->renderWireframe = true;
		addChild(lightShape);		
	}
	lightShape->castShadows = false;
	lightShape->visible = false;
	*/
	
	lightShape = NULL;
}

void SceneLight::enableDebugDraw(bool val) {
	if(lightShape) {
		lightShape->visible = val;
	}
}

void SceneLight::enableShadows(bool val, Number resolution) {
	if(val) {
		if(!zBufferTexture) {
			CoreServices::getInstance()->getRenderer()->createRenderTextures(NULL, &zBufferTexture, resolution, resolution);
		}
		if(!spotCamera) {
			spotCamera = new Camera(parentScene);
//			spotCamera->setPitch(-45.0f);
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

Number SceneLight::getIntensity() {
	return intensity;
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
