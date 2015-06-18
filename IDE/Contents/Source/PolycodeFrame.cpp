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

#include "PolycodeFrame.h"


UIColorPicker *globalColorPicker;
PolycodeFrame *globalFrame;
extern UIGlobalMenu *globalMenu;
EditorHolder *activeEditorHolder = NULL;
extern PolycodeEditorManager *globalEditorManager;


EditPoint::EditPoint(BezierPoint *point, unsigned int type) : Entity() {
	this->point = point;
	this->type = type;
	processInputEvents = true;
	
	draggingPoint = NULL;
	dragging = false;

	controlHandle1 = new UIRect(5, 5);
    controlHandle1->setColor(0.0, 1.0, 0.3, 1.0);
	controlHandle1->setAnchorPoint(0.0, 0.0, 0.0);
	
	controlHandle1->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	controlHandle1->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	controlHandle1->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	controlHandle1->processInputEvents = true;
	controlHandle1->setWidth(30);
	controlHandle1->setHeight(30);
		
	addChild(controlHandle1);
	
	controlHandle2 = new UIRect(5, 5);
    controlHandle2->setColor(0.0, 1.0, 0.3, 1.0);
	controlHandle2->setAnchorPoint(0.0, 0.0, 0.0);
	controlHandle2->processInputEvents = true;
	
	controlHandle2->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	controlHandle2->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	controlHandle2->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	controlHandle2->setWidth(30);
	controlHandle2->setHeight(30);
	
	addChild(controlHandle2);
	
	pointHandle = new UIRect(8, 8);
    pointHandle->setColor(1.0, 0.5, 0.2, 1.0);
	pointHandle->processInputEvents = true;
	pointHandle->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	pointHandle->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	pointHandle->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	pointHandle->setAnchorPoint(0.0, 0.0, 0.0);
	pointHandle->setWidth(30);
	pointHandle->setHeight(30);

	
	if(type == TYPE_START_POINT) {
		controlHandle1->visible = false;
		controlHandle1->enabled = false;		
		connectorLine1 = NULL;
	} else {
		connectorLine1 = new SceneLine(pointHandle, controlHandle1);
		addChild(connectorLine1);
		connectorLine1->setColorInt(39, 212, 255, 100);
		connectorLine1->setLineWidth(2.0);
		connectorLine1->lineSmooth = true;
	}
	
	
	if(type == TYPE_END_POINT) {
		controlHandle2->visible = false;
		controlHandle2->enabled = false;		
		connectorLine2 = NULL;
	} else {
		connectorLine2 = new SceneLine(pointHandle, controlHandle2);
		addChild(connectorLine2);
		connectorLine2->setColorInt(39, 212, 255, 100);
		connectorLine2->setLineWidth(2.0);
		connectorLine2->lineSmooth = true;
	}	
	
	CoreServices::getInstance()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	
	addChild(pointHandle);	
	
	updatePosition();
}

void EditPoint::setMode(unsigned int mode) {
	this->mode = mode;
}

void EditPoint::updateCurvePoint() {

	point->p1.x = controlHandle1->getPosition2D().x/300;
	point->p1.y = controlHandle1->getPosition2D().y/-100;

	point->p2.x = pointHandle->getPosition2D().x/300;
	point->p2.y = pointHandle->getPosition2D().y/-100;		
	
	point->p3.x = controlHandle2->getPosition2D().x/300;
	point->p3.y = controlHandle2->getPosition2D().y/-100;	

}

void EditPoint::handleEvent(Event *event) {

	if(event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput()) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEMOVE:
				if(dragging) {
					if(draggingPoint) {
					
						Vector2 newPosition = CoreServices::getInstance()->getCore()->getInput()->getMousePosition();
						
						Vector2 translateAmt = Vector2(basePosition.x - newPosition.x, basePosition.y - newPosition.y);
						
						if(type != TYPE_POINT && draggingPoint == pointHandle) {

							// don't let drag start and end control points
							translateAmt.x = 0.0;
						} 						
						
						draggingPoint->setPosition(basePointPosition.x - translateAmt.x, basePointPosition.y - translateAmt.y);												
						
						if(draggingPoint == pointHandle) {
							controlHandle1->setPosition(baseControl1.x - translateAmt.x, baseControl1.y - translateAmt.y);
							controlHandle2->setPosition(baseControl2.x - translateAmt.x, baseControl2.y - translateAmt.y);																			
						}
						
						limitPoint(pointHandle);
						limitPoint(controlHandle1);
						limitPoint(controlHandle2);
						
						updateCurvePoint();
						dispatchEvent(new Event(), Event::CHANGE_EVENT);
					}
				}
			break;
		}
	}

	if(event->getDispatcher() == pointHandle || event->getDispatcher() == controlHandle1 || event->getDispatcher() == controlHandle2) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				if(mode == CurveEditor::MODE_SELECT) {
					draggingPoint = (UIImage*)event->getDispatcher();
					dragging = true;
					basePosition = CoreServices::getInstance()->getCore()->getInput()->getMousePosition(); 
					basePointPosition = draggingPoint->getPosition2D();
				
					baseControl1 = controlHandle1->getPosition2D();
					baseControl2 = controlHandle2->getPosition2D();				
				}
				
				if(mode == CurveEditor::MODE_REMOVE) {
					if(type == TYPE_POINT) {
						dispatchEvent(new Event(), Event::CANCEL_EVENT);				
					}
				}
				
			break;
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:			
				dragging = false;				
				draggingPoint = NULL;
			break;
		}
	}
}

void EditPoint::limitPoint(UIRect *point) {
		if(point->getPosition().x < 0.0)
			point->setPositionX(0.0);
		if(point->getPosition().x > 300.0)
			point->setPositionX(300.0);

		if(point->getPosition().y > 0.0)
			point->setPositionY(0.0);
		if(point->getPosition().y < -100.0)
			point->setPositionY(-100.0);

}

void EditPoint::updatePosition() {
	pointHandle->setPosition(300.0*point->p2.x, -100*point->p2.y, 0.0);	
	controlHandle1->setPosition(300.0*point->p1.x, -100*point->p1.y, 0.0);	
	controlHandle2->setPosition(300.0*point->p3.x, -100*point->p3.y, 0.0);	
}

EditPoint::~EditPoint() {

}

EditCurve::EditCurve(BezierCurve *targetCurve, Color curveColor) : UIElement() {
	
	this->targetCurve = targetCurve;
	
	visMesh = new SceneMesh(Mesh::LINE_STRIP_MESH);
	
	for(int i=0; i < CURVE_SIZE; i++) {		
		visMesh->getMesh()->addVertex(0.0, 0.0, 0.0);
	}
	
	visMesh->lineSmooth = true;
	visMesh->lineWidth = 2.0;

	addChild(visMesh);
	visMesh->setPosition(0, 100);	
	visMesh->color = curveColor;
	
	pointsBase = new UIElement();
	addChild(pointsBase);
	
	pointToRemove = NULL;
	
	updateCurve();
	updatePoints();
	
	Deactivate();
}

void EditCurve::updatePoints() {
	for(int i=0; i < points.size(); i++) {
		pointsBase->removeChild(points[i]);
		//delete points[i];
	}
	
	points.clear();
	for(int i=0; i < targetCurve->getNumControlPoints(); i++) {
	
		unsigned int type = EditPoint::TYPE_POINT;
		if(i == 0)
			type = EditPoint::TYPE_START_POINT;

		if(i == targetCurve->getNumControlPoints()-1)
			type = EditPoint::TYPE_END_POINT;


		EditPoint *point = new EditPoint(targetCurve->getControlPoint(i), type);
		point->setMode(mode);
		point->addEventListener(this, Event::CHANGE_EVENT);
		point->addEventListener(this, Event::CANCEL_EVENT);		
		pointsBase->addChild(point);
		points.push_back(point);
		point->setPosition(0, 100);			
	}
}

