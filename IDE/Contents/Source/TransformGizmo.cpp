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

TransformGizmoMenu::TransformGizmoMenu(TransformGizmo *gizmo) : UIElement() {
	processInputEvents = true;
    
	this->gizmo = gizmo;
		
	moveModeButton = new UIImageButton("entityEditor/move_gizmo.png", 1.0, 24, 24);
	addChild(moveModeButton);
	moveModeButton->setPosition(4, 2);
	moveModeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	scaleModeButton = new UIImageButton("entityEditor/scale_gizmo.png", 1.0, 24, 24);
	addChild(scaleModeButton);
	scaleModeButton->setPosition(30, 2);
	scaleModeButton->addEventListener(this, UIEvent::CLICK_EVENT);
	
	rotateModeButton = new UIImageButton("entityEditor/rotate_gizmo.png", 1.0, 24, 24);
	addChild(rotateModeButton);
	rotateModeButton->setPosition(56, 2);
	rotateModeButton->addEventListener(this, UIEvent::CLICK_EVENT);
    
    transformModeSelector = new UIImage("entityEditor/button_selector.png", 24, 24);
    addChild(transformModeSelector);
    transformModeSelector->setPosition(moveModeButton->getPosition());
    
    orientationCombo = new UIComboBox(globalMenu, 100);
    orientationCombo->addComboItem("Global");
    orientationCombo->addComboItem("Local");
    orientationCombo->setSelectedIndex(0);
    addChild(orientationCombo);
    orientationCombo->setPosition(100, 2);
    
	centerModeMedianButton = new UIImageButton("entityEditor/median_center.png", 1.0, 24, 24);
	addChild(centerModeMedianButton);
	centerModeMedianButton->setPosition(210, 2);
	centerModeMedianButton->addEventListener(this, UIEvent::CLICK_EVENT);

    centerModeCentersButton = new UIImageButton("entityEditor/individual_centers.png", 1.0, 24, 24);
	addChild(centerModeCentersButton);
	centerModeCentersButton->setPosition(238, 2);
	centerModeCentersButton->addEventListener(this, UIEvent::CLICK_EVENT);

    centerModeSelector = new UIImage("entityEditor/button_selector.png", 24, 24);
    addChild(centerModeSelector);
    centerModeSelector->setPosition(centerModeMedianButton->getPosition());

    
    orientationCombo->addEventListener(this, UIEvent::CHANGE_EVENT);
}

void TransformGizmoMenu::handleEvent(Event *event) {
	if(event->getDispatcher() == moveModeButton) {
		gizmo->setTransformMode(TransformGizmo::TRANSFORM_MOVE);
        transformModeSelector->setPosition(moveModeButton->getPosition());
	} else if(event->getDispatcher() == scaleModeButton) {
		gizmo->setTransformMode(TransformGizmo::TRANSFORM_SCALE);
        transformModeSelector->setPosition(scaleModeButton->getPosition());
	} else if(event->getDispatcher() == rotateModeButton) {
		gizmo->setTransformMode(TransformGizmo::TRANSFORM_ROTATE);
        transformModeSelector->setPosition(rotateModeButton->getPosition());
	} else if(event->getDispatcher() == orientationCombo) {
        gizmo->setTransformOrientation(orientationCombo->getSelectedIndex());
    } else if(event->getDispatcher() == centerModeMedianButton) {
        centerModeSelector->setPosition(centerModeMedianButton->getPosition());
        gizmo->setCenterMode(TransformGizmo::CENTER_MODE_MEDIAN);
    } else if(event->getDispatcher() == centerModeCentersButton) {
        centerModeSelector->setPosition(centerModeCentersButton->getPosition());
        gizmo->setCenterMode(TransformGizmo::CENTER_MODE_INDIVIDUAL);
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
    yLine->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX() * 2.0);
	transformAndScaleLines->addChild(yLine);

	xLine = new SceneMesh(Mesh::LINE_MESH);
	xLine->getMesh()->addVertex(0.0, 0.0, 0.0);
	xLine->getMesh()->addVertex(1.0, 0.0, 0.0);
	xLine->getMesh()->dirtyArrays();
	xLine->depthTest = false;
	xLine->setColor(1.0, 0.0, 0.0, 1.0);
    xLine->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX() * 2.0);
	transformAndScaleLines->addChild(xLine);

	zLine = new SceneMesh(Mesh::LINE_MESH);
	zLine->getMesh()->addVertex(0.0, 0.0, 0.0);
	zLine->getMesh()->addVertex(0.0, 0.0, 1.0);
	zLine->getMesh()->dirtyArrays();
	zLine->depthTest = false;
	zLine->setColor(0.0, 0.0, 1.0, 1.0);
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
	xTransformGrip->bBox.set(1.3, 0.1, 0.1);
    xTransformGrip->depthTest = false;
    xTransformGrip->setColor(1.0, 0.0, 0.0, 1.0);
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
	coreInput->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	coreInput->addEventListener(this, InputEvent::EVENT_KEYDOWN);
    
	gizmoMode = GIZMO_MODE_3D;
	setTransformMode(TRANSFORM_MOVE);
}

void TransformGizmo::setTransformOrientation(int orientation) {
    this->orientation = orientation;
}

