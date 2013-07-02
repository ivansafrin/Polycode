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

PostEditorPane::PostEditorPane() : UIElement() {
	currentMaterial = NULL;
	
	bottomElement = new UIElement();
	
	headerBgBottom = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	bottomElement->addChild(headerBgBottom);
	headerBgBottom->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBgBottom->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));	
	
	propList = new PropList("POST EFFECT EDITOR");
	bottomElement->addChild(propList);
	
	baseProps = new PropSheet("EFFECT OPTIONS", "");
	propList->addPropSheet(baseProps);

	nameProp = new StringProp("Name");
	baseProps->addProp(nameProp);
	nameProp->addEventListener(this, Event::CHANGE_EVENT);
	
	fp16Prop = new BoolProp("HDR targets");
	fp16Prop->set(false);
	baseProps->addProp(fp16Prop);
	fp16Prop->addEventListener(this, Event::CHANGE_EVENT);
		
	baseProps->propHeight = 100;	

	targetsProps = new RenderTargetsSheet();
	propList->addPropSheet(targetsProps);
		
	passProps = new ShaderPassesSheet();
	propList->addPropSheet(passProps);
	passProps->addEventListener(this, Event::CHANGE_EVENT);
	passProps->addEventListener(this, Event::REMOVE_EVENT);
	passProps->addEventListener(this, Event::SELECT_EVENT);

	optionsPropList = new PropList("SHADER PASS OPTIONS");
	bottomElement->addChild(optionsPropList);
	optionsPropList->setPosition(400, 0);

	targetBindingProps = new TargetBindingsSheet();
	optionsPropList->addPropSheet(targetBindingProps);
	targetBindingProps->addEventListener(this, Event::CHANGE_EVENT);
		
	shaderTextureSheet = new ShaderTexturesSheet();
	optionsPropList->addPropSheet(shaderTextureSheet);

	shaderOptionsSheet = new ShaderOptionsSheet();
	optionsPropList->addPropSheet(shaderOptionsSheet);

	
	topElement = new UIElement();	
	postPreview = new PostPreviewBox();
	topElement->addChild(postPreview);
	postPreview->setPosition(0, 0);
		
	mainSizer = new UIVSizer(100, 100, 300, true);
	mainSizer->setPosition(0, 0);
	mainSizer->addTopChild(topElement);
	mainSizer->addBottomChild(bottomElement);
	mainSizer->addEventListener(this, UIEvent::CHANGE_EVENT);
	addChild(mainSizer);
	enabled = false;
		
}

PostEditorPane::~PostEditorPane() {

}

void PostEditorPane::Resize(Number width, Number height) {
	mainSizer->Resize(width, height);
	headerBgBottom->setShapeSize(width, 30);	
	propList->Resize(width/2.0, height- mainSizer->getMainHeight());
	
	propList->updateProps();
	optionsPropList->Resize(width/2.0, height- mainSizer->getMainHeight());
	optionsPropList->setPosition(floor(width/2.0), optionsPropList->getPosition().y);
	optionsPropList->updateProps();	
	UIElement::Resize(width, height);
	adjustPreview();
}

void PostEditorPane::adjustPreview() {
	targetsProps->normTextureWidth = getWidth();
	targetsProps->normTextureHeight = mainSizer->getMainHeight()-30;
	postPreview->Resize(getWidth(), mainSizer->getMainHeight());
}


void PostEditorPane::setMaterial(Material *material) {
	enabled = true;
	currentMaterial = material;		
		
	nameProp->set(material->getName());
	
	if(currentMaterial->fp16RenderTargets) {
		fp16Prop->set(true);
	} else {
		fp16Prop->set(false);
	}
	
	targetsProps->material = material;
	passProps->setMaterial(material);	
	postPreview->setMaterial(material);
	
	optionsPropList->visible = false;
	optionsPropList->enabled = false;
	
	adjustPreview();
	
	for(int i=0; i < currentMaterial->getNumShaderRenderTargets(); i++) {
		ShaderRenderTarget *target = currentMaterial->getShaderRenderTarget(i);
		if(target->sizeMode == ShaderRenderTarget::SIZE_MODE_NORMALIZED) {
			target->normalizedWidth = targetsProps->normTextureWidth;
			target->normalizedHeight = targetsProps->normTextureHeight;
			currentMaterial->recreateRenderTarget(target);
		}
	}
				
}