void EditCurve::setMode(unsigned int mode) {
	this->mode = mode;
	for(int i=0; i < points.size(); i++) {
		points[i]->setMode(mode);
	}
}

void EditCurve::Activate() {
	pointsBase->visible = true;
	pointsBase->enabled = true;
	visMesh->color.a = 1.0;	
}

void EditCurve::Deactivate() {
	pointsBase->visible = false;
	pointsBase->enabled = false;
	visMesh->color.a = 1.0;	
}

void EditCurve::Update() {
	if(pointToRemove) {
		targetCurve->removePoint(pointToRemove->point);
		updatePoints();
		updateCurve();
		pointToRemove = NULL;
	}
}

void EditCurve::handleEvent(Event *event) {
	if(event->getEventCode() == Event::CHANGE_EVENT) {
		updateCurve();
	}

	if(event->getEventCode() == Event::CANCEL_EVENT) {	
		for(int i=0; i < points.size(); i++) {	
			if(event->getDispatcher() == points[i]) {	
				pointToRemove = points[i];
				break;
			}
		}
	}
}

void EditCurve::updateCurve() {
	targetCurve->recalculateDistances();
	
	Number interval = 300.0/CURVE_SIZE;
	Number normInterval = 1.0/CURVE_SIZE;
	
	interval += interval/CURVE_SIZE;
	normInterval += normInterval/CURVE_SIZE;

    visMesh->getMesh()->vertexPositionArray.data.clear();
    
	for(int i=0; i < CURVE_SIZE; i++) {        
        visMesh->getMesh()->addVertex(targetCurve->getPointAt(normInterval * i).x * 300, targetCurve->getPointAt(normInterval * i).y * 100.0, 0.0);
	}
	
    visMesh->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
}

EditCurve::~EditCurve() {

}

CurveEditor::CurveEditor() : UIWindow("", 440, 160) {
	
	closeOnEscape = true;
		
	bg = new UIRect(300, 100);
    bg->setColor(0.1, 0.1, 0.1, 1.0);
	addChild(bg);
	bg->setPosition(160, 63);
	bg->processInputEvents = true;
	bg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
	selectorImage = new UIImage("main/selector.png", 24, 24);
	addChild(selectorImage);
		
	selectButton = new UIImageButton("main/arrow.png", 1.0, 24, 24);
	addChild(selectButton);
	selectButton->addEventListener(this, UIEvent::CLICK_EVENT);
	selectButton->setPosition(170, 33);

	addButton = new UIImageButton("main/arrow_add.png", 1.0, 24, 24);
	addChild(addButton);
	addButton->addEventListener(this, UIEvent::CLICK_EVENT);	
	addButton->setPosition(170 + 32, 33);

	removeButton = new UIImageButton("main/arrow_remove.png", 1.0, 24, 24);
	addChild(removeButton);
	removeButton->addEventListener(this, UIEvent::CLICK_EVENT);		
	removeButton->setPosition(170 + 64, 33);
	
	selectorImage->setPosition(selectButton->getPosition().x, selectButton->getPosition().y);

	selectedCurve = NULL;

	setMode(0);
	
	treeContainer = new UITreeContainer("boxIcon.png", L"Curves", 145, 135);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	treeContainer->setPosition(12, 33);
	
	treeContainer->getRootNode()->setUserData(NULL);

	
	addChild(treeContainer);	

}

void CurveEditor::onClose() {
	visible = false;
	enabled = false;
}


void CurveEditor::clearCurves() {
	selectedCurve = NULL;
	treeContainer->getRootNode()->clearTree();
	for(int i=0; i < curves.size(); i++) {
		removeChild(curves[i]);
		delete curves[i];
	}
	
	curves.clear();
}

void CurveEditor::addCurve(String name, BezierCurve *curve, Color curveColor) {

	UITree *newNode = treeContainer->getRootNode()->addTreeChild("main/curve_icon.png", name);
	EditCurve *editCurve = new EditCurve(curve, curveColor);
	addChild(editCurve);
	editCurve->setPosition(160, 63);	
	curves.push_back(editCurve);
	
	newNode->setUserData((void*) editCurve);
	
}

void CurveEditor::setMode(unsigned int mode) {
	this->mode = mode;
	if(selectedCurve) {
		selectedCurve->setMode(mode);
	}
}

void CurveEditor::handleEvent(Event *event) {
	
	if(mode == MODE_ADD) {
		if(event->getDispatcher() == bg) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				InputEvent *inputEvent = (InputEvent*)event;
				if(selectedCurve) {
					Vector2 pos = inputEvent->mousePosition;
					pos.x = pos.x/300.0;
					pos.y = 1.0-(pos.y/100.0);
					
					BezierCurve *targetCurve = selectedCurve->targetCurve;
				
					bool done = false;
					for(int i=0; i < targetCurve->getNumControlPoints(); i++) {
						if(pos.x < targetCurve->getControlPoint(i)->p2.x && !done) {
							targetCurve->insertPoint = targetCurve->getControlPoint(i);
							done = true;							
						}
					}
				
					targetCurve->addControlPoint2dWithHandles(pos.x-0.1, pos.y, pos.x, pos.y, pos.x + 0.1, pos.y);
					selectedCurve->updatePoints();
					selectedCurve->updateCurve();					
				}
			}
		}
	}
	
	if(event->getDispatcher() == selectButton) {
		selectorImage->setPosition(selectButton->getPosition().x, selectButton->getPosition().y);
		setMode(0);
	}

	if(event->getDispatcher() == addButton) {
		selectorImage->setPosition(addButton->getPosition().x, addButton->getPosition().y );
		setMode(1);
	}

	if(event->getDispatcher() == removeButton) {
		selectorImage->setPosition(removeButton->getPosition().x, removeButton->getPosition().y);
		setMode(2);
	}
	
	if(event->getDispatcher() == treeContainer->getRootNode()) {
		if(event->getEventCode() == UITreeEvent::SELECTED_EVENT){ 
			EditCurve *curve = (EditCurve *)treeContainer->getRootNode()->getSelectedNode()->getUserData();
			if(selectedCurve) {
				selectedCurve->Deactivate();
			}
			selectedCurve = curve;
			if(curve) {
				curve->Activate();
				curve->setMode(mode);
                curve->getParentEntity()->moveChildTop(curve);
			}
		}
	}	
	
	UIWindow::handleEvent(event);
}

CurveEditor::~CurveEditor() {

}

