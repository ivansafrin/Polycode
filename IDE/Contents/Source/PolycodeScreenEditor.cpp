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


ScreenEntityNameDisplay::ScreenEntityNameDisplay(ScreenEntity *targetEntity) : ScreenEntity() {
	label = new ScreenLabel(targetEntity->id, 10, "mono");
	label->setColor(1.0, 1.0, 0.0, 1.0);
	label->setPosition(10, -20);
	
	tagsLabel = new ScreenLabel(targetEntity->id, 10, "mono");
	tagsLabel->setColor(1.0, 0.0, 1.0, 1.0);
	tagsLabel->setPosition(10, 20);

	
	addChild(label);
	addChild(tagsLabel);
	
	editorOnly = true;
	this->targetEntity = targetEntity;
	
}

void ScreenEntityNameDisplay::Update() {
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

ScreenEntityNameDisplay::~ScreenEntityNameDisplay() {

}

EntityTreeView::EntityTreeView(Entity *rootEntity) : UIElement() {

	this->rootEntity = rootEntity;

	targetLayer = NULL;

	bg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(bg);
	bg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	bg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	bg->blockMouseInput = true;
	bg->processInputEvents = true;
	
	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	ScreenLabel *label = new ScreenLabel("TREE VIEW", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(10, 3);
	
	treeContainer = new UITreeContainer("Images/entity_icon.png", L"Layers", 200, 555);
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
	ScreenEntity::handleEvent(event);
}


EntityTreeView::~EntityTreeView() {

}


void EntityTreeView::Resize(Number width, Number height) {
	setWidth(width);
	setHeight(height);
	
	bg->setShapeSize(width, height);
	headerBg->setShapeSize(width, 30);
	
	newLayerButton->setPosition(width- 30, 3);		
	targetLayerButton->setPosition(width- 55, 3);	
		
	treeContainer->Resize(width, height-30);
}


PolycodeScreenEditorMain::PolycodeScreenEditorMain() {

	multiSelect = false;
	currentLayer = NULL;
	treeView = NULL;
	placementCount = 0;
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");	
	Number padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");	

	isScalingEntity = false;
	
	selectedEntity = NULL;
	isDraggingEntity = false; 
		
	baseEntity = new ScreenEntity();
	addChild(baseEntity);
	baseEntity->processInputEvents = true;
		
	baseEntity->setPositionMode(ScreenEntity::POSITION_CENTER);	

	objectBaseEntity = new ScreenEntity();
	baseEntity->addChild(objectBaseEntity);
	objectBaseEntity->processInputEvents = true;

	screenPreviewShape = new ScreenShape(ScreenShape::SHAPE_RECT, 1, 1);
	baseEntity->addChild(screenPreviewShape);
	screenPreviewShape->setColor(1.0, 1.0, 1.0, 0.0);
	screenPreviewShape->strokeEnabled = true;
	screenPreviewShape->strokeColor = Color(1.0, 1.0, 1.0, 0.5);

	layerBaseEntity = new ScreenEntity();
	layerBaseEntity->processInputEvents = true;
	objectBaseEntity->addChild(layerBaseEntity);
	
	currentLayer = layerBaseEntity;

	placingPreviewEntity = new ScreenEntity();
	objectBaseEntity->addChild(placingPreviewEntity);
	
	previewEntity = new ScreenImage("Images/ScreenEditor/entity_marker.png");
	placingPreviewEntity->addChild(previewEntity);
	previewEntity->setPositionMode(ScreenEntity::POSITION_CENTER);
	previewEntity->billboardMode = true;
	previewEntity->billboardIgnoreScale = true;
	
	previewSound = new ScreenSound("test.wav", 50, 100);
	placingPreviewEntity->addChild(previewSound);
				
	createSoundRef(previewSound);

	
	previewEmitter = new ScreenParticleEmitter("default.png", Particle::BILLBOARD_PARTICLE, ParticleEmitter::CONTINUOUS_EMITTER, 2.0, 30, Vector3(0.0, -40.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(10.0, 10.0, 0.0));
	placingPreviewEntity->addChild(previewEmitter);
	createParticleRef(previewEmitter);
	
	previewShape = new ScreenShape(ScreenShape::SHAPE_RECT, 100, 100);
	placingPreviewEntity->addChild(previewShape);
	previewShape->setColor(1.0, 1.0, 1.0, 0.5);

	previewLabel = new ScreenLabel("Text", 24);
	previewLabel->setPositionMode(ScreenEntity::POSITION_CENTER);
	placingPreviewEntity->addChild(previewLabel);
	previewLabel->setColor(1.0, 1.0, 1.0, 0.5);
	previewLabel->positionAtBaseline = false;

	previewSprite = new ScreenSprite("default/default.sprite");
	previewSprite->setPositionMode(ScreenEntity::POSITION_CENTER);	
	placingPreviewEntity->addChild(previewSprite);
	previewSprite->setColor(1.0, 1.0, 1.0, 0.5);
	
	previewImage = new ScreenImage("default.png");
	previewImage->setPositionMode(ScreenEntity::POSITION_CENTER);
	placingPreviewEntity->addChild(previewImage);
	previewImage->setColor(1.0, 1.0, 1.0, 0.5);

	previewInstance = new ScreenEntityInstance("default/default.entity2d");
	previewInstance->setPositionMode(ScreenEntity::POSITION_CENTER);
	placingPreviewEntity->addChild(previewInstance);
	previewInstance->setColor(1.0, 1.0, 1.0, 0.5);

	grid = false;
	setGrid(16);
	
	gridSnap = false;

	centerImage = new ScreenImage("Images/ScreenEditor/screenCenter.png");
	centerImage->setPositionMode(ScreenEntity::POSITION_CENTER);
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


	screenTransformShape = new ScreenShape(ScreenShape::SHAPE_RECT, 10, 10);
	screenTransformShape->strokeColor = Color(0.0, 0.3, 1.0, 1.0);
	screenTransformShape->lineSmooth = true;
	screenTransformShape->strokeEnabled = true;
	screenTransformShape->setColor(1.0, 1.0, 1.0, 0.0);
	baseEntity->addChild(screenTransformShape);		


	screenTransform = new ScreenEntity();
	baseEntity->addChild(screenTransform);	
	screenTransform->visible = false;
	screenTransform->processInputEvents = true;
	
//	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_LINEAR);
	
	ScreenImage *base = new ScreenImage("Images/ScreenEditor/transform_base.png");
	base->setPositionMode(ScreenEntity::POSITION_CENTER);
	screenTransform->addChild(base);
	
	transformRotator = new ScreenImage("Images/ScreenEditor/transform_rotator.png");
	transformRotator->setPositionMode(ScreenEntity::POSITION_CENTER);
	transformRotator->setPosition(-40, 40);
	screenTransform->addChild(transformRotator);
	transformRotator->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	transformRotator->processInputEvents = true;
	transformRotator->blockMouseInput = true;

	transformScalerY = new ScreenImage("Images/ScreenEditor/transform_scaler.png");
	transformScalerY->setColor(0.0, 0.5, 1.0, 0.7);
	transformScalerY->setPositionMode(ScreenEntity::POSITION_CENTER);
	transformScalerY->setPosition(0, -50);
	screenTransform->addChild(transformScalerY);	
	transformScalerY->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	transformScalerY->processInputEvents = true;
	transformScalerY->blockMouseInput = true;
	
	transformScalerX = new ScreenImage("Images/ScreenEditor/transform_scaler.png");
	transformScalerX->setColor(1.0, 0.5, 0.0, 0.7);
	transformScalerX->setPositionMode(ScreenEntity::POSITION_CENTER);
	transformScalerX->setRotation(90);
	transformScalerX->setPosition(50, 0);
	screenTransform->addChild(transformScalerX);	
	transformScalerX->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	transformScalerX->processInputEvents = true;
	transformScalerX->blockMouseInput = true;
	
	
	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
	
	entityInfoWindow = new UIWindow("Selected entity", 140, 100);
	addChild(entityInfoWindow);	
	entityInfoWindow->setPosition(15,15);
	entityInfoWindow->enabled = false;
	
	ScreenLabel *label2 = new ScreenLabel(L"Entity color:", fontSize, fontName, Label::ANTIALIAS_FULL);
	entityInfoWindow->addChild(label2);
	label2->setPosition(padding, entityInfoWindow->topPadding+20);
/*
	entityColorBox = new UIColorBox(Color(1.0, 1.0, 1.0, 0.0), 30,30);
	entityColorBox->setPosition(label2->getPosition().x, label2->getPosition().y+label2->getHeight());
	entityInfoWindow->addChild(entityColorBox);		
	entityColorBox->addEventListener(this, UIEvent::CHANGE_EVENT);
	*/

	viewOptions = new ScreenEntity();
	addChild(viewOptions);
	viewOptions->processInputEvents = true;
	viewOptions->blockMouseInput = true;
			
	viewOptionsBg = new ScreenShape(ScreenShape::SHAPE_RECT, 20,20);
	viewOptionsBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	viewOptionsBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	viewOptions->addChild(viewOptionsBg);
	
	viewOptionsBg->blockMouseInput = true;
	viewOptionsBg->processInputEvents = true;
	

	ScreenLabel *label = new ScreenLabel("GRID", 18, "section", Label::ANTIALIAS_FULL);
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

	label = new ScreenLabel("SNAP", 18, "section", Label::ANTIALIAS_FULL);
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
	
		
	properties = new ScreenEntity();
	addChild(properties);
	properties->processInputEvents = true;
	properties->blockMouseInput = true;
			
	propertiesBg = new ScreenShape(ScreenShape::SHAPE_RECT, 20,20);
	propertiesBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	propertiesBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	properties->addChild(propertiesBg);
	propertiesBg->blockMouseInput = true;
	propertiesBg->processInputEvents = true;
	
	label = new ScreenLabel("SCREEN RATIO", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	properties->addChild(label);
	label->setPosition(10, 3);
	
	scaleInput = new UITextInput(false, 70, 12);
	scaleInput->setText("1.0");
	properties->addChild(scaleInput);
	scaleInput->setPosition(140, 4);
	scaleInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	label = new ScreenLabel("PREVIEW ASPECT", 18, "section", Label::ANTIALIAS_FULL);
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
			
	label = new ScreenLabel("ZOOM", 18, "section", Label::ANTIALIAS_FULL);
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
			
	toolPalette = new ScreenEntity();
	toolPalette->setPosition(0, 30);
	toolPalette->processInputEvents = true;
	toolPalette->blockMouseInput = true;
	addChild(toolPalette);
	
	toolPaletteBg = new ScreenShape(ScreenShape::SHAPE_RECT, 80, 20);
	toolPaletteBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	toolPaletteBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiSmallHeaderBgColor"));
	toolPalette->addChild(toolPaletteBg);
	toolPaletteBg->processInputEvents = true;
	toolPaletteBg->blockMouseInput = true;
	Number yOffset = 15.0;
		
	selectorImage = new ScreenImage("Images/ScreenEditor/selector.png");
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
	entityProps->addPropSheet(particleSheet);

	spriteSheet = new ScreenSpriteSheet();
	spriteSheet->addEventListener(this, Event::CHANGE_EVENT);	
	entityProps->addPropSheet(spriteSheet);
	
	instanceSheet = new ScreenEntityInstanceSheet();
	instanceSheet->addEventListener(this, Event::CHANGE_EVENT);	
	entityProps->addPropSheet(instanceSheet);

	labelSheet = new ScreenLabelSheet();
	labelSheet->addEventListener(this, Event::CHANGE_EVENT);	
	entityProps->addPropSheet(labelSheet);

	soundSheet = new SoundSheet();
	entityProps->addPropSheet(soundSheet);
	soundSheet->addEventListener(this, Event::CHANGE_EVENT);

	imageSheet = new ScreenImageSheet();
	entityProps->addPropSheet(imageSheet);
	imageSheet->addEventListener(this, Event::CHANGE_EVENT);	

	shapeSheet = new ShapeSheet();
	shapeSheet->addEventListener(this, Event::CHANGE_EVENT);
	entityProps->addPropSheet(shapeSheet);

	transform2dSheet = new Transform2DSheet();
	transform2dSheet->addEventListener(this, Event::CHANGE_EVENT);
	entityProps->addPropSheet(transform2dSheet);
	
	entitySheet = new EntitySheet();
	entityProps->addPropSheet(entitySheet);
	
	selectEntity(NULL);	
	
	entityProps->updateProps();		
	
	parenting = false;
	parentingChild = NULL;	
	
	parentingLine = new ScreenLine(Vector2(), Vector2(0,0));
	parentingLine->setLineWidth(4.0);
	parentingLine->setColor(0.0, 0.5, 1.0, 0.5);
	baseEntity->addChild(parentingLine);
	
	setMode(MODE_SELECT);	
}

void PolycodeScreenEditorMain::setGrid(int gridSize) {

	this->gridSize = gridSize;

	Polygon *gridPoly = new Polygon();
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
	
		grid = new ScreenMesh(gridMesh);
		grid->setColor(1.0, 1.0, 1.0, 0.1);
		objectBaseEntity->addChild(grid);		
	}

	grid->setPosition(-(gridSize * gridLen)/2, -(gridSize * gridLen)/2);
}

PolycodeScreenEditorMain::~PolycodeScreenEditorMain() {

}


void PolycodeScreenEditorMain::syncTransformToSelected() {
	if(!selectedEntity)
		return;
	
	objectBaseEntity->rebuildTransformMatrix();	
	selectedEntity->rebuildTransformMatrix();
	

	if(selectedEntities.size() == 1) {

		screenTransformShape->setShapeSize(selectedEntity->getWidth(),selectedEntity->getHeight());	
		Matrix4 final = selectedEntity->getConcatenatedMatrixRelativeTo(baseEntity);
		screenTransform->setPosition(final.getPosition());
		screenTransformShape->dirtyMatrix(false);
		screenTransformShape->setTransformByMatrixPure(final);
		
		screenTransform->rotation.roll = selectedEntity->getCombinedRoll();
	} else {
	
		// Calculate corners transformed into base entity space and get center and 
		// transformed bounding vertices
		
		std::vector<Vector3> corners;
		
		for(int i=0; i < selectedEntities.size(); i++) {
			ScreenEntity *entity = selectedEntities[i];
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
		
		Number width = fabs(max.x - min.x);
		Number height = fabs(max.y - min.y);
				
		Vector3 center = Vector3(min.x + (width/2.0), min.y + (height/2.0), 0.0);
						
		screenTransform->setPosition(center);
		screenTransformShape->setShapeSize(width, height);
		screenTransformShape->setPosition(center);
					
//		screenTransformShape->setShapeSize(selectedEntity->getWidth(),selectedEntity->getHeight());	
//		Matrix4 final = selectedEntity->getConcatenatedMatrixRelativeTo(baseEntity);
//		screenTransform->setPosition(final.getPosition());			
//		screenTransformShape->matrixDirty = false;
//		screenTransformShape->setTransformByMatrixPure(final);		
		
	}
	
	screenTransform->rebuildTransformMatrix();
	
}

void PolycodeScreenEditorMain::updateCursor() {
	switch(mode) {
		case MODE_SELECT:
			CoreServices::getInstance()->getCore()->setCursor(CURSOR_ARROW);
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
			CoreServices::getInstance()->getCore()->setCursor(CURSOR_CROSSHAIR);
		break;
		case MODE_ZOOM:
			CoreServices::getInstance()->getCore()->setCursor(CURSOR_CROSSHAIR);		
		break;
		case MODE_PAN:
			CoreServices::getInstance()->getCore()->setCursor(CURSOR_OPEN_HAND);		
		break;
		default:
			CoreServices::getInstance()->getCore()->setCursor(CURSOR_ARROW);		
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
			zooming = false;
		}
		break;
		case MODE_SELECT:	
		{
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
				Vector2 offset = position-mouseBase;
				Number newScale = baseZoomScale + (offset.x * 0.01);
				if(newScale < 0.1) 
					newScale = 0.1;
					
				objectBaseEntity->setScale(newScale, newScale);
				resizePreviewScreen();
				syncTransformToSelected();
				
				zoomComboBox->setSelectedIndex(7);
			}
		}
		break;
		case MODE_SELECT:
		{
		
			if(rotating) {
			
				Vector2 diff = CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - screenTransform->getScreenPosition();
				diff.Normalize();
				Number newAngle = atan2(diff.x, diff.y);				
				selectedEntity->setRotation(baseRotateAngle - (TODEGREES * (newAngle-baseAngle)));
				syncTransformToSelected();			
			} else if(scalingY) {				
				
				
				Vector2 trans = CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - mouseBase;
			
				Vector3 trans3 = Vector3(trans.x, trans.y, 0.0);
				
				Quaternion q;								
				q.fromAxes(0.0, 0.0, -selectedEntity->getCombinedRoll());
				trans3 = q.applyTo(trans3);
								
				Number scaleMod = 0.04;								
				selectedEntity->setScaleY(baseScale.y - (trans3.y * scaleMod));				
				syncTransformToSelected();	
				
			} else if(scalingX) {				
				
				Vector2 trans = CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - mouseBase;
			
				Vector3 trans3 = Vector3(trans.x, trans.y, 0.0);
				Quaternion q;
				
				q.fromAxes(0.0, 0.0, -selectedEntity->getCombinedRoll());
				trans3 = q.applyTo(trans3);
								
				Number scaleMod = 0.04;								
				selectedEntity->setScaleX(baseScale.x + (trans3.x * scaleMod));				
				syncTransformToSelected();	
				
			}  else if(moving) {

				Vector2 trans = (CoreServices::getInstance()->getCore()->getInput()->getMousePosition() - mouseBase);

				for(int i=0; i < selectedEntities.size(); i++) {
					Vector3 trans3 = Vector3(trans.x, trans.y, 0.0);
				
					Vector3 trans3_a = baseEntity->getConcatenatedMatrix() * trans3;				
					Vector3 trans3_b = selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().inverse() * trans3_a;
				
					trans3_b = trans3_b - selectedEntities[i]->getParentEntity()->getConcatenatedMatrixRelativeTo(baseEntity).inverse().getPosition();
					
				
					Vector2 newPosition = Vector2(baseEntityPositions[i].x + trans3_b.x, baseEntityPositions[i].y + trans3_b.y);
				
					if(gridSnap) {
						newPosition.x = round(((Number)newPosition.x)/((Number)gridSize)) * gridSize;
						newPosition.y = round(((Number)newPosition.y)/((Number)gridSize)) * gridSize;	
					}				
				
					selectedEntities[i]->setPosition(newPosition); 
				}
				
				syncTransformToSelected();
			}
		}
		break;
		case MODE_SHAPE:
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				if(gridSnap) {
					newPosition.x = round(((Number)newPosition.x)/((Number)gridSize)) * gridSize;
					newPosition.y = round(((Number)newPosition.y)/((Number)gridSize)) * gridSize;	
				}				
				
				previewShape->setPosition(newPosition);		
		}
		break;
		case MODE_IMAGE:
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				if(gridSnap) {
					newPosition.x = round(((Number)newPosition.x)/((Number)gridSize)) * gridSize;
					newPosition.y = round(((Number)newPosition.y)/((Number)gridSize)) * gridSize;	
				}				
		
			previewImage->setPosition(newPosition);	
		}
		break;
		case MODE_PARTICLES:
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				if(gridSnap) {
					newPosition.x = round(((Number)newPosition.x)/((Number)gridSize)) * gridSize;
					newPosition.y = round(((Number)newPosition.y)/((Number)gridSize)) * gridSize;	
				}				
		
			previewEmitter->setPosition(newPosition);	
		}
		break;		
		case MODE_TEXT:				
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				if(gridSnap) {
					newPosition.x = round(((Number)newPosition.x)/((Number)gridSize)) * gridSize;
					newPosition.y = round(((Number)newPosition.y)/((Number)gridSize)) * gridSize;	
				}				
		
			previewLabel->setPosition(newPosition);				
		}
		break;
		case MODE_LINK:				
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				if(gridSnap) {
					newPosition.x = round(((Number)newPosition.x)/((Number)gridSize)) * gridSize;
					newPosition.y = round(((Number)newPosition.y)/((Number)gridSize)) * gridSize;	
				}				
		
			previewInstance->setPosition(newPosition);				
		}
		break;		
		case MODE_ENTITY:				
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				if(gridSnap) {
					newPosition.x = round(((Number)newPosition.x)/((Number)gridSize)) * gridSize;
					newPosition.y = round(((Number)newPosition.y)/((Number)gridSize)) * gridSize;	
				}				
		
			previewEntity->setPosition(newPosition);				
		}
		case MODE_SOUND:				
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				if(gridSnap) {
					newPosition.x = round(((Number)newPosition.x)/((Number)gridSize)) * gridSize;
					newPosition.y = round(((Number)newPosition.y)/((Number)gridSize)) * gridSize;	
				}				
		
			previewSound->setPosition(newPosition);				
		}		
		case MODE_SPRITE:
		{
				Vector2 newPosition = Vector2(position.x / objectBaseEntity->getScale2D().x, position.y /objectBaseEntity->getScale2D().y);			
				if(gridSnap) {
					newPosition.x = round(((Number)newPosition.x)/((Number)gridSize)) * gridSize;
					newPosition.y = round(((Number)newPosition.y)/((Number)gridSize)) * gridSize;	
				}				
		
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
			mouseBase = position;
			zooming = true;
			baseZoomScale = objectBaseEntity->getScale().x;
		}
		break;
		case MODE_TEXT:
		{
				ScreenLabel *placingLabel = new ScreenLabel(previewLabel->getText(), previewLabel->getLabel()->getSize(), previewLabel->getLabel()->getFont()->getFontName());
				placingLabel->setPositionMode(ScreenEntity::POSITION_CENTER);
				placingLabel->setPosition(previewLabel->getPosition2D());
				placingLabel->processInputEvents = true;
				placingLabel->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingLabel->addEventListener(this, InputEvent::EVENT_MOUSEUP);
				placingLabel->id = "ScreenLabel."+String::IntToString(placementCount);		
				placingLabel->blockMouseInput = true;
				placingLabel->positionAtBaseline = false;
				currentLayer->addChild(placingLabel);
				placementCount++;
				
				if(treeView) {
					treeView->Refresh();		
				}				
		}
		break;		
		case MODE_IMAGE:
		{
				ScreenImage *placingImage = new ScreenImage(previewImage->getTexture()->getResourcePath());
				placingImage->setPositionMode(ScreenEntity::POSITION_CENTER);
				placingImage->setPosition(previewImage->getPosition2D());
				placingImage->processInputEvents = true;
				placingImage->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
				placingImage->addEventListener(this, InputEvent::EVENT_MOUSEUP);
				placingImage->id = "ScreenImage."+String::IntToString(placementCount);
				placingImage->blockMouseInput = true;
				currentLayer->addChild(placingImage);
				placementCount++;
					
				if(treeView) {
					treeView->Refresh();		
				}											
		}
		break;		
		case MODE_SHAPE:
		{
				ScreenShape *placingShape = new ScreenShape(ScreenShape::SHAPE_RECT, 100, 100);			
				placingShape->setPosition(previewShape->getPosition2D());
				placingShape->processInputEvents = true;
				placingShape->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingShape->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				currentLayer->addChild(placingShape);
				placingShape->id = "ScreenShape."+String::IntToString(placementCount);			
				
				placingShape->blockMouseInput = true;				
				*placingShape = *previewShape;
				placementCount++;	

				if(treeView) {
					treeView->Refresh();		
				}											
		}
		break;
		case MODE_PARTICLES:
		{
				ScreenParticleEmitter *placingEmitter = new ScreenParticleEmitter("default.png", Particle::BILLBOARD_PARTICLE, ParticleEmitter::CONTINUOUS_EMITTER, 2.0, 30, Vector3(0.0, -40.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(10.0, 10.0, 0.0));

				placingEmitter->setPosition(previewEmitter->getPosition2D());
				placingEmitter->processInputEvents = true;
				placingEmitter->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingEmitter->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				currentLayer->addChild(placingEmitter);
				placingEmitter->id = "ScreenParticleEmitter."+String::IntToString(placementCount);
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

				placingEmitter->setPositionMode(ScreenEntity::POSITION_CENTER);

				placingEmitter->setWidth(placingEmitter->emitterRadius.x);
				placingEmitter->setHeight(placingEmitter->emitterRadius.y);			

				createParticleRef(placingEmitter);
				
				if(treeView) {
					treeView->Refresh();		
				}											
		}
		break;			
		case MODE_SPRITE:
		{
				ScreenSprite *placingSprite = new ScreenSprite(previewSprite->getFileName());			
				placingSprite->setPosition(previewSprite->getPosition2D());
				placingSprite->processInputEvents = true;
				placingSprite->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingSprite->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				currentLayer->addChild(placingSprite);
				placingSprite->id = "ScreenSprite."+String::IntToString(placementCount);
				placingSprite->blockMouseInput = true;
				
				if(previewSprite->getCurrentAnimation()) {
						placingSprite->playAnimation(previewSprite->getCurrentAnimation()->name, 0, false);
				}
				
				placementCount++;	


				if(treeView) {
					treeView->Refresh();		
				}											
		}
		break;		
		case MODE_LINK:
		{
				ScreenEntityInstance *placingInstance = new ScreenEntityInstance(previewInstance->getFileName());
				placingInstance->setPosition(previewInstance->getPosition2D());
				placingInstance->processInputEvents = true;
				placingInstance->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingInstance->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				currentLayer->addChild(placingInstance);
				placingInstance->id = "ScreenInstance."+String::IntToString(placementCount);				
				placingInstance->blockMouseInput = true;
				placementCount++;	
				
				placingInstance->setWidth(50);
				placingInstance->setHeight(50);				
				
				applyEditorProperties(placingInstance);

				if(treeView) {
					treeView->Refresh();		
				}											
		}
		break;		
		case MODE_ENTITY:
		{
				ScreenEntity *placingEntity = new ScreenEntity();
				placingEntity->setPosition(previewEntity->getPosition2D());
				placingEntity->processInputEvents = true;
				placingEntity->setPositionMode(ScreenEntity::POSITION_CENTER);
				placingEntity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingEntity->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				placingEntity->setWidth(50);
				placingEntity->setHeight(50);				
				currentLayer->addChild(placingEntity);
				placingEntity->id = "ScreenEntity."+String::IntToString(placementCount);
				placingEntity->blockMouseInput = true;	
				placementCount++;
								
				createEntityRef(placingEntity);				

				if(treeView) {
					treeView->Refresh();		
				}								
		}
		break;
		case MODE_SOUND:
		{
				Sound *sound = previewSound->getSound();
				
				ScreenSound *placingSound = new ScreenSound(sound->getFileName(), sound->getReferenceDistance(), sound->getMaxDistance());
				placingSound->setPosition(previewSound->getPosition2D());
				placingSound->processInputEvents = true;
				placingSound->setPositionMode(ScreenEntity::POSITION_CENTER);
				placingSound->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
				placingSound->addEventListener(this, InputEvent::EVENT_MOUSEUP);				
				placingSound->setWidth(50);
				placingSound->setHeight(50);				
				currentLayer->addChild(placingSound);
				placingSound->id = "ScreenSound."+String::IntToString(placementCount);
				placingSound->blockMouseInput = true;	
				placementCount++;
				
				createSoundRef(placingSound);
								
			
				if(treeView) {
					treeView->Refresh();		
				}								
		}
		break;		
	}
}

