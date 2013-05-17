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
#include "PolyScreenLabel.h"
#include "PolyScreenShape.h"
#include "PolyScreenEntity.h"
#include "PolyUIEvent.h"
#include "PolyUIBox.h"
#include "PolyUIElement.h"
#include "PolyInputEvent.h"
#include "PolyFont.h"

namespace Polycode {

	class _PolyExport UIHSlider : public UIElement {
		public:
			UIHSlider(Number start, Number end, Number width);
			~UIHSlider();		
			void handleEvent(Event *event);
			void Update();
			
			void setSliderValue(Number val);
			Number getSliderValue();			
			
		private:
		
			Number gripPos;
			
			bool dragging;
			
			Number labelXPos;
			Number labelYPos;
			UIBox *bgRect;
			ScreenImage *gripRect;
			
			Number sliderValue;
			Number startValue;
			Number endValue;
			Number sliderWidth;
			
			ScreenShape *bgHitBox;
			ScreenLabel *buttonLabel;
			bool pressedDown;
	};
}