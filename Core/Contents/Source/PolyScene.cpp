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

#include "PolyScene.h"
#include "OSBasics.h"
#include "PolyCamera.h"
#include "PolyCoreServices.h"
#include "PolyLogger.h"
#include "PolyMaterial.h"
#include "PolyMesh.h"
#include "PolyRenderer.h"
#include "PolyResource.h"
#include "PolyResourceManager.h"
#include "PolySceneLight.h"
#include "PolySceneMesh.h"
#include "PolySceneManager.h"

using std::vector;
using namespace Polycode;

Scene::Scene() : EventDispatcher() {
	defaultCamera = new Camera(this);
	activeCamera = defaultCamera;
	fogEnabled = false;
	lightingEnabled = false;
	enabled = true;
	isSceneVirtual = false;
	hasLightmaps = false;
	clearColor.setColor(0.13f,0.13f,0.13f,1.0f); 
	ambientColor.setColor(0.0,0.0,0.0,1.0);
	useClearColor = false;
	ownsChildren = false;
	CoreServices::getInstance()->getSceneManager()->addScene(this);	
}

Scene::Scene(bool virtualScene) : EventDispatcher() {
	defaultCamera = new Camera(this);
	activeCamera = defaultCamera;
	fogEnabled = false;
	lightingEnabled = false;
	enabled = true;
	isSceneVirtual = virtualScene;
	hasLightmaps = false;
	clearColor.setColor(0.13f,0.13f,0.13f,1.0f); 
	ambientColor.setColor(0.0,0.0,0.0,1.0);	
	useClearColor = false;
	ownsChildren = false;
	if (!isSceneVirtual) {
		CoreServices::getInstance()->getSceneManager()->addScene(this);
	}
}

void Scene::setActiveCamera(Camera *camera) {
	activeCamera = camera;
}

Camera *Scene::getActiveCamera() {
	return activeCamera;
}

void Scene::setVirtual(bool val) {
	isSceneVirtual = val;
}

bool Scene::isVirtual() {
	return isSceneVirtual;
}

void Scene::setEnabled(bool enabled) {
	this->enabled = enabled;
}

bool Scene::isEnabled() {
	return enabled;
}

void Scene::Update() {
	for(int i=0; i<entities.size();i++) {
		entities[i]->doUpdates();
		entities[i]->updateEntityMatrix();
	}
}

Scene::~Scene() {
	if(ownsChildren) {
		for(int i=0; i < entities.size(); i++) {
			delete entities[i];
		}
	}
	CoreServices::getInstance()->getSceneManager()->removeScene(this);
	delete defaultCamera;
}

void Scene::enableLighting(bool enable) {
	lightingEnabled = enable;
	CoreServices::getInstance()->getRenderer()->enableLighting(enable);
}



void Scene::enableFog(bool enable) {
	fogEnabled = enable;

}

void Scene::setFogProperties(int fogMode, Color color, Number density, Number startDepth, Number endDepth) {
	this->fogMode = fogMode;
	fogColor = color;
	fogDensity = density;
	fogStartDepth = startDepth;
	fogEndDepth = endDepth;

}

SceneEntity *Scene::getEntityAtScreenPosition(Number x, Number y) {
	for(int i =0; i< entities.size(); i++) {
		if(entities[i]->testMouseCollision(x,y)) {
			return entities[i];
		}
	}
	return NULL;
}

void Scene::addEntity(SceneEntity *entity) {
	entity->setRenderer(CoreServices::getInstance()->getRenderer());
	entities.push_back(entity);
}

void Scene::addChild(SceneEntity *entity) {
	addEntity(entity);
}

void Scene::removeEntity(SceneEntity *entity) {
	for(int i=0; i < entities.size(); i++) {
		if(entities[i] == entity) {
			entities.erase(entities.begin()+i);
			return;
		}
	}
}

Camera *Scene::getDefaultCamera() {
	return defaultCamera;
}

