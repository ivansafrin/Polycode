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

TransformGizmo::TransformGizmo(Scene *targetScene, Camera *targetCamera) : Entity() {
	processInputEvents = true;
	
	this->targetScene = targetScene;
	this->targetCamera = targetCamera;
	
	trasnformDecorators = new Entity();
	addChild(trasnformDecorators);
	
	scaleDecorators = new Entity();
	addChild(scaleDecorators);
		
	transformAndScaleLines = new Entity();
	addChild(transformAndScaleLines);
		
	rotateDectorators = new Entity();
	addChild(rotateDectorators);	
	
			
	SceneMesh *yLine = new SceneMesh(Mesh::LINE_MESH);	
	Polycode::Polygon *poly = new Polycode::Polygon();
	poly->addVertex(0.0, 0.0, 0.0);
	poly->addVertex(0.0, 1.0, 0.0);	
	yLine->getMesh()->addPolygon(poly);
	yLine->getMesh()->dirtyArrays();
	yLine->depthTest = false;
	yLine->setColor(0.0, 1.0, 0.0, 1.0);
	transformAndScaleLines->addChild(yLine);

	SceneMesh *xLine = new SceneMesh(Mesh::LINE_MESH);	
	poly = new Polycode::Polygon();
	poly->addVertex(0.0, 0.0, 0.0);
	poly->addVertex(1.0, 0.0, 0.0);	
	xLine->getMesh()->addPolygon(poly);
	xLine->getMesh()->dirtyArrays();
	xLine->depthTest = false;
	xLine->setColor(1.0, 0.0, 0.0, 1.0);
	transformAndScaleLines->addChild(xLine);

	SceneMesh *zLine = new SceneMesh(Mesh::LINE_MESH);	
	poly = new Polycode::Polygon();
	poly->addVertex(0.0, 0.0, 0.0);
	poly->addVertex(0.0, 0.0, 1.0);	
	zLine->getMesh()->addPolygon(poly);
	zLine->getMesh()->dirtyArrays();
	zLine->depthTest = false;
	zLine->setColor(0.0, 0.0, 1.0, 1.0);
	transformAndScaleLines->addChild(zLine);
	
	// MOVE
	
	ScenePrimitive *yArrow = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 0.2, 0.05, 12);
	yArrow->setColor(0.0, 1.0, 0.0, 1.0);
	yArrow->setPosition(0.0, 1.0, 0.0);
	yArrow->depthTest = false;
	trasnformDecorators->addChild(yArrow);
	
	ScenePrimitive *xArrow = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 0.2, 0.05, 12);
	xArrow->setColor(1.0, 0.0, 0.0, 1.0);
	xArrow->setPosition(1.0, 0.0, 0.0);
	xArrow->Roll(-90);
	xArrow->depthTest = false;
	trasnformDecorators->addChild(xArrow);

	ScenePrimitive *zArrow = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 0.2, 0.05, 12);
	zArrow->setColor(0.0, 0.0, 1.0, 1.0);
	zArrow->setPosition(0.0, 0.0, 1.0);
	zArrow->Pitch(90);
	zArrow->depthTest = false;	
	trasnformDecorators->addChild(zArrow);

	// SCALE

	ScenePrimitive *yBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.1, 0.1, 0.1);
	yBox->setColor(0.0, 1.0, 0.0, 1.0);
	yBox->setPosition(0.0, 1.0, 0.0);
	yBox->depthTest = false;
	scaleDecorators->addChild(yBox);
	
	ScenePrimitive *xBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.1, 0.1, 0.1);
	xBox->setColor(1.0, 0.0, 0.0, 1.0);
	xBox->setPosition(1.0, 0.0, 0.0);
	xBox->Roll(-90);
	xBox->depthTest = false;
	scaleDecorators->addChild(xBox);

	ScenePrimitive *zBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.1, 0.1, 0.1);
	zBox->setColor(0.0, 0.0, 1.0, 1.0);
	zBox->setPosition(0.0, 0.0, 1.0);
	zBox->Pitch(90);
	zBox->depthTest = false;	
	scaleDecorators->addChild(zBox);

	// ROTATE

	ScenePrimitive *bgCircle = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 1.6, 1.6, 32);
	bgCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	bgCircle->setColor(0.0, 0.0, 0.0, 1.0);
	bgCircle->depthTest = false;
	bgCircle->billboardMode = true;
	rotateDectorators->addChild(bgCircle);

	ScenePrimitive *outerCircle = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 2.0, 2.0, 32);
	outerCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	outerCircle->setColor(1.0, 1.0, 1.0, 1.0);
	outerCircle->depthTest = false;
	outerCircle->billboardMode = true;
	rotateDectorators->addChild(outerCircle);
	
	ScenePrimitive *pitchCircle = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 1.6, 1.6, 32);
	pitchCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	pitchCircle->setColor(1.0, 0.0, 0.0, 1.0);
	pitchCircle->depthTest = false;
	pitchCircle->Yaw(90);	
	rotateDectorators->addChild(pitchCircle);
	pitchCircle->setMaterialByName("OneSidedLine");

	ScenePrimitive *yawCircle = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 1.6, 1.6, 32);
	yawCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	yawCircle->setColor(0.0, 1.0, 0.0, 1.0);
	yawCircle->depthTest = false;
	yawCircle->Pitch(90);
	rotateDectorators->addChild(yawCircle);
	yawCircle->setMaterialByName("OneSidedLine");
	
	ScenePrimitive *rollCircle = new ScenePrimitive(ScenePrimitive::TYPE_CIRCLE, 1.6, 1.6, 32);
	rollCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	rollCircle->setColor(0.0, 0.0, 1.0, 1.0);
	rollCircle->depthTest = false;
	rotateDectorators->addChild(rollCircle);
	rollCircle->setMaterialByName("OneSidedLine");
		
	pitchCircle->lineWidth = 2.0;	
	yawCircle->lineWidth = 2.0;
	rollCircle->lineWidth = 2.0;		
	
	xTransformGrip = new Entity();
	xTransformGrip->bBox.set(1.3, 0.1, 0.1);
	addChild(xTransformGrip);
	xTransformGrip->setAnchorPoint(Vector3(-1.0, 0.0, 0.0));
	xTransformGrip->processInputEvents = true;
	xTransformGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);

	yTransformGrip = new Entity();
	yTransformGrip->bBox.set(0.1, 1.3, 0.1);
	addChild(yTransformGrip);
	yTransformGrip->setAnchorPoint(Vector3(0.0, -1.0, 0.0));
	yTransformGrip->processInputEvents = true;
	yTransformGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);

	zTransformGrip = new Entity();
	zTransformGrip->bBox.set(0.1, 0.1, 1.3);
	addChild(zTransformGrip);
	zTransformGrip->setAnchorPoint(Vector3(0.0, 0.0, -1.0));
	zTransformGrip->processInputEvents = true;
	zTransformGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);


		
	transforming = false;
	mode = TRANSFORM_MOVE;
	
	visible = false;
	enabled = false;
	
	coreInput = CoreServices::getInstance()->getCore()->getInput();
	coreInput->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
	coreInput->addEventListener(this, InputEvent::EVENT_MOUSEUP);	
	
	setTransformMode(TRANSFORM_MOVE);
}