void PolycodeScreenEditorMain::applyEditorOnly(ScreenEntity *entity) {
	entity->editorOnly = true;
	entity->removeAllHandlersForListener(this);
	for(int i=0; i < entity->getNumChildren(); i++) {
		applyEditorOnly((ScreenEntity*)entity->getChildAtIndex(i));
	}
}

void PolycodeScreenEditorMain::createEntityRef(ScreenEntity *entity) {
	ScreenImage *markerImage = new ScreenImage("Images/ScreenEditor/entity_marker.png");
	entity->addChild(markerImage);
	markerImage->setPositionMode(ScreenEntity::POSITION_CENTER);
	markerImage->editorOnly = true;
	markerImage->billboardMode = true;
	markerImage->billboardIgnoreScale = true;
	
	ScreenEntityNameDisplay *nameDisplay = new ScreenEntityNameDisplay(entity);
	entity->addChild(nameDisplay);
	nameDisplay->billboardMode = true;
	nameDisplay->billboardIgnoreScale = true;
	
}

void PolycodeScreenEditorMain::createParticleRef(ScreenParticleEmitter *target) {

	ScreenImage *markerImage = new ScreenImage("Images/particle_system_icon_editor.png");
	markerImage->setColor(0.0, 1.0, 1.0, 1.0);
	target->addChild(markerImage);
	markerImage->setPositionMode(ScreenEntity::POSITION_CENTER);
	markerImage->editorOnly = true;
	markerImage->billboardMode = true;
	markerImage->billboardIgnoreScale = true;
	
	ScreenShape *refRect = new ScreenShape(ScreenShape::SHAPE_RECT, target->emitterRadius.x, target->emitterRadius.y);
	
	refRect->strokeEnabled = true;
	refRect->strokeWidth = 1.0;
	refRect->id = "refRect";
	refRect->setStrokeColor(1.0, 1.0, 0.0, 0.5);
	refRect->setColor(0.0, 0.0, 0.0, 0.0);
	target->addChild(refRect);
	refRect->editorOnly = true;				
		
}