EditorHolder::EditorHolder(PolycodeProject *project, PolycodeEditorManager *editorManager, EditorHolder *parentHolder) : UIElement() {
	this->editorManager = editorManager;
	this->parentHolder = parentHolder;
	this->project = project;
	
	currentEditor = NULL;
	
	holderBar = new UIElement();
	addChild(holderBar);
	
	snapToPixels = true;
	
	headerBg = new UIRect(30, 30);
	holderBar->addChild(headerBg);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	vSplitButton = new UIImageButton("main/editor_vsplit.png", 1.0, 19, 13);
	holderBar->addChild(vSplitButton);
	vSplitButton->addEventListener(this, UIEvent::CLICK_EVENT);

	hSplitButton = new UIImageButton("main/editor_hsplit.png", 1.0, 19, 13);
	holderBar->addChild(hSplitButton);
	hSplitButton->addEventListener(this, UIEvent::CLICK_EVENT);	

	mergeSplitButton = new UIImageButton("main/editor_mergesplit.png", 1.0, 19, 13);
	holderBar->addChild(mergeSplitButton);
	mergeSplitButton->addEventListener(this, UIEvent::CLICK_EVENT);	
		
	closeFileButton = new UIImageButton("main/remove_icon.png", 1.0, 12, 12);
	holderBar->addChild(closeFileButton);
	closeFileButton->setPosition(10, 8);
	closeFileButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	currentFileSelector = new UIComboBox(globalMenu, 350);
	currentFileSelector->addEventListener(this, UIEvent::CHANGE_EVENT);
	holderBar->addChild(currentFileSelector);
	currentFileSelector->setPosition(30, 3);

	addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
			
	vSizer = NULL;
	hSizer = NULL;
	
	firstChildHolder = NULL;
	secondChildHolder = NULL;
	
	displayFilePathInSelector = false;
	
	initialUpdate = true;
	updateFileSelector();
	
	editorToMerge = NULL;
	isActive = false;
    
    setOwnsChildrenRecursive(true);
}

void EditorHolder::activateEditor(bool val) {
	if(firstChildHolder) {
		firstChildHolder->activateEditor(val);
		secondChildHolder->activateEditor(val);
		return;
	}
    if(currentEditor) {
        if(val) {
            currentEditor->Activate();
        } else {
            currentEditor->Deactivate();
        }
    }
}

ObjectEntry *EditorHolder::getEditorHolderConfig() {
	ObjectEntry *configEntry = new ObjectEntry();
	configEntry->name = "editor_holder";
	
	if(vSizer) {	
		configEntry->addChild("split", "vsplit");
		ObjectEntry *childEditors = configEntry->addChild("child_editors");
		childEditors->addChild(firstChildHolder->getEditorHolderConfig())->addChild("size", vSizer->getMainHeight());
		childEditors->addChild(secondChildHolder->getEditorHolderConfig());				
	} else if(hSizer) {
		configEntry->addChild("split", "hsplit");
		ObjectEntry *childEditors = configEntry->addChild("child_editors");
		childEditors->addChild(firstChildHolder->getEditorHolderConfig())->addChild("size", hSizer->getMainWidth());
		childEditors->addChild(secondChildHolder->getEditorHolderConfig());				
	} else {
		configEntry->addChild("split", "none");	
		if(currentEditor) {
			configEntry->addChild("file_name", 	currentEditor->getFilePath());
			ObjectEntry *editorConfig = currentEditor->getEditorConfig();
			if(editorConfig) {
				configEntry->addChild(editorConfig)->name = "editor_config";
			}			
		}

	}
	return configEntry;
}

void EditorHolder::applyConfig(ObjectEntry *entry) {
	ObjectEntry *splitEntry = (*entry)["split"];
	if(splitEntry) {
		if(splitEntry->stringVal == "none") {
			ObjectEntry *fileNameEntry = (*entry)["file_name"];
			if(fileNameEntry) {
				OSFileEntry file = OSFileEntry(fileNameEntry->stringVal, OSFileEntry::TYPE_FILE);
				PolycodeEditor *editor = globalEditorManager->openFile(file);
				if(editor) {
					setEditor(editor);
					ObjectEntry *editorConfig = (*entry)["editor_config"];
					if(editorConfig) {
						editor->applyEditorConfig(editorConfig);
					}
				}	
			}
		} else {
			if(splitEntry->stringVal == "hsplit") {
				makeHSplit();
			} else {
				makeVSplit();
			}
			
			ObjectEntry *childEntries = (*entry)["child_editors"];
			if(childEntries) {
				ObjectEntry *firstChildEntry = (*childEntries)[0];
				if(firstChildEntry) {
					firstChildHolder->applyConfig(firstChildEntry);
					if(vSizer) {
						vSizer->setMainHeightWithMinimum((*firstChildEntry)["size"]->NumberVal);
					} else if(hSizer) {
						hSizer->setMainWidthWithMinimum((*firstChildEntry)["size"]->NumberVal);
					}
				}
				ObjectEntry *secondChildEntry = (*childEntries)[1];
				if(secondChildEntry) {
					secondChildHolder->applyConfig(secondChildEntry);
				}				
			}
			
		}
	}
}

void EditorHolder::setActive(bool val) {

	isActive = val;
	
	if(firstChildHolder) {
		firstChildHolder->setActive(val);
		return;
	}	
	
	if(val) {	
		headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiAccentColor"));
		if(activeEditorHolder && activeEditorHolder != this) {
			activeEditorHolder->setActive(false);
		}
		activeEditorHolder = this;
		editorManager->setCurrentEditor(currentEditor);
	} else {
		headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	}
}

void EditorHolder::updateFileSelector() {
	currentFileSelector->removeAllHandlersForListener(this);
	currentFileSelector->clearItems();
	
	std::vector<PolycodeEditor*> editors = editorManager->getOpenEditorsForProject(project);

	for(int i=0; i < editors.size(); i++) {
		OSFileEntry entry(editors[i]->getFilePath(), OSFileEntry::TYPE_FILE);
		
		String projName = editors[i]->parentProject->getProjectName();
		String rootFolder = editors[i]->parentProject->getRootFolder();
		String filePath = editors[i]->getFilePath();
		
		String fullEntry = filePath;
		if(filePath.find(rootFolder) != -1) {
			fullEntry = projName + filePath.substr(rootFolder.size(), filePath.size()-1);
		}
		if(editors[i]->hasChanges()) {
			if (displayFilePathInSelector)
				currentFileSelector->addComboItem("* "+fullEntry, (void*)editors[i]);
			else
				currentFileSelector->addComboItem("* "+entry.name, (void*)editors[i]);
		} else {
			if (displayFilePathInSelector)
				currentFileSelector->addComboItem(fullEntry, (void*)editors[i]);
			else
				currentFileSelector->addComboItem(entry.name, (void*)editors[i]);
		}
		
		if(currentEditor == editors[i]) {
			if(!initialUpdate) {
				currentFileSelector->setSelectedIndex(i);
			}
		}
	}
	
	if(firstChildHolder) {
		firstChildHolder->updateFileSelector();
	}
	if(secondChildHolder) {
		secondChildHolder->updateFileSelector();
	}
	currentFileSelector->addEventListener(this, UIEvent::CHANGE_EVENT);
	initialUpdate = false;
}

void EditorHolder::setEditor(PolycodeEditor *newEditor) {

	if(vSizer || hSizer) {
		firstChildHolder->setEditor(newEditor);
		return;
	}

	if(currentEditor) {
		removeChild(currentEditor);
        currentEditor->Deactivate();
		currentEditor->setEditorHolder(NULL);
	}
	currentEditor = newEditor;
	if(currentEditor) {
        currentEditor->Activate();
		EditorHolder *currentEditorHolder = currentEditor->getEditorHolder();
		if(currentEditorHolder) {
			currentEditorHolder->setEditor(NULL);
		}
		if(currentEditor) {
			currentEditor->setEditorHolder(this);	
		}
		addChild(currentEditor);
	}

	updateFileSelector();
    
	if(isActive) {
		editorManager->setCurrentEditor(currentEditor);
	}
    
	Resize(getWidth(), getHeight());
}

PolycodeEditor *EditorHolder::getEditor() {
	return currentEditor;
}

