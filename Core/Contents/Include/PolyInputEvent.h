/*
 *  PolyInputEvent.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/28/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Core

#pragma once

#include "PolyGlobals.h"
#include "PolyEvent.h"
#include "PolyVector2.h"
#include "PolyInputKeys.h"

namespace Polycode {

	class _PolyExport InputEvent : public Event {
		public:
			InputEvent(Vector2 mousePosition,int timestamp);
//			InputEvent(TAUKey key, int timestamp);
			InputEvent(TAUKey key, wchar_t charCode, int timestamp);			
			~InputEvent();
		
		static const int EVENT_MOUSEDOWN = 0;
		static const int EVENT_MOUSEUP = 1;
		static const int EVENT_MOUSEMOVE = 2;
		static const int EVENT_MOUSEOVER = 3;
		static const int EVENT_MOUSEOUT = 4;
		static const int EVENT_DOUBLECLICK = 5;
		static const int EVENT_MOUSEUP_OUTSIDE = 6;
		static const int EVENT_MOUSEWHEEL_UP = 7;
		static const int EVENT_MOUSEWHEEL_DOWN = 8;
		
		static const int EVENT_KEYDOWN = 13;
		static const int EVENT_KEYUP = 14;
		
		int mouseButton;
		Vector2 mousePosition;
		TAUKey key;
		
		int keyCode() { return key; }
		
		wchar_t charCode;
		int timestamp;
		
		protected:
		
			
	};
}