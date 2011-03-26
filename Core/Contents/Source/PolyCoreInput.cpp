/*
 *  PolyCoreInput.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/27/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "PolyCoreInput.h"

namespace Polycode {
	
	CoreInput::CoreInput() : EventDispatcher() {
		mouseButtons[0] = false;
		mouseButtons[1] = false;
		mouseButtons[2] = false;
		
		for(int i=0; i < 512; i++) {
			keyboardState[i] = 0;
		}
	}
	
	CoreInput::~CoreInput() {
	}
	
	bool CoreInput::getMouseButtonState(int mouseButton) {
		return mouseButtons[mouseButton];
	}
	
	void CoreInput::setMouseButtonState(int mouseButton, bool state, int ticks) {
		InputEvent *evt = new InputEvent(mousePosition, ticks);
		evt->mouseButton = mouseButton;		
		if(state)
			dispatchEvent(evt, InputEvent::EVENT_MOUSEDOWN);
		else
			dispatchEvent(evt, InputEvent::EVENT_MOUSEUP);
		mouseButtons[mouseButton] = state;
	}
	
	void CoreInput::mouseWheelDown(int ticks) {
		InputEvent *evt = new InputEvent(mousePosition, ticks);
		dispatchEvent(evt, InputEvent::EVENT_MOUSEWHEEL_DOWN);				
	}
	
	void CoreInput::mouseWheelUp(int ticks) {
		InputEvent *evt = new InputEvent(mousePosition, ticks);
		dispatchEvent(evt, InputEvent::EVENT_MOUSEWHEEL_UP);		
	}
	
	void CoreInput::setMousePosition(int x, int y, int ticks) {
		mousePosition.x = x;
		mousePosition.y = y;
		InputEvent *evt = new InputEvent(mousePosition, ticks);
		dispatchEvent(evt, InputEvent::EVENT_MOUSEMOVE);
	}
	
	Vector2 CoreInput::getMouseDelta() {
		return deltaMousePosition;
	}
	
	void CoreInput::setDeltaPosition(int x, int y) {
		deltaMousePosition.x = (Number)x;
		deltaMousePosition.y = (Number)y;
	}

	Vector2 CoreInput::getMousePosition() {
		return mousePosition;
	}
	
	bool CoreInput::getKeyState(TAUKey keyCode) {
		if(keyCode < 512)
			return keyboardState[keyCode];
		else
			return false;
	}
	
	void CoreInput::setKeyState(TAUKey keyCode, wchar_t code, bool newState, int ticks) {
		InputEvent *evt = new InputEvent(keyCode, code, ticks);
		if(keyCode < 512)
			keyboardState[keyCode] = newState;
		if(newState) {
			dispatchEvent(evt, InputEvent::EVENT_KEYDOWN);
		} else {
			dispatchEvent(evt, InputEvent::EVENT_KEYUP);
		}
	}
}