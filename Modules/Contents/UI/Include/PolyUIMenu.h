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
#include "PolyUIElement.h"
#include "PolyScreenLabel.h"
#include "PolyUIBox.h"

namespace Polycode {


	class _PolyExport UIMenuItem : public UIElement {
		public:
			UIMenuItem(String label, String _id, void *data, Number comboWidth, Number comboHeight);
			~UIMenuItem();
			
			void *data;
			String label;
			String _id;
			ScreenLabel *itemLabel;
	};

	class _PolyExport UIMenu : public UIElement {
		public:
			UIMenu(Number menuWidth);
			~UIMenu();
			
			UIMenuItem *addOption(String label, String _id, void *data = NULL);
			void Resize(Number width, Number height);

			void Update();
			
			UIMenuItem *getSelectedItem();

			void handleEvent(Event *event);
			
		protected:
		
			Vector2 initialMouse;
		
			Number menuItemHeight;
			Number menuWidth;
			
			Number selectorPadding;
			
			Number nextItemHeight;
			
			int selectedOffset;
			
			UIBox *dropDownBox;			
			UIBox *selectorBox;
			
			Number paddingX;
			Number paddingY;
			
			bool ignoreMouse;
						
			std::vector<UIMenuItem*> items;
			
	};


	class _PolyExport UIGlobalMenu : public ScreenEntity {
		public:
			UIGlobalMenu();
			~UIGlobalMenu();
			
			void handleEvent(Event *event);
			
			void Update();
			
			void hideMenu();
			UIMenu *showMenu(Number x, Number y, Number width);
			
			UIMenu *showMenuAtMouse(Number width);
			
			Number defaultMenuWidth;
			
		protected:			
		
			bool willHideMenu;
			UIMenu *currentMenu;
	};

	

	
}
