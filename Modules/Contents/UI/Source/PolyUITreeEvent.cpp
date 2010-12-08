/*
 *  PolyUITreeEvent.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 7/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyUITreeEvent.h"

using namespace Polycode;

UITreeEvent::UITreeEvent(UITree *selection) {
	this->selection = selection;
	eventType = "UITreeEvent";
}

UITreeEvent::UITreeEvent() {

}

UITreeEvent::~UITreeEvent() {

}
