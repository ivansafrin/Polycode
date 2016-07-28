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
 
#include "polycode/ide/PolycodeSpriteEditor.h"
#include "polycode/ide/PolycodeFrame.h"

extern UIColorPicker *globalColorPicker;
extern PolycodeFrame *globalFrame;
extern UIGlobalMenu *globalMenu;

SpriteSheetEditor::SpriteSheetEditor(Core *core, ResourcePool *pool, SpriteSet *sprite) : UIElement(core), resourcePool(pool)
{
	this->sprite = sprite;
	willCreateFrame = false;
	zoomScale = 1.0;
	drawCall.options.enableScissor = true;
	
	Texture::clampDefault = false;
	previewBg = new UIImage(core, pool, "main/grid_dark.png");
	addChild(previewBg);
	previewBg->processInputEvents = true;
	
	panning = false;
	
	previewBg->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);
	previewBg->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
	previewBg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	previewBg->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	previewBg->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	previewBg->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	
	previewImage = new UIRect(core, pool, 10, 10);
	previewImage->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	addChild(previewImage);
	
	frameVisualizerMesh = new SceneMesh();
	frameVisualizerMesh->setColor(1.0, 1.0, 1.0, 1.0);
	addChild(frameVisualizerMesh);
	frameVisualizerMesh->setAnchorPoint(-1.0, -1.0, 0.0);
	frameVisualizerMesh->getShaderPass(0).shaderBinding->setTextureForParam("diffuse", pool->loadTexture("main/stipple.png"));
	frameVisualizerMesh->lineWidth = 1; //CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX();

	frameVisualizerMeshSelected = new SceneMesh();
	frameVisualizerMeshSelected->setColor(1.0, 1.0, 0.0, 1.0);
	addChild(frameVisualizerMeshSelected);
	frameVisualizerMeshSelected->setAnchorPoint(-1.0, -1.0, 0.0);
	frameVisualizerMeshSelected->getShaderPass(0).shaderBinding->setTextureForParam("diffuse", pool->loadTexture("main/stipple.png"));
	frameVisualizerMeshSelected->lineWidth = 2;
	
	previewImage->setTexture(sprite->getTexture());
	
	
	transformGrips = new TransformGrips(core, pool);
	transformGrips->addEventListener(this, Event::CHANGE_EVENT);
	addChild(transformGrips);
	
	bottomMenu = new Entity();
	addChild(bottomMenu);
	
	bottomMenu->processInputEvents = true;
	
	bottomMenuRect = new UIRect(core, pool, 100, 100);
	bottomMenu->addChild(bottomMenuRect);
	bottomMenuRect->setAnchorPoint(-1.0, -1.0, 0.0);
	bottomMenuRect->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	changeImageButton = new UIButton(core, pool, "Change image", 120);
	bottomMenu->addChild(changeImageButton);
	changeImageButton->addEventListener(this, UIEvent::CLICK_EVENT);
	changeImageButton->setPosition(5.0, 3.0);
	
	clearFramesButton = new UIButton(core, pool, "Clear", 60);
	bottomMenu->addChild(clearFramesButton);
	clearFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
	clearFramesButton->setPosition(125.0, 3.0);
	
	generateFramesButton = new UIButton(core, pool, "Generate", 70);
	bottomMenu->addChild(generateFramesButton);
	generateFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
	generateFramesButton->setPosition(185.0, 3.0);
	
	generateTypeDropdown = new UIComboBox(core, pool, globalMenu, 120);
	bottomMenu->addChild(generateTypeDropdown);
	generateTypeDropdown->setPosition(255, 3.0);
	
	generateTypeDropdown->addComboItem("Uniform grid");
	generateTypeDropdown->addComboItem("Detect frames");
	
	generateTypeDropdown->setSelectedIndex(0);
	
	generateTypeDropdown->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	generateOptionsButton = new UIButton(core, pool, "Options", 80);
	bottomMenu->addChild(generateOptionsButton);
	generateOptionsButton->setPosition(375.0, 3.0);
	generateOptionsButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	optionsWindow = new UIWindow(core, pool, "Frame generation options", 230.0, 100.0);
	addChild(optionsWindow);
	optionsWindow->hideWindow();
	optionsWindow->visible = false;
	optionsWindow->enabled = false;
	
	uniformOptions = new UIElement(core);
	optionsWindow->addChild(uniformOptions);
	detectOptions = new UIElement(core);
	optionsWindow->addChild(detectOptions);
	detectOptions->visible = false;
	detectOptions->enabled = false;
	
	UILabel *label;
	
	label = new UILabel(core, pool, "Default anchor", 12);
	optionsWindow->addChild(label);
	label->setPosition(120.0 - label->getWidth(), 43.0);
	
	defaultAnchorCombo = new UIComboBox(core, pool, globalMenu, 112.0);
	optionsWindow->addChild(defaultAnchorCombo);
	defaultAnchorCombo->setPosition(130.0, 40.0);
	
	
	defaultAnchorCombo->addComboItem("Center");
	defaultAnchorCombo->addComboItem("Top-left");
	defaultAnchorCombo->addComboItem("Top");
	defaultAnchorCombo->addComboItem("Top-right");
	defaultAnchorCombo->addComboItem("Left");
	defaultAnchorCombo->addComboItem("Right");
	defaultAnchorCombo->addComboItem("Bottom-left");
	defaultAnchorCombo->addComboItem("Bottom");
	defaultAnchorCombo->addComboItem("Bottom-right");
	defaultAnchorCombo->setSelectedIndex(0);
	
	
	defaultAnchors.push_back(Vector2(0.0, 0.0));
	defaultAnchors.push_back(Vector2(-0.5, -0.5));
	defaultAnchors.push_back(Vector2(0.0, -0.5));
	defaultAnchors.push_back(Vector2(0.5, -0.5));
	defaultAnchors.push_back(Vector2(-0.5, 0.0));
	defaultAnchors.push_back(Vector2(0.5, 0.0));
	defaultAnchors.push_back(Vector2(-0.5, 0.5));
	defaultAnchors.push_back(Vector2(0.0, 0.5));
	defaultAnchors.push_back(Vector2(0.5, 0.5));
	
	label = new UILabel(core, pool, "Grid width (px)", 12);
	uniformOptions->addChild(label);
	label->setPosition(120.0 - label->getWidth(), 68.0);
	
	uniformGridWidthInput = new UITextInput(core, pool, false, 100.0, 12);
	uniformOptions->addFocusChild(uniformGridWidthInput);
	uniformGridWidthInput->setPosition(130.0, 65.0);
	uniformGridWidthInput->setText("32");
	uniformGridWidthInput->setNumberOnly(true);

	label = new UILabel(core, pool, "Grid height (px)", 12);
	uniformOptions->addChild(label);
	label->setPosition(120.0 - label->getWidth(), 93.0);
	
	uniformGridHeightInput = new UITextInput(core, pool, false, 100, 12);
	uniformOptions->addFocusChild(uniformGridHeightInput);
	uniformGridHeightInput->setPosition(130.0, 90);
	uniformGridHeightInput->setText("32");
	uniformGridHeightInput->setNumberOnly(true);
	
	label = new UILabel(core, pool, "Min. distance (px)", 12);
	detectOptions->addChild(label);
	label->setPosition(120.0 - label->getWidth(), 68.0);
	
	minimumDistanceInput = new UITextInput(core, pool, false, 30, 12);
	detectOptions->addFocusChild(minimumDistanceInput);
	minimumDistanceInput->setPosition(130.0, 65.0);
	minimumDistanceInput->setText("0");
	minimumDistanceInput->setNumberOnly(true);
   
	headerBg = new UIRect(core, pool, 10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	label = new UILabel(core, pool, "SPRITE SHEET", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	
	addChild(label);
	label->setPosition(10, 3);
	
	bgSelector = new UIIconSelector(core, pool);
	bgSelector->addIcon("spriteEditor/grid_icon_dark.png");
	bgSelector->addIcon("spriteEditor/grid_icon_light.png");
	bgSelector->selectIndex(0);
	bgSelector->addEventListener(this, UIEvent::SELECT_EVENT);
	addChild(bgSelector);
	
	creatingFrame = false;
	
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
}

bool SpriteSheetEditor::hasSelectedID(unsigned int frameID) {
	for(int i=0; i < selectedIDs.size(); i++) {
		if(selectedIDs[i] == frameID) {
			return true;
		}
	}
	return false;
}

void SpriteSheetEditor::Update(Number elapsed) {
	std::shared_ptr<Mesh> mesh = frameVisualizerMesh->getMesh();
	std::shared_ptr<Mesh> meshSelected = frameVisualizerMeshSelected->getMesh();
	
	mesh->clearMesh();
	meshSelected->clearMesh();
	
	MeshGeometry geometry;
	MeshGeometry geometrySelected;
	
	geometry.meshType = MeshGeometry::LINE_MESH;
	geometrySelected.meshType = MeshGeometry::LINE_MESH;
	
	geometry.indexedMesh = true;
	geometrySelected.indexedMesh = true;
	
	unsigned int offsetSelected = 0;
	unsigned int offset = 0;
	
	for(int i=0; i < sprite->getNumFrames(); i++){
		SpriteFrame frame = sprite->getSpriteFrame(i);
		
		geometry.addVertexWithUV(frame.coordinates.x, -frame.coordinates.y, 0.0, frame.coordinates.x, frame.coordinates.y);
		geometry.addVertexWithUV(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y);
		geometry.addVertexWithUV(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y + frame.coordinates.h);
		geometry.addVertexWithUV(frame.coordinates.x, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x, frame.coordinates.y + frame.coordinates.h);
		geometry.addIndexedFace(offset+0,offset+1);
		geometry.addIndexedFace(offset+1,offset+2);
		geometry.addIndexedFace(offset+2,offset+3);
		geometry.addIndexedFace(offset+3,offset+0);
		offset += 4;
		
		if(hasSelectedID(frame.frameID)) {
			geometrySelected.addVertexWithUV(frame.coordinates.x, -frame.coordinates.y, 0.0, frame.coordinates.x, frame.coordinates.y);
			geometrySelected.addVertexWithUV(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y);
			geometrySelected.addVertexWithUV(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y + frame.coordinates.h);
			geometrySelected.addVertexWithUV(frame.coordinates.x, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x, frame.coordinates.y + frame.coordinates.h);
			geometrySelected.addIndexedFace(offsetSelected+0,offsetSelected+1);
			geometrySelected.addIndexedFace(offsetSelected+1,offsetSelected+2);
			geometrySelected.addIndexedFace(offsetSelected+2,offsetSelected+3);
			geometrySelected.addIndexedFace(offsetSelected+3,offsetSelected+0);
			offsetSelected += 4;
		}
		
	}
	
	if(creatingFrame) {
	 
		SpriteFrame frame = frameToAdd;
		
		geometry.addVertexWithUV(frame.coordinates.x, -frame.coordinates.y, 0.0, frame.coordinates.x, frame.coordinates.y);
		geometry.addVertexWithUV(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y);
		geometry.addVertexWithUV(frame.coordinates.x+frame.coordinates.w, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y + frame.coordinates.h);
		geometry.addVertexWithUV(frame.coordinates.x, -frame.coordinates.y - frame.coordinates.h, 0.0, frame.coordinates.x, frame.coordinates.y + frame.coordinates.h);
		geometry.addIndexedFace(offset+0,offset+1);
		geometry.addIndexedFace(offset+1,offset+2);
		geometry.addIndexedFace(offset+2,offset+3);
		geometry.addIndexedFace(offset+3,offset+0);
		offset += 4;
	}
	
	mesh->addSubmesh(geometry);
	meshSelected->addSubmesh(geometrySelected);
}

void SpriteSheetEditor::handleEvent(Event *event) {
	if(event->getDispatcher() == changeImageButton) {
		globalFrame->assetBrowser->addEventListener(this, UIEvent::OK_EVENT);
		std::vector<String> extensions;
		extensions.push_back("png");
		extensions.push_back("hdr");
		extensions.push_back("jpg");
		extensions.push_back("psd");
		extensions.push_back("tga");
		globalFrame->showAssetBrowser(extensions);
	} else if(event->getDispatcher() == generateFramesButton) {
		
		PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
		for(int i=0; i < sprite->getNumFrames(); i++) {
			beforeData->spriteFrames.push_back(sprite->getSpriteFrame(i));
		}
		
		if(generateTypeDropdown->getSelectedIndex() == 0) {
			int numX = floor(sprite->getTexture()->getWidth() / uniformGridWidthInput->getText().toNumber());
			int numY = floor(sprite->getTexture()->getHeight() / uniformGridHeightInput->getText().toNumber());
			sprite->createGridFrames(numX, numY, defaultAnchors[defaultAnchorCombo->getSelectedIndex()]);
		} else {
			sprite->createFramesFromIslands(minimumDistanceInput->getText().toInteger(), defaultAnchors[defaultAnchorCombo->getSelectedIndex()]);
		}
		
		PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
		for(int i=0; i < sprite->getNumFrames(); i++) {
			data->spriteFrames.push_back(sprite->getSpriteFrame(i));
		}
		data->reverse = false;
		editor->didAction("changed_frames", beforeData, data);
		
		dispatchEvent(new Event(),Event::CHANGE_EVENT);
	} else if(event->getDispatcher() == bgSelector) {
		Texture::clampDefault = false;
		switch(bgSelector->getSelectedIndex()) {
			case 0:
				previewBg->loadTexture("main/grid_dark.png");
				break;
			case 1:
				previewBg->loadTexture("main/grid_light.png");
				break;
		}
	} else if(event->getDispatcher() == generateTypeDropdown) {
		if(generateTypeDropdown->getSelectedIndex() == 0) {
			uniformOptions->visible = true;
			uniformOptions->enabled = true;
			detectOptions->visible = false;
			detectOptions->enabled = false;
		} else {
			uniformOptions->visible = false;
			uniformOptions->enabled = false;
			detectOptions->visible = true;
			detectOptions->enabled = true;
		}
	} else if(event->getDispatcher() == clearFramesButton) {
		
		PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
		for(int i=0; i < sprite->getNumFrames(); i++) {
			beforeData->spriteFrames.push_back(sprite->getSpriteFrame(i));
		}
		
		sprite->clearFrames();
		
		PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
		for(int i=0; i < sprite->getNumFrames(); i++) {
			data->spriteFrames.push_back(sprite->getSpriteFrame(i));
		}
		data->reverse = false;
		editor->didAction("changed_frames", beforeData, data);
		
		dispatchEvent(new Event(),Event::CHANGE_EVENT);
	} else if(event->getDispatcher() == generateOptionsButton) {
		optionsWindow->visible = !optionsWindow->visible;
		optionsWindow->enabled = !optionsWindow->enabled;
	} else if(event->getDispatcher() == globalFrame->assetBrowser) {
		String newImagePath = globalFrame->assetBrowser->getSelectedAssetPath();
		
		PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
		beforeData->name = sprite->getTexture()->getResourcePath();
		
		PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
		data->name = globalFrame->assetBrowser->getSelectedAssetPath();
		data->reverse = false;
		editor->didAction("changed_image", beforeData, data);
		
		sprite->setTexture(resourcePool->loadTexture(globalFrame->assetBrowser->getSelectedAssetPath()));
		previewImage->setTexture(sprite->getTexture());
		
		globalFrame->assetBrowser->removeAllHandlersForListener(this);
		globalFrame->hideModal();
		
		Resize(getWidth(), getHeight());
	  
	} else if(event->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*) event;
		
		switch(inputEvent->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
			{
				switch(inputEvent->getKey()) {
					case Polycode::KEY_BACKSPACE:
					case Polycode::KEY_DELETE:
						if(previewBg->hasFocus) {
							deleteSelectedFrames();
						}
					break;
				}
			}
			break;
		}
	} else if(event->getDispatcher() == transformGrips) {
		if(sprite->getNumFrames() > 0 && selectedIDs.size() > 0) {


			SpriteFrame frame = sprite->getSpriteFrameByID(selectedIDs[selectedIDs.size()-1]);

			Polycode::Rectangle gripRect = transformGrips->getGripRectangle();
		
			frame.coordinates.x = ((gripRect.x-previewImage->getPosition().x) / previewImage->getWidth() / zoomScale);
			frame.coordinates.y = ((gripRect.y-previewImage->getPosition().y) / previewImage->getHeight() / zoomScale);
			
			
			frame.coordinates.w = gripRect.w / previewImage->getWidth() / zoomScale;
			frame.coordinates.h = gripRect.h / previewImage->getHeight() / zoomScale;
			
			frame.anchorPoint = transformGrips->getAnchorPoint();
			
			PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
			for(int i=0; i < sprite->getNumFrames(); i++) {
				beforeData->spriteFrames.push_back(sprite->getSpriteFrame(i));
			}
			
			sprite->setSpriteFrame(frame);
			
			PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
			for(int i=0; i < sprite->getNumFrames(); i++) {
				data->spriteFrames.push_back(sprite->getSpriteFrame(i));
			}
			data->reverse = false;
			editor->didAction("changed_frames", beforeData, data);

			
			dispatchEvent(new Event(),Event::CHANGE_EVENT);
		}
	} else if(event->getDispatcher() == previewBg) {
		
		InputEvent *inputEvent = (InputEvent*) event;
		
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEWHEEL_UP:
				zoomScale *= 1.02;
				Resize(getWidth(), getHeight());
			break;
			case InputEvent::EVENT_MOUSEWHEEL_DOWN:
				zoomScale *= 0.98;
				if(zoomScale < 0.1) {
					zoomScale = 0.1;
				}
				Resize(getWidth(), getHeight());
			break;
			case InputEvent::EVENT_MOUSEDOWN:
				
				willCreateFrame = true;
				previewBg->focusSelf();
				
				if(core->getInput()->getKeyState(KEY_LALT)) {
					panning = true;
					panMouseBase = core->getInput()->getMousePosition();
				} else {
					
					if(!core->getInput()->getKeyState(KEY_LSHIFT) &&
					   !core->getInput()->getKeyState(KEY_LSHIFT)) {
						clearSelected();
					}
					
					// check hit detection on frames
					Vector2 mouseCoord = core->getInput()->getMousePosition();
					clickBaseCoord = mouseCoord;
					
					for(int i=0; i < sprite->getNumFrames(); i++) {
						SpriteFrame frame = sprite->getSpriteFrame(i);
						
						Polycode::Rectangle transforedCoords;
						
						Vector2 corner = previewImage->getScreenPositionForMainCamera();
						
						transforedCoords.x = corner.x + (frame.coordinates.x * zoomScale * previewImage->getWidth()) ;
						transforedCoords.y = corner.y + (frame.coordinates.y * zoomScale * previewImage->getHeight());
						transforedCoords.w = frame.coordinates.w * zoomScale * previewImage->getWidth();
						transforedCoords.h = frame.coordinates.h * zoomScale  * previewImage->getHeight();

						if(mouseCoord.x >= transforedCoords.x && mouseCoord.x <= transforedCoords.x + transforedCoords.w && mouseCoord.y >= transforedCoords.y && mouseCoord.y <= transforedCoords.y + transforedCoords.h) {
							if(!hasSelectedID(frame.frameID)) {
								selectedIDs.push_back(frame.frameID);
								willCreateFrame = false;
							} else {
								
								if(core->getInput()->getKeyState(KEY_LSHIFT) ||
								   core->getInput()->getKeyState(KEY_LSHIFT)) {
									for(int f=0; f < selectedIDs.size(); f++) {
										if(selectedIDs[f] == frame.frameID)
										{
											selectedIDs.erase(selectedIDs.begin() + f);
											break;
										}}
								}
							}
							break;
						}
					}
				}
			break;
			case InputEvent::EVENT_MOUSEMOVE:
				if(panning) {
					panOffset += core->getInput()->getMousePosition() - panMouseBase;
					panMouseBase = core->getInput()->getMousePosition();
					Resize(getWidth(), getHeight());
				} else {
					CoreInput *input = core->getInput();
					
					if(input->getMouseButtonState(CoreInput::MOUSE_BUTTON1) && willCreateFrame) {
						if(clickBaseCoord.distance(input->getMousePosition()) > 2.0) {
							Vector2 screenCoordinates = previewImage->getScreenPositionForMainCamera();
							screenCoordinates = clickBaseCoord - screenCoordinates;
							
							screenCoordinates.x = screenCoordinates.x / previewImage->getWidth() / zoomScale;
							screenCoordinates.y = screenCoordinates.y / previewImage->getHeight() / zoomScale;
							
							
							Vector2 screenCoordinates2 = previewImage->getScreenPositionForMainCamera();
							screenCoordinates2 = input->getMousePosition() - screenCoordinates2;
							
							screenCoordinates2.x = screenCoordinates2.x / previewImage->getWidth() / zoomScale;
							screenCoordinates2.y = screenCoordinates2.y / previewImage->getHeight() / zoomScale;
							
							frameToAdd.coordinates.x = screenCoordinates.x;
							frameToAdd.coordinates.y = screenCoordinates.y;
							
							frameToAdd.coordinates.w = screenCoordinates2.x - screenCoordinates.x;
							frameToAdd.coordinates.h = screenCoordinates2.y - screenCoordinates.y;
							
							creatingFrame = true;
							
						}
					}
				}
			break;
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:
				panning = false;
				willCreateFrame = false;
				
				if(creatingFrame) {
					if(fabs(frameToAdd.coordinates.w) > 0.001 & fabs(frameToAdd.coordinates.h) > 0.001) {
						
						if(frameToAdd.coordinates.w < 0.0) {
							frameToAdd.coordinates.x = frameToAdd.coordinates.x + frameToAdd.coordinates.w;
							frameToAdd.coordinates.w *= -1.0;
						}

						if(frameToAdd.coordinates.h < 0.0) {
							frameToAdd.coordinates.y = frameToAdd.coordinates.y + frameToAdd.coordinates.h;
							frameToAdd.coordinates.h *= -1.0;
						}
						
						
						PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
						for(int i=0; i < sprite->getNumFrames(); i++) {
							beforeData->spriteFrames.push_back(sprite->getSpriteFrame(i));
						}
						
						sprite->addSpriteFrame(frameToAdd);
						
						
						PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
						for(int i=0; i < sprite->getNumFrames(); i++) {
							data->spriteFrames.push_back(sprite->getSpriteFrame(i));
						}
						data->reverse = false;
						editor->didAction("changed_frames", beforeData, data);
						
					}
				}
				creatingFrame = false;
			break;
		}
	}
}