void EditorHolder::makeVSplit() {
	holderBar->visible = false;
	holderBar->enabled = false;

	vSizer = new UIVSizer(getWidth(), getHeight(), getHeight()/2.0, true);
	vSizer->setMinimumSize(200);
	vSizer->setProportionalResize(true);
	
	addChild(vSizer);
	firstChildHolder = new EditorHolder(project, editorManager, this);
	firstChildHolder->addEventListener(this, UIEvent::CLOSE_EVENT);
	vSizer->addTopChild(firstChildHolder);		
	if(isActive) {
		firstChildHolder->setActive(true);
	}		
	secondChildHolder = new EditorHolder(project, editorManager, this);
	secondChildHolder->addEventListener(this, UIEvent::CLOSE_EVENT);
	vSizer->addBottomChild(secondChildHolder);


	if(currentEditor) {
		removeChild(currentEditor);
		currentEditor->setEditorHolder(NULL);			
		firstChildHolder->setEditor(currentEditor);
		currentEditor = NULL;
	}
    Resize(getWidth(), getHeight());
}

void EditorHolder::makeHSplit() {
	holderBar->visible = false;
	holderBar->enabled = false;
	
	hSizer = new UIHSizer(getWidth(), getHeight(), getWidth()/2.0, true);
	hSizer->setMinimumSize(200);
	hSizer->setProportionalResize(true);
	
	addChild(hSizer);
	firstChildHolder = new EditorHolder(project, editorManager, this);
	firstChildHolder->addEventListener(this, UIEvent::CLOSE_EVENT);		
	hSizer->addLeftChild(firstChildHolder);
	secondChildHolder = new EditorHolder(project, editorManager, this);
	secondChildHolder->addEventListener(this, UIEvent::CLOSE_EVENT);		
	hSizer->addRightChild(secondChildHolder);
	if(isActive) {
		firstChildHolder->setActive(true);
	}		
	
	if(currentEditor) {
		removeChild(currentEditor);
		currentEditor->setEditorHolder(NULL);
		firstChildHolder->setEditor(currentEditor);
		currentEditor = NULL;
	}
    Resize(getWidth(), getHeight());    
}

void EditorHolder::handleEvent(Event *event) {

	if(event->getDispatcher() == this) {
		if(holderBar->visible) {
			setActive(true);
		}
	} else if(event->getDispatcher() == vSplitButton) {
		makeVSplit();
	} else if(event->getDispatcher() == hSplitButton) {
		makeHSplit();								
	} else if(event->getDispatcher() == currentFileSelector) {
		PolycodeEditor *editor = (PolycodeEditor*) currentFileSelector->getSelectedItem()->data;
		if(currentEditor != editor) {
			setEditor(editor);
            Resize(getWidth(), getHeight());
		}
	
	} else if(event->getDispatcher() == mergeSplitButton) {
		if(parentHolder) {
			parentHolder->mergeSides(this);
            Resize(getWidth(), getHeight());
		}
	} else if(event->getDispatcher() == closeFileButton) {
		dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
	} else if(event->getDispatcher() == firstChildHolder || event->getDispatcher() == secondChildHolder) {
		if(event->getEventCode() == UIEvent::CLOSE_EVENT) {
			dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);		
		}
        Resize(getWidth(), getHeight());
	}
	
	UIElement::handleEvent(event);
}

void EditorHolder::Update() {
	if(editorToMerge) {
		_mergeSides(editorToMerge);
		editorToMerge = NULL;
	}
}

void EditorHolder::mergeSides(EditorHolder *mainHolder) {
	editorToMerge = mainHolder;
}

void EditorHolder::_mergeSides(EditorHolder *mainHolder) {
	holderBar->visible = true;
	holderBar->enabled = true;

    activeEditorHolder = this;
    
	PolycodeEditor *mainHolderEditor = mainHolder->getEditor();
		
	if(firstChildHolder) {
		PolycodeEditor *holderEditor = firstChildHolder->getEditor();
		if(holderEditor) {
			holderEditor->setEditorHolder(NULL);
		}
	}

	if(secondChildHolder) {
		PolycodeEditor *holderEditor = secondChildHolder->getEditor();
		if(holderEditor) {		
			holderEditor->setEditorHolder(NULL);
		}
	}
	
	if(vSizer) {
		removeChild(vSizer);
		delete vSizer;
	}
	if(hSizer) {
		removeChild(hSizer);
		delete hSizer;
	}
    
    firstChildHolder->setOwnsChildrenRecursive(false);
    secondChildHolder->setOwnsChildrenRecursive(false);
    
	delete firstChildHolder;
	delete secondChildHolder;
	
	firstChildHolder = NULL;
	secondChildHolder = NULL;
	vSizer = NULL;
	hSizer = NULL;
	
	setActive(true);
	setEditor(mainHolderEditor);
}

EditorHolder::~EditorHolder() {
	if(vSizer) {
		removeChild(vSizer);
		delete vSizer;
	}
	if(hSizer) {
		removeChild(hSizer);
		delete hSizer;
	}	
	
	if(firstChildHolder) {
		delete firstChildHolder;
	}
	if(secondChildHolder) {
		delete secondChildHolder;
	}
}
		
void EditorHolder::Resize(Number width, Number height) {

	if(headerBg->visible) {
		headerBg->Resize(width, 30);	
		hSplitButton->setPosition(width - 30, 7);
		vSplitButton->setPosition(width - 55, 7);
		if(parentHolder) {
			mergeSplitButton->visible = true;
			mergeSplitButton->enabled = true;
			mergeSplitButton->setPosition(width - 80, 7);
			currentFileSelector->Resize(width - 125, currentFileSelector->getHeight());
		} else {
			mergeSplitButton->visible = false;
			mergeSplitButton->enabled = false;			
			currentFileSelector->Resize(width - 100, currentFileSelector->getHeight());			
		}
	}
		
	
	if(currentEditor) {
		currentEditor->setPosition(0, 30);
		currentEditor->Resize(width, height-30);
	}
	
	if(vSizer) {
		vSizer->Resize(width, height);
	}
	if(hSizer) {
		hSizer->Resize(width, height);
	}
	
	UIElement::Resize(width, height);
}

PolycodeProjectTab::PolycodeProjectTab(String caption, PolycodeProject *project, PolycodeEditorManager *editorManager) : UIElement() {

	tabName = caption;
	
	this->editorManager = editorManager;

	editorHolder = new EditorHolder(project, editorManager, NULL);
	editorHolder->setActive(true);
	editorHolder->addEventListener(this, UIEvent::CLOSE_EVENT);
	
	mainSizer = new UIHSizer(100,100,200,true);
	mainSizer->setMinimumSize(100);
	addChild(mainSizer);					
	projectBrowser = new PolycodeProjectBrowser(project);
	mainSizer->addLeftChild(projectBrowser);
	mainSizer->addRightChild(editorHolder);

	active = false;

	projectBrowser->treeContainer->getRootNode()->addEventListener(this, UITreeEvent::DRAG_START_EVENT);
}

void PolycodeProjectTab::setActive(bool val) {
	active = val;
    editorHolder->activateEditor(val);
    
	if(!active) {
		projectBrowser->removeAllHandlers();
    }
}

bool PolycodeProjectTab::isActive() {
	return active;
}

void PolycodeProjectTab::handleEvent(Event *event) {
	if(event->getDispatcher() == editorHolder && event->getEventCode() == UIEvent::CLOSE_EVENT) {
		dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
	}
	UIElement::handleEvent(event);
}

