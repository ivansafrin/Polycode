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
#include "PolyCubemap.h"

extern UIColorPicker *globalColorPicker;
extern UIGlobalMenu *globalMenu;
extern PolycodeFrame *globalFrame;

CubemapEditorPane::CubemapEditorPane() : UIElement() {
	currentCubemap = NULL;

	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));	
	
	propList = new PropList("CUBEMAP EDITOR");
	addChild(propList);
	propList->setPosition(0, 0);

	PropSheet *baseProps1 = new PropSheet("CUBEMAP OPTIONS", "");
	propList->addPropSheet(baseProps1);

	nameProp = new StringProp("Name");
	baseProps1->addProp(nameProp);
	
	baseProps1->propHeight = 70;
	
	PropSheet *baseProps = new PropSheet("CUBEMAP TEXTURES", "");
	propList->addPropSheet(baseProps);

	xPosTexture = new TextureProp("X+");
	baseProps->addProp(xPosTexture);
	xNegTexture = new TextureProp("X-");
	baseProps->addProp(xNegTexture);	
	yPosTexture = new TextureProp("Y+");
	baseProps->addProp(yPosTexture);		
	yNegTexture = new TextureProp("Y-");
	baseProps->addProp(yNegTexture);
	zPosTexture = new TextureProp("Z+");
	baseProps->addProp(zPosTexture);
	zNegTexture = new TextureProp("Z-");
	baseProps->addProp(zNegTexture);

	nameProp->addEventListener(this, Event::CHANGE_EVENT);	
	yPosTexture->addEventListener(this, Event::CHANGE_EVENT);
	yNegTexture->addEventListener(this, Event::CHANGE_EVENT);
	xPosTexture->addEventListener(this, Event::CHANGE_EVENT);
	xNegTexture->addEventListener(this, Event::CHANGE_EVENT);
	zPosTexture->addEventListener(this, Event::CHANGE_EVENT);
	zNegTexture->addEventListener(this, Event::CHANGE_EVENT);						
	
	baseProps->propHeight = 220;
	propList->updateProps();
	
	cubemapPreview = new MaterialPreviewBox();
	addChild(cubemapPreview);
	cubemapPreview->setPosition(400, 0);
	
	Material *previewMaterial = CoreServices::getInstance()->getMaterialManager()->createMaterial("CubemapPreview", "LightCube");
	cubemapPreview->setMaterial(previewMaterial);
	enabled = false;
	
}

void CubemapEditorPane::setCubemap(Cubemap *cubemap) {
	enabled = true;
	currentCubemap = cubemap;
	
	nameProp->set(cubemap->getResourceName());
	
	cubemapPreview->previewPrimitive->getLocalShaderOptions()->clearCubemap("lightCube");
	cubemapPreview->previewPrimitive->getLocalShaderOptions()->addCubemap("lightCube", cubemap);	
	
	yPosTexture->set(cubemap->getTexture(Cubemap::CUBEMAP_YPOS));
	yNegTexture->set(cubemap->getTexture(Cubemap::CUBEMAP_YNEG));
	xPosTexture->set(cubemap->getTexture(Cubemap::CUBEMAP_XPOS));
	xNegTexture->set(cubemap->getTexture(Cubemap::CUBEMAP_XNEG));
	zPosTexture->set(cubemap->getTexture(Cubemap::CUBEMAP_ZPOS));
	zNegTexture->set(cubemap->getTexture(Cubemap::CUBEMAP_ZNEG));				
	
}