Vector3 TransformGizmo::getTransformPlanePosition() {

	Number planeDistance = 0;
	if(transformPlane.x > 0) {
		planeDistance = getPosition().x;
	} else if(transformPlane.y > 0.0) {
		planeDistance = getPosition().y;	
	} else if(transformPlane.z > 0.0) {
		planeDistance = getPosition().z;	
	}
	Ray ray = targetScene->projectRayFromCameraAndViewportCoordinate(targetCamera, coreInput->getMousePosition());	
	
	return ray.planeIntersectPoint(transformPlane, planeDistance);
}

void TransformGizmo::setTransformMode(int newMode) {

	trasnformDecorators->visible = false;
	scaleDecorators->visible = false;
	transformAndScaleLines->visible = false;
	rotateDectorators->visible = false;
	xTransformGrip->enabled = false;
	yTransformGrip->enabled = false;
	zTransformGrip->enabled = false;
			
	mode = newMode;
	switch (mode) {
		case TRANSFORM_MOVE:
			trasnformDecorators->visible = true;
			transformAndScaleLines->visible = true;
			xTransformGrip->enabled = true;
			yTransformGrip->enabled = true;
			zTransformGrip->enabled = true;						
		break;
		case TRANSFORM_SCALE:
			scaleDecorators->visible = true;
			transformAndScaleLines->visible = true;					
			xTransformGrip->enabled = true;
			yTransformGrip->enabled = true;
			zTransformGrip->enabled = true;				
		break;	
		case TRANSFORM_ROTATE:
			rotateDectorators->visible = true;
		break;
		default:
			assert(false); // invalid mode
		break;
	}
}

