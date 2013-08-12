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
 
#include "PolycodeScreenEditor.h"
#include "PolycodeFrame.h"

extern UIColorPicker *globalColorPicker;
extern PolycodeFrame *globalFrame;
extern UIGlobalMenu *globalMenu;

PolycodeScreenEditorActionDataEntry::PolycodeScreenEditorActionDataEntry(Entity *entity) {
	this->entity = entity;
	this->parentEntity = (Entity*)entity->getParentEntity();
}

PolycodeScreenEditorActionDataEntry::PolycodeScreenEditorActionDataEntry(Vector3 vec3, Number number) {
	this->vec3 = vec3;
	this->number = number;	
}

PolycodeScreenEditorActionDataEntry::PolycodeScreenEditorActionDataEntry(Vector3 vec3) {
	this->vec3 = vec3;
}

PolycodeScreenEditorActionDataEntry::PolycodeScreenEditorActionDataEntry(Number number) {
	this->number = number;
}

EntityNameDisplay::EntityNameDisplay(Entity *targetEntity) : Entity() {
	label = new SceneLabel(targetEntity->id, 10, "mono");
	label->setColor(1.0, 1.0, 0.0, 1.0);
	label->setPosition(10, -20);
	
	tagsLabel = new SceneLabel(targetEntity->id, 10, "mono");
	tagsLabel->setColor(1.0, 0.0, 1.0, 1.0);
	tagsLabel->setPosition(10, 20);

	
	addChild(label);
	addChild(tagsLabel);
	
	editorOnly = true;
	this->targetEntity = targetEntity;
	
}

void EntityNameDisplay::Update() {
	label->setText(targetEntity->id);
	
	String tagString = "";
	for(int i=0; i < targetEntity->getNumTags(); i++) {
		if(i != 0) {
			tagString += ",";
		}
		tagString += targetEntity->getTagAtIndex(i);
	}
	tagsLabel->setText(tagString);
	
}

EntityNameDisplay::~EntityNameDisplay() {

}

EntityTreeView::EntityTreeView(Entity *rootEntity) : UIElement() {

	this->rootEntity = rootEntity;

	targetLayer = NULL;

	bg = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE,10,10);
	addChild(bg);
	bg->setAnchorPoint(-1.0, -1.0, 0.0);
	bg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	bg->blockMouseInput = true;
	bg->processInputEvents = true;
	
	headerBg = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE,10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	SceneLabel *label = new SceneLabel("TREE VIEW", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(10, 3);
	
	treeContainer = new UITreeContainer("Images/entity_icon.png", L"Entity", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	treeContainer->setPosition(0, 30);
	
	EntityBrowserData *data = new EntityBrowserData();
	data->entity = rootEntity;
	treeContainer->getRootNode()->setUserData((void*) data)	;	
	
	addChild(treeContainer);	
	
	newLayerButton = new UIImageButton("Images/new_layer.png");
	addChild(newLayerButton);

	targetLayerButton = new UIImageButton("Images/target_layer.png");
	addChild(targetLayerButton);

	
	dontSendSelectionEvent = false;
	
}

void EntityTreeView::setRootEntity(Entity *entity) {
	rootEntity = entity;
	EntityBrowserData *oldData = (EntityBrowserData*)treeContainer->getRootNode()->getUserData();
	if(oldData)
		delete oldData;
	
	EntityBrowserData *data = new EntityBrowserData();
	data->entity = rootEntity;
	treeContainer->getRootNode()->setUserData((void*) data)	;	
}

void EntityTreeView::syncNodeToEntity(UITree *node, Entity *entity) {

	// remove non existing and set proper ids, 
	
	std::vector<UITree*> nodesToRemove;

	for(int i=0; i < node->getNumTreeChildren(); i++) {
		UITree *child = node->getTreeChild(i);
		
		bool hasChild = false;
		for(int j=0; j < entity->getNumChildren(); j++) {
			if(!entity->getChildAtIndex(j)->editorOnly) {
			if(((EntityBrowserData*)child->getUserData())->entity == entity->getChildAtIndex(j)) {
				hasChild = true;
				
				String entityName = entity->getChildAtIndex(j)->id;
				if(entity->getChildAtIndex(j) == targetLayer) {
					entityName += " (current)";
				}
				
				if(child->getLabelText() != entityName) {
					child->setLabelText(entityName);
				}
				
				if(entity->getChildAtIndex(j) == selectedEntity) {
					dontSendSelectionEvent = true;				
					child->setSelected();
				}
				
			}
			}
		}

		if(!hasChild) {
			nodesToRemove.push_back(child);
		}
	}
	
	for(int i=0; i < nodesToRemove.size(); i++) {
		node->removeTreeChild(nodesToRemove[i]);
	}
	
	std::vector<Entity*> entitiesToAdd;
	
	for(int j=0; j < entity->getNumChildren(); j++) {	
		if(!entity->getChildAtIndex(j)->editorOnly) {	
		bool hasEntity = false;			
		for(int i=0; i < node->getNumTreeChildren(); i++) {
			UITree *child = node->getTreeChild(i);
			if(((EntityBrowserData*)child->getUserData())->entity == entity->getChildAtIndex(j)) {
				hasEntity = true;
			}
		}
		
		if(!hasEntity) {
			entitiesToAdd.push_back(entity->getChildAtIndex(j));
		}
		}
	}
	
	for(int i=0; i < entitiesToAdd.size(); i++) {
	
		String entityName = entitiesToAdd[i]->id;
		if(entitiesToAdd[i] == targetLayer) {
			entityName += " (current)";
		}
	
		UITree *newNode = node->addTreeChild("Images/entity_icon.png", entityName);
		EntityBrowserData *data = new EntityBrowserData();
		data->entity = entitiesToAdd[i];		
		newNode->setUserData((void*)data);				
		
		if(entitiesToAdd[i] == selectedEntity) {
			dontSendSelectionEvent = true;
			newNode->setSelected();
		}
	}
	
	for(int i=0; i < node->getNumTreeChildren(); i++) {
		UITree *child = node->getTreeChild(i);
		syncNodeToEntity(child, ((EntityBrowserData*)child->getUserData())->entity);
	}
}

void EntityTreeView::Refresh() {
	syncNodeToEntity(treeContainer->getRootNode(), rootEntity);
}

void EntityTreeView::handleEvent(Event *event) {
	
	if(event->getDispatcher() == treeContainer->getRootNode()) {
		if(event->getEventCode() == UITreeEvent::SELECTED_EVENT){ 			
			if(!dontSendSelectionEvent) {
				EntityBrowserData *data = (EntityBrowserData *)treeContainer->getRootNode()->getSelectedNode()->getUserData();
				selectedEntity =  data->entity;
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
			}
			dontSendSelectionEvent = false;
		}
	}
//
//	if(event->getEventCode() == Event::CHANGE_EVENT && event->getEventType() == "Event") {
//		for(int i=0; i < layers.size(); i++) {
//			if(event->getDispatcher() == layers[i]) {
//				currentLayer->setSelected(false);
//				layers[i]->setSelected(true);
//				currentLayer = layers[i];				
//				dispatchEvent(new Event(), Event::CHANGE_EVENT);
//			}
//		}
//	}
/*
	if(event->getDispatcher() == treeContainer->getRootNode()) {
		if(event->getEventCode() == UITreeEvent::SELECTED_EVENT){ 
			selectedNode = treeContainer->getRootNode()->getSelectedNode();			
			MaterialBrowserData *data = (MaterialBrowserData *)selectedNode->getUserData();
			selectedData =  data;
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
	*/
	Entity::handleEvent(event);
}


EntityTreeView::~EntityTreeView() {

}


void EntityTreeView::Resize(Number width, Number height) {
	setWidth(width);
	setHeight(height);
	
	bg->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, width, height);
	headerBg->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, width, 30);
	
	newLayerButton->setPosition(width- 30, 3);		
	targetLayerButton->setPosition(width- 55, 3);	
		
	treeContainer->Resize(width, height-30);
}


PolycodeScreenEditorMain::PolycodeScreenEditorMain(PolycodeEditor *editor) {
	this->editor = editor;
	firstMove = false;

	multiSelect = false;
	currentLayer = NULL;
	treeView = NULL;
	placementCount = 0;
	beforeData = NULL;
	
	currentLayer = NULL;
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");

	isScalingEntity = false;	
	isDraggingEntity = false; 
		
	baseEntity = new Entity();
	addChild(baseEntity);
	baseEntity->processInputEvents = true;
		
	baseEntity->setAnchorPoint(0.0, 0.0, 0.0);	

	objectBaseEntity = new Entity();
	baseEntity->addChild(objectBaseEntity);
	objectBaseEntity->processInputEvents = true;

	sizePreviewShape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1, 1);
	baseEntity->addChild(sizePreviewShape);
	sizePreviewShape->setColor(1.0, 1.0, 1.0, 0.0);
	
	screenPreviewShape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 1, 1);
	baseEntity->addChild(screenPreviewShape);
	screenPreviewShape->setColor(1.0, 1.0, 1.0, 0.0);

	layerBaseEntity = new Entity();
	layerBaseEntity->processInputEvents = true;
	objectBaseEntity->addChild(layerBaseEntity);
	
	setCurrentLayer(layerBaseEntity);

	placingPreviewEntity = new Entity();
	objectBaseEntity->addChild(placingPreviewEntity);
	
	previewEntity = new UIImage("Images/ScreenEditor/entity_marker.png");
	placingPreviewEntity->addChild(previewEntity);
	previewEntity->setAnchorPoint(0.0, 0.0, 0.0);
	previewEntity->billboardMode = true;
	previewEntity->billboardIgnoreScale = true;
	
	previewSound = new SceneSound("test.wav", 50, 100);
	placingPreviewEntity->addChild(previewSound);
				
	createSoundRef(previewSound);

	
	previewEmitter = new SceneParticleEmitter("default.png", Particle::BILLBOARD_PARTICLE, ParticleEmitter::CONTINUOUS_EMITTER, 2.0, 30, Vector3(0.0, -40.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(10.0, 10.0, 0.0));
	placingPreviewEntity->addChild(previewEmitter);
	createParticleRef(previewEmitter);
	
	previewShape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 100, 100);
	placingPreviewEntity->addChild(previewShape);
	previewShape->setColor(1.0, 1.0, 1.0, 0.5);

	previewLabel = new SceneLabel("Text", 24);
	previewLabel->setAnchorPoint(0.0, 0.0, 0.0);
	placingPreviewEntity->addChild(previewLabel);
	previewLabel->setColor(1.0, 1.0, 1.0, 0.5);
	previewLabel->positionAtBaseline = false;

	previewSprite = new SceneSprite("default/default.sprite");
	previewSprite->setAnchorPoint(0.0, 0.0, 0.0);	
	placingPreviewEntity->addChild(previewSprite);
	previewSprite->setColor(1.0, 1.0, 1.0, 0.5);
	previewSprite->getResourceEntry()->reloadOnFileModify = true;
		
	previewImage = new UIImage("default.png");
	previewImage->setAnchorPoint(0.0, 0.0, 0.0);
	placingPreviewEntity->addChild(previewImage);
	previewImage->setColor(1.0, 1.0, 1.0, 0.5);

	previewInstance = new SceneEntityInstance("default/default.entity2d");
	previewInstance->setAnchorPoint(0.0, 0.0, 0.0);
	placingPreviewEntity->addChild(previewInstance);
	previewInstance->setColor(1.0, 1.0, 1.0, 0.5);
	previewInstance->getResourceEntry()->reloadOnFileModify = true;
	previewInstance->getResourceEntry()->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
	
	CoreServices::getInstance()->getResourceManager()->addResource(previewInstance->getResourceEntry());	
	CoreServices::getInstance()->getResourceManager()->addResource(previewSprite->getResourceEntry());	
	
	grid = false;
	setGrid(16);
	
	gridSnap = false;
	pixelSnap = true;

	centerImage = new UIImage("Images/ScreenEditor/screenCenter.png");
	centerImage->setAnchorPoint(0.0, 0.0, 0.0);
	baseEntity->addChild(centerImage);
	
	baseEntity->setPosition(256,256);
	firstResize = true;
	
	baseEntity->setWidth(20000);
	baseEntity->setHeight(20000);
		

	CoreServices::getInstance()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	CoreServices::getInstance()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);

	baseEntity->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	baseEntity->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	baseEntity->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	baseEntity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	baseEntity->addEventListener(this, InputEvent::EVENT_MOUSEOUT);
	baseEntity->processInputEvents = true;


	screenTransformShape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 10, 10);
//	screenTransformShape->strokeColor = Color(0.0, 0.3, 1.0, 1.0);
	screenTransformShape->lineSmooth = true;
