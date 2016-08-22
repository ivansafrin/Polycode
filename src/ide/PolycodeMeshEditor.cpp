/*
 Copyright (C) 2012 by Ivan Safrin
 
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
 
#include "polycode/ide/PolycodeMeshEditor.h"

extern UIGlobalMenu *globalMenu;

PolycodeMeshEditor::PolycodeMeshEditor(Core *core, ResourcePool *pool) : PolycodeEditor(core, pool, true), localResourcePool(core, "", pool) {
	
	previewScene = new Scene(core, Scene::SCENE_3D);
	renderTexture = new SceneRenderTexture(512, 512, false);
	
	ownsChildren = true;

	previewScene->clearColor.setColor(0.2, 0.2, 0.2, 1.0);
	previewScene->useClearColor = true;
	
//	previewScene->ambientColor.setColor(0.0, 0.0, 0.0, 1.0);
				
	Number customFalloff = 0.006;
	mainLight = new SceneLight(SceneLight::POINT_LIGHT, 999999, customFalloff, customFalloff, customFalloff);
	previewScene->addChild(mainLight);

	secondLight = new SceneLight(SceneLight::POINT_LIGHT, 999999, customFalloff, customFalloff, customFalloff);
	previewScene->addChild(secondLight);
	
	mainLight->setPosition(9999, 9999, 9999);
	secondLight->setPosition(-9999, -9999, -9999);

	
	previewShape = new UIRect(core, pool, 256, 256);
	previewShape->setAnchorPoint(-1.0, -1.0, 0.0);	
	previewShape->setTexture(renderTexture->getTargetTexture());
	addChild(previewShape);

	previewBase = new Entity();
	previewScene->addChild(previewBase);
	
	previewMesh = NULL; 
	trackballCamera = new TrackballCamera(core->getInput(), previewScene->getDefaultCamera(), previewShape);
	trackballCamera->getTargetCamera()->setClippingPlanes(0.1, 1000.0);
	//trackballCamera->getTargetCamera()->setPosition(0.0, 0.0, 50.);
	trackballCamera->setOrbitingCenter(Vector3(0.0, 0.0, 0.0));
}

void PolycodeMeshEditor::Activate() {
	previewScene->enabled = true;
	renderTexture->enabled = true;
}

void PolycodeMeshEditor::Deactivate() {
	previewScene->enabled = false;
	renderTexture->enabled = false;
	
}

void PolycodeMeshEditor::Render(GPUDrawBuffer *buffer) {
	renderTexture->Render(buffer->renderFrame, previewScene, previewScene->getDefaultCamera());
}

void PolycodeMeshEditor::handleEvent(Event *event) {
}

PolycodeMeshEditor::~PolycodeMeshEditor() {
	resourcePool->removeAllHandlersForListener(this);
	previewScene->rootEntity.setOwnsChildrenRecursive(true);
	delete previewScene;
	delete renderTexture;
	delete trackballCamera;
}

bool PolycodeMeshEditor::openFile(OSFileEntry filePath) {
	previewMesh = new SceneMesh(&localResourcePool, filePath.fullPath);
	previewBase->addChild(previewMesh);
	previewMesh->setMaterial(resourcePool->getMaterial("Default"));
	PolycodeEditor::openFile(filePath);
	trackballCamera->setCameraDistance(previewMesh->getMesh()->getRadius() * 3.0);
	trackballCamera->setCameraPosition(trackballCamera->getOribitingCenter()+Vector3(0.0, 0.0, trackballCamera->getCameraDistance()));
	return true;
}

void PolycodeMeshEditor::Resize(int x, int y) {
	
	renderTexture->resizeRenderTexture(x, y-30);
	previewShape->setTexture(renderTexture->getTargetTexture());	
	previewShape->Resize(x, y-30);	
	previewShape->setPosition(0, 30);
	PolycodeEditor::Resize(x,y);
}

