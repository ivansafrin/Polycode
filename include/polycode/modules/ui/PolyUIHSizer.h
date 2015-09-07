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
#include "PolyScenePrimitive.h"
#include "PolyUIElement.h"

namespace Polycode {
	
	class CoreInput;
	
	class _PolyExport UIHSizer : public UIElement {
		public:
			UIHSizer(Number width, Number height, Number mainWidth, bool leftSizer);
			virtual ~UIHSizer();
			
			void handleEvent(Event *event);
			
			void setMainWidth(Number width);
			void setMainWidthWithMinimum(Number newWidth);
						
			Number getMainWidth();
			
			void addLeftChild(UIElement *element);
			void addRightChild(UIElement *element);			
			
			UIElement *getLeftChild();
			UIElement *getRightChild();	
			void removeLeftChild();
			void removeRightChild();
						
			void Resize(Number width, Number height);
			
			void updateSizer();
			
			void setMinimumSize(Number minimumSize);
			
			void setProportionalResize(bool val);
			
		protected:
		
			bool proportionalResize;
		
			Entity *childElements;			
			Number mainWidth;
			
			CoreInput *coreInput;
			
			Number minimumSize;
			
			bool resizing;
			Number baseMouseX;
			Number baseMainWidth;
			
			bool leftSizer;
			
			UIRect *separatorHitShape;
			UIRect *separatorBgShape;
			
			UIElement *firstElement;
			UIElement *secondElement;			
	};
	
}