void TransformGizmo::setTransformPlaneFromView() {
    if(gizmoMode == GIZMO_MODE_2D) {
        setTransformPlane(0.0, 0.0, 1.0, true);
    } else {
        Vector3 camVec =  targetCamera->getConcatenatedMatrix().getPosition() - getConcatenatedMatrix().getPosition();
        camVec.Normalize();
        setTransformPlane(camVec.x, camVec.y, camVec.z, true);
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
	
			
	mode = newMode;
	switch (mode) {
		case TRANSFORM_MOVE:
			trasnformDecorators->visible = true;
			transformAndScaleLines->visible = true;
			xTransformGrip->enabled = true;
			yTransformGrip->enabled = true;
            if(gizmoMode == GIZMO_MODE_3D) {
                zTransformGrip->enabled = true;
                zArrow->visible = true;
                zLine->visible = true;
            } else {
                zArrow->visible = false;
                zLine->visible = false;
            }
            
		break;
		case TRANSFORM_SCALE:
			scaleDecorators->visible = true;
			transformAndScaleLines->visible = true;					
			xTransformGrip->enabled = true;
			yTransformGrip->enabled = true;
            if(gizmoMode == GIZMO_MODE_3D) {
                zTransformGrip->enabled = true;
                zBox->visible = true;
                zLine->visible = true;
            } else {
                zBox->visible = false;
                zLine->visible = false;
            }

		break;	
		case TRANSFORM_ROTATE:
			rotateDectorators->visible = true;
            
            if(gizmoMode == GIZMO_MODE_3D) {
                rollGrip->enabled = true;
                rollCircle->visible = true;
                pitchGrip->enabled = true;
                pitchCircle->visible = true;
                yawGrip->enabled = true;
                yawCircle->visible = true;
                viewportRotateGrip->enabled = false;
                outerCircle->visible = false;
                outerCircle->setColor(1.0, 1.0, 1.0, 1.0);
                
            } else {
                rollGrip->enabled = false;
                rollCircle->visible = false;
                pitchGrip->enabled = false;
                pitchCircle->visible = false;
                yawGrip->enabled = false;
                yawCircle->visible = false;
                
                viewportRotateGrip->enabled = true;
                outerCircle->visible = true;
                outerCircle->setColor(0.0, 0.0, 1.0, 1.0);
            }
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

void TransformGizmo::transformSelectedEntities(const Vector3 &move, const Vector3 &scale, Number rotate) {
    
    Vector3 globalCenter = getConcatenatedMatrix().getPosition();
    
	for(int i=0; i < selectedEntities.size(); i++) {
        
        
        if((orientation == ORIENTATION_GLOBAL && mode != TRANSFORM_SCALE_VIEW) || (ORIENTATION_LOCAL && mode == TRANSFORM_MOVE_VIEW)) {
            selectedEntities[i]->Translate(move);
            
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
                
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+newScale));
                
                if(newScale.length() > 0.0) {
                    Vector3 scalePosition;
                    scalePosition.x = globalPosition.x + ((globalPosition.x - globalCenter.x) * newScale.x);
                    scalePosition.y = globalPosition.y + ((globalPosition.y - globalCenter.y) * newScale.y);
                    scalePosition.z = globalPosition.z + ((globalPosition.z - globalCenter.z) * newScale.z);
                    scalePosition = selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().Inverse().transpose() * scalePosition;
                    selectedEntities[i]->setPosition(scalePosition);
                }
                
            } else {
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+newScale));
            }
        } else {
            
            selectedEntities[i]->Translate(getRotationQuat().applyTo(move));
            
            Quaternion q;
            Quaternion currentRotation = selectedEntities[i]->getRotationQuat();
            Vector3 axisVector = transformConstraint;
            
            // always global in the 2d view
            if(gizmoMode == GIZMO_MODE_2D || mode == TRANSFORM_ROTATE_VIEW) {
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
                
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+scale));
                
                if(scale.length() > 0.0) {
                    Vector3 scalePosition;
                    scalePosition.x = globalPosition.x + ((globalPosition.x - globalCenter.x) * scale.x);
                    scalePosition.y = globalPosition.y + ((globalPosition.y - globalCenter.y) * scale.y);
                    scalePosition.z = globalPosition.z + ((globalPosition.z - globalCenter.z) * scale.z);
                    scalePosition = selectedEntities[i]->getParentEntity()->getConcatenatedMatrix().Inverse().transpose() * scalePosition;
                    selectedEntities[i]->setPosition(scalePosition);
                }
                
            } else {
                selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
                selectedEntities[i]->setScale(selectedEntities[i]->getScale() * (Vector3(1.0, 1.0, 1.0)+scale));
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
                if(gizmoMode == GIZMO_MODE_2D) {
                    transforming = true;
                    transformConstraint = Vector3(0.0, 0.0, -1.0);
                    setTransformPlane(0.0, 0.0, 1.0, true);
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
        
        if(event->getEventCode() == InputEvent::EVENT_KEYDOWN) {
            InputEvent *inputEvent = (InputEvent*) event;
            switch(inputEvent->key) {
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
                    if(gizmoMode == GIZMO_MODE_2D) {
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
                    if(mode == TRANSFORM_SCALE_VIEW || mode == TRANSFORM_ROTATE_VIEW || mode == TRANSFORM_MOVE_VIEW) {
                        mode = previousMode;
                    }                    
                    transforming = false;
                }
                break;
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
                    if(mode == TRANSFORM_SCALE_VIEW || mode == TRANSFORM_ROTATE_VIEW || mode == TRANSFORM_MOVE_VIEW) {
                        mode = previousMode;
                    }
                    transforming = false;
                }
                break;
            }
        }
	}
}

TransformGizmo::~TransformGizmo() {

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
    if(gizmoMode == GIZMO_MODE_2D) {
        scale = targetCamera->getPosition().length() * 0.1;
    } else {
        scale = getPosition().distance(targetCamera->getPosition()) * 0.1;
    }
    
    if(scale < 0.0) {
        scale = 0.0;
    }
	setScale(scale, scale, scale);
}