//	screenTransformShape->strokeEnabled = true;
	screenTransformShape->setColor(1.0, 1.0, 1.0, 0.0);
	baseEntity->addChild(screenTransformShape);		


	screenTransform = new Entity();
	baseEntity->addChild(screenTransform);	
	screenTransform->visible = false;
	screenTransform->processInputEvents = true;
	
	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_LINEAR);
	
	UIImage *base = new UIImage("Images/ScreenEditor/transform_base.png");
	base->setAnchorPoint(0.0, 0.0, 0.0);
	screenTransform->addChild(base);
	
	transformRotator = new UIImage("Images/ScreenEditor/transform_rotator.png");
	transformRotator->setAnchorPoint(0.0, 0.0, 0.0);
	transformRotator->setPosition(-40, 40);
	screenTransform->addChild(transformRotator);
	transformRotator->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	transformRotator->processInputEvents = true;
	transformRotator->blockMouseInput = true;

	transformScalerY = new UIImage("Images/ScreenEditor/transform_scaler.png");
	transformScalerY->setColor(0.0, 0.5, 1.0, 0.7);
	transformScalerY->setAnchorPoint(0.0, 0.0, 0.0);
	transformScalerY->setPosition(0, -50);
	screenTransform->addChild(transformScalerY);	
	transformScalerY->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	transformScalerY->processInputEvents = true;
	transformScalerY->blockMouseInput = true;
	transformScalerY->setScale(0.7, 0.7);
	
	transformScalerX = new UIImage("Images/ScreenEditor/transform_scaler.png");
	transformScalerX->setColor(1.0, 0.5, 0.0, 0.7);
	transformScalerX->setAnchorPoint(0.0, 0.0, 0.0);
	transformScalerX->setRoll(90);
	transformScalerX->setPosition(50, 0);
	screenTransform->addChild(transformScalerX);	
	transformScalerX->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	transformScalerX->processInputEvents = true;
	transformScalerX->blockMouseInput = true;
	transformScalerX->setScale(0.7, 0.7);
		
	transformScalerXY = new UIImage("Images/ScreenEditor/transform_scaler.png");
	transformScalerXY->setColor(1.0, 1.0, 1.0, 0.7);
	transformScalerXY->setAnchorPoint(0.0, 0.0, 0.0);
	transformScalerXY->setRoll(-45);
	transformScalerXY->setPosition(40, -40);
	screenTransform->addChild(transformScalerXY);
	transformScalerXY->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	transformScalerXY->processInputEvents = true;
	transformScalerXY->blockMouseInput = true;
	
	
	
	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
	
	viewOptions = new Entity();
	addChild(viewOptions);
	viewOptions->processInputEvents = true;
	viewOptions->blockMouseInput = true;
			
	viewOptionsBg = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 20,20);
	viewOptionsBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	viewOptionsBg->setAnchorPoint(-1.0, -1.0, 0.0);
	viewOptions->addChild(viewOptionsBg);
	
	viewOptionsBg->blockMouseInput = true;
	viewOptionsBg->processInputEvents = true;
	

	SceneLabel *label = new SceneLabel("GRID", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	viewOptions->addChild(label);
	label->setPosition(10, 3);
	
	gridSizeInput = new UITextInput(false, 40, 12);
	gridSizeInput->setText("16");
	viewOptions->addChild(gridSizeInput);
	gridSizeInput->setPosition(60, 4);
	gridSizeInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	gridCheckBox = new UICheckBox("On", true);
	gridCheckBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	viewOptions->addChild(gridCheckBox);
	gridCheckBox->setPosition(115, 5);

	label = new SceneLabel("SNAP", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	viewOptions->addChild(label);
	label->setPosition(180, 3);

	pixelSnapBox = new UICheckBox("Pixel", true);
	pixelSnapBox->addEventListener(this, UIEvent::CHANGE_EVENT);	
	viewOptions->addChild(pixelSnapBox);
	pixelSnapBox->setPosition(230, 5);

	gridSnapBox = new UICheckBox("Grid", true);
	gridSnapBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	viewOptions->addChild(gridSnapBox);
	gridSnapBox->setPosition(290, 5);
	gridSnapBox->setChecked(false);
	
	label = new SceneLabel("SHOW", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	viewOptions->addChild(label);
	label->setPosition(360, 3);
	
	showRefsBox = new UICheckBox("Refs", true);
	showRefsBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	viewOptions->addChild(showRefsBox);
	showRefsBox->setPosition(420, 5);	
		
	properties = new Entity();
	addChild(properties);
	properties->processInputEvents = true;
	properties->blockMouseInput = true;
			
	propertiesBg = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 20,20);
	propertiesBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	propertiesBg->setAnchorPoint(-1.0, -1.0, 0.0);
	properties->addChild(propertiesBg);
	propertiesBg->blockMouseInput = true;
	propertiesBg->processInputEvents = true;
	
	label = new SceneLabel("SCREEN RATIO", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	properties->addChild(label);
	label->setPosition(10, 3);
	
	scaleInput = new UITextInput(false, 70, 12);
	scaleInput->setText("1.0");
	properties->addChild(scaleInput);
	scaleInput->setPosition(140, 4);
	scaleInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	label = new SceneLabel("PREVIEW ASPECT", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	properties->addChild(label);
	label->setPosition(230, 3);
	
	aspectComboBox = new UIComboBox(globalMenu, 80);
	aspectComboBox->addComboItem("4:3");
	aspectComboBox->addComboItem("16:9");
	aspectComboBox->addComboItem("16:10");
	aspectComboBox->addComboItem("3:2");
	aspectComboBox->addComboItem("1:1");
	
	aspectComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	aspects[0] = 4.0/3.0;
	aspects[1] = 16.0/9.0;
	aspects[2] = 16/10.0;
	aspects[3] = 3.0/2.0;
	aspects[4] = 1.0;
							
	aspectComboBox->setSelectedIndex(0);
	properties->addChild(aspectComboBox);
	aspectComboBox->setPosition(380, 2);
			
	label = new SceneLabel("ZOOM", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	properties->addChild(label);
	label->setPosition(470, 3);
			
	zoomComboBox = new UIComboBox(globalMenu, 80);
	zoomComboBox->addComboItem("8:1");
	zoomComboBox->addComboItem("4:1");
	zoomComboBox->addComboItem("2:1");
	zoomComboBox->addComboItem("1:1");
	zoomComboBox->addComboItem("1:2");
	zoomComboBox->addComboItem("1:4");
	zoomComboBox->addComboItem("1:8");
	zoomComboBox->addComboItem("Free");
	
	zooms[0] = 8.0;
	zooms[1] = 4.0;
	zooms[2] = 2.0;
	zooms[3] = 1.0;
	zooms[4] = 1.0/2.0;
	zooms[5] = 1.0/4.0;
	zooms[6] = 1.0/8.0;						
							
	zoomComboBox->setSelectedIndex(3);
	
	zoomComboBox->addEventListener(this, UIEvent::CHANGE_EVENT);	
	properties->addChild(zoomComboBox);
	zoomComboBox->setPosition(530, 2);
			
	toolPalette = new Entity();
	toolPalette->setPosition(0, 30);
	toolPalette->processInputEvents = true;
	toolPalette->blockMouseInput = true;
	addChild(toolPalette);
	
	toolPaletteBg = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 80, 20);
	toolPaletteBg->setAnchorPoint(-1.0, -1.0, 0.0);
	toolPaletteBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiSmallHeaderBgColor"));
	toolPalette->addChild(toolPaletteBg);
	toolPaletteBg->processInputEvents = true;
	toolPaletteBg->blockMouseInput = true;
	Number yOffset = 15.0;
		
	selectorImage = new UIImage("Images/ScreenEditor/selector.png");
	selectorImage->setColor(0.0, 0.0, 0.0, 0.3);
	toolPalette->addChild(selectorImage);
	
	arrowToolButton = new UIImageButton("Images/ScreenEditor/arrow.png");
	arrowToolButton->addEventListener(this, UIEvent::CLICK_EVENT);
	toolPalette->addChild(arrowToolButton);
	arrowToolButton->setPosition(12, yOffset);

	imageToolButton = new UIImageButton("Images/ScreenEditor/image.png");
	toolPalette->addChild(imageToolButton);
	imageToolButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	imageToolButton->setPosition(42, yOffset);

	entityToolButton = new UIImageButton("Images/ScreenEditor/screen_entity.png");
	toolPalette->addChild(entityToolButton);
	entityToolButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	entityToolButton->setPosition(72, yOffset);


	yOffset += 32;
	
	textToolButton = new UIImageButton("Images/ScreenEditor/text.png");
	toolPalette->addChild(textToolButton);
	textToolButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	textToolButton->setPosition(12, yOffset);

	shapeToolButton = new UIImageButton("Images/ScreenEditor/shape.png");
	toolPalette->addChild(shapeToolButton);
	shapeToolButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	shapeToolButton->setPosition(42, yOffset);

	soundToolButton = new UIImageButton("Images/ScreenEditor/screen_sound.png");
	toolPalette->addChild(soundToolButton);
	soundToolButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	soundToolButton->setPosition(72, yOffset);


	yOffset += 32;
	
	zoomToolButton = new UIImageButton("Images/ScreenEditor/zoom.png");
	toolPalette->addChild(zoomToolButton);
	zoomToolButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	zoomToolButton->setPosition(12, yOffset);

	panToolButton = new UIImageButton("Images/ScreenEditor/pan.png");
	toolPalette->addChild(panToolButton);
	panToolButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	panToolButton->setPosition(42, yOffset);
	
	parentToolButton = new UIImageButton("Images/ScreenEditor/link.png");
	toolPalette->addChild(parentToolButton);
	parentToolButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	parentToolButton->setPosition(72, yOffset);

	yOffset += 32;
	
	linkToolButton = new UIImageButton("Images/link_entity.png");
	toolPalette->addChild(linkToolButton);
	linkToolButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	linkToolButton->setPosition(12, yOffset);	

	spriteToolButton = new UIImageButton("Images/ScreenEditor/sprite_icon.png");
	toolPalette->addChild(spriteToolButton);
	spriteToolButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	spriteToolButton->setPosition(42, yOffset);	

	particlesToolButton = new UIImageButton("Images/particle_system_icon.png");
	toolPalette->addChild(particlesToolButton);
	particlesToolButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	particlesToolButton->setPosition(72, yOffset);	


	yOffset += 64;

	moveUpButton = new UIButton("Move Up", 90);
	moveUpButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	moveUpButton->setPosition(5, yOffset);
	toolPalette->addChild(moveUpButton);

	yOffset += 32;	
	moveDownButton = new UIButton("Move Down", 90);
	moveDownButton->setPosition(5, yOffset);
	moveDownButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	toolPalette->addChild(moveDownButton);

	yOffset += 32;	
	moveTopButton = new UIButton("Move To Front", 90);
	moveTopButton->setPosition(5, yOffset);
	moveTopButton->addEventListener(this, UIEvent::CLICK_EVENT);			
	toolPalette->addChild(moveTopButton);

	yOffset += 32;	
	moveBottomButton = new UIButton("Move To Back", 90);
	moveBottomButton->setPosition(5, yOffset);
	moveBottomButton->addEventListener(this, UIEvent::CLICK_EVENT);				
	toolPalette->addChild(moveBottomButton);

	yOffset += 64;	
	unparentButton = new UIButton("Unparent", 90);
	unparentButton->setPosition(5, yOffset);
	unparentButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	toolPalette->addChild(unparentButton);


	selectorImage->setPosition(arrowToolButton->getPosition().x - 4, arrowToolButton->getPosition().y - 4);
	
	placing = false;
	moving = false;
	scalingY = false;
	scalingX = false;	
	rotating = false;
	zooming = false;
	panning = false;
	
	lastMode = MODE_SELECT;
	
	previewAspectRatio = aspects[0];
	
	
	entityProps = new PropList();
	
	particleSheet = new ScreenParticleSheet();
	particleSheet->addEventListener(this, Event::CHANGE_EVENT);	
	particleSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);		
	entityProps->addPropSheet(particleSheet);

	spriteSheet = new SceneSpriteSheet();
	spriteSheet->addEventListener(this, Event::CHANGE_EVENT);
	spriteSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);	
	entityProps->addPropSheet(spriteSheet);
	
	instanceSheet = new SceneEntityInstanceSheet();
	instanceSheet->addEventListener(this, Event::CHANGE_EVENT);	
	instanceSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
	entityProps->addPropSheet(instanceSheet);

	labelSheet = new SceneLabelSheet();
	labelSheet->addEventListener(this, Event::CHANGE_EVENT);	
	labelSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);	
	entityProps->addPropSheet(labelSheet);

	soundSheet = new SoundSheet();
	entityProps->addPropSheet(soundSheet);
	soundSheet->addEventListener(this, Event::CHANGE_EVENT);
	soundSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
	
	imageSheet = new UIImageSheet();
	entityProps->addPropSheet(imageSheet);
	imageSheet->addEventListener(this, Event::CHANGE_EVENT);	
	imageSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
	
	shapeSheet = new ShapeSheet();
	shapeSheet->addEventListener(this, Event::CHANGE_EVENT);
	shapeSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
	entityProps->addPropSheet(shapeSheet);

	transform2dSheet = new Transform2DSheet();
	transform2dSheet->addEventListener(this, Event::CHANGE_EVENT);
	transform2dSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);	
	entityProps->addPropSheet(transform2dSheet);
	
	entitySheet = new EntitySheet();
	entityProps->addPropSheet(entitySheet);
	entitySheet->addEventListener(this, Event::CHANGE_EVENT);	
	entitySheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
					
	entityPropSheet = new EntityPropSheet();
	entityPropSheet->addEventListener(this, Event::CHANGE_EVENT);	
	entityPropSheet->addEventListener(this, PropEvent::EVENT_PROP_CHANGE);
	entityProps->addPropSheet(entityPropSheet);	
	
	entityProps->updateProps();		
	
	parenting = false;
	parentingChild = NULL;	
	
	parentingLine = new SceneLine(Vector3(), Vector3(0,0,0));
	parentingLine->setLineWidth(4.0);
	parentingLine->setColor(0.0, 0.5, 1.0, 0.5);
	baseEntity->addChild(parentingLine);
	
	setMode(MODE_SELECT);	
}