void Scene::Render(Camera *targetCamera) {

	if(!targetCamera && !activeCamera)
		return;

	if(!targetCamera)
		targetCamera = activeCamera;

	// prepare lights...
	for(int i=0; i<entities.size();i++) {
		entities[i]->updateEntityMatrix();
	}

	//make these the closest

	Matrix4 textureMatrix;
	Matrix4 *matrixPtr;


	targetCamera->rebuildTransformMatrix();

	if(useClearColor)
		CoreServices::getInstance()->getRenderer()->setClearColor(clearColor.r,clearColor.g,clearColor.b);

	CoreServices::getInstance()->getRenderer()->setAmbientColor(ambientColor.r,ambientColor.g,ambientColor.b);

	CoreServices::getInstance()->getRenderer()->clearLights();

	for(int i=0; i < lights.size(); i++) {
		SceneLight *light = lights[i];
		if(!light->enabled)
			continue;

		Vector3 direction;
		Vector3 position;
		matrixPtr = NULL;
		direction.x = 0;
		direction.y = 0;
		direction.z = -1;


		direction = light->getConcatenatedMatrix().rotateVector(direction);
		direction.Normalize();

		Texture *shadowMapTexture = NULL;
		if(light->areShadowsEnabled() && light->getType() == SceneLight::SPOT_LIGHT) {
//			textureMatrix.identity();
			
			Matrix4 matTexAdj(0.5f, 0.0f, 0.0f, 0.0f,
							  0.0f, 0.5f, 0.0f, 0.0f,
							  0.0f, 0.0f, 0.5f, 0.0f,
							  0.5f, 0.5f, 0.5f, 1.0f );


			light->renderDepthMap(this);
			textureMatrix = light->getLightViewMatrix() * matTexAdj;
			matrixPtr = &textureMatrix;
		//	CoreServices::getInstance()->getRenderer()->addShadowMap(light->getZBufferTexture());
			shadowMapTexture = light->getZBufferTexture();
		}

		position = light->getPosition();
		if(light->getParentEntity() != NULL) {
			position = light->getParentEntity()->getConcatenatedMatrix() * position;
		}
		CoreServices::getInstance()->getRenderer()->addLight(light->getLightImportance(), position, direction, light->getLightType(), light->lightColor, light->specularLightColor, light->getConstantAttenuation(), light->getLinearAttenuation(), light->getQuadraticAttenuation(), light->getIntensity(), light->getSpotlightCutoff(), light->getSpotlightExponent(), light->areShadowsEnabled(), matrixPtr, shadowMapTexture);
	}

	if(targetCamera->getOrthoMode()) {
		CoreServices::getInstance()->getRenderer()->_setOrthoMode(targetCamera->getOrthoSizeX(), targetCamera->getOrthoSizeY());
	}

	targetCamera->doCameraTransform();
	targetCamera->buildFrustumPlanes();

	CoreServices::getInstance()->getRenderer()->enableFog(fogEnabled);
	if(fogEnabled) {
		CoreServices::getInstance()->getRenderer()->setFogProperties(fogMode, fogColor, fogDensity, fogStartDepth, fogEndDepth);
	} else {
		CoreServices::getInstance()->getRenderer()->setFogProperties(fogMode, fogColor, 0.0, fogStartDepth, fogEndDepth);
	}


	for(int i=0; i<entities.size();i++) {
		if(entities[i]->getBBoxRadius() > 0) {
			if(targetCamera->isSphereInFrustum((entities[i]->getPosition()), entities[i]->getBBoxRadius()))
				entities[i]->transformAndRender();
		} else {
			entities[i]->transformAndRender();
		}
	}

	if(targetCamera->getOrthoMode()) {
		CoreServices::getInstance()->getRenderer()->setPerspectiveMode();
	}

}


void Scene::RenderDepthOnly(Camera *targetCamera) {

	CoreServices::getInstance()->getRenderer()->cullFrontFaces(true);
/*	
	for(int i=0; i<entities.size();i++) {
		entities[i]->doUpdates();
		entities[i]->updateEntityMatrix();
	}
*/	
	targetCamera->rebuildTransformMatrix();
	targetCamera->doCameraTransform();
	targetCamera->buildFrustumPlanes();

	CoreServices::getInstance()->getRenderer()->setTexture(NULL);
	CoreServices::getInstance()->getRenderer()->enableShaders(false);
	for(int i=0; i<entities.size();i++) {
		if(entities[i]->castShadows) {
			if(entities[i]->getBBoxRadius() > 0) {
				if(targetCamera->isSphereInFrustum((entities[i]->getPosition()), entities[i]->getBBoxRadius()))
					entities[i]->transformAndRender();
			} else {
				entities[i]->transformAndRender();
			}
		}
	}
	CoreServices::getInstance()->getRenderer()->enableShaders(true);
	CoreServices::getInstance()->getRenderer()->cullFrontFaces(false);
}

void Scene::addLight(SceneLight *light) {
	lights.push_back(light);
	addEntity(light);
}

void Scene::removeLight(SceneLight *light) {
	removeEntity(light);
	for(int i=0; i < lights.size(); i++) {
		if(lights[i] == light) {
			lights.erase(lights.begin()+i);
			return;
		}
	}
}

SceneLight *Scene::getNearestLight(Vector3 pos) {
	if(lights.size() > 0)
		return lights[0];
	else
		return NULL;
}

int Scene::getNumLights() {
	return lights.size();
}

SceneLight *Scene::getLight(int index) {
	return lights[index];
}