void SpriteSheetEditor::selectAll() {
	if(previewBg->hasFocus) {
		clearSelected();
		for(int i=0; i < sprite->getNumFrames(); i++) {
			SpriteFrame frame = sprite->getSpriteFrame(i);
			selectedIDs.push_back(frame.frameID);
		}
	}
}

void SpriteSheetEditor::deleteSelectedFrames() {
 
	PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
	for(int i=0; i < sprite->getNumFrames(); i++) {
		beforeData->spriteFrames.push_back(sprite->getSpriteFrame(i));
	}
	
	for(int i=0; i < selectedIDs.size(); i++) {
		sprite->removeFrameByID(selectedIDs[i]);
	}
	clearSelected();
	
	PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
	for(int i=0; i < sprite->getNumFrames(); i++) {
		data->spriteFrames.push_back(sprite->getSpriteFrame(i));
	}
	data->reverse = false;
	editor->didAction("changed_frames", beforeData, data);
	
}

void SpriteSheetEditor::clearSelected() {
	selectedIDs.clear();
}

SpriteSheetEditor::~SpriteSheetEditor() {
	core->getInput()->removeAllHandlersForListener(this);
}

std::vector<unsigned int> SpriteSheetEditor::getSelectedFrameIDs() {
	return selectedIDs;
}

