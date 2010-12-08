
#pragma once 

#include <Polycode.h>
#include <PolycodeUI.h>
#include "PolycodeProject.h"

using namespace Polycode;


class BrowserUserData  {
public:
	OSFileEntry fileEntry;
};


class PolycodeProjectBrowser : public ScreenEntity {
public:
	PolycodeProjectBrowser();
	~PolycodeProjectBrowser();
	
	void Resize(int newWidth, int newHeight);
	void addProject(PolycodeProject *project);
	
	void handleEvent(Event *event);
	
	void parseFolderIntoNode(UITree *node, string spath);
	
	BrowserUserData *getSelectedData() { return selectedData; }
	
protected:
	
		BrowserUserData *selectedData;
		UITreeContainer *treeContainer;
};	