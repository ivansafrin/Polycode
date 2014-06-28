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

	class _PolyExport UITabButton : public UIElement {
	public:
		UITabButton(String caption);
		~UITabButton();

		void setActive(bool val);
		void handleEvent(Event *event);
		void updateLabel(String caption);
	protected:
		UIImage *bgRect;
		UILabel *tabLabel;
	};

	class _PolyExport UITab : public UIElement{
	public:
		UITab(String caption, UIElement *tabContent);
		~UITab();

		void Resize(Number width, Number height);

		void setActive(bool val);
		bool isActive();

		void setContent(UIElement *newContent);
		UIElement *getContent();
		UILabel *getTabLabel();

		String getTabName();
		void setTabName(String newName);

		UITabButton *getTabButton();

	protected:
		bool active;
		String tabName;

		UITabButton *button;
		UIElement *content;
	};

	class _PolyExport UITabFrame : public UIElement {
	public:
		UITabFrame(UITab *tab, Number width = 320, Number height = 200);
		~UITabFrame();

		void showTab(UITab *tab);
		void showTab(unsigned int tabIndex);
		void addNewTab(UITab *newTab);
		std::vector<UITab *> getTabs();

		virtual void Update() {}
		
		UITab *getActiveTab();
		unsigned int getActiveTabIndex();
		unsigned int getTabIndex(UITab *tab);

		void handleEvent(Event *event);

		void Resize(Number width, Number height);

		void setTabButtonAnchorPosition(Vector2 _pos);
		void setTabButtonAnchorPosition(Number x, Number y);
		Vector2 getTabButtonAnchorPosition();

		UITab *UITabFrame::getTabAtIndex(unsigned int index);
		unsigned int getNumTabs();

	protected:
		UITabButton *menu;
		UIElement	*tabButtonAnchor;

		UITab *activeTab;
		std::vector<UITabButton *>	tabButtons;
		std::vector<UITab *>		tabs;
	};
}