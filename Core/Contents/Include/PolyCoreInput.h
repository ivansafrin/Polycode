/*
 *  PolyCoreInput.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/27/08.
 *  Copyright 2008 Ivan Safrin. All rights reserved.
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
	
	/**
	* User input event dispatcher. The Core input class is where all of the input events originate. You can add event listeners to this class to listen for user input events or poll it manually to check the state of user input.
	*/
	class _PolyExport CoreInput : public EventDispatcher {
		
		friend class PolyCore;
		
	public:
		
		CoreInput();
		~CoreInput();
		
		/**
		* Left mouse button.
		*/ 
		static const int MOUSE_BUTTON1 = 0;
		
		/**
		* Right mouse button
		*/ 		
		static const int MOUSE_BUTTON2 = 1;
		
		/**
		* Middle mouse button
		*/ 		
		static const int MOUSE_BUTTON3 = 2;
		
		/** 
		* Returns the current mouse position.
		* @return Mouse position as a 2d vector.
		*/		
		Vector2 getMousePosition();
		
		/** 
		* Returns the state of the specified key.
		* @param keyCode The key to check for
		* @return True if the key is pressed, false otherwise.
		*/				
		bool getKeyState(PolyKEY keyCode);		
		
		/** 
		* Returns the current mouse position as delta from last frame.
		* @return Mouse position as a 2d vector delta from last frame.
		*/		
		Vector2 getMouseDelta();	
		
		/** 
		* Returns the state of the specified mouse button
		* @param mouseButton Mouse button to check the state of. Possible values are CoreInput::MOUSE_BUTTON1, CoreInput::MOUSE_BUTTON2 and CoreInput::MOUSE_BUTTON3
		* @return True if the button is pressed, false otherwise.
		*/								
		bool getMouseButtonState(int mouseButton);		

		
		void mouseWheelUp(int ticks);
		void mouseWheelDown(int ticks);
		void setMouseButtonState(int mouseButton, bool state, int ticks);
		void setMousePosition(int x, int y, int ticks);
		void setKeyState(PolyKEY keyCode, wchar_t code, bool newState, int ticks);
		void setDeltaPosition(int x, int y);
		
		
		
		static InputEvent *createEvent(Event *event){ return (InputEvent*)event; }
		
	protected:
		
		bool keyboardState[512];
		bool mouseButtons[3];
		Vector2 mousePosition;
		Vector2 deltaMousePosition;
	};
	
}