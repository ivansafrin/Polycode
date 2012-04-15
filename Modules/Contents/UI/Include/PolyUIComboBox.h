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
#include "PolyUIBox.h"
#include "PolyFont.h"

namespace Polycode {

	class _PolyExport UIComboBoxItem : public ScreenEntity {
		public:
			UIComboBoxItem(String label, Number comboWidth, Number comboHeight);
			~UIComboBoxItem();
			
			String label;
			ScreenLabel *itemLabel;
	};

	class _PolyExport UIComboBox : public ScreenEntity {
		public:
			UIComboBox(Number comboWidth);
			~UIComboBox();
			
			void toggleDropDown();
		
			void updateVis();
		
			int addComboItem(String itemName);
			int getSelectedIndex();
			void setSelectedIndex(unsigned int newIndex);
			void handleEvent(Event *event);
				
		private:
		
			std::vector<UIComboBoxItem*> items;
			int selectedIndex;
			
			ScreenLabel *selectedLabel;
			Number comboHeight;
			Number comboWidth;
			
			int selectedOffset;
						
			Number nextItemHeight;
			bool isDroppedDown;
			UIBox *dropDownBox;
			UIBox *bgBox;
			UIBox *selectorBox;			
			ScreenImage *dropDownImage;
	};
}