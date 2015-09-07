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
#include "PolySceneImage.h"
#include "PolySceneLabel.h"
#include "PolyScenePrimitive.h"
#include "PolyEntity.h"
#include "PolyUIEvent.h"
#include "PolyUIBox.h"
#include "PolyUIMenu.h"
#include "PolyUIElement.h"
#include "PolyFont.h"

namespace Polycode {

	class _PolyExport UIComboBoxItem {
		public:
			UIComboBoxItem(String label, void *data);
			virtual ~UIComboBoxItem();
			
			void *data;
			String label;
	};

	class _PolyExport UIComboBox : public UIElement {
		public:
			UIComboBox(UIGlobalMenu *globalMenu, Number comboWidth);
			~UIComboBox();
			
			void toggleDropDown();
		
			void clearItems();
			
			int addComboItem(String itemName);			
			int addComboItem(String itemName, void *data);
						
			int getSelectedIndex();
			UIComboBoxItem *getSelectedItem();
			void setSelectedIndex(unsigned int newIndex, bool suppressChangeEvent = false);
			void handleEvent(Event *event);
			
			void Resize(Number width, Number height);
			
			unsigned int getNumItems();
			UIComboBoxItem *getItemAtIndex(unsigned int index);
							
		private:
		
			UIMenu *dropDownMenu;
		
			UIGlobalMenu *globalMenu;
		
			std::vector<UIComboBoxItem*> items;
			int selectedIndex;
			
			UILabel *selectedLabel;
			Number comboHeight;
			Number comboWidth;
			Number dropDownX;
			Number dropDownY;
						
			int selectedOffset;
						
			Number nextItemHeight;

			UIBox *bgBox;
			UIImage *dropDownImage;
	};
}