void SpriteSheetEditor::Resize(Number width, Number height) {
	
	headerBg->Resize(width, 30.0);
	
	previewBg->setPosition(0.0, 30.0);
	previewBg->Resize(width, height-60.0);
	previewBg->setImageCoordinates(0, 0, width, height-60);
	
	Vector2 screenPosition = getScreenPositionForMainCamera();
	scissorBox.setRect(screenPosition.x, screenPosition.y, width, height);
	
	
	Number imageAspectRatio = ((Number)previewImage->getTexture()->getHeight()) / ((Number)previewImage->getTexture()->getWidth());
	
	Number imageWidth = (height-60.0) / imageAspectRatio;
	Number imageHeight = height-60.0;
	
	if(imageWidth > width) {
		imageWidth = width;
		imageHeight = width * imageAspectRatio;
	}
	
	previewImage->Resize(imageWidth, imageHeight);
	previewImage->setScale(zoomScale, zoomScale, 1.0);
	
	previewImage->setPosition((width-(previewImage->getWidth()*zoomScale))/ 2.0, 30.0+(height-(previewImage->getHeight()*zoomScale)-60.0)/2.0);
	
	previewImage->Translate(panOffset.x, panOffset.y, 0.0);
	
	frameVisualizerMesh->setPosition(previewImage->getPosition());
	frameVisualizerMesh->setScale(previewImage->getWidth() * zoomScale, previewImage->getHeight() * zoomScale, 1.0);

	frameVisualizerMeshSelected->setPosition(previewImage->getPosition());
	frameVisualizerMeshSelected->setScale(previewImage->getWidth() * zoomScale, previewImage->getHeight() * zoomScale, 1.0);
	
	bottomMenuRect->Resize(width, 31.0);
	bottomMenu->setPosition(0.0, height-30.0);
	
	optionsWindow->setPosition(width-optionsWindow->getWidth()-10.0, height-optionsWindow->getHeight()-40.0);
	
	bgSelector->setPosition(width - bgSelector->getWidth()-3.0, 3.0);
	
	UIElement::Resize(width, height);
}

void SpriteSheetEditor::Render(GPUDrawBuffer *buffer) {
	
	
	if(sprite->getNumFrames() > 0 && selectedIDs.size() == 1) {
		
		transformGrips->visible = true;
		transformGrips->enabled = true;
		
		SpriteFrame frame = sprite->getSpriteFrameByID(selectedIDs[selectedIDs.size()-1]);
		
		Vector2 gripsPosition = Vector2(
										previewImage->getPosition().x + (frame.coordinates.x * (previewImage->getWidth()*zoomScale)),
										previewImage->getPosition().y + (frame.coordinates.y * (previewImage->getHeight() *zoomScale))
										);
		
		Polycode::Rectangle gripRect;

		gripRect.x = previewImage->getPosition().x + (frame.coordinates.x * previewImage->getWidth() * zoomScale);
		gripRect.y = previewImage->getPosition().y + (frame.coordinates.y * previewImage->getHeight() * zoomScale);
		gripRect.w = frame.coordinates.w * previewImage->getWidth() * zoomScale;
		gripRect.h = frame.coordinates.h * previewImage->getHeight() * zoomScale;
		
		transformGrips->setGripRectangle(gripRect, frame.anchorPoint);
	} else {
		transformGrips->visible = false;
		transformGrips->enabled = false;
	}
}

