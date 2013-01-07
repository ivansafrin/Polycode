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
 
#include "PolycodeMaterialEditor.h"

extern UIColorPicker *globalColorPicker;
extern UIGlobalMenu *globalMenu;

MaterialEditorPane::MaterialEditorPane() : UIWindow("Material", 670, 250) {

	
	previewScene = new Scene(true);	
	
	renderTexture = new SceneRenderTexture(previewScene, previewScene->getDefaultCamera(), 256, 256);
	
	ScenePrimitive *previewBg = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 15.0, 15.0, 15.0);
	previewBg->Yaw(45.0);
	previewBg->backfaceCulled = false;
	previewBg->loadTexture("Images/material_grid.png");
	previewScene->addChild(previewBg);
	
	previewScene->clearColor.setColor(0.1, 0.1, 0.1, 0.0);	
	previewScene->ambientColor.setColor(0.2, 0.2, 0.2, 1.0);
			
	previewPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 3.0, 1.2, 26, 16);
	previewScene->addChild(previewPrimitive);
	shapePrimitives.push_back(previewPrimitive);
	previewPrimitive->getMesh()->calculateTangents();	

	previewPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 3.0, 16, 16);
	previewScene->addChild(previewPrimitive);
	shapePrimitives.push_back(previewPrimitive);
	previewPrimitive->getMesh()->calculateTangents();	

	previewPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 4.0, 4.0, 4.0);
	previewPrimitive->Yaw(45.0);
	previewPrimitive->getMesh()->calculateNormals(false);
	previewPrimitive->getMesh()->calculateTangents();
	previewScene->addChild(previewPrimitive);
	shapePrimitives.push_back(previewPrimitive);

	previewPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 6.0, 6.0);
	previewPrimitive->billboardMode = true;
	previewScene->addChild(previewPrimitive);
	shapePrimitives.push_back(previewPrimitive);
	previewPrimitive->getMesh()->calculateTangents();	

	
	mainLight = new SceneLight(SceneLight::AREA_LIGHT, previewScene, 290.0);
	mainLight->setPosition(-10,10,10);
	previewScene->addLight(mainLight);

	secondLight = new SceneLight(SceneLight::AREA_LIGHT, previewScene, 250.0);
	secondLight->setPosition(10,-10,10);
	previewScene->addLight(secondLight);

	
	previewScene->getDefaultCamera()->setPosition(0,7,9);
	previewScene->getDefaultCamera()->lookAt(Vector3());
	
	previewShape = new ScreenShape(ScreenShape::SHAPE_RECT, 128, 128);
	previewShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	previewShape->setTexture(renderTexture->getTargetTexture());
	previewShape->setPosition(20,40);
	previewShape->strokeEnabled = true;
	previewShape->strokeColor = Color(1.0, 1.0, 1.0, 0.2);
	previewShape->setStrokeWidth(1.0);
	addChild(previewShape);
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");	
	Number padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");	
	
	Number xPos = 165;
	
	ScreenLabel *label = new ScreenLabel("SHADER", 22, "section", Label::ANTIALIAS_FULL);
	label->color.a = 0.4;
	addChild(label);
	label->setPosition(xPos,90);

	label = new ScreenLabel("BLEND MODE", 22, "section", Label::ANTIALIAS_FULL);
	label->color.a = 0.4;
	addChild(label);
	label->setPosition(xPos,150);


	label = new ScreenLabel("NAME", 22, "section", Label::ANTIALIAS_FULL);
	label->color.a = 0.4;		
	addChild(label);
	label->setPosition(xPos,30);

	nameInput = new UITextInput(false, 210, 30);
	nameInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	addChild(nameInput);
	nameInput->setPosition(xPos, 60);
	
	Number yPos = 145;
	
	
	yPos += 50;
	label = new ScreenLabel("TEXTURES", 22, "section", Label::ANTIALIAS_FULL);
	addChild(label);
	label->color.a = 0.4;	
	label->setPosition(xPos+230, 30);
	label->getLabel()->setColorForRange(Color(), 0, 8);
	label->getLabel()->setColorForRange(Color(0.5,0.5,0.5,1.0), 8, 35);
	label->setText("TEXTURES (DRAG FROM PROJECT TO SET)");

	paramsEntity = new UIElement();
	addChild(paramsEntity);

	label = new ScreenLabel("SHADER PROPERTIES", 22, "section", Label::ANTIALIAS_FULL);
	label->color.a = 0.4;
	paramsEntity->addChild(label);
	paramsEntity->setPositionX(xPos+230);

	textureSlotBase = new ScreenEntity();
	addChild(textureSlotBase);
	
	textureSlotBase->setPosition(xPos+230, 60);

	shaderSelector = new UIComboBox(globalMenu, 210);	
	shaderSelector->addEventListener(this, UIEvent::CHANGE_EVENT);

	
	blendSelector = new UIComboBox(globalMenu, 210);	
	blendSelector->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	addChild(blendSelector);
	blendSelector->setPosition(xPos, 180);
		
	blendSelector->addComboItem("Normal");
	blendSelector->addComboItem("Lighten");
	blendSelector->addComboItem("Color");
	blendSelector->addComboItem("Premultiplied");
	blendSelector->addComboItem("Multiply");
	