String PolycodeProjectTab::getTabName() {
	return tabName;
}

ObjectEntry *PolycodeProjectTab::getTabConfig() {
	ObjectEntry *configEntry = new ObjectEntry();
	configEntry->name = "tab";
	
	configEntry->addChild(projectBrowser->getBrowserConfig());
	
	configEntry->addChild("tab_name", tabName);	
	configEntry->addChild("tab_active", isActive());
	
	configEntry->addChild(editorHolder->getEditorHolderConfig());
	return configEntry;
}

void PolycodeProjectTab::applyTabConfig(ObjectEntry *tabEntry) {
	ObjectEntry *browserEntry = (*tabEntry)["project_browser"];
	if(browserEntry) {
		ObjectEntry *browserWidthEntry = (*browserEntry)["width"];
		if(browserWidthEntry) {
			mainSizer->setMainWidth(browserWidthEntry->NumberVal);
		}
		projectBrowser->applyBrowserConfig(browserEntry);
	}
	
	ObjectEntry *editorHolderEntry = (*tabEntry)["editor_holder"];
	if(editorHolderEntry) {
		editorHolder->applyConfig(editorHolderEntry);
	}
}

void PolycodeProjectTab::setTabName(String newName) {
	tabName = newName;
}

void PolycodeProjectTab::Resize(Number width, Number height) {
	mainSizer->Resize(width, height);
	UIElement::Resize(width, height);
}

EditorHolder *PolycodeProjectTab::getEditorHolder() {
	return editorHolder;
}

void PolycodeProjectTab::showEditor(PolycodeEditor *editor) {
    if(!activeEditorHolder) {
        return;
    }
    
	if(activeEditorHolder->getEditor()) {
		activeEditorHolder->setEditor(NULL);
	}
	
	activeEditorHolder->setEditor(editor);
	editor->Activate();
	Resize(getWidth(), getHeight());
}

PolycodeProjectBrowser *PolycodeProjectTab::getProjectBrowser() {
	return projectBrowser;
}

PolycodeProjectTab::~PolycodeProjectTab() {

}

PolycodeTabButton::PolycodeTabButton(PolycodeProjectTab *tab) : UIElement() {
	this->tab = tab;
	bgRect = new UIImage("main/tab_bg.png", 150,30);
	addChild(bgRect);
	bgRect->processInputEvents = true;
	processInputEvents = true;
	bgRect->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
	setWidth(150);
	setHeight(30);
	
	tabLabel = new UILabel(tab->getTabName().toUpperCase(), 16, "section");
    tabLabel->setColor(0.0, 0.0, 0.0, 1.0);
	tabLabel->setPosition(getWidth()-tabLabel->getWidth()-10.0, ((getHeight()-tabLabel->getHeight())/2.0) - 3.0);
	addChild(tabLabel);
	
	closeButton = new UIImageButton("main/tab_close_button.png", 1.0, 18, 18);
	closeButton->setPosition(4.0, floor((30.0 - closeButton->getHeight()) / 2.0));
	addChild(closeButton);
	closeButton->blockMouseInput = true;
	closeButton->addEventListener(this, UIEvent::CLICK_EVENT);
}

void PolycodeTabButton::updateLabel() {
	tabLabel->setText(tab->getTabName().toUpperCase());
	tabLabel->setPosition(getWidth()-tabLabel->getWidth()-10.0, ((getHeight()-tabLabel->getHeight())/2.0) - 3.0);
}

void PolycodeTabButton::handleEvent(Event *event) {

	if(event->getDispatcher() == renamePopup) {
		renamePopup->removeAllHandlersForListener(this);
		tabLabel->setText(renamePopup->getValue().toUpperCase());
		tab->setTabName(renamePopup->getValue());
		tabLabel->setPosition(getWidth()-tabLabel->getWidth()-10.0, ((getHeight()-tabLabel->getHeight())/2.0) - 3.0);
	}

	if(event->getDispatcher() == menu) {
		if(menu->getSelectedItem()->_id == "close_tab") {
			dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
		} else if(menu->getSelectedItem()->_id == "rename_tab") {
			renamePopup = globalFrame->showTextInput("Enter new tab name.", "rename_tab", tab->getTabName());
			renamePopup->addEventListener(this, UIEvent::OK_EVENT);
		}
	}
	
	if(event->getDispatcher() == closeButton) {
		dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);		
	}
	
	if(event->getDispatcher() == bgRect) {
		if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
			dispatchEvent(new Event(), Event::SELECT_EVENT);
			InputEvent *inputEvent = (InputEvent*) event;
			if(inputEvent->getMouseButton() == CoreInput::MOUSE_BUTTON2) {
				menu = globalMenu->showMenuAtMouse(120);
				menu->addOption("Rename tab", "rename_tab");
				menu->addOption("Close tab", "close_tab");
				menu->addEventListener(this, UIEvent::OK_EVENT);
			}
		}		
	}
	UIElement::handleEvent(event);
}

void PolycodeTabButton::setActive(bool val) {
	if(val) {
		bgRect->color.a = 0.4;
	} else {
		bgRect->color.a = 0.2;	
	}
}

PolycodeProjectTab *PolycodeTabButton::getTab() {
	return tab;
}

PolycodeTabButton::~PolycodeTabButton() {

}

PolycodeProjectFrame::PolycodeProjectFrame(PolycodeProject *project, PolycodeEditorManager *editorManager) {
	tabToClose = NULL;
	this->editorManager = editorManager;
	this->project = project;
	lastActiveEditorHolder = NULL;
	tabButtonAnchor = new UIElement();
	addChild(tabButtonAnchor);
	tabButtonAnchor->setPosition(400, -30);
	
	activeTab = NULL;
	
	newTabButton = new UIImageButton("main/new_tab_button.png", 1.0, 27, 26);
	tabButtonAnchor->addChild(newTabButton);
	newTabButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addNewTab("Default");
}

void PolycodeProjectFrame::showNextTab() {
	for(int i=0; i < tabs.size(); i++) {
		if(tabs[i] == activeTab) {
			if(i < tabs.size()-1) {
				showTab(tabs[i+1]);
				return;				
			} else {
				showTab(tabs[0]);	
				return;				
			}
		}
	}
}

void PolycodeProjectFrame::showPreviousTab() {
	for(int i=0; i < tabs.size(); i++) {
		if(tabs[i] == activeTab) {
			if(i > 0) {
				showTab(tabs[i-1]);
				return;				
			} else {
				showTab(tabs[tabs.size()-1]);
				return;
			}
		}
	}
}

PolycodeProjectTab *PolycodeProjectFrame::getTabAtIndex(unsigned int index) {
	return tabs[index];
}

unsigned int PolycodeProjectFrame::getNumTabs() {
	return tabs.size();
}

PolycodeProjectTab *PolycodeProjectFrame::getActiveTab() {
	return activeTab;
}

PolycodeProjectTab *PolycodeProjectFrame::addNewTab(String caption) {
	PolycodeProjectTab *newTab = new PolycodeProjectTab(caption, project, editorManager);
	tabs.push_back(newTab);
	
	PolycodeTabButton *newTabButton = new PolycodeTabButton(newTab);
	tabButtonAnchor->addChild(newTabButton);
	tabButtons.push_back(newTabButton);
	newTabButton->addEventListener(this, Event::SELECT_EVENT);
	newTabButton->addEventListener(this, UIEvent::CLOSE_EVENT);
	showTab(newTab);
	return newTab;
}

