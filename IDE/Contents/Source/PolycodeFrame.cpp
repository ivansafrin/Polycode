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

EditPoint::EditPoint(BezierPoint *point, unsigned int type) : ScreenEntity() {
	this->point = point;
	this->type = type;
	processInputEvents = true;

	draggingPoint = NULL;
	dragging = false;

	controlHandle1 = new ScreenImage("Images/bezier_handle.png");
	controlHandle1->setPositionMode(ScreenEntity::POSITION_CENTER);

	controlHandle1->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	controlHandle1->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	controlHandle1->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	controlHandle1->processInputEvents = true;
	controlHandle1->setWidth(30);
	controlHandle1->setHeight(30);

	addChild(controlHandle1);

	controlHandle2 = new ScreenImage("Images/bezier_handle.png");
	controlHandle2->setPositionMode(ScreenEntity::POSITION_CENTER);
	controlHandle2->processInputEvents = true;

	controlHandle2->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	controlHandle2->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	controlHandle2->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	controlHandle2->setWidth(30);
	controlHandle2->setHeight(30);

	addChild(controlHandle2);


	pointHandle = new ScreenImage("Images/bezier_point.png");
	pointHandle->processInputEvents = true;
	pointHandle->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	pointHandle->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	pointHandle->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);	
	pointHandle->setPositionMode(ScreenEntity::POSITION_CENTER);
	pointHandle->setWidth(30);
	pointHandle->setHeight(30);


	if(type == TYPE_START_POINT) {
		controlHandle1->visible = false;
		controlHandle1->enabled = false;
		connectorLine1 = NULL;
	} else {
		connectorLine1 = new ScreenLine(pointHandle, controlHandle1);
		addChild(connectorLine1);
		connectorLine1->setColorInt(39, 212, 255, 128);
		connectorLine1->setLineWidth(2.0);
		connectorLine1->lineSmooth = true;
	}


	if(type == TYPE_END_POINT) {
		controlHandle2->visible = false;
		controlHandle2->enabled = false;
		connectorLine2 = NULL;
	} else {
		connectorLine2 = new ScreenLine(pointHandle, controlHandle2);
		addChild(connectorLine2);
		connectorLine2->setColorInt(39, 212, 255, 128);
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

	point->p1.x = controlHandle1->getPosition2D().x/610;
	point->p1.y = controlHandle1->getPosition2D().y/-254;

	point->p2.x = pointHandle->getPosition2D().x/610;
	point->p2.y = pointHandle->getPosition2D().y/-254;

	point->p3.x = controlHandle2->getPosition2D().x/610;
	point->p3.y = controlHandle2->getPosition2D().y/-254;

}