//	blendSelector->setSelectedIndex(0);
							
	MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
	for(int i=0; i < materialManager->getNumShaders(); i++) {
		if(!materialManager->getShaderByIndex(i)->screenShader) {
			shaderSelector->addComboItem(materialManager->getShaderByIndex(i)->getName(), (void*)materialManager->getShaderByIndex(i));
		}
	}
	
	shaderSelector->setPosition(xPos, 120);
	addChild(shaderSelector);
	
	shapeSelector = new ScreenImage("Images/small_selector.png");
	addChild(shapeSelector);
	shapeSelector->color.a = 0.4;
	
	shapeSwitches.push_back(new UIImageButton("Images/torus_icon.png"));
	shapeSwitches.push_back(new UIImageButton("Images/sphere_icon.png"));
	shapeSwitches.push_back(new UIImageButton("Images/box_icon.png"));
	shapeSwitches.push_back(new UIImageButton("Images/plane_icon.png"));

	for(int i=0; i < shapeSwitches.size(); i++) {
		addChild(shapeSwitches[i]);
		shapeSwitches[i]->setPosition(40 + (25 * i), 180);
		shapeSwitches[i]->addEventListener(this, UIEvent::CLICK_EVENT);
	}
				
	currentMaterial = NULL;
	
	showPrimitive(0);
	
	enabled = false;
}

void MaterialEditorPane::showPrimitive(unsigned int index) {
	for(int i=0; i < shapePrimitives.size(); i++) {
		shapePrimitives[i]->visible = false;	
	}
	shapePrimitives[index]->visible = true;	
	shapeSelector->setPosition(38 + (25 * index), 178);
	if(currentMaterial) {
		shapePrimitives[index]->setMaterial(currentMaterial);
	}
	previewPrimitive = shapePrimitives[index];
}

