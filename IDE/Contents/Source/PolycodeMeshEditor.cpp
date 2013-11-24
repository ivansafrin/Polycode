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
 
#include "PolycodeMeshEditor.h"

extern UIGlobalMenu *globalMenu;

PolycodeMeshEditor::PolycodeMeshEditor() : PolycodeEditor(true){
	
	previewScene = new Scene(Scene::SCENE_3D, true);		
	renderTexture = new SceneRenderTexture(previewScene, previewScene->getDefaultCamera(), 512, 512);

	previewScene->clearColor.setColor(0.2, 0.2, 0.2, 1.0);	
	previewScene->useClearColor = true;
	
//	previewScene->ambientColor.setColor(0.0, 0.0, 0.0, 1.0);
				
	mainLight = new SceneLight(SceneLight::AREA_LIGHT, previewScene, 1590.0);
	mainLight->setPosition(-10,10,10);
	previewScene->addLight(mainLight);

	secondLight = new SceneLight(SceneLight::AREA_LIGHT, previewScene, 1590.0);
	secondLight->setPosition(10,-10,10);
	previewScene->addLight(secondLight);

	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));		
	
	previewShape = new UIRect(256, 256);
	previewShape->setAnchorPoint(-1.0, -1.0, 0.0);	
	previewShape->setTexture(renderTexture->getTargetTexture());
	addChild(previewShape);
	
	
	UILabel *label = new UILabel("MATERIAL", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(10, 3);
	
	materialDropDown = new UIComboBox(globalMenu, 200);
	addChild(materialDropDown);
	materialDropDown->setPosition(100, 3);

	label = new UILabel("LIGHTS", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(320, 3);

	lightsSlider = new UIHSlider(0.0, 5000, 200);
	addChild(lightsSlider);
	lightsSlider->setSliderValue(1000.0);
	lightsSlider->setPosition(380, 8);	
	lightsSlider->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	reloadMaterials();

	previewBase = new Entity();
	previewScene->addChild(previewBase);

	CoreServices::getInstance()->getResourceManager()->dispatchChangeEvents = true;	
	CoreServices::getInstance()->getResourceManager()->addEventListener(this, Event::CHANGE_EVENT);
	
	previewMesh = NULL;	
	trackballCamera = new TrackballCamera(previewScene->getDefaultCamera(), previewShape);
	
}

void PolycodeMeshEditor::reloadMaterials() {

	Resource *selectedMaterial = NULL;
		
	if(materialDropDown->getSelectedItem()) {
		selectedMaterial = (Resource*) materialDropDown->getSelectedItem()->data;
	}
	
	materialDropDown->removeAllHandlersForListener(this);
	
	materialDropDown->clearItems();
	std::vector<Resource*> materials = CoreServices::getInstance()->getResourceManager()->getResources(Resource::RESOURCE_MATERIAL);
	for(int i=0; i < materials.size(); i++) {
		materialDropDown->addComboItem(materials[i]->getResourceName(), (void*) materials[i]);
		if(selectedMaterial == materials[i]) {
			materialDropDown->setSelectedIndex(i);
		}
	}
	
	materialDropDown->addEventListener(this, UIEvent::CHANGE_EVENT);	
}

void PolycodeMeshEditor::handleEvent(Event *event) {
	
	if(event->getDispatcher() == lightsSlider) {
		mainLight->setIntensity(lightsSlider->getSliderValue());
		secondLight->setIntensity(lightsSlider->getSliderValue());		
	} else if(event->getDispatcher() == materialDropDown) {
		if(previewMesh) {
			previewMesh->setMaterial((Material*)materialDropDown->getSelectedItem()->data);
		}
	} else if(event->getDispatcher() == CoreServices::getInstance()->getResourceManager()) {
		reloadMaterials();
	}
}

PolycodeMeshEditor::~PolycodeMeshEditor() {
    CoreServices::getInstance()->getResourceManager()->removeAllHandlersForListener(this);
}

bool PolycodeMeshEditor::openFile(OSFileEntry filePath) {
	previewMesh = new SceneMesh(filePath.fullPath);
	previewBase->addChild(previewMesh);
	previewMesh->setMaterialByName("Default");
	PolycodeEditor::openFile(filePath);

	previewMesh->alphaTest = true;
	CoreServices::getInstance()->getRenderer()->alphaTestValue = 0.9;
	
	Number radius = previewMesh->getBBoxRadius();
				
	mainLight->setPosition(-(radius*3),(radius*3),(radius*3));
	secondLight->setPosition((radius*3),-(radius*3),(radius*3));
	
	trackballCamera->setCameraDistance(radius*3);
	return true;
}

void PolycodeMeshEditor::Resize(int x, int y) {
	headerBg->Resize(x, 30);	
	renderTexture->resizeRenderTexture(x, y-30);
	previewShape->setTexture(renderTexture->getTargetTexture());	
	previewShape->Resize(x, y-30);	
	previewShape->setPosition(0, 30);
}