void PolycodeProjectFrame::Update() {
	if(tabToClose) {
	
		// can't close the last tab
		if(tabs.size() == 1) {
			tabToClose = NULL;
			return;
		}
		
		for(int i=0; i < tabs.size(); i++) {
			if(tabs[i] == tabToClose) {
				tabs.erase(tabs.begin()+i);
				break;
			}
		}
		
		for(int i=0; i < tabButtons.size(); i++) {
			if(tabButtons[i]->getTab() == tabToClose) {
				tabButtonAnchor->removeChild(tabButtons[i]);
				delete tabButtons[i];
				tabButtons.erase(tabButtons.begin()+i);
				break;
			}
		}
		
		if(tabToClose == activeTab) {
			showTab(tabs[0]);
		}
		
		delete tabToClose;
		tabToClose = NULL;
		restructTabs();
	}
}

void PolycodeProjectFrame::closeTab(PolycodeProjectTab *tab) {
	tabToClose = tab;
}

void PolycodeProjectFrame::showTab(PolycodeProjectTab *tab) {
	if(activeTab) {
		activeTab->setActive(false);
		activeTab->removeAllHandlersForListener(this);
		removeChild(activeTab);
	}

	addChild(tab);
	tab->addEventListener(this, UIEvent::CLOSE_EVENT);
	tab->setActive(true);
	tab->getEditorHolder()->setActive(true);
	tab->Resize(getWidth(), getHeight());
	activeTab = tab;
	restructTabs();
	dispatchEvent(new UIEvent(), Event::CHANGE_EVENT);			
}

void PolycodeProjectFrame::restructTabs() {
	int i;
	for(i=0; i < tabButtons.size(); i++) {
		tabButtons[i]->setPosition(i * 152.0, 0.0);
		tabButtons[i]->setActive(tabButtons[i]->getTab()->isActive());		
		tabButtons[i]->updateLabel();
	}
	newTabButton->setPosition((i * 152) + 3, 0.0);
}

ObjectEntry *PolycodeProjectFrame::getFrameConfig() {
	ObjectEntry *configEntry = new ObjectEntry();
	configEntry->name = "frame";
	
	ObjectEntry *tabsEntry = configEntry->addChild("tabs");
	
	for(int i=0; i < tabs.size(); i++) {
		tabsEntry->addChild(tabs[i]->getTabConfig());
	}
	return configEntry;
}

void PolycodeProjectFrame::handleEvent(Event *event) {
	for(int i=0; i < tabs.size(); i++) {
		if(event->getDispatcher() == tabs[i] && event->getEventCode() == UIEvent::CLOSE_EVENT) {
			dispatchEvent(new UIEvent, UIEvent::CLOSE_EVENT);
			return;
		 } 
	}
	
	if(event->getDispatcher() == newTabButton) {
		addNewTab();
	} else {
		for(int i=0; i < tabButtons.size(); i++) {
			if(event->getDispatcher() == tabButtons[i]) {
				if(event->getEventCode() == Event::SELECT_EVENT) {
					showTab(tabButtons[i]->getTab());
					break;
				} else 	if(event->getEventCode() == UIEvent::CLOSE_EVENT) {
					closeTab(tabButtons[i]->getTab());
					break;
				} else 	if(event->getEventCode() == UIEvent::CHANGE_EVENT) {
					dispatchEvent(new UIEvent(), UIEvent::CHANGE_EVENT);
					break;
				}
			}
		}
	}
}

PolycodeProject *PolycodeProjectFrame::getProject() {
	return project;
}

void PolycodeProjectFrame::Resize(Number width, Number height) {
	activeTab->Resize(width, height);
	UIElement::Resize(width, height);
}

PolycodeProjectFrame::~PolycodeProjectFrame() {

}


PolycodeFrame::PolycodeFrame(PolycodeEditorManager *editorManager) : UIElement() {

	this->editorManager = editorManager;

	activeProjectFrame = NULL;
	consoleSize = 200;
	
	globalFrame = this;
	processInputEvents = true;
	willHideModal = false;
	showingConsole = true;
	modalChild = NULL;
	
	welcomeEntity = new Entity();
	welcomeEntity->processInputEvents = true;
	addChild(welcomeEntity);
	welcomeImage = new UIImage("main/welcome.png", 759, 207);
	welcomeEntity->addChild(welcomeImage);
	welcomeEntity->snapToPixels = true;
	
	newProjectButton = new UIButton("Create A New Project!", 220);	
	newProjectButton->setPosition(260,120);
	newProjectButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	examplesButton = new UIButton("Browse Example Projects!", 220);	
	examplesButton->setPosition(490,120);
	examplesButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	welcomeEntity->addChild(newProjectButton);
	welcomeEntity->addChild(examplesButton);
	
	
	topBarBg = new UIRect(2,2);
	topBarBg->setColorInt(21, 18, 17, 255);
	topBarBg->setAnchorPoint(-1.0, -1.0, 0.0);
	topBarBg->processInputEvents = true;
	topBarBg->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	topBarBg->blockMouseInput = true;
	addChild(topBarBg);

	consoleSizer = new UIVSizer(100,100,200, false);
	console = new PolycodeConsole();	
	consoleSizer->addBottomChild(console);
	addChild(consoleSizer);
	consoleSizer->setPosition(0.0, 45);
	
	logo = new UIImage("main/barLogo.png", 38, 38);
	addChild(logo);
	
	playButton = new UIImageButton("main/play_button.png", 1.0, 32, 32);
	addChild(playButton);
	playButton->setPosition(10,5);

	stopButton = new UIImageButton("main/stop_button.png", 1.0, 32, 32);
	addChild(stopButton);
	stopButton->setPosition(10,5);

	currentProjectSelector = new UIComboBox(globalMenu, 300);
	currentProjectSelector->addEventListener(this, UIEvent::CHANGE_EVENT);
	addChild(currentProjectSelector);
	currentProjectSelector->setPosition(60, 10);
	
	resizer = new UIImage("main/corner_resize.png", 14, 14);
	addChild(resizer);
	resizer->setColor(0,0,0,0.4);
	
	modalBlocker = new UIRect(10,10);
    modalBlocker->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
	modalBlocker->setColor(0,0,0,0.4);
	modalBlocker->setAnchorPoint(-1.0, -1.0, 0.0);
	modalBlocker->enabled = false;	
	modalBlocker->blockMouseInput = true;
	modalBlocker->processInputEvents = true;
	addChild(modalBlocker);
	
	assetBrowser = new AssetBrowser();
	assetBrowser->visible = false;	
	
	newProjectWindow = new NewProjectWindow();
	newProjectWindow->visible = false;
	
	exampleBrowserWindow = new ExampleBrowserWindow();
	exampleBrowserWindow->visible = false;

	settingsWindow = new SettingsWindow();
	settingsWindow->visible = false;
	
	newFileWindow = new NewFileWindow();
	newFileWindow->visible = false;
	
	exportProjectWindow = new ExportProjectWindow();
	exportProjectWindow->visible = false;
	
	textInputPopup = new TextInputPopup();
	textInputPopup->visible = false;
	
	yesNoPopup = new YesNoPopup();
	yesNoPopup->visible = false;
    
    messagePopup = new MessagePopup();
    messagePopup->visible = false;
	
	yesNoCancelPopup = new YesNoCancelPopup();
	yesNoCancelPopup->visible = false;
	
	
	aboutWindow = new UIWindow("", 800, 440);
	aboutWindow->closeOnEscape = true;
	UIImage *aboutImage = new UIImage("main/about.png", 321, 122);
	aboutWindow->addChild(aboutImage);
	aboutImage->setPosition(20, 40);
	aboutWindow->visible = false;
	aboutOKButton = new UIButton("OK", 100);
	aboutWindow->addChild(aboutOKButton);
	aboutOKButton->setPosition(700, 420);
	aboutOKButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
    String info1Text = "Polycode is developed by:\n\nProject lead:\nIvan Safrin\n\nTop project contributors in order of commits:\nCameron Hart, Andi McClure, samiamwork, Christian Bielert,\nChristopher Reed, TheCosmotect, Danny Warren, Paul Smith,\nDevin Stone, Jon Kristinsson, Henry Maddocks,\nJohan Klokkhammer Helsing, Chris Ledet, Per Bodin, Quinlan P.,\nLee-R, Guillaume Papin, Remi Gillig, ZenX2,\nMatt Tuttle, Alejandro Cámara, Jake Scott, tastymorsel";
    
    UIMultilineLabel *info1 = new UIMultilineLabel(info1Text, 12, 5);
    aboutWindow->addChild(info1);
    info1->setPosition(40, 200);
    
    String info2Text = "Polycode uses the following open-source libraries:\n\nAssimp (BSD license)\nBox2D (zlib license)\nBullet Physics (zlib license)\nFreetype (Freetype license)\nlibpng (libpng license)\nLua (MIT license),\nOggVorbis (BSD license)\nPhysFS (zlib license)\ntinyXML (zlib license)\nSDL (on Linux only) (zlib license)\n\nPolycode itself is distributed\nunder the MIT license.\n\n\n\nThank you for using Polycode!";
    
    UIMultilineLabel *info2 = new UIMultilineLabel(info2Text, 12, 5);
    aboutWindow->addChild(info2);
    info2->setPosition(450, 40);

	UILabel *versionLabel = new UILabel("version "POLYCODE_VERSION_STRING, 12, "mono");
	aboutWindow->addChild(versionLabel);
	versionLabel->setPosition(40, 430);
	versionLabel->color.a = 1.0;
	
	assetImporterWindow = new AssetImporterWindow();
	
		
	isDragging  = false;
	dragLabel = new UILabel("NONE", 11, "sans");
	dragLabel->setPosition(0,-15);
	
	dragEntity = new Entity();
	dragEntity->addChild(dragLabel);
	addChild(dragEntity);
	dragEntity->visible = false;	
	
		
	CoreServices::getInstance()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	CoreServices::getInstance()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	CoreServices::getInstance()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	
	curveEditor = new CurveEditor();
	addChild(curveEditor);
	curveEditor->setPosition(200,100);
	curveEditor->visible = false;
	curveEditor->enabled = false;
	
		
	globalColorPicker = new UIColorPicker();
	globalColorPicker->setPosition(300,300);
    globalColorPicker->setContinuous(false);
	addChild(globalColorPicker);

	modalRoot = new UIElement();
	addChild(modalRoot);
	
	fileDialogBlocker = new UIRect(100, 100);
	fileDialogBlocker->setAnchorPoint(-1.0, -1.0, 0.0);
	addChild(fileDialogBlocker);
	fileDialogBlocker->setColor(0.0, 0.0, 0.0, 0.5);
	fileDialogBlocker->processInputEvents = true;
	fileDialogBlocker->blockMouseInput = true;
	fileDialogBlocker->visible = false;
	fileDialogBlocker->enabled = false;

	fileBrowserRoot = new UIElement();
	addChild(fileBrowserRoot);

	fileDialog = NULL;
	
	displayFilePathInSelector = false;
}