void CubemapEditorPane::handleEvent(Event *event) {

	if(event->getDispatcher() == nameProp) {
		currentCubemap->setResourceName(nameProp->get());
		dispatchEvent(new Event(), Event::CHANGE_EVENT);					
	}

	if(event->getDispatcher() == yPosTexture) {
		currentCubemap->setTexture(yPosTexture->get(), Cubemap::CUBEMAP_YPOS);
		currentCubemap->recreateFromTextures();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);			
	}	
	
	if(event->getDispatcher() == yNegTexture) {
		currentCubemap->setTexture(yNegTexture->get(), Cubemap::CUBEMAP_YNEG);
		currentCubemap->recreateFromTextures();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);			
	}	

	if(event->getDispatcher() == xPosTexture) {
		currentCubemap->setTexture(xPosTexture->get(), Cubemap::CUBEMAP_XPOS);
		currentCubemap->recreateFromTextures();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);			
	}	

	if(event->getDispatcher() == xNegTexture) {
		currentCubemap->setTexture(xNegTexture->get(), Cubemap::CUBEMAP_XNEG);
		currentCubemap->recreateFromTextures();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);			
	}	

	if(event->getDispatcher() == zPosTexture) {
		currentCubemap->setTexture(zPosTexture->get(), Cubemap::CUBEMAP_ZPOS);
		currentCubemap->recreateFromTextures();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);			
	}	

	if(event->getDispatcher() == zNegTexture) {
		currentCubemap->setTexture(zNegTexture->get(), Cubemap::CUBEMAP_ZNEG);
		currentCubemap->recreateFromTextures();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);			
	}	
	
}

CubemapEditorPane::~CubemapEditorPane() {

}

void CubemapEditorPane::Resize(Number width, Number height) {
	headerBg->setShapeSize(width, 30);	
	propList->Resize(370, height);
	propList->updateProps();
}


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

MaterialPreviewBox::MaterialPreviewBox() : UIElement() {
	currentMaterial = NULL;
	previewScene = new Scene(true);	
	
	renderTexture = new SceneRenderTexture(previewScene, previewScene->getDefaultCamera(), 512, 512);
	
	ScenePrimitive *previewBg = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 15.0, 15.0, 15.0);
	previewBg->Yaw(45.0);
	previewBg->backfaceCulled = false;
	
	Material *bgMaterial = CoreServices::getInstance()->getMaterialManager()->createMaterial("MaterialEditorBg", "Unlit");
	
	previewBg->setMaterial(bgMaterial);
	Texture *tex = CoreServices::getInstance()->getMaterialManager()->createTextureFromFile("Images/material_grid.png");
	if(previewBg->getLocalShaderOptions()) {
	previewBg->getLocalShaderOptions()->addTexture("diffuse", tex);
	}
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
	previewBase->setPosition(0, 0);
	addChild(previewBase);
	
	previewShape = new ScreenShape(ScreenShape::SHAPE_RECT, 256, 256);
	previewShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	previewShape->setTexture(renderTexture->getTargetTexture());
	previewShape->setPosition(20,40);
	previewShape->strokeEnabled = true;
	previewShape->strokeColor = Color(1.0, 1.0, 1.0, 0.2);
	previewShape->setStrokeWidth(1.0);
	previewBase->addChild(previewShape);
	
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

	showPrimitive(0);
}

void MaterialPreviewBox::clearMaterial() {
	previewPrimitive->clearMaterial();
}

MaterialPreviewBox::~MaterialPreviewBox() {

}

void MaterialPreviewBox::setMaterial(Material *material) {
	currentMaterial = material;
	previewPrimitive->setMaterial(material);	
	
}