SpriteBrowser::SpriteBrowser(Core *core, ResourcePool *pool, SpriteSet *spriteSet) : UIElement (core) {
	this->spriteSet = spriteSet;
	
	headerBg = new UIRect(core, pool, 10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	UILabel *label = new UILabel(core, pool, "SPRITES", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	
	addChild(label);
	label->setPosition(10, 3);
	
	
	newSpriteButton = new UIImageButton(core, pool, "spriteEditor/button_add.png", 1.0, 24, 24);
	addChild(newSpriteButton);
	newSpriteButton->addEventListener(this, UIEvent::CLICK_EVENT);

	removeSpriteButton = new UIImageButton(core, pool, "spriteEditor/button_remove.png", 1.0, 24, 24);
	addChild(removeSpriteButton);
	removeSpriteButton->addEventListener(this, UIEvent::CLICK_EVENT);

	moreButton = new UIImageButton(core, pool, "spriteEditor/button_more.png", 1.0, 24, 24);
	addChild(moreButton);
	moreButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	
	spriteTreeView = new UITreeContainer(core, pool, "boxIcon.png", "All Sprites", 10, 10);
	spriteTreeView->setPosition(0, 30);
	addChild(spriteTreeView);
	
	spriteTreeView->getRootNode()->toggleCollapsed();
	spriteTreeView->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
}

void SpriteBrowser::handleEvent(Event *event) {
	if(event->getDispatcher() == newSpriteButton) {
		globalFrame->textInputPopup->action = "newSprite";
		globalFrame->textInputPopup->setCaption("New sprite name");
		globalFrame->textInputPopup->setValue("New Sprite");
		globalFrame->showModal(globalFrame->textInputPopup);
		globalFrame->textInputPopup->addEventListener(this, UIEvent::OK_EVENT);
	} else if(event->getDispatcher() == globalFrame->textInputPopup) {
		if(event->getEventCode() == UIEvent::OK_EVENT) {
			if(globalFrame->textInputPopup->action == "newSprite") {
				
				std::shared_ptr<Sprite> newEntry = std::make_shared<Sprite>(globalFrame->textInputPopup->getValue());
				
				SpriteState *defaultState = new SpriteState(spriteSet, "default");
				newEntry->addSpriteState(defaultState);
				
				spriteSet->addSpriteEntry(newEntry);
				selectedEntry = newEntry;
				refreshSprites();

				PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
				beforeData->sprite = newEntry;
				
				PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
				data->sprite = newEntry;
				data->reverse = false;
				editor->didAction("new_sprite", beforeData, data);
				
			} else if(globalFrame->textInputPopup->action == "renameSprite") {
				
				PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
				beforeData->sprite = selectedEntry;
				beforeData->name = selectedEntry->getName();
				
				selectedEntry->setName(globalFrame->textInputPopup->getValue());
				
				PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
				data->sprite = selectedEntry;
				data->reverse = false;
				data->name = selectedEntry->getName();
				editor->didAction("rename_sprite", beforeData, data);
				
				refreshSprites();
			}
			globalFrame->textInputPopup->removeAllHandlersForListener(this);
		}
	} else if(event->getDispatcher() == globalFrame->yesNoPopup) {
		if(event->getEventCode() == UIEvent::OK_EVENT) {
			if(globalFrame->yesNoPopup->action == "removeSprite") {
				if(selectedEntry) {
					spriteSet->removeSprite(selectedEntry);
					
					PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
					beforeData->sprite = selectedEntry;
					
					PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
					data->sprite = selectedEntry;
					data->reverse = false;
					editor->didAction("remove_sprite", beforeData, data);

					selectedEntry = NULL;
					refreshSprites();
					dispatchEvent(new Event(), Event::CHANGE_EVENT);
				}
			}
		}
		globalFrame->yesNoPopup->removeAllHandlersForListener(this);
	} else if(event->getDispatcher() == removeSpriteButton) {
		if(selectedEntry) {
			globalFrame->yesNoPopup->setCaption("Are you sure you want to remove sprite \""+selectedEntry->getName()+"\"?");
			globalFrame->yesNoPopup->action = "removeSprite";
			globalFrame->yesNoPopup->addEventListener(this, UIEvent::OK_EVENT);
			globalFrame->showModal(globalFrame->yesNoPopup);

		}
	} else if(event->getDispatcher() == moreButton) {
		spriteMoreMenu = globalMenu->showMenuAtMouse(100.0);
		spriteMoreMenu->addOption("Rename", "rename");
		spriteMoreMenu->fitToScreenVertical();
		spriteMoreMenu->addEventListener(this, UIEvent::OK_EVENT);
	} else if(event->getDispatcher() == spriteMoreMenu) {
		if(selectedEntry) {
			if(spriteMoreMenu->getSelectedItem()->getMenuItemID() == "rename") {
				globalFrame->textInputPopup->action = "renameSprite";
				globalFrame->textInputPopup->setCaption("New sprite name");
				globalFrame->textInputPopup->setValue(selectedEntry->getName());
				globalFrame->textInputPopup->addEventListener(this, UIEvent::OK_EVENT);
				globalFrame->showModal(globalFrame->textInputPopup);
			}
		}
	} else if(event->getDispatcher() == spriteTreeView->getRootNode()) {
		selectedEntry = std::static_pointer_cast<Sprite>(spriteTreeView->getRootNode()->getSelectedNode()->getSharedUserData());
		if(selectedEntry) {
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
}

std::shared_ptr<Sprite> SpriteBrowser::getSelectedSpriteEntry() {
	return selectedEntry;
}

void SpriteBrowser::refreshSprites() {
	spriteTreeView->getRootNode()->clearTree();
	for(int i=0; i < spriteSet->getNumSpriteEntries(); i++) {
		std::shared_ptr<Sprite> spriteEntry = spriteSet->getSpriteEntry(i);
		UITree *treeNode = spriteTreeView->getRootNode()->addTreeChildShared("treeIcons/sprite.png", spriteEntry->getName(), spriteEntry);
		if(spriteEntry == selectedEntry) {
			treeNode->setSelected();
		}
	}
}

SpriteBrowser::~SpriteBrowser() {
	globalFrame->textInputPopup->removeAllHandlersForListener(this);
	globalFrame->yesNoPopup->removeAllHandlersForListener(this);
}

void SpriteBrowser::Resize(Number width, Number height) {
	headerBg->Resize(width, 30.0);

	moreButton->setPosition(width - 30.0, 3.0);
	removeSpriteButton->setPosition(width - 56.0, 3.0);
	newSpriteButton->setPosition(width - 82.0, 3.0);
	
	spriteTreeView->Resize(width, height-30);
}

SpriteStateEditorDetails::SpriteStateEditorDetails(Core *core, ResourcePool *pool, SpriteSet *spriteSet) : UIElement(core) {
	
	this->spriteSet = spriteSet;
	
	headerBg = new UIRect(core, pool, 10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	UILabel *label = new UILabel(core, pool, "STATE DETAILS", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(10, 3);
	
	editBar = new SpriteStateEditBar(core, pool, spriteSet);
	addChild(editBar);
	editBar->setPosition(140.0, 80.0);
	
	playButton = new UIImageButton(core, pool, "spriteEditor/play_button.png", 1.0, 32, 32);
	addChild(playButton);
	playButton->setPosition(140.0, 35.0);
	playButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	pauseButton = new UIImageButton(core, pool, "spriteEditor/pause_button.png", 1.0, 32, 32);
	addChild(pauseButton);
	pauseButton->setPosition(140.0, 35.0);
	pauseButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	appendFramesButton = new UIButton(core, pool, "Append", 80.0);
	addChild(appendFramesButton);
	appendFramesButton->setPosition(180.0, 40.0);
	appendFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);

	removeFramesButton = new UIButton(core, pool, "Remove", 80.0);
	addChild(removeFramesButton);
	removeFramesButton->setPosition(180.0 + 80.0 + 5.0, 40.0);
	removeFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	clearFramesButton = new UIButton(core, pool, "Clear", 80.0);
	addChild(clearFramesButton);
	clearFramesButton->setPosition(180.0 + 160.0 + 10.0, 40.0);
	clearFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	UIImage *divider = new UIImage(core, pool, "spriteEditor/divider.png", 4, 128);
	addChild(divider);
	divider->setPosition(132.0, 30.0);
	divider->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	label = new UILabel(core, pool, "FPS", 18, "section", Label::ANTIALIAS_FULL);
	label->setPosition(60.0-label->getWidth(), 40.0);
	addChild(label);
	
	fpsInput = new UITextInput(core, pool, false, 50.0, 12.0);
	addFocusChild(fpsInput);
	fpsInput->setPosition(65.0, 40.0);
	fpsInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	label = new UILabel(core, pool, "PPU", 18, "section", Label::ANTIALIAS_FULL);
	label->setPosition(60.0-label->getWidth(), 65.0);
	addChild(label);
	
	scaleInput = new UITextInput(core, pool, false, 50.0, 12.0);
	addFocusChild(scaleInput);
	scaleInput->setPosition(65.0, 65.0);
	scaleInput->addEventListener(this, UIEvent::CHANGE_EVENT);

	label = new UILabel(core, pool, "WIDTH", 18, "section", Label::ANTIALIAS_FULL);
	label->setPosition(60.0-label->getWidth(), 90.0);
	addChild(label);
	
	bBoxWidthInput = new UITextInput(core, pool, false, 50.0, 12.0);
	addFocusChild(bBoxWidthInput);
	bBoxWidthInput->setPosition(65.0, 90.0);
	bBoxWidthInput->addEventListener(this, UIEvent::CHANGE_EVENT);

	label = new UILabel(core, pool, "HEIGHT", 18, "section", Label::ANTIALIAS_FULL);
	label->setPosition(60.0-label->getWidth(), 115.0);
	addChild(label);
	
	bBoxHeightInput = new UITextInput(core, pool, false, 50.0, 12.0);
	addFocusChild(bBoxHeightInput);
	bBoxHeightInput->setPosition(65.0, 115.0);
	bBoxHeightInput->addEventListener(this, UIEvent::CHANGE_EVENT);

	label = new UILabel(core, pool, "X OFF", 18, "section", Label::ANTIALIAS_FULL);
	label->setPosition(60.0-label->getWidth(), 140.0);
	addChild(label);
	
	offsetXInput = new UITextInput(core, pool, false, 50.0, 12.0);
	addFocusChild(offsetXInput);
	offsetXInput->setPosition(65.0, 140.0);
	offsetXInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	label = new UILabel(core, pool, "Y OFF", 18, "section", Label::ANTIALIAS_FULL);
	label->setPosition(60.0-label->getWidth(), 165.0);
	addChild(label);
	
	offsetYInput = new UITextInput(core, pool, false, 50.0, 12.0);
	addFocusChild(offsetYInput);
	offsetYInput->setPosition(65.0, 165.0);
	offsetYInput->addEventListener(this, UIEvent::CHANGE_EVENT);
	
	visible = false;
	enabled = false;
}

void SpriteStateEditBar::setSceneSprite(SceneSprite *sprite) {
	sceneSprite = sprite;
}

SpriteStateEditBar *SpriteStateEditorDetails::getEditBar() {
	return editBar;
}

void SpriteStateEditorDetails::setSceneSprite(SceneSprite *sceneSprite) {
	this->sceneSprite = sceneSprite;
	editBar->setSceneSprite(sceneSprite);
}

void SpriteStateEditorDetails::Update(Number elapsed) {
	if(sceneSprite) {
		if(sceneSprite->isPaused()) {
			playButton->visible = true;
			playButton->enabled = true;
			pauseButton->visible = false;
			pauseButton->enabled = false;
		} else {
			playButton->visible = false;
			playButton->enabled = false;
			pauseButton->visible = true;
			pauseButton->enabled = true;
		}
	}
}

void SpriteStateEditorDetails::setSpriteState(SpriteState *state) {
	if(!state) {
		visible = false;
		enabled = false;
		editBar->setSpriteState(state);
		return;
	}
	visible = true;
	enabled = true;
	spriteState = state;
	editBar->setSpriteState(state);
	refreshState();
}

PolycodeSpriteEditorActionData *SpriteStateEditorDetails::makeStateData() {
	PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
	data->stateFPS = spriteState->getStateFPS();
	data->stateScale = spriteState->getPixelsPerUnit();
	data->stateBBox = spriteState->getBoundingBox();
	data->stateOffset = spriteState->getSpriteOffset();
	data->state = spriteState;
	return data;
}

void SpriteStateEditorDetails::handleEvent(Event *event) {
	if(event->getDispatcher() == fpsInput) {
		PolycodeSpriteEditorActionData *beforeData = makeStateData();
		spriteState->setStateFPS(fpsInput->getText().toNumber());
		PolycodeSpriteEditorActionData *data = makeStateData();
		editor->didAction("changed_state_info", beforeData, data);
	} else if(event->getDispatcher() == scaleInput) {
		PolycodeSpriteEditorActionData *beforeData = makeStateData();
		spriteState->setPixelsPerUnit(scaleInput->getText().toNumber());
		PolycodeSpriteEditorActionData *data = makeStateData();
		editor->didAction("changed_state_info", beforeData, data);
	} else if(event->getDispatcher() == bBoxWidthInput) {
		PolycodeSpriteEditorActionData *beforeData = makeStateData();
		Vector2 bBox = spriteState->getBoundingBox();
		spriteState->setBoundingBox(Vector2(bBoxWidthInput->getText().toNumber(), bBox.y));
		PolycodeSpriteEditorActionData *data = makeStateData();
		editor->didAction("changed_state_info", beforeData, data);
	} else if(event->getDispatcher() == bBoxHeightInput) {
		PolycodeSpriteEditorActionData *beforeData = makeStateData();
		Vector2 bBox = spriteState->getBoundingBox();
		spriteState->setBoundingBox(Vector2(bBox.x, bBoxHeightInput->getText().toNumber()));
		PolycodeSpriteEditorActionData *data = makeStateData();
		editor->didAction("changed_state_info", beforeData, data);
	} else if(event->getDispatcher() == offsetXInput) {
		PolycodeSpriteEditorActionData *beforeData = makeStateData();
		Vector2 offset = spriteState->getSpriteOffset();
		spriteState->setSpriteOffset(Vector2(offsetXInput->getText().toNumber(), offset.y));
		PolycodeSpriteEditorActionData *data = makeStateData();
		editor->didAction("changed_state_info", beforeData, data);
	} else if(event->getDispatcher() == offsetYInput) {
		PolycodeSpriteEditorActionData *beforeData = makeStateData();
		Vector2 offset = spriteState->getSpriteOffset();
		spriteState->setSpriteOffset(Vector2(offset.x, offsetYInput->getText().toNumber()));
		PolycodeSpriteEditorActionData *data = makeStateData();
		editor->didAction("changed_state_info", beforeData, data);
	} else if(event->getDispatcher() == playButton) {
		sceneSprite->setPaused(false);
	}  else if(event->getDispatcher() == pauseButton) {
		sceneSprite->setPaused(true);
	} else if(event->getDispatcher() == clearFramesButton) {
		
		PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
		for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
			beforeData->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
		}
		
		spriteState->clearFrames();
		
		PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
		for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
			data->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
		}
		data->reverse = false;
		editor->didAction("changed_sprite_set_frames", beforeData, data);
		
	} else if(event->getDispatcher() == removeFramesButton) {
		
		PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
		for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
			beforeData->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
		}
		
		editBar->deleteSelectedFrames();
		
		PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
		for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
			data->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
		}
		data->reverse = false;
		editor->didAction("changed_sprite_set_frames", beforeData, data);
	
	}
}

SpriteStateEditorDetails::~SpriteStateEditorDetails() {
	
}

UIButton *SpriteStateEditorDetails::getAppendFramesButton() {
	return appendFramesButton;
}

SpriteState *SpriteStateEditorDetails::getSpriteState() {
	return spriteState;
}

void SpriteStateEditorDetails::refreshState() {
	editBar->refreshBar();
	fpsInput->setText(String::NumberToString(spriteState->getStateFPS()));
	scaleInput->setText(String::NumberToString(spriteState->getPixelsPerUnit()));
	bBoxWidthInput->setText(String::NumberToString(spriteState->getBoundingBox().x));
	bBoxHeightInput->setText(String::NumberToString(spriteState->getBoundingBox().y));
	
	offsetXInput->setText(String::NumberToString(spriteState->getSpriteOffset().x));
	offsetYInput->setText(String::NumberToString(spriteState->getSpriteOffset().y));
	
}

void SpriteStateEditorDetails::Resize(Number width, Number height) {
	headerBg->Resize(width, 30.0);
	editBar->Resize(width-110.0, height-90.0);
}

void SpriteStateEditBar::clearBar() {
	
}

void SpriteStateEditBar::setSpriteState(SpriteState *state) {
	spriteState = state;
	if(state) {
		state->rebuildStateMeshes();
		refreshBar();
	}
	
}

void SpriteStateEditBar::refreshBar() {
	
	if(!spriteSet || !spriteState || !sceneSprite) {
		return;
	}
	
	barMesh->getShaderPass(0).shaderBinding->setTextureForParam("diffuse", spriteSet->getTexture());
	
	std::shared_ptr<Mesh> mesh = barMesh->getMesh();
	mesh->clearMesh();
	MeshGeometry meshGeometry;
	
	std::shared_ptr<Mesh> meshBg = barMeshBg->getMesh();
	meshBg->clearMesh();
	MeshGeometry meshBgGeometry;
	
	std::shared_ptr<Mesh> meshTicks = frameTicksMesh->getMesh();
	meshTicks->clearMesh();
	MeshGeometry meshTicksGeometry;
	
	std::shared_ptr<Mesh> meshGrips = frameGripsMesh->getMesh();
	meshGrips->clearMesh();
	MeshGeometry meshGripsGeometry;
	
	Number frameOffset = 0;
	Number frameSize = 0;
	
	unsigned int offset = 0;
	unsigned int offsetIcon = 0;
	unsigned int offsetGrip = 0;
	
	for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
		unsigned int frameID = spriteState->getFrameIDAtIndex(i);
	 
		SpriteFrame frame = spriteSet->getSpriteFrameByID(frameID);
		
		
		Number gapSize = 1.0;
		Number frameGapSize = 1.0;
		
		Number frameTickHeight = 10.0;
		Number frameTickGap = 2.0;
		
		bool drawGrip = true;
		bool drawIcon = true;
		
		frameSize = defaultFrameWidth * zoomScale;
		Number frameHeight = getHeight()-frameTickHeight-frameTickGap-scroller->getHScrollBar()->getHeight();
		
		if(i < spriteState->getNumFrameIDs()-1) {
			if(spriteState->getFrameIDAtIndex(i+1) == frameID) {
				gapSize = 0.0;
				drawGrip = false;
			}
		}
		
		if(i > 0) {
			if(spriteState->getFrameIDAtIndex(i-1) == frameID) {
				drawIcon = false;
			}
		}
		
		if(frameHeight < 32.0) {
			frameHeight = 32.0;
		}
		
		frameOffset = ((Number)i) * frameSize;
		
		// draw frame ticks
		
		Color vertexColor(0.1, 0.1, 0.1, 1.0);
		if(i % 2) {
			vertexColor = Color(0.2, 0.2, 0.2, 1.0);
		}
		
		if(i == sceneSprite->getCurrentFrame()) {
			vertexColor = Color(1.0, 0.8, 0.0, 1.0);
		}
		
		meshTicksGeometry.addVertexWithUV(frameOffset, 0.0, 0.0, 0.0, 0.0);
		meshTicksGeometry.addColor(vertexColor);
		
		meshTicksGeometry.addVertexWithUV(frameOffset, 0.0-frameTickHeight, 0.0, 0.0, 1.0);
		meshTicksGeometry.addColor(vertexColor);
		
		meshTicksGeometry.addVertexWithUV(frameOffset+frameSize-frameGapSize, -frameTickHeight, 0.0, 1.0, 1.0);
		meshTicksGeometry.addColor(vertexColor);
		
		meshTicksGeometry.addVertexWithUV(frameOffset+frameSize-frameGapSize, 0.0, 0.0, 1.0, 0.0);
		meshTicksGeometry.addColor(vertexColor);
		
		meshTicksGeometry.addIndexedFace(offset+0,offset+1, offset+2);
		meshTicksGeometry.addIndexedFace(offset+0,offset+2, offset+3);
		// draw icons
		
		Number imageAspectRatio = ((Number)spriteSet->getTexture()->getWidth()) / ((Number)spriteSet->getTexture()->getHeight());
		Number aspectRatio = frame.coordinates.h / frame.coordinates.w / imageAspectRatio;
		
		Number iconFrameWidth = frameSize * 0.5;
		Number iconFrameHeight = iconFrameWidth * aspectRatio;
		
		if(iconFrameHeight > frameHeight * 0.8) {
			iconFrameHeight = frameHeight * 0.8;
			iconFrameWidth = iconFrameHeight / aspectRatio;
		}
		
		Number iconOffset = 2.0;
		
		if(drawIcon) {
			meshGeometry.addVertexWithUV(frameOffset+iconOffset, -frameTickHeight-frameTickGap-iconOffset, 0.0, frame.coordinates.x, 1.0-frame.coordinates.y);
			meshGeometry.addVertexWithUV(frameOffset+iconOffset, -frameTickHeight-frameTickGap-iconFrameHeight-iconOffset, 0.0, frame.coordinates.x, 1.0-frame.coordinates.y  - frame.coordinates.h);
			meshGeometry.addVertexWithUV(frameOffset+iconFrameWidth+iconOffset, -frameTickHeight-frameTickGap-iconFrameHeight-iconOffset, 0.0, frame.coordinates.x+frame.coordinates.w, 1.0- frame.coordinates.y  - frame.coordinates.h);
			meshGeometry.addVertexWithUV(frameOffset+iconFrameWidth+iconOffset, -frameTickHeight-frameTickGap-iconOffset, 0.0, frame.coordinates.x+frame.coordinates.w, 1.0-frame.coordinates.y);
			
			meshGeometry.addIndexedFace(offsetIcon+0,offsetIcon+1, offsetIcon+2);
			meshGeometry.addIndexedFace(offsetIcon+0,offsetIcon+2, offsetIcon+3);
			offsetIcon += 4;
		}
		
		// draw frame backgrounds
		
		Color bgFrameColor = Color(1.0, 1.0, 1.0, 1.0);
		
		if(isFrameSelected(i)) {
			bgFrameColor = Color(1.0, 0.5, 0.5, 1.0);
		}
		
		meshBgGeometry.addVertexWithUV(frameOffset, -frameTickHeight-frameTickGap, 0.0, 0.0, 0.0);
		meshBgGeometry.addColor(bgFrameColor);
		
		meshBgGeometry.addVertexWithUV(frameOffset, -frameTickHeight-frameTickGap-frameHeight, 0.0, 0.0, 1.0);
		meshBgGeometry.addColor(bgFrameColor);
		
		meshBgGeometry.addVertexWithUV(frameOffset+frameSize-gapSize, -frameTickHeight-frameTickGap-frameHeight, 0.0, 1.0, 1.0);
		meshBgGeometry.addColor(bgFrameColor);
		
		meshBgGeometry.addVertexWithUV(frameOffset+frameSize-gapSize, -frameTickHeight-frameTickGap, 0.0, 1.0, 0.0);
		meshBgGeometry.addColor(bgFrameColor);

		
		meshBgGeometry.addIndexedFace(offset+0, offset+1, offset+2);
		meshBgGeometry.addIndexedFace(offset+0, offset+2, offset+3);
		
		Number gripWidth = 8;
		Number gripHeight = 24;
		
		Number gripOffset = (frameHeight-24.0) / 2.0;
		
		if(drawGrip) {
			meshGripsGeometry.addVertexWithUV(frameOffset+frameSize-gapSize-gripWidth, -frameTickHeight-frameTickGap-gripOffset, 0.0, 0.0, 0.0);
			meshGripsGeometry.addVertexWithUV(frameOffset+frameSize-gapSize-gripWidth, -frameTickHeight-frameTickGap-gripHeight-gripOffset, 0.0, 0.0, 1.0);
			meshGripsGeometry.addVertexWithUV(frameOffset+frameSize-gapSize, -frameTickHeight-frameTickGap-gripHeight-gripOffset, 0.0, 1.0, 1.0);
			meshGripsGeometry.addVertexWithUV(frameOffset+frameSize-gapSize, -frameTickHeight-frameTickGap-gripOffset, 0.0, 1.0, 0.0);
			
			meshGripsGeometry.addIndexedFace(offsetGrip+0, offsetGrip+1, offsetGrip+2);
			meshGripsGeometry.addIndexedFace(offsetGrip+0, offsetGrip+2, offsetGrip+3);
			
			offsetGrip += 4;
		}
		
		offset += 4;
		
	}
	
	meshGeometry.indexedMesh = true;
	meshBgGeometry.indexedMesh = true;
	meshGripsGeometry.indexedMesh = true;
	meshTicksGeometry.indexedMesh = true;
	
	mesh->addSubmesh(meshGeometry);
	meshBg->addSubmesh(meshBgGeometry);
	meshGrips->addSubmesh(meshGripsGeometry);
	meshTicks->addSubmesh(meshTicksGeometry);
	
	scroller->setContentSize(frameOffset+frameSize, getHeight());
}