void PolycodeScreenEditorMain::setGrid(int gridSize) {

	this->gridSize = gridSize;

	Polycode::Polygon *gridPoly = new Polycode::Polygon();
	int gridLen = 300;
	
	for(int x=0; x < gridLen+1; x++) {
		gridPoly->addVertex(x * gridSize,0, 0);
		gridPoly->addVertex(x * gridSize,gridSize * gridLen, 0);		
	}

	for(int y=0; y < gridLen+1; y++) {
		gridPoly->addVertex(0, y * gridSize, 0);
		gridPoly->addVertex(gridSize * gridLen, y * gridSize, 0);		
	}	

	if(grid) {
		grid->getMesh()->clearMesh();
		grid->getMesh()->addPolygon(gridPoly);
	} else {
		Mesh *gridMesh = new Mesh(Mesh::LINE_MESH);
		gridMesh->addPolygon(gridPoly);
	
		grid = new SceneMesh(gridMesh);
		grid->setColor(1.0, 1.0, 1.0, 0.1);
		objectBaseEntity->addChild(grid);		
	}

	grid->setPosition(-(gridSize * gridLen)/2, -(gridSize * gridLen)/2);
}

PolycodeScreenEditorMain::~PolycodeScreenEditorMain() {
	CoreServices::getInstance()->getCore()->getInput()->removeAllHandlersForListener(this);
	setOwnsChildrenRecursive(true);
}

void PolycodeScreenEditorMain::doAction(String actionName, PolycodeEditorActionData *data) {
	PolycodeScreenEditorActionData *screenData = (PolycodeScreenEditorActionData*)data;
	if(actionName == "move") {
		for(int i=0; i < selectedEntities.size(); i++) {
			selectedEntities[i]->position = screenData->entries[i].vec3;
		}
		syncTransformToSelected();
	} else if(actionName == "scale") {
		for(int i=0; i < selectedEntities.size(); i++) {
			selectedEntities[i]->scale = screenData->entries[i].vec3;
		}	
		syncTransformToSelected();		
	} else if(actionName == "rotate") {
		for(int i=0; i < selectedEntities.size(); i++) {
			selectedEntities[i]->position = screenData->entries[i].vec3;		
			selectedEntities[i]->setRoll(screenData->entries[i].number);
		}
		syncTransformToSelected();			
	} else if(actionName == "select") {
			selectEntity(NULL, false);	
			if(data) {
				bool oldMultiSelect = multiSelect;
				multiSelect = true;
				for(int i=0; i < screenData->entries.size(); i++) {
					selectEntity(screenData->entries[i].entity, false);
				}					
				multiSelect = oldMultiSelect;				
			}
		syncTransformToSelected();			
	} else if(actionName == "set_current_layer") {
		if(screenData->entry.entity) {
			setCurrentLayer(screenData->entry.entity, false);
		}
	} else if(actionName == "delete") {
		if(screenData->reverse) {
			bool oldMultiSelect = multiSelect;
			multiSelect = true;
			for(int i=0; i < screenData->entries.size(); i++) {
				screenData->entries[i].parentEntity->addChild(screenData->entries[i].entity);
				selectEntity(screenData->entries[i].entity, false);
			}					
			multiSelect = oldMultiSelect;		
		} else {
			for(int i=0; i < screenData->entries.size(); i++) {
				deleteEntity(screenData->entries[i].entity);
			}					
			selectEntity(NULL, false);
		}
	} else if(actionName == "paste") {
		if(screenData->reverse) {
			for(int i=0; i < screenData->entries.size(); i++) {
				deleteEntity(screenData->entries[i].entity);
			}		
		} else {
			bool oldMultiSelect = multiSelect;
			multiSelect = true;
			for(int i=0; i < screenData->entries.size(); i++) {
				screenData->entries[i].parentEntity->addChild(screenData->entries[i].entity);
				selectEntity(screenData->entries[i].entity, false);
			}
			multiSelect = oldMultiSelect;			
		}
		if(treeView) {
			treeView->Refresh();		
		}					
	} else if(actionName == "create_entity") {	
		if(screenData->reverse) {
			deleteEntity(screenData->entry.entity);
		} else {
			screenData->entry.parentEntity->addChild(screenData->entry.entity);			
		}
		
		if(treeView) {
			treeView->Refresh();		
		}			
					
	} else if(actionName == "prop_change") {
		PolycodeEditorPropActionData *propData = (PolycodeEditorPropActionData*) data;
		propData->sheet->applyPropActionData(propData);
	}
}

void PolycodeScreenEditorMain::syncTransformToSelected() {
	sizePreviewShape->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, layerBaseEntity->getWidth() * objectBaseEntity->getScale().x, layerBaseEntity->getHeight() * objectBaseEntity->getScale().x);


	if(selectedEntities.size() == 0)
		return;
	
	Entity *selectedEntity = selectedEntities[0];
	
	objectBaseEntity->rebuildTransformMatrix();	
	selectedEntity->rebuildTransformMatrix();
	

	if(selectedEntities.size() == 1) {

		screenTransformShape->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, selectedEntity->getWidth(),selectedEntity->getHeight());	
		Matrix4 final = selectedEntity->getConcatenatedMatrixRelativeTo(baseEntity);
		screenTransform->setPosition(final.getPosition());
		screenTransformShape->dirtyMatrix(false);
		screenTransformShape->setTransformByMatrixPure(final);		
		screenTransform->rotation.roll = selectedEntity->getCombinedRoll();
	} else {
			
		Vector3 center;
		Number width;
		Number height;
		getCenterAndSizeForSelected(&center, &width, &height);
		
		screenTransform->setPosition(center.x, center.y);
		screenTransformShape->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, width, height);
		screenTransformShape->setPosition(center);
		
		screenTransform->rotation.roll = groupRoll * TODEGREES;
	}
	
	screenTransform->rebuildTransformMatrix();
	
}

void PolycodeScreenEditorMain::getCenterAndSizeForSelected(Vector2 *center, Number *width, Number *height) {
		// Calculate corners transformed into base entity space and get center and 
		// transformed bounding vertices
		
		std::vector<Vector3> corners;
		
		for(int i=0; i < selectedEntities.size(); i++) {
			Entity *entity = selectedEntities[i];
			Vector3 tl = Vector3(-entity->getWidth()/2.0, -entity->getHeight()/2.0, 0.0);
			Vector3 tr = Vector3(entity->getWidth()/2.0, -entity->getHeight()/2.0, 0.0);
			Vector3 bl = Vector3(-entity->getWidth()/2.0, entity->getHeight()/2.0, 0.0);
			Vector3 br = Vector3(entity->getWidth()/2.0, entity->getHeight()/2.0, 0.0);
			
			Matrix4 final = entity->getConcatenatedMatrixRelativeTo(baseEntity);			
			
			tl = final * tl;
			tr = final * tr;
			bl = final * bl;
			br = final * br;
												
			corners.push_back(tl);
			corners.push_back(tr);
			corners.push_back(bl);
			corners.push_back(br);									
		}
		
		Vector3 min = Vector3(3.4E+38, 3.4E+38, 0.0);
		Vector3 max = Vector3(-3.4E+38, -3.4E+38, 0.0);		
				
		for(int i=0; i < corners.size(); i++) {
			if(corners[i].x < min.x) {
				min.x = corners[i].x;
			}
			if(corners[i].y < min.y) {
				min.y = corners[i].y;
			}
			
			if(corners[i].x > max.x) {
				max.x = corners[i].x;
			}
			if(corners[i].y > max.y) {
				max.y = corners[i].y;
			}						
		}						
		
		*width = fabs(max.x - min.x);
		*height = fabs(max.y - min.y);

		center->x = min.x + (*width/2.0);
		center->y = min.y + (*height/2.0);

		
}


void PolycodeScreenEditorMain::updateCursor() {
	switch(mode) {
		case MODE_SELECT:
			CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_ARROW);
		break;
		case MODE_IMAGE:
		case MODE_TEXT:		
		case MODE_SHAPE:
		case MODE_PARENT:		
		case MODE_ENTITY:				
		case MODE_SOUND:
		case MODE_LINK:
		case MODE_SPRITE:	
		case MODE_PARTICLES:				
			CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_CROSSHAIR);
		break;
		case MODE_ZOOM:
			CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_CROSSHAIR);		
		break;
		case MODE_PAN:
			CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_OPEN_HAND);		
		break;
		default:
			CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_ARROW);		
		break;
	}
}

void PolycodeScreenEditorMain::handleMouseUp(Vector2 position) {

	switch(mode) {
		case MODE_PARENT:
			if(parenting) {
//				parentingLine->visible = false;
//				parenting = false;
			}
		break;
		case MODE_PAN:
			panning = false;
		break;
		case MODE_ZOOM:
		{
			if(!zoomingMoved) {
			
				Number zoomChange = 2.0;
				
				if(CoreServices::getInstance()->getCore()->getInput()->getKeyState(KEY_LALT) ||
					CoreServices::getInstance()->getCore()->getInput()->getKeyState(KEY_RALT)) {
					zoomChange = 1.0/zoomChange;
				} 
	
			
				Number newScale = baseZoomScale * zoomChange;
				if(newScale < 0.1) 
					newScale = 0.1;
					
				objectBaseEntity->setScale(newScale, newScale);					
								
				Vector2 centerPosition = Vector2(getWidth()/2.0, getHeight()/2.0);
				
				Vector2 finalPosition = Vector2(				
					((centerPosition.x)) - (zoomBaseMousePosition.x / baseZoomScale * newScale),
					((centerPosition.y)) - (zoomBaseMousePosition.y / baseZoomScale * newScale)
				);				

				baseEntity->setPosition(finalPosition);				
				resizePreviewScreen();
				syncTransformToSelected();
								
				// set zoom selection box to Free zoom
				zoomComboBox->setSelectedIndex(7);				
			}
			zooming = false;
		}
		break;
		case MODE_SELECT:	
		{
			Vector2 trans = (CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - mouseBase);
			if(trans.length() > 0) {
		
			if(moving) {
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				for(int i=0; i < selectedEntities.size(); i++) {
					data->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]->position));
				}
				editor->didAction("move", beforeData, data);
			} else if(scalingX || scalingY) {
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				for(int i=0; i < selectedEntities.size(); i++) {
					data->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]->scale));
				}
				editor->didAction("scale", beforeData, data);
			} else if(rotating) {
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				for(int i=0; i < selectedEntities.size(); i++) {
					data->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]->position, selectedEntities[i]->getRotation()));
				}
				editor->didAction("rotate", beforeData, data);
			}
			}
			
			moving = false;
			scalingY = false;
			scalingX = false;
			rotating = false;
		}
		break;	
		case MODE_SHAPE:
		break;
	}
}

void PolycodeScreenEditorMain::adjustForSnap(Vector2 *position) {
	if(gridSnap) {
		position->x = round(((Number)position->x)/((Number)gridSize)) * gridSize;
		position->y = round(((Number)position->y)/((Number)gridSize)) * gridSize;	
	} else if(pixelSnap) {
		position->x = round(((Number)position->x));
		position->y = round(((Number)position->y));
	}			
}

