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

MaterialEditorPane::MaterialEditorPane() : UIElement() {	
	
	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));	
	
	propList = new PropList("MATERIAL EDITOR");
	addChild(propList);
	propList->setPosition(0, 0);

	PropSheet *baseProps = new PropSheet("MATERIAL SETTINGS", "");
	propList->addPropSheet(baseProps);
	
	nameProp = new StringProp("Name");
	baseProps->addProp(nameProp);	
	nameProp->addEventListener(this, Event::CHANGE_EVENT);
		
	shaderProp = new ComboProp("Shader");
	baseProps->addProp(shaderProp);
	shaderProp->addEventListener(this, Event::CHANGE_EVENT);
	
	blendModeProp = new ComboProp("Blend mode");
	baseProps->addProp(blendModeProp);
	blendModeProp->addEventListener(this, Event::CHANGE_EVENT);
		
	blendModeProp->comboEntry->addComboItem("Normal");
	blendModeProp->comboEntry->addComboItem("Lighten");
	blendModeProp->comboEntry->addComboItem("Color");
	blendModeProp->comboEntry->addComboItem("Premultiplied");
	blendModeProp->comboEntry->addComboItem("Multiply");	
	
	baseProps->propHeight = 130;	
	
	shaderTextureSheet = new ShaderTexturesSheet();
	propList->addPropSheet(shaderTextureSheet);			
	
	vertexOptionsSheet = new ShaderOptionsSheet("VERTEX SHADER OPTIONS", "vertex_options", false);
	propList->addPropSheet(vertexOptionsSheet);

	fragmentOptionsSheet = new ShaderOptionsSheet("FRAGMENT SHADER OPTIONS", "fragment_options", true);
	propList->addPropSheet(fragmentOptionsSheet);
	
	propList->updateProps();
						
	// TODO: Move the preview widget to its own class
	
	previewScene = new Scene(true);	
	
	renderTexture = new SceneRenderTexture(previewScene, previewScene->getDefaultCamera(), 512, 512);
	
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
	
	previewBase = new ScreenEntity();
	previewBase->processInputEvents = true;
	previewBase->setPosition(400, 0);
	addChild(previewBase);
	
	previewShape = new ScreenShape(ScreenShape::SHAPE_RECT, 256, 256);
	previewShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	previewShape->setTexture(renderTexture->getTargetTexture());
	previewShape->setPosition(20,40);
	previewShape->strokeEnabled = true;
	previewShape->strokeColor = Color(1.0, 1.0, 1.0, 0.2);
	previewShape->setStrokeWidth(1.0);
	previewBase->addChild(previewShape);
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");
	int fontSize = conf->getNumericValue("Polycode", "uiDefaultFontSize");	
	Number padding = conf->getNumericValue("Polycode", "uiWindowSkinPadding");	
	
	shapeSelector = new ScreenImage("Images/small_selector.png");
	previewBase->addChild(shapeSelector);
	shapeSelector->color.a = 0.4;
	
	shapeSwitches.push_back(new UIImageButton("Images/torus_icon.png"));
	shapeSwitches.push_back(new UIImageButton("Images/sphere_icon.png"));
	shapeSwitches.push_back(new UIImageButton("Images/box_icon.png"));
	shapeSwitches.push_back(new UIImageButton("Images/plane_icon.png"));

	for(int i=0; i < shapeSwitches.size(); i++) {
		previewBase->addChild(shapeSwitches[i]);
		shapeSwitches[i]->setPosition(105 + (25 * i), 300);
		shapeSwitches[i]->addEventListener(this, UIEvent::CLICK_EVENT);
	}
				
	currentMaterial = NULL;	
	showPrimitive(0);
	
	reloadShaders();
	
	enabled = false;
}

void MaterialEditorPane::reloadShaders() {

	shaderProp->comboEntry->clearItems();

	MaterialManager *materialManager = CoreServices::getInstance()->getMaterialManager();
	for(int i=0; i < materialManager->getNumShaders(); i++) {
		if(!materialManager->getShaderByIndex(i)->screenShader) {
			shaderProp->comboEntry->addComboItem(materialManager->getShaderByIndex(i)->getName(), (void*)materialManager->getShaderByIndex(i));
		}
	}	
}

