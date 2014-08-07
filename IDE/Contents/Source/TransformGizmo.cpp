/*
 Copyright (C) 2013 by Ivan Safrin
 
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
 
#include "TransformGizmo.h"

extern UIGlobalMenu *globalMenu;

TransformGrips::TransformGrips() : UIElement() {
    
    mainRect = new UIRect(1.0, 1.0);
    mainRect->setBlendingMode(Renderer::BLEND_MODE_NORMAL);
    mainRect->color.setColor(0.0, 0.5, 1.0, 0.2);
    grips.push_back(mainRect);
    
    transformTL = new UIImage("spriteEditor/transform_corner.png", 8, 8);
    grips.push_back(transformTL);
    transformT = new UIImage("spriteEditor/transform_corner.png", 8, 8);
    grips.push_back(transformT);
    transformTR = new UIImage("spriteEditor/transform_corner.png", 8, 8);
    grips.push_back(transformTR);
    transformL = new UIImage("spriteEditor/transform_corner.png", 8, 8);
    grips.push_back(transformL);
    transformR = new UIImage("spriteEditor/transform_corner.png", 8, 8);
    grips.push_back(transformR);
    transformBL = new UIImage("spriteEditor/transform_corner.png", 8, 8);
    grips.push_back(transformBL);
    transformB = new UIImage("spriteEditor/transform_corner.png", 8, 8);
    grips.push_back(transformB);
    transformBR = new UIImage("spriteEditor/transform_corner.png", 8, 8);
    grips.push_back(transformBR);
    transformOffset = new UIImage("spriteEditor/transform_offset.png", 12, 12);
    grips.push_back(transformOffset);
    
    for(int i=0; i < grips.size(); i++) {
        addChild(grips[i]);
        if(grips[i] != mainRect) {
            grips[i]->setAnchorPoint(Vector3());
        }
        grips[i]->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
        grips[i]->addEventListener(this, InputEvent::EVENT_MOUSEUP);
        grips[i]->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
        grips[i]->blockMouseInput = true;
    }
    
    
    Services()->getCore()->getInput()->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);
    
    transforming = false;
    
    movingTransform = NULL;
}

Polycode::Rectangle TransformGrips::getGripRectangle() {
    return gripRectangle;
}

void TransformGrips::handleEvent(Event *event) {
    if(event->getDispatcher() == Services()->getCore()->getInput()) {
        if(transforming) {
            
            Vector2 newMouse = Services()->getCore()->getInput()->getMousePosition();
            
            if(movingTransform == mainRect) {
                gripRectangle.x += newMouse.x - mouseBase.x;
                gripRectangle.y += newMouse.y - mouseBase.y;
            } else if(movingTransform == transformTL) {
                gripRectangle.x += newMouse.x - mouseBase.x;
                gripRectangle.y += newMouse.y - mouseBase.y;
                gripRectangle.w -= newMouse.x - mouseBase.x;
                gripRectangle.h -= newMouse.y - mouseBase.y;
            } else if(movingTransform == transformTR) {
                gripRectangle.y += newMouse.y - mouseBase.y;
                gripRectangle.w += newMouse.x - mouseBase.x;
                gripRectangle.h -= newMouse.y - mouseBase.y;
            } else if(movingTransform == transformT) {
                gripRectangle.y += newMouse.y - mouseBase.y;
                gripRectangle.h -= newMouse.y - mouseBase.y;
            } else if(movingTransform == transformL) {
                gripRectangle.x += newMouse.x - mouseBase.x;
                gripRectangle.w -= newMouse.x - mouseBase.x;
            } else if(movingTransform == transformR) {
                gripRectangle.w += newMouse.x - mouseBase.x;
            } else if(movingTransform == transformBL) {
                gripRectangle.x += newMouse.x - mouseBase.x;
                gripRectangle.w -= newMouse.x - mouseBase.x;
                gripRectangle.h += newMouse.y - mouseBase.y;
            } else if(movingTransform == transformBR) {
                gripRectangle.w += newMouse.x - mouseBase.x;
                gripRectangle.h += newMouse.y - mouseBase.y;
            } else if(movingTransform == transformB) {
                gripRectangle.h += newMouse.y - mouseBase.y;
            } else if(movingTransform == transformOffset) {
                anchorPoint.x += (newMouse.x - mouseBase.x) / gripRectangle.w;
                anchorPoint.y += (newMouse.y - mouseBase.y) / gripRectangle.h;
            }
            
            mouseBase = newMouse;
            dispatchEvent(new Event(), Event::CHANGE_EVENT);
        }
    } else {
        if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
            movingTransform = (UIImage*) event->getDispatcher();
            transforming = true;
            
            mouseBase = Services()->getCore()->getInput()->getMousePosition();
            
        } else {
            transforming = false;
        }
    }
}

Vector2 TransformGrips::getAnchorPoint() {
    return anchorPoint;
}

TransformGrips::~TransformGrips() {
    Services()->getCore()->getInput()->removeAllHandlersForListener(this);
}

void TransformGrips::setGripRectangle(Polycode::Rectangle rectangle, Vector2 offset) {
    
    mainRect->setPosition(rectangle.x, rectangle.y);
    mainRect->Resize(rectangle.w, rectangle.h);
    
    transformTL->setPosition(rectangle.x, rectangle.y);
    transformT->setPosition(rectangle.x + (rectangle.w * 0.5), rectangle.y);
    transformTR->setPosition(rectangle.x + (rectangle.w), rectangle.y);
    
    transformL->setPosition(rectangle.x, rectangle.y +(rectangle.h * 0.5));
    transformR->setPosition(rectangle.x + (rectangle.w), rectangle.y+(rectangle.h * 0.5));
    
    transformBL->setPosition(rectangle.x, rectangle.y+rectangle.h);
    transformB->setPosition(rectangle.x + (rectangle.w * 0.5), rectangle.y+rectangle.h);
    transformBR->setPosition(rectangle.x+rectangle.w, rectangle.y+rectangle.h);
    
    transformOffset->setPosition(rectangle.x + (rectangle.w * 0.5) + (offset.x * rectangle.w), rectangle.y + (rectangle.h * 0.5) + (offset.y * rectangle.h));
    
    gripRectangle = rectangle;
    anchorPoint = offset;
    
}

TrasnformGizmoEvent::TrasnformGizmoEvent(int mode) : Event() {
    this->mode =  mode;
    this->eventCode = eventCode;
    eventType = "TrasnformGizmoEvent";
}

TransformGizmoMenu::TransformGizmoMenu(TransformGizmo *gizmo) : UIElement() {
	processInputEvents = true;
    
	this->gizmo = gizmo;
    
    transformSelector = new UIIconSelector();
    addChild(transformSelector);
    transformSelector->addIcon("entityEditor/move_gizmo.png");
    transformSelector->addIcon("entityEditor/scale_gizmo.png");
    transformSelector->addIcon("entityEditor/rotate_gizmo.png");
    transformSelector->setPosition(4, 3.0);
    transformSelector->addEventListener(this, UIEvent::SELECT_EVENT);
    
    orientationCombo = new UIComboBox(globalMenu, 100);
    orientationCombo->addComboItem("Global");
    orientationCombo->addComboItem("Local");
    orientationCombo->setSelectedIndex(0);
    addChild(orientationCombo);
    orientationCombo->setPosition(100, 2);
    orientationCombo->addEventListener(this, UIEvent::CHANGE_EVENT);
    
    centerSelector = new UIIconSelector();
    addChild(centerSelector);
    centerSelector->addIcon("entityEditor/median_center.png");
    centerSelector->addIcon("entityEditor/individual_centers.png");
    centerSelector->setPosition(210, 3.0);
    centerSelector->addEventListener(this, UIEvent::SELECT_EVENT);
    
}

void TransformGizmoMenu::handleEvent(Event *event) {
	if(event->getDispatcher() == transformSelector) {
        switch(transformSelector->getSelectedIndex()) {
            case 0:
                gizmo->setTransformMode(TransformGizmo::TRANSFORM_MOVE);
            break;
            case 1:
                gizmo->setTransformMode(TransformGizmo::TRANSFORM_SCALE);
            break;
            case 2:
                gizmo->setTransformMode(TransformGizmo::TRANSFORM_ROTATE);
            break;
        }
	} else if(event->getDispatcher() == orientationCombo) {
        gizmo->setTransformOrientation(orientationCombo->getSelectedIndex());
    } else if(event->getDispatcher() == centerSelector) {
        if(centerSelector->getSelectedIndex() == 0) {
            gizmo->setCenterMode(TransformGizmo::CENTER_MODE_MEDIAN);
        } else {
            gizmo->setCenterMode(TransformGizmo::CENTER_MODE_INDIVIDUAL);
        }
    }
}

TransformGizmoMenu::~TransformGizmoMenu() {

}

void TransformGizmo::setCenterMode(int centerMode) {
    this->centerMode = centerMode;
}


TransformGizmo::TransformGizmo(Scene *targetScene, Camera *targetCamera) : Entity() {
	processInputEvents = true;
    orientation = ORIENTATION_GLOBAL;
    centerMode = CENTER_MODE_MEDIAN;
    enableGizmo = true;
    firstMove = true;
    
    snapEnabled = false;
    snapSize = 1.0;
    
	this->targetScene = targetScene;
	this->targetCamera = targetCamera;
	
	ScenePrimitive *centerCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 0.3, 0.3, 16);
	centerCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	centerCircle->setColor(0.7, 0.7, 0.7, 1.0);
	centerCircle->depthTest = false;
	centerCircle->billboardMode = true;
	addChild(centerCircle);
    centerCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
		  
	trasnformDecorators = new Entity();
	addChild(trasnformDecorators);
	
	scaleDecorators = new Entity();
	addChild(scaleDecorators);
		
	transformAndScaleLines = new Entity();
	addChild(transformAndScaleLines);    
		
	rotateDectorators = new Entity();
	addChild(rotateDectorators);
    
	yLine = new SceneMesh(Mesh::LINE_MESH);
	yLine->getMesh()->addVertex(0.0, 0.0, 0.0);
	yLine->getMesh()->addVertex(0.0, 1.0, 0.0);
	yLine->getMesh()->dirtyArrays();
	yLine->depthTest = false;
	yLine->setColor(0.0, 1.0, 0.0, 1.0);
    yLine->setLocalBoundingBox(yLine->getMesh()->calculateBBox());
    yLine->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX() * 2.0);
	transformAndScaleLines->addChild(yLine);

	xLine = new SceneMesh(Mesh::LINE_MESH);
	xLine->getMesh()->addVertex(0.0, 0.0, 0.0);
	xLine->getMesh()->addVertex(1.0, 0.0, 0.0);
	xLine->getMesh()->dirtyArrays();
	xLine->depthTest = false;
	xLine->setColor(1.0, 0.0, 0.0, 1.0);
    xLine->setLocalBoundingBox(xLine->getMesh()->calculateBBox());
    xLine->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX() * 2.0);
	transformAndScaleLines->addChild(xLine);

	zLine = new SceneMesh(Mesh::LINE_MESH);
	zLine->getMesh()->addVertex(0.0, 0.0, 0.0);
	zLine->getMesh()->addVertex(0.0, 0.0, 1.0);
	zLine->getMesh()->dirtyArrays();
	zLine->depthTest = false;
	zLine->setColor(0.0, 0.0, 1.0, 1.0);
    zLine->setLocalBoundingBox(zLine->getMesh()->calculateBBox());
    zLine->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX() * 2.0);
	transformAndScaleLines->addChild(zLine);
	
	// MOVE
	
	yArrow = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 0.2, 0.05, 12);
	yArrow->setColor(0.0, 1.0, 0.0, 1.0);
	yArrow->setPosition(0.0, 1.0, 0.0);
	yArrow->depthTest = false;
	trasnformDecorators->addChild(yArrow);
	
	xArrow = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 0.2, 0.05, 12);
	xArrow->setColor(1.0, 0.0, 0.0, 1.0);
	xArrow->setPosition(1.0, 0.0, 0.0);
	xArrow->Roll(-90);
	xArrow->depthTest = false;
	trasnformDecorators->addChild(xArrow);

	zArrow = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 0.2, 0.05, 12);
	zArrow->setColor(0.0, 0.0, 1.0, 1.0);
	zArrow->setPosition(0.0, 0.0, 1.0);
	zArrow->Pitch(90);
	zArrow->depthTest = false;	
	trasnformDecorators->addChild(zArrow);

	// SCALE

	yBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.1, 0.1, 0.1);
	yBox->setColor(0.0, 1.0, 0.0, 1.0);
	yBox->setPosition(0.0, 1.0, 0.0);
	yBox->depthTest = false;
	scaleDecorators->addChild(yBox);
	
	xBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.1, 0.1, 0.1);
	xBox->setColor(1.0, 0.0, 0.0, 1.0);
	xBox->setPosition(1.0, 0.0, 0.0);
	xBox->Roll(-90);
	xBox->depthTest = false;
	scaleDecorators->addChild(xBox);

	zBox = new ScenePrimitive(ScenePrimitive::TYPE_BOX, 0.1, 0.1, 0.1);
	zBox->setColor(0.0, 0.0, 1.0, 1.0);
	zBox->setPosition(0.0, 0.0, 1.0);
	zBox->Pitch(90);
	zBox->depthTest = false;	
	scaleDecorators->addChild(zBox);

	// ROTATE

	bgCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 2.6, 2.6, 32);
	bgCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	bgCircle->setColor(0.0, 0.0, 0.0, 1.0);
	bgCircle->depthTest = false;
	bgCircle->billboardMode = true;
	rotateDectorators->addChild(bgCircle);
    bgCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());

	outerCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 3.0, 3.0, 32);
	outerCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	outerCircle->setColor(1.0, 1.0, 1.0, 1.0);
	outerCircle->depthTest = false;
	outerCircle->billboardMode = true;
	rotateDectorators->addChild(outerCircle);
    outerCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX() * 2.0);
    
	pitchCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 2.55, 2.55, 32);
	pitchCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	pitchCircle->setColor(1.0, 0.0, 0.0, 1.0);
	pitchCircle->depthTest = false;
	pitchCircle->Yaw(90);	
	rotateDectorators->addChild(pitchCircle);
	pitchCircle->setMaterialByName("OneSidedLine");
    pitchCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX() * 2.0);
    
	yawCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 2.65, 2.65, 32);
	yawCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	yawCircle->setColor(0.0, 1.0, 0.0, 1.0);
	yawCircle->depthTest = false;
	yawCircle->Pitch(90);
	rotateDectorators->addChild(yawCircle);
	yawCircle->setMaterialByName("OneSidedLine");
    yawCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX()* 2.0);
    
	rollCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 2.6, 2.6, 32);
	rollCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	rollCircle->setColor(0.0, 0.0, 1.0, 1.0);
	rollCircle->depthTest = false;
	rotateDectorators->addChild(rollCircle);
	rollCircle->setMaterialByName("OneSidedLine");
    rollCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX()* 2.0);
    
	
	rotateDectorators->processInputEvents = true;
	
	//pitchGrip = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 1.55 * 0.5, 0.05, 16, 3);
    pitchGrip = new ScenePrimitive(ScenePrimitive::TYPE_UNCAPPED_CYLINDER, 0.15, 2.55 * 0.5, 16);
	pitchGrip->setColor(1.0, 0.0, 0.0, 0.2);
	pitchGrip->depthTest = false;
	pitchGrip->Pitch(90);	
	pitchGrip->Yaw(90);		
	rotateDectorators->addChild(pitchGrip);
	pitchGrip->processInputEvents = true;
	pitchGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	pitchGrip->useGeometryHitDetection = true;
	pitchGrip->blockMouseInput = true;

    rollGrip = new ScenePrimitive(ScenePrimitive::TYPE_UNCAPPED_CYLINDER, 0.15, 2.6 * 0.5, 16);
	rollGrip->setColor(0.0, 0.0, 1.0, 0.2);
	rollGrip->depthTest = false;
	rollGrip->Pitch(90);		
	rotateDectorators->addChild(rollGrip);
	rollGrip->processInputEvents = true;
	rollGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	rollGrip->useGeometryHitDetection = true;
	rollGrip->blockMouseInput = true;
	
	yawGrip= new ScenePrimitive(ScenePrimitive::TYPE_UNCAPPED_CYLINDER, 0.15, 2.65 * 0.5, 16);
	yawGrip->setColor(0.0, 1.0, 0.0, 0.2);
	yawGrip->depthTest = false;
	yawGrip->Yaw(90);		
	rotateDectorators->addChild(yawGrip);
	yawGrip->processInputEvents = true;
	yawGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	yawGrip->useGeometryHitDetection = true;
	yawGrip->blockMouseInput = true;
	
    viewportRotateGripBase = new Entity();
    viewportRotateGripBase->processInputEvents = true;
	rotateDectorators->addChild(viewportRotateGripBase);
    
	viewportRotateGrip = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 3.0 * 0.5, 0.08, 16, 3);
    viewportRotateGrip->Pitch(90);
	viewportRotateGrip->setColor(0.0, 1.0, 0.0, 0.2);
	viewportRotateGrip->depthTest = false;
	viewportRotateGripBase->addChild(viewportRotateGrip);
	viewportRotateGrip->processInputEvents = true;
	viewportRotateGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	viewportRotateGrip->useGeometryHitDetection = true;
	viewportRotateGrip->blockMouseInput = true;

    pitchGrip->visible = false;
	yawGrip->visible = false;
	rollGrip->visible = false;
    viewportRotateGrip->visible = false;

	xTransformGrip = new Entity();
	xTransformGrip->setLocalBoundingBox(1.3, 0.1, 0.1);
    xTransformGrip->depthTest = false;
    xTransformGrip->setColor(1.0, 0.0, 0.0, 1.0);
	addChild(xTransformGrip);
	xTransformGrip->setAnchorPoint(Vector3(-1.0, 0.0, 0.0));
	xTransformGrip->processInputEvents = true;
	xTransformGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);

	yTransformGrip = new Entity();
	yTransformGrip->setLocalBoundingBox(0.1, 1.3, 0.1);
	addChild(yTransformGrip);
	yTransformGrip->setAnchorPoint(Vector3(0.0, -1.0, 0.0));
	yTransformGrip->processInputEvents = true;
	yTransformGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);

	zTransformGrip = new Entity();
	zTransformGrip->setLocalBoundingBox(0.1, 0.1, 1.3);
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
	coreInput->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	coreInput->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    
	gizmoMode = GIZMO_MODE_3D;
	setTransformMode(TRANSFORM_MOVE);
}

void TransformGizmo::enableSnap(bool val) {
    snapEnabled = val;
}

void TransformGizmo::setSnapSize(Number snapSize) {
    this->snapSize = snapSize;
}

void TransformGizmo::setTransformOrientation(int orientation) {
    this->orientation = orientation;
}

void TransformGizmo::setTransformPlaneFromView() {
    
    switch(gizmoMode) {
        case GIZMO_MODE_2D_X:
            setTransformPlane(1.0, 0.0, 0.0, true);
            transformConstraint = Vector3(1.0, 0.0, 0.0);
        break;
        case GIZMO_MODE_2D_Y:
            setTransformPlane(0.0, 1.0, 0.0, true);
            transformConstraint = Vector3(0.0, 1.0, 0.0);
        break;
        case GIZMO_MODE_2D_Z:
            setTransformPlane(0.0, 0.0, 1.0, true);
            transformConstraint = Vector3(0.0, 0.0, -1.0);
        break;
        default:
            Vector3 camVec =  targetCamera->getConcatenatedMatrix().getPosition() - getConcatenatedMatrix().getPosition();
            camVec.Normalize();
            setTransformPlane(camVec.x, camVec.y, camVec.z, true);
        break;
    }
}

void TransformGizmo::setTransformPlane(Number x, Number y, Number z, bool forceGlobal) {
    planeMatrix = getConcatenatedMatrix();
    
    Vector3 localPlane = Vector3(x,y,z);
    localTransformPlane = localPlane;
	Number planeDistance = 0;

    if(forceGlobal) {
        transformPlane = localPlane;
        transformPlaneDistance = planeDistance;
        planeMatrix.identity();
        return;
    }
    
    transformPlane = planeMatrix.rotateVector(localPlane);
    Vector3 planePoint = planeMatrix.getPosition();
    transformPlaneDistance = planePoint.dot(transformPlane);
    
	Ray gizmoRay;
	gizmoRay.origin = 0.0;
	gizmoRay.direction = transformPlane * -1;
    
	gizmoPoint = gizmoRay.planeIntersectPoint(transformPlane, transformPlaneDistance);
    gizmoPoint = planeMatrix.Inverse() * gizmoPoint;
    
}

Vector3 TransformGizmo::getTransformPlanePosition() {

	Ray ray = targetScene->projectRayFromCameraAndViewportCoordinate(targetCamera, coreInput->getMousePosition());
    
    // hack to fix NaN's in the plane intersect math (sorry)
    ray.direction += Vector3(0.00001, 0.00001, 0.00001);
    
    
    Vector3 ret = ray.planeIntersectPoint(transformPlane, transformPlaneDistance);
    return ret;
}

void TransformGizmo::setTransformMode(int newMode) {
    
    transformMode = newMode;
	trasnformDecorators->visible = false;
	scaleDecorators->visible = false;
	transformAndScaleLines->visible = false;
	rotateDectorators->visible = false;
	xTransformGrip->enabled = false;
	yTransformGrip->enabled = false;
	zTransformGrip->enabled = false;
	
	pitchGrip->enabled = false;
	rollGrip->enabled = false;
	yawGrip->enabled = false;
    viewportRotateGrip->enabled = false;
	
    xTransformGrip->enabled = false;
    yTransformGrip->enabled = false;
    zTransformGrip->enabled = false;
    
			
	mode = newMode;
	switch (mode) {
		case TRANSFORM_MOVE:
			trasnformDecorators->visible = true;
			transformAndScaleLines->visible = true;
            
            switch(gizmoMode) {
                case GIZMO_MODE_3D:
                    xTransformGrip->enabled = true;
                    yTransformGrip->enabled = true;
                    zTransformGrip->enabled = true;
                    xArrow->visible = true;
                    yArrow->visible = true;
                    zArrow->visible = true;
                    xLine->visible = true;
                    yLine->visible = true;
                    zLine->visible = true;
                break;
                case GIZMO_MODE_2D_X:
                    xTransformGrip->enabled = false;
                    yTransformGrip->enabled = true;
                    zTransformGrip->enabled = true;
                    xArrow->visible = false;
                    yArrow->visible = true;
                    zArrow->visible = true;
                    xLine->visible = false;
                    yLine->visible = true;
                    zLine->visible = true;
                break;
                case GIZMO_MODE_2D_Y:
                    xTransformGrip->enabled = true;
                    yTransformGrip->enabled = false;
                    zTransformGrip->enabled = true;
                    xArrow->visible = true;
                    yArrow->visible = false;
                    zArrow->visible = true;
                    xLine->visible = true;
                    yLine->visible = false;
                    zLine->visible = true;
                break;
                case GIZMO_MODE_2D_Z:
                    xTransformGrip->enabled = true;
                    yTransformGrip->enabled = true;
                    zTransformGrip->enabled = false;
                    xArrow->visible = true;
                    yArrow->visible = true;
                    zArrow->visible = false;
                    xLine->visible = true;
                    yLine->visible = true;
                    zLine->visible = false;

                break;
            }
		break;
		case TRANSFORM_SCALE:
			scaleDecorators->visible = true;
			transformAndScaleLines->visible = true;
            switch(gizmoMode) {
                case GIZMO_MODE_3D:
                    xTransformGrip->enabled = true;
                    yTransformGrip->enabled = true;
                    zTransformGrip->enabled = true;
                    xBox->visible = true;
                    yBox->visible = true;
                    zBox->visible = true;
                    xLine->visible = true;
                    yLine->visible = true;
                    zLine->visible = true;
                    break;
                case GIZMO_MODE_2D_X:
                    xTransformGrip->enabled = false;
                    yTransformGrip->enabled = true;
                    zTransformGrip->enabled = true;
                    xBox->visible = false;
                    yBox->visible = true;
                    zBox->visible = true;
                    xLine->visible = false;
                    yLine->visible = true;
                    zLine->visible = true;
                    break;
                case GIZMO_MODE_2D_Y:
                    xTransformGrip->enabled = true;
                    yTransformGrip->enabled = false;
                    zTransformGrip->enabled = true;
                    xBox->visible = true;
                    yBox->visible = false;
                    zBox->visible = true;
                    xLine->visible = true;
                    yLine->visible = false;
                    zLine->visible = true;
                    break;
                case GIZMO_MODE_2D_Z:
                    xTransformGrip->enabled = true;
                    yTransformGrip->enabled = true;
                    zTransformGrip->enabled = false;
                    xBox->visible = true;
                    yBox->visible = true;
                    zBox->visible = false;
                    xLine->visible = true;
                    yLine->visible = true;
                    zLine->visible = false;
                    break;
            }
            

		break;	
		case TRANSFORM_ROTATE:
			rotateDectorators->visible = true;
            
            switch(gizmoMode) {
                case GIZMO_MODE_3D:
                    rollGrip->enabled = true;
                    rollCircle->visible = true;
                    pitchGrip->enabled = true;
                    pitchCircle->visible = true;
                    yawGrip->enabled = true;
                    yawCircle->visible = true;
                    viewportRotateGrip->enabled = false;
                    outerCircle->visible = false;
                    outerCircle->setColor(1.0, 1.0, 1.0, 1.0);
                break;
                case GIZMO_MODE_2D_X:
                    rollGrip->enabled = false;
                    rollCircle->visible = false;
                    pitchGrip->enabled = false;
                    pitchCircle->visible = false;
                    yawGrip->enabled = false;
                    yawCircle->visible = false;
                    viewportRotateGrip->enabled = true;
                    outerCircle->visible = true;
                    outerCircle->setColor(1.0, 0.0, 0.0, 1.0);
                    viewportRotateGrip->setYaw(90);
                    viewportRotateGrip->setPitch(90);
                break;
                case GIZMO_MODE_2D_Y:
                    rollGrip->enabled = false;
                    rollCircle->visible = false;
                    pitchGrip->enabled = false;
                    pitchCircle->visible = false;
                    yawGrip->enabled = false;
                    yawCircle->visible = false;
                    viewportRotateGrip->enabled = true;
                    outerCircle->visible = true;
                    outerCircle->setColor(0.0, 1.0, 0.0, 1.0);
                    viewportRotateGrip->setPitch(0);
                    viewportRotateGrip->setYaw(0);
                break;
                case GIZMO_MODE_2D_Z:
                    rollGrip->enabled = false;
                    rollCircle->visible = false;
                    pitchGrip->enabled = false;
                    pitchCircle->visible = false;
                    yawGrip->enabled = false;
                    yawCircle->visible = false;
                    viewportRotateGrip->enabled = true;
                    outerCircle->visible = true;
                    outerCircle->setColor(0.0, 0.0, 1.0, 1.0);
                    viewportRotateGrip->setPitch(90);
                    viewportRotateGrip->setYaw(0);
                break;
            }
		break;
		default:
			assert(false); // invalid mode
		break;
	}
}

void TransformGizmo::setTransformSelection(std::vector<Entity*> selectedEntities) {
    entityPositions.clear();
	this->selectedEntities = selectedEntities;
	if(selectedEntities.size() > 0) {
		visible = true;
		enabled = true;
		
		Vector3 centerPoint;
		for(int i=0; i < selectedEntities.size(); i++) {
			centerPoint += selectedEntities[i]->getConcatenatedMatrix().getPosition();
            entityPositions.push_back(selectedEntities[i]->getPosition());
		}
		centerPoint = centerPoint / selectedEntities.size();
		setPosition(centerPoint);
	} else {
		visible = false;
		enabled = false;
	}
    
}

void TransformGizmo::transformSelectedEntities(const Vector3 &move, const Vector3 &scale, Number rotate) {
    
    if(firstMove) {
        firstMove = false;
        dispatchEvent(new TrasnformGizmoEvent(mode), Event::SELECT_EVENT);
    }
    
    Vector3 globalCenter = getConcatenatedMatrix().getPosition();
	for(int i=0; i < selectedEntities.size(); i++) {
        
        
        if((orientation == ORIENTATION_GLOBAL && mode != TRANSFORM_SCALE_VIEW) || (ORIENTATION_LOCAL && mode == TRANSFORM_MOVE_VIEW)) {
            entityPositions[i] += move;
            
            Quaternion q;
            Quaternion currentRotation = selectedEntities[i]->getRotationQuat();
            Vector3 axisVector = transformConstraint;
            axisVector = currentRotation.Inverse().applyTo(axisVector);
            axisVector.Normalize();
            q.fromAngleAxis(rotate, axisVector);
            
            
            Vector3 newScale = selectedEntities[i]->getRotationQuat().applyTo(scale);
            newScale.x = fabs(newScale.x);
            newScale.y = fabs(newScale.y);
            newScale.z = fabs(newScale.z);
            if(scale.x < 0 || scale.y < 0 || scale.z < 0) {
                newScale = newScale * -1.0;
            }
            
            if(centerMode == CENTER_MODE_MEDIAN) {
                Vector3 globalPosition = selectedEntities[i]->getConcatenatedMatrix().getPosition();

                Quaternion tQ;
                tQ.fromAngleAxis(rotate, transformConstraint);
                Vector3 trans = globalCenter + tQ.applyTo(globalPosition-globalCenter) - globalPosition;
                globalPosition += trans;
                
                selectedEntities[i]->setPosition(globalPosition - selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().getPosition());
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                if(move.length() == 0.0) {
                    entityPositions[i] = selectedEntities[i]->getPosition();
                }
                
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+newScale));
                
                if(newScale.length() > 0.0) {
                    Vector3 scalePosition;
                    scalePosition.x = globalPosition.x + ((globalPosition.x - globalCenter.x) * newScale.x);
                    scalePosition.y = globalPosition.y + ((globalPosition.y - globalCenter.y) * newScale.y);
                    scalePosition.z = globalPosition.z + ((globalPosition.z - globalCenter.z) * newScale.z);
                    scalePosition = selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().Inverse().transpose() * scalePosition;
                    selectedEntities[i]->setPosition(scalePosition);
                    if(move.length() == 0.0) {
                        entityPositions[i] = selectedEntities[i]->getPosition();
                    }
                }
                
            } else {
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+newScale));
            }
        } else {
            
            entityPositions[i] += getRotationQuat().applyTo(move);
            
            Quaternion q;
            Quaternion currentRotation = selectedEntities[i]->getRotationQuat();
            Vector3 axisVector = transformConstraint;
            
            // always global in the 2d view
            if(gizmoMode != GIZMO_MODE_3D || mode == TRANSFORM_ROTATE_VIEW) {
                axisVector = currentRotation.Inverse().applyTo(axisVector);
            }
            axisVector.Normalize();
            q.fromAngleAxis(rotate, axisVector);
            
            
            if(centerMode == CENTER_MODE_MEDIAN) {
                Vector3 globalPosition = selectedEntities[i]->getConcatenatedMatrix().getPosition();
                
                Quaternion tQ;
                tQ.fromAngleAxis(rotate, getRotationQuat().applyTo(axisVector));
                Vector3 trans = globalCenter + tQ.applyTo(globalPosition-globalCenter) - globalPosition;
                globalPosition += trans;
                
                selectedEntities[i]->setPosition(globalPosition - selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().getPosition());
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                if(move.length() == 0.0) {
                    entityPositions[i] = selectedEntities[i]->getPosition();
                }
                
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+scale));
                
                if(scale.length() > 0.0) {
                    Vector3 scalePosition;
                    scalePosition.x = globalPosition.x + ((globalPosition.x - globalCenter.x) * scale.x);
                    scalePosition.y = globalPosition.y + ((globalPosition.y - globalCenter.y) * scale.y);
                    scalePosition.z = globalPosition.z + ((globalPosition.z - globalCenter.z) * scale.z);
                    scalePosition = selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().Inverse().transpose() * scalePosition;
                    selectedEntities[i]->setPosition(scalePosition);
                    if(move.length() == 0.0) {
                        entityPositions[i] = selectedEntities[i]->getPosition();
                    }
                }
                
            } else {
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+scale));
            }

            
        }

        // snap if moving and snap is on
        if(scale.length() == 0.0 && rotate == 0.0) {
            if(snapEnabled) {
                Vector3 snappedPositon = entityPositions[i];
                snappedPositon.x = round(((Number)snappedPositon.x)/(snapSize)) * snapSize;
                snappedPositon.y = round(((Number)snappedPositon.y)/(snapSize)) * snapSize;
                snappedPositon.z = round(((Number)snappedPositon.z)/(snapSize)) * snapSize;
                selectedEntities[i]->setPosition(snappedPositon);
            } else {
                selectedEntities[i]->setPosition(entityPositions[i]);
            }
        }
		
	}
}

Number TransformGizmo::getTransformPlaneAngle() {
	
	Ray gizmoRay;
	gizmoRay.origin = getConcatenatedMatrix().getPosition();
	gizmoRay.direction = localTransformPlane * -1;
				
	Vector3 gizmoIntersect = gizmoRay.planeIntersectPoint(transformPlane, transformPlaneDistance);
    gizmoIntersect = planeMatrix.Inverse() * gizmoIntersect;
	   
    
	Ray ray = targetScene->projectRayFromCameraAndViewportCoordinate(targetCamera, coreInput->getMousePosition());	
	Vector3 mouseIntersect = ray.planeIntersectPoint(transformPlane, transformPlaneDistance);
    mouseIntersect = planeMatrix.Inverse() * mouseIntersect;
    
	Vector2 planePosition;
    
	if(localTransformPlane.x > 0) {
		planePosition.x = mouseIntersect.z - gizmoIntersect.z;
		planePosition.y = mouseIntersect.y - gizmoIntersect.y;
	} else if(localTransformPlane.y > 0.0) {
		planePosition.x = mouseIntersect.x - gizmoIntersect.x;
		planePosition.y = mouseIntersect.z - gizmoIntersect.z;
	} else if(localTransformPlane.z > 0.0) {
		planePosition.x = mouseIntersect.x - gizmoIntersect.x;
		planePosition.y = mouseIntersect.y - gizmoIntersect.y;
	}
    
	planePosition.Normalize();
	
	return atan2(planePosition.x, planePosition.y);
}

void TransformGizmo::setGizmoMode(int newMode) {
    gizmoMode = newMode;
    setTransformMode(transformMode);
}

void TransformGizmo::handleEvent(Event *event) {
    if(!enableGizmo) {
        return;
    }
    
	if(!coreInput->getKeyState(KEY_LALT) && !coreInput->getKeyState(KEY_RALT)) {
		if(event->getDispatcher() == pitchGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				transforming = true;
				transformConstraint = Vector3(1.0, 0.0, 0.0);
                setTransformPlane(1.0, 0.0, 0.0);
				startingAngle = getTransformPlaneAngle();
			}
		} else 	if(event->getDispatcher() == yawGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				transforming = true;
				transformConstraint = Vector3(0.0, 1.0, 0.0);
                setTransformPlane(0.0, 1.0, 0.0);
				startingAngle = getTransformPlaneAngle();
			}
		} else 	if(event->getDispatcher() == rollGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				transforming = true;
				transformConstraint = Vector3(0.0, 0.0, -1.0);
				setTransformPlane(0.0, 0.0, 1.0);
				startingAngle = getTransformPlaneAngle();
			}
		} else 	if(event->getDispatcher() == viewportRotateGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
                if(gizmoMode != GIZMO_MODE_3D) {
                    transforming = true;
                    setTransformPlaneFromView();
                    startingAngle = getTransformPlaneAngle();
                }
			}
		}

		if(event->getDispatcher() == xTransformGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				transforming = true;
				transformConstraint = Vector3(1.0, 0.0, 0.0);
                if(gizmoMode == GIZMO_MODE_3D) {
                    setTransformPlane(0.0, 1.0, 0.0);
                } else {
                    setTransformPlane(0.0, 0.0, 1.0);
                }
				startingPoint = getTransformPlanePosition();
			}
		} else 	if(event->getDispatcher() == yTransformGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				transforming = true;
				transformConstraint = Vector3(0.0, 1.0, 0.0);
				setTransformPlane(0.0, 0.0, 1.0);
				startingPoint = getTransformPlanePosition();
			}
		} else 	if(event->getDispatcher() == zTransformGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				transforming = true;
				transformConstraint = Vector3(0.0, 0.0, 1.0);
				setTransformPlane(0.0, 1.0, 0.0);
				startingPoint = getTransformPlanePosition();
			}		
		}
	}
	
	if(event->getDispatcher() == coreInput) {
        
		if (!coreInput->getKeyState(KEY_LCTRL) && !coreInput->getKeyState(KEY_RCTRL) && !coreInput->getKeyState(KEY_LALT) && !coreInput->getKeyState(KEY_RALT)) {
			if (event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
				InputEvent *inputEvent = (InputEvent*)event;
				switch (inputEvent->key) {
				case KEY_s:
				{
							  transforming = true;
							  previousMode = mode;
							  mode = TRANSFORM_SCALE_VIEW;
							  setTransformPlaneFromView();
							  startingPoint = getTransformPlanePosition();

				}
					break;
				case KEY_r:
				{
							  previousMode = mode;
							  mode = TRANSFORM_ROTATE_VIEW;
							  transforming = true;
							  setTransformPlaneFromView();
							  transformConstraint = transformPlane;
							  if (gizmoMode == GIZMO_MODE_2D_Z) {
								  transformConstraint = transformConstraint * -1.0;
							  }
							  startingAngle = getTransformPlaneAngle();
				}
					break;
				case KEY_g:
				{
							  previousMode = mode;
							  mode = TRANSFORM_MOVE_VIEW;
							  transforming = true;
							  setTransformPlaneFromView();
							  startingPoint = getTransformPlanePosition();
				}
					break;
				case KEY_ESCAPE:
				{
								   if (mode == TRANSFORM_SCALE_VIEW || mode == TRANSFORM_ROTATE_VIEW || mode == TRANSFORM_MOVE_VIEW) {
									   dispatchEndEvent();
									   mode = previousMode;
								   }
								   transforming = false;
								   firstMove = true;
				}
					break;
				}
			}
        }
        
        if(transforming) {
            switch(event->getEventCode()) {
                case InputEvent::EVENT_MOUSEMOVE:
                {
                    switch(mode) {
                        case TRANSFORM_MOVE:
                        {
                            Vector3 newPoint = getTransformPlanePosition();
                            Vector3 diff = (planeMatrix.Inverse() * newPoint) -(planeMatrix.Inverse() * startingPoint);
                            diff = diff * getCompoundScale();                                                        
                            transformSelectedEntities(transformConstraint * diff, Vector3(0.0, 0.0, 0.0), 0.0);
                            startingPoint = newPoint;
                        }
                        break;
                        case TRANSFORM_MOVE_VIEW:
                        {
                            Vector3 newPoint = getTransformPlanePosition();
                            Vector3 diff = newPoint - startingPoint;
                            
                            transformSelectedEntities(diff, Vector3(0.0, 0.0, 0.0), 0.0);
                            startingPoint = newPoint;
                        }
                        break;
                        case TRANSFORM_SCALE_VIEW:
                        {
                            Vector3 newPoint = getTransformPlanePosition();
                            
                            Number scaleMult = 1.0;
                            if(newPoint.distance(gizmoPoint) < startingPoint.distance(gizmoPoint)) {
                                scaleMult = -1.0;
                            }
                            
                            transformSelectedEntities(Vector3(0.0, 0.0, 0.0), (Vector3(1.0, 1.0, 1.0) * (newPoint-startingPoint).length() * scaleMult) / getCompoundScale().x, 0.0);
                            startingPoint = newPoint;
                        }
                        break;
                        case TRANSFORM_ROTATE_VIEW:
                        {
                            Number newAngle = getTransformPlaneAngle();
                            
                            Vector3 newPoint = planeMatrix.Inverse() *getTransformPlanePosition();
                            
                            transformSelectedEntities(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), newAngle - startingAngle);
                            startingAngle = newAngle;
                        }
                        break;
                        case TRANSFORM_SCALE:
                        {
                            Vector3 newPoint = getTransformPlanePosition();
                            
                            Vector3 diff = (planeMatrix.Inverse() * newPoint) -(planeMatrix.Inverse() * startingPoint);
                            diff = diff * getCompoundScale();
                            
                            
                            transformSelectedEntities(Vector3(0.0, 0.0, 0.0), (diff * transformConstraint) / getCompoundScale().x, 0.0);
                            startingPoint = newPoint;					
                        }
                        break;
                        case TRANSFORM_ROTATE:
                        {
                            Number newAngle = getTransformPlaneAngle();
                            transformSelectedEntities(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), newAngle - startingAngle);
                            startingAngle = newAngle;						
                        }
                        break;
                    }
                }
                break;
                case InputEvent::EVENT_MOUSEUP:
                {
                    dispatchEndEvent();
                    
                    if(mode == TRANSFORM_SCALE_VIEW || mode == TRANSFORM_ROTATE_VIEW || mode == TRANSFORM_MOVE_VIEW) {
                        mode = previousMode;
                    }
                    transforming = false;
                    firstMove = true;
                }
                break;
            }
        }
	}
}

void TransformGizmo::dispatchEndEvent() {
    switch(mode) {
        case TRANSFORM_MOVE:
        case TRANSFORM_MOVE_VIEW:
            dispatchEvent(new TrasnformGizmoEvent(mode), Event::CHANGE_EVENT);
            break;
        case TRANSFORM_SCALE:
        case TRANSFORM_SCALE_VIEW:
            dispatchEvent(new TrasnformGizmoEvent(mode), Event::CHANGE_EVENT);
            break;
        case TRANSFORM_ROTATE:
        case TRANSFORM_ROTATE_VIEW:
            dispatchEvent(new TrasnformGizmoEvent(mode), Event::CHANGE_EVENT);
            break;
    }
}

TransformGizmo::~TransformGizmo() {
    coreInput->removeAllHandlersForListener(this);
}

void TransformGizmo::updateOrientationForEntity(Entity *entity) {
    Quaternion q;
    switch(orientation) {
        case ORIENTATION_GLOBAL:
            setRotationByQuaternion(q);
        break;
        case ORIENTATION_LOCAL:
            q = entity->getRotationQuat();
            setRotationByQuaternion(q);
        break;
    }
}

void TransformGizmo::Update() {
    
    if(selectedEntities.size() > 0) {
        Vector3 centerPoint;
        for(int i=0; i < selectedEntities.size(); i++) {
            centerPoint += selectedEntities[i]->getConcatenatedMatrix().getPosition();
        }
        centerPoint = centerPoint / selectedEntities.size();
        setPosition(centerPoint);
        
        updateOrientationForEntity(selectedEntities[0]);
    }
    
    viewportRotateGripBase->setRotationByQuaternion(getRotationQuat().Inverse());
    
	Number scale;
    if(gizmoMode != GIZMO_MODE_3D) {
        scale = targetCamera->getPosition().length() * 0.1;
    } else {
        scale = getPosition().distance(targetCamera->getPosition()) * 0.1;
    }
    
    if(scale < 0.0) {
        scale = 0.0;
    }
	setScale(scale, scale, scale);
}