void PolycodeScreenEditorMain::handleMouseMove(Vector2 position) {
	switch(mode) {
	
		case MODE_PARENT:
		{
			if(parenting) {
				parentingLine->setEnd(position);
			}
		}
		break;
		case MODE_PAN:
		{
			if(panning) {
			Number moveModifier =  1.0;//  / objectBaseEntity->getScale().x;
			Vector2 trans = (CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - mouseBase) * moveModifier; 
				
			baseEntity->setPosition(basePanPosition.x + trans.x, basePanPosition.y + trans.y); 
		}
		}
		break;
		case MODE_ZOOM:
		{
			if(zooming) {
				Vector2 mousePosition = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();
				Vector2 offset = mousePosition-mouseBase;
				Number newScale = baseZoomScale + ((offset.x-offset.y) * 0.002);
				if(newScale < 0.1) 
					newScale = 0.1;
					
				objectBaseEntity->setScale(newScale, newScale);					
				
				Vector2 centerPosition = Vector2(getWidth()/2.0, getHeight()/2.0);
				
				Vector2 finalPosition = Vector2(				
					((centerPosition.x)) - (zoomBasePosition.x / baseZoomScale * newScale),
					((centerPosition.y)) - (zoomBasePosition.y / baseZoomScale * newScale)
				);				

				baseEntity->setPosition(finalPosition);
				
				resizePreviewScreen();
				syncTransformToSelected();
				
				// set zoom selection box to Free zoom
				zoomComboBox->setSelectedIndex(7);
				zoomingMoved = true;
			}
		}
		break;
		case MODE_SELECT:
		{
		
			if(rotating) {
			
				Vector2 diff = CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - baseScaleScreenPosition;
				diff.Normalize();
				Number newAngle = atan2(diff.x, diff.y);				
			
				if(selectedEntities.size() == 1) {
					selectedEntities[0]->setRoll(baseRotateAngles[0] - (TODEGREES * (newAngle-baseAngle)));
				} else {
				
					groupRoll = -(newAngle-baseAngle);
					
					for(int i=0; i < selectedEntities.size(); i++) {
						Vector3 v3Center = Vector3(groupCenterPoint.x,groupCenterPoint.y,0.0);
						
						Vector3 v3CenterRelative = selectedEntities[i]->getParentEntity()->getConcatenatedMatrixRelativeTo(baseEntity).Inverse() * v3Center;	
						
						selectedEntities[i]->setRoll(baseRotateAngles[i] - (TODEGREES * (newAngle-baseAngle)));						
						
						Number s = sin(newAngle-baseAngle);
						Number c = cos(newAngle-baseAngle);

						Vector2 p = baseEntityPositions[i];
						p.x -= v3CenterRelative.x;
						p.y -= v3CenterRelative.y;

						Number xnew = p.x * c + p.y * s;
						Number ynew = -p.x * s + p.y * c;

						p.x = xnew + v3CenterRelative.x;
						p.y = ynew + v3CenterRelative.y;																
						
						selectedEntities[i]->setPosition(p.x, p.y);
					}
				
				}
				syncTransformToSelected();			
			} 
			else if(scalingY && scalingX) {
				Vector2 newMousePosition = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();
				Vector2 trans = newMousePosition - mouseBase;
								
				Number baseDist = mouseBase.distance(baseScaleScreenPosition);
				Number newDist = newMousePosition.distance(baseScaleScreenPosition);	
				Number scaleMod = 0.04;
				Number newScale = newDist - baseDist;

				for(int i=0; i < selectedEntities.size(); i++) {												
					Number newScaleX, newScaleY;
					if(baseEntityScales[i].x < 0.0) {
						newScaleX = (baseEntityScales[i].x - (newScale * scaleMod));					
					} else {
						newScaleX = (baseEntityScales[i].x + (newScale * scaleMod));					
					}
					
					if(baseEntityScales[i].y < 0.0) {
						newScaleY = (baseEntityScales[i].y - (newScale * scaleMod));					
					} else {
						newScaleY = (baseEntityScales[i].y + (newScale * scaleMod));					
					}					
					
					selectedEntities[i]->setScale(newScaleX, newScaleY);
				}
				syncTransformToSelected();					
			} else if(scalingY) {												
				Vector2 trans = CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - mouseBase;
				for(int i=0; i < selectedEntities.size(); i++) {			
							
					Vector3 trans3 = Vector3(trans.x, trans.y, 0.0);
				
					Quaternion q;								
					q.fromAxes(0.0, 0.0, -selectedEntities[i]->getCombinedRoll());
					trans3 = q.applyTo(trans3);
								
					Number scaleMod = 0.04;
					
					if(baseEntityScales[i].y < 0.0) {
						selectedEntities[i]->setScaleY(baseEntityScales[i].y + (trans3.y * scaleMod));
					} else {
						selectedEntities[i]->setScaleY(baseEntityScales[i].y - (trans3.y * scaleMod));	
					}					
																	
				}
				syncTransformToSelected();					
			} else if(scalingX) {				
				
				Vector2 trans = CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - mouseBase;
			
				for(int i=0; i < selectedEntities.size(); i++) {			
					Vector3 trans3 = Vector3(trans.x, trans.y, 0.0);
					Quaternion q;
				
					q.fromAxes(0.0, 0.0, -selectedEntities[i]->getCombinedRoll());
					trans3 = q.applyTo(trans3);
								
					Number scaleMod = 0.04;
					
					if(baseEntityScales[i].x < 0.0) {			
						selectedEntities[i]->setScaleX(baseEntityScales[i].x - (trans3.x * scaleMod));		
					} else {
						selectedEntities[i]->setScaleX(baseEntityScales[i].x + (trans3.x * scaleMod));							
					}
				}
				syncTransformToSelected();	
				
			}  else if(moving) {

				Vector2 trans = (CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - mouseBase);

				for(int i=0; i < selectedEntities.size(); i++) {
					Vector3 trans3 = Vector3(trans.x, trans.y, 0.0);
				
					Vector3 trans3_a = baseEntity->getConcatenatedMatrix() * trans3;				
					Vector3 trans3_b = selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().Inverse() * trans3_a;
				
					trans3_b = trans3_b - selectedEntities[i]->getParentEntity()->getConcatenatedMatrixRelativeTo(baseEntity).Inverse().getPosition();
					
				
					Vector2 newPosition = Vector2(baseEntityPositions[i].x + trans3_b.x, baseEntityPositions[i].y + trans3_b.y);
				
					adjustForSnap(&newPosition);
				
					selectedEntities[i]->setPosition(newPosition); 
				}
				
				syncTransformToSelected();
			}
		}
		break;
		case MODE_SHAPE:
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				adjustForSnap(&newPosition);
				previewShape->setPosition(newPosition);		
		}
		break;
		case MODE_IMAGE:
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				adjustForSnap(&newPosition);		
			previewImage->setPosition(newPosition);	
		}
		break;
		case MODE_PARTICLES:
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				adjustForSnap(&newPosition);		
			previewEmitter->setPosition(newPosition);	
		}
		break;		
		case MODE_TEXT:				
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				adjustForSnap(&newPosition);		
			previewLabel->setPosition(newPosition);				
		}
		break;
		case MODE_LINK:				
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				adjustForSnap(&newPosition);		
			previewInstance->setPosition(newPosition);				
		}
		break;		
		case MODE_ENTITY:				
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				adjustForSnap(&newPosition);		
			previewEntity->setPosition(newPosition);				
		}
		case MODE_SOUND:				
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				adjustForSnap(&newPosition);		
			previewSound->setPosition(newPosition);				
		}		
		case MODE_SPRITE:
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				adjustForSnap(&newPosition);		
			previewSprite->setPosition(newPosition);				
		}			
		
		break;		
	}
}

void PolycodeScreenEditorMain::handleMouseDown(Vector2 position) {
	switch(mode) {
		case MODE_PAN:
			mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();
			panning = true;
			basePanPosition = baseEntity->getPosition2D();
		break;
		case MODE_SELECT:	
		{
		}
		break;
		case MODE_ZOOM:
		{
			mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();
			zooming = true;
			baseZoomScale = objectBaseEntity->getScale().x;
			basePanPosition = baseEntity->getPosition2D();
			Vector2 centerPosition = Vector2(getWidth()/2.0, getHeight()/2.0);
			zoomBasePosition.x = (centerPosition.x - baseEntity->position.x);
			zoomBasePosition.y = (centerPosition.y - baseEntity->position.y);
			zoomingMoved = false;
			zoomBaseMousePosition = position;
		}
		break;
		case MODE_TEXT:
		{
				SceneLabel *placingLabel = new SceneLabel(previewLabel->getText(), previewLabel->getLabel()->getSize(), previewLabel->getLabel()->getFont()->getFontName());
				placingLabel->setAnchorPoint(0.0, 0.0, 0.0);
				placingLabel->setPosition(previewLabel->getPosition2D());
				placingLabel->processInputEvents = true;
				placingLabel->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingLabel->addEventListener(this, InputEvent::EVENT_MOUSEUP);
				placingLabel->id = "SceneLabel."+String::IntToString(placementCount);		
				placingLabel->blockMouseInput = true;
				placingLabel->positionAtBaseline = false;
				currentLayer->addChild(placingLabel);
				placementCount++;
				
				if(treeView) {
					treeView->Refresh();		
				}
				
				PolycodeScreenEditorActionData *beforeData = new PolycodeScreenEditorActionData();
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				data->reverse = false;
				data->entry = PolycodeScreenEditorActionDataEntry(placingLabel);
				beforeData->entry = PolycodeScreenEditorActionDataEntry(placingLabel);
				editor->didAction("create_entity", beforeData, data);
		}
		break;		
		case MODE_IMAGE:
		{
				UIImage *placingImage = new UIImage(previewImage->getTexture()->getResourcePath());
				placingImage->setAnchorPoint(0.0, 0.0, 0.0);
				placingImage->setPosition(previewImage->getPosition2D());
				placingImage->processInputEvents = true;
				placingImage->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
				placingImage->addEventListener(this, InputEvent::EVENT_MOUSEUP);
				placingImage->id = "UIImage."+String::IntToString(placementCount);
				placingImage->blockMouseInput = true;
				placingImage->getTexture()->reloadOnFileModify = true;
				currentLayer->addChild(placingImage);
				placementCount++;
					
				if(treeView) {
					treeView->Refresh();		
				}	
				
				PolycodeScreenEditorActionData *beforeData = new PolycodeScreenEditorActionData();
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				data->reverse = false;
				data->entry = PolycodeScreenEditorActionDataEntry(placingImage);
				beforeData->entry = PolycodeScreenEditorActionDataEntry(placingImage);
				editor->didAction("create_entity", beforeData, data);
											
		}
		break;		
		case MODE_SHAPE:
		{
				ScenePrimitive *placingShape = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 100, 100);			
				placingShape->setPosition(previewShape->getPosition2D());
				placingShape->processInputEvents = true;
				placingShape->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingShape->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				currentLayer->addChild(placingShape);
				placingShape->id = "ScenePrimitive."+String::IntToString(placementCount);			
				
				placingShape->blockMouseInput = true;				
				*placingShape = *previewShape;
				placementCount++;	

				if(treeView) {
					treeView->Refresh();		
				}
				
				PolycodeScreenEditorActionData *beforeData = new PolycodeScreenEditorActionData();
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				data->reverse = false;
				data->entry = PolycodeScreenEditorActionDataEntry(placingShape);
				beforeData->entry = PolycodeScreenEditorActionDataEntry(placingShape);				
				editor->didAction("create_entity", beforeData, data);
															
		}
		break;
		case MODE_PARTICLES:
		{
				SceneParticleEmitter *placingEmitter = new SceneParticleEmitter("default.png", Particle::BILLBOARD_PARTICLE, ParticleEmitter::CONTINUOUS_EMITTER, 2.0, 30, Vector3(0.0, -40.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(10.0, 10.0, 0.0));

				placingEmitter->setPosition(previewEmitter->getPosition2D());
				placingEmitter->processInputEvents = true;
				placingEmitter->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingEmitter->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				currentLayer->addChild(placingEmitter);
				placingEmitter->id = "SceneParticleEmitter."+String::IntToString(placementCount);
				placingEmitter->blockMouseInput = true;				
				placementCount++;	
				
				placingEmitter->emitterRadius = previewEmitter->emitterRadius;
				placingEmitter->dirVector = previewEmitter->dirVector;
				placingEmitter->gravVector = previewEmitter->gravVector;
				placingEmitter->deviation = previewEmitter->deviation;
				
				placingEmitter->brightnessDeviation = previewEmitter->brightnessDeviation;
				placingEmitter->particleSize = previewEmitter->particleSize;
				placingEmitter->perlinModSize = previewEmitter->perlinModSize;
				placingEmitter->perlinEnabled = previewEmitter->perlinEnabled;
				placingEmitter->particleSpeedMod = previewEmitter->particleSpeedMod;
				
				placingEmitter->rotationSpeed = previewEmitter->rotationSpeed;
				placingEmitter->lifespan = previewEmitter->lifespan;
				placingEmitter->particleSpeedMod = previewEmitter->particleSpeedMod;
				placingEmitter->setParticleCount(previewEmitter->getNumParticles());						

				placingEmitter->rotationFollowsPath = previewEmitter->rotationFollowsPath;
				placingEmitter->useScaleCurves = previewEmitter->useScaleCurves;
				placingEmitter->scaleCurve = previewEmitter->scaleCurve;

				placingEmitter->useColorCurves = previewEmitter->useColorCurves;
				
				placingEmitter->colorCurveR = previewEmitter->colorCurveR;
				placingEmitter->colorCurveG = previewEmitter->colorCurveG;
				placingEmitter->colorCurveB = previewEmitter->colorCurveB;
				placingEmitter->colorCurveA = previewEmitter->colorCurveA;																
				placingEmitter->setParticleBlendingMode(previewEmitter->getParticleBlendingMode());
				
				placingEmitter->setParticleTexture(previewEmitter->getParticleTexture());

				placingEmitter->setAnchorPoint(0.0, 0.0, 0.0);

				placingEmitter->setWidth(placingEmitter->emitterRadius.x);
				placingEmitter->setHeight(placingEmitter->emitterRadius.y);			

				createParticleRef(placingEmitter);
				
				if(treeView) {
					treeView->Refresh();		
				}
				
				PolycodeScreenEditorActionData *beforeData = new PolycodeScreenEditorActionData();
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				data->reverse = false;
				data->entry = PolycodeScreenEditorActionDataEntry(placingEmitter);
				beforeData->entry = PolycodeScreenEditorActionDataEntry(placingEmitter);				
				editor->didAction("create_entity", beforeData, data);
																										
		}
		break;			
		case MODE_SPRITE:
		{
				SceneSprite *placingSprite = new SceneSprite(previewSprite->getFileName());			
				placingSprite->setPosition(previewSprite->getPosition2D());
				placingSprite->processInputEvents = true;
				placingSprite->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingSprite->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				currentLayer->addChild(placingSprite);
				placingSprite->id = "SceneSprite."+String::IntToString(placementCount);
				placingSprite->blockMouseInput = true;
				placingSprite->getTexture()->reloadOnFileModify = true;
				placingSprite->getResourceEntry()->reloadOnFileModify = true;
								
				if(previewSprite->getCurrentAnimation()) {
						placingSprite->playAnimation(previewSprite->getCurrentAnimation()->name, 0, false);
				}
				
				placementCount++;	


				if(treeView) {
					treeView->Refresh();		
				}
				
				PolycodeScreenEditorActionData *beforeData = new PolycodeScreenEditorActionData();
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				data->reverse = false;
				data->entry = PolycodeScreenEditorActionDataEntry(placingSprite);
				beforeData->entry = PolycodeScreenEditorActionDataEntry(placingSprite);				
				editor->didAction("create_entity", beforeData, data);
																										
		}
		break;		
		case MODE_LINK:
		{
				SceneEntityInstance *placingInstance = new SceneEntityInstance(previewInstance->getFileName());
				placingInstance->setPosition(previewInstance->getPosition2D());
				placingInstance->processInputEvents = true;
				placingInstance->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingInstance->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				currentLayer->addChild(placingInstance);
				placingInstance->id = "ScreenInstance."+String::IntToString(placementCount);				
				placingInstance->blockMouseInput = true;
				placementCount++;	
								
				applyEditorProperties(placingInstance);

				if(treeView) {
					treeView->Refresh();		
				}

				PolycodeScreenEditorActionData *beforeData = new PolycodeScreenEditorActionData();
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				data->reverse = false;
				data->entry = PolycodeScreenEditorActionDataEntry(placingInstance);
				beforeData->entry = PolycodeScreenEditorActionDataEntry(placingInstance);				
				editor->didAction("create_entity", beforeData, data);
															
		}
		break;		
		case MODE_ENTITY:
		{
				Entity *placingEntity = new Entity();
				placingEntity->setPosition(previewEntity->getPosition2D());
				placingEntity->processInputEvents = true;
				placingEntity->setAnchorPoint(0.0, 0.0, 0.0);
				placingEntity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingEntity->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				placingEntity->setWidth(50);
				placingEntity->setHeight(50);				
				currentLayer->addChild(placingEntity);
				placingEntity->id = "Entity."+String::IntToString(placementCount);
				placingEntity->blockMouseInput = true;	
				placementCount++;
								
				createEntityRef(placingEntity);				

				if(treeView) {
					treeView->Refresh();		
				}

				PolycodeScreenEditorActionData *beforeData = new PolycodeScreenEditorActionData();
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				data->reverse = false;
				data->entry = PolycodeScreenEditorActionDataEntry(placingEntity);
				beforeData->entry = PolycodeScreenEditorActionDataEntry(placingEntity);				
				editor->didAction("create_entity", beforeData, data);
				
								
		}
		break;
		case MODE_SOUND:
		{
				Sound *sound = previewSound->getSound();
				
				SceneSound *placingSound = new SceneSound(sound->getFileName(), sound->getReferenceDistance(), sound->getMaxDistance());
				placingSound->setPosition(previewSound->getPosition2D());
				placingSound->processInputEvents = true;
				placingSound->setAnchorPoint(0.0, 0.0, 0.0);
				placingSound->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingSound->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				placingSound->setWidth(50);
				placingSound->setHeight(50);				
				currentLayer->addChild(placingSound);
				placingSound->id = "SceneSound."+String::IntToString(placementCount);
				placingSound->blockMouseInput = true;	
				placementCount++;
				
				createSoundRef(placingSound);
								
			
				if(treeView) {
					treeView->Refresh();		
				}

				PolycodeScreenEditorActionData *beforeData = new PolycodeScreenEditorActionData();
				PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
				data->reverse = false;
				data->entry = PolycodeScreenEditorActionDataEntry(placingSound);
				beforeData->entry = PolycodeScreenEditorActionDataEntry(placingSound);				
				editor->didAction("create_entity", beforeData, data);
				
																				
		}
		break;		
	}
}

