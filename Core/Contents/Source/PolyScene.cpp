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
	fogMode = Renderer::FOG_LINEAR;
    overrideMaterial = NULL;
	lightingEnabled = false;
	enabled = true;
	isSceneVirtual = virtualScene;	
	hasLightmaps = false;
	clearColor.setColor(0.13f,0.13f,0.13f,1.0f); 
	ambientColor.setColor(0.0,0.0,0.0,1.0);	
	useClearColor = false;
	useClearDepth = true;
	ownsChildren = false;
    remapMouse = false;
    _doVisibilityChecking = true;
    constrainPickingToViewport = true;
	renderer = CoreServices::getInstance()->getRenderer();
	rootEntity.setRenderer(renderer);
    CoreServices::getInstance()->getSceneManager()->addScene(this);
	
    setSceneType(sceneType);
	
    core->addEventListener(this, Core::EVENT_CORE_RESIZE);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);	
}

void Scene::setOverrideMaterial(Material *material) {
    overrideMaterial = material;
}

void Scene::setSceneType(int newType) {
    sceneType = newType;
	switch(sceneType) {
		case SCENE_2D:
			defaultCamera->setClippingPlanes(-100.0, 100.0);
			defaultCamera->setOrthoMode(true);
            defaultCamera->setOrthoSize(1.0, 1.0);
            break;
		case SCENE_2D_TOPLEFT:
			defaultCamera->setClippingPlanes(-100.0, 100.0);
			defaultCamera->setOrthoMode(true);
            defaultCamera->setOrthoSizeMode(Camera::ORTHO_SIZE_VIEWPORT);
			defaultCamera->topLeftOrtho = true;
			rootEntity.setInverseY(true);
            rootEntity.setPositionY(-CoreServices::getInstance()->getCore()->getYRes());            
            break;
		case SCENE_3D:
			defaultCamera->setClippingPlanes(1.0, 1000.0);
            break;		
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
    rootEntity.updateEntityMatrix();
	rootEntity.doUpdates();
}

void Scene::fixedUpdate() {
    rootEntity.updateEntityMatrix();
	rootEntity.doFixedUpdates();
}

Scene::~Scene() {
	core->getInput()->removeAllHandlersForListener(this);
    core->removeAllHandlersForListener(this);
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

void Scene::doVisibilityChecking(bool val) {
    _doVisibilityChecking = val;
    if(!_doVisibilityChecking) {
        setEntityVisibilityBool(&rootEntity, true);
    }
}

bool Scene::doesVisibilityChecking() {
    return _doVisibilityChecking;
}

void Scene::setEntityVisibilityBool(Entity *entity, bool val) {
    entity->rendererVis = val;
    for(int i=0; i < entity->getNumChildren(); i++) {
        setEntityVisibilityBool(entity->getChildAtIndex(i), val);
    }
}

void Scene::setEntityVisibility(Entity *entity, Camera *camera) {
    if(camera->frustumCulling) {
        entity->recalculateAABB();
        entity->rendererVis = camera->isAABBInFrustum(entity->getWorldAABB());
    } else {
        entity->rendererVis = true;
    }
    for(int i=0; i < entity->getNumChildren(); i++) {
        setEntityVisibility(entity->getChildAtIndex(i), camera);
    }
}

void Scene::Render(Camera *targetCamera) {	
	if(!targetCamera && !activeCamera)
		return;
    
    renderer->setOverrideMaterial(overrideMaterial);
	
	if(!targetCamera)
		targetCamera = activeCamera;
		
	//make these the closest
	
	Matrix4 textureMatrix;
	Matrix4 *matrixPtr;
	
	
	targetCamera->rebuildTransformMatrix();
		
	if(useClearColor) {
		CoreServices::getInstance()->getRenderer()->setClearColor(clearColor.r,clearColor.g,clearColor.b, clearColor.a);	
	}
	if (useClearColor || useClearDepth) {
		CoreServices::getInstance()->getRenderer()->clearScreen(useClearColor, useClearDepth);
	}
	
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
		direction.y = 0.0;
		direction.z = -1.0;
		direction.Normalize();
		
		direction = light->getConcatenatedMatrix().rotateVector(direction);
		
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
    
	CoreServices::getInstance()->getRenderer()->enableFog(fogEnabled);
	if(fogEnabled) {
		CoreServices::getInstance()->getRenderer()->setFogProperties(fogMode, fogColor, fogDensity, fogStartDepth, fogEndDepth);
	} else {
		CoreServices::getInstance()->getRenderer()->setFogProperties(fogMode, fogColor, 0.0, fogStartDepth, fogEndDepth);	
	}
	
    if(_doVisibilityChecking) {
        targetCamera->buildFrustumPlanes();
        setEntityVisibility(&rootEntity, targetCamera);
    }
	rootEntity.transformAndRender();		
}


void Scene::RenderDepthOnly(Camera *targetCamera) {
	
	CoreServices::getInstance()->getRenderer()->cullFrontFaces(true);

	targetCamera->rebuildTransformMatrix();	
	targetCamera->doCameraTransform();
	
	CoreServices::getInstance()->getRenderer()->setTexture(NULL);
	CoreServices::getInstance()->getRenderer()->enableShaders(false);
		
    if(_doVisibilityChecking) {
        targetCamera->buildFrustumPlanes();
        setEntityVisibility(&rootEntity, targetCamera);
    }
	rootEntity.transformAndRender();	
	
	CoreServices::getInstance()->getRenderer()->enableShaders(true);
	CoreServices::getInstance()->getRenderer()->cullFrontFaces(false);	
}

Ray Scene::projectRayFromCameraAndViewportCoordinate(Camera *camera, Vector2 coordinate) {

	Polycode::Rectangle viewport = camera->getViewport();
    
    if(remapMouse) {
        viewport.x = sceneMouseRect.x * renderer->getBackingResolutionScaleX();
        viewport.y = (core->getYRes() - (sceneMouseRect.y + sceneMouseRect.h)) * renderer->getBackingResolutionScaleY();
    }
    
	Vector3 dir =  renderer->projectRayFrom2DCoordinate(coordinate.x *  renderer->getBackingResolutionScaleX(), coordinate.y  * renderer->getBackingResolutionScaleY(), camera->getConcatenatedMatrix(), camera->getProjectionMatrix(), viewport);
	Vector3 pos;
    
	switch(sceneType) {
		case SCENE_2D:
		{
            
            Number orthoSizeX = camera->getOrthoSizeX();
            Number orthoSizeY = camera->getOrthoSizeY();

            switch(camera->getProjectionMode()) {
                case Camera::ORTHO_SIZE_LOCK_HEIGHT:
                    orthoSizeX = orthoSizeY * (viewport.w/viewport.h);
                    break;
                case Camera::ORTHO_SIZE_LOCK_WIDTH:
                    orthoSizeY = orthoSizeX * (viewport.h/viewport.w);
                    break;
                case Camera::ORTHO_SIZE_VIEWPORT:
                    orthoSizeX = camera->getViewport().x;
                    orthoSizeY = camera->getViewport().y;
                break;
            }
            
            Vector2 remappedMouse = Vector2(coordinate.x, coordinate.y);
            Vector2 screenSize = Vector2(core->getXRes(), core->getYRes());
            if(remapMouse) {
                remappedMouse.x = coordinate.x - sceneMouseRect.x;
                remappedMouse.y = coordinate.y - sceneMouseRect.y;
                screenSize = Vector2(sceneMouseRect.w, sceneMouseRect.h);
            }
            
			pos = Vector3(((remappedMouse.x/screenSize.x)*orthoSizeX) - (orthoSizeX*0.5), (((screenSize.y-remappedMouse.y)/screenSize.y)*orthoSizeY) - (orthoSizeY*0.5), 0.0);
            
			pos = camera->getConcatenatedMatrix() * pos;
            
		}
		break;
		case SCENE_2D_TOPLEFT:
			pos = Vector3(coordinate.x, core->getYRes()-coordinate.y, 0.0);
			pos = camera->getConcatenatedMatrix() * pos;			
		break;
		case SCENE_3D:
			pos = camera->getConcatenatedMatrix().getPosition();
		break;		
	}

	return Ray(pos, dir);
}


void Scene::handleEvent(Event *event) {
    if(event->getDispatcher() == core) {
        if(sceneType == SCENE_2D_TOPLEFT) {
            rootEntity.setPositionY(-CoreServices::getInstance()->getCore()->getYRes());
        }
    } else if(event->getDispatcher() == core->getInput() && rootEntity.processInputEvents) {
		InputEvent *inputEvent = (InputEvent*) event;

        if(constrainPickingToViewport) {
            Polycode::Rectangle v = activeCamera->getViewport();
            if(remapMouse) {
                v.x = sceneMouseRect.x;
                v.y = sceneMouseRect.y;
            }            
            if(inputEvent->mousePosition.x < v.x || inputEvent->mousePosition.x > v.x+(v.w / renderer->getBackingResolutionScaleX()) || inputEvent->mousePosition.y < v.y || inputEvent->mousePosition.y > v.y + (v.h/renderer->getBackingResolutionScaleY())) {
                    return;
            }
        }
        
		Ray ray = projectRayFromCameraAndViewportCoordinate(activeCamera, inputEvent->mousePosition);
		
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

int Scene::getNumLights() {
	return lights.size();
}

SceneLight *Scene::getLight(int index) {
	return lights[index];
}