void MaterialPreviewBox::showPrimitive(unsigned int index) {
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

void MaterialPreviewBox::handleEvent(Event *event) {
	for(int i=0; i < shapeSwitches.size(); i++) {
		if(event->getDispatcher() == shapeSwitches[i]) {
			if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
				showPrimitive(i);
			}
		}
	}
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
		
	shaderOptionsSheet = new ShaderOptionsSheet("SHADER OPTIONS", "shader_options");
	propList->addPropSheet(shaderOptionsSheet);
	shaderOptionsSheet->addEventListener(this, Event::CHANGE_EVENT);
		
	propList->updateProps();
							
	
	materialPreview = new MaterialPreviewBox();
	addChild(materialPreview);
	materialPreview->setPosition(400, 0);
	
	Config *conf = CoreServices::getInstance()->getConfig();	
	String fontName = conf->getStringValue("Polycode", "uiDefaultFontName");	
				
	currentMaterial = NULL;	
	
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

void MaterialEditorPane::handleEvent(Event *event) {

	if(event->getDispatcher() == currentMaterial) {
		shaderTextureSheet->setShader(currentMaterial->getShader(0), currentMaterial);
		shaderOptionsSheet->setShader(currentMaterial->getShader(0), currentMaterial);		
	}

	if(event->getDispatcher() == shaderTextureSheet || event->getDispatcher() == shaderOptionsSheet) {
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
				materialPreview->clearMaterial();
				
				ShaderBinding *newShaderBinding = selectedShader->createBinding();				
				currentMaterial->addShader(selectedShader, newShaderBinding);
				materialPreview->setMaterial(currentMaterial);					
			}
			
			shaderTextureSheet->setShader(selectedShader, currentMaterial);
			shaderOptionsSheet->setShader(selectedShader, currentMaterial);
		}
		
		if(!changingMaterial) {
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}		
	}
}

void MaterialEditorPane::setMaterial(Material *material) {
	changingMaterial = true;
	
	if(currentMaterial) {
		currentMaterial->removeAllHandlersForListener(this);
	}
	
	currentMaterial = material;
	materialPreview->setMaterial(material);		
	
	material->addEventListener(this, Event::RESOURCE_RELOAD_EVENT);
	
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
	cubemapPane = new CubemapEditorPane();
		
	addChild(materialPane);
	addChild(shaderPane);	
	addChild(cubemapPane);
	enableScissor = true;
}
	
void MaterialMainWindow::Resize(Number width, Number height) {	
	Vector2 pos = getScreenPosition();	
	scissorBox.setRect(pos.x,pos.y,width, height);
	materialPane->Resize(width, height);
	shaderPane->Resize(width, height);
	cubemapPane->Resize(width, height);	
}