void PolycodeScreenEditorMain::applyEditorOnly(Entity *entity) {
	entity->editorOnly = true;
	entity->removeAllHandlersForListener(this);
	for(int i=0; i < entity->getNumChildren(); i++) {
		applyEditorOnly((Entity*)entity->getChildAtIndex(i));
	}
}

void PolycodeScreenEditorMain::createEntityRef(Entity *entity) {
	UIImage *markerImage = new UIImage("Images/ScreenEditor/entity_marker.png");
	entity->addChild(markerImage);
	markerImage->setAnchorPoint(0.0, 0.0, 0.0);
	markerImage->editorOnly = true;
	markerImage->billboardMode = true;
	markerImage->billboardIgnoreScale = true;
	markerImage->addTag("editorRef");
	
	EntityNameDisplay *nameDisplay = new EntityNameDisplay(entity);
	entity->addChild(nameDisplay);
	nameDisplay->billboardMode = true;
	nameDisplay->billboardIgnoreScale = true;
	
}

void PolycodeScreenEditorMain::createParticleRef(SceneParticleEmitter *target) {

	UIImage *markerImage = new UIImage("Images/particle_system_icon_editor.png");
	markerImage->addTag("editorRef");
	markerImage->setColor(0.0, 1.0, 1.0, 1.0);
	target->addChild(markerImage);
	markerImage->setAnchorPoint(0.0, 0.0, 0.0);
	markerImage->editorOnly = true;
	markerImage->billboardMode = true;
	markerImage->billboardIgnoreScale = true;
	
	ScenePrimitive *refRect = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, target->emitterRadius.x, target->emitterRadius.y);
	
	refRect->strokeEnabled = true;
	refRect->strokeWidth = 1.0;
	refRect->addTag("editorRef");
	refRect->id = "refRect";
	refRect->setStrokeColor(1.0, 1.0, 0.0, 0.5);
	refRect->setColor(0.0, 0.0, 0.0, 0.0);
	target->addChild(refRect);
	refRect->editorOnly = true;				
		
}

void PolycodeScreenEditorMain::createSoundRef(SceneSound *target) {
	UIImage *markerImage = new UIImage("Images/ScreenEditor/screen_sound_icon.png");
	target->addChild(markerImage);
	markerImage->setAnchorPoint(0.0, 0.0, 0.0);
	markerImage->editorOnly = true;
	markerImage->billboardMode = true;
	markerImage->billboardIgnoreScale = true;
	markerImage->addTag("editorRef");
		
	ScenePrimitive *refCircle = new ScenePrimitive(ScenePrimitive::SHAPE_CIRCLE, target->getSound()->getReferenceDistance(), target->getSound()->getReferenceDistance(), 16);
	refCircle->strokeEnabled = true;
	refCircle->strokeWidth = 1.0;
	refCircle->id = "refCircle";
	refCircle->setStrokeColor(1.0, 0.5, 0.0, 0.5);
	refCircle->setColor(0.0, 0.0, 0.0, 0.0);
	target->addChild(refCircle);
	refCircle->editorOnly = true;				
	refCircle->addTag("editorRef");
		
	ScenePrimitive *maxCircle = new ScenePrimitive(ScenePrimitive::SHAPE_CIRCLE, target->getSound()->getMaxDistance(), target->getSound()->getMaxDistance(), 16);
	maxCircle->strokeEnabled = true;
	maxCircle->strokeWidth = 1.0;
	maxCircle->id = "maxCircle";				
	maxCircle->addTag("editorRef");	
	maxCircle->setStrokeColor(0.0, 1.0, 1.0, 0.5);
	maxCircle->setColor(0.0, 0.0, 0.0, 0.0);
	target->addChild(maxCircle);
	maxCircle->editorOnly = true;
}

bool PolycodeScreenEditorMain::hasSelected(Entity *entity) {
	for(int i=0; i < selectedEntities.size(); i++) {
		if(selectedEntities[i] == entity) {
			return true;
		}
	}
	return false;
}

void PolycodeScreenEditorMain::resetSelectedEntityTransforms() {
	baseEntityPositions.clear();
	baseEntityScales.clear();
	baseRotateAngles.clear();
	
	for(int i=0; i < selectedEntities.size(); i++) {
		baseEntityPositions.push_back(selectedEntities[i]->getPosition2D());	
		baseEntityScales.push_back(selectedEntities[i]->getScale2D());
		baseRotateAngles.push_back(selectedEntities[i]->getRotation());
	}
	
	Number width;
	Number height;
	getCenterAndSizeForSelected(&groupCenterPoint, &width, &height);					
	
	groupRoll = 0;
}

void PolycodeScreenEditorMain::selectEntity(Entity *entity, bool doAction) {

	((Entity*)baseEntity->getParentEntity())->focusChild(baseEntity);

	if(entity != NULL) {
		if(hasSelected(entity)) {
			resetSelectedEntityTransforms();
			return;
		}
	}	
	
	if(doAction) {
		beforeData = new PolycodeScreenEditorActionData();
		for(int i=0; i < selectedEntities.size(); i++) {
			beforeData->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]));
		}		
	}	

	transform2dSheet->entity = NULL;
	entitySheet->entity = NULL;
	shapeSheet->shape = NULL;
	imageSheet->image = NULL;
	labelSheet->label = NULL;
	soundSheet->sound = NULL;
	instanceSheet->instance = NULL;
	particleSheet->emitter = NULL;
	spriteSheet->sprite = NULL;
	entityPropSheet->entity = NULL;
	EntitySheet->entity = NULL;
				
	if(!entity) {
		selectedEntities.clear();
		screenTransform->visible = false;
		screenTransform->enabled = false;
		screenTransformShape->visible = false;			
		entityProps->updateProps();
		selectedEntities.clear();
		baseEntityPositions.clear();
		if(treeView) {
			treeView->Refresh();		
		}
		if(doAction) {
			editor->didAction("select", beforeData, NULL, false);
		}
		return;
	}
	
	if(!multiSelect) {
		selectedEntities.clear();
	}
		
	selectedEntities.push_back(entity);
	
	resetSelectedEntityTransforms();
	
	Entity *parent = NULL;
	parent = (Entity*)entity->getParentEntity();
	
	if(entity->getEntityProp("editor_type") != "layer" && entity != layerBaseEntity) {	
		transform2dSheet->entity = entity;
	}
	
	if(entity != layerBaseEntity && entity->getEntityProp("editor_type") != "layer") {
		entitySheet->entity = entity;
		entityPropSheet->entity = entity;
		EntitySheet->entity = entity;
	} else {
		entitySheet->entity = entity;
		if(entity == layerBaseEntity) {
			entityPropSheet->entity = entity;		
			EntitySheet->entity = entity;			
		}
	}

	if(dynamic_cast<SceneParticleEmitter*>(entity)) {
		particleSheet->emitter = (SceneParticleEmitter*) entity;
	}
	
	if(dynamic_cast<SceneSprite*>(entity)) {
		spriteSheet->sprite = (SceneSprite*) entity;
	}
	
	if(dynamic_cast<ScenePrimitive*>(entity)) {
		shapeSheet->shape = (ScenePrimitive*) entity;
		EntitySheet->entity = NULL;
	}

	if(dynamic_cast<UIImage*>(entity)) {
		imageSheet->image = (UIImage*) entity;
	}

	if(dynamic_cast<SceneLabel*>(entity)) {
		labelSheet->label = (SceneLabel*) entity;
	}

	if(dynamic_cast<SceneSound*>(entity)) {
		soundSheet->sound = ((SceneSound*) entity);
	}
	
	if(dynamic_cast<SceneEntityInstance*>(entity) && entity != layerBaseEntity) {
		instanceSheet->instance = ((SceneEntityInstance*) entity);
	}
			
		
	if(entity->getEntityProp("editor_type") != "layer" && entity != layerBaseEntity) {
		screenTransform->visible = true;
		screenTransform->enabled = true;	
		screenTransformShape->visible = true;
	} else {
		screenTransform->visible = false;
		screenTransform->enabled = false;	
		screenTransformShape->visible = false;	
	}
	
	syncTransformToSelected();	
		
	entityProps->updateProps();	
	
	if(treeView) {
		treeView->Refresh();		
	}
	
	if(doAction) {
		PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
		for(int i=0; i < selectedEntities.size(); i++) {
			data->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]));
		}			
		editor->didAction("select", beforeData, data, false);
	}	
	
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void PolycodeScreenEditorMain::resizePreviewScreen() {
	previewAspectRatio = aspects[aspectComboBox->getSelectedIndex()];
	Number scaleVal = 1.0/atof(scaleInput->getText().c_str());		
	screenPreviewShape->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, 1.0/scaleVal * previewAspectRatio * objectBaseEntity->getScale().x, 1.0/scaleVal * objectBaseEntity->getScale().x);
	
	sizePreviewShape->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, layerBaseEntity->getWidth() * objectBaseEntity->getScale().x, layerBaseEntity->getHeight() * objectBaseEntity->getScale().x);

}

void PolycodeScreenEditorMain::setRefVisibility(bool val) {
		setEntityRefVisibility(objectBaseEntity, val);
}

