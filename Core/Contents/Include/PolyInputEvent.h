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
#include "PolyGlobals.h"
#include "PolyEvent.h"
#include "PolyVector2.h"
#include "PolyInputKeys.h"

namespace Polycode {

class TouchInfo { 
	public:
		int id;
		Vector2 position;
};

/**
* Event dispatched by CoreInput. This event is dispatched by CoreInput when input happens.
*/
class _PolyExport InputEvent : public Event {
	public:
		InputEvent();
		InputEvent(Vector2 mousePosition,int timestamp);
//			InputEvent(PolyKEY key, int timestamp);
		InputEvent(PolyKEY key, wchar_t charCode, int timestamp);
		virtual ~InputEvent();

		// ----------------------------------------------------------------------------------------------------------------
		/** @name Input event types.
		*  Possible input event types dispatched by CoreInput.
		*/
		//@{
		static const int EVENTBASE_INPUTEVENT = 0x400;
		static const int EVENT_MOUSEDOWN = EVENTBASE_INPUTEVENT+0;
		static const int EVENT_MOUSEUP = EVENTBASE_INPUTEVENT+1;
		static const int EVENT_MOUSEMOVE = EVENTBASE_INPUTEVENT+2;
		static const int EVENT_MOUSEOVER = EVENTBASE_INPUTEVENT+3;
		static const int EVENT_MOUSEOUT = EVENTBASE_INPUTEVENT+4;
		static const int EVENT_DOUBLECLICK = EVENTBASE_INPUTEVENT+5;
		static const int EVENT_MOUSEUP_OUTSIDE = EVENTBASE_INPUTEVENT+6;
		static const int EVENT_MOUSEWHEEL_UP = EVENTBASE_INPUTEVENT+7;
		static const int EVENT_MOUSEWHEEL_DOWN = EVENTBASE_INPUTEVENT+8;
		
		static const int EVENT_KEYDOWN = EVENTBASE_INPUTEVENT+13;
		static const int EVENT_KEYUP = EVENTBASE_INPUTEVENT+14;
		
		static const int EVENT_JOYBUTTON_DOWN = EVENTBASE_INPUTEVENT+15;
		static const int EVENT_JOYBUTTON_UP = EVENTBASE_INPUTEVENT+16;
		static const int EVENT_JOYAXIS_MOVED = EVENTBASE_INPUTEVENT+17;
		static const int EVENT_JOYDEVICE_ATTACHED = EVENTBASE_INPUTEVENT+18;
		static const int EVENT_JOYDEVICE_DETACHED = EVENTBASE_INPUTEVENT+19;
		
		static const int EVENT_TOUCHES_BEGAN = EVENTBASE_INPUTEVENT+20;
		static const int EVENT_TOUCHES_MOVED = EVENTBASE_INPUTEVENT+21;
		static const int EVENT_TOUCHES_ENDED = EVENTBASE_INPUTEVENT+22;


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

		std::vector<TouchInfo> touches;
		TouchInfo touch;

		unsigned int joystickDeviceID;
		float joystickAxisValue;
		unsigned int joystickButton;
		unsigned int joystickAxis;
		unsigned int joystickIndex;

	protected:

};

}