void PolycodeFrame::showFileBrowser(String baseDir, bool foldersOnly, std::vector<String> extensions, bool allowMultiple) {
	
	if(fileDialog)
		delete fileDialog;

	fileDialog = new UIFileDialog(baseDir, foldersOnly, extensions, allowMultiple);
	fileDialog->addEventListener(this, UIEvent::CANCEL_EVENT);
	fileDialog->addEventListener(this, UIEvent::OK_EVENT);
	fileBrowserRoot->addChild(fileDialog);
	fileDialog->setPosition(100,100);
	
	fileDialogBlocker->visible = true;
	fileDialogBlocker->enabled = true;
}

void PolycodeFrame::showCurveEditor() {
	curveEditor->visible = true;
	curveEditor->enabled = true;
}

void PolycodeFrame::showModal(UIWindow *modalChild) {
	modalBlocker->enabled = true;
	
	focusChild(NULL);
	
	this->modalChild = modalChild;
	modalRoot->addChild(modalChild);
	modalChild->showWindow();
	modalChild->addEventListener(this, UIEvent::CLOSE_EVENT);
	Resize(getWidth(), getHeight());
	
    modalChild->focusSelf();
    
	CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_ARROW);	
}

void PolycodeFrame::hideModal() {
	if(modalChild) {
		modalRoot->removeChild(modalChild);
		assetBrowser->removeAllHandlers();
		modalChild->hideWindow(); 
		modalChild = NULL;
	}
	modalBlocker->enabled = false;		
}

bool PolycodeFrame::isShowingConsole() {
	return showingConsole;
}
	
void PolycodeFrame::showConsole() {
	if(!showingConsole)
		toggleConsole();
}

void PolycodeFrame::hideConsole() {
	if(showingConsole)
		toggleConsole();
}

void PolycodeFrame::toggleConsole() {
	if(showingConsole) {
		consoleSize = consoleSizer->getMainHeight();
		consoleSizer->setMainHeight(0);
		console->visible = false;
		console->enabled = false;
	} else {
		consoleSizer->setMainHeight(consoleSize);	
		console->visible = true;
		console->enabled = true;		
	}
	showingConsole = !showingConsole;
}

Number PolycodeFrame::getConsoleSize() {
	if(showingConsole) {
		return consoleSizer->getMainHeight();
	} else {
		return consoleSize;
	}
}

void PolycodeFrame::Update() {
	if(willHideModal) {
		hideModal();
		willHideModal = false;
	}
}

TextInputPopup * PolycodeFrame::showTextInput(String caption, String action, String value) {
	textInputPopup->action = action;
	textInputPopup->setCaption(caption);
	textInputPopup->setValue(value);
	showModal(textInputPopup);
	return textInputPopup;
}

void PolycodeFrame::showAssetBrowserForPools(std::vector<ResourcePool*> pools, int resourceType) {
	if(!projectManager->getActiveProject()) {
		return;
	}
	assetBrowser->setResourcePools(pools, resourceType);
    assetBrowser->setBrowseMode(AssetBrowser::BROWSE_MODE_RESOURCES);
	showModal(assetBrowser);
    
}

void PolycodeFrame::showAssetBrowser(std::vector<String> extensions) {
	if(!projectManager->getActiveProject()) {
		return;
	}
	assetBrowser->setProject(projectManager->getActiveProject());
	assetBrowser->setExtensions(extensions);
   assetBrowser->setBrowseMode(AssetBrowser::BROWSE_MODE_FILES);
	showModal(assetBrowser);
}

