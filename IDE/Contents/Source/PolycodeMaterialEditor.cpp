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
#include "PolycodeFrame.h"

extern UIColorPicker *globalColorPicker;
extern UIGlobalMenu *globalMenu;
extern PolycodeFrame *globalFrame;

ShaderEditorPane::ShaderEditorPane() : UIElement() {	

	changingShader = false;
	currentShader = NULL;

	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));	
	
	propList = new PropList("SHADER EDITOR");
	addChild(propList);
	propList->setPosition(0, 0);
	
	PropSheet *baseProps = new PropSheet("SHADER SETTINGS", "");
	propList->addPropSheet(baseProps);
	
	nameProp = new StringProp("Name");
	baseProps->addProp(nameProp);	
	nameProp->addEventListener(this, Event::CHANGE_EVENT);	
	
	screenShaderProp = new BoolProp("Screen shader");
	baseProps->addProp(screenShaderProp);	
	screenShaderProp->addEventListener(this, Event::CHANGE_EVENT);	
	
	
	vertexProgramProp = new ComboProp("Vertex prog.");
	baseProps->addProp(vertexProgramProp);	
	vertexProgramProp->addEventListener(this, Event::CHANGE_EVENT);	

	fragmentProgramProp = new ComboProp("Fragment prog.");
	baseProps->addProp(fragmentProgramProp);	
	fragmentProgramProp->addEventListener(this, Event::CHANGE_EVENT);	
	
	areaLightsProp = new NumberProp("Num area lights");
	baseProps->addProp(areaLightsProp);	
	areaLightsProp->addEventListener(this, Event::CHANGE_EVENT);

	spotLightsProp = new NumberProp("Num spotlights");
	baseProps->addProp(spotLightsProp);	
	spotLightsProp->addEventListener(this, Event::CHANGE_EVENT);

	baseProps->propHeight = 220;
	
	PropSheet *vertexProps = new PropSheet("VERTEX PROGRAM OPTIONS", "");
	propList->addPropSheet(vertexProps);

	PropSheet *fragmentProps = new PropSheet("FRAGMENT PROGRAM OPTIONS", "");
	propList->addPropSheet(fragmentProps);


	propList->updateProps();
	
	enabled = false;
}

ShaderEditorPane::~ShaderEditorPane() {

}

void ShaderEditorPane::handleEvent(Event *event) {
	if(!changingShader) {
	
		if(event->getDispatcher() == nameProp) {
			currentShader->setName(nameProp->get());
			dispatchEvent(new Event(), Event::CHANGE_EVENT);			
		}
	
		if(event->getDispatcher() == screenShaderProp) {
			currentShader->screenShader = screenShaderProp->get();
			dispatchEvent(new Event(), Event::CHANGE_EVENT);			
		}
				
		if(event->getDispatcher() == areaLightsProp) {
			currentShader->numAreaLights = floor(areaLightsProp->get());
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}

		if(event->getDispatcher() == spotLightsProp) {
			currentShader->numSpotLights = floor(spotLightsProp->get());
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}		
		
		if(event->getDispatcher() == vertexProgramProp) {
			ShaderProgram* vpProgram = (ShaderProgram*)vertexProgramProp->comboEntry->getSelectedItem()->data;
			if(vpProgram) {			
				currentShader->setVertexProgram(vpProgram);
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
			} else {
				globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
				std::vector<String> extensions;
				extensions.push_back("vert");
				choosingVertexProgram = true;
				globalFrame->showAssetBrowser(extensions);				
			}
		}		

		if(event->getDispatcher() == fragmentProgramProp) {
			ShaderProgram* fpProgram = (ShaderProgram*)fragmentProgramProp->comboEntry->getSelectedItem()->data;
			if(fpProgram) {			
				currentShader->setFragmentProgram(fpProgram);
				dispatchEvent(new Event(), Event::CHANGE_EVENT);
			} else {
				globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
				std::vector<String> extensions;
				extensions.push_back("frag");
				choosingVertexProgram = false;
				globalFrame->showAssetBrowser(extensions);			
			}
		}
	}
	
	if(event->getDispatcher() == globalFrame->assetBrowser && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::OK_EVENT) {
		String newProgramPath = globalFrame->assetBrowser->getFullSelectedAssetPath();
		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		

		OSFileEntry entry(newProgramPath, OSFileEntry::TYPE_FILE);
		ShaderProgram *newProgram = CoreServices::getInstance()->getMaterialManager()->createProgramFromFile(newProgramPath);
		newProgram->reloadOnFileModify = true;
		if(newProgram) {
			newProgram->setResourceName(entry.name);
			newProgram->setResourcePath(newProgramPath);
			CoreServices::getInstance()->getResourceManager()->addResource(newProgram);
		}

		if(choosingVertexProgram) {
			currentShader->setVertexProgram(newProgram);			
		} else {
			currentShader->setFragmentProgram(newProgram);		
		}
		
		dispatchEvent(new Event(), Event::CHANGE_EVENT);		
		globalFrame->hideModal();
		
		reloadPrograms();
	}	
}