void PolycodeScreenEditorMain::setEntityRefVisibility(Entity *entity, bool val) {
	if(entity->editorOnly == true) {
		if(entity->hasTag("editorRef")) {
			entity->visible = val;
		}
	}
	
	for(int i=0; i < entity->getNumChildren(); i++) {
		setEntityRefVisibility((Entity*)entity->getChildAtIndex(i), val);
	}
}

void PolycodeScreenEditorMain::deleteEntity(Entity *entity) {				
	if(entity == layerBaseEntity) {
		PolycodeConsole::print("You cannot delete the root entity.\n");
	} else if(entity->getEntityProp("editor_type") == "layer" && layers.size() == 1) {
		PolycodeConsole::print("You cannot delete the last layer.\n");						
	} else {
		entity->ownsChildren = true;
		entity->getParentEntity()->removeChild(entity);

		if(entity->getEntityProp("editor_type") == "layer") {
			for(int i=0; i < layers.size(); i++) {
				if(layers[i] == entity) {
					layers.erase(layers.begin()+i);
				}
			}
		}							

		if(entity == currentLayer) {
				setCurrentLayer(layers[0]);
				treeView->targetLayer = currentLayer;
		}
		treeView->Refresh();
	}
}

void PolycodeScreenEditorMain::handleEvent(Event *event) {

	if(event->getEventCode() == Event::RESOURCE_RELOAD_EVENT && event->getEventType() == "") {
			SceneEntityInstanceResourceEntry *entry = dynamic_cast<SceneEntityInstanceResourceEntry*>(event->getDispatcher());
			if(entry) {	
				applyEditorProperties(entry->getInstance());
				applyEditorOnlyChildren(entry->getInstance());				
			}
	}
	
	if(!editor->enabled)
		return;		

	InputEvent *inputEvent = (InputEvent*) event;		
	if(event->getEventCode() == UIEvent::CHANGE_EVENT && event->getEventType() == "UIEvent") {


		if(event->getDispatcher() == pixelSnapBox) {
			pixelSnap = pixelSnapBox->isChecked();
		} else if(event->getDispatcher() == gridSnapBox) {
			gridSnap = gridSnapBox->isChecked();
		} else if(event->getDispatcher() == gridSizeInput) {
			setGrid(atoi(gridSizeInput->getText().c_str()));
		} else if(event->getDispatcher() == gridCheckBox) {
			grid->visible = gridCheckBox->isChecked();
		} else if(event->getDispatcher() == scaleInput) {
			resizePreviewScreen();
		} else if(event->getDispatcher() == zoomComboBox) {
			if(zoomComboBox->getSelectedIndex() != 7) {
				Number newScale = zooms[zoomComboBox->getSelectedIndex()];
				objectBaseEntity->setScale(newScale, newScale);
//				baseEntity->setPosition(getWidth()/2.0, getHeight()/2.0);
				resizePreviewScreen();
				syncTransformToSelected();				
			}
		}else if(event->getDispatcher() == aspectComboBox) {
			resizePreviewScreen();
		} else if(event->getDispatcher() == showRefsBox) {
			setRefVisibility(showRefsBox->isChecked());
			sizePreviewShape->visible = showRefsBox->isChecked();
		}
	}

	if(event->getDispatcher() == particleSheet && event->getEventType() == "") {	
		if(particleSheet->emitter) {
		ScenePrimitive *refRect = (ScenePrimitive*) particleSheet->emitter->getEntityById("refRect", false);
		if(refRect) {
			refRect->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, particleSheet->emitter->emitterRadius.x, particleSheet->emitter->emitterRadius.y);
			particleSheet->emitter->setWidth(particleSheet->emitter->emitterRadius.x);
			particleSheet->emitter->setHeight(particleSheet->emitter->emitterRadius.y);			
		}
		}

	}
	
	if(event->getDispatcher() == soundSheet && event->getEventType() == "") {	
		ScenePrimitive *refCircle = (ScenePrimitive*) soundSheet->sound->getEntityById("refCircle", false);
		if(refCircle) {
			refCircle->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, soundSheet->sound->getSound()->getReferenceDistance(), soundSheet->sound->getSound()->getReferenceDistance());
		}

		ScenePrimitive *maxCircle = (ScenePrimitive*) soundSheet->sound->getEntityById("maxCircle", false);
		if(maxCircle) {
			maxCircle->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, soundSheet->sound->getSound()->getMaxDistance(), soundSheet->sound->getSound()->getMaxDistance());
		}

		
	}

	if(event->getDispatcher() == entityPropSheet && event->getEventType() == "") {
			entityProps->updateSize();
			entityProps->scrollContainer->setScrollValue(0.0, 1.0);
	}
	
	if(event->getEventCode() == PropEvent::EVENT_PROP_CHANGE) {
		PropEvent *propEvent  = (PropEvent*) event;
		editor->didAction("prop_change", propEvent->beforeData, propEvent->afterData);
	}
	
	if((event->getDispatcher() == transform2dSheet || event->getDispatcher() == labelSheet || event->getDispatcher() == imageSheet || event->getDispatcher() == shapeSheet || event->getDispatcher() == EntitySheet) && event->getEventType() == "") {
		syncTransformToSelected();
		treeView->Refresh();		
	}
	
	if(event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput()) {
		if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
			switch(inputEvent->key) {
				case Polycode::KEY_ESCAPE:
					if(selectedEntities.size() > 0) {
						scalingY = false;
						scalingX = false;
						moving = false;
						rotating = false;
						selectEntity(NULL);
					}
				break;
				case Polycode::KEY_BACKSPACE:
				{
					if(selectedEntities.size() > 0 && baseEntity->hasFocus) {
							
						PolycodeScreenEditorActionData *oldData = new PolycodeScreenEditorActionData();
						PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
						data->reverse = false;
						for(int i=0; i < selectedEntities.size(); i++) {
							oldData->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]));
							data->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]));
						}			
					
						for(int i=0; i < selectedEntities.size(); i++) {
							deleteEntity(selectedEntities[i]);
						}
									
						editor->didAction("delete", oldData, data); 						
						selectEntity(NULL, false);
					}
				}
				break;
				case Polycode::KEY_SPACE:
				{
					if(mode != MODE_PAN) {
						lastMode = mode;
						mode = MODE_PAN;
						updateCursor();
					}
				}	
				break;				
				case Polycode::KEY_RSHIFT:
				case Polycode::KEY_LSHIFT:
					multiSelect = true;
				break;
				default:
					// We don't care about the other keys
				break;
			}
		}
		
		if(event->getEventCode() == InputEvent::EVENT_KEYUP) {
			switch(inputEvent->key) {
				case Polycode::KEY_SPACE:
				{
					if(mode == MODE_PAN) {
						mode = lastMode;
						panning = false;
						updateCursor();					
					}
				}	
				break;
				case Polycode::KEY_RSHIFT:
				case Polycode::KEY_LSHIFT:
					multiSelect = false;
				break;
				default:
					// We don't care about the other keys
				break;
			}
		}
	
		
	}

	if(event->getDispatcher() == transformScalerXY) {
		if(selectedEntities.size() > 0) {
			scalingY = true;
			scalingX = true;			
			resetSelectedEntityTransforms();
			beforeData = new PolycodeScreenEditorActionData();
			for(int i=0; i < selectedEntities.size(); i++) {
				beforeData->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]->scale));
			}			
			mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();			
			baseScaleScreenPosition = screenTransform->getScreenPosition();
		}	
	} else if(event->getDispatcher() == transformScalerY) {
		if(selectedEntities.size() > 0) {
			scalingY = true;
			resetSelectedEntityTransforms();
			beforeData = new PolycodeScreenEditorActionData();			
			for(int i=0; i < selectedEntities.size(); i++) {
				beforeData->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]->scale));
			}						
			mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();			
		}
	} else if(event->getDispatcher() == transformScalerX) {
		if(selectedEntities.size() > 0) {
			scalingX = true;
			resetSelectedEntityTransforms();
			beforeData = new PolycodeScreenEditorActionData();			
			for(int i=0; i < selectedEntities.size(); i++) {
				beforeData->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]->scale));
			}						
			mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();			
		}
	} else if(event->getDispatcher() == transformRotator) {
		if(selectedEntities.size() > 0) {
			baseScaleScreenPosition = screenTransform->getScreenPosition();		
			rotating = true;
			resetSelectedEntityTransforms();
			mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();
			beforeData = new PolycodeScreenEditorActionData();			
			for(int i=0; i < selectedEntities.size(); i++) {
				beforeData->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]->position, selectedEntities[i]->getRotation()));
			}
			
			Vector2 diff = mouseBase - screenTransform->getScreenPosition();
			baseAngle = atan2(diff.x, diff.y);
			groupRoll = -baseAngle;
		}
	}
	

	if(event->getEventCode() == UIEvent::CLICK_EVENT && event->getEventType() == "UIEvent") {
	
		if(event->getDispatcher() == moveUpButton) {
			for(int i=0; i < selectedEntities.size(); i++) {
				if(selectedEntities[i]->getParentEntity()) {
					((Entity*)selectedEntities[i]->getParentEntity())->moveChildUp(selectedEntities[i]);
				}
			}
		}

		if(event->getDispatcher() == moveDownButton) {
			for(int i=0; i < selectedEntities.size(); i++) {
				if(selectedEntities[i]->getParentEntity()) {
					((Entity*)selectedEntities[i]->getParentEntity())->moveChildDown(selectedEntities[i]);
				}
			}
		}

		if(event->getDispatcher() == moveTopButton) {
			for(int i=0; i < selectedEntities.size(); i++) {
				if(selectedEntities[i]->getParentEntity()) {
					((Entity*)selectedEntities[i]->getParentEntity())->moveChildTop(selectedEntities[i]);
				}
			}
		}

		if(event->getDispatcher() == moveTopButton) {
			for(int i=0; i < selectedEntities.size(); i++) {
				if(selectedEntities[i]->getParentEntity()) {
					((Entity*)selectedEntities[i]->getParentEntity())->moveChildTop(selectedEntities[i]);
				}
			}
		}

		if(event->getDispatcher() == moveBottomButton) {
			for(int i=0; i < selectedEntities.size(); i++) {
				if(selectedEntities[i]->getParentEntity()) {
					((Entity*)selectedEntities[i]->getParentEntity())->moveChildBottom(selectedEntities[i]);
				}
			}
		}

		if(event->getDispatcher() == unparentButton) {
			for(int i=0; i < selectedEntities.size(); i++) {
				if(selectedEntities[i]->getParentEntity()) {
					selectedEntities[i]->getParentEntity()->removeChild(selectedEntities[i]);
					currentLayer->addChild(selectedEntities[i]);
				}
			}
			syncTransformToSelected();			
		}
			
	
		if(event->getDispatcher() == arrowToolButton) {
			selectorImage->setPosition(arrowToolButton->getPosition().x - 4, arrowToolButton->getPosition().y - 4);
			setMode(MODE_SELECT);
		}

		if(event->getDispatcher() == shapeToolButton) {
			selectorImage->setPosition(shapeToolButton->getPosition().x - 4, shapeToolButton->getPosition().y - 4);
			setMode(MODE_SHAPE);
		}

		if(event->getDispatcher() == soundToolButton) {
			selectorImage->setPosition(soundToolButton->getPosition().x - 4, soundToolButton->getPosition().y - 4);
			setMode(MODE_SOUND);
		}


		if(event->getDispatcher() == zoomToolButton) {
			selectorImage->setPosition(zoomToolButton->getPosition().x - 4, zoomToolButton->getPosition().y - 4);
			setMode(MODE_ZOOM);
		}

		if(event->getDispatcher() == panToolButton) {
			selectorImage->setPosition(panToolButton->getPosition().x - 4, panToolButton->getPosition().y - 4);
			setMode(MODE_PAN);
		}

		if(event->getDispatcher() == imageToolButton) {
			selectorImage->setPosition(imageToolButton->getPosition().x - 4, imageToolButton->getPosition().y - 4);
			setMode(MODE_IMAGE);
		}

		if(event->getDispatcher() == textToolButton) {
			selectorImage->setPosition(textToolButton->getPosition().x - 4, textToolButton->getPosition().y - 4);
			setMode(MODE_TEXT);
		}
		
		if(event->getDispatcher() == parentToolButton) {
			selectorImage->setPosition(parentToolButton->getPosition().x - 4, parentToolButton->getPosition().y - 4);
			setMode(MODE_PARENT);
		}

		if(event->getDispatcher() == linkToolButton) {
			selectorImage->setPosition(linkToolButton->getPosition().x - 4, linkToolButton->getPosition().y - 4);
			setMode(MODE_LINK);
		}

		if(event->getDispatcher() == spriteToolButton) {
			selectorImage->setPosition(spriteToolButton->getPosition().x - 4, spriteToolButton->getPosition().y - 4);
			setMode(MODE_SPRITE);
		}

		if(event->getDispatcher() == particlesToolButton) {
			selectorImage->setPosition(particlesToolButton->getPosition().x - 4, particlesToolButton->getPosition().y - 4);
			setMode(MODE_PARTICLES);
		}



		if(event->getDispatcher() == entityToolButton) {
			selectorImage->setPosition(entityToolButton->getPosition().x - 4, entityToolButton->getPosition().y - 4);
			setMode(MODE_ENTITY);
		}
	}
		
	if(currentLayer) {
		for(int i=0; i < currentLayer->getNumChildren(); i++) {
			Entity* childEntity = (Entity*) currentLayer->getChildAtIndex(i);
			processEventForEntity(childEntity, inputEvent);
		}
	}
	
	if(event->getDispatcher() == baseEntity) {
		switch (event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				firstMove = true;
				handleMouseDown(inputEvent->mousePosition);
				focusChild(baseEntity);
			break;		
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:			
				firstMove = false;
				handleMouseUp(inputEvent->mousePosition);
			break;
			case InputEvent::EVENT_MOUSEOUT:
				CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_ARROW);
			break;
			case InputEvent::EVENT_MOUSEMOVE:
			{
				if(firstMove) {
					Core *core = CoreServices::getInstance()->getCore();
					if((core->getInput()->getKeyState(COPYMOD_1) || core->getInput()->getKeyState(COPYMOD_2)) && selectedEntities.size() > 0) {
						void *data;
						String type = Copy(&data);
						if(data) {
							Paste(data, type);
							destroyClipboardData(data, type);
						}
						beforeData = new PolycodeScreenEditorActionData();						
						for(int i=0; i < selectedEntities.size(); i++) {
							beforeData->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]->position));
						}															
					}
					firstMove = false;					
				}
				updateCursor();
				handleMouseMove(inputEvent->mousePosition);
			}
			break;			
		}
		return;
	}

}

