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
#include "PolySceneLabel.h"
#include "PolyUIElement.h"
#include "PolyUIEvent.h"
#include "PolyUIImageButton.h"
#include "PolyFont.h"
#include "PolyInputKeys.h"
#include "PolyUIBox.h"
#include "PolyTween.h"

namespace Polycode {

	class _PolyExport UIWindow : public UIElement {
		public:
			UIWindow(String windowName, Number width, Number height);
			virtual ~UIWindow();
			
			void showWindow();
			void hideWindow();
			void onKeyDown(PolyKEY key, wchar_t charCode);
			virtual void onClose();
			void onLoseFocus();
			
			void setWindowSize(Number w, Number h);
			
			void setWindowCaption(String caption);
			
			void onMouseDown(Number x, Number y);
					
			virtual void handleEvent(Event *event);
		
			Number padding;
			Number topPadding;
		
			bool closeOnEscape;
		
		protected:				
			
			Number closeIconX;
			Number closeIconY;
			
			SceneLabel *titleLabel;
		
			Font *font;
			UIImageButton *closeBtn;
			UIBox *windowRect;
			Entity *titlebarRect;
			void resetTween();
	};
}