void ShaderEditorPane::reloadPrograms() {
	vertexProgramProp->comboEntry->clearItems();
	fragmentProgramProp->comboEntry->clearItems();
		
	vertexProgramProp->comboEntry->addComboItem("Custom...", NULL);
	fragmentProgramProp->comboEntry->addComboItem("Custom...", NULL);	
		
	std::vector<Resource*> programs = CoreServices::getInstance()->getResourceManager()->getResources(Resource::RESOURCE_PROGRAM);
	
	for(int i=0; i < programs.size(); i++) {
		ShaderProgram* program = (ShaderProgram*) programs[i];
		if(program->type == ShaderProgram::TYPE_VERT) {
			vertexProgramProp->comboEntry->addComboItem(program->getResourceName(), (void*)program);
			if(program == currentShader->vp) {
				vertexProgramProp->comboEntry->setSelectedIndex(vertexProgramProp->comboEntry->getNumItems()-1);
			}
		} else if(program->type == ShaderProgram::TYPE_FRAG) {
			fragmentProgramProp->comboEntry->addComboItem(program->getResourceName(), (void*)program);		
			if(program == currentShader->fp) {
				fragmentProgramProp->comboEntry->setSelectedIndex(fragmentProgramProp->comboEntry->getNumItems()-1);
			}			
		}
	}	
}

void ShaderEditorPane::setShader(Shader *shader) {
	changingShader = true;
	
	currentShader = shader;
	
	reloadPrograms();
		
	nameProp->set(shader->getName());
	
	for(int i=0; i < vertexProgramProp->comboEntry->getNumItems(); i++) {
		ShaderProgram* program = (ShaderProgram*) vertexProgramProp->comboEntry->getItemAtIndex(i)->data;
		if(program == shader->vp) {
			vertexProgramProp->comboEntry->setSelectedIndex(i);
		}
	}

	for(int i=0; i < fragmentProgramProp->comboEntry->getNumItems(); i++) {
		ShaderProgram* program = (ShaderProgram*) fragmentProgramProp->comboEntry->getItemAtIndex(i)->data;
		if(program == shader->fp) {
			fragmentProgramProp->comboEntry->setSelectedIndex(i);
		}
	}
	
	screenShaderProp->set(shader->screenShader);
	
	areaLightsProp->set(shader->numAreaLights);
	spotLightsProp->set(shader->numSpotLights);
	
	enabled = true;
	
	changingShader = false;	
}

void ShaderEditorPane::Resize(Number width, Number height) {
	headerBg->setShapeSize(width, 30);	
	propList->Resize(370, height);
	propList->updateProps();
}


