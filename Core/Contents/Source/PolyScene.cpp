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
#include "PolyInputEvent.h"
#include "PolySceneMesh.h"
#include "PolyRay.h"
#include "PolySceneManager.h"

using std::vector;
using namespace Polycode;

Scene::Scene() : EventDispatcher() {
	initScene(SCENE_3D, false);
}

Scene::Scene(int sceneType, bool virtualScene) : EventDispatcher() {
	initScene(sceneType, virtualScene);
}

void Scene::initScene(int sceneType, bool virtualScene) {

	core = CoreServices::getInstance()->getCore();
	this->sceneType = sceneType;
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
	renderer = CoreServices::getInstance()->getRenderer();
	rootEntity.setRenderer(renderer);
	if (!isSceneVirtual) {
		CoreServices::getInstance()->getSceneManager()->addScene(this);
	}
	
	switch(sceneType) {
		case SCENE_2D:
			printf("WHAT\n");
			defaultCamera->setClippingPlanes(-100.0, 100.0);
			defaultCamera->setOrthoMode(true, CoreServices::getInstance()->getCore()->getXRes(),CoreServices::getInstance()->getCore()->getYRes());	
		break;
		case SCENE_2D_TOPLEFT:
			defaultCamera->setClippingPlanes(-100.0, 100.0);
			defaultCamera->setOrthoMode(true, 0,0);
			defaultCamera->topLeftOrtho = true;
			rootEntity.setInverseY(true);
		break;
		case SCENE_3D:
			defaultCamera->setClippingPlanes(1.0, 1000.0);
		break;		
	}
	
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);	
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
	if(sceneType == SCENE_2D_TOPLEFT) {
		rootEntity.setPositionY(-CoreServices::getInstance()->getCore()->getYRes());
	}
	rootEntity.doUpdates();
}

Scene::~Scene() {
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

void Scene::addEntity(Entity *entity) {
	rootEntity.addChild(entity);
}

void Scene::addChild(Entity *entity) {
	addEntity(entity);
}

void Scene::removeEntity(Entity *entity) {
	rootEntity.removeChild(entity);
}

Camera *Scene::getDefaultCamera() {
	return defaultCamera;
}

void Scene::Render(Camera *targetCamera) {	
	if(!targetCamera && !activeCamera)
		return;
	
	if(!targetCamera)
		targetCamera = activeCamera;
		
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
		if(light->areShadowsEnabled()) {
			if(light->getType() == SceneLight::SPOT_LIGHT) {
//				textureMatrix.identity();
				
				Matrix4 matTexAdj(0.5f,	0.0f,	0.0f,	0.0f,
								  0.0f,	0.5f,	0.0f,	0.0f,
								  0.0f,	0.0f,	0.5f,	0.0f,
								  0.5f,	0.5f,	0.5f,	1.0f );
				
								
				light->renderDepthMap(this);
				textureMatrix = light->getLightViewMatrix() * matTexAdj;				
				matrixPtr = &textureMatrix;				
			//	CoreServices::getInstance()->getRenderer()->addShadowMap(light->getZBufferTexture());
				shadowMapTexture = light->getZBufferTexture();
			}
		}
		
		position = light->getPosition();
		if(light->getParentEntity() != NULL) {
			position = light->getParentEntity()->getConcatenatedMatrix() * position;			
		}
		CoreServices::getInstance()->getRenderer()->addLight(light->getLightImportance(), position, direction, light->getLightType(), light->lightColor, light->specularLightColor, light->getConstantAttenuation(), light->getLinearAttenuation(), light->getQuadraticAttenuation(), light->getIntensity(), light->getSpotlightCutoff(), light->getSpotlightExponent(), light->areShadowsEnabled(), matrixPtr, shadowMapTexture);
	}	
		
	targetCamera->doCameraTransform();
	targetCamera->buildFrustumPlanes();
	
	CoreServices::getInstance()->getRenderer()->enableFog(fogEnabled);	
	if(fogEnabled) {
		CoreServices::getInstance()->getRenderer()->setFogProperties(fogMode, fogColor, fogDensity, fogStartDepth, fogEndDepth);
	} else {
		CoreServices::getInstance()->getRenderer()->setFogProperties(fogMode, fogColor, 0.0, fogStartDepth, fogEndDepth);	
	}
	
	
	rootEntity.updateEntityMatrix();
	rootEntity.transformAndRender();		
}


void Scene::RenderDepthOnly(Camera *targetCamera) {
	
	CoreServices::getInstance()->getRenderer()->cullFrontFaces(true);

	targetCamera->rebuildTransformMatrix();	
	targetCamera->doCameraTransform();	
	targetCamera->buildFrustumPlanes();
	
	CoreServices::getInstance()->getRenderer()->setTexture(NULL);
	CoreServices::getInstance()->getRenderer()->enableShaders(false);
	
	
	rootEntity.updateEntityMatrix();
	rootEntity.transformAndRender();	
	
	CoreServices::getInstance()->getRenderer()->enableShaders(true);
	CoreServices::getInstance()->getRenderer()->cullFrontFaces(false);	
}

void Scene::handleEvent(Event *event) {
	if(event->getDispatcher() == core->getInput() && rootEntity.processInputEvents) {
		InputEvent *inputEvent = (InputEvent*) event;
		Vector3 dir =  renderer->projectRayFrom2DCoordinate(inputEvent->mousePosition.x, inputEvent->mousePosition.y, activeCamera->getConcatenatedMatrix(), activeCamera->getProjectionMatrix());				
		Vector3 pos;
		
		
		switch(sceneType) {
			case SCENE_2D:
			{
				Number orthoSizeX = activeCamera->getOrthoSizeX();
				Number orthoSizeY = activeCamera->getOrthoSizeY();			
				pos = Vector3(((inputEvent->mousePosition.x/(Number)core->getXRes())*orthoSizeX) - (orthoSizeX*0.5), (((core->getYRes()-inputEvent->mousePosition.y)/(Number)core->getYRes())*orthoSizeY) - (orthoSizeY*0.5), 0.0);
				pos = activeCamera->getConcatenatedMatrix() * pos;	
			}
			break;
			case SCENE_2D_TOPLEFT:
				pos = Vector3(inputEvent->mousePosition.x, core->getYRes()-inputEvent->mousePosition.y, 0.0);
				pos = activeCamera->getConcatenatedMatrix() * pos;			
			break;
			case SCENE_3D:
				pos = activeCamera->getConcatenatedMatrix().getPosition();
			break;		
		}
				
		Ray ray(pos, dir);
		
		switch(inputEvent->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				rootEntity.onMouseDown(ray, inputEvent->mouseButton, inputEvent->timestamp);
			break;
			case InputEvent::EVENT_MOUSEMOVE:
				rootEntity.onMouseMove(ray, inputEvent->timestamp);
			break;
			case InputEvent::EVENT_MOUSEUP:
				rootEntity.onMouseUp(ray, inputEvent->mouseButton, inputEvent->timestamp);
			break;
			case InputEvent::EVENT_MOUSEWHEEL_UP:
				rootEntity.onMouseWheelUp(ray, inputEvent->timestamp);
			break;
			case InputEvent::EVENT_MOUSEWHEEL_DOWN:
				rootEntity.onMouseWheelDown(ray,inputEvent->timestamp);	
			break;	
		}
	}
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