MaterialBrowser::MaterialBrowser() : UIElement() {
	treeContainer = new UITreeContainer("boxIcon.png", L"Material Library", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
		
	shadersNode = treeContainer->getRootNode()->addTreeChild("Images/shader_icon.png", "Shaders", NULL);
	materialsNode = treeContainer->getRootNode()->addTreeChild("Images/material_icon.png", "Materials", NULL);
	cubemapsNode = treeContainer->getRootNode()->addTreeChild("Images/cubemap_icon.png", "Cubemaps", NULL);
	postEffectsNode = treeContainer->getRootNode()->addTreeChild("folder.png", "Post Effects", NULL);
				
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
	newMaterialButton->setPosition(32,4);

	newCubemapButton = new UIImageButton("Images/new_cubemap.png");
	addChild(newCubemapButton);
	newCubemapButton->setPosition(59,4);
	
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

UITree *MaterialBrowser::addCubemap(Cubemap *cubemap) {
	MaterialBrowserData *data = new MaterialBrowserData();
	data->cubemap = cubemap;
	return cubemapsNode->addTreeChild("cubemap_icon.png", cubemap->getResourceName(), (void*)data);	
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
		CoreServices::getInstance()->getResourceManager()->addResource(shaders[i]);
	}	

	cubemaps = CoreServices::getInstance()->getMaterialManager()->loadCubemapsFromFile(filePath.fullPath);
	for(int i=0; i < cubemaps.size(); i++) {
		materialBrowser->addCubemap(cubemaps[i]);
		CoreServices::getInstance()->getResourceManager()->addResource(cubemaps[i]);
	}	

	
	materials = CoreServices::getInstance()->getMaterialManager()->loadMaterialsFromFile(filePath.fullPath);	
	for(int i=0; i < materials.size(); i++) {
		materialBrowser->addMaterial(materials[i]);
	}
	
	mainWindow = new MaterialMainWindow();
	mainSizer->addLeftChild(mainWindow);
	
	mainWindow->materialPane->addEventListener(this, Event::CHANGE_EVENT);
	mainWindow->shaderPane->addEventListener(this, Event::CHANGE_EVENT);
	mainWindow->cubemapPane->addEventListener(this, Event::CHANGE_EVENT);
		
	mainWindow->shaderPane->parentProject = parentProject;
	
	materialBrowser->newMaterialButton->addEventListener(this, UIEvent::CLICK_EVENT);
	materialBrowser->newShaderButton->addEventListener(this, UIEvent::CLICK_EVENT);
	materialBrowser->newCubemapButton->addEventListener(this, UIEvent::CLICK_EVENT);
			
	mainWindow->materialPane->addEventListener(this, Event::CHANGE_EVENT);
	
	PolycodeEditor::openFile(filePath);
	return true;
}

String PolycodeMaterialEditor::createStringValue(unsigned int type, void *value) {
	String retString;
	
	switch(type) {
		case ProgramParam::PARAM_NUMBER:
			retString = String::NumberToString(*((Number*)value));
		break;
		case ProgramParam::PARAM_COLOR:
		{
			Color color = *((Color*)value);
			retString = String::NumberToString(color.r) + " " + String::NumberToString(color.g) + " " + String::NumberToString(color.b) + " " + String::NumberToString(color.a);
		}
		break;
		case ProgramParam::PARAM_VECTOR2:
		{
			Vector2 vec = *((Vector2*)value);
			retString = String::NumberToString(vec.x) + " " + String::NumberToString(vec.y);
		}
		break;
		case ProgramParam::PARAM_VECTOR3:
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

	ObjectEntry *shadersEntry = fileData.root.addChild("shaders");
	for(int i=0; i < shaders.size(); i++) {
		ObjectEntry *shaderEntry = shadersEntry->addChild("shader");
		shaderEntry->addChild("type", String("glsl"));
		shaderEntry->addChild("name", shaders[i]->getName());
		shaderEntry->addChild("numAreaLights", shaders[i]->numAreaLights);
		shaderEntry->addChild("numSpotLights", shaders[i]->numSpotLights);
		shaderEntry->addChild("screen", shaders[i]->screenShader);

		ObjectEntry *vpEntry = shaderEntry->addChild("vp");
		String sourcePath = shaders[i]->vp->getResourcePath();
		sourcePath = sourcePath.replace(parentProject->getRootFolder()+"/", "");
		vpEntry->addChild("source", sourcePath);
				
		ObjectEntry *fpEntry = shaderEntry->addChild("fp");
		sourcePath = shaders[i]->fp->getResourcePath();
		sourcePath = sourcePath.replace(parentProject->getRootFolder()+"/", "");		
		fpEntry->addChild("source", sourcePath);
	}

	ObjectEntry *cubemapsEntry = fileData.root.addChild("cubemaps");
	
	for(int i=0; i < cubemaps.size(); i++) {
		ObjectEntry *cubemapEntry = cubemapsEntry->addChild("cubemap");
		cubemapEntry->addChild("name", cubemaps[i]->getResourceName());
		
		cubemapEntry->addChild("xPos", cubemaps[i]->getTexture(Cubemap::CUBEMAP_XPOS)->getResourcePath());
		cubemapEntry->addChild("xNeg", cubemaps[i]->getTexture(Cubemap::CUBEMAP_XNEG)->getResourcePath());
		cubemapEntry->addChild("yPos", cubemaps[i]->getTexture(Cubemap::CUBEMAP_YPOS)->getResourcePath());
		cubemapEntry->addChild("yNeg", cubemaps[i]->getTexture(Cubemap::CUBEMAP_YNEG)->getResourcePath());
		cubemapEntry->addChild("zPos", cubemaps[i]->getTexture(Cubemap::CUBEMAP_ZPOS)->getResourcePath());
		cubemapEntry->addChild("zNeg", cubemaps[i]->getTexture(Cubemap::CUBEMAP_ZNEG)->getResourcePath());										
	}
	
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

		for(int j=0; j < shader->expectedCubemaps.size(); j++) {
			Cubemap *cubemap = shaderBinding->getCubemap(shader->expectedCubemaps[j]);
			if(cubemap) {
				String cubemapName = cubemap->getResourceName();
				ObjectEntry *cubemapEntry = texturesEntry->addChild("cubemap", cubemapName);
				cubemapEntry->addChild("name", shader->expectedCubemaps[j]);
			}
		}


		if(shader->expectedParams.size() > 0 || shader->expectedParams.size() > 0) {
			ObjectEntry *paramsEntry = shaderEntry->addChild("params");
			
			for(int j=0; j < shader->expectedParams.size(); j++) {
				if(shaderBinding->getLocalParamByName(shader->expectedParams[j].name)) {
					ObjectEntry *paramEntry = paramsEntry->addChild("param");
					paramEntry->addChild("name", shader->expectedParams[j].name);
					paramEntry->addChild("value", createStringValue(shader->expectedParams[j].type, shaderBinding->getLocalParamByName(shader->expectedParams[j].name)->data));
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

	if(event->getDispatcher() == mainWindow->cubemapPane && event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
		if(selectedMaterialNode && mainWindow->cubemapPane->currentCubemap) {
			selectedMaterialNode->setLabelText(mainWindow->cubemapPane->currentCubemap->getResourceName());
		}
		setHasChanges(true);
	}

		
	if(event->getDispatcher() == materialBrowser->newMaterialButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		Material *newMaterial = CoreServices::getInstance()->getMaterialManager()->createMaterial("Untitled", "DefaultShader");
			materialBrowser->addMaterial(newMaterial)->setSelected();
			materials.push_back(newMaterial);
			setHasChanges(true);			
	}	

	if(event->getDispatcher() == materialBrowser->newShaderButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
			Shader *newShader = CoreServices::getInstance()->getMaterialManager()->createShader("glsl", "Untitled", "Unlit.vert", "Unlit.frag", false);
			if(newShader) {
				materialBrowser->addShader(newShader);
				shaders.push_back(newShader);
				CoreServices::getInstance()->getMaterialManager()->addShader(newShader);
				setHasChanges(true);	
			} else {
				printf("Error creating shader!\n");
			}
	}	

	if(event->getDispatcher() == materialBrowser->newCubemapButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {	
		Cubemap *cubemap = CoreServices::getInstance()->getRenderer()->createCubemap(
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, "default.png"),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, "default.png"),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, "default.png"),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, "default.png"),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, "default.png"),
							 (Texture*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_TEXTURE, "default.png"));
		cubemap->setResourceName("Cubemap"+String::IntToString(cubemaps.size()));
		cubemaps.push_back(cubemap);
		materialBrowser->addCubemap(cubemap);
		setHasChanges(true);
		CoreServices::getInstance()->getResourceManager()->addResource(cubemap);
	}	
		

	if(event->getDispatcher() == materialBrowser) {
		if(event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
			if(materialBrowser->selectedData)  {
				mainWindow->materialPane->enabled = false;
				mainWindow->shaderPane->enabled = false;
				mainWindow->cubemapPane->enabled = false;
												
				if(materialBrowser->selectedData->material) {
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->materialPane->setMaterial(materialBrowser->selectedData->material);					
				} else if(materialBrowser->selectedData->shader) {
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->shaderPane->setShader(materialBrowser->selectedData->shader);
				} else if(materialBrowser->selectedData->cubemap) {
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->cubemapPane->setCubemap(materialBrowser->selectedData->cubemap);
				}

			}			
		}
	}
}

void PolycodeMaterialEditor::Resize(int x, int y) {
	mainSizer->Resize(x,y);
	PolycodeEditor::Resize(x,y);
}

