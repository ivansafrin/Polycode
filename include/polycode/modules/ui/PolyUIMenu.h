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
#include "PolySceneLabel.h"
#include "PolyUIBox.h"

namespace Polycode {
	class SceneLine;

	/**
	 * An single selectable entry in an UIMenu
	 */
	class _PolyExport UIMenuItem : public UIElement {
		public:
			UIMenuItem(String label, String _id, void *data, Number comboWidth, Number comboHeight);
			virtual ~UIMenuItem();

			virtual bool isSelectable();
        
            String getMenuItemID();
			
			/**
			 * The user-data associated with this entry, as set in UIMenu::addOption()
			 */
			void *data;

			/**
			 * The display text of this entry, as set in UIMenu::addOption()
			 */
			String label;

			/**
			 * The internal ID of this entry, as set in UIMenu::addOption()
			 *
			 * Use this instead of label to identify an option, as the label
			 * may be changed by e.g. translations.
			 */
			String _id;

		protected:
			UIMenuItem();

			SceneLabel *itemLabel;
			friend class UIMenu;
	};

	class _PolyExport UIMenuDivider : public UIMenuItem {
	public:
		UIMenuDivider(Number comboWidth, Number comboHeight);
		~UIMenuDivider();
		bool isSelectable();

	protected:
		SceneLine* line;
	};

	/** 
	 * A dropdown menu.
	 *
	 * Displays a vertical list of text entries that can be clicked.
	 * When clicked, an UIEvent::OK_EVENT event will be dispatched. 
	 * You can then retrieve the selected entry with getSelectedItem()
	 */
	class _PolyExport UIMenu : public UIElement {
		public:
			/**
			 * Create an empty dropdown menu with the given width.
			 * 
			 * Use addOption() to populate the menu.
			 */
			UIMenu(Number menuWidth);
			~UIMenu();
			
			/**
			 * Add a selectable entry to the dropdown.
			 *
			 * @param label The text string that will be displayed to the user for this entry.
			 * @param _id The internal ID of this entry.
			 * @param data A pointer to arbitrary user-data associated with this menu entry.
			 *
			 * @see UIMenuItem
			 */
			UIMenuItem *addOption(String label, String _id, void *data = NULL);

			/**
			 * Add a non-selectable entry to the dropdown
			 * used to separate sections of the menu
			 *
			 */
			UIMenuItem *addDivider();

			/**
			 * Returns the currently selected item.
			 *
			 * This can be used both for retrieving the currently selected item while the menu
			 * is open, as well as retrieving the last selected item after an UIEvent::OK_EVENT
			 * was dispatched.
			 */
			UIMenuItem *getSelectedItem();

			void Resize(Number width, Number height);

			void Update();
			
			void handleEvent(Event *event);

			void fitToScreenVertical();
			
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


	class _PolyExport UIGlobalMenu : public Entity {
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