void PolycodeScreenEditorMain::processEventForEntity(Entity *childEntity, InputEvent *inputEvent) {

		for(int i=0; i < childEntity->getNumChildren(); i++) {
			processEventForEntity((Entity*)childEntity->getChildAtIndex(i), inputEvent);
		}

		if(inputEvent->getDispatcher() == childEntity) {
		
			if(inputEvent->getEventCode() == InputEvent::EVENT_MOUSEUP) {
				if(mode == MODE_PARENT && parenting == true) {
					parenting = false;
					if(parentingChild && (parentingChild != childEntity)) {
						parentingChild->getParentEntity()->removeChild(parentingChild);
						childEntity->addChild(parentingChild);
						syncTransformToSelected();						
					}
					parentingLine->visible = false;
				}
			}
							
			if(inputEvent->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				if(mode == MODE_SELECT) {
					selectEntity(childEntity);
					if(selectedEntities.size() > 0) {
						moving = true;
						beforeData = new PolycodeScreenEditorActionData();						
						for(int i=0; i < selectedEntities.size(); i++) {
							beforeData->entries.push_back(PolycodeScreenEditorActionDataEntry(selectedEntities[i]->position));
						}									
						mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();
					}					
					return;
				}

				if(mode == MODE_PARENT) {
					parenting = true;
					parentingChild = childEntity;
					parentingLine->visible = true;
					
					Matrix4 m1 = childEntity->getConcatenatedMatrix();
					Matrix4 m2 = baseEntity->getConcatenatedMatrix();
					
					Matrix4 final = m1 - m2;
					Vector3 pos;
					
					pos = final * pos;
					
					parentingLine->setStart(Vector2(pos.x, pos.y));
					parentingLine->setEnd(Vector2(pos.x, pos.y));
					return;
				}
			}
		}
}


Entity *PolycodeScreenEditorMain::addNewLayer(String layerName) {
	Entity *newLayer = new Entity();
	newLayer->id = layerName;
	layerBaseEntity->addChild(newLayer);
	setCurrentLayer(newLayer, false);
	treeView->targetLayer = newLayer;	
	newLayer->setEntityProp("editor_type", "layer");	
	selectEntity(currentLayer);	
	layers.push_back(newLayer);
	treeView->Refresh();	
	return newLayer;
}

void PolycodeScreenEditorMain::setMode(int newMode) {
	mode = newMode;

	previewShape->visible = false;
	previewImage->visible = false;
	previewLabel->visible = false;
	previewEntity->visible = false;
	previewSound->visible = false;
	previewInstance->visible = false;	
	previewSprite->visible = false;	
	previewEmitter->visible = false;	
			
	parentingLine->visible = false;
	parenting = false;
	
	selectEntity(NULL, false);
	
	switch(mode) {
		case MODE_SHAPE:
			previewShape->visible = true;	
			shapeSheet->shape = previewShape;
			entityProps->updateProps();					
		break;
		case MODE_IMAGE:
			previewImage->visible = true;	
			imageSheet->image = previewImage;
			entityProps->updateProps();					
		break;
		case MODE_TEXT:
			previewLabel->visible = true;	
			labelSheet->label = previewLabel;
			entityProps->updateProps();				
		break;
		case MODE_ENTITY:
			previewEntity->visible = true;	
			entityProps->updateProps();				
		break;
		case MODE_SOUND:
			previewSound->visible = true;
			soundSheet->sound = previewSound;
			entityProps->updateProps();				
		break;
		case MODE_LINK:
			previewInstance->visible = true;
			instanceSheet->instance = previewInstance;
			entityProps->updateProps();				
		break;
		case MODE_SPRITE:
			previewSprite->visible = true;
			spriteSheet->sprite = previewSprite;
			entityProps->updateProps();				
		break;
		case MODE_PARTICLES:
			previewEmitter->visible = true;
			particleSheet->emitter =  previewEmitter;
			entityProps->updateProps();				
		break;

	}

}

Entity *PolycodeScreenEditorMain::getCurrentLayer() {
	return currentLayer;
}

void PolycodeScreenEditorMain::setCurrentLayer(Entity *newLayer, bool doAction) {

	if(doAction) {
		beforeData = new PolycodeScreenEditorActionData();
		beforeData->entry.entity = currentLayer;
	}

	if(currentLayer) {
		currentLayer->processInputEvents = false;
	}
	currentLayer = newLayer;
	if(currentLayer) {
		currentLayer->processInputEvents = true;
	}
	
	if(doAction) {
		PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
		data->entry.entity = currentLayer;
		editor->didAction("set_current_layer", beforeData, data, false);
	}
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void PolycodeScreenEditorMain::Resize(Number width, Number height) {


	viewOptionsBg->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, ceil(width), 30);
	viewOptions->setPosition(0, height-30);

	propertiesBg->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, ceil(width), 30);
	
	toolPaletteBg->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, 100,height-60);
			
	if(firstResize && width > 0.0 && height > 0.0) {
		baseEntity->setPosition(width/2.0, height/2.0);
		firstResize = false;
	}
	
	UIElement::Resize(getWidth(), getHeight());
}

void PolycodeScreenEditorMain::handleDroppedFile(OSFileEntry file, Number x, Number y) {

	Entity *newEntity = NULL;
	
	if(file.extension == "png") {
		UIImage *newImage = new UIImage(file.fullPath);
		newImage->setAnchorPoint(0.0, 0.0, 0.0);
		currentLayer->addChild(newImage);
		newImage->setPosition(x-baseEntity->getPosition2D().x,y-baseEntity->getPosition2D().y);
		newEntity = newImage;
		newImage->processInputEvents = true;
	}
	
	if(newEntity) {
		newEntity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
		newEntity->blockMouseInput = true;
	}
}

PolycodeScreenEditor::PolycodeScreenEditor() : PolycodeEditor(true){

	mainSizer = new UIHSizer(100,100,340,false);
	addChild(mainSizer);	

	editorMain = new PolycodeScreenEditorMain(this);
	editorMain->addEventListener(this, Event::CHANGE_EVENT);
	mainSizer->addLeftChild(editorMain);
	
	propSizer = new PropertiesSizer();
	mainSizer->addRightChild(propSizer);
	
	treeView = new EntityTreeView(editorMain->layerBaseEntity);
	treeView->addEventListener(this, Event::CHANGE_EVENT);

	editorMain->treeView = treeView;

	treeView->newLayerButton->addEventListener(this, UIEvent::CLICK_EVENT);
	treeView->targetLayerButton->addEventListener(this, UIEvent::CLICK_EVENT);
		
	propSizer->sizer->addTopChild(treeView);
	propSizer->sizer->addBottomChild(editorMain->entityProps);
	
	propSizer->sizer->blockMouseInput = true;

	treeView->Refresh();
}

String PolycodeScreenEditor::Copy(void **data) {
	if(editorMain->baseEntity->hasFocus) {
		return editorMain->Copy(data);
	} else {
		return "";
	}
}

void PolycodeScreenEditor::Paste(void *data, String clipboardType) {
	if(editorMain->baseEntity->hasFocus) {
		editorMain->Paste(data, clipboardType);
	}
}

void PolycodeScreenEditor::destroyClipboardData(void *data, String type) {
	editorMain->destroyClipboardData(data, type);
}

String PolycodeScreenEditorMain::Copy(void **data) {
	if(selectedEntities.size() > 0) {
		EntityClipboardData *newData = new EntityClipboardData();
		for(int i=0; i < selectedEntities.size(); i++) {
			Entity *clone = (Entity*)selectedEntities[i]->Clone(true, true);
			newData->entities.push_back(clone);
		}
		*data = (void*) newData;
	}
	return "Entity";
}

void PolycodeScreenEditorMain::Paste(void *data, String clipboardType) {
	if(!data)
		return;
	if(clipboardType == "Entity") {
		selectEntity(NULL);
		multiSelect = true;
		EntityClipboardData *newData = (EntityClipboardData*) data;
		if(currentLayer) {
		
			PolycodeScreenEditorActionData *beforeData = new PolycodeScreenEditorActionData();
			PolycodeScreenEditorActionData *data = new PolycodeScreenEditorActionData();
			data->reverse = false;
	
			for(int i=0; i < newData->entities.size(); i++) {
				Entity *entity = (Entity*) newData->entities[i]->Clone(true, true);
				entity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				entity->addEventListener(this, InputEvent::EVENT_MOUSEUP);
				
				bool addToLayer = true;
				if(selectedEntities.size() > 0) {
					if(selectedEntities[0] != currentLayer) {
						selectedEntities[0]->getParentEntity()->addChild(entity);
						addToLayer = false;
					}
				}
				
				if(addToLayer) {
					currentLayer->addChild(entity);
				}
				applyEditorProperties(entity);
				selectEntity(entity, false);

				beforeData->entries.push_back(PolycodeScreenEditorActionDataEntry(entity));				
				data->entries.push_back(PolycodeScreenEditorActionDataEntry(entity));
				
			}
			
			editor->didAction("paste", beforeData, data);			
		}
		multiSelect = false;
	}
	if(treeView) {
		treeView->Refresh();		
	}											
}

void PolycodeScreenEditorMain::destroyClipboardData(void *data, String type) {
	if(type == "Entity") {
		EntityClipboardData *oldData = (EntityClipboardData*) data;
		for(int i=0; i < oldData->entities.size(); i++) {
			delete oldData->entities[i];
		}
		delete oldData;
	}
}

void PolycodeScreenEditor::Activate() {
	editorMain->labelSheet->refreshFonts();
}

void PolycodeScreenEditor::doAction(String actionName, PolycodeEditorActionData *data) {
	editorMain->doAction(actionName, data);
}

void PolycodeScreenEditor::saveCurveToObject(ObjectEntry *entry, BezierCurve *curve) {
	ObjectEntry *controlPoints = entry->addChild("controlPoints");
	
	for(int i=0; i < curve->getNumControlPoints(); i++) {
		ObjectEntry *controlPointEntry = controlPoints->addChild("controlPoint");
		ObjectEntry *pt1 = controlPointEntry->addChild("pt1");
		pt1->addChild("x", curve->getControlPoint(i)->p1.x);
		pt1->addChild("y", curve->getControlPoint(i)->p1.y);		

		ObjectEntry *pt2 = controlPointEntry->addChild("pt2");
		pt2->addChild("x", curve->getControlPoint(i)->p2.x);
		pt2->addChild("y", curve->getControlPoint(i)->p2.y);		

		ObjectEntry *pt3 = controlPointEntry->addChild("pt3");
		pt3->addChild("x", curve->getControlPoint(i)->p3.x);
		pt3->addChild("y", curve->getControlPoint(i)->p3.y);		

	}
}