bool SpriteStateEditBar::isFrameSelected(unsigned int frameIndex) {
	for(int i=0; i < selectedFrames.size(); i++) {
		if(selectedFrames[i] == frameIndex) {
			return true;
		}
	}
	return false;
}

void SpriteStateEditBar::Update(Number elapsed) {
	refreshBar();
}

void SpriteStateEditBar::Resize(Number width, Number height) {
	UIElement::Resize(width, height);
	scroller->Resize(width, height);
	refreshBar();
}

SpriteStateEditBar::SpriteStateEditBar(Core *core, ResourcePool *pool, SpriteSet *spriteSet) : UIElement(core) {
	
	this->spriteSet = spriteSet;
	sceneSprite = NULL;
	spriteState = NULL;
	
	draggingFrames = false;
	extendingFrame = false;
	
	barBase = new UIElement(core);
	
	barMeshBg = new SceneMesh();
	barMeshBg->setMaterial(pool->getMaterial("UnlitVertexColor"));
	barBase->addChild(barMeshBg);
	barMeshBg->getShaderPass(0).shaderBinding->setTextureForParam("diffuse", pool->loadTexture("spriteEditor/sprite_frame_bg.png"));
	barMeshBg->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	
	barMesh = new SceneMesh();
	barMesh->setMaterial(pool->getMaterial("Unlit"));
	barBase->addChild(barMesh);
	barMesh->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	
	frameTicksMesh = new SceneMesh();
	frameTicksMesh->setMaterial(pool->getMaterial("UnlitUntexturedVertexColor"));
	barBase->addChild(frameTicksMesh);
	
	frameGripsMesh = new SceneMesh();
	barBase->addChild(frameGripsMesh);
	frameGripsMesh->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	frameGripsMesh->setMaterial(pool->getMaterial("Unlit"));
	frameGripsMesh->getShaderPass(0).shaderBinding->setTextureForParam("diffuse", pool->loadTexture("spriteEditor/frame_grip.png"));
	
	this->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
	this->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);
	this->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	this->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	this->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	this->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	
	zoomScale = 1.0;
	defaultFrameWidth = 50.0;
	
	scroller = new UIScrollContainer(core, pool, barBase, true, false, 10, 10);
	addChild(scroller);
}

