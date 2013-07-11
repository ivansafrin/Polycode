/*
 Copyright (C) 2012 by Ivan Safrin
 
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
#include "PolyScreenShape.h"
#include "PolyUIElement.h"

namespace Polycode {
	
	class CoreInput;
	
	class _PolyExport UIVSizer : public UIElement {
		public:
			UIVSizer(Number width, Number height, Number mainHeight, bool topSizer);
			~UIVSizer();
			
			void handleEvent(Event *event);
			
			void setMainHeight(Number height);
			Number getMainHeight();
			
			void addTopChild(UIElement *element);
			void addBottomChild(UIElement *element);			
			void Resize(Number width, Number height);
			
			void updateSizer();
			
		protected:
		
			ScreenEntity *childElements;			
			Number mainHeight;
			
			bool topSizer;
			
			CoreInput *coreInput;
			
			bool resizing;
			Number baseMouseY;
			Number baseMainHeight;
			
			ScreenShape *separatorHitShape;
			ScreenShape *separatorBgShape;
			
			UIElement *firstElement;
			UIElement *secondElement;			
	};
	
}