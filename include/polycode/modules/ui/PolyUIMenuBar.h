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
#include "polycode/core/PolySceneLabel.h"
#include "polycode/core/PolyScenePrimitive.h"
#include "polycode/core/PolyEntity.h"
#include "polycode/core/PolyInputEvent.h"
#include "polycode/core/PolyConfig.h"
#include "polycode/modules/ui/PolyUIEvent.h"
#include "polycode/modules/ui/PolyUIBox.h"
#include "polycode/modules/ui/PolyUIMenu.h"
#include "polycode/modules/ui/PolyUIElement.h"

namespace Polycode {

	class UIMenuBarEntryItem {
		public:
			UIMenuBarEntryItem(CoreInput *input, String name, String code, PolyKEY shortCut1, PolyKEY shortCut2);
			String name;	
			String code;

			bool checkShortCut(PolyKEY shortCut);

			PolyKEY shortCut1;
			PolyKEY shortCut2;
		
			CoreInput *input;

	};

	class _PolyExport UIMenuBarEntry : public UIElement {
		public:
			UIMenuBarEntry(Core *core, ResourcePool *pool, String name, const Color &accentColor, const Color &bgColor);
			virtual ~UIMenuBarEntry();		
			void addItem(String name, String code, PolyKEY shortCut1 = KEY_UNKNOWN, PolyKEY shortCut2 = KEY_UNKNOWN);

			void Select();
			void Deselect();

			UIRect *bg;
			SceneLabel *label;

			std::vector<UIMenuBarEntryItem> items;
		
			Color accentColor;
			Color bgColor;

	};
	
	class _PolyExport UIMenuBar : public UIElement {
		public:
			UIMenuBar(Core *core, ResourcePool *pool, CoreInput *input, int width, UIGlobalMenu *globalMenu);
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
			CoreInput *input;
			bool holdingMouse;
			ResourcePool *resourcePool;

			String selectedItem;
			UIRect *bgShape;
			std::vector<UIMenuBarEntry*> entries;
			UIMenuBarEntry *currentEntry;
		
			Color accentColor;
			Color bgColor;
	};
}
