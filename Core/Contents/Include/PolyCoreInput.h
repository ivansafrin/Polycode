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
#include "PolyString.h"
#include "PolyVector2.h"
#include "PolyInputKeys.h"
#include "PolyEventDispatcher.h"

namespace Polycode {
	
	class JoystickInfo {
		public:
			JoystickInfo();
			
			float joystickAxisState[32];
			bool joystickButtonState[64];
			unsigned int deviceID;		
	};
	
	class InputEvent;

	/**
	* User input event dispatcher. The Core input class is where all of the input events originate. You can add event listeners to this class to listen for user input events or poll it manually to check the state of user input.
	*/
	class _PolyExport CoreInput : public EventDispatcher {
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

		unsigned int getNumJoysticks();
		JoystickInfo *getJoystickInfoByIndex(unsigned int index);

		JoystickInfo *getJoystickInfoByID(unsigned int deviceID);
		void addJoystick(unsigned int deviceID);
		void removeJoystick(unsigned int deviceID);
		void joystickAxisMoved(unsigned int axisID, float value, unsigned int deviceID);
		void joystickButtonDown(unsigned int buttonID, unsigned int deviceID);
		void joystickButtonUp(unsigned int buttonID, unsigned int deviceID);
						
		void mouseWheelUp(int ticks);
		void mouseWheelDown(int ticks);
		void setMouseButtonState(int mouseButton, bool state, int ticks);
		void setMousePosition(int x, int y, int ticks);
		void setKeyState(PolyKEY keyCode, wchar_t code, bool newState, int ticks);
		void setDeltaPosition(int x, int y);
		
		
		
		static InputEvent *createEvent(Event *event){ return (InputEvent*)event; }
		
	protected:
		
		std::vector<JoystickInfo> joysticks;
		bool keyboardState[512];
		bool mouseButtons[3];
		Vector2 mousePosition;
		Vector2 deltaMousePosition;
	};
	
}
