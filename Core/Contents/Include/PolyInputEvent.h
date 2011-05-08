/*
Copyright (C) 2011 by Ivan Safrin

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

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyEvent.h"
#include "PolyVector2.h"
#include "PolyInputKeys.h"

namespace Polycode {

	/**
	* Event dispatched by CoreInput. This event is dispatched by CoreInput when input happens.
	*/
	class _PolyExport InputEvent : public Event {
		public:
			InputEvent(Vector2 mousePosition,int timestamp);
//			InputEvent(PolyKEY key, int timestamp);
			InputEvent(PolyKEY key, wchar_t charCode, int timestamp);			
			~InputEvent();
		
			// ----------------------------------------------------------------------------------------------------------------
			/** @name Input event types.
			*  Possible input event types dispatched by CoreInput.
			*/
			//@{
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
		
		//@}
		// ----------------------------------------------------------------------------------------------------------------
		
		/**
		* If this is a mouse click event, the mouse button that's pressed.
		*/
		int mouseButton;
		
		/**
		* If this is a mouse event, the mouse position.
		*/
		Vector2 mousePosition;
		
		Vector2 getMousePosition() { return mousePosition; }
		PolyKEY getKey() { return key; }
		int getMouseButton() { return mouseButton; }
						
		/**
		* If this is a key event, the key code that's coming down or up.
		*/		
		PolyKEY key;
		
		int keyCode() { return key; }
		
		/**
		* If this is a key press event, this will contain the unicode character that's being typed.
		*/				
		wchar_t charCode;
		int timestamp;
		
		protected:
		
			
	};
}