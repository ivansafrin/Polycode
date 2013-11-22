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

TransformGizmoMenu::TransformGizmoMenu(TransformGizmo *gizmo) : UIElement() {
	processInputEvents = true;
	
	this->gizmo = gizmo;
		
	moveModeButton = new UIImageButton("entityEditor/move_gizmo.png", 1.0, 24, 24);
	addChild(moveModeButton);
	moveModeButton->setPosition(4, 2);
	moveModeButton->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
	scaleModeButton = new UIImageButton("entityEditor/scale_gizmo.png", 1.0, 24, 24);
	addChild(scaleModeButton);
	scaleModeButton->setPosition(30, 2);
	scaleModeButton->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	
	rotateModeButton = new UIImageButton("entityEditor/rotate_gizmo.png", 1.0, 24, 24);
	addChild(rotateModeButton);
	rotateModeButton->setPosition(60, 2);
	rotateModeButton->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
}

void TransformGizmoMenu::handleEvent(Event *event) {
	if(event->getDispatcher() == moveModeButton) {
		gizmo->setTransformMode(TransformGizmo::TRANSFORM_MOVE);
	} else if(event->getDispatcher() == scaleModeButton) {
		gizmo->setTransformMode(TransformGizmo::TRANSFORM_SCALE);	
	} else if(event->getDispatcher() == rotateModeButton) {
		gizmo->setTransformMode(TransformGizmo::TRANSFORM_ROTATE);	
	}
}

TransformGizmoMenu::~TransformGizmoMenu() {

}


