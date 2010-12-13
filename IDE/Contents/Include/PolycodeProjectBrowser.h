
#pragma once 

#include <Polycode.h>
#include <PolycodeUI.h>
#include "PolycodeProject.h"

using namespace Polycode;


class BrowserUserData  {
public:
	OSFileEntry fileEntry;
	int type;
};


class PolycodeProjectBrowser : public ScreenEntity {
public:
	PolycodeProjectBrowser();
	~PolycodeProjectBrowser();
	
	void Resize(int newWidth, int newHeight);
	void addProject(PolycodeProject *project);
	
	void handleEvent(Event *event);
	
	void parseFolderIntoNode(UITree *node, String spath);
	
	BrowserUserData *getSelectedData() { return selectedData; }
	
protected:
	
		BrowserUserData *selectedData;
		UITreeContainer *treeContainer;
};	