void TransformGizmo::setTransformSelection(std::vector<Entity*> selectedEntities) {
	this->selectedEntities = selectedEntities;
	if(selectedEntities.size() > 0) {
		visible = true;
		enabled = true;
		
		Vector3 centerPoint;
		for(int i=0; i < selectedEntities.size(); i++) {
			centerPoint += selectedEntities[i]->getConcatenatedMatrix().getPosition();			
		}
		centerPoint = centerPoint / selectedEntities.size();
		setPosition(centerPoint);
	} else {
		visible = false;
		enabled = false;
	}
	
}

void TransformGizmo::transfromSelectedEntities(const Vector3 &move, const Vector3 &scale) {
	for(int i=0; i < selectedEntities.size(); i++) {
		selectedEntities[i]->Translate(move);
		selectedEntities[i]->setScale(selectedEntities[i]->getScale() + scale);
	}
	Translate(move);
}

void TransformGizmo::handleEvent(Event *event) {
	if(event->getDispatcher() == xTransformGrip) {
		if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
			transforming = true;
			transformConstraint = Vector3(1.0, 0.0, 0.0);
			transformPlane = Vector3(0.0, 1.0, 0.0);
			startingPoint = getTransformPlanePosition();
		}
	} else 	if(event->getDispatcher() == yTransformGrip) {
		if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
			transforming = true;
			transformConstraint = Vector3(0.0, 1.0, 0.0);
			transformPlane = Vector3(0.0, 0.0, 1.0);			
			startingPoint = getTransformPlanePosition();
		}
	} else 	if(event->getDispatcher() == zTransformGrip) {
		if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
			transforming = true;
			transformConstraint = Vector3(0.0, 0.0, 1.0);
			transformPlane = Vector3(0.0, 1.0, 0.0);			
			startingPoint = getTransformPlanePosition();
		}		
	} else if(event->getDispatcher() == coreInput && transforming) {
		InputEvent *inputEvent = (InputEvent*) event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEMOVE:
			{
				switch(mode) {
					case TRANSFORM_MOVE:
					{
						Vector3 newPoint = getTransformPlanePosition();
						transfromSelectedEntities((newPoint-startingPoint) * transformConstraint, Vector3(0.0, 0.0, 0.0));
						startingPoint = newPoint;
					}
					break;
					case TRANSFORM_SCALE:
					{
						Vector3 newPoint = getTransformPlanePosition();
						transfromSelectedEntities(Vector3(0.0, 0.0, 0.0), ((newPoint-startingPoint) * transformConstraint));
						startingPoint = newPoint;					
					}
					break;
				}
			}
			break;
			case InputEvent::EVENT_MOUSEUP:
			{
				transforming = false;
			}
			break;
		}
	}
}

TransformGizmo::~TransformGizmo() {

}

void TransformGizmo::Update() {
	Number scale = getPosition().distance(targetCamera->getPosition()) * 0.1;
	setScale(scale, scale, scale);
}

EditorGrid::EditorGrid() : Entity() {
	grid = NULL;
	setGrid(1.0);
	setPitch(90);
}

void EditorGrid::setGrid(int gridSize) {
	Polycode::Polygon *gridPoly = new Polycode::Polygon();
	int gridLen = 16;
	
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
				
			grid = new SceneMesh(gridMesh);
			grid->setColor(1.0, 1.0, 1.0, 0.1);
			addChild(grid);                
			grid->setPosition(-gridSize * gridLen * 0.5, -gridSize * gridLen * 0.5);
	}
}


EditorGrid::~EditorGrid() {

}


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
				
	sideBar = new Entity();
	addChild(sideBar);
	sideBar->setPosition(0, 30);
	
	UIImage *sidebarBg = new UIImage("Images/entity_editor/sidebar.png");
	sideBar->addChild(sidebarBg);
	
	headerBg = new UIRect(10,10);
	addChild(headerBg);
	headerBg->setAnchorPoint(-1.0, -1.0, 0.0);
	headerBg->color.setColorHexFromString(CoreServices::getInstance()->getConfig()->getStringValue("Polycode", "uiHeaderBgColor"));
	
	
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
	
	
//	transformGizmo->setTransformMode(TransformGizmo::TRANSFORM_ROTATE);
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

