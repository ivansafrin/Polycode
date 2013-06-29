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

#include <Polycode.h>
#include <PolycodeUI.h>
#include "PolycodeProject.h"
#include "OSBasics.h"

using namespace Polycode;


class BrowserUserData  {
public:
	BrowserUserData() { parentProject = NULL; }
	OSFileEntry fileEntry;
	PolycodeProject *parentProject;
	int type;
};


class PolycodeProjectBrowserEvent : public Event {
	public:
		PolycodeProjectBrowserEvent() : Event() {eventType = "PolycodeProjectBrowserEvent";}
		~PolycodeProjectBrowserEvent() {}
		static const int HANDLE_MENU_COMMAND = 0;

		String command;

};

class PolycodeProjectBrowser : public UIElement {
public:
	PolycodeProjectBrowser();
	~PolycodeProjectBrowser();

	void Resize(Number width, Number height);
	void addProject(PolycodeProject *project);
	void removeProject(PolycodeProject *project);

	UITree *nodeHasName(UITree *node, String name);
	bool listHasFileEntry(vector<OSFileEntry> files, OSFileEntry fileEntry);

	void refreshProject(PolycodeProject *project);

	void handleEvent(Event *event);

	void parseFolderIntoNode(UITree *node, String spath, PolycodeProject *parentProject);



	BrowserUserData *getSelectedData() { return selectedData; }

	UITreeContainer *treeContainer;

protected:

		ScreenShape *headerBg;

		UIMenu *contextMenu;

		BrowserUserData *selectedData;
};
