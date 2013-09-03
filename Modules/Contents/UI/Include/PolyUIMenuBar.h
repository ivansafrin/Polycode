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
#include "PolySceneLabel.h"
#include "PolyScenePrimitive.h"
#include "PolyEntity.h"
#include "PolyUIEvent.h"
#include "PolyUIBox.h"
#include "PolyUIMenu.h"
#include "PolyUIElement.h"
#include "PolyInputEvent.h"

namespace Polycode {

	class UIMenuBarEntryItem {
		public:
			UIMenuBarEntryItem(String name, String code, PolyKEY shortCut1, PolyKEY shortCut2);
			String name;	
			String code;

			bool checkShortCut(PolyKEY shortCut);

			PolyKEY shortCut1;
			PolyKEY shortCut2;

	};

	class _PolyExport UIMenuBarEntry : public UIElement {
		public:
			UIMenuBarEntry(String name);
			virtual ~UIMenuBarEntry();		
			void addItem(String name, String code, PolyKEY shortCut1 = KEY_UNKNOWN, PolyKEY shortCut2 = KEY_UNKNOWN);

			void Select();
			void Deselect();

			UIRect *bg;
			SceneLabel *label;

			std::vector<UIMenuBarEntryItem> items;

	};
	
	class _PolyExport UIMenuBar : public UIElement {
		public:
			UIMenuBar(int width, UIGlobalMenu *globalMenu);
			virtual ~UIMenuBar();

			void handleEvent(Event *event);	

			void showMenuForEntry(UIMenuBarEntry *entry);
			void Resize(Number width, Number height);
			UIMenuBarEntry *addMenuBarEntry(String name);
			
			String getSelectedItem();
		protected:
			UIMenu *dropMenu;
			UIGlobalMenu *globalMenu;
			int entryOffset;
			
			bool holdingMouse;

			String selectedItem;
			UIRect *bgShape;
			std::vector<UIMenuBarEntry*> entries;
			UIMenuBarEntry *currentEntry;
	};
}