void PolycodeScreenEditorMain::createSoundRef(ScreenSound *target) {
	ScreenImage *markerImage = new ScreenImage("Images/ScreenEditor/screen_sound_icon.png");
	target->addChild(markerImage);
	markerImage->setPositionMode(ScreenEntity::POSITION_CENTER);
	markerImage->editorOnly = true;
	markerImage->billboardMode = true;
	markerImage->billboardIgnoreScale = true;
	
	ScreenShape *refCircle = new ScreenShape(ScreenShape::SHAPE_CIRCLE, target->getSound()->getReferenceDistance(), target->getSound()->getReferenceDistance(), 16);
	refCircle->strokeEnabled = true;
	refCircle->strokeWidth = 1.0;
	refCircle->id = "refCircle";
	refCircle->setStrokeColor(1.0, 0.5, 0.0, 0.5);
	refCircle->setColor(0.0, 0.0, 0.0, 0.0);
	target->addChild(refCircle);
	refCircle->editorOnly = true;				
	
	ScreenShape *maxCircle = new ScreenShape(ScreenShape::SHAPE_CIRCLE, target->getSound()->getMaxDistance(), target->getSound()->getMaxDistance(), 16);
	maxCircle->strokeEnabled = true;
	maxCircle->strokeWidth = 1.0;
	maxCircle->id = "maxCircle";				
	maxCircle->setStrokeColor(0.0, 1.0, 1.0, 0.5);
	maxCircle->setColor(0.0, 0.0, 0.0, 0.0);
	target->addChild(maxCircle);
	maxCircle->editorOnly = true;
}