void EditPoint::handleEvent(Event *event) {

	if(event->getDispatcher() == CoreServices::getInstance()->getCore()->getInput()) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEMOVE:
				if(dragging && draggingPoint) {
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
			break;
		}
	}

	if(event->getDispatcher() == pointHandle || event->getDispatcher() == controlHandle1 || event->getDispatcher() == controlHandle2) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				if(mode == CurveEditor::MODE_SELECT) {
					draggingPoint = (ScreenImage*)event->getDispatcher();
					dragging = true;
					basePosition = CoreServices::getInstance()->getCore()->getInput()->getMousePosition(); 
					basePointPosition = draggingPoint->getPosition2D();

					baseControl1 = controlHandle1->getPosition2D();
					baseControl2 = controlHandle2->getPosition2D();
				}

				if(mode == CurveEditor::MODE_REMOVE && type == TYPE_POINT) {
					dispatchEvent(new Event(), Event::CANCEL_EVENT);
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

void EditPoint::limitPoint(ScreenImage *point) {
		if(point->position.x < 0.0)
			point->position.x = 0.0;
		if(point->position.x > 610.0)
			point->position.x = 610.0;

		if(point->position.y > 0.0)
			point->position.y = 0.0;
		if(point->position.y < -254.0)
			point->position.y = -254.0;

}

void EditPoint::updatePosition() {
	pointHandle->setPosition(610.0*point->p2.x, -254*point->p2.y, 0.0);
	controlHandle1->setPosition(610.0*point->p1.x, -254*point->p1.y, 0.0);
	controlHandle2->setPosition(610.0*point->p3.x, -254*point->p3.y, 0.0);
}

EditPoint::~EditPoint() {

}

EditCurve::EditCurve(BezierCurve *targetCurve, Color curveColor) : UIElement() {

	this->targetCurve = targetCurve;

	poly = new Polycode::Polygon();

	for(int i=0; i < CURVE_SIZE; i++) {
		poly->addVertex(0.0, 0.0, 0.0);
	}

	visMesh = new ScreenMesh(Mesh::LINE_STRIP_MESH);
	visMesh->getMesh()->addPolygon(poly);

	visMesh->lineSmooth = true;
	visMesh->lineWidth = 2.0;

	addChild(visMesh);
	visMesh->setPosition(0, 254);
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
		point->setPosition(0, 254);
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
	visMesh->color.a = 0.7;	
}

void EditCurve::Deactivate() {
	pointsBase->visible = false;
	pointsBase->enabled = false;
	visMesh->color.a = 0.4;	
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
	targetCurve->rebuildBuffers();

	Number interval = 610.0/CURVE_SIZE;
	Number normInterval = 1.0/CURVE_SIZE;

	interval += interval/CURVE_SIZE;
	normInterval += normInterval/CURVE_SIZE;

	for(int i=0; i < CURVE_SIZE; i++) {
		poly->getVertex(i)->set(targetCurve->getPointAt(normInterval * i).x * 610, targetCurve->getPointAt(normInterval * i).y * -254.0, 0.0);
	}

	visMesh->getMesh()->arrayDirtyMap[RenderDataArray::VERTEX_DATA_ARRAY] = true;
}

EditCurve::~EditCurve() {

}

CurveEditor::CurveEditor() : UIWindow("", 750, 300) {

	closeOnEscape = true;

	bg = new ScreenImage("Images/curve_editor_bg.png");
	addChild(bg);
	bg->setPosition(160, 63);
	bg->processInputEvents = true;
	bg->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);

	selectorImage = new ScreenImage("Images/ScreenEditor/selector.png");
	selectorImage->setColor(0.0, 0.0, 0.0, 0.3);
	addChild(selectorImage);

	selectButton = new UIImageButton("Images/ScreenEditor/arrow.png");
	addChild(selectButton);
	selectButton->addEventListener(this, UIEvent::CLICK_EVENT);
	selectButton->setPosition(170, 33);

	addButton = new UIImageButton("Images/arrow_add.png");
	addChild(addButton);
	addButton->addEventListener(this, UIEvent::CLICK_EVENT);
	addButton->setPosition(170 + 32, 33);

	removeButton = new UIImageButton("Images/arrow_remove.png");
	addChild(removeButton);
	removeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	removeButton->setPosition(170 + 64, 33);

	selectorImage->setPosition(selectButton->getPosition().x - 4, selectButton->getPosition().y - 4);

	selectedCurve = NULL;

	setMode(0);

	treeContainer = new UITreeContainer("boxIcon.png", L"Curves", 145, 280);
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

	UITree *newNode = treeContainer->getRootNode()->addTreeChild("Images/curve_icon.png", name);
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

	if(mode == MODE_ADD && event->getDispatcher() == bg) {
		if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
			InputEvent *inputEvent = (InputEvent*)event;
			if(selectedCurve) {
				Vector2 pos = inputEvent->mousePosition;
				pos.x = pos.x/610.0;
				pos.y = 1.0-(pos.y/254.0);

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

	if(event->getDispatcher() == selectButton) {
		selectorImage->setPosition(selectButton->getPosition().x - 4, selectButton->getPosition().y - 4);
		setMode(0);
	}

	if(event->getDispatcher() == addButton) {
		selectorImage->setPosition(addButton->getPosition().x - 4, addButton->getPosition().y - 4);
		setMode(1);
	}

	if(event->getDispatcher() == removeButton) {
		selectorImage->setPosition(removeButton->getPosition().x - 4, removeButton->getPosition().y - 4);
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
			}
		}
	}

	UIWindow::handleEvent(event);
}