void MaterialEditorPane::handleEvent(Event *event) {
	
	for(int i=0; i < shapeSwitches.size(); i++) {
		if(event->getDispatcher() == shapeSwitches[i]) {
			if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
				showPrimitive(i);
			}
		}
	}
	
	if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT && currentMaterial) {		
	
		if(event->getDispatcher() == nameInput) {
			currentMaterial->setName(nameInput->getText());
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	
		if(event->getDispatcher() ==blendSelector) {			
			currentMaterial->blendingMode = blendSelector->getSelectedIndex();
		}
		if(event->getDispatcher() == shaderSelector) {
			Shader *selectedShader = (Shader*)shaderSelector->getSelectedItem()->data;
			
			clearAll();
			if(selectedShader) {	
				for(int i=0; i < selectedShader->expectedTextures.size(); i++) {
					MaterialTextureSlot *textureSlot = new MaterialTextureSlot(selectedShader->expectedTextures[i]);
					textureSlotBase->addChild(textureSlot);
					textureSlot->setPosition(0, (40*i));
					textureSlots.push_back(textureSlot);
					
					if(currentMaterial->getShaderBinding(0)) {
						Texture *currentTexture = currentMaterial->getShaderBinding(0)->getTexture(selectedShader->expectedTextures[i]);
						if(currentTexture) {
							textureSlot->imageShape->setTexture(currentTexture);
							std::vector<String> parts = currentTexture->getResourcePath().split("/");
							if(parts.size() > 1) {
								textureSlot->textureFileName->setText(parts[parts.size()-1]);
							} else {
								textureSlot->textureFileName->setText(currentTexture->getResourcePath());			
							}
						}
					}
				}

			}
			
			paramsEntity->setPositionY(70 + (selectedShader->expectedTextures.size()*40));

			bool replacingShader = false;
			if(currentMaterial->getShader(0) != selectedShader) {
				currentMaterial->clearShaders();
				previewPrimitive->clearMaterial();
				replacingShader = true;
			}
			
			if(selectedShader) {
				if(replacingShader) {			
					ShaderBinding *newShaderBinding = selectedShader->createBinding();				
					currentMaterial->addShader(selectedShader, newShaderBinding);
					previewPrimitive->setMaterial(currentMaterial);	
				}
				
				for(int i=0; i < textureSlots.size(); i++) {
					if(textureSlots[i]->textureFileName->getText() != "None") {
						currentMaterial->getShaderBinding(0)->clearTexture(textureSlots[i]->textureString);			
						currentMaterial->getShaderBinding(0)->addTexture(textureSlots[i]->textureString, textureSlots[i]->imageShape->getTexture());
					}
				}								
					
				if(currentMaterial->getShaderBinding(0)) {
				
				int yOffset = 30;
				
				for(int i=0; i < selectedShader->expectedFragmentParams.size(); i++) {
					if(!selectedShader->expectedFragmentParams[i].isAuto) {
					MaterialPropertySlot *propertySlot = new MaterialPropertySlot(currentMaterial->getShaderBinding(0), selectedShader->expectedFragmentParams[i]);
					paramsEntity->addChild(propertySlot);
					propertySlot->setPosition(0, yOffset);
					fragmentPropertySlots.push_back(propertySlot);					
					yOffset += 45;
				}
				}
								
				for(int i=0; i < selectedShader->expectedVertexParams.size(); i++) {
					if(!selectedShader->expectedVertexParams[i].isAuto) {
					MaterialPropertySlot *propertySlot = new MaterialPropertySlot(currentMaterial->getShaderBinding(0), selectedShader->expectedVertexParams[i]);
					paramsEntity->addChild(propertySlot);
					propertySlot->setPosition(0, yOffset);
					fragmentPropertySlots.push_back(propertySlot);					
					yOffset += 45;					
				}
				}
								

				}
			}
			
			int winHeight = (fragmentPropertySlots.size() * 45) + (textureSlots.size() * 40) + 100;

			if(winHeight < 250)
				winHeight = 250;
	
			setWindowSize(670, winHeight);			
		}			
	}
	
	
	UIWindow::handleEvent(event);
}

void MaterialEditorPane::clearAll() {
	for(int i=0; i < textureSlots.size(); i++) {
		textureSlotBase->removeChild(textureSlots[i]);
		delete textureSlots[i];
	}
	textureSlots.clear();
	
	for(int i=0; i < fragmentPropertySlots.size(); i++) {
		paramsEntity->removeChild(fragmentPropertySlots[i]);
		delete fragmentPropertySlots[i];
	}
	fragmentPropertySlots.clear();									
}