void PolycodeScreenEditor::saveEntityToObjectEntry(Entity *entity, ObjectEntry *entry) {

	if(entity->editorOnly)
		return;

	entry->addChild("id", entity->id);
	
	//if(entity->getNumTags() > 0) {
	String tagString = "";
	for(int i=0; i < entity->getNumTags(); i++) {
		if(i != 0) {
			tagString += ",";
		}
		tagString += entity->getTagAtIndex(i);
	}
	entry->addChild("tags", tagString);
	//}

	if(entity->entityProps.size() > 0) {
		ObjectEntry *props = entry->addChild("props");		
		for(int i=0; i < entity->entityProps.size(); i++) {
			ObjectEntry *prop = props->addChild("prop");
			prop->addChild("name", entity->entityProps[i].propName);
			prop->addChild("value", entity->entityProps[i].propValue);
		}
	}

	if(dynamic_cast<SceneEntityInstance*>(entity) && entity != editorMain->layerBaseEntity) {
		if(!(*(entry))["type"])
			entry->addChild("type", "SceneEntityInstance");
		SceneEntityInstance *instance = (SceneEntityInstance*) entity;
		ObjectEntry *instanceEntry = entry->addChild("SceneEntityInstance");		
		instanceEntry->addChild("filePath", instance->getFileName());
	}
	
	if(dynamic_cast<UIImage*>(entity)) {
		if(!(*(entry))["type"])
			entry->addChild("type", "UIImage");
		UIImage *image = (UIImage*) entity;
		ObjectEntry *imageEntry = entry->addChild("UIImage");		
		imageEntry->addChild("filePath", image->getTexture()->getResourcePath());
	}

	
	if(dynamic_cast<SceneParticleEmitter*>(entity)) {
		if(!(*(entry))["type"])
			entry->addChild("type", "SceneParticleEmitter");
			
		SceneParticleEmitter *emitter = (SceneParticleEmitter*) entity;
		
		ObjectEntry *emitterEntry = entry->addChild("SceneParticleEmitter");		

		emitterEntry->addChild("texturePath", emitter->getParticleTexture()->getResourcePath());
		emitterEntry->addChild("radiusX", emitter->emitterRadius.x);
		emitterEntry->addChild("radiusY", emitter->emitterRadius.y);

		emitterEntry->addChild("dirX", emitter->dirVector.x);
		emitterEntry->addChild("dirY", emitter->dirVector.y);

		emitterEntry->addChild("deviationX", emitter->deviation.x);
		emitterEntry->addChild("deviationY", emitter->deviation.y);

		emitterEntry->addChild("gravX", emitter->gravVector.x);
		emitterEntry->addChild("gravY", emitter->gravVector.y);

		emitterEntry->addChild("brightnessDeviation", emitter->brightnessDeviation);
		emitterEntry->addChild("particleSize", emitter->particleSize);
		emitterEntry->addChild("perlinModSize", emitter->perlinModSize);
		emitterEntry->addChild("perlinEnabled", emitter->perlinEnabled);
		emitterEntry->addChild("particleSpeedMod", emitter->particleSpeedMod);

		emitterEntry->addChild("rotationSpeed", emitter->rotationSpeed);
		emitterEntry->addChild("rotationFollowsPath", emitter->rotationFollowsPath);
		emitterEntry->addChild("lifespan", emitter->lifespan);
		emitterEntry->addChild("particleCount", (int)emitter->getNumParticles());

		emitterEntry->addChild("useScaleCurves", emitter->useScaleCurves);
		emitterEntry->addChild("useColorCurves", emitter->useColorCurves);

		emitterEntry->addChild("ignoreParentMatrix", emitter->getIgnoreParentMatrix());

		saveCurveToObject(emitterEntry->addChild("scaleCurve"), &emitter->scaleCurve);

		saveCurveToObject(emitterEntry->addChild("colorCurveR"), &emitter->colorCurveR);
		saveCurveToObject(emitterEntry->addChild("colorCurveG"), &emitter->colorCurveG);
		saveCurveToObject(emitterEntry->addChild("colorCurveB"), &emitter->colorCurveB);
		saveCurveToObject(emitterEntry->addChild("colorCurveA"), &emitter->colorCurveA);						

		emitterEntry->addChild("particleBlendMode", (int)emitter->getParticleBlendingMode());		
		
	}
		
	
	if(dynamic_cast<SceneSprite*>(entity)) {
		if(!(*(entry))["type"])
			entry->addChild("type", "SceneSprite");
		SceneSprite *sprite = (SceneSprite*) entity;
		
		ObjectEntry *spriteEntry = entry->addChild("SceneSprite");
		spriteEntry->addChild("filePath", sprite->getFileName());
		
		String animName = "";
		if(sprite->getCurrentAnimation()) {
			animName = sprite->getCurrentAnimation()->name;
		}
		spriteEntry->addChild("anim", animName);
	}	
	
	if(dynamic_cast<SceneLabel*>(entity)) {
		SceneLabel *label = (SceneLabel*) entity;
		
		if(!(*(entry))["type"])
			entry->addChild("type", "SceneLabel");
		ObjectEntry *labelEntry = entry->addChild("SceneLabel");		
		labelEntry->addChild("text", label->getText());
		labelEntry->addChild("font", label->getLabel()->getFont()->getFontName());
		labelEntry->addChild("size", (int)label->getLabel()->getSize());
		labelEntry->addChild("aaMode", (int)label->getLabel()->getAntialiasMode());
	}
	
	if(dynamic_cast<SceneSound*>(entity)) {
		SceneSound *sound = (SceneSound*) entity;
		
		if(!(*(entry))["type"])
			entry->addChild("type", "SceneSound");
		ObjectEntry *soundEntry = entry->addChild("SceneSound");		
		soundEntry->addChild("filePath", sound->getSound()->getFileName());
		soundEntry->addChild("refDistance", sound->getSound()->getReferenceDistance());
		soundEntry->addChild("maxDistance", sound->getSound()->getMaxDistance());
		soundEntry->addChild("volume", sound->getSound()->getVolume());
		soundEntry->addChild("pitch", sound->getSound()->getPitch());		
	}	
	
	if(dynamic_cast<ScenePrimitive*>(entity)) {
		if(!(*(entry))["type"])
			entry->addChild("type", "ScenePrimitive");	
		ScenePrimitive *shape = (ScenePrimitive*) entity;
		ObjectEntry *shapeEntry = entry->addChild("ScenePrimitive");
		shapeEntry->addChild("type", shape->getShapeType());
		shapeEntry->addChild("width", shape->getWidth());
		shapeEntry->addChild("height", shape->getHeight());
		

		shapeEntry->addChild("strokeEnabled", shape->strokeEnabled);
		shapeEntry->addChild("strokeColorR", shape->strokeColor.r);
		shapeEntry->addChild("strokeColorG", shape->strokeColor.g);
		shapeEntry->addChild("strokeColorB", shape->strokeColor.b);
		shapeEntry->addChild("strokeColorA", shape->strokeColor.a);
		shapeEntry->addChild("strokeWidth", shape->strokeWidth);

	}

	if(!(*(entry))["type"])
		entry->addChild("type", "Entity");
	
	entry->addChild("colorR", entity->color.r);
	entry->addChild("colorG", entity->color.g);
	entry->addChild("colorB", entity->color.b);
	entry->addChild("colorA", entity->color.a);
	
	entry->addChild("blendMode", entity->blendingMode);
	
	entry->addChild("scaleX", entity->scale.x);	
	entry->addChild("scaleY", entity->scale.y);
	
	entry->addChild("positionMode", entity->getPositionMode());	

	entry->addChild("rotation", entity->getRotation());	
	
	entry->addChild("posX", entity->position.x);	
	entry->addChild("posY", entity->position.y);
	
	entry->addChild("width", entity->getWidth());
	entry->addChild("height", entity->getHeight());
		
	ObjectEntry *children = NULL;
	
	for(int i=0; i < entity->getNumChildren(); i++) {
		if(!entity->getChildAtIndex(i)->editorOnly) {
			if(!children)
				children = entry->addChild("children");		
			ObjectEntry *child = children->addChild("child");
			saveEntityToObjectEntry((Entity*)entity->getChildAtIndex(i), child);
		}
	}
}

void PolycodeScreenEditor::saveFile() {
	Object saveObject;
	
	saveObject.root.name = "Screen";
	ObjectEntry *children = saveObject.root.addChild("root");
	
	saveEntityToObjectEntry(editorMain->layerBaseEntity, children);	
//	saveObject.saveToXML("/Users/ivansafrin/Desktop/test2.xml");
	saveObject.saveToBinary(filePath);
	setHasChanges(false);	
}

void PolycodeScreenEditor::handleEvent(Event *event) {

	if(event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
		if(event->getDispatcher() == treeView) {			
			editorMain->selectEntity((Entity*)treeView->selectedEntity);
		}

		if(event->getDispatcher() == editorMain) {
			if(editorMain->selectedEntities.size() > 0) {
				treeView->selectedEntity = editorMain->selectedEntities[0];			
			} else {
				treeView->selectedEntity = NULL;
			}
			treeView->targetLayer = editorMain->getCurrentLayer();
			treeView->Refresh();				
		}

	}

	if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		if(event->getDispatcher() == treeView->newLayerButton) {
			editorMain->addNewLayer("new_layer");
		}

		if(event->getDispatcher() == treeView->targetLayerButton) {
			if(treeView->selectedEntity->getEntityProp("editor_type") == "layer") {
				printf("setting new layer\n");
				editorMain->setCurrentLayer((Entity*)treeView->selectedEntity);
				treeView->targetLayer = editorMain->getCurrentLayer();
				treeView->Refresh();				
			} else {
				PolycodeConsole::print("Select a layer to set as default layer.\n");
			}
		}

	}
	PolycodeEditor::handleEvent(event);
}

PolycodeScreenEditor::~PolycodeScreenEditor() {
	delete mainSizer;
	delete propSizer;
	delete treeView;
	delete editorMain;
}

void PolycodeScreenEditorMain::applyEditorOnlyChildren(Entity *entity) {
	for(int i=0; i < entity->getNumChildren(); i++) {
		applyEditorOnly((Entity*)entity->getChildAtIndex(i));
	}
}

void PolycodeScreenEditorMain::applyEditorProperties(Entity *entity) {
	
	for(int i=0; i < entity->getNumChildren(); i++) {
		applyEditorProperties((Entity*)entity->getChildAtIndex(i));
	}

	if(dynamic_cast<SceneEntityInstance*>(entity) && entity != layerBaseEntity) {
		SceneEntityInstance *instance = (((SceneEntityInstance*)entity));
		instance->cloneUsingReload = true;
		applyEditorOnlyChildren(instance);
		instance->getResourceEntry()->reloadOnFileModify = true;		
		if(!CoreServices::getInstance()->getResourceManager()->hasResource(instance->getResourceEntry())) { 
			instance->getResourceEntry()->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
			CoreServices::getInstance()->getResourceManager()->addResource(instance->getResourceEntry());
		}
	} else if(dynamic_cast<SceneSprite*>(entity)) {	
		SceneSprite *sprite = (((SceneSprite*)entity));	
		sprite->getResourceEntry()->reloadOnFileModify = true;
		if(!CoreServices::getInstance()->getResourceManager()->hasResource(sprite->getResourceEntry())) { 
			CoreServices::getInstance()->getResourceManager()->addResource(sprite->getResourceEntry());
		}		
	} else if(dynamic_cast<ScenePrimitive*>(entity)) {
	} else if(dynamic_cast<UIImage*>(entity)) {
	} else if(dynamic_cast<SceneLabel*>(entity)) {

	} else if(dynamic_cast<SceneSound*>(entity)) {
		createSoundRef((SceneSound*)entity);
	} else if(dynamic_cast<SceneParticleEmitter*>(entity)) {
		createParticleRef((SceneParticleEmitter*)entity);		
	} else {	
		if(entity != layerBaseEntity && entity->getEntityProp("editor_type") != "layer") {
			createEntityRef(entity);
		}
	}
	
	if(dynamic_cast<SceneMesh*>(entity)) {	
		Texture *texture = ((SceneMesh*)entity)->getTexture();
		if(texture) {
			texture->reloadOnFileModify = true;
		}
	}
	
	if(entity->getEntityProp("editor_type") != "layer") {
		entity->processInputEvents = true;
	}
	entity->blockMouseInput = true;
	entity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	entity->addEventListener(this, InputEvent::EVENT_MOUSEUP);	
//	entity->setAnchorPoint(0.0, 0.0, 0.0);

}
		
bool PolycodeScreenEditor::openFile(OSFileEntry filePath) {
	PolycodeEditor::openFile(filePath);	
		
	SceneEntityInstance *loadedInstance = new SceneEntityInstance(filePath.fullPath);
	
	editorMain->layerBaseEntity = loadedInstance;
	editorMain->objectBaseEntity->addChild(loadedInstance);

	editorMain->applyEditorProperties(editorMain->layerBaseEntity);

	if(editorMain->layerBaseEntity->getNumChildren() == 0) {
		editorMain->addNewLayer("default_layer");
	} else {
		editorMain->setCurrentLayer((Entity*)editorMain->layerBaseEntity->getChildAtIndex(0), false);
		treeView->targetLayer = editorMain->getCurrentLayer();
		
		for(int i=0; i < editorMain->layerBaseEntity->getNumChildren(); i++) {
			editorMain->layers.push_back((Entity*)editorMain->layerBaseEntity->getChildAtIndex(i));
		}
	}

	((Entity*)(editorMain->layerBaseEntity->getParentEntity()))->moveChildBottom(editorMain->layerBaseEntity);

	if(treeView) {
		treeView->setRootEntity(editorMain->layerBaseEntity);
		treeView->Refresh();
	}
	
	editorMain->syncTransformToSelected();
	
	return true;
}

void PolycodeScreenEditor::handleDroppedFile(OSFileEntry file, Number x, Number y) {
	editorMain->handleDroppedFile(file, x, y);
}

void PolycodeScreenEditor::Resize(int x, int y) {
	PolycodeEditor::Resize(x,y);	
	mainSizer->Resize(x,y);
}

PropertiesSizer::PropertiesSizer() : UIElement() {
	sizer = new UIVSizer(100, 100, 220, true);
	
	addChild(sizer);
}

PropertiesSizer::~PropertiesSizer() {

}

void PropertiesSizer::Resize(Number width, Number height) {
	sizer->Resize(getWidth(), getHeight());
	UIElement::Resize(getWidth(), getHeight());
}



