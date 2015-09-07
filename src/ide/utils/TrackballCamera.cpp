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


TrackballCamera::TrackballCamera(Camera *targetCamera, Entity *trackballShape) : EventHandler() {
	mouseMode = MOUSE_MODE_IDLE;
	
	this->targetCamera = targetCamera;
	this->trackballShape = trackballShape;
	
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEDOWN);
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEUP);
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEMOVE);	
	trackballShape->addEventListener(this, InputEvent::EVENT_MOUSEUP_OUTSIDE);
	trackballShape->processInputEvents = true;
	
	trackballRotateSpeed = 1.0;
	trackballPanSpeed = 0.6;
	trackballZoomSpeed = 1.0;
	cameraDistance = 10.0;
	
	coreInput = CoreServices::getInstance()->getCore()->getInput();
	
	targetCamera->setPosition(cameraDistance, cameraDistance, cameraDistance);
	trackballRotateEnd = getMouseProjectionOnBall(Vector2(trackballShape->getWidth()/2.0, trackballShape->getHeight()/2.0));
	trackballRotateStart = trackballRotateEnd;
	
	updateCamera();	
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

void TrackballCamera::handleEvent(Event *event) {

	if(event->getDispatcher() == trackballShape) {
		InputEvent *inputEvent = (InputEvent*) event;
		switch(event->getEventCode()) {
			case InputEvent::EVENT_MOUSEDOWN:
				if(coreInput->getKeyState(KEY_LALT) || coreInput->getKeyState(KEY_RALT)) {		
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
						mouseMode = MOUSE_MODE_ORBITING;
						trackballRotateStart = trackballRotateEnd = getMouseProjectionOnBall(inputEvent->getMousePosition());
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
		}		
		return;
	}
}

void TrackballCamera::setOrbitingCenter(const Vector3 &newCenter) {
	orbitingCenter = newCenter;
	updateCamera();	
}

void TrackballCamera::processMouseMovement(const Vector2 &newPosition) {
	switch(mouseMode) {
		case MOUSE_MODE_ORBITING:
		{
			trackballRotateEnd = getMouseProjectionOnBall(newPosition);
			updateCamera();
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
				
				pan = pan + (Vector3(0.0, 1.0, 0.0).setLength(mouseChange.y));
				
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



void TrackballCamera::updateCamera() {

	trackballEye = targetCamera->getPosition() - orbitingCenter;
	trackballEye.setLength(cameraDistance);
	
	
	Number angle = acos(trackballRotateStart.dot(trackballRotateEnd) / trackballRotateStart.length() / trackballRotateEnd.length());
	
	if(angle == angle) {
		Vector3 axis = trackballRotateStart.crossProduct(trackballRotateEnd);
		axis.Normalize();
		Quaternion q;
		
		angle *= trackballRotateSpeed;	
		q.fromAngleAxis(angle, axis);
		
		trackballEye = q.applyTo(trackballEye);
		trackballRotateEnd = q.applyTo(trackballRotateEnd);
		
		trackballRotateStart = trackballRotateEnd;
	}
		
	targetCamera->setPosition(orbitingCenter + trackballEye);	
	targetCamera->lookAt(orbitingCenter);
	
}

Vector3 TrackballCamera::getMouseProjectionOnBall(const Vector2 &mousePosition) {

	Vector3 mouseOnBall = Vector3((mousePosition.x - (trackballShape->getWidth() * 0.5)) / (trackballShape->getWidth() * 0.5),(mousePosition.y - (trackballShape->getHeight() * 0.5)) / (trackballShape->getHeight() * 0.5), 0.0);
	mouseOnBall.x *= -1;	
	
	Number length = mouseOnBall.length();
	

	if (length < sqrt(0.5)) {
		mouseOnBall.z = sqrt(1.0 - length*length);
	} else {
		mouseOnBall.z = 0.5 / length;
	}

	trackballEye = targetCamera->getPosition() - orbitingCenter;
	
	Vector3 projection = Vector3(0.0, 1.0, 0.0).setLength(mouseOnBall.y);		
	
	projection = projection + (Vector3(0.0, 1.0, 0.0).crossProduct(trackballEye).setLength(mouseOnBall.x));				
	
	trackballEye.setLength(mouseOnBall.z);
	projection = projection + (trackballEye);
	
	return projection;	
}
