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
 
#include "TrackballCamera.h"


TrackballCamera::TrackballCamera(Camera *targetCamera, Entity *trackballShape) : EventDispatcher() {
	mouseMode = MOUSE_MODE_IDLE;
	
    rotationDisabled = false;
    
	this->targetCamera = targetCamera;
	this->trackballShape = trackballShape;
	
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);	
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_UP);
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEWHEEL_DOWN);
	trackballShape->processInputEvents = true;
	
	trackballRotateSpeed = 1.0;
	trackballPanSpeed = 0.6;
	trackballZoomSpeed = 1.0;
	cameraDistance = 10.0;
	
	coreInput = CoreServices::getInstance()->getCore()->getInput();
	
	targetCamera->lookAt(orbitingCenter);
	updateCamera();
}

Number TrackballCamera::getCameraDistance() {
    return cameraDistance;
}

TrackballCamera::~TrackballCamera() {
	trackballShape->removeAllHandlersForListener(this);
}

void TrackballCamera::setCameraDistance(Number cameraDistance) {
	this->cameraDistance = cameraDistance;
	updateCamera();
}

Camera *TrackballCamera::getTargetCamera() {
	return targetCamera;
}


bool TrackballCamera::isNavKeyDown() {
	return (coreInput->getKeyState(KEY_LALT) || coreInput->getKeyState(KEY_RALT));
}

void TrackballCamera::handleEvent(Event *event) {
	if(event->getDispatcher() == trackballShape) {
		InputEvent *inputEvent = (InputEvent*) event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				if(isNavKeyDown() || inputEvent->mouseButton == CoreInput::MOUSE_BUTTON3) {
					if(coreInput->getKeyState(KEY_LSHIFT) || coreInput->getKeyState(KEY_RSHIFT)) {
						mouseMode = MOUSE_MODE_PANNING;
						trackBallMouseStart = Vector2(
							inputEvent->getMousePosition().x / trackballShape->getWidth(),
							inputEvent->getMousePosition().y / trackballShape->getHeight()
						);
						trackBallMouseEnd = trackBallMouseStart;
					} else if(coreInput->getKeyState(KEY_LCTRL) || coreInput->getKeyState(KEY_RCTRL)) {
						mouseMode = MOUSE_MODE_ZOOMING;
						trackBallMouseStart = Vector2(
							inputEvent->getMousePosition().x / trackballShape->getWidth(),
							inputEvent->getMousePosition().y / trackballShape->getHeight()
						);
						trackBallMouseEnd = trackBallMouseStart;												
					} else {
                        if(!rotationDisabled) {
                            mouseMode = MOUSE_MODE_ORBITING;
							trackBallMouseStart = trackBallMouseEnd = Vector2(
								inputEvent->getMousePosition().x / trackballShape->getWidth(),
								inputEvent->getMousePosition().y / trackballShape->getHeight()
							);
                        }
					}
				}
			break;
			case InputEvent::EVENT_MOUSEUP:
			case InputEvent::EVENT_MOUSEUP_OUTSIDE:
				mouseMode = MOUSE_MODE_IDLE;
			break;
			case InputEvent::EVENT_MOUSEMOVE:
				processMouseMovement(inputEvent->getMousePosition());
			break;
			case InputEvent::EVENT_MOUSEWHEEL_UP:
				cameraDistance *= 0.9;
				updateCamera();
			break;
			case InputEvent::EVENT_MOUSEWHEEL_DOWN:
				cameraDistance *= 1.1;
				updateCamera();
			break;
		}		
		return;
	}
}

void TrackballCamera::setOrbitingCenter(const Vector3 &newCenter) {
	orbitingCenter = newCenter;
}

void TrackballCamera::processMouseMovement(const Vector2 &newPosition) {
	switch(mouseMode) {
		case MOUSE_MODE_ORBITING:
		{
			trackBallMouseEnd  = Vector2(
							newPosition.x / trackballShape->getWidth(),
							newPosition.y / trackballShape->getHeight()
						);
			updateCamera();
			trackBallMouseStart = trackBallMouseEnd;
		}	
		break;
		case MOUSE_MODE_PANNING:
		{
			trackBallMouseEnd  = Vector2(
							newPosition.x / trackballShape->getWidth(),
							newPosition.y / trackballShape->getHeight()
						);

			
			Vector2 mouseChange = trackBallMouseEnd - trackBallMouseStart;
			Number mouseChangeLength = mouseChange.length() * mouseChange.length();
			if(mouseChangeLength) {
				mouseChange = mouseChange * trackballEye.length() * trackballPanSpeed;
								
				Vector3 pan = trackballEye.crossProduct(Vector3(0.0, 1.0, 0.0)).setLength(mouseChange.x);
				
                Vector3 panCross = trackballEye.crossProduct(Vector3(0.0, 1.0, 0.0)).crossProduct(trackballEye);
                
				pan = pan + (panCross.setLength(mouseChange.y));
                
				targetCamera->Translate(pan);
				orbitingCenter += pan;
				trackBallMouseStart = trackBallMouseEnd;
			}
		}	
		break;		
		case MOUSE_MODE_ZOOMING:
		{
			trackBallMouseEnd  = Vector2(
							newPosition.x / trackballShape->getWidth(),
							newPosition.y / trackballShape->getHeight()
						);
								
			Number factor = 1.0 + ( trackBallMouseEnd.y - trackBallMouseStart.y ) * trackballZoomSpeed;			
			if(factor != 1.0 && factor > 0.0 ) {
				cameraDistance *= factor;
			}
			trackBallMouseStart = trackBallMouseEnd;			
			updateCamera();
		}
		break;
		default:
		break;
	}
}

void TrackballCamera::setCameraPosition(Vector3 cameraPosition) {
    targetCamera->setPosition(cameraPosition);
	targetCamera->lookAt(orbitingCenter);
    updateCamera();
}

Vector3 TrackballCamera::getOribitingCenter() {
    return orbitingCenter;
}

void TrackballCamera::updateCamera() {

	Quaternion currentCamQuat = targetCamera->getRotationQuat();
	trackballEye = targetCamera->getPosition() - orbitingCenter;
	trackballEye.setLength(cameraDistance);

	if(mouseMode == MOUSE_MODE_ORBITING) {
		Vector2 localMouse =  trackBallMouseEnd - trackBallMouseStart;

		Quaternion q;
		// yaw
        q.fromAngleAxis(localMouse.x*-2.0, Vector3(0.0, 1.0, 0.0));
		currentCamQuat = q * currentCamQuat;
		trackballEye = q.applyTo(trackballEye);

		// local pitch
		q.fromAngleAxis(localMouse.y*-2.0, currentCamQuat.applyTo(Vector3(1.0, 0.0, 0.0)));
		currentCamQuat = q * currentCamQuat;
		trackballEye = q.applyTo(trackballEye);
	}
		
	targetCamera->setPosition(orbitingCenter + trackballEye);	
	targetCamera->setRotationByQuaternion(currentCamQuat);
    dispatchEvent(new Event(), Event::CHANGE_EVENT);
}

void TrackballCamera::disableRotation(bool val) {
    rotationDisabled = val;
}

/*
void TrackballCamera::setCameraPosition(Vector3 cameraPosition) {

}
    
bool TrackballCamera::disableRotation(bool val) {
	return false;
}

    
Number TrackballCamera::getCameraDistance() {
	return 0.0;
}

Vector3 TrackballCamera::getOribitingCenter() {
	return Vector3();
}*/
