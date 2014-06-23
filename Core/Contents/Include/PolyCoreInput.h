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
	
	/**
	* Joystick info.
	*/
	class JoystickInfo : public PolyBase {
		public:
			JoystickInfo();
			
			/**
			* State array of the joystick axis knobs.
			*/
			float joystickAxisState[32];
			
			/**
			* State array of the joystick buttons.
			*/			
			bool joystickButtonState[64];
			
			/**
			* Internal device ID.
			*/			
			unsigned int deviceID;		
			
			/**
			* Joystick index.
			*/						
			unsigned int deviceIndex;
	};
	
	class InputEvent;
	class TouchInfo;

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
		* Returns the state of the specified joystick button for the specified joystick index. If the joystick index is invalid, returns false
		* @param joystickIndex Joystick index to check the state on
		* @param button Joystick button to check the stat of.
		* @return True if the button is pressed, false otherwise or if joystick index is invalid.
		*/						
		bool getJoystickButtonState(int joystickIndex, int button);
		
		/** 
		* Returns the value of the specified joystick axis for the specified joystick index. If the joystick index is invalid, returns 0
		* @param joystickIndex Joystick index to check the state on
		* @param axis Joystick axis to get the value of.
		* @return Value of the joystick axis (0 if joystickIndex is invalid)
		*/						
		Number getJoystickAxisValue(int joystickIndex, int axis);
		
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

		/**
		* Returns the current number of active joysticks.
		* @return Number of active joysticks.
		*/		
		unsigned int getNumJoysticks();
		
		/**
		* Returns joystick info for specified joystick index.
		* @param index Joystick index. Returns NULL if index is invalid.
		* @return Joystick info for specified joystick.
		* @see JoystickInfo
		*/
		JoystickInfo *getJoystickInfoByIndex(unsigned int index);

		/**
         * Returns joystick info for specified joystick device ID. Returns NULL if the joystick device ID is invalid.
         * @param deviceID Joystick device ID.
         * @return Joystick info for specified joystick.
         * @see JoystickInfo
         */
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
		
		void touchesBegan(TouchInfo touch, std::vector<TouchInfo> touches, int ticks);
		void touchesMoved(TouchInfo touch, std::vector<TouchInfo> touches, int ticks);
		void touchesEnded(TouchInfo touch, std::vector<TouchInfo> touches, int ticks);
				
		static InputEvent *createEvent(Event *event){ return (InputEvent*)event; }
		
		/**
		* If set to true, will fire touch events on mouse input. Defaults to false.
		*/
		bool simulateTouchWithMouse;

        /**
         * If set to true, will fire mouse events on touch input. Defaults to false.
         */
		bool simulateMouseWithTouch;
        
        /**
         * If set to true, will not send touch events outside of the screen as define by current core resolution. Defaults to false.
         */
		bool ignoreOffScreenTouch;	
		
		void clearInput();
		
        /**
        * If set to false, will ignore repeat system keypress events if a key is already pressed-down. Defaults to true.
        */
        bool keyRepeat;
		
		std::vector<JoystickInfo> joysticks;
		bool keyboardState[512];
		bool mouseButtons[3];
		Vector2 mousePosition;
		Vector2 deltaMousePosition;
	};
	
}