CurveEditor::~CurveEditor() {

}

EditorHolder::EditorHolder() : UIElement() {
	currentEditor = NULL;
}

EditorHolder::~EditorHolder() {

}

void EditorHolder::Resize(Number width, Number height) {
	if(currentEditor) {
		currentEditor->Resize(width, height);
	}
}


PolycodeFrame::PolycodeFrame() : ScreenEntity() {

	globalFrame = this;
	processInputEvents = true;
	willHideModal = false;
	showingConsole = true;
	modalChild = NULL;

	welcomeEntity = new ScreenEntity();
	welcomeEntity->processInputEvents = true;
	addChild(welcomeEntity);
	welcomeImage = new ScreenImage("Images/welcome.png");
	welcomeEntity->addChild(welcomeImage);
	welcomeEntity->snapToPixels = true;

	newProjectButton = new UIButton("Create A New Project!", 220);	
	newProjectButton->setPosition(230,80);
	newProjectButton->addEventListener(this, UIEvent::CLICK_EVENT);

	examplesButton = new UIButton("Browse Example Projects!", 220);	
	examplesButton->setPosition(460,80);
	examplesButton->addEventListener(this, UIEvent::CLICK_EVENT);

	welcomeEntity->addChild(newProjectButton);
	welcomeEntity->addChild(examplesButton);

	mainSizer = new UIHSizer(100,100,200,true);
	mainSizer->setPosition(0, 45);
	addChild(mainSizer);

	consoleSize = 200;

	consoleSizer = new UIVSizer(100,100,200, false);
	mainSizer->addRightChild(consoleSizer);	

	projectBrowser = new PolycodeProjectBrowser();
	mainSizer->addLeftChild(projectBrowser);

	editorHolder = new EditorHolder();
	consoleSizer->addTopChild(editorHolder);

	console = new PolycodeConsole();
	consoleSizer->addBottomChild(console);

	projectBrowser->treeContainer->getRootNode()->addEventListener(this, UITreeEvent::DRAG_START_EVENT);

	topBarBg = new ScreenShape(ScreenShape::SHAPE_RECT, 2,2);
	topBarBg->setColorInt(21, 18, 17, 255);
	topBarBg->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
	topBarBg->processInputEvents = true;
	topBarBg->blockMouseInput = true;
	addChild(topBarBg);

	logo = new ScreenImage("Images/barlogo.png");
	addChild(logo);


	playButton = new UIImageButton("Images/play_button.png");
	addChild(playButton);
	playButton->setPosition(10,4);

	stopButton = new UIImageButton("Images/stop_button.png");
	addChild(stopButton);
	stopButton->setPosition(10,4);

	currentProjectTitle = new ScreenLabel("", 32, "section");
	addChild(currentProjectTitle);
	currentProjectTitle->color.a = 0.4;
	currentProjectTitle->setPosition(70, 0);

	currentFileSelector = new UIComboBox(globalMenu, 350);
	currentFileSelector->addEventListener(this, UIEvent::CHANGE_EVENT);
	addChild(currentFileSelector);

	closeFileButton = new UIImageButton("Images/remove_icon.png");
	addChild(closeFileButton);

	resizer = new ScreenImage("Images/corner_resize.png");	
	addChild(resizer);
	resizer->setColor(0,0,0,0.4);

	modalBlocker = new ScreenShape(ScreenShape::SHAPE_RECT, 10,10);
	modalBlocker->setColor(0,0,0,0.4);
	modalBlocker->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
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

	yesNoCancelPopup = new YesNoCancelPopup();
	yesNoCancelPopup->visible = false;


	aboutWindow = new UIWindow("", 800, 440);
	aboutWindow->closeOnEscape = true;
	ScreenImage *aboutImage = new ScreenImage("Images/about.png");
	aboutWindow->addChild(aboutImage);
	aboutImage->setPosition(20, 40);
	aboutWindow->visible = false;
	aboutOKButton = new UIButton("OK", 100);
	aboutWindow->addChild(aboutOKButton);
	aboutOKButton->setPosition(700, 420);
	aboutOKButton->addEventListener(this, UIEvent::CLICK_EVENT);

	ScreenLabel *versionLabel = new ScreenLabel("version 0.8.2", 12, "mono");
	aboutWindow->addChild(versionLabel);
	versionLabel->setPosition(20, 430);
	versionLabel->color.a = 0.4;

	isDragging  = false;
	dragLabel = new ScreenLabel("NONE", 11, "sans");
	dragLabel->setPosition(0,-15);

	dragEntity = new ScreenEntity();
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
	addChild(globalColorPicker);

	modalRoot = new UIElement();
	addChild(modalRoot);

	fileDialogBlocker = new ScreenShape(ScreenShape::SHAPE_RECT, 100, 100);
	fileDialogBlocker->setPositionMode(ScreenEntity::POSITION_TOPLEFT);
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

	this->modalChild = modalChild;
	modalRoot->addChild(modalChild);
	modalChild->showWindow();
	modalChild->addEventListener(this, UIEvent::CLOSE_EVENT);
	Resize(frameSizeX, frameSizeY);

	if(modalChild == yesNoPopup) {
		yesNoPopup->focusChild(yesNoPopup->okButton);
	}
}