void PostEditorPane::handleEvent(Event *event) {
	if(event->getDispatcher() == nameProp) {
		currentMaterial->setName(nameProp->get());
		dispatchEvent(new Event(), Event::CHANGE_EVENT);					
	} else if(event->getDispatcher() == mainSizer && event->getEventCode() == UIEvent::CHANGE_EVENT) {
			propList->Resize(propList->getWidth(), height-mainSizer->getMainHeight());
			propList->updateProps();
			adjustPreview();
	} else if(event->getDispatcher() == passProps || event->getDispatcher() == targetBindingProps) {
		if(event->getEventCode() == Event::REMOVE_EVENT) {
				optionsPropList->visible = false;
				optionsPropList->enabled = false;	
		} else if(event->getEventCode() == Event::CHANGE_EVENT) {
			postPreview->clearMaterial();
			postPreview->setMaterial(currentMaterial);
		} else if(event->getEventCode() == Event::SELECT_EVENT) {
			if(passProps->selectedProp) {
				int shaderIndex = passProps->selectedProp->shaderIndex;
				Material *material = passProps->selectedProp->material;
				ShaderBinding *binding = material->getShaderBinding(shaderIndex);
				targetBindingProps->setShader(currentMaterial->getShader(shaderIndex), material, binding);
				shaderTextureSheet->setShader(currentMaterial->getShader(shaderIndex), material, binding);
				shaderOptionsSheet->setShader(currentMaterial->getShader(shaderIndex), material, binding);		
				optionsPropList->visible = true;
				optionsPropList->enabled = true;	
				
			}
		}
	} else if(event->getDispatcher() == fp16Prop && event->getEventCode() == Event::CHANGE_EVENT) {
		currentMaterial->fp16RenderTargets = fp16Prop->get();
		currentMaterial->recreateRenderTargets();
	}
}



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

PostPreviewBox::PostPreviewBox() : UIElement() {

	headerBg = new ScreenShape(ScreenShape::SHAPE_RECT,10,10);
	addChild(headerBg);
	headerBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));	

	ScreenLabel *label = new ScreenLabel("POST PREVIEW", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(10, 3);

	currentMaterial = NULL;
	previewScene = new Scene(true);	
	
	renderTexture = new SceneRenderTexture(previewScene, previewScene->getDefaultCamera(), 512, 512, true);
	

	CoreServices::getInstance()->getRenderer()->setClippingPlanes(0.1, 100.0);

	previewScene->clearColor.setColor(0.0, 0.0, 0.0, 1.0);	
	previewScene->ambientColor.setColor(0.0, 0.0, 0.0, 1.0);

	mainLight = new SceneLight(SceneLight::AREA_LIGHT, previewScene, 90.0);
	mainLight->setPosition(-6,6,6);
	previewScene->addLight(mainLight);

	secondLight = new SceneLight(SceneLight::AREA_LIGHT, previewScene, 90.0);
	secondLight->setPosition(6,-6,6);
	previewScene->addLight(secondLight);

	previewPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 10.0, 10.0);
	previewScene->addChild(previewPrimitive);
	previewPrimitive->setMaterialByName("DefaultHDR");
	previewPrimitive->setColorInt(198, 192, 166, 255);	
	
	// Avoid ugly crashes if material is missing and is NULL
	Material *mat = previewPrimitive->getMaterial();
	if(mat != NULL)
		mat->getShaderBinding(0)->getLocalParamByName("shininess")->setNumber(90);

	previewPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 0.9, 0.45, 26, 16);
	previewScene->addChild(previewPrimitive);
	previewPrimitive->setMaterialByName("DefaultHDR");
	previewPrimitive->setColorInt(255, 0, 0, 255);	
	previewPrimitive->setPosition(1.5, 0.4, 1.0);

	previewPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_SPHERE, 1.0, 16, 16);
	previewScene->addChild(previewPrimitive);
	previewPrimitive->setMaterialByName("DefaultHDR");
	previewPrimitive->setColorInt(0, 255, 0, 255);
	previewPrimitive->setPosition(-0.8, 1.0, 0.8);

	previewPrimitive = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 2,  2, 2);
	previewPrimitive->getMesh()->calculateNormals(false);	
	previewScene->addChild(previewPrimitive);
	previewPrimitive->setMaterialByName("DefaultHDR");
	previewPrimitive->setColorInt(0, 0, 255, 255);
	previewPrimitive->rotation.yaw = 20;
	previewPrimitive->setPosition(1.0, 1.0, -2.5);
	
	previewScene->getDefaultCamera()->setPosition(0,3.0,5);
	previewScene->getDefaultCamera()->lookAt(Vector3(0.0, 0.5, 0.0));

	
	previewBase = new ScreenEntity();
	previewBase->processInputEvents = true;
	previewBase->setPosition(0, 30);
	addChild(previewBase);
	
	previewShape = new ScreenShape(ScreenShape::SHAPE_RECT, 256, 256);
	previewShape->setPositionMode(ScreenEntity::POSITION_TOPLEFT);	
	previewShape->setTexture(renderTexture->getTargetTexture());