void MaterialEditorPane::Resize(Number width, Number height) {
	headerBg->setShapeSize(width, 30);	
	propList->Resize(370, height);
	propList->updateProps();
}

void MaterialEditorPane::showPrimitive(unsigned int index) {
	for(int i=0; i < shapePrimitives.size(); i++) {
		shapePrimitives[i]->visible = false;	
	}
	shapePrimitives[index]->visible = true;	
	shapeSelector->setPosition(105 - 2 + (25 * index), 298);
	if(currentMaterial) {
		shapePrimitives[index]->setMaterial(currentMaterial);
	}
	previewPrimitive = shapePrimitives[index];
}

void MaterialEditorPane::handleEvent(Event *event) {

	if(event->getDispatcher() == blendModeProp) {
		currentMaterial->blendingMode = blendModeProp->get();
	} else if(event->getDispatcher() == nameProp) {
		currentMaterial->setName(nameProp->get());
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	} else if(event->getDispatcher() == shaderProp) {
		Shader *selectedShader = (Shader*)shaderProp->comboEntry->getSelectedItem()->data;
		if(selectedShader) {			
			if(currentMaterial->getShader(0) != selectedShader) {
				currentMaterial->clearShaders();
				previewPrimitive->clearMaterial();
				
				ShaderBinding *newShaderBinding = selectedShader->createBinding();				
				currentMaterial->addShader(selectedShader, newShaderBinding);
				previewPrimitive->setMaterial(currentMaterial);					
			}
			
			shaderTextureSheet->setShader(selectedShader, currentMaterial);
			vertexOptionsSheet->setShader(selectedShader, currentMaterial);
			fragmentOptionsSheet->setShader(selectedShader, currentMaterial);						
		}
	}
	
	for(int i=0; i < shapeSwitches.size(); i++) {
		if(event->getDispatcher() == shapeSwitches[i]) {
			if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
				showPrimitive(i);
			}
		}
	}
}

void MaterialEditorPane::setMaterial(Material *material) {
	currentMaterial = material;
	previewPrimitive->setMaterial(material);		
	
	if(!currentMaterial)
		return;
	
	blendModeProp->set(currentMaterial->blendingMode);
	
	if(currentMaterial->getShader(0)) {	
	for(int i=0; i < shaderProp->comboEntry->getNumItems(); i++) {
		Shader *shader = (Shader*)shaderProp->comboEntry->getItemAtIndex(i)->data;
		if(shader) {
			if(currentMaterial->getShader(0)->getName() == shader->getName()) {
				shaderProp->set(i);
				break;
			}
		}
	}
	} else {
		shaderProp->set(0);
	}	
	
	nameProp->set(currentMaterial->getName());
	
	enabled = true;
					
}

MaterialEditorPane::~MaterialEditorPane() {

}

MaterialMainWindow::MaterialMainWindow() : UIElement() {

	materialPane = new MaterialEditorPane();
	addChild(materialPane);
	enableScissor = true;
}
	
void MaterialMainWindow::Resize(Number width, Number height) {	
	Vector2 pos = getScreenPosition();	
	scissorBox.setRect(pos.x,pos.y,width, height);
	materialPane->Resize(width, height);
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
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));	

	
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
	treeContainer->Resize(width, height-30);
	treeContainer->setPosition(0, 30);	
	headerBg->setShapeSize(width, 30);	
}

PolycodeMaterialEditor::PolycodeMaterialEditor() : PolycodeEditor(true){
	selectedMaterialNode = NULL;
}

PolycodeMaterialEditor::~PolycodeMaterialEditor() {
	
}

bool PolycodeMaterialEditor::openFile(OSFileEntry filePath) {
	
		
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
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->materialPane->setMaterial(materialBrowser->selectedData->material);
				}
			}			
		}
	}
}

void PolycodeMaterialEditor::Resize(int x, int y) {
	mainSizer->Resize(x,y);
	PolycodeEditor::Resize(x,y);
}