PolycodeProjectBrowser *PolycodeFrame::getProjectBrowser() {
	return projectBrowser;
}

void PolycodeFrame::removeEditor(PolycodeEditor *editor) {
	for(int i=0; i < editors.size(); i++) {
		if(editors[i] == editor) {
			editors.erase(editors.begin()+i);
			editorHolder->removeChild(editor);
			if(editor == editorHolder->currentEditor) {
				editorHolder->currentEditor = NULL;
			}
			return;
		}
	}
}

void PolycodeFrame::addEditor(PolycodeEditor *editor) {
	editors.push_back(editor);
	editorHolder->addChild(editor);
	editor->enabled = false;
}

void PolycodeFrame::showEditor(PolycodeEditor *editor) {
	if(editorHolder->currentEditor) {
		editorHolder->currentEditor->enabled = false;
		editorHolder->currentEditor = NULL;
	}

	editorHolder->currentEditor = editor;
	editorHolder->currentEditor->enabled = true;
	editorHolder->currentEditor->Activate();

	Resize(frameSizeX, frameSizeY);
}

void PolycodeFrame::hideModal() {
	if(modalChild) {
		modalRoot->removeChild(modalChild);
		modalChild->removeEventListener(this, UIEvent::CLOSE_EVENT);
		modalChild->hideWindow(); 
		modalChild = NULL;
	}
	modalBlocker->enabled = false;
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

void PolycodeFrame::Update() {
	if(willHideModal) {
		hideModal();
		willHideModal = false;
	}
}

void PolycodeFrame::showAssetBrowser(std::vector<String> extensions) {
	if(!projectManager->getActiveProject()) {
		return;
	}
	assetBrowser->setProject(projectManager->getActiveProject());
	assetBrowser->setExtensions(extensions);
	showModal(assetBrowser);
}

void PolycodeFrame::handleEvent(Event *event) {

	if(event->getDispatcher() == currentFileSelector && event->getEventType() == "UIEvent") {
		PolycodeEditor *editor = editorManager->openEditors[currentFileSelector->getSelectedIndex()];
		editorManager->setCurrentEditor(editor, false);
		showEditor(editor);
	}

	if(event->getDispatcher() == editorManager) {
		updateFileSelector();
	}

	if(event->getDispatcher() == projectManager && projectManager->getActiveProject()) {
		currentProjectTitle->setText(projectManager->getActiveProject()->getProjectName());
	} else if (projectManager->getProjectCount() == 0) { 
		currentProjectTitle->setText(""); 
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
				if(isDragging && editorHolder->currentEditor) {
					InputEvent *inputEvent = (InputEvent*) event;
					Number posX = inputEvent->mousePosition.x;
					Number posY = inputEvent->mousePosition.y;
					editorHolder->currentEditor->handleDroppedFile(draggedFile, posX, posY);
				}
				isDragging = false;
				dragEntity->visible = false;
			break;
			case InputEvent::EVENT_MOUSEMOVE:
				if(isDragging) {
					dragEntity->setPosition(((InputEvent*)event)->mousePosition);
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
					InputEvent *inEv = (InputEvent*)event;
					if (inEv->getKey() == KEY_TAB) {
						showNextEditor();
					} else if (inEv->getKey() == KEY_SLASH) {
						displayFilePathInSelector = (displayFilePathInSelector ? false : true);
						updateFileSelector();
					}
				}
			break;

		}
	}

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

	if(event->getDispatcher() == modalChild) {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLOSE_EVENT) {
			willHideModal = true;
		}
	} else {
		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT && event->getDispatcher() == newProjectButton) {

			newProjectWindow->ResetForm();
			showModal(newProjectWindow);

		}

		if(event->getEventType() == "UIEvent" && event->getEventCode() == UIEvent::CLICK_EVENT && event->getDispatcher() == examplesButton) {

			newProjectWindow->ResetForm();
			showModal(exampleBrowserWindow);

		}

	}
}

