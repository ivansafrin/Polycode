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
#include "PolyScreenImage.h"
#include "PolyScreenLabel.h"
#include "PolyScreenShape.h"
#include "PolyScreenEntity.h"
#include "PolyUIEvent.h"
#include "PolyUITextInput.h"
#include "PolyUIWindow.h"
#include "PolyUIHSlider.h"
#include "PolyUIBox.h"
#include "PolyUIElement.h"
#include "PolyFont.h"

namespace Polycode {


	class _PolyExport UIColorPicker : public UIWindow {
		public:
			UIColorPicker();
			~UIColorPicker();
			
			void updateSelectedColor(bool updateTextFields=true, bool updateHue = true, bool updateSV=true);
			void setHue(Number hueNum);			
			void handleEvent(Event *event);
			void setSaturationAndValue(Number S, Number V);
			
			void updateColorFromMainSelector();
			void updateColorFromHueSelector();
			void rebuildFromTextInputs();
			
			void cancelColorListeners();
			
			void Update();			
			void onClose();
			
			void setPickerColor(Color newColor);
			
			Color getSelectedColor();
			
		protected:
		
			Vector2 lastMainSelectorPosition;
			Number lastHueSelectorPosition;
			
			bool suppressTextChangeEvent;
		
			Color selectedColor;
		
			Number colorAlpha;
			
			Number currentH;
			Number currentS;
			Number currentV;
			
			UITextInput *rTextInput;
			UITextInput *gTextInput;
			UITextInput *bTextInput;
			UITextInput *aTextInput;						
									
			ScreenImage *mainFrame;
			ScreenImage *mainBg;			
			ScreenImage *hueFrame;
			ScreenImage *hueSelector;
			ScreenImage *mainSelector;	
			
			UIHSlider *alphaSlider;
			
			ScreenShape *mainColorRect;
			
			vector<ScreenLabel *> junkLabels; // Kept only to delete
	};

	class _PolyExport UIColorBox : public UIElement {
		public:
			UIColorBox(UIColorPicker *colorPicker, Color initialColor, Number width, Number height);
			virtual ~UIColorBox();
			
			Color getSelectedColor();
			
			void setBoxColor(Color newColor);
			void showColorPicker();			
			void handleEvent(Event *event);
				
		protected:
		
		
			bool listeningToPicker;
			UIColorPicker *colorPicker;
			
			Color selectedColor;
				
			UIBox *frameImage;
			ScreenShape *bgImage;
			ScreenShape *colorShape;			
		
	};
}