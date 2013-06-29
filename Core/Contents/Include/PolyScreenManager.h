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
#include "PolyEventDispatcher.h"
#include <vector>

namespace Polycode {

class Screen;

/**
* 2D Screen manager. Must be accessed via CoreServices. Screens are automatically added to the manager when they are created, so there is no need to manually add them.
*/ 
class _PolyExport ScreenManager : public EventDispatcher {
	public:
		ScreenManager();
		~ScreenManager();

		/**
		* Removes a screen from the manager, taking it out of the render loop.
		* @param screen Screen to remove. 
		*/
		void removeScreen(Screen *screen);
		void addScreen(Screen* screen);
		void Update();
		void Render();

		void handleEvent(Event *event);

	private:

		std::vector <Screen*> screens;

};

}
