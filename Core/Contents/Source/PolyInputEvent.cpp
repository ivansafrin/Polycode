/*
 *  PolyInputEvent.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 3/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyInputEvent.h"

namespace Polycode {

InputEvent::InputEvent(Vector2 mousePosition, int timestamp) : Event() {
	this->mousePosition = mousePosition;
	this->timestamp = timestamp;
	eventType = "InputEvent";
}

InputEvent::InputEvent(TAUKey key, wchar_t charCode, int timestamp) : Event() {
	this->key = key;
	this->charCode = charCode;
	this->timestamp = timestamp;
}

/*
InputEvent::InputEvent(TAUKey key, int timestamp)  : Event() {
	this->key = key;
	this->timestamp = timestamp;	
}
*/

InputEvent::~InputEvent() {

}

}