void MaterialEditorPane::handleDroppedFile(OSFileEntry file, Number x, Number y) {
	Vector2 screenPos = textureSlotBase->getScreenPosition();
	
	x = x - screenPos.x;
	y = y - screenPos.y;
		
	for(int i=0; i < textureSlots.size(); i++) {
		if(x > textureSlots[i]->getPosition().x && x < textureSlots[i]->getPosition().x + textureSlots[i]->getWidth() && 
		y > textureSlots[i]->getPosition().y && y < textureSlots[i]->getPosition().y + textureSlots[i]->getHeight()) {
			Texture *newTexture = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile(file.fullPath);
			textureSlots[i]->imageShape->setTexture(newTexture);
			textureSlots[i]->textureFileName->setText(file.name);
			currentMaterial->getShaderBinding(0)->clearTexture(textureSlots[i]->textureString);			
			currentMaterial->getShaderBinding(0)->addTexture(textureSlots[i]->textureString, newTexture);
			
		}
	}	
}

void MaterialEditorPane::setMaterial(Material *material) {
	currentMaterial = material;
	previewPrimitive->setMaterial(material);
		
	clearAll();	
	
	if(!currentMaterial) // ???
		return;		
	
	enabled = true;
	
	blendSelector->setSelectedIndex(currentMaterial->blendingMode);
					
	if(currentMaterial->getShader(0)) {		
	
	for(int i=0; i < shaderSelector->getNumItems(); i++) {
		Shader *shader = (Shader*)shaderSelector->getItemAtIndex(i)->data;
		if(shader) {
			if(currentMaterial->getShader(0)->getName() == shader->getName()) {
				shaderSelector->setSelectedIndex(i);
				break;
			}
		}
	}
	} else {
		shaderSelector->setSelectedIndex(0);	
	}
	
	nameInput->setText(currentMaterial->getName());
}

MaterialPropertySlot::MaterialPropertySlot(ShaderBinding *binding, ProgramParam param) : UIElement() {

	setWidth(280);
	setHeight(43);

	this->param = param;
	this->binding = binding;
	
	std::vector<String> stringParts = param.name.split("_");
	
	if(stringParts.size() > 0) {
		for(int i=0; i < stringParts.size(); i++) {
			finalName += stringParts[i].substr(0,1).toUpperCase() + stringParts[i].substr(1) + " ";	
		}
	} else {
		finalName = param.name.substr(0,1).toUpperCase() + param.name.substr(1);
	}
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");	
	Number padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");		

	propertyName = new ScreenLabel(finalName, fontSize, fontName, Label::ANTIALIAS_FULL);
	propertyName->setColor(1.0, 1.0, 1.0, 0.7);		
	addChild(propertyName);
	
	numberSlider = NULL;	
	colorBox = NULL;
	
	minLabel = NULL;
	maxLabel = NULL;
	
	switch(param.paramType) {
		case ProgramParam::PARAM_Number:
		{
			
			Number minVal = (*(Number*)param.minValue);
			minLabel = new ScreenLabel(String::NumberToString(minVal), fontSize, fontName, Label::ANTIALIAS_FULL);
			minLabel->setColor(1.0, 1.0, 1.0, 0.3);		
			addChild(minLabel);			
			minLabel->setPosition(0.0, 18);

			Number maxVal = (*(Number*)param.maxValue);
			maxLabel = new ScreenLabel(String::NumberToString(maxVal), fontSize, fontName, Label::ANTIALIAS_FULL);
			maxLabel->setColor(1.0, 1.0, 1.0, 0.3);		
			addChild(maxLabel);			
			maxLabel->setPosition(240, 18);

			numberSlider = new UIHSlider(minVal, maxVal, 180);
			addChild(numberSlider);
			numberSlider->setPosition(50, 23);
			numberSlider->addEventListener(this, UIEvent::CHANGE_EVENT);
//			binding->addLocalParam(param.name, &numberValue);

			Number numberValue = (*(Number*)binding->getLocalParamByName(param.name)->data);
			numberSlider->setSliderValue(numberValue);
					
			propertyName->setText(finalName+"("+String::NumberToString(numberValue)+")");

		}
		break;
		case ProgramParam::PARAM_Color:
			Color colorValue = ((*(Color*)binding->getLocalParamByName(param.name)->data));
			colorBox = new UIColorBox(globalColorPicker, colorValue, 30, 23);
			colorBox->addEventListener(this, UIEvent::CHANGE_EVENT);			
			colorBox->setPosition(0.0, 18);
//			binding->addLocalParam(param.name, &colorValue);			
			addChild(colorBox);
		break;
	}
}