//	previewShape->strokeEnabled = true;
//	previewShape->strokeColor = Color(1.0, 1.0, 1.0, 0.2);
//	previewShape->setStrokeWidth(1.0);
	previewBase->addChild(previewShape);

	spinValue = 0.0;
	
	rotateCheckBox = new UICheckBox("Auto-rotate", false);
	addChild(rotateCheckBox);
	rotateCheckBox->setPosition(150, 2);

	label = new ScreenLabel("EXPOSURE", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(270, 3);
	
	cameraExposureInput = new UITextInput(false, 40, 12);
	addChild(cameraExposureInput);
	cameraExposureInput->setPosition(370, 2);
	cameraExposureInput->setText(String::NumberToString(previewScene->getDefaultCamera()->getExposureLevel()));	
	cameraExposureInput->addEventListener(this, UIEvent::CHANGE_EVENT);

	label = new ScreenLabel("LIGHT INT.", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(430, 3);

	lightStrength = new UITextInput(false, 40, 12);
	addChild(lightStrength);
	lightStrength->setPosition(530, 2);
	lightStrength->setText("90.0");
	lightStrength->addEventListener(this, UIEvent::CHANGE_EVENT);
	
}

void PostPreviewBox::Update() {
	spinValue += CoreServices::getInstance()->getCore()->getElapsed();
	
	if(rotateCheckBox->isChecked()) {
		previewScene->getDefaultCamera()->setPosition(sin(spinValue) * 5.0,3.0, cos(spinValue) * 5.0);
	} else {
		previewScene->getDefaultCamera()->setPosition(0,3.0,5);
	}	
	previewScene->getDefaultCamera()->lookAt(Vector3(0.0, 0.5, 0.0));		

}

void PostPreviewBox::Resize(Number width, Number height) {
	previewShape->setShapeSize(width, height-30);
	headerBg->setShapeSize(width, 30);
	
	int textureWidth = (int)width;
	int textureHeight = (int) (height-30);
	renderTexture->resizeRenderTexture(textureWidth, textureHeight);
	previewShape->setTexture(renderTexture->getTargetTexture());	
	UIElement::Resize(width, height);
	
	if(currentMaterial) {
		for(int i=0; i < currentMaterial->getNumShaderRenderTargets(); i++) {
			currentMaterial->getShaderRenderTarget(i)->normalizedWidth = textureWidth;
			currentMaterial->getShaderRenderTarget(i)->normalizedHeight = textureHeight;
			currentMaterial->recreateRenderTarget(currentMaterial->getShaderRenderTarget(i));
		}
	}
}

PostPreviewBox::~PostPreviewBox() {

}

void PostPreviewBox::setMaterial(Material *material) {
	previewScene->getDefaultCamera()->setPostFilter(material);
}

void PostPreviewBox::clearMaterial() {
	previewScene->getDefaultCamera()->removePostFilter();
}

void PostPreviewBox::handleEvent(Event *event) {
	if(event->getDispatcher() == cameraExposureInput && event->getEventCode() == UIEvent::CHANGE_EVENT) {
		Number newExposure = atof(cameraExposureInput->getText().c_str());
		previewScene->getDefaultCamera()->setExposureLevel(newExposure);
	} else if(event->getDispatcher() == lightStrength && event->getEventCode() == UIEvent::CHANGE_EVENT) {
		Number newStrength = atof(lightStrength->getText().c_str());
		mainLight->setIntensity(newStrength);
		secondLight->setIntensity(newStrength);		
	}
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
		
	shaderOptionsSheet = new ShaderOptionsSheet();
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
		shaderTextureSheet->setShader(currentMaterial->getShader(0), currentMaterial, currentMaterial->getShaderBinding(0));
		shaderOptionsSheet->setShader(currentMaterial->getShader(0), currentMaterial, currentMaterial->getShaderBinding(0));		
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
			
			shaderTextureSheet->setShader(selectedShader, currentMaterial, currentMaterial->getShaderBinding(0));
			shaderOptionsSheet->setShader(selectedShader, currentMaterial, currentMaterial->getShaderBinding(0));
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
	postPane = new PostEditorPane();
		
	addChild(materialPane);
	addChild(shaderPane);	
	addChild(cubemapPane);
	addChild(postPane);	
	enableScissor = true;
}
	
void MaterialMainWindow::Resize(Number width, Number height) {	
	Vector2 pos = getScreenPosition();	
	scissorBox.setRect(pos.x,pos.y,width, height);
	materialPane->Resize(width, height);
	shaderPane->Resize(width, height);
	cubemapPane->Resize(width, height);
	postPane->Resize(width, height);
}

MaterialBrowser::MaterialBrowser() : UIElement() {
	treeContainer = new UITreeContainer("boxIcon.png", L"Material Library", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
		
	shadersNode = treeContainer->getRootNode()->addTreeChild("Images/shader_icon.png", "Shaders", NULL);
	materialsNode = treeContainer->getRootNode()->addTreeChild("Images/material_icon.png", "Materials", NULL);
	cubemapsNode = treeContainer->getRootNode()->addTreeChild("Images/cubemap_icon.png", "Cubemaps", NULL);
	postEffectsNode = treeContainer->getRootNode()->addTreeChild("Images/screenshader_icon.png", "Post Effects", NULL);
				
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
		
	newPostButton = new UIImageButton("Images/new_screenshader.png");
	addChild(newPostButton);
	newPostButton->setPosition(86,4);

	removeButton = new UIImageButton("Images/remove_icon.png");
	addChild(removeButton);
	removeButton->setPosition(0,4);
	
	selectedNode = NULL;

}

void MaterialBrowser::removeSelected() {
	selectedNode->getParent()->removeTreeChild(selectedNode);
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

UITree *MaterialBrowser::addPostMaterial(Material *material) {
	MaterialBrowserData *data = new MaterialBrowserData();
	data->postMaterial = material;
	return postEffectsNode->addTreeChild("screenshader_icon.png", material->getName(), (void*)data);
}

MaterialBrowser::~MaterialBrowser() {

}

void MaterialBrowser::Resize(Number width, Number height) {
	treeContainer->Resize(width, height-30);
	treeContainer->setPosition(0, 30);	
	headerBg->setShapeSize(width, 30);	
	removeButton->setPosition(width - 24, 8);
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

	
	std::vector<Material*> mats = CoreServices::getInstance()->getMaterialManager()->loadMaterialsFromFile(filePath.fullPath);
	
	materials.clear();
	for(int i=0; i < mats.size(); i++) {
		if(mats[i]->screenMaterial) {
			postMaterials.push_back(mats[i]);
		} else {
			materials.push_back(mats[i]);		
		}
	}
	
	for(int i=0; i < materials.size(); i++) {
		materialBrowser->addMaterial(materials[i]);
	}

	for(int i=0; i < postMaterials.size(); i++) {
		materialBrowser->addPostMaterial(postMaterials[i]);
	}
	
	mainWindow = new MaterialMainWindow();
	mainSizer->addLeftChild(mainWindow);
	
	mainWindow->materialPane->addEventListener(this, Event::CHANGE_EVENT);
	mainWindow->shaderPane->addEventListener(this, Event::CHANGE_EVENT);
	mainWindow->cubemapPane->addEventListener(this, Event::CHANGE_EVENT);
	mainWindow->postPane->addEventListener(this, Event::CHANGE_EVENT);
			
	mainWindow->shaderPane->parentProject = parentProject;
	
	materialBrowser->newMaterialButton->addEventListener(this, UIEvent::CLICK_EVENT);
	materialBrowser->newShaderButton->addEventListener(this, UIEvent::CLICK_EVENT);
	materialBrowser->newCubemapButton->addEventListener(this, UIEvent::CLICK_EVENT);
	materialBrowser->newPostButton->addEventListener(this, UIEvent::CLICK_EVENT);
	materialBrowser->removeButton->addEventListener(this, UIEvent::CLICK_EVENT);
					
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

void PolycodeMaterialEditor::saveMaterials(ObjectEntry *materialsEntry, std::vector<Material*> materials) {
	for(int i=0; i < materials.size(); i++) {
		Material *material = materials[i];				
		
		ObjectEntry *materialEntry = materialsEntry->addChild("material");
		materialEntry->addChild("name", material->getName());
		materialEntry->addChild("blendingMode", material->blendingMode);
		
		if(material->screenMaterial) {
			materialEntry->addChild("screen", true);
		}
		
		if(material->screenMaterial) {		
		if(material->getNumShaderRenderTargets() > 0) {		
			ObjectEntry *targetsEntry = materialEntry->addChild("rendertargets");
			if(material->fp16RenderTargets) {
				targetsEntry->addChild("type", String("rgba_fp16"));
			} else {
				targetsEntry->addChild("type", String("rgba"));			
			}
			
			for(int j=0; j < material->getNumShaderRenderTargets(); j++) {
				ObjectEntry *targetEntry = targetsEntry->addChild("rendertarget");
				
				ShaderRenderTarget *target = material->getShaderRenderTarget(j);
				
				targetEntry->addChild("id", target->id);
				if(target->sizeMode == ShaderRenderTarget::SIZE_MODE_NORMALIZED) {
					targetEntry->addChild("sizeMode", "normalized");
				} else {
					targetEntry->addChild("sizeMode", "pixels");
				}
				
				targetEntry->addChild("width", target->width);
				targetEntry->addChild("height", target->height);								
			}
			
			}
		}
		
		if(material->getNumShaders() > 0) {
			for(int s=0; s < material->getNumShaders(); s++) { 
				Shader *shader = material->getShader(s);
				
				ObjectEntry *shaderEntry = materialEntry->addChild("shader");
				shaderEntry->addChild("name", shader->getName());		
				ObjectEntry *texturesEntry = shaderEntry->addChild("textures");
				
				ShaderBinding *shaderBinding = material->getShaderBinding(s);
				
				if(material->screenMaterial) {
					if(shaderBinding->getNumRenderTargetBindings() > 0) {
						ObjectEntry *targetsEntry = shaderEntry->addChild("targettextures");
						for(int j=0; j < shaderBinding->getNumRenderTargetBindings(); j++) {
							RenderTargetBinding *binding = shaderBinding->getRenderTargetBinding(j);
							ObjectEntry *targetEntry = targetsEntry->addChild("targettexture");
							switch(binding->mode) {
								case RenderTargetBinding::MODE_IN:
									targetEntry->addChild("mode", "in");								
									targetEntry->addChild("name", binding->name);
									targetEntry->addChild("id", binding->id);									
								break;
								case RenderTargetBinding::MODE_OUT:
									targetEntry->addChild("mode", "out");								
									targetEntry->addChild("name", binding->name);
									targetEntry->addChild("id", binding->id);								
								break;
								case RenderTargetBinding::MODE_COLOR:
									targetEntry->addChild("mode", "color");
									targetEntry->addChild("name", binding->name);		
								break;
								case RenderTargetBinding::MODE_DEPTH:
									targetEntry->addChild("mode", "depth");
									targetEntry->addChild("name", binding->name);
								break;																								
							}
						}
					}
				}
				
				for(int j=0; j < shader->expectedTextures.size(); j++) {
					Texture *texture = shaderBinding->getTexture(shader->expectedTextures[j]);
					
					bool inRenderBinding = false;
					
					for(int b=0; b < shaderBinding->getNumRenderTargetBindings(); b++) {
						RenderTargetBinding *_binding = shaderBinding->getRenderTargetBinding(b);
						if(_binding->name == shader->expectedTextures[j]) {
							inRenderBinding = true;
						}
					}
					
					if(texture && !inRenderBinding) {
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
	}
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
	saveMaterials(materialsEntry, materials);
	saveMaterials(materialsEntry, postMaterials);
			
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

	if(event->getDispatcher() == mainWindow->postPane && event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
		if(selectedMaterialNode && mainWindow->postPane->currentMaterial) {
			selectedMaterialNode->setLabelText(mainWindow->postPane->currentMaterial->getName());
		}
		setHasChanges(true);
	}

	if(event->getDispatcher() == materialBrowser->newPostButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
	
		Material *newMaterial = CoreServices::getInstance()->getMaterialManager()->createMaterial("PostEffect"+String::IntToString(postMaterials.size()), "PassThrough");
			newMaterial->screenMaterial = true;
			materialBrowser->addPostMaterial(newMaterial)->setSelected();
			postMaterials.push_back(newMaterial);
			setHasChanges(true);			
	}	

	if(event->getDispatcher() == materialBrowser->newMaterialButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
		Material *newMaterial = CoreServices::getInstance()->getMaterialManager()->createMaterial("Untitled", "DefaultShader");
			materialBrowser->addMaterial(newMaterial)->setSelected();
			materials.push_back(newMaterial);
			setHasChanges(true);			
	}	

	if(event->getDispatcher() == materialBrowser->newShaderButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {
			Shader *newShader = CoreServices::getInstance()->getMaterialManager()->createShader("glsl", "Untitled", "default/Unlit.vert", "default/Unlit.frag", false);
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
		
	if(event->getDispatcher() == materialBrowser->removeButton && event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT) {

				mainWindow->materialPane->enabled = false;
				mainWindow->shaderPane->enabled = false;
				mainWindow->cubemapPane->enabled = false;
				mainWindow->postPane->enabled = false;
				
				if(materialBrowser->selectedData) {
				if(materialBrowser->selectedData->material) {
					for(int i=0; i < materials.size(); i++) {
						if(materials[i] == materialBrowser->selectedData->material) {
							materials.erase(materials.begin()+i);
							materialBrowser->removeSelected();
							break;							
						}
					}
				} else if(materialBrowser->selectedData->shader) {
					for(int i=0; i < shaders.size(); i++) {
						if(shaders[i] == materialBrowser->selectedData->shader) {
							shaders.erase(shaders.begin()+i);
							materialBrowser->removeSelected();							
							break;
						}
					}				
				} else if(materialBrowser->selectedData->cubemap) {
					for(int i=0; i < cubemaps.size(); i++) {
						if(cubemaps[i] == materialBrowser->selectedData->cubemap) {
							cubemaps.erase(cubemaps.begin()+i);
							materialBrowser->removeSelected();							
							break;
						}
					}								
				} else if(materialBrowser->selectedData->postMaterial) {
					for(int i=0; i < postMaterials.size(); i++) {
						if(postMaterials[i] == materialBrowser->selectedData->postMaterial) {
							postMaterials.erase(postMaterials.begin()+i);
							materialBrowser->removeSelected();							
							break;
						}
					}												
				}	
				}			
		
	}

	if(event->getDispatcher() == materialBrowser) {
		if(event->getEventType() == "" && event->getEventCode() == Event::CHANGE_EVENT) {
			if(materialBrowser->selectedData)  {
				mainWindow->materialPane->enabled = false;
				mainWindow->shaderPane->enabled = false;
				mainWindow->cubemapPane->enabled = false;
				mainWindow->postPane->enabled = false;
																
				if(materialBrowser->selectedData->material) {
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->materialPane->setMaterial(materialBrowser->selectedData->material);					
				} else if(materialBrowser->selectedData->shader) {
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->shaderPane->setShader(materialBrowser->selectedData->shader);
				} else if(materialBrowser->selectedData->cubemap) {
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->cubemapPane->setCubemap(materialBrowser->selectedData->cubemap);
				} else if(materialBrowser->selectedData->postMaterial) {
					selectedMaterialNode = materialBrowser->selectedNode;				
					mainWindow->postPane->setMaterial(materialBrowser->selectedData->postMaterial);
				}

			}			
		}
	}
}

void PolycodeMaterialEditor::Resize(int x, int y) {
	mainSizer->Resize(x,y);
	PolycodeEditor::Resize(x,y);
}