void PolycodeFrame::handleEvent(Event *event) {

	if(event->getDispatcher() == activeProjectFrame) {
		if(event->getEventCode() == Event::CHANGE_EVENT) {
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}

	if(event->getDispatcher() == activeProjectFrame) {
		if(event->getEventCode() == UIEvent::CLOSE_EVENT) {
			dispatchEvent(new UIEvent(), UIEvent::CLOSE_EVENT);
		}
	}

	if(event->getDispatcher() == currentProjectSelector) {
		PolycodeProject *project = (PolycodeProject*)currentProjectSelector->getSelectedItem()->data;
		projectManager->setActiveProject(project);
	}
		
	if(event->getDispatcher() == editorManager) {
		updateFileSelector();
	}
	
	if(event->getDispatcher() == topBarBg) {
		CoreServices::getInstance()->getCore()->setCursor(Core::CURSOR_ARROW);	
	}
	
	if(event->getDispatcher() == projectManager) {
		currentProjectSelector->clearItems();
		for(int i=0; i < projectManager->getProjectCount(); i++) {
			PolycodeProject *project = projectManager->getProjectByIndex(i);
			currentProjectSelector->addComboItem(project->getProjectName(), (void*) project);
			if(projectManager->getActiveProject() == project) {
				currentProjectSelector->setSelectedIndex(i, true);
			}
		}
	}
	
	if(event->getDispatcher() == aboutOKButton && event->getEventType() == "UIEvent") {
		hideModal();
	}
	
	if(event->getDispatcher() == fileDialog && event->getEventType() == "UIEvent") {
		fileBrowserRoot->removeChild(fileDialog);
		fileDialogBlocker->visible = false;
		fileDialogBlocker->enabled = false;
	}

	if(event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput()) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEUP:
				if(isDragging) {
				/*
					if(editorHolder->currentEditor) {
						InputEvent *inputEvent = (InputEvent*) event;						
						Number posX = inputEvent->mousePosition.x;
						Number posY = inputEvent->mousePosition.y;			
						editorHolder->currentEditor->handleDroppedFile(draggedFile, posX, posY);
					}
				*/
				}
				isDragging = false;
				dragEntity->visible = false;
			break;
			case InputEvent::EVENT_MOUSEMOVE:			
				if(isDragging) {
					//dragEntity->setPosition(((InputEvent*)event)->mousePosition);
				}
			break;
			// TODO: add in key combos to switch editors in reverse order
			case InputEvent::EVENT_KEYDOWN:
				CoreInput *input = CoreServices::getInstance()->getCore()->getInput();
				
				if (input->getKeyState(KEY_LSUPER) || input->getKeyState(KEY_RSUPER)) {
					InputEvent *inEv = (InputEvent*)event;
					// commenting this out for now until issue with KEY_BACKQUOTE is figured out
					/*if (inEv->getKey() == KEY_BACKQUOTE) {
						showNextEditor();
					}*/
					if (inEv->getKey() == KEY_SLASH) {
						displayFilePathInSelector = (displayFilePathInSelector ? false : true);
						updateFileSelector();
					}
				} else if (input->getKeyState(KEY_LCTRL) || input->getKeyState(KEY_RCTRL)) {
//					InputEvent *inEv = (InputEvent*)event;
//					if (inEv->getKey() == KEY_TAB) {
//						showNextEditor();
//					} else if (inEv->getKey() == KEY_SLASH) {
//						displayFilePathInSelector = (displayFilePathInSelector ? false : true);
//						updateFileSelector();
//					}
				}
			break;
				
		}
	}

/*
	if(event->getDispatcher() == projectBrowser->treeContainer->getRootNode()) {
		switch (event->getEventCode()) {
			case UITreeEvent::DRAG_START_EVENT:
			{
				UITreeEvent *treeEvent = (UITreeEvent*) event;
				BrowserUserData *data = (BrowserUserData*)treeEvent->selection->getUserData();
				draggedFile = data->fileEntry;
				dragLabel->setText(data->fileEntry.name);
				dragEntity->visible = true;
				isDragging = true;
//				printf("START DRAG: %s\n", data->fileEntry.name.c_str());
			}
			break;
		}
	}
*/

	if(event->getDispatcher() == modalChild) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLOSE_EVENT) {
			willHideModal = true;
		}
	} else {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT && event->getDispatcher() == newProjectButton) {

			showModal(newProjectWindow);
			newProjectWindow->ResetForm();
		}	
		
	if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT && event->getDispatcher() == examplesButton) {

			showModal(exampleBrowserWindow);
			newProjectWindow->ResetForm();
		}			
		
	}
}

PolycodeProjectBrowser *PolycodeFrame::getCurrentProjectBrowser() {
	if(activeProjectFrame) {
		return activeProjectFrame->getActiveTab()->getProjectBrowser();
	} else {
		return NULL;
	}
}

void PolycodeFrame::Resize(int x, int y) {	
		
	welcomeEntity->setPosition((x-welcomeImage->getWidth()) / 2,
		(y-welcomeImage->getHeight()) / 2); 
	
	topBarBg->Resize(x, 45);
	logo->setPosition(x-logo->getWidth()-2, 2);
	resizer->setPosition(x-resizer->getWidth()-1, y-resizer->getHeight()-1);	
	consoleSizer->Resize(x,y-45);	
	
	modalBlocker->Resize(x, y);
	fileDialogBlocker->Resize(x, y);
			
	if(this->modalChild) {
		modalChild->setPosition((x-modalChild->getWidth())/2.0f, (y-modalChild->getHeight())/2.0f);
	}
	
	UIElement::Resize(x, y);
}

ObjectEntry *PolycodeFrame::getFrameConfigForProject(PolycodeProject *project) {
	for(int i=0; i < projectFrames.size(); i++) {
		if(projectFrames[i]->getProject() == project) {
			return projectFrames[i]->getFrameConfig();
		}
	}
	return NULL;
}

void PolycodeFrame::removeProjectFrame(PolycodeProject *project) {
    //TODO: implement. this is being called from PolycodeIDEApp::doCloseProject()
}

PolycodeProjectFrame *PolycodeFrame::getActiveProjectFrame() {
	return activeProjectFrame;
}

PolycodeFrame::~PolycodeFrame() {
	
}

UIVSizer *PolycodeFrame::getConsoleSizer() {
	return consoleSizer;
}

PolycodeProjectFrame *PolycodeFrame::createProjectFrame(PolycodeProject *project) {
	PolycodeProjectFrame *newProjectFrame = new PolycodeProjectFrame(project, editorManager);
	projectFrames.push_back(newProjectFrame);	
	switchToProjectFrame(newProjectFrame);
	return newProjectFrame;
}

void PolycodeFrame::switchToProjectFrame(PolycodeProjectFrame *projectFrame) {
	if(projectFrame == activeProjectFrame) {
		return;
	}
	if(activeProjectFrame) {
		consoleSizer->removeTopChild();
		if(editorManager->getCurrentEditor()) {
			activeProjectFrame->lastActiveEditorHolder = editorManager->getCurrentEditor()->getEditorHolder();
		}
		activeProjectFrame->removeAllHandlersForListener(this);
	} 
	activeProjectFrame = projectFrame;
	consoleSizer->addTopChild(activeProjectFrame);
	activeProjectFrame->getActiveTab()->getEditorHolder()->setActive(true);
	activeProjectFrame->addEventListener(this, UIEvent::CLOSE_EVENT);
	activeProjectFrame->addEventListener(this, Event::CHANGE_EVENT);
	Resize(getWidth(), getHeight());
}

PolycodeProjectFrame *PolycodeFrame::getProjectFrame(PolycodeProject *project) {
	for(int i=0; i < projectFrames.size(); i++) {
		if(projectFrames[i]->getProject() == project) {
			return projectFrames[i];
		}
	}
	return NULL;
}

void PolycodeFrame::updateFileSelector() {
	if(activeProjectFrame)  {
		activeProjectFrame->getActiveTab()->getEditorHolder()->updateFileSelector();
	}
}