void MaterialPropertySlot::handleEvent(Event *event) {
	if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CHANGE_EVENT) {
		if(event->getDispatcher() == numberSlider) {
			propertyName->setText(finalName+"("+String::NumberToString(numberSlider->getSliderValue())+")");
			(*(Number*)binding->getLocalParamByName(param.name)->data) = numberSlider->getSliderValue();
		}
		
		if(event->getDispatcher() == colorBox) {
			(*(Color*)binding->getLocalParamByName(param.name)->data) = colorBox->getSelectedColor();
		}
	}
}

MaterialPropertySlot::~MaterialPropertySlot() {
	
	delete propertyName;
	
	if(minLabel)
		delete minLabel;
	if(maxLabel)
		delete maxLabel;

	if(colorBox) {
		delete colorBox;
	}
	
	if(numberSlider)
		delete numberSlider;
}

MaterialTextureSlot::MaterialTextureSlot(String textureNameString) : UIElement() {

	setWidth(280);
	setHeight(38);
	
	textureString = textureNameString;
	
	bgShape  = new ScreenShape(ScreenShape::SHAPE_RECT, 280,38);
	bgShape->setColor(0.0, 0.0, 0.0, 0.4);
	bgShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	addChild(bgShape);

	imageShape = new ScreenShape(ScreenShape::SHAPE_RECT, 32,32);
	imageShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	imageShape->setPosition(3,3);
	addChild(imageShape);
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");	
	Number padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");	
	
	std::vector<String> stringParts = textureNameString.split("_");
	
	String finalName;
	if(stringParts.size() > 0) {
		for(int i=0; i < stringParts.size(); i++) {
			finalName += stringParts[i].substr(0,1).toUpperCase() + stringParts[i].substr(1) + " ";	
		}
	} else {
		finalName = textureNameString.substr(0,1).toUpperCase() + textureNameString.substr(1);
	}
	
	textureName = new ScreenLabel(finalName, fontSize, fontName, Label::ANTIALIAS_FULL);
	textureName->setPosition(40, 3);
	textureName->setColor(1.0, 1.0, 1.0, 0.5);		
	addChild(textureName);

	textureFileName = new ScreenLabel("None", fontSize, fontName, Label::ANTIALIAS_FULL);
	textureFileName->setPosition(40, 20);
	textureFileName->setColor(1.0, 1.0, 1.0, 0.8);		
	addChild(textureFileName);

}

MaterialTextureSlot::~MaterialTextureSlot() {
	delete bgShape;
	delete imageShape;
		
	delete textureName;
	delete textureFileName;		
}

MaterialEditorPane::~MaterialEditorPane() {

}

MaterialMainWindow::MaterialMainWindow() : UIElement() {

	materialPane = new MaterialEditorPane();
	addChild(materialPane);
	
	enableScissor = true;
}
	
void MaterialMainWindow::Resize(Number width, Number height) {
	materialPane->setPosition((width-materialPane->getWidth())/2.0, (height-materialPane->getHeight())/2.0);
	
	Vector2 pos = getScreenPosition();	
	scissorBox.setRect(pos.x,pos.y,width, height);
}