TransformGizmo::TransformGizmo(Scene *targetScene, Camera *targetCamera) : Entity() {
	processInputEvents = true;
	
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
	Polycode::Polygon *poly = new Polycode::Polygon();
	poly->addVertex(0.0, 0.0, 0.0);
	poly->addVertex(0.0, 1.0, 0.0);	
	yLine->getMesh()->addPolygon(poly);
	yLine->getMesh()->dirtyArrays();
	yLine->depthTest = false;
	yLine->setColor(0.0, 1.0, 0.0, 1.0);
    yLine->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
	transformAndScaleLines->addChild(yLine);

	xLine = new SceneMesh(Mesh::LINE_MESH);
	poly = new Polycode::Polygon();
	poly->addVertex(0.0, 0.0, 0.0);
	poly->addVertex(1.0, 0.0, 0.0);	
	xLine->getMesh()->addPolygon(poly);
	xLine->getMesh()->dirtyArrays();
	xLine->depthTest = false;
	xLine->setColor(1.0, 0.0, 0.0, 1.0);
    xLine->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
	transformAndScaleLines->addChild(xLine);

	zLine = new SceneMesh(Mesh::LINE_MESH);
	poly = new Polycode::Polygon();
	poly->addVertex(0.0, 0.0, 0.0);
	poly->addVertex(0.0, 0.0, 1.0);	
	zLine->getMesh()->addPolygon(poly);
	zLine->getMesh()->dirtyArrays();
	zLine->depthTest = false;
	zLine->setColor(0.0, 0.0, 1.0, 1.0);
    zLine->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
	transformAndScaleLines->addChild(zLine);
	
	// MOVE
	
	yArrow = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 0.2, 0.1, 12);
	yArrow->setColor(0.0, 1.0, 0.0, 1.0);
	yArrow->setPosition(0.0, 1.0, 0.0);
	yArrow->depthTest = false;
	trasnformDecorators->addChild(yArrow);
    yArrow->setMaterialByName("Unlit");
	
	xArrow = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 0.2, 0.1, 12);
	xArrow->setColor(1.0, 0.0, 0.0, 1.0);
	xArrow->setPosition(1.0, 0.0, 0.0);
	xArrow->Roll(-90);
	xArrow->depthTest = false;
	trasnformDecorators->addChild(xArrow);

	zArrow = new ScenePrimitive(ScenePrimitive::TYPE_CONE, 0.2, 0.1, 12);
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

	bgCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 1.6, 1.6, 32);
	bgCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	bgCircle->setColor(0.0, 0.0, 0.0, 1.0);
	bgCircle->depthTest = false;
	bgCircle->billboardMode = true;
	rotateDectorators->addChild(bgCircle);
    bgCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());

	outerCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 2.0, 2.0, 32);
	outerCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	outerCircle->setColor(1.0, 1.0, 1.0, 1.0);
	outerCircle->depthTest = false;
	outerCircle->billboardMode = true;
	rotateDectorators->addChild(outerCircle);
    outerCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
    
	pitchCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 1.55, 1.55, 32);
	pitchCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	pitchCircle->setColor(1.0, 0.0, 0.0, 1.0);
	pitchCircle->depthTest = false;
	pitchCircle->Yaw(90);	
	rotateDectorators->addChild(pitchCircle);
	pitchCircle->setMaterialByName("OneSidedLine");
    pitchCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
    
	yawCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 1.65, 1.65, 32);
	yawCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	yawCircle->setColor(0.0, 1.0, 0.0, 1.0);
	yawCircle->depthTest = false;
	yawCircle->Pitch(90);
	rotateDectorators->addChild(yawCircle);
	yawCircle->setMaterialByName("OneSidedLine");
    yawCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
    
	rollCircle = new ScenePrimitive(ScenePrimitive::TYPE_LINE_CIRCLE, 1.6, 1.6, 32);
	rollCircle->getMesh()->setMeshType(Mesh::LINE_LOOP_MESH);
	rollCircle->setColor(0.0, 0.0, 1.0, 1.0);
	rollCircle->depthTest = false;
	rotateDectorators->addChild(rollCircle);
	rollCircle->setMaterialByName("OneSidedLine");
    rollCircle->setLineWidth(CoreServices::getInstance()->getRenderer()->getBackingResolutionScaleX());
    
	pitchCircle->lineWidth = 2.0;	
	yawCircle->lineWidth = 2.0;
	rollCircle->lineWidth = 2.0;		
	
	rotateDectorators->processInputEvents = true;
	
	pitchGrip = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 1.55 * 0.5, 0.1, 10, 3);
	pitchGrip->setColor(1.0, 0.0, 0.0, 0.2);
	pitchGrip->depthTest = false;
	pitchGrip->Pitch(90);	
	pitchGrip->Yaw(90);		
	rotateDectorators->addChild(pitchGrip);
	pitchGrip->processInputEvents = true;
	pitchGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	pitchGrip->useGeometryHitDetection = true;
	pitchGrip->blockMouseInput = true;

	rollGrip = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 1.6 * 0.5, 0.1, 10, 3);
	rollGrip->setColor(0.0, 0.0, 1.0, 0.2);
	rollGrip->depthTest = false;
	rollGrip->Pitch(90);		
	rotateDectorators->addChild(rollGrip);
	rollGrip->processInputEvents = true;
	rollGrip->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	rollGrip->useGeometryHitDetection = true;
	rollGrip->blockMouseInput = true;
	
	yawGrip = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 1.65 * 0.5, 0.1, 10, 3);
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
    
	viewportRotateGrip = new ScenePrimitive(ScenePrimitive::TYPE_TORUS, 2.0 * 0.5, 0.1, 10, 3);
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

	gizmoMode = GIZMO_MODE_3D;
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
			pitchGrip->enabled = true;
			yawGrip->enabled = true;
            viewportRotateGrip->enabled = true;
            
            if(gizmoMode == GIZMO_MODE_3D) {
                rollGrip->enabled = true;
                rollCircle->visible = true;
                rollCircle->visible = true;
                outerCircle->setColor(1.0, 1.0, 1.0, 1.0);
            } else {
                rollCircle->visible = false;
                rollCircle->visible = false;
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

void TransformGizmo::transfromSelectedEntities(const Vector3 &move, const Vector3 &scale, Number rotate) {
	for(int i=0; i < selectedEntities.size(); i++) {
		selectedEntities[i]->Translate(move);
		selectedEntities[i]->setScale(selectedEntities[i]->getScale() + scale);
		
		Quaternion q;
		Quaternion currentRotation = selectedEntities[i]->getRotationQuat();
					
		Vector3 axisVector = transformConstraint;
		axisVector = currentRotation.Inverse().applyTo(axisVector);
		
		q.fromAngleAxis(rotate, axisVector);
		selectedEntities[i]->setRotationByQuaternion(currentRotation * q);
	}
}

Number TransformGizmo::getTransformPlaneAngle() {

	Number planeDistance = 0;
	
	Ray gizmoRay;
	gizmoRay.origin = getConcatenatedMatrix().getPosition();
	gizmoRay.direction = transformPlane * -1;
					
	if(transformPlane.x > 0) {
		planeDistance = getPosition().x;
	} else if(transformPlane.y > 0.0) {
		planeDistance = getPosition().y;	
	} else if(transformPlane.z > 0.0) {
		planeDistance = getPosition().z;	
	}
						
	Vector3 gizmoIntersect = gizmoRay.planeIntersectPoint(transformPlane, planeDistance);
	
	Ray ray = targetScene->projectRayFromCameraAndViewportCoordinate(targetCamera, coreInput->getMousePosition());	
	Vector3 mouseIntersect = ray.planeIntersectPoint(transformPlane, planeDistance);

	Vector2 planePosition;
	
	if(transformPlane.x > 0) {
		planePosition.x = mouseIntersect.z - gizmoIntersect.z;
		planePosition.y = mouseIntersect.y - gizmoIntersect.y;
	} else if(transformPlane.y > 0.0) {
		planePosition.x = mouseIntersect.x - gizmoIntersect.x;
		planePosition.y = mouseIntersect.z - gizmoIntersect.z;
	} else if(transformPlane.z > 0.0) {
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
                
                if(gizmoMode == GIZMO_MODE_3D) {
                    transformPlane = Vector3(1.0, 0.0, 0.0);
                } else {
                    transformPlane = Vector3(0.0, 0.0, 1.0);
                }
                
				startingAngle = getTransformPlaneAngle();
			}
		} else 	if(event->getDispatcher() == yawGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				transforming = true;
				transformConstraint = Vector3(0.0, 1.0, 0.0);
                
                if(gizmoMode == GIZMO_MODE_3D) {
                    transformPlane = Vector3(0.0, 1.0, 0.0);
                } else {
                    transformPlane = Vector3(0.0, 0.0, 1.0);
                }
                
				startingAngle = getTransformPlaneAngle();
			}
		} else 	if(event->getDispatcher() == rollGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				transforming = true;
				transformConstraint = Vector3(0.0, 0.0, -1.0);
				transformPlane = Vector3(0.0, 0.0, 1.0);
				startingAngle = getTransformPlaneAngle();
			}
		} else 	if(event->getDispatcher() == viewportRotateGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
                if(gizmoMode == GIZMO_MODE_2D) {
                    transforming = true;
                    transformConstraint = Vector3(0.0, 0.0, -1.0);
                    transformPlane = Vector3(0.0, 0.0, 1.0);
                    startingAngle = getTransformPlaneAngle();
                }
			}
		}


		if(event->getDispatcher() == xTransformGrip) {
			if(event->getEventCode() == InputEvent::EVENT_MOUSEDOWN) {
				transforming = true;
				transformConstraint = Vector3(1.0, 0.0, 0.0);
                
                if(gizmoMode == GIZMO_MODE_3D) {
                    transformPlane = Vector3(0.0, 1.0, 0.0);
                } else {
                    transformPlane = Vector3(0.0, 0.0, 1.0);
                }
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
		}
	}
	
	if(event->getDispatcher() == coreInput && transforming) {
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEMOVE:
			{
				switch(mode) {
					case TRANSFORM_MOVE:
					{
						Vector3 newPoint = getTransformPlanePosition();
						transfromSelectedEntities((newPoint-startingPoint) * transformConstraint, Vector3(0.0, 0.0, 0.0), 0.0);
						startingPoint = newPoint;
					}
					break;
					case TRANSFORM_SCALE:
					{
						Vector3 newPoint = getTransformPlanePosition();
						transfromSelectedEntities(Vector3(0.0, 0.0, 0.0), ((newPoint-startingPoint) * transformConstraint), 0.0);
						startingPoint = newPoint;					
					}
					break;
					case TRANSFORM_ROTATE:
					{
						Number newAngle = getTransformPlaneAngle();
						transfromSelectedEntities(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 0.0), newAngle - startingAngle);
						startingAngle = newAngle;						
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
    
    if(selectedEntities.size() > 0) {
        Vector3 centerPoint;
        for(int i=0; i < selectedEntities.size(); i++) {
            centerPoint += selectedEntities[i]->getConcatenatedMatrix().getPosition();
        }
        centerPoint = centerPoint / selectedEntities.size();
        setPosition(centerPoint);
    }
    
    viewportRotateGripBase->lookAt(targetCamera->getPosition());
	Number scale = getPosition().distance(targetCamera->getPosition()) * 0.1;
    if(scale < 0.0) {
        scale = 0.0;
    }
	setScale(scale, scale, scale);
}

