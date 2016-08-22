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

#include "polycode/core/PolyScene.h"
#include "polycode/core/PolyCamera.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyMaterial.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyResource.h"
#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyInputEvent.h"
#include "polycode/core/PolySceneMesh.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyRay.h"

using std::vector;
using namespace Polycode;

Scene::Scene(Core *core) : core(core), EventDispatcher() {
	initScene(SCENE_3D);
}

Scene::Scene(Core *core, int sceneType) : core(core), EventDispatcher() {
	initScene(sceneType);
}

void Scene::initScene(int sceneType) {
	rootEntity.setContainerScene(this);
	this->sceneType = sceneType;
	defaultCamera = new Camera();
	activeCamera = defaultCamera;
	overrideMaterial = NULL;
	enabled = true;
	clearColor.setColor(0.13f,0.13f,0.13f,1.0f); 
	ambientColor.setColor(0.0,0.0,0.0,1.0); 
	useClearColor = false;
	useClearDepth = true;
	ownsChildren = false;
	remapMouse = false;
	_doVisibilityChecking = true;
	constrainPickingToViewport = true;
	setSceneType(sceneType);	
	core->addEventListener(this, Core::EVENT_CORE_RESIZE);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
	core->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);	
}

void Scene::setOverrideMaterial(std::shared_ptr<Material> material) {
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
			rootEntity.setPositionY(-core->getYRes());
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

void Scene::setEnabled(bool enabled) {
	this->enabled = enabled;
}

bool Scene::isEnabled() {
	return enabled;
}

void Scene::Update(Number elapsed) {
	rootEntity.updateEntityMatrix();
	rootEntity.doUpdates(elapsed);
}

void Scene::fixedUpdate() {
	rootEntity.updateEntityMatrix();
	rootEntity.doFixedUpdates();
}

Scene::~Scene() {
	core->getInput()->removeAllHandlersForListener(this);
	core->removeAllHandlersForListener(this);	
	delete defaultCamera;
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

void Scene::Render(RenderFrame *frame, Camera *targetCamera, std::shared_ptr<RenderBuffer> targetFramebuffer, std::shared_ptr<Material> overrideMaterial, bool shadowMapPass) {
	if(!targetCamera && !activeCamera)
		return;
	
    if(!targetCamera) {
		targetCamera = activeCamera;
    }
    
	if(targetFramebuffer) {
		targetCamera->setViewport(Polycode::Rectangle(0.0, 0.0, targetFramebuffer->getWidth(), targetFramebuffer->getHeight()));
	} else {
		targetCamera->setViewport(frame->viewport);
	}
	
	GPUDrawBuffer *drawBuffer = new GPUDrawBuffer();
	drawBuffer->renderFrame = frame;
	drawBuffer->clearColor = clearColor;
	drawBuffer->clearColorBuffer = useClearColor;
	drawBuffer->clearDepthBuffer = useClearDepth;
	drawBuffer->targetFramebuffer = targetFramebuffer;
	drawBuffer->viewport = targetCamera->getViewport();
	drawBuffer->backingResolutionScale = Vector2(1.0, 1.0);	
    drawBuffer->userData = (void*) this;
    drawBuffer->shadowMapPass = shadowMapPass;
    
	if(overrideMaterial) {
		drawBuffer->globalMaterial = overrideMaterial;
	} else {
		drawBuffer->globalMaterial = this->overrideMaterial;
	}
		
	drawBuffer->projectionMatrix = targetCamera->createProjectionMatrix();
	drawBuffer->viewMatrix = targetCamera->getConcatenatedMatrix().Inverse();
	drawBuffer->cameraMatrix = targetCamera->getConcatenatedMatrix();

	/*
	if(_doVisibilityChecking) {
		targetCamera->buildFrustumPlanes();
		setEntityVisibility(&rootEntity, targetCamera);
	}
*/
	rootEntity.transformAndRender(drawBuffer, NULL);
	frame->addDrawBuffer(drawBuffer);
}

Ray Scene::projectRayFromCameraAndViewportCoordinate(Camera *camera, Vector2 coordinate) {

	Polycode::Rectangle viewport = camera->getViewport();
	
	if(remapMouse) {
		viewport.x = sceneMouseRect.x * core->getRenderer()->getBackingResolutionScaleX();
		viewport.y = sceneMouseRect.y * core->getRenderer()->getBackingResolutionScaleY();
	}
	
	Vector3 dir =  camera->projectRayFrom2DCoordinate(Vector2(coordinate.x *  core->getRenderer()->getBackingResolutionScaleX(), coordinate.y	* core->getRenderer()->getBackingResolutionScaleY()), viewport);
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
			rootEntity.setPositionY(-core->getYRes());
		}
	} else if(event->getDispatcher() == core->getInput() && rootEntity.processInputEvents) {
		InputEvent *inputEvent = (InputEvent*) event;
		
		if(constrainPickingToViewport) {
			Polycode::Rectangle v = activeCamera->getViewport();
			if(remapMouse) {
				v.x = sceneMouseRect.x;
				v.y = sceneMouseRect.y;
			}
			
			if(inputEvent->mousePosition.x < v.x || inputEvent->mousePosition.x > v.x+(v.w / core->getRenderer()->getBackingResolutionScaleX()) || inputEvent->mousePosition.y < v.y || inputEvent->mousePosition.y > v.y + (v.h/core->getRenderer()->getBackingResolutionScaleY())) {
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