MaterialBrowser::MaterialBrowser() : UIElement() {
	treeContainer = new UITreeContainer("boxIcon.png", L"Material Library", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
		
	shadersNode = treeContainer->getRootNode()->addTreeChild("folder.png", "Shaders", NULL);
	materialsNode = treeContainer->getRootNode()->addTreeChild("folder.png", "Materials", NULL);
	cubemapsNode = treeContainer->getRootNode()->addTreeChild("folder.png", "Cubemaps", NULL);
	cubemapsNode = treeContainer->getRootNode()->addTreeChild("folder.png", "Post Effects", NULL);
				
	addChild(treeContainer);		
	selectedData = NULL;
	
	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->setColor(0.1, 0.1, 0.1, 1.0);
	
	newMaterialButton = new UIImageButton("Images/new_material.png");
	addChild(newMaterialButton);
	newMaterialButton->setPosition(5,5);
	
	selectedNode = NULL;

}


void MaterialBrowser::handleEvent(Event *event) {

	if(event->getDispatcher() == treeContainer->getRootNode()) {
		if(event->getEventCode() == UITreeEvent::SELECTED_EVENT){ 
			selectedNode = treeContainer->getRootNode()->getSelectedNode();			
			MaterialBrowserData *data = (MaterialBrowserData *)selectedNode->getUserData();
			selectedData =  data;
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
	
	ScreenEntity::handleEvent(event);
}


UITree *MaterialBrowser::addMaterial(Material *material) {
	MaterialBrowserData *data = new MaterialBrowserData();
	data->material = material;
	return materialsNode->addTreeChild("material_icon.png", material->getName(), (void*)data);
}

MaterialBrowser::~MaterialBrowser() {

}

void MaterialBrowser::Resize(Number width, Number height) {
	treeContainer->Resize(width, height-32);
	treeContainer->setPosition(0, 32);
	
	headerBg->setShapeSize(width, 32);	
}

PolycodeMaterialEditor::PolycodeMaterialEditor() : PolycodeEditor(true){
	selectedMaterialNode = NULL;
}

PolycodeMaterialEditor::~PolycodeMaterialEditor() {
	
}

bool PolycodeMaterialEditor::openFile(OSFileEntry filePath) {
	
	
	grid = new ScreenImage("Images/editorGrid.png");
	
	addChild(grid);
	grid->snapToPixels = true;	
	grid->getTexture()->clamp = false;
	grid->getTexture()->recreateFromImageData();	
	
	mainSizer = new UIHSizer(100,100,200,false);
	addChild(mainSizer);	
	
	materialBrowser = new MaterialBrowser();
	mainSizer->addRightChild(materialBrowser);
	
	materialBrowser->addEventListener(this, Event::CHANGE_EVENT);
	
	materials = CoreServices::getInstance()->getMaterialManager()->loadMaterialsFromFile(filePath.fullPath);
	
	for(int i=0; i < materials.size(); i++) {
		materialBrowser->addMaterial(materials[i]);
	}
	
	mainWindow = new MaterialMainWindow();
	mainSizer->addLeftChild(mainWindow);
	
	mainWindow->materialPane->addEventListener(this, Event::CHANGE_EVENT);
	
	materialBrowser->newMaterialButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeMaterialEditor::handleDroppedFile(OSFileEntry file, Number x, Number y) {		
	mainWindow->materialPane->handleDroppedFile(file, x,y);
}

String PolycodeMaterialEditor::createStringValue(unsigned int type, void *value) {
	String retString;
	
	switch(type) {
		case ProgramParam::PARAM_Number:
			retString = String::NumberToString(*((Number*)value));
		break;
		case ProgramParam::PARAM_Color:
		{
			Color color = *((Color*)value);
			retString = String::NumberToString(color.r) + " " + String::NumberToString(color.g) + " " + String::NumberToString(color.b) + " " + String::NumberToString(color.a);
		}
		break;
		case ProgramParam::PARAM_Vector2:
		{
			Vector2 vec = *((Vector2*)value);
			retString = String::NumberToString(vec.x) + " " + String::NumberToString(vec.y);
		}
		break;
		case ProgramParam::PARAM_Vector3:
		{
			Vector3 vec = *((Vector3*)value);
			retString = String::NumberToString(vec.x) + " " + String::NumberToString(vec.y) + " " + String::NumberToString(vec.z);
		}
		break;
	}
	
	return retString;
}

void PolycodeMaterialEditor::saveFile() {

	Object fileData;
	fileData.root.name = "polycode_material_library";
	
	ObjectEntry *materialsEntry = fileData.root.addChild("materials");
	
	for(int i=0; i < materials.size(); i++) {
		Material *material = materials[i];				
		
		ObjectEntry *materialEntry = materialsEntry->addChild("material");
		materialEntry->addChild("name", material->getName());
		materialEntry->addChild("blendingMode", material->blendingMode);
		
		if(material->getShader(0) && material->getShaderBinding(0)) {
				
		Shader *shader = material->getShader(0);
		
		ObjectEntry *shaderEntry = materialEntry->addChild("shader");
		shaderEntry->addChild("name", shader->getName());		
		ObjectEntry *texturesEntry = shaderEntry->addChild("textures");
		
		ShaderBinding *shaderBinding = material->getShaderBinding(0);
		for(int j=0; j < shader->expectedTextures.size(); j++) {
			Texture *texture = shaderBinding->getTexture(shader->expectedTextures[j]);
			if(texture) {
				String texturePath = texture->getResourcePath();
				texturePath = texturePath.replace(parentProject->getRootFolder()+"/", "");
				
				ObjectEntry *textureEntry = texturesEntry->addChild("texture", texturePath);
				textureEntry->addChild("name", shader->expectedTextures[j]);
			}
		}

		if(shader->expectedFragmentParams.size() > 0 || shader->expectedVertexParams.size() > 0) {
			ObjectEntry *paramsEntry = shaderEntry->addChild("params");
			
			for(int j=0; j < shader->expectedFragmentParams.size(); j++) {
				if(shaderBinding->getLocalParamByName(shader->expectedFragmentParams[j].name) && !shader->expectedFragmentParams[j].isAuto) {
				ObjectEntry *paramEntry = paramsEntry->addChild("param");
				paramEntry->addChild("name", shader->expectedFragmentParams[j].name);
				paramEntry->addChild("type", shader->expectedFragmentParams[j].typeString);
				paramEntry->addChild("value", createStringValue(shader->expectedFragmentParams[j].paramType, shaderBinding->getLocalParamByName(shader->expectedFragmentParams[j].name)->data));
				}
			}

			for(int j=0; j < shader->expectedVertexParams.size(); j++) {
				if(shaderBinding->getLocalParamByName(shader->expectedVertexParams[j].name) && !shader->expectedVertexParams[j].isAuto) {
				ObjectEntry *paramEntry = paramsEntry->addChild("param");
				paramEntry->addChild("name", shader->expectedVertexParams[j].name);
				paramEntry->addChild("type", shader->expectedVertexParams[j].typeString);
				paramEntry->addChild("value", createStringValue(shader->expectedVertexParams[j].paramType, shaderBinding->getLocalParamByName(shader->expectedVertexParams[j].name)->data));
				}
			}
			}
			
		}
	}
	
	fileData.saveToXML(filePath);

}

void PolycodeMaterialEditor::handleEvent(Event *event) {

	if(event->getDispatcher() == mainWindow->materialPane && event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
		if(selectedMaterialNode && mainWindow->materialPane->currentMaterial) {
			selectedMaterialNode->setLabelText(mainWindow->materialPane->currentMaterial->getName());
		}
	}
		
	if(event->getDispatcher() == materialBrowser->newMaterialButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		Material *newMaterial = CoreServices::getInstance()->getMaterialManager()->createMaterial("Untitled", "DefaultShader");
			materialBrowser->addMaterial(newMaterial)->setSelected();
			materials.push_back(newMaterial);
	}	
		

	if(event->getDispatcher() == materialBrowser) {
		if(event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
			if(materialBrowser->selectedData)  {
				if(materialBrowser->selectedData->material) {
					mainWindow->materialPane->setMaterial(materialBrowser->selectedData->material);
					selectedMaterialNode = materialBrowser->selectedNode;
				}
			}			
		}
	}
}

void PolycodeMaterialEditor::Resize(int x, int y) {
	grid->setImageCoordinates(0,0,x,y);	
	mainSizer->Resize(x,y);
	PolycodeEditor::Resize(x,y);
}