void SpriteStateEditBar::handleEvent(Event *event) {
	if(event->getDispatcher() == this) {
		InputEvent *inputEvent = (InputEvent*) event;
		
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEWHEEL_UP:
				zoomScale *= 1.02;
			break;
			case InputEvent::EVENT_MOUSEWHEEL_DOWN:
				zoomScale *= 0.98;
				if(zoomScale < 0.25) {
					zoomScale = 0.25;
				}
			break;
			case InputEvent::EVENT_MOUSEDOWN:
			{
				
				if(inputEvent->getMousePosition().y < getHeight()-scroller->getHScrollBar()->getHeight()) {						   
					clickBaseCoord = core->getInput()->getMousePosition();
					focusSelf();
					frameMoveBase = core->getInput()->getMousePosition();
					
					
					Number offsetInFrame = fmod(inputEvent->getMousePosition().x - barBase->getPosition().x, defaultFrameWidth * zoomScale);
					
					
					extendingIndex = (inputEvent->getMousePosition().x - barBase->getPosition().x)/ defaultFrameWidth / zoomScale;
					extendingID = spriteState->getFrameIDAtIndex(extendingIndex);
					
					bool willBeExtendingFrame = true;
					
					if(extendingIndex < spriteState->getNumFrameIDs()-1) {
						if(spriteState->getFrameIDAtIndex(extendingIndex+1) == extendingID) {
							willBeExtendingFrame = false;
						}
					}
					
					
					if((defaultFrameWidth * zoomScale) - offsetInFrame < 20.0 && willBeExtendingFrame) {
						
						extendingFrame = true;
						
						while(spriteState->getFrameIDAtIndex(extendingIndex-1) == extendingID && extendingID > 1) {
							extendingIndex--;
						}
					} else {
						unsigned int selectedFrameIndex = (inputEvent->getMousePosition().x - barBase->getPosition().x)/ defaultFrameWidth / zoomScale;
						
						if(!isFrameSelected(selectedFrameIndex)) {
							if(!core->getInput()->getKeyState(KEY_LSHIFT) &&
							   !core->getInput()->getKeyState(KEY_LSHIFT)) {
								selectedFrames.clear();
							}
							doSelectFrame(selectedFrameIndex);
						}
					}
				}

			}
			break;
			case InputEvent::EVENT_MOUSEMOVE:
				
				if(extendingFrame) {
					selectedFrames.clear();
					Number distance = core->getInput()->getMousePosition().x - frameMoveBase.x;
					
					if(fabs(distance) > defaultFrameWidth * zoomScale) {
						if(distance > 0.0) {
							
							PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
							for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
								beforeData->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
							}
							
							spriteState->insertFrame(extendingIndex, extendingID);
							
							PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
							for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
								data->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
							}
							data->reverse = false;
							editor->didAction("changed_sprite_set_frames", beforeData, data);
							
						} else {
							if(extendingIndex < spriteState->getNumFrameIDs()-1) {
								if(spriteState->getFrameIDAtIndex(extendingIndex+1) == extendingID) {
									
									
									PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
									for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
										beforeData->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
									}
									
									spriteState->removeFrameByIndex(extendingIndex+1);
									
									PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
									for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
										data->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
									}
									data->reverse = false;
									editor->didAction("changed_sprite_set_frames", beforeData, data);
									
								}
							}
						}
						frameMoveBase =	 core->getInput()->getMousePosition();
					}
				} else {
					if(core->getInput()->getMousePosition().distance(clickBaseCoord) > 4.0 && core->getInput()->getMouseButtonState(CoreInput::MOUSE_BUTTON1) && inputEvent->getMousePosition().y < getHeight()-scroller->getHScrollBar()->getHeight()) {
						
						draggingFrames = true;
						
						Number distance = core->getInput()->getMousePosition().x - frameMoveBase.x;
						
						if(fabs(distance) > defaultFrameWidth * zoomScale) {
							
							
							PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
							for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
								beforeData->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
							}
							
							if(distance > 0.0) {
								moveSelectedRight();
							} else {
								moveSelectedLeft();
							}
							
							PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
							for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
								data->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
							}
							data->reverse = false;
							editor->didAction("changed_sprite_set_frames", beforeData, data);
							
							frameMoveBase =	 core->getInput()->getMousePosition();
						}
						
					} else {
						draggingFrames = false;
						Number offsetInFrame = fmod(inputEvent->getMousePosition().x - barBase->getPosition().x, defaultFrameWidth * zoomScale);
						if((offsetInFrame / (defaultFrameWidth * zoomScale)) > 0.8) {
							core->setCursor(Core::CURSOR_RESIZE_LEFT_RIGHT);
						} else {
							core->setCursor(Core::CURSOR_ARROW);
						}
						
						extendingIndex = (inputEvent->getMousePosition().x - barBase->getPosition().x)/ defaultFrameWidth / zoomScale;
						extendingID = spriteState->getFrameIDAtIndex(extendingIndex);
						
						if(extendingIndex < spriteState->getNumFrameIDs()-1) {
							if(spriteState->getFrameIDAtIndex(extendingIndex+1) == extendingID) {
								core->setCursor(Core::CURSOR_ARROW);
							}
						}
					}
				}
			break;
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:
				extendingFrame = false;
				
				if(core->getInput()->getMousePosition().distance(clickBaseCoord) < 4.0) {
					if(inputEvent->getMousePosition().y < getHeight()-scroller->getHScrollBar()->getHeight()) {
						unsigned int selectedFrameIndex = (inputEvent->getMousePosition().x - barBase->getPosition().x)/ defaultFrameWidth / zoomScale;
						if(!core->getInput()->getKeyState(KEY_LSHIFT) &&
						   !core->getInput()->getKeyState(KEY_LSHIFT)) {
							selectedFrames.clear();
						}
						doSelectFrame(selectedFrameIndex);
					}
				}
				draggingFrames = false;
			break;
		}
	} else if(event->getDispatcher() == core->getInput()) {
		InputEvent *inputEvent = (InputEvent*) event;
		
		if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
			switch(inputEvent->getKey()) {
				case Polycode::KEY_DELETE:
				case Polycode::KEY_BACKSPACE:
					if(hasFocus) {
						deleteSelectedFrames();
					}
				break;
			}
		}
	}
}

void SpriteStateEditBar::doSelectFrame(unsigned int selectedFrameIndex) {
	unsigned int selectedFrameID = spriteState->getFrameIDAtIndex(selectedFrameIndex);
	
	// select back and front
	int frameIndex = selectedFrameIndex;
	do {
		if(!isFrameSelected(frameIndex)) {
			selectedFrames.push_back(frameIndex);
		}
		frameIndex--;
	} while(spriteState->getFrameIDAtIndex(frameIndex) == selectedFrameID && frameIndex >= 0);
	
	frameIndex = selectedFrameIndex;
	do {
		if(!isFrameSelected(frameIndex)) {
			selectedFrames.push_back(frameIndex);
		}
		frameIndex++;
	} while(spriteState->getFrameIDAtIndex(frameIndex) == selectedFrameID && frameIndex < spriteState->getNumFrameIDs());
	
	
	std::sort(selectedFrames.begin(), selectedFrames.end());
}

void swapElements(const std::vector<unsigned int>& indexes, std::vector<unsigned int>& array){
	for(int j=0; j < indexes.size(); j++){
		unsigned int i = indexes[j];
		if (i < 1 || i >= array.size()){
			continue;
		}
		std::swap(array[i-1], array[i]);
	}
}

void swapElementsRight(const std::vector<unsigned int>& indexes, std::vector<unsigned int>& array){
	for(int j=indexes.size()-1; j >= 0; j--){
		unsigned int i = indexes[j];
		if (i > array.size() - 2){
			continue;
		}
		std::swap(array[i+1], array[i]);
	}
}

void SpriteStateEditBar::moveSelectedLeft() {

	if(spriteState->getNumFrameIDs() < 2) {
		return;
	}
	
	for(int i=0; i < selectedFrames.size();i++) {
		if(selectedFrames[i] == 0) {
			return;
		}
	}
	
	std::vector<unsigned int> newIDS;
	
	for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
		unsigned int frameID = spriteState->getFrameIDAtIndex(i);
		newIDS.push_back(frameID);
	}
	
	swapElements(selectedFrames, newIDS);
	
	for(int i=0; i < selectedFrames.size(); i++) {
		if(selectedFrames[i] > 0) {
			selectedFrames[i]--;
		}
	}
	
	spriteState->setNewFrameIDs(newIDS);
}

void SpriteStateEditBar::moveSelectedRight() {
	if(spriteState->getNumFrameIDs() < 2) {
		return;
	}
	
	for(int i=0; i < selectedFrames.size();i++) {
		if(selectedFrames[i] == spriteState->getNumFrameIDs()-1) {
			return;
		}
	}
	
	std::vector<unsigned int> newIDS;
	
	for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
		unsigned int frameID = spriteState->getFrameIDAtIndex(i);
		newIDS.push_back(frameID);
	}
	
	swapElementsRight(selectedFrames, newIDS);
	
	for(int i=0; i < selectedFrames.size(); i++) {
		if(selectedFrames[i] < spriteState->getNumFrameIDs()-1) {
			selectedFrames[i]++;
		}
	}
	
	spriteState->setNewFrameIDs(newIDS);
}

void SpriteStateEditBar::deleteSelectedFrames() {
	if(!spriteState) {
		return;
	}
	spriteState->removeFrameIndices(selectedFrames);
	selectedFrames.clear();
}

SpriteStateEditBar::~SpriteStateEditBar() {
	core->getInput()->removeAllHandlersForListener(this);
}

