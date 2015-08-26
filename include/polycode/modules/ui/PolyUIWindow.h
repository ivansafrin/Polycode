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

#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyScenePrimitive.h"
#include "polycode/core/PolySceneLabel.h"
#include "polycode/modules/ui/PolyUIElement.h"
#include "polycode/modules/ui/PolyUIEvent.h"
#include "polycode/modules/ui/PolyUIImageButton.h"
#include "polycode/core/PolyFont.h"
#include "polycode/core/PolyInputKeys.h"
#include "polycode/modules/ui/PolyUIBox.h"
#include "polycode/core/PolyTween.h"

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