MaterialEditorPane::MaterialEditorPane() : UIElement() {	

	changingMaterial = false;
	
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
	shaderTextureSheet->addEventListener(this, Event::CHANGE_EVENT);
	
	vertexOptionsSheet = new ShaderOptionsSheet("VERTEX SHADER OPTIONS", "vertex_options", false);
	propList->addPropSheet(vertexOptionsSheet);
	vertexOptionsSheet->addEventListener(this, Event::CHANGE_EVENT);
	
	fragmentOptionsSheet = new ShaderOptionsSheet("FRAGMENT SHADER OPTIONS", "fragment_options", true);
	propList->addPropSheet(fragmentOptionsSheet);
	fragmentOptionsSheet->addEventListener(this, Event::CHANGE_EVENT);
		
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

	if(event->getDispatcher() == shaderTextureSheet || event->getDispatcher() == vertexOptionsSheet || event->getDispatcher() == fragmentOptionsSheet) {
		if(!changingMaterial) {
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}		
		
	} else if(event->getDispatcher() == blendModeProp) {
		currentMaterial->blendingMode = blendModeProp->get();
		if(!changingMaterial) {
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	} else if(event->getDispatcher() == nameProp) {
		currentMaterial->setName(nameProp->get());
		if(!changingMaterial) {
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
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
		
		if(!changingMaterial) {
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
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
	changingMaterial = true;
	currentMaterial = material;
	previewPrimitive->setMaterial(material);		
	
	reloadShaders();
	
	if(!currentMaterial)
		return;
	
	blendModeProp->set(currentMaterial->blendingMode);
	
	if(currentMaterial->getShader(0)) {	
	for(int i=0; i < shaderProp->comboEntry->getNumItems(); i++) {
		Shader *shader = (Shader*)shaderProp->comboEntry->getItemAtIndex(i)->data;
		if(shader) {
			if(currentMaterial->getShader(0)->getName() == shader->getName()) {
				shaderProp->set(i);
				shaderProp->dispatchEvent(new Event(), Event::CHANGE_EVENT);
				break;
			}
		}
	}
	} else {
		shaderProp->set(0);
		shaderProp->dispatchEvent(new Event(), Event::CHANGE_EVENT);		
	}	
	
	nameProp->set(currentMaterial->getName());
	
	enabled = true;
	changingMaterial = false;
					
}

MaterialEditorPane::~MaterialEditorPane() {

}

MaterialMainWindow::MaterialMainWindow() : UIElement() {

	materialPane = new MaterialEditorPane();
	shaderPane = new ShaderEditorPane();
		
	addChild(materialPane);
	addChild(shaderPane);	
	enableScissor = true;
}
	
void MaterialMainWindow::Resize(Number width, Number height) {	
	Vector2 pos = getScreenPosition();	
	scissorBox.setRect(pos.x,pos.y,width, height);
	materialPane->Resize(width, height);
	shaderPane->Resize(width, height);
}

MaterialBrowser::MaterialBrowser() : UIElement() {
	treeContainer = new UITreeContainer("boxIcon.png", L"Material Library", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
		
	shadersNode = treeContainer->getRootNode()->addTreeChild("Images/shader_icon.png", "Shaders", NULL);
	materialsNode = treeContainer->getRootNode()->addTreeChild("Images/material_icon.png", "Materials", NULL);
	cubemapsNode = treeContainer->getRootNode()->addTreeChild("folder.png", "Cubemaps", NULL);
	cubemapsNode = treeContainer->getRootNode()->addTreeChild("folder.png", "Post Effects", NULL);
				
	addChild(treeContainer);		
	selectedData = NULL;
	
	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));	

	newShaderButton = new UIImageButton("Images/new_shader.png");
	addChild(newShaderButton);
	newShaderButton->setPosition(5,4);
	
	newMaterialButton = new UIImageButton("Images/new_material.png");
	addChild(newMaterialButton);
	newMaterialButton->setPosition(28,4);
	
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

UITree *MaterialBrowser::addShader(Shader *shader) {
	MaterialBrowserData *data = new MaterialBrowserData();
	data->shader = shader;
	return shadersNode->addTreeChild("shader_icon.png", shader->getName(), (void*)data);
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
	
	
	shaders = CoreServices::getInstance()->getMaterialManager()->loadShadersFromFile(filePath.fullPath);
	for(int i=0; i < shaders.size(); i++) {
		materialBrowser->addShader(shaders[i]);
		CoreServices::getInstance()->getMaterialManager()->addShader(shaders[i]);
	}	
	
	materials = CoreServices::getInstance()->getMaterialManager()->loadMaterialsFromFile(filePath.fullPath);	
	for(int i=0; i < materials.size(); i++) {
		materialBrowser->addMaterial(materials[i]);
	}
	
	mainWindow = new MaterialMainWindow();
	mainSizer->addLeftChild(mainWindow);
	
	mainWindow->materialPane->addEventListener(this, Event::CHANGE_EVENT);
	mainWindow->shaderPane->addEventListener(this, Event::CHANGE_EVENT);
	
	mainWindow->shaderPane->parentProject = parentProject;
	
	materialBrowser->newMaterialButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	mainWindow->materialPane->addEventListener(this, Event::CHANGE_EVENT);
	
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
	setHasChanges(false);
}

void PolycodeMaterialEditor::handleEvent(Event *event) {

	if(event->getDispatcher() == mainWindow->materialPane && event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
		if(selectedMaterialNode && mainWindow->materialPane->currentMaterial) {
			selectedMaterialNode->setLabelText(mainWindow->materialPane->currentMaterial->getName());
		}
		setHasChanges(true);
	}

	if(event->getDispatcher() == mainWindow->shaderPane && event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
		if(selectedMaterialNode && mainWindow->shaderPane->currentShader) {
			selectedMaterialNode->setLabelText(mainWindow->shaderPane->currentShader->getName());
		}
		setHasChanges(true);
	}

		
	if(event->getDispatcher() == materialBrowser->newMaterialButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		Material *newMaterial = CoreServices::getInstance()->getMaterialManager()->createMaterial("Untitled", "DefaultShader");
			materialBrowser->addMaterial(newMaterial)->setSelected();
			materials.push_back(newMaterial);
			setHasChanges(true);			
	}	
		

	if(event->getDispatcher() == materialBrowser) {
		if(event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
			if(materialBrowser->selectedData)  {
				mainWindow->materialPane->enabled = false;
				mainWindow->shaderPane->enabled = false;
								
				if(materialBrowser->selectedData->material) {
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->materialPane->setMaterial(materialBrowser->selectedData->material);					
				} else if(materialBrowser->selectedData->shader) {
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->shaderPane->setShader(materialBrowser->selectedData->shader);
				}
			}			
		}
	}
}

void PolycodeMaterialEditor::Resize(int x, int y) {
	mainSizer->Resize(x,y);
	PolycodeEditor::Resize(x,y);
}