bool PolycodeScreenEditorMain::hasSelected(ScreenEntity *entity) {
	for(int i=0; i < selectedEntities.size(); i++) {
		if(selectedEntities[i] == entity) {
			return true;
		}
	}
	return false;
}

void PolycodeScreenEditorMain::selectEntity(ScreenEntity *entity) {

	if(entity != NULL) {
		if(hasSelected(entity)) {
			return;
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
				
	if(!entity) {
		selectedEntity = NULL;
		screenTransform->visible = false;
		screenTransform->enabled = false;
		screenTransformShape->visible = false;			
		entityProps->updateProps();
		selectedEntities.clear();
		baseEntityPositions.clear();
		if(treeView) {
			treeView->Refresh();		
		}
		return;
	}
	
	if(!multiSelect) {
		selectedEntities.clear();
	}
	
	if(selectedEntities.size() == 0) {
		baseEntityPositions.clear();
	}
	
	selectedEntities.push_back(entity);
	baseEntityPositions.push_back(entity->getPosition2D());	
		
	currentLayer->focusChild(entity);
	
	if(entity->getEntityProp("editor_type") != "layer" && entity->getEntityProp("editor_type") != "root") {	
		transform2dSheet->entity = entity;
	}
	
	if(entity->getEntityProp("editor_type") != "root") {
		entitySheet->entity = entity;	
	}

	if(dynamic_cast<ScreenParticleEmitter*>(entity)) {
		particleSheet->emitter = (ScreenParticleEmitter*) entity;
	}
	
	if(dynamic_cast<ScreenSprite*>(entity)) {
		spriteSheet->sprite = (ScreenSprite*) entity;
	}
	
	if(dynamic_cast<ScreenShape*>(entity)) {
		shapeSheet->shape = (ScreenShape*) entity;
	}

	if(dynamic_cast<ScreenImage*>(entity)) {
		imageSheet->image = (ScreenImage*) entity;
	}

	if(dynamic_cast<ScreenLabel*>(entity)) {
		labelSheet->label = (ScreenLabel*) entity;
	}

	if(dynamic_cast<ScreenSound*>(entity)) {
		soundSheet->sound = ((ScreenSound*) entity);
	}
	
	if(dynamic_cast<ScreenEntityInstance*>(entity)) {
		instanceSheet->instance = ((ScreenEntityInstance*) entity);
	}
			
		
	if(entity->getEntityProp("editor_type") != "layer" && entity->getEntityProp("editor_type") != "root") {
		screenTransform->visible = true;
		screenTransform->enabled = true;	
		screenTransformShape->visible = true;
	} else {
		screenTransform->visible = false;
		screenTransform->enabled = false;	
		screenTransformShape->visible = false;	
	}
	
	selectedEntity = entity;
	syncTransformToSelected();	
		
	entityProps->updateProps();	
	
	if(treeView) {
		treeView->Refresh();		
	}
	
	dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void PolycodeScreenEditorMain::resizePreviewScreen() {
	previewAspectRatio = aspects[aspectComboBox->getSelectedIndex()];
	Number scaleVal = 1.0/atof(scaleInput->getText().c_str());		
	screenPreviewShape->setShapeSize(1.0/scaleVal * previewAspectRatio * objectBaseEntity->getScale().x, 1.0/scaleVal * objectBaseEntity->getScale().x);
}
	
void PolycodeScreenEditorMain::handleEvent(Event *event) {
	InputEvent *inputEvent = (InputEvent*) event;
	
	if(event->getEventCode() == UIEvent::CHANGE_EVENT && event->getEventType() == "UIEvent") {


		if(event->getDispatcher() == pixelSnapBox) {
			layerBaseEntity->setDefaultScreenOptions(pixelSnapBox->isChecked());
			screenTransform->setDefaultScreenOptions(pixelSnapBox->isChecked());
		}

	
		if(event->getDispatcher() == gridSnapBox) {
			gridSnap = gridSnapBox->isChecked();
		}
	
		if(event->getDispatcher() == gridSizeInput) {
			setGrid(atoi(gridSizeInput->getText().c_str()));
		}
	
		if(event->getDispatcher() == gridCheckBox) {
			grid->visible = gridCheckBox->isChecked();
		}
	
		if(event->getDispatcher() == scaleInput) {
			resizePreviewScreen();
		}

		if(event->getDispatcher() == zoomComboBox) {
			if(zoomComboBox->getSelectedIndex() != 7) {
				Number newScale = zooms[zoomComboBox->getSelectedIndex()];
				objectBaseEntity->setScale(newScale, newScale);
				resizePreviewScreen();
				syncTransformToSelected();				
			}
		}

		if(event->getDispatcher() == aspectComboBox) {
			resizePreviewScreen();
		}
	}

	if(event->getDispatcher() == particleSheet && event->getEventType() == "") {	
		if(particleSheet->emitter) {
		ScreenShape *refRect = (ScreenShape*) particleSheet->emitter->getEntityById("refRect", false);
		if(refRect) {
			refRect->setShapeSize(particleSheet->emitter->emitterRadius.x, particleSheet->emitter->emitterRadius.y);
			particleSheet->emitter->setWidth(particleSheet->emitter->emitterRadius.x);
			particleSheet->emitter->setHeight(particleSheet->emitter->emitterRadius.y);			
		}
		}

	}
	
	if(event->getDispatcher() == soundSheet && event->getEventType() == "") {	
		ScreenShape *refCircle = (ScreenShape*) soundSheet->sound->getEntityById("refCircle", false);
		if(refCircle) {
			refCircle->setShapeSize(soundSheet->sound->getSound()->getReferenceDistance(), soundSheet->sound->getSound()->getReferenceDistance());
		}

		ScreenShape *maxCircle = (ScreenShape*) soundSheet->sound->getEntityById("maxCircle", false);
		if(maxCircle) {
			maxCircle->setShapeSize(soundSheet->sound->getSound()->getMaxDistance(), soundSheet->sound->getSound()->getMaxDistance());
		}

		
	}
	
	if((event->getDispatcher() == transform2dSheet || event->getDispatcher() == labelSheet || event->getDispatcher() == imageSheet) && event->getEventType() == "") {
		syncTransformToSelected();
		treeView->Refresh();		
	}
	
	if(event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput()) {
		if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
			switch(inputEvent->key) {
				case Polycode::KEY_ESCAPE:
					if(selectedEntity) {
						scalingY = false;
						scalingX = false;
						moving = false;
						rotating = false;
						selectEntity(NULL);
					}
				break;
				case Polycode::KEY_BACKSPACE:
				{
					if(selectedEntity) {
						if(selectedEntity->hasFocus) {
							selectedEntity->ownsChildren = true;
							selectedEntity->getParentEntity()->removeChild(selectedEntity);
							delete selectedEntity;
							selectEntity(NULL);							
							
						}
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
			}
		}
	
		
	}

	if(event->getDispatcher() == transformScalerY) {
		if(selectedEntity) {
			scalingY = true;
			baseScale = selectedEntity->getScale();
			mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();			
		}
	}

	if(event->getDispatcher() == transformScalerX) {
		if(selectedEntity) {
			scalingX = true;
			baseScale = selectedEntity->getScale();
			mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();			
		}
	}
	
	if(event->getDispatcher() == transformRotator) {
		if(selectedEntity) {
			rotating = true;
			baseRotateAngle = selectedEntity->getRotation();
			mouseBase = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();
			
			Vector2 diff = mouseBase - screenTransform->getScreenPosition();
			baseAngle = atan2(diff.x, diff.y);
		}
	}
	

	if(event->getEventCode() == UIEvent::CLICK_EVENT && event->getEventType() == "UIEvent") {
	
		if(event->getDispatcher() == moveUpButton) {
			if(selectedEntity) {
				if(selectedEntity->getParentEntity()) {
					((ScreenEntity*)selectedEntity->getParentEntity())->moveChildUp(selectedEntity);
				}
			}	
		}

		if(event->getDispatcher() == moveDownButton) {
			if(selectedEntity) {
				if(selectedEntity->getParentEntity()) {
					((ScreenEntity*)selectedEntity->getParentEntity())->moveChildDown(selectedEntity);
				}
			}	
		}

		if(event->getDispatcher() == moveTopButton) {
			if(selectedEntity) {
				if(selectedEntity->getParentEntity()) {
					((ScreenEntity*)selectedEntity->getParentEntity())->moveChildTop(selectedEntity);
				}
			}	
		}

		if(event->getDispatcher() == moveBottomButton) {
			if(selectedEntity) {
				if(selectedEntity->getParentEntity()) {
					((ScreenEntity*)selectedEntity->getParentEntity())->moveChildBottom(selectedEntity);
				}
			}	
		}
		
		if(event->getDispatcher() == unparentButton) {
			if(selectedEntity) {
				if(selectedEntity->getParentEntity()) {
					selectedEntity->getParentEntity()->removeChild(selectedEntity);
					currentLayer->addChild(selectedEntity);
					syncTransformToSelected();
				}
			}	
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
	
	if(event->getDispatcher() == entityColorBox  && event->getEventType() == "UIEvent") {
		switch (event->getEventCode()) {
			case UIEvent::CHANGE_EVENT:
				if(selectedEntity) {
					selectedEntity->setColor(entityColorBox->getSelectedColor());
				}
			break;
		}
		return;
	}
	
	if(currentLayer) {
		for(int i=0; i < currentLayer->getNumChildren(); i++) {
			ScreenEntity* childEntity = (ScreenEntity*) currentLayer->getChildAtIndex(i);
			processEventForEntity(childEntity, inputEvent);
		}
	}
	
	if(event->getDispatcher() == baseEntity) {
		switch (event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				handleMouseDown(inputEvent->mousePosition);
				focusChild(baseEntity);
			break;		
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:			
				handleMouseUp(inputEvent->mousePosition);
			break;
			case InputEvent::EVENT_MOUSEOUT:
				CoreServices::getInstance()->getCore()->setCursor(CURSOR_ARROW);
			break;
			case InputEvent::EVENT_MOUSEMOVE:
			{
				updateCursor();
				handleMouseMove(inputEvent->mousePosition);
			}
			break;			
		}
		return;
	}

}

void PolycodeScreenEditorMain::processEventForEntity(ScreenEntity *childEntity, InputEvent *inputEvent) {

		for(int i=0; i < childEntity->getNumChildren(); i++) {
			processEventForEntity((ScreenEntity*)childEntity->getChildAtIndex(i), inputEvent);
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
					if(selectedEntity) {
						moving = true;
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


ScreenEntity *PolycodeScreenEditorMain::addNewLayer(String layerName) {
	ScreenEntity *newLayer = new ScreenEntity();
	newLayer->id = layerName;
	newLayer->processInputEvents = true;
	layerBaseEntity->addChild(newLayer);
	currentLayer = newLayer;
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
	
	selectEntity(NULL);
	
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

void PolycodeScreenEditorMain::Resize(Number width, Number height) {


	viewOptionsBg->setShapeSize(ceil(width), 30);
	viewOptions->setPosition(0, height-30);

	propertiesBg->setShapeSize(ceil(width), 30);
	
	toolPaletteBg->setShapeSize(100,height-60);
			
	if(firstResize && width > 0.0 && height > 0.0) {
		baseEntity->setPosition(width/2.0, height/2.0);
		firstResize = false;
	}
	
}

void PolycodeScreenEditorMain::handleDroppedFile(OSFileEntry file, Number x, Number y) {

	ScreenEntity *newEntity = NULL;
	
	if(file.extension == "png") {
		ScreenImage *newImage = new ScreenImage(file.fullPath);
		newImage->setPositionMode(ScreenEntity::POSITION_CENTER);
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

	mainSizer = new UIHSizer(100,100,300,false);
	addChild(mainSizer);	

	editorMain = new PolycodeScreenEditorMain();
	editorMain->addEventListener(this, Event::CHANGE_EVENT);
	mainSizer->addLeftChild(editorMain);
	
	propSizer = new PropertiesSizer();
	mainSizer->addRightChild(propSizer);
	
	editorMain->layerBaseEntity->setEntityProp("editor_type", "root");
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

void PolycodeScreenEditor::Activate() {
	editorMain->labelSheet->refreshFonts();
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

void PolycodeScreenEditor::saveEntityToObjectEntry(ScreenEntity *entity, ObjectEntry *entry) {

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

	if(dynamic_cast<ScreenEntityInstance*>(entity)) {
		if(!(*(entry))["type"])
			entry->addChild("type", "ScreenEntityInstance");
		ScreenEntityInstance *instance = (ScreenEntityInstance*) entity;
		ObjectEntry *instanceEntry = entry->addChild("ScreenEntityInstance");		
		instanceEntry->addChild("filePath", instance->getFileName());
	}
	
	if(dynamic_cast<ScreenImage*>(entity)) {
		if(!(*(entry))["type"])
			entry->addChild("type", "ScreenImage");
		ScreenImage *image = (ScreenImage*) entity;
		ObjectEntry *imageEntry = entry->addChild("ScreenImage");		
		imageEntry->addChild("filePath", image->getTexture()->getResourcePath());
	}

	
	if(dynamic_cast<ScreenParticleEmitter*>(entity)) {
		if(!(*(entry))["type"])
			entry->addChild("type", "ScreenParticleEmitter");
			
		ScreenParticleEmitter *emitter = (ScreenParticleEmitter*) entity;
		
		ObjectEntry *emitterEntry = entry->addChild("ScreenParticleEmitter");		

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

		saveCurveToObject(emitterEntry->addChild("scaleCurve"), &emitter->scaleCurve);

		saveCurveToObject(emitterEntry->addChild("colorCurveR"), &emitter->colorCurveR);
		saveCurveToObject(emitterEntry->addChild("colorCurveG"), &emitter->colorCurveG);
		saveCurveToObject(emitterEntry->addChild("colorCurveB"), &emitter->colorCurveB);
		saveCurveToObject(emitterEntry->addChild("colorCurveA"), &emitter->colorCurveA);						

		emitterEntry->addChild("particleBlendMode", (int)emitter->getParticleBlendingMode());		
		
	}
		
	
	if(dynamic_cast<ScreenSprite*>(entity)) {
		if(!(*(entry))["type"])
			entry->addChild("type", "ScreenSprite");
		ScreenSprite *sprite = (ScreenSprite*) entity;
		
		ObjectEntry *spriteEntry = entry->addChild("ScreenSprite");
		spriteEntry->addChild("filePath", sprite->getFileName());
		
		String animName = "";
		if(sprite->getCurrentAnimation()) {
			animName = sprite->getCurrentAnimation()->name;
		}
		spriteEntry->addChild("anim", animName);
	}	
	
	if(dynamic_cast<ScreenLabel*>(entity)) {
		ScreenLabel *label = (ScreenLabel*) entity;
		
		if(!(*(entry))["type"])
			entry->addChild("type", "ScreenLabel");
		ObjectEntry *labelEntry = entry->addChild("ScreenLabel");		
		labelEntry->addChild("text", label->getText());
		labelEntry->addChild("font", label->getLabel()->getFont()->getFontName());
		labelEntry->addChild("size", (int)label->getLabel()->getSize());
		labelEntry->addChild("aaMode", (int)label->getLabel()->getAntialiasMode());
	}
	
	if(dynamic_cast<ScreenSound*>(entity)) {
		ScreenSound *sound = (ScreenSound*) entity;
		
		if(!(*(entry))["type"])
			entry->addChild("type", "ScreenSound");
		ObjectEntry *soundEntry = entry->addChild("ScreenSound");		
		soundEntry->addChild("filePath", sound->getSound()->getFileName());
		soundEntry->addChild("refDistance", sound->getSound()->getReferenceDistance());
		soundEntry->addChild("maxDistance", sound->getSound()->getMaxDistance());
		soundEntry->addChild("volume", sound->getSound()->getVolume());
		soundEntry->addChild("pitch", sound->getSound()->getPitch());		
	}	
	
	if(dynamic_cast<ScreenShape*>(entity)) {
		if(!(*(entry))["type"])
			entry->addChild("type", "ScreenShape");	
		ScreenShape *shape = (ScreenShape*) entity;
		ObjectEntry *shapeEntry = entry->addChild("ScreenShape");
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

	if(dynamic_cast<ScreenSound*>(entity)) {
		ScreenSound *sound = ((ScreenSound*) entity);
	}
	
	if(!(*(entry))["type"])
		entry->addChild("type", "ScreenEntity");
	
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
	
	ObjectEntry *children = NULL;
	
	for(int i=0; i < entity->getNumChildren(); i++) {
		if(!entity->getChildAtIndex(i)->editorOnly) {
			if(!children)
				children = entry->addChild("children");		
			ObjectEntry *child = children->addChild("child");
			saveEntityToObjectEntry((ScreenEntity*)entity->getChildAtIndex(i), child);
		}
	}
}

void PolycodeScreenEditor::saveFile() {
	Object saveObject;
	
	saveObject.root.name = "Screen";
	ObjectEntry *children = saveObject.root.addChild("root");
	
	saveEntityToObjectEntry(editorMain->layerBaseEntity, children);	
//	saveObject.saveToXML(filePath);
	saveObject.saveToBinary(filePath);
}

void PolycodeScreenEditor::handleEvent(Event *event) {

	if(event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
		if(event->getDispatcher() == treeView) {			
			editorMain->selectEntity((ScreenEntity*)treeView->selectedEntity);
		}

		if(event->getDispatcher() == editorMain) {			
			treeView->selectedEntity = editorMain->selectedEntity;
		}

	}

	if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		if(event->getDispatcher() == treeView->newLayerButton) {
			ScreenEntity *newLayer = editorMain->addNewLayer("new_layer");
		}

		if(event->getDispatcher() == treeView->targetLayerButton) {
			if(treeView->selectedEntity->getEntityProp("editor_type") == "layer") {
				printf("setting new layer\n");
				editorMain->currentLayer = (ScreenEntity*)treeView->selectedEntity;
				treeView->targetLayer = editorMain->currentLayer;
				treeView->Refresh();				
			} else {
				PolycodeConsole::print("Select a layer to set as default layer.\n");
			}
		}

	}

}

PolycodeScreenEditor::~PolycodeScreenEditor() {
	
}

void PolycodeScreenEditorMain::applyEditorProperties(ScreenEntity *entity) {
	
	for(int i=0; i < entity->getNumChildren(); i++) {
		applyEditorProperties((ScreenEntity*)entity->getChildAtIndex(i));
	}

	if(dynamic_cast<ScreenEntityInstance*>(entity)) {
		applyEditorOnly(((ScreenEntityInstance*)entity)->getRootEntity());
		entity->setWidth(50);
		entity->setHeight(50);		
	} else if(dynamic_cast<ScreenShape*>(entity)) {
	
	} else if(dynamic_cast<ScreenImage*>(entity)) {

	} else if(dynamic_cast<ScreenLabel*>(entity)) {

	} else if(dynamic_cast<ScreenSound*>(entity)) {
		createSoundRef((ScreenSound*)entity);
	} else if(dynamic_cast<ScreenParticleEmitter*>(entity)) {
		createParticleRef((ScreenParticleEmitter*)entity);		
	} else {	
		if(entity->getEntityProp("editor_type") != "root" && entity->getEntityProp("editor_type") != "layer") {
			entity->setWidth(50);
			entity->setHeight(50);						
			createEntityRef(entity);
		}
	}
	
	entity->processInputEvents = true;
	entity->blockMouseInput = true;
	entity->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);	
	entity->addEventListener(this, InputEvent::EVENT_MOUSEUP);	
//	entity->setPositionMode(ScreenEntity::POSITION_CENTER);

}
		
bool PolycodeScreenEditor::openFile(OSFileEntry filePath) {
	PolycodeEditor::openFile(filePath);	
	
	
	ScreenEntityInstance *loadedInstance = new ScreenEntityInstance(filePath.fullPath);
	
	editorMain->layerBaseEntity = loadedInstance->getRootEntity();
	editorMain->objectBaseEntity->addChild(loadedInstance->getRootEntity());

	editorMain->applyEditorProperties(editorMain->layerBaseEntity);

	if(editorMain->layerBaseEntity->getNumChildren() == 0) {
		ScreenEntity *newLayer = editorMain->addNewLayer("default_layer");
	} else {
		editorMain->currentLayer = (ScreenEntity*)editorMain->layerBaseEntity->getChildAtIndex(0);
		treeView->targetLayer = editorMain->currentLayer;
	}

	((ScreenEntity*)(editorMain->layerBaseEntity->getParentEntity()))->moveChildBottom(editorMain->layerBaseEntity);

	if(treeView) {
		treeView->rootEntity = editorMain->layerBaseEntity;
		treeView->Refresh();
	}
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
	sizer->Resize(width, height);
	UIElement::Resize(width, height);
}