SpriteStateBrowser::SpriteStateBrowser(Core *core, ResourcePool *pool) : UIElement(core) {
	
	headerBg = new UIRect(core, pool, 10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	UILabel *label = new UILabel(core, pool, "STATES", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	addChild(label);
	label->setPosition(10, 3);
	
	
	stateTreeView = new UITreeContainer(core, pool, "boxIcon.png", "All States", 10, 10);
	addChild(stateTreeView);
	stateTreeView->getRootNode()->toggleCollapsed();
	stateTreeView->setPosition(0.0, 30.0);
	
	newStateButton = new UIImageButton(core, pool, "spriteEditor/button_add.png", 1.0, 24, 24);
	addChild(newStateButton);
	newStateButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	removeStateButton = new UIImageButton(core, pool, "spriteEditor/button_remove.png", 1.0, 24, 24);
	addChild(removeStateButton);
	removeStateButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	moreButton = new UIImageButton(core, pool, "spriteEditor/button_more.png", 1.0, 24, 24);
	addChild(moreButton);
	moreButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
}

SpriteStateBrowser::~SpriteStateBrowser() {
	
}

void SpriteStateBrowser::Resize(Number width, Number height) {
	headerBg->Resize(width, 30.0);
	stateTreeView->Resize(width, height-30.0);

	moreButton->setPosition(width - 30.0, 3.0);
	removeStateButton->setPosition(width - 56.0, 3.0);
	newStateButton->setPosition(width - 82.0, 3.0);
}

SpriteStateEditor::SpriteStateEditor(Core *core, ResourcePool *pool, SpriteSet *spriteSet) : UIElement(core) {
	this->spriteSet = spriteSet;
	
	stateSizer = new UIHSizer(core, pool, 10, 10, 200, true);
	addChild(stateSizer);
	
	stateDetails = new SpriteStateEditorDetails(core, pool, spriteSet);
	stateSizer->addRightChild(stateDetails);
	
	stateBrowser = new SpriteStateBrowser(core, pool);
	stateSizer->addLeftChild(stateBrowser);
	
	newStateButton = stateBrowser->newStateButton;
	newStateButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	stateBrowser->removeStateButton->addEventListener(this, UIEvent::CLICK_EVENT);
	stateBrowser->moreButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	stateTreeView = stateBrowser->stateTreeView;
	stateTreeView->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	
	selectedState = NULL;
	
	visible = false;
	enabled = false;
}

SpriteState *SpriteStateEditor::getSelectedState() {
	return selectedState;
}

SpriteStateEditorDetails *SpriteStateEditor::getDetailsEditor() {
	return stateDetails;
}

SpriteStateBrowser *SpriteStateEditor::getStateBrowser() {
	return stateBrowser;
}

void SpriteStateEditor::setSpriteEntry(std::shared_ptr<Sprite> entry) {
	
	if(!entry) {
		visible = false;
		enabled = false;
		return;
	}
	
	visible = true;
	enabled = true;

	spriteSetEntry = entry;
	
	refreshStates();
	
	if(entry->getNumStates() > 0) {
		stateBrowser->stateTreeView->getRootNode()->getTreeChild(0)->setSelected();
		dispatchEvent(new Event(), Event::CHANGE_EVENT);
	}
	
}

void SpriteStateEditor::handleEvent(Event *event) {
	if(event->getDispatcher() == newStateButton) {
		
		globalFrame->textInputPopup->action = "newState";
		globalFrame->textInputPopup->setCaption("New state name");
		globalFrame->textInputPopup->setValue("New State");
		globalFrame->textInputPopup->addEventListener(this, UIEvent::OK_EVENT);
		globalFrame->showModal(globalFrame->textInputPopup);
		
	} else if(event->getDispatcher() == globalFrame->textInputPopup) {
		if(event->getEventCode() == UIEvent::OK_EVENT) {
			if(globalFrame->textInputPopup->action == "newState") {
				SpriteState *newState = new SpriteState(spriteSet, globalFrame->textInputPopup->getValue());
				spriteSetEntry->addSpriteState(newState);
				
				PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
				beforeData->sprite = spriteSetEntry;
				beforeData->state = newState;
				
				PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
				data->sprite = spriteSetEntry;
				data->state = newState;
				data->reverse = false;
				editor->didAction("new_state", beforeData, data);
				
				refreshStates();
			} else if(globalFrame->textInputPopup->action == "renameState") {
				
				
				PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
				beforeData->state = selectedState;
				beforeData->sprite = spriteSetEntry;
				beforeData->name = selectedState->getName();
				
				selectedState->setName(globalFrame->textInputPopup->getValue());
				refreshStates();
				
				PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
				data->sprite = spriteSetEntry;
				data->state = selectedState;
				data->name = selectedState->getName();
				data->reverse = false;
				editor->didAction("rename_state", beforeData, data);
				
				
			}
		}
		globalFrame->textInputPopup->removeAllHandlersForListener(this);
	} else if(event->getDispatcher() == globalFrame->yesNoPopup) {
		if(event->getEventCode() == UIEvent::OK_EVENT) {
			if(globalFrame->yesNoPopup->action == "removeState") {
				if(selectedState) {
					spriteSetEntry->removeSpriteState(selectedState);

					PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
					beforeData->state = selectedState;
					beforeData->sprite = spriteSetEntry;
					
					PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
					data->sprite = spriteSetEntry;
					data->state = selectedState;
					data->reverse = false;
					editor->didAction("remove_state", beforeData, data);
					
					selectedState = NULL;
					stateDetails->setSpriteState(NULL);
					refreshStates();
					
					dispatchEvent(new Event(), Event::CHANGE_EVENT);
				}
			}
		}
		globalFrame->yesNoPopup->removeAllHandlersForListener(this);
	} else if(event->getDispatcher() == stateBrowser->removeStateButton) {
		if(selectedState) {
			globalFrame->yesNoPopup->setCaption("Are you sure you want to remove state \""+selectedState->getName()+"\"?");
			globalFrame->yesNoPopup->action = "removeState";
			globalFrame->yesNoPopup->addEventListener(this, UIEvent::OK_EVENT);
			globalFrame->showModal(globalFrame->yesNoPopup);
		}
	} else if(event->getDispatcher() == stateBrowser->moreButton) {
		stateMoreMenu = globalMenu->showMenuAtMouse(100.0);
		stateMoreMenu->addOption("Rename", "rename");
		stateMoreMenu->fitToScreenVertical();
		stateMoreMenu->addEventListener(this, UIEvent::OK_EVENT);
	} else if(event->getDispatcher() == stateMoreMenu) {
		if(selectedState) {
			if(stateMoreMenu->getSelectedItem()->getMenuItemID() == "rename") {
				globalFrame->textInputPopup->action = "renameState";
				globalFrame->textInputPopup->setCaption("New state name");
				globalFrame->textInputPopup->setValue(selectedState->getName());
				globalFrame->textInputPopup->addEventListener(this, UIEvent::OK_EVENT);
				globalFrame->showModal(globalFrame->textInputPopup);
			}
		}
		
	} else if(event->getDispatcher() == stateTreeView->getRootNode()) {
		selectedState = (SpriteState*) stateTreeView->getRootNode()->getSelectedNode()->getUserData();
		if(selectedState) {
			stateDetails->setSpriteState(selectedState);
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
		
	}
}

void SpriteStateEditor::refreshStates() {
	stateTreeView->getRootNode()->clearTree();
	
	for(int i=0; i < spriteSetEntry->getNumStates(); i++) {
		SpriteState *state = spriteSetEntry->getState(i);
		UITree *newNode = stateTreeView->getRootNode()->addTreeChild("treeIcons/state.png", state->getName(), (void*) state);
		if(state == selectedState) {
			newNode->setSelected();
		}
	}
}

SpriteStateEditor::~SpriteStateEditor() {
	globalFrame->textInputPopup->removeAllHandlersForListener(this);
	globalFrame->yesNoPopup->removeAllHandlersForListener(this);
	
}

void SpriteStateEditor::Resize(Number width, Number height) {
	stateSizer->Resize(width, height);
}

SpritePreview::SpritePreview(Core *core, ResourcePool *pool, SpriteSet *spriteSet) : UIElement(core) {
	
	previewBg = new UIImage(core, pool, "main/grid_dark.png");
	addChild(previewBg);
	previewBg->processInputEvents = true;
	previewBg->setPosition(0.0, 30.0);
	
	sprite = new SceneSprite(spriteSet);
	addChild(sprite);
	sprite->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	
	headerBg = new UIRect(core, pool, 10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	UILabel *label = new UILabel(core, pool, "PREVIEW", 18, "section", Label::ANTIALIAS_FULL);
	label->color.setColorHexFromString(core->getConfig()->getStringValue("Polycode", "uiHeaderFontColor"));
	
	addChild(label);
	label->setPosition(10, 3);
	
	boundingBoxPreview = new SceneMesh();
	addChild(boundingBoxPreview);
	boundingBoxPreview->getShaderPass(0).shaderBinding->setTextureForParam("diffuse", pool->loadTexture("main/stipple_small.png"));
	boundingBoxPreview->lineWidth = 1;

	
	bgSelector = new UIIconSelector(core, pool);
	bgSelector->addIcon("spriteEditor/grid_icon_dark.png");
	bgSelector->addIcon("spriteEditor/grid_icon_light.png");
	bgSelector->selectIndex(0);
	bgSelector->addEventListener(this, UIEvent::SELECT_EVENT);
	addChild(bgSelector);
	
}

SceneSprite *SpritePreview::getSceneSprite() {
	return sprite;
}

SpritePreview::~SpritePreview() {
	
}

void SpritePreview::handleEvent(Event *event) {
	if(event->getDispatcher() == bgSelector) {
		switch(bgSelector->getSelectedIndex()) {
			case 0:
				previewBg->loadTexture("main/grid_dark.png");
			break;
			case 1:
				previewBg->loadTexture("main/grid_light.png");
			break;
		}
	}
}

void SpritePreview::Update(Number elapsed) {
	
	SpriteState	 *state = sprite->getCurrentSpriteState();
	
//	  if(state) {
//		  Vector2 bBox = state->getBoundingBox();
//		  sprite->setLocalBoundingBox(bBox.x / state->getPixelsPerUnit(), bBox.y / state->getPixelsPerUnit(), 0.001);
//	  }
//	  
	//boundingBoxPreview->setPrimitiveOptions(ScenePrimitive::TYPE_VPLANE, sprite->getLocalBoundingBox().x, sprite->getLocalBoundingBox().y);
	
	std::shared_ptr<Mesh> bbBoxMesh = boundingBoxPreview->getMesh();
	bbBoxMesh->clearMesh();
	
	MeshGeometry bBoxMeshGeometry;
	bBoxMeshGeometry.indexedMesh = true;
	
	
	Number spriteScale =  (getWidth() - 80) / sprite->getSpriteBoundingBox().x;
	
	if(sprite->getSpriteBoundingBox().y * spriteScale > getHeight() - 80) {
		spriteScale =  (getHeight() - 80) / sprite->getSpriteBoundingBox().y;
	}
	
	Vector3 bBox = sprite->getLocalBoundingBox() * spriteScale;
	
	SpriteFrame frame;
	
	
	frame.coordinates.x = 0.0;
	frame.coordinates.y = 0.0;
	Vector3 bBoxNorm = bBox;
	bBoxNorm.Normalize();
	frame.coordinates.w = bBoxNorm.x * spriteScale;
	frame.coordinates.h = bBoxNorm.y * spriteScale;
	
	bBoxMeshGeometry.addVertexWithUV(-bBox.x * 0.5, bBox.y * 0.5, 0.0, frame.coordinates.x, frame.coordinates.y);
	bBoxMeshGeometry.addVertexWithUV((-bBox.x * 0.5)+bBox.x, bBox.y * 0.5, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y);
	bBoxMeshGeometry.addVertexWithUV((-bBox.x * 0.5)+bBox.x, bBox.y * 0.5 - bBox.y, 0.0, frame.coordinates.x+frame.coordinates.w, frame.coordinates.y + frame.coordinates.h);
	bBoxMeshGeometry.addVertexWithUV(-bBox.x * 0.5, bBox.y * 0.5 - bBox.y, 0.0, frame.coordinates.x, frame.coordinates.y + frame.coordinates.h);
	
	bBoxMeshGeometry.addIndexedFace(0,1);
	bBoxMeshGeometry.addIndexedFace(1,2);
	bBoxMeshGeometry.addIndexedFace(2,3);
	bBoxMeshGeometry.addIndexedFace(3,0);
	
	bbBoxMesh->addSubmesh(bBoxMeshGeometry);
	
	sprite->setScale(spriteScale, spriteScale, 1.0);

}

void SpritePreview::Resize(Number width, Number height) {
	headerBg->Resize(width, 30.0);
	previewBg->Resize(width, height-30.0);
	previewBg->setImageCoordinates(0, 0, width, height-30.0);
	
	sprite->setPosition(width/2.0, height/2.0);
	boundingBoxPreview->setPosition(sprite->getPosition());
	
	bgSelector->setPosition(width - bgSelector->getWidth() - 3.0, 3.0);
	
	UIElement::Resize(width, height);
}

PolycodeSpriteEditor::PolycodeSpriteEditor(Core *core, ResourcePool *pool) : PolycodeEditor(core, pool, true){
	
}

void PolycodeSpriteEditor::handleEvent(Event *event) {
	if(event->getDispatcher() == spriteBrowser) {
		std::shared_ptr<Sprite> selectedSprite = spriteBrowser->getSelectedSpriteEntry();
		spritePreview->getSceneSprite()->setSprite(selectedSprite);
		stateEditor->setSpriteEntry(selectedSprite);
	} else if(event->getDispatcher() == addFramesButton) {
		SpriteState *spriteState = stateEditor->getDetailsEditor()->getSpriteState();
		bool generateBBox = false;
		if(spriteState->getNumFrameIDs() == 0) {
			generateBBox = true;
		}
		
		
		PolycodeSpriteEditorActionData *beforeData = new PolycodeSpriteEditorActionData();
		for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
			beforeData->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
		}
		
		spriteState->appendFrames(spriteSheetEditor->getSelectedFrameIDs());
		
		PolycodeSpriteEditorActionData *data = new PolycodeSpriteEditorActionData();
		for(int i=0; i < spriteState->getNumFrameIDs(); i++) {
			data->frameIDs.push_back(spriteState->getFrameIDAtIndex(i));
		}
		data->reverse = false;
		didAction("changed_sprite_set_frames", beforeData, data);
		
		if(generateBBox && spriteSheetEditor->getSelectedFrameIDs().size() > 0) {
			
			SpriteFrame frame = sprite->getSpriteFrameByID(spriteSheetEditor->getSelectedFrameIDs()[0]);
			
			Number aspectRatio = frame.coordinates.w / frame.coordinates.h;
			
			Number textureAspectRatio = ((Number)sprite->getTexture()->getWidth()) / ((Number)sprite->getTexture()->getHeight());
			
			
			Number frameHeight = frame.coordinates.h * ((Number)sprite->getTexture()->getHeight());
			
			Number frameWidth = frameHeight * aspectRatio * textureAspectRatio;
			
			spriteState->setBoundingBox(Vector2(frameWidth, frameHeight));
		}
		
		stateEditor->getDetailsEditor()->refreshState();
	
		
	} else if(event->getDispatcher() == stateEditor) {
		spritePreview->getSceneSprite()->setSpriteState(stateEditor->getSelectedState(), 0, false);
	} else if(event->getDispatcher() == spriteSheetEditor) {
		SpriteState *state = spritePreview->getSceneSprite()->getCurrentSpriteState();
		if(state) {
			state->rebuildStateMeshes();
		}
	}
	PolycodeEditor::handleEvent(event);
}

PolycodeSpriteEditor::~PolycodeSpriteEditor() {
	core->getResourceManager()->unsubscibeFromResourcePool(sprite);
	delete mainSizer;
	delete topSizer;
	delete bottomSizer;
	delete spriteSheetEditor;
	delete spriteBrowser;
	delete stateEditor;
	delete spritePreview;
}

bool PolycodeSpriteEditor::openFile(OSFileEntry filePath) {
	
	String resourceName = filePath.fullPath.replace(parentProject->getRootFolder()+"/", "");
	
	sprite = (SpriteSet*) core->getResourceManager()->getResourcePoolByName(resourceName);
	
	if(!sprite) {
		sprite = new SpriteSet(core, filePath.fullPath, resourcePool);
		sprite->reloadResourcesOnModify = true;
		sprite->deleteOnUnsubscribe = true;
		
	}
	core->getResourceManager()->subscribeToResourcePool(sprite);
	
	mainSizer = new UIVSizer(core, resourcePool, 100, 100, 200, false);
	addChild(mainSizer);
	
	topSizer = new UIHSizer(core, resourcePool, 100, 100, 400, false);
	mainSizer->addTopChild(topSizer);
	
	bottomSizer = new UIHSizer(core, resourcePool, 100, 100, 200, true);
	mainSizer->addBottomChild(bottomSizer);
	
	
	spriteSheetEditor = new SpriteSheetEditor(core, resourcePool, sprite);
	topSizer->addLeftChild(spriteSheetEditor);
	spriteSheetEditor->addEventListener(this, Event::CHANGE_EVENT);
	spriteSheetEditor->editor = this;
	
	spriteBrowser = new SpriteBrowser(core, resourcePool, sprite);
	spriteBrowser->editor = this;
	bottomSizer->addLeftChild(spriteBrowser);
	spriteBrowser->addEventListener(this, Event::CHANGE_EVENT);
	
	stateEditor = new SpriteStateEditor(core, resourcePool, sprite);
	bottomSizer->addRightChild(stateEditor);
	stateEditor->editor = this;
	stateEditor->getDetailsEditor()->editor = this;
	stateEditor->getDetailsEditor()->getEditBar()->editor = this;
	
	addFramesButton = stateEditor->getDetailsEditor()->getAppendFramesButton();
	addFramesButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	spritePreview = new SpritePreview(core, resourcePool, sprite);
	topSizer->addRightChild(spritePreview);
	
	stateEditor->getDetailsEditor()->setSceneSprite(spritePreview->getSceneSprite());
	
	stateEditor->addEventListener(this, Event::CHANGE_EVENT);
	
	spriteBrowser->refreshSprites();
	
	
	PolycodeEditor::openFile(filePath);
	return true;
}

void PolycodeSpriteEditor::selectAll() {
	spriteSheetEditor->selectAll();
}

void PolycodeSpriteEditor::doAction(String actionName, PolycodeEditorActionData *data) {

	PolycodeSpriteEditorActionData *spriteData = (PolycodeSpriteEditorActionData*)data;
	
	if(actionName == "new_sprite") {
		if(spriteData->reverse) {
			sprite->removeSprite(spriteData->sprite);
			stateEditor->setSpriteEntry(NULL);
		} else {
			sprite->addSpriteEntry(spriteData->sprite);
			stateEditor->setSpriteEntry(spriteData->sprite);
		}
		spriteBrowser->refreshSprites();
		stateEditor->refreshStates();
		
	} else if(actionName == "remove_sprite") {
		if(spriteData->reverse) {
			sprite->addSpriteEntry(spriteData->sprite);
			stateEditor->setSpriteEntry(spriteData->sprite);
		} else {
			sprite->removeSprite(spriteData->sprite);
			stateEditor->setSpriteEntry(NULL);
		}
		spriteBrowser->refreshSprites();
		stateEditor->refreshStates();
	} else if(actionName == "rename_sprite") {
		spriteData->sprite->setName(spriteData->name);
		spriteBrowser->refreshSprites();
		stateEditor->refreshStates();
	} else if(actionName == "new_state") {

		if(spriteData->reverse) {
			spriteData->sprite->removeSpriteState(spriteData->state);
			stateEditor->getDetailsEditor()->setSpriteState(NULL);
		} else {
			spriteData->sprite->addSpriteState(spriteData->state);
			stateEditor->getDetailsEditor()->setSpriteState(spriteData->state);
		}
		stateEditor->refreshStates();
 
	} else if(actionName == "remove_state") {
		
		if(spriteData->reverse) {
			spriteData->sprite->addSpriteState(spriteData->state);
			stateEditor->getDetailsEditor()->setSpriteState(spriteData->state);
		} else {
			spriteData->sprite->removeSpriteState(spriteData->state);
			stateEditor->getDetailsEditor()->setSpriteState(NULL);
		}
		stateEditor->refreshStates();
	} else if(actionName == "rename_state") {
		
		spriteData->state->setName(spriteData->name);
		stateEditor->refreshStates();
	} else if(actionName == "changed_sprite_set_frames") {
		
		SpriteState *spriteState = stateEditor->getDetailsEditor()->getSpriteState();
		spriteState->clearFrames();
		spriteState->appendFrames(spriteData->frameIDs);
		
		if(spriteSheetEditor->getSelectedFrameIDs().size() > 0) {
			
			SpriteFrame frame = sprite->getSpriteFrameByID(spriteSheetEditor->getSelectedFrameIDs()[0]);
			Number aspectRatio = frame.coordinates.w / frame.coordinates.h;
			Number textureAspectRatio = ((Number)sprite->getTexture()->getWidth()) / ((Number)sprite->getTexture()->getHeight());
			Number frameHeight = frame.coordinates.h * ((Number)sprite->getTexture()->getHeight());
			Number frameWidth = frameHeight * aspectRatio * textureAspectRatio;
			spriteState->setBoundingBox(Vector2(frameWidth, frameHeight));
		}
		
		stateEditor->getDetailsEditor()->refreshState();
		
	} else if(actionName == "changed_frames") {
		sprite->clearFrames();
		for(int i=0; i < spriteData->spriteFrames.size(); i++) {
			sprite->addSpriteFrame(spriteData->spriteFrames[i]);
		}
	} else if(actionName == "changed_image") {
		spriteSheetEditor->sprite->setTexture(sprite->getTexture());
		spriteSheetEditor->previewImage->setTexture(sprite->getTexture());
		
	} else if(actionName == "changed_state_info") {
		spriteData->state->setSpriteOffset(spriteData->stateOffset);
		spriteData->state->setBoundingBox(spriteData->stateBBox);
		spriteData->state->setStateFPS(spriteData->stateFPS);
		spriteData->state->setPixelsPerUnit(spriteData->stateScale);
		stateEditor->getDetailsEditor()->refreshState();
	}

}

void PolycodeSpriteEditor::saveFile() {
	Object fileObject;
	fileObject.root.name = "sprite_set";
	
	ObjectEntry *spriteSheetEntry = fileObject.root.addChild("sprite_sheet");
	
	spriteSheetEntry->addChild("fileName", sprite->getTexture()->getResourcePath());
	
	ObjectEntry *framesEntry = spriteSheetEntry->addChild("frames");
	
	
	for(int i=0; i < sprite->getNumFrames(); i++) {
		ObjectEntry *frameEntry = framesEntry->addChild("frame");
		SpriteFrame frame = sprite->getSpriteFrame(i);
		frameEntry->addChild("id", (int)frame.frameID);
		frameEntry->addChild("x", frame.coordinates.x);
		frameEntry->addChild("y", frame.coordinates.y);
		frameEntry->addChild("w", frame.coordinates.w);
		frameEntry->addChild("h", frame.coordinates.h);
		frameEntry->addChild("ax", frame.anchorPoint.x);
		frameEntry->addChild("ay", frame.anchorPoint.y);
	}
	
	ObjectEntry *spritesEntry = fileObject.root.addChild("sprites");
	for(int i=0; i < sprite->getNumSpriteEntries(); i++) {
		std::shared_ptr<Sprite> spriteEntry = sprite->getSpriteEntry(i);
		ObjectEntry *spriteEntryEntry = spritesEntry->addChild("sprite");
		spriteEntryEntry->addChild("name", spriteEntry->getName());

		ObjectEntry *spriteStatesEntry = spriteEntryEntry->addChild("states");
		
		for(int j=0; j < spriteEntry->getNumStates(); j++) {
			SpriteState *spriteState = spriteEntry->getState(j);
			ObjectEntry *spriteStateEntry = spriteStatesEntry->addChild("state");
			
			spriteStateEntry->addChild("name", spriteState->getName());
			spriteStateEntry->addChild("fps", spriteState->getStateFPS());
			spriteStateEntry->addChild("scale", spriteState->getPixelsPerUnit());
			spriteStateEntry->addChild("width", spriteState->getBoundingBox().x);
			spriteStateEntry->addChild("height", spriteState->getBoundingBox().y);
			spriteStateEntry->addChild("offset_x", spriteState->getSpriteOffset().x);
			spriteStateEntry->addChild("offset_y", spriteState->getSpriteOffset().y);
			
			String frameIDs;
			
			for(int f=0; f < spriteState->getNumFrameIDs(); f++) {
				frameIDs += String::IntToString(spriteState->getFrameIDAtIndex(f));
				if(f < spriteState->getNumFrameIDs()-1) {
					frameIDs += ",";
				}
			}
			
			spriteStateEntry->addChild("frame_ids", frameIDs);
		}
		
	}
	fileObject.saveToXML(core, filePath);
	setHasChanges(false);
}

void PolycodeSpriteEditor::Resize(int x, int y) {
	mainSizer->Resize(x, y);
	PolycodeEditor::Resize(x,y);
}

