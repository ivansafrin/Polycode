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
 
#include "PolycodeEntityEditor.h"

EntityEditorMainView::EntityEditorMainView() {
	processInputEvents = true;

	mainScene = new Scene(Scene::SCENE_3D, true);		
	renderTexture = new SceneRenderTexture(mainScene, mainScene->getDefaultCamera(), 512, 512);
	mainScene->clearColor.setColor(0.2, 0.2, 0.2, 1.0);	
	mainScene->useClearColor = true;
	mainScene->rootEntity.processInputEvents = true;
	
	renderTextureShape = new UIRect(256, 256);
	renderTextureShape->setAnchorPoint(-1.0, -1.0, 0.0);	
	renderTextureShape->setTexture(renderTexture->getTargetTexture());
	addChild(renderTextureShape);
	renderTextureShape->setPosition(0, 30);
				
			
	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	sideBar = new Entity();
	addChild(sideBar);
	sideBar->setPosition(0, 0);
	sideBar->processInputEvents = true;
    
	
	mainScene->getDefaultCamera()->setPosition(10, 10, 10);
	mainScene->getDefaultCamera()->lookAt(Vector3());

	grid = new EditorGrid();
	mainScene->addChild(grid);
			
	// TEMPORARY!	
	
	ScenePrimitive  *testCube = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 3.0, 1.0, 1.0);
	testCube->processInputEvents = true;
	testCube->setColor(0.5, 0.5, 0.5, 1.0);
//	testCube->setPosition(5, 7, 2);
	mainScene->addChild(testCube);
	testCube->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	testCube->wireFrameColor = Color(1.0, 0.8, 0.3, 1.0);
	
	transformGizmo = new TransformGizmo(mainScene, mainScene->getDefaultCamera());
	mainScene->addChild(transformGizmo);		
	trackballCamera = new TrackballCamera(mainScene->getDefaultCamera(), renderTextureShape);
	
	transformGizmoMenu = new TransformGizmoMenu(transformGizmo);
	sideBar->addChild(transformGizmoMenu);

}

void EntityEditorMainView::Update() {
}

void EntityEditorMainView::handleEvent(Event *event) {

	if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN ) {
		InputEvent *inputEvent = (InputEvent*) event;

		if(inputEvent->mouseButton == CoreInput::MOUSE_BUTTON2) {
			Entity* targetEntity = (Entity*) event->getDispatcher();
			
			selectedEntities.clear();			
			selectedEntities.push_back(targetEntity);
			transformGizmo->setTransformSelection(selectedEntities);
							
			SceneMesh *sceneMesh = dynamic_cast<SceneMesh*>(targetEntity);
			if(sceneMesh) {
				sceneMesh->overlayWireframe = true;
			}
		}
	}
}

EntityEditorMainView::~EntityEditorMainView() {
	
}
			
void EntityEditorMainView::Resize(Number width, Number height) {
	headerBg->Resize(width, 30);
	
	mainScene->sceneMouseAdjust.x = renderTextureShape->getScreenPositionForMainCamera().x;
	mainScene->sceneMouseAdjust.y = CoreServices::getInstance()->getCore()->getYRes() - (renderTextureShape->getScreenPositionForMainCamera().y + renderTextureShape->getHeight());
	
	renderTexture->resizeRenderTexture(width, height-30);
	renderTextureShape->setTexture(renderTexture->getTargetTexture());		
	renderTextureShape->Resize(width, height-30);
}

PolycodeEntityEditor::PolycodeEntityEditor() : PolycodeEditor(true){
	mainSizer = new UIHSizer(300, 300, 200, false);
	addChild(mainSizer);
	
	mainView = new EntityEditorMainView();
	mainSizer->addLeftChild(mainView);
}

PolycodeEntityEditor::~PolycodeEntityEditor() {
}

bool PolycodeEntityEditor::openFile(OSFileEntry filePath) {	
	PolycodeEditor::openFile(filePath);	
	return true;
}

void PolycodeEntityEditor::Resize(int x, int y) {
	mainSizer->Resize(x, y);
	PolycodeEditor::Resize(x,y);
}

