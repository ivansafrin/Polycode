/*
Copyright (C) 2014 by Joachim Meyer

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
#include "PolyUIElement.h"

namespace Polycode {

	/**
	* Is used to switch to a certain tab
	*/
	class _PolyExport UITabButton : public UIElement {
	public:
		/**
		* Creates a new UITabButton by a caption
		* @param caption String used for the label
		*/
		UITabButton(String caption);
		~UITabButton();

		/**
		* Sets the button's state
		* @param val If true the button is selected, if false not
		*/
		void setActive(bool val);
		void handleEvent(Event *event);

		/**
		* Updates the label to the given String
		* @param caption A String used as new name
		*/
		void updateLabel(String caption);
	protected:
		UIImage *bgRect;
		UILabel *tabLabel;
	};

	/**
	* A tab used in UITabFrame
	*/
	class _PolyExport UITab : public UIElement{
	public:
		/**
		* Creates a new tab of the given name and content
		* @param caption String used as name
		* @param tabContent A UIElement that has the children you want to have visible in this tab
		*/
		UITab(String caption, UIElement *tabContent);
		~UITab();

		/**
		* Resizes the tab to the given width and height
		* @param width Width value of the tab
		* @param height Height value of the tab
		*/
		void Resize(Number width, Number height);

		/**
		* Set this tab active or inactive
		* @param val True if tab should be visible, false if not
		*/
		void setActive(bool val);

		/**
		* @return Whether the tab is active or not
		*/
		bool isActive();

		/**
		* Sets new content (old content will be overriden)
		* @param newContent A UIElement that has the children you want to have visible in this tab
		*/
		void setContent(UIElement *newContent);
		
		/**
		* @return The content of the tab
		*/
		UIElement *getContent();

		/**
		* @return The name of the tab
		*/
		String getTabName();

		/**
		* Sets new name
		* @param newName String that should be the new name
		*/
		void setTabName(String newName);

		/**
		* @return The UITabButton instance used by this tab
		*/
		UITabButton *getTabButton();

	protected:
		bool active;
		String tabName;

		UITabButton *button;
		UIElement *content;
	};

	/**
	* An UI frame in which you can create tabs.
	*/
	class _PolyExport UITabFrame : public UIElement {
	public:
		/**
		* Creates a new tab frame, needs a first tab.
		* @param tab First UITab
		* @param width Width value of the whole frame, if not provided defaulting to 320
		* @param height Height value of the whole frame, if not provided defaulting to 200
		*/
		UITabFrame(UITab *tab, Number width = 320, Number height = 200);
		~UITabFrame();

		/**
		* Brings the given tab to the front
		* @param tab UITab to show
		*/
		void showTab(UITab *tab);
		
		/**
		* Brings the tab of the given index to the front
		* @param tabIndex index of the tab in tabs
		*/
		void showTab(unsigned int tabIndex);

		/**
		* Adds a new tab to the frame
		* @param newTab UITab instance to add
		*/
		void addNewTab(UITab *newTab);

		/**
		* @return std::vector of the tabs in the frame
		*/
		std::vector<UITab *> getTabs();

		virtual void Update() {}
		
		/**
		* @return Active tab
		*/
		UITab *getActiveTab();

		/**
		* @return Index of the active tab
		*/
		unsigned int getActiveTabIndex();

		/**
		* Returns the index of a given UITab
		* @param tab A UITab instance of which you want to get the index
		* @return Index of the given UITab
		*/
		unsigned int getTabIndex(UITab *tab);

		/**
		* Returns the the tab of the given index
		* @param index Index of the UITab to return
		* @return UITab at index
		*/
		UITab *UITabFrame::getTabAtIndex(unsigned int index);

		/**
		* @return How many tabs in the frame are - as unsigned int
		*/
		unsigned int getNumTabs();

		void handleEvent(Event *event);

		/**
		* Resizes the tab frame to the given width and height
		* @param width Width value of the whole frame,
		* @param height Height value of the whole frame
		*/
		void Resize(Number width, Number height);

		/**
		* Sets the position of the tab button anchor (all the tab buttons positions are relative to this)
		* @param _pos A Vector2 of the new position
		*/
		void setTabButtonAnchorPosition(Vector2 _pos);

		/**
		* Sets the position of the tab button anchor (all the tab buttons positions are relative to this)
		* @param x X-coordinate of the new position
		* @param y Y-coordinate of the new position
		*/
		void setTabButtonAnchorPosition(Number x, Number y);

		/**
		* Returns the position of the tab button anchor (all the tab buttons positions are relative to this)
		* @return Position of the tab button anchor
		*/
		Vector2 getTabButtonAnchorPosition();

	protected:
		UIElement	*tabButtonAnchor;

		UITab *activeTab;
		std::vector<UITabButton *>	tabButtons;
		std::vector<UITab *>		tabs;
	};
}