void PolycodeFrame::Resize(int x, int y) {

	frameSizeX = x;
	frameSizeY = y;

	welcomeEntity->setPosition((x-welcomeImage->getWidth()) / 2,
		(y-welcomeImage->getHeight()) / 2); 

	topBarBg->setShapeSize(x, 45);
	logo->setPosition(x-logo->getWidth()-2, 2);
	resizer->setPosition(x-resizer->getWidth()-1, y-resizer->getHeight()-1);
	mainSizer->Resize(x,y-45);

	modalBlocker->setShapeSize(x, y);
	fileDialogBlocker->setShapeSize(x, y);

	currentFileSelector->setPosition(x-400, 11);
	closeFileButton->setPosition(currentFileSelector->getPosition().x-20, currentFileSelector->getPosition().y+6);

	if(this->modalChild) {
		modalChild->setPosition((x-modalChild->getWidth())/2.0f, (y-modalChild->getHeight())/2.0f);
	}
}

PolycodeFrame::~PolycodeFrame() {

}

void PolycodeFrame::showNextEditor() {
	if (currentFileSelector->getSelectedIndex() == currentFileSelector->getNumItems()-1)
		currentFileSelector->setSelectedIndex(0);
	else
		currentFileSelector->setSelectedIndex(currentFileSelector->getSelectedIndex()+1);
}
void PolycodeFrame::showPreviousEditor() {
	if (currentFileSelector->getSelectedIndex() == 0)
		currentFileSelector->setSelectedIndex(currentFileSelector->getNumItems()-1);
	else
		currentFileSelector->setSelectedIndex(currentFileSelector->getSelectedIndex()-1);
}

void PolycodeFrame::updateFileSelector() {
	currentFileSelector->clearItems();

	for(int i=0; i < editorManager->openEditors.size(); i++) {
		OSFileEntry entry(editorManager->openEditors[i]->getFilePath(), OSFileEntry::TYPE_FILE);
		
		String projName = editorManager->openEditors[i]->parentProject->getProjectName();
		String rootFolder = editorManager->openEditors[i]->parentProject->getRootFolder();
		String filePath = editorManager->openEditors[i]->getFilePath();
		
		String fullEntry = filePath;
		if(filePath.find(rootFolder) != -1) {
			fullEntry = projName + filePath.substr(rootFolder.size(), filePath.size()-1);
		}
		if(editorManager->openEditors[i]->hasChanges()) {
			if (displayFilePathInSelector)
				currentFileSelector->addComboItem("* "+fullEntry);
			else
				currentFileSelector->addComboItem("* "+entry.name);
		} else {
			if (displayFilePathInSelector)
				currentFileSelector->addComboItem(fullEntry);
			else
				currentFileSelector->addComboItem(entry.name);
		}

		if(editorManager->getCurrentEditor() == editorManager->openEditors[i]) {
			currentFileSelector->setSelectedIndex(i);
		}
	}
}
