/*
 *  PolyCoreInput.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/27/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Core

#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include "PolyVector2.h"
#include "PolyEventDispatcher.h"
#include "PolyInputEvent.h"
#include "PolyInputKeys.h"

namespace Polycode {
	
	class _PolyExport CoreInput : public EventDispatcher {
		
		friend class PolyCore;
		
	public:
		
		CoreInput();
		~CoreInput();
		
		static const int MOUSE_BUTTON1 = 0;
		static const int MOUSE_BUTTON2 = 1;
		static const int MOUSE_BUTTON3 = 2;
		
		
		void mouseWheelUp(int ticks);
		void mouseWheelDown(int ticks);
		bool getMouseButtonState(int mouseButton);		
		void setMouseButtonState(int mouseButton, bool state, int ticks);
		void setMousePosition(int x, int y, int ticks);
		Vector2 getMousePosition();
		void setKeyState(TAUKey keyCode, wchar_t code, bool newState, int ticks);

		bool getKeyState(TAUKey keyCode);
		
		Vector2 getMouseDelta();
		void setDeltaPosition(int x, int y);
		
		
		
		static InputEvent *createEvent(Event *event){ return (InputEvent*)event; }
		
	protected:
		
		bool keyboardState[512];
		bool mouseButtons[3];
		Vector2 mousePosition;
		Vector2 deltaMousePosition;